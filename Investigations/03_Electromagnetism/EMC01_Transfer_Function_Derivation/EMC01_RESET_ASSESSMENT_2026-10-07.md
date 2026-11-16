# EMC01 — blank-slate assessment (2026-10-07)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1.

## 0. Inputs read before the pre-registration, and exposure
Read: `EMC01/PROMPT.md` (including its 2026-10-05 gating note); `laws.hpp` (`measured`, `law_I` P_conv/N/Φ/ε, `law_III` P_eff, f_transfer, R_charge, F_occlusion, F_coulomb, F_nuclear_electron, `lock_geometry`); the graph (EMC01: layer 0, reach 101, consumers FLM03 and GOM02, no supplier among the investigations). Not read: `EMC01_VERDICT_DIRECT_2026-07-23.md`, `emc01_rerun_2026-07-23.txt`, `emc01_transfer_function.cpp`, `emc01_scroller.html`.
Exposure: the prompt states its own resolution (the substitution that gives P_eff = m_p²m_e²c⁵/(4παℏ³)) and its expected routes; the engine labels P_eff "target-free", class C, "passes delete-test", and describes an "EMC04 electropause balance". The author evaluated the algebra of the substitution before registering (it holds). The tests below check that algebra numerically, trace each input to its measurement chain, and test the claims the prompt makes about independence; the expected landing in §5 is stated with this disclosure.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | P_eff is defined by the requirement F_Coulomb = (π/4)P_eff R_charge⁴/r² with R_charge⁴ = (R_p r_e)². Its numerator is therefore the hydrogen coupling αℏc. A recovery of the Coulomb strength at the hydrogen seat from this P_eff is an equality between the definition and its use. |
| D2 | gating | The delete-test as written ("remove the Coulomb comparison; does P_eff stand?") has two readings: (a) no Coulomb force measurement enters (the numerator αℏc is α, the hydrogen rung, a spectroscopic input), (b) no Coulomb coupling enters at all (false: αℏc is the coupling). The result depends on which quantity is called the input. The gateway fixes the reading by origin: α is the koppa rung of the hydrogen ground state (CLAUDE.md, PPT02/APS05), an SDT input measured by CODATA g-2 and atom-recoil chains, not by a force measurement. |
| D3 | data | The engine's r_e is α²a₀ with a₀ measured (spectroscopy via R∞); the prompt's Class A condition is "no measured length input". The basis form αℏ/(m_e c) replaces a₀; the two are equal to the mutual consistency of the CODATA constants. |
| D4 | gating | "Route C" (centripetal balance m_e v²/a₀ at v = αc, inverted through the occlusion law) is algebraically P_eff,C = 4m_ec²/(πR_p²r_e). Its ratio to Route A is m_e c r_e/(αℏ), which equals 1 when r_e = αℏ/(m_ec), i.e. when a₀ = ℏ/(m_e c α) (the Bohr relation). |
| D5 | gating | "f's global reading independent of R_CMB" (T4): f = P_eff/P_conv with P_conv = N u_CMB and N = R_CMB/ℓ_P; f ∝ 1/R_CMB by definition. The question is the origin of R_CMB (`measured::R_CMB`, OBSERVED, an observed cosmological scale), not its exponent. |
| D6 | premise | The root dependency named by the prompt is the lock rule R_p = (W+1)ℏ/(m_p c) with W+1 = 4 (supplier FLM07, not run blind here). P_eff ∝ (W+1)⁻². |
| D7 | data | CODATA 2022 R_p is not in the repo or `Datasets/`; the comparison uses the engine value (8.414e-16 m, quoted 0.8414(19) fm in other prompts of this repo). Entering the 2022 value requires a manifest row (PENDING). |
| D8 | record | The prompt's "G within 5×" gate and the vacuum-cancellation claims rest on the cosmology debt (R_CMB) and on FLM01's hierarchy; the prompt does not give the G construction. DEFERRED to FLM01/FLM06 (not run here). |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** none among the investigations (graph); inputs {α, ℏ, c, m_p, m_e} (engine), W+1 = 4 (FLM07, open supplier), a₀ (measured), R_CMB, u_CMB (measured). **Dependents:** FLM03, GOM02 (graph); `laws.hpp` F_coulomb, F_nuclear_electron, f_transfer. Edges: FLM07 → EMC01 `required` (root dependency); EMC01 → FLM03, GOM02 `required`.

## 3. Hypotheses, observables, ledger
H1 (Route A): P_eff constructed from {α, ℏ, c, m_p, m_e} with R_p = 4ℏ/(m_p c) equals the engine's P_eff, and equals the Coulomb-defined P_eff with the measured R_p to within the 0.02% R_p residual (0.04% in P_eff). H2 (delete-test, reading a): no measured length enters P_eff beyond the basis quantities. H3 (Route C): the centripetal route reproduces Route A. H4: f is independent of R_CMB. H5: the lock integer W+1 = 4 is consistent with the measured R_p ƛ_p ratio.
Ledger: α, ℏ, c, m_p, m_e, a₀, R_p, R_CMB, T_CMB MEASURED-INPUT (engine); W+1 = 4 integer from FLM07 (supplier open); no calibrated parameter; P_eff and f DERIVED/COMPUTED as stated.

## 4. Pre-registration (written before `emc01_reset_1.cpp` exists)

**Validations (not met ⇒ G0).**
- V1 (known answer): the hydrogen Coulomb force αℏc/a₀² = 8.2387e-8 N (to 1e-4); ħc = 197.327 MeV fm; P_conv and f of the engine reproduce the prompt's 2.459e48 Pa and 2.123e-17 within 0.5% (the prompt's values are claims, tolerance registered for the transcription only).
- V2 (exponent machinery): central finite differences d ln F/d ln x recover the exponents of a test function x²y⁻³z^{1/2} to 1e-8.

**Tests.**
- T1 (COMPUTED, Route A): P_basis = m_p²m_e²c⁵/(4παℏ³); P_engine = `law_III::P_eff`; P_Coulomb-defined = 4αℏc/(πR_p²r_e²) with measured R_p. Ratios and relative differences. Rejection criterion R1: H1 rejected if |P_basis/P_engine − 1| > 1e-3 or |P_engine/P_Coulomb-defined − 1| > 5e-4.
- T2 (COMPUTED, delete-test): (a) dependence exponents d ln P_eff/d ln x for x = α, ℏ, c, m_p, m_e, (W+1); (b) P_eff recomputed with a₀ replaced by ℏ/(m_ec α): relative change δ_a0; (c) F_coulomb(r)·r² against αℏc (CONSTRUCTION check). Rejection criterion R2: H2 rejected if |δ_a0| > 1e-6. Contaminating-input line recorded for (c): αℏc — measured via CODATA α (g-2 and atom-recoil chains) — enters at `laws.hpp:461`.
- T3 (COMPUTED, Route C): P_C = 4m_ec²/(πR_p²r_e) with the engine's r_e and R_p_lock; ratio P_C/P_A − 1. Rejection criterion R3: H3 rejected if |P_C/P_A − 1| > 1e-6.
- T4 (COMPUTED): f = P_eff/P_conv; the closed form 4αℏcℓ_P/(πR_p²r_e²R_CMB u_CMB) to 1e-12; d ln f/d ln R_CMB. Rejection criterion R4: H4 rejected if |d ln f/d ln R_CMB| > 1e-6.
- T5 (COMPUTED): (W+1)_eff = R_p m_pc/ℏ with σ from 0.0019 fm; P_eff for W+1 = 3, 4, 5; the number of integers within 3σ (look-elsewhere count 3). Rejection criterion R5: H5 rejected if |(W+1)_eff − 4| > 3σ. Report the P_eff shift if (W+1)_eff replaces 4.
- T6: the G gate (D8): DEFERRED (FLM01/FLM06).

**Whole-range single pass.** All tests are evaluated once.

## 5. Gradated outputs and triggers
| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1 or V2 not met | repair the instrument |
| G1 | R1, R2, R3 or R5 met | name the premise (substitution, measured length, lock rule) and open the alternatives of §6 |
| G2 | conditional on FLM07 (the lock integer) | FLM07 outcome decides |
| G3 | consistent within tolerance, shared-input (contaminating-input line written) | derive the input or find an independent measurement |
| G4 | consistent, independent origin | not expected for the Coulomb strength at the seat |
| G5 | not available | — |
Expected landing (with the exposure of §0): R1–R5 not met; G3 for the Coulomb strength at the seat (CONSTRUCTION, contaminating input αℏc), G2 for P_eff as a parameter-free function (conditional on FLM07), R4 met (f ∝ 1/R_CMB).

## 6. Alternative outs
1. A second force from the same P_eff and radii compared with a measurement not used to set P_eff (the Z-scaling of hydrogenic ionisation energies, the deuteron well of NP06/NP17).
2. The G construction (FLM01/FLM06) with R_CMB replaced by the koppa closure ℓ_P² = ϟ ƛ (FLM06), so f has no cosmological input.
3. An independent determination of the boundary radius (muonic spectroscopy datum with a manifest row) to test the lock integer at the 1e-3 level.

## 7. Run record

- Date 2026-10-07. Instrument `emc01_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; constants from `sdt::laws`). Output `emc01_reset_1_results.txt`. Single pass, no re-run, no amendment.
- **Validations met.** V1: αℏc/a₀² = 8.23872e-8 N (8.2387e-8); ℏc = 197.3270 MeV fm; P_conv = 2.46082e48 Pa (prompt 2.459e48); f = 2.12419e-17 (prompt 2.123e-17). V2: finite-difference exponent error 2.2e-11.
- **T1 (COMPUTED, Route A).** P_basis (W+1 = 4) = 5.227252e31 Pa; closed form m_p²m_e²c⁵/(4παℏ³) = 5.227252e31 (relative difference 4e-16); `law_III::P_eff` = 5.227252e31, P_basis/P_engine − 1 = +1.22e-9; Coulomb-defined with the measured R_p (8.41400e-16 m against R_p_lock = 8.41236e-16 m): 5.225210e31, P_engine/P_Coulomb-defined − 1 = +3.908e-4 (equal to (R_p/R_lock)² − 1). R1 not met: H1 consistent.
- **T2 (COMPUTED, delete-test).** Exponents d ln P_eff/d ln x (basis form): α −1.0000, ℏ −3.0000, c +5.0000, m_p +2.0000, m_e +2.0000, (W+1) −2.0000. The measured a₀ (5.2917721090e-11 m) and ℏ/(m_ecα) (5.2917721058e-11 m) differ by −6.1e-10; replacing a₀ changes P_eff by +1.22e-9 (R2 not met: the measured length is redundant with the basis quantities to 1.2e-9). F_coulomb(r)r²/(αℏc) − 1 = −2.2e-16: CONSTRUCTION, contaminating input: αℏc — measured via CODATA α (g-2 and atom-recoil chains) — enters at `laws.hpp:461`.
- **T3 (COMPUTED, Route C).** P_C = 4m_ec²/(πR_lock²r_e) = 5.227252e31 Pa; P_C/P_A − 1 = +6.1e-10, equal to m_ecr_e/(αℏ) − 1 and to the a₀ relation above (R3 not met). The two routes differ only through the Bohr relation a₀ = ℏ/(m_ecα) as realised in the CODATA constants.
- **T4 (COMPUTED).** f = 2.124189e-17; closed form 4αℏcℓ_P/(πR_lock²r_e²R_CMB u_CMB) agrees to 6e-16; d ln f/d ln R_CMB = −1.000000; R_CMB = 9.5270e26 m (MEASURED-INPUT, observed cosmological scale). R4 met: f is not independent of R_CMB.
- **T5 (COMPUTED).** (W+1)_eff = R_pm_pc/ℏ = 4.00078 ± 0.00903 (σ from 0.0019 fm), +0.09σ from 4; P_eff(W+1 = 3, 4, 5) = 9.2929e31, 5.2273e31, 3.3454e31 Pa; P_eff shifts by −3.906e-4 if (W+1)_eff replaces 4; of the integers 2…6 one lies within 3σ. R5 not met.
- **T6.** G gate: DEFERRED (FLM01/FLM06).
- Registration defects found: none.

## 8. Outcome and direction

**Grades.** H1 (P_eff from the basis equals the engine value and the Coulomb-defined value within the R_p residual): **G3**, consistent within tolerance, shared-input. Contaminating-input line: `αℏc — measured via CODATA α (g-2 and atom-recoil chains) — enters at laws.hpp:461`; the Coulomb strength recovered at the hydrogen seat is CONSTRUCTION (the numerator of P_eff is that coupling), so the recovery is not a test. H2 (no measured length beyond the basis): consistent (1.2e-9), G3. H3 (Route C): consistent (6.1e-10), G3, the same construction through the Bohr relation (the routes share α and the a₀ relation; neither is independent of the other). H4 (f independent of R_CMB): **G1**, excluded: f ∝ 1/R_CMB by definition; R_CMB is an observed input; f carries it. H5 (lock integer consistent with the measured boundary): consistent (0.09σ), **G2** as a statement about P_eff because the integer is FLM07's open supplier, with P_eff shifting by −0.039% if the measured value is used. P_eff as a whole: a parameter-free function of {α, ℏ, c, m_p, m_e, W+1} with exponents (−1, −3, +5, +2, +2, −2); no fitted parameter; **G2** conditional on FLM07. G gate: **G2**, deferred.

**What changes for the dependents.**
- FLM03 and GOM02 take P_eff as a parameter-free function conditional on the lock integer. They take no confirmation of Coulomb's law from F_coulomb(r) at the hydrogen seat (CONSTRUCTION); independent content has to come from a regime where P_eff is not set by the seat (ionisation energies, the deuteron well).
- The engine labels (class C, "target-free", "measured R_p, k_e and e absent from the forward form") are consistent with this record as statements about symbols; the numerator is αℏc. Proposed (propose-only): a comment at `laws.hpp:454–461` stating that the Coulomb strength at the seat is recovered by construction from the numerator αℏc.
- f carries the observed R_CMB with exponent −1 (class B-conditioned in the engine, consistent).
- Edges: FLM07 → EMC01 `required`; EMC01 → FLM03, GOM02 `required`; EMC04 → EMC01 `cross-check` (the engine names an EMC04 electropause balance; EMC04 has no PROMPT and is not run here).

**Direction for the next layer of theory.**
1. A second force from P_eff and the registered radii, compared with a measurement not used to set P_eff: the Z-scaling of hydrogenic ionisation energies and the deuteron well (NP06/NP17); register before computing.
2. Remove R_CMB from f through the koppa closure ℓ_P² = ϟƛ (FLM06) so that f has no cosmological input; register the form first.
3. An independent boundary-radius datum (muonic spectroscopy, with a manifest row) to test the lock integer at the 1e-3 level; P_eff ∝ (W+1)⁻² makes the 0.04% shift visible only at that precision.
4. The movement sentence the prompt asks for: at fixed ℏ, c, m_p, m_e and W+1, P_eff ∝ 1/α, i.e. the interaction pressure scales inversely with the hydrogen ground-state gear v/c.

## 9. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
