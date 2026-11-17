"""PROVIDED. Self-check for Part A.   python check_my_protein_engine.py <PDBID>   (every line must say PASS)
Compares YOUR engine with OpenMM at the starting structure of your protein (same box, 9 A cutoff, no PME).
"""
import sys, numpy as np
sys.path.insert(0, '../part_b_protein')
import openmm as mm
from openmm import unit
from openmm_setup import make_system
from protein_system import load, maxwell_velocities, COULOMB, RC
from neighbours import pairs_within, min_img
import engine as me

pid = sys.argv[1].upper()
S = load(f'../proteins/{pid}/{pid}'); pos = S['pos']; N = S['N']; ok = True
def report(name, passed, extra=''):
    global ok; ok &= bool(passed); print(f'{"PASS" if passed else "FAIL"}  {name}  {extra}')

def omm(zero_charges):
    _, crd, system = make_system(pid, '../proteins')
    for i, f in enumerate(system.getForces()):
        f.setForceGroup(i)
        if zero_charges and isinstance(f, mm.NonbondedForce):
            for a in range(f.getNumParticles()):
                _, s, e = f.getParticleParameters(a); f.setParticleParameters(a, 0.0, s, e)
            for k in range(f.getNumExceptions()):
                a, b, qq, s, e = f.getExceptionParameters(k); f.setExceptionParameters(k, a, b, 0.0, s, e)
    ctx = mm.Context(system, mm.VerletIntegrator(0.001), mm.Platform.getPlatformByName('Reference'))
    ctx.setPositions(crd.positions); ctx.setPeriodicBoxVectors(*crd.boxVectors)
    g = {type(f).__name__: ctx.getState(getEnergy=True, groups={i}).getPotentialEnergy().value_in_unit(unit.kilocalories_per_mole)
         for i, f in enumerate(system.getForces())}
    st = ctx.getState(getEnergy=True, getForces=True)
    return g, st.getPotentialEnergy().value_in_unit(unit.kilocalories_per_mole), \
        st.getForces(asNumpy=True).value_in_unit(unit.kilocalories_per_mole / unit.nanometer) / 10.0

full, Uo, Fo = omm(False); lj, _, _ = omm(True)
for name, fn, key in [('bond', me.bond_terms, 'HarmonicBondForce'), ('angle', me.angle_terms, 'HarmonicAngleForce'),
                      ('dihedral', me.dihedral_terms, 'PeriodicTorsionForce')]:
    E, _ = fn(S, pos); report(f'{name} energy equals OpenMM', abs(E - full[key]) < 1e-3, f'(yours {E:.4f}, OpenMM {full[key]:.4f})')
e, F = me.energy_forces(S, pos)
report('VDW (Lennard-Jones) energy equals OpenMM', abs(e['VDW'] - lj['NonbondedForce']) < 0.05, f'(yours {e["VDW"]:.4f}, OpenMM {lj["NonbondedForce"]:.4f})')
el_omm = full['NonbondedForce'] - lj['NonbondedForce']
report('Coulomb energy equals OpenMM', abs(e['ELECT'] - el_omm) < 0.05, f'(yours {e["ELECT"]:.4f}, OpenMM {el_omm:.4f})')
report('total potential equals OpenMM', abs(e['POT'] - Uo) < 0.05, f'(yours {e["POT"]:.4f}, OpenMM {Uo:.4f})')
dF = np.abs(F - Fo).max(); report('forces equal OpenMM', dF < 1e-3, f'(max difference {dF:.1e} kcal/mol/A)')
report('net force is ~0', np.abs(F.sum(0)).max() < 1e-6, f'({np.abs(F.sum(0)).max():.1e})')
vel = maxwell_velocities(S['mass'], 300.0, 1)
K, U, t = me.nve_sim(S, vel, 0.5, 200, 20); Et = K + U
ch = Et.max() - Et.min(); lim = 0.02 * K[0]
report('NVE 0.1 ps (0.5 fs): total energy conserved (change < 2% of the kinetic energy)', ch < lim, f'(change {ch:.2f}, limit {lim:.2f} kcal/mol)')
print('ALL GOOD' if ok else 'SOMETHING FAILS - fix and rerun')
