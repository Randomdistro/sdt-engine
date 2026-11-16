# NP13 (Fe-56 against Ni-62, grammar efficiency) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `np13_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `NP13/PROMPT.md` in full (including the 2026-10-05 audit correction); the grammar in `CLAUDE.md` (one α core, n_t = A − 2Z, n_d = 3Z − A − 2); the NSEQ05 record of this programme (the AME2020 parse, with its flags); the first lines of `NUBASE2020.txt` and the header of the IAEA table. Not read: `NP13_VERDICT.md`, `np13_grammar_efficiency.cpp`. Exposure: the prompt states its own thresholds and an earlier sign-off ("FAIL on stated thesis; PASS on grammar audit") in the audit correction.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The data table's grammar (Fe-56 "5α + 6d + 6t (26p, 30n)", Ni-62 "5α + 6d + 9t (28p, 34n)") does not sum to the stated Z and N: 5α + 6d + 6t = 22p, 28n; 5α + 6d + 9t = 25p, 34n. Under the constitutional grammar (one α core plus n_d deuterons plus n_t tritons) Fe-56 is 20d + 4t (Z = 2 + 20 + 4 = 26, N = 2 + 20 + 8 = 30) and Ni-62 is 20d + 6t (Z = 28, N = 34). The triton fractions 50% and 60% become 16.7% and 23.1%, and the symmetry metric |n_d − n_t|/(n_d + n_t) becomes 0.667 (Fe-56) and 0.538 (Ni-62): **the ordering of the prompt's predicted symmetry reverses**. |
| D2 | premise | The metric is a function of (Z, N) alone: n_d − n_t = 3Z − 2N − 2 and n_d + n_t = Z − 2, so s = |3Z − 2N − 2|/(Z − 2), zero at N ≈ 1.5 Z. The grammar counts are an invertible map of (Z, N) (the grammar↔(Z,N) degeneracy), so a correlation of s with any nuclear observable is a correlation with the neutron excess and cannot be independent evidence of packing. Nuclei with s = 0 have N/Z ≈ 1.5, far above the valley of stability for Z > 10. |
| D3 | premise | "Fe-56 is more cosmically abundant than Ni-62" compares an elemental cosmic abundance (Fe/Ni by mass about 18) with an isotopic fraction (Ni-62 is 3.63% of nickel). The two are not like for like; neither follows from a packing symmetry without a production mechanism (the prompt gives none; stellar nucleosynthesis, where Ni-56 decays to Fe-56, is not in it). Solar elemental abundances are not in the local data (PENDING). |
| D4 | premise | "Does packing efficiency explain the maximum of B/A?" The prompt places the maximum at Fe-56; the measured maximum is at Ni-62 (the prompt's own table gives 8.790 and 8.795, and its question 1 says 8.790 and 8.794). The AME2020 values are computed here. |
| D5 | gating | The audit correction says "Gate B/A at ≤ 3.6% only". No native B/A model is given in the prompt, so a prediction error cannot be formed; the gate is OWED, with the requirement stated (a model of B/A from the grammar, e.g. the seat/shadow packing of NP17). |
| D6 | gating | Success criteria (abundance explained; correlation established; pattern extended to Z = 1–83) are not decidable as written; registered replacements below. |
| D7 | record | Nuclei with n_t < 0 or n_d < 0 (the neutron-poor ones, e.g. ³He) lie outside the constitutional grammar (they use the alternate electron-capture grammar); they are excluded from the correlation sets and counted. |
No downgrade is made on agreement grounds.

## 2. Registered quantities, validations, criteria (fixed before the run)
**Data.** AME2020 mass excess (experimental rows; parse as NSEQ05 amended: 3558 rows, 2550 experimental); B/A = [Z·ME(¹H) + N·ME(n) − ME(Z,N)]/A. NUBASE2020 ground states (isomer index 0) with an `IS=` value as the isotopic abundance (percent); elements with at least two such isotopes for the per-Z tests.
**T1 (the pair).** Under both grammars (the prompt's table and the constitutional one): (Z, N) reconstructed, n_d, n_t, triton fraction, s; AME2020 B/A for Fe-56 and Ni-62; NUBASE abundance of each within its element. The top five nuclides by B/A.
**T2.** s against the closed form |3Z − 2N − 2|/(Z − 2) for every grammar nuclide (identity); the zero line N = (3Z − 2)/2.
**T3 (extension to all elements).** For stable or naturally occurring isotopes with abundance, Z = 2…83 and inside the grammar (n_d, n_t ≥ 0): (a) Spearman rank correlation of s with abundance and of s with B/A; (b) for each element with ≥ 2 isotopes, whether the most abundant isotope has the smallest s (counted), against the chance count Σ 1/k_Z; (c) the same count for two trivial predictors, "most abundant = heaviest" and "= lightest", to show what s reduces to.
**T4 (magic numbers).** s*(Z) = s of the most abundant isotope of Z; rank of s*(Z) among Z−2…Z+2 for Z = 2, 8, 20, 28, 50, 82 (rank 1 = smallest s); chance 1/5 each.
**T5 (B/A gate).** OWED (D5).
**Validations.** V1: the AME parse counts (3558 rows; 2550 experimental) and the n, ¹H entries. V2: the computed B/A equals the file's own binding-energy-per-nucleon column to 0.01 keV for ²H, ⁴He, ⁵⁶Fe, ⁶²Ni, ²⁰⁸Pb. V3: the NUBASE abundances of each element sum to 100 ± 0.5 for every element with isotope entries; ¹H 99.9855, ²H 0.0145 read by key. V4: reconstruction: α + n_d·d + n_t·t reproduces (Z, N) for every grammar nuclide.
**Outcomes.** Verification rows: T1 (D1 reversal), T2. Decisions: T3(b): the most-abundant-isotope = most-symmetric reading is supported only if the count exceeds the chance count by more than two binomial standard deviations; T3(a): the correlation is reported with its sign and size (not a decision, D2); T4 reported.
**Expected landing (hand estimate).** The reversal of the symmetry order (0.667 against 0.538); Fe-56 abundance 91.75% of iron and Ni-62 3.63% of nickel; B/A 8790.4 and 8794.6 keV, with Ni-62 the maximum; T3(b): a count at or below chance because s falls toward the neutron-rich end of an element's isotopes while the most abundant isotope sits in the middle; T4 not estimated.

## 3. Results (COMPUTED; instrument `np13_reset_1.cpp`, output `np13_reset_1_results.txt`; single pass, no amendment, all validations met)
**Validations.** V1 met (3558 rows, 2550 experimental); V2 met (B/A against the file's column: worst 5×10⁻⁵ keV for ²H, ⁴He, ⁵⁶Fe, ⁶²Ni, ²⁰⁸Pb); V3 met (288 ground-state nuclides with `IS=` in 84 elements; ¹H 99.9855, ²H 0.0145; worst |sum − 100| = 0.012); V4 met.
**T1 (the pair).** The prompt's table gives, by its own multiplicities, Fe-56 → (Z, N) = (22, 28) against the stated (26, 30) and Ni-62 → (25, 34) against (28, 34): it does not sum. Constitutional grammar: **Fe-56 = α + 20d + 4t**, triton fraction 0.1667, **s = 0.6667**, B/A = 8790.356 keV, 91.754% of iron; **Ni-62 = α + 20d + 6t**, triton fraction 0.2308, **s = 0.5385**, B/A = 8794.556 keV, 3.6345% of nickel. The prompt's order of symmetry (Fe-56 s = 0, Ni-62 s = 0.2) reverses: by the registered metric Ni-62 is the more symmetric. Top five by B/A: Ni-62 8794.556, Fe-58 8792.253, **Fe-56 8790.356**, Ni-60 8780.777, Cr-54 8777.967: the maximum is Ni-62, third place is Fe-56.
**T2.** s = |3Z − 2N − 2|/(Z − 2) exactly (2378 grammar nuclides, difference 0); s = 0 at N = (3Z − 2)/2, N/Z → 1.5.
**T3.** 279 natural isotopes inside the grammar (one outside, with n_d or n_t < 0). Spearman(s, abundance) = **−0.085**; Spearman(s, B/A) = **+0.563** (the sign is opposite to the prompt's reasoning, and is the trend of s with N/Z and Z, D2). Elements with at least two isotopes: 58; **the most abundant isotope is the most symmetric in 13** against a chance count of 17.3 ± 3.3 (below chance by 1.3σ): **not supported**. For comparison the most abundant isotope is the heaviest in 17 elements and the lightest in 21.
**T4.** s* at the magic Z, rank among Z−2…Z+2: Z = 2 rank 1 (three window values only), Z = 8 rank 2, Z = 20 rank 5, Z = 28 rank 5, Z = 50 rank 2, Z = 82 rank 4 (four values): no pattern; the magic numbers are not symmetry minima.
**T5.** OWED (D5).
The expected landing held (order reversal, abundances, B/A with Ni-62 the maximum, T3(b) at or below chance).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Prompt data table (grammar of Fe-56 and Ni-62) | **VERIFICATION: inconsistent** | does not sum to the stated Z, N (D1); constitutional counts 20d + 4t and 20d + 6t |
| Thesis "Fe-56's grammar is more symmetric than Ni-62's" | **G1, excluded** | s = 0.667 (Fe-56) against 0.538 (Ni-62) under the constitutional grammar; the order reverses |
| "Fe-56 is at the maximum of B/A" | **VERIFICATION: false as stated** | the maximum is Ni-62 (8794.556 keV); Fe-56 is third (8790.356) |
| Symmetry explains abundance (T3) | **G1, excluded for "most abundant = most symmetric"** (13 against 17.3 ± 3.3); correlation with abundance −0.085 | s is a function of (Z, N) (D2): no independent evidence either way |
| Magic numbers as symmetry minima (T4) | **not supported** | ranks 1, 2, 5, 5, 2, 4 |
| B/A gate ≤ 3.6% (audit correction) | **OWED** | needs a native B/A model from the grammar |
| Cosmic abundance of Fe against Ni | **PENDING (data not local; elemental against isotopic, D3)** | production mechanism not in the prompt |

## 5. Direction
1. The prompt's thesis does not survive the constitutional grammar: it should be restated or closed. The grammar's symmetry axis is the neutron excess line N/Z ≈ 1.5, not the valley of stability.
2. A packing-efficiency account of the B/A maximum needs a B/A model built from the grammar (seat/shadow packing, NP17/NP35): the metric s cannot be that model.
3. Cosmic abundance of Fe against Ni needs the production chain (the decay of Ni-56 to Fe-56) and solar elemental abundances (PENDING).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.

## 7. Run 2 (2026-10-11): corrected prompt — registration (written before `np13_reset_2.cpp` exists)
**Instruction (Harvey, 2026-10-11):** fix the prompt and run again; failed data by input is not an error in the claim.
**What was fixed.** `PROMPT.md` data table and the two worked lines (struck through, not deleted): the grammar rows (now α + 20d + 4t and α + 20d + 6t), the triton fractions (16.7%, 23.1%), the B/A values (8.7904, 8.7946 MeV/n), the symmetry values (0.667, 0.538). The claim text is unchanged.
**Reclassification of Run 1 rows (input defect against claim result).**
| Run 1 row | Class now |
|---|---|
| D1 grammar table does not sum | **input defect, corrected**; not a result about the claim |
| D4 "the prompt places the B/A maximum at Fe-56" | **my misreading, withdrawn**: the target line says Ni-62 has the higher B/A; nothing to correct in the prompt; the row "false as stated" in §4 is withdrawn |
| "Thesis: Fe-56 more symmetric than Ni-62: G1 excluded" | **claim result**, computed from the constitutional counts (never from the faulty table); it is re-run on the corrected inputs |
| "most abundant = most symmetric: G1 excluded" | **claim result** (computed from Z and A for all isotopes) |
| Magic numbers as symmetry minima | **claim result** |
| D2 (s is a function of (Z, N)), D3 (elemental against isotopic abundance), D5 (B/A gate needs a native model) | **task-definition observations**, not data defects; unchanged |
**Run 2 content.** The same computations as Run 1 (T1–T4) with the corrected table now an input that is checked, not bypassed. New validation V5: the corrected table rows equal the grammar counts and the AME2020 values: (Z, N) from 1 + 20d + 4t and 1 + 20d + 6t equal (26, 30) and (28, 34); triton fractions 4/24 and 6/26; symmetry 16/24 and 14/26; B/A within 0.1 keV of 8790.356 and 8794.556. T1 no longer prints the old table. Gates, criteria and the B/A gate (OWED) unchanged.
**Expected landing.** Every number equal to Run 1 (the Run 1 instrument computed the grammar from Z and A and never consumed the faulty table); V5 met. The claim result stands as before: the registered symmetry metric ranks Ni-62 (0.538) as more symmetric than Fe-56 (0.667), so the prompt's prediction is not supported by that metric on correct inputs.

## 8. Run 2 results and the corrected grading (2026-10-11)
**Run 2** (`np13_reset_2.cpp`, output `np13_reset_2_results.txt`; single pass; V1–V5 met). T1–T5 are numerically identical to Run 1 (checked by diff of the printed results), as registered. V5 met: the corrected prompt table equals the grammar and AME2020.
**Corrected pair.** Fe-56 = α + 20d + 4t (triton fraction 16.7%, s = 0.667, B/A = 8790.356 keV, 91.754% of iron); Ni-62 = α + 20d + 6t (23.1%, s = 0.538, B/A = 8794.556 keV, 3.6345% of nickel). Top five by B/A: Ni-62, Fe-58, Fe-56, Ni-60, Cr-54.
**Grades, split as instructed (an input defect is not a claim result).**
| Item | Class | Grade |
|---|---|---|
| Prompt data table (grammar rows, triton fractions, B/A values, worked symmetry lines) | **input defect** | **corrected in `PROMPT.md` 2026-10-11**; V5 met; no claim grade |
| Row "Fe-56 at the B/A maximum, false as stated" (§4 of Run 1) | my misreading | **withdrawn**: the prompt's target says Ni-62 has the higher B/A, which the data confirm |
| Prediction "Fe-56's grammar is more symmetric (equal d and t count)" | **claim result, correct inputs** | **not supported (G1)**: n_d = 20 against n_t = 4 for Fe-56 (not equal); s(Fe-56) = 0.667 against s(Ni-62) = 0.538 |
| "Fe-56's abundance explained by grammar symmetry" | claim result | **not supported**: Spearman(s, abundance) = −0.085 over 279 isotopes |
| "Most abundant isotope at each Z is the most symmetric" | claim result | **not supported (G1)**: 13 of 58 elements against chance 17.3 ± 3.3 |
| "Magic numbers correspond to symmetry maxima" | claim result | **not supported**: ranks 1, 2, 5, 5, 2, 4 |
| "Pattern extended to all elements Z = 1–83" | task | done for the 279 grammar-valid natural isotopes (one outside the grammar); the pattern is absent |
| B/A gate (audit correction) | task definition | OWED: needs a native B/A model |
| Cosmic abundance of Fe against Ni | task definition | PENDING: elemental against isotopic fractions, production chain and solar abundances not local |
| s is a function of (Z, N) (zero at N/Z ≈ 1.5) | task-definition observation | stands: correlations with s are not independent evidence of packing |
The three success-criteria boxes of the prompt remain unchecked on the corrected inputs.

## 9. Direction (revised)
1. With the inputs corrected, the claim result is negative on every registered test; the metric s = |n_d − n_t|/(n_d + n_t) measures distance from the line N/Z ≈ 1.5 and ranks the stable-valley nuclei by their neutron excess.
2. If the author's intent is a different symmetry (for example balance of deuteron and triton seats within closed shells, the NSEQ05 pure-shell picture), it needs a stated definition and a registration; the present metric is what the prompt specifies.
3. Open: a native B/A model from the grammar (seat/shadow packing, NP17/NP35), and the Fe/Ni production chain with solar abundances.
