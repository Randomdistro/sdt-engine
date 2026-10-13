# NP07 (primordial lithium resolution) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `np07_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `NP07/PROMPT.md` (data table, investigation prompt, success criteria; the pivot table and the audit correction were not read in full); `CLAUDE.md` (the grammar, n_t = A − 2Z, n_d = 3Z − A − 2; the alternate electron-capture grammar n_t = A − 2Z + 1, n_d = 3Z − A − 3 with a He-3 core); the NP13 record of this programme. External, verified by search on 2026-10-10: Khatri and Sunyaev, arXiv:1009.3932 (the primordial lithium abundance is the sum of Li-7 and Be-7 produced in BBN; Be-7 converts to Li-7 by electron capture only after recombination, well after BBN; the hydrogenic Be-7 half-life is quoted as 106.4 d). Not read: `RUN_LOG.md`, `np07_results.txt`. Exposure: the prompt states the "lithium problem" factor (about 3×).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The central mechanism (fully ionised Be-7 cannot capture an electron, so its decay waits for recombination and Be-7 is destroyed by p + Be-7 in the meantime) is already part of the standard treatment: Be-7 survives until it recombines, and the primordial Li-7 abundance is the sum Li-7 + Be-7. The electron-capture timing cannot change that sum (EC conserves A = 7). The prompt's reasoning that a delay lets p + Be-7 → B-8 destroy Be-7 is a statement about the BBN rate network, which the standard calculation already contains; it is not a new SDT consequence. The literature points the other way: conversion early enough would let the more fragile Li-7 be destroyed by protons. |
| D2 | premise | The calculation requested (the temperature of Be-7 recombination; Be-7 destroyed between t_BBN and t_recombine; the surviving Li-7/H) needs a big-bang cosmology (an expansion history, a baryon-to-photon ratio from the CMB analysis, a reaction network with rates). All three are imported frames; SDT's own cosmology has no expansion and no stated network. Not runnable natively; OWED. |
| D3 | premise | The grammar table is inconsistent (as in NP13): "Li-7 = α + d + t (3 blocks, 1 triton)" is 4 + 2 + 3 = 9 nucleons, not 7; "Be-7 = α + d" is 6 nucleons. Constitutional grammar: Li-7 (Z = 3, A = 7): n_t = 1, n_d = 0, so α + t; Li-6: n_t = 0, n_d = 1, so α + d; Be-7 (Z = 4, A = 7): n_t = −1 (outside the grammar), alternate EC grammar He-3 core + 2d (3 + 4 = 7; Z = 2 + 2 = 4). The stated EC transition "Δn_tri = +2, Δn_deu = −3" does not follow: Be-7 → Li-7 is He-3 + 2d → α + t, a change of core and of the block counts that this arithmetic does not reproduce. |
| D4 | premise | "EC rates depend on charge state" (the prompt cites INVESTIGATION_11): the SDT vocabulary rules exclude the word; the physical point (the number of K electrons available) is counted as electrons: neutral Be-7 has two 1s electrons, the hydrogenic ion one, so the capture rate halves. This is checkable: 2 × 53.22 d = 106.44 d against the literature 106.4 d. |
| D5 | gating | Success criteria (the delay quantified; Li-7/H computed; ratio drops from 4.68 to ~1.6×10⁻¹⁰) cannot be decided without D2. The "~1.6" is the observed value used as the target (target-first). |
| D6 | record | The required reduction is a fixed number: 4.68 → 1.58 is a factor 2.96 (a 66% loss of the A = 7 total), with the relative uncertainty 24% from the two quoted errors. Any proposed mechanism must remove that fraction of the total or leave it. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Run.** (a) The grammar of Li-6, Li-7, Be-7 under the constitutional grammar and the alternate EC grammar (counts, reconstructed (Z, N), validity). (b) The required reduction: R = 4.68/1.58, its relative uncertainty by quadrature of the quoted errors (0.67/4.68, 0.31/1.58), the loss fraction 1 − 1/R, log₁₀R. (c) The K-electron count arithmetic: 2 × 53.22 d against 106.4 d (relative difference). (d) The conservation statement: EC changes (Z, N) = (4, 3) → (3, 4) with A = 7 fixed: A-sum unchanged (arithmetic). (e) What a mechanism must do: the A = 7 total at the end of BBN is fixed by the BBN network; an EC delay changes only the split between Be-7 and Li-7, not the sum.
**Validations.** V1: the grammar reconstruction of (Z, N) from the block counts for every grammar-valid nuclide in the table. V2: 2 × half-life ratio check against the literature value to 0.1%.
**Outcome form.** Verification rows only; the physics criteria are OWED (D2), with the named requirements: an SDT-native production and destruction chain for the A = 7 total, with no imported expansion history or network.
**Expected landing.** Li-7 = α + t; Be-7 outside the standard grammar; R = 2.96 (loss 66%); 2 × 53.22 = 106.44 d against 106.4 d (0.04%).

## 3. Results (COMPUTED; instrument `np07_reset_1.cpp`, output `np07_reset_1_results.txt`; single pass, no amendment; validations met)
**Grammar.** Li-6: n_t = 0, n_d = 1 (α + d). Li-7: n_t = 1, n_d = 0 (α + t). Be-7: n_t = −1, n_d = 3: outside the constitutional grammar; alternate EC grammar n_t = 0, n_d = 2 (He-3 + 2d: 3 + 4 = 7 nucleons, Z = 2 + 2 = 4). The prompt's table (Li-7 = α + d + t, 9 nucleons; Be-7 = α + d, 6 nucleons) does not sum to A = 7. V1 met.
**Required reduction.** 4.68 ± 0.67 against 1.58 ± 0.31 (×10⁻¹⁰): R = 2.962 (± 24%), a loss of 66.2% of the A = 7 total (log₁₀R = 0.472).
**K electrons (V2).** 2 × 53.22 d = 106.44 d against the literature 106.4 d: 3.8×10⁻⁴ (met).
**Conservation.** Be-7 (Z, N) = (4, 3) → Li-7 (3, 4): A = 7 → 7. The A = 7 total is unchanged by when the capture happens.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Premise: "EC delay until recombination" as a new SDT consequence | **VERIFICATION: already in the standard treatment** | primordial Li-7 = Li-7 + Be-7; EC timing conserves the sum (D1) |
| Direction of the proposed effect | **G1, excluded as stated** | a delay does not reduce the A = 7 total; the literature's own statement is that earlier conversion into the more fragile Li-7 would (inference from the sources, flagged) |
| Grammar table | **VERIFICATION: inconsistent** | does not sum (D3); the stated EC transition counts do not follow |
| K-electron count (rate halves for the hydrogenic ion) | **VERIFICATION, met** | 106.44 d against 106.4 d |
| Calculation (recombination temperature, destruction, Li-7/H) | **OWED** | needs an expansion history, a baryon-to-photon ratio and a reaction network, all imported; no SDT-native chain exists (D2) |
| "Lithium problem resolved" | **not supported** | the quantity a mechanism must change is the A = 7 total at BBN by a factor 2.96 |

## 5. Direction
1. A native account must produce or destroy A = 7 at the formation epoch, not time the Be-7 → Li-7 capture. What the grammar offers: Be-7 sits in the alternate EC grammar (He-3 core), Li-7 in the constitutional one (α + t), and the capture changes the core; whether that transition has a cost bearing on destruction is open.
2. The native version of the question does not use an expansion history. The requirements to name: a native formation chain for light nuclei in the CMB-relay picture, with the observed Li/H (1.58 ± 0.31 ×10⁻¹⁰, a measured abundance) as a final comparison only.
3. The vocabulary rule (D4) applies to the prompt's "charge state": count K electrons.

Sources for the external statements (search 2026-10-10): arXiv 1009.3932 (Khatri and Sunyaev, Be-7 conversion time).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
