# Chapter 29 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch29_many_electron_organisation.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The engine's many-electron construction `atomic::dodecardinal` (APS14, `laws.hpp:1565–2015`): a state energy in independent shell radii (Rydberg units, radii in $a_0$)
$$E=\sum_i\Big[\frac{n_i^2}{r_{g(i)}^2}-\frac{2Z}{r_{g(i)}}\Big]+\sum_{i<j}\frac{2\,w_{ij}}{\lvert\vec r_i-\vec r_j\rvert},$$
with seats (two $n=1$ polar, two $n=2$ polar, then a six-ring of $n=2$ lanes) and pair prices $w_{ij}$ of exact geometry ($8/7$, $7/8$, $\pi/3$, $1$, $(6/7)\,K$-ratio$+1/14$, $1/14$); a Newton solver in log-radii with four starting scales; and `first_ionisation_eV` as the difference of relaxed ion and neutral minima. The header states that no measured ionisation energy and no element-specific screening enters. This chapter executes the checks the plan requires of a numerical minimum: stationarity (analytic gradient against finite differences), stability (positive Hessian), independence of the starting point, and the distinction between a relaxed (adiabatic) and a frozen-geometry (vertical) ionisation; and then a registered comparison with measured first ionisation energies, with the computed values printed before the measured list is loaded. The functional form is the engine's; the chapter does not derive it.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | one electron: `solve_state(Z,1)` returns $r=1/Z$ ($a_0$) and $E=-Z^2$ Ry for $Z=1\ldots10$ (minimum of $1/r^2-2Z/r$) | $10^{-9}$ relative |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | stationarity. For $Z=1\ldots10$ and $1\le N_e\le10$ ($N_e\le Z+2$): at 5 fixed pseudo-random log-radius vectors the analytic `state_gradient` equals the central finite difference of `state_energy_ry` (step $10^{-6}$) | relative to $\max(1,\lvert E\rvert)$ within $10^{-6}$ | yes — a gradient inconsistent with the energy rejects any claim that the solver found a stationary point |
| T2 | converged neutral states for $Z=1\ldots10$: `converged` is true and `force_residual` $<10^{-8}$; from 20 pseudo-random starts (log-radii in $[\ln0.05,\ln6]$) a damped gradient descent with backtracking on the engine's energy and gradient never reaches an energy below the engine's minimum by more than $10^{-7}$ Ry. The number of distinct minima found (energy rounded to $10^{-6}$ Ry) is printed | as stated | yes — a lower minimum found by an independent start rejects the engine's minimum |
| T3 | stability. At each converged neutral minimum the finite-difference Hessian in log-radii (step $10^{-4}$) is positive definite (leading principal minors positive) | positive definite for $Z=1\ldots10$ | yes |
| T4 | ionisation. (a) Hydrogen: `first_ionisation_eV(1)` equals the stored Ry to $10^{-9}$. (b) The computed first ionisation energies for $Z=1\ldots10$ are printed **before** the measured list is read. (c) Registered comparison with the measured values (H 13.5984, He 24.5874, Li 5.3917, Be 9.3227, B 8.2980, C 11.2603, N 14.5341, O 13.6181, F 17.4228, Ne 21.5645 eV; OBSERVED): the relative residual of every element is within 10%. Reported: all residuals, the mean absolute residual, the sign pattern | (a) $10^{-9}$; (c) every residual $\le10\%$; a miss is a finding and is recorded as such | yes |
| T5 | relaxation. For $Z=2\ldots10$, the vertical ionisation (the ion with $Z-1$ electrons evaluated at the neutral's relaxed radii) is at least the adiabatic value (the ion's own minimum) within $10^{-9}$ Ry; the relaxation energy is printed | as stated | yes — a vertical value below the adiabatic one contradicts the minimum |

Reported, not criteria: radii, relaxation energies, the number of minima, residuals.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch29_many_electron_organisation`

## Record of run 1; repairs to T1 and T2 (2026-11-10)

Run 1 (`ch29_run1_output.txt`) met V1, T3, T4 (a, c: every residual within 10%, worst 5.25%, mean 1.94%) and T5, and failed T1; T2 passed but is weakened as follows.

1. **T1** failed at $2.5\times10^{-6}$ against $10^{-6}$. The finite difference with step $10^{-6}$ is stiff-limited: when two random radii nearly coincide the pair term $1/d$ is nearly singular and the truncation error of the central difference is no longer small. The analytic gradient was derived by hand and matches the expression in the engine; the instrument is repaired with a Richardson-extrapolated difference $(4D(h/2)-D(h))/3$ at $h=10^{-4}$ (truncation $O(h^4)$); the tolerance $10^{-6}$ is unchanged.
2. **T2** passed in run 1 only weakly. The plain gradient descent of the instrument converged from few starts for $Z\ge8$: for $Z=8$ and $Z=10$ the only converged starts reached higher local minima ($-66.3$ and $-127.1$ Ry against the engine's $-149.6$ and $-257.0$), and for $Z=9$ no start converged, so the criterion held vacuously there. Two results follow. First, a **finding**: the energy has more than one local minimum (two distinct minima for $Z=3\ldots7$, and higher minima for $Z=8,10$), so the choice of start matters; the engine uses four starting scales and keeps the lowest. Second, an **instrument repair**: the independent search is replaced by BFGS with Armijo backtracking on the engine's energy and gradient from 40 starts, and the test requires at least 5 converged starts for every $Z$ (otherwise the test is inconclusive and counts as failed); the criterion on the lowest energy found is unchanged. Run 2 is the run of record.
