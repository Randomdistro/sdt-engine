# Chapter 37 — Stellar Structure

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\varpi_b$ is the baryon koppa length (Chapter 18), $\varpi_\odot$ the Sun's source length, read from the ephemeris constant published as $GM_\odot=c^2\varpi_\odot$ (Chapter 36), $N_b$ a baryon count, $G_{\rm eff}=c^2\varpi_b/m_p$ the structural coefficient of Section 37.3. Executable companion: `Textbook/examples/ch37_stellar_structure.cpp`; pre-registration and captured output in `Textbook/validation/`. The luminosity $L_\odot=3.828\times10^{26}$ W is an input anchor throughout. No model of the solar interior is used as evidence, and no value in this chapter is compared with one.

## 37.1 Convergence recycling

Under the release-cascade architecture a star processes omnidirectional convergence, rearranges and excites internal structure, and releases outgoing photospheric transport into secondary relay shells. Confinement, core processing and release belong to one contact-network ledger, so a stellar boundary is not the purely absorbing sink of the finite-sphere theorem (Chapter 10).

This is the framework's answer to the classical heating objection against shadow models. That objection computes the energy deposited by corpuscles striking a body and finds the body would be vaporised. Here nothing strikes (Chapter 9, Section 9.2.1), and what the medium does to matter at sufficient depth, exciting it, transmuting it and holding it as plasma, is the claim and not a defect: the stars are the outcome the objection called absurd. The requirement that remains is quantitative. The Sun releases $L_\odot/N_b=3.22\times10^{-31}$ W per baryon (COMPUTED from the anchor $L_\odot$ and the count of Section 37.3), and one processing law has to give that figure for a star and a far smaller one for a planet, so it cannot be proportional to the baryon count or to the shadow area alone; it has to rise steeply with depth or loading (residual R37.1). No planetary heat flow is loaded here.

The convergence pressure $P_{\rm conv}=N\,u_{\rm CMB}$ sets an energy-density scale. **Executed (T1).** $P_{\rm conv}=2.4608\times10^{48}$ Pa; multiplied by the area $4\pi R_\odot^2$ it is a force, $1.4967\times10^{67}$ N, not a power. Inserting $c$ to obtain a "power", $4.487\times10^{75}$ W, gives $1.2\times10^{49}$ times $L_\odot$. The enormous value of $P_{\rm conv}$ cannot be turned into supplied power by multiplying by $c$. An absolute luminosity needs a transfer rate, a directional engagement and the partition between outgoing transport and stored deformation; that transfer law is not derived (residual R37.1).

## 37.2 Structure and power equations

A reduced stationary stellar model needs radial traction balance, composition response, internal energy transport and processing rates. With $L(r)$ the net outward power, a shell ledger is

$$\frac{dL}{dr}=4\pi r^2\big(s_{\rm processing}-s_{\rm storage}\big), \tag{37.1}$$

with both source terms in power per volume. Pressure support and energy release are coupled through the same state variables. Core transmutation needs module rearrangement, accessible barriers and rates (Chapter 19): a reaction count multiplied by the event energy gives a power only after the event rate is established. The measured $L_\odot$ in `law_II` therefore remains an input anchor of the current domain calculations and not an ab-initio luminosity.

## 37.3 Traction balance under the source-length acceleration

In the native form the acceleration at radius $r$ is $g=c^2\varpi_{\rm enc}(r)/r^2$ with $\varpi_{\rm enc}=N_{\rm enc}(r)\varpi_b$, each baryon contributing the same koppa length (Chapter 32, Section 32.5, and `materials.hpp`). The hydrostatic balance is $dP/dr=-\rho g$, which is the Poisson form of the polytropic problem with the structural coefficient

$$G_{\rm eff}=\frac{c^2\varpi_b}{m_p}. \tag{37.2}$$

**A caution on independence.** The stored baryon koppa $\varpi_b=\ell_P^2/(R_p/4)$ (Chapter 18) contains the stored Planck length, and the stored $\ell_P$ carries $G$: contaminating input: $G$, measured by laboratory gravitational torsion-balance determinations, enters at `laws.hpp:99` (the stored $\ell_P$). **Executed (T3a).** $G_{\rm eff}/(\ell_P^2c^3/\hbar)=R_{p,\rm lock}/R_p=1/C_g=0.9998047$ to $10^{-14}$ (Chapter 18): the structural coefficient equals the Planck-length combination, that is $G$ as it enters the stored $\ell_P$, times the comparison factor $1/C_g$. The structure equation is G-free in form and inherits $G$ numerically through $\varpi_b$ (the classification CALIBRATED(1) of Chapter 6, R6.1).

**The baryon count of the Sun.** With $GM_\odot=132712440041.94$ km$^3$/s$^2$ from the ephemeris (OBSERVED-processed), $\varpi_\odot=1476.625039$ m and $N_b=\varpi_\odot/\varpi_b=1.189030\times10^{57}$ baryons, $M=N_bm_p=1.988798\times10^{30}$ kg (printed, not compared). This count uses $\varpi_b$ and therefore carries the same input as (37.2).

**A polytropic closure as a stand-in.** The equation of state, composition, transport and reaction rates are not supplied by the engine. A polytropic closure $P=K\rho^{1+1/n}$ gives the Lane–Emden problem $\theta''+(2/\xi)\theta'+\theta^n=0$, with $\rho=\rho_c\theta^n$, radius $R=\xi_1a$, $a^2=(n+1)K\rho_c^{1/n-1}/(4\pi G_{\rm eff})$ and mass $M=4\pi a^3\rho_c w_1$, $w_1=-\xi_1^2\theta'(\xi_1)$. The solver was validated on the known solutions (V1): $(\xi_1,w_1)=(\sqrt6,2\sqrt6)$, $(\pi,\pi)$, $(3.653754,2.714055)$, $(6.896849,2.018236)$ for $n=0,1,1.5,3$ (agreement $8\times10^{-11}$ to $2\times10^{-6}$; the $n=0$ coefficient to $1.8\times10^{-5}$; the known answer registered for the $n=0$ coefficient was wrong in the first run and is recorded as corrected).

**Executed (T3).** For $n=3$ with $M=N_bm_p$ and the stored $R_\odot$: mean density $1.4101\times10^3$ kg/m$^3$, central density $7.640\times10^4$ kg/m$^3$ and central pressure $1.2451\times10^{16}$ Pa (printed; not compared with any solar model). The hydrostatic balance with the source-length acceleration, $dP/dr=-\rho\,c^2\varpi_{\rm enc}/r^2$, holds on the scaled solution at $r/R=0.3,0.6,0.9$ to $2\times10^{-16}$ (an identity of the construction, since the polytrope solves that equation; it checks the units and the scaling of the instrument), and the scalings $P_c\propto M^2/R^4$ hold exactly: $P_c(2R)/P_c(R)=1/16$ and $P_c(2M)/P_c(M)=4$ to round-off. The values depend on the closure ($n$); a different equation of state with the same $M$ and $R$ gives other central values. What the native law contributes is the acceleration and the coefficient (37.2); what fixes the pressure–density relation is not supplied (residual R37.2).

## 37.4 Domain and stability

The reference domain $r_{\rm domain}=\sqrt{L/(4\pi F_{\rm CMB})}$ equates the outward flux of the star to a reference ambient flux $F_{\rm CMB}=cu_{\rm CMB}/4$. **Executed (T2).** `pressure_domain(L_Sun)` equals the independent evaluation to $10^{-12}$: $F_{\rm CMB}=3.1289\times10^{-6}$ W/m$^2$, $r_{\rm domain}=3.12021\times10^{15}$ m $=20857.3$ AU; the stored `r_domain_Sun` $=3.12\times10^{15}$ m agrees to $6.7\times10^{-5}$ (it is a three-digit pre-computed value). The domain is conditional on $L$, an anchor.

A stability calculation perturbs the core state and the transport together; whether heating increases release or stored deformation determines the sign of the feedback. That calculation is not performed (residual R37.5). The determining closure is one contact-processing operator that yields the luminosity, the composition evolution and the perturbation response, without an empirical solar wattage.

## 37.5 Energy-chain accounting

The engine counts solar neutrinos from the luminosity and the chain energy: `solar::nu_rate` $=L_\odot\times2/(26.7\ \mathrm{MeV})$ and `flux_1AU` $=\mathrm{nu\_rate}/(4\pi\mathrm{AU}^2)$. **Executed (T4).** Both equal their definitions to round-off; the chain rate is $L_\odot/E_{\rm chain}=8.9485\times10^{37}$ s$^{-1}$, the rate of the emitted channel $1.7897\times10^{38}$ s$^{-1}$ and the flux at 1 AU $6.3638\times10^{14}$ m$^{-2}$s$^{-1}$. The mass–energy time $Mc^2/L_\odot=1.4796\times10^{13}$ yr, and a chain releases a fraction $26.7\,\mathrm{MeV}/(4m_pc^2)=0.00711$ of the rest energy of the four protons. These are accounting consequences of the anchor $L_\odot$ and the chain energy: the rate is *inferred from* $L_\odot$, not predicted from the core. The engine's header comment that the flux matches measured values was not tested; the total emission rate is a statement about all neutrinos, whereas detectors see a part of the spectrum, and no measured flux is loaded.

## 37.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $L_\odot$ | `law_II::L_Sun` | MEASURED-INPUT (anchor; IAU nominal) |
| $P_{\rm conv}$, $F_{\rm CMB}$, $r_{\rm domain}$ | `law_I`, `law_II` | COMPUTED from the stored inputs ($P_{\rm conv}$ is conditioned on $R_{\rm CMB}$) |
| $GM_\odot$ | ephemeris constant | OBSERVED (processed) |
| $\varpi_b$, $G_{\rm eff}$, $N_b$ | `bridge`, Section 37.3 | COMPUTED from the stored lengths; carries $G$ through $\ell_P$ (CALIBRATED(1)) |
| polytropic $\rho_c$, $P_c$ | Section 37.3 | COMPUTED under an assumed closure (CONSTRUCTION) |
| 26.7 MeV, 2 per chain | `neutrino.hpp` | the engine's chain bookkeeping |
| chain rate, flux, times | Section 37.5 | COMPUTED (accounting on the anchor $L_\odot$) |

**Residuals.**

* **R37.1 — the transfer law.** No law turns $P_{\rm conv}$ into a luminosity.
* **R37.2 — the closure.** The equation of state, composition, transport and reaction rates are not supplied; the polytrope is a stand-in and its central values depend on $n$.
* **R37.3 — the anchor.** $L_\odot$ and the Sun's source length are inputs; no luminosity is predicted.
* **R37.4 — G in the source ledger.** $\varpi_b$, $G_{\rm eff}$ and $N_b$ inherit $G$ through the stored $\ell_P$.
* **R37.5 — stability.** The feedback sign of a perturbation of the core and its transport is not computed.
* **R37.6 — neutrino flux.** The accounting rate is not compared with a measured flux.

## 37.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch37_stellar_structure
```

Criteria were registered in `Textbook/validation/ch37_PRE_REGISTRATION.md` before the instrument existed. A first build failed on a namespace path. Run 1 met every criterion except the $n=0$ mass coefficient of V1, whose registered known answer was wrong ($\xi_1^3/3=2\sqrt6$, not 2; a registration error). Run 2 (`ch37_run2_output.txt`) is the run of record and met every criterion.

## 37.8 Exercises and answers

**Exercise 1.** Show that $P_{\rm conv}\cdot\mathrm{area}$ has the dimension of force.

*Answer.* $[\mathrm{Pa}][\mathrm m^2]=[\mathrm N\,\mathrm m^{-2}][\mathrm m^2]=[\mathrm N]$. A power needs a further factor of a speed with the dimension of a transfer rate that is derived, not inserted.

**Exercise 2.** Evaluate $r_{\rm domain}$ in AU from $L_\odot=3.828\times10^{26}$ W and $F_{\rm CMB}=3.1289\times10^{-6}$ W/m$^2$.

*Answer.* $\sqrt{3.828\times10^{26}/(4\pi\times3.1289\times10^{-6})}=3.1202\times10^{15}$ m, $20857$ AU.

**Exercise 3.** Derive $dP/dr=-\rho g$ with $g=c^2\varpi_{\rm enc}/r^2$ as the Poisson form.

*Answer.* $\varpi_{\rm enc}=(M(r)/m_p)\varpi_b$, so $g=(c^2\varpi_b/m_p)M(r)/r^2=G_{\rm eff}M(r)/r^2$.

**Exercise 4.** Why does $P_c\propto M^2/R^4$ follow?

*Answer.* For fixed $n$, $\rho_c\propto M/R^3$ and $K\propto G_{\rm eff}a^2\rho_c^{1-1/n}$ with $a\propto R$, so $P_c=K\rho_c^{1+1/n}\propto G_{\rm eff}R^2\rho_c^2\propto M^2/R^4$.

**Exercise 5.** Compute the chain rate for $L_\odot=3.828\times10^{26}$ W and 26.7 MeV.

*Answer.* $26.7\ \mathrm{MeV}=4.278\times10^{-12}$ J, rate $=8.949\times10^{37}$ s$^{-1}$.

**Exercise 6.** Why does the accounting flux not test the model?

*Answer.* It is $L_\odot$ times a constant divided by an area; the luminosity is the anchor.

## 37.9 Scope

Established: that $P_{\rm conv}$ is an energy density and that inserting $c$ does not give $L_\odot$ (the ratio is $10^{49}$); the reference domain radius for the anchor $L_\odot$; the native acceleration and structural coefficient (37.2) with the polytropic stand-in, its scalings and the units of the instrument; the dependence of $\varpi_b$, $G_{\rm eff}$ and $N_b$ on $G$ through $\ell_P$; and the accounting identities of the neutrino bookkeeping.

Not established: a transfer law (R37.1), the equation of state, composition, transport and reaction rates (R37.2), a luminosity (R37.3), stability (R37.5) and a measured neutrino flux comparison (R37.6).

*Where it leads.* Chapter 38 turns to extended sources: bulge, disc, bar and arms, and what a flat rotation curve constrains.
