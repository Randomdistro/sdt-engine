# Chapter 11 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch11_universal_interaction.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The pressure and geometry factors of the engine's universal interaction, `law_III` of `laws.hpp` (lines 457–560): $F=(\pi/4)P_{\rm eff}R_1^2R_2^2/r^2$ with $P_{\rm eff}=4\alpha\hbar c/(\pi R_{\rm lock}^2r_e^2)$, $R_{\rm lock}=4\hbar/(m_pc)$, $r_e=\alpha^2a_0$ (the interaction radius $R_{\rm int}=\sqrt{R_{\rm lock}r_e}$ is formed locally in the instrument). The test is of the engine's internal consistency and of the chapter's statements about it; the magnitude of $P_{\rm eff}$ is not derived here (EMC04), and the comparison with a measured force is deferred to the value of $k_ee^2$ of Chapter 6.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | geometry factor: $q\pi^2R_1^2R_2^2/r^2$ with $q=U/4\pi$ equals $(\pi/4)UR_1^2R_2^2/r^2$ for $(R_1,R_2,r,U)=(2,3,7,5)$ | $10^{-15}$ |
| V2 | log-slope of a pure inverse-square function between $r$ and $10r$ is $-2$ (the slope estimator itself) | $10^{-13}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | three forms of $P_{\rm eff}$ agree: the engine's $P_{\rm eff}$, $m_p^2m_e^2c^5/(4\pi\alpha\hbar^3)$ and $m_ec^2/V_{\rm int}$ (`P_eff_from_volume`), where $V_{\rm int}=(\pi/4)R_{\rm lock}^2r_e$; the engine's compile-time bound between the first and last is $10^{-8}$ | pairwise within $10^{-9}$ relative | yes — a wrong power of $c$ or $\hbar$ in any form rejects |
| T2 | Coulomb form: $F_{\rm Coulomb}(r)\,r^2=\alpha\hbar c$ for $r\in\{a_0,\,10^{-9},\,10^{-6},\,1\}$ m, and $F_{\rm Coulomb}(r)=(\pi/4)P_{\rm eff}R_{\rm int}^4/r^2$ with $R_{\rm int}$ formed locally; the engine's $\alpha\hbar c$ against $k_ee^2$ of the stored CODATA constants | $10^{-14}$ for the algebra; $10^{-9}$ against $k_ee^2$ | yes |
| T3 | inverse-square: for `F_occlusion` with $(R_1,R_2)=(R_{\rm lock},r_e)$ and with $(2,3)$ the log-slope between $r$ and $10r$ is $-2$ for six decades of $r$ | within $10^{-12}$ | yes |
| T4 | count scaling: $F_{\rm nuc\text{-}e}(Z,r)/F_{\rm nuc\text{-}e}(1,r)=Z$ for $Z=1\ldots20$ at $r=a_0$; $F_{\rm nuc\text{-}e}(1,a_0)=F_{\rm Coulomb}(a_0)$. For contrast the excluded geometry $R_{\rm nuc}=ZR_p$ gives $Z^2$ (printed) | scaling within $10^{-14}$; equality within $10^{-14}$ | yes — a $Z^2$ law would reject |
| T5 | hydrogen balance: $F_{\rm Coulomb}(a_0)=m_e(\alpha c)^2/a_0$, the centripetal requirement of the circular law $v=\alpha c$ at $a_0$ with the inertial mass $m_e$. The agreement is algebraic given $a_0=\hbar/(\alpha m_ec)$ and is labelled CONSTRUCTION | within $10^{-9}$ relative | yes |
| T6 | the measured boundary radius against the lock boundary: $F_{\rm occlusion}(R_p,r_e,a_0)/F_{\rm Coulomb}(a_0)=(R_p/R_{\rm lock})^2$, printed with its value | within $10^{-12}$ of $(R_p/R_{\rm lock})^2$ | yes |
| T7 | transfer function: `f_transfer` $=P_{\rm eff}/P_{\rm conv}$ equals $V_{\rm disp,e}/(3V_{\rm int})$ (the engine's stated identity) | within $10^{-9}$ | yes |

Reported, not criteria: $P_{\rm eff}$, $P_{\rm conv}$, $f$, $V_{\rm int}$, $R_{\rm lock}$, $R_{\rm int}$, $F_{\rm Coulomb}(a_0)$, and the pressure ladder $u_{\rm CMB}$, $P_{\rm rad}$, $P_{\rm cf}$, $P_{\rm conv}$, $P_{\rm eff}$.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch11_universal_interaction`
