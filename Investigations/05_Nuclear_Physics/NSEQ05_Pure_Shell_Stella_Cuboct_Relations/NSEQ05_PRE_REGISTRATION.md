# NSEQ05 Pre-Registration — Pure-shell schedule + stella→cuboct→14→42

**Date:** 2026-08-09  
**Canon edited:** no  
**Upstream:** NSEQ01–04; author geometric clarifications (stella tritons → deuteron
links → next triton shell); NP34/NP34b parity census

## Objectives

1. Expand the engine’s *grouped* closure increments into consecutive **pure
   species shells** and verify they reproduce measured magic numbers.
2. Discriminate two geometric readings of the first “12” after T₈:
   - **Face rule:** triangular faces of a triangulated cube → 12, then 16, 20…
   - **Link rule:** nearest inter-vertex contacts (cube edges) → 12, then 20, 30…
3. Prove the exact incidence chain T₈ stella vertices → 12 cuboctahedral edge
   midpoints (3+6+3) → 14 cuboctahedral face normals, with latitudes.
4. Show a symmetry-preserving construction of **42** contacts on those 14
   sites (degree 6), with two polar orientation branches left as debt.
5. Record required comment corrections (parity L∪H; belt→shell; pure-shell
   narrative) as propose-and-wait — not silent canon edits.

## Frozen capacity forms (from `laws.hpp`, unchanged)

```text
F(n) = (n+1)(n+2)     # tier / full bipartite layer
B(n) = 2(n+1)         # triton shell capacity (was “belt”)
R(n) = n(n+1)         # surface remainder = deuteron link count after n≥3
```

## Pure-shell expansion (hypothesis under test)

After N=20, consecutive pure shells:

```text
20 --T8--> 28 --D12--> 40 --T10--> 50 --D20--> 70 --T12--> 82
   --D30--> 112 --T14--> 126 --D42--> 168 --T16--> 184
```

Grouped engine notation `+12d+10t` is a *closure increment*, not one mixed shell.

## Pre-committed gates

| ID | Gate | PASS iff |
|---|---|---|
| C1 | Pure-shell expansion | Magic {28,50,82,126} hit; intermediates {40,70,112,168} as stated; 184 = 126+42+16 |
| C2 | Face vs link | Face sequence ≠ {12,20,30}; link sequence = {12,20,30} for R(3..5) |
| C3 | Stella→cuboct | 12 midpoints: latitudes split 3+6+3; cuboct edge lengths consistent |
| C4 | Cuboct→14 | 14 face normals: 2 poles + 6@arcsin(1/√3) + 6@arcsin(1/3) (mirrored) |
| C5 | 14→42 | Both polar Q–Q choices yield connected 6-regular graphs, E=42 |
| C6 | Simple-polyhedron bound | E=42 > 3V−6=36 recorded as OPEN topology debt (not smoothed) |

## Decision

- All C1–C5 PASS → `PURE_SHELL_STELLA_CUBOCT_RELATIONS_SURVIVE`
- Any C1–C5 FAIL → `RELATION_EXCLUDED` with named gate
- C6 is diagnostic OPEN, not a kill of C1–C5

## Out of scope

κ fits, IAEA RMS maps, Cassini, `laws.hpp` edits without exact approve phrase.
