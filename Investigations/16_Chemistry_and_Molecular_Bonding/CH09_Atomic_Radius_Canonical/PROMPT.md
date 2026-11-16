# CH09 — Atomic radius, canonical (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification and its audit blocks are kept below the line.

## 1. State after the reset audit (2026-10-10)
**G2, open: specification incomplete; no instrument run.** No native radius definition is committed. The gate (correlation ≥ 0.85) is passed by any Z-monotone trend within periods, so it is not a test.

## 2. What opens it (registered order)
1. A committed definition of **outer-seat reach** on the electron ladder (v(r) = c√(Ѻ/r) with Ѻ = r_e for hydrogen; how Ѻ scales with Z for the fielded population is itself owed; see the PPT18 question on Z·r_e).
2. A gate a monotone trend cannot pass: the **positions and magnitudes of the shell jumps** (alkali onsets), registered first.

## 3. New data and links from the 2026-10-07 to 2026-10-12 work
- The NIST ionisation snapshot (`Datasets/nuclear/NIST_ionisation_snapshot.txt`, `ionisation_energies.json`) gives a second, independent observable on the same ladder: the outer-seat reach should co-predict first-ionisation energies. Register both before computing either.

## Prohibitions (all items in this batch)
- No mechanism or functional form chosen to reach the anchors (2026-10-07 method rule).
- Tolerances are committed before any value is computed.
- No QM narration; no G or GM; the word "charge" is not used.

---

## Previous specification (kept as written)

# CH09 — Atomic Radius: the Canonical Definition

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B31). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

The periodic trends of atomic size — shrinking across a period, jumping at each new shell —
under a single native definition of "radius." Measured anchors: covalent radius tables
(Cordero) as the comparison set.

## SDT footing

Natively an atom's size is the reach of its outermost occupied seat — the radius at which
the outer rider's route closes on the wake ladder. The trends should be the ladder's own
arithmetic: added core occlusion pulls the outer seat in across a period; a new shell opens
a new void tier and the reach jumps. Existing corpus: APS01 (terrain, emergent capacities),
NP30 (the invariant ladder v = c√(r_e/r)), CH03/CH04 (valence and geometry). The original
sheet's gate (correlation ≥ 0.85 with closure offsets ≤ 1 group) is adopted.

## Pre-registration skeleton (complete before any tool)

- Question: does outer-seat reach, computed from core occlusion on the ladder, correlate
  ≥ 0.85 with measured covalent radii Z = 1–36 with shell jumps at the right groups?
- Rejection criterion (populated): correlation < 0.85 or a shell jump displaced by more
  than one group.
- Anchors: Cordero covalent radii.
- Tolerance: as stated; magnitudes phase two.

## Benchmark linkage

Catalogue row B31 · suite coverage roster · tally on computed number only.

---

## Audit correction 2026-10-05 (gating)

**Finding:** The gate "correlation ≥ 0.85 with covalent radii" is met by any Z-monotone trend within periods, and no native radius definition is committed.

**Correction:** Define the radius from the outer seat reach and gate residuals against Cordero radii after removing the Z trend.

**Status:** OWED — needs a new run, derivation or data; the corrected requirement is recorded here.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
