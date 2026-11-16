# RUN_LOG — NP08: Triple-Alpha Rate from Geometric Packing

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only.

## Pre-Run Commitments — NP08

- Prompt completion target: B (honest floor C if the core phase defers)
- Physics class hoped: NATIVE; honest floor accepted: OPEN/DEFERRED
- CALIBRATED budget: **0**
- Engine namespaces: `measured` (B_deuteron, B_alpha, R_He, R_p), `coulomb_identity` (αℏc),
  nuclear grammar `n_t = A−2Z`, `n_d = 3Z−A−2`
- Typed OBSERVED anchors (AME2020, flagged): B(Be-8) = 56.49951 MeV, B(C-12) = 92.161753 MeV,
  E(Hoyle) = 7.65407 MeV above C-12 g.s.

## Premise correction (per 2026-07-03 PROMPT note, applied BEFORE running)

NP09's scalar occlusion FAILED (−97.3%); FLM12-D1 killed the linear volume price (34×).
The only *paid* SDT nuclear binding mechanism is **NP17's shared-electron Coulomb well**
(deuteron PASS at −1.06%; **alpha and heavier: PENDING** — electrostatics under-binds ~6×,
needs the tetrahedral-lock/occlusion term). Consequence declared now: a knob-free signed
computation of the tetrahedral-closure energy (the 7.654 MeV target) requires exactly the
NP17-PENDING magnitude machinery. If P2 confirms that, the phase is **DEFERRED (dependency:
NP17-PENDING lock term)** per the pivot table — NOT plugged, NOT retro-passed.

## Committed phases + decision rules

- **P0 (exact integers):** grammar decomposition of Be-8 and C-12 from the constitutional
  formulas. NOTE, written before running: the PROMPT asserts "Be-8 grammar: 2α + 0d".
  The constitutional formulas give `n_d(Be-8) = 3·4−8−2 = 2` → **α + 2d**, which CONTRADICTS
  the PROMPT. The formulas are constitutional; the PROMPT text loses. This finding stands
  regardless of any energy number.
- **P1 (grammar ledger, IDENTITY-class bookkeeping, labelled as such):** inter-block scaffold
  binding required = B(nucleus) − ΣB(blocks) for Be-8 (α+2d) and C-12 (α+4d); packing
  comparison α+n_d·d vs all-α at fixed A=8, 12. Checks (exact algebra, not predictions):
  Q(3α→C-12) = B(C12) − 3B(α); Be-8 unbound margin = B(Be8) − 2B(α).
- **P2 (native attempt at the Hoyle target, gate 20% of 7.654 MeV — committed here):**
  boundary-contact tetrahedral geometry (4 d at vertices, α at centre; centre-to-vertex
  = R_He + D/2 with D = NP17's deuteron length 2R_p + R_p/3; edge = r_cv·√(8/3)).
  Computable knob-free TODAY: the point-Coulomb repulsion ledger of that configuration.
  NOT computable knob-free: the attractive shared-electron side (electron count/placement
  between d-blocks and α core is NP17-PENDING). Decision rule: if the attractive side
  cannot be written without inventing electron placements, P2 = **DEFERRED**, and NO number
  is scored against the 20% gate. Guessing placements to reach 7.654 is forbidden.
- **P3 (stability directions, sign-only):** does the ledger give (i) Be-8 → 2α downhill and
  (ii) 3α → C-12 downhill, with no sign choices? (Uses measured BEs → labelled
  ledger-consistency, not prediction.)

## Forbidden retroactive changes
Inventing electron placements/counts to force 7.654; widening 20%; selling P1/P3 ledger
identities as predictions; occlusion-route resurrection without new physics.

## Planned outputs
`np08_triple_alpha.cpp` → MSVC → `np08_results.txt` (redirected) → `NP08_VERDICT.md`.
