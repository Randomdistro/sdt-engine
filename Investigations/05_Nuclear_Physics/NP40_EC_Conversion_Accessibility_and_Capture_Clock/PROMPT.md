# NP40 — EC conversion accessibility and capture clock (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The 2026-10-05 specification is kept below the line, superseded where stated.

## 1. What is established (reset run 2026-10-10, `NP40_RESET_ASSESSMENT_2026-10-10.md`)
| # | Result | Grade |
|---|---|---|
| E1 | **Accessibility:** of 2,249 ground-state pairs, 1,235 have Q_EC > 0. Every one of the 988 primary EC nuclides with experimental masses has Q_EC > 0 (known answer met). | G4 |
| E2 | **EC-grammar coverage (He-3 core; valid band Z − 1 ≤ N ≤ 2Z − 3):** 7.81% of primary EC nuclides fall outside it, all on the proton-rich side N < Z − 1 (⁸B, ⁹C, ¹⁰C, ¹²N, ¹³O, ¹⁴O, ¹⁷Ne, ¹⁸Ne …). None fall outside at N > 2Z − 3. | **G1** for coverage (gate: > 1%) |
| E3 | **No selectivity:** EC nuclides are grammar-valid at 92.2%, all nuclides at 91.2%, β⁻ emitters at 92.9%. The band says where nuclides sit in (Z, N), not which ones capture. | NP24 shared-input reading, confirmed |
| E4 | **The live sequencer (NSEQ18-WEB-1) has no EC grammar.** `grammar()` implements only the canonical decomposition, so it **refuses** ⁷Be and ¹¹C (N = Z − 1; n_t = −1) and ⁸B. The He-3-core alternate grammar in `CLAUDE.md` exists only in prose. | checked 2026-10-12 |

## 2. What the errors teach
1. **There are two boundaries, not one.**
   - The constitutional EC grammar cannot reach N < Z − 1.
   - The live construction cannot reach even N = Z − 1.
   - Any capture claim from structure needs a **construction** for proton-rich nuclei before it can be tested: a core with fewer neutron seats, or free proton seats. That is a constitutional question for Harvey, not a patch.
2. **Coverage can never be evidence** (NP24): the band is an invertible condition on (Z, N). Future gates on the grammar must test **structure** (positions, contacts, observables from the built nucleus), not membership.

## 3. Next round (registered order)
- **P0′:** once Harvey rules on the proton-rich construction, add it to the sequencer as a proposal (Release is propose-only). Validate it builds ⁷Be, ¹¹C and ⁸B with A protons, A electrons and N stabled.
- **P1′ (structure, not coverage):** from the built EC parents, a structural observable registered before computing. Candidate: the count of fielded electrons within reach of the node seats, as the native "K-electron access". Validation: the known halving of the ⁷Be capture rate in the hydrogenic ion (2 × 53.22 d = 106.44 d against 106.4 d; NP07 reset). The construction must reproduce the factor 2 from electron count alone.
- **P2 (clock):** waits on NP11 (supplier), not yet re-run.
- **P3 (rate law):** no multiplier-free law exists; not run.

## 4. Prohibitions
- Grammar membership is not evidence.
- No inserted rate multiplier.
- The word "charge" is not used (count electrons).
- Release is not edited (proposal only).

---

## Superseded specification (2026-10-05, kept as written)

# NP40 — EC conversion event, accessibility and capture clock (child C1 of SDT_Loading_EC_Reseating_Neutrino_Coupling)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, opened 2026-10-05. Id and placement proposed. Gateways binding; direct execution only.
> **Parent:** Phase 3. **Depends on:** child B (PM08) for a loading input, but P0–P2 here can run on supplied loadings.

## ⓪ Five questions
1. **What don't we know?** (i) A physical selection of which nuclides can undergo electron capture (the continuation's "213 inventory pairs" is only a count of rows with at least three deuterons; none has Q_EC > 0 against AME2020), and (ii) a capture clock that is not back-solved (ledger D44, D45).
2. **Why does it matter?** The conversion event and its rate are the dependent variable of the loading hypothesis; with no selection and no clock, nothing can be predicted or falsified.
3. **How will we find out?** P0 defines accessibility from AME2020 Q_EC and the grammar's alternate EC grammar (n_t = A − 2Z + 1, n_d = 3Z − A − 3); P1 tests the grammar against known EC nuclides; P2 builds the clock candidates and their ambiguity (as NP11 did for B); P3 compares to measured EC rates only if a rate law with no inserted multiplier exists.
4. **What would prove us wrong?** (a) The alternate grammar fails to map more than 1% of tabulated EC nuclides to a valid (n_d, n_t ≥ 0) decomposition; (b) any candidate clock needs a dimensional multiplier fixed on a measured rate; (c) B_req = ln(τ/t) ambiguity across clocks exceeds the 7.5-nat spread NP11 recorded and the ambiguity is not reduced.
5. **How will we know we're done?** Prompt completion A–D; physics class OPEN is acceptable and recorded; a rate prediction needs the no-multiplier gate.

## 1. Executive summary
Question: which conversions are admissible, and what sets the capture time? The loading chain needs both. Expected outcome: an accessibility table with its Q_EC basis, plus a record of whether any non-fitted clock exists.

## 2. Physical context
EC nuclides use the alternate grammar in `CLAUDE.md`. NP18 is DEFER (coherence 7 orders short); NP20 OPEN (no derived Q_β); NP11 gives B back-solved with 7.5 nats spread over five nuclear-scale clocks and a null-model census P = 0.64. PPT10/PPT11 leave the carrier OPEN (grade C), so no neutrino energy or momentum is assumed.

## 3. Theoretical framework
No fitted rate constant. Q_EC enters only as a measured selection input (AME2020 in `Datasets/nuclear/`), declared as OBSERVED, not as a derived quantity. Shared-input rule: counts that are an invertible map of (Z, N) (NP24) cannot be independent evidence.

## 4. Investigation strategy
- **P0 accessibility:** for each AME2020 nuclide with a valid parent and daughter, record Q_EC, the grammar decomposition of parent and daughter, and whether Δn_t, Δn_d match the EC grammar. Report the denominator (all rows, not only grammar-eligible).
- **P1 grammar test:** fraction of known EC nuclides that map to valid decompositions (gate ⓪.4a). Null model: the same test on random (Z, N) pairs.
- **P2 clock candidates:** list each candidate clock with its source and units; report the ambiguity in B_req across them; no selection by agreement with a target.
- **P3 rate comparison:** only if a rate law exists without an inserted multiplier. Be-7 is target-exposed (NP18); a hold-out nuclide sealed before access is required.

## 5. Success criteria
P0 table complete with a stated denominator; P1 gate evaluated against the null; P2 ambiguity reported; P3 not run unless the no-multiplier gate holds.

## 6. Outputs
`RUN_LOG.md`, `NP40_ASSESSMENT.md`, `np40_*.cpp` or `.py`, results files, an accessibility CSV with provenance.

## 7. Dependencies (from `DEPENDENCY_LEDGER_v2.csv`)
| Row | Item | Recorded status |
|---|---|---|
| U21 | NP11 | NP11_BARRIER_DEPTH_OPEN |
| U22 | NP17 | RESOLVED (mechanism, deuteron); PENDING (heavy) |
| U23 | NP18 | DEFER |
| U24 | NP20 | OPEN |
| U25 | NP24 | shared-input (not independent) |
| U30 | NSEQ16 | contact construction candidate |
| U32 | NSEQ18 | construction pass; value law pending |
| U19, U20 | PPT10, PPT11 | OPEN |
| D44–D47 | Q_β, clock, carrier | OPEN |

## 8. Falsification tests
Triggers in ⓪.4 with numeric thresholds fixed here.

## 9. Implementation notes
Datasets in `Datasets/nuclear/` (AME2020_mass_excess.txt, NUBASE2020.txt). Constants from `laws.hpp`. Record the data provenance for each file used.

## ⑩ Adaptive execution
**Pre-run commitment:** completion target B; physics class hoped CONVERGENCE for accessibility, OPEN for the clock; CALIBRATED budget 0; forbidden: choosing a clock because it matches a rate, inserting a rate multiplier, pruning nuclides after seeing results.
| Trigger | First response | If pivot fails | Forbidden |
|---|---|---|---|
| grammar maps < 99% of EC nuclides | assess the failures by class (odd-odd, light, heavy); test alternate cores | record the boundary of the grammar | drop failing nuclides |
| clock needs a multiplier | list it as CALIBRATED(1) with the target it was fitted to, and stop | OPEN | present it as derived |
| B_req ambiguity unresolved | record as a limit of the programme | OPEN | pick the clock giving the smallest B |
Failures get an in-depth assessment and a dated next round.
