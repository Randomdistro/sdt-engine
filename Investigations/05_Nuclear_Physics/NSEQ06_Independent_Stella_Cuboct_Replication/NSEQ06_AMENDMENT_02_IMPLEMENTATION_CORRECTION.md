# NSEQ06 Amendment 02 — Implementation Correction Before Acceptance

**Date:** 2026-08-09  
**Status of prior output:** invalidated; no scientific verdict accepted from it.

The first two deterministic executions after Amendment 01 exposed two audit-code
errors. They are recorded rather than interpreted as failures of the proposal.

| Error origin | Incorrect behaviour | Correction |
|---|---|---|
| NSEQ06 cuboct direction generator | Constructed the expected twelve directions with an invalid conditional index mapping, so a true cube-edge-midpoint equality was reported as F2 `FAIL`. | Construct each direction by assigning the two signs to the two non-zero coordinate positions. |
| Auditor's unregistered expectation | Added a test that exactly three Q-Q selections would be invariant under the pre-registered `C3 × inversion` group. The pre-registration requires exhaustive enumeration, not that result. | Remove the expectation; report the actual cardinality and topology of each invariant selection. |

The source freeze remains valid: no frozen input changed after Amendment 01. The
corrected script is rerun twice and only its new deterministic output is used in
the NSEQ06 result report. This amendment narrows the prior proposed correction:
the two-branch statement is not rejected unless the corrected enumeration fails
to recover it under the stated group.
