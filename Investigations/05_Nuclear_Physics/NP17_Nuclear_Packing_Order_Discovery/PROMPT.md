# NP17 — Nuclear binding as a mass-defect ledger on the packing construction

**Rewritten 2026-10-10 at Harvey's direction.** The instruction was to complete dependencies first, rewrite prompts to carry new data, and understand the packing sequencer and the prior mass-defect work before doing grammar work. NP17 had no PROMPT.md; the original specification is `INVESTIGATION.md` (kept unchanged). This prompt supersedes that file as the specification.

**Exposure (recorded, per the reset protocol).** At Harvey's direction the author read the prior mass-defect and packing record before writing this, so this prompt is **not blind**:
- `INVESTIGATION.md`, `NP17_VERDICT.md`, `np17_results.txt`
- NP30 §1–§12, the NP14 native assessment, the NP06 reset record (including its eight-length table T4)
- the ATOMICUS rules
- the live engine `traction-gear-engine.js` (NSEQ18-WEB-1), which was also run

Numbers known before registration:
- αħc/r for r ∈ {R_p/3, R_p/2, 2R_p/3, R_p, D/3, D/2, D, 2R_p} (NP06 T4)
- the old electrostatic alpha (4.45 MeV)
- the live engine's zero-fit ledger for ⁴He–¹⁶O (below)
- by hand: the half-movement rule at hydrogen, H₂⁺ (static midpoint) and the deuteron (static gap)

The grades below carry these exposures.

---

## 1. What is established (inputs to this prompt, with source)

| # | Fact | Source | Status |
|---|---|---|---|
| E1 | Ѻ_H = r_e, so an electron seated at radius r about a proton turns at v(r) = c√(r_e/r) | NP30 §1, `laws.hpp` (r_e = α²a₀) | DERIVED ladder |
| E2 | αħc/r ≡ m_e·v(r)², an identity through r_e = αħ/(m_e c). A "Coulomb energy" at r *is* the movement of the electron seated at r. | algebra | identity |
| E3 | Law III is a push; energy is movement; binding is mass defect. Pair-potential bookkeeping (U = Σ q_i q_j/r) is a Standard import. | Harvey ruling 2026-10-07 (NP14 N1, PPT08 withdrawn) | binding rule |
| E4 | A mass-defect ledger is list-dependent. The deuteron against {p, n} is 2.2246 MeV; against {p, p, e} it is 1.4422 MeV. | NP14 native | measured arithmetic |
| E5 | The neutron's own ledger (m_n − m_p − m_e = +0.782 MeV) is **owed**. No seat-velocity derivation stands (SCT demotion 2026-07-01; FLM12: the internal electron is a standing W = 1 harmonic). A list containing n therefore carries an underived term. | SCT memory; FLM12 | open |
| E6 | Electron economy: A protons and A electrons; N stabled (node R_p/3, 3.17c), Z fielded (a₀, αc). Seat R_p = 0.8414 fm at 1.830c. | NP30 §2–§3 | construction |
| E7 | Mass defect = movement freed from double-carrying (interleave depth). The contact-instant geometry fixes binding; the swept extent fixes size. | NP30 §5, §9 | construction (framing) |
| E8 | Grammar: 1 α + n_d d + n_t t. Counts are an invertible map of (Z, N), so they are shared-input, never independent evidence. The grammar breaks at N < Z − 1 and its validity band is not EC-selective. | ATOMICUS rules; NP24; NP40, NP16A01 (2026-10-10) | constitutional + limits |
| E9 | Hydrogen: the defect of ¹H against {p, e} is 13.598 eV = ½·m_e·v(a₀)², with v(a₀) = αc. A known answer at the atomic end of the ladder. | measured; E2 | validation anchor |

## 2. What failed or was mis-scored, and what each error teaches

| # | Error | Origin | What it points to |
|---|---|---|---|
| X1 | **The old NP17 deuteron PASS (2.200 vs 2.2246, −1.06%) compared a {p, p, e} sum against a {p, n} binding.** E = 3αħc/D is the p–e–p configuration referenced to infinite separation of p, p and e. In the same bookkeeping, the neutron's internal electron at R_p/3 already carries αħc/(R_p/3) = 5.13 MeV, so against {p, n} the construction is unbound. Against its own list the target is 1.4422 MeV, and 2.200 misses by +53%. | Ledger list not fixed before comparison (E4 was not yet known when NP17 was written) | Every binding claim must name its list. The clean list for a p/e construction is {A p, N e} (nucleus) or {A p, A e} (atom), which needs **no neutron mass** (E5). |
| X2 | The factor 3 = (−4 + 1) is pair-potential bookkeeping: two p–e attractions plus a p–p repulsion. | Withdrawn on 2026-10-07 (E3) | A native ledger has movement terms only. A p–p "repulsion energy" has no place. Whether the protons' push enters, and how, must be stated as movement (seat speeds), not as a potential. |
| X3 | NP06: r = D/3 was one of eight lengths, with about a 0.35 chance of a hit by luck. "Why D/3" was never derived; D/3 appears only as the algebraic image of 3αħc/D. | Census over lengths | No length is selected by agreement. The seat geometry is fixed by the construction before any value is loaded. |
| X4 | Electrostatic alpha 4.45 MeV against 28.3 (old NP17). NP10 reset: binding per contact rises 1.16–3.18× the deuteron's with coordination, so a shared-resource lock (H-W) is excluded. | Pairwise additive ledger | The ledger is **cooperative**: closed contact loops carry more per contact than open chains (NP10 alternative out; NP33 "completing the graph saves one unit", `laws.hpp:2132–2150`). |
| X5 | Live engine (NSEQ18-WEB-1, run 2026-10-10): ²H, ³H and ³He are **CALIBRATED(8/9)**. `fitLightNucleus` fits separation, tilt, phases, compliance, split shift, an energy bridge and a magnetic bridge to that nucleus's own binding, moment and quadrupole. The zero-fit route (A ≥ 4) is `universalObservableLedger`: binding = Σ contact wake coupling × αħc/R_p × contraction. It returns ⁴He 11.69, ⁶Li 19.99, ⁷Li 23.29, ⁹Be 30.19, ¹²C 39.44, ¹⁶O 55.12 MeV, about 0.41–0.43 of the measured {p, n} bindings (28.30, 32.0, 39.2, 58.2, 92.2, 127.6). It also gives μ(⁴He) = 1.65 μN against a measured 0. | The light seeds are fitted, not built; the universal ledger's per-contact unit and contact weights are not derived | No derived deuteron exists in the live construction. The unit αħc/R_p = m_e v(R_p)² (E2: the movement at the 1.83c seat) is the engine's native scale. The missing factor is in the contact count or weight, not in the scale. Report only; a near-constant ratio is not adopted as a fit. |
| X6 | The legacy packer (`pack-nucleus.js`, NSEQ05-CONTROL-3): radii fail 4/6 (NP12f); 3αħc/1.45 fm = 2.979 MeV for the Li-6 deuteron unit (NP17b G1). | Fixed shell steps; frozen dnn | Do not use the legacy control as the construction. |
| X7 | NP09: the integrated far-field Law III gives about 0.06–0.08 MeV per contact (×30 short) and is withdrawn as bookkeeping. | Far-field occlusion is not the binding scale | The MeV scale is the seat movement (E2), not the occlusion integral. |

## 3. Hypotheses under test in this round

**H-SE (shared-electron seat ledger, the class NP17 proposed, now written natively).** Binding is the movement freed when stabled electrons are seated *outside* the proton boundaries, in gaps between protons. Each electron–proton seat pair (electron at r_ij ≥ R_p from proton j) contributes the hydrogen rule ½·m_e·v(r_ij)² = ½·αħc/r_ij (E2, E9). There is no p–p term (E3).

- **Domain.** r ≥ R_p, i.e. the electron is outside every boundary. Inside a boundary is the node regime of E5, whose ledger is owed. The neutron fact is computed as a domain check: the rule at the node predicts p + e → n *lighter* by ½·αħc/(R_p/3); measured is *heavier* by 0.782 MeV.
- **Geometry-free ceiling.** One electron serving k protons at r ≥ R_p contributes at most k·½·αħc/R_p. Electrons can serve at most A protons each, so for a nucleus with N stabled electrons:
  - **B_max(H-SE) = N·A·½·αħc/R_p**
  - This bound needs no placement.

**H-SE consequences tested:**
- T1 (decisive, geometry-free): the ceilings for ³H, ³He and ⁴He against their native-list defects.
- T2 (post-seen, deuteron): the NP30 contact geometry (electron at the gap centre, D/2 = 7R_p/6 from each proton).
- T3 (cross-scale): H₂⁺ under the same rule at the measured bond length. The ladder is one system (NP30 §3), so a rule set by αħc/r must hold at both ends unless a regime difference is named.

## 4. Data (MEASURED-INPUT; anchors, not findings)

- **AME2020 atomic masses**, `Datasets/nuclear/AME2020_mass_excess.txt` (Huang et al., Wang et al., Chin. Phys. C 45, 030002/3, 2021): ¹H, ²H, ³H, ³He, ⁴He. u = 931494.10242 keV (AME2020).
- **Native lists:**
  - atom: {A p, A e};
  - nucleus: {A p, N e}, obtained by removing Z fielded electrons. Their atomic binding (≤ 0.08 keV for A ≤ 4) is neglected and stated.
- `sdt::laws::measured`: m_p, m_e, m_n, m_d, α, ħ, c, a₀, Ry_eV, R_p.
- **H₂⁺:**
  - binding to {p, p, e} = 131058.1219937 cm⁻¹ = 16.2494 eV, vibrationless ground level (the H₂⁺ ionisation energy in the thermodynamic-cycle summary of arXiv:1804.11143);
  - bond length R_e = 2a₀ ("experimental bond length", arXiv:1502.00291).
  - **Limitation:** the 16.249 eV includes zero-point motion of the protons (~0.14 eV), within the gate.

## 5. Pre-registered tests (round 1)

**Validations (any not met → G0, repair the instrument):**
- V1: αħc from the engine = 1.439964 MeV·fm to 1e-5; identity αħc/r = m_e c²·(r_e/r) to 1e-12 at r = 7R_p/6.
- V2: ½·m_e·(αc)² = Ry_eV to 1e-9 relative (the engine's Ry).
- V3: AME parser. Defect of ¹H against {p, e} = 13.598 eV ± 0.5 eV (the eV tolerance covers CODATA/AME unit vintages).
- V4: the deuteron by two routes. AME (²H atom − e against {2p, 2e} … reduced to {2p, 1e}) against the engine (m_p + m_n − m_d − (m_n − m_p − m_e)) agree to 1 keV.

**Tests:**
- **T1 (decisive, geometry-free; H-SE ceiling).** For X ∈ {³H, ³He, ⁴He}: B_meas(X; {A p, N e}) ≤ N·A·½·αħc/R_p?
  - **Exclusion:** if B_meas exceeds the ceiling for at least 2 of the 3, H-SE is **excluded (G1)** as the binding mechanism for A ≥ 3. The ceiling is the most generous placement (every electron on every boundary at once).
  - Also report the deuteron's ceiling (expected to admit).
- **T2 (deuteron, post-seen; capped at G3).** H-SE at the NP30 contact geometry gives B = 2·½·αħc/(7R_p/6), against B_meas(d; {2p, 1e}).
  - Within ±3%: G3, post-seen, carrying NP06's look-elsewhere count of 8.
  - Otherwise: G1 for this placement.
- **T3 (cross-scale).** H-SE for H₂⁺ with the electron static at the midpoint, R_e = 2a₀: B = 2·½·αħc/a₀, against 16.249 eV.
  - Within ±5%: the rule is scale-consistent.
  - Otherwise: **the static-seat rule is not one law across the ladder.** The deuteron and H₂⁺ then require a named regime difference (confined gap against a toured electron, FLM14).
- **T4 (domain check, neutron).** H-SE at the node against the measured n − p − e. Sign and size are reported; this does not grade H-SE outside its domain.
- **T5 (report only).** The old NP17 ledger on its own list: 3αħc/D against 1.4422 (X1 corrected), and against 2.2246 with the neutron's node term included in the same bookkeeping.

**Whole-range single pass.** One instrument, one run, all of the above.

## 6. Grades and what each starts

| Outcome | Grade | Next |
|---|---|---|
| any V fails | G0 | repair the instrument |
| T1 excluded | H-SE G1 for A ≥ 3 | Open O1 (contact-mesh cooperative ledger) as round 2. NP09 and NP10 are rewritten to consume it. |
| T1 admits | H-SE G2 (open) | Placement geometry from the construction (sequencer seats) is registered before T2-like tests on A = 3, 4. |
| T2 within ±3% | G3, post-seen | NP09 takes it as a conditional deuteron (not independent). |
| T3 fails | static seat rule not ladder-universal | Name the regime difference before any reuse at A ≥ 3. |

## 7. Alternative outs (registered now; specified natively before any value is loaded)

- **O1, contact-mesh cooperative ledger.** Binding is carried by proton–proton boundary contacts: counter-rotating mesh at the 1.83c seat (NP30 §5), unit m_e·v(R_p)² = αħc/R_p (E2; the live engine's scale, X5). Contacts in a closed loop lock circulation and save the units an open chain spends (NP10 alternative out, NP33). Electrons set the phase (counter-rotation) and are not the energy carrier.
  - **Structural prediction to register in round 2, before loading:** binding against {A p, N e} is insensitive to N at fixed contact graph, i.e. ³H ≈ ³He.
- **O2, node-regime ledger.** The stabled electron's ledger inside the boundary (FLM12 field engagement). Needed for E5 and any list containing n.
- **O3, live-engine contact weight.** Derive the per-contact weight of `universalObservableLedger` from the seat geometry rather than the wake-family integral. Report-only until derived.

## 8. Dependencies

- **Suppliers:**
  - NP06 (reset G1/G2: no α-free Δω; why D/3 open)
  - PPT09 (reset: W + 1 classification)
  - NP30 (construction; no PROMPT)
  - NP14 native (list rule)
  - NP10 reset (cooperative lock)
- **Dependents:** NP09 (deuteron), NP10 (alpha), GOM19, NP20, NP22, NP23, NP31. NP17b is G2 on this outcome.

## 9. Prohibitions (binding)

- No pair potentials or "Coulomb wells" as mechanism; αħc/r is read only as the seat movement m_e v(r)².
- No neutron as an independent particle, and no {p, n} list without naming the owed neutron term.
- No length chosen by agreement.
- No fraction censuses.
- No QM formalism as narration.
- The word "charge" is not used.
- Engine and Laws are not edited (propose-and-wait).

Author attribution: J. C. Harvey, Melbourne.

---

## Addendum 2026-10-10 (after round 1): data for round 2 (O1), taken from the live sequencer

**Round 1 outcome** (`NP17_RESET_ASSESSMENT_2026-10-10.md`):
- H-SE is excluded for A ≥ 3 (T1);
- the deuteron is G3, isolated and post-seen;
- the static seat rule is not ladder-universal (H₂⁺ +67%);
- the old PASS is withdrawn.

**Sequencer contact graphs** (NSEQ18-WEB-1, `buildNuclide`; structure only, no binding read):

| nuclide | V | E | cycle rank | contact kinds |
|---|---|---|---|---|
| ²H | 2 | 1 | 0 | internal 1 |
| ³H, ³He | 3 | 2 | 0 | internal 2 (open chain) |
| ⁴He | 4 | 4 | 1 | alpha 4 (**4-ring**) |
| ⁶Li | 6 | 6 | 1 | alpha 4, dock 1, internal 1 |
| ¹²C | 12 | 12 | 1 | alpha 4, dock 4, internal 4 |
| ¹⁶O | 16 | 16 | 1 | alpha 4, dock 6, internal 6 |
| ⁴⁰Ca | 40 | 40 | 1 | alpha 4, dock 18, internal 18 |
| ⁵⁶Fe | 56 | 56 | 1 | alpha 4, dock 24, internal 28 |

**Structural consequence, stated before round 2 is registered.** On these graphs any ledger that depends only on contact counts and loop count gives, for A ≥ 4:

B = (α-ring term) + Σ_kinds n_kind · w_kind

This is linear in the counts, with at most three weights. The rise and fall of B/A across A therefore cannot come from the graph. It must come from contact geometry: the sequencer's contraction scale and its wake-contact distances (O3).

Round 2 must therefore register **one** native per-contact movement rule that depends on contact geometry (distance and orientation at the 1.83c seat), with no free weight. It is tested blind on A ≥ 6 nuclei on the sequencer's graphs (native lists, AME2020), against a per-nucleus ±5% gate over the whole range in a single pass.

**Owed before round 2 can be registered:** the native statement of what one counter-rotating boundary contact frees, as a function of its geometry. Candidate sources are:
- FLM07 glancing transfer;
- the FLM10 lattice solver;
- Harvey's construction statement.

Inventing it from the measured values is excluded.
