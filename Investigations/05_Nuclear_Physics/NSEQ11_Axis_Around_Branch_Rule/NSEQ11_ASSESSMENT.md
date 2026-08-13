# NSEQ11 Assessment — Axis / around branch rule

**Date:** 2026-08-11  
**Pre-registration:** `NSEQ11_PRE_REGISTRATION.md` (gates frozen; no hypothesis amend)  
**Instrument:** `nseq11_axis_around.py`  
**Stdout:** `.audit-tmp/nseq11_run.txt`  
**Canon edited:** no  
**C3:** not used

## Status

`AXIS_AROUND_BRANCH_RULE_SURVIVES`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1 | **PASS** | Shared=4, Priv_tri=2, Priv_hex=2 |
| C2 | **PASS** | Private union = `K_{2,2}({±x},{±z})`; the two privates are its perfect matchings |
| C3 | **PASS** | Shared disjoint from that K₂,₂; each branch = Shared ∪ one matching |
| C4 | **PASS** | Builders call only `eid` / frozenset / axis literals — no C3 orbit helpers |

*Note:* First executable attempt failed C4 only because the procedural string-scan
matched its own forbid-list literals (instrument fault). Physics gates C1–C3
already passed on that run. C4 was corrected to `co_names` inspection; hypotheses
unchanged.

## Rule (rod DoF)

Ontology: pnpn / n–p–n ⇒ **axis** (up/down) + **around** (rotation).

On the polar QQ constructions:

```
Shared (4)     = contacts common to both branches  (fixed seating)
K₂,₂(±x,±z)    = four axial–transverse links
matching₁      = {(-x,−z), (+x,+z)}   → triangles private
matching₂      = {(-x,+z), (+x,−z)}   → hexagon private

branch = Shared ∪ matchingᵢ
```

So the binary is not a C3 filter and not an assumed pole. It is:

**which perfect matching of one axial–transverse K₂,₂ is occupied**, with the
shared contacts held fixed.

## Relation to NSEQ08 / NSEQ10

| Item | Status |
|---|---|
| NSEQ08 `\|∩\|=4` | Recovered as Shared |
| NSEQ10 C3 partition “rule” | Still WITHDRAWN (tautology) |
| This rule | Axis/around matching choice — no C3 |

## Scope

- Combinatorial / geometric seating rule only.  
- No emission energy, no capacity change.  
- Which cube-axis pair plays “axis” vs “transverse” in a packed nucleus is
  set by the rod seating frame (here `{x,z}` for the frozen NSEQ05/08
  constructions); not a free fit.
