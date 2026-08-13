# NSEQ07 Pre-registration — D₄₂ topology debt (NSEQ05-C6)

**Date:** 2026-08-09  
**Parent:** NSEQ05-C6 OPEN (`E=42 > 3V−6=36`); NSEQ06 doublet counts  
**Objective:** Close the advertised topology debt: is the 14→42 contact
graph a failed spherical polyhedron, or a classified non-spherical
incidence with a unique surface/chord split?

## Frozen inputs

- 14 cuboct face normals as unit vertices (8 T + 6 Q), from NSEQ05.
- Edge classes: T−Q at `arccos(1/√3)` (24), T−T at `arccos(1/3)` (12),
  Q−Q at 90° selected by each polar branch (6 of 12).
- Both branches from NSEQ05/NSEQ06: `triangles` and `hexagon`.
- No capacities, no IAEA, no `laws.hpp` arithmetic edits.

## Hypotheses (pre-registered)

**H1 — Surface triangulation.**  
`S = (T−Q) ∪ (T−T)` has `|S|=36`. Treating faces as triangles
(`2E = 3F`) yields `F=24` and Euler `χ = V−E+F = 2` (sphere).  
Bound `E ≤ 3V−6 = 36` is saturated — maximal spherical.

**H2 — Chords = excess = doublets.**  
Each polar branch adds exactly the 6 selected Q−Q edges.  
`|full| − |S| = 6 = excess over 3V−6 = NSEQ06 doublet count`.

**H3 — Genus-1 full graph.**  
Full graph is 6-regular on `V=14` ⇒ `E = 3V = 42`.  
Any triangulation embedding (`2E=3F`) has `F=28` and `χ=0`
(orientable genus `g=1`, torus). Spherical simple-polyhedron language
is the wrong category, not a packing failure.

**H4 — Doublet provenance.**  
Each of the 6 radial doublets pairs **exactly one Q−Q chord midpoint**
with **exactly one surface-edge midpoint** (same oriented unit ray).

## Decision rules

| Gate | SURVIVE | EXCLUDE / OPEN |
|---|---|---|
| C1 (H1) | `|S|=36`, `χ=2`, `2E=3F` both imply triangulation | else EXCLUDE surface claim |
| C2 (H2) | excess=`|QQ|=6` both branches; equals doublet count | else EXCLUDE |
| C3 (H3) | 6-regular, `E=3V`, triangulation `χ=0` | else OPEN/EXCLUDE |
| C4 (H4) | all 6 doublets are {QQ, surface} pairs | if some doublets are surface–surface or QQ–QQ → EXCLUDE H4; counts may still close C1–C3 |

**Headline SURVIVES** if C1–C3 pass on both branches.  
C4 is a strengthening; failure of C4 alone → `TOPOLOGY_CLASSIFIED__DOUBLET_PROVENANCE_OPEN`.

## Non-goals

No capacity change, no emission physics, no averaging of orientation
branches, no `laws.hpp` edit (propose-and-wait comment only if C1–C3 pass).
