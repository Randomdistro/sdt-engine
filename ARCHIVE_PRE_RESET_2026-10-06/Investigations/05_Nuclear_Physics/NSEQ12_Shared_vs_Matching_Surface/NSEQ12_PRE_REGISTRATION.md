# NSEQ12 Pre-registration — Shared vs matching surface partners

**Date:** 2026-08-11  
**Parents:** NSEQ11 (Shared ∪ K₂,₂ matching); NSEQ07 (doublet = QQ ⊕ surface)  
**Forbidden:** C3 gates; energy fits; amending hypotheses after stdout  
**Objective:** Test whether Shared QQ contacts and matching (private) QQ
contacts pair with **different** surface-edge species under the radial-doublet
map — a geometric discriminator with no MeV.

## Frozen inputs

- Polar branches `triangles` / `hexagon` (NSEQ05/08).  
- `Shared = QQ_tri ∩ QQ_hex` (4 edges).  
- `K₂,₂` matchings = Priv_tri / Priv_hex (NSEQ11).  
- Surface `S = TQ ∪ TT` (24+12).  
- Radial doublet: two edges share an oriented midpoint ray (NSEQ06/07).  
  NSEQ07: each doublet is exactly one QQ + one surface edge.

## Hypotheses (committed)

**H1 — Shared → T−T.** For both branches, every Shared QQ edge that
participates in a radial doublet does so with a **T−T** surface partner.

**H2 — Matching → T−Q.** For both branches, every private/matching QQ edge
that participates in a radial doublet does so with a **T−Q** surface partner.

**H3 — Exhaustion.** All 6 QQ edges of each branch appear in exactly one
doublet (NSEQ06 count); hence H1 covers 4 Shared and H2 covers 2 matching
per branch.

**H4 — No C3 / no energy.** Instrument builders do not call C3 orbit helpers;
no AME / MeV.

## Decision

| Gate | SURVIVE | EXCLUDE |
|---|---|---|
| C1 (H3) | 6 QQ doublets/branch; 4 Shared + 2 matching | else EXCLUDE |
| C2 (H1) | all Shared doublet partners are T−T (both branches) | else EXCLUDE |
| C3 (H2) | all matching doublet partners are T−Q (both branches) | else EXCLUDE |
| C4 (H4) | no C3 in builder `co_names` | else EXCLUDE |

Headline `SHARED_TT__MATCHING_TQ_SURVIVES` iff C1–C4 pass.  
Any EXCLUDE is terminal for this pre-reg — **no amendment cycle**.

## Non-goals

Occupation energy; capacity changes; which axis is “the” rod axis beyond
NSEQ11’s `{x,z}` K₂,₂.
