# NP17 / NP09 / NP10: tolerance-cascade run, pre-registration (2026-10-11)

**Direction (Harvey, 2026-10-11):** "run them all with a cascade of tolerances, each band signifying how important."
This file is written before either instrument (`np17_cascade_1.cpp`, `nseq_cascade_1.js`) exists. Gates are not changed after the run.

## 1. The cascade
One relative residual ρ = |predicted/measured − 1| per check. Each band has a fixed meaning and a fixed next step.

| Band | ρ | What it signifies | What it starts |
|---|---|---|---|
| **B1** | ≤ 0.1% | precision agreement: a candidate exact relation | independence and look-elsewhere audit; held-out replication |
| **B2** | ≤ 1% | strong quantitative agreement | replication on a held-out set; derive any remaining factor |
| **B3** | ≤ 3% | mechanism very likely right; a second-order term is owed | name the second-order term natively |
| **B4** | ≤ 10% | order-correct: the mechanism is in play, but structure is missing | find the missing structure (geometry or contact weight) |
| **B5** | ≤ 30% | scale right, structure wrong | keep the scale, replace the structure |
| **B6** | ≤ 200% | order of magnitude only | the mechanism is not established |
| **B7** | > 200%, or wrong sign | excluded at this level | withdraw the route |

**Weight modifiers.** Each applies to the band's significance; the band itself is still reported.
- **post-seen:** the value was known before registration. The band is reported, but weight is capped at "consistency" whatever the band.
- **calibrated-to-target:** the parameters were fitted to the same value. No band is assigned (marked **FIT**); it carries no weight.
- **shared-input:** the prediction contains the measured quantity or a derivative of it. The band is reported and flagged as not independent.
- **wrong-sign:** B7 regardless of magnitude.

For a measured zero (μ_α = 0), ρ is taken as |predicted| / (the nucleon scale μ_p) and stated as such.

## 2. Runs and checks

### Run C1: `np17_cascade_1.cpp` (engine constants + AME2020)

All checks carry exposure: their values were printed in the NP17 reset run of 2026-10-10.

| id | check | measured | modifier |
|---|---|---|---|
| NP17-T1-t | H-SE ceiling for ³H, ratio form (ceiling/measured) | native {3p, 2e} | post-seen |
| NP17-T1-h | H-SE ceiling for ³He | native {3p, 1e} | post-seen |
| NP17-T1-a | H-SE ceiling for ⁴He | native {4p, 2e} | post-seen |
| NP17-T2 / NP09-C1a | H-SE deuteron at the contact geometry | native {2p, 1e} | post-seen |
| NP17-T3 | H₂⁺, static seat | 16.2491 eV | post-seen |
| NP17-T4 | neutron node, H-SE (prediction −2.567 against +0.782) | m_n − m_p − m_e | wrong-sign |
| NP17-T5 / NP09-C1b | old ledger 3αħc/D on its own list | {2p, 1e} | post-seen |
| NP09-C1c | old ledger 3αħc/D against {p, n} (the old claim) | 2.224571 | post-seen; list mismatch |
| NP10-C4 | 2R_p_lock against R_He | 1.6755 fm | post-seen |

For the ceilings, the cascade is applied to ρ = |B_max/B_meas − 1|, and the ceiling's direction is stated. A ceiling below the measured value is a bound violation; the band then measures by how much.

### Run C2: `nseq_cascade_1.js`, the live sequencer's zero-fit ledger (NSEQ18-WEB-1), whole range, single pass

**Set.** Every NUBASE2020 ground state marked `stbl` that the grammar admits (N between Z and 2Z − 2), plus the seeds ²H, ³H, ³He and ⁴He. Measured masses come from AME2020.

**Prediction.** `observableLedger.massDefect.calculatedBindingMeV`. The engine's zero-fit route uses wake contact coupling × αħc/R_p × contraction. Seeds are CALIBRATED in the engine and are marked FIT.

**Measured, two lists:**
- primary: native **{A p, N e}** (NP17 E4);
- secondary: **{Z p, N n}**, the list the engine's preset uses. It carries the owed neutron term (+0.782 MeV per neutron).

**Outputs:**
- per nuclide: ρ and band on both lists;
- band histogram;
- median ratio, and the coefficient of variation (CV) of the ratio across the set. The CV is the **shape observable**: a constant ratio means the structure is right and only the scale is off. The cascade on the CV is: B2 ≤ 1%, B3 ≤ 3%, B4 ≤ 10%, B5 ≤ 30%.
- the ratio in the first and last A-quintiles (the trend).

**Exposure.** The ratio on {p, n} was seen before this registration:
- about 0.41–0.43 for ⁴He–¹⁶O;
- 0.374 for ⁵⁶Fe, 0.358 for ¹²⁰Sn and 0.355 for ²⁰⁸Pb (computed 2026-10-10/11 and compared mentally).

The whole run is therefore **post-seen** in level and trend. It is reported for completeness and for the band census over the 254-nuclide set, most of which was not looked at individually.

**Moment check (NP10-C3).** μ(⁴He) from the same ledger against 0, using ρ = |μ|/μ_p. Post-seen (1.65 μN).

## 3. Expected landing (stated before the run)
- C1 reproduces the 2026-10-10 numbers. The bands follow from them.
- C2 lands in B6 on both lists, with CV in B4–B5.
- If C2 shows B1–B3 for any nuclide, that is a coincidence class: with 254 nuclides spread over B6, a few nuclides near any ratio are expected. It is reported with that count, not as support.

## 4. Not run, and why
- NP09-C2, NP10-C1/C2 and NP17 round 2 need the O1 per-contact statement (owed; PROMPT addendum 2026-10-10).
- No rule is invented to fill that gap.
