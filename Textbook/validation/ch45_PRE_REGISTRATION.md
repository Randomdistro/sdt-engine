# Chapter 45 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch45_pressure_origin_redshift.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Two conventions for the spectral shift between an emitter at depth $z_e$ and an observer at depth $z_o$ in the engine's depth closure, with the tick-rate ratio $C=1-z$ (`depth_closure::clock_rate`). (A) the engine's `z_spectral`: $z_{\rm spec}=z_e-z_o$. (B) the tick-rate-ratio form (45.1): $1+z_{\rm spec}=C_o/C_e=(1-z_o)/(1-z_e)$, i.e. $z_{\rm spec}=(z_e-z_o)/(1-z_e)$. Within one convention, a count bookkeeping (cycles emitted per remote duration, cycles counted per observer duration) fixes the sign and the ratio; across conventions the difference is $(z_e-z_o)\,z_e/(1-z_e)$, a ratio $1/(1-z_e)$ between the two shifts independent of $z_o$. Composition: $1+z$ telescopes multiplicatively across intermediate states for (B) and not for (A); $z$ telescopes additively for (A) and not for (B); the CR07 branch (octaves; $1+z=2^{\Delta n}$) is multiplicative. Inputs: $z_e$, $z_o$ are defined geometric depths $\mathrm{Om}/r$ (author ruling 2026-11-03: a defined geometric ratio, not a derived slowing); no measured shift is read; solar constants $R_\odot$, AU (IAU) and the engine's `bridge::koppa_Sun` are read after the native computation is printed.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | by hand: $z_e=0.5$, $z_o=0$: (A) gives $0.5$, (B) gives $1.0$ ($1+z=1/0.5$); $z_e=0.2$, $z_o=0.1$: (A) $0.1$, (B) $0.1/0.8=0.125$; $z_e=z_o$: both $0$; the engine's `z_spectral` and `clock_rate` return $z_e-z_o$ and $1-z$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | difference between conventions. For $z_e\in\{10^{-6},10^{-3},0.1,0.3,0.9\}$ and $z_o\in\{0,\,z_e/2\}$: $z_B/z_A=1/(1-z_e)$ exactly, independent of $z_o$; at the solar surface $z_e=$`z_spectral_Sun` the relative difference $z_B/z_A-1$ equals $z_e/(1-z_e)$ and is below $2.2\times10^{-6}$; at $z_e=0.3$ the relative difference exceeds 40 per cent | $10^{-12}$ relative; thresholds as stated | yes |
| T2 | composition. For depths $(z_A,z_B,z_C)=(0.30,0.12,0.02)$ with $z_{XY}$ the shift from emitter $X$ to observer $Y$: for (B) $(1+z_{AB})(1+z_{BC})-(1+z_{AC})$ is $0$ to $10^{-14}$ and the additive residual $z_{AB}+z_{BC}-z_{AC}$ is nonzero; for (A) $z_{AB}+z_{BC}-z_{AC}$ is $0$ to $10^{-14}$ and the multiplicative residual equals $z_{AB}z_{BC}$ to $10^{-12}$ relative | as stated | yes |
| T3 | agreement to first order. With depths scaled by $s=10^{-3},\,10^{-2},\,10^{-1}$ from $(z_e,z_o)=(0.1,0.03)$: the relative difference $z_B/z_A-1$ scales as $s^{p}$ with the log-log slope $p$ between $0.99$ and $1.02$ over the scan; $z_B-z_A=(z_e-z_o)z_e/(1-z_e)$ to $10^{-12}$ relative | as stated | yes |
| T4 | one matched emitter–route–observer experiment with the chain carried through. Emitter: the solar surface, $z_e=\varpi_\odot/R_\odot$ with $\varpi_\odot=$`bridge::koppa_Sun`; observer at 1 AU, $z_o=\varpi_\odot/\mathrm{AU}$. A count bookkeeping: emitter local frequency $f_e=5\times10^{14}$ Hz, a remote window $\Delta t=10^{-9}$ s, cycles in the window $N=f_eC_e\Delta t$, observer frequency $f_o=N/(C_o\Delta t)$: $f_e/f_o=C_o/C_e$ to $10^{-12}$, the shift is positive for $z_e>z_o$ (deeper emitter) and negative for $z_e<z_o$. Velocity-equivalent shifts $c\,z_{\rm spec}$ in both conventions are reported; the difference between conventions, $c(z_B-z_A)$, lies between $1.0\times10^{-3}$ and $2.0\times10^{-3}$ m/s (predicted before the run as $c\,(z_e-z_o)\,z_e/(1-z_e)\approx1.35\times10^{-3}$ m/s) | as stated | yes |
| T5 | strong depth. For $z_e\to1$ at fixed $z_o=0$: $z_A\le1$ always and $z_B=z_e/(1-z_e)$ increases without limit (at $z_e=0.999$, $z_B=999$ to $10^{-9}$ relative); the engine's `clock_rate` domain is $0\le z\le1$ | as stated | yes |

Reported, not criteria: the shifts in both conventions in m/s; the multiplicative and additive composition residuals.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch45_pressure_origin_redshift`

## Record of run 1; four failures from cancellation (2026-11-10)

Run 1 (`ch45_run1_output.txt`): V1, T2, T4, T5 met every criterion; **T1 failed twice and T3 failed twice**. (i) Instrument defect: the instrument formed $z_B$ as $(C_o/C_e)-1$, which subtracts 1 from a number within $10^{-6}$ of 1 and keeps only about 10 digits at $z\sim10^{-6}$ (worst grid error $2.3\times10^{-10}$ in $z_B/z_A\cdot(1-z_e)-1$; $T3$ at $s=10^{-3}$: $5\times10^{-9}$). (ii) Registration error: two registered quantities are differences of near-equal numbers (the solar "relative difference" $z_B/z_A-1\approx2\times10^{-6}$, and $z_B-z_A$ at $z_e=10^{-4}$), whose double-precision floor is about $5\times10^{-11}$ and $10^{-12}$ respectively; the registered tolerance of $10^{-12}$ cannot be met in the subtraction form for any correct implementation, and the registration did not consider it. The repair leaves the criteria unchanged and evaluates each in its equivalent cancellation-free form: $z_B$ is computed as $(z_e-z_o)/(1-z_e)$ (the second form of (45.1)); "relative difference equals $z_e/(1-z_e)$" is tested as $z_B/z_A=1/(1-z_e)$ (the same statement without the subtraction of 1); "$z_B-z_A=(z_e-z_o)z_e/(1-z_e)$" is tested as $(z_B/z_A)(1-z_e)=1$. The subtraction forms are printed as reported lines with their floating-point floors, and the loss of digits in the $(C_o/C_e)-1$ form at shallow depth is reported as a finding on the formula's numerical use. Run 2 is the run of record.
