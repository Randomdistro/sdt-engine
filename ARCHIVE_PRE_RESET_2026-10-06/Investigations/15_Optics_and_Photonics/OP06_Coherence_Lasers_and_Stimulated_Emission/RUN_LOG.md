# OP06 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04.

## Pre-Run Commitments — OP06 (written BEFORE first compile/run)

- Prompt completion target: **C** (P1–P3 gated; P4 = coherence time from the same phase walk)
- Physics class hoped: **CONVERGENCE** — pre-declared: lock-vs-independent statistics of summed
  real phasors is CLASSICAL stochastic optics; if the numbers land, that is convergence with the
  classical account, not a native triumph. The genuinely quantum discriminator (antibunching,
  g²(0) < 1) is expected UNREACHABLE by any lock model — to be reported as the honest limit.
- CALIBRATED budget: **0** (rate-equation parameters are declared MODEL-SCALE inputs; the gated
  content is STRUCTURAL — knee at gain = loss, clamping, scaling exponents — not any fitted magnitude)
- Engine namespaces used: `measured::` (context only)
- **Implementation honesty rules (committed):** intensity = mean-square of summed real displacement
  registers over emitters (no Fock states, no boson bunching postulate, no quantised mode);
  stimulated emission = an in-phase re-emission trigger (phase copied), spontaneous = random-phase
  dump; population bookkeeping in continuous intensity units, never photon number.
- Phase thresholds (committed before run):
  - P1: N = 200 emitters, M = 200,000 realisations: g²(0) independent-phase = 2 − 1/N within 1%;
    g²(0) phase-locked (jitter σ = 0.05) within 1% of 1.00
  - P2: steady-state pump sweep: sharp knee; above threshold the emitter-excitation clamps at the
    loss/gain ratio within 1%, and output vs pump is linear (R² > 0.999)
  - P3: phase-diffusion linewidth: log-log slope of Δν vs P over A = 10/20/40/80 = −1 ± 10%;
    simulated diffusion D within ×3 of the kick-ledger R_sp/(2A²). The ABSOLUTE Schawlow–Townes
    prefactor πhν(Δν_c)²/P requires the hν emission quantum — the FLM12/ℏ-entry root; it is a
    comparison note, NOT a gate (gating it would smuggle the ℏ debt in as if paid).
  - P4: field autocorrelation e-fold time = 2/D within 10% ⇒ coherence length c·τ_c ∝ P recovered
- §G mirror check: no gate imports boson statistics as axiom OR forbids it as data; g² = 2/1 are
  measured anchors (HBT/laser interferometry). Antibunching is logged as a measured fact the lock
  model must be TESTED against later (single-vortex dead-time), not legislated either way.
- Forbidden retroactive changes: writing the bosonic coherent/thermal g² result and calling it
  derived; quantising the cavity; tuning the inversion to force a knee; tolerance widening.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Phase | Result | Notes (from `results.txt`, run 2026-07-04, exit 0) |
|-------|--------|-------|
| P1 | **PASS-GATE** | g²(0): independent 2.0000 (target 2−1/N = 1.9950, dev 0.25%); locked 1.0000 |
| P2 | **PASS-GATE** | n₂ clamps at κ/G to 0.010% at 2× threshold; slope R² = 1.000000; knee contrast ×1504 |
| P3 | **PASS-GATE (exponent) / prefactor NOT gated (committed)** | exponent −0.992 (gate −1±0.1); D_sim vs kick-ledger ×0.94–0.99; absolute ST prefactor = FLM12/ℏ-entry debt |
| P4 | **PASS-GATE** | e-fold lag 7865 vs 2/D = 8425 ticks (ratio 0.934, gate ±10%) |
