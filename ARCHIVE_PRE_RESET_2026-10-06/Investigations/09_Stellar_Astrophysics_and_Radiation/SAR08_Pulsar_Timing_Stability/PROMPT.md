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
