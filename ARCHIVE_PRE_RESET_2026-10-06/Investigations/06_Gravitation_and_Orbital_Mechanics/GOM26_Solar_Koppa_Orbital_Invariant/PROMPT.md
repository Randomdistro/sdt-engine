# GOM26 — Solar Koppa Orbital Invariant (GOM25 Repair Re-Audit)

> **Status:** PRE-REGISTERED — 2026-08-07.
> **Upstream:** `GOM25_Solar_Depth_Propagation_Audit` §17–§20 (PARTIAL recovery; reformulation OPEN).
> **Canon edits:** none. Investigation-level re-audit of a proposed initial-condition repair.

## 0. Objective

Re-audit the GOM25 reformulation hypothesis that solar depth input `ϟ` is an **orbital invariant**, not the instantaneous `v²r/c²` sampled on an elliptical state vector.

This loop does not edit `laws.hpp`. It tests whether the stated repair:

1. collapses the 1.2% elliptic CV on D1;
2. still yields a spectral amplitude compatible with the frozen D3 comparator under the same 2σ rule **without** inflating prediction σ by the elliptic CV;
3. remains stable on a held-out orbit sample that was not used to set the invariant.

## 1. Claim under test

| Claim ID | Exact claim |
|---|---|
| GOM26-C1 | Under Keplerian two-body kinematics on EMB–Sun vectors, there exists a single `ϟ` such that `v² = c² ϟ (2/r − 1/a)` with constant `ϟ` and semi-major axis `a`. |
| GOM26-C2 | That invariant `ϟ` equals `μ/c²` where `μ` is recovered from pairwise energy consistency of the same vectors (no `G`, no engine `koppa_Sun`, no spectral target). |
| GOM26-C3 | Using frozen invariant `ϟ` alone, `v_pred = c·ϟ/R_Sun` is COMPATIBLE with HARPS paper summary `638 ± 6 m/s` under the GOM25 2σ rule, with `σ_pred` from `μ` uncertainty only. |
| GOM26-C4 | The same invariant on a held-out orbit sample agrees with the calibration sample to relative `|Δϟ|/ϟ < 10⁻³`. |

## 2. Exact equations (frozen)

```text
# Pairwise two-body μ estimator (from energy equality between epochs i,j):
μ_ij = (v_j² − v_i²) / [ 2 (1/r_j − 1/r_i) ]     # only when |1/r_j − 1/r_i| > ε

# Robust central value:
μ     = median({ μ_ij : pairs retained })
σ_μ   = 1.4826 × MAD({ μ_ij }) / √N_eff

ϟ     = μ / c²

# Per-epoch reconstruction (requires a):
E_i   = v_i²/2 − μ/r_i
a     = −μ / (2 ⟨E⟩)
ϟ_i   = v_i² / [ c² (2/r_i − 1/a) ]               # when (2/r − 1/a) > 0

# Spectral map (held-out observable; GOM25 surface form):
v_pred = c · ϟ / R_Sun
```

**Prohibited inputs:** `G`, solar mass, `bridge::koppa_Sun`, HARPS values as inputs to `μ`/`ϟ`, PPN coefficients, engine `shapiro_delay` for the spectral test.

**Assumed constitutive relation:** Keplerian two-body energy conservation on the relative EMB–Sun orbit. This is a kinematic premise of the repair, not an SDT-derived law. If it fails, the repair is NO RECOVERY under this definition.

## 3. Datasets

| ID | File | Role |
|---|---|---|
| D1-cal | `Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2025.csv` | Calibration year (frozen in GOM25) |
| D1-hold | `Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv` | Held-out year (freeze + checksum before writing C3/C4 results) |
| D2 | IAU nominal `R_Sun = 6.957e8 m`; Haberreiter `695658±140 km` | Radius anchors |
| D3 | HARPS paper summary `638±6 m/s` | Spectral comparator (MODEL-PROCESSED nuisances retained) |

If D1-hold cannot be retrieved, fall back (pre-registered) to **intra-year split**: odd-indexed D1-cal rows calibrate; even-indexed rows hold out. Label that fallback explicitly.

## 4. Decision rules (before execution)

1. **Invariance gate (C1/C2):** On calibration, CV of `{ϟ_i}` must be `< 1×10⁻³`. Else **NO RECOVERY** for this repair route.
2. **μ sanity:** `μ` positive and finite; usable pairs `≥ 50%` of pairs with `|Δ(1/r)| > ε` (`ε = 1×10⁻¹⁵ m⁻¹`).
3. **Spectral gate (C3):** `|v_pred − 638| > 2√(σ_pred²+6²)` ⇒ EXCLUDED; else COMPATIBLE. Confirmation remains UNADJUDICATED.
4. **Hold-out gate (C4):** `|ϟ_hold − ϟ_cal| / ϟ_cal < 1×10⁻³` else EXCLUDED as invariant across samples.
5. **No retuning** of ε, CV threshold, 2σ rule, or radius after seeing residuals.

## 5. Instrument validation (before targets)

A. Near-circular Kepler mock (`e=0.01`, known `μ`): recovered `μ` within 1e-8 relative; CV(`ϟ_i`) < 1e-6.
B. Eccentric Kepler mock (`e=0.0167`, known `μ`): same thresholds as A.
C. Delete-test: do not read `bridge::koppa_Sun` or HARPS until after `ϟ` is printed.

Instrument-validation thresholds may be tightened for known-answer mocks; the empirical CV gate (`1e-3`) is unchanged.

## 6. Cassini D4 side-probe

| Claim ID | Claim | Decision |
|---|---|---|
| GOM26-D4 | SCE1 ATDF alone yields an admissible propagation residual | Remains **PENDING_DATA** until TRK-2-25 decode + independent geometry/clock reconstruction. Record-type census is documentation only. |

Do not substitute Bertotti et al. fitted `γ` or published residual plots as SDT targets.

## 7. Classification

Use master-protocol statuses only. Do not promote COMPATIBLE spectral amplitude to EMPIRICALLY SURVIVES in this loop.

## 8. Downstream if C1–C4 pass

Register invariant `ϟ` as investigation-level DERIVED IC for subsequent shared-profile tests. Canon adoption remains propose-and-wait.
