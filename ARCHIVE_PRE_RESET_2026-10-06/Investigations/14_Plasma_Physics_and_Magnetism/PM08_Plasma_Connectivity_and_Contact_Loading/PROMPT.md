# PM08 — Plasma connectivity and contact loading (child B of SDT_Loading_EC_Reseating_Neutrino_Coupling)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, opened 2026-10-05. Id and placement proposed. Gateways binding; direct execution only.
> **Parent:** `Investigations/SDT_Loading_EC_Reseating_Neutrino_Coupling/` (Phase 2). **Depends on child A (APS15) as COMPUTED.**

## ⓪ Five questions
1. **What don't we know?** A native definition of collective electron connectivity and plasma pressure, and a rule that turns it into a contact loading on a nuclear seat (ledger D48, OPEN).
2. **Why does it matter?** It is the entry of the whole loading chain: without it, no later phase has an input that varies with environment.
3. **How will we find out?** Phase 1 builds the definition from existing PM01–PM07 objects (circulation count, Debye length, wake interaction) with no new constant; Phase 2 tests it on cases with known answers; Phase 3 evaluates a loading law only if Phase 2 closes.
4. **What would prove us wrong?** (a) The definition needs an inserted coefficient to reproduce the Debye length to 5%; (b) the connectivity of a uniform neutral plasma differs from the PM04 plasma frequency relation by more than 1e-6 relative in a closed-domain test; (c) two equivalent constructions of the same connectivity disagree by more than 1e-10 normalised.
5. **How will we know we're done?** Assessment gives prompt completion (A–D) and physics class (NATIVE / CONVERGENCE / OPEN); a defined connectivity with passing known-answer tests is A and NATIVE or CONVERGENCE; any inserted coefficient is CALIBRATED and documented.

## 1. Executive summary
Question: what is "collective electron connectivity" in SDT terms, and what pressure on a nuclear seat does it exert? Closes the Phase 2 gap of the parent. Expected outcome: a stated definition with test results, or a dated record that PM01–PM07 cannot supply one.

## 2. Physical context
Free electrons around a nucleus have no engine definition of connectivity (graph of wake overlaps between electrons) or of a plasma pressure acting on seats. PM01–PM07 give vortex circulation, induction, plasma oscillation and Debye shielding, reconnection, and MHD orphans. PM04's P2c PASS does not reproduce under g++ (commit d814fb6): any use of PM04 numbers must be re-run on the toolchain in use.

## 3. Theoretical framework
Inputs only from `laws.hpp`. No fields as primitives (Prohibitions). The occlusion channel weights in `occlusion.hpp` are a frozen construction (D49) and are carried as such. Connectivity is to be defined as a count or graph quantity of wake contacts, not as a field.

## 4. Investigation strategy
- **P0:** re-run PM04 on the current toolchain and record which PM04 gates reproduce; restate PM01–PM07 statuses from their own files.
- **P1:** write the definition of connectivity and plasma pressure as formulas in terms of existing quantities; state every symbol and dimension; list inputs.
- **P2 (known answers):** (i) Debye length and plasma frequency of a uniform plasma; (ii) the connectivity of an isolated electron is zero; (iii) connectivity is symmetric under relabelling; (iv) closed-domain conservation 1e-6, decreasing under refinement.
- **P3:** a loading law (pressure on a seat as a function of connectivity) only if P2 closes; otherwise record OPEN.
- Whole range, single pass; no retro-selection of cases.

## 5. Success criteria
P2 known answers reproduce to the tolerances in ⓪.4; no inserted coefficient; P3 produces a dimensionally consistent loading with its inputs tabulated.

## 6. Outputs
`RUN_LOG.md`, `PM08_ASSESSMENT.md`, results files, tool source, dependency table (below) updated.

## 7. Dependencies (from `DEPENDENCY_LEDGER_v2.csv`)
| Row | Item | Recorded status |
|---|---|---|
| U34 | PM01 circulation | NATIVE (P1); rest not re-extracted |
| U35 | PM02 induction | NATIVE (P1) |
| U36 | PM03 EM waves | CLASS C; verdict file marked do-not-trust |
| U37 | PM04 plasma oscillations | mixed; toolchain-dependent PASS |
| U38 | PM05 reconnection | class not re-extracted |
| U39 | PM06 cyclotron | class not re-extracted |
| U40 | PM07 MHD | OPEN (named orphans) |
| D48 | collective connectivity | OPEN |
| D49 | occlusion weights | CONSTRUCTION |
| D52 | solver qualification | stale |

## 8. Falsification tests
Triggers in ⓪.4; each has a numeric threshold fixed here.

## 9. Implementation notes
C++20, `#include <sdt/laws.hpp>`; standalone compile with `cl /std:c++20 /EHsc /O2 /I Engine/include`. Constants from `laws.hpp` only.

## ⑩ Adaptive execution
**Pre-run commitment:** completion target A; physics class hoped CONVERGENCE; CALIBRATED budget 0; thresholds as ⓪.4; forbidden: widening tolerances, redefining connectivity after seeing results, inserting a plasma coefficient.
| Trigger | First response | If pivot fails | Forbidden |
|---|---|---|---|
| (a) Debye length off > 5% | alternative native definition from PM01 circulation count | record OPEN | fit a coefficient |
| (b) uniform plasma off > 1e-6 | check discretisation, refine twice | record non-closure | loosen tolerance |
| (c) equivalent constructions disagree | locate the construction bug, record both | OPEN | choose the agreeing one silently |
Failures get an in-depth assessment and a dated next round (hypothesise, experiment, assess).
