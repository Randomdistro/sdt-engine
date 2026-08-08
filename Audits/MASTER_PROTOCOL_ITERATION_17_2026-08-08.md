# Master Protocol — Iteration 17 (GOM37 Multi-Day Detrended Residual)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 16 GOM36 time-confound

## Result

| Gate | Result |
|---|---|
| Multi-day K252 DSS-25 (157–160) | PASS |
| Train scale + linear detrend (day 157 only) | PASS (`s=−0.294774`) |
| b(t) span on test | 35.4 – 42.7 R_☉ |
| \|corr(r⊥, dΔt/dt)\| | 0.992 (high) |
| \|corr(r⊥, time)\| | 0.996 → **confounded** |
| amp_ratio | **7.07×10⁶** → gate FAIL |
| Solar **K** fit | none |

**Status:** `UNADJUDICATED`

## Cascade

| Path | Status |
|---|---|
| ODF Doppler vs solar-**K** delay-rate | **blocked / UNADJUDICATED** (GOM36–37) |
| Root cause | observable definition + day-transfer fidelity, not K |
| Next claim leverage | type-37 range / light-time, or BF080 δ |

## Next tests (ranked)

1. GOM38 — type-37 range / light-time with frozen **K**, **or** formal
   `PENDING_DEFINITION` on Doppler solar-K path.  
2. BF080 staging / benchmark detox (parallel).
