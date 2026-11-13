import sys, os

os.environ['OPENMM_CPU_THREADS'] = '12'

import openmm as mm
from openmm import app, unit

# ---
prmtop = app.AmberPrmtopFile('../input/2HEP.prmtop')
inpcrd = app.AmberInpcrdFile('../input/2HEP_equil.rst7')

# ---
system = prmtop.createSystem(
    nonbondedMethod=app.CutoffPeriodic,
    nonbondedCutoff=0.9 * unit.nanometer,
    ewaldErrorTolerance=1e-5
)

# integrator
integrator = mm.VerletIntegrator(0.001 * unit.picoseconds)

# ---
platform = mm.Platform.getPlatformByName('CPU')
platform.setPropertyDefaultValue('Threads', '12') 

sim = app.Simulation(prmtop.topology, system, integrator, platform)
sim.context.setPositions(inpcrd.positions)
sim.context.setPeriodicBoxVectors(*inpcrd.boxVectors)

# initial velocities according to 300 K
sim.context.setVelocitiesToTemperature(300 * unit.kelvin, 12345)

# output | every 100 steps (0.2 ps) and trajectory
sim.reporters.append(app.StateDataReporter('nve.csv', 50, step=True, time=True, potentialEnergy=True, kineticEnergy=True, totalEnergy=True, temperature=True))
sim.reporters.append(app.DCDReporter('nve.dcd', 100))

# run
n_steps = 12000
sim.step(n_steps)
