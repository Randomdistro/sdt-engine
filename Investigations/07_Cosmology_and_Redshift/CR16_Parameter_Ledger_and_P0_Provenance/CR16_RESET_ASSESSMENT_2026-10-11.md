# CR16 (parameter ledger and the provenance of P₀) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `cr16_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `CR16/PROMPT.md` in full; `Engine/include/sdt/laws.hpp` lines for the measured constants `T_CMB` (2.7255 K, FIRAS) and `a_rad` (7.5657×10⁻¹⁶ J m⁻³ K⁻⁴). Not read: `CR16_ASSESSMENT.md`, `cr16_ledger.py`, `cr16_results.txt` (archived). The cited object, *SDT — Cosmological Sector* (2026-07-30), Parts II and IV–IX with Propositions 1–14 and Theorems 4–5, is **not in this repository** (searched `Theory/`, `Papers/` and the cosmology investigations for the title: no file; the title occurs only inside CR14/CR15/CR16 prompt and assessment text). Exposure: the prompt quotes P₀ = 1.3916×10⁻¹⁴ Pa as the document's value.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | input | T1 compares a quoted number (1.3916×10⁻¹⁴ Pa, the document's tag [C]) with the photon-gas pressure of the measured CMB. The solar chain P_eff,⊙/z_⊙ that produced the quoted number is not reconstructible from the prompt and cannot be re-derived here (P_eff,⊙ and z_⊙ are not defined in the prompt text). The test is therefore on the quoted value; the origin chain is stated as untraced. |
| D2 | construction | T2 is an identity once T1 holds: with T_N = N·T₀ the photon-gas pressure at T_N is a T_N⁴/3 = N⁴·(a T₀⁴/3). The check shows that the clause P_N = N⁴ P₀ adds nothing beyond T_N = N T₀ and the Stefan–Boltzmann law, if P₀ = aT₀⁴/3. The count of postulates is reduced by one in that case. |
| D3 | document | T3 (dependency audit of Parts IV–IX against seven [C] inputs), T4 (parameter ledger, like for like) and T5 (zero-parameter subset) all need the document's propositions, theorems and the seven [C] inputs. They cannot be run from the repository: **PENDING_DATA**. The prompt's fairness constraint (state both halves: fewer parameters and a smaller observable list) is carried into the record as a standing condition. |
| D4 | wording | The prompt says "numbers must align when a framework is correct, so alignment is not the discriminator — origin and parameter count are". That is the rule applied here. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**T1.** P₀(T) = a_rad·T_CMB⁴/3 from `laws.hpp`'s measured constants; the number of agreeing significant figures with the quoted 1.3916×10⁻¹⁴ Pa; the prompt's rule: agreement to ≥ 4 significant figures ⟹ P₀ is a function of T₀, not an independent input. Sensitivity: the same with T_CMB = 2.7255 ± 0.0006 K (FIRAS), to state how many figures the measured T₀ itself fixes.
**T2.** For N = 1, 10, 100, 1100 (the last is shown only as the arithmetic of the clause, not as a target): P_N = N⁴P₀ against a_rad (N T₀)⁴/3: relative difference, expected 0 to rounding.
**T3–T5.** PENDING_DATA.
**Decision.** T1: the registered rule. T2: identity (grade IDENTITY once T1 holds). Postulate count reduction reported. No cosmological target number (z ≈ 1100, 3000 K) is used.
**Expected landing (hand estimate before registering).** a T⁴/3 = 1.3917×10⁻¹⁴ Pa (T⁴ = 55.18, a T⁴ = 4.175×10⁻¹⁴ J/m³); agreement with 1.3916 to 4–5 figures, within the FIRAS uncertainty (0.0006/2.7255 = 2.2×10⁻⁴ in T, 8.8×10⁻⁴ in T⁴), so the measured T₀ fixes only three figures.

## 3. Results (COMPUTED; instrument `cr16_reset_1.cpp`, output `cr16_reset_1_results.txt`; one compile fix (a missing header), then a single pass)
**T1.** a_rad = 7.5657×10⁻¹⁶ J m⁻³ K⁻⁴ and T_CMB = 2.7255 K give u = a T⁴ = 4.174783×10⁻¹⁴ J/m³ and **P₀ = a T⁴/3 = 1.391594×10⁻¹⁴ Pa** against the quoted 1.3916×10⁻¹⁴ Pa: relative difference −4.2×10⁻⁶, **five significant figures agree**. The registered rule (≥ 4 figures ⟹ P₀ is a function of T₀, not an independent input) is **met**. The measured T₀ itself fixes only three figures (FIRAS 0.0006 K ⇒ P₀ moves by ±8.8×10⁻⁴); the quoted value matches a T of 2.725503 K, i.e. 0.005 of the FIRAS standard deviation from the measured 2.7255 K. An independent solar calibration of the same number would agree with the photon-gas pressure only at the precision of its own inputs; agreement at 4×10⁻⁶ with a quantity measured to 9×10⁻⁴ says that the quoted number was built from T₀. The solar chain (P_eff,⊙ / z_⊙) that the document cites for it is not reconstructible here (D1); it is stated as untraced, not as refuted.
**T2.** P_N = N⁴P₀ against a(N T₀)⁴/3 for N = 1, 10, 100, 1100: worst relative difference 4.4×10⁻¹⁶ (**IDENTITY**). Given T_N = N T₀ and the Stefan–Boltzmann law, the second clause of P6 carries no content beyond the first once P₀ = aT₀⁴/3: **the postulate count is reduced by one**.
**T3, T4, T5: PENDING_DATA** (the document is not in the repository; the title occurs only in CR14, CR15 and CR16 text and in the 2026-10-05 audit digest).
Expected landing: 1.3917×10⁻¹⁴ Pa (found 1.3916×10⁻¹⁴), agreement 4–5 figures (found 5), the measured T₀ fixing three figures (found: ±8.8×10⁻⁴ in P₀, three figures).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| T1 P₀ = aT₀⁴/3 | **COMPUTED; shared-input (P₀ is a function of T₀); provenance of the solar chain untraced** | rule met (the quoted number reproduces to 4×10⁻⁶); the prompt's tag "independent solar calibration [C]" does not stand for the quoted value |
| T2 P ∝ N⁴ as a separate clause | **IDENTITY; clause redundant** | follows from T_N = N T₀ by Stefan–Boltzmann |
| T3–T5 | **PENDING_DATA** | document absent |
The fairness constraint is carried unchanged: any ledger drawn from T4/T5 must state both halves (fewer fitted numbers and a smaller observable list).

## 5. Direction
1. The document's tag of P₀ should read [derived from T₀] rather than [C]; the dependency of P₀ on a solar chain is then either redundant or a consistency check, to be decided when the chain is available.
2. T3–T5 need the document (or its propositions as a data file) before they can be run; a request for the file is the open item.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
