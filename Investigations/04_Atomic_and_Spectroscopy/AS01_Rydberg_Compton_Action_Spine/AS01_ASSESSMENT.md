# AS01 Assessment — Rydberg/Compton spine

**Date:** 2026-08-11  
**Stdout:** `.audit-tmp/as01_run.txt`

## Status

`AS01_SPINE_SURVIVES__LENGTH_OM_EXCLUDED__AS_OPEN`

## Relationship correction

| Wrong | Correct |
|---|---|
| Plug `Om_H = a₀α² = r_e` into `R_∞ = 1/(4π a₀ Om_H)` | **EXCLUDED** (off by ~10¹⁷) |
| Spectroscopic `Om_H` in product identity | Dimensionless `1/α` — **IDENTITY with α**, not EM length |
| `R = α²/(2 a₀)` | **EXCLUDED** |

## Survives (conditional / Bohr)

- `R_∞ = α/(4π a₀)` vs NIST (rel ~1e-12)
- `λ_C = 2π a₀ α` vs NIST
- `R_∞ λ_C = α²/2`

## OPEN

Native action invariant `A_s` ≠ imported `ℏ`.
