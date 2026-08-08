# NP12b Close-Pack Boundary Radius Reproduction — Pre-Registration

**Date:** 2026-08-09  
**Branch:** nuclear radius law currently in `sdt::laws::nuclear::nuclear_boundary_radius`  
**Role:** master-protocol Iteration 25 — independent reproduction against frozen IAEA/Angeli radii  
**Canon edited:** no

## Objective

Test whether the zero-fit close-pack formula adopted after NP12,

```text
R(A) = R_p · (A / η)^(1/3),   η = π/√18
```

reproduces measured nuclear RMS charge radii from the frozen IAEA ground-state table
within pre-committed tolerances. Rejection uses measurement only. No standard-model
`r₀`, liquid-drop fit, or rival coefficient may enter the pass/fail rule.

## Provenance gate (before numeric parse)

| Source | SHA-256 | Bytes | Class |
|---|---|---:|---|
| `Datasets/nuclear/IAEA_ground_states_radii.csv` | `8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795` | 900,613 | IAEA ground-state radii compilation (Angeli & Marinova lineage); OBSERVED radii column |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | 97,482 | Hypothesis under test (`nuclear_boundary_radius`) |

If either hash fails at run time → `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION`.

## Fixed prediction

Call `sdt::laws::nuclear::nuclear_boundary_radius(A)` with `A = Z + N` from the table.
Convert metres → fm by `× 1e15`. Do not refit `R_p` or `η`. Do not edit `laws.hpp`.

**Shared-input note (not a rejection criterion):** `R_p` is a measured whitelist
constant and also appears in the prediction. The tabulated nuclear radii are an
independent compilation; the shared-input is recorded as Scope, not as a PASS.

## Scan domain

Include a row only if:

1. `z` parses as integer `Z ≥ 1`
2. `n` parses as integer `N ≥ 0`
3. `A = Z + N ≥ 1`
4. `radius` parses as finite and `radius > 0.1` fm (excludes the free-neutron negative entry)

No abundance or stability filter. Report light (`A < 16`), mid (`16 ≤ A < 40`), and
heavy (`A ≥ 40`) subsets as diagnostics; the adjudication domain is `A ≥ 16`.

## Metrics (committed before parse)

Primary:

```text
RMS_rel = sqrt( mean( (R_pred / R_meas − 1)^2 ) )   over A ≥ 16
```

Diagnostics (not pass/fail): median |rel|, max |rel|, N rows, light/mid/heavy RMS_rel,
and the retracted form `R = Z · R_p` RMS_rel on the same `A ≥ 16` set (delete-test:
must be worse than close-pack by more than 10× if the dimensionality kill stands).

## Pre-committed decision

| Condition | Classification |
|---|---|
| Hashes pass; `RMS_rel(A≥16) ≤ 0.08` | `CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION` |
| Hashes pass; `RMS_rel(A≥16) > 0.20` | `CLOSE_PACK_RADIUS_EXCLUDED` |
| Hashes pass; `0.08 < RMS_rel(A≥16) ≤ 0.20` | `CLOSE_PACK_RADIUS_UNADJUDICATED` |
| Hash failure | `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION` |
| Parser/domain failure after hashes pass | `INSTRUMENT_OR_DOMAIN_FAILURE` |

These labels adjudicate only this fixed formula vs this frozen table. They do not
accept or reject SDT wholesale. Rival `r₀·A^(1/3)` is not computed for rejection.

## Instrument validation (before full scan)

On synthetic rows: `A=1` → `R_pred = R_p / η^(1/3)`; `A=4` → `R_pred = R_p · (4/η)^(1/3)`.
Both must match a hand calculation to relative `1e-12`. Then open the CSV.

## Out of scope

- Cassini residual / TDF decoder / BF080 / GOM20 (deferred Iteration 23)
- NP21 geometric-floor ratio retuning (Iteration 24)
- Canon edits to `laws.hpp`
- Fitting any coefficient to the IAEA table
