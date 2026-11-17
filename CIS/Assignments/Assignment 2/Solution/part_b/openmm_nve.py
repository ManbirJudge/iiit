"""PART B - OpenMM NVE run for YOUR protein.
Usage:  python openmm_nve.py <PDBID> [nsteps] [dt_fs]
        default: 12000 steps x 1 fs = 12 ps (2 ps equilibration + 10 ps production, as in the NAMD file)
Writes out_openmm/<ID>_dt<dt>.csv (energies in kJ/mol) and a .dcd trajectory (frame every 1 ps).
Same physics as proteins/<ID>/nve.namd: periodic box, 9 A cutoff (no PME), flexible bonds, NO thermostat/barostat."""
import sys, os, time
import openmm as mm
from openmm import app, unit
from openmm_setup import make_system, platform

pid = sys.argv[1].upper()
nsteps = int(sys.argv[2]) if len(sys.argv) > 2 else 12000
dt_fs = float(sys.argv[3]) if len(sys.argv) > 3 else 1.0
os.makedirs('out_openmm', exist_ok=True)
tag = f'out_openmm/{pid}_dt{dt_fs:g}'

prmtop, inpcrd, system = make_system(pid)
integrator = mm.VerletIntegrator(dt_fs * 1e-3 * unit.picoseconds)          # <- NVE
plat = platform()
sim = app.Simulation(prmtop.topology, system, integrator, plat)
sim.context.setPositions(inpcrd.positions)
sim.context.setPeriodicBoxVectors(*inpcrd.boxVectors)
sim.context.setVelocitiesToTemperature(300 * unit.kelvin, 12345)
every = max(1, int(round(100 / dt_fs)))                                     # one energy line per 0.1 ps
sim.reporters.append(app.StateDataReporter(f'{tag}.csv', every, step=True, time=True, potentialEnergy=True,
                     kineticEnergy=True, totalEnergy=True, temperature=True))
sim.reporters.append(app.DCDReporter(f'{tag}.dcd', int(round(1000 / dt_fs))))
t0 = time.time(); sim.step(nsteps); w = time.time() - t0
print(f'{pid}: {nsteps} steps x {dt_fs} fs done in {w:.0f} s ({w/nsteps*1000:.1f} ms/step) on {plat.getName()}')
