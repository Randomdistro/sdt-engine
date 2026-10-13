# NSEQ10 Pre-registration — Q−Q branch selection rule

**Date:** 2026-08-11  
**Parents:** NSEQ06 (20 selections / 2 under C3×inversion); NSEQ08 (`QQ∩`);
NSEQ07 (genus-1); NSEQ09 (N=184 sparse diagnostic)  
**Objective:** Elevate “two polar branches” from an observed pair to a
**selection rule**: mandatory shared core + binary private completion under
stated symmetry. No emission MeV claim.

## Frozen geometry

- 14 cuboct face normals; surface `S = TQ ∪ TT` fixed (`|S|=36`).
- Q vertices = 6 axis normals; QQ candidate edges = 12 right-angle pairs.
- Each Q has surface degree 4 ⇒ full 6-regular graph needs **exactly 2** QQ
  edges per Q ⇒ selected QQ set is a **2-factor** of the octahedron graph
  (disjoint cycle cover of all 6 Q vertices).

## Hypotheses

**H1 — Census.** Number of distinct 2-factors of the octahedron QQ graph is
**20** (NSEQ06 F4 reconfirm).

**H2 — Symmetry cut.** Under `C3 × inversion` (axis cycle + sign flip),
exactly **2** of those 20 are invariant. Component counts are `{1, 2}`:
one 6-cycle and one triangle-pair.  
*(Amendment 01: these need not equal the NSEQ05 polar-construction
“triangles/hexagon” pair — that pair is a different, polar-axis labelling.
C2 tests the symmetry census + type split, then reports overlap with the
polar pair.)*

**H3 — Mandatory core.** Let `Core = S₁ ∩ S₂` for the two symmetry
survivors. `|Core|=4`, and every survivor contains `Core`.

**H4 — Binary private pool.** `|S₁ ∪ S₂|=8`, `|S₁ Δ S₂|=4`, unused QQ
edges `=4`. Each survivor’s private set has size 2.

**H5 — N=184 diagnostic (report-only).** Using NSEQ09 AME route, report
`nZ` and median `D` for N=168 (OPEN_D) and N=184 (SEAL forward).  
If `nZ≥3` and medians exist, compare to NSEQ09 thresholds; else
`DATA_SPARSE` (not a FAIL of H1–H4).

## Decision

| Gate | SURVIVE | EXCLUDE / OPEN |
|---|---|---|
| C1 (H1) | \|2-factors\|=20 | else EXCLUDE census |
| C2 (H2) | exactly 2 invariant; match triangle+hexagon | else EXCLUDE |
| C3 (H3) | both contain `QQ∩` | else EXCLUDE mandatory-core claim |
| C4 (H4) | \|symdiff\|=4, \|union\|=8, unused=4 | else EXCLUDE |
| C5 (H5) | reported; PASS only if adjudicable *and* SEAL-like at 184 / weak at 168 | else OPEN sparse |

Headline `QQ_BRANCH_SELECTION_RULE_SURVIVES` if C1–C4 pass.  
C5 does not veto C1–C4.

## Non-goals

No capacity change; no emission/transition *energy*; no averaging of branches;
no claim that symmetry *is* the physical mechanism — only that under this
symmetry the selection collapses to mandatory core + binary private choice.
