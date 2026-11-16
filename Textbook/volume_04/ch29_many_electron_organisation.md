# Chapter 29 — Many-Electron Organisation

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: shell radii $r_g$ are in units of $a_0$ and energies in Rydberg units unless stated; $w_{ij}$ is a pair price; $g(i)$ is the shell group of seat $i$. Executable companion: `Textbook/examples/ch29_many_electron_organisation.cpp`; pre-registration and captured output in `Textbook/validation/`. The functional form is the engine's (`atomic::dodecardinal`, `laws.hpp:1565–2015`); this chapter checks the numerical state and its stability and compares with measurement under a registered window, and does not derive the form.

## 29.1 The physical question

A many-electron atom is a collective construction in which occupancy and radius relax together: fixing every shell radius from one-electron values would remove the collective response being tested. The questions are what organises the electrons (seats and pair prices), whether the engine's numerical minimum is a stationary, stable, start-independent minimum, how ionisation should be computed (relaxed or frozen geometry), and how far a single pair law and a single optimisation specification reach across the first ten elements without an element-specific screening insertion.

## 29.2 The construction

The engine's state is a set of seats: two polar seats at $n=1$ (group 0), two polar seats at $n=2$ (group 1), and then six $n=2$ lanes on a ring in three $120^\circ$ lanes followed by their antipodes (group 2), up to ten electrons. Each group has one radius. The state energy in the engine's units is

$$E=\sum_i\Big[\frac{n_i^2}{r_{g(i)}^2}-\frac{2Z}{r_{g(i)}}\Big]+\sum_{i<j}\frac{2\,w_{ij}}{d_{ij}},\qquad d_{ij}^2=r_i^2+r_j^2-2r_ir_j\cos\theta_{ij}. \tag{29.1}$$

The pair prices are exact geometry: $8/7$ for the polar $s$ dyad, $7/8$ between seats of unlike $n$ (one shared $n^3$ period), $\pi/3$ between $2s$ and $2p$ (a $60^\circ$ glancing arc over its chord), $1$ for $p$ lanes at $60^\circ$, $\tfrac67$ times a counterphase path-to-chord ratio plus $\tfrac1{14}$ at $120^\circ$, and $\tfrac1{14}$ at $180^\circ$. The state is the minimum of (29.1) in the independent group radii. The header states that no measured ionisation energy and no element-specific screening enters. Occlusion modifies directional throughput rather than subtracting a universal scalar from the source strength; a scalar effective-source approximation is a reduction that needs an angular justification, and the angular dependence is what the prices above carry.

## 29.3 A numerical minimum has to be checked

A minimum returned by a numerical solver must satisfy residual stationarity and stability, and several starting configurations are needed to distinguish a local minimum from a lower accessible construction.

**One-electron check (V1).** For $Z=1\ldots10$ the solver returned $r=1/Z$ to $9.9\times10^{-15}$ and $E=-Z^2$ Ry to $2.2\times10^{-16}$, the exact minimum of $1/r^2-2Z/r$.

**Stationarity (T1).** The analytic gradient in log-radii was compared with a Richardson-extrapolated central difference of the energy at five pseudo-random radius vectors for every $Z=1\ldots10$ and every electron count $1\le N_e\le\min(10,Z+2)$: 360 combinations, worst deviation $5.0\times10^{-7}$ relative to $\max(1,|E|)$. (Run 1 used a plain central difference of step $10^{-6}$ and failed at $2.5\times10^{-6}$; stiffness where two radii nearly coincide limits that difference, and the repair is recorded in the pre-registration.)

**Independence of the start (T2).** All ten neutral states converged with force residual below $10^{-8}$ (largest $1.5\times10^{-9}$). A BFGS minimiser with backtracking, run from 40 pseudo-random starts in $r\in[0.05,6]$ for each $Z$, converged in 39 or 40 starts, and for every $Z$ its lowest energy equalled the engine's to the printed digits ($-1.00000000$, $-5.87755102$, $-15.11177308$, $-29.46406523$, $-49.32608207$, $-75.56018764$, $-108.87600336$, $-149.62774997$, $-198.77322831$, $-257.02040333$ Ry for $Z=1\ldots10$): no start reached a lower energy. **The energy has more than one stationary minimum.** For $Z\ge3$ two distinct minima were found. The first run of the instrument, a plain gradient descent, ended at higher minima for $Z=8$ ($-66.3$ Ry) and $Z=10$ ($-127.1$ Ry) and did not converge for $Z=9$, so a single start can end in the wrong basin; the engine uses four starting scales and keeps the lowest. The conclusion that the engine's value is the global minimum of (29.1) rests on 40 random starts per element, not on a proof.

**Stability (T3).** The finite-difference Hessian in log-radii at each converged minimum is positive definite: the leading principal minors are positive for all ten neutral states (for $Z=10$: $3.75\times10^2$, $2.45\times10^3$, $1.36\times10^5$).

## 29.4 First ionisation under a registered window

Ionisation compares the relaxed neutral and ion constructions, $E_{\rm ion}=E_{\rm ion,min}-E_{\rm neutral,min}$ with $N_e=Z-1$ for the ion.

**Executed (T4).** Hydrogen equals the stored Ry to $2.6\times10^{-16}$ (one electron; the infinite-nucleus value). The computed first ionisation energies for $Z=1\ldots10$ were printed before the measured list was read: $13.6057,\ 25.5454,\ 5.1304,\ 8.8334,\ 8.2500,\ 11.2791,\ 14.6434,\ 13.5511,\ 17.1657,\ 21.1595$ eV. The registered comparison (every residual within 10%) with the measured values (OBSERVED) gives:

| element | computed (eV) | measured (eV) | residual |
|---|---|---|---|
| H | 13.6057 | 13.5984 | $+0.05\%$ |
| He | 25.5454 | 24.5874 | $+3.90\%$ |
| Li | 5.1304 | 5.3917 | $-4.85\%$ |
| Be | 8.8334 | 9.3227 | $-5.25\%$ |
| B | 8.2500 | 8.2980 | $-0.58\%$ |
| C | 11.2791 | 11.2603 | $+0.17\%$ |
| N | 14.6434 | 14.5341 | $+0.75\%$ |
| O | 13.5511 | 13.6181 | $-0.49\%$ |
| F | 17.1657 | 17.4228 | $-1.48\%$ |
| Ne | 21.1595 | 21.5645 | $-1.88\%$ |

Table 29.1. Computed against measured first ionisation energies, executed (T4).

All residuals lie within the registered window; the mean absolute residual is $1.94\%$ and the worst is $5.25\%$ (beryllium). The hydrogen residual $+0.05\%$ is the reduced-mass effect of Chapter 25, not a property of (29.1). The window (10%) was wide and registered before the data were read, so the result says that one pair law and one optimisation specification, with no element-specific screening, reproduce the first ten ionisation energies at the few-percent level; it does not say that the mechanism is established. The seat order (which lanes fill first) is a premise of the construction (residual R29.2), no look-elsewhere count was made, and the residuals have a sign pattern (positive for H, He, C, N; negative for Li, Be, B, O, F, Ne) that a mechanism must account for. The measured Rydberg scale remains an explicit anchor because the computed values consume it.

## 29.5 Relaxed and vertical ionisation

Keeping the neutral geometry frozen computes a different process, a vertical ionisation. **Executed (T5).** For $Z=2\ldots10$ the ion energy evaluated at the neutral's relaxed radii was at least the ion's own minimum (within $10^{-9}$ Ry) in every case, as it must be. The relaxation energies (vertical minus adiabatic ionisation) are $1.11$, $0.0001$, $0.25$, $1.04$, $1.62$, $2.24$, $2.96$, $3.59$ and $4.52$ eV for $Z=2\ldots10$. The relaxation is not small against the ionisation energy itself, so the observable protocol decides which construction is appropriate: a photoionisation measurement at fixed geometry and a threshold measurement are different comparisons.

## 29.6 What is not covered

The engine's solver accepts at most ten electrons, so periodic structure beyond neon is not constructed. Exchange-like observables, occupancy sequences beyond the fixed seat order and excitation spectra are not computed. A mode-resolved pair response that predicts both the equilibrium organisation and the dynamical excitation is the determining extension; the pair prices here are static and enter only the energy.

## 29.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (29.1), seats, pair prices | engine's (APS14) | the engine's construction (exact geometry prices; seat order a premise) |
| Ry, $Z$ | `measured::` | MEASURED-INPUT (anchor of the energy scale) |
| neutral and ion minima | Section 29.3 | COMPUTED |
| measured first ionisation energies | Table 29.1 | OBSERVED (compared after the computed values were printed) |
| residuals, relaxation energies | Sections 29.4–29.5 | COMPUTED |

**Residuals.**

* **R29.1 — range.** At most ten electrons; no periodic structure beyond neon.
* **R29.2 — seat order and form.** The seat order, the form (29.1) and the claim that the pair prices are exact geometry are the engine's; they are not derived in this chapter.
* **R29.3 — multiple minima.** The energy has two or more distinct minima for $Z\ge3$; global minimality is established by multi-start search only.
* **R29.4 — sign pattern.** The signs of the residuals in Table 29.1 are not explained.
* **R29.5 — protocol.** Relaxed and vertical ionisation differ by up to $4.5$ eV in the executed range; the comparison protocol has to be fixed per observable.
* **R29.6 — observables beyond ionisation.** Radii, occupancy and excitation are not compared.

## 29.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch29_many_electron_organisation
```

Criteria were registered in `Textbook/validation/ch29_PRE_REGISTRATION.md` before the instrument existed, including the 10% window and the order in which computed and measured values were read. Run 1 failed T1 (a stiff finite difference) and passed T2 only weakly (plain descent; $Z=9$ vacuous). Both were repaired and the weakness recorded as a finding. Run 2 (`ch29_run2_output.txt`) is the run of record and met every criterion.

## 29.9 Exercises and answers

**Exercise 1.** Find the minimum of the one-electron term $1/r^2-2Z/r$.

*Answer.* The derivative $-2/r^3+2Z/r^2=0$ gives $r=1/Z$ and $E=Z^2-2Z^2=-Z^2$.

**Exercise 2.** Derive the pair contribution to the gradient with respect to $\ln r_1$.

*Answer.* $\partial_{\ln r_1}(2w/d)=-2w\,d^{-2}\,\partial_{\ln r_1}d=-2w\,r_1(r_1-r_2\cos\theta)/d^3$ since $\partial_{r_1}d=(r_1-r_2\cos\theta)/d$.

**Exercise 3.** Why must a vertical ion energy be at least the relaxed ion energy?

*Answer.* The relaxed energy is the minimum over radii, and the vertical energy is one value of the same function.

**Exercise 4.** What does the finding of two minima for $Z\ge3$ require of a solver?

*Answer.* Several starting configurations and a record of the lowest converged state; one start can end in a higher basin.

**Exercise 5.** Why does a 10% window passing not establish the mechanism?

*Answer.* The window is wide, the seat order is a premise, and a mechanism must also explain the sign pattern and other observables.

**Exercise 6.** Why is the hydrogen residual $+0.05\%$ not a test of (29.1)?

*Answer.* One electron has no pair term; the residual is the reduced-mass factor, $m_e/m_p=0.0545\%$.

## 29.10 Scope

Established: the one-electron limit of (29.1); that the engine's gradient is the gradient of its energy over 360 configurations; that the converged neutral minima for $Z=1\ldots10$ are stationary, positive definite and, in 40 starts each, the lowest found, with at least two distinct minima for $Z\ge3$; that the first ionisation energies computed under one pair law without element-specific screening lie within 5.25% (mean 1.94%) of measured values, under a window registered beforehand; and the size of the difference between relaxed and vertical ionisation.

Not established: the form and seat order (R29.2), global minimality beyond a multi-start search (R29.3), the sign pattern of the residuals (R29.4), the range beyond ten electrons (R29.1) and any observable other than ionisation (R29.6).

*Where it leads.* Chapter 30 asks whether atomic and nuclear structure correspond, with scale factors predicted and not fitted per observable.
