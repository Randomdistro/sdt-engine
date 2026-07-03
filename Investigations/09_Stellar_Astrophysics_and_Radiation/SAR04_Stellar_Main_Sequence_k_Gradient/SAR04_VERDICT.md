# SAR04 — Verdict: Stellar Main Sequence from k-Gradient

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03.
**Tool:** `sar04_ms_k_gradient.cpp` → `results.txt`. Gates pre-committed in `RUN_LOG.md`. Data: 16 canonical MS calibration bins (ADJ-001 — GAIA/Torres not in repo; values memory-transcribed, verify before publication; completion capped at C by this deviation).

## Dual verdict

**Prompt completion: C** (all four tests run; the ≥50-star criterion not met — ADJ-001).
**Physics class: CONVERGENCE** (ordering) / **KILLED as stated** (L∝M^3.5 emergence claim).

## The numbers

| Test (pre-committed gate) | Result | Grade |
|---|---|---|
| T1 monotonic k-sequence, Spearman ≥ 0.90 | ρ(k,T_eff) = −0.982 (4 local inversions of 15 steps) | **PASS** (rank-monotonic, not strictly) |
| T2 L(k) power law, R² ≥ 0.90 | L ∝ k^−22.0, R² = 0.936 | PASS — **slope MEASURED, not derived** |
| T3 solar point within 3% | k(G2V) = 686.4 vs engine 686.3 → 0.01% | **PASS** |
| T4 L∝M^3.5 emerges from k alone | a_implied = n(β−1)/2 = 3.36 vs table 3.55 — but only by importing empirical R∝M^0.69 | **NOT EMERGENT** |

k convention: engine v_circ (k_Sun=686.3), not the prompt's own escape-velocity formula, which
contradicts its own solar value (would give 485) — prompt inconsistency flagged in RUN_LOG.

## What this settles

1. **The MS is a k-ordered sequence, but a feeble one.** k spans only 324→778 (×2.4) while L
   spans 10^8. The k-axis compresses the entire main sequence into a factor-2.4 window with
   local inversions (F0/F5, G2/G8): k is a *label*, not a *lever*. Hot O stars = low k (strong
   convergence), M dwarfs = high k — the prompt's qualitative picture holds, its O-star guess
   (k≈300) was even right (324).
2. **The exponent −22 is phenomenology.** Nothing in the k-hierarchy predicts it, and at this
   steepness tiny k errors swamp L — the fit is real (R²=0.94) but structurally empty.
3. **L∝M^3.5 does NOT come from k.** Algebra makes it explicit: k² = (R/M)·k☉², so L(k) plus
   L(M) jointly *determine* the empirical R(M) (β=0.69); the k-route "reproduces" a=3.4 only
   by consuming that same empirical R(M). Circular by construction — k alone cannot fix L(M).
4. Bonus column earned: per-star pressure domains (law_II) — O5V dominion 1.9e7 AU (~90 pc),
   M5V 1850 AU. Untested against Roche lobes (no binary data in repo) — stated, not sold.

## §D — Seven questions (on the KILLED T4 / capped completion)

1. **Why fail?** k ≡ c/v_circ is a function of M/R only — one dimensionless ratio. L requires
   an absolute scale; no map from a pure ratio to 8 decades of luminosity exists without a
   second coordinate.
4. **Errored premise?** "The main sequence is a *one-parameter* k-sequence." The MS is (at
   least) a two-parameter family; projecting onto k discards the scale coordinate.
5. **What freedom corrects it?** The koppa LENGTH ϟ = v²R/c² (bridge::koppa) — dimensional,
   scale-carrying, native. (k, ϟ) jointly carry (M, R) with no G; an L(ϟ) or L(k,ϟ) law is the
   honest successor hypothesis. NOT run here (not pre-registered — running it post-hoc on this
   table would be a fished recovery; it needs its own pre-committed prompt).
6. **Native or knob?** Native — ϟ is already in the engine and is GOM14's working variable
   (mass-free koppa-density, 693 systems).
7. **Cascade?** Partial — shares the "which koppa variable carries the physics" root with
   GOM14; otherwise an independent premise error (single-coordinate compression).

**Recovery: PARTIAL** — premise error named (one-parameter projection), native freedom named
(ϟ), not yet run under pre-commitment.

**earned:** solar point 0.01%; rank-ordering ρ=−0.98 confirmed with honest ×2.4-span caveat; T4 circularity made explicit (a = n(β−1)/2 decomposition); prompt's k-formula inconsistency caught.
**owed:** GAIA/Torres real-star rerun (≥50 stars); L(ϟ) successor prompt; Roche-lobe vs r_domain test (needs binary data).

> **Prompt completion C · Physics class CONVERGENCE (k-ordering) / KILLED (L∝M^3.5-from-k claim) · Recovery PARTIAL · Cascade root: koppa-variable selection (shared with GOM14), else none.**
