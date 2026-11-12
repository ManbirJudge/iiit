"""Plot NVE energies from NAMD (log) and OpenMM (csv), all in kcal/mol.

Usage:
    python plot_nve.py                          # your runs: ../namd/out/nve.log and ../openmm/nve.csv
    python plot_nve.py NAMD_LOG OPENMM_CSV      # any two files, e.g. the reference results
    python plot_nve.py NAMD_LOG -               # NAMD only ('-' = skip OpenMM)

For runs longer than 30 ps the first 10 ps (NVE equilibration) are left out of the statistics.
Writes nve_energies.png in the current folder.
"""
import os, re, sys
import numpy as np, matplotlib
matplotlib.use('Agg'); import matplotlib.pyplot as plt

EQUIL_PS = 10.0          # discarded at the start of long runs
KJ2KCAL = 1 / 4.184      # OpenMM writes kJ/mol, NAMD writes kcal/mol
N_ATOMS = 6215

NAMD_LOG = sys.argv[1] if len(sys.argv) > 1 else '../namd/out/nve.log'
OMM_CSV  = sys.argv[2] if len(sys.argv) > 2 else '../openmm/nve.csv'


def read_namd(path):
    """ENERGY: lines of a NAMD log; columns are named on the ETITLE: line."""
    cols, rows, dt_fs = None, [], 2.0
    for line in open(path):
        if line.startswith('Info: TIMESTEP '):
            dt_fs = float(line.split()[2])          # timestep in fs, read from the log
        elif line.startswith('ETITLE:'):
            cols = line.split()[1:]
        elif line.startswith('ENERGY:'):
            rows.append([float(x) for x in line.split()[1:]])
    if not rows:
        sys.exit(f'No ENERGY: lines in {path}. Has NAMD finished (tail -3 {path})?')
    d = np.array(rows); c = {k: i for i, k in enumerate(cols)}
    t = d[:, c['TS']] * dt_fs / 1000                 # ps
    return t, dict(KE=d[:, c['KINETIC']], PE=d[:, c['POTENTIAL']],
                   E=d[:, c['TOTAL']], T=d[:, c['TEMP']])


def read_openmm(path):
    """CSV columns: step, time (ps), PE, KE, total (kJ/mol), T (K)."""
    o = np.atleast_2d(np.genfromtxt(path, delimiter=',', skip_header=1))
    return o[:, 1], dict(PE=o[:, 2] * KJ2KCAL, KE=o[:, 3] * KJ2KCAL,
                         E=o[:, 4] * KJ2KCAL, T=o[:, 5])


runs = []
for name, path, reader in [('NAMD', NAMD_LOG, read_namd), ('OpenMM', OMM_CSV, read_openmm)]:
    if path == '-':
        continue
    if not os.path.exists(path):
        print(f'{name}: {path} not found, skipping')
        continue
    runs.append((name, *reader(path)))
if not runs:
    sys.exit('Nothing to plot.')

fig, ax = plt.subplots(2, len(runs), figsize=(5.5 * len(runs), 7), squeeze=False)
for j, (name, t, s) in enumerate(runs):
    long_run = t[-1] > 30
    m = t >= EQUIL_PS if long_run else np.ones_like(t, bool)   # short runs: keep everything
    a = ax[0, j]
    a.plot(t, s['PE'] - s['PE'][m].mean(), label='PE')
    a.plot(t, s['KE'] - s['KE'][m].mean(), label='KE')
    a.plot(t, s['E'] - s['E'][m].mean(), 'k', label='Total')
    if long_run:
        a.axvspan(0, EQUIL_PS, color='grey', alpha=.2)
    a.set_title(name + ': energies (each shifted to mean 0)')
    a.set_xlabel('time (ps)'); a.set_ylabel('kcal/mol'); a.legend()
    b = ax[1, j]
    b.plot(t[m], s['E'][m] - s['E'][m][0], 'k')
    b.set_title(name + ': total energy only')
    b.set_xlabel('time (ps)'); b.set_ylabel('E - E0 (kcal/mol)')
    slope = np.polyfit(t[m], s['E'][m], 1)[0] if m.sum() > 1 else float('nan')   # kcal/mol/ps
    note = '' if long_run else '   (short run: ignore drift)'
    print(f"{name:7s} <T>={s['T'][m].mean():6.1f} K  std(Etot)={s['E'][m].std():.3f} kcal/mol  "
          f"drift={slope*1000:+.2f} kcal/mol/ns  ({slope*1000/N_ATOMS:+.4f} per atom per ns){note}")
plt.tight_layout(); plt.savefig('nve_energies.png', dpi=130); print('saved nve_energies.png')
