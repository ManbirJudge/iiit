"""OpenMM NVE tutorial: Trp-cage (1L2Y) in TIP3P water, Amber ff14SB.
Run from this folder:  python nve.py [nsteps]     (writes nve.csv and nve.dcd)
  In class:  python nve.py 1000     1000 steps x 2 fs = 2 ps, a few minutes on a laptop CPU
  Default:   30000 steps = 60 ps    about 30 min on CPU (results are in ../reference_results/)
"""
import sys
import openmm as mm
from openmm import app, unit

# 1. Load topology+force field and equilibrated coordinates/box
prmtop = app.AmberPrmtopFile('../inputs/trpcage_wat.prmtop')
inpcrd = app.AmberInpcrdFile('../inputs/trpcage_equil.rst7')

# 2. Build the system (same settings as the NAMD file)
system = prmtop.createSystem(
    nonbondedMethod=app.PME,
    nonbondedCutoff=0.9 * unit.nanometer,      # 9 A
    constraints=app.HBonds,                    # rigid X-H bonds
    rigidWater=True,
    ewaldErrorTolerance=1e-5)
# (no thermostat, no barostat were added -> NVE)

# 3. NVE integrator: velocity-Verlet-like, 2 fs
integrator = mm.VerletIntegrator(0.002 * unit.picoseconds)

# 4. Simulation object (CPU platform works everywhere)
platform = mm.Platform.getPlatformByName('CPU')
sim = app.Simulation(prmtop.topology, system, integrator, platform)
sim.context.setPositions(inpcrd.positions)
sim.context.setPeriodicBoxVectors(*inpcrd.boxVectors)

# 5. (No minimisation: structure is already equilibrated.) Initial velocities: 300 K Maxwell-Boltzmann
sim.context.setVelocitiesToTemperature(300 * unit.kelvin, 12345)

# 6. Output: energies every 100 steps (0.2 ps) and a trajectory
sim.reporters.append(app.StateDataReporter(
    'nve.csv', 100, step=True, time=True, potentialEnergy=True,
    kineticEnergy=True, totalEnergy=True, temperature=True))
sim.reporters.append(app.DCDReporter('nve.dcd', 500))

# 7. Run NVE. In the full run the first 10 ps are equilibration (discarded in analysis)
nsteps = int(sys.argv[1]) if len(sys.argv) > 1 else 30000
sim.step(nsteps)
