# RUN_LOG — CR09

## Pre-Run Commitments — CR09 Route B / T3 (2026-10-05, before any tool)
- Scope this run: Route B only (raw m_B, SDT-standardised). Routes A, C–H not run.
- Prompt completion target: B. Physics class hoped: CONVERGENCE. CALIBRATED budget: standardisation (M, α, β) and σ_int, all fitted per the SN standardisation itself, plus H0 absorbed in M. **Zero cosmological shape parameters.**
- Model (CR12, fixed shape): d_L = (1+z)(c/H0) ln(1+z); μ = 5 log₁₀(d_L/10 pc). Data: `Datasets/cosmology/PantheonPlusSH0ES.dat`, columns zHD, mB, mBERR, x1, x1ERR, c, cERR, IS_CALIBRATOR; drop IS_CALIBRATOR = 1 and zHD < 0.01 (as CR12). **m_b_corr, MU_SH0ES not used.**
- Fit: m_B = M − α x1 + β c + 5 log₁₀(d_L/(c/H0)) with M absorbing H0; weighted least squares; variance mBERR² + α²x1ERR² + β²cERR² + σ_int² (α, β from a first pass; two iterations); σ_int chosen so that χ²/dof = 1 (profile) and the value reported.
- Diagonal errors only (no 1701×1701 covariance); stated limitation. SN covariance between x1, c and m_B (COV_x1_c etc.) ignored.
- **T3 gate (fixed now):** met if (a) σ_int needed for χ²/dof = 1 is ≤ 0.15 mag, and (b) in 8 equal-count z bins the median residual of every bin is within ±0.06 mag and the Spearman correlation of residual with z has |ρ| < 0.10. Failure of (b) with (a) met = "systematic residual, a lead" (the PROMPT's wording), not a pass. Reported also: χ²/dof at σ_int = 0 (raw errors only).
- Exposure: CR12 recorded the same law on MU_SH0ES (χ² 773 for the SDT law, 681 for ΛCDM); the raw-m_B, own-standardisation version has not been run.
- No rival-model comparison in this run (PROMPT Route B: "No rival comparison; the datum is the photons").
- Forbidden retroactive changes: bin edges, z cuts, the σ_int ceiling, adding a shape parameter after seeing residuals.
2026-10-05 Route B run: T3 = systematic residual (lead). See CR09_ASSESSMENT.md.

## Round 2 registered (2026-10-05, after round 1; one shape parameter allowed by the PROMPT's parameter count)
Law family (CR06 `cr06_redshift_fit.cpp`): d_L/(c/H0) = (1+z)·[1 − (1+z)^(−n)]/n, n → 0 being the round-1 coasting law ln(1+z). n is fitted on raw m_B with the same standardisation, weights and σ_int-for-χ²/dof=1 rule; scan n over [−0.5, 2.0] step 0.005. CALIBRATED(1), reported as such, not derived. Gates fixed now: T3′ met if the fitted n gives (a) σ_int ≤ 0.15 mag, (b) every 8-bin median within ±0.06 mag and |Spearman(z, residual)| < 0.10, as in round 1. Consistency (reported, not gated): fitted n within ±0.10 of CR06's 0.656. Exposure: round 1 residual shape seen; CR06 recorded n = 0.656 on MU_SH0ES.

2026-10-05 Round 2 result and a correction of my own convention. The fitted parameter in my script is the exponent e of d_L/(c/H0) = (1+z)[1 − (1+z)^(−e)]/e. CR06's code (`cr06_redshift_fit.cpp`, DL "SDTn") writes e = p − 1, so CR06's n = 0.656 corresponds to e = −0.344, not e = 0.656. My round-2 "consistency" line compared e with CR06's n and printed |n − 0.656| = 1.021 — a mismatch of conventions, not of data. In CR06's convention the raw-m_B fit gives n = 1 + e = 0.635 (|Δ| = 0.021, within the registered ±0.10). Instrument validation (post hoc, known answer): the same code on MU_SH0ES gives χ²(e = 0) = 773.2 = CR12's recorded SDT coasting χ² (773), and its best e = −0.280 (CR06-convention n = 0.720) lies near CR06's e = −0.344; at CR06's e = 0.656 (a misreading) χ² = 1601.8. The T3′ gate result is unaffected by this correction.
