# GOM26 Assessment — Shared-Profile Solar Deflection

**Date:** 2026-08-07  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Pre-registration:** `PROMPT.md`  
**Instrument SHA-256:** `3bd9261d0cfa7830168e6d783810cfb561979c0fe1af8322da7066c2d4b42961`  
**Stdout:** `.audit-tmp/gom26_run.txt`  
**Frozen input:** `ϟ_Sun = 1476.664437 m` (GOM25b) — not retuned  
**Canon edited:** no

## Mechanism

```text
c_far = c (1 − ϟ/r)²
n(r)  = c / c_far = 1/(1 − ϟ/r)²
b     = n(r0) r0
δ     = 2∫ φ_half − π
```

## Instrument validation

| Test | Result |
|---|---|
| Reduced-koppa continuity vs 4ϟ/b | PASS (within 5%) |
| Weak-field b=5 R_Sun vs 4ϟ/b | PASS (rel 1.0×10⁻⁴) |
| Step refinement | PASS (1.1×10⁻⁴) |
| Turning-point identity | PASS |

## Computed prediction ledger (whole registered b-scan)

| b/R_Sun | δ [arcsec] COMPUTED | 4ϟ/b [arcsec] |
|---:|---:|---:|
| 1.01 | 1.733956 | 1.733898 |
| 1.05 | 1.667898 | 1.667845 |
| 1.10 | 1.592091 | 1.592034 |
| 1.20 | 1.459420 | 1.459364 |
| 1.50 | 1.167538 | 1.167491 |
| 2.00 | 0.875662 | 0.875619 |
| 3.00 | 0.583785 | 0.583746 |
| 5.00 | 0.350283 | 0.350247 |
| 10.00 | 0.175162 | 0.175124 |
| 1.00 (limb) | 1.751215 | 1.751237 |

Higher-order residue relative to 4ϟ/b is O(10⁻⁴–10⁻⁵) across the scan — solar weak field.

## Empirical status

**PENDING_DATA** for whole-range adjudication: no impact-parameter deflection table was frozen.  
A single limb nominal (~1.75″) is MODEL-PROCESSED / summary-scale and remains **UNADJUDICATED** as a confirmation gate.

## Cascade

| Upstream | Effect |
|---|---|
| GOM25b invariant ϟ | consumed frozen; not fitted |
| Spectral UNADJUDICATED | unchanged |
| Cassini PENDING_DATA | unchanged |

## Next

Freeze a b-resolved solar deflection dataset (radio/optical) with stated solar offset and uncertainties; run one-pass residual test against the ledger above without retuning ϟ.
