# GOM33 Assessment — Geometric Predicted Doppler

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom33_predicted_doppler.py`  
**Stdout:** `.audit-tmp/gom33_run.txt`  
**Ephemeris:** `Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_geocentric_2002_157.csv`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM33-C1 | **PASS** — Horizons Cassini `@399` vectors for P0 window (volume SPK starts DOY 160; not used) |
| GOM33-C2 | **PASS** — DSS-25 nominal coords recorded; first pass uses **geocenter** LOS |
| GOM33-C3 | **PASS** — `f_geom = -2 (ṙ/c) f_ref` COMPUTED |
| GOM33-C4 | **PASS** — `|f_geom|/|obs|` median ratio = **3.365** ∈ [0.1, 10] |
| GOM33-C5 | **PASS** — solar **K** = 1476.35 m frozen/unused; no fit |
| GOM33-C6 | **PASS** — no gamma / Bertotti |

## Numbers (P0 K252, DSS-25 type-12 subsample)

| Quantity | Value | Tag |
|---|---|---|
| Samples compared | 125 | COMPUTED |
| `f_ref` median | 2.116648992×10⁹ Hz | COMPUTED from ODF |
| \|f_geom\| median | 169026 Hz | COMPUTED |
| \|obs_Hz\| median | 50232 Hz | COMPUTED from RAW |
| Ratio | 3.365 | COMPUTED |

## Classification

**`GEOM_DOPPLER_MAGNITUDE_PASS`.**

Same kHz–hundreds-of-kHz class as engineering `obs_Hz`. This is **not** an
SDT empirical survival or exclusion. Geocenter approximation, missing uplink
ramp reconstruction, and unused solar-**K** profile term remain Scope limits.

## Next gate

1. Station-centered LOS + turnaround/ramp reconstruction (reduce factor-~3 gap).  
2. Time-series residual `obs − f_geom` without fitting solar **K**.  
3. Separate COMPUTED solar-**K** Doppler/delay correction with **K** held fixed.
