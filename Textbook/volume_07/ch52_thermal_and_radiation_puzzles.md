# Chapter 52 — Thermal and Radiation Puzzles

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $a$ the scale-free mode price (energy $a\hbar\omega$ per allowed mode); $d$ plate separation; $\lambda$ a smooth transparency cutoff length ($e^{-\lambda\omega/c}$); $x=\lambda/d$; $E(x)$ the regularised energy difference per area in units $a\hbar c/d^3$; $u_{\rm CMB}=aT^4$ with the native radiation constant of Chapter 44. Executable companion: `Textbook/examples/ch52_thermal_and_radiation_puzzles.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs: $\{\hbar,c,k_B\}$ and $T_{\rm CMB}$ (`measured`). No measured force is loaded. Disclosure: the output of the earlier FLM15-cas reset run was read before this chapter's registration; the instrument here was written afresh and registered against analytic results.

## 52.1 Mode geometry and occupation are separate

Counting the allowed modes between two ideal plates supplies a density of states. Energy requires a price per mode or an occupation rule. For a scale-free price $a\hbar\omega$ and a smooth cutoff the energy difference per area is

$$E(x)=2\Bigl[\tfrac12g(0)+\sum_{n\ge1}g\!\Bigl(\frac{n\pi}{d}\Bigr)-\frac d\pi\int_0^\infty g\,dq\Bigr],\quad g(q)=\frac{e^{-\lambda q}}{2\pi}\Bigl(\frac{q^2}{\lambda}+\frac{2q}{\lambda^2}+\frac2{\lambda^3}\Bigr), \tag{52.1}$$

in units $a\hbar c/d^3$ (the factor 2 counts two polarisations; the $n=0$ term carries one). The Euler–Maclaurin series with $g'''(0)=-1/\pi$ gives the cutoff-free limit

$$\frac{\Delta E}{A}=-\frac{a\pi^2\hbar c}{360\,d^3},\qquad P=-\frac{a\pi^2\hbar c}{120\,d^4}, \tag{52.2}$$

so counting fixes the exponent and the coefficient per unit $a$ under this premise. The amplitude $a$ has to come from the contact excitation law or remain an explicit calibration; $a=\tfrac12$ reproduces the ideal-plate coefficient $\pi^2\hbar c/(240d^4)$ and $a=1$ gives twice it. A zero-point justification of $\tfrac12$ is an imported premise that this framework does not use, so $a$ is CALIBRATED (1) until derived (R52.1).

**Executed (V1, T1).** $\int_0^\infty g\,dq=3/(\pi\lambda^4)$ at $\lambda=1$ and $\int x^3/(e^x-1)dx=\pi^4/15$ were reproduced to $3\times10^{-15}$ and $5\times10^{-15}$, and $g'''(0)=-0.3183097$ against $-1/\pi=-0.3183099$ ($5.9\times10^{-7}$; run 1 used a stencil whose own truncation error exceeded the registered tolerance, recorded in the pre-registration). With compensated summation at $x=0.08,0.06,0.04,0.03$:

| $x=\lambda/d$ | $E(x)$ | $E/E_0-1$ |
|---|---|---|
| $0.08$ | $-2.716915336\times10^{-2}$ | $-8.988\times10^{-3}$ |
| $0.06$ | $-2.727672044\times10^{-2}$ | $-5.065\times10^{-3}$ |
| $0.04$ | $-2.735378171\times10^{-2}$ | $-2.254\times10^{-3}$ |
| $0.03$ | $-2.738079821\times10^{-2}$ | $-1.268\times10^{-3}$ |

The polynomial in $x^2$ through the four points, extrapolated to $x=0$, is $-2.741556817\times10^{-2}$ against $-\pi^2/360=-2.741556778\times10^{-2}$ (relative $1.4\times10^{-8}$). The leading correction is $E/E_0-1=-1.409\,x^2$ (the ratio of the corrections at $x=0.06$ and $0.03$ is $3.9934$, registered $4$ to 2 per cent).

## 52.2 Occupation at the present temperature

Thermal occupation at the present background temperature leaves a pressure that does not depend on the plate separation. **Executed (T2).** $u_{\rm CMB}=a_{\rm native}T^4=4.174801\times10^{-14}$ J m$^{-3}$ and $u/3=1.391600\times10^{-14}$ Pa. At $d=1\ \mu$m the ratio of this pressure to the ideal-plate pressure $\pi^2\hbar c/(240d^4)$ is $1.0704\times10^{-11}$; the two are equal at $d_*=5.52863\times10^{-4}$ m, and the thermal value does not change with $d$ (a function of $T$ only). Thermal occupation at this temperature therefore cannot produce the separation dependence $d^{-4}$ at micrometre separations: the exponent of the short-distance regime comes from the mode price and the counting of Section 52.1, not from thermal occupation.

## 52.3 Finite energy and physical cutoffs

A diverging formal mode integral needs a physical domain, a cancellation or a response law. A material transparency cutoff changes the boundary problem and can alter the local scaling. **Executed (T3), fixed $\lambda$.** The local exponent $-d\ln|\Delta E|/d\ln d$ is $2.999775$ at $d/\lambda=100$ (registered $[2.99,3.01]$). In this test $\lambda$ is fixed and the energies are in units $a\hbar c/\lambda^3$. At $d/\lambda=0.1$ the energy difference is positive, $E=+0.2575$ (in the limit $d\ll\lambda$, $E\to g(0)=1/(\pi\lambda^3)$), against $-2.741\times10^{-8}$ at $d/\lambda=100$: the sign changes at $d/\lambda=0.81402$, where the local exponent has no meaning. A cutoff changes the force law over a range of separations around its own length, and its sign and exponent there are consequences of the cutoff model.

**A fitted length makes a prediction (T4).** Choosing $\lambda$ so that the energy at $d=1$ falls to $0.99$ of the cutoff-free value gives $\lambda/d=0.084402$; the deficit at $d=2$ with the same $\lambda$ is $2.508\times10^{-3}$ against $0.01/4=2.5\times10^{-3}$ (registered to 4 per cent). Choosing a cutoff solely to reproduce a desired deviation hides a fitted length; once fixed it predicts the deficit at every other separation, with the $1/d^2$ fall, and that prediction is what a second measurement tests. Deriving the transparency from the same material construction that supplies the other interaction domains is the cross-domain test (R52.2).

## 52.4 Thermal ancestry and entropy

Radiation can lose source-direction information while retaining frequency, or exchange frequency while retaining total energy ancestry. Entropy accounting depends on the retained resolution and the exported correlations. A thermal spectrum requires the appropriate redistribution and population dynamics; elastic redirection alone supplies no unique equilibrium spectrum. Chapter 44 (T3) showed that a mixture of two energy-matched Planck components has three different temperature readings (peak, energy, number: $4.494$, $3.241$, $3.120$ K) and a best single-Planck fit residual of $0.162$: the thermal shape is information that an energy-matched temperature discards. No redistribution kernel is supplied here (R52.4), and entropy was not computed (R52.5).

## 52.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\hbar,c,k_B$, $T_{\rm CMB}=2.7255$ K | `measured` | CODATA; FIRAS |
| $a_{\rm native}$ | Chapter 44 | COMPUTED from the Planck form |
| price amplitude $a$ | Section 52.1 | CALIBRATED (1) (not derived) |
| $E(x)$, $\Delta E$, $P$, $d_*$ | Sections 52.1–52.2 | COMPUTED |
| cutoff $\lambda$ and its fitted value | Section 52.3 | CALIBRATED (1) where fitted; CONSTRUCTION otherwise |

**Residuals.**

* **R52.1 — the amplitude.** $a$ is not derived from a contact-response calculation; the counting fixes only the coefficient per unit $a$.
* **R52.2 — the cutoff.** The transparency cutoff is not derived from the material construction; a derived cutoff would have to predict the sign change and the exponent near $d\sim\lambda$.
* **R52.3 — real plates.** Finite conductivity, roughness, geometry other than parallel plates and temperature corrections were not computed.
* **R52.4 — redistribution.** No kernel converts a mixed radiation history into a thermal spectrum.
* **R52.5 — entropy.** Entropy accounting for retained resolution and exported correlations was not computed.
* **R52.6 — a second observable.** The next step (derive $a$ from a contact calculation, then predict a second observable with $a$ unchanged) is not taken.

## 52.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch52_thermal_and_radiation_puzzles
```

Criteria were registered in `Textbook/validation/ch52_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch52_run1_output.txt`) failed two criteria (a finite-difference stencil whose truncation error exceeded the registered tolerance, a registration error; and a deficit compared with the wrong $1/d^3$ normalisation, an instrument defect), both recorded. Run 2 (`ch52_run2_output.txt`) is the run of record and met every criterion.

## 52.7 Exercises and answers

**Exercise 1.** Show that $\Delta E/A$ is $-a\pi^2\hbar c/(360d^3)$ from $g'''(0)=-1/\pi$.

*Answer.* Euler–Maclaurin, with $g'(0)=0$: $\sum'g(nh)-\frac1h\int g=-\frac{B_4}{4!}h^3g'''(0)+\ldots$, where $\sum'$ carries the $n=0$ term at half weight. With $B_4=-\tfrac1{30}$ and $g'''(0)=-\tfrac1\pi$ the term is $\frac{h^3}{720}\cdot(-\tfrac1\pi)=-h^3/(720\pi)$, and $h=\pi/d$ gives $-\pi^2/(720d^3)$ per unit; the factor 2 for the two polarisations gives $-\pi^2/(360d^3)$.

**Exercise 2.** Find the pressure from $\Delta E/A$.

*Answer.* $P=-\partial(\Delta E/A)/\partial d=-3a\pi^2\hbar c/(360d^4)=-a\pi^2\hbar c/(120d^4)$.

**Exercise 3.** At what separation does the ideal-plate pressure equal $u/3$?

*Answer.* $\pi^2\hbar c/(240d^4)=u/3$ gives $d_*=(\pi^2\hbar c/(80u))^{1/4}=5.53\times10^{-4}$ m.

**Exercise 4.** Why does a fitted cutoff predict a $1/d^2$ fall of the deficit?

*Answer.* $E/E_0-1\approx-1.409(\lambda/d)^2$ at fixed $\lambda$.

**Exercise 5.** What is the limit of $E$ for $d\ll\lambda$?

*Answer.* The sum is dominated by the $n=0$ term and $E\to g(0)=1/(\pi\lambda^3)$ in units $a\hbar c$.

**Exercise 6.** Why is the thermal pressure no obstacle to a $d^{-4}$ regime at $1\ \mu$m?

*Answer.* It is $1.4\times10^{-14}$ Pa, $10^{-11}$ of the ideal-plate pressure at that separation, and independent of $d$.

## 52.8 Scope

Established: the cutoff-free coefficient and exponent per unit $a$ with the corrections of the cutoff; that thermal occupation at the present temperature gives a separation-independent pressure; that a finite cutoff changes the exponent and the sign near $d\sim\lambda$; that a fitted cutoff length predicts other separations.

Not established: the amplitude (R52.1), a derived cutoff (R52.2), real plates (R52.3), a redistribution kernel (R52.4), entropy (R52.5) and a second observable (R52.6).

*Where it leads.* Chapter 53 asks what physical observable diverges in a collapse, and what a regularity theorem must establish.
