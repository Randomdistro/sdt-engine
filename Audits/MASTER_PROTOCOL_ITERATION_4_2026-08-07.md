# Master Protocol Iteration 4 — BF080 Provenance Gate

**Date:** 2026-08-07  
**Scope:** one bounded discovery loop under the experimental/observational-only
rule. No canonical law, SDT parameter, or theory equation was changed.

## Trigger

GOM27 had a frozen whole-range deflection prediction but no admissible
absolute deflection table. The published Fomalont gamma/residual summary
remained excluded rather than repurposed as a direct SDT target.

## Procedure

1. Re-ranked outstanding gates: absolute b-resolved deflection outranked the
   source-blocked Cassini grammar path.
2. Pre-registered the observable, provenance, and exclusion rules in
   `GOM27_D5_ABSOLUTE_VLBI_DISCOVERY_PRE_REGISTRATION.md`.
3. Queried NRAO's public observational archive metadata and froze the BF080
   extract plus access documentation with manifest hashes.
4. Checked project identity, four source names, eight session dates, product
   access state, and presence of required observable fields.

## Result

| Item | Classification |
|---|---|
| BF080 campaign identity | PASS |
| Public raw-product discovery | PASS |
| Catalogue as angular-deflection observable | FAIL — required fields absent |
| GOM27 numerical comparison | NOT RUN |
| Empirical SDT verdict | UNADJUDICATED |
| Data path | PENDING_RECONSTRUCTION |

## Error correction and cascade

The earlier blanket `PENDING_DATA` label is narrowed: a relevant raw campaign
has been identified, but its data have not been reconstructed into an
uncertainty-bearing, b-resolved observable. Treating public execution-block
metadata as a measurement would be a category error. No previously computed
prediction, spectral result, or Cassini status changes.

## Next gate

Stage a fixed BF080 raw subset through the NRAO Archive Access Tool, freeze its
checksums and calibration inputs, validate a correlator-to-angle pipeline on a
non-solar fixture, then run the pre-registered GOM27 residual test without
retuning the solar profile.
