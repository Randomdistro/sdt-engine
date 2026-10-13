# MM01 Assessment — micro→macro ε_agg debt

**Date:** 2026-08-09  
**Instrument:** `mm01_epsilon_agg.py`  
**Stdout:** `.audit-tmp/mm01_run.txt`  
**Canon edited:** no

## Status

`EPSILON_AGG_DEBT_RECORDED`

## Computed (direct execution)

| Quantity | Value | Class |
|---|---|---|
| `Om_H = a0 α²` | `2.8179403262×10⁻¹⁵ m` | IDENTITY |
| `R_g,☉ = GM_☉/c²` | `1476.669691 m` | DERIVED from MEASURED |
| `N ≈ M_☉/m_u` | `1.197485×10⁵⁷` | MEASURED-INPUT proxy |
| `N·Om_H` | `3.374440×10⁴² m` | COMPUTED |
| `ε_agg = R_g/(N·Om_H)` | `4.376043×10⁻⁴⁰` | COMPUTED debt |
| `(N·Om_H)/R_g` | `2.285×10³⁹` | COMPUTED |

Prior verbal claim `≈4.41×10⁻⁴⁰` is the same order; small shift is constant
choice (nucleon vs atomic mass unit, solar mass convention) — not a salvage.

## Classification

- Naive `Om_body = N·Om_H`: **FORMAL_DEFECT** (overshoot ~10³⁹–¹⁰⁴⁰).
- `ε_agg` number: **COMPUTED** attenuation required if that product were the
  starting sum — **not** a prediction and **not** EMPIRICALLY SURVIVES.
- Occlusion / packing derivation of `ε_agg` without fitting `R_g`: **OPEN /
  UNDERDETERMINED**.

## Forbidden next moves

- Fitting a free coefficient to solar `R_g` and calling it derived.
- Importing GR interior solutions as SDT mechanism.
- Cascading “solar body depth works” public claims until the mechanism exists.
