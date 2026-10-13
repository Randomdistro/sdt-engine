# SAR01 (Le Sage thermal budget) — blank-slate assessment (2026-10-08)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07. Instrument `sar01_reset_1.cpp`; outputs `sar01_reset_1_results_run1.txt` (registered form) and `sar01_reset_1_results_run2_amended.txt` (with one post-seen candidate). The registration of Run 1 is the header comment of the tool (three throughput candidates fixed before the run) and this record.

## 0. Inputs read and exposure
Read: `SAR01/PROMPT.md` in full; `laws.hpp` (`law_I` P_conv, P_rad, u_CMB; `law_II::F_CMB`; `law_III::P_eff`; `bridge::koppa_Sun_from_precession`). Not read: `SAR01_VERDICT.md`, `results.txt`, `sar01_lesage_budget.py` (the prompt says the earlier artifacts were deleted by design, then lists files with those names; the folder holds them).
Exposure: the prompt states the earlier leakage ceiling (η < 4.4×10⁻¹⁸) and the structure of the earlier ruling (throughpole, buffer, terminus). Both were read before the instrument was written.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | η is the fraction of the redirected flux that thermalises; its ceiling is the geothermal budget over "the occluded throughput". The prompt never defines the throughput in watts. |
| D2 | gating | The engine defines three flux quantities with power dimensions: the CMB flux, F_CMB = u c/4 (3.1289×10⁻⁶ W/m², the prompt quotes 3.131×10⁻⁶); the convergence flux P_conv c; and P_eff c. Through the Earth's cross-section they give throughputs of 4.0×10⁸ W, 9.4×10⁷⁰ W and 2.0×10⁵⁴ W, and ceilings η_max = 1.2×10⁵ (no constraint), 5.0×10⁻⁵⁸ and 2.4×10⁻⁴¹: a spread of 62 orders of magnitude. None gives the prompt's 4.4×10⁻¹⁸. |
| D3 | record | The throughput implied by 4.4×10⁻¹⁸ is 47 TW/4.4×10⁻¹⁸ = 1.068×10³¹ W. It equals the Sun's pull on the Earth times c: F = M_E c²ϟ/AU² = 3.5414×10²² N (M_E external), F·c = 1.0617×10³¹ W, η_max = 4.427×10⁻¹⁸ (ratio to the quoted ceiling 1.0061). Found by back-solving after the quoted number was seen; it identifies what the earlier ceiling meant and is not a test. |
| D4 | gating | Route B (what restores the isotropy of the redirected flux) is stated by the prompt as an open root (the Law-II release rate). |
| D5 | gating | Route C asks for the ledger "in, through and out" of the redirected flux but gives no ledger equations; the claim "the push needs no terminus" (T2) has no formula to test. |
| D6 | premise | The guard "f is a pressure ratio, not an efficiency" is respected: f is not used. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** none among the investigations (graph: layer 0, reach 32); named: Law I, Law III, EMC01 (f), the Law-II release rate. **Dependents:** per graph (stellar-radiation chain).

## 3. The five questions
**1. What do we not know?** What fraction of the movement that a body redirects to produce its push ends as disordered heat with no efflux, and what the redirected throughput is in watts.
**2. Why does it matter?** A push by occlusion removes the need for a terminus only if the heat leakage is below the budget a body shows (47 TW for the Earth). If it is not, the occlusion picture has a heating problem of the kind that ended the older corpuscle pictures.
**3. By what methods?** (M1) Define the redirected throughput in watts from the force actually produced (a flux moving at c carries energy equal to its momentum times c). (M2) Bound η by the heat budget over that throughput. (M3) Keep the alternative definitions in a table with their ceilings. (M4) State the ledger equations before claiming throughpole accounting.
**4. What would prove us wrong?** (a) Indicators: a ceiling chosen by choosing the definition; f used as an efficiency; an invented recharge. (b) Mathematics: η_max above 1 under the registered definition (no constraint) or below the measured heat (inconsistent); the ledger failing to close. (c) What it breaks: if the leakage exceeds the ceiling, every gravitational body would be heated by its own pull.
**5. Done when** the definition of the throughput is native and registered, the ceiling is computed once from it, and the ledger equations are written; otherwise recorded as open (this record).

## 4. Results (COMPUTED)
- **Validation met.** u c/4 = 3.12892×10⁻⁶ W/m² equals `law_II::F_CMB`; 3P_rad/u − 1 = 0.
- **Run 1 (three candidates, fixed before the run).** Earth cross-section πR² = 1.2752×10¹⁴ m² (R = 6.371×10⁶ m [ext]); heat budget 4.7×10¹³ W [prompt]. (1) CMB flux: throughput 3.9899×10⁸ W, η_max = 1.1780×10⁵. (2) P_conv c = 7.3774×10⁵⁶ W/m²: throughput 9.4073×10⁷⁰ W, η_max = 4.9961×10⁻⁵⁸. (3) P_eff c = 1.5671×10⁴⁰ W/m²: throughput 1.9983×10⁵⁴ W, η_max = 2.3520×10⁻⁴¹. The quoted 4.4×10⁻¹⁸ needs 1.068×10³¹ W; against the three throughputs the ratios are 2.7×10²², 1.1×10⁻⁴⁰, 5.3×10⁻²⁴.
- **Run 2 (Amendment 1, made after the quoted ceiling was compared).** Candidate (4), redirected power F·c with F the Sun's pull on the Earth: acceleration at 1 AU 5.92998×10⁻³ m/s², F = 3.5414×10²² N, F·c = 1.0617×10³¹ W, η_max = 4.4269×10⁻¹⁸ (ratio to the quoted ceiling 1.0061). With the Earth's weight instead (M_E g, g = 9.80665 m/s² [ext]): F·c = 1.7557×10³⁴ W, η_max = 2.6769×10⁻²¹.

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| Route A (the ceiling) | **G2, open: conditional on the definition of the throughput** | the ceiling is 4.4×10⁻¹⁸ if the throughput is the redirected power F·c with F the Sun's pull on the Earth (the earlier ceiling is reproduced to 0.6%); 2.7×10⁻²¹ with the Earth's weight; 5.0×10⁻⁵⁸ if the throughput is the whole convergence flux through the cross-section; 1.2×10⁵ if it is the CMB flux; the definition is not derived in the prompt, and candidate (4) was identified after the target was known |
| Route B (recharge) | **G2, open** | the named root (Law-II release rate) is not derived here |
| Route C (ledger) | not run | no ledger equations in the prompt |
| T3 (f not used as an efficiency) | consistent | f is not used |

## 6. Direction
1. A native definition of the redirected power from the force produced: P_redirected = F_net·c for a flux moving at c, with the net force the sum of all pulls on the body; register it, then bound η once. The work extracted from the redirected power is F·v, a fraction v/c of it (for the Earth's orbit v/c = 9.9×10⁻⁵).
2. The ledger for a bound orbit: the work F·v exchanged between perihelion and aphelion is returned (a buffer), so a closed orbit has zero net deposition; write that as equations and test it on the Earth's orbit and on a falling body.
3. The recharge root (Law-II release rate) stays open and is shared with other branches.
4. The alternative definitions of the throughput stay in the record as a table; a native rule must choose among them before any ceiling is quoted as a result.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
