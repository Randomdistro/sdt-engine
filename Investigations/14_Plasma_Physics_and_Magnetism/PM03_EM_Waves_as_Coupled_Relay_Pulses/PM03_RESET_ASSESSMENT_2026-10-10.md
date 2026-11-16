# PM03 (EM waves as coupled relay pulses) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `pm03_reset_1.cpp` exists. Results follow.

## 0. Inputs read and exposure
Read: `PM03/PROMPT.md` in full; `laws.hpp` names `measured::c`, `l_P`, `hbar`. Not read: `PM03_VERDICT.md` (the prompt states it was superseded for a static-Courant PASS), `pm03_em_waves.cpp`, `pm03_evolved_pulse.cpp`, `results.txt`, `pm03_evolved_results_2026-10-05.txt`. Exposure: the prompt itself states the failure of the earlier verdict (a static Courant number printed without time-stepping).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | Phase 1 evolves a second-order wave equation with the speed c as its coefficient and a tick Δt = ℓ_P/c. A pulse then moves at c by construction (at C = 1 the update is an exact one-cell shift per tick; at C < 1 the long-wave phase speed is c to second order). The pass condition |v_peak − c|/c < 1% cannot be failed by a stable run; the prompt's anti-tautology firewall is itself defeated, because the evolved run inherits c from its coefficient and tick. What the run can show: stability limits (C > 1 fails), dispersion at short wavelength, and the anisotropy of a lattice. |
| D2 | premise | "Maxwell equations as primitive" are forbidden but no native relay update is written. The wave equation in Phase 1 plays that role. A native reading: the relay passes content one cell per tick (travel); a right-moving pulse is a distribution of right-movers shifted by one cell per tick; a transverse displacement ψ is the sum of a right-moving and a left-moving part. That is exactly the C = 1 update. This reading is registered and used. |
| D3 | gating | F4 asks that c_T = c and c_L = c/√3 come out distinct, ratio 0.577. A longitudinal speed below the transverse speed has no stored-energy elastic reading (c_L²/c_T² = K/μ + 4/3 > 4/3 for positive bulk and shear moduli, so c_L/c_T > 1.155), and SDT states no stored potential for the medium; the FD05 c/√3 is a throughput ceiling in the self-jam picture, not a modulus ratio. F4 is therefore not a test of anything computed here; Phase 2 is a label (IDENTIFICATION), and no value is computed for c_L. |
| D4 | record | Phase 0 is a unit identity: SI defines the electrical units so that 1/√(μ₀ε₀) = c, with μ₀ and ε₀ carried as measured values; the check tests CODATA's internal consistency, not the lattice. |
| D5 | gating | Phase 3 (coupled E/B-like pair) is DEFER in the prompt; not run. |
| D6 | record | The "short-wavelength bend" (question 3) is available analytically for a lattice with given Δx, Δt and is computed below; it is the content of FLM10's handoff that a discrete lattice supplies without any further input. |
No downgrade is made on agreement grounds.

## 2. Registered quantities, validations, criteria
**Scheme.** Leapfrog u_i^{n+1} = 2u_i^n − u_i^{n−1} + C²(u_{i+1}^n − 2u_i^n + u_{i−1}^n), C = cΔt/Δx, periodic ring of N = 512 cells, Δx = ℓ_P, Δt = C·ℓ_P/c. A right-moving Gaussian u(x, 0) = exp(−(x/σ)²/2... exactly exp(−(x − x₀)²/(2σ²)), previous level u^{−1}(x) = f(x + CΔx) (d'Alembert).
**Phase 0 (gate).** |c − 1/√(μ₀ε₀)|/c < 10⁻⁹ with CODATA 2018 μ₀ = 1.25663706212×10⁻⁶ N A⁻², ε₀ = 8.8541878128×10⁻¹² F m⁻¹ (OBSERVED, typed from the CODATA table; not in `laws.hpp`).
**Validations.** V1: at C = 1 after 300 steps the pulse equals the initial pulse shifted by 300 cells (max error < 10⁻¹²). V2: at C = 0.5, σ = 8, after 1000 steps the solution agrees with the d'Alembert solution (analytic shift on the ring) to < 10⁻³ of the amplitude. V3: the leapfrog discrete energy E^n = Σ[(u^{n+1} − u^n)²/Δt² + c² (u_{i+1}^{n+1} − u_i^{n+1})(u_{i+1}^n − u_i^n)/Δx²] is constant to 10⁻¹⁰ relative over 1000 steps at C = 0.5.
**Phase 1 (gate, mandatory).** 1500 steps for (C, σ in cells) = (1, 8), (1, 1), (0.9, 8), (0.9, 2), (0.5, 8), (0.5, 2), (0.5, 1). Peak = argmax |u| with parabolic refinement, position unwrapped; v_peak/c = (slope of position against step in cells per step)/C. Criterion: |v_peak/c − 1| < 0.01 and max|u| ≤ 1.01 × initial for every configuration. Reported with it: final peak amplitude over initial.
**Stability (F3).** C = 1.05, σ = 8: max|u| after 1500 steps over initial; expected unbounded growth (the class "unstable" must be populated).
**Dispersion (analytic, computed).** 1-D: phase-speed ratio v_p/c = (2/(Cq)) asin(C sin(q/2)) and group-speed ratio v_g/c = cos(q/2)/√(1 − C² sin²(q/2)), q = kΔx, at q = 0.1, 0.5, 1, π/2, π for C = 0.5 and C = 1. 3-D cubic with C₃ = cΔt/Δx = 1/√3: sin²(ωΔt/2) = C₃²[sin²(q_x/2) + sin²(q_y/2) + sin²(q_z/2)]; v_p/c along the axis and along the diagonal at |q| = 0.1, 0.5, 1. Small-q: δv_p/c = −(1 − C²)q²/24 (1-D); at C₃ along an axis −q²/36. Physical scale: q for a 31 GeV photon with Δx = ℓ_P (q = Eℓ_P/(ħc)) and the resulting δv_p/c.
**Phase 2.** Printed labels only: c_T = c; c_L = c/√3 marked IDENTIFICATION (FD05); no computation (D3).
**Verdict form (prompt).** B if Phase 0 and Phase 1 pass; D if identity only; F if no evolution. Physics class: CONVERGENCE (identity plus discrete wave) / OPEN (coupling). With D1 stated: a B is a CONSTRUCTION result.
**Expected landing (hand estimate before registering).** Phase 0 passes (~1×10⁻¹⁰); C = 1 configurations give v_peak = c to rounding; C = 0.5, σ = 8 within 10⁻³; σ = 1 and 2 at C < 1 show dispersive tails (the peak is not a clean tracker there) and may exceed the 1% window or the amplitude bound; C = 1.05 grows without bound; δv_p/c at 31 GeV with d = ℓ_P is below 10⁻³⁶. The rejection class is populated by the instability case and by the short-wave dispersive cases.

## 3. Results (COMPUTED; instrument `pm03_reset_1.cpp`, output `pm03_reset_1_results.txt`)
**Attempt 1 was G0 at V2** (`pm03_reset_1_attempt1_G0.txt`, kept): my registered gate (agreement with d'Alembert to 10⁻³ at C = 0.5, σ = 8) was a tolerance I had not derived; the measured 4.35×10⁻² is the lattice dispersion (about −5×10⁻⁴ in speed over 500 cells of travel). V1 (8×10⁻²⁵) and V3 (6×10⁻¹⁵) had already shown the stencil correct. **Amendment 1** (dated in the tool header): V2 compares the finite-difference result with the exact discrete solution in Fourier space (ω = (2/Δt) asin(C sin(k/2))) to 10⁻¹⁰; the difference from d'Alembert is descriptive.
**Validations (attempt 2).** Phase 0: |c − 1/√(μ₀ε₀)|/c = 2.2×10⁻¹⁴ (met). V1 met (8.3×10⁻²⁵). V2 met (4.0×10⁻¹⁴; d'Alembert difference 4.35×10⁻² descriptive). V3 met (energy drift 5.6×10⁻¹⁵).
**Phase 1 (1500 steps, ring of 512).** | C | σ (cells) | v_peak/c | final peak / initial | max over run / initial |
|---|---|---|---|---|
| 1.00 | 8 | 1.00000000 | 1.0000 | 1.0000 |
| 1.00 | 1 | 1.00000000 | 1.0000 | 1.0000 |
| 0.90 | 8 | 0.99963 | 0.9968 | 1.0001 |
| 0.90 | 2 | 0.99829 | 0.6955 | 1.0003 |
| 0.50 | 8 | 0.99858 | 0.9944 | 1.0004 |
| 0.50 | 2 | 0.99593 | 0.5800 | 1.0048 |
| 0.50 | 1 | 0.99615 | 0.3201 | 1.0055 |
All seven meet the registered criterion (|v_peak/c − 1| < 0.01 and amplitude ≤ 1.01 × initial). The hand estimate that the short-pulse cases at C < 1 might miss the 1% window was wrong: they are within 0.4%; what they lose is the pulse shape (the peak falls to 32% of its initial value at σ = 1, C = 0.5), which the registered criterion does not measure.
**F3 stability.** C = 1.05, σ = 8: overflow to infinity within 1500 steps: UNSTABLE (the rejection class is populated; the pulse reading "carried at c" does not hold for C > 1).
**Analytic dispersion.** 1-D, C = 0.5: v_p/c = 0.999687 (q = 0.1), 0.992157 (0.5), 0.968280 (1), 0.920214 (π/2), 0.666667 (π); v_g/c = 0.999062, 0.976412, 0.903938, 0.755929, 0 (the group speed vanishes at the zone edge). C = 1: v_p = v_g = c at every q (no dispersion; v_g formally diverges at q = π). 3-D cubic at C = 1/√3: along the axis v_p/c = 0.999722 (|q| = 0.1), 0.993012 (0.5), 0.971537 (1); along the diagonal exactly 1.000000 at every q (the scheme at its Courant limit is exact along the diagonal); the axis–diagonal difference −2.8×10⁻⁴, −7.0×10⁻³, −2.8×10⁻² at |q| = 0.1, 0.5, 1. Physical scale: for a 31 GeV photon with Δx = ℓ_P, q = 2.54×10⁻¹⁸ and δv_p/c = −q²/36 = −1.8×10⁻³⁷ (axis, 3-D cubic) or −2.0×10⁻³⁷ (1-D, C = 0.5), 37 orders below any timing sensitivity. No dataset was used; a comparison with a photon-arrival-time bound is PENDING.
**Phase 2, 3.** Labels only (D3); Phase 3 DEFER.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Phase 0 identity | **CONSTRUCTION (OBSERVED dress)** | SI makes 1/√(μ₀ε₀) = c; the check tests CODATA's consistency (2.2×10⁻¹⁴) |
| Phase 1 evolved pulse at c | **G3 CONSTRUCTION, prompt verdict B** | met in 7/7 and stable for C ≤ 1, but c is the scheme's coefficient and the tick is ℓ_P/c: at C = 1 the update is an exact shift per tick (D1, D2); the rejection class is populated only by C > 1 (unstable) and by pulse-shape loss at C < 1 |
| Lattice dispersion and anisotropy (analytic) | **G3 COMPUTED** | a discrete relay lattice with C < 1 has v_p < c at q ~ 1 (axis anisotropy up to 3% at |q| = 1 on the cubic grid), and none at C = 1 in 1-D; at photon energies the effect is 10⁻³⁷ |
| F4 (c_L = c/√3 distinct from c_T) | **not a test (D3)** | label only; a longitudinal speed below the transverse one has no positive stored-energy elastic reading, and SDT states none |
| Phase 3 coupled pulses | **DEFER** | open |
Physics class: CONVERGENCE (identity plus discrete wave) / OPEN (coupling), as the prompt states.

## 5. Direction
1. The relay rule should be written natively as the pass rule (right-movers shift one cell per tick; ψ = R + L): it is the C = 1 update, exactly c, no dispersion in 1-D, and it makes Phase 1 a construction check, not a test. What is testable: how a 3-D relay lattice keeps c isotropic when the grid axes and the Courant limit differ by 1/√3 (the axis is slower than the diagonal, 3% at |q| = 1 on the cubic grid): FLM10 (lattice structure) must supply a grid for which the anisotropy is absent or invisible.
2. Replace the pass criterion by one that measures what a pulse keeps (shape retention at a given σ and C), not only its peak speed.
3. The Courant limit 1/√3 of the 3-D cubic grid and the prompt's c/√3 branch (FD05) are numerically the same number; whether they are the same fact is a lead (B-type until a mechanism links them), recorded in the addendum.
4. Photon-arrival-time bounds on a lattice spacing need a stated lattice and the quadratic coefficient: δv_p/c = −(1 − C²)q²/24 (1-D) or −q²/36 (3-D cubic axis at its Courant limit); PENDING data.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
