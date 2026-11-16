# GOM_DAT9 Assessment — Ramp / Fbias Reconstruction

**Date:** 2026-08-08  
**Class:** data / reconstruction task  
**Instrument:** `gom_dat9_ramp_fbias.py`  
**Stdout:** `.audit-tmp/gom_dat9_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| DAT9-C1 | **PASS** — 1× DSS-25 ramp row; sky-level f0 |
| DAT9-C2 | **PASS** — Fbias candidates formed |
| DAT9-C3 | **PASS** — predictors reported |
| DAT9-C4 | **FAIL** — none meet ratio/resid gates |
| DAT9-C5 | **FBIAS_RECON_UNRESOLVED** |
| DAT9-C6 | **PASS** — solar **K** unused |

## Ramp census (COMPUTED)

| Field | Value |
|---|---|
| Station | 25 |
| Start frequency | **34.317852320 GHz** (sky-level) |
| Rate | 0 Hz/s (constant) |
| Span | 2002-06-06 18:22 – 2002-06-07 02:52 UTC |

## Classification

**`FBIAS_RECON_UNRESOLVED`.**

Applying TRK-2-18 Case-2 `Fbias = ρ·f_ref` or ramp sky frequency **worsens**
the magnitude mismatch vs `obs_Hz`. The ~3.4× gap is not cured by ramp/`Fbias`
alone. Geometry still tracks (GOM_DAT7); definition debt remains.

## Next

Claim investigation with **one** pre-registered hold-out scale (CALIBRATED)
against solar conjunction geometry — not further unlabeled DAT scale scans.
