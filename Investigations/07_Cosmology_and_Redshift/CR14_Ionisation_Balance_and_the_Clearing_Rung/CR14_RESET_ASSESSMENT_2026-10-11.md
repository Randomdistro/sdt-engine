# CR14 (ionisation balance and the clearing rung) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `cr14_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `CR14/PROMPT.md` in full (including the 2026-10-05 correction: the reproduction target R1 is struck as target-defined); `Engine/include/sdt/laws.hpp` for the measured constants (`m_e`, `k_B`, `hbar`, `Ry_eV`, `T_CMB`) and the BBN baryon-to-photon ratio `release_acoustics::eta_bbn_deuterium` = 6.1×10⁻¹⁰ with `photon_count(T)`. Not read: `CR14_ASSESSMENT.md`, `cr14_saha_ladder.py`, `cr14_results.txt` (archived). Exposure: from CR15/CR16 text in this programme and from memory the earlier conclusion that the static vessel lands in the right neighbourhood but the Saha relation is insensitive to density; these are not used as inputs.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | target | R1 asks that Branch B land within ±10% of N = 1100 and Branch C asks for the density that places the criterion exactly at 2998.05 K. Both use z = 1100 and T = 3000 K as targets; the 2026-10-05 correction and CR16 strike them as ΛCDM fitted outputs. Registered: Branch C is not run as a target-fitting step (the density sweep D carries the same functional information); R1 is replaced by the corrected form: the Branch-B N_half is reported as a prediction from the vessel's own density law, and its distance to the measured neutrality epoch is stated afterwards, with the measured epoch taken from the engine's `T_release` / `z_release` entry labelled as such. |
| D2 | premise | The present baryon number density is not in the prompt. Registered: n_b0 = η·n_γ(T_CMB), with η = 6.1×10⁻¹⁰ (BBN deuterium, an external input already in `laws.hpp`, labelled as such) and n_γ the blackbody photon number density (`photon_count`). Pure hydrogen means n_H = n_b0 (declared; helium and the non-equilibrium Peebles correction are out of scope). |
| D3 | structure | The Saha relation x²/(1−x) = S(T)/n is exponentially steep in 1/T and only logarithmic in n: d ln T_half/d ln n = 1/(3/2 + B/k_BT) ≈ 0.019 near 3000 K. R3 (non-discriminating, d ln T_half/d ln n < 0.05) is therefore expected to fire from the structure of the equation, before any run; it outranks R1. |
| D4 | contraband | R4: the Saha relation is imported statistical mechanics; no outcome may be labelled DERIVED; the best label is COMPUTED. |
| D5 | known answer | V2 uses the textbook Saha half-ionisation redshift (Dodelson §3.3) at about 1370 as the known answer for Branch A; the window 1250–1450 is the prompt's. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Equation.** x²/(1−x) = S(T)/n, S(T) = (m_e k_B T/2πℏ²)^{3/2} exp(−B/k_BT), B = `Ry_eV`; x solved by bisection to 10⁻¹⁴; T_half(n) by bisection on x(T) = criterion for criteria x = 1/2, 0.1, 0.01.
**Branches.** A: n_b = n_b0 (1+z)³, T = T₀(1+z), solved jointly (z at the criterion). B: n_b = n_b0 constant, T = N T₀ (N = T/T₀ at the criterion). D: T_half over n from 10⁻⁶ to 10¹⁴ m⁻³ (every decade). C: not run as a target step (D1).
**Validations.** V1: x → 1 at 10⁵ K and x → 0 at 10³ K on Branch A densities. V2: Branch A at x = 1/2 returns z in 1250–1450 (no branch result is reportable otherwise). V3: the analytic d ln T_half/d ln n = 1/(3/2 + B/k_BT) against a central difference of the solver, agreement < 1%.
**Statistics.** For each criterion: Branch A z and T; Branch B N and T; the density ratio n_A/n_B at the criterion; the sensitivity d ln T/d ln n analytic and numeric; the Branch-B N_half against the measured neutrality epoch afterwards (`z_release` from the engine), stated as a difference, not a pass/fail target.
**Decisions.** R3: if d ln T_half/d ln n < 0.05 at the Branch-B point, the Saha reproduction cannot discriminate and may not be cited as evidence for the static vessel (R3 outranks R1). R2/R1 replaced by the corrected D1 statement. No outcome is labelled DERIVED.
**Expected landing (hand estimate before registering).** n_b0 = 6.1×10⁻¹⁰ × 4.11×10⁸ = 0.251 m⁻³. Branch A half-ionisation at z ≈ 1370 (T ≈ 3730 K). Branch B at about 2550 K (N ≈ 940). d ln T/d ln n ≈ 0.019 (R3 fires). The density ratio between the branches at their own criteria is of order 10⁹.

## 3. Attempt 1 and Amendment 1 (instrument defect; registered before attempt 2)
**Attempt 1 (kept: `cr14_reset_1_attempt1_branchA_bisection_direction.txt`).** V1 met, V3 met, **V2 not met**: Branch A returned z = 5000 (the upper end of the bracket) at T = 13 630 K. The gate worked as designed (no branch result reportable). Cause: in the Branch-A bisection I moved the lower bound up when x_e was above the criterion; x_e rises with z, so the upper bound must move down. A sign defect of mine in the solver, not a property of the relation.
**Amendment 1.** The comparison is reversed (x_e above the criterion ⇒ the upper bound moves down). Registered gates, windows and expectations are unchanged.

## 4. Results (attempt 2; COMPUTED; instrument `cr14_reset_1.cpp`, output `cr14_reset_1_results.txt`; validations met)
**Inputs.** n_γ(T₀) = 4.107268×10⁸ m⁻³; η = 6.1×10⁻¹⁰ (BBN deuterium, external); **n_b0 = n_H = 0.250543 m⁻³**; B/k_B = 157 887.5 K.
**Validations.** V1: x_e = 1.000000000 at 10⁵ K and 1.3×10⁻²⁵ at 10³ K on Branch A densities (met). V2: Branch A at x_e = ½ gives **z = 1379.2**, T = 3761.7 K (window 1250–1450, textbook about 1370: met). V3: d ln T_half/d ln n = 0.015491 analytic and numeric, relative difference 4.8×10⁻¹¹ (met).
**Branches (x_e = 0.5 / 0.1 / 0.01).** A: z = 1379.2 / 1260.7 / 1140.2, T = 3761.7 / 3438.8 / 3110.2 K, n = 6.59×10⁸ / 5.03×10⁸ / 3.72×10⁸ m⁻³. B (static vessel): T_half = **2504.1 / 2364.6 / 2212.2 K, N = 918.8 / 867.6 / 811.7**. Density ratio n_A/n_B = 2.63×10⁹ (9.42 decades), 2.01×10⁹, 1.49×10⁹; the half-ionisation temperature ratio T_A/T_B = 1.502.
**R3 fires.** The sensitivity d ln T_half/d ln n is 0.0155 at the Branch-B point (0.0137–0.0156 over the criteria), below 0.05: a 9.4-decade difference in density moves the half-ionisation temperature by a factor 1.5. The density sweep (n from 10⁻⁶ to 10¹⁴ m⁻³) gives T_half from 2099 K to 5173 K (N from 770 to 1898): **a density of about 10⁴ m⁻³, four orders above the present baryon density, would place N at 1100; the relation cannot tell a static vessel from a diluting one by this temperature.** R3 outranks R1; the Branch-B number is not evidence for or against the vessel. Per R4 the label is COMPUTED (an imported relation); nothing is DERIVED.
**After the fact (not a target; corrected R1).** The engine's measured entry T_release = 2970.8 K (z_release = 1089, OBSERVED). The vessel's own density law gives N_half = 918.8 (x_e = ½): 15.7% below the index of the measured entry (T 2504 K against 2971 K); at x_e = 0.01 it gives 2212 K, 25.5% below. Branch A gives 3762 K (+26.6% in z at x_e = ½) and 3110 K at x_e = 0.01 (z = 1140.2, +4.7% against 1089). The Saha half-point is not the last-scattering surface (the non-equilibrium calculation is out of scope), so none of these distances is a test of either density law.
Landing against the hand estimate: n_b0 = 0.251 m⁻³ (held); Branch A z ≈ 1370 (found 1379); Branch B about 2550 K, N ≈ 940 (found 2504 K, N = 919); sensitivity ≈ 0.019 (found 0.0155); density ratio of order 10⁹ (found 2.6×10⁹).

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| Instrument (V1–V3) | **validated** | known answer z = 1379 in the window; analytic and numerical sensitivity agree to 5×10⁻¹¹ |
| Branch A (diluting density) | **COMPUTED; reproduces the textbook Saha half-point** | |
| Branch B (static vessel density) | **COMPUTED: N_half = 919 (x_e = ½), 868, 812** | depends on n_b0 from an external η (BBN) and on the criterion (spread 12%) |
| R3 | **fires: DEGENERATE-in-density (non-discriminating)** | sensitivity 0.0155 < 0.05; may not be cited as evidence for pressurised space |
| R4 | **no DERIVED label** | Saha is imported statistical mechanics |
| Corrected R1 | **N_half = 919 from the vessel's own density, 15.7% below the measured entry's index** | reported afterwards, no pass/fail |
| Branch C (inverse to a struck target) | **not run** | the sweep carries the same information without the target |

## 6. Direction
1. The one place where the vessel and the diluting density differ by nine decades produces a 1.5× difference in the half-ionisation temperature: a clearing-rung claim has to be tested by an observable that responds to density at first power (opacity, mean free path, optical depth), not by the Saha temperature (CR15 takes the density law further).
2. The criterion dependence (x_e = ½, 0.1, 0.01 span 12% in N for the same density) should be stated whenever a "recombination temperature" is quoted.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
