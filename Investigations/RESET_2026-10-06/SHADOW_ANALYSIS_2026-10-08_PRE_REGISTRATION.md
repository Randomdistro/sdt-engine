# Shadow analysis of the paste-math evaluation and the algebra demos — pre-registration (2026-10-08)

Object: `PASTE_MATH_EVALUATION_2026-10-07.md` (+ `paste_math_eval/`) and `paste_algebra_demos/` (2026-10-08). Written before the instrument `shadow_analysis/shadow_1.cpp` exists. Constants from `sdt::laws`; external values are tagged MEASURED-INPUT with source, or [B] (from memory, unverified) until checked. No criterion is changed after a result is seen; an amendment, if any, is dated and placed below this line with its reason.

## Validations (must be met before any check runs)
- V1 Compton-type drag: the integral F/(uσ) = −(1/2)∫μ[γ(1−βμ)]⁻⁴dμ against the closed form −(4/3)γ²β at β = 0.3 to 1e-6 (known answer).
- V2 Dilatation centre u_r = A/r²: numerically differentiated ε_rr, ε_θθ against −2A/r³, +A/r³ to 1e-6, trace to 1e-9.
- V3 Algebra of the c-closure: c_closure computed through the engine path equals v_E·√(6π AU/(δφ a(1−e²))) with v_E = v_surface_Sun·√(R_Sun/AU) to 1e-12 (shows R_Sun cancels).

## Checks and their criteria
| Id | Statement under test | Confirmed if | Rejected if |
|---|---|---|---|
| S1 (E1) | c_closure/c depends on lengths only through AU and a_Mercury, with R_Sun cancelling | changing R_Sun by ±10% changes c_closure by < 1e-12 relative | any change ≥ 1e-12 |
| S2 (E2) | C3's ϟ ratio and C7's c ratio are one fact | c_closure/c = (ϟ_Merc/ϟ_Earth-orbit)^(−1/2) to 1e-12, where ϟ_Earth-orbit = v_surface_Sun² R_Sun/c² | difference > 1e-12 |
| S3 (E4) | Sirius B mismatch originates in the radius | with the radius of the paper that supplies z (to be verified), M_z lies within 1σ of the dynamical 1.018 ± 0.011 M☉ when the redshift error is propagated | outside 1σ (then the radius is not the sole origin) |
| S4 (E5) | the paste's ρ/ρ₀ = 1 − Ω₀/(4πr³) equals 1 − ε_θθ of the incompressible field | equal to 1e-12 at r = R₀, 2R₀, 10R₀ | not equal |
| S5 (E8) | ϟ_Sun/ϟ_b ÷ (M☉/m_p) reduces to R_p/(4ƛ_p) when ϟ_Sun is the GM-route value | the two quantities agree to 1e-12 (using ϟ_Sun = GM☉/c², GM☉ IAU, l_P CODATA, G CODATA, ƛ_p = ħ/(m_p c)); the demo's −1.2e-4 is then decomposed into this ratio times ϟ_Mercury/ϟ_GM | disagreement > 1e-12 |
| S6 (E9) | Earth's CMB drag at 370 km/s | reported; criterion: ratio to the orbital-speed figure = 370/29.78 to 1e-6 (linear regime) | otherwise |
| S7 (item 5) | exact drag factor | demo's ratios at β = 0.001, 0.01, 0.1, 0.5 equal γ² to 1e-5 | any > 1e-5 |
| S8 (item 11) | lattice dispersion lag for GRB 090510 (31 GeV photon, z ≈ 0.903, lookback distance taken as D = c·t_lb with t_lb from the measured-z table entry [to be verified]) | reported; criterion: Δt_quadratic with ℓ = ℓ_P is below the published delay sensitivity (≈ 1 s scale, to be verified) | above it (lattice spacing ℓ_P would be excluded) |
| S9 (item 4) | solar ϟ = zR with a measured solar gravitational redshift (if a published value with uncertainty is found) | abs(z_meas/z_pred − 1) within 2σ_meas, z_pred = ϟ_Sun_from_precession/R_Sun (no fit) | outside 2σ |

Items 1, 2, 3, 7, 8, 9, 10 of the plan are recorded as targets only in this round (no measured values loaded).

## Amendment 2026-10-08 (before the instrument was written; no result seen)
1. **S3.** Sourcing showed the evaluation paired Barstow et al. 2005's redshift (80.42 ± 4.83 km/s) with the mass of Joyce et al. 2018 (1.017 ± 0.025 M☉). The 2018 paper (read directly, Table 3 and §3.1.7) gives v_gr = 80.65 ± 0.77 km/s and R = 0.803 ± 0.011 R☉/100. S3 is re-registered as follows. Compute ϟ_B = (v_gr/c)·R from the 2018 pair. Express it in solar units as ϟ_B/ϟ_Sun_from_precession, the same form as the paper's equation (3). Compare it with the dynamical 1.018 ± 0.011 (Bond et al. 2017b, as quoted by Joyce et al.).
   - **Confirmed** if within 1σ combined, with σ propagated from v_gr and R.
   - **Rejected** otherwise.

   Also report the evaluation's (z, R) pair, to locate where its 1.061 came from.
2. **S8.** The published delay distance integral uses ΛCDM, a prohibited input. Instead use the bound L ≤ R_CMB (engine) and the blue-shift of k along the path ≤ (1+z)², with z = 0.903. Coefficient: group velocity v_g = c·cos(kℓ/2), so Δt ≈ (kℓ)²L/(8c). The plan's 1/24 was the phase-velocity coefficient. Bound to compare against: |Δt| = 0.859 s (Fermi LAT, arXiv:1008.2913).
3. **S9.** Measured value: 638 ± 6 m/s (González Hernández et al. 2020, A&A 643 A146, Moon-reflected light, HARPS with laser frequency comb, 97 weak Fe lines), as observed at Earth.
   - Prediction: c·ϟ_Sun_from_precession·(1/R_Sun − 1/AU), minus Earth's own surface term c·ϟ_Earth/R_Earth (engine `bridge::koppa_Earth`).
   - **Confirmed** if within 2σ.

## Sources to verify before the run (each tagged verified/unverified in the assessment)
Barstow et al. 2005 (Sirius B R, z, M); modern uncertainty of Mercury's anomalous perihelion advance; González Hernández et al. 2020 (solar gravitational redshift); GRB 090510 delay sensitivity and redshift.
