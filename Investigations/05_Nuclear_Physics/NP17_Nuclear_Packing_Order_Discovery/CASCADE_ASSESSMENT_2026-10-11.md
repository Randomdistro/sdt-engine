# NP17 / NP09 / NP10: tolerance-cascade run, assessment (2026-10-11)

**Registration:** `CASCADE_PRE_REGISTRATION_2026-10-11.md`, written before both instruments; gates unchanged.

**Bands:**
- B1 ≤ 0.1%: precision
- B2 ≤ 1%: strong
- B3 ≤ 3%: mechanism likely; second-order term owed
- B4 ≤ 10%: order-correct; structure missing
- B5 ≤ 30%: scale right; structure wrong
- B6 ≤ 200%: order of magnitude only
- B7 > 200% or wrong sign: excluded

**Modifiers:** post-seen (weight capped at consistency), FIT (no band), shared-input.

## C1 — `np17_cascade_1.cpp` (output `np17_cascade_1_results.txt`)
Single pass. Validations (V2 Ry, V3 ¹H defect 13.586 eV) met. All values reproduce the 2026-10-10 reset run.

| id | check | ρ | band | weight |
|---|---|---|---|---|
| NP17-T1-t | H-SE ceiling, ³H (ceiling below measured) | 25.8% | B5 | post-seen; a bound violation |
| NP17-T1-h | H-SE ceiling, ³He | 63.0% | B6 | post-seen; a bound violation |
| NP17-T1-a | H-SE ceiling, ⁴He | 74.4% | B6 | post-seen; a bound violation |
| NP17-T2 = NP09-C1a | H-SE deuteron at the contact geometry, native list | 1.71% | **B3** | post-seen; isolated (the same rule's ceiling is violated at A ≥ 3) |
| NP17-T3 | H₂⁺, static seat | 67.5% | B6 | post-seen |
| NP17-T4 | neutron node | — | **B7** | wrong sign |
| NP17-T5 = NP09-C1b | old ledger on its own list | 52.6% | B6 | post-seen |
| NP09-C1c | old ledger against {p, n} (the old claim) | 1.09% | B3 | **list mismatch: carries no weight**. The band records why the old claim looked strong. |
| NP10-C4 | 2R_p_lock against R_He | 0.42% | **B2** | post-seen; a single radius, not discriminating |

**Reading C1 through the bands.**
- **B2:** only the geometric radius check (NP10-C4).
- **B3:** two results, the H-SE deuteron and the old mismatched claim. Both sit at A = 2, and neither survives off A = 2. A B3 at the simplest case, with B6/B7 everywhere the same rule is extended, is the signature of an isolated agreement, not a mechanism.
- **The ceilings** grow worse with A: B5 for ³H, B6 for ³He and ⁴He. The per-electron class fails progressively.
- **B7, wrong sign:** the node regime, the one place the seat ledger meets the neutron.

## C2 — `nseq_cascade_1.js` (output `nseq_cascade_1_results.txt`)

**Run.** Single pass over 253 nuclides: the NUBASE2020 stable ground states the grammar admits, plus ³H. Validations met: ¹H 13.586 eV; d on {2p, 1e} 1.442246 MeV.

**FIT (no band, no weight).** ²H, ³H and ³He are calibrated seeds in the engine; it has no zero-fit ledger for them. **250 nuclides are zero-fit.**

| list | bands | ratio median | ratio range | CV (shape) | first A-quintile | last A-quintile |
|---|---|---|---|---|---|---|
| native {A p, N e} | **B6: 250 of 250** | 0.3897 | 0.373 (¹¹⁰Pd) – 0.674 (⁶Li) | 8.51%, **B4** | 0.4408 | 0.3902 |
| {Z p, N n} (owed neutron term) | B6: 250 of 250 | 0.3682 | 0.353 – 0.625 | 8.25%, **B4** | 0.4177 | 0.3674 |

**NP10-C3.** μ(⁴He) = 1.6506 μN against 0; ρ = |μ|/μ_p = 59.1%, **B6**.

**Reading C2 through the bands.**
- **Level, B6 everywhere.** The engine's zero-fit ledger is right in order of magnitude only, across the whole stable range. No nuclide reaches B5 or better, so there is no coincidence class to discount.
- **Shape, B4.** The ratio is roughly constant (CV 8.5%), but it trends from 0.67 (Li) and about 0.45 (C–Ne) down to 0.39 (Pb). The engine's binding per nucleon is nearly flat, about 2.8–3.4 MeV, while the measured value rises steeply through the light nuclei and then levels. So the engine has the scale of a per-contact unit (αħc/R_p), but not the rise of binding per nucleon with coordination. That rise is the cooperative effect NP10 found; a tree plus one ring cannot carry it (NP17 addendum).
- **Same list behaviour.** Both lists give the same bands. The owed neutron term moves the level by about 6% and does not change the picture.

**Post-run diagnostic** (not a registered gate; reported because it is a sign error). Along isotope chains of stable nuclides, the engine's binding **decreases** when neutrons are added in **23 of 173 steps**. Each such step is wrong sign (B7) as an increment, since measured binding always rises. They cluster at N = 36–44, 64–72, 92–100 and 108–126. The largest is ²⁰⁷Pb → ²⁰⁸Pb: −27.1 MeV against a measured +6.6.

Origin, checked on ⁶²/⁶⁴Ni, ¹⁵²/¹⁵⁴Sm and ²⁰⁷/²⁰⁸Pb. `calculatedBindingMeV = wakeCoupling × αħc/R_p × contractionScale` (`traction-gear-engine.js:3055`), so:
- (i) the contraction factor (a **size** quantity: 1.05 → 0.97 as tritons close) multiplies the **binding**;
- (ii) the wake coupling itself falls as positions contract (²⁰⁸Pb: 359.33 → 350.40 despite one more contact).

Both make tightening **lower** the binding. NP30 §6 reads contraction as the closure lock, and closures are the most bound nuclides. **Sequencer defect, propose-only** (Release not edited). Contraction should enter the binding with the opposite sense, or not as a multiplier at all, and the wake integral's dependence on contraction should be checked against the contact-instant geometry (NP30 §9).

## Overall reading (what the bands say is important)

| Band | Results | Importance |
|---|---|---|
| B2 | 2R_p_lock = R_He (0.42%) | strongest result in the chain, but a single geometric correspondence; not a binding result |
| B3 | H-SE deuteron (1.71%); old mismatched claim (1.09%) | both at A = 2 only; both isolated (the same rules go B5–B7 off A = 2). No weight as mechanism. |
| B4 | the sequencer's ratio constancy (CV 8.5%) | **the most useful binding result.** The per-contact scale αħc/R_p (= m_e v(R_p)², the 1.83c seat movement) is right in order across 250 nuclides with zero fit. What is missing is a factor (1/ratio) of about 1.5× at Li, 2.2× at C–Ne and 2.6× at Pb: it **grows with coordination** and levels in the heavy nuclei. *(Corrected 2026-10-11 before reporting: the first draft said "rising toward the light nuclei", which inverts the ratio.)* |
| B5–B6 | H-SE ceilings; H₂⁺; old ledger on its list; sequencer level (250/250); μ_α | mechanism not established at these levels |
| B7 | neutron node (wrong sign); 23 sequencer isotope steps (wrong sign) | excluded / defects to repair |

**Direction for O1 (NP17 round 2).** Keep the unit m_e v(R_p)². Replace the per-contact weighting with a cooperative term that grows with coordination (closed contact loops) from ⁴He upward and saturates in the heavy nuclei, where measured B/A plateaus. *(Corrected 2026-10-11 before reporting: the draft said "large at light A".)* Make contraction raise binding, not lower it. All of this is to be stated natively before loading, and tested blind against the engine's construction graphs.

## Run log
- **2026-10-11, C2 launch 1:** aborted by me before completion. A `| head` pipe would have cut the process. No rows were assessed; it is not counted as a run.
- **C2 launch 2:** the single pass.
