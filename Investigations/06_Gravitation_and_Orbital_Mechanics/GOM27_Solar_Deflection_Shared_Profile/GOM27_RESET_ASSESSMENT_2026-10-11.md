# GOM27 (solar deflection from the shared depth profile) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom27_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM27/PROMPT.md` in full; the GOM26, RTM01 and GOM39 records of this programme (the invariant ϟ = 1476.351 m with its year-to-year spread 3.5×10⁻⁴ and the working systematic 6×10⁻⁴; the VLBA γ summary and the weak-index integral); the Fomalont et al. paper in the local ar5iv file (its Sections 3.4, 4, 5 and Tables 4–5 as extracted). Not read: `GOM27_ASSESSMENT.md`, `RUN_LOG.md`, `GOM27_D5_*`, `gom27_deflection_profile.cpp`. Exposure: the prompt freezes ϟ_Sun = 1476.351201 m (GOM26), the same value as this programme's GOM26 record.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | The weak-field claim δ_wf = 4ϟ/b follows from n = 1 + 2ϟ/r by the straight-path integral (RTM01 V3 reproduced it to 5×10⁻⁹). The numerical ray tracing recovers it by construction in the weak field; the content is the O(ϟ/b) correction. |
| D2 | premise | The profile n(r) = 1/(1 − ϟ/r)² is the index implied by c_far = c(1 − ϟ/r)². Its second-order deflection coefficient differs from the Schwarzschild one in isotropic or areal coordinates only through the choice of the radial variable (here the far-frame r, with b = n(r₀)r₀). The coefficient is computed and compared with 15π/4 (the general-relativistic value for the coefficient of (GM/(c²b))² in the standard coordinates); the comparison is between profile choices and coordinates, not between measurements, and is unmeasurable at the solar limb (second-order term about 5×10⁻¹¹ rad). |
| D3 | gating | D5 (data gate). The local Fomalont tables list, per session and source, positions with respect to the reference source J1304 (Table 4 of the ar5iv file) and position changes from the non-deflected positions (the table with "Each Freq" and "Corona-Free" rows). Their fit is χ² = Σ((P − 0.5(γ − 1)D)/σ)², so P is the residual after subtracting the differential **GR (γ = 1) bending prediction D_d(i)**, which is not tabulated. The rows are MODEL-PROCESSED residuals; the only quantity comparable without inserting γ as an SDT input is the global summary, γ = 0.9998 ± 0.0003. Under the prompt's rule (a global γ summary only) the empirical status is PENDING_DATA / UNADJUDICATED, and "EMPIRICALLY SURVIVES" is not available. Registered: the γ-equivalent of the SDT coefficient is reported against 0.9998 ± 0.0003 for information. |
| D4 | gating | The deflection δ = 2φ_half − π is a difference of two numbers of order 1 when δ ~ 10⁻⁶; direct quadrature loses digits near the turning point. Registered: the algebraically stable form below, validated by instrument tests A–D. |
| D5 | record | The scan values b/R_☉ ∈ {1.01, 1.05, 1.1, 1.2, 1.5, 2, 3, 5, 10} plus the limb b = R_☉; the impact parameter b in the profile is b = n(r₀)r₀, as the prompt states. |
No downgrade is made on agreement grounds.

## 2. Registered method, validations, outputs (fixed before the run)
**Stable quadrature.** With u = r₀/r = 1 − s², n(r) = r²/(r − ϟ)², h(r) = n r = r³/(r − ϟ)², b = h(r₀) (r₀ solved from b by Newton iteration): g(u) = n(r)² − n₀²u² = (h − h₀)(h + h₀)/r², with h − h₀ = (p − p₀)·Q₁·Q₂/((r − ϟ)²(r₀ − ϟ)²), p = √r, p₀ = √r₀, Q₁ = r r₀ − ϟ(r + p p₀ + r₀), Q₂ = p³(r₀ − ϟ) + p₀³(r − ϟ), p − p₀ = (r − r₀)/(p + p₀), r − r₀ = r₀ s²/u (an exact factorisation that removes the cancellation at the turning point). The half-angle φ_half = ∫₀¹ n₀ 2s ds/√g, and **δ = 2∫₀¹ [2 s n₀/√g(s) − 2/√(2 − s²)] ds** (the flat-space integral ∫₀¹ 2/√(2 − s²) ds = π/2 is subtracted analytically). Gauss–Legendre, 64 nodes (128 for the refinement test).
**Validations (before the solar ledger).** A: a reduced case ϟ/b = 10⁻³ and 10⁻⁴: δ ≈ 4ϟ/b within 5%. B: solar ϟ at b = 5 R_☉: |δ − 4ϟ/b|/(4ϟ/b) < 0.02. C: 64 against 128 nodes: relative change < 10⁻³. D: the turning identity |n(r₀)r₀ − b|/b < 10⁻¹⁰ for the solved r₀. Added: E: the same integral for n = 1 (ϟ → 0) returns 0 to 10⁻¹⁴ (the subtraction is exact).
**Outputs.** For the nine scan values and the limb: r₀/R_☉, δ in rad and arcseconds, δ/δ_wf − 1, and the second-order coefficient c₂ = (δ − 4ϟ/b)/(ϟ/b)² (compared with 15π/4 = 11.781 and reported at ϟ/b = 10⁻⁴ and at the limb). The scan with ϟ = 1476.351201 m (frozen), and, for information, the engine's `koppa_Sun` and the GOM26 2024 value. The γ-equivalent: γ_eq = 2·ϟ/(GM☉/c²) − 1 with GM☉/c² = 1476.6250 m (IAU nominal, used only for this PPN normalisation) against 0.9998 ± 0.0003 (Fomalont et al.).
**Decisions.** Instrument tests A–E must pass before the ledger; the whole-range COMPUTED δ(b) is published; the empirical comparison: PENDING_DATA / UNADJUDICATED (D3); no bin is excluded (no admissible (b, δ_obs, σ) table). No retuning of ϟ.
**Expected landing (hand estimate before registering).** δ_limb = 4ϟ/R_☉ ≈ 8.4885×10⁻⁶ rad = 1.7509″ with a relative O(ϟ/b) correction of order 10⁻⁵; c₂ a number of order 10 (the Schwarzschild coefficient is 11.78; the SDT profile's c₂ is not estimated); the γ-equivalent 0.99963 for ϟ = 1476.3512 m, 0.6σ from 0.9998.

## 3. Results (COMPUTED; instrument `gom27_reset_1.cpp`, output `gom27_reset_1_results.txt`; single pass, no amendment; instrument tests met)
**Instrument tests.** E (ϟ → 10⁻⁹ m at b = 10⁹ m): δ = 1.6×10⁻¹⁶, which is rounding level (gate 10⁻¹⁴ + 10·4ϟ/b: met). A: ϟ/b = 10⁻³ gives δ/δ_wf − 1 = +3.95×10⁻³ and ϟ/b = 10⁻⁴ gives +3.93×10⁻⁴ (gate 5%: met; the correction is linear in ϟ/b, as the second-order term requires). B: solar ϟ at b = 5 R☉: relative +1.67×10⁻⁶ (gate 2%: met). C: 64 against 128 nodes: 2.9×10⁻¹¹ (gate 10⁻³: met). D: turning identity 0 to double precision (gate 10⁻¹⁰: met).
**Second-order coefficient.** c₂ = (δ − 4ϟ/b)/(ϟ/b)² = 15.7154 at ϟ/b = 10⁻⁴ and 15.7830 at 10⁻³; the linear extrapolation to ϟ/b → 0 gives 15.708 (= 5π to the printed digits), and the solar scan returns 15.708 at every b ≤ 5 R☉. The Schwarzschild-coordinate value is 15π/4 = 11.781. The two differ because the radial variable and the profile differ (D2); the difference is a coordinate-and-profile statement, not a measurement.
**Whole-range COMPUTED δ(b)**, ϟ = 1476.351201 m (frozen):
| b/R☉ | r₀/R☉ | δ (rad) | δ (arcsec) | δ/δ_wf − 1 |
|---|---|---|---|---|
| 1.00 | 0.999995756 | 8.488507×10⁻⁶ | 1.750880 | +8.33×10⁻⁶ |
| 1.01 | 1.009995756 | 8.404461×10⁻⁶ | 1.733545 | +8.25×10⁻⁶ |
| 1.05 | 1.049995756 | 8.084289×10⁻⁶ | 1.667504 | +7.94×10⁻⁶ |
| 1.10 | 1.099995756 | 7.716818×10⁻⁶ | 1.591708 | +7.58×10⁻⁶ |
| 1.20 | 1.199995756 | 7.073746×10⁻⁶ | 1.459065 | +6.95×10⁻⁶ |
| 1.50 | 1.499995756 | 5.658989×10⁻⁶ | 1.167250 | +5.56×10⁻⁶ |
| 2.00 | 1.999995756 | 4.244236×10⁻⁶ | 0.875436 | +4.17×10⁻⁶ |
| 3.00 | 2.999995756 | 2.829486×10⁻⁶ | 0.583623 | +2.78×10⁻⁶ |
| 5.00 | 4.999995756 | 1.697690×10⁻⁶ | 0.350174 | +1.67×10⁻⁶ |
| 10.00 | 9.999995756 | 8.488443×10⁻⁷ | 0.175087 | +8.34×10⁻⁷ |
**Limb sensitivity to ϟ** (information only): ϟ = 1476.3512 m gives 1.750880″; the engine's `koppa_Sun` = R☉/k_Sun² = 1477.0459 m gives 1.751704″; the GOM26 2024 value 1476.8693 m gives 1.751495″. The spread 8×10⁻⁴″ is the ϟ systematic (4.7×10⁻⁴ between the engine value and the frozen invariant), well inside every measurement.
**γ-equivalent.** With GM☉/c² = 1476.6250 m used only to normalise the PPN parameter, γ_eq = 2ϟ/(GM☉/c²) − 1 = 0.99963. Against the VLBA γ = 0.9998 ± 0.0003: difference −1.7×10⁻⁴, which is 0.57σ on the VLBA error alone and 0.20σ when the ϟ systematic (4×10⁻⁴ in ϟ, ±0.0008 in γ_eq) is included. The registered landing named 0.6σ (the VLBA-only figure); the run reports both.
The registered expectation held: δ_limb 1.7509″ (found 1.7509″ weak-field; 1.750880″ ray-traced), relative correction ~10⁻⁵ (found 8.3×10⁻⁶), γ_eq 0.99963 (found 0.99963). The c₂ value was not estimated beforehand (order 10 registered; found 5π).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Stable ray-traced integral (tests A–E) | **instrument validated** | five registered tests met; 64/128 agreement 3×10⁻¹¹ |
| Weak-field δ = 4ϟ/b | **COMPUTED (reproduced)** | recovered by the integral at 8×10⁻⁶ relative at the limb; this is the construction in D1 |
| Second-order coefficient c₂ = 5π | **COMPUTED; coordinate-and-profile dependent** | not comparable with 15π/4 without fixing the radial variable; the contribution is ~7×10⁻¹¹ rad at the limb and unmeasurable |
| Whole-range δ(b) table | **COMPUTED** | ϟ frozen, no retuning |
| γ-equivalent 0.99963 against 0.9998 ± 0.0003 | **consistent within 0.2–0.6σ; PENDING_DATA / UNADJUDICATED** | one-parameter γ-equivalent of the same ϟ the Doppler/orbit chain uses; ϟ is not fitted to the deflection; GM☉ is used only for the PPN normalisation. The row-level Fomalont tables are model-processed residuals about the γ = 1 bending (D not tabulated) and give no admissible (b, δ_obs, σ) set; SDT − GR(γ = 1) is 1.85×10⁻⁴ of δ_GR (0.02–0.07 mas) against σ ≥ 0.05–0.1 mas: non-discriminating |
No bin is excluded. "EMPIRICALLY SURVIVES" is not claimed.

## 5. Direction
1. The empirical test needs an absolute or differential deflection table with the GR bending tabulated beside it (the BF080 route in the archive's D5 pre-registration is the supplier); until then GOM27 is a COMPUTED prediction with a γ-equivalent.
2. The engine's `koppa_Sun` (R☉/k_Sun²) sits 4.7×10⁻⁴ above the GOM26 invariant; whichever is carried, the limb value moves by 8×10⁻⁴″. Propose-only: reconcile at the k_Sun seat; no edit to `Engine/include/sdt/`.
3. The second-order coefficient is a profile statement: the next discriminating deflection test is at b ≲ 10⁻³ R☉ scales that do not exist for the Sun; it would need a compact lens (pulsar-binary Shapiro, GOM-class), not the solar limb.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
