# PSP02 Assessment — gradient path ledger; radio gated

**Date:** 2026-08-12  
**Stdout:** `.audit-tmp/psp02_run.txt`  
**Ledger:** `psp02_enc22_path_ledger.csv`  
**Canon edited:** no

## Status

`PATH_LEDGER_READY__RADIO_PENDING_DATA`

## What was done

1. Investigation scaffolded (`PROMPT`, pre-reg, data requirements).  
2. Enc-22 public path staged from Horizons (PSP + Earth).  
3. Single-pass SDT depth ledger along the path (\(\Omega\) frozen):  
   \(z\), \(c_\mathrm{far}\), \(z_\mathrm{spec}\), geometric LOS Doppler fraction.

## Enc-22 perihelion sample (Horizons)

| Quantity | Value |
|---|---|
| \(t\) (TDB) | 2024-12-24 11:42 |
| \(r\) | 9.864 \(R_\odot\) (C1 PASS vs 9.86) |
| Speed | 190.77 km/s |
| \(z=\Omega/r\) | 2.152×10⁻⁷ |
| \(z_\mathrm{spec}\) | 2.051×10⁻⁷ |
| \((c-c_\mathrm{far})/c\) | 4.303×10⁻⁷ |
| Geom. Earth–PSP \(\dot r\) | 154.0 km/s |

## What was *not* done (blocked)

**All raw DSN transmission products (TRK-2-34 TNF / ODF) are access-restricted.**  
They are not on PDS as a public Parker dump. Without them:

- No map from predicted depth terms → observed carrier residuals.  
- No onboard-path vs apparent-radiometric-path comparison.  
- No EMPIRICALLY SURVIVES.

FIELDS plasma radio is **not** a substitute (local emission ≠ DSN carrier).

## Next (author / mission data)

1. Stage authorized Enc-22 (or nominated) TRK-2-34 under `Datasets/parker_solar_probe_2026-08/radio/`.  
2. Run P2 decode (PyTrk234) → P3 residual vs C4 columns.  
3. Until then, path ledger is the deliverable.
