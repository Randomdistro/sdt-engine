# NSEQ05 Assessment — Pure-shell + stella→cuboct→14→42

**Date:** 2026-08-09  
**Pre-registration:** `NSEQ05_PRE_REGISTRATION.md`  
**Instrument:** `nseq05_pure_shell_stella_cuboct.py`  
**Stdout:** `.audit-tmp/nseq05_run.txt`  
**Canon edited:** no

## Status

`PURE_SHELL_STELLA_CUBOCT_RELATIONS_SURVIVE`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1 | PASS | Pure shells `20-T8-28-D12-40-T10-50-D20-70-T12-82-D30-112-T14-126-D42-168-T16-184` |
| C2 | PASS | Face rule `{12,16,20}` excluded; link rule `{12,20,30}=R(3..5)` |
| C3 | PASS | 12 nearest stella links → cuboct midpoints; polar split **3+6+3** |
| C4 | PASS | 14 face normals under triangle pole: 2×90° + 6×35.264° + 6×19.471° |
| C5 | PASS | Both Q–Q branches: connected 6-regular on 14 sites, E=42, distinct |
| C6 | OPEN→**CLOSED by NSEQ07** | E=42 > 3V−6 was category error: surface χ=2 + 6 Q–Q ⇒ genus-1 (χ=0) |

## Relationship corrections (narrative)

1. **Grouped vs pure shells.** Engine `+12d+10t` style increments are
   *closure groups*. Species-consecutive reading is alternating pure
   triton / deuteron shells. Capacities unchanged.
2. **“12 faces” trap.** Same count as 12 cube edges / cuboct vertices, but
   triangular-face continuation predicts 16,20 where the schedule requires
   20,30. Links win; faces do not.
3. **Stella → cuboct → 14.** Proven incidence:
   T₈ vertices → 12 edge midpoints (cuboct) → 14 face normals.
   The 14-set is the natural orientation for **T₁₄**, not the immediate
   triton shell after D₁₂ (that is T₁₀ under the capacity schedule).
4. **14 → 42.** Combinatorial degree-6 construction exists with a binary
   orientation debt (triangle vs hexagon Q–Q choice). Excess over
   `3V−6` remains OPEN (3-D / crossing contacts).
5. **NSEQ03 dual-tetra seating** is compatible with polar family
   `2 + 2n` sites; this audit supplies the incidence geometry that
   “belt / equator” language obscured.

## Required canon comment corrections (propose-and-wait)

See `PROPOSE_LAWS_HPP_RELATION_COMMENT_CORRECTIONS.md`:

- belt → shell nomenclature (extends NSEQ03 proposal);
- pure-shell expansion narrative beside grouped `closure(k)`;
- parity comment: “precisely five” → `L ∪ H` (NP34 / NP34b);
- retire rolling-equator as seating justification.

No capacity or `static_assert` change proposed.

## External thread (not in this tree)

`SDT_Audit_Iterations_07-22_Corrected_Mathematical_Proofs.md` (micro→macro
`ε_agg≈4.41×10⁻⁴⁰` debt; several advertised numerical passes failing direct
execution) was **not found** under this workspace. Import that document into
`Audits/` before cascading its exclusions into the engine ledger.
