# GOM27 D5 BF080 Catalogue Extract Specification

**Date:** 2026-08-07  
**Status:** frozen before catalogue-file retrieval.

## Archive query

- **Service:** NRAO TAP endpoint `https://data-query.nrao.edu/tap/sync`
- **Protocol:** `REQUEST=doQuery`, `LANG=ADQL`, `FORMAT=csv`
- **Query:**

```sql
SELECT project_code, target_name, t_min, t_max, s_ra, s_dec,
       center_frequencies, access_format, access_estsize,
       proprietary_status, obs_id, scan_num
FROM tap_schema.obscore
WHERE project_code = 'BF080'
ORDER BY t_min, obs_id, scan_num
```

## Intended use

This CSV records public catalogue metadata for the candidate 2005 VLBA program.
It is used only to establish project identity, observing coverage, data-product
format, access status, and missing reconstruction inputs. It contains no
angular-deflection observable and must not be compared to GOM27 predictions.

## Required checks after retrieval

1. SHA-256 and byte size are written to the dataset manifest before parsing.
2. Project code is uniformly `BF080`.
3. The four designated source names and the eight reported October sessions are
   present.
4. Product format and access metadata are reported without assuming that public
   raw correlator output is a calibrated deflection result.
5. The archive result is classified `PENDING_RECONSTRUCTION` unless it supplies
   the calibration chain and b-resolved angular offsets required by the D5
   pre-registration.
