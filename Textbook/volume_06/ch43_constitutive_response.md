# Chapter 43 — Constitutive Response

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $S$ the state coordinate of Chapter 41; $\eta$ declared controls; $J$ a vector of throughputs; $\lambda$ multipliers; $S_{kj}=\partial y(t_k)/\partial\theta_j$ the sensitivity matrix of an output $y$ to parameters $\theta$. Executable companion: `Textbook/examples/ch43_constitutive_response.cpp`; pre-registration and captured output in `Textbook/validation/`. All models are generic stand-ins (TOY) with no measured input.

## 43.1 The missing map is a physical operator

Compatibility constrains $Q(S)$ (Chapters 41 and 42); a constitutive law selects a route. Write $Q_i=Q_i(S;\eta)$ and $dS/d\tau=F_S(S,\eta)$ separately. The first governs correlated state changes; the second governs the rate of progression. A calibrated wavelength ladder can constrain the first without determining the second, and so without determining an elapsed duration (here $\tau$ is a parameter of the route, to be tied to a counted recurrence before it means a duration).

For measured controls $u$, local identifiability of the parameters $\theta$ depends on the rank of $\partial(\text{outputs})/\partial\theta$ after known symmetries are removed. Nearly parallel response columns can make a formally identifiable model poorly conditioned.

**Executed (T2).** Take $y(t)=a\,e^{-bt}+c\,e^{-dt}$ with $\theta=(a,b,c,d)=(1,1,1,1+\Delta)$ sampled at $t_k=0.2k$, $k=1\ldots10$. The singular values of $S$ (computed by a one-sided Jacobi iteration; the first version formed $S^TS$ and lost the small singular values, which is recorded in the pre-registration) give the condition number $4.36\times10^{2}$ for $\Delta=1$, $2.80\times10^{5}$ for $\Delta=0.1$ and $2.75\times10^{8}$ for $\Delta=0.01$; at $\Delta=0$ the two exponentials coincide, the smallest singular values are $5\times10^{-17}$ and $9\times10^{-17}$ and the model has rank 2 and is not identifiable. The parameters are formally identifiable for every $\Delta>0$ and practically unidentifiable as $\Delta\to0$.

**The useful next measurement (T3).** For $\Delta=0.1$, repeating the same ten sampling times leaves the condition number unchanged ($2.8023\times10^{5}$, to $2\times10^{-13}$ relative: duplicating rows scales $S^TS$ and not its conditioning), while adding ten samples at $t=4,4.5,\ldots,8.5$ lowers it to $5.96\times10^{4}$, a factor $4.7$. The useful measurement distinguishes response directions; more points along an already constrained direction do not.

## 43.2 Constrained allocation and dual response

Contact throughput has capacities, inventories and competing channels. A conditional stationary reduction minimises a supplied functional $F(J,X)$ subject to $CJ=b$. With the Lagrangian $F+\lambda^T(CJ-b)$ the multipliers enforce the constraint,

$$\nabla_JF+C^T\lambda=0,\qquad\frac{\partial F^*}{\partial b}=-\lambda, \tag{43.1}$$

so that the dual variables quantify the marginal response of the constrained optimum to the constraint.

**Executed (V1, T1).** The routine reproduced the known case $Q=I_2$, $c=0$, $J_1+J_2=1$ ($J=(\tfrac12,\tfrac12)$, $\lambda=-\tfrac12$, $F^*=\tfrac14$). For the four-channel problem ($Q$ symmetric positive definite, $c=(1,-2,0.5,1)$, two constraints, $b=(1,0.3)$) the optimum is $J=(0.210365,\,0.511900,\,-0.023033,\,0.300768)$ with $\lambda=(-0.549290,\,-0.973820)$ and $F^*=0.15862572$; the stationarity residual and the constraint residual are $2.2\times10^{-16}$, and $\partial F^*/\partial b_i$ by central difference equals $-\lambda_i$ to $1.4\times10^{-12}$ and $1.8\times10^{-12}$. The third channel is negative, which a flow with a sign convention of throughput would have to allow or forbid explicitly.

The mathematics also appears in economics and in network allocation because the constraint structure is shared. That correspondence suggests useful sensitivities and bottleneck diagnostics. It does not supply the functional: a cost functional, dissipation metric or preference ordering has to be derived for the physical contact system, and economic terminology cannot supply an unknown microscopic coefficient or establish a variational principle without mechanics.

## 43.3 Matching sectors

At an interface, compatible state and flux conditions join optical, thermal, mechanical and chemical sectors. No artificial cross-sector barrier belongs in the atlas, but a physical boundary can suppress a coupling. A zero coupling is recorded as a calculated or measured result with its domain, and not assumed to be a universal communication strength.

## 43.4 The determining closure

One contact-response kernel producing the directional impulse, the relay duration, the material transport and the transition rates, with a shared parameter ledger and independently checked reservoir balances. The tests above set the conditions it must meet: its parameters must be identifiable from the planned measurements (the rank and conditioning of its sensitivity matrix reported), its constrained reductions must state their functional, and its duals must be the marginal responses (43.1).

## 43.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (43.1) and the KKT solution | Section 43.2 | DERIVED (exact) and COMPUTED |
| identifiability and conditioning | Section 43.1 | COMPUTED (stand-in model) |
| model, functional, constraints | as stated | CONSTRUCTION (no measured input) |

**Residuals.**

* **R43.1 — the operator.** No constitutive operator $F_S$ or correlated map is supplied by the engine or derived here.
* **R43.2 — the functional.** The functional $F(J,X)$ for the physical contact system is not derived; the quadratic form is a stand-in.
* **R43.3 — sector coupling.** Which sectors are coupled at an interface, and which couplings vanish, are not computed.
* **R43.4 — measured identifiability.** No measured response is loaded; identifiability was assessed for a stand-in model only.

## 43.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch43_constitutive_response
```

Criteria were registered in `Textbook/validation/ch43_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion but its T2 pass was weak (the condition number at $\Delta=0.01$ printed as infinity because singular values were taken from $S^TS$); the routine was replaced and the criterion strengthened. Run 2 (`ch43_run2_output.txt`) is the run of record and met every criterion.

## 43.7 Exercises and answers

**Exercise 1.** Show $\partial F^*/\partial b=-\lambda$.

*Answer.* At the optimum $F^*(b)=L(J^*(b),\lambda^*(b);b)$ with $L=F+\lambda^T(CJ-b)$. By stationarity in $J$ and $\lambda$ only the explicit dependence on $b$ remains: $\partial L/\partial b=-\lambda$.

**Exercise 2.** In V1, find $J$ and $\lambda$ analytically.

*Answer.* $\nabla F=J$, so $J+\lambda(1,1)^T=0$ and $J_1=J_2=-\lambda$; $J_1+J_2=1$ gives $J=(\tfrac12,\tfrac12)$, $\lambda=-\tfrac12$, $F^*=\tfrac14$.

**Exercise 3.** Why does duplicating the sampling times leave $\kappa$ unchanged?

*Answer.* The doubled sensitivity matrix has $S_2^TS_2=2S^TS$; all singular values are multiplied by $\sqrt2$ and their ratio is unchanged.

**Exercise 4.** Why is the model at $\Delta=0$ not identifiable?

*Answer.* $y=(a+c)e^{-bt}$ depends on $a$ and $c$ only through their sum, and the columns for $a$ and $c$ (and for $b$ and $d$) coincide.

**Exercise 5.** What does a negative multiplier $\lambda_1$ mean?

*Answer.* $\partial F^*/\partial b_1=-\lambda_1>0$: increasing the first constraint level raises the optimal value.

**Exercise 6.** Why can a cost functional not be taken from an analogy?

*Answer.* The analogy supplies the constraint structure; the coefficients of the functional are properties of the physical system and need their own derivation.

## 43.8 Scope

Established: the stationarity and duality relations (43.1) executed on a stand-in allocation; the rank and conditioning of a sensitivity matrix as the test of identifiability, with the exact effect of repeating samples and the effect of adding samples at new times.

Not established: the constitutive operator (R43.1), the physical functional (R43.2), the sector couplings (R43.3) and any measured identifiability (R43.4).

*Where it leads.* Chapter 44 treats thermal recurrence: temperature readings from mode populations and the octave algebra of the spectral reference.
