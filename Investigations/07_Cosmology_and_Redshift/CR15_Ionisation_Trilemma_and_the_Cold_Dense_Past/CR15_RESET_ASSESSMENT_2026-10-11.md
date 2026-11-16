# CR15 (ionisation trilemma and the cold dense past) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `cr15_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `CR15/PROMPT.md` in full (including the 2026-10-05 correction: the ±10% window around N = 1100 is struck as a target and is replaced by a prediction from the vessel's own density law); the CR14 and CR16 records of this programme (the Saha solver and its three gates, V2 at z = 1379.2; n_b0 = η·n_γ = 0.2505 m⁻³; the finding that the half-ionisation temperature is insensitive to density). Not read: `CR15_ASSESSMENT.md`, `cr15_trilemma.py`, `cr15_results.txt` (archived). The cited document (*SDT — Cosmological Sector*, 2026-07-30) is not in the repository (CR16 record): T1 cannot be run.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | document | T1 (recompute every [D]-tagged number of Parts VI–IX: N_max, v_min, T_max, ρ_s, P_min, T_end, v_dec, t_lb, D_CMB, BAO u_r, τ_now) requires the document: **PENDING_DATA**. The same absence limits T4's optical-depth half (the path length is the document's) and the t_lb quantities. |
| D2 | target | T2's window (±10% of N = 1100) and T5's "place the transition at N = 1100" use the struck target. Registered: T2 is run as a prediction of the half-ionisation epoch N_half from the stated postulates; the logical content, whether the postulate set (i)+(ii)+Prop 13 puts a neutrality transition at the epoch the document identifies with the CMB, is read from N_half without a window. T5 is run as a descriptive scan of N_half against the bridge exponent s (n ∝ N^{4s}) and the s that the struck target would require is reported as such, not as a result. |
| D3 | construction | T4 is the diluting-density branch of CR14 (Branch A: n_b = n_b0 N³, T = N T₀, B constant) under another name; the numerical result is the CR14 value by construction (identity of the two statements), so the content is the label and the optical-depth half. |
| D4 | scaling | T2 and T3 follow from scalings: in T2, B/k_BT = (B₀/k_BT₀)/N³, S ∝ N^{3/2}, n ∝ N³; in T3 (Prop 5 with T ∝ N⁻²) B/k_BT is constant at B₀/k_BT₀ = 57 931 and S/n ∝ N⁻⁶. The solver reproduces these exponents on known limits before the results are read. |
| D5 | trap | The prompt names the trap: an N near 10 from T2 is not to be read as a match to the reionisation epoch (the cube root of an imported number). Registered: no comparison with reionisation is made. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Solver.** CR14's: x²/(1−x) = S/n with S = (m_e k_BT/2πℏ²)^{3/2} exp(−B/k_BT), B₀ = `Ry_eV`, n_b0 = η·n_γ(T₀) (0.250543 m⁻³), pure hydrogen. The three CR14 gates are re-run: V1 limits, V2 Branch A at x_e = ½ in 1250–1450 (≈1379), V3 analytic against numerical sensitivity (< 1%).
**T2.** B(N) = B₀/N², T = T₀N, n = n_b0N³: x_e(N) over N = 1 … 3000 (log grid), the half-ionisation epoch N_half (the crossing x_e = ½, if any), and the ionised-era extent (N range with x_e > ½).
**T3.** B = B₀/N², T = T₀/N², n = n_b0N³ (Prop 5 as written): x_e(N) over the same grid; whether x_e is monotonically decreasing in N; whether any N has x_e > ½. Computed in logarithms to avoid underflow: ln(S/n) is printed.
**T4.** The CR14 Branch A: z at x_e = ½ (identity with V2) and the statement of the optical-depth half as PENDING_DATA (the document's path length).
**T5.** N_half(s) for s = 0, 1/8, 1/4, 3/8, 1/2, 5/8, 3/4, 1 (n = n_b0N^{4s}, T = T₀N, B constant), and the s for which the struck target N = 1100 would be placed (solved by bisection; reported as the exponent the target would require, not as a result).
**Decisions.** T2: N_half stated; if the ionised era (x_e > ½) extends to all N > N_half, the transition cannot coincide with an epoch in the past of N_half, and legs (i)+(ii)+Prop 13 are in conflict with the document's identification of the CMB epoch with the neutrality transition (a combination, not the vessel: the prompt's limit on what a failure concludes). T3: if x_e is monotonically decreasing in N and below ½ everywhere, no ionised era exists under Prop 5 as written. T1: PENDING_DATA. Labels: COMPUTED; none DERIVED (R4 of CR14 stands).
**Expected landing (hand estimate before registering).** T2: ln(S/n) = ln(4.3×10²²) − 1.5 ln N − 57 931/N³ crosses ln(½) near N = 10.7; the bath is ionised for all N above it (so the transition lies at N ≈ 10.7, not at the document's CMB epoch); T3: x_e ≈ 0 at every N (ln(S/n) ≈ −57 931 + 51 − 6 ln N), monotonically decreasing, no ionised era; T4: z = 1379.2; T5: N_half(s = 3/4) = 1379 and N_half ≈ 1100 at s ≈ 3/8.

## 3. Attempt 1 and Amendment 1 (instrument defect; registered before attempt 2)
**Attempt 1 (kept: `cr15_reset_1_attempt1_xe_cancellation.txt`; run 2026-10-12 after the instrument file, lost in the interrupted session, was rewritten from the same text).** V1 met, V2 met (z = 1379.20), **V3 not met** (analytic 0.603, numeric 0.000), `VALIDATIONS NOT MET -> G0`: no result of T2–T5 was produced. Cause: my x_e routine used the root x = ½(−r + √(r² + 4r)), which loses all precision for r ≳ 10¹⁶ (it returns 0 instead of 1), so the temperature bisection of V3 ran to its upper bound. The CR14 routine had a guard for large r; I dropped it. Also, for r → 0 the routine returned r instead of √r. Defects of mine, caught by the gate.
**Amendment 1.** x_e = 2/(1 + √(1 + 4/r)) (stable for all r, x ≈ √r for small r), for ln r < −700 x = exp(ln r / 2). The equation, gates, windows and expectations are unchanged.
**Attempt 2 and Amendment 2 (kept: `cr15_reset_1_attempt2_target_exponent_sign.txt`).** Validations met and T2–T5 produced; the last descriptive line of T5 (the exponent that the struck target would require) printed s = 1.00000, which contradicts the table above it (N_half(s = 3/8) = 1096.8): the bisection moved the bounds the wrong way since N_half increases with s. A sign defect of mine in a line that is not a result. Amendment 2: the comparison is reversed; nothing else changes. All other attempt-2 numbers stand and are re-printed by attempt 3.

## 4. Results (attempt 3; COMPUTED; instrument `cr15_reset_1.cpp`, output `cr15_reset_1_results.txt`; validations met)
**Validations.** V1 limits (x_e = 1.000000000 at 10⁵ K, 1.3×10⁻²⁵ at 10³ K), V2 (Branch A z = 1379.20 in 1250–1450), V3 (sensitivity 0.015491 analytic and numeric): met.
**T1: PENDING_DATA** (the [D]-tagged numbers belong to the document, which is not in the repository).
**T2 (B ∝ N⁻², T = T₀N, n = n_b0N³).** B/k_BT = 57 930/N³, so the exponential factor is negligible above N ≈ 20 and S/n ∝ N^(−3/2). The half-ionisation crossing is at **N_half = 10.554**; x_e = 1 − 7×10⁻³ at N = 11, 1.000000 from N = 15; x_e is 1.000000000 for every N from 11 to 3000, including N = 1100. **The postulate set (i) + (ii) + Prop 13 gives a neutrality transition at N ≈ 10.6 and an ionised bath at every earlier epoch (larger N): it places no transition at the epoch the document identifies with the CMB.** Per the prompt's own limit this falsifies a combination (P5, P6, Prop 13 with the CMB identification), not the vessel, the pressure ladder or Part V. As the prompt warned, N_half ≈ 10.6 is not compared with the reionisation epoch.
**T3 (Prop 5 as written: B ∝ N⁻², T ∝ N⁻²).** B/k_BT is constant at 57 929.7; ln(S/n) = −57 878 at N = 1 and decreases monotonically (−57 891 at N = 10, −57 920 at N = 1100); x_e ≈ exp(ln(S/n)/2) underflows to 0 at every N. **No ionised era exists under Prop 5 as written**: x_e is monotonically decreasing in N and nowhere reaches ½; there would be no recombination event to trigger and the CMB could not be a last-scattering surface by this route. The registered consequence for `z_rec`/`T_rec` (leaving the `measured` namespace) is a finding for a ruling; the engine is not edited (propose-only).
**T4.** The diluting branch is CR14 Branch A: z = 1379.20 at x_e = ½ (N_half = 1380.20 in the T5 table at s = 3/4: the same number as N = 1 + z). Reproduces the comparator by construction; the optical-depth half is PENDING_DATA (path length from the document). CR14's Branch E objection is not withdrawn or confirmed here.
**T5 (n = n_b0N^{4s}, T = T₀N).** N_half(s): s = 0: 918.8 (2504 K); 1/8: 970.4; 1/4: 1029.2; 3/8: 1096.8 (2989 K); 1/2: 1175.5; 5/8: 1268.4; 3/4: 1380.2 (3762 K); 1: 1692.2 (4612 K). The scan is slow in s (the sensitivity of CR14). The exponent that the struck target N = 1100 would require is s = 0.3805 (n ∝ N^1.52): reported as such, **not a result and not a prediction of PENDING (1)**; it follows from imposing a ΛCDM-fitted output, and a different exponent is equally compatible with any epoch within ±25% of it.
Landing against the hand estimate: T2 N_half ≈ 10.7 (found 10.55), the ionised bath at every larger N (held); T3 no ionised era (held); T4 z = 1379.2 (held); T5 N_half(3/4) = 1379 (found 1380.2 = 1 + z) and N ≈ 1100 near s = 3/8 (found 1096.8 at s = 3/8; the target needs 0.3805).

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| T1 arithmetic audit | **PENDING_DATA** | document absent |
| T2 legs (i)+(ii) with Prop 13 | **COMPUTED: transition at N = 10.55, ionised for all N above; not at the CMB identification** | combination of P5, P6, Prop 13 and the identification is in conflict |
| T3 Prop 5 reading | **COMPUTED: no ionised era (x_e monotone decreasing, below ½ everywhere)** | CMB cannot be a last-scattering surface under this reading; `z_rec`/`T_rec` provenance question for a ruling |
| T4 CR14 correction | **identity with CR14 Branch A (z = 1379.2); τ half PENDING_DATA** | |
| T5 bridge exponent | **descriptive scan; the struck target's exponent s = 0.3805 not a result** | |
| Labels | **COMPUTED; none DERIVED** | Saha is imported (CR14 R4) |

## 6. Direction
1. The trilemma is real as a computation: the three legs cannot all hold. Which leg is withdrawn is a ruling, with the consequences listed above (T2: a transition at N ≈ 10.6 under P5/P6 with Prop 13; T3: no ionised era under Prop 5 alone).
2. The document is needed for T1 and the optical-depth half of T4.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
