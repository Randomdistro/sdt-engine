# OM01 Pre-registration — shared solar om profile (deflection + redshift + delay marker)

**Date:** 2026-08-11  
**Program:** solar lensing / propagation coupled profile (protocol §XII)

## Single profile

`om_☉ = R_☉ / k_☉²` with `k_☉ = c / v_surf` **or** equivalently from Mercury
precession closure (`koppa_Sun_from_precession`). This run uses:

- `R_☉ = 6.957×10⁸ m`
- `v_surf = 4.36762×10⁵ m/s` (engine validation anchor — disclosed)
- `om = v_surf² R / c²`

## Predictions from ONE om (no retune)

| Observable | Formula | Target class |
|---|---|---|
| Limb deflection | `α = 4 om / R` (rad) → arcsec | known-match ~1.75″ |
| Surface redshift | `z = om / R` | ~2.12×10⁻⁶ |
| Weak Shapiro-like marker | `Δt ~ (2/c) · 2 om · ln(4 r_E r_⊙ / b²)` order | COMPUTED order only |

## Decision

- SURVIVE **conditional consistency** if limb α and z both come from same om
  within 1e-9 relative construction error.
- Do **not** claim EMPIRICALLY SURVIVES (v_surf / precession inputs are
  model-touched; no raw Cassini integration this run).
- EXCLUDE any path that retunes om between observables.
