# Chapter 34 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch34_noncircular_trajectories.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Motion under the relative acceleration $a=-\mu\hat r/r^2$ with $\mu=c^2\varpi_{\rm tot}$ (Chapter 15; units $\mu=1$ here) when the trajectory is not circular, and under a named departure from it. (a) The radial and transverse decomposition: $\dot r^2=2(\varepsilon+\mu/r)-L^2/r^2$ with the conserved energy $\varepsilon$ and angular momentum $L$; turning points $r_{p,a}=a(1\mp e)$, $a=-\mu/(2\varepsilon)$, $e=\sqrt{1+2\varepsilon L^2/\mu^2}$; period $2\pi\sqrt{a^3/\mu}$ independent of $e$; (b) closure: the pure inverse-square route has no apsidal advance, while an added acceleration $-\kappa/r^3$ gives the exact advance per radial period $\Delta\varphi=2\pi\big(1/\sqrt{1-\kappa/L^2}-1\big)$ (the orbit equation in $u=1/r$ is linear: $u''+(1-\kappa/L^2)u=\mu/L^2$); (c) the open trajectory ($\varepsilon>0$): periapsis $r_p=p/(1+e)$ with $p=L^2/\mu$ and deflection $2\arcsin(1/e)$. All by RK4 integration of the central-force equations (no engine call is needed beyond the conserved ledger of Chapter 15); no measured data are loaded; the named source condition is a point source of fixed strength.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | apoapsis start $r_a=1.51$, $v_a=\sqrt{2/r_a-1}$ ($\mu=1$): $\varepsilon=-\tfrac12$ ($a=1$) and $e=0.51$ from the formulas | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | $e\in\{0.3,0.6,0.9\}$, $a=1$, apoapsis start, RK4 with $T/2\times10^5$ steps over 3 periods: the extreme radii equal $1\mp e$ to $10^{-8}$ (parabolic interpolation); the period measured between successive apoapsis passages equals $2\pi$ to $10^{-8}$ relative for all three $e$; energy and angular momentum drift $\le10^{-9}$ relative over 3 periods; $\lvert\dot r^2-[2(\varepsilon+\mu/r)-L^2/r^2]\rvert\le10^{-7}$ at 1000 sampled points | as stated | yes |
| T2 | apsidal motion, $e=0.3$ start at $r_a=1.3$ with $v_a=\sqrt{2/r_a-1}$: with $\kappa=0$ the angle between successive apoapsis passages is $2\pi$ to $10^{-7}$ rad; with $\kappa=0.002$ the advance per radial period equals $2\pi(1/\sqrt{1-\kappa/L^2}-1)$ to $2\times10^{-4}$ relative to the advance, with $L=r_av_a$ | as stated | yes — a nonzero advance at $\kappa=0$, or a mismatch with the exact form, rejects |
| T3 | open trajectory, $\mu=1$, start at $(-2000,\,1)$ with velocity $(1,0)$; integrate until $r\ge2000$ again: $\varepsilon=\tfrac12-\tfrac1{r_0}$ with $r_0=\sqrt{2000^2+1}$, $L=1\cdot1$; periapsis radius equals $p/(1+e)$ to $10^{-8}$; the angle between initial and final velocity equals $2\arcsin(1/e)$ to $10^{-5}$ rad | as stated | yes |

Reported, not criteria: the measured advances.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch34_noncircular_trajectories`

## Record of run 1; instrument defect in the perturbing acceleration (2026-11-10)

Run 1 (`ch34_run1_output.txt`) met V1, T1 (all three eccentricities: extreme radii to $4\times10^{-13}$, period to $4.5\times10^{-13}$, conservation and radial equation to $6\times10^{-13}$), the $\kappa=0$ clause of T2 (advance $-8.3\times10^{-14}$ rad) and T3 (periapsis to $4\times10^{-10}$, deflection to $2.5\times10^{-7}$ rad), and failed the $\kappa=0.002$ clause of T2: the measured advance $1.527\times10^{-2}$ rad was $2.2$ times the registered exact form $6.916\times10^{-3}$ rad. Cause: the instrument's acceleration components were coded as $-(1/r^3+\kappa/r^5)\,x$, i.e. a radial perturbation $-\kappa/r^4$, instead of $-(1/r^3+\kappa/r^4)\,x$ for the registered radial perturbation $-\kappa/r^3$. The registered form is correct for $-\kappa/r^3$: with Binet's equation $u''+u=-a_r/(L^2u^2)$ one has $u''+u=(\mu+\kappa u)/L^2$, linear. This is an instrument defect, not a finding on the object, and the criterion is unchanged. The exponent in the instrument is corrected. Run 2 is the run of record.
