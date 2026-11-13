# Model 7
## Description
[DGM]\
We can define the potential operator as
$$\hat{U}(\hat x, \hat y)\equiv\left\{ \begin{matrix} 0, x^2 + y^2 = R^2 \\ \infty, \text{otherwise} \end{matrix} \right.$$

## Calculation
### Wavefunction
From Schrodinger's equation,
$$\hat K \psi(x,y) + \hat U (\hat x, \hat y) \psi(x,y) = E \psi(x,y)$$

For $x^2 + y^2 = R^2$,
$$\hat K \psi(x,y) = E \psi(x,y)$$
$$- \frac{\hbar^2}{2m} \nabla^2 \psi(x,y) = E\psi(x,y)$$

Changing to polar coordinates:
$$-\frac{\hbar^2}{2m} \nabla^2 \psi(r, \theta) = E\psi(r, \theta)$$
$$-\frac{\hbar^2}{2m} \left( \frac{\partial^2}{\partial r^2} \psi(r, \theta) + \frac{1}{r} \frac{\partial}{\partial r} \psi(r, \theta) + \frac{1}{r^2} \frac{\partial^2}{\partial\theta^2} \psi(r, \theta)\right) = E \psi(r, \theta)$$

> **Note:** Look at derivation of Laplacian operator for polar coordinates [here](https://faculty.curgus.wwu.edu/Courses/Math_pages/Math_430/Laplacian_in_polar.html).

But since $r = R$ is fixed, $\psi(r,\theta) = \psi(R, \theta)=\psi(\theta)$.\
And hence, radial derivatives vanish and, we get
$$-\frac{\hbar^2}{2m} \left( \frac{1}{R^2}\frac{\partial^2 \psi(\theta)}{\partial\theta^2} \right) = E \psi(\theta)$$

Substitute, moment of inertia, $I = mR^2$.

$$\boxed {-\frac{\hbar^2}{2I} \frac{\partial^2 \psi(\theta)}{\partial\theta^2} = E \psi(\theta)}$$

After solving, we get
$$\psi(\theta) = Ae^{i m_l \theta}$$

Applying boundary conditions:
$$\psi(\theta + 2\pi) = \psi(\theta)$$
$$Ae^{i m_l (\theta + 2\pi)} = Ae^{i m_l \theta}$$
$$e^{m_l 2\pi i} = 0$$
$$m_l \in I$$

Normalization:
$$\int_0^{2\pi} \psi^\star(\theta)\psi(\theta) \,d\theta = 1$$
$$...$$
$$A = \frac{1}{\sqrt{2\pi}}$$

Therefore,
$$\boxed{\psi_{m_l}(\theta) = \frac{1}{\sqrt{2\pi}} e^{i m_l \theta}} \text{ for } m_l \in I$$

### Kinetic Energy
Extending definition of kinetic energy operator to circular motion:
$$\hat K\equiv-\frac{\hbar^2}{2I}\frac{d^2}{d\theta^2}$$
Therefore,
$$-\frac{\hbar^2}{2I}\frac{d^2}{d\theta^2}\psi_{m_l}(\theta)=K\psi_{m_l}(\theta)$$
$$-\frac{\hbar^2}{2I}\frac{d^2}{d\theta^2} \left( \frac{1}{\sqrt{2\pi}}e^{i m_l \theta}\right)=K\psi_{m_l}(\theta)$$
$$-\frac{\hbar^2}{2I}\frac{1}{\sqrt{2\pi}}(i m_l)^2e^{i m_l \theta}=K\psi_{m_l}(\theta)$$
$$\boxed{K_{m_l}=\frac{m_l^2 \hbar^2}{2mR^2}}$$

## Energy
**Ground state:** $m_l = 0$ and $E_{min} = E_0 = 0$.\
[DGM]\
Each energy level (except for ground state) corresponds to two separate excited states corresponding to $\pm m_l$. We call such states as **degenerate**.

## Exercises
- Angular momentum operator
- Stark effect, Zeeman effect and magnetization operator