from typing import Tuple

import numpy as np

from protein_system import maxwell_velocities
from protein_system import COULOMB, SCEE, SCNB, KB, ACC, KRF, CRF, RC
from geometry import angle_and_grad, dihedral_and_grad
from neighbours import pairs_within, min_img

def bond_terms(S, pos):
    i  = S['bonds'][:, 0]
    j  = S['bonds'][:, 1]
    k  = S['bond_k']
    r0 = S['bond_r0']

    r = pos[i] - pos[j]
    d = np.linalg.norm(r, axis=1)
    r_hat = r / d[:, None]

    E = (k * (d - r0) ** 2).sum()

    dEdr = 2.0 * k * (d - r0)
    f = -dEdr[:, None] * r_hat

    F = np.zeros_like(pos)
    np.add.at(F, i, f)
    np.add.at(F, j, -f)

    return E, F

def angle_terms(S, pos):
    A  = S['angles']
    k  = S['angle_k']
    t0 = S['angle_t0']

    t, g = angle_and_grad(pos, A)

    E = (k * (t - t0) ** 2).sum()

    dEdt = 2.0 * k * (t - t0)

    F = np.zeros_like(pos)
    for c in range(3):
        f = -dEdt[:, None] * g[:, c]
        np.add.at(F, A[:, c], f)

    return E, F

def dihedral_terms(S, pos):
    D     = S['dihs']
    k     = S['dih_k']
    n     = S['dih_n']
    phase = S['dih_phase']

    phi, g = dihedral_and_grad(pos, D)

    E = (k * (1 + np.cos(n * phi - phase))).sum()

    dEdphi = -k * n * np.sin(n * phi - phase)

    F = np.zeros_like(pos)
    for c in range(4):
        f = -dEdphi[:, None] * g[:, c]
        np.add.at(F, D[:, c], f)

    return E, F

def nonbonded_terms(S, pos, p_list=None):
    N, box_size = S['N'], S['box']
    q, sigma, epsilon = S['q'], S['sigma'], S['eps']
    F = np.zeros_like(pos)

    # --- regular pairs
    I, J = p_list if p_list is not None else pairs_within(pos, box_size, RC)

    # TODO: exclusion logic 
    key = I.astype(np.int64) * N + J
    ex  = S['excl_keys']
    loc = np.searchsorted(ex, key)
    loc[loc == len(ex)] = 0
    keep = ex[loc] != key
    I, J = I[keep], J[keep]

    # cutoff
    r = min_img(pos[I] - pos[J], box_size)
    d2 = (r * r).sum(axis = 1)
    
    mask = d2 < (RC ** 2)

    I, J, r, d2 = I[mask], J[mask], r[mask], d2[mask]

    # calc
    d = np.sqrt(d2)

    sig = 0.5 * (sigma[I] + sigma[J])
    eps = np.sqrt(epsilon[I] * epsilon[J])

    s6 = (sig**2 / d2) ** 3
    qq = COULOMB * q[I] * q[J]

    E_vdw = (4 * eps * (s6 ** 2 - s6)).sum()
    E_ele = (qq * (1/d + KRF * d2 - CRF)).sum()

    f = ((24 * eps * (2 * s6**2 - s6) / d2) + (qq * (1/d**3 - 2 * KRF)))[:, None] * r

    np.add.at(F, I, f)
    np.add.at(F, J, -f)
    
    # --- 1-4 pairs
    a, b = S['pairs14'].T

    r = min_img(pos[a] - pos[b], box_size)
    d2 = (r * r).sum(axis=1)
    d = np.sqrt(d2)

    sig = 0.5 * (sigma[a] + sigma[b])
    eps = np.sqrt(epsilon[a] * epsilon[b])
    
    s6 = (sig**2 / d2) ** 3
    qq = COULOMB * q[a] * q[b]

    E_vdw += ((4 * eps * (s6 ** 2 - s6)) / SCNB).sum()
    E_ele += ((qq / d) / SCEE).sum()

    f = (
        ((24 * eps * (2 * s6**2 - s6) / d2) / SCNB) + 
        ((qq * (1/d**3)) / SCEE)
    )[:, None] * r

    np.add.at(F, a, f)
    np.add.at(F, b, -f)

    # ---
    return E_vdw, E_ele, F

def energy_forces(S, pos, p_list=None):
    """TODO 5: add everything up.  Return (e, F) where e is a dict with the keys
    BOND, ANGLE, DIHED, VDW, ELECT, POT (POT = sum of the five) and F the total force (N,3)."""

    BOND,  F1 = bond_terms(S, pos)
    ANGLE, F2 = angle_terms(S, pos)
    DIHED, F3 = dihedral_terms(S, pos)
    VDW, ELECT, F4 = nonbonded_terms(S, pos, p_list)

    return {
        'BOND':  BOND,
        'ANGLE': ANGLE,
        'DIHED': DIHED,
        'VDW':   VDW,
        'ELECT': ELECT,
        'POT':   BOND + ANGLE + DIHED + VDW + ELECT
    }, F1 + F2 + F3 + F4


def nve_sim(S, v0: np.ndarray, dt: float, n_steps: int, n_out: int) -> Tuple[np.ndarray, np.ndarray, np.ndarray]:
    dt /= 1000.0

    r = S['pos'].copy()
    v = np.array(v0, dtype=float) 

    m = S['mass'][:, None]

    p_list = pairs_within(r, S['box'], RC + 2.0)  # TODO: what?

    energies, F = energy_forces(S, r, p_list)
    a = (F / m) * ACC

    K_list = []
    U_list = []
    t_list = []  # TODO: we can probably use np.linspace

    for i in range(n_steps + 1):
        print(f'step {i}')

        if i % n_out == 0:
            K_list.append(0.5 * np.sum(m * v**2) / ACC)
            U_list.append(energies['POT'])
            t_list.append(i * dt)

        if i > 0 and i % 10 == 0:
            p_list = pairs_within(r, S['box'], RC + 2.0)  # TODO: what?

        r += (v * dt) + (0.5 * a * (dt ** 2))
        energies, F = energy_forces(S, r, p_list)                     
        a_new = (F / m) * ACC
        v = v + (0.5 * (a + a_new) * dt)     
        a = a_new

    return np.array(K_list), np.array(U_list), np.array(t_list)