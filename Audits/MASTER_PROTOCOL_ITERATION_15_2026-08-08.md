# Master Protocol — Iteration 15 (GOM35 Scale/Sign Hypotheses)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 14 STATION_DOPPLER_FIDELITY_FAIL

## Result

| Gate | Result |
|---|---|
| Discrete documented scale/sign hypotheses H0–H7 | none PASS |
| Closest | H3/H5/H6/H7 at rel_resid ≈ 0.15 (near miss; not promoted) |
| Solar **K** | unused |

**Status:** `SCALE_CONVENTION_UNRESOLVED`

## Cascade

| Path | Status |
|---|---|
| Geometry shape tracking | excellent (\|corr\|≈0.9996) |
| Station LOS as gap source | ruled out (I14) |
| Simple documented scale factors | **unresolved** (I15) |
| TRK-2-18 ramp/`Fbias` reconstruction | **NEXT** |
| Solar-**K** Doppler profile | blocked until definition closes |

## Next tests (ranked)

1. GOM36 — ODF Group-4 ramp + `Doppler = Observable + Fbias` reconstruction.  
2. Solar-**K** profile term only after scale closure (**K** fixed).  
3. BF080 / benchmark detox (parallel).
