# CR09 — Assessment, Route B / T3 only (2026-10-05)

**Classification:** `CR09_ROUTEB_ZERO_KNOB_LAW_SYSTEMATIC_RESIDUAL_LEAD__OTHER_ROUTES_NOT_RUN`<br>
**Run class:** direct. Pre-run commitments in `RUN_LOG.md` (gates fixed before the run). Tool `cr09_routeB_rawmB.py`; output `cr09_routeB_results.txt`. Data `Datasets/cosmology/PantheonPlusSH0ES.dat`, raw columns mB, x1, c and their errors; calibrators and z < 0.01 dropped (1580 SNe, z = 0.0102–2.2614). **Canon edits:** none. **Cosmological shape parameters:** 0 (d_L = (1+z)(c/H0) ln(1+z)). Fitted: M (absorbs H0), α, β (standardisation), σ_int.

## Result
- Raw errors only: χ²/dof = 2.15 (α = 0.125, β = 2.67). With σ_int = 0.112 mag χ²/dof = 1 (α = 0.125, β = 2.60). Gate (a) σ_int ≤ 0.15 mag: **met**.
- Residual structure (observed minus law), 8 equal-count z bins: −0.040, −0.064, −0.049, −0.009, +0.011, +0.016, +0.046, +0.087 mag from z ≈ 0.02 to z > 0.5; Spearman(z, residual) = +0.265. Gate (b) (every bin within ±0.06 mag, |ρ| < 0.10): **not met** (max |bin median| 0.087; ρ = 0.265).
- T3 outcome per the registered rule: **systematic residual, a lead; not a pass.** The law is monotonically too faint-predicting at low z and too bright at high z by about 0.15 mag across the range.

## Assessment
1. The fixed-shape coasting law with no cosmological knob does not track the raw m_B within errors; its residual is a smooth, monotonic trend (a curvature mismatch), not scatter.
2. This agrees in kind with CR06: its one-parameter propagation power (n ≈ 0.656, fitted, not derived) also left drifting residuals (−0.07 mag at z = 0.02, +0.07 at z = 0.1). Both results say the data want more curvature than the zero-knob shape carries.
3. Not tested here and relevant: this raw-m_B standardisation applies no selection-bias correction and no host-mass step (the file's `biasCor_m_b` is built under an assumed cosmology, which PROMPT R0 forbids using). Such corrections are known to move high-z magnitudes by a few hundredths of a mag, smaller than the 0.15 mag range seen but not zero; the trend is therefore not attributable to them by size. Diagonal errors only; SN covariances not used.
4. Route F's hypothesis (the curvature is the z³ / octave structure of the propagation term) is the open question this residual poses; it is not tested. A registered next round would fit the one-parameter propagation power on raw m_B with the same standardisation and gates, and report whether the residual structure vanishes; the parameter then counts as CALIBRATED(1) (CR06 gave n ≈ 0.656 without a derivation).
5. Routes A (mismatch sign and size), C, D (BAO and CMB angles), E, G, H are not run; no result is claimed on the Hubble tension itself. CR09 stays open.

## Round 2 (2026-10-05) — one shape parameter on raw m_B
Registered in `RUN_LOG.md` before the run (same gates as round 1, one shape parameter allowed by the PROMPT's count; CALIBRATED(1)).

| Quantity | Result |
|---|---|
| exponent e minimising χ² (σ_int = 0), CR06 convention n = 1 + e | e = −0.365, n = 0.635; χ²/dof = 1.85 |
| σ_int for χ²/dof = 1 | 0.100 mag (α = 0.138, β = 2.72) — gate (a) met |
| 8-bin median residuals (z low → high) | +0.027, −0.013, +0.006, +0.012, +0.005, −0.008, −0.009, −0.044 mag |
| max \|bin median\| | 0.0435 mag — within the 0.06 limit |
| Spearman(z, residual) | −0.117 — outside the registered \|ρ\| < 0.10 |
| T3′ | **not met** (misses the correlation limit by 0.017; not widened) |

- Adding the one shape parameter removes the 0.15 mag monotonic trend of round 1 (bin medians now ±0.04 or less); a small residual correlation with z remains, with the highest-z bin (z > 0.51) 0.044 mag brighter than the law.
- The fitted n = 0.635 agrees with CR06's 0.656 (fitted on a different dataset and cut) and with 0.720 from MU_SH0ES on this file: n is stable at about 0.64–0.72 across three data treatments. It is still a fitted number, CALIBRATED(1), without a derivation (CR06 states this).
- A convention mismatch in my first consistency line (e against CR06's n) is corrected in `RUN_LOG.md`; the instrument reproduces CR12's coasting χ² (773) exactly.
- Limits unchanged: diagonal errors, raw m_B with no selection-bias or host-mass term, no covariance, bins fixed in advance.
- Classification update: `CR09_ROUTEB_ONE_KNOB_LAW_TRACKS_RAW_MB_TO_0P04MAG__T3PRIME_GATE_MISSED_ON_SPEARMAN`.
