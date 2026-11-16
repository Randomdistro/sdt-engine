# FLM01 (State28D force-ratio constants) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `flm01_reset_1.cpp` exists. This item was an earlier non-blind draft in the ledger of open items; this record is a fresh pass from the prompt, the engine header and `laws.hpp` only.

## 0. Inputs read and exposure
Read: `FLM01/PROMPT.md` in full (the question field, Phases 1–4, the success tiers, the 2026-10-05 correction: delete the order-of-magnitude tier and score any scale not derived to ≤ 20% as CALIBRATED/OPEN); `Engine/include/sdt/state28d.hpp` around the two scales (lines 174–208: the comments "OPEN/PENDING (HUNTER P11, 2026-07-03, Harvey-authorized flag): the 1e10 [Pa/m] … un-derived scale" and "OPEN/DEAD (HUNTER P12) … un-derived 1e-20 [J]"); `laws.hpp` symbols `l_P`, `R_CMB`, `law_I::{epsilon, Phi, P_conv}`, `P_eff`, `R_p_lock`, `r_e`. Not read: the archived FLM01 verdict, derivation, tool and results.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | record | The engine header already records both scales as un-derived (OPEN). The question "derived or fitted?" therefore has a recorded present answer; the pass tests whether the prompt's own routes change it. |
| D2 | prompt inconsistency | The prompt names the scales "10³⁰ Pa·m" and "10⁻⁹ J" in its summary and "10¹⁰ Pa/m" and "10⁻²⁰ J" in the code excerpt; the code (`state28d.hpp`) uses 10¹⁰ Pa/m and 10⁻²⁰ J. The code values are the ones tested; the summary values are listed as a prompt error. |
| D3 | dimensions | Phase 1 defines P_atom = Φ·ε/a³ and calls it a pressure. Φ and ε are energies, so Φ·ε/a³ has units J²/m³, not Pa; the "gradient" T₅ = Φε/((a_e − a_p)a_e³) has units J²/m⁴, not Pa/m. The same Phase 1 takes a_e ~ 10⁻¹⁵ m as the "atomic" and a_p ~ 10⁻¹⁸ m as the "nuclear" radius, whereas the atomic c-boundary is r_e = 2.8×10⁻¹⁵ m and the atomic size is 10⁻¹⁰ m (and the proton boundary 10⁻¹⁵ m). Registered: the Phase-1 expression is evaluated as written (to show its number) and graded as dimensionally invalid; the pressure P_conv = Φ/ℓ_P³ of `law_I` (Pa) is the dimensionally valid reading. |
| D4 | Phase 2 | Φ₅ ~ ½ m_e (c/√2)² = m_e c²/4 is an energy (J) and valid in form. |
| D5 | native candidates | The dimensionally valid native quantities with units Pa/m are P/L for the engine's pressures P ∈ {P_eff, P_conv} and lengths L ∈ {R_p_lock, r_e, ℓ_P}; with units J, the engine's energies {m_e c²/4, P_eff R_p_lock³, ε, Φ}. All are registered now (this is the whole candidate set, 6 pressure-gradient and 4 energy candidates) so the look-elsewhere count is fixed before the comparison. |
No downgrade is made on agreement grounds.

## 2. Registered quantities and decision (fixed before the run)
Compute: ε = a_rad T₀⁴ ℓ_P³ (via `law_I::epsilon`), Φ = Nε with N = R_CMB/ℓ_P, P_conv = Φ/ℓ_P³; the prompt's T₅ (as written, with a_e = 10⁻¹⁵, a_p = 10⁻¹⁸ m) and its units; Φ₅ = m_e c²/4; the ten native candidates above. Compare each with the code scales 10¹⁰ Pa/m (pressure-gradient candidates) and 10⁻²⁰ J (energy candidates): ratio and log₁₀ ratio. **Decision (the corrected rule):** a scale is DERIVED-to-≤20% only if a dimensionally valid candidate lies within 20%; otherwise CALIBRATED/OPEN. A candidate within 20% found among ten is reported with the chance expectation for a log-uniform set of that size over the span of the candidates (the look-elsewhere), not claimed as a derivation without a stated route. The order-of-magnitude tier is not used.
**Expected landing (hand estimate before registering).** Φ₅ = m_e c²/4 = 2.05×10⁻¹⁴ J, six orders above 10⁻²⁰ J; P_conv ≈ 10¹⁷–10²⁶ Pa (Φ/ℓ_P³ with Φ = Nε is enormous); the prompt's T₅ in J²/m⁴ is some number with no bearing on Pa/m; no candidate within 20% of either code scale; both scales remain OPEN.

## 3. Results (COMPUTED; instrument `flm01_reset_1.cpp`, output `flm01_reset_1_results.txt`; one pass after one compile fix (the symbols `P_eff` and `R_p_lock` live in `law_III`); no registered quantity changed)
**Engine quantities.** ε = a_rad T₀⁴ ℓ_P³ = 1.7626×10⁻¹¹⁸ J; N = R_CMB/ℓ_P = 5.8945×10⁶¹; Φ = Nε = 1.0390×10⁻⁵⁶ J; P_conv = Φ/ℓ_P³ = 2.4608×10⁴⁸ Pa; P_eff = 5.2273×10³¹ Pa; R_p_lock = 8.4124×10⁻¹⁶ m; r_e = 2.8179×10⁻¹⁵ m.
**Prompt Phase 1 as written.** P_atom = Φε/a_e³ = 1.83×10⁻¹²⁹ J²/m³ and T₅ = Φε/((a_e − a_p)a_e³) = 1.83×10⁻¹¹⁴ J²/m⁴: the target unit is Pa/m = J/m⁴, the expression has an extra energy dimension, so it is **dimensionally invalid** (D3), and its number is 124 orders below 10¹⁰.
**Prompt Phase 2.** Φ₅ = m_e c²/4 = 2.0468×10⁻¹⁴ J against the code scale 10⁻²⁰ J: ratio 2.05×10⁶ (log₁₀ 6.31), well outside 20%.
**Native candidates (dimensionally valid, the registered set of 10).** Pressure gradients [Pa/m] against 10¹⁰: P_eff/R_p_lock 6.2×10⁴⁶ (log₁₀ ratio 36.8); P_eff/r_e 1.9×10⁴⁶ (36.3); P_eff/ℓ_P 3.2×10⁶⁶ (56.5); P_conv/R_p_lock 2.9×10⁶³ (53.5); P_conv/r_e 8.7×10⁶² (52.9); P_conv/ℓ_P 1.5×10⁸³ (73.2). Energies [J] against 10⁻²⁰: m_e c²/4 2.05×10⁻¹⁴ (+6.3); P_eff R_p_lock³ 3.11×10⁻¹⁴ (+6.5); ε 1.76×10⁻¹¹⁸ (−97.8); Φ 1.04×10⁻⁵⁶ (−36.0). **0 of 10 within 20%**; the expected number inside by chance for a log-uniform set of this size over 30 decades is 0.06. The nearest candidates are the two electron-scale rest-energy-class energies, six orders above the code scale; the pressure gradients are 36 or more orders above.
Landing against the hand estimate: Φ₅ six orders above 10⁻²⁰ J (held, 6.3); no candidate within 20% (held); **P_conv ≈ 10¹⁷–10²⁶ Pa was wrong by more than 20 orders** (found 2.5×10⁴⁸ Pa), and Φ = Nε is 10⁻⁵⁶ J, not a large energy (I had read "Nε" as large because N is large; ε is 10⁻¹¹⁸ J).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| 10¹⁰ Pa/m (`state28d.hpp` T₅ scale) | **CALIBRATED/OPEN, not derived** | no dimensionally valid candidate within 20%; the prompt's Phase-1 route is dimensionally invalid |
| 10⁻²⁰ J (Φ₅ scale) | **CALIBRATED/OPEN, not derived** | the prompt's Phase-2 route gives 2.05×10⁻¹⁴ J, ×2×10⁶ |
| Prompt's summary values (10³⁰ Pa·m, 10⁻⁹ J) | **prompt error** | differ from the code values and from each other's units; not tested |
| Order-of-magnitude tier | **not used** (corrected rule) | |
Physics class: OPEN. The engine header's flags (HUNTER P11, P12) stand; nothing in `Engine/include/sdt/` is edited.

## 5. Direction
1. A derivation of either scale needs the intended physical meaning of T₅ and Φ₅ (what pressure gradient, over which torus, and which transition energy); the prompt's formulas do not supply it. If the scales are screening and transition normalisations of a smooth function (tanh and 1 + |Φ₅|/scale), a replacement by quantities with the right dimensions that already exist in the engine (P_eff/R_p_lock and an energy such as m_e c²/4) would change the behaviour by 36 and 6 orders respectively: a Harvey decision, propose-only.
2. The prompt text should be corrected (D2, D3).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
