# GOM25b Assessment — Orbital-Invariant Solar Koppa

**Date:** 2026-08-07  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Pre-registration:** `PROMPT_B_INVARIANT_KOPPA.md`  
**Instrument SHA-256:** `095de47c3fcaefbd303dea6ddadbf69a09555617b695d7c49e9c6387bde0e4f9`  
**Stdout:** `.audit-tmp/gom25b_run.txt`  
**Canon edited:** no

## Failed model frozen

Instantaneous `ϟ_i = v_i² r_i / c²` (GOM25): mean 1477.26 m, **CV = 1.196%**.

## Repair executed

```text
a = (r_min + r_max)/2
ϟ_vv,i = v_i² / [c² (2/r_i − 1/a)]
ϟ_Sun = mean(ϟ_vv,i)
```

No `G`, `M`, or `bridge::koppa_Sun` in the prediction path.

## Validation

| Test | Result |
|---|---|
| Circular mock ϟ_inst = ϟ_vv | PASS (1.5×10⁻¹⁶) |
| Elliptic mock CV_vv ≪ CV_inst | PASS (0 vs 1.18%) |

## Hold-out / quality gates (pre-registered)

| Gate | Value | Threshold | Result |
|---|---:|---:|---|
| CV_vv / CV_inst (2025) | 1.15×10⁻⁵ / 1.20×10⁻² | CV_vv < 0.1 CV_inst | PASS |
| H1 vs H2 \|Δ\|/ϟ | 6.98×10⁻⁶ | < 5×10⁻⁴ | PASS |
| 2024 vs 2025 \|Δ\|/ϟ | 2.20×10⁻⁵ | < 5×10⁻⁴ | PASS |

2024 Horizons table frozen:  
`raw/jpl_horizons_emb_sun_vectors_2024.csv`  
SHA-256 `bae3494660ca2dee27e70b6baebf631396f03940c2018946dc3952a49a5c0de4`.

## Spectral re-test

| Quantity | Value | Label |
|---|---:|---|
| ϟ_Sun (2025) | 1476.664 m | COMPUTED |
| σ_ϟ (hold-out) | 0.023 m | COMPUTED |
| v_pred depth-diff (IAU R) | 633.37 ± 0.13 m/s | COMPUTED |
| v_obs (HARPS summary) | 638 ± 6 m/s | OBSERVED + MODEL-PROCESSED deps |
| Decision | COMPATIBLE (\|Δ\|=4.63 < 2σ=12.00) | confirmation still **UNADJUDICATED** |

Prediction σ no longer inflated by elliptic instantaneous CV.

## Classification

| Item | Status |
|---|---|
| Instantaneous-ϟ IC debt | **RECOVERED** at investigation level (held-out) |
| Canon `bridge::koppa_Sun` | unchanged; propose-and-wait if adoption desired |
| Spectral depth map | COMPATIBLE / **UNADJUDICATED** |
| New freedom class | DERIVED from state-vector geometry (`a` from r extrema) |

## Root-cause closure (seven questions — repair audit)

1. Failure was magnitude instability of instantaneous ϟ (±1.2%).  
2. Observable: solar surface depth should not track EMB eccentricity.  
3. Premise: `ϟ = v²r/c²` instantaneous.  
4. Local to orbital→depth map.  
5. Freedom: vis-viva invariant with geometric `a`.  
6. Freedom is DERIVED (no fitted amplitude).  
7. Downstream: redshift, Shapiro, lensing should consume invariant ϟ, not instantaneous.

## Remaining debt

1. Cassini/admissible delay residual still PENDING_DATA.  
2. Shared-profile deflection vs impact parameter not yet run.  
3. Residual CV ~10⁻⁵ may reflect `(r_min+r_max)/2` vs true SMA and EMB lunar wobble — register as second-order open if a tighter invariant is needed.  
4. Spectral confirmation still blocked by atmospheric/lab-λ pipeline.
