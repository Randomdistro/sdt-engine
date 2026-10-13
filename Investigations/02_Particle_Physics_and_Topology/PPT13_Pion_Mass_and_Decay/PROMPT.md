# PPT13 — Pion mass and decay (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification and its audit blocks are kept below the line.

## 1. State after the reset audit (2026-10-10)
**G2, open: specification incomplete; no instrument run.** The "unstable winding configuration" is undefined, and no tolerance is committed. law_VI has no metastable-rung rule; choosing one to land on 273 m_e would be a census.

## 2. What opens it (registered order)
1. A native metastable-winding rule from the PPT01 mode equations plus an unwinding barrier (PPT09 open).
2. An unwinding route preference (which decay channel).
3. Then the PDG comparison, with cascade bands.

## 3. New data and links from the 2026-10-07 to 2026-10-12 work
- Shares its first step with PPT14 (excitation ladder) and inherits PPT18's winding ruling.
- The muon budget test (PPT16, G4) validates Law V at γ ≈ 29. It supplies no rung rule.

## Prohibitions (all items in this batch)
- No mechanism or functional form chosen to reach the anchors (2026-10-07 method rule).
- Tolerances are committed before any value is computed.
- No QM narration; no G or GM; the word "charge" is not used.

---

## Previous specification (kept as written)

# PPT13 — Pion Mass and Decay from Open-Winding States

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B72). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

The charged pion: mass 139.570 MeV (~273 electron rungs), lifetime 26 ns, decay almost
entirely to muon + neutrino. Measured anchors: PDG values.

## SDT footing

No quark constituents are available (prohibited inputs) — natively a pion must be an
UNSTABLE winding configuration: a knot that does not close on the W-ladder's stable rungs
(electron W=1, proton W=3) and unwinds to the nearest stable lepton rung plus the
un-closable winding (PPT10's neutrino as straight-light). The decay channel — muon, not
electron, despite more available movement — is the sharp native question: route preference
in unwinding. Existing corpus: PPT01 (equilibrium quantisation — which windings ARE stable),
PPT09 (winding stability), PPT10, NP33 (the mesh the pion mediates in the prevailing
account's nuclear story — natively the mesh needs no mediator, which re-poses what a pion IS:
a struck fragment of mesh, not a force carrier).

## Pre-registration skeleton (complete before any tool)

- Question: does the winding ladder admit a metastable configuration near 273 m_e, and does
  its least-resistance unwinding route land on the muon rung?
- Rejection criterion (populated): no metastable winding near the measured mass, or
  unwinding preferring the electron rung (the measured branching is 99.99% muon — a wrong
  preference is fatal).
- Anchors: m_π±, τ_π, branching ratios (PDG).
- Tolerance: committed before instrumentation.

## Benchmark linkage

Catalogue row B72 · suite coverage roster · tally on computed number only.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The seed asserts an "unstable winding configuration" for the pion with no definition of the configuration, and its tolerance is "committed before instrumentation" but not committed.

**Correction:** Specify the winding configuration and the mass rung rule, then commit the tolerance.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
