# APS10 Assessment — first ionisation energies from occlusion pressure

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `aps10_verify_ie1.cpp` (calls `sdt::laws::atomic::dodecardinal::first_ionisation_eV` as shipped)<br>
**Stdout:** `aps10_results.txt`<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)"

## Status

`APS10_SUPERSEDED_BY_APS14_REVERIFIED` — the seed's premise (no native derivation in the corpus)
was out of date on its own filing date. APS14 computes He–Ne first ionisation; this run
reproduces that result against APS10's gates. COMPUTED, not a blind prediction.

## Instrument validation

`solve_state(1,1)` = −13.605693 eV against −Ry, and `solve_state(2,1)` = −54.422772 eV against
−4Ry, both exact to the printed digits with `converged = true` (residuals 4×10⁻¹⁵, 1×10⁻¹⁴).

## Result (single pass, Z = 2–10)

| Z | | IE₁ computed (eV) | IE₁ measured (eV) | error % |
|---:|---|---:|---:|---:|
| 2 | He | 25.5454 | 24.5874 | 3.896 |
| 3 | Li | 5.1304 | 5.3917 | 4.846 |
| 4 | Be | 8.8334 | 9.3227 | 5.249 |
| 5 | B | 8.2500 | 8.2980 | 0.578 |
| 6 | C | 11.2791 | 11.2603 | 0.167 |
| 7 | N | 14.6434 | 14.5341 | 0.752 |
| 8 | O | 13.5511 | 13.6181 | 0.492 |
| 9 | F | 17.1657 | 17.4228 | 1.476 |
| 10 | Ne | 21.1595 | 21.5646 | 1.879 |

| Gate | Registered | Result |
|---|---|---|
| median error | ≤ 15% | 1.476% — inside |
| maximum error | ≤ 40% | 5.249% (Be) — inside |
| period-trend sign, 8 consecutive pairs | 0 disagreements | 0 — inside (Be→B and N→O decreases reproduced) |
| convergence | residual < 1e-8 | all states converged, maximum 1.5×10⁻⁹ |

The rejection criterion was not met. The computed median and maximum equal APS14's recorded
1.476% and 5.249%. The suite's own B06 gate (`Benchmarks/B01_B25/benchmarks_suite.cpp:500`)
is median ≤ 5% and every row ≤ 15%; both are met. The report-only reading "maximum ≤ 5%"
registered here is stricter than the suite's gate and is not met by Be (5.249%).

## Label and downgrade trace (procedural §3.8)

COMPUTED, not DERIVED. `contaminating input: first ionisation energies He–Ne — measured via
NIST/CRC tables, hard-coded as the B06 comparison rows — enters at
Benchmarks/B01_B25/benchmarks_suite.cpp:503–511, where APS14's post-freeze diagnostics
isolated the coefficient forms (APS14_ASSESSMENT.md:25–26; forms fixed at
Engine/include/sdt/laws.hpp:1486–1492)`. The 45 higher sequential ionisations were not used
in that isolation and are the part of APS14's record that is not exposed to it.

## Limitations

1. **Not a blind test.** The coefficient forms were chosen with the comparison rows in view.
   This run shows the shipped closure meets APS10's gates; it does not show the forms would
   have been found without the rows.
2. **Shared code path.** The engine function is the one the suite's B06 row calls, and the
   one APS14's closure script reached. Agreement among them is reproducibility, not a second
   derivation.
3. **Largest residuals** sit at He (+3.9%, computed above measured), Li (−4.8%) and Be (−5.2%).
   The three lightest closed or near-closed shells carry the largest errors; none approaches
   the 15% row gate.
4. **Domain.** The closure ends at Ne: `solve_state` returns a non-converged state above ten
   electrons. Z = 11–18 is not attempted. The seed's "and beyond" remains open.

## Data defect found

`Datasets/nuclear/NIST_ionisation_snapshot.txt` (33 lines) is a cached NIST ASD error page
("Invalid Checkbox Setting"), not an ionisation table. It is not used here. It is recorded and
left in place: relocation or deletion needs approval, item by item.

## Open

- First-ionisation closure beyond Ne (APS14 records the same).
- Seed text of `PROMPT.md` still reads "no native derivation exists"; the pre-registration
  block above it carries the dated correction.
