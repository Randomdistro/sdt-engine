# Chapter 54 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch54_cosmological_accounting.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. A cosmological model has to predict spectral shift, distance, angular scale, timing and background intensity jointly, with one declared frame convention for every factor. This instrument is an accounting of factors of $(1+z)$ in generic conventions (TOY): no measured data, no engine distance law (the engine has none: `cosmology.hpp` records NO-DERIVED-$d(z)$) and no fitted parameter. For an unresolved source the observed bolometric flux is $F=L/(4\pi d^2)\times f_E\times f_R$, with $d$ the declared geometric distance, $f_E$ the energy-per-event factor and $f_R$ the event-rate factor. (a) Endpoint-ratio branch (CR07; Chapters 45 and 47): the energy per event and the arrival rate per observer duration both scale as $(1+z)^{-1}$, so $F=L/[4\pi d^2(1+z)^2]$ with $d$ the static geometric distance; define $d_L=d(1+z)$. (b) A branch in which only the energy per event shifts has $f_R=1$ and $F=L/[4\pi d^2(1+z)]$. (c) Hybrid: taking a distance already containing the factor $(1+z)$ (an expansion-history $d_L=d_M(1+z)$) into the flux law of branch (a) applies the factor twice: $F\propto(1+z)^{-4}$ against the geometric distance, a magnitude error $5\log_{10}(1+z)$. (d) A single observable can hide the hybrid by redefining the distance, $d'=d/(1+z)$; the angular size $\theta=s/d'$ then differs from the geometric prediction by the factor $(1+z)$: a joint test is needed. (e) Reciprocity: with $d_A$ the angular-diameter distance, $\eta=d_L/[(1+z)^2d_A]$; with sizes unscaled by the endpoint ruler ratio ($d_A=d$) the branch-(a) value is $\eta=1/(1+z)$; with the physical size transforming as the endpoint ruler ratio $(1+z)$ ($d_A=d/(1+z)$) it is $\eta=1$; the convention has to be declared, and the two differ by $33$ per cent at $z=0.5$ and $50$ per cent at $z=1$. Nothing here decides between conventions.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $5\log_{10}2=1.505150$; $2.5\log_{10}2=0.752575$; magnitude difference of a flux ratio $r$ is $2.5\log_{10}r$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | flux factors. For $z\in\{0.1,0.5,1,2\}$: the hybrid (a)+(c) differs from the consistent branch (a) by $5\log_{10}(1+z)$ mag; branch (b) differs from branch (a) by $2.5\log_{10}(1+z)$ mag; the values at $z=1$ are $1.50515$ and $0.752575$ | $10^{-12}$ | yes |
| T2 | reciprocity. $\eta_{A}=1/(1+z)$ and $\eta_B=1$ for the grid; the relative difference of the conventions is $z/(1+z)$: $0.3333$ at $z=0.5$ and $0.5$ at $z=1$ | $10^{-12}$ | yes |
| T3 | hiding a hybrid. After the redefinition $d'=d/(1+z)$ the flux of the hybrid equals the consistent branch-(a) flux to $10^{-12}$ at every $z$ in the grid, and the predicted angular size $s/d'$ exceeds the geometric $s/d$ by the factor $1+z$ ($0.693$ in $\ln$ at $z=1$) | $10^{-12}$ | yes |

Reported, not criteria: the magnitude offsets and ratios.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch54_cosmological_accounting`

## Record of run 1; two instrument defects (2026-11-10)

Run 1 (`ch54_run1_output.txt`): V1, the T1 hybrid criteria (four) and all T2 criteria (twelve) and the angular-size criteria of T3 (four) were met. Eight criteria failed, from two defects in the instrument (not in the registration or the object). (1) T1, branch (b): the magnitude difference was computed with the arguments in the wrong order, so the printed values were $-0.1035$, $-0.4402$, $-0.7526$, $-1.1928$ mag: the correct magnitudes with the opposite sign (branch (b) is brighter than (a), so its magnitude is lower; the registered statement is the magnitude of the difference $2.5\log_{10}(1+z)$ with the sign convention "brighter by"). (2) T3, the hybrid flux after the redefinition: the instrument applied the factor $(1+z)$ twice when forming the hybrid distance (`d' (1+z)(1+z)` where the registration specifies $d_L=d'(1+z)$), giving the flux of a doubly corrected hybrid; the registered statement is that with $d'=d/(1+z)$ the hybrid flux equals the consistent flux, which holds for the correct expression ($d'(1+z)=d$). The criteria are unchanged. Run 2 is the run of record for T1–T3.

## Addendum T4, registered 2026-11-10 after run 2 and before the T4 code existed

Object. The distance and duration scales stored in the engine, as an accounting of provenance: `law_I::R_CMB` $=9.527\times10^{26}$ m (a stored observed boundary), the light-travel time $R_{\rm CMB}/c$, the comment in `cosmology.hpp` that $R_{\rm CMB}=\ln(1+z)/\sigma_0$ with $\sigma_0=H_0/c$ (the header guard marks any $\sigma_0$-integrated distance as not an SDT derivation), and the stored `age::age_SDT_Gyr` $=48$ Gyr. The registration is of what the stored numbers imply for each other; no value is fitted.

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T4 | (i) $R_{\rm CMB}/c$ lies in $[100.5,100.9]$ Gyr; (ii) $\ln(1+z_{\rm rec})/\sigma_{\rm CMB}$ with $z_{\rm rec}=1100$ and $\sigma_{\rm CMB}=H_{0,\rm CMB}/c$ differs from the stored $R_{\rm CMB}$ by a relative amount in $[0.005,0.015]$; (iii) the same with $z_{\rm release}=1089$ differs by a relative amount in $[0.003,0.012]$; (iv) the stored $R_{\rm CMB}$ is not equal to either to within $10^{-3}$ (so the comment relation is approximate, not an identity); (v) $\mathrm{age\_SDT\_Gyr}/(R_{\rm CMB}/c)$ lies in $[0.45,0.50]$: the two stored time scales differ by a factor of about 2.1 | as stated | yes |

Reported, not criteria: the three durations and the three relative differences. Run 3 repeats T1–T3 unchanged and adds T4; run 3 is the run of record.
