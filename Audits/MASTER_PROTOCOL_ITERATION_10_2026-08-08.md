# Master Protocol — Iteration 10 (GOM30 ODF Observable Decode)

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Upstream:** Iteration 9 FIELD_CENSUS_PASS

## Result

| Gate | Result |
|---|---|
| Label-scaled `obs_Hz` decode | PASS (7447 finite) |
| Reference-frequency field | PASS (constant 2.116648992 GHz; S-band scale / Ka IDs noted) |
| Validity | all good |
| Multi-day freeze list | 8 ODFs enumerated; 1 HAVE / 7 PENDING_FETCH |
| Mirror fetch (Atmospheres/Geosciences guesses) | all 404 |
| SDT residual | PENDING_DATA |

**Status:** `OBSERVABLE_DECODE_PASS / PENDING_FETCH / PENDING_RECONSTRUCTION`

## Cascade

| Path | Status |
|---|---|
| ODF structure (GOM28) | STRUCTURE_PASS |
| ODF field census (GOM29) | FIELD_CENSUS_PASS |
| ODF Hz decode (GOM30) | OBSERVABLE_DECODE_PASS |
| Multi-day conjunction coverage | PENDING_FETCH |
| Geometry/clock residual | PENDING_RECONSTRUCTION |
| TDF | STRUCTURE_PARTIAL |
| BF080 absolute δ | PENDING_ACCESS |
| GOM26 multi-year C4 | COMPATIBLE (I7) |

## Next tests (ranked)

1. Authoritative PDS volume path for `XMMMV0` day-157 + days 158–160 ODFs.  
2. Non-conjunction fixture confirming observable unit path (kHz field vs residual).  
3. Light-time geometry pre-registration (Horizons/SPK + station) — no `ϟ` fit.  
4. NRAO BF080 staging (human).  
5. Benchmark detox propose-and-wait.
