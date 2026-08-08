# Master Protocol - Iteration 24 (NP21 AME2020 Reproduction)

**Date:** 2026-08-09
**Branch:** nuclear binding resistance landscape

## Decision

`GEOMETRIC_FLOOR_KILL_CONFIRMED` for the fixed zero-fit NP21 functional.

## Evidence and result

- The canonical AME2020 table and the historical duplicate match byte-for-byte;
  the path split is recorded as source hygiene, not a data discrepancy.
- An independent parser and evaluator scanned 284 alpha-valid natural-basis
  nuclides from the registered AME2020 evaluated experimental target.
- The fixed geometric functional places its minimum at U-238, not in the
  pre-registered Fe/Ni window `A in [54,64]`; the miss is 182 mass units.
- The no-fit rank diagnostic is negative (`-0.5739768`), consistent with the
  floor failure. No standard-framework prediction or fitted coefficient was
  used as a rejection rule.

## Scope boundary

This kills only the claim that the stated geometric coefficient ratio derives
the iron-region floor. It does not reject SDT wholesale and does not validate
the historical fitted branch, which remains calibrated by construction.

## Next gate

Do not tune the ratio against AME2020. A new native derivation of the
spread-to-surface weight ratio, frozen before examining the target, is required
to reopen the geometric-floor claim.
