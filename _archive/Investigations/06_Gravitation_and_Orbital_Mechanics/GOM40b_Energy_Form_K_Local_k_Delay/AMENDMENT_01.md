# GOM40b Amendment 01 — SMA sanity / dual arc

**Date:** 2026-08-09  
**Trigger:** First SCE1 Earth pass returned **a ≈ 3.53×10¹¹ m**, **K ≈ 927 m**
with CV(**K_recon**) still < 1×10⁻³ — a short-arc conditioning artefact, not a
solar invariant.

## Added gates (before re-run of object claims)

| ID | Gate |
|---|---|
| GOM40b-C3b | Recovered SMA **a ∈ [1.4×10¹¹, 1.6×10¹¹] m**. Else label that arc **`ARC_INSUFFICIENT`** (not a solar-**K** value). |
| GOM40b-C3c | Dual route: (1) SCE1 Earth 157–160; (2) frozen GOM26 D1-cal EMB–Sun 2025 year file. Year route supplies energy-form **K** for local-**k** delay-rate if SCE1 is `ARC_INSUFFICIENT`. |

No Doppler residual gate added. No **K** fitted to ODF.
