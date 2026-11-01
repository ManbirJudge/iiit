# Model 1
[TBDL]

## Inputs
- Time step $= \Delta t$
- Step length $= \Delta x$
- $P_+ = \frac{1}{2}$
- $P_- = \frac{1}{2}$
- Number of steps $= N$
- Length of wire $= L$

## Required Outputs
- Frequency distribution of Final Positions
- $\langle x \rangle$
- $\langle x^2 \rangle$
- $\langle x \rangle$ vs $t$
- $\langle x^2 \rangle$ vs $t$

## Expected Outputs
[TBDL]

## Code
In `model1.py`.

## Computed Outputs
[TBDL]

## Observation
$\langle x \rangle$ vs $t$ is linear with slope of $\frac{(\Delta x)^2}{\Delta t}$.\
We define, **diffusion constant**, $D = \frac{(\Delta x)^2}{2 \Delta t}$

## Mathematical Treatment
### Variance ($\sigma$) of Frequency Distribution of $x$
Final mean position is
$$\langle x \rangle = \frac{\int_{x_{min}}^{x_{max}} xf(x) \,dx}{\int_{x_{min}}^{x_{max}} f(x) \,dx}$$
Variance is
$$\sigma = \langle (x - \langle x \rangle)^2 \rangle = \frac{\int_{x_{min}}^{x_{max}} (x - \langle x \rangle)^2 f(x) \,dx}{\int_{x_{min}}^{x_{max}} f(x) \,dx}$$

### Collision Probability
$\mathbb{P}_{col}(x) = $ probability of two electrons to meet at $x$ after $N$ steps\
Expected plot:\
[TBDL]