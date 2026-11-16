# MM01 Pre-registration — micro→macro aggregation factor ε_agg

**Date:** 2026-08-09  
**Source debt:** Corrected-proofs audit finding (imported as claim, not as
evidence): naive `ϟ_body = N · ϟ_H` with `ϟ_H = a₀ α²` overshoots solar
compactness `GM_☉/c² ≈ 1476.6 m` by ~10⁴⁰.

## Definitions (MEASURED / IDENTITY inputs)

| Symbol | Value | Class |
|---|---|---|
| `a₀` | 5.29177210903×10⁻¹¹ m | MEASURED-INPUT (CODATA) |
| `α` | 7.2973525693×10⁻³ | MEASURED-INPUT (CODATA) |
| `ϟ_H` | `a₀ α²` | IDENTITY / DERIVED |
| `M_☉` | 1.98847×10³⁰ kg | MEASURED-INPUT (IAU/CODATA family) |
| `m_u` | 1.66053906660×10⁻²⁷ kg | MEASURED-INPUT |
| `G`, `c` | CODATA | MEASURED-INPUT |
| `R_g,☉` | `GM_☉/c²` | DERIVED observable marker |

## Faulty premise (frozen)

`ϟ_body ≟ N · ϟ_H` with `N ≈ M_☉ / m_u` (nucleon count proxy).

## Computed debt

`ε_agg ≔ R_g,☉ / (N · ϟ_H)` — required attenuation if the naive product were
the starting micro sum. **Classification:** UNDERDETERMINED mechanism until
occlusion/packing derives `ε_agg` without fitting `R_g,☉`.

## Decision rules

- Report COMPUTED `ε_agg` and the ratio `(N·ϟ_H)/R_g`.
- Do **not** mark EMPIRICALLY SURVIVES — no mechanism yet.
- Status: `FORMAL_DEFECT` of the naive product; `OPEN` for occlusion derivation.
- Forbidden: introduce a free coefficient and call it a prediction.

## Non-goals

No laws.hpp change; no solar-model retune; no Cassini.
