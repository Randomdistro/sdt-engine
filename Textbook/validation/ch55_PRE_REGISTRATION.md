# Chapter 55 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch55_framework_correspondence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The native orbital chain $k=c/v$, $\mathrm{Om}=R/k^2$, $a=c^2\mathrm{Om}/r^2$ and the movement budget $v_{\rm circ}^2+v^2=c^2$ against the equivalent standard expressions; provenance and discrimination kept as separate columns; the correspondence table with the native derivation, the equivalent expression, the input chain, the retained approximation and the two columns. (a) Orbital chain, native-first: with $\mathrm{Om}_\odot=R_\odot/k_\odot^2$ (`bridge::koppa_Sun`, $k_\odot=686.3$ stored; the surface speed behind it is a source-strength input read from ephemeris-fitted values, a named shared input) the circular period at $r=1$ AU is $T=2\pi\sqrt{r^3/(c^2\mathrm{Om}_\odot)}$, computed before any measured year is read; the circular speed is $c\sqrt{\mathrm{Om}/r}$. (b) Movement budget: $\gamma=[1-v^2/c^2]^{-1/2}$, $p=\gamma mv$, $E=\gamma mc^2$ satisfy $E^2=(pc)^2+(mc^2)^2$ identically; $\gamma(0.6c)=1.25$. (c) The correspondence table: each row carries a provenance class (A derived with no matched target input; B shared-input, named; C calibrated) and a discrimination class (none known: the same observable function; candidate: different predictions at some stated scale, unmeasured here). The two axes are independent: the table must populate (A, none), (B, none), (A, candidate) and (B, candidate). Inputs: $R_\odot$, AU (IAU), $c$; $k_\odot$ stored; the sidereal year (IAU) is read only after the native period is printed.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\gamma(0.6c)=1.25$; $v_{\rm circ}(v_{\rm trans}(x))=x$; $c\sqrt{\mathrm{Om}/r}$ equals $2\pi r/T$ for $T=2\pi\sqrt{r^3/(c^2\mathrm{Om})}$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | orbital chain. The native period at 1 AU lies in $[365.07,365.44]$ d (a window of $\pm5\times10^{-4}$ about the 365.2564 d expected from the stored $k_\odot$); the circular speed lies in $[29.7,29.9]$ km/s; then the sidereal year 365.256363 d is read and the relative difference reported; the difference is not a discriminating result: the stored $k_\odot$ shares its input chain with the measured source strength | as stated | yes |
| T2 | movement budget. $E^2-(pc)^2=(mc^2)^2$ to $10^{-14}$ relative for 20 speeds from $0.01c$ to $0.999c$; the photon limit $v_{\rm circ}=0$ gives $v=c$; $\gamma(0.6c)=1.25$ | as stated | yes |
| T3 | correspondence table. Eight rows, each with the five descriptive fields and the two classes; the rows populate (A, none), (B, none), (A, candidate), (B, candidate); the numbers quoted in the candidate rows are computed here: the relative difference of the two redshift conventions at $z_e=0.3$ ($0.4286$, to $10^{-4}$) and at the solar surface ($2.1231\times10^{-6}$, to $10^{-6}$ relative); the source-strength difference of an alpha and four free protons ($6.897\times10^{-3}$, to $10^{-3}$) | as stated | yes |

Reported, not criteria: the native period, speed, the difference from the sidereal year.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch55_framework_correspondence`

## Record of run 1; one registration error (2026-11-10)

Run 1 (`ch55_run1_output.txt`): every criterion was met except one, the T2 identity $E^2-(pc)^2=(mc^2)^2$ over 20 speeds: the worst deviation $4.93\times10^{-14}$ exceeded the registered $10^{-14}$. At $\beta=0.999$, $E^2/(mc^2)^2=\gamma^2=500$ and $(pc)^2/(mc^2)^2=499$: the identity subtracts two terms near 500 to give 1, so the double-precision error of the difference is about $500\times10^{-16}$ relative to the result, which is the observed value. The registration expressed the tolerance relative to the difference rather than to the size of the terms, and did not account for the cancellation (the same class as Chapters 15 and 23). This is a registration error, not a finding on the object. The criterion is unchanged in content; the deviation is evaluated relative to $E^2$ (the size of the terms) with the tolerance $10^{-14}$ unchanged; the value relative to the difference is reported. Run 2 is the run of record.
