import numpy as np
import matplotlib.pyplot as plt

# --- units
# length - Angstrom
# mass - amu
# energy - kcal/mol
# time - ps

# --- constants
k_b = 0.0019872041  # kcal/mol/K

# --- inputs
EPS = 0.238  # kcal/mol
SIG = 3.4  # Å

N = 108

L = 20.0  # Å
D_min = 3.4  # Å

M = 39.948  # amu

T_0 = 100.0  # K

dt = 0.002  # ps

S = 5000
N_out = 10

CF = 418.4  # conversion factor for (kcal/mol/Å)/amu -> Å/ps^2

# --- random
rng = np.random.default_rng(83)

# --- simulation
r = np.empty((N, 3), dtype=float)

# kinetic energy function
def K(v):
    return 0.5 * M * (v ** 2).sum() / CF

# initializing positions
_c = 0
while _c < N:
    new = rng.uniform(0.0, L, 3)

    too_close = False
    for i in range(_c):
        old = r[i]
        dist = np.sqrt(((new - old) ** 2).sum())
        if dist < D_min:
            too_close = True
            break

    if not too_close:
        r[_c] = new
        _c += 1

# initializing velocities
sigma_v_0 = np.sqrt(k_b * T_0 / M * CF)  # standard deviation of velocities (for a specific temperature)

v = rng.normal(0.0, sigma_v_0, (N, 3))
v -= v.mean(axis=0)  # removing mean velocity, so that total momentum is zero

DOF = 3 * (N - 1)  # degrees of freedom
T = 2 * K(v) / (DOF * k_b)  # temperature we actually got

v *= np.sqrt(T_0 / T)  # scale velocities according to T (velocity is proportional to sqrt(temperature))

# force calculation
def forces(r: np.array) -> (np.array, float):
    F = np.zeros((N, 3))
    U = 0.0

    for i in range(N):
        _r = r[i] - r
        d = (_r ** 2).sum(axis=1)
        d[i] = np.inf  # no force on particle itself

        _ = (SIG ** 2 / d) ** 3
        _F = 24 * EPS * (2 * (_ ** 2) - _) / d

        F[i] = np.dot(_F, _r)

        U += 2 * EPS * (_ ** 2 - _).sum()  # each pair is counted twice so only doing 2x here

    return F, U

# running the sim
F, U = forces(r)
a = (F / M) * CF

K_list = []
U_list = []
t_list = []  # TODO: we can probably use np.linspace
r_list = []

for i in range(S + 1):  # Verlet integrator
    if i % N_out == 0:
        K_list.append(K(v))
        U_list.append(U)
        t_list.append(i * dt)
        r_list.append(r.copy())

    r += (v * dt) + (0.5 * a * (dt ** 2))
    F, U = forces(r)
    a_new = (F / M) * CF
    v = v + (0.5 * (a + a_new) * dt)
    a = a_new

K_list = np.array(K_list)
U_list = np.array(U_list)
t_list = np.array(t_list)
r_list = np.array(r_list)

E_list = K_list + U_list
T_list = 2 * K_list / (DOF * k_b)

# --- plots
plt.figure(1)
plt.title('EnErGiEs')
plt.plot(t_list, K_list, label='K')
plt.plot(t_list, U_list, label='U')
plt.xlabel('t')
plt.ylabel('energy (kcal/mol)')
plt.legend()

plt.figure(2)
plt.title('Energy Drift')
plt.plot(t_list, E_list - E_list[0])
plt.xlabel('t')
plt.ylabel('E(t) - E(0) (kcal/mol)')

plt.figure(3)
plt.title('Temperature')
plt.plot(t_list, T_list)
plt.xlabel('t')
plt.ylabel('T (K)')

plt.show()