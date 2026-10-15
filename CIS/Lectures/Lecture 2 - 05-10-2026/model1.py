import random
import matplotlib.pyplot as plt
import numpy as np

rng = np.random.default_rng()

L = 1000
dx = 1
dt = 1
N = 1000
Pp = 0.5
Pn = 1 - Pp 

n_elec = 10000
f = [0 for i in range(0, L, dx)]
x_t = [[-1 for i in range(N)] for _ in range(int(n_elec / 10))]

for j in range(n_elec):
    x = 0

    for i in range(N):
        y = random.random()
        dx_ = rng.normal(0.0, 1.0)
        x += dx_
        
        x = max(-int(L/2), x)
        x = min(int(L/2), x)

        # if (y >= Pp): 
        #     x -= dx_
        #     x = max(-int(L/2), x)
        # else:
        #     x += dx_
        #     x = min(int(L/2), x)

        if j % 10 == 0:        
            x_t[int(j / 10)][i] = x

    f[int(x) + int(L / 2)] += 1

n_crossings = [0 for i in range(N)]
for i in range(N):
    for j in range(0, n_elec, 100):
        if j % 10 != 0: continue
        for k in range(0, n_elec, 100):
            if k % 10 != 0: continue
            if (x_t[int(j / 10)][i] == x_t[int(k / 10)][i]):
                n_crossings[i] += 1

n_crossings = np.array(n_crossings)
# n_crossings /= (n_elec / 100)

positions = np.array([x - int(L/2) for x in range(0, L, dx)])
mean_x = np.average(positions, weights=f)
mean_x_sqr = np.average(positions**2, weights=f)

mean_x_t = [np.average([x_t[i][j] for i in range(int(n_elec / 10))]) for j in range(N)]
mean_x_sqr_t = [np.average([x_t[i][j] ** 2 for i in range(int(n_elec / 10))]) for j in range(N)]

print(f'<x> = {mean_x}')
print(f'<x^2> = {mean_x_sqr}')

plt.figure(1)
plt.scatter([x - int(L/2) for x in range(0, L, dx)], f, s=5)
plt.title('Frequency Distribution')
plt.xlabel('x')
plt.ylabel('f')

plt.figure(2)
for j in range(int(n_elec / 10)):
    plt.plot([i * dt for i in range(N)], x_t[j])
plt.title('Time Series')
plt.xlabel('t')
plt.ylabel('x')

plt.figure(3)
plt.title('<x> vs t')
plt.plot([i * dt for i in range(N)], mean_x_t)
plt.xlabel('t')
plt.ylabel('<x>')
plt.ylim(-L/2, L/2)

plt.figure(4)
plt.title('<x^2> vs t')
plt.plot([i * dt for i in range(N)], mean_x_sqr_t)
plt.xlabel('t')
plt.ylabel('<x^2>')

plt.figure(5)
plt.title('Pcol vs t')
plt.plot([i * dt for i in range(N)], n_crossings)
plt.xlabel('t')
plt.ylabel('Pcol')

plt.show()