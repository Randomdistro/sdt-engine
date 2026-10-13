# NP08 (triple-alpha from geometric packing) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `np08_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `NP08/PROMPT.md` in full (run 1, the run-2 specification and the audit correction); `CLAUDE.md` (the grammar); the NP10, NP13, NSEQ02 and NSEQ05 records of this programme. Not read: `NP08_VERDICT.md`, `RUN_LOG.md`, `np08_results.txt`, `np08_triple_alpha.cpp`, and (by the blank-slate protocol) every prior verdict that the run-2 Phase 0 lists. Exposure: the run-2 prompt states earlier numbers (a 6.327 MeV repulsion ledger, the d/t/α lock ladder −1.1%/+0.9%/−5.6%, an NP08 premise correction that Be-8 is α + 2d) and the required-lock rows 5.948 MeV.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | Run 1 states Be-8 = 2α + 0d. The constitutional grammar gives every nucleus with Z ≥ 2 a unique decomposition: Be-8 (Z = 4, A = 8): n_t = 0, n_d = 3·4 − 8 − 2 = 2, so **α + 2d**. "2α" is not a grammar state; the instability of Be-8 cannot be explained by "two standalone alphas with no scaffold bonds". The run-2 prompt and the audit correction already say this. |
| D2 | premise | The energy accounting in run 1 and run 2 is "bonds − Coulomb repulsion" with a point-Coulomb ledger (6.327 MeV) and a "lock" magnitude subtracted from it. A repulsion ledger of point charges is an imported electrostatic source model (the 2026-10-07 ruling on NP14: no attractive law, no imported source model; binding = mass defect, excess = obstruction). The vocabulary of the ledger uses the charge noun (prohibited). The ledger is not run. |
| D3 | gating | Run 2, Phase 0, instructs the executor to read prior verdicts and result files (NP08 run 1, NP10 run 2, NP17, the sequencer). In a blank-slate programme these are archived; their content cannot enter the registration. Phase B is in any case blocked by the prompt on a derived lock (NP10, FLM14, NP17). In this programme NP10 is recorded: the lock is not a scarce angular resource shared among partners; the cooperative (closed-loop) alternative is open. |
| D4 | gating | The audit correction gates the Hoyle-state offset above the 3α threshold at ≤ 5%. That offset is a small difference of two large numbers: 7.654 − 7.275 = 0.379 MeV (a 5.2% error in the 7.654 MeV state is 0.40 MeV, i.e. 105% of the offset). The 20% gate on 7.654 MeV (run 1) therefore admits predictions that miss the offset entirely; the 5% gate on 0.379 MeV is the real constraint, and the Be-8 margin (0.092 MeV) is a difference of two ~28 MeV ledgers. |
| D5 | gating | What can be fixed today, before any lock derivation exists, is the target row from measured masses: the 3α Q-value, the Be-8 unbound margin, the Hoyle offset, and the ¹²C(α,γ)¹⁶O Q-value (for the run-2 Phase C sign check). Registered below so that a later derivation cannot be steered toward them. |
| D6 | record | The Hoyle excitation energy 7.654 MeV is an excited-level energy (external, OBSERVED, from the evaluated level scheme); the local mass files carry ground states only. It is typed, labelled, and used only in the offset. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Run.** From AME2020 (experimental rows; parse as NSEQ05 amended, V gated on 3558/2550): Q(3α) = 3 ME(⁴He) − ME(¹²C) (keV); the Be-8 margin Δ(Be-8) = ME(⁸Be) − 2 ME(⁴He) (keV, positive means unbound); the Hoyle offset E_H − Q(3α) with E_H = 7654.2 keV (OBSERVED, typed); the offset as a fraction of E_H; the ⁴He + ¹²C → ¹⁶O Q-value; the grammar of ⁸Be, ¹²C, ¹⁶O, ⁹Be (constitutional). The allowed tolerance for a later derivation, from the audit correction: the Hoyle offset within 5% means ±19 keV; the Be-8 margin in the run-2 ±50% gate means ±46 keV; the error on E_H itself that the 20% run-1 gate allows (±1.53 MeV) compared with the offset.
**Validations.** V1: AME parse (3558 rows, 2550 experimental; ¹H and neutron rows). V2: the prompt's mass table recomputed: 3 × 4.002603 u = 12.007809 u and Q = 7.275 MeV from the AME mass excesses to 0.5 keV. V3: grammar reconstruction of (Z, N).
**Outcome form.** Verification rows and the target row (COMPUTED, measured anchors). The physics criteria (Hoyle offset within 5% from a lock derivation; Be-8 margin; the O-16 sign check) are OWED: the lock derivation is blocked (D3) and the Coulomb ledger is not run (D2).
**Expected landing (hand estimate).** Q(3α) = 7274.7 keV; Be-8 margin +91.84 keV; Hoyle offset +379.5 keV (about 5.0% of E_H); Q(α + ¹²C → ¹⁶O) = 7161.9 keV; 5% of the offset = 19 keV.

## 3. Results (COMPUTED; instrument `np08_reset_1.cpp`, output `np08_reset_1_results.txt`; single pass, no amendment; validations met)
**Validations.** V1 met (3558 rows, 2550 experimental); V2 met (3 × 4.002603 u = 12.007809 u; Q(3α) = 7274.7476 keV against the table's 7.275 MeV, −0.25 keV); V3 met.
**Grammar (constitutional).** He-4 = α; **Be-8 = α + 2d**; Be-9 = α + d + t; **C-12 = α + 4d**; **O-16 = α + 6d**.
**Target row (measured anchors).** ME(⁴He) = 2424.915870 keV; ME(¹²C) = 0 (definition); ME(⁸Be) = 4941.672000 keV; ME(¹⁶O) = −4737.002170 keV. **Q(3α → ¹²C) = 7274.7476 keV. Be-8 margin ME(⁸Be) − 2 ME(⁴He) = +91.8403 keV (unbound). Hoyle offset E_H − Q(3α) = 379.4524 keV** with E_H = 7654.2 keV (OBSERVED, typed): 4.96% of E_H. **Q(⁴He + ¹²C → ¹⁶O) = 7161.9180 keV.**
**Tolerances implied for a later derivation.** 5% of the Hoyle offset (audit correction) = 19.0 keV; the run-1 20% gate on E_H = 1531 keV = 4.0 times the offset; 50% of the Be-8 margin = 45.9 keV; a fractional error of E_H equal to 4.96% already equals the whole offset.
**Not run:** the point-Coulomb repulsion ledger (imported source model, D2); the lock derivation (blocked, D3); the alignment-cost computation (needs the lock).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Premise "Be-8 = 2α + 0d is unbonded" | **VERIFICATION: contradicts the grammar** | Be-8 = α + 2d (D1) |
| C-12 = α + 4d; O-16 = α + 6d | **VERIFICATION, met** | constitutional counts |
| Target row (Q(3α), Be-8 margin, Hoyle offset, Q(α + ¹²C)) | **COMPUTED, measured anchors; on the record before any lock derivation** | AME2020 differences; E_H typed OBSERVED |
| Run-1 gate "Hoyle energy within 20% of 7.654 MeV" | **not a discriminating gate** | 20% = 1531 keV = 4× the offset (D4) |
| Audit-corrected gate (offset within 5%) | **OWED** | needs a derived lock (blocked) |
| Hoyle state "derived from tetrahedral closure packing energy" | **OWED / not supported** | no energy model that avoids the imported repulsion ledger; NP10 (this programme): the lock is cooperative and unspecified |
| Be-8 margin (0.092 MeV), O-16 sign check | **OWED** | same dependency |

## 5. Direction
1. State the native mechanism for why α + 2d lies 91.84 keV above two separated α-clusters while α + 4d lies 7274.75 keV below three, before any energy ledger: the grammar gives both as unique decompositions, so the question is what makes the ground state of A = 8 a near-threshold resonance (a difference of two nearly equal costs) and the ground state of A = 12 deep.
2. Gate the Hoyle offset (379.45 keV, ±19 keV) and the Be-8 margin (91.84 keV, ±46 keV) together, from one rule with no per-nucleus constants; the 20% gate on 7.654 MeV should be retired.
3. Dependencies: NP10 (the lock), FLM14 and NP17 (the tour-energy law), none of them recorded blind in this programme yet.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
