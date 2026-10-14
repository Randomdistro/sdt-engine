# GOM42 (koppa N-body integrator), Round 2: V3′ and P1 — assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration of **V3′**, written before `gom42_reset_2.cpp` exists. P1 (Sun–Jupiter–Saturn great inequality) is registered separately below in Section 4 after its inputs are sourced, and before its instrument exists.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (the state after the reset; errors X1–X3; Round 2: V3′ and P1; prohibitions); `gom42_reset_1.cpp` lines 1–40 (the integrator: velocity Verlet with a_i = c² Σ κ_j (r_j − r_i)/r³, collision stop restoring the pre-step state; energy E = Σ ½ κ v² − c² Σ κ_i κ_j / r; invariants). Not read: `GOM42_ASSESSMENT.md`, `gom42_nbody.cpp`, the earlier results. Exposure: the prompt states the reset outcome (V0, V1 4.9×10⁻⁶, V2 4.000, V4 5×10⁻⁸, V5 1×10⁻¹⁴, V6 met; V3 equal-source Lagrange not met because the configuration is unstable, side drift 1.2×10⁻⁶ at 2 periods and 2.87 at 10).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | stability | The equal-source Lagrange triangle violates Routh's criterion 27(κ₁κ₂ + κ₂κ₃ + κ₃κ₁) < (Σκ)² (27 × 3 = 81 > 9), so it is unstable and cannot serve as a validation over 20 periods. V3′ takes sources (1, 0.01, 0.01): 27 × 0.0201 = 0.5427 < 1.0404 (stable by Routh). |
| D2 | construction | The Lagrange equilateral solution is exact for any source set: the triangle rotates rigidly about the κ-weighted barycentre with ω² = c² Σκ / s³ (s the side). Initial state: vertices A = (0, 0), B = (s, 0), C = (s/2, s√3/2); positions shifted to the κ-weighted barycentre; velocities v = ω ẑ × r. |
| D3 | linear stability margin | Routh's criterion is a linear-stability condition. For (1, 0.01, 0.01) the instability growth rate is zero and the small oscillation frequencies are real; round-off perturbations stay bounded at 20 periods. The gate (below) tests that numerically. |
No downgrade is made on agreement grounds.

## 2. Registered gates (fixed before the run)
**V3′.** Sources (1, 0.01, 0.01), s = 1, c² = 1 (the validation units), dt = P/4000, 20 periods (80 000 steps): max over steps of the relative side drift max_{pairs} |side − s|/s ≤ 1×10⁻⁴; barycentre drift (κ-weighted position relative to its start) ≤ 1×10⁻¹⁰ s; normalised momentum and angular-momentum drift ≤ 1×10⁻¹¹ and 1×10⁻¹⁰ (the V5 limits). Diagnostic (post-seen, not gated): the equal-source triangle (1, 1, 1) side drift after 1, 2 and 5 periods. A second, smaller perturbation check: displace one source by 10⁻⁸ s and report the drift growth over the 20 periods (stability).
**Expected landing (hand estimate before registering).** V3′ side drift of order the Verlet phase error for dt = P/4000 over 20 periods, (2π/4000)² × 20/12 ≈ 4×10⁻⁶ for a circular orbit; far below 10⁻⁴. The perturbed run grows linearly or stays bounded (no exponential).

## 3. Results, V3′ (VERIFICATION; `gom42_reset_2.cpp`, output `gom42_reset_2_results.txt`; one compile fix, `M_PI` undefined under MSVC)
Routh: 27 Σκ_iκ_j = 0.5427 < (Σκ)² = 1.0404: stable. **V3′ met:** sources (1, 0.01, 0.01), 20 periods, Δt = P/4000: max side drift **1.234×10⁻⁶** (gate 1×10⁻⁴), barycentre drift 3.5×10⁻¹⁴ (gate 10⁻¹⁰), momentum drift 5.7×10⁻¹⁵ (10⁻¹¹), angular-momentum drift 1.5×10⁻¹⁴ (10⁻¹⁰). Perturbation check (one source displaced by 10⁻⁸ s): side drift 1.301×10⁻⁶, i.e. no exponential growth. Post-seen diagnostic, equal sources (1, 1, 1): side drift 1.2×10⁻⁶ after 1 and 2 periods and 4.3×10⁻⁶ after 5 periods (the earlier instability at 10 periods was not re-run). The hand estimate 4×10⁻⁶ was conservative by a factor 3.

## 4. P1 (great Jupiter–Saturn inequality with native inputs) — summary; full record in `GOM42_P1_REGISTRATION_2026-10-14.md` sections 5–8
Sources cached with hashes (`Datasets/solar_system/GOM42_P1_SOURCES_2026-10-14.md`): Standish Tables 2a/2b (f = 38.35125°/cy → 938.68 yr; amplitudes 0.3615° and 0.8835°) and JPL satellite mean elements (Io, Titan). κ_J = 1.42114 m (Io), κ_S = 0.4222 m (Titan), κ_Sun = 1476.351201 m. Validations VP1–VP3 met; VP4 as amended met (energy 3.6×10⁻⁷). **Result: dominant long-period term 473.15 yr (−49.6% from 938.68), Jupiter amplitude 0.0748° (sourced 0.3615°), Saturn/Jupiter amplitude ratio 2.48 (sourced 2.44). G-P1 NOT MET.** Cause traced: the initial conditions' mean motions (Saturn's simulated rate +0.65% over the sourced L̇) put the 2:5 near-resonance at twice its true frequency; κ_Sun's offset leaves the period unchanged and κ_J, κ_S ×0.992 move it by 0.4%. The calibrated-initial-condition amendment did not converge and is not a result.

## 5. Grades
| Item | Grade |
|---|---|
| V3′ stable Lagrange triangle | **VERIFICATION, met (1.2×10⁻⁶)** |
| Integrator validations VP1–VP3 and VP4 (amended) | **met** |
| P1 great inequality, G-P1 (period within 2%) | **NOT MET under the registered initial conditions (473 yr against 938.7); Amendment 2 inconclusive** |
| What P1 says about the native κ inputs | **nothing decisive**: the failure comes from the initial mean motions, the test is hypersensitive to them (factor ≈ 75 in the resonance frequency), and the native inputs move the period by 0.0–0.4% |
| Label | **convergent with Newtonian N-body (as the prompt states); not a discriminator** |

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
