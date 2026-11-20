"""PART B4 (optional helper) - backbone RMSD of the protein against the first frame of a DCD trajectory.
Usage: python rmsd_backbone.py <PDBID> <traj.dcd> [label]      -> rmsd_<label>.png and prints the RMSD at the end
Works for the NAMD (out/nve.dcd) and the OpenMM (out_openmm/*.dcd) trajectories (frame every 1 ps)."""
import sys, numpy as np, matplotlib
matplotlib.use('Agg'); import matplotlib.pyplot as plt
import MDAnalysis as mda
from MDAnalysis.analysis import rms
pid, dcd = sys.argv[1].upper(), sys.argv[2]; label = sys.argv[3] if len(sys.argv) > 3 else 'traj'
u = mda.Universe(f'../proteins/{pid}/{pid}.prmtop', dcd)
R = rms.RMSD(u, u, select='backbone', ref_frame=0).run()
t = np.arange(len(R.results.rmsd)) * 1.0                      # ps (1 frame per ps)
plt.plot(t, R.results.rmsd[:, 2]); plt.xlabel('time (ps)'); plt.ylabel('backbone RMSD (A)'); plt.title(f'{pid} {label}')
plt.savefig(f'rmsd_{label}.png', dpi=130); print(f'{pid} {label}: final backbone RMSD = {R.results.rmsd[-1, 2]:.3f} A over {len(t)} frames')
