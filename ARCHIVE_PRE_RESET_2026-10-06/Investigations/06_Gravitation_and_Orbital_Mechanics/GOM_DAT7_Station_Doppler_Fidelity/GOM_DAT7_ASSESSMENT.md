# GOM34 Assessment — Station LOS + Band/Turnaround Fidelity

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom34_station_doppler.py`  
**Stdout:** `.audit-tmp/gom34_run.txt`  
**DSS-25 ephemeris:** `Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM34-C1 | **PASS** — Horizons Cassini `@DSS-25` range/range-rate (31 samples) |
| GOM34-C2 | **PASS** — bands Ka/Ka/S (3/3/1); turnaround 209/15 |
| GOM34-C3 | **PASS** — predictors A / B1 / B2 computed |
| GOM34-C4 | **FAIL** — DSS-25 does not improve ratio or residual vs geocenter |
| GOM34-C5 | **PASS** — residual series reported |
| GOM34-C6 | **PASS** — solar **K** unused; not fitted |

## Numbers (P0 K252, n=125)

| Quantity | Value |
|---|---|
| ratio_A (geo + f_ref) | 3.365 |
| ratio_B1 (DSS-25 + f_ref) | 3.392 |
| ratio_B2 (DSS-25 + Ka nominal) | 51.33 |
| \|res\|_med B1 | 220640 Hz |
| res stdev B1 | 9553 Hz |
| corr(obs, f_pred_B1) | **−0.999623** |
| median(obs / f_pred_B1) | **−0.2948** (diagnostic COMPUTED) |

## Classification

**`STATION_DOPPLER_FIDELITY_FAIL`** with informative exclusion of the station-LOS hypothesis.

### What is ruled out

1. **Geocenter vs DSS-25** as the source of the ~3.4× magnitude gap (ratios 3.365 vs 3.392).  
2. **Raw Ka carrier substitution** (`f = 32.028 GHz`) — makes the gap worse (~51×).  
3. Solar **K** as the gap source: a depth correction at conjunction is fractional ~10⁻⁶ class, not tens of percent.

### What survives as mechanism for the next loop

The geometric range-rate **shape tracks** `obs_Hz` almost perfectly (|corr| ≈ 0.9996) with a nearly constant scale/sign offset (|scale| ≈ 0.295 ≈ 1/3.39). The defect is in the **ODF observable ↔ −2(ṙ/c)f_ref definition** (sign/polarity and scale), not in spacecraft–station geometry and not in solar **K**.

## Reformulation (local)

1. Premise: first-pass `f_pred = −2(ṙ/c)f_ref` equals Items 4–5.  
2. Error: scale/sign mismatch with excellent shape correlation.  
3. Freedom: reconstruct sky frequency and bias using ODF ramp groups + TRK-2-18 polarity; or identify the exact count-rate reference.  
4. Downstream: only after scale/sign closure may a solar-**K** profile term be tested (still without fitting **K**).

## Next gate

GOM35 — TRK-2-18 observable reconstruction (ramp/`Fbias`/bias polarity) on P0; solar **K** still frozen.
