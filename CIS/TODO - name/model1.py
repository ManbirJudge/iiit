import matplotlib.pyplot as plt
import numpy as np

# inputs
dt = 1
dx = 0.1
Pp = 0.5
Pn = 1 - Pp
N = 1_000

# simulation
n_elec = 10_000

rng = np.random.default_rng()

x_t = np.empty((n_elec, N + 1), dtype=float)  # time series (all electrons)
x_t[:, 0] = 0.0

for j in range(n_elec):
    x = 0
    for i in range(N):
        _dx = rng.choice([dx, -dx], size=np.shape(x), p=[Pp, Pn])
        x += _dx

        x_t[j][i + 1] = x

# plots
_t = np.arange(N + 1) * dt  # time axis (need for plots)
final_positions = x_t[:, -1]
mean_positions = x_t.mean(axis=0)
mean_square_positions = (x_t ** 2).mean(axis=0)

plt.figure(1)
for i in range(n_elec):
    plt.plot(_t, x_t[i])
plt.title('Time Series')
plt.xlabel('t')
plt.ylabel('x')

plt.figure(2)
plt.title('Frequency Distribution')
plt.hist(mean_positions, bins=30, density=True)
plt.xlabel('<x>')
plt.ylabel('f(x)')

plt.figure(3)
plt.title('<x> vs t')
plt.plot(_t, mean_positions)
plt.xlabel('t')
plt.ylabel('<x>')

plt.figure(4)
plt.title('<x^2> vs t')
plt.plot(_t, mean_square_positions)
plt.xlabel('t')
plt.ylabel('<x^2>')

plt.show()