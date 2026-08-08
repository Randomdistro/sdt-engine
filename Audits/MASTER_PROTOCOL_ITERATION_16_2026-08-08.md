# Master Protocol — Iteration 16 (GOM_DAT9 + GOM36)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none

## A — Data task GOM_DAT9

| Gate | Result |
|---|---|
| DSS-25 ramp decode | PASS — sky f0 = 34.317852320 GHz, rate 0 |
| TRK-2-18 Fbias predictors close scale gap | **FAIL** → `FBIAS_RECON_UNRESOLVED` |

## B — Claim investigation GOM36

| Gate | Result |
|---|---|
| CALIBRATED(1) train scale | `s = −0.250217` |
| \|corr(r, dΔt/dt)\| on test | 0.999983 → pre-registered **SOLAR_K_RESIDUAL_SIGNAL** |
| Delete-test corr(r, time) | **0.999987** (confound) |
| \|f·dΔt/dt\| vs \|r\| | 0.033 Hz vs ~15 kHz |

**Effective status:** `UNADJUDICATED` after delete-test — not EMPIRICALLY SURVIVES.

## Cascade

| Path | Status |
|---|---|
| DAT1–DAT9 ODF chain | decode PASS; scale/Fbias unresolved |
| GOM36 solar-**K** residual | gate met; **time-confounded** |
| Next claim test | multi-day / time-detrended residual (GOM37) |

## Next tests (ranked)

1. GOM37 — multi-day b(t) + time-detrended hold-out residual; **K** fixed.  
2. Parallel: BF080 staging; benchmark detox.
