# Chapter 16 — Conservation and Continuum Limits

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. A scaled count is $t=\varepsilon m$ for $m$ relay counts at hop spacing $\varepsilon$; it is a dimensionless ratio and not a duration. Executable companion: `Textbook/examples/ch16_conservation_and_continuum_limits.cpp`; pre-registration and captured output in `Textbook/validation/`. Sections 16.2–16.5 use the TOY relay chain of Chapter 14, generic and carrying no measured input; Section 16.6 executes the engine's transport kernel at CONSTRUCTION test values.

## 16.1 The physical question

A conservation statement is made at one of three levels, and the level fixes what can be asserted. It is **exact** when the update rule itself conserves the quantity, so the statement holds for every state and every number of counts. It is **coarse-grained** when a continuum equation, obtained from the rule by a scaling limit, conserves the quantity; the statement then holds to the order of the limit and only for wavenumbers the limit covers. It is **numerical** when a discretisation of a continuum equation conserves the quantity; that is a property of the scheme, and two schemes for the same equation can differ in it. The chapter derives the continuity and balance equations of the chain, separates the three levels by execution, and then states which transport coefficients of the engine belong to which limit.

## 16.2 Exact conservation on a ring

On a ring the chain of Eq. (14.2) has no boundary, so Eq. (15.1) has no flux term. Summing the update over cells gives $\sum R'=(1-s)\sum R+s\sum L$ and $\sum L'=(1-s)\sum L+s\sum R$. The total $U=\sum(R+L)$ is unchanged and the momentum content $P=\sum(R-L)$ obeys

$$P(m+1)=(1-2s)\,P(m),\qquad P(m)=(1-2s)^mP(0). \tag{16.1}$$

Content is exactly conserved; momentum content is exactly not, and decays at a rate fixed by the reversal fraction. The difference $P(0)-P(m)$ is the total recoil taken by the reversing agent (Eq. 15.2), so the ring has no momentum ledger of its own (residual R15.1 of the previous chapter). Executed (T1, 200 cells, random content, 200 counts): the content changed by at most $5.0\times10^{-15}$ (relative, $s=0.1$) and $1.1\times10^{-14}$ ($s=0.3$); the momentum content matched $(1-2s)^mP(0)$ to $4.6\times10^{-14}$ and $3.5\times10^{-14}$ of $\lvert P(0)\rvert$ with $P(0)=-4.14311$, and after 200 counts it had fallen to $2.8\times10^{-14}$ in magnitude.

## 16.3 The exact two-field recurrence and its balance form

Write $u=R+L$ and $j=R-L$ and $\rho=1-2s$. Inserting $R=(u+j)/2$ and $L=(u-j)/2$ into (14.2) gives, exactly,

$$u'_i=\tfrac12\big(u_{i-1}+u_{i+1}\big)-\tfrac12\rho\,\big(j_{i+1}-j_{i-1}\big),\qquad j'_i=-\tfrac12\big(u_{i+1}-u_{i-1}\big)+\tfrac12\rho\,\big(j_{i-1}+j_{i+1}\big), \tag{16.2}$$

with primes denoting the next count. The first line is a continuity equation: $u'-u$ is a difference of interface terms (Exercise 1). The second is the balance of momentum content with the reversal factor $\rho$ built in. Nothing has yet been approximated.

## 16.4 The scaling limit: the telegraph system

Take the hop spacing $\varepsilon\to0$ with the reversal fraction scaling as $s=\gamma\varepsilon$, so that the reversal count per unit scaled count is fixed, and with $x=\varepsilon i$, $t=\varepsilon m$. Expanding (16.2) to first order in $\varepsilon$ gives

$$\partial_tu=-\partial_xj+O(\varepsilon),\qquad \partial_tj=-\partial_xu-2\gamma\,j+O(\varepsilon), \tag{16.3}$$

the telegraph system. Eliminating $j$:

$$\partial_t^2u+2\gamma\,\partial_tu=\partial_x^2u. \tag{16.4}$$

Its modes $e^{ikx+\mu t}$ have $\mu_\pm=-\gamma\pm\sqrt{\gamma^2-k^2}$. For $k>\gamma$ the roots are complex: a damped wave at unit speed with decay rate $\gamma$ independent of $k$, the scaling limit of the wave branch of Chapter 14. For $k\ll\gamma$, $\mu_+\simeq-k^2/(2\gamma)$, so $\partial_tu=D\,\partial_x^2u$ with

$$D=\frac1{2\gamma}, \tag{16.5}$$

the scaling limit of the chain's $D=(1-s)/(2s)$. The telegraph equation keeps a finite front speed (one), which the diffusion equation does not have; the two agree for scaled counts long compared with $1/(2\gamma)$.

**Executed (T2).** For $\gamma=1$ the chain eigenvalue $\lambda_+(\kappa=k\varepsilon;\,s=\gamma\varepsilon)$ was compared, as $\ln\lambda_+/\varepsilon$, with $\mu_+(k)$ for $\varepsilon=0.1,\,0.05,\,0.025,\,0.0125$:

| $k$ | $\mu_+$ | errors at the four $\varepsilon$ | observed orders |
|---|---|---|---|
| 0.5 | $-0.133975$ | $1.515\times10^{-2},\ 7.652\times10^{-3},\ 3.846\times10^{-3},\ 1.928\times10^{-3}$ | $0.985,\ 0.992,\ 0.996$ |
| 2.0 | $-1.000000+1.732051\,i$ | $1.338\times10^{-1},\ 6.192\times10^{-2},\ 2.987\times10^{-2},\ 1.468\times10^{-2}$ | $1.112,\ 1.052,\ 1.025$ |

Table 16.1. Convergence of the chain's dispersion relation to the telegraph system, executed (T2).

The limit exists on both branches and is first order, as the $O(\varepsilon)$ terms of (16.3) require.

**Executed (T3).** On a ring of length 40 with $\gamma=1$, a Gaussian $u_0=e^{-(x-20)^2/2}$ with $j=0$ (so $R=L=u_0/2$ at every cell) was run to scaled count $t=2$ on $400$, $800$ and $1600$ cells ($\varepsilon=0.1,\,0.05,\,0.025$) and compared at the cell positions with the Fourier solution of (16.4), $u=\sum_nc_nF(k_n,t)e^{ik_nx}$ with $F=(\mu_+e^{\mu_-t}-\mu_-e^{\mu_+t})/(\mu_+-\mu_-)$. The relative $L^2$ error was $2.83\times10^{-2},\,1.40\times10^{-2},\,6.99\times10^{-3}$, an observed order of $1.011$ and $1.005$. The continuum equation is the limit of the chain in real space as well as in Fourier space, at first order.

The limit is not uniform in $k$. The expansion needs $k\varepsilon\ll1$ and $s\ll1$; at wavenumbers of order the hop spacing the chain's own dispersion, Eq. (14.5) and the band edge (14.4), replace the telegraph form. A continuum equation therefore has a stated domain, and a feature outside the domain (the superluminal-looking group velocity of Chapter 14, for example) is a property of the chain and not of the limit.

## 16.5 Numerical conservation is a property of the scheme

A continuum equation in flux form, $\partial_tu=\partial_x(D(x)\partial_xu)$, conserves $\int u$. A discretisation conserves $\sum u$ only if it is written as a difference of interface fluxes, so that the sum telescopes. Executed (T4) on a ring of length 1 with $D(x)=1+\tfrac12\sin2\pi x$ and a Gaussian of width $0.1$ at $x=0.3$, run to scaled count $0.05$ with $\Delta=0.2h^2/1.5$:

| points $n$ | steps | flux-form drift of $\sum u$ | expanded-form drift of $\sum u$ |
|---|---|---|---|
| 64 | 1536 | $0$ | $2.653\times10^{-4}$ |
| 128 | 6144 | $2.2\times10^{-16}$ | $6.634\times10^{-5}$ |
| 256 | 24576 | $2.2\times10^{-16}$ | $1.659\times10^{-5}$ |

Table 16.2. Relative change of the sum under the two schemes, executed (T4). The expanded form is $D_iu_{xx}+D'_iu_x$ with central differences.

The expanded form is the same equation to second order and drifts at second order in $h$ (observed $2.000$ and $2.000$); the flux form conserves to round-off at every $n$. The two schemes agree on the equation and differ on the ledger. A conserved quantity checked only in the continuum equation is therefore not yet checked in a computation (Chapter 15 reported conserved sums of the engine's integrators for the same reason).

## 16.6 The engine's transport coefficients

The engine carries a block of dilute monatomic transport from one collision kernel (`law_IV::transport`, `laws.hpp:748–827`; its own header gives provenance SDT-computed, class C, domain hard-lock dilute monatomic, with the statement that no transport observation enters). Two atoms of mechanical boundary $b$ contact at diameter $2b$; the lock-weighted collision measure is $\tfrac67(2b)^2$ with the factor $\tfrac67$ the engaged fraction of the spherical domain (FLM15). The hard-lock collision integrals are unity, and the moments are $\tfrac38$ (diffusion), $\tfrac5{16}$ (trace-free traction) and $\tfrac{75}{64}$ (energy). With $n=P/(k_BT)$ and $\sigma=\tfrac67(2b)^2$ the engine returns

$$\eta=\frac5{16}\frac{\sqrt{mk_BT/\pi}}{\sigma},\qquad \kappa=\frac{75}{64}\frac{k_B\sqrt{k_BT/(\pi m)}}{\sigma},\qquad D=\frac38\frac{\sqrt{k_BT/(\pi m)}}{n\,\sigma}. \tag{16.6}$$

Because all three come from one kernel their ratios are fixed numbers. With $c_p=\tfrac52k_B/m$ and $\rho_m=nm$:

$$\mathrm{Pr}=\frac{c_p\eta}{\kappa}=\frac52\cdot\frac5{16}\cdot\frac{64}{75}=\frac23,\qquad \mathrm{Sc}=\frac{\eta}{\rho_mD}=\frac{5/16}{3/8}=\frac56,\qquad \mathrm{Le}=\frac{\mathrm{Sc}}{\mathrm{Pr}}=\frac54. \tag{16.7}$$

**Executed (T5).** At the CONSTRUCTION test point $T=300$ K, $P=101325$ Pa, $m=6.6\times10^{-26}$ kg, $b=1.8\times10^{-10}$ m the kernel returned $\eta=2.624165\times10^{-5}$ Pa s, $\kappa=2.058551\times10^{-2}$ W m$^{-1}$K$^{-1}$, $D=1.950367\times10^{-5}$ m$^2$s$^{-1}$, with collision measure $1.110857\times10^{-19}$ m$^2$. The three numbers (16.7) were reproduced to $2\times10^{-16}$. The scalings were reproduced to $10^{-13}$ or better: at fixed $P$, $T\to4T$ multiplies $\eta$ and $\kappa$ by $2$ and $D$ by $8$; $P\to2P$ leaves $\eta,\kappa$ unchanged and halves $D$; $b\to2b$ divides all three by $4$; $m\to4m$ multiplies $\eta$ by $2$ and halves $\kappa$ and $D$. These checks establish that the function does what its header states: they do not compare the coefficients with any measured gas, and no measured transport value was loaded.

**Form compared with the textbook hard-sphere first approximation.** The textbook expressions for rigid spheres of diameter $d$ have the same moments $\tfrac5{16}$, $\tfrac{75}{64}$, $\tfrac38$ with collision measure $d^2$. With $d=2b$ the engine's three coefficients equal them multiplied by $7/6$ in each case ($\eta/\eta_{HS}=\kappa/\kappa_{HS}=D/D_{HS}=1.166667$ to $10^{-13}$). The coincidence of form is convergence of two derivations, not a finding that the engine imports the textbook result: the engine's moments come from its own collision integral and the factor $7/6$ is the inverse of its engaged-volume fraction $\tfrac67$.

**Which limit these coefficients belong to.** The coefficients (16.6) are those of the parabolic limit, the analogue of (16.5): a coefficient fixed by a collision measure and a speed. The chain has no collision geometry, only a reversal fraction, and its $D=1/(2\gamma)$ is the same logical kind (a speed squared over a reversal rate). The engine's kernel supplies no relaxation count, so it does not say for how many counts after a disturbance the hyperbolic behaviour of (16.4) must be used instead (residual R16.3).

## 16.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| chain parameters ($s,\gamma,\varepsilon$, sizes, generator seed), scheme parameters of T4 | as stated | CONSTRUCTION |
| (16.1)–(16.5) and the executed convergence and conservation values | Sections 16.2–16.5 | DERIVED (exact) or COMPUTED |
| $k_B$ | `measured::k_B` | MEASURED-INPUT (unit bridge) |
| moments $\tfrac38,\tfrac5{16},\tfrac{75}{64}$, hard-lock collision integrals $=1$ | engine's | DERIVED in the engine (FD02); taken as stated here, not re-derived |
| engaged fraction $\tfrac67$ | engine's | DERIVED in the engine (FLM15); not re-derived here |
| test point $T,P,m,b$ | as stated | CONSTRUCTION |
| (16.7), scalings, ratio $7/6$ | Section 16.6 | COMPUTED |

**Residuals.**

* **R16.1 — the limit is of a TOY.** The telegraph system is the scaling limit of a chain whose response operator is not that of the real medium (R14.1). The continuity and balance equations of the real medium await a response law.
* **R16.2 — uniformity.** The limits hold at first order and for $k\varepsilon\ll1$; behaviour near the hop scale is that of the chain.
* **R16.3 — relaxation count.** The engine's transport kernel gives parabolic coefficients without a relaxation count; the crossover to the hyperbolic regime for the real medium is not given.
* **R16.4 — the thermal input.** $T$ enters through $k_BT$ with $k_B$ a unit bridge; what $T$ measures in the relay medium is not derived here.
* **R16.5 — boundary and load from outside.** The mechanical boundary $b$ and the load $m$ enter as inputs. No comparison with measured transport coefficients is made in this chapter; the engine's own comparison is its benchmark B16, and a registered comparison with measured coefficients is left to the chapters that compare with measurement.
* **R16.6 — domain.** The kernel is valid for the dilute monatomic hard-lock domain only, as the engine's header states.
* **R16.7 — the moments.** The coefficients $\tfrac38,\tfrac5{16},\tfrac{75}{64}$ and the fraction $\tfrac67$ are taken from the engine; a derivation within the book is not given.

## 16.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch16_conservation_and_continuum_limits
```

Criteria were registered in `Textbook/validation/ch16_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch16_run1_output.txt`) is the run of record and met every criterion: the instrument checks V1 (exact discrete decay factor of a Fourier mode under the flux-form scheme) and V2 (the solution factor $F$ on its known limits) preceded the tests on the object.

## 16.9 Exercises and answers

**Exercise 1.** Show that the first line of (16.2) is a continuity equation.

*Answer.* $u'_i-u_i=\tfrac12(u_{i-1}-2u_i+u_{i+1})-\tfrac12\rho(j_{i+1}-j_{i-1})$ is a difference of interface quantities $G_{i+1/2}-G_{i-1/2}$ with $G_{i+1/2}=\tfrac12(u_{i+1}-u_i)-\tfrac12\rho(j_{i+1}+j_i)$.

**Exercise 2.** Obtain (16.4) from (16.3).

*Answer.* Differentiate the first equation in $t$ and substitute the second: $\partial_t^2u=-\partial_x\partial_tj=\partial_x^2u+2\gamma\partial_xj=\partial_x^2u-2\gamma\partial_tu$.

**Exercise 3.** Show $D=1/(2\gamma)$ in the limit $k\ll\gamma$.

*Answer.* $\mu_+=-\gamma+\gamma\sqrt{1-k^2/\gamma^2}\simeq-k^2/(2\gamma)$, so $e^{\mu_+t}$ is the decay of a diffusion with $D=1/(2\gamma)$.

**Exercise 4.** Derive (16.1).

*Answer.* $\sum R'-\sum L'=[(1-s)-s]\sum R-[(1-s)-s]\sum L=(1-2s)P$.

**Exercise 5.** Evaluate $\mathrm{Pr}$ from (16.6).

*Answer.* $\mathrm{Pr}=\frac52\frac{k_B}{m}\eta/\kappa$ with $\eta/\kappa=\frac{5/16}{75/64}\frac{m}{k_B}=\frac{4}{15}\frac m{k_B}$, so $\mathrm{Pr}=\frac52\cdot\frac4{15}=\frac23$.

**Exercise 6.** Show why a flux-form scheme conserves $\sum u$ on a ring.

*Answer.* $\sum_i(F_{i+1/2}-F_{i-1/2})=0$ on a ring, because each interface flux appears once with each sign.

**Exercise 7.** By what factor does the engine's $\eta$ exceed the rigid-sphere first approximation with $d=2b$?

*Answer.* The collision measure is $\tfrac67d^2$ instead of $d^2$, so $\eta$ is larger by $7/6=1.166667$.

## 16.10 Scope

Established in this chapter: content is exactly conserved and momentum content exactly decays as $(1-2s)^m$ on the TOY ring; the chain has the exact two-field recurrence (16.2); its scaling limit is the telegraph system (16.3)–(16.4) at first order, in Fourier space and in real space, with diffusion coefficient $1/(2\gamma)$ in the parabolic limit; numerical conservation depends on the form of the scheme, not on the equation; and the engine's monatomic transport kernel returns the fixed ratios $2/3$, $5/6$, $5/4$ and the stated scalings, with coefficients equal to $7/6$ times the rigid-sphere first approximation at $d=2b$.

Not established: the continuity and balance equations of the real medium (R16.1), the crossover count between hyperbolic and parabolic behaviour (R16.3), the meaning of $T$ (R16.4), any comparison of the transport coefficients with measurement (R16.5), and the derivation of the moments and of $\tfrac67$ (R16.7).

*Where it leads.* Volume III turns from the response of the medium to the persistent forms in it, beginning with the electron circulation (Chapter 17) and the proton (Chapter 18).
