# APS10 (first ionisation from pressure), next round: the higher sequential ionisations, Z = 2–10 — assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `aps10_reset_2.cpp` exists. Follows the rewritten prompt of 2026-10-12 ("Next round 1: blind run on the higher sequential ionisations (Z = 2–10, all stages), with cascade bands and gates committed before the run").

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (state after the reset; next round; prohibitions); `APS10_RESET_ASSESSMENT_2026-10-10.md` (the opening gate and its validations); `aps10_reset_1.cpp` and its output (the first-ionisation run: median 1.48%, max 5.25%, 8/8 signs); `Engine/include/sdt/laws.hpp` `atomic::dodecardinal::solve_state(Z, N)` (energy_eV, force_residual, converged) and the canon note beside it. **Exposure (stated, not hidden):** the canon note in `laws.hpp` records that "APS14 COMPUTES … 45 unused higher ionisations (median 1.62%, max 8.63%)". I have read that note, so this run is **not blind to the engine's own claim**; it is an independent re-verification of that claim with an instrument written here, and the registered expectation below is that claim. Not read: `APS10_ASSESSMENT.md`, `aps10_results.txt`, `aps10_verify_ie1.cpp`, the APS14 assessment.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | counting | Z = 2–10, all stages: Σ Z = 54 ionisations, of which 9 are first ionisations (the opening set) and **45** are higher stages. 9 of the 45 are the last electron of a hydrogenic ion (stage s = Z), where the solver is exact by its own validation (E = −Z² Ry); 36 are many-electron stages. |
| D2 | construction | IE_s(Z) = E(Z, Z − s) − E(Z, Z − s + 1), with E(Z, N) = `solve_state(Z, N).energy_eV` and E(Z, 0) = 0 (the bare nucleus, registered). |
| D3 | anchor | Measured IE_s from `Datasets/nuclear/ionisation_energies.json` (the CRC/NIST compilation). The measured last-stage values contain relativistic and finite-size terms (z_last/Z² − 1 = 4×10⁻⁴ to 1.2×10⁻² for Z ≤ 29, NP24 record); the solver has none, so the nine hydrogenic stages carry a known systematic of order (Zα)² (up to 0.5% at Z = 10). |
| D4 | shared input | The solver's coefficient forms were isolated against the first ionisations. The higher stages are therefore not part of the isolation (the registered sense of "blind"), but the measured ladder is not independent of the first ionisations in origin of data (same table). |
| D5 | extension | Z > 10 needs the solver's domain extended; not attempted (the prompt: register the extension rule first). |
No downgrade is made on agreement grounds.

## 2. Registered gates and quantities (fixed before the run)
**Validation.** The two APS10 validations: solve_state(1,1) = −Ry and solve_state(2,1) = −4 Ry to 1e-6 relative, converged; every state used converged with force residual < 1e-8 (a state that does not converge is excluded and counted, not replaced).
**Quantities.** For each (Z, s), Z = 2–10, s = 1…Z: predicted and measured IE_s (eV), relative error. Sets: all 54; the 9 first ionisations (must reproduce the opening run: median 1.48%, max 5.25%); the 45 higher stages; the 36 many-electron higher stages; the 9 hydrogenic stages.
**Gates (committed now; the opening gate carried over).** Opening: median |error| ≤ 15% and max ≤ 40% on the 45 higher stages. Monotone: within each element the predicted IE_s increases with s as the measured does (all consecutive pairs). Destination (reported, not gated): median ≤ 5% and max ≤ 15% (the suite's 5% destination, widened for the max). Cascade bands: G4 (COMPUTED, good) if opening met and destination met; G3 if opening met and destination not met; G1 (excluded in range) if the opening median exceeds 15%.
**Label ceiling.** COMPUTED (native solver, no wavefunction; coefficient forms isolated against IE1). Not DERIVED.
**Expected landing (the engine note's claim, plus a hand estimate for the hydrogenic stages).** Higher stages: median 1.6%, max 8.6%; hydrogenic stages within 0.5% of the measured (the (Zα)² gap); all monotone; G4.

## 3. Results (COMPUTED, re-verification; `aps10_reset_2.cpp`, output `aps10_reset_2_results.txt`; single pass, no amendment)
**Validation met** (solve_state(1,1) = −13.605693 eV = −Ry; solve_state(2,1) = −54.422772 eV = −4 Ry); all 54 states converged, max force residual 3.23×10⁻⁹ (gate 10⁻⁸).
**First ionisations (opening set):** median 1.48%, max 5.25% — identical to the opening run.
**The 45 higher stages: median 1.62%, max 8.63%** (Be⁺, s = 2). Many-electron 36: median 1.86%, max 8.63%. Hydrogenic last stages (9): median 0.04%, max 0.12%. **Monotone: 45 of 45** predicted orderings equal the measured. Opening gate (median ≤ 15%, max ≤ 40%): **MET**. Destination (median ≤ 5%, max ≤ 15%): **reached**. Cascade band **G4 (COMPUTED, good)**.
**Pattern in the errors (descriptive, not gated).** The large negative errors (−5% to −8.6%) sit at the stages that remove the first electron of the 2s/2p shell after the n = 2 shell is partly stripped: Be⁺ −8.63, B⁺ −7.46, B²⁺ −8.18, C²⁺ −7.24, C³⁺ −7.36, N³⁺ −6.69, N⁴⁺ −6.61, O⁴⁺ −6.13, O⁵⁺ −5.98, F⁵⁺ −5.63, F⁶⁺ −5.46, Ne⁶⁺ −5.21, Ne⁷⁺ −5.02; the stage that opens the n = 1 shell (s = Z − 1) is over-predicted by +1.1 to +3.2% (Li +3.15, Be +2.48, B +2.02, C +1.69, N +1.45, O +1.26, F +1.09, Ne +0.96). The residual therefore follows the shell structure of the construction (a rung-dependent under-binding of the last n = 2 electrons), not a smooth drift in Z: where the construction's coefficients were isolated (first ionisations) the errors are 0.2–5%, and the same family of forms continues at the same size one shell down.
Landing: the engine note's claim (median 1.62%, max 8.63%) is **reproduced exactly** by the instrument written here, which was not derived from the note's code. The hydrogenic stages are within 0.12%, smaller than my hand estimate of up to 0.5% (the measured last-stage excess over Z² is 1.2×10⁻³ at Z = 10, not 5×10⁻³; D3 over-stated it).

## 4. Grades
| Item | Grade |
|---|---|
| 45 higher sequential ionisations Z = 2–10 | **COMPUTED, G4** (median 1.62%, max 8.63%; monotone 45/45) |
| Blindness | **not blind to the engine's own note** (exposure stated); an independent re-verification; the forms were isolated against IE1 only |
| Hydrogenic stages | median 0.04%, max 0.12% (validation-level; the solver is exact for one-electron ions by construction, so not evidence) |
| Label ceiling | **COMPUTED; not DERIVED** |
| Extension past Z = 10 | **not attempted** (extension rule to be registered first) |

## 5. Direction
1. The 45 higher stages are not independent evidence beyond the isolation set only in the sense that the measured table is shared; for a truly held-out test the solver's domain needs Z > 10 with the extension rule registered before any value is loaded.
2. CH09 (atomic radius) is to use the same outer-seat ladder, registered together with this one (prompt §2): the stage-resolved error pattern above is the natural co-registered observable for the radius.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
