# NP12b observable-admissibility audit — results

**Audit status:** COMPLETE
**Numerical proxy:** reproduced
**Physical boundary-law verdict:** UNADJUDICATED
**Required correction:** `PROXY_REPRODUCED_UNDER_UNDERIVED_SURFACE_CHARGE_MAPPING`

## What was tested

The hash-registered IAEA ground-state `radius` column was independently reduced using the exact historical inclusion rule.  The fixed canonical expression was reproduced without fitting:

```text
R_proxy(A) = 0.8414 fm * cbrt(A / (pi / 4.242640687119285)).
```

The source gate passed for the IAEA table, canon, historical NP12b artifacts, manifest, and the previously discovered NP12 mapping artifacts.  Full identities are frozen in `NP12B_OBSERVABLE_ADMISSIBILITY_SOURCE_FREEZE_2026-08-09.md`.

## Reproducible observational result

The independent parser accepted 908 rows, skipped 2478 rows under the precommitted domain rule, and retained 885 rows with `A >= 16`.  It reproduces the historical direct-proxy gate:

| Domain | N | RMS relative residual |
|---|---:|---:|
| all accepted | 908 | `0.0496430583` |
| `A < 16` | 23 | `0.2115321386` |
| `16 <= A < 40` | 51 | `0.1071866411` |
| `A >= 40` | 834 | `0.0273228576` |
| **`A >= 16`** | **885** | **`0.0369539479`** |

Under NP12b's original numerical threshold alone, `0.0369539479 <= 0.08`, so the label `CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION` is reproduced as a statement about the direct proxy calculation.  No fitted coefficient, data exclusion beyond the frozen domain rule, or competing framework was used.

## Observable conflict and origin of error

The canonical function calls its output a **nuclear boundary radius**, while NP12b's target and its own assessment identify the IAEA quantity as an **RMS charge radius**.  The assessment already discloses that distinction, but it still promotes the direct comparison to investigation-level support for the boundary law.

The repository's earlier NP12 code resolves the hidden assumption: it names the unconverted close-pack form the **surface-charge limit** and labels the associated periphery-charge strength **un-derived**.  In the same prior analysis, a `sqrt(3/5)` uniform-limit conversion is distinct and fails.  The audit does not use that alternate result as a rejection criterion; it establishes that the direct metric selects a charge-distribution endpoint rather than deriving a boundary-to-RMS observable map.

The error is therefore not arithmetic or data provenance.  It is an inference error: treating agreement under an un-derived surface-charge assignment as an observational test of a differently defined boundary radius.  An ontological re-labeling of the target quantity does not supply the missing measurement map.

## Correction and scope

- Keep the `3.695%` result as `DIRECT_PROXY_REPRODUCED`.
- Replace physical “survives” support for `nuclear_boundary_radius` with `UNADJUDICATED` until SDT derives and executes a boundary-to-RMS map.
- Do not declare the close-pack `A^(1/3)` geometry false. This audit does not test that geometry against a like-for-like observable.
- Do not alter `R_p`, `eta`, or introduce a fitted conversion factor. Canonical files remain untouched.

The audit instrument is `np12b_observable_admissibility_audit.py` (SHA-256 `719ebce5dd359a25a9d3bdcd1fa091e973efff6b2995b57864df704156ff6ae5`).  Its deterministic JSON result is `np12b_observable_admissibility_audit_results.json` (SHA-256 `a63cda4c2b1fb0e0a573389eb4f31180c9b0380adf5f448e0583155afcfeeae7`).

## Reopening gate

Before calling this a physical radius prediction, freeze a new, executable SDT derivation that maps the boundary construction to the IAEA measurement.  It must specify the predicted radial observable, its density or boundary profile, charge weighting and finite-proton treatment where needed, all parameters and units, and a source-registered holdout comparison.  The map must be fixed without using the target radii; only then may the measured RMS column adjudicate the boundary law.
