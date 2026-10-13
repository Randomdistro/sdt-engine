# RUN_LOG — QM07 Spin & Stern–Gerlach from Handedness

**J. C. Harvey, Melbourne — 2026-07-04.** Executor: HUNTER-disciplined agent run.
Written BEFORE any tool code, per `PROMPT_EXECUTION_PROTOCOL.md`.

## Pre-Run Commitments — QM07

- Prompt completion target: **B** (A does NOT require the g-number; g is OPEN per the prompt's
  own engine-fact correction — deferred to B17, never cited from W+1, no μ_B anywhere).
- Physics class hoped: NATIVE on two-valuedness/two-spot; OPEN expected on sequential-SG cos²(θ/2).
- CALIBRATED budget: 0. No μ_B, no magnetons, no W+1 g-factor citation, no Pauli algebra, no spin
  operator. The observed sequential-SG transmission curve cos²(θ/2) is an **OBSERVED data anchor**
  (measured beam fractions), used as comparison target and — in one clearly-labelled probe — as a
  diagnostic weighting (per HUNTER §B, the QM05 probe pattern).
- §G mirror at hunt start: faith ledger — accepted: binary circulation handedness (EMC03, native
  structure); differential occlusion push ∝ handedness × gradient (PM01 mechanism, structural).
  Gatekeeper — no gate below enforces a rival axiom; the discriminator (no middle spot) is the
  measured SG 1922 result (data anchor).

## Phase thresholds (committed before run)

N = 2×10⁵ vortices per condition; MC seed 23.

- **P1/P3 (two spots, no middle — the discriminator):** deflection = η·G·L with η = ±1 binary +
  transverse thermal smear σ = (G·L)/6. Gates: (a) centre band (|x| < G·L/2) occupancy < 1%;
  (b) two peaks equal-weight within 4σ statistical; (c) peak separation ∝ gradient to 1% across
  G ∈ {1, 2, 4} (arb. units — magnitudes are NOT calibrated to any magneton; only linearity and
  two-valuedness are claimed). RIVAL comparison column (classical continuous dipole, μcosθ with
  isotropic θ): centre-band occupancy expected ≫ 30% — the observed two-spot data kills the
  continuous rival, not SDT.
- **P2 (moment magnitude / g):** NOT numerically claimed. Binary moment (two signs, equal
  magnitude) is structural from P1. The g **number** stays OPEN → engine benchmark B17 owns the
  measured 2.00232 comparison. Pre-declared: no attempt will be made here.
- **P4 (sequential SG):** two machineries, one probe:
  - **M1 (native candidate — undisturbed hidden vector):** vortices passing filter A retain their
    handedness vector; pass B iff λ·b̂ > 0. Committed analytic expectation: triangle law 1 − θ/π.
    Gate: RMS vs the OBSERVED cos²(θ/2) over θ ∈ {0,15,…,180}° — **expected to FAIL the <2%
    prompt gate** (expected RMS ≈ 7%); the failure is the honest result and fires the prompt's T3.
  - **M2 (diagnostic probe, labelled — NOT a derivation):** re-preparation residence density
    ∝ cos(angle to filter axis) on the passed hemisphere. Committed: reproduces cos²(θ/2) to
    RMS < 0.5% (MC noise). Purpose: NAME the machinery debt — the cos-weighted re-preparation
    density is exactly the residence law (RESIDENCE-LAW root); nothing here derives it.
- Forbidden: fitting a re-preparation density to pass the gate and calling it native; citing g
  from W+1; importing μ_B; suppressing the M1 failure.

## Run record

- 2026-07-04: commitments frozen. Tool `qm07_sg_handedness.py` written after this block.
  → `qm07_results.txt` (real stdout), `QM07_VERDICT.md`.
