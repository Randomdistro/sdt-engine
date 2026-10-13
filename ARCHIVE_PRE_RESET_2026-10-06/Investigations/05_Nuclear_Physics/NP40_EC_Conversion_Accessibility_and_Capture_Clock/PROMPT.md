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
