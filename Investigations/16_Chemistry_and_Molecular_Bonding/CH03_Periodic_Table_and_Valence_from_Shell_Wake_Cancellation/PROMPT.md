# CH03 — Periodic Table & Valence from Shell Wake-Cancellation

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

The periodic table, the concept of valence, and the octet rule are usually read off filled
electron shells and orbital subshells. **Can periodicity, valence number, and the octet rule be
derived instead from the period-2 wake-cancel map — paired fore/aft wakes go silent, lone wakes
stay active and repel — so that an atom's chemistry is set by how many *active* (uncancelled)
wakes it carries, with no orbitals, no subshells, and no Aufbau wavefunction?** This turns the
B–O / C–F / N–Ne pairing note ([[project_foundational_ontology_influx_monopole]]) into the
explanation of the table itself.

## SDT mechanism & hypotheses

Each electron held at the electropause (EMC04) trails a convergence wake. When electropauses pair
so their wakes sit fore/aft, the wakes **cancel** and go silent (chemically inert, no bonding
hunger); a **lone** wake stays active and will seek a partner — that drive *is* valence. A noble
configuration is one where every wake is paired and silent: the octet is the wake-cancellation
fixed point for a period, not a magic count of eight. The period lengths (2, 8, 8, 18…) are the
counts of wake slots before the next cancellation symmetry closes — the same combinatorics the
period-2 map encodes (B–O, C–F, N–Ne: silent if paired, magnetic/liftable if lone).

- **H1 (valence = active wakes):** valence number = count of uncancelled wakes; predicts the
  valence of each main-group element from the wake-pairing tally.
- **H2 (octet = cancellation fixed point):** the closed-shell/noble state is the all-paired-silent
  configuration; the octet rule and inertness fall out, no orbital filling invoked.
- **H3 (period structure):** period lengths and the B–O/C–F/N–Ne pairing map come from the
  wake-slot symmetry; APS01 k-factors set the radial size per period.

## Strategy

**Phase 1 — Wake tally.** *Goal:* assign active-wake counts. *Method:* build the period-2
fore/aft pairing for Z=1–18. *Success:* recover the standard valence of every period-1–3 element.

**Phase 2 — Octet & inertness.** *Goal:* explain noble gases. *Method:* identify the all-paired
fixed point. *Success:* He/Ne/Ar emerge as zero-active-wake; octet rule reproduced as the rule
not a postulate.

**Phase 3 — Pairing map & periods.** *Goal:* B–O/C–F/N–Ne map + period lengths. *Method:* extend
the wake-slot symmetry; size with APS01. *Success:* paired/lone (silent/magnetic) assignment
matches measured paramagnetism (O₂ paramagnetic, N₂ not); period lengths 2/8/8.

**Phase 4 — Falsifier.** *Goal:* a novel call. *Method:* predict an un-tabulated valence or a
paramagnetic/diamagnetic assignment (e.g. a radical) from wake count alone.

## Success criteria

- **PASS (A):** valence of Z=1–18 + octet + B–O/C–F/N–Ne paramagnetism from wake-cancellation with
  no orbitals, plus a correct novel paramagnetic call.
- **QUALIFIED (C):** valences and octet recovered; one period-length symmetry CALIBRATED(1).
  *(Expected landing.)*
- **PENDING (D):** valence tally works for period 2 only; heavier periods qualitative.
- **FAIL (F):** valence/octet cannot be reproduced without subshell filling.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Valence = active-wake count | period-1–3 valences correct | valence needs orbital occupancy |
| Octet = all-paired fixed point | noble gases zero active wakes | octet is an independent postulate |
| Pairing map | O₂ paramagnetic, N₂ not, from lone wakes | paramagnetism needs MO diagram |

## Dependencies

**Upstream:** CH01 (electropause), the period-2 wake-cancel map
([[project_foundational_ontology_influx_monopole]]), APS01 (k-factor radial sizing).
**Downstream:** CH04 (geometry uses the same active/lone wakes), CH02 (transfer follows valence).
**Related:** EMC03 handed redirection; the "Be waits for O" / loosest-dyad notes.
