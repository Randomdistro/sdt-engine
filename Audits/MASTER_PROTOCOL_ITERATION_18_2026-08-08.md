# Master Protocol — Iteration 18 (GOM38 Range / Light-Time)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 17 Doppler path blocked

## Result

| Gate | Result |
|---|---|
| Type-37 census (XMMMV0) | PASS — 793 rows; X-band uplink |
| Absolute RTLT from RU/F | not recovered (no fitted scale) |
| Frozen-**K** Shapiro Δt | 6.58×10⁻⁵ s @ ~41.7 R_☉ |
| Resolvability Δt_K/σ | 8.6×10⁻⁶ → **RANGE_K_UNRESOLVED** |
| Doppler–solar-K path | **PENDING_DEFINITION** |

**Status:** `RANGE_K_UNRESOLVED` + Doppler path administratively closed pending definition.

## Cascade

| Path | Status |
|---|---|
| ODF Doppler vs solar **K** | PENDING_DEFINITION (GOM36–37) |
| ODF type-37 range vs solar **K** | RANGE_K_UNRESOLVED (GOM38) |
| Orbital **K** (GOM26) | still investigation IC |
| δ(b) empirical (GOM27/BF080) | PENDING_ACCESS |
| Spectral (GOM25) | COMPATIBLE / UNADJUDICATED |

## Next tests (ranked)

1. BF080 absolute deflection staging (human NRAO) / GOM25 mechanism.  
2. GOM20 clock equation.  
3. DAT-only RU modulo reconstruction (optional).  
4. Benchmark detox propose-and-wait.
