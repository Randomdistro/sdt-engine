# NP17: the shared-electron seat ledger on native lists (reset record, 2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`, amended for this item by Harvey's direction of 2026-10-10. That direction was to complete dependencies first, and to understand the packing sequencer and prior mass-defect work before grammar work. Session sdt-engine-e0.

**Why NP17 now.** NP10 (the first item attempted with an unmet supplier) needs a native single-bond ledger. It names NP09. NP09's premise is withdrawn (its reset record), and that record names NP17 as the native mechanism. NP17's own suppliers:
- NP06: reset G1/G2.
- PPT09: reset.
- NP30: no PROMPT; read as a construction.

## Exposure (not blind)
At Harvey's direction I read the following before registering:
- `INVESTIGATION.md`, `NP17_VERDICT.md`, `np17_results.txt`
- NP30 in full
- the NP14 native assessment
- the NP06 reset record
- the NP10 reset record
- the ATOMICUS rules
- the live sequencer `traction-gear-engine.js` NSEQ18-WEB-1, which I also ran

The specification and registration are in `PROMPT.md` (written 2026-10-10; §5 is the registration). PROMPT.md lists the numbers known before the run. T2 and T3 were anticipated by hand and are graded with that in mind.

## Run
- **Instrument:** `np17_reset_1.cpp`, built with `build_reset_1.bat` (MSVC, `/std:c++20 /O2 /utf-8`). Constants come from `sdt::laws`; AME2020 is read from `Datasets/nuclear/AME2020_mass_excess.txt`.
- **Attempt 1: G0** (output kept as `np17_reset_1_results_attempt1_G0.txt`). Two validations were not met, both instrument faults.
  - **V1:** the identity αħc/r = m_e c² r_e/r held only to 6×10⁻¹⁰. The 1e-12 tolerance was below the engine's constant-vintage floor (m_e from CODATA 2018, α from 2022).
  - **V3:** ¹H came out at 14.894 eV. The engine's m_p (CODATA 2022, kg) had been converted to MeV by a different route from the AME masses (AME's u→keV factor). That mix is 1.3 eV per proton.
- **Attempt 2.** All masses are carried in u with the CODATA 2022 u (kg and MeV); V1 tolerance is 1e-8, with the floor stated. Gates unchanged. Output: `np17_reset_1_results.txt`.

## Validations (attempt 2): met
| | Result |
|---|---|
| V1 | αħc = 1.439965 MeV·fm; the identity holds to 6×10⁻¹⁰ |
| V2 | ½ m_e(αc)² = 13.605693123 eV = engine Ry |
| V3 | ¹H defect against {p, e} = 13.586 eV (measured 13.598) |
| V4 | deuteron against {2p, 1e}: 1.442233 MeV (engine CODATA masses) and 1.442246 MeV (AME), differing by 13 eV |

## Results
**Seat unit:** ½ αħc/R_p = ½ m_e v(R_p)² = 0.855696 MeV, with v(R_p) = 1.83006c.

**T1 (decisive, geometry-free): the H-SE ceiling B_max = N·A·(½ αħc/R_p).**

| nucleus | N | A | B on native list {A p, N e} | ceiling | ratio |
|---|---|---|---|---|---|
| ²H | 1 | 2 | 1.442246 | 1.711391 | 0.843 (within) |
| ³H | 2 | 3 | 6.917143 | 5.134174 | **1.347** |
| ³He | 1 | 3 | 6.935735 | 2.567087 | **2.702** |
| ⁴He | 2 | 4 | 26.731023 | 6.845565 | **3.905** |

All three A ≥ 3 nuclei exceed the ceiling. **H-SE is excluded (G1) as the binding mechanism for A ≥ 3.** The ceiling places every electron on every proton boundary at once, so no placement can rescue the class.

**T2 (deuteron, post-seen).** NP30 contact geometry, with the electron at 7R_p/6 from each proton: 1.466907 MeV against 1.442246, **+1.71%**. Within the registered 3%. **G3 at most:**
- post-seen (the number is NP06 T4's D/2 entry);
- look-elsewhere count 8 (NP06);
- the same rule is excluded at A ≥ 3 (T1).

It is therefore an isolated agreement, not support for the mechanism.

**T3 (cross-scale).** H₂⁺ under the same rule (static midpoint electron, R_e = 2a₀) gives 27.2114 eV against 16.2491 eV measured: **+67.5%**. The static seat rule is not one law across the ladder.

**T4 (domain check).** The rule at the node predicts n *lighter* than p + e by 2.567 MeV. Measured: n is *heavier* by 0.782 MeV. The gap is 3.349 MeV. The node regime has a different ledger (E5, owed).

**T5 (old ledger, corrected).** 3αħc/D = 2.200360 MeV:
- on its own list {p, p, e}, against 1.442246: **+52.6%**;
- against {p, n}, with the neutron's node term in the same pair-potential bookkeeping: −2.934 MeV (unbound).

**The old "deuteron PASS, −1.06%" is withdrawn.** It compared the configuration on the {p, p, e} list with the binding on the {p, n} list. Contaminating input: m_n — CODATA neutron mass via the {p, n} binding B_d — entered at the comparison line of the old `np17_nuclear_packing.cpp` (2.224 MeV target). The withdrawn text stays in `NP17_VERDICT.md` (annotated below).

**Context (report only):**
- Native-list defects at A = 3: t − h = −0.0186 MeV. The defect does not track the number of stabled electrons (2 against 1).
- This was seen in this run, so it cannot later serve as the blind test of O1's "insensitive to N" prediction. That prediction is now **post-seen** for A = 3. A blind O1 test must use nuclei not yet tabulated on native lists, with contact graphs taken from the live sequencer.

## What the errors teach (direction)
1. **The binding is not carried per electron.**
   - The ceiling is broken by factors growing with A (1.35, 2.70, 3.90).
   - ³H and ³He bind equally with 2 and 1 stabled electrons.
   - The carrier must scale with proton–proton contacts and their closure, which is O1. This agrees with NP10's cooperative-lock finding.
2. **The seat movement unit m_e v(R_p)² = αħc/R_p is still the natural native scale.** The live engine's zero-fit ledger uses exactly it and lands at about 0.42× across ⁴He–¹⁶O, so the scale is right in order. What is missing is the contact weighting, which must be derived rather than fitted.
3. **No derived deuteron exists anywhere in the live construction.** Its light seeds are CALIBRATED(8/9). A deuteron derived from O1 would be the first.
4. **Lists.** All future nuclear ledgers are stated on {A p, N e} or {A p, A e}. A {p, n} comparison names the owed neutron term (E5).

## Grades
| Item | Grade |
|---|---|
| H-SE for A ≥ 3 | **G1, excluded** (T1) |
| H-SE deuteron | **G3**, post-seen, isolated |
| H-SE across scale (static seat) | not one law (T3) |
| Old NP17 deuteron PASS | **withdrawn** (X1) |
| Binding mechanism | **G2, open**; O1 opens |

## Downstream
- **NP09** (deuteron): takes no derived deuteron. The H-SE deuteron is G3, isolated. Its prompt is rewritten to consume O1.
- **NP10** (alpha): takes the T1 exclusion of per-electron ledgers, which joins its own exclusion of shared-resource locks. Prompt rewritten to O1.
- **NP17b G2:** the "packed pairwise rule" it awaited is the withdrawn pair-potential ledger. It stays closed on the legacy control.
- **GOM19, NP20, NP22, NP23, NP31:** any consumption of "shared-electron Coulomb binding" is withdrawn.

## Comparison with the archived record
Made at Harvey's direction (exposure above). The old verdict's deuteron PASS is withdrawn (T5). Its alpha shortfall agrees in direction with T1.
