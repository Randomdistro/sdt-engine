# NP40 — EC accessibility and capture clock: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`
- `CLAUDE.md` (the EC grammar)
- the NUBASE2020 header and five sample rows
- `graph_v2.json`

**Not opened:** `NP40_ASSESSMENT.md`, `np40_results.txt`, `np40_accessibility.py`, `RUN_LOG.md`.

**Chain:** APS15 → PM08 → NP40 → NP41 → SAR10. The prompt allows P0–P2 to run on supplied inputs, so NP40 needs no loading from PM08.

## Registration (fixed before the instrument)

**Data.** `Datasets/nuclear/NUBASE2020.txt` (Kondev et al. 2021), ground states only (i = 0).
- Its mass excesses for ground states are the AME2020 values (the prompt names AME2020). Values marked '#' (from systematics) are excluded from Q_EC.

**EC set.**
- **Primary:** ground states with Z ≥ 2 whose decay modes contain `EC` or `B+` with a stated intensity (`=`, `~`, `<`, `>`). NUBASE's `B+` is the total of positron emission and EC.
- **Secondary:** the same, also including modes marked `?`.

**EC grammar (constitutional, `CLAUDE.md`).** n_t = A − 2Z + 1, n_d = 3Z − A − 3. Valid if both are ≥ 0, which is equivalent to **Z − 1 ≤ N ≤ 2Z − 3**.

**P0 (accessibility).**
- For every ground-state pair (Z, A) → (Z − 1, A) with both mass excesses experimental: Q_EC = Δ(Z, A) − Δ(Z − 1, A).
- Report the denominator, the count with Q_EC > 0, and the grammar validity of the parent among those.
- **Known-answer validation:** every primary EC nuclide with both Δ experimental has Q_EC > 0.

**P1 (gate a, prompt).** The grammar fails if **more than 1%** of the primary EC set maps to an invalid decomposition. Failures are assessed by class (N < Z − 1, proton-rich; N > 2Z − 3).
- **Null model:** the fraction valid among all ground states with Z ≥ 2.
- **Contrast:** the fraction valid among β⁻ emitters.

**Label, fixed now (NP24).** Grammar validity is an invertible condition on (Z, N), a band. Coverage is therefore a statement about where EC nuclides lie in (Z, N): **shared-input, not independent evidence** for the grammar's physics.

**P2 (clock candidates): not run.** The candidate clocks and their B_req spread come from NP11's record, which has not been rerun under this protocol, and opening the old record is not permitted. Recorded as open, with NP11 as the deciding supplier.

**P3: not run.** No rate law without an inserted multiplier exists.

**Validations:**
- V1: the parser reads ⁷Be (Z = 4, Δ = 15769.00 keV, EC = 100) and ²²Na correctly.
- V2: Q_EC(⁷Be) = 861.89 keV (known).
- V3: validity of ⁷Be under the EC grammar: n_t = 0, n_d = 1, valid.

**Erratum (2026-10-10, after the run; the criterion is unchanged).** V3 above reads "n_t = 0, n_d = 1". The formula gives n_d = 3·4 − 7 − 3 = **2**, and the instrument used the formula. A slip in my registration text.

## Run and results
- `np40_reset_1.cpp`, output in `np40_reset_1_results.txt`. Single pass. V1–V3 met.
- 3,558 ground states parsed.

**P0 (accessibility).**
- 2,249 ground-state pairs with experimental mass excesses.
- 1,235 have Q_EC > 0. Of those, 1,160 (93.9%) have parents valid under the EC grammar.
- Known answer met: all 988 primary EC nuclides with experimental Δ have Q_EC > 0.

**P1 (gate a). The EC grammar's validity band, Z − 1 ≤ N ≤ 2Z − 3:**

| set | n | valid | invalid | invalid with N < Z − 1 | invalid with N > 2Z − 3 |
|---|---|---|---|---|---|
| primary EC (EC/B+ with value) | 1152 | 92.19% | **7.81%** | 90 | 0 |
| secondary EC (incl. '?') | 1473 | 92.53% | 7.47% | 110 | 0 |
| primary EC, experimental Δ only | 999 | 94.39% | 5.61% | 56 | 0 |
| null: all ground states Z ≥ 2 | 3550 | 91.18% | 8.82% | 182 | 131 |
| contrast: β⁻ emitters | 1480 | 92.91% | 7.09% | 0 | 105 |

**Gate (a) MET** (7.81% > 1%): the alternate EC grammar does not cover the EC nuclides. **G1 for coverage, as registered.**
- **Where it breaks:** only on the proton-rich side, N < Z − 1. Examples: ⁸B, ⁹C, ¹⁰C, ¹²N, ¹³O, ¹⁴O, ¹⁷Ne, ¹⁸Ne, all more proton-rich than the He-3-core construction reaches. There are no failures at N > 2Z − 3.
- **No selectivity.** EC nuclides are grammar-valid at 92.2%, essentially the same as all nuclides (91.2%) and β⁻ emitters (92.9%). The band is a statement about where nuclides sit in (Z, N), not about which ones capture. That is the NP24 shared-input reading registered beforehand.

**P2 and P3:** not run. NP11, which supplies P2, is the deciding item; no multiplier-free rate law exists for P3.

**Grades.**
- Accessibility table: G4, computed. Q_EC > 0 for every EC nuclide; known answer.
- Grammar coverage: G1. Boundary at N = Z − 1 on the proton-rich side.
- Clock: G2, open.

**Premise traced to its source.** The EC grammar's He-3 core needs N ≥ Z − 1. Very proton-rich capturers need a different construction, for example a core with fewer neutrons or free proton seats. That would be a constitutional question, not something this investigation can patch.

**Downstream (NP41, SAR10):** they take the accessibility table. They do not take the grammar as a selection rule for capture.

## Comparison with the archived record
Deferred.
