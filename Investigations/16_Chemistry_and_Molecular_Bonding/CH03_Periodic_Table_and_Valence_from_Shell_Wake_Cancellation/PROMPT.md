# CH03 — Periodic Table & Valence from Shell Wake-Cancellation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether periodicity, valence number, and the octet rule can be
   derived from the period-2 wake-cancel map (paired fore/aft wakes silent, lone wakes active) —
   so that an atom's chemistry is set by its count of **active (uncancelled)** wakes — with **no
   orbitals, no subshells, no Aufbau wavefunction**.
2. **Why does it matter?** — It turns the B–O / C–F / N–Ne pairing note
   ([[project_foundational_ontology_influx_monopole]]) into the explanation of the table *itself*;
   it feeds CH04 (bond geometry uses the same active/lone wakes) and CH02 (transfer follows
   valence); valence is the bonding driver for everything downstream.
3. **How will we find out?** — Gated phases in §④: a wake tally for Z=1–18, the octet as the
   all-paired fixed point, the pairing map checked against measured paramagnetism, sized by APS01
   k-factors — native wake mechanism established *before* any orbital picture is invoked.
4. **What would prove us wrong?** — §⑧ numeric triggers: valence/octet that cannot reproduce
   without subshell filling, or O₂/N₂ paramagnetism coming out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation here is **generating the valence numbers and the octet from the
wake-pairing combinatorics** — the period-2 fore/aft cancellation symmetry — **not** reading them
off a standard electron-configuration table and re-narrating them in wake language.

> **If the wake tally only reproduces the textbook valences by being seeded from the known
> electron configuration / subshell-filling order, that is a re-labelling, not a derivation — it
> caps the grade at C.**

The period-length symmetry (the count of wake slots per period) **may be CALIBRATED(1)** — if so,
declare it explicitly in the Pre-Run Commitment Block and the verdict. Everything else must fall
out of the combinatorics. The O₂-paramagnetic / N₂-diamagnetic split must come **out of** lone-wake
counting, never be assumed as an input.

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

| Test | Predicted outcome | If FAIL (kill trigger) |
|------|-------------------|------------------------|
| Valence = active-wake count | period-1–3 valences correct from the pairing tally | **any period-1–3 valence wrong ⇒ KILL valence = active-wake** (valence needs orbital occupancy) |
| Octet = all-paired fixed point | He/Ne/Ar carry zero active wakes | **any noble gas shows nonzero active wakes ⇒ octet is an independent postulate** |
| Pairing map → paramagnetism | O₂ paramagnetic, N₂ diamagnetic, from lone-wake count | **O₂ predicted diamagnetic or N₂ paramagnetic ⇒ KILL pairing map** (needs MO diagram) |
| Firewall (anti-tautology) | valence numbers fall out of the period-2 pairing combinatorics alone | **valences only reproduce when the tally is seeded from the known electron config ⇒ re-labelling, cap at C** |

## Dependencies

**Upstream:** CH01 (electropause), the period-2 wake-cancel map
([[project_foundational_ontology_influx_monopole]]), APS01 (k-factor radial sizing).
**Downstream:** CH04 (geometry uses the same active/lone wakes), CH02 (transfer follows valence).
**Related:** EMC03 handed redirection; the "Be waits for O" / loosest-dyad notes.
---

## Questions This Opens *(generative — log new ones in `CH03_VERDICT.md`)*

1. Do the period lengths 2, 8, 18, 32 fall out of the wake-slot symmetry **without** being put in
   by hand — i.e. is the 2n² progression *derivable* from the fore/aft cancellation combinatorics?
2. Are the transition-metal anomalies (Cr, Cu) **wake-cancellation frustration** (a geared
   near-degeneracy between two pairings) rather than ad-hoc "orbital exceptions"?
3. Does the wake-pairing tally predict the ionization-energy **zig-zags** natively — the B<Be and
   O<N dips — as the cost of breaking versus exposing a paired wake?
4. Does the **active-wake count** predict magnetic moments *quantitatively*, expressed in
   SDT-native yardsticks (electron-wake / koppa units — **not** Bohr magnetons)?
5. Is the electronegativity trend across a period just the **active-wake hunger** — the drive of an
   unpaired wake to recruit a partner — so the trend needs no separate "charge" parameter?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 standard valence correct for ALL Z=1–18 · P2 He/Ne/Ar emerge as zero-active-wake (octet reproduced as rule) · P3 O₂ paramagnetic + N₂ diamagnetic from lone-wake count, period lengths 2/8/8 · P4 novel para/diamagnetic call correct
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Wake tally only matches when seeded from electron config | re-derive valence from period-2 pairing combinatorics alone | **OPEN/KILL** if irreducible | re-label config as 'wake count', claim NATIVE |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · seeding the wake tally from the known electron configuration then claiming NATIVE · subshell/Aufbau filling in any native chain.

---

*CH03 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
