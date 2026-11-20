"""PROVIDED. Builds the OpenMM system with the assignment settings (same as the NAMD files):
periodic box, 9 A cutoff (no PME; reaction-field Coulomb, OpenMM default dielectric 78.3), no long-range correction, all bonds flexible, no thermostat/barostat."""
import openmm as mm
from openmm import app, unit

def make_system(pid, base='..'):
    prmtop = app.AmberPrmtopFile(f'{base}/{pid}/{pid}.prmtop')
    inpcrd = app.AmberInpcrdFile(f'{base}/{pid}/{pid}_equil.rst7')
    system = prmtop.createSystem(nonbondedMethod=app.CutoffPeriodic, nonbondedCutoff=0.9 * unit.nanometer,
                                 constraints=None, rigidWater=False)
    for f in system.getForces():
        if isinstance(f, mm.NonbondedForce):
            f.setUseDispersionCorrection(False)
    return prmtop, inpcrd, system

def platform():
    try: return mm.Platform.getPlatformByName('CPU')
    except Exception: return mm.Platform.getPlatformByName('Reference')
