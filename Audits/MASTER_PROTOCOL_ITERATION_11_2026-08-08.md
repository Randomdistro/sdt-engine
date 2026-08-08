# Master Protocol — Iteration 11 (GOM31 Multi-Day ODF Decode)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 10 OBSERVABLE_DECODE_PASS; Atmospheres `v10` volume path confirmed

## Result

| Gate | Result |
|---|---|
| Local CORS_0021 inventory (8 ODFs) | PASS (8/8 HAVE) |
| Label-pointer row bounds vs `ROWS` | PASS on all files |
| Finite `obs_Hz` / positive `f_ref` | PASS (451022 rows) |
| Authoritative URL | `…/co-ss-rss-1-sce1-v10/cors_0021/` (`v10`, not `v1.0`) |
| SDT residual | PENDING_DATA |

**Status:** `MULTIDAY_DECODE_PASS / PENDING_RECONSTRUCTION`

## Cascade

| Path | Status |
|---|---|
| ODF structure (GOM28) | STRUCTURE_PASS |
| ODF field census (GOM29) | FIELD_CENSUS_PASS |
| ODF Hz decode (GOM30) | OBSERVABLE_DECODE_PASS |
| Multi-day conjunction coverage (GOM31) | **MULTIDAY_DECODE_PASS** |
| Geometry/clock residual | PENDING_RECONSTRUCTION |
| Observable unit path | UNADJUDICATED |
| TDF | STRUCTURE_PARTIAL |
| BF080 absolute δ | PENDING_ACCESS |
| GOM26 multi-year C4 | COMPATIBLE (I7) |

## Next tests (ranked)

1. Fixture confirming type-12 `obs_Hz` unit path (residual vs count-rate).  
2. Pre-register light-time geometry (Horizons/SPK + station) — no `ϟ` fit; DSS-25 type-12 first.  
3. NRAO BF080 staging (human).  
4. Benchmark detox propose-and-wait.
