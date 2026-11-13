import numpy as np
import matplotlib.pyplot as plt

KJ_2_KCAL = 1 / 4.184  # OpenMM writes kJ/mol | NAMD writes kcal/mol

def analyze_openmm(path):
    res = np.atleast_2d(np.genfromtxt(path, delimiter=',', skip_header=1))

    return res[:, 1], dict(
        PE=res[:, 2] * KJ_2_KCAL,
        KE=res[:, 3] * KJ_2_KCAL,
        E= res[:, 4] * KJ_2_KCAL,
        T= res[:, 5]
    )

if __name__ == '__main__':
    t, openmm_res = analyze_openmm("openmm/nve.csv")

    print(f'Average temperature = {openmm_res["T"].mean():.2f} K')
    print(f'Average potential energy = {openmm_res["PE"].mean():.2f} kcal/mol')

    plt.figure(1)
    plt.title('Energy')
    plt.xlabel('t (ps)')
    plt.ylabel('energy (kcal/mol)')
    plt.plot(t, openmm_res['PE'], label='PE')
    plt.plot(t, openmm_res['KE'], label='KE')
    plt.plot(t, openmm_res['E' ], label='Total')
    plt.legend()

    plt.figure(2)
    plt.xlabel('t (ps)')
    plt.ylabel('energy (kcal/mol)')
    plt.title('Total Energy Fluctuation')
    plt.plot(t, openmm_res['E'] - openmm_res['E'][0])

    plt.figure(3)
    plt.xlabel('t (ps)')
    plt.ylabel('T (K)')
    plt.title('Temperature')
    plt.plot(t, openmm_res['T'])

    plt.show()