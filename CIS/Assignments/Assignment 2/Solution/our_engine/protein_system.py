# ### PROVIDED ###

import numpy as np
import parmed as pmd

# --- constants
KB = 0.0019872041  # kcal/mol/K
ACC = 418.4        # (kcal/mol/A)/amu -> A/ps^2

# ---
COULOMB = 332.0637                                # kcal/mol * A / e^2
SCEE, SCNB = 1.2, 2.0
RC = 9.0                                          # cutoff (A)
EPS_RF = 78.3                                     # reaction-field dielectric (OpenMM's default)
KRF = (EPS_RF - 1) / ((2 * EPS_RF + 1) * RC**3)   # reaction-field constants, see Appendix B of the PDF
CRF = (1 / RC) * (3 * EPS_RF / (2 * EPS_RF + 1))

def load(prefix):  # TODO: understand 
    raw = pmd.load_file(prefix + '.prmtop', prefix + '_equil.rst7')

    N = len(raw.atoms)

    # ---
    data = dict(
        N=N, 
        box   = np.array(raw.box[:3], float),
        pos   = np.array(raw.coordinates, float),
        mass  = np.array([a.mass    for a in raw.atoms]),
        q     = np.array([a.charge  for a in raw.atoms]),
        sigma = np.array([a.sigma   for a in raw.atoms]),
        eps   = np.array([a.epsilon for a in raw.atoms])
    )

    data['bonds'] = np.array([[b.atom1.idx, b.atom2.idx] for b in raw.bonds])
    data['bond_k'] = np.array([b.type.k for b in raw.bonds])
    data['bond_r0'] = np.array([b.type.req for b in raw.bonds])

    data['angles'] = np.array([[a.atom1.idx, a.atom2.idx, a.atom3.idx] for a in raw.angles])
    data['angle_k'] = np.array([a.type.k for a in raw.angles])
    data['angle_t0'] = np.deg2rad([a.type.theteq for a in raw.angles])

    # ---
    dihs, k, n, ph = [], [], [], []
    for dh in raw.dihedrals:
        for t in (dh.type if isinstance(dh.type, pmd.DihedralTypeList) else [dh.type]):
            dihs.append([dh.atom1.idx, dh.atom2.idx, dh.atom3.idx, dh.atom4.idx])
            k.append(t.phi_k)
            n.append(t.per)
            ph.append(np.deg2rad(t.phase))

    data['dihs'] = np.array(dihs)
    data['dih_k'] = np.array(k)
    data['dih_n'] = np.array(n, float)
    data['dih_phase'] = np.deg2rad(0) + np.array(ph)

    # ---
    ex, ex12_13 = set(), set()

    for a in raw.atoms:
        for p in a.bond_partners:     ex12_13.add((min(a.idx, p.idx), max(a.idx, p.idx)))
        for p in a.angle_partners:    ex12_13.add((min(a.idx, p.idx), max(a.idx, p.idx)))
        for p in a.dihedral_partners: ex.add(     (min(a.idx, p.idx), max(a.idx, p.idx)))

    ex |= ex12_13

    data['excl_keys'] = np.sort(np.array([i * N + j for i, j in ex], dtype=np.int64))

    # ---
    p14 = set()

    for dh in raw.dihedrals:
        if dh.improper or dh.ignore_end: continue

        pr = (
            min(dh.atom1.idx, dh.atom4.idx), 
            max(dh.atom1.idx, dh.atom4.idx)
        )

        if pr not in ex12_13: p14.add(pr)

    data['pairs14'] = np.array(sorted(p14))

    # ---
    return data

# ---
def maxwell_velocities(
    m: np.ndarray,
    T: float = 300.0,
    seed: int = 67
) -> np.ndarray:
    """Random Maxwell-Boltzmann velocities (A/ps):
    - 0 total momentum
    - Scaled to T Kelvin"""

    m = m[:, None]

    rng = np.random.default_rng(seed)
    N = len(m)

    v_std = np.sqrt((KB * T / m) / ACC)
    v = rng.normal(0, 1, (N, 3)) * v_std

    v -= (m * v).sum() / m.sum()

    dof = N - 1
    T_got = ((m * v ** 2).sum() / (3 * dof * KB)) / ACC

    return v * np.sqrt(T / T_got)