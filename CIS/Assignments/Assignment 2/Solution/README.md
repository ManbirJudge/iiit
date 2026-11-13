# Assignment 2
## Settings
- Periodic box - each atom interacts with nearest copy of every other atom
- Non-bonded interactions (van der Waals and Coulomb) cut of at `9 angstrom`
- All bonds flexible
- Timestep of `1 fs`
- Initial velocities at `300 K`
- No thermostat, no barostat

## NAMD and OpenMM
- `2 ps` of equilibrium. `10 ps` of production. Time step of `1 fs`.
- To report:
  - Average temperature
  - Average potential energy
  - Total energy fluctuation (and drift)
  - Plot kinetic, potential and total energy vs time
  - Explain why K and U mirror. Explain why temperature fluctuates.
- Repeat for time step of `0.5 fs` and `2 fs` for `2 ps`. 