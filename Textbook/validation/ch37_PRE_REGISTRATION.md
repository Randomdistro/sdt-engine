# Chapter 37 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch37_stellar_structure.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What the engine and the framework supply for a star, and what they do not. The luminosity $L_\odot=3.828\times10^{26}$ W (`law_II::L_Sun`) is an input anchor, not a prediction. (a) The convergence pressure $P_{\rm conv}=N\,u_{\rm CMB}$ is an energy density: times an area it is a force; inserting $c$ to obtain a power gives a number many orders of magnitude from $L_\odot$, so a transfer law is needed and is not supplied (dimensional and numerical check); (b) the reference domain radius $r_{\rm domain}=\sqrt{L/(4\pi F_{\rm CMB})}$ with $F_{\rm CMB}=cu_{\rm CMB}/4$ (`law_II::pressure_domain`) against the stored value; (c) a reduced stationary structure under the native source-length acceleration $g=c^2\varpi_{\rm enc}(r)/r^2$ with $\varpi_{\rm enc}=N_{\rm enc}\varpi_b$ (Chapters 18 and 35): a polytropic closure gives the Lane–Emden problem with structural coefficient $G_{\rm eff}=c^2\varpi_b/m_p$; the solver is validated on the known solutions; the solar-scale central density and pressure of an $n=3$ polytrope with baryon count $N_b=\varpi_\odot/\varpi_b$ and the stored radius are computed and are **not** compared with any solar-model value (no model of the solar interior is admitted as evidence); (d) the energy-chain accounting of `neutrino.hpp` (`solar::nu_rate`, `flux_1AU`), which is an accounting consequence of the anchor $L_\odot$ and the chain energy 26.7 MeV and not an independent rate prediction; the mass–energy time and the fraction of the stellar rest energy released by one chain per four protons. The source strength of the Sun is read from the ephemeris constants (`Textbook/data/horizons/gm.csv`, OBSERVED-processed).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | Lane–Emden solutions $(\xi_1,\,-\xi_1^2\theta'(\xi_1))$: $n=0$: $(\sqrt6,2)$; $n=1$: $(\pi,\pi)$; $n=1.5$: $(3.65375,2.71406)$; $n=3$: $(6.89685,2.01824)$ | $10^{-6}$ ($n=0,1$); $10^{-5}$ ($n=1.5,3$) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | $P_{\rm conv}$ has the dimension of a pressure (energy density); $P_{\rm conv}\cdot4\pi R_\odot^2$ is a force; $P_{\rm conv}\cdot4\pi R_\odot^2\cdot c$ divided by $L_\odot$ exceeds $10^{40}$ (printed) | ratio $>10^{40}$ | yes — a ratio near 1 would reject the statement that a transfer law is missing |
| T2 | `pressure_domain(L_Sun)` equals $\sqrt{L_\odot/(4\pi F_{\rm CMB})}$ computed independently to $10^{-12}$; the stored `r_domain_Sun` ($3.12\times10^{15}$ m) agrees with it within $2\times10^{-3}$; the value in AU is printed | as stated | yes |
| T3 | structure. (a) $G_{\rm eff}/(\ell_P^2c^3/\hbar)=R_{p,\rm lock}/R_p=1/C_g$ to $10^{-14}$; (b) $N_b=\varpi_\odot/\varpi_b$ from the Sun's ephemeris $GM$ and the engine's $\varpi_b$; $M=N_bm_p$ printed; (c) the $n=3$ polytrope with $M$, $R=R_\odot$ (stored): $\rho_c=M\xi_1^3/(4\pi R^3w_1)$, $K=4\pi G_{\rm eff}a^2\rho_c^{1-1/n}/(n+1)$, $P_c=K\rho_c^{1+1/n}$ printed; (d) hydrostatic consistency at $r/R=0.3,0.6,0.9$: $\mathrm dP/\mathrm dr=-\rho g$ with $g=c^2\varpi_{\rm enc}/r^2$, $\varpi_{\rm enc}=N_{\rm enc}\varpi_b$, within $10^{-5}$ relative; (e) scaling: $P_c(2R)/P_c(R)=1/16$ and $P_c(2M)/P_c(M)=4$ to $10^{-12}$ | as stated | yes |
| T4 | accounting. `solar::nu_rate` equals $2L_\odot/(26.7\,\mathrm{MeV})$ to $10^{-12}$ and `flux_1AU` equals that rate over $4\pi\mathrm{AU}^2$ to $10^{-12}$; printed: the chain rate, the mass–energy time $Mc^2/L_\odot$ (years), and the fraction $26.7\,\mathrm{MeV}/(4m_pc^2)$ | as stated; printed values are accounting, not predictions | yes |

Reported, not criteria: $\rho_c$, $P_c$, $N_b$, $M$, the AU value of the domain, the accounting numbers.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch37_stellar_structure`

## Record of run 1; correction of a registered known answer (2026-11-10)

A first build failed on a namespace path (`neutrino::solar`); no run resulted. Run 1 (`ch37_run1_output.txt`) met every criterion except the $n=0$ mass coefficient in V1: the registered known answer $-\xi_1^2\theta'(\xi_1)=2$ for $n=0$ was wrong. For $n=0$, $\theta=1-\xi^2/6$ and $\theta'=-\xi/3$, so $-\xi_1^2\theta'(\xi_1)=\xi_1^3/3=2\sqrt6=4.898979$ (I had written $\xi_1^2/3$, a different quantity). The solver's value was $4.898891$. This is an error in the registration of an instrument check, not a finding on the object, and the other seven V1 lines (the four values of $\xi_1$ and the coefficients for $n=1,1.5,3$) passed. The known answer is corrected to $2\sqrt6$ with tolerance $10^{-4}$ (the $n=0$ case starts from a non-smooth series and converges slowly in the coefficient); T1–T4 are unchanged and all passed in run 1. Run 2 is the run of record.
