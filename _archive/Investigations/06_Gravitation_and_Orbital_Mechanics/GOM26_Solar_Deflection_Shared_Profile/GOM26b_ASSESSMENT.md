# GOM26b Assessment — Fomalont Elongation Ledger

**Date:** 2026-08-07  
**Instrument:** `gom26b_fomalont_elongation_ledger.cpp`  
**Frozen ϟ:** 1476.664437 m (GOM25b)  
**Data frozen:** `Datasets/solar_propagation_2026-08/raw/fomalont_vlba_deflection_2009.pdf`  
SHA-256 `66c1f9a90b3b5481d04b9ecc36f8ee4bd3a4a39b7f44b2c00042b4f23275fb6b`

## Admissibility ruling

Fomalont et al. (2009) Table 4 reports position residuals **after** the correlator
applied γ=1 gravitational bending. Those residuals constrain (γ−1), not absolute
δ(b). Using them as absolute deflection data would import a competitor-model prior.

**Status:** PENDING_DATA for absolute b-scan adjudication.  
**Status:** UNADJUDICATED for any claim that “γ≈1 confirms SDT.”

## What was computed

Per-source absolute SDT deflection at Table 3 solar elongations
`b = AU·sin(θ)` with the shared `n=1/(1−ϟ/r)²` profile. Example:

| Source | Date | SR⊙ [deg] | δ_SDT [mas] |
|---|---|---:|---:|
| 3C279 | Oct11 | 3.2 | 145.8 |
| 3C279 | Oct10a | 2.2 | 212.1 |
| J1246 | Oct09 | 3.7 | 126.1 |

Paper text cites ~100 mas **differential** GR bending 3C279–J1304 on Oct11.
Absolute differentials require J1304 elongation (Fig. 1), which is not tabulated.

## Cascade

GOM26 COMPUTED δ(b) curve stands. Empirical confirmation still blocked on data
product class, not on numerical instability of the profile.
