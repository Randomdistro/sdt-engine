# Master Protocol Iteration 5 — BF080 Staging Gate

**Date:** 2026-08-07  
**Rule set:** experimental/observational inputs only; no standard-framework
parameter is used as an SDT rejection gate.

## Objective

Attempt to move the verified BF080 campaign from archive metadata to a
checksum-verifiable raw-data subset without issuing an e-mail request or
starting a model-dependent reduction.

## Outcome

| Gate | Result |
|---|---|
| Pre-registered earliest-session selection | PASS |
| Six public execution blocks identified | PASS |
| First raw UVFITS identity and scan metadata | PASS |
| Direct non-interactive raw retrieval | FAIL — no delivery URL exposed |
| Calibration/reconstruction | NOT RUN |
| Deflection residual | NOT RUN |
| Data-path status | `PENDING_ACCESS / PENDING_RECONSTRUCTION` |

## Corrective finding

The archive detail endpoint requires a UVFITS filename rather than the TAP
publisher identifier. That assumption was tested, failed with a 404, corrected,
and retained. The corrected query proves metadata access only. It does not
justify treating the public catalogue as a calibrated angular measurement.

## Next gate

Human-mediated NRAO Archive Access Tool staging is now the explicit external
dependency. After the six raw files and calibration inputs are frozen, begin a
fresh pre-registered reconstruction loop; do not inherit a physical verdict
from this access audit.
