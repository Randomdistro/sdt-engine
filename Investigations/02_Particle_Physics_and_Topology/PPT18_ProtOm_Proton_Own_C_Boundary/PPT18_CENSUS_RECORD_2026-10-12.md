# PPT18 stage 3 census: does any map cell match a recorded measurement? (2026-10-12)

**Registration:** PROMPT.md addendum (e), written before `ppt18_census.py`. Output `ppt18_census_results.txt`. **A census: not evidence** (2026-10-07 rule).

**Scope.**
- 110 cells: 90 on the proton's own ladder and 20 on hydrogen's; 84 distinct values.
- 28 references, fixed in advance.
- 3,080 comparisons.

**By construction (not counted):** at z = 1 the F and B forms return the mover's rest energy: e 0.511 MeV and p 938.27 MeV.

**Correction to the instrument's own tally (stated here, not hidden).** The two B2 "matches" of the 938.27 MeV cells to the **neutron** (0.14%) are the same construction cell sitting next to m_n ≈ m_p. They are counted as construction. So are the two B3 matches of those same cells to η′. The registered rule excluded only exact rest-energy equalities, so the script counted them.

**Remaining matches:**

| band | Δ | cell | value | reference |
|---|---|---|---|---|
| B2 | 0.73% | proton, F, R_p → a | 295.8 MeV | Δ(1232) − N excitation, 293.7 MeV |
| B3 | 1.30% | electron on hydrogen's ladder, H, R_p → a | 1.461 MeV | native deuteron 1.442 MeV |
| B3 | 1.33% | proton, F, R_p → Ѻ_p | 765.0 MeV | ρ 775.3 MeV |
| B3 | 2.10% | electron on hydrogen's ladder, F, R_p → Ѻ_p | 7.556 MeV | helion binding 7.718 MeV |
| B3 | 2.26% | proton, F, R_p → Ѻ_p | 765.0 MeV | ω 782.7 MeV |

**Chance baseline** (the grid multiplied by a random factor in [0.5, 2], 20,000 trials):
- mean B1 + B2 matches **4.74** (observed, as the script counted it: 3; after the correction above: 1);
- mean B1–B3 matches **14.3** (observed: 9; after the correction: 5).

**The grid matches recorded values *less* often than a randomly rescaled copy of itself.** There is no signal above chance.

**Chosen cell (fixed before matching):** proton-mass circulation, H, ∞ → contact = **43.32 MeV**. **No reference within 3%.** The nearest is α binding, 28.30 MeV, +53%. The list holds no recorded value at 43 MeV.

**Limits.**
- The reference list is short (28) and deliberately excludes nuclear gamma-line catalogues. Those are dense enough that every cell would hit something, which makes them worthless as tests.
- The best non-trivial cell (Δ − N at 0.73%) is at chance level and is not entered as a coincidence: 1 of 3,080 comparisons, below the chance expectation.

**Answer:** no result of the map matches a recorded measurement beyond what chance gives.
