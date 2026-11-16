# PPT01 (vortex equilibrium quantisation) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `ppt01_reset_1.py` exists. This item was an earlier non-blind draft; this is a fresh pass from the prompt and `laws.hpp` only.

## 0. Inputs read and exposure
Read: `PPT01/PROMPT.md` in full (the question field added 2026-10-05, Steps 1–5, the mass-spectrum section, the (p,q) generalisation, Key Results, the 2026-10-05 correction: separate identity rows from tests). Not read, by the blank-slate rule: `PPT01_VERDICT.md`, `INVESTIGATION.md`, `R2_REOPEN_2026-10-05.md`, `ppt01_vortex_equilibrium.cpp`, `ppt01_r2_closure_rules.cpp`, `ppt01_r2_results_2026-10-05.txt`, the scroller. Exposure: the FLM01 prompt (read in this programme) cites "W=1 electron, W=3 proton from PPT01" with v_T = c/√2 for W=1; the PPT01 prompt's own Key Results give the proton as the (2,3) trefoil.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | question | The measurable gap (the 2026-10-05 field): do the movement-budget equilibria of a W = 1 and a W = 3 vortex (v_circ² + v² = c²) fix the quantised radii and the ratio a_e/a_p with no inserted integer? The winding number W (or the pair (p, q)) is an inserted integer by construction, so the "no inserted integer" part is answered by the structure of the derivation (D4); the radii and the ratio are what is computed. |
| D2 | identity | The budget closure v_T² + v_P² = c² is an algebraic identity once (6) and (7) are written; it cannot fail. Registered as IDENTITY, not a test. |
| D3 | premise | Eq. (4) R/a = v_P/v_T comes from Step 2, the "de Broglie" condition 2πR = h/(m v_T), 2πa = h/(m v_P) with the same mass m for both modes. That is a wave-wavelength condition on a particle (the Prohibitions list excludes wave-particle duality as an input) and it carries h. The result R/a = √W (or √(q/p)) depends on it; Eq. (1) alone gives v_P/v_T = W a/R and the budget, which leave R/a free. Registered: R/a = √W is conditional on the imported Step-2 premise; a native substitute (equal period for both circulations is Step 1; the extra condition is the ratio of the two speeds to the two sizes) is not supplied by the prompt. |
| D4 | inserted integers | W (or p, q) enters every result. The budget fixes the speed fractions and R/a *given* the integers; it does not select them. Which integers occur is the content of Law VI / PPT-line questions, not of this derivation. |
| D5 | inconsistency | The prompt assigns the proton two ways: Step 4's general result with W = 3 (p = 1, q = 3): v_T = c/2, v_P = 0.866c, R/a = √3; and Key Results 3 with the (2,3) trefoil: v_T = 0.632c, v_P = 0.775c, R/a = 1.225. Also "W=2 is unstable: unknotted, lighter than electron at same a": the statement "lighter" holds only at fixed a and is not a mass prediction. Registered: both assignments are computed and compared. |
| D6 | scale | Eq. (2)–(3) give a = ℏ/(m v_P): for the electron (1,1), a_e = √2 ℏ/(m_e c) = √2 × 3.862×10⁻¹³ m = 5.46×10⁻¹³ m (the reduced Compton scale), versus the engine's atomic c-boundary r_e = 2.82×10⁻¹⁵ m. The mass ratio is not derived (the prompt says so); a_e/a_p uses m_p/m_e as a census input. |
No downgrade is made on agreement grounds.

## 2. Registered quantities and decisions (fixed before the run)
**Instrument.** A solver independent of the closed forms: for each (p, q) iterate the fixed point ρ ← (q/p)/ρ (Eq. 1 generalised with Eq. 4, damped geometric mean), obtain ρ = R/a, then v_P/v_T = ρ and the speeds from the budget, v_T = c/√(1 + ρ²), v_P = ρ v_T. Compare with the closed forms (6)–(11) to 1e-12. Cases: W = 1, 2, 3 (p = 1) and (p, q) = (2,3), (2,5), (3,4), (1,1). Knot test: gcd(p,q) = 1 and min(p,q) ≥ 2.
**Quantities.** v_T/c, v_P/c, R/a, budget residual (expected 0, IDENTITY), for each case; electron (1,1) a_e and R_e from m_e (`sdt::laws::measured`); proton as (a) W = 3 and (b) (2,3) with m_p from `measured`: a_p = ℏ/(m_p v_P), R_p = ℏ/(m_p v_T), the ratios a_e/a_p and R_e/R_p for (a) and (b) (census-input mass ratio, labelled).
**Decisions.** Budget rows: IDENTITY. Closed forms vs the independent solve: VERIFICATION (the algebra). R/a = √W and the speeds: COMPUTED, conditional on D3. Inserted integers: stated. Dual-proton discrepancy: reported with the two sets of numbers; which assignment the framework carries is a ruling. The ratio a_e/a_p: COMPUTED from a census input, not derived.
**Expected landing (hand estimate before registering).** W=1: v_T = v_P = 0.7071c, R/a = 1; W=2: v_T = 0.5774c, R/a = 1.414; W=3: v_T = 0.5c, v_P = 0.866c, R/a = 1.732; (2,3): v_T = 0.6325c, v_P = 0.7746c, R/a = 1.2247; a_e/a_p = 2011 for (b) and 1836.15 × 0.866/0.7071 = 2249 for (a); R_e/R_p = 1642 for (b) and 1836.15 × 0.5/0.7071 = 1298 for (a).

## 3. Results (VERIFICATION / COMPUTED; `ppt01_reset_1.py`, output `ppt01_reset_1_results.txt`; single pass, no amendment)
**Equilibria.** R/a, v_T/c, v_P/c: (1,1) 1.000000, 0.707107, 0.707107; (1,2) 1.414214, 0.577350, 0.816497; (1,3) 1.732051, 0.500000, 0.866025; trefoil (2,3) 1.224745, 0.632456, 0.774597; (2,5) 1.581139, 0.534522, 0.845154; (3,4) 1.154701, 0.654654, 0.755929. Budget residual |v_T² + v_P² − c²|/c² ≤ 4.4×10⁻¹⁶ in every case (**IDENTITY**). The independent numerical solve agrees with the closed forms (6)–(11) to 2.2×10⁻¹⁶ (gate 10⁻¹²: met). Limit of that check: the damped fixed-point iteration is a Newton iteration for √(q/p), so it verifies the algebra of Steps 1–4 and the budget arithmetic, not the premise of Step 2. Knot test (gcd = 1 and min(p,q) ≥ 2): (2,3), (2,5), (3,4) knots; (1,1), (1,2), (1,3) unknots.
**Electron (1,1).** a_e = R_e = ℏ/(m_e v) = 5.461117×10⁻¹³ m = √2 ℏ/(m_e c) (equal to √2 times the reduced Compton length to the printed digits); the engine's atomic c-boundary r_e = 2.82×10⁻¹⁵ m is two orders smaller (D6; not a test).
**Proton, two assignments in the prompt.** (a) W = 3 (1,3): R/a = 1.7321, v_T = 0.5000c, v_P = 0.8660c, a_p = 2.4284×10⁻¹⁶ m, R_p = 4.2062×10⁻¹⁶ m, **a_e/a_p = 2248.8, R_e/R_p = 1298.4**. (b) trefoil (2,3): R/a = 1.2247, v_T = 0.6325c, v_P = 0.7746c, a_p = 2.7151×10⁻¹⁶ m, R_p = 3.3253×10⁻¹⁶ m, **a_e/a_p = 2011.4, R_e/R_p = 1642.3**. The two differ by 12% in a_e/a_p and 26% in R_e/R_p; the mass ratio m_p/m_e = 1836.15 enters as a census input in both. The prompt's Step 4 (W = 3) and Key Result 3 (trefoil) cannot both be the proton of the framework.
The expected landing held in every printed number (including a_e/a_p = 2011 and 2249, R_e/R_p = 1642 and 1298).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Budget closure v_T² + v_P² = c² | **IDENTITY** | algebraic; cannot fail |
| Closed forms (6)–(11) against an independent solve | **VERIFICATION, met** | 2×10⁻¹⁶ |
| R/a = √W, √(q/p) and the speed fractions | **COMPUTED, conditional on the Step-2 de Broglie condition** | Eq. (4) imports a wavelength condition with h; Eq. (1) and the budget alone leave R/a free |
| "No inserted integer" | **not achieved: W or (p, q) is inserted** | the budget fixes R/a and the speeds given the integers, not the integers |
| Radii and a_e/a_p | **COMPUTED from a census input (m_p/m_e), not derived** | 2011.4 for the trefoil, 2248.8 for W = 3 |
| Proton assignment | **OPEN: the prompt carries two (W = 3 and (2,3))** | numbers above; a ruling is needed |
Physics class: OPEN.

## 5. Direction
1. The premise of Step 2 needs a native statement (why the two circulations have sizes inversely proportional to their speeds with one common mass); until then R/a = √(q/p) is conditional.
2. The corpus should carry one proton assignment; FLM01 and the Key Results of PPT01 currently quote different ones.
3. Which integers occur (and the mass ratio) are PPT03 and Law VI questions, not this derivation.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
