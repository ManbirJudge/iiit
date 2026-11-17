"""PROVIDED. Energy of the starting structure in OpenMM, split into BOND / ANGLE / DIHED / VDW / ELECT (kcal/mol).
Usage: python singlepoint_openmm.py <PDBID>"""
import sys, json
import openmm as mm
from openmm import unit
from openmm_setup import make_system, platform
pid = sys.argv[1].upper()
prmtop, inpcrd, system = make_system(pid)

def run(zero_charges):
    prmtop, inpcrd, system = make_system(pid)
    for i, f in enumerate(system.getForces()):
        f.setForceGroup(i)
        if zero_charges and isinstance(f, mm.NonbondedForce):
            for a in range(f.getNumParticles()):
                _, s, e = f.getParticleParameters(a); f.setParticleParameters(a, 0.0, s, e)
            for k in range(f.getNumExceptions()):
                a, b, qq, s, e = f.getExceptionParameters(k); f.setExceptionParameters(k, a, b, 0.0, s, e)
    ctx = mm.Context(system, mm.VerletIntegrator(0.001), platform())
    ctx.setPositions(inpcrd.positions); ctx.setPeriodicBoxVectors(*inpcrd.boxVectors)
    return {type(f).__name__: ctx.getState(getEnergy=True, groups={i}).getPotentialEnergy().value_in_unit(unit.kilocalories_per_mole)
            for i, f in enumerate(system.getForces())}
full, lj = run(False), run(True)
res = dict(BOND=full['HarmonicBondForce'], ANGLE=full['HarmonicAngleForce'], DIHED=full['PeriodicTorsionForce'],
           VDW=lj['NonbondedForce'], ELECT=full['NonbondedForce'] - lj['NonbondedForce'])
res['POTENTIAL'] = sum(res.values())
print(f'{pid}: OpenMM energy of the starting structure (kcal/mol)')
for k, v in res.items(): print(f'  {k:10s} {v:14.4f}')
json.dump(res, open(f'singlepoint_openmm_{pid}.json', 'w'), indent=1)
