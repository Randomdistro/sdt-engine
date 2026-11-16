# Chapter 44 — Thermal Recurrence

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $b$ the Wien constant, $a$ the radiation constant ($u=aT^4$), $x_\lambda$ and $x_\nu$ the roots of $x=5(1-e^{-x})$ and $x=3(1-e^{-x})$, $T_W=b/\lambda_{\rm peak}$ a wavelength-peak reading, $T_u=(u/a)^{1/4}$ an energy reading, $T_n$ a photon-number reading, $n$ an octave index. Executable companion: `Textbook/examples/ch44_thermal_recurrence.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs are $\{h,\hbar,c,k_B\}$ (unit bridges in `sdt::laws::measured`) and $T_{\rm CMB}$ (FIRAS); the Planck spectral form is taken as the calibrated reference relation (R44.1).

## 44.1 Thermal readings from mode populations

A temperature is a reading: an instrument couples to selected modes, reaches a response fixed by transfer and relaxation, and reports a number. A wavelength-derived temperature is a spectral reading; a material equilibrium temperature needs matched exchange conditions between the material and the radiation. Which reading is meant has to be stated.

For the reference spectrum $u_\nu=(8\pi h/c^3)\,\nu^3/(e^{h\nu/k_BT}-1)$ three readings can be formed from one spectrum:

$$T_W=\frac{b}{\lambda_{\rm peak}},\qquad T_u=\Bigl(\frac{u}{a}\Bigr)^{1/4},\qquad T_n=\frac{\hbar c}{k_B}\Bigl(\frac{\pi^2n}{2\zeta(3)}\Bigr)^{1/3}, \tag{44.1}$$

with $u=\int u_\nu\,d\nu$ and $n=\int u_\nu/(h\nu)\,d\nu$. The constants follow from the form: $b=hc/(k_Bx_\lambda)$ and $a=\pi^2k_B^4/(15\hbar^3c^3)$. If the physical medium state changes $a$, the log derivatives obey $a_u=a_a+4a_T$ (from $\ln u=\ln a+4\ln T$); holding $a$ fixed is a reference branch, not a theorem about every pressure state.

**Executed (V1, T1).** The integrals $\int x^3/(e^x-1)\,dx=\pi^4/15$ and $\int x^2/(e^x-1)\,dx=2\zeta(3)$ and the roots $x_\lambda=4.965114231744$, $x_\nu=2.821439372122$ were reproduced to $10^{-15}$ before use. Computed from $\{h,c,k_B\}$ before any stored value was read: $b=2.897771955\times10^{-3}$ m K and $a=7.565733250\times10^{-16}$ J m$^{-3}$ K$^{-4}$. Read afterwards, the engine's wavelength-peak constant ($2.898\times10^{-3}$, in `cosmology::wien_peak`) is high by $7.87\times10^{-5}$ relative and `a_rad` ($7.5657\times10^{-16}$) is low by $4.40\times10^{-6}$: both are rounded values. At $T(z{=}1100)=3000.7755$ K the engine's peak wavelength is $965.750$ nm against $965.674$ nm from the native constant.

**One reading, one temperature (T2).** For a single Planck spectrum at $2.7255$ K and at $3000$ K the three readings (44.1) return $T$ to $10^{-8}$ or better (energy reading $7\times10^{-14}$ and $2\times10^{-15}$ relative). The reading depends on the spectral variable that is maximised: $\lambda_{\rm peak}\nu_{\rm peak}/c=x_\nu/x_\lambda=0.568252661$, so a temperature obtained by taking the peak in frequency, converting it with $\lambda=c/\nu_{\rm peak}$ and applying $b$ returns $0.568253\,T$. The wavelength-peak reading is a convention of the spectral variable, not a second measurement.

A note on the stored constant. Run 1 of the instrument used the stored `a_rad` for the energy reading and failed its registered criterion by $1.1\times10^{-6}$ (recorded in the pre-registration); the cause is that reading $(u/a)^{1/4}$ with the rounded constant is biased high by $1.099\times10^{-6}$ relative, $+2.995\ \mu$K at $2.7255$ K and $+3.296$ mK at $3000$ K. A temperature read from an energy density inherits the rounding of $a$ at a quarter of its relative size.

## 44.2 Octaves

For $\lambda(n)=D\,2^{-n}$, $T_W(n)=(b/D)\,2^n$. With $a$ fixed, $u$ and the radiation pressure $u/3$ rise by exactly 16 per wavelength-halving octave. The calibrated reference $D=760\,\mathrm{nm}\cdot2^{44}=1.3370\times10^{7}$ m places the visible reference at octave 44.

**Executed (T4).** For $n=0\ldots10$ the ratios $T_W(n+1)/T_W(n)=2$ and $u(n+1)/u(n)=16$ hold to the arithmetic floor (deviation $0$); $\lambda(44)=760$ nm and $T_W(44)=b/760\,\mathrm{nm}=3812.86$ K. The CMB Wien peak is $b/T_{\rm CMB}=1.063207$ mm, which is $10.4501$ octaves above 760 nm and $10.0907$ octaves above 975 nm. Taking $D_{\rm Earth}=2R_{\rm Earth}=1.2742\times10^{7}$ m ($R_{\rm Earth}=6.371\times10^6$ m, stored in `bridge`), $\log_2(D_{\rm Earth}/760\,\mathrm{nm})=43.9306$: the nearest integer is 44 (registered and met), and the offset is $-0.0694$ octave, a factor $0.9530$ in length ($4.7$ per cent). The calibration fixes an octave origin by choosing the integer; the octave algebra does not predict that origin, and the fractional offset belongs to the calibration, not to the algebra.

## 44.3 Spectral ancestry

A mixture of radiation histories need not have one blackbody shape even when a fitted effective temperature reproduces the integrated energy. Directional scattering, true absorption, emission and number-changing processes retain spectral information differently, so an energy-matched temperature is not a shape.

**Executed (T3).** Take two Planck components at $T_1=2.7255$ K and $2T_1$ with equal energy densities ($4.174801\times10^{-14}$ J m$^{-3}$ each). The energy reading reproduces the integrated energy to $2\times10^{-16}$ by construction, and the three readings of (44.1) are $T_W=4.4938$ K, $T_u=3.2412$ K and $T_n=3.1199$ K: a spread of $1.374$ K, $42$ per cent of $T_u$ (registered: at least 10 per cent). The best single-Planck fit over temperature and amplitude to the full spectrum has relative $L^2$ residual $0.1623$ at $T=3.8544$ K (registered: at least 0.02), a fit temperature which equals none of the three readings. For components 1 per cent apart ($T_2=1.01T_1$) the best-fit residual is $3.5\times10^{-5}$ (registered: below $10^{-3}$), so the mixture measure is continuous: near-equal components are nearly Planck, and the departure grows with the temperature ratio.

A gamma-origin energy ancestry for the present background would need a thermalization operator that predicts the observed shape from the stated redistribution, not only a correspondence between two endpoint wavelengths. The determining test is to evolve an explicitly mixed spectrum through the proposed kernel and compare the integrated energy and the full spectral residuals with unchanged coefficients. No such kernel is supplied here (R44.2).

## 44.4 Engine functions

**Executed (T5).** `T_at_z` and `z_at_T` are exact inverses, `T_at_z(1100)` equals $T_{\rm CMB}\cdot1101=3000.7755$ K, and `wien_peak` of that temperature agrees with the native $b/T$ to $7.87\times10^{-5}$ (the rounding of the constant). The relation $T(z)=T_{\rm CMB}(1+z)$ is an emission-epoch map, not a transit history of any photon (Chapter 45).

## 44.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $h,\hbar,c,k_B$ | `measured` | unit bridges (exact SI) |
| $T_{\rm CMB}=2.7255$ K | `measured` | OBSERVED (FIRAS) |
| $b$, $a$ | Section 44.1 | COMPUTED from the Planck form (reference relation) |
| $2.898\times10^{-3}$, `a_rad` | engine | stored rounded values; differ from COMPUTED by $7.9\times10^{-5}$, $4.4\times10^{-6}$ |
| octave origin $D=760\,\mathrm{nm}\cdot2^{44}$ | Section 44.2 | CALIBRATED (1): the integer 44 |
| $R_{\rm Earth}$ | `bridge` | OBSERVED (stored) |
| mixture components and weights | Section 44.3 | CONSTRUCTION (no measured input) |

**Residuals.**

* **R44.1 — the reference form.** The Planck spectral form is the calibrated reference relation here. $T(S)$, the mode set, the occupation statistics and the thermometer response have not been derived from the contact mechanism.
* **R44.2 — thermalization.** No redistribution kernel is supplied; the ancestry hypothesis is untested on shape.
* **R44.3 — the octave origin.** The integer 44 and the $4.7$ per cent offset of the Earth-scale diameter are calibration; no derivation of the origin exists here.
* **R44.4 — the radiation constant branch.** $a$ held fixed is a reference branch; its dependence on the medium state is not computed.
* **R44.5 — thermometer transfer.** Coupling, relaxation and the material-equilibrium temperature were not examined.
* **R44.6 — stored constants (proposal to the author, canon untouched).** `cosmology::wien_peak` carries $2.898\times10^{-3}$ and `a_rad` is rounded to five digits; the computed values above are available if the author chooses to replace them.

## 44.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch44_thermal_recurrence
```

Criteria were registered in `Textbook/validation/ch44_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch44_run1_output.txt`) failed two T2 criteria through an instrument defect (the stored rounded `a_rad` was used where the registration specifies the computed $a$) and exposed a registration slip (a decimal for $x_\nu/x_\lambda$ typed as 0.568240; the criterion itself was the ratio of the validated roots and passed). Both are recorded; the criteria were not retuned. Run 2 (`ch44_run2_output.txt`) is the run of record and met every criterion.

## 44.7 Exercises and answers

**Exercise 1.** Show that $T_W=T$ for a Planck spectrum.

*Answer.* The peak of $u_\lambda\propto\lambda^{-5}/(e^{hc/\lambda k_BT}-1)$ is at $hc/(\lambda k_BT)=x_\lambda$, so $\lambda_{\rm peak}=hc/(k_BTx_\lambda)=b/T$.

**Exercise 2.** Why does the frequency peak give a different "Wien constant"?

*Answer.* The peak of $u_\nu$ is at $h\nu/k_BT=x_\nu$; converting with $\lambda=c/\nu$ gives $b'=hc/(k_Bx_\nu)=b\,x_\lambda/x_\nu=1.7597\,b$. The two spectral densities have different maxima because $u_\lambda\,d\lambda=u_\nu\,d\nu$ carries the Jacobian $\nu^2/c$.

**Exercise 3.** How many octaves lie between 975 nm and 1.0632 mm?

*Answer.* $\log_2(1.063207\times10^{-3}/9.75\times10^{-7})=10.0907$.

**Exercise 4.** Why does an energy reading inherit a quarter of the relative error of $a$?

*Answer.* $T_u=(u/a)^{1/4}$, so $\delta T_u/T_u=-\tfrac14\,\delta a/a$; with $\delta a/a=-4.4\times10^{-6}$ the bias is $+1.1\times10^{-6}$.

**Exercise 5.** Why can an energy-matched temperature not stand for a mixture?

*Answer.* It reproduces one moment (the energy). The spectrum has a shape, and the best single-Planck fit to the executed mixture leaves a residual of $0.162$ at a temperature unlike any of the three readings.

**Exercise 6.** What does the octave algebra fix, and what does it leave open?

*Answer.* It fixes ratios (a factor 2 in $T_W$ and 16 in $u$ per octave); the origin (which octave carries 760 nm) is a calibration.

## 44.8 Scope

Established: the three readings (44.1) agree on a Planck spectrum and disagree on a mixture; the spectral-variable convention of a peak reading; the computed constants $b$ and $a$ and the rounding of the stored values; the octave ratios and the calibrated integer 44 with its fractional offset against the Earth-scale diameter.

Not established: $T(S)$ and the mode statistics from the mechanism (R44.1), a thermalization kernel (R44.2), the octave origin (R44.3), the dependence of $a$ on the medium state (R44.4) and the thermometer response (R44.5).

*Where it leads.* Chapter 45 separates the emitter, route and observer contributions to a measured shift.
