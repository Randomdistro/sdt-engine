# NP12b Assessment — Close-Pack Boundary Radius Reproduction

**Date:** 2026-08-09  
**Pre-registration:** `NP12b_PRE_REGISTRATION.md`  
**Instrument:** `np12b_closepack_radius_audit.cpp`  
**Stdout:** `.audit-tmp/np12b_run.txt`  
**Compiler:** MSVC `/std:c++20 /O2` via VsDevCmd x64  
**Canon edited:** no

## Status

`CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION`

## Provenance

| Source | SHA-256 | Bytes | Gate |
|---|---|---:|---|
| `Datasets/nuclear/IAEA_ground_states_radii.csv` | `8aee5dc…12c795` | 900,613 | PASS |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb…255835b` | 97,482 | PASS |

Instrument validation (A=1, A=4 hand vs `nuclear_boundary_radius`) PASS at ≤1e−16 relative.

## Results (direct run)

| Domain | N | RMS_rel |
|---|---:|---:|
| All accepted | 908 | 0.0496 |
| A &lt; 16 | 23 | 0.212 |
| 16 ≤ A &lt; 40 | 51 | 0.107 |
| A ≥ 40 | 834 | 0.0273 |
| **A ≥ 16 (adjudication)** | **885** | **0.0370** |

Mean |rel| (A≥16) = 0.0270; max |rel| = 0.214.

Delete-test diagnostic (not a rival rejection criterion): retracted `R = Z·R_p` on the same A≥16 set has RMS_rel = 9.02 (244× worse than close-pack). The dimensionality exclusion of the linear-Z law stands.

## Decision rule application

Pre-registered: survive if `RMS_rel(A≥16) ≤ 0.08`. Observed 0.0370 → **SURVIVES**.

No `r₀`, liquid-drop coefficient, or standard-model prediction entered the gate.

## Scope / Limitations / Residuals

- **Shared-input:** `R_p` is a measured derivation basis constant and also enters `R(A)`. Tabulated nuclear radii are an independent compilation; this run does not claim independence from `R_p`.
- **Light nuclei:** A&lt;16 residual remains large (RMS_rel ≈ 21%). Not used to exclude the heavy-domain law under the pre-registered domain.
- **Observable class:** IAEA column is RMS charge radius; the formula is a boundary-radius construction. Agreement at the few-percent level does not prove charge-distribution identity.
- **Does not reopen** NP21 geometric-floor tuning, Cassini residual, or BF080.

## Cascade

Investigation-level support for the post-NP12 canon form `nuclear_boundary_radius(A)`. No `laws.hpp` edit required by this reproduction. Light-A residual remains an open local debt.
