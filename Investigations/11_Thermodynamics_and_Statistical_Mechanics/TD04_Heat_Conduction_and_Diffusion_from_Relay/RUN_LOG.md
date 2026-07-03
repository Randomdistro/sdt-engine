# RUN_LOG — TD04 Heat Conduction and Diffusion from Relay

**Executor:** J. C. Harvey, Melbourne · 2026-07-03
**Committed BEFORE first compile/run. No threshold below may be widened after a number is seen.**

## Pre-Run Commitments — TD04

- Prompt completion target: **C** (prompt's own honest expected landing)
- Physics class hoped: CONVERGENCE (pre-registered: the λ_mfp·v random-walk machinery is
  textbook kinetic theory; SDT relabels carriers as relay throughput — unless a lattice-specific
  step appears, class is CONVERGENCE/NULL-SDT for the mechanism)
- CALIBRATED budget: 0 in the native chain. Declared upfront: the Milne slip coefficient
  z0 = 0.7104 (boundary-layer transport theory) is quoted for the slab comparison as a KNOWN
  finite-size correction, not fitted; the gate is set wide enough (5%) that it is not load-bearing.
- Engine namespaces: `measured::k_B` (+ measured gas properties as OBSERVED inputs in P4).
- Units: v = 1, λ = 1, k_B = 1 internally; all results pure numbers.

## Phase thresholds (committed)

- **P1 (random-walk coefficient):** 3D carriers, fixed speed v, exponential free paths mean λ,
  isotropic scattering. Gate: fitted D from late-time MSD slope satisfies |D/(vλ/3) − 1| < 2%.
- **P2 (diffusion equation):** stripe release; variance grows linearly, fitted α = vλ/3 within
  2%; position kurtosis → 3.0 ± 0.1 (Gaussian profile). No free knob.
- **P3 (Fourier slab):** L = 100λ, diffuse (cosine-law) walls at T_h = 1.1, T_c = 0.9 (ε/k_B units),
  carrier energy tag = k_B·T of last wall. Gate: k_fit = J·L_eff/ΔT within 5% of k_th = ⅓ n v λ k_B,
  with L_eff = L + 2·z0·λ (slip declared above; at L=100λ it is a 1.4% effect).
  Linearity: flux at ΔT/2 scales by 0.5 within 3%.
- **P4 (materials + √T):**
  - Argon 300 K, 1 atm: inputs OBSERVED (d = 3.40e-10 m LJ diameter, m = 39.95 u,
    k_measured = 0.0177 W/m·K). Gate per prompt: k_pred within factor **2** = PASS; between
    2 and 3 = FAIL reported honestly (pivot: grade D on magnitude, keep mechanism).
  - Air 300 K: same procedure (d = 3.7e-10 m, c_v = 5/2 k_B diatomic, k_measured = 0.026 W/m·K).
  - Copper: **DEFERRED** — a native electron-transport channel requires degenerate carrier
    statistics SDT has not derived; borrowing v_F and λ_e from Fermi-surface data would be
    BORROW-SMUGGLE. Declared OPEN, not simulated.
  - √T law: slab flux at 4T vs T: ratio 2.0 ± 3% (v ∝ √T at fixed λ — the lattice fixed-λ limit,
    same caveat as FD02: real gases at fixed P have λ(T), Sutherland ~0.7).
- **P5 (Wiedemann–Franz):** NO simulation. Committed statement: one-channel classical relay
  carriers give L = (3/2)(k_B/e)² = 1.11e-8 WΩK⁻² vs measured 2.44e-8 (ratio 2.2). The measured
  Lorenz number needs degenerate statistics (π²/3) that SDT has not derived natively →
  sub-claim graded **D/OPEN**. Constancy-across-metals cannot be tested natively (no
  metal-specific native input exists). This is recorded as a fired falsifier T3 unless the
  classical value lands within 10% (it will not — stated before the run).

## Decision rules

- Gate misses → pivot table PROMPT.md §⑩ (finer numerics first), never widen.
- Physics class by the standard question: which step would break on a non-SDT substrate?

## Run record

- [x] compile (MSVC /std:c++20 /O2) — clean
- [x] RUN 1: exit 0 (core). P1 1.05% PASS · P2 worst 1.99% PASS (by 0.01% — recorded) ·
      P3 0.34% PASS · P4 argon ×3.30, air ×2.96 **FAIL as committed, reported** ·
      P5 fired as declared (classical L low ×2.19) → OPEN. No re-runs, no adjustments.
- [x] verdict: TD04_VERDICT.md — Prompt C · Physics CONVERGENCE · P4 failure run to ground
      (shared root with FD02's ×1.44: single-speed coarse-graining drops the speed–flux
      correlation; PARTIAL recovery route named, owed)
