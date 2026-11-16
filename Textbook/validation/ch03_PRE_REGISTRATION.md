# Chapter 3 — pre-registration of the worked-example instruments

Registered 2026-11-03, before `Textbook/examples/ch03_relay_kinematics.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object under test: the relay-kinematic relations of the chapter and the engine's depth-closure relations (`sdt::laws::depth_closure`, `laws.hpp:2820–2881`): local closure $\ell(z)=\ell_\infty(1-z)$, local oscillator rate $1-z$, far-frame relay speed $c_\infty(1-z)^2$, spectral shift $z_{\rm spec}=z_e-z_o$, and the integrated relay-speed deficit (`shapiro_delay`). All quantities in the chapter's tables are dimensionless counts or ratios; the SI conversion of the relay rate is a unit bridge and is printed as such.

Notation: $\mathrm{Om}=R/k^2$; depth $z=\mathrm{Om}/r$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\int_{-L}^{L}dl/\sqrt{l^2+b^2}=2\operatorname{asinh}(L/b)$ by the instrument's quadrature, for $L/b=3,\,300,\,3\times10^{4}$ (panelled rule) | $10^{-12}$ relative |
| V2 | series $\big[(1-z)^{-2}-1\big]/(2z)=1+\tfrac32z+2z^2+\tfrac52z^3+\dots$ against direct evaluation at $z=10^{-3}$ (four terms) | $10^{-11}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | the far-frame relay speed factorises into one closure factor for the hop and one for the oscillator rate: `c_far(c,z)` $=c\cdot\text{closure\_local}(1,z)\cdot\text{clock\_rate}(z)$ for $z\in\{0,0.1,\dots,0.9\}$, and `depth_from_c_far(c_far(c,z),c)` $=z$ | factorisation within $10^{-15}$ relative; inverse within $10^{-14}$ | yes — a single-factor $c(1-z)$ or a $\sqrt{1-z}$ clock fails |
| T2 | the two spectral forms differ by an exact amount: $\dfrac{1-z_o}{1-z_e}-1-(z_e-z_o)=\dfrac{z_e(z_e-z_o)}{1-z_e}$, for $z_e\in\{10^{-6},10^{-4},10^{-2},0.1,0.3\}$ with $z_o=z_e/3$ | within $10^{-12}$ of the exact difference (absolute value relative to $z_e^2$) | yes |
| T3 | integrated relay-speed deficit. For a straight ray with impact parameter $b=R_\odot$ between $r_1=1$ AU and $r_2=1.523679$ AU: (a) `shapiro_delay(koppa_Sun, r1, r2, b)` equals $(2\,\mathrm{Om}/c)\,[\operatorname{asinh}(l_1/b)+\operatorname{asinh}(l_2/b)]$ with $l_i=\sqrt{r_i^2-b^2}$, within $5\times10^{-5}$ relative; (b) it equals the quadrature of the exact integrand $\int(1/c_{\rm far}-1/c)\,dl$, $z=\mathrm{Om}/r$, within $10^{-5}$ relative | tolerances as stated | yes — a missing factor 2 (coefficient 1) or an unweighted $z$ fails by 50 % or more |
| T4 | recurrence counts. For a circular state of reach $r$ and speed $v$: relay intervals per orbit $n_{\rm orb}=2\pi\,k\,r/\ell_P$ equals $P_{\rm orb}\,c/\ell_P$ with $P_{\rm orb}=2\pi r/v$; radians swept per light-crossing of $r$ equal $v/c$. Cases: hydrogen ground state ($r=a_0$, $v=\alpha c$) and the Earth about the Sun at 1 AU ($v$ from the Sun's precession-derived $k$, `bridge::k_Sun_from_precession`) | each identity within $10^{-14}$ relative | yes — a unit slip ($2\pi$, $\ell_P$) fails |
| T5 | engine consistency of the counts: `law_I::N` equals $R_{\rm CMB}/\ell_P$; hydrogen $\mathrm{Om}_H=\alpha^2a_0$ equals $r_e$ | $10^{-9}$ relative (CODATA rounding) | yes |

The hop counts of Table 3.1 (lengths over $\ell_P$) and the depth values of Table 3.2 are tabulated, not criteria. The relation of the Sun's depth to a measured spectral shift is not tested here (Chapter 45); the measured shift is limited by convective blueshift.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch03_relay_kinematics`

## Correction before the first run (2026-11-03)

T2 as first written compared a double-precision evaluation of the difference of the two spectral forms with its exact value. While writing the instrument it was found that the difference is of order $z_e^2$, so for $z_e\le10^{-4}$ a double-precision evaluation cancels to the size of the quantity itself and cannot meet the registered $10^{-12}$ (relative to $z_e^2$). The method is replaced; the criterion becomes stricter, not looser. T2 is evaluated in exact rational arithmetic (64-bit integer fractions with overflow checks) for $z_e\in\{3/10,\ 10^{-1},\ 10^{-2},\ 10^{-4},\ 10^{-6}\}$ with $z_o=z_e/3$, and passes when
$$\frac{1-z_o}{1-z_e}-1-(z_e-z_o)\;=\;\frac{z_e\,(z_e-z_o)}{1-z_e}$$
holds as an exact equality of rationals in every case. No run existed when this correction was made.

## Record of run 1 and repair of V1 (2026-11-03)

Run 1 (`ch03_run1_output.txt`) failed instrument validation V1 at $L/b=3\times10^{4}$: the uniform-panel rule in the variable $l$ returned $22.053$ against the exact $22.004$ (relative error $2.2\times10^{-3}$). The cause is an instrument limit, not a property of the object: 64 equal panels over $[-L,L]$ are each $937\,b$ wide, while the integrand varies on the scale $b$. Test T3 does not use that rule; it integrates in the variable $u$ with $l=b\sinh u$, where the integrand is smooth. Because V1 did not validate the instrument as T3 uses it, the T-results of run 1 are not quoted. V1 is replaced by the known-answer test on the substituted variable: $\int_{-L}^{L}dl\,(l^2+b^2)^{-3/2}=2L/\big(b^2\sqrt{L^2+b^2}\big)$, evaluated as $\int b^{-2}\operatorname{sech}^2u\,du$ over $[-\operatorname{asinh}(L/b),\operatorname{asinh}(L/b)]$ with the quadrature of T3, for $L/b=3,\,300,\,3\times10^{4}$, tolerance $10^{-12}$ relative. All other criteria are unchanged. Run 2 is the run of record.
