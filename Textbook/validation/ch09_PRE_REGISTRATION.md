# Chapter 9 — pre-registration of the worked-example instruments

Registered 2026-11-03, before `Textbook/examples/ch09_directional_convergence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Units: content density $U=1$ (so $q=U/4\pi$ per steradian), $\kappa=\varepsilon=\ell=1$ where the displaced-observer case is used, body radii as stated. $U$ stands for the engine's $P_{\rm conv}=\Phi/\ell^3$ read as a density of arriving content (Chapter 9, premise P7).

## Quadrature

Gauss–Legendre nodes in $\mu=\cos\theta$ (Newton iteration on $P_n$), uniform trapezoid in $\phi$ (exact for trigonometric polynomials of degree below the node count). Node counts: $n_\mu = 96$, $n_\phi = 64$ unless stated. Hemisphere integrals use $\mu\in[0,1]$ directly, so no integrand kink lies inside a panel.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V1 | $\oint d\Omega = 4\pi$; $\oint n_in_j\,d\Omega = (4\pi/3)\delta_{ij}$; $\oint n_x^2n_y^2\,d\Omega = 4\pi/15$; $\oint n_z^4\,d\Omega = 4\pi/5$ | $10^{-12}$ relative |
| V2 | $\oint n_i\,d\Omega = 0$ and $\oint n_in_jn_k\,d\Omega = 0$ for all index triples | $10^{-12}$ absolute |
| V3 | hemisphere $\int_{\mu>0}\mu\,d\Omega = \pi$ and $\int_{\mu>0}\mu^2\,d\Omega = 2\pi/3$ | $10^{-12}$ relative |

If V1–V3 fail the instrument is faulty; no T-result is quoted until it is repaired and re-validated. A recalled reference value that is the suspect is re-derived by an independent route before the instrument is blamed.

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | isotropic incident content on an absorbing plane: traction $=U/6$ along the inward normal | $\lvert t\rvert/U\in 1/6\pm10^{-12}$; tangential part $<10^{-14}$ | yes — $1/4$, $1/3$ or $1/2$ fail |
| T2 | specular plane: traction $=U/3$, equal to the trace share $\operatorname{tr}\Pi/3$ | within $10^{-12}$ of $U/3$ and of $\operatorname{tr}\Pi/3$ | yes |
| T3 | displaced observer in a common ball, exact $L(\theta)$ of Eq. (4.10): the second moment is $\Pi_{ij}=\Pi_\parallel\hat s_i\hat s_j+\Pi_\perp(\delta_{ij}-\hat s_i\hat s_j)$ with $\operatorname{tr}\Pi=\Phi(s)$ and the series coefficients $(\Pi_\parallel-\Pi_\perp)\,\ell R/(\kappa\varepsilon s^2) \to 1/15$ | for $s/R\in\{0.01,0.05,0.1\}$: relative difference from $1/15$ at most $3\,(s/R)^2$ (the next term is $O(s^2/R^2)$); $\Pi_\parallel+2\Pi_\perp$ equals the closed form $\Phi(s)$ of Section 4.6 to $10^{-10}$ relative | yes — a wrong coefficient (e.g. $1/10$, $2/15$) fails at $s/R=0.01$ |
| T4 | sphere in a parallel beam, net force by surface integration: absorbing $=\sigma q_b$, specular $=\sigma q_b$ (transverse part zero), Lambertian re-emission at albedo $\rho$ gives $\sigma q_b(1+4\rho/9)$ | each within $10^{-10}$ relative; transverse $<10^{-12}$ | yes — a flat-plate coefficient $1+2\rho/3$ fails |
| T5 | shadow of a sphere of radius $R_1$ at distance $r$ removes, from an absorbing target of area $\sigma_2$, the force $\sigma_2 q\,\Omega_{\rm proj}$, $\Omega_{\rm proj}=\int_{\rm cap}\mu\,d\Omega=\pi R_1^2/r^2$; the unweighted cap is $2\pi(1-\sqrt{1-R_1^2/r^2})$ | for $r/R_1\in\{1,1.5,2,5,10,100\}$: projected value within $10^{-12}$ of $\pi R_1^2/r^2$; unweighted value within $10^{-12}$ of the closed form | yes |
| T6 | engine implementation agrees with the chapter | `law_III::solid_angle_occluded`, `solid_angle_cap`, `cap_over_projected` each within $10^{-12}$ relative of T5's closed forms; `F_occlusion(R1,R2,r)/P_eff` $=(\pi/4)R_1^2R_2^2/r^2$ within $10^{-12}$ | yes |

T6 is an implementation-consistency check: it shows that the chapter's closed forms and the engine's code are the same expression. It says nothing about the magnitude of $P_{\rm eff}$, which Chapter 11 treats.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such.

## Build line

`cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include /Fe:<scratchpad>/ch09.exe Textbook/examples/ch09_directional_convergence.cpp`
