import random
import matplotlib.pyplot as plt
import numpy as np

L = 1000
dx = 1
dt = 1
N = 5000
Pp = 0.5
Pn = 1 - Pp 

n_elec = 1000
f = [0 for i in range(0, L, dx)]
x_t = [[-1 for i in range(N)] for _ in range(int(n_elec / 10))]

for j in range(n_elec):
    x = 0

    for i in range(N):
        y = random.random()

        if (y >= Pp): 
            x -= dx
            x = max(-int(L/2), x)
        else:
            x += dx
            x = min(int(L/2), x)
        
        x_t[int(j / 10)][i] = x

    f[x + int(L / 2)] += 1

mean_x = np.average([x - int(L/2) for x in range(0, L, dx)], weights=f)
mean_x_sqr = np.average([(x - int(L/2)) ** 2 for x in range(0, L, dx)], weights=f)

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
plt.title('Time Series')  # for the last run
plt.xlabel('t')
plt.ylabel('x')

plt.show()
