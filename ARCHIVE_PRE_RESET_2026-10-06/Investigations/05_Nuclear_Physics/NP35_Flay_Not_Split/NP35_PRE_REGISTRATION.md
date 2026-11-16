# NP35 Pre-registration — flay, not split

**Date:** 2026-08-13  
**Canon edits:** none  
**Ontology:** the nucleus is sealed masonry plus unfrozen outer shells. A driven event **unwraps** outer shells. The core is not a liquid drop. NP25 two-lobe/neck language is withdrawn as mechanism (the ledger identity `2d→α` is kept).

## Claim under test

**F3 (author ontology):** deuteron shells flay; the heavy remnant is the **outermost sealed triton shell**. A triton shell is sealed only when the **next deuteron tier is complete**.

Species-pure N-sequence (NSEQ05 / `laws.hpp`):

```
2  8  20  28  40  50  70  82  112  126  168
         T8      T10     T12       T14
```

| T-shell | completes at N | next D completes at | sealed iff |
|---|---|---|---|
| T8 | 28 | 40 | N ≥ 40 |
| T10 | 50 | 70 | N ≥ 70 |
| T12 | 82 | 112 | N ≥ 112 |
| T14 | 126 | 168 | N ≥ 168 |

Actinides in the IAEA eight have 142 ≤ N ≤ 147, so F3 predicts **N_H = 82** (T12), not 126. T14 is not sealed because D42 is incomplete.

**Z_H** = `round(N_H · Z_parent / N_parent)` (composition-preserving jacket). Not Z=50 inserted.

**A_H_pre** = Z_H + N_H, **A_L_pre** = A* − A_H_pre. Independent yields are post-prompt-neutron; ν is not used to choose the split.

## Controls (must run)

| ID | Rule | Role |
|---|---|---|
| F1 | Heavy N = largest reached closure (any species) | Naive unwrap-to-first-complete. Actinides → **126**. Expected EXCLUDED vs A_H~140. |
| F_Z50 | N_H=82, Z_H=50 | Inserts proton magic. Control column only. |

## Gates (frozen)

| Gate | MATCH | EXCLUDED |
|---|---|---|
| G1 F1 vs U-235 thermal A_H | — | \|ΔA_H\| ≥ 20 |
| G2 F3 vs U-235 thermal A_H | \|ΔA_H\| < 8 | \|ΔA_H\| ≥ 20 |
| G3 F3 A_H all 8 systems | every A_H in [128, 148] | any A_H < 120 or > 160 |
| G4 F3 A_H vs A* slope | \|slope\| < 0.25 | slope > 0.5 |
| G5 F3 A_L_pre − A_L_obs | in [1.0, 8.0] (ν-class residue) | negative or > 12 |

ORDER = 8 ≤ \|ΔA_H\| < 20. No mid-pass retune. No N=82 from yield peaks.

## Forbidden

- Liquid-drop / neck bipartition as the mechanism  
- Fitting Z_H or N_H to centroids  
- Using literature ν to pick the channel  
- Labelling EMPIRICALLY SURVIVES on G2 alone (cross-fissioner G3–G5 required)

## Superheavy switch (stated, not scored this pass)

If N_parent ≥ 168, F3 predicts N_H = 126 (T14 sealed). No in-repo SF table for that N. PENDING_DATA (Cf-252 is N=154, still T12).
