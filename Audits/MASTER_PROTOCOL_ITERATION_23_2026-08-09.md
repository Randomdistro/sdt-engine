# Master Protocol - Iteration 23 (Cassini Branch Deferral)

**Date:** 2026-08-09
**Decision:** move the GOM36-to-GOM40 Cassini Doppler/local-K branch to the
back of the active queue.

## Reason

GOM40 exhausted the only newly justified parameter-grammar recalculation:
local-K cannot clear the registered amplitude or time-confound gates. The
remaining work is producer-applicable ODF scale/intermediate-frequency/ramp
reconstruction or an independently calibrated delay/range product. Further
local parameter changes would be post-data tuning, not falsification.

## Deferred status

| Branch | Status | Re-entry condition |
|---|---|---|
| GOM36-GOM40 Cassini Doppler/local-K | `DEFERRED_OBSERVABLE_DEFINITION` | Freeze a producer-applicable observable definition or independently calibrated delay/range product |
| GOM25 TDF/ODF decoder | `DEFERRED_DOCUMENTATION_GAP` | Obtain a producer-applicable TRK grammar or binary fixture resolving the retained conflicts |
| GOM27 BF080 deflection | `DEFERRED_ARCHIVE_ACCESS` | Human-stage raw data and calibration inputs |
| GOM20 GPS clock transport | `DEFERRED_MODEL_SPECIFICATION` | Supply a signed, dimensionally closed clock equation |

## Selection rule for the next branch

Choose only a claim that has a complete SDT prediction, named observable,
pre-registerable primary experimental/observational source, no rival-framework
quantity as a rejection criterion, and no unresolved decoder or author-equation
dependency. Retain every negative result and source conflict.
