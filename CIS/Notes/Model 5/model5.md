# Model 5
## Further Discussion on Hamiltonian Mechanics
By solving Hamilton's equations, we get trajectory of the given system in the phase-space.

For an isolated system, Hamiltonian (i.e., energy) is conserved:
$$H(x(t), p(t)) = E = H(x(0), p(0))$$
In above case, the phase-space trajectory is the fixed ellipse (called the **constant-energy curve**) we computed.

### Potential Energy
For model 4,
$$\frac{d^2U}{dx^2} = k$$
It is called **how shallow** or **steep of curve**.

### Entropy
Each point in phase-space defines a **microstate** of the system.\
Points on the ellipse is the set of accessible microstates. All other microstates (points) are inaccessible.

We define
$$\Omega(E) = \text{number of accessible microstates for energy E}$$

Experimentally,
$$S \propto \ln(\Omega(E))$$
$$S = k_b \ln(\Omega(E))$$

Boltzmann constant, $k_b = 1.38 \times 10^{-23} \space m^2 kg s^{-2} K^{-1}$

We also know,
$$\Omega(E) \propto \text{circumference of ellipse} \propto \pi(a + b)$$
$$\Omega(E) \propto E^{\frac{1}{2}}$$

## Model 5
[DGM]\
Number of particles, $N = 108$\
Side of cube $ = L$\
$0 \le x_i, y_i, z_i \le L$\
Distance between any two particles, $r_{ij} \ge 3$

Set of all positions, $\{\vec r\} = \{\vec{r_1}, \vec{r_2}, ..., \vec{r_N}\}$

Now, potential energy $U$ is as follows:
$$U(\{\vec r\}) = \sum_{i=1}^{N-1} \sum_{j=i+1}^{N} U_{ij}$$
$$U_{ij} = 4 \varepsilon \left[ \left( \frac{\sigma}{r_{ij}} \right)^{12} + \left( \frac{\sigma}{r_{ij}} \right)^6 \right]$$
Here, $\varepsilon$ and $\sigma$ are constant parameters.

And kinetic energy $K$ is as follows:
$$K(\{\vec p\}) = \sum_{i=1}^{N} \frac{p_i^2}{2m}$$

So Hamilton's equations for this system are
$$\frac{d \vec p_i}{dt} = -\frac{dH}{d \vec r_i}$$
$$\frac{d \vec r_i}{dt} = \frac{dH}{d \vec p_i}$$

Phase space for each particles would be chaotic (not random - deterministic but chaotic).

Solving $\frac{d \vec p_i}{dt}$,
$$TBDL$$

Solving $\frac{d \vec r_i}{dt}$,
$$TBDL$$