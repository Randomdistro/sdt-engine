# RUN_LOG — NP10: Alpha Binding from Tetrahedral Geometry (NP17 premise)

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only.

## Pre-Run Commitments — NP10

- Prompt completion target: B
- Physics class hoped: NATIVE; honest floor accepted: OPEN (expected: the pure-electrostatic
  number FAILS, per NP17's declared PENDING — the deliverable is then the *measured size and
  scaling* of the missing lock term, not a fake pass)
- CALIBRATED budget: **0**
- Engine namespaces: `measured`, `coulomb_identity`, `nuclear` (R_He_predicted)

## Premise correction (per 2026-07-03 PROMPT note, applied BEFORE running)

NP09's scalar-occlusion E_pn FAILED (−97.3%); FLM12-D1 killed the linear volume price.
The PROMPT's Step-2 bond formula (4·E_pn + E_nn + (E_pp − E_C) with occlusion E's) is
therefore dead as written. Substituted premise: **NP17 shared-electron Coulomb well** —
alpha = 4p + 2e, E = −Σ q_i q_j αℏc/r_ij, no fitted energy scale.

## Committed configurations (geometry fixed BEFORE any energy is computed)

1. **Alpha, NP17-exact (continuity):** 4 protons at regular tetrahedron, **edge a = 2R_p**
   (boundary contact); 2 electrons at midpoints of two OPPOSITE edges (the interlocked-
   deuteron reading). This is byte-for-byte NP17's committed configuration.
2. **Alpha, D-spaced variant:** same shape, edge a = D = 2R_p + R_p/3 (deuteron bond length).
3. **Triton, chain (committed):** p–e–p–e–p collinear, adjacent p–p spacing D, electrons at
   bond midpoints (two NP17 deuteron bonds sharing the middle proton).
4. **Triton, triangle variant:** 3 protons equilateral edge D, electrons at two edge midpoints.

No other configurations will be tried after seeing energies (no geometry fishing).

## Gates (committed now)

- **G1 — headline:** |E(α, config 1) − 28.296|/28.296 ≤ 20% → else FAIL→OPEN with the lock
  remainder R_lock = 28.296 − E quantified. (Expected FAIL ≈ −84% per NP17; committed anyway,
  not softened.)
- **G2 — size:** |2R_p − R_He_meas|/R_He_meas ≤ **1% (blind bar; NOT the known 0.43%)**.
- **G3 — ratio structure:** B_α/B_t predicted vs measured 28.296/8.482 = 3.336, gate ±20%,
  scored for BOTH consistent pairings (config 1 vs 3; config 2 vs 3/4). Purpose: decide
  whether the missing lock term is a COMMON multiplicative factor (ratio would pass) or
  coordination-dependent (ratio fails) — either outcome is information, only one is a pass.
- **G4 — μ_α = 0:** qualitative pairing-cancellation statement; class ceiling DEGENERATE
  (declared now: every model predicts 0 for spin-0).
- **G5 — inversion (record):** edge required for 28.296 MeV electrostatically; if < 2R_p,
  unphysical → confirms the lock remainder is real, not a spacing choice.

## Forbidden retroactive changes
New electron placements after seeing energies; widening 20%/1%; selling G2 (an existing
laws.hpp result, class C-flagged) as a new NP10 discovery; occlusion-route resurrection.

## Planned outputs
`np10_alpha_binding.cpp` → MSVC → `np10_results.txt` (redirected) → `NP10_VERDICT.md`.
