# Propose-and-wait — `laws.hpp` triton “belt” nomenclature

**Date proposed:** 2026-08-09  
**Status:** **APPLIED** — 2026-08-09 (author: approve geometric shell replaces Gemini belt model).  
**Applied in:** `Engine/include/sdt/laws.hpp` (+ `docs/dist/`, `Release/.../dist/` mirrors);  
`Benchmarks/B01_B25/benchmarks_suite.cpp` B38; site/docs `benchmarks.html` B38 strings.

## Applied edits

1. “triton belts” → “triton shells”; planar/rolling-equator seating **WITHDRAWN**.  
2. `triton_belt_pairs` → `triton_shell_pairs`; `belt_capacity` → `triton_shell_capacity`.  
3. Completion law: vertex/link `B(n)=V`, `R(n)=E`; face-rule 12→16→20 excluded.  
4. Pure-shell species order documented; T₈/D₁₂/T₁₄ geometry notes (NSEQ05).  
5. Capacities / `static_assert`s unchanged numerically.
