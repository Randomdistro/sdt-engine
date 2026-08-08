# Master Protocol — Iteration 13 (GOM33 Geometric Doppler)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 12 UNIT_PATH_ENGINEERING_DOPPLER_HZ

## Result

| Gate | Result |
|---|---|
| Horizons Cassini geocentric ephemeris (P0 window) | PASS |
| Geometric 2-way `f_geom = -2(ṙ/c)f_ref` | COMPUTED |
| Magnitude vs `obs_Hz` | PASS (ratio 3.365) |
| Solar **K** | frozen 1476.35 m; unused; not fitted |
| SDT residual adjudication | not claimed |

**Status:** `GEOM_DOPPLER_MAGNITUDE_PASS`

## Cascade

| Path | Status |
|---|---|
| ODF chain GOM28–32 | PASS → engineering Doppler Hz |
| Geometric Doppler class check (GOM33) | **PASS** |
| Station/ramp-fidelity residual | PENDING_RECONSTRUCTION |
| Solar-**K** profile term on Doppler/delay | PENDING (K fixed) |

## Next tests (ranked)

1. Station-centered LOS + uplink/turnaround fidelity (close factor-~3 gap).  
2. Time-series `obs − f_pred` with solar **K** held fixed.  
3. BF080 / benchmark detox (parallel).
