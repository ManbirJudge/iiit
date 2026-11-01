import matplotlib.pyplot as plt
import numpy as np

# inputs
dt = 1
N = 4_000
L = 800.0

dx = 1.0     # for model 1
Pp = 0.5     # for model 1
Pn = 1 - Pp  # for model 1

sigma = 1.0  # for model 3
mean_x = 0.0 # for model 3

# simulation
n_elec = 2_000

rng = np.random.default_rng()

x_t = np.empty((n_elec, N + 1), dtype=float)  # time series (all electrons)
x_t[:, 0] = 0.0

for j in range(n_elec):
    x = 0
    for i in range(N):
        # _dx = rng.choice([dx, -dx], size=np.shape(x), p=[Pp, Pn])  # for model 1
        _dx = rng.normal(loc=mean_x, scale=sigma)  # for model 3
        x += _dx

        x_t[j][i + 1] = x

# calculations
x_t_sqr = x_t ** 2

# plots
_t = np.arange(N + 1) * dt  # time axis

print(f'<x>   = {x_t[:, -1].mean()}')
print(f'<x^2> = {x_t_sqr[:, -1].mean()}')

plt.figure(1)
for i in range(n_elec):
    plt.plot(_t, x_t[i])
plt.title('Time Series')
plt.xlabel('t')
plt.ylabel('x')
plt.ylim(-L/2, L/2)

plt.figure(2)
plt.title('Frequency Distribution of Final Positions')
plt.hist(x_t[:, -1], bins=60, range=(-L/2, L/2), density=True)
plt.xlabel('$x_f$')
plt.ylabel('$f(x_f)$')

plt.figure(3)
plt.title('<x> vs t')
plt.plot(_t, x_t.mean(axis=0))
plt.xlabel('t')
plt.ylabel(r'$\langle x \rangle$')
plt.ylim(-L/2, L/2)

plt.figure(4)
plt.title('<x^2> vs t')
plt.plot(_t, x_t_sqr.mean(axis=0))
plt.xlabel(r'$t$')
plt.ylabel(r'$\langle x^2 \rangle$')

plt.show()