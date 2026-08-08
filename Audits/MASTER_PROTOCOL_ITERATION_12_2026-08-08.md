# Master Protocol — Iteration 12 (GOM32 ODF Unit Path)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 11 MULTIDAY_DECODE_PASS

## Result

| Gate | Result |
|---|---|
| Label Item-4 equation class | PASS (count-interval Doppler observable) |
| Type-12 / FORMAT ID 2 | PASS |
| TRK-2-18 `Observable + Fbias` | PASS (documented) |
| K252 \|obs\| magnitude ∈ [1e3, 1e7] Hz | PASS (10.7–53.1 kHz medians) |
| MESSENGER unpack fixture | PASS (−382738.66 Hz) |
| Solar **K** fit / residual | not computed |

**Status:** `UNIT_PATH_ENGINEERING_DOPPLER_HZ`

## Cascade

| Path | Status |
|---|---|
| ODF structure → field → Hz decode → multi-day | PASS (GOM28–31) |
| Observable unit path (GOM32) | **ENGINEERING_DOPPLER_HZ** |
| Predicted Doppler / light-time residual | PENDING_RECONSTRUCTION |
| Solar **K** (GOM26 orbital) | frozen investigation IC (~1476.35 m) |
| BF080 absolute δ | PENDING_ACCESS |

## Next tests (ranked)

1. Pre-register DSS-25 type-12 **predicted Doppler** geometry (SPK/Horizons + station); solar **K** held fixed.  
2. Optional: type-37 range channel census for delay-like path.  
3. NRAO BF080 staging / benchmark detox (parallel).
