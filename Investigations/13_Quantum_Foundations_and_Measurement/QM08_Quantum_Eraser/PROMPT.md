# QM08 — Quantum eraser (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification and its audit blocks are kept below the line.

## 1. State after the reset audit (2026-10-10)
**G2, open: specification incomplete; no instrument run.** Only a reading ("subset selection over route-definite arrivals") is given. There is no arrival model per gating configuration and no tolerance, and the rejection criterion is not numeric.

## 2. What opens it (registered order)
1. The QM01/QM05 arrival and pair-correlation rules, written as a **generator of coincidence counts**: route-definite arrivals, sequential occupancy (FLM14), with no wavefunction.
2. Visibility for each Kim et al. (2000) pairing, computed from the generator. Tolerance committed first.
3. The single comparison.

## 3. New data and links from the 2026-10-07 to 2026-10-12 work
- FLM14 (rotating spation; electron positions sequential; Born = dwell time) supplies the native arrival picture the generator must use. No QM formalism is used as scaffolding (standing rule).

## Prohibitions (all items in this batch)
- No mechanism or functional form chosen to reach the anchors (2026-10-07 method rule).
- Tolerances are committed before any value is computed.
- No QM narration; no G or GM; the word "charge" is not used.

---

## Previous specification (kept as written)

# QM08 — The Eraser Experiments Without Retrocausality

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B57). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Delayed-choice eraser results: interference visibility returns or vanishes depending on
whether which-path records are erased — with the "choice" made after the particle has
landed. The prevailing account narrates retrocausality or observer-dependence. Measured
anchors: the Kim et al. coincidence data; visibility-vs-distinguishability tradeoffs.

## SDT footing

Natively there is nothing to erase backward: the knot always takes one route (QM01), the
pattern is dwell bookkeeping over many arrivals, and the "eraser" only changes WHICH
SUBSET of arrivals a coincidence gate selects. Sorting dots after the fact changes the
histogram you draw, never the dots. The whole phenomenon should reduce to conditional
selection on correlated pairs (the throughpole correlation of QM05) — bookkeeping,
not backward causation. Existing corpus: QM01 (deterministic double slit), QM04 (dwell),
QM05 (pair correlation).

## Pre-registration skeleton (complete before any tool)

- Question: does route-definite relay dynamics plus coincidence-subset selection reproduce
  the measured visibility in every gating configuration of the Kim experiment?
- Rejection criterion (populated): any gating configuration whose measured visibility
  cannot be reproduced by subset selection over route-definite arrivals — that outcome
  would force non-local ledger revision and wound QM01/QM05 jointly.
- Anchors: Kim et al. visibilities per detector pairing.
- Tolerance: committed before instrumentation.

## Benchmark linkage

Catalogue row B57 · suite coverage roster · tally on computed number only.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The seed names no mechanism (only "subset selection over route-definite arrivals") and no committed tolerance, and its kill condition ("forces non-local ledger revision") is not a numeric trigger.

**Correction:** Define the which-path selection model and state a visibility tolerance from the Kim et al. data before running.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
