from pathlib import Path
import sys

import matplotlib.pyplot as plt
import numpy as np

from protein_system import load, maxwell_velocities

from engine import nve_sim

def run_sim(prefix: str, dt: float):
    n_steps = round(2000 / dt_fs)  # total 2 ps
    n_out   = round(10 / dt_fs)    # save every 0.01 ps

    # load data
    data = load(prefix)

    # initialize velocities
    v0 = maxwell_velocities(data['mass'], 300)

    # energy terms at the starting structure
    # if not os.path.exists('singlepoint.json'):
    #     e, F = energy_forces(data, data['pos'])
    #     out = {k: float(x) for k, x in e.items()}
    #     out['max_net_force'] = float(np.abs(F.sum(0)).max())
    #     json.dump(out, open('singlepoint.json', 'w'), indent=2)
    #     print(out)

    # the run
    K, U, t = nve_sim(data, v0, dt_fs, n_steps, n_out)
    E = K + U

    # output
    out_dir_path = Path("out")
    if not out_dir_path.exists():
        out_dir_path.mkdir(parents=True, exist_ok=True)

    np.save(out_dir_path / f'K_{dt}.npy', K)
    np.save(out_dir_path / f'U_{dt}.npy', U)
    np.save(out_dir_path / f'E_{dt}.npy', E)
    np.save(out_dir_path / f't_{dt}.npy', t)

def ANALYZE():
    out_dir_path = Path("out")
    if not out_dir_path.exists():
        print('Output directory doesn\'t exist!')

    _c = 1

    dic = {}

    # ---
    for dt in [0.5, 1.0, 2.0]:
        print(f'--- {dt} fs ---')

        try:
            K = np.load(out_dir_path / f'K_{dt}.npy', )
            U = np.load(out_dir_path / f'U_{dt}.npy', )
            E = np.load(out_dir_path / f'E_{dt}.npy', )
            t = np.load(out_dir_path / f't_{dt}.npy', )
        except Exception as e:
            print(f'Error while loading data:\n{e}')
            continue

        plt.figure(_c)
        plt.title(f'NVE Kinetic Energy | dt = {dt} fs')
        plt.plot(t, K)
        plt.ylabel('energy (kcal/mol)')
        plt.xlabel('t (ps)')
        plt.savefig(str(out_dir_path / f'K_{dt}.png'), dpi=300)
        _c += 1
        
        plt.figure(_c)
        plt.title(f'NVE Potential Energy | dt = {dt} fs')
        plt.plot(t, U, label='Potential Energy')
        plt.ylabel('energy (kcal/mol)')
        plt.xlabel('t (ps)')
        plt.savefig(str(out_dir_path / f'P_{dt}.png'), dpi=300)
        _c += 1

        plt.figure(_c)
        plt.title(f'NVE Total Energy | dt = {dt} fs')
        plt.plot(t, E, label='Total Energy')
        plt.ylabel('energy (kcal/mol)')
        plt.xlabel('t (ps)')
        plt.savefig(str(out_dir_path / f'E_{dt}.png'), dpi=300)
        _c += 1

        dic[str(dt)] = {
            'K': K,
            'U': U,
            'E': E,
            't': t
        }

        print(f'Initial TE = {E[0]:.3f} kcal/mol')
        print(f'Final TE = {E[-1]:.3f} kcal/mol')
        print(f'Change in TE = {abs(E[0] - E[-1]):.3f} kcal/mol')
        print('')
    
    # ---
    for dt in [0.5, 1.0, 2.0]:
        try:
            E = dic[str(dt)]['E']
        except: continue

        plt.figure(_c)
        plt.title(f'Energy Fluctuation | dt = {dt} fs')
        plt.plot(t, E - E[0])
        plt.ylabel('energy (kcal/mol)')
        plt.xlabel('t (ps)')
        plt.savefig(str(out_dir_path / f'E_fluctuation_{dt}.png'), dpi=300)
        _c += 1

    # ---
    plt.show()

def print_help():
    print(f'Usage: {sys.argv[0]} <cmd> <prefix> <dt>')
    print('Command: sim, analyze')
    print('<prefix> and <dt> are required for simulation.')

if __name__ == '__main__':
    if len(sys.argv) <= 1:
        print_help()
        sys.exit(1)

    cmd = sys.argv[1]

    if cmd == 'sim':
        if len(sys.argv) != 4:
            print_help()

    if cmd == 'sim':
        if len(sys.argv) != 4:
            print_help()
            sys.exit(2)

        prefix = sys.argv[2]
        dt_fs  = float(sys.argv[3])

        run_sim(prefix, dt_fs)

    elif cmd == 'analyze':
        ANALYZE()