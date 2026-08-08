# Master Protocol — Iteration 7 (GOM26 C4 Multi-Year Hold-Out)

**Date:** 2026-08-07  
**Branch:** GOM26 solar orbital invariant

## Decision

The pre-registered 2024 C4 hold-out is `COMPATIBLE`:
`|Δkoppa|/koppa = 3.508332e-04 < 1e-3`. It is a formal construction check on
JPL's processed DE441 state vectors, not empirical confirmation of SDT.

## Integrity and correction

- The discovered 2024 file was source-accepted before numerical parsing, with
  checksum, Sun-centered header, interval, cadence, and 27-row structure
  recorded in the GOM26 source-acceptance record.
- The first output falsely displayed zero rows because of a hard-coded reporting
  value. The tool was repaired, recompiled, and rerun; both samples now report
  `27 (of 27)`. The numerical estimates and gates were unaffected.
- C3 remains `COMPATIBLE / UNADJUDICATED`; no physical pass is promoted from a
  model-processed ephemeris or from a nuisance-limited published line-shift
  summary.

## Cascade

The multi-year C4 caveat is narrowed but the main observational gap remains:
absolute solar deflection data or independently reconstructed propagation
residuals. The next discriminating tests remain BF080 raw-visibility reduction
and Cassini TDF clock/geometry reconstruction. No canonical files changed.
