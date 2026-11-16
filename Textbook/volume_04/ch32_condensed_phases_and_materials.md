# Chapter 32 — Condensed Phases and Materials

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: $C_{ij}$ are stiffness constants in Voigt notation; $G_V$, $G_R$, $G_H$ the Voigt, Reuss and Hill shear moduli; $\alpha_{\rm th}$ the thermal diffusivity; $\delta$ the thermal penetration depth. All model functions are labelled TOY: generic, with no measured material input. Executable companion: `Textbook/examples/ch32_condensed_phases_and_materials.cpp`; pre-registration and captured output in `Textbook/validation/`. The engine's `materials.hpp` supplies bulk aggregation (Section 32.5) and no constitutive law; this chapter states the determining equations and tests their structure, and assigns no closed material law.

## 32.1 The physical question

A material state includes composition, density, order, contact geometry and memory. The questions are what constraints linear response must satisfy before any material is specified, how far a scalar modulus can go, what fixes the slope of a phase boundary and what does not fix a transition rate, and how thermal forcing propagates. The chapter derives these constraints and checks them numerically on stand-ins; the engine's bulk and transport results are not extended to dense phases.

## 32.2 Elastic response

Linear elastic response is $\delta\sigma=C:\delta\varepsilon$ with $C$ a fourth-rank stiffness tensor whose symmetry and positivity depend on the material class. For a cubic class there are three independent constants $(C_{11},C_{12},C_{44})$. A scalar modulus discards the anisotropy and cannot predict orientation-dependent optics.

**Stability.** Small-strain collapse is prevented if and only if the $6\times6$ Voigt matrix is positive definite, which for cubic symmetry is

$$C_{11}>\lvert C_{12}\rvert,\qquad C_{11}+2C_{12}>0,\qquad C_{44}>0. \tag{32.1}$$

The wave speeds follow from the Christoffel matrix $\Gamma_{ik}=C_{ijkl}n_jn_l$ for propagation along $\hat n$; with (32.1) it is positive definite in every direction, so every speed is real.

**Isotropic reductions.** For cubic constants, with $d=C_{11}-C_{12}$, the Voigt average $G_V=(d+3C_{44})/5$ and the Reuss average $G_R=5\,d\,C_{44}/(4C_{44}+3d)$ satisfy $G_R\le G_V$, with equality exactly when the Zener ratio $A=2C_{44}/d=1$ (an isotropic material).

**Executed (T1; V1).** The isotropic constants $(\lambda,G)=(2,1)$ gave $A=1$, bulk modulus $\lambda+2G/3$ and $G_V=G_R=G$ to round-off. For 20000 pseudo-random triples (7870 of them satisfying (32.1)): the Cholesky factorisation of the Voigt matrix succeeded exactly when (32.1) held, in every one of the 20000 cases; for every stable triple the smallest Christoffel eigenvalue over 50 random directions was positive; for the unstable triple $(3,1,-1)$ the $[100]$ shear eigenvalue was $-1$ (an imaginary speed); $G_R\le G_V$ held for every stable triple; and over the sample the spread $(G_V-G_R)/G_H$ reached $1.9996$ (a factor-two disagreement between the two averages for strongly anisotropic constants), while for 200 isotropic triples it was $4\times10^{-16}$. A single modulus can therefore hide a spread of order its own size.

Beyond the linear regime, yielding, fracture and phase rearrangement need the evolution of the contact network; geometry-dependent changes in surviving contacts (Chapter 23, R23.3) can dominate latent work.

## 32.3 Phase boundaries and thermal response

Along a coexistence line of two phases with Gibbs functions $g_1(T,P)$, $g_2(T,P)$, $dg_1=dg_2$ gives

$$\frac{dP}{dT}=\frac{\Delta s}{\Delta v}=\frac{L}{T\,\Delta v}, \tag{32.2}$$

with $s=-\partial g/\partial T$, $v=\partial g/\partial P$ and $L=T\Delta s$, in one consistent per-particle or per-volume convention. The relation constrains a coexistence slope. A nucleation time also needs a barrier and a rate (Chapter 31, Section 31.5), and crystallisation, glass arrest and sublimation cannot be represented by one scalar transition flag.

**Executed (T2).** Two TOY Gibbs functions, quadratic in $\theta=T-T_0$ and $P$ with distinct entropy, heat-capacity, volume and compressibility constants, meeting at $(T_0,P_0)=(1,0)$. The coexistence pressure was found by Newton's method at 20 temperatures in $[0.9,1.1]$ ($P_c=-0.219691$ at $T=0.9$ and $0.283864$ at $T=1.1$; the TOY pressure is negative at low $T$) and its numerical derivative equalled $\Delta s/\Delta v$, with $s$ and $v$ evaluated on the curve, to $9.1\times10^{-9}$ relative (slopes $1.907793$ and $3.199829$ at the two ends, from $\Delta s=0.4,0.6$ and $\Delta v=0.20967,0.18751$). The second form, $L/(T\Delta v)$, is the same quantity by the definition of $L$ and agreed to the same figure.

**Periodic thermal forcing.** For a surface forced as $\cos\omega t$ on a conducting half-space, the steady periodic solution is $e^{-x/\delta}\cos(\omega t-x/\delta)$ with

$$\delta=\sqrt{\frac{2\alpha_{\rm th}}{\omega}},\qquad\alpha_{\rm th}=\frac{k_{\rm th}}{\rho c_p}. \tag{32.3}$$

**Executed (T3).** The heat equation with $\alpha_{\rm th}=1$, $\omega=2$ ($\delta=1$) was integrated in time (Crank–Nicolson, $\Delta x=0.01$, $\Delta t=0.005$, 30 periods from a zero state, far boundary at $8\delta$) and the response extracted over the last period: the amplitude at $x=\delta$ was $0.367762$ ($e^{-1}=0.367879$, difference $3.2\times10^{-4}$ relative), at $2\delta$ $0.135309$ ($e^{-2}=0.135335$, $2.0\times10^{-4}$), and the phase lags were $1.00046$ and $1.99962$ rad against $x/\delta=1,2$. A change in contact order can modify the conductivity, the heat capacity and the optical depth together, so the same chart of coupled ratios should carry all three while allowing distinct response functions for each.

## 32.4 Transport regime

The hard-lock dilute monatomic ratios of Chapter 16 ($\mathrm{Pr}=2/3$, $\mathrm{Sc}=5/6$, $\mathrm{Le}=5/4$) are properties of one collision kernel in the dilute domain, and the engine states that domain in its header. They are not universal constants of liquids or solids. Dense correlations and internal modes require a new closure derived from the changed contact ensemble; no dense-phase value is loaded or claimed here (residual R32.3).

## 32.5 What the engine's materials module supplies

`materials.hpp` aggregates a bulk state from a baryon count and a radius: volume, baryon density, the total koppa length (each baryon contributes `bridge::koppa_per_baryon`; Chapter 18) and its density, the far acceleration $c^2\varpi_{\rm tot}/d^2$ (the kernel of Chapter 15) and the surface value. It also carries a normalised helical wake kernel in which the $r^{-3}$ exponent is canonical and the unit surface normalisation is a visualisation convention, not an absolute amplitude prediction. These are source and far-field relations. They contain no stiffness tensor, no equation of state, no thermal law and no transport closure, so the constitutive response of Sections 32.2–32.4 has no engine counterpart yet.

## 32.6 The determining test

Predict elastic, thermal and optical changes across one material transition from the same order variable and the same energy ledger, with no sector-specific coefficient. By Section 32.2, the elastic part must satisfy (32.1) on both sides of the transition, and by (32.2) the slope of the transition line must follow from the entropy and volume jumps of the same ledger.

## 32.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (32.1), Voigt–Reuss inequality, (32.2), (32.3) | Sections 32.2–32.3 | DERIVED (exact), checked on TOY inputs |
| TOY stiffness triples, Gibbs functions, forcing | as stated | CONSTRUCTION (no measured input) |
| bulk aggregation in `materials.hpp` | engine's | the engine's source/far-field relations (no constitutive law) |

**Residuals.**

* **R32.1 — a constitutive law.** No stiffness tensor, equation of state or thermal law follows from the engine's contact law; the material rows are outstanding.
* **R32.2 — one order variable.** The same order variable and energy ledger across a transition have not been specified.
* **R32.3 — dense transport.** Closures for dense phases and internal modes are not derived.
* **R32.4 — rates.** Nucleation, yielding and fracture rates need barriers and mode populations, not computed here.
* **R32.5 — measured materials.** No measured modulus, latent heat or diffusivity is loaded.

## 32.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch32_condensed_phases_and_materials
```

Criteria were registered in `Textbook/validation/ch32_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch32_run1_output.txt`) is the run of record and met every criterion.

## 32.9 Exercises and answers

**Exercise 1.** Show that (32.1) is the positive-definiteness condition of the cubic Voigt matrix.

*Answer.* The matrix is block diagonal: the $3\times3$ block with $C_{11}$ on the diagonal and $C_{12}$ elsewhere has eigenvalues $C_{11}+2C_{12}$ (once) and $C_{11}-C_{12}$ (twice), and the shear block has eigenvalue $C_{44}$ (three times). Positivity of all of them gives $C_{11}+2C_{12}>0$, $C_{11}>C_{12}$, $C_{44}>0$. These are equivalent to (32.1): the extra statement $C_{11}>-C_{12}$ in $C_{11}>\lvert C_{12}\rvert$ follows from $C_{11}>C_{12}\ge0$ when $C_{12}\ge0$, and from $C_{11}>-2C_{12}>-C_{12}$ when $C_{12}<0$.

**Exercise 2.** Evaluate $G_V$ and $G_R$ for $(C_{11},C_{12},C_{44})=(3,1,1)$.

*Answer.* $d=2$; $G_V=(2+3)/5=1$; $G_R=5\cdot2\cdot1/(4+6)=1$. This is isotropic ($A=2\cdot1/2=1$).

**Exercise 3.** Derive (32.2).

*Answer.* On the line $g_1=g_2$, $-s_1dT+v_1dP=-s_2dT+v_2dP$, so $dP/dT=(s_2-s_1)/(v_2-v_1)$.

**Exercise 4.** Show the penetration depth (32.3).

*Answer.* With $T=\mathrm{Re}\,\hat T(x)e^{i\omega t}$, $i\omega\hat T=\alpha_{\rm th}\hat T''$ gives $\hat T=e^{-(1+i)x/\delta}$ with $\delta=\sqrt{2\alpha_{\rm th}/\omega}$.

**Exercise 5.** What is the phase lag at $x=3\delta$?

*Answer.* $3$ rad, from the factor $e^{-i3}$; the amplitude is $e^{-3}$.

**Exercise 6.** Why can the dilute $\mathrm{Pr}$ not be used for a liquid?

*Answer.* It follows from one collision kernel in the dilute domain; a dense phase has a different contact ensemble and internal modes.

## 32.10 Scope

Established: the stability conditions (32.1) and their consequences for wave speeds and the Voigt–Reuss spread, checked on 20000 stand-in triples; the coexistence slope (32.2) on a stand-in pair; the thermal penetration depth (32.3) against a time-domain solution; and the statement of what the engine's materials module supplies and does not supply.

Not established: a constitutive law (R32.1), one order variable across a transition (R32.2), dense transport (R32.3), rates (R32.4) and any measured material response (R32.5).

*Where it leads.* Volume V turns to the motion of bodies and the geometry of source and shadow: gravity without $G$, orbital mechanics and the solar system on the engine (Chapter 33 onward).
