# Chapter 17 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch17_persistent_electron_circulation.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The hydrogen rung of the engine (`bridge::k_hydrogen = 1/α`, `koppa_hydrogen = r_e = α²a_0`, `atomic::bohr_velocity`, `atomic::bohr_radius`) as a ledger of three radii (a path radius, a boundary radius, an interaction radius) and a family of circulation states that satisfy a phase closure; and the *method* the chapter says a stability statement needs: a fixed equilibrium geometry, a linearisation, and a restoring eigenvalue computed from the same law that fixed the equilibrium. The method is executed on the point-source central kernel $a=-r^{-p}\hat r$, for which a circular route exists for every exponent $p$ and is a stable route only for $p<3$ (radial frequency $\kappa=\sqrt{3-p}\,\omega$), and on the engine's own bridge kernel ($p=2$, `dynamics::step_rk4`). The point-source kernel is a geometry of the route only: the chapter states that the engine does not supply the cross-section, wake or response of the real electron construction (the operator $T[X]$ of the plan), so no stability statement for the real construction is made.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the instrument's central-force integrator at $p=-1$ (force proportional to $r$, the isotropic oscillator) gives a radial frequency $\kappa=2\omega$: $\delta r(t)=\delta\sin(2t)/2$ at $t=0.7,\,1.9,\,3.1$ | $10^{-4}$ of $\delta/2$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | hydrogen rung. (a) $r_e=\alpha\hbar/(m_ec)$ from the stored measured set; (b) $\alpha a_0/\bar\lambda_C=1$ with $\bar\lambda_C=\hbar/(m_ec)$; (c) $r_e/a_0=\alpha^2$ and $\omega=\alpha c/a_0$ equal the engine constant `law_VI::omega_electron_locked`. (a) and (b) are consequences of the CODATA relations among $\alpha$, $a_0$, $m_e$, $\hbar$ and therefore **shared-input**: they test the consistency of the stored set and are not independent evidence | (a),(b) relative $10^{-9}$; (c) relative $10^{-14}$ | yes — a mismatch above CODATA rounding rejects the stored set |
| T2 | the circulation ladder. For $Z=1\ldots5$, $n=1\ldots10$: $v_{Zn}^2r_{Zn}/c^2=Z\,r_e$ (the same boundary length at every state, for $Z=1$), the phase closure $m_ev_{Zn}r_{Zn}=n\hbar$, and the circulation-period ratio $T_{Zn}/T_{11}=n^3/Z^2$ with $T=2\pi r/v$ | relative $10^{-14}$ for the first and third; $10^{-9}$ for the closure (shared-input with T1) | yes |
| T3 | method on the point-source kernel $a=-r^{-p}\hat r$, circular route radius 1 and speed 1 (so $\omega=1$), with a radial perturbation of speed $\delta=10^{-6}$ at fixed angular momentum; RK4, step $10^{-3}$. Linear prediction $\delta r(t)=\delta\sin(\kappa t)/\kappa$ with $\kappa=\sqrt{3-p}$ for $p\in\{1,2,2.9\}$ at $t\in\{1,2,3,5\}$; $p=3$: $\delta r(6)=6\delta$; $p=3.5$: $\delta r(6)=\delta\sinh(\lambda\cdot6)/\lambda$, $\lambda=\sqrt{0.5}$. At $p=2$ the radial and azimuthal frequencies coincide ($\kappa=\omega$: the route closes) | relative to $\delta/\kappa$ (or to the predicted value for $p=3$, $3.5$) within $10^{-4}$ | yes — a stable growth where the prediction is oscillation rejects |
| T4 | the engine's bridge kernel. `circular_pair` with $\varpi=(10^3,\,3\times10^3)$ m at $d=10^9$ m; add to the relative separation a radial speed $u=10^{-6}\omega d$ with the barycentre momentum kept zero; `dynamics::step_rk4` with $T/4000$ steps; the separation obeys $\delta d(t)=(u/\omega)\sin\omega t$ at $t=T/8,\,T/4,\,3T/8,\,T/2$ | within $10^{-4}$ of $u/\omega$ | yes |
| T5 | three radii. $a_0$, $r_e$ and the engine's interaction radius $\sqrt{R_{p,\rm lock}\,r_e}$ (`laws.hpp:514`) are mutually distinct by at least a factor 1.5 pairwise; $a_0/r_e=\alpha^{-2}$ to $10^{-14}$. Values printed | as stated | yes — a pair within a factor 1.5 would remove the distinction the chapter relies on |

Reported, not criteria: the numerical values of the three radii and of $\omega$.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch17_persistent_electron_circulation`

## Record of run 1; correction of the T3 closure check (2026-11-09)

A first build failed on a namespace path (`omega_electron_locked` is in `law_VI::winding`); no run resulted and no criterion changed. Run 1 (`ch17_run1_output.txt`) met every criterion except the closure clause of T3 ($p=2$: radial deviation vanishes at $t=\pi$ and $2\pi$). The instrument evaluated "$t=\pi$" at the nearest multiple of the step $10^{-3}$, $t=3.142$, where the exact linear solution is $\delta\sin(3.142)=-4.07\times10^{-10}$; the reported values ($-4.03\times10^{-10}$ and $-1.85\times10^{-10}$) are that value, so the integration is consistent with the prediction and the check point was misplaced. This is an instrument defect, not a finding on the object. The clause is repaired without changing its criterion: the check integrates with step $\pi/3000$ so that $\pi$ and $2\pi$ are grid points; the tolerance remains $10^{-4}\delta$. Run 2 is the run of record.
