# PSP02 Pre-registration

**Date:** 2026-08-12  
**Ω frozen:** 1476.625 m  
**Window:** Enc-22 perihelion 2024-12-24 10:00–14:00 TDB (extendable)

## Predictions (path-only, before radio)

Along Horizons \(r(t)\):

- \(z(t)=\Omega/r(t)\)
- \(c_\mathrm{far}=c(1-z)^2\)
- \(z_\mathrm{spec}(t)=z_\mathrm{psp}-z_\oplus\) (Earth at ~1 AU depth)
- Geometric two-way Doppler class from LOS range-rate (separate column)

## Gates

| Gate | Pass |
|---|---|
| C1 | \(\min r\) within 1% of \(9.86 R_\odot\) |
| C2 | Ledger written; Ω unused as fit |
| C3 | LOS Doppler column present |
| C4 | Depth terms in separate columns |
| C5–C6 | Radio present → compare; else PENDING_DATA |

## Rejection

Fitting Ω; promoting FIELDS as DSN carrier; EMPIRICALLY SURVIVES without TNF.
