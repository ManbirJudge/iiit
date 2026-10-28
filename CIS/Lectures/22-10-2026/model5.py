import numpy as np
import random
import matplotlib.pyplot as plt

def dist(x1: float, x2: float, y1: float, y2: float, z1: float, z2: float) -> float:
    return np.sqrt(((x1 - x2) ** 2) + ((y1 - y2) ** 2) + ((z1 - z2) ** 2))

N = 108
min_r = 3  # angstrom
L = 20  # angstrom

Us = []

for _ in range(10000):
    print(f'\rIter {_}', end='')

    x = np.empty((N,), dtype=float)
    y = np.empty((N,), dtype=float)
    z = np.empty((N,), dtype=float)
    x[0] = random.random() * L
    y[0] = random.random() * L
    z[0] = random.random() * L

    for i in range(1, N):
        found = False

        while not found:
            x[i] = random.random() * L
            y[i] = random.random() * L
            z[i] = random.random() * L

            found = True
            for j in range(i):
                if dist(x[i], x[j], y[i], y[j], z[i], z[j]) < min_r:
                    found = False
                    break

    sigma = 3.4  # angstrom
    epsilon = 0.238  # kcal/mol

    U = 0.0

    for i in range(N - 1):
        for j in range(i + 1, N):
            d = dist(x[i], x[j], y[i], y[j], z[i], z[j])

            U += 4 * epsilon * (((sigma / d) ** 12) - ((sigma / d) ** 6))

    Us.append(U)

plt.hist(Us, bins=50, edgecolor="black")
plt.xlabel("U (kcal/mol)")
plt.ylabel("Frequency")
plt.title("Potential Energy Distribution")
plt.show()

# with open('coords.txt', 'w') as f:
#     f.write('108\n')
#     f.write('model 5\n')
#     for i in range(N):
#         f.write(f'C {x[i]} {y[i]} {z[i]}\n')
# 
# print(f'U = {U}')
# 
# fig = plt.figure()
# ax  = fig.add_subplot(projection='3d')
# ax.scatter(x, y, z)
# 
# plt.show()