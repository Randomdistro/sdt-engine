# RUN_LOG — PM04 (Plasma Oscillations and Debye Shielding)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Written BEFORE any code.

## Pre-Run Commitments — PM04

- Prompt completion target: **C** (the prompt expects C; the restoring GAIN is α-anchored, see below).
- Physics class hoped: NATIVE for the slab mechanics (SHM from pairwise occlusion, no E field);
  CONVERGENCE for the gain (charge coupling enters as A = αℏc = `coulomb_identity::k_e_e2`, which
  laws.hpp itself labels class F / definitional — so the "native gain = 4παℏc" is a RE-EXPRESSION
  through the permitted α anchor, not a derivation of e²/ε₀. Committed up front.)
- CALIBRATED budget: 0. Pairwise force A/r² from Law III (engine `F_coulomb` structure); α, ℏ, c,
  k_B, m_e from `measured`. e and ε₀ appear ONLY on final [IMPORTED] comparison lines.
- Method: 1-D electrostatic sheet model (real N-body dynamics, evolved arrays — the PM03 sin of
  never-evolving is explicitly forbidden here). Sheet–sheet force = 2πAσ_s per carrier (distance-
  independent), derived by integrating the Law-III 1/r² occlusion over an infinite sheet; ion
  background immobile. TD02 thermal ensemble supplies Maxwellian initial velocities.

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | slab/sheet SHM at ω_p | measured ring frequency vs ω_p = √(4πA n/m_e) < 1%; restoring linear (SHM, stable amplitude) |
| P2 | Debye screening | analytic: λ_D = √(k_B T/(4πA n)) ≡ √(ε₀k_BT/ne²) (identity, machine) — form <2% trivially, flagged. Simulation: time-averaged excess-electron profile around a q_t=5 test sheet decays exponentially; fitted e-folding within **15%** of λ_D (1-D PIC noise bracket, committed now); fit window 0.5–3 λ_D |
| P3 | Bohm–Gross coefficient | warm modes kλ_D ≈ 0.19, 0.31: fit ω² = ω_p²(1 + C k²λ_D²) → **C ∈ [2,4]** (sim); analytic claim: C = 3 = (d+2)/d at d=1 (1-D adiabatic index), stated as the dimensionality origin — FD05 handshake (1/3 = 1/d at d=3) related-but-distinct |
| P4 | upper hybrid | slab restoring ⊕ unsigned Coriolis turning (PM01 channel, HG-1 disclosed): measured ω vs √(ω_p²+Ω²) < 0.5% for 3 values of Ω |

### Forbidden retroactive changes
Import e²/ε₀m or a primitive E into the restoring chain then claim the gain native; widen the 15%
Debye bracket or the C window; magnetons anywhere; static-array IDENTITY-PASS (arrays must evolve).

## Run record (filled after execution)
- See `pm04_results.txt`, `PM04_VERDICT.md`.

## ADJ-1/ADJ-2 (numerics, disclosed; gates unchanged)
- ADJ-1: P2 bins 2λ_D → 0.25λ_D (run-1 fit was NaN on 2 bins); P3 zero-crossing estimator →
  Hann-windowed DFT peak, seed amplitude 0.15→0.4Δ (noise-biased estimator).
- ADJ-2: P2 dt halved, folded two-sided profile, window [0.5,2.5]λ_D, sampled-T instrumented.

## P2 absolute gate: FAILED — recorded, not retried
Run 3: λ_fit = 3.53e-5 vs λ_D = 2.18e-5 (+61.8%; gate 15%). Instrumentation rules out heating
(T_meas = 0.954e5 K) and tail-selection bias (all 8 bins positive). The committed gate assumed the
thermalized Boltzmann screening coefficient; a collisionless 1-D sheet plasma with a suddenly
introduced test sheet phase-mixes to a WIDER (≈1.66 λ_D) cloud. FAIL stands as the run-3 number.

## Phase split P2b (declared 2026-07-04 BEFORE the run, after P2 fail)
Scaling test of the committed form λ ∝ √(T/n): second run at T₂ = 4×10⁵ K (all else identical);
gate: λ_fit(T₂)/λ_fit(T₁) = √(T₂/T₁) = 2.0 ± 15%. One run, no rebracketing after seeing the number.

## P2b: FAILED (ratio 1.071 vs 2.0±15%) — recorded
Fitted slopes are window-dependent (1.66 λ_D at T₁ vs 0.87 λ_D at T₂): collisionless profile is not
a single exponential. Root (premise, §D-4): 1-D equal-mass sheets have NO velocity-relaxation
channel (crossings = pass-throughs), so the Boltzmann screening response the Debye formula assumes
CANNOT form in this apparatus. Apparatus error, not yet a claim kill.

## Phase P2c (declared 2026-07-04 BEFORE the run — Closure Principle: add the missing loop)
Same as P2a but with a Langevin thermostat making TD02's thermal ensemble real: γ_L = 0.05 ω_p,
bath T = 1e5 K. Gates (committed): profile exponential over [0.5,2.5]λ_D; λ_fit within 15% of λ_D.
ONE run; PASS or FAIL recorded as-is. If PASS: Debye screening = thermal-ensemble result (TD02 input
essential); collisionless anomaly logged as generative finding. If FAIL: KILL H2 per pivot.
