# Chapter 33 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch33_circular_similarity_across_scales.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The shared circulation geometry $v^2r=c^2\mathrm{Om}$, $a=c^2\mathrm{Om}/r^2$, $z_{\rm depth}=\mathrm{Om}/r$, $k=\sqrt{r/\mathrm{Om}}$, $P_{\rm orb}c/\mathrm{Om}=2\pi x^{3/2}$ with $x=r/\mathrm{Om}$. With $\mathrm{Om}$ defined as $v^2r/c^2$ these relations are identities; the content is that $\mathrm{Om}$ is the same at different radii within one system and that independently defined determinations agree. The tests: (a) the master relations to round-off on the hydrogen ladder, Earth's surface, the Moon's orbit and the six inner planets; (b) hydrogen: $\mathrm{Om}_n=r_e$ for $n=1\ldots8$ (shared-input with the CODATA set); (c) the Sun: $\mathrm{Om}_\odot=(2\pi a/T)^2a/c^2$ for Mercury, Venus, Earth, Mars, Jupiter and Saturn from published mean semi-major axes and sidereal periods (OBSERVED, processed ephemeris elements; no $G$, no source mass), with the registered criterion that the spread (max/min $-1$) of the six values is at most $2\times10^{-3}$ (the mass of Jupiter alone, an effect of order $10^{-3}$, lies inside it); (d) Earth: $\mathrm{Om}_\oplus$ from the surface circular speed and radius stored in the engine (`bridge::v_Earth`, `R_Earth`) against $\mathrm{Om}_\oplus$ from the lunar orbit ($a=384400$ km, sidereal period 27.321661 d), registered to agree within 2%; (e) the logarithmic-derivative identity (33.4) for the pressure-state change of the circular speed; (f) the relation between $\mathrm{Om}_H$ and the proton lock radius, arithmetic only. The criteria are registered before the observed elements are read.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $x=4$: $v/c=1/2$, $a\,\mathrm{Om}/c^2=1/16$, $P_{\rm orb}c/\mathrm{Om}=16\pi$ (the illustrative values of the draft) | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | master relations. For each system point (hydrogen $n=1$, Earth surface, Moon orbit, Mercury… Saturn): $v/c=x^{-1/2}$, $a\mathrm{Om}/c^2=x^{-2}$, $P_{\rm orb}c/\mathrm{Om}=2\pi x^{3/2}$ with $\mathrm{Om}=v^2r/c^2$, $a=v^2/r$, $P=2\pi r/v$ | $10^{-12}$ relative | yes |
| T2 | hydrogen ladder: $\mathrm{Om}_n=v_n^2r_n/c^2=r_e$ for $n=1\ldots8$ ($Z=1$); shared-input with the CODATA set | $10^{-14}$ | yes |
| T3 | six planets: $\mathrm{Om}_i$ from $(a_i,T_i)$; spread $\le2\times10^{-3}$; the mean $\mathrm{Om}_\odot$ and the values are printed; $x_i=a_i/\mathrm{Om}_\odot$ spans 4 orders of magnitude of $a$ ratio (Saturn/Mercury) and the spread does not trend with $x$ at the level of the registered window (slope of $\ln\mathrm{Om}$ against $\ln x$ is below $10^{-4}$ in magnitude) | as stated | yes — a spread above $2\times10^{-3}$ or a trend rejects a single $\mathrm{Om}$ for the Sun at this precision |
| T4 | Earth: the ratio $\mathrm{Om}_\oplus$(lunar orbit)/$\mathrm{Om}_\oplus$(surface) lies in $[0.98,1.02]$; printed with the two values and $x$ for each | as stated | yes |
| T5 | identity (33.4): for $c(S)=c_0(1+0.3S)$, $\mathrm{Om}(S)=\mathrm{Om}_0e^{0.2S}$, $r(S)=r_0(1+S^2)$: $d\ln v/dS$ from finite differences of $v=c\sqrt{\mathrm{Om}/r}$ equals $d\ln c/dS+\tfrac12d\ln\mathrm{Om}/dS-\tfrac12d\ln r/dS$ at $S=0.4$ | $10^{-8}$ | yes |
| T6 | $r_e/R_p$ (stored $R_p$) and $\mathrm{Om}_H/R_{p,\rm lock}$ are printed; criterion: they are not 1 (distinct objects) | as stated | yes |

Reported, not criteria: $\mathrm{Om}$ values for every system, $x$ values, $\log_{10}$ range.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch33_circular_similarity_across_scales`
