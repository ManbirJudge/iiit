"""PART B - analysis of one NAMD log and one OpenMM csv (same protein, same dt).
Usage: python analyze_nve.py <PDBID> <namd.log> <openmm.csv> [dt_fs=1.0] [equil_ps=2.0]
Prints mean T, mean PE, std(E_total), drift (kcal/mol/ns, also per atom) for both engines, draws nve_<ID>_dt<dt>.png,
writes stats_<ID>_dt<dt>.json.  Everything in kcal/mol.  Discards the first equil_ps of the run."""
import sys, json, re, numpy as np, matplotlib
matplotlib.use('Agg'); import matplotlib.pyplot as plt
pid, namd_log, omm_csv = sys.argv[1].upper(), sys.argv[2], sys.argv[3]
dt = float(sys.argv[4]) if len(sys.argv) > 4 else 1.0
equil = float(sys.argv[5]) if len(sys.argv) > 5 else 2.0
KJ = 1 / 4.184
natoms = int(re.search(r'atoms\s*:\s*(\d+)', open(f'../proteins/{pid}/system_info.txt').read()).group(1))

cols, rows = None, []
for l in open(namd_log):
    if l.startswith('ETITLE:'): cols = l.split()[1:]
    elif l.startswith('ENERGY:'): rows.append([float(x) for x in l.split()[1:]])
d = np.array(rows); c = {k: i for i, k in enumerate(cols)}
tn = d[:, c['TS']] * dt / 1000
namd = dict(KE=d[:, c['KINETIC']], PE=d[:, c['POTENTIAL']], E=d[:, c['TOTAL']], T=d[:, c['TEMP']])
o = np.genfromtxt(omm_csv, delimiter=',', skip_header=1)
to = o[:, 1]
omm = dict(PE=o[:, 2] * KJ, KE=o[:, 3] * KJ, E=o[:, 4] * KJ, T=o[:, 5])

fig, ax = plt.subplots(2, 2, figsize=(11, 7)); stats = dict(pdb=pid, natoms=natoms, dt_fs=dt)
for j, (name, t, s) in enumerate([('NAMD', tn, namd), ('OpenMM', to, omm)]):
    m = t >= equil
    for key, col in [('PE', 'C0'), ('KE', 'C1')]: ax[0, j].plot(t, s[key] - s[key][m].mean(), col, label=key)
    ax[0, j].plot(t, s['E'] - s['E'][m].mean(), 'k', label='Total'); ax[0, j].axvspan(0, equil, color='grey', alpha=.2)
    ax[0, j].set(title=name + ': energies (mean removed)', xlabel='time (ps)', ylabel='kcal/mol'); ax[0, j].legend()
    ax[1, j].plot(t[m], s['E'][m] - s['E'][m][0], 'k'); ax[1, j].set(title=name + ': total energy only', xlabel='time (ps)', ylabel='E-E0 (kcal/mol)')
    slope = np.polyfit(t[m], s['E'][m], 1)[0] * 1000          # kcal/mol/ns
    stats[name] = dict(T_mean=float(s['T'][m].mean()), T_std=float(s['T'][m].std()), E_mean=float(s['E'][m].mean()),
                       E_std=float(s['E'][m].std()), PE_mean=float(s['PE'][m].mean()), KE_mean=float(s['KE'][m].mean()),
                       PE_std=float(s['PE'][m].std()), drift_kcal_per_ns=float(slope), drift_per_atom_per_ns=float(slope / natoms))
    print(f"{name:7s} <T>={stats[name]['T_mean']:6.1f} K  <PE>={stats[name]['PE_mean']:.1f}  std(E)={stats[name]['E_std']:.3f}  drift={slope:+.2f} kcal/mol/ns ({slope/natoms:+.5f}/atom/ns)")
plt.tight_layout(); plt.savefig(f'nve_{pid}_dt{dt:g}.png', dpi=130)
json.dump(stats, open(f'stats_{pid}_dt{dt:g}.json', 'w'), indent=1); print('wrote', f'stats_{pid}_dt{dt:g}.json')
