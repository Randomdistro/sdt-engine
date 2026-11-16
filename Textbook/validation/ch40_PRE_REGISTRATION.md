# Chapter 40 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch40_compact_objects_and_singularity_tests.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The strong-depth end of the circular family, under the engine's profiles (`depth_closure`), without asserting an interior solution. (a) The exterior circular branch reaches $v=c$ at $r=\mathrm{Om}$ and its extrapolation exceeds $c$ inside: a boundary of the branch, not an interior solution; (b) an extended symmetric source with enclosed source length $\varpi_{\rm enc}(r)=\varpi(r/R)^3$ has radial acceleration $c^2\varpi r/R^3$ near and through the centre, so a radial oscillation through the centre has period $2\pi\sqrt{R^3/(c^2\varpi)}$ with finite acceleration everywhere (a conditional interior regularity, not a derivation of the density profile); (c) coordinate arrest: for $c_{\rm far}=c(1-\mathrm{Om}/r)^2$ and radial propagation $dr/dt=-c_{\rm far}$ the elapsed coordinate time to reach $\delta=r-\mathrm{Om}$ is $ct=r+2\mathrm{Om}\ln\delta-\mathrm{Om}^2/\delta+\text{const}$ (exact), so $\delta\to0$ is not reached in finite time and $\delta\approx\mathrm{Om}^2/(ct)$ at late times; the accumulated local duration with tick-rate ratio $C=1-z=\delta/r$ is $\tau=(\mathrm{Om}\ln\delta+\delta)/c+\text{const}$ (exact), diverging logarithmically; (d) the angular-impulse ledger: for the circular family $h=c\sqrt{\mathrm{Om}\,r}$, so $h=c\,\mathrm{Om}$ at $r=\mathrm{Om}$, and a continuation to a zero-angular-momentum axial state needs the difference carried by source circulation, medium deformation or outgoing transport (the ledger value is printed; no continuation law is supplied). The chapter does not establish an interior law, finite stress or a continuation; a numerical refusal or a vanishing coordinate speed completes neither.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the antiderivative $F(r)=r+2\mathrm{Om}\ln(r-\mathrm{Om})-\mathrm{Om}^2/(r-\mathrm{Om})$ has derivative $r^2/(r-\mathrm{Om})^2$ (central difference at $r/\mathrm{Om}=1.01,1.5,3,10$, step $10^{-5}\mathrm{Om}$); and the antiderivative $G(\delta)=\mathrm{Om}\ln\delta+\delta$ has derivative $(\mathrm{Om}+\delta)/\delta$ | $10^{-7}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | $v/c=\sqrt{\mathrm{Om}/r}$ equals 1 at $r=\mathrm{Om}$, 2 at $r=\mathrm{Om}/4$, and exceeds 1 for every $r<\mathrm{Om}$ sampled ($r/\mathrm{Om}=0.9,0.5,0.1,0.01$); the engine's `depth_closure::v_bound` agrees with the formula | $10^{-14}$ | yes |
| T2 | uniform-density interior: RK4 integration of a radial oscillation through the centre ($\ddot x=-\omega^2x$ with $\omega^2=c^2\varpi/R^3$, started at rest at $x=R$) over 3 periods: period equals $2\pi/\omega$ to $10^{-9}$; the speed at the centre is $\omega R$ to $10^{-9}$; acceleration at $r=10^{-2}R$ is $10^{-2}\,c^2\varpi/R^2$ while the point-source value there is $10^{4}\,c^2\varpi/R^2$ (ratio $10^{-6}$, exact) | as stated | yes |
| T3 | arrest. RK4 integration of $d\delta/dt=-c(\delta/(\mathrm{Om}+\delta))^2$ from $\delta_0=0.5\mathrm{Om}$ (units $c=\mathrm{Om}=1$): the time to reach $\delta=10^{-3}$ equals $F(1+\delta_0)-F(1+10^{-3})$ to $10^{-6}$ relative; $\delta\,ct/\mathrm{Om}^2$ at $ct/\mathrm{Om}=10^2,10^3,10^4$ printed and within $5\times10^{-3}$ of 1 at $10^4$; the local duration $\tau(\delta_0\to10^{-3})$ by numerical integration of $C\,dt$ equals $G(\delta_0)-G(10^{-3})$ divided by $c$ to $10^{-6}$ relative, and the increment per decade of $\delta$ at small $\delta$ equals $\mathrm{Om}\ln10/c$ to 1% | as stated | yes |
| T4 | ledger scale. $c\,\mathrm{Om}$ for the Sun ($\varpi_\odot=1476.6$ m) and for the Milky Way's baryonic total (`milky_way::koppa_mw_m`) printed (m$^2$/s) | printed | — |

Reported, not criteria: the late-time values $\delta ct/\mathrm{Om}^2$, the ledger scales.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch40_compact_objects_and_singularity_tests`

## Record of run 1; step of the V1 central difference (2026-11-10)

Run 1 (`ch40_run1_output.txt`) met every criterion of T1, T2, T3 and the second line of V1, and failed the first line of V1 ($9.9\times10^{-7}$ against $10^{-7}$). The registered central-difference step $10^{-5}\mathrm{Om}$ is fixed, while the function $F$ is stiff near $r=\mathrm{Om}$ (the terms $\ln(r-\mathrm{Om})$ and $1/(r-\mathrm{Om})$ vary on the scale $r-\mathrm{Om}=0.01\mathrm{Om}$ at $r/\mathrm{Om}=1.01$), so the relative truncation error $\sim(h/(r-\mathrm{Om}))^2\approx10^{-6}$ exceeds the tolerance there. This is an instrument defect, not a finding on the object (the exactness of $F$ is independently confirmed by the T3 clause, where the time to reach $\delta=10^{-3}$ matches $F(1.5)-F(1.001)$ to $3\times10^{-14}$). The step is scaled with the distance to the singularity, $h=10^{-3}(r-\mathrm{Om})$, with the tolerance unchanged. Results of run 1 recorded for the chapter: period through the centre $2\pi$ to $1.6\times10^{-12}$; $\delta\,ct/\mathrm{Om}^2=1.0659,\,1.0110,\,1.0016$ at $ct/\mathrm{Om}=10^2,10^3,10^4$; local duration to $\delta=10^{-3}$ equal to $G(\delta_0)-G(10^{-3})$ to $1.7\times10^{-8}$; $c\,\mathrm{Om}=4.4281\times10^{11}$ m$^2$/s (Sun), $2.2893\times10^{22}$ m$^2$/s (Milky Way baryonic total). Run 2 is the run of record.

## Record of run 2; the repair of run 1 did not change the worst case (2026-11-10)

Run 2 (`ch40_run2_output.txt`) reproduced run 1 in every clause and failed the first line of V1 at the same value ($9.868388\times10^{-7}$). The repair recorded above was inadequate: the worst case is $r/\mathrm{Om}=1.01$, where the new step $10^{-3}(r-\mathrm{Om})=10^{-5}\mathrm{Om}$ is identical to the old fixed step, so nothing changed there, and the truncation error $(h/(r-\mathrm{Om}))^2=10^{-6}$ remained. The step is set to $h=10^{-4}(r-\mathrm{Om})$ (relative truncation $\approx10^{-8}$; rounding at $r=1.01$ is $\approx10^{-12}$ relative); the tolerance is unchanged. Run 3 is the run of record.
