# Chapter 18 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch18_proton_topology_and_boundary.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The proton lock construction of the engine (`lock_geometry`, `law_III::R_p_lock`, `law_VI::winding`, `bridge::proton_wake`, `bridge::koppa_per_baryon`): (a) the choice of lock coordination 4 from close-packed void geometry; (b) the rank-two and rank-four directional moments of the four tetrahedral channels (TD03/B37); (c) the lock length $R_{p,\rm lock}=q\hbar/(m_pc)$ with $q=4$ as a prediction printed **before** the stored $R_p$ is read, and the comparison that retains the operational difference as $C_g=R_p/R_{p,\rm lock}$ rather than setting it to 1; (d) the wake closure $\ell_P^2=\varpi_b\bar\lambda_p$, $\bar\lambda_p=R_p/(W+1)$, with the statement of which parts are inverse evaluations of one stored length; (e) the interaction-volume identity $P_{\rm eff}=m_ec^2/V_{\rm int}$. What a comparison of the lock length with the stored $R_p$ can establish is limited by two facts recorded in the chapter: the stored $R_p$ carries no uncertainty in the header, and the operational definitions differ (exclusion envelope against the root-mean-square radius of the electromagnetic response).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the void-radius routine (centre-to-vertex distance of a regular arrangement of touching unit spheres, minus 1) on the simple-cubic cell: eight spheres at the corners of a cube of edge 2, void ratio $\sqrt3-1=0.7320508075688772$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | void geometry from coordinates. Unit spheres touching at tetrahedral positions (vertices $(\pm1,\pm1,\pm1)/\sqrt2$ with an even number of minus signs: edge 2) and at octahedral positions (vertices $(\pm\sqrt2,0,0)$ and permutations: edge 2). Void ratios from coordinates equal the engine constants `tetrahedral_void_radius_ratio` and `octahedral_void_radius_ratio`; the resistance prices $4\rho_t^3$ and $6\rho_o^3$ equal the engine's; `trefoil_lock_coordination` $=4=W_{\rm proton}+1$ | $10^{-14}$ relative; integer equalities exact. The two integers have different origins (void pricing; trefoil winding number) and their equality is reported as convergence | yes — a coordinate void ratio that differs from the engine's rejects the stored constants |
| T2 | rank moments of the four channels $(\pm1,\pm1,\pm1)/\sqrt3$ with product of signs $+1$. For 20000 random directions (fixed generator): $M_2=1/3$; $M_4$ from the channel sum equals $[1+4(n_x^2n_y^2+n_x^2n_z^2+n_y^2n_z^2)]/9$; extremes $1/9$ on the axis and $7/27$ on $(1,1,1)$; the sphere average of $M_4$ is $1/5$ by exact quadrature (64 azimuth points, 24-point Gauss–Legendre in the polar cosine) | $M_2$: $10^{-14}$; $M_4$: $10^{-14}$; extremes $10^{-15}$; average $10^{-13}$ | yes — a direction dependence of $M_2$, or a sphere average different from $1/5$, rejects the 2-design statement |
| T3 | lock length and comparison. $R_{p,\rm lock}=4\hbar/(m_pc)$ computed and printed first. Then: engine constants `R_p_lock` and `R_p_predicted` equal it to $10^{-15}$. Then the stored $R_p$ is read: $C_g=R_p/R_{p,\rm lock}$ lies within 1% of 1 (a loose window chosen to make no claim of precision) and $W_{\rm eff}=R_pm_pc/\hbar-1$ lies in $(2.99,3.01)$. The look-elsewhere probability is computed: for the offset $\lvert R_pm_pc/\hbar-4\rvert$ the chance that a uniform value lands that close to the single pre-selected integer, and to any integer in $1\ldots10$ | as stated; probabilities reported, not criteria | yes — a $C_g$ outside 1% rejects the lock length at this window |
| T4 | wake closure. $\varpi_b=\ell_P^2/(R_p/4)$ and $\sqrt{\varpi_b\,R_p/4}=\ell_P$ to $10^{-14}$ (an inverse evaluation of one stored length, reported as consistency); the ratio of the engine's $\varpi_b$ to the legacy Compton-wake value $\ell_P^2m_pc/\hbar$ equals $1/C_g$ to $10^{-14}$ | as stated | yes |
| T5 | interaction volume. $V_{\rm int}=(\pi/4)R_{p,\rm lock}^2r_e$ and $P_{\rm eff}V_{\rm int}/(m_ec^2)=1$; and $\alpha\hbar c/(m_ec^2r_e)=1$ (the Coulomb identity inside $P_{\rm eff}$; shared-input with the CODATA set) | $10^{-9}$ | yes |

Reported, not criteria: $R_{p,\rm lock}$, $C_g$, $W_{\rm eff}$, $\varpi_b$, $V_{\rm int}$, $P_{\rm eff}$, the look-elsewhere probabilities.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch18_proton_topology_and_boundary`
