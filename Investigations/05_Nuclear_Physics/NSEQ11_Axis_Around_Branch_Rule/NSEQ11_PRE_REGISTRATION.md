# NSEQ11 Pre-registration — Axis / around branch rule (no C3)

**Date:** 2026-08-11  
**Parents:** Author ontology (pnpn ⇒ only axis up/down + rotation around);
NSEQ08 polar `|∩|=4`; NSEQ10 C3 rule-win WITHDRAWN  
**Forbidden:** `C3×inversion` as a gate or as the definition of the binary.  
**Objective:** State the polar binary as a rod DoF choice: shared contacts
fixed; private contacts = choice of one perfect matching on a single
axial–transverse `K_{2,2}`.

## Ontology (inputs, not hypotheses)

A coherent n–p–n / p–n–p–n rod affords two directions only:

- **axis** — up / down along the rod  
- **around** — rotation about that axis  

Dual-tetra / cuboct polar seating (NSEQ05) is the shell readout of that
pair. No pole is “assumed”; the rod supplies it.

## Frozen constructions

- Q vertices = six axis normals `±x,±y,±z` (cuboct square faces).  
- Polar branches = NSEQ05/08 `triangles` and `hexagon` QQ 2-factors.  
- `Shared = QQ_tri ∩ QQ_hex` (expect 4).  
- `Priv_tri = QQ_tri \ Shared`, `Priv_hex = QQ_hex \ Shared`.

## Hypotheses

**H1 — Shared fixed.** `|Shared|=4`, `|Priv_tri|=|Priv_hex|=2`.

**H2 — Private = K₂,₂ matchings.** There exist two opposite-axis pairs
`{±u}`, `{±v}` (distinct cube axes) such that:

- `Priv_tri ∪ Priv_hex` = all four edges of the complete bipartite
  `K({±u},{±v})`  
- `Priv_tri` and `Priv_hex` are the two perfect matchings of that `K_{2,2}`  
- `Priv_tri ∩ Priv_hex = ∅`

**H3 — Branch = matching choice.**  
`QQ_tri = Shared ∪ Priv_tri`, `QQ_hex = Shared ∪ Priv_hex`  
with `Shared` disjoint from the `K_{2,2}`.

**H4 — No C3 gate.** Source uses no `C3×inversion` / orbit-invariance test
to define or pass the binary.

## Decision

| Gate | SURVIVE | EXCLUDE |
|---|---|---|
| C1 (H1) | cardinalities as stated | else EXCLUDE |
| C2 (H2) | some cube-axis pair realises the K₂,₂ split | else EXCLUDE |
| C3 (H3) | shared disjoint from that K₂,₂; unions recover both branches | else EXCLUDE |
| C4 (H4) | no C3 in builder/gates | else EXCLUDE (procedure fault) |

Headline `AXIS_AROUND_BRANCH_RULE_SURVIVES` iff C1–C4 pass.  
On any EXCLUDE: record FAIL — **do not amend gates to match data**.

## Non-goals

No emission MeV; no capacity change; no revival of NSEQ10 C3 partition claim.
