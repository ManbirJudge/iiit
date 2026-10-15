import random
import matplotlib.pyplot as plt
import numpy as np
import math

L = 2 * math.pi
dx = 1
dt = 1
N = 1000
Pp = 0.5
Pn = 1 - Pp 

n_elec = 10000
f = [0 for i in np.arange(0, L, dx)]
x_t = [[-1 for i in range(N)] for _ in range(int(n_elec / 10))]

for j in range(n_elec):
    x = 0

    for i in range(N):
        y = random.random()

        if (y >= Pp): 
            x -= dx
        else:
            x += dx

        if j % 10 == 0:        
            x_t[int(j / 10)][i] = math.fmod(x, 2 * math.pi) 

    f[x + int(L / 2)] += 1

positions = np.array([x for x in np.range(0, L, dx)])
mean_x = np.average(positions, weights=f)
mean_x_sqr = np.average(positions**2, weights=f)

mean_x_t = [np.average([x_t[i][j] for i in range(int(n_elec / 10))]) for j in range(N)]
mean_x_sqr_t = [np.average([x_t[i][j] ** 2 for i in range(int(n_elec / 10))]) for j in range(N)]

print(f'<theta> = {mean_x}')
print(f'<theta^2> = {mean_x_sqr}')

plt.figure(1)
plt.scatter([x for x in range(0, L, dx)], f, s=5)
plt.title('Frequency Distribution')
plt.xlabel('theta')
plt.ylabel('f')

plt.figure(2)
for j in range(int(n_elec / 10)):
    plt.plot([i * dt for i in range(N)], x_t[j])
plt.title('Time Series')
plt.xlabel('t')
plt.ylabel('x')

plt.figure(3)
plt.title('<theta> vs t')
plt.plot([i * dt for i in range(N)], mean_x_t)
plt.xlabel('t')
plt.ylabel('<theta>')
plt.ylim(-L/2, L/2)

plt.figure(4)
plt.title('<theta^2> vs t')
plt.plot([i * dt for i in range(N)], mean_x_sqr_t)
plt.xlabel('t')
plt.ylabel('<theta^2>')

plt.show()