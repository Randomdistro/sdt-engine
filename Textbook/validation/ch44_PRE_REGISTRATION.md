# Chapter 44 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch44_thermal_recurrence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Thermal readings from radiation spectra and the octave algebra of the spectral reference. (a) Native constants: the Wien displacement constant $b=hc/(k_Bx_\lambda)$ with $x_\lambda$ the root of $x=5(1-e^{-x})$, and the Stefan radiation constant $a=\pi^2k_B^4/(15\hbar^3c^3)$, are computed from $\{h,c,k_B\}$ (unit bridges, `sdt::laws::measured`) before the engine's stored values are read; the engine's `wien_peak` constant $2.898\times10^{-3}$ and `a_rad` are then compared. (b) Reading conventions: for a Planck spectrum a peak-wavelength reading, an energy-density reading and a photon-number reading return one temperature; the wavelength-peak and frequency-peak readings differ by the exact factor $\lambda_{\rm peak}\nu_{\rm peak}/c=x_\nu/x_\lambda$ ($x_\nu$ the root of $x=3(1-e^{-x})$), so a "wavelength-derived temperature" depends on which spectral variable is maximised. (c) Spectral ancestry: a mixture of two Planck spectra with equal energy and temperature ratio 2 is read by the three conventions; they disagree, and no single Planck spectrum fits the mixture; a mixture whose components differ by 1 per cent is fitted to within a small residual. (d) Octaves: $\lambda(n)=D\,2^{-n}$ gives $T_W(n)=(b/D)2^n$ and $u\propto T^4$ rises by exactly 16 per octave under a fixed $a$; the calibration $D=760\,\mathrm{nm}\cdot2^{44}$ fixes an origin that the algebra does not predict.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\int_0^\infty x^3/(e^x-1)\,dx=\pi^4/15$; $\int_0^\infty x^2/(e^x-1)\,dx=2\zeta(3)$ with $\zeta(3)=1.2020569031595942$; the root of $x=5(1-e^{-x})$ is $4.965114231744276$ and of $x=3(1-e^{-x})$ is $2.821439372122079$ | $10^{-10}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | native constants. $b$ computed from the root and $\{h,c,k_B\}$ equals $2.897771955\times10^{-3}$ m K; $a$ computed equals $7.565733\times10^{-16}$ J m$^{-3}$ K$^{-4}$. Then, read after the computation: the engine's Wien constant $2.898\times10^{-3}$ and `a_rad` $7.5657\times10^{-16}$ agree with the computed values within $10^{-4}$ and $10^{-5}$ relative respectively (the engine values are rounded) | $10^{-6}$ for the native values; $10^{-4}$, $10^{-5}$ for the engine comparison | yes |
| T2 | one reading, one temperature for a Planck spectrum. For $T=2.7255$ K and $T=3000$ K (numerical integration of $B$ on a grid): the peak-wavelength reading $b/\lambda_{\rm peak}$, the energy reading $(u/a)^{1/4}$ and the photon-number reading all return $T$ to $10^{-8}$ relative; $\lambda_{\rm peak}\nu_{\rm peak}/c=x_\nu/x_\lambda=0.568240$ to $10^{-8}$, so $T_{\rm from\,\nu_{\rm peak}\ \rm converted\ as\ \lambda=c/\nu}$ differs from $T$ by the factor $1/0.568240$ | as stated | yes |
| T3 | spectral ancestry. A mixture $M$ of two Planck spectra at $T_1=2.7255$ K and $T_2=2T_1$ with equal energy densities: (i) the energy reading $T_u=(u/a)^{1/4}$ reproduces the integrated energy to $10^{-9}$; (ii) the three readings (peak, energy, number) of $M$ span at least 10 per cent of $T_u$; (iii) the best single-Planck fit over $(T,A)$ of the full spectrum has relative $L^2$ residual at least 0.02; (iv) for $T_2=1.01\,T_1$ the best-fit residual is below $10^{-3}$ | as stated | yes |
| T4 | octaves. For $n=0\ldots10$: $T_W(n+1)/T_W(n)=2$ and $u(n+1)/u(n)=16$ under fixed $a$, to $10^{-12}$; with $D=760\,\mathrm{nm}\cdot2^{44}$, $\lambda(44)=760$ nm and $T_W(44)=b/760\,\mathrm{nm}$; the number of octaves from the CMB peak $b/T_{\rm CMB}$ to 760 nm and to 975 nm is computed and reported; the nearest integer to $\log_2(D_{\rm Earth}/760\,\mathrm{nm})$ with $D_{\rm Earth}=2R_{\rm Earth}$ (`laws.hpp` R_Earth) is 44, and the offset from 44 is reported, not tuned | as stated | yes |
| T5 | engine consistency. `cosmology::T_at_z` and `z_at_T` are exact inverses ($10^{-12}$); `T_at_z(1100)` times nothing else equals $T_{\rm CMB}\cdot1101$; the engine's `wien_peak(T_at_z(1100))` is within $10^{-4}$ of the native $b/T$ | as stated | yes |

Reported, not criteria: the three readings of the mixture; the best-fit temperature and residual; the octave offsets; the number of octaves from the CMB peak to 975 nm.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch44_thermal_recurrence`

## Record of run 1; two failures, one instrument defect, one registration slip (2026-11-10)

Run 1 (`ch44_run1_output.txt`): V0 and V1 passed; T1, T3, T4, T5 met every criterion; **T2 failed twice** (the energy-density reading at $T=2.7255$ K and at $T=3000$ K, relative error $1.099\times10^{-6}$ in both, tolerance $10^{-8}$). Cause: the instrument's `read()` divided the integrated energy density by the engine's stored `a_rad` ($7.5657\times10^{-16}$, rounded) and not by the native $a$ computed in T1 ($7.565733250\times10^{-16}$); a relative error $4.4\times10^{-6}$ in $a$ gives $1.1\times10^{-6}$ in $(u/a)^{1/4}$. The criterion as registered ("$(u/a)^{1/4}$ returns $T$") means the native $a$ of T1; the failure is an instrument defect (a stored rounded constant was used where the registration specifies the computed one), not a finding on Planck spectra. It is a finding on the engine constant: reading a temperature from an energy density with the stored `a_rad` is biased high by $1.1\times10^{-6}$ relative ($+3.0\ \mu$K at 2.7255 K). The repair: `read()` and the T3 energy check use the native $a$; the criteria and tolerances are unchanged; the biased reading with the stored constant is added as a reported line. T3's energy-reproduction check had passed trivially for the same reason (the same constant on both sides) and is now stated against the native $a$. Registration slip: the decimal 0.568240 printed in the Object paragraph is an arithmetic error for $x_\nu/x_\lambda=2.821439372122079/4.965114231744276=0.568252661$; the criterion was coded as the ratio of the two validated roots, which is what the registration's formula states, and passed in run 1 to $10^{-16}$. Run 2 is the run of record.
