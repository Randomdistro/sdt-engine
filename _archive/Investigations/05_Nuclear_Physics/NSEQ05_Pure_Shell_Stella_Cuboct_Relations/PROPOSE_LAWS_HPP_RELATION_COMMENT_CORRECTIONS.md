# Propose-and-wait — `laws.hpp` relation / comment corrections

**Date:** 2026-08-09  
**Status:** **APPLIED** — 2026-08-09 (author approved geometric shell replaces
Gemini belt; covered with NSEQ03 nomenclature apply in `laws.hpp`).  
**Scope:** comments + identifier renames. **No arithmetic change.**

## Corrections required by NSEQ05 + NP34b

### 1. Pure-shell narrative (shell schedule block ~L1112–1132)

Add beside the grouped `closure(k)` description:

```text
Species-consecutive pure shells after N=20:
  20 -T8-> 28 -D12-> 40 -T10-> 50 -D20-> 70 -T12-> 82
     -D30-> 112 -T14-> 126 -D42-> 168 -T16-> 184
Grouped increments (+12d+10t, …) are closure sums, not mixed shells.
Deuteron counts R(n)=n(n+1) read as nearest-link (edge) capacities;
triangular-face continuation {12,16,20} is excluded (NSEQ05-C2).
```

### 2. Belt → shell (carry NSEQ03 proposal)

Rename comments/symbols `belt` → `shell` / `triton_shell_*` as already
proposed. Retire “rolling-equator” as the seating justification; keep
`B(n)=2(n+1)` with dual-tetra / polar-family reading (NSEQ03 + NSEQ05).

### 3. Stella–cuboct incidence (optional comment)

```text
T8 stella vertices -> 12 cube-edge midpoints (cuboctahedron, 3+6+3 under
triangle pole) -> 14 face normals (2 poles + 6 at arcsin(1/√3) + 6 at
arcsin(1/3)). The 14-set orients T14; it is not the immediate shell after D12.
14->42 admits two polar Q-Q orientation branches (E=42, deg=6); E>3V-6 is OPEN.
```

### 4. Triton parity comment (~L1158–1164)

Replace “precisely the five naturally occurring odd-odd quasi-stables …” with:

```text
Among primordial odd-Z NUBASE entries the misfit set is exactly L ∪ H
(NP34b): light stable odd–odd L={²H,⁶Li,¹⁰B,¹⁴N} and long-lived radioactive
odd–odd H={K-40,V-50,La-138,Lu-176,Ta-180m}. The older “precisely five”
wording is excluded by whole-range census (NP34).
```

Function body unchanged.

## Non-proposals

- No change to `magic_numbers`, capacities, `closure`, grammar, or asserts.
- No κ retune; no IAEA RMS map; no Cassini.

## Approval

Reply **`approve laws.hpp relation comment corrections`** (or amend).
Applying this may subsume the earlier belt→shell rename proposal.
