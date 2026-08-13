# NSEQ13 Pre-registration — TT partner flip-axis vs K₂,₂ frame

**Date:** 2026-08-12  
**Parents:** NSEQ12 EXCLUDED (all QQ doublets → TT); NSEQ11 K₂,₂({±x},{±z})  
**Forbidden:** C3 gates; MeV; amending hypotheses after stdout  
**Objective:** Inside the universal TT partner class, test whether Shared vs
matching QQ contacts are distinguished by **which cube coordinate the TT
edge flips**, relative to the NSEQ11 matching frame `{x,z}`.

## Motivation (not a free fit)

NSEQ11: matching lives on `K₂,₂({±x},{±z})`; **y** is the spectator axis.  
NSEQ12: every QQ radial doublet pairs with a Hamming-1 T−T edge (one sign
flip among the eight cube corners).

Committed split:

- **Shared** (fixed seating) ↔ TT partner flips the **spectator** axis `y`  
- **Matching** (around choice on `{x,z}`) ↔ TT partner flips an axis in
  `{x,z}`

## Frozen inputs

- Branches / Shared / Priv from NSEQ11.  
- Surface S = TQ ∪ TT; radial doublets as NSEQ07/12.  
- Matching frame `M = {x,z}`; spectator `s = y` (locked to NSEQ11 result —
  not re-searched).

## Hypotheses

**H1 — Shared flips spectator.** For both branches, every Shared QQ’s TT
doublet partner flips coordinate **y** only.

**H2 — Matching flips frame axis.** For both branches, every matching QQ’s
TT doublet partner flips **x** or **z** (never y).

**H3 — Exhaustion.** 6 QQ doublets/branch; 4 Shared + 2 matching (NSEQ12-C1).

**H4 — No C3 / no MeV.** Builder `co_names` free of C3 orbit helpers; no AME.

## Decision

| Gate | SURVIVE | EXCLUDE |
|---|---|---|
| C1 (H3) | 6/6 QQ partners; 4+2 split | else EXCLUDE |
| C2 (H1) | all Shared flip-axis = y (both branches) | else EXCLUDE |
| C3 (H2) | all matching flip-axis ∈ {x,z} (both branches) | else EXCLUDE |
| C4 (H4) | no C3 in builders | else EXCLUDE |

Headline `TT_FLIP_AXIS_SPLIT_SURVIVES` iff C1–C4 pass.  
EXCLUDE is terminal — **no amendment cycle**.

## Non-goals

Energy; capacity; re-opening NSEQ12 species claim; C3 partition.
