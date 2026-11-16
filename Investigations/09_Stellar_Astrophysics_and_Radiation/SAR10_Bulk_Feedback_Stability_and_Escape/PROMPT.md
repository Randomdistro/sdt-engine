# SAR10 — Bulk feedback stability and escape (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**Deferred:** at least one of PM08, NP40 or NP41 must be COMPUTED with its loop terms defined. NP40 supplies no loading or clock; PM08 is G2 (connectivity undefined); NP41 was blocked.

## 2. New data and what it teaches (2026-10-10 to 2026-10-12)
- NP41 can now start (P0 from the sequencer cascade). PM08 still needs Harvey's native statement of connectivity.

## 3. Next round (registered order)
1. PM08 connectivity (Harvey).
2. NP41 value law.
3. P0's loop graph naming only defined terms.

## Prohibitions
- No census over candidate predictors.
- Grammar counts are not evidence (NP24).
- No data substitution without a label.
- Release is read, never edited (proposals only).
- The word "charge" is not used.

---

## Previous specification (kept as written)

# SAR10 — Bulk feedback, stability and escape (child D of SDT_Loading_EC_Reseating_Neutrino_Coupling)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, opened 2026-10-05. Id and placement proposed. Gateways binding; direct execution only.
> **Parent:** Phase 5. **Depends on:** NP40, NP41 and PM08; cannot start before at least one of them is COMPUTED.

## ⓪ Five questions
1. **What don't we know?** Whether a population of conversion events feeds back on its own rate (loading → conversion → emission → loading) and whether any stable, runaway or escaping regime follows, with the governing equation absent from the corpus.
2. **Why does it matter?** This is the claim of the parent hypothesis that would make it a physical mechanism for transients; without a feedback law the hypothesis is only a list of couplings.
3. **How will we find out?** P0 states the minimal closed loop in terms of quantities the earlier children defined; P1 writes its linearised growth rate and checks the sign structure analytically; P2 integrates it with refinement; P3 compares to observation only with a sealed hold-out.
4. **What would prove us wrong?** (a) The linearised growth rate changes by more than 5% over three refinement levels; (b) the loop energy budget exceeds the available conversion energy by a factor above 1 without a named source; (c) the loop requires a rate multiplier fixed on an observed transient.
5. **How will we know we're done?** Prompt completion A–D; OPEN is recorded if the earlier children leave the loop undefined.

## 1. Executive summary
Question: does the loading chain close into a self-limiting or runaway loop? Closes the Phase 5 gap. Expected outcome: a stated loop with its inputs, or a record that its terms are undefined.

## 2. Physical context
PPT09 leaves dynamical stability OPEN (classification COMPUTED). SAR03 (solar luminosity from recycling) is OPEN with two leads and CALIBRATED 0. SAR01 gives a Le Sage thermal budget (unanchored). FLM06 keeps l_P as Axiom R1; PM07 names three MHD orphans. FLM15 (influx phase resistance ratio, engaged fraction 6/7) has not been extracted in the ledger and must be read before use.

## 3. Theoretical framework
No inserted instability growth constant. Energy budget must close in a bounded domain (1e-6 residual, decreasing under refinement). Hydrodynamic or plasma language is allowed only for quantities that the earlier children defined natively.

## 4. Investigation strategy
- **P0:** write the loop as a dependency graph from the children's outputs; flag every term without a definition.
- **P1:** if all terms are defined, derive the linearised growth rate; otherwise stop and record the undefined terms.
- **P2:** integrate with three refinement levels; growth-rate change < 5%.
- **P3:** comparison with an observed transient only against a hold-out sealed before access; the declared historical exposure in the parent's RUN_LOG applies.

## 5. Success criteria
P0 graph complete with every undefined term named; later phases run only if P0 shows none.

## 6. Outputs
`RUN_LOG.md`, `SAR10_ASSESSMENT.md`, the loop graph as a table.

## 7. Dependencies
| Row | Item | Recorded status |
|---|---|---|
| U18 | PPT09 | COMPUTED / OPEN |
| U40 | PM07 | OPEN (named orphans) |
| U42 | SAR03 | OPEN |
| U41 | SAR01 | recorded; class not re-extracted |
| U09 | FLM06 | AXIOM |
| U14 | FLM15 influx ratio | NOT EXTRACTED |
| children | PM08, NP40, NP41 | not yet run |

## 8. Falsification tests
Triggers in ⓪.4.

## 9. Implementation notes
Standalone tool, constants from `laws.hpp`; source freeze before any run.

## ⑩ Adaptive execution
**Pre-run commitment:** completion target C (graph); physics class hoped OPEN with named terms; CALIBRATED budget 0; forbidden: inventing a feedback term to complete the loop, fitting growth to an observed light curve.
| Trigger | First response | If pivot fails | Forbidden |
|---|---|---|---|
| P0 finds an undefined term | record the term and its owner investigation | OPEN | supply a plausible form |
| growth not converged | refine, check stiffness | record non-convergence | pick the converged level silently |
Failures get an in-depth assessment and a dated next round.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The prompt states that the governing equation of the feedback loop is absent from the corpus, so the loop cannot be closed without inventing its terms (blocked on PM08, NP40 and NP41).

**Correction:** Hold until the earlier children define their terms, then derive the linearised loop from those definitions.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
