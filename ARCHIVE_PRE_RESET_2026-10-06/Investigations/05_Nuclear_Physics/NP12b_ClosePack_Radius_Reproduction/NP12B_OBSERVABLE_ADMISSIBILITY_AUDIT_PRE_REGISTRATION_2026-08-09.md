# NP12b observable-admissibility audit — pre-registration

**Status:** FROZEN BEFORE THIS AUDIT PARSES THE IAEA RADIUS CSV
**Date:** 2026-08-09
**Objective:** Reproduce the historical direct numerical proxy comparison, then determine whether it is an admissible observational test of the stated SDT boundary-radius formula.

## Initial conditions and question

The fixed hypothesis is the canonical function `nuclear_boundary_radius(A) = R_p (A/eta)^(1/3)` with `eta = pi/sqrt(18)`, evaluated with mass number `A = Z + N`.  The target table is identified in the historical pre-registration and manifest as an IAEA/Angeli–Marinova **RMS charge-radius** compilation.  The formula and the target are therefore observationally comparable only if a frozen native map connects the formula's boundary radius to the tabulated RMS charge radius.

The audit asks two separate questions:

1. Does the fixed direct proxy calculation reproduce the declared `RMS_rel(A >= 16)` from the hash-registered table without fitting a coefficient?
2. Does the branch define and execute a physical boundary-to-RMS observable map before using that calculation to support the boundary-radius law?

No liquid-drop coefficient, standard-model radius prediction, fit, rescaling, or rival framework is allowed to set the pass/fail conclusion.  A conventional mapping may be described only to identify the missing variable definition; it cannot rescue or reject the law post hoc.

## Frozen source inventory

| Source | Expected SHA-256 | Expected bytes | Role |
|---|---|---:|---|
| `Datasets/nuclear/IAEA_ground_states_radii.csv` | `8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795` | 900613 | observational target; do not parse before all identity gates pass |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | 97482 | canonical formula and variable label under audit |
| `NP12b_PRE_REGISTRATION.md` | hash and freeze before conclusion | existing historical gate |
| `NP12b_ASSESSMENT.md` | hash and freeze before conclusion | historical classification |
| `np12b_closepack_radius_audit.cpp` | hash and freeze before conclusion | historical computation |
| `Datasets/MANIFEST.md` | hash and freeze before conclusion | cached-data provenance and observable label |

An identity mismatch produces `PROVENANCE_BLOCKED` with no CSV parsing.

## Frozen method

1. Hash and byte-count every listed source.  Record complete identities.  Stop before parsing observations if either the raw CSV or canonical law fails.
2. Inspect the fixed law, historical pre-registration, historical instrument, assessment, and manifest for: (a) the hypothesis output's variable meaning; (b) the measurement-column meaning; and (c) an executable, parameter-free transformation from the former to the latter.  A bare assertion that charge radius is “boundary radius” is not a transformation.
3. Only after the gates pass, independently parse the CSV with a standards-compliant CSV reader.  Apply the historical inclusion rule exactly: integer `Z >= 1`, integer `N >= 0`, finite `radius > 0.1 fm`, and `A = Z + N`; adjudication subset `A >= 16`.
4. Recompute the direct proxy `R_p * 1e15 * cbrt(A/eta)`, the relative residual to the table's `radius`, and `RMS_rel`.  No coefficient, threshold, data row, unit, or variable definition may be altered.
5. Independently calculate only the historical gates: survival at `RMS_rel <= 0.08`, exclusion at `RMS_rel > 0.20`, otherwise unadjudicated.  Keep this as a **proxy-numerical** result, not as a physical verdict, unless Step 2 supplies the required map.

## Decision table

| Condition | Required record |
|---|---|
| Source identity fails | `PROVENANCE_BLOCKED` |
| Direct proxy fails historical numerical gate | report the original numeric classification; boundary law fails that proxy test |
| Direct proxy passes but no frozen boundary-to-RMS map exists | `PROXY_REPRODUCED_OBSERVABLE_MISMATCH`; physical boundary-law verdict `UNADJUDICATED` |
| Direct proxy passes and a native, executable, zero-fit map exists | apply historical gate as an observational test of the mapped law |
| A historical document calls the direct proxy confirmation despite a declared observable mismatch | correct it; do not replace the missing map with a fitted factor |

## Error control and reopening path

- The test does not deny that a boundary radius and an RMS charge radius can be related under additional physical assumptions; it requires those assumptions and their parameters to be stated and derived by SDT before comparison.
- The resulting admissibility conclusion is limited to the fixed `nuclear_boundary_radius` branch and this target observable.  It is not a global SDT verdict.
- To reopen a physical test, define the charge-density or boundary-to-RMS map, include charge weighting and finite-proton treatment if required by the model, derive all quantities without the target radii, and preregister a fresh holdout dataset.
- Canonical law files remain read-only.  No attempt to change `R_p`, `eta`, or a conversion factor is permitted in this audit.
