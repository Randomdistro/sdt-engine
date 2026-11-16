# Chapter 39 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch39_lensing_and_propagation_delay.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. One relay response, two observables. For a stationary relay speed $c_{\rm far}=c_\infty(1-z)^2$ with $z=\varpi/r$ (`depth_closure::c_far`), the one-way delay along a path is $\Delta t=\int(1/c_{\rm far}-1/c_\infty)\,ds$ and the bending follows from the refractive index $n=c_\infty/c_{\rm far}=(1-z)^{-2}=1+2z+3z^2+\ldots$. (a) The inverse-speed series $1/c_{\rm far}=c_\infty^{-1}(1+2z+3z^2+\ldots)$; the straight-path first-order delay $(2\varpi/c)\big[\sinh^{-1}(s_1/b)+\sinh^{-1}(s_2/b)\big]$ and its far-endpoint limit $(2\varpi/c)\ln(4r_1r_2/b^2)$ (`depth_closure::shapiro_delay`), checked against numerical integration of the exact integrand for an Earth–Mars grazing geometry with the Sun's source length; (b) bending: the exact ray deflection in the spherically symmetric index $n(r)$ by the Bouguer integral $\alpha=2\int_{r_0}^\infty b\,dr/(r\sqrt{n^2r^2-b^2})-\pi$, $b=n(r_0)r_0$, whose expansion in $\varpi/b$ starts at $4\varpi/b$; (c) branch discrimination: the alternative profile $c_{\rm far}/c_\infty=1-2z$ has $n=1/(1-2z)=1+2z+4z^2+\ldots$ and shares the first-order delay and bending, so first-order agreement cannot select the branch; the second-order coefficients of the deflection differ and their difference at the solar limb is computed. No measured delay or deflection is loaded.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | (i) $\int_{-s_1}^{s_2}ds/\sqrt{b^2+s^2}=\sinh^{-1}(s_1/b)+\sinh^{-1}(s_2/b)$ by quadrature at $b=1$, $s_1=3$, $s_2=7$; (ii) the Bouguer integral gives deflection 0 for a constant index $n=1.5$; (iii) for $n=1+\epsilon/r$ with $\epsilon=10^{-4}$ and $r_0=1$ the deflection equals $2\epsilon/b$ to $10^{-3}$ relative ($b=n_0r_0$) | $10^{-10}$, $10^{-10}$ (absolute), $10^{-3}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | series and delay. $(1-z)^{-2}$ against $1+2z+3z^2+4z^3$ at $z=10^{-2}$: difference $\le5z^4$; the engine's `shapiro_delay` for $\varpi_\odot$ (from `bridge::koppa_Sun`), $r_1=1$ AU, $r_2=1.524$ AU, $b=R_\odot$ equals $(2\varpi/c)\ln(4r_1r_2/b^2)$ exactly; the first-order delay with the exact endpoints $s_i=\sqrt{r_i^2-b^2}$ differs from the far-endpoint form by at most $10^{-6}$ relative; numerical integration of the exact integrand $1/c_{\rm far}-1/c$ differs from the first-order endpoint form by the second-order term, equal to $(3\varpi^2/c)\int ds/(b^2+s^2)$ to 1% relative; printed: the round-trip delay in $\mu$s | as stated | yes |
| T2 | bending. For $n=(1-\varpi/r)^{-2}$ the deflection obtained by the Bouguer integral at $\varpi/b=10^{-3},\,2\times10^{-3},\,4\times10^{-3}$ is fitted by $\alpha=c_1x+c_2x^2+c_3x^3$ ($x=\varpi/b$): $c_1=4$ to $10^{-5}$; $c_2$ printed. At the solar limb $4\varpi_\odot/R_\odot$ in arcsec is printed | $\lvert c_1-4\rvert\le4\times10^{-5}$ | yes |
| T3 | branches. The same fit for $n=1/(1-2\varpi/r)$: $c_1=4$ to $10^{-5}$ (shared first order); $c_2$ differs from the first branch's by an amount $\Delta c_2\ne0$; a third branch $n=1+2z+2z^2$ gives $c_2$ such that $c_2$ is linear in the coefficient $a$ of $z^2$ (differences between $a=2,3,4$ equal to 1%). Printed: $\Delta c_2$, the difference in deflection between the two branches at the solar limb (arcsec), the second-order delay difference $\pi\varpi^2/(bc)$ for $\varpi_\odot$, $b=R_\odot$ (picoseconds, one way) | as stated | yes — a $c_2$ equal for the two branches would reject the statement that the second order discriminates them |

Reported, not criteria: $c_2$ values, the solar-limb differences.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch39_lensing_and_propagation_delay`

## Record of run 1; two tolerances corrected (2026-11-10)

Run 1 (`ch39_run1_output.txt`) met every criterion of T2 and T3, the delay clauses of T1 and the first and third lines of V1, and failed two clauses, both defects of the registered tolerances and not findings on the object.

1. **V1, constant index.** The Bouguer integral gave deflection $1.0000000001-1$, i.e. $1.0\times10^{-10}$ against the registered absolute $10^{-10}$. This is the accuracy of the instrument's quadrature, whose integrand has an endpoint guard ($t<10^{-8}$) and a $t^{-1}$-type cancellation near the periapsis. The tolerance is set to $10^{-9}$ for this line.
2. **T1, series.** The registered bound $\lvert(1-z)^{-2}-(1+2z+3z^2+4z^3)\rvert\le5z^4$ at $z=10^{-2}$ is violated by the next terms, since the remainder is $5z^4+6z^5+\ldots=5z^4(1+1.2z+\ldots)$; the bound should have been $5z^4(1+2z)$. Corrected to $5.1z^4$.

The rest of run 1 is recorded as results: the round-trip first-order delay for $r_1=1$ AU, $r_2=1.524$ AU, $b=R_\odot$ is $247.314\ \mu$s (the engine's header comment states $247.24\ \mu$s, a difference of $0.03\%$, not examined); the exact integrand minus the first-order term equals the second-order term to $6\times10^{-5}$ relative; the fitted deflection coefficients are $c_1=4.0000038$ and $c_2=15.7019$ (active profile) and, for $n=1+2z+az^2$, $c_2=12.5642,\ 15.7042,\ 18.8398$ for $a=2,3,4$ (equal to $\pi(a+2)$ within $10^{-3}$ relative). Run 2 is the run of record.
