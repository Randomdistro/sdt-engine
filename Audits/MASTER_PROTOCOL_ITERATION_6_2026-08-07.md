# Master Protocol — Iteration 6 (GOM20 GPS Anchor)

**Date:** 2026-08-07  
**Branch:** GOM20 clock transport / GPS

## Decision

`PENDING_MECHANISM`; physical claim `UNADJUDICATED`.

The available GPS value is an engineering configuration, not a qualifying
independent clock observation. The retained historical NAVSTAR-4 metadata is
explicitly correction processed and lacks a data series. No fit or external
theory comparison was performed.

## Retained findings

- The configured `-4.4647e-10` offset has a `38.575008 μs/day` compensation
  magnitude; its `0.124992 μs/day` difference from the GOM20 target exceeds
  GOM20's proposed tolerance.
- The model-author amendment requires polar-radius `koppa`, baryon-volume and
  spation-shell exclusions, inverse-square fall-off, then movement budget.
  All ingredients are recorded but no dimensions, signs, normalizations, or
  composition equation is yet defined.
- The current implementation exposes two leading-order-incompatible depth-rate
  laws, and GOM20 does not choose one.
- Two audit-instrument false positives were identified, traced, and repaired;
  the final run passes all source hash checks.

## Next gate

Complete the amended equation and freeze its observed inputs before retrieving
a direct, timestamped satellite/ground clock-comparison set. The later test
must compare the signed SDT prediction directly to observation with correction
provenance and uncertainty; existing frameworks are not a rejection gate.
