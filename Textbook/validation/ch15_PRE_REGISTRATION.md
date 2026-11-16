# Chapter 15 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch15_energy_and_momentum_balance.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. (a) The ledger of a finite control region for content on the TOY relay chain of Chapter 14: content balance with boundary flux, and a momentum balance in which the recoil of the scatterer is computed from the reversal events and then omitted to show the residual; (b) the engine's koppa-weighted body ledger in `sdt/dynamics.hpp` (the bridge kernel $a_i=c^2\sum_j\varpi_j\vec r_{ji}/|r_{ji}|^3$, invariants weighted by the source length $\varpi_i$, i.e. koppa): conservation of weighted momentum and angular momentum, the order of convergence of the velocity-Verlet and RK4 steps in the energy invariant, the Lagrange equilateral configuration, and the refusal of a step at contact; (c) the recoil of an emitter with a dipole emission pattern. A momentum ledger in which the medium's momentum is *defined* as the negative of the body's is an accounting identity and not a test (CONSTRUCTION); the tests below say what each ledger does and does not include.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | `circular_pair(\varpi_1,\varpi_2,d)` with $\varpi_1=10^3$ m, $\varpi_2=3\times10^3$ m, $d=10^9$ m integrated one period $T=2\pi/\omega$, $\omega=c\sqrt{(\varpi_1+\varpi_2)/d^3}$, by RK4 with 4000 steps returns each body to its start | position error $<10^{-6}d$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | chain ledger. For random initial content on a chain of 200 cells (fixed generator), $s=0.3$, region $V=\{50,\ldots,149\}$, 100 counts: $\Delta U_V=\text{inflow}-\text{outflow}$ across the two interfaces at every count, with the interface flux from the update rule. Momentum content $P=\sum(R_i-L_i)$: $\Delta P_V+\text{recoil}_V=\text{net momentum flux}$ with the recoil $=\sum_{i\in V}2s(R_i-L_i)$ computed from the reversals; omitting the recoil leaves a residual equal to it | content closure $\le10^{-14}$ per count; with recoil $\le10^{-14}$; the omitted-recoil residual equals the recoil to $10^{-14}$ and is non-zero | yes — a missing interface term rejects |
| T2 | engine ledger. Two bodies $\varpi=(10^3,3\times10^3)$ m at $d=10^9$ m on `circular_pair`, one orbit with velocity-Verlet and with RK4: the weighted momentum $\sum\varpi_i\vec v_i$ stays below $10^{-12}$ of $\varpi_{\rm tot}v_{\max}$ and the weighted angular momentum below $10^{-9}$ relative drift. Energy error at the end of one orbit with $N=200,400,800$ steps per orbit: the observed order $\log_2(\epsilon_N/\epsilon_{2N})$ lies in $[1.8,2.2]$ for Verlet and $[3.7,4.3]$ for RK4 | as stated | yes — a first-order step or a broken pairing rejects |
| T3 | Lagrange configuration. `equilateral_three` with equal $\varpi=10^3$ m and side $10^9$ m integrated a quarter period by RK4 (2000 steps): the three side lengths stay equal to $10^{-8}$ relative and the weighted momentum stays zero | as stated | yes |
| T4 | contact. Two bodies with collision radius $10^6$ m each, released at rest from $d=10^8$ m with $\varpi=10^3$ m each, stepped by Verlet with $dt=T_{\rm ff}/10^{4}$ ($T_{\rm ff}$ the radial free-fall scale $d^{3/2}/(c\sqrt{2\varpi_{\rm tot}})$): the engine returns `collision` at some step; the state is not modified by the refused step; the last accepted separation exceeds the contact distance $2\times10^6$ m | as stated | yes |
| T5 | dipole emitter. A body radiating luminosity $\mathcal L$ with angular pattern $\propto1+\varepsilon\mu$ has net momentum flux $\varepsilon\mathcal L/(3c)$, and $0$ for $\varepsilon=0$ (an isotropic emitter carries energy without recoil): by quadrature, $\varepsilon\in\{0,10^{-3},0.5,1\}$ | within $10^{-13}$ of $\varepsilon/3$ in units of $\mathcal L/c$ | yes |

Reported, not criteria: the energy errors and observed orders; the separation at refusal.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch15_energy_and_momentum_balance`

## Record of run 1; corrections to T1 and T2 (2026-11-09)

Run 1 (`ch15_run1_output.txt`) met V1, T3, T4, T5, the momentum clauses of T1 and the momentum/angular-momentum clauses of T2, and failed three clauses.

1. **T1 content closure** returned $1.33\times10^{-13}$ against the registered absolute $10^{-14}$. The summed content of the region is of order 100 (one unit in the last place near $1.4\times10^{-14}$), so an absolute tolerance of $10^{-14}$ was registered without regard to the size of the sum; the momentum sum is signed and small and met it. The clause is corrected to a residual **relative to the region's content at the start of the count**, $\le10^{-14}$ (observed relative size $1.3\times10^{-15}$ is to be read from the rerun, not assumed). The mechanism being tested (the interface terms) is unchanged.
2. **T2 observed orders** failed both ranges. The Verlet energy error after one full circular orbit was $1.6\times10^{-14},\,5.8\times10^{-16},\,1.2\times10^{-15}$ for $N=200,400,800$, i.e. at the round-off floor, and RK4 gave order $5.0$ (not $4$). A circular orbit is a symmetric trajectory on which the leading error terms of the energy cancel at a full period; it is not a generic probe of the order of a step. The registered ranges were stated for a generic orbit, and the test was placed on a symmetric one. The circular-orbit energy errors are kept as reported values. The order criterion is moved to a new test registered here, before it is coded:

**T2(c), eccentric orbit.** Bodies from `circular_pair($\varpi_1=10^3$ m, $\varpi_2=3\times10^3$ m, $d=10^9$ m)` with both velocities multiplied by $0.7$ (the barycentre momentum remains zero; apoapsis at $d$, eccentricity $0.51$). Period $T_e=2\pi\sqrt{a^3/(c^2\varpi_{\rm tot})}$ with $a=d/(2-0.49)$. For $N\in\{400,800,1600\}$ steps per $T_e$ the quantity $\epsilon_N=\max_{\text{steps}}\lvert E-E_0\rvert/\lvert E_0\rvert$ over one period is recorded. Criteria: observed order $\log_2(\epsilon_N/\epsilon_{2N})$ lies in $[1.8,2.2]$ for velocity-Verlet and in $[3.5,4.5]$ for RK4, for both successive pairs. Rejection class: a first-order step, or a kernel inconsistent with the invariant, falls outside. The registered ranges of the original T2 order clause are withdrawn in favour of this one. The weighted momentum and angular-momentum clauses of T2 are unchanged. Run 2 is intended as the run of record.
