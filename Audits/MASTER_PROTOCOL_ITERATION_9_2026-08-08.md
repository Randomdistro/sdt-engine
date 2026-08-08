# Master Protocol — Iteration 9 (GOM29 ODF Field Census)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 8 ODF STRUCTURE_PASS

## Result

Label-driven decode of the SCE1 ODF Orbit Data Group:

| Gate | Result |
|---|---|
| Rows | 7447 (matches label) |
| FORMAT ID | 2 (all) |
| Data type | 12 = two-way Doppler (all) |
| Stations | RX=TX=25 |
| Time span | 2002-06-06 20:41:30.5 – 22:45:36.5 UTC |
| Residual | PENDING_DATA |

**Status:** `FIELD_CENSUS_PASS / PENDING_RECONSTRUCTION`

## Cascade

ODF path now has structure + field metadata. Empirical Shapiro-like marker still
blocked on multi-day conjunction coverage + independent geometry/clock/media.
TDF path remains STRUCTURE_PARTIAL. BF080 absolute δ still PENDING_ACCESS.

## Next tests

1. Inventory/freeze additional SCE1 ODF days around conjunction (not only 157).  
2. Non-conjunction fixture validation of observable→Hz conversion.  
3. Geometry/light-time reconstruction pre-registration.  
4. NRAO BF080 staging (human).  
5. Benchmark detox propose-and-wait.
