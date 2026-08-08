# Master Protocol - Iteration 22 (GOM40 Local-K Robustness)

**Date:** 2026-08-09
**Branch:** Cassini multi-day Doppler residual

## Decision

`LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES`; physical SDT verdict
`UNADJUDICATED`.

## Recalculated outcome

- The GOM39 local-K correction decreases the frozen proxy by 1.402987%; it does
  not alter the train-only residual or the time correlation.
- The GOM37 amplitude ratio changes from `7.0741069e6` to `7.1747680e6`, still
  far above the registered limit of `100`; the time delete-test remains
  confounded.
- The former recovery idea is therefore falsified narrowly: this local-K
  substitution alone cannot cure the GOM37 fixed-pipeline failures.
- All pre-registered raw ODF, label, processed-geometry, and instrument hashes
  passed before parsing. No data was retrieved and no parameter was fitted.

## Integrity correction

The first GOM40 draft sampled raw record indices rather than the filtered-row
indices used by GOM37. Review caught and repaired the discrepancy before any
numeric output. The final run reproduces GOM37 exactly at its frozen K value.

## Boundary and next gate

This is not an SDT exclusion because ODF scale/intermediate-frequency and media
definitions remain unresolved and the geometry input is processed. The next
eligible Cassini step is a producer-applicable observable-definition recovery
or an independently calibrated delay/range product; no K retuning is allowed.
