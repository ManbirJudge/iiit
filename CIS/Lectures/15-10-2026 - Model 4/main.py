import numpy as np
import matplotlib.pyplot as plt

k = 1.0
m = 1.0
dt = 0.001

x = 2.0
p = 2.0
F = -1 * k * x

N = 10000

x_t = np.empty((N), dtype=float)
p_t = np.empty((N), dtype=float)

for i in range(N):
    p = p + (F * dt)
    x = x + (p / m * dt) + (0.5 * F / m * dt * dt)
    
    F = -1 * k * x

    x_t[i] = x
    p_t[i] = p

plt.figure()
plt.plot(x_t, p_t)

plt.figure()
plt.plot(x_t, np.linspace(0, N * dt, num=N))
plt.show()