# OM02 Assessment — Om radius vs circumference

**Date:** 2026-08-11  
**Instrument:** `om02_radius_vs_circumference.py`  
**Stdout:** `.audit-tmp/om02_run.txt`  
**Canon edited:** no

## Status

`OM_RADIUS_REQUIRED__CIRCUMFERENCE_NAIVE_EXCLUDED`

## Freeze

| Quantity | Value | Role |
|---|---|---|
| \(\Omega_\odot\) (OM01) | **1476.625 m** | distance from centre to c-boundary |
| \(C_\odot=2\pi\Omega_\odot\) | **9.278 km** | circumference of that locus |

(GOM25b/GOM26 freezes give \(C\) in **9.276–9.280 km**.)

## Solar screen (naive \(L\) substitution)

| Observable | \(L=\Omega\) | \(L=C\) |
|---|---|---|
| Limb \(4L/R\) | **MATCH** (1.751″) | ORDER — high by \(2\pi\) (~11.0″) |
| Redshift \(L/R\) | **MATCH** | ORDER — ×\(2\pi\) |
| Mercury \(6\pi L/\ldots\) | **MATCH** (42.98″/cy) | ORDER — ×\(2\pi\) |
| Shapiro marker | **MATCH** (~239 µs) | ORDER — ×\(2\pi\) |

## Relationship

| Claim | Result |
|---|---|
| \(C\) is a well-defined geometric length on the c-boundary | true (\(2\pi\Omega\)) |
| Drop \(C\) into existing solar formulas in place of \(\Omega\) | **ruled out** — every linear-in-\(L\) solar match moves by \(2\pi\) |
| Keep physics, rename length | formulas must use \(\Omega = C/(2\pi)\) |

## Not claimed

EMPIRICALLY SURVIVES for new raw solar path data. This run only tests the
author length-vs-radius relation against the in-repo solar formula set.
