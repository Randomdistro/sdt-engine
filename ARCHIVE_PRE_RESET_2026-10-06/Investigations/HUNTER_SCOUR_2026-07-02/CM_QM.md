# HUNTER SCOUR — Condensed Matter (CM01–07) + Quantum Foundations (QM01–07)

> Region: `Investigations/12_Condensed_Matter_Physics/` + `Investigations/13_Quantum_Foundations_and_Measurement/`.
> Auditor: HUNTER at maximum pressure, 2026-07-02, under `HUNTER_PROTOCOL.md`. Assume fabrication until disproven.
> Scope: 14 investigations. **Only 3 have executed content** (CM02, QM06, QM01); the other 11 are unexecuted
> `PROMPT.md` specs (Status: SPEC) with no results, no verdicts — nothing to fabricate, nothing claimed as achieved.

## Execution record (all runnable artifacts were COMPILED + RUN this audit)

| Artifact | Build | Run | stdout vs committed `results.txt` |
|---|---|---|---|
| `cm02_ohms_law.cpp` (MSVC cl /std:c++20 /O2) | **BUILD_EXIT=0** | RUN_EXIT=0 | **byte-match** (σ=5.988e7, 0.47%, PASS) |
| `qm06_discrete_spectra.cpp` (MSVC) | **BUILD_EXIT=0** | RUN_EXIT=0 | **byte-match** (E₁ err 0.00e+00; Hα 656.1123 nm, 0.025%; closure 1.000000) |
| `qm01_bell_local_vs_throughpole.py` (py 3.13) | — | ran | matches memo (LOCAL S=2.0000, THROUGHPOLE S=2.8284) |

Unlike APS04 (which never compiled), **CM02 and QM06 genuinely build and run, and their committed numbers reproduce
exactly.** The faults are therefore NOT execution-fabrication — they are structural (circular / identity) faults in
what the tool *computes*. Both already self-flagged ⚠️ SUPERSEDED (self-caught, recorded not re-charged).

---

## Fault table

| ID | Status line | Grade | Fault (evidence) |
|---|---|---|---|
| **CM02** | Ohm/Drude — builds+runs, PASS reproduces | **CIRCULAR** (self-flagged ⚠️ SUPERSEDED) | `TAU_CU = 2.5e-14` is hard-coded, source-commented `// mean collision time [s] (from measured sigma)` and printed `[OBSERVED via sigma]`. Then `sigma = N_CU*e*e*TAU_CU/me` "predicts" σ=5.988e7 vs meas 5.96e7 (0.47% PASS). This is τ-from-σ → σ-from-τ: the exact CIRCULARITY the kill-list names. The "native occlusion mean-free-path" that would make τ independent is admitted OPEN in the tool's own verdict. |
| **QM06** | Discrete spectra — builds+runs, PASS reproduces | **IDENTITY-PASS** (self-flagged ⚠️ SUPERSEDED) | `E_1 vs Ry: 0.00e+00 rel err` — literally zero because `atomic::ionisation_energy_eV(1,1)` ≡ `Ry_eV` by definition (laws.hpp:884). Hα "prediction" calls `atomic::rydberg_energy_eV` = textbook `Ry·Z²·(1/n₁²−1/n₂²)` (laws.hpp:877) seeded with `measured::Ry_eV`. The 0.025% Hα residual is CODATA-rounding of Ry_eV, not an SDT mechanism. Closure `2πr₁/λ₁ = 1.000000` is a de-Broglie/Bohr tautology (both defined so it closes). No wavefunction imported, but the Rydberg scale is re-exposed, not derived. |
| **QM01** | Bell CHSH memo — runs, honest | **OPEN (no fault)** | `E_tp = cos(2(x−y))` is the QM/Malus law written by hand, so "THROUGHPOLE = QM exactly" is true *by construction*. **But the memo says so, in bold:** "Model (2) does not derive 2.828 — it assumes... yields QM by construction... Claiming this 'reproduces QM entanglement' would be the dishonest read." The LOCAL Monte-Carlo (N=3e6) genuinely computes S=2.0000 (a real hidden-variable sim, not plugged). Correctly self-graded OPEN; localises the non-locality debt to 0.828. No home-team pass needed — this one is clean. |
| **CM01** | Superconductivity — SPEC only | — | No tool/results/verdict. Mechanism (phase-locked vortex pairs, Φ₀=h/2e) is *proposed*, not claimed achieved. Nothing to fault; nothing earned. |
| **CM03** | Band structure — SPEC only | — | Unexecuted spec. |
| **CM04** | Crystal/phonons — SPEC only | — | Unexecuted spec. |
| **CM05** | Superfluidity/BEC — SPEC only | — | Unexecuted spec; no mechanism realised, no re-statement passed as result. |
| **CM06** | Quantum Hall / Josephson — SPEC only | — | **Answers the mandate's R_K question:** R_K=h/e² is **NOT derived** anywhere — it is the *target* the spec asks to reproduce as an integer edge-channel count, explicitly not yet done. The prompt itself forbids IDENTITY-PASS and importing a Chern number. (Note: the *lone* place R_K currently appears computed is CM02's `R_K=h/e²=25812.807` line — tagged `[OBSERVED]`, honest, not a claim.) Honest OPEN. |
| **CM07** | Ferromagnetism — SPEC only | — | Unexecuted spec. |
| **QM02** | Uncertainty/relay-bandwidth — SPEC only | — | Unexecuted spec. |
| **QM03** | Tunnelling — SPEC only | — | Unexecuted spec. |
| **QM04** | Born rule — SPEC only | — | **Answers the mandate's |ψ|² question:** nothing produced yet, so no |ψ|² or Rydberg re-exposure *has* occurred. The risk is real *if executed* (residence-density → Born can smuggle |ψ|²), but no fault exists to charge today. Honest SPEC. |
| **QM05** | Bell/EPR/throughpole — SPEC only | — | Unexecuted spec (the concrete Bell work lives under QM01's folder). |
| **QM07** | Spin/Stern-Gerlach — SPEC only | — | Unexecuted spec. |

---

## Confirmations demanded by the mandate

- **CM02 CIRCULARITY — CONFIRMED.** τ hard-coded from measured σ, then σ recovered. Already ⚠️ SUPERSEDED (2026-06-29). Self-caught.
- **QM06 IDENTITY-PASS — CONFIRMED.** Wraps `atomic::` Rydberg; E₁ error is a definitional 0.00e+00; Hα 0.025% is a re-exposure. Already ⚠️ SUPERSEDED. Self-caught.
- **QM04 / QM06 re-expose |ψ|²/Rydberg?** QM06 re-exposes the **Rydberg scale** (yes, that is its whole fault). QM04 is unexecuted → no |ψ|² imported yet. Neither imports a wavefunction as a primitive; QM06's sin is scale re-exposure, not ψ-import.
- **CM06 R_K DERIVED or OBSERVED?** **Neither derived nor even attempted** — CM06 is an unexecuted spec; R_K=h/e² is its target. The only computed instance (CM02) is tagged `[OBSERVED]`. No false "DERIVED" claim anywhere.
- **CM01/CM05 mechanism or re-statement?** **Neither** — both are unexecuted specs. No mechanism realised, so no re-statement could be smuggled as a result.

## Minor note (not a fault)
- For both CM02 and QM06 the `.cpp` mtime (2026-06-27 17:08) is ~5 h **after** the committed `results.txt` (12:24). Since a fresh build reproduces the committed output byte-for-byte, the later edit was cosmetic (labels/comments) and the numbers are not stale. Recorded for completeness.

## Verdict line
> **Region completion A** (all runnable tools built + run; all 14 investigations characterised) ·
> **Physics class:** CM02 = CIRCULAR (self-flagged), QM06 = IDENTITY-PASS (self-flagged), QM01 = OPEN (honest, clean),
> remaining 11 = SPEC/unexecuted (no claim) · **Recovery:** the *ideas* survive as OPEN (native occlusion-MFP for τ;
> native standing-wake derivation of the Rydberg scale; native throughpole projection for Bell) — only the two fake
> PASSes are retracted, and both were **already retracted** by the ⚠️ SUPERSEDED flags · **Cascade root:** none new;
> the two structural faults share the generic root "a native scale/quantity (τ, Ry) was not built, so a measured/
> engine value was re-exposed in its place."

— HUNTER · CM_QM scour · 2026-07-02
