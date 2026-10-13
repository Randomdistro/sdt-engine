# GOM23 (koppa on a straight line) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom23_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM23/PROMPT.md` in full; `laws.hpp` (`bridge::koppa_Earth = v_Earth² R_Earth / c²` with v_Earth = 7909 m/s and R_Earth = 6.371×10⁶ m; `koppa_hydrogen = r_e`; `koppa_Sun = R_Sun / k_Sun²` with k_Sun = 686.3; `measured::a_0`, `alpha`, `r_e`, `R_Sun`). Not read: `GOM23_VERDICT.md`, `gom23_results.txt`, `gom23_straightline.cpp`, `DATA_REQUIREMENTS.md`. Exposure: the prompt states its own gates (0.5%, 0.1%, 1%) and the claim that the straight-line family lands on the circular ladder.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | I1 is the statement that standing still is thrust, a = c²ϟ/R², with ϟ = v²R/c² the circular-orbit definition: a = v²/R, the centripetal acceleration of a circular orbit at the surface radius. Its agreement with measured g tests that the surface-circular speed (7909 m/s) and g are consistent, a known equality; the "reaction instrument" reading is a statement about what g is, not a new measurement. |
| D2 | construction | I2 is an identity: Δν/ν = ϟh/r² = g h/c² when g = c²ϟ/r². The gate "matches gh/c²" cannot fail once I1 holds; the measured class (~4.9×10⁻¹⁴ for a 450 m tower) is the observed anchor. |
| D3 | record | I3: ϟ_H = a₀/k² with k = c/√(2E_ion/m_e) equals α²a₀ = r_e if E_ion is the infinite-mass value; with the measured hydrogen E_ion (reduced mass) the result is r_e × (1 − 5.4×10⁻⁴), the finite-proton seat offset the prompt asks to be stated. It is the Bohr-model identity (v = αc at the ground state) read as an escape speed; the straight (radial) escape is where it differs from the circular path. |
| D4 | construction | P1 (the π-audit) counts π in the lines of the recovery chains. By construction of the chains (g R²/c², ϟ h/r², a₀/k²) none contains π. The constants carry π only inside their definitions (ħ = h/2π in a₀, α), consumed as measured numbers. The audit demonstrates the form of the chains, not that the measured inputs are π-free. |
| D5 | gating | P3 validates extraction algebra on a synthetic ascent whose acceleration law is the injected one: recovery is the identity (a_prop − r̈)r²/c² = ϟ by construction. The prompt says so (the pass licenses the instrument, not the result). Real telemetry is OWED. |
| D6 | gating | P4: the closed form Δv⊥ = 2c²ϟ/(bv) is the lateral impulse of the inverse-square acceleration c²ϟ/r² along the unperturbed line; the numeric integral against the closed form is a check of calculus. The physical content is the claim that a straight line costs this impulse, which needs a measurement (deflection, null-steering) that is OWED. |
| D7 | gating | P5 asks for the Sun's straight-line ϟ. The local data contain no straight-line measurement of the Sun's ϟ that is not a fitted post-Newtonian coefficient (light deflection and radar delay are fitted γ values); that row is PENDING. |
| D8 | record | The "founding distinction" (free fall is not straight; straightness is bought by reaction) is a ruling of the author; no instrument here tests it. |
No downgrade is made on agreement grounds. Shared-form caveat (mandatory in the prompt): ϟ_E = gR²/c² equals GM/c² numerically once g = GM/R²; this chain uses neither G nor M.

## 2. Registered quantities, validations, gates (fixed before the run)
**Inputs.** c, α, a₀, r_e, R_Sun, `bridge::koppa_Earth`, `koppa_hydrogen`, `koppa_Sun` (comparison anchors; consumed only in the comparisons). OBSERVED typed literals: g₀ = 9.80665 m/s² (conventional); equatorial and polar gravity 9.780327 and 9.832186 m/s²; R_eq = 6 378 137 m; ω_E = 7.292115×10⁻⁵ rad/s; E_ion(H) = 13.598434599702 eV; infinite-mass Rydberg energy 13.605693122994 eV (for the offset statement); h = 450 m; chronometric class 4.9×10⁻¹⁴.
**P1.** The consumed constants of each chain listed; π-count of the chain formula strings (expected 0).
**P2 I1.** a_pred = c² ϟ_E/R_Earth² (anchor) against g₀: gate |a_pred/g₀ − 1| < 0.5%, and inside the polar–equatorial band; equatorial row: a_pred(R_eq) − ω²R_eq against 9.780327, gate < 0.5%. Recovery: ϟ_rec = g₀R²/c² against the anchor.
**P2 I2.** Δν/ν = ϟ_E h/R² at h = 450 m against g₀h/c² (gate 1%) and against 4.9×10⁻¹⁴ (gate 2%).
**P2 I3.** ϟ_H,rec = a₀/k², k = c/√(2E_ion/m_e) with the measured E_ion against r_e: gate 0.1%; and with the infinite-mass E: identity to 10⁻¹².
**P3.** Vertical ascent from R_Earth to about R_Earth + 200 km, proper acceleration a_prop(t) = 15 + 10 t/T m/s² (T = 300 s), integrated with RK4 (dt = 0.01 s) under a = a_prop − c²ϟ_inj/r², ϟ_inj = koppa_Earth; kinematic acceleration by the central second difference of r(t); ϟ_i = (a_prop,i − r̈_i) r_i²/c²; mean over interior samples against the injection: gate 0.1%. Descriptive: the kinematic precision needed for 0.1% (δa < 10⁻² m/s²).
**P4.** Line at speed v = 3×10⁴ m/s past the Sun (b = R_Sun, ϟ_Sun anchor) and the Earth (b = R_Earth, ϟ_E, v = 10⁴ m/s): the integral of c²ϟ b/(b² + x²)^{3/2} dx/v over |x| ≤ X, by Simpson in x = b sinh u (independent of the analytic form), for X/b = 10³ and 10⁴, against 2c²ϟ/(bv); gate 0.5%. Descriptive: a full trajectory integration (RK4, step ∝ r/v) in the same field from x = −X to X, transverse velocity change against the closed form.
**P5.** Closure table, whole range, single pass: Earth (I1 recovery against the anchor), hydrogen (I3 against r_e), Sun (PENDING, D7); gate every computed row < 1%.
**Validations.** V1: Simpson in sinh substitution reproduces ∫dx/(b²+x²)^{3/2} = 2X/(b²√(b²+X²)) for a test b to 10⁻¹⁰. V2: the RK4 free-fall check: with a_prop = 0 the integrator conserves energy to 10⁻⁹ over 300 s from R_Earth with the injected field. V3: constants read from `laws.hpp` match the stated values (c exact; α a₀ identity r_e).
**Expected landing (hand estimate before registering).** I1: +0.119% against g₀ (9.8183 against 9.80665); equatorial row −0.18%; I2: 4.9158×10⁻¹⁴, ratio to gh/c² 1.0011, to the measured class +0.32%; I3: −0.0534%; P3: recovery to about 10⁻⁶ or better; P4: the line integral to 10⁻⁹ or better; the trajectory integration within about 4×10⁻⁴ for the Sun case; P5: Earth −0.118%, hydrogen −0.053%, Sun PENDING.
**Registration slip (corrected before the run, noted in the tool header).** The P4 speeds were registered as 3×10⁴ m/s (Sun) and 10⁴ m/s (Earth); both lie below the escape speed at b, so the "line" would be a hyperbolic dive (Δv⊥ larger than v). The run uses 3×10⁷ m/s (Sun, deflection/v = 4.2×10⁻⁴) and 10⁶ m/s (Earth, 1.3×10⁻⁴).

## 3. Results (COMPUTED; instrument `gom23_reset_1.cpp`, output `gom23_reset_1_results.txt`; single pass, no amendment; all validations met)
**Validations.** V1 met (3.3×10⁻¹⁶); V2 met (RK4 energy change 1.4×10⁻¹⁵ over 300 s); V3 met.
**P1.** Three chains listed with their consumed constants; π in the formula strings: 0 (VERIFICATION, by the form of the chains, D4).
**I1.** a = c²ϟ_E/R_E² = 9.81828 m/s² against g₀ = 9.80665: **+0.1186%** (gate 0.5%: met), inside the polar–equatorial band [9.780327, 9.832186]. Equatorial: c²ϟ_E/R_eq² = 9.79632, centrifugal ω²R_eq = 0.03392, difference 9.76241 against 9.780327: **−0.1832%** (gate 0.5%: met). Recovery ϟ_rec = g₀R²/c² = 4.428886×10⁻³ m against ϟ_E = 4.434139×10⁻³ m: −0.1185%.
**I2.** h = 450 m: ϟ_E h/R² = 4.9159×10⁻¹⁴; g₀h/c² = 4.9101×10⁻¹⁴ (ratio 1.00119; gate 1%: met); against the measured class 4.9×10⁻¹⁴: +0.325% (gate 2%: met).
**I3.** k = c/√(2E_ion/m_e) = 137.07257 (1/α = 137.03600); ϟ_H,rec = a₀/k² = 2.816437×10⁻¹⁵ m against r_e = 2.817940×10⁻¹⁵ m: **−0.0533%** (gate 0.1%: met). With the infinite-mass Rydberg energy: +1.9×10⁻¹² relative to r_e; the finite-proton seat offset is −0.0533%.
**P3.** Synthetic ascent r: 6 371 000 → 6 761 462 m in 300 s; mean recovered ϟ = 4.434139×10⁻³ m against the injected 4.434139×10⁻³ m: −3.7×10⁻¹¹ (gate 0.1%: met); worst sample 1.0×10⁻⁶. Descriptive: 0.1% requires the kinematic and accelerometer error below 0.010 m/s².
**P4.** Sun (v = 3×10⁷ m/s): line integral 1.272102×10⁴ m/s against the closed form 1.272103×10⁴ m/s at X/b = 10³ (−5.0×10⁻⁷) and 10⁴ (−5.0×10⁻⁹); Earth (v = 10⁶ m/s): 125.1045 against 125.1046 m/s at 10³ (−5.0×10⁻⁷). Gate 0.5%: met in all four. Trajectory integration (RK4 in the same field): transverse change within −3.3×10⁻⁷ (Sun) and −4.4×10⁻⁷ (Earth) of the closed form; the estimate that second-order terms would reach ~4×10⁻⁴ was pessimistic.
**P5.** Earth −0.1185% (gate 1%: met); hydrogen −0.0533% (met); Sun PENDING.
Anchors: ϟ_E = 4.434139×10⁻³ m, ϟ_Sun = 1477.0459 m, ϟ_H = 2.817940×10⁻¹⁵ m.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| P1 π-audit | **VERIFICATION, met** | zero π by the form of the chains; the measured a₀ and α carry ħ = h/2π in their definitions (D4) |
| I1 standing still is thrust | **VERIFICATION; G3 shared-input** | a = v²/R: the Earth anchor v_E = 7909 m/s is the first cosmic speed √(gR) (7904 m/s with g₀) rounded, so agreement at 0.12% shares g with the recovery (D1); an independent ladder rung would be a satellite's or the Moon's v²r |
| I2 clock tower | **VERIFICATION (identity)** | equals g h/c² once I1 holds (D2); the measured class 4.9×10⁻¹⁴ is the observed anchor, +0.33% |
| I3 photoionisation | **VERIFICATION; G3 shared-input** | the Bohr identity v = αc as an escape speed; E_ion (spectroscopy) and α, a₀ come from one CODATA adjustment (the infinite-mass identity holds to 2×10⁻¹²); the −0.0533% finite-proton offset is stated |
| P3 synthetic ascent | **VERIFICATION (algebra)** | recovery is the identity by construction (D5); real launch telemetry OWED |
| P4 null-steered line | **VERIFICATION (calculus)** | closed form confirmed; the physical claim needs a deflection or null-steering measurement (OWED, D6) |
| P5 closure table | **incomplete: Earth and hydrogen met, Sun PENDING** | no straight-line Sun measurement local that is not a fitted coefficient (D7) |
F1–F5 are not triggered. No π enters any recovery chain.

## 5. Direction
1. The Earth rung needs an anchor independent of g: a satellite orbit (v²r from a period and a semi-major axis, which carries the sampling-geometry π) against g R²/c².
2. The Sun's straight-line rung needs a raw (unfitted) deflection or radar-delay measurement through a stated chain; this is where the GOM_DAT chain (Cassini ODF/TDF, decoded in this programme) would feed.
3. The hydrogen rung reproduces k = 137.0726 as the seat value from the measured ionisation energy with m_e (finite-proton offset 5.3×10⁻⁴ from 1/α); a native statement of the offset is the reduced mass.
4. Real ascent telemetry (named class in `DATA_REQUIREMENTS.md`) is the data requirement that turns P3 from algebra into a measurement.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
