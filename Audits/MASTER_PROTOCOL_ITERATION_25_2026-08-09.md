# Master Protocol - Iteration 25 (NP32 Prediction Eligibility)

**Date:** 2026-08-09
**Branch:** nuclear scission-surface selection

## Decision

`EMPIRICAL_REGULARITY_REPRODUCED_NOT_SDT_PREDICTION`.

## Evidence and correction

- Eight hash-registered IAEA independent-yield tables reproduce the historical
  stationary-heavy/sliding-light summary under its frozen extraction rule.
- The sole NP32 computation only loads those yields and calculates centroids,
  slopes, and valley statistics. It has no contact graph, bond/cost definition,
  cut/partition minimization, or pre-data forward split output.
- The N=82/Z=50 anchor is explicitly imported as a session measurement, not
  derived by a frozen mechanism in this branch.
- Historical P3 is false under its own every-system `[1.5,4.0]` gate: the
  reproduced U-235 value is `4.3766499781`. P4 remains refuted as reported.

## Scope boundary

This does not reject SDT or the observed yield pattern. It rejects the claim
that this branch tested a zero-fit SDT minimum-cut predictor. No standard-model
output or fitted comparator was used in reaching that conclusion.

## Next gate

Require an executable native graph/cost/min-cut mechanism and an independently
derived anchor before opening preregistered holdout yield distributions. Do not
relax P3 or retrofit a cut rule to the eight already examined systems.
