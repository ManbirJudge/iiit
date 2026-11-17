# ### PROVIDED ###

"""Geometry helpers with derivatives (so you only need the chain rule).
angle_and_grad(pos, idx)    idx (K,3) -> theta (K,) rad,  dtheta (K,3,3): d theta / d r  for the 3 atoms (A^-1)
dihedral_and_grad(pos, idx) idx (D,4) -> phi (D,) rad,    dphi   (D,4,3): d phi   / d r  for the 4 atoms (A^-1)
Force on an atom = - (dE/dtheta) * dtheta/dr   (and the same for phi).  Use np.add.at to add forces up."""

import numpy as np

def angle_and_grad(pos, idx):
    a, b, c = pos[idx[:, 0]], pos[idx[:, 1]], pos[idx[:, 2]]
    u, v = a - b, c - b
    lu, lv = np.linalg.norm(u, axis=1), np.linalg.norm(v, axis=1)
    cos = np.clip((u * v).sum(1) / (lu * lv), -1, 1); th = np.arccos(cos); sin = np.sqrt(1 - cos**2)
    dcos_da = (v / (lu * lv)[:, None]) - (cos / lu**2)[:, None] * u
    dcos_dc = (u / (lu * lv)[:, None]) - (cos / lv**2)[:, None] * v
    dth_da, dth_dc = -dcos_da / sin[:, None], -dcos_dc / sin[:, None]
    return th, np.stack([dth_da, -dth_da - dth_dc, dth_dc], axis=1)

def dihedral_and_grad(pos, idx):
    r1, r2, r3, r4 = (pos[idx[:, i]] for i in range(4))
    F, G, H = r1 - r2, r2 - r3, r4 - r3
    A, B = np.cross(F, G), np.cross(H, G)
    lG = np.linalg.norm(G, axis=1); A2 = (A * A).sum(1); B2 = (B * B).sum(1)
    phi = np.arctan2((np.cross(B, A) * G).sum(1) / lG, (A * B).sum(1))
    FG, HG = (F * G).sum(1), (H * G).sum(1)
    g1 = -(lG / A2)[:, None] * A
    g4 = (lG / B2)[:, None] * B
    g2 = (lG / A2)[:, None] * A + (FG / (A2 * lG))[:, None] * A - (HG / (B2 * lG))[:, None] * B
    g3 = -(lG / B2)[:, None] * B - (FG / (A2 * lG))[:, None] * A + (HG / (B2 * lG))[:, None] * B
    return phi, np.stack([g1, g2, g3, g4], axis=1)
