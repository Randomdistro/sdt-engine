# Master Protocol — Iteration 35 (relationship corrections)

**Date:** 2026-08-09  
**Commit base:** `3d2de34` (working tree dirty; see git status)  
**Decision:** relationships re-audited; one advertised signature corrected down

## Scope

Continue NSEQ05 geometry chain + register micro→macro aggregation debt that the
external corrected-proofs note had flagged but not imported as an executable.

## What was already correct in-tree (no re-litigation)

From NSEQ05 + `laws.hpp` (already updated):

1. Pure shells `T8→D12→T10→D20→T12→D30→T14→D42→T16` (grouped `+nd+nt` = sums).
2. Link rule for deuteron 12→20→30; triangular-face 12→16→20 **excluded**.
3. Stella → cuboct midpoints (3+6+3) → 14 face normals (2+6+6 under triangle pole).
4. 14 orients **T14**, not the shell immediately after D12 (T10 intervenes).
5. 14→42 degree-6 face graph with two polar Q–Q branches; `E>3V−6` OPEN.
6. Parity misfits = `L ∪ H` (NP34b); “precisely five” withdrawn in comments.

## New executable results

### NSEQ06 — midpoint doublets

- **SURVIVES:** 42 midpoints → 36 directions → 6 radial doublets (both branches).
- **EXCLUDED:** empty-complementarity of the two branches’ doublet rays
  (`|inter|=4`, `|union|=8`). Corrected relationship: shared 4 + 2 private each.

Evidence: `Investigations/05_Nuclear_Physics/NSEQ06_Link_Midpoint_Direction_Doublets/`
`.audit-tmp/nseq06_run.txt`

### MM01 — ε_agg debt

- `Om_H = a0 α² = 2.8179403262e-15 m`
- `N·Om_H ≈ 3.374×10⁴² m` vs `R_g,☉ ≈ 1476.67 m`
- `ε_agg ≈ 4.376×10⁻⁴⁰` (**COMPUTED debt**, not a mechanism)
- Naive product: **FORMAL_DEFECT**; occlusion derivation: **OPEN**

Evidence: `Investigations/06_Gravitation_and_Orbital_Mechanics/MM01_Micro_Macro_Aggregation_Factor/`
`.audit-tmp/mm01_run.txt`

## Ledger update

See `Audits/RELATIONSHIP_CORRECTIONS_2026-08-09.md`.

## Next highest-value tests

1. Derive `ε_agg` from occlusion/packing with **held-out** solar marker (MM02).
2. Interpret shared vs private doublet rays as emission/transition discriminator
   without retuning capacities.
3. Import full `SDT_Audit_Iterations_07-22_Corrected_Mathematical_Proofs.md` if
   located, and cascade its remaining advertised-pass exclusions one by one.
