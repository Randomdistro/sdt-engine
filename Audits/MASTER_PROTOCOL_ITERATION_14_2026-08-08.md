# Master Protocol — Iteration 14 (GOM34 Station Doppler Fidelity)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 13 GEOM_DOPPLER_MAGNITUDE_PASS

## Result

| Gate | Result |
|---|---|
| Horizons DSS-25 range-rate | PASS |
| Ka/Ka band IDs + turnaround 209/15 | PASS |
| Fidelity improvement vs geocenter | **FAIL** (ratio 3.392 vs 3.365) |
| Shape tracking diagnostic | \|corr\| ≈ 0.9996; scale ≈ −0.295 |
| Solar **K** | unused; not the gap |

**Status:** `STATION_DOPPLER_FIDELITY_FAIL` — station-LOS hypothesis excluded as gap source.

## Cascade

| Path | Status |
|---|---|
| ODF decode / unit path | PASS (engineering Doppler Hz) |
| Geometric class check | PASS (GOM33) |
| Station LOS closes ~3.4× gap | **FAIL / ruled out** |
| Observable↔predictor definition | **REFORMULATION** (scale/sign) |
| Solar **K** profile on Doppler | deferred until definition closes |

## Next tests (ranked)

1. GOM35 — TRK-2-18 ramp/`Fbias`/polarity reconstruction (explain scale ≈ 0.295).  
2. Only then: solar-**K** profile term with **K** fixed.  
3. BF080 / benchmark detox (parallel).
