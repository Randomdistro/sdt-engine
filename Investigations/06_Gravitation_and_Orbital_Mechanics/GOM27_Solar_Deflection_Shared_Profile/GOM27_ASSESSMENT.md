# GOM27 Assessment — Solar Deflection Shared Profile

**Date:** 2026-08-07  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom27_deflection_profile.cpp`  
**Source SHA-256:** `055A60381104ADEF2ED7D8BCFE8D1812213B4D41CE64471D615D7FF94B002E84`  
**Stdout:** `.audit-tmp/gom27_run.txt`  
**Canon edited:** no  
**Evidence rule:** codebase audits are not inputs. Statuses from frozen datasets, GOM26 cal ϟ, `laws.hpp` hypothesis, and this stdout only.

## 1. Scope

Shared-profile test: freeze GOM26 `ϟ = 1476.351201 m`, set `n = c/c_far = 1/(1−ϟ/r)²`, compute `δ(b)` over the pre-registered impact-parameter scan.

## 2. Claim ledger

| Claim ID | Claim | Status |
|---|---|---|
| GOM27-C1 | Weak-field analytic `δ_wf = 4ϟ/b` from `n = 1+2ϟ/r+…` | DERIVED (algebra); numerical recovery PASS at `b=5 R_Sun` |
| GOM27-C2 | Whole-range COMPUTED `δ(b)` from frozen ϟ, no new coefficient | COMPUTED — ledger in stdout |
| GOM27-C3 | Empirical `δ(b)` vs independent absolute deflection table | **PENDING_DATA** (Fomalont products are MODEL-PROCESSED γ/PPN fits; no admissible absolute b-scan) |
| GOM27-C4 | Limb single-point vs ~1.75″ literature scale | **UNADJUDICATED** (informational only; not a survival criterion) |
| GOM27-D4 | Cassini ranging residual | **PENDING_DATA** |

## 3. Mechanism

Far-frame refractive index from relay profile. Ray turning condition `b = n(r₀)r₀`. Deflection `δ = 2φ_half − π`.

## 4. Inputs

| Input | Value | Label | Source |
|---|---:|---|---|
| ϟ | 1476.351201 m | DERIVED | GOM26 cal stdout (Horizons 2025) |
| R_Sun | `measured::R_Sun` | CONVENTIONAL | engine measured derivation basis |
| c | SI exact | MEASURED-INPUT | engine |
| bridge::koppa_Sun | unused | — | delete-test |

## 5–6. Pre-registration / validation

`PROMPT.md` fixed before execution. Validation A–D: PASS.

## 7. Prediction ledger (COMPUTED)

| b/R_Sun | δ [arcsec] | 4ϟ/b [arcsec] |
|---:|---:|---:|
| 1.01 | 1.733593 | 1.733530 |
| 1.05 | 1.667544 | 1.667491 |
| 1.10 | 1.591771 | 1.591696 |
| 1.20 | 1.459102 | 1.459055 |
| 1.50 | 1.167292 | 1.167244 |
| 2.00 | 0.875482 | 0.875433 |
| 3.00 | 0.583676 | 0.583622 |
| 5.00 | 0.350209 | 0.350173 |
| 10.00 | 0.175123 | 0.175087 |
| 1.00 (limb) | 1.750844 | 1.750866 |

Relative (δ − 4ϟ/b)/(4ϟ/b) ≤ 2.1×10⁻⁴ over the scan.

## 8. Data provenance (D5)

| File | SHA-256 | Class |
|---|---|---|
| `raw/fomalont_vlba_deflection_2009.pdf` | `66c1f9a90b3b5481d04b9ecc36f8ee4bd3a4a39b7f44b2c00042b4f23275fb6b` | paper |
| `raw/fomalont_vlba_2009_ar5iv.html` | `bb970a51d97cb171fa37ebd6910dd8fcc7b361b07776421d9c24f9bdaba0c9ce` | HTML tables |

Fomalont Table 4/5 products report deflection *changes* and γ solutions under a PPN propagation equation → MODEL-PROCESSED. Not used as a load-bearing SDT absolute-δ(b) target.

## 9. Classification

- EMPIRICALLY SURVIVES: none (no admissible absolute δ(b) table)  
- EMPIRICALLY EXCLUDED: none  
- COMPUTED: δ(b) ledger  
- PENDING_DATA: whole-range empirical deflection; Cassini D4  
- UNADJUDICATED: limb single-point literature note  

## 10. Root cause (data gate, not profile failure)

1. Failed exactly: nothing numerically failed; empirical gate lacks an absolute δ(b) product.  
2. Observable owed: absolute deflection vs impact parameter / elongation with uncertainty, independent of a γ fit used as SDT input.  
3. Premise: treating PPN-fitted VLBI summaries as absolute δ(b) would import competitor machinery.  
4. Local to D5 data admissibility.  
5. Freedom: obtain/reconstruct absolute angular offsets vs solar elongation from primary VLBI observables.  
6. That freedom is DATA, not a coefficient.  
7. Downstream: shared-profile claim cannot yet earn EMPIRICALLY SURVIVES for deflection.

**Recovery class:** OPEN (data) — profile prediction is published; empirical survival blocked on admissible table.

## 11. Cascade (direct only)

| Item | Impact |
|---|---|
| GOM26 ϟ freeze | Used unchanged |
| Spectral UNADJUDICATED | Unchanged |
| Shared-profile program | COMPUTED δ(b) available for later absolute comparison |
| D4 | Still PENDING_DATA |

## 12. Next tests

1. Reconstruct absolute VLBI deflection vs elongation from primary observables (or find a non-γ table).  
2. Cassini ODF/TDF residual pipeline (D4).  
3. Direct benchmark row re-trace (no audit inheritance).
