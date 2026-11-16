# Equation register

Opened 2026-10-27. One row per load-bearing equation. Columns follow Section 2 of the production plan in condensed form: dimensions and the full derivation live in the chapter; the register carries identity, dependencies, domain, implementation and verification.

Registered so far: Chapters 4 and 9. Chapters 1–3 and 33 (drafted in the pasted text) are not yet registered; their equation identifiers are assigned when that text is typeset into `volume_01/`.

| id | expression | premises | upstream | domain / order | engine reference | verification | supersession |
|---|---|---|---|---|---|---|---|
| 4.2 | $f(D)=\tfrac12(1-\sqrt{1-a^2/D^2})$ | P5, P6 | — | spherical target, $D>a$ | — | `ch04` kernel table (exact vs far-field) | — |
| 4.3 | $d\Phi=\kappa\varepsilon\,d\Omega\,dD/(4\pi\ell)$ | P1–P6 | 4.1, 4.2 | far field, $D\gg a$ | — | T3 | proves R6 / T1 (numbering note, Ch 4 §4.2) |
| 4.4 | $\Phi=(\kappa\varepsilon/\ell)\langle L\rangle$ | P1–P6 | 4.3 | any bounded domain | — | T3, T4 | — |
| 4.5 | $\Phi=\kappa N\varepsilon$ | P1–P6, centred ball | 4.4 | $N=R/\ell$ | `law_I::Phi`, `laws.hpp:284` | T3, T6 | T2 (Ruleset) with $\kappa=1$ |
| 4.6 | $\vec F=(\kappa\varepsilon/\ell)\langle L\hat n\rangle$ | P1–P6 | 4.4 | any bounded domain | — | T4 | — |
| 4.8 | $\Phi_q\propto N^{3-q}$ | P1–P3 | 4.3 | kernel $D^{-q}$ | — | Ex 4.1 | — |
| 4.10 | $L(\theta)=-s\cos\theta+\sqrt{R^2-s^2\sin^2\theta}$ | P5, common ball | — | $s<R$ | — | T4 | — |
| 4.11 | $\vec F=-(\kappa\varepsilon/\ell)(s/3)\hat s$ | P1–P6, common ball | 4.6, 4.10 | $s<R$, continuum far field | — | T4 (≤ $6\times10^{-6}$ relative) | — |
| 4.12 | $\Phi(s)=(\kappa\varepsilon/\ell)R[1-s^2/3R^2]$ | as 4.11 | 4.10 | $s\ll R$ | — | Ex 4.4 | — |
| 4.13 | $\lvert\nabla P\rvert=P_{\rm conv}/(3R)$ | as 4.11 | 4.5, 4.12 | $s\ll R$ | `convergence_floor::pressure_gradient`, `laws.hpp:731` | T6 | feeds APS03 floor, `laws.hpp:687–746` |
| 4.14 | $\Phi_\delta=\kappa\varepsilon\tau(1-\tau^N)/(1-\tau)$ | P4 | 4.5 | $\tau=1-\delta$ | — | T5 | — |
| 4.15 | $\delta\ll1/N$ | P4 | 4.14 | $N\delta\ll1$ | — | `ch04` derived figures | — |
| 9.1 | $\phi(\hat n)=\kappa\varepsilon L(\hat n)/(4\pi\ell)$ | P1–P6 | 4.3 | any bounded domain | — | Ch 9 T3 | — |
| 9.2 | $\phi=\Phi/4\pi$ (centred ball) | P1–P6 | 9.1 | centre of a ball | — | Ch 9 V1 | Law III, Theorem 3 |
| 9.4 | $M_1=0,\ \Pi_{ij}=(\Phi/3)\delta_{ij}$ | P1–P6 | 9.1 | centre of a ball | `law_IV` comment, `laws.hpp:607` | Ch 9 V1, V2 | Ruleset T7 is the specular value; Complete Laws Cor. 3.2 writes this as $P_{\rm conv}$ (Ch 9 §9.3) |
| 9.5 | $t_{\rm abs}=U/6$ | P1–P8, absorbing plane | 9.1 | isotropic arrival | — | Ch 9 T1 | — |
| 9.6 | $t_{\rm spec}=U/3=\operatorname{tr}\Pi/3$ | P1–P8, specular plane | 9.5 | isotropic arrival | $P_{\rm cf}=P_{\rm conv}/3$ | Ch 9 T2 | — |
| 9.7 | $\Pi_\parallel=\tfrac{\kappa\varepsilon}{\ell}[R/3-s^2/15R]$, $\Pi_\perp=\tfrac{\kappa\varepsilon}{\ell}[R/3-2s^2/15R]$ | P1–P6, common ball | 4.10 | $s\ll R$ | — | Ch 9 T3 | — |
| 9.8 | $(\Pi_\parallel-\Pi_\perp)/\Phi=s^2/15R^2$ | as 9.7 | 9.7, 4.12 | $s\ll R$ | — | Ch 9 T3 (0.3 % at $s/R=0.1$) | — |
| 9.9 | $F=\sigma_2q\int_{\rm cap}\mu\,d\Omega=\sigma_2q\pi R_1^2/r^2$ | P1–P8, absorbing or specular target | 9.1 | $r\ge R_1$, exact | `law_III::solid_angle_occluded`, `laws.hpp:567` | Ch 9 T5, T6 | — |
| 9.10 | $F=(\pi/4)\,U\,R_1^2R_2^2/r^2$ | as 9.9, $q=U/4\pi$ | 9.9 | $r\ge R_1$ | `law_III::F_occlusion`, `laws.hpp:535` ($P_{\rm eff}$ for $U$) | Ch 9 T6 | Law III, Theorem 4 |

Open items against this register: residuals R4.1–R4.4 in Chapter 4 §4.9; R9.1–R9.5 in Chapter 9 §9.9.
