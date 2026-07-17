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

---
---

# RUN 2 PROMPT (2026-07-06) — valence from mesh closure: the O₂/N₂ dual gate

> **Author:** J. C. Harvey, Melbourne · **Status:** SPEC (run 2). The run-1 prompt above is the
> historical record and is UNTOUCHED — this section only adds. **No verdict label changes here:**
> M1/M2 stay KILLED-in-static-class until the pre-committed mesh-class run below actually lands.
> **Inherits:** everything the run-1 header inherits, PLUS `Investigations/HUNTER_PROTOCOL.md`
> (§A kill list · §D seven questions · §G mirror incl. G.3) and
> `Investigations/FARMER_PASS_2026-07-03.md` refinement 8 (movement triad; rolling-vs-meshing
> wake firewall; meshing = bond = movement saved; Born = running alignment).

## Standing of the record (the executor reads this before anything else)

- **Run 1** (`CH03_VERDICT.md`): M0 tally 18/18 but LINGUISTIC-capped (capacities CALIBRATED);
  **M1 native filling FAIL 6/8** — the static 1/d seat kernel pairs antipodally at n=2 (Be) and
  n=6 (O); **M2 KILLED-in-static-class at O₂** — predicted diamagnetic, measured paramagnetic
  (χ_mol = +3449×10⁻⁶ cm³/mol). Both failures ran to ground at ONE premise: **ROOT-SEAT** (static,
  simultaneous seat occupancy) — the same root FARMER logged for QM04/05, PPT08, NP10, FLM03.
- **⟐ RE-OPENED notice** (2026-07-06, `CH03_VERDICT.md`, §G.3 premise-class event): the mesh class
  names the missing mechanism — *pairing is a cadence/closure constraint, not a distance choice* —
  and commits the quantitative gate. **This run is the pre-committed mesh-class run that notice
  calls for.** Its Phase A executes exactly the committed gate; nothing is promoted before it runs.
- **FLM14 state** (runs 4–5, `FLM14_VERDICT.md`): the two-channel tour instrument exists (ADJ-11:
  locks + same-tick rigid-cluster kicks inside the tour; centre reading p ≈ +2.04 at β=0.20,
  split-half and seed-2 replicated at the centre) but the **claim was REFUSED** (three blockers
  named per ADJ-12; T_W dependence hardened to dissolution — WAKE-MEMORY debt). The named next
  instrument is **run-6: the memory-free dwell-count measure**. Phase B of this run is BLOCKED on
  it. A Phase-A PASS here does **not** pay the FLM14 re-open condition for M1 — run-6 remains the
  full payer named in the run-1 recovery.

## What run 2 does differently (the error-resistance upgrades over run 1)

1. **Mine before modelling.** Phase 0 is mandatory and gated: the base data of five sibling
   investigations is extracted into RUN_LOG before any ADJ is written. Run 1 built its kernel
   blind; run 2 may not.
2. **One rule, five molecules.** Run 1's two misses shared one premise; the correction must be one
   premise too. Zero per-molecule freedom anywhere in the chain.
3. **The null model is run 1's corpse.** The static 1/d kernel already scored 6/8 with O₂ wrong —
   cite it, do not re-run it.
4. **Contraband check written in.** The rival's machinery (MO aufbau) is banned in-chain; the
   rival's axioms are banned from the gates (GATE-CONTRABAND); convergences are reported, not
   hidden and not borrowed.
5. **Conditional phasing.** Phase B is explicitly blocked on FLM14 run-6; its leads are mined now,
   its gates are scored later. No phase pretends to a licence it does not hold.

## Phase 0 — MANDATORY base-data mining (gate: table in RUN_LOG **before** the ADJ is written)

The executor actively mines the following files and records, in `RUN_LOG.md`, a Phase-0 table:
one row per source, columns = {path · quantity extracted (quoted number or quoted line) · what it
constrains in this run}. **No ADJ, no code, until this table exists.** Disqualified or superseded
numbers are copied WITH their disqualification labels attached (see mandatory clause 2).

| Source | Files (repo-relative) | Extract |
|---|---|---|
| CH03 run 1 (the corpse) | `Investigations/16_Chemistry_and_Molecular_Bonding/CH03_Periodic_Table_and_Valence_from_Shell_Wake_Cancellation/ch03_valence_wakes.py` · `results.txt` · `RUN_LOG.md` · `CH03_VERDICT.md` | the M0 tally arithmetic `active(n)=min(n,2S−n)`; the exact n=2 and n=6 minimum-energy configurations of the 1/d kernel (the null's failure geometry); the committed run-1 gates |
| CH04 VSEPR minimiser | `Investigations/16_Chemistry_and_Molecular_Bonding/CH04_Molecular_Geometry_VSEPR_from_Wake_Balance/ch04_wake_geometry.py` · `results.txt` · `CH04_VERDICT.md` | which geometries the wake-balance minimiser earned vs missed; the angle results any mesh rule must not contradict |
| CH06 residual-wake sums | `Investigations/16_Chemistry_and_Molecular_Bonding/CH06_Hydrogen_Bonding_and_van_der_Waals_from_Residual_Wake/ch06_residual_wake.cpp` · `results.txt` · `CH06_VERDICT.md` | residual-wake magnitudes after pairing — the measured size class a "mesh defect" must map onto |
| NP17 shared-electron machinery | `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/np17_nuclear_packing.cpp` · `NP17_VERDICT.md` | the shared-electron pairing energetics (E = −Σqq·(αℏc)/r, the 137 gear-down) — the precedent for "shared = bond" bookkeeping |
| NP10 run-2 lock ladder | `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/np10_contact_wall.cpp` · `np10_contact_wall_results.txt` · `NP10_VERDICT.md` | the Face-T **(Z−1)! closed-tour lock** (d −1.1% / t +0.9% / α −5.6%, zero constants) and the lock ladder ×1.01/×1.98/×6.35 — the tour-count primitive this run builds with |
| FLM14 instrument state | `Investigations/01_Foundations_and_Lattice_Mechanics/FLM14_Rotating_Spation_Sequential_Occupancy/flm14_form4b.py` · `flm14_form5.py` · `flm14_form4b_results.txt` · `flm14_form5_results.txt` · `FLM14_VERDICT.md` · `RUN_LOG.md` (ADJ-11/ADJ-12) | the two-channel tour architecture (locks + same-tick rigid-cluster kicks); machinery anchors +2.596/+2.040/+1.620; the run-6 named instrument (memory-free dwell measure) and its claim conjunction |
| FARMER refinement 8 | `Investigations/FARMER_PASS_2026-07-03.md` §"Rules refinements", item 8 | the movement triad (PASS/BECOME/PRESS); the firewall (desynchronised rotations ROLL = repulsion; cadence-locked rotations MESH = bond = movement saved); Born = running alignment (dwell statistics of an unterminated search) |

## Phase A — the mesh-closure model (the committed dual gate)

**The premise class this run works in (the correction to ROOT-SEAT):** a shell is not a set of
tenants at seats — it is a **closed tour** (FLM14: the orbital is a sequence; NP10 Face T: the
count of distinct closed tours is (Z−1)!, and it priced the nuclear lock ladder with zero
constants). Two wakes silence each other only when their tours **mesh** — cadence-locked,
fore/aft, on time every pass (FARMER §8: mesh = bond = movement saved; roll = repulsion).
**A shell closes only when its tours mesh completely.** Pairing is therefore a CADENCE/TIMING
constraint, not a distance choice: geometric adjacency — the run-1 kernel's only criterion — is
neither necessary nor sufficient for silence. That single substitution is what run 1's §D
recovery named, and it must carry the whole phase.

**The task:** build ONE closure rule from tour/cadence primitives — candidates are the FLM14
two-channel instrument state (locks + rigid-cluster kicks), FLM07's 1:4 void gearing, and NP10's
(Z−1)! closed-tour counts — commit it in the ADJ **before code**, then score it against the five
homonuclear diatomics. The rule assigns each diatomic an integer count of **residual unpaired
defects** (tours or tour segments that cannot be brought into complete mesh with one identical
partner). The committed qualitative fork from the ⟐ notice is the physics: **N₂ achieves complete
triple-mesh self-closure; O₂ is a structure that cannot fully close with one identical partner.**

**GATE A (the dual gate — committed here, before any code, per the ⟐ notice):** ONE closure
rule — same rule, same constants, ZERO per-molecule freedom — applied to B₂, C₂, N₂, O₂, F₂ must
yield: **O₂ → exactly TWO unpaired defects** (measured anchor: paramagnetic, χ_mol = +3449×10⁻⁶
cm³/mol) **AND N₂ → exactly ZERO** (measured: diamagnetic) **AND**, as the pre-committed
extension, **B₂ paramagnetic · C₂ diamagnetic · F₂ diamagnetic** — five homonuclear diatomics,
one rule, **gate = 5/5 on unpaired-count parity** (zero = diamagnetic vs nonzero = paramagnetic),
with the two named legs exact (O₂ = 2, N₂ = 0). 4/5 is FAIL. Any per-molecule adjustment is FAIL.
Any post-run tolerance change is FAIL.

Measured-anchor table (data boundary — quoted in measured units; executor confirms each value
against a standard table and records the source in RUN_LOG before scoring):

| Molecule | Measured verdict (anchor) | Note |
|---|---|---|
| B₂ | paramagnetic — two unpaired signatures (matrix-isolation ESR) | use the raw ESR verdict; the rival's term-symbol bookkeeping is NOT the anchor |
| C₂ | diamagnetic ground state | |
| N₂ | diamagnetic (χ_mol ≈ −12×10⁻⁶ cm³/mol) | exact-count leg: ZERO defects |
| O₂ | paramagnetic, two unpaired (χ_mol = +3449×10⁻⁶ cm³/mol) | exact-count leg: TWO defects |
| F₂ | diamagnetic | |

**Pre-gate smoke legs (not scored, but a miss = STOP and report, no patching):** H₂ must close
(diamagnetic, bound); He₂ must present no mesh (closed tours already self-silenced — no covalent
closure available). These check the rule's floor before the gate spends it.

**Null model:** run 1's static 1/d seat kernel — already scored **6/8 with O₂ wrong**
(`CH03_VERDICT.md`, M1/M2 rows). **Cite it; do not re-run it.** The mesh rule must beat it on the
five-molecule gate, and specifically must repair the two misses that share its premise.

**CONTRABAND CHECK (written into this phase, executed and recorded before code):** the closure
rule may NOT import MO theory's aufbau/orbital machinery — orbital energy ordering, σ/π level
diagrams, spin-filling rules — that is the rival's machinery (BORROW-SMUGGLE, §A). The rule must
be built from tour/cadence primitives: FLM14 two-channel instrument state, FLM07 1:4 gearing,
NP10 (Z−1)! closed-tour counts. Symmetrically (GATE-CONTRABAND, §A/§G.2): every kill condition in
this phase must trace to a measured anchor or a pre-committed native criterion, never to "the
rival forbids it". If the finished mesh rule turns out to reproduce the rival's σ/π ordering as
an OUTPUT, that is **reported as convergence** — stated openly in the verdict, never hidden, and
never used as evidence in the chain.

## Phase B — M1 native filling re-run in the tour class (CONDITIONAL — currently BLOCKED)

**Blocking condition, explicit:** Phase B's gated re-run of M1 (native filling of Z=1–18 inside
the rotation/tour class) **does not execute until FLM14 run-6 lands its memory-free dwell rule**
(the dwell-count residence measure, seed-1 AND seed-2, claim conjunction unchanged — a new
pre-committed FLM14 ADJ is required there; it cannot be written from here). If run-6 kills the
dwell measure, Phase B stays closed and M1 remains killed-in-static-class with its re-open
condition unpaid. If run-6 lands, Phase B is specced as run 3 with its own ADJ and gates. Nothing
in this phase scores a gate now.

**What runs NOW — leads-mining (builds the run-3 target table, no verdicts):** the executor
converts each periodic-geography lead recorded in the ⟐ notice and FARMER §8 into a TESTABLE
structural statement with a NAMED observable, and tabulates the measured anchor for each (value +
source recorded in RUN_LOG; indicative values below must be confirmed against standard tables):

| Lead (from the ⟐ notice / FARMER §8) | Convert to testable statement | Named observable (measured anchor to tabulate) |
|---|---|---|
| **Carbon = 4-hook/4-aperture tetrahedral symmetry maximum** | C's four hooks admit four simultaneous cadence-locked meshes at tetrahedral separation — the symmetry maximum of the period-2 rim | CH₄ bond angle (109.47°, four equivalent bonds); C₂'s diamagnetism despite four hooks; diamond's tetrahedral lattice |
| **N₂ triple mesh self-closure** | one identical partner suffices to close ALL of N's open cadence — complete triple mesh, zero residual | N₂ bond energy (≈ 945 kJ/mol — anomalously large vs single-mesh diatomics); N₂ chemical inertness at ambient conditions |
| **Li = lone rotor on closed core** | one rotor riding an already-closed (self-meshed) core: cheap to lend, catastrophic to break the core | Li ionization step IE₁ vs IE₂ (≈ 5.39 eV vs ≈ 75.6 eV, a ×14 cliff); Li₂'s weak bond (≈ 105 kJ/mol) vs H₂ (≈ 436 kJ/mol) |
| **P = N's hook count without N's closure attitude at the period-3 rim — angle is the premium** | same hook count, wrong rim angles: P cannot reach N's triple self-mesh, so it spends hooks at strained angles instead (FARMER refinement 2: contact ANGLE is the scarce resource) | P₂ vs N₂ bond-energy ratio (≈ 490/945 ≈ 0.52 — the triple-mesh premium P cannot collect); P₄ tetrahedral allotrope with 60° angles (strain accepted to trade angle for closure) vs the non-existence of ambient N₄; white-P reactivity vs N₂ inertness |

Deliverable of Phase B (this run): the four rows above expanded into a run-3 target table in
`RUN_LOG.md` — statement · observable · confirmed measured anchor · source — **no gates scored in
this phase.**

## Mandatory clauses (the constitution of this run — each binding as written)

1. **Phase 0 base-data mining is mandatory** with the file paths as listed above (CH04 VSEPR
   minimiser results, CH06 residual-wake sums, NP17 shared-electron machinery, NP10 run-2 lock
   ladder, FLM14 instrument state). No ADJ, no code, before the Phase-0 table is in RUN_LOG.
2. **Harvey's disqualified-data fallback:** run-1's static-seat kernel outputs and any quarantined
   candidates may be consulted as LEADS; their disqualification labels travel with them wherever
   they are copied; nothing is promoted from lead to input without a derivation.
3. **ADJ-before-code:** the closure rule, all gates, the smoke legs, and any scan grid go into
   `RUN_LOG.md` as a numbered ADJ entry BEFORE any code is written.
4. **Gates are never widened.** Committed thresholds are immutable post-run; RETRO-PASS is a §A
   instant fail.
5. **§D seven questions on any FAIL/KILL/OPEN/DEFER** (HUNTER §D = `PROMPT_EXECUTION_PROTOCOL.md`
   §8), graded RECOVERED / PARTIAL / NO RECOVERY, with the cascade root run to ground.
6. **GATE-CONTRABAND check** (HUNTER §A + §G.2) executed on every kill condition of this prompt
   before coding, result recorded: a gate that enforces a rival's axiom rather than a measured
   anchor is itself killed — kill the gate, not the route.
7. **NO G, no M, no GM anywhere in-chain.**
8. **Never "charge radius"** — boundary/surface/displacement radius only.
9. **No borrowed units** — no Bohr magnetons, no μ_B, no imported yardsticks in the chain.
   Magnetic susceptibilities quoted as measured anchors in their measured units (cm³/mol) are
   fine — that is the data boundary, not a borrow.
10. **Results = teed stdout:** the tool prints everything it scores; stdout is teed to a results
    `.txt` committed alongside; **exit-code honesty** (nonzero exit on FAIL — no cosmetic exit 0).
11. **Machinery anchors for any reused code:** any machinery inherited from run 1 or FLM14 must
    reproduce its source run's published numbers to **1e-6** before it is used here, and the
    anchor check is printed in the results.
12. **`PYTHONIOENCODING=utf-8`** set for any Python tool (Windows console; protects the teed
    record).

## Pre-Run Commitment Block (copy to `RUN_LOG.md` as the run-2 ADJ before coding)

```markdown
## Pre-Run Commitments — CH03 RUN 2 (mesh closure)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list — any entry documented]
- Closure rule (ONE, stated in full before code): [the rule]
- Primitives used: FLM14 two-channel state / FLM07 1:4 gearing / NP10 (Z−1)! tours — cite which
- GATE A: 5/5 parity on {B₂,C₂,N₂,O₂,F₂} + exact counts O₂=2, N₂=0 — 4/5 is FAIL
- Smoke legs: H₂ closes (diamagnetic, bound) · He₂ no mesh — miss = STOP, report, no patch
- Null (cited, not re-run): run-1 static 1/d kernel, 6/8, O₂ wrong
- Contraband check result: [gates traced to anchors — statement]
- Phase B: BLOCKED on FLM14 run-6; leads-mining only, no gates
- Forbidden: widen gates; per-molecule freedom; MO aufbau in-chain; RETRO-PASS; PLUG;
  seeding from electron configuration then claiming NATIVE
```

## Failure discipline (extends the run-1 pivot table; nothing there is loosened)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| GATE A scores 4/5 or worse | §D seven questions; trace which molecule broke the rule and to which premise | **OPEN or KILL the mesh-closure rule in this class** — record the premise class and the re-open condition per §G.3 | re-scoring with a "variant" rule; per-molecule freedom; widening to "4/5 acceptable" |
| Rule only lands by importing MO ordering | strip the import; re-derive from tour/cadence primitives | **BORROW — label it, do not promote** | hiding the import; renaming aufbau as "cadence order" |
| O₂/N₂ legs pass but an extension molecule fails | report the split honestly; §D on the extension leg | OPEN — the extension trio was pre-committed; a partial dual-gate is NOT the ⟐ notice's gate | promoting the dual legs alone as if the gate passed |
| FLM14 run-6 kills the dwell measure | Phase B stays closed; record it | M1 remains killed-in-static-class, re-open condition unpaid | running Phase B anyway on the refused instrument |

**Verdict line (mandatory, HUNTER format):** Prompt completion [A–F] · Physics class [NATIVE /
CONVERGENCE / DEGENERATE / BORROW / KILLED / OPEN] · Recovery [RECOVERED / PARTIAL / NO RECOVERY]
· Cascade root [id or none]. Convergence with the rival's σ/π ordering, if found, is REPORTED in
this line as convergence.

---

*CH03 RUN 2 · 2026-07-06 · J. C. Harvey · spec only — execute with `PROMPT_EXECUTION_PROTOCOL.md`
+ `Investigations/HUNTER_PROTOCOL.md`; labels change only when the run lands.*
