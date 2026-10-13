# SAR08 — Pulsar timing stability (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification and its audit blocks are kept below the line.

## 1. State after the reset audit (2026-10-10)
**G2, open: specification incomplete; no instrument run.** There is no noise-floor model and no wake-release braking law. The rejection trigger is order-of-magnitude and committed to no number.

## 2. What opens it (registered order)
1. A native rotor-rigidity noise bound: the timing floor a rigid rotating boundary sets.
2. A wake-release spin-down law.
3. Each gives a committed number before the J0437−4715 and ATNF comparison.

## 3. New data and links from the 2026-10-07 to 2026-10-12 work
- The canon's light law is c(1 − z)² (GOM22). A pulsar's surface depth (z ≈ 0.1–0.2) makes the emission-side shift a large term. Any timing model must carry it from the surface Ѻ = zR, with no GM.
- A pulsar surface lies between the shallow (stellar) and deep (nuclear contact) regimes PPT18 separated. A natural place to test the displacement-modulated occlusion proposal once derived.

## Prohibitions (all items in this batch)
- No mechanism or functional form chosen to reach the anchors (2026-10-07 method rule).
- Tolerances are committed before any value is computed.
- No QM narration; no G or GM; the word "charge" is not used.

---

## Previous specification (kept as written)

# SAR08 — Pulsar Timing: the Cleanest Clocks

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B91). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Millisecond pulsars keep time to one part in 10¹⁵ — rivalling atomic clocks — with slow,
smooth spin-down. Measured anchors: PSR J0437−4715 timing residuals; the standard spin-down
law P-dot vs P population.

## SDT footing

A pulsar is a maximally compressed rotor near the medium's compression floor (NP30 §11 —
the same floor that landed 11.0 km at 1.4 M☉). Its clock stability is the stability of a
budget-saturated rotor: circulation at the ledger's edge has no free capacity for jitter.
Spin-down is release (L8) through the rotating-wake channel (GOM21's object at full power).
The native questions: does the compression floor's rigidity account for the timing noise
floor, and does wake-channel release give the measured braking without a fitted moment.

## Pre-registration skeleton (complete before any tool)

- Question: does the floor-rotor model bound timing noise at the observed 10⁻¹⁵ class, and
  does wake release produce the P–P-dot population's slope?
- Rejection criterion (populated): predicted noise floor orders above observed, or a
  braking-law slope inconsistent with the population.
- Anchors: J0437−4715 residuals; ATNF P/P-dot catalogue slope.
- Tolerance: committed before instrumentation.

## Benchmark linkage

Catalogue row B91 · suite coverage roster · tally on computed number only.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The seed gives no noise-floor model for millisecond pulsars and its kill ("noise floor orders above observed") is an order-of-magnitude trigger.

**Correction:** Define the noise mechanism and gate against J0437−4715 residuals at a stated factor.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
