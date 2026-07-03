# CH02 — Ionic & Metallic Bonding from Electropause Transfer

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the ionic bond can be derived as an electropause handed off
   *entirely* to the partner and the metallic bond as electropauses *delocalised* into a lattice
   sea — recovering NaCl's lattice energy (~787 kJ/mol) and a metal's bonding radius from
   electropause/occlusion balance, with NO charge substance ("charge" = handed redirection of the
   convergent phase, no orbitals, no band-theory wavefunctions).
2. **Why does it matter?** — CH02 is the second primary-bond branch off CH01 (covalent = shared
   electropause): ionic = full handoff, metallic = delocalised sea. The metallic sea is *literally*
   the conduction substrate of CM02 downstream — one pressure must yield both cohesion and
   conductivity — and the transfer criterion makes the electronegativity ordering fall out as a
   convergence-well-depth ordering.
3. **How will we find out?** — Gated phases in §④: (P1) transfer criterion from APS01 well depths,
   (P2) NaCl lattice energy as a geometric Madelung-analogue occlusion sum, (P3) metallic
   delocalised-pressure balance, (P4) one novel lattice energy — native mechanism established
   BEFORE importing any Coulomb constant as a primitive or touching rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with concrete numeric triggers: wrong
   ionic/covalent split, lattice energy that cannot cohere without importing the Coulomb (or
   literature Madelung) constant as a fitted primitive, wrong sign, or post-hoc tuning of the
   occlusion-pressure scale to hit 787 kJ/mol (IDENTITY-PASS).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), logged in `CH02_VERDICT.md`.

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is the **geometric occlusion sum** over the rock-salt lattice (a
Madelung-analogue computed from lattice *geometry*) together with the **well-depth transfer
criterion** — NOT importing the Coulomb constant or the literature Madelung constant as a fitted
primitive and reading 787 kJ/mol back off it. State plainly: **importing the Coulomb constant (or
the literature Madelung constant) as a primitive caps the grade at C — it is the textbook identity,
not the SDT derivation.** The occlusion-pressure scale MAY be CALIBRATED(1), but it must be declared
in the Pre-Run Commitment Block; matching the measured lattice energy by tuning that scale post-hoc
is forbidden (IDENTITY-PASS).

## Question

CH01 derived the covalent bond as a **shared** electropause. The other two primary bonds are the
same boundary handled differently. **Can the ionic bond be derived as an electropause handed off
*entirely* to the partner, and the metallic bond as electropauses *delocalised* into a shared
lattice sea — recovering NaCl's lattice energy and a metal's bonding radius from electropause
balance, with no charge substance, no orbitals, no band-theory wavefunctions?** "Charge" here is
only the handed redirection of the convergent phase ([[project_cq47_repulsion_inverse]]); the
ion's "+/−" is which way its convergent phase is redirected after the handoff.

## SDT mechanism & hypotheses

When one atom's electropause can sit *more deeply* in a neighbour's convergence well than in its
own, the electropause migrates: the donor is left with a tighter core electropause (the cation),
the acceptor gains an extra outer one (the anion). The bond is then the residual occlusion balance
([[law_III]]) between the two reorganised cores at their equilibrium separation. In a metal the
outermost electropauses cannot settle on any single host — they **delocalise** into a lattice-wide
shared sea, the same merge as CH01 but periodic, which is exactly the conduction substrate of CM02.

- **H1 (transfer):** the electropause migrates iff the partner well is deeper; predicts which
  pairs go ionic vs covalent (electronegativity ordering as well-depth ordering).
- **H2 (lattice energy):** ionic cohesion = summed occlusion balance over the lattice; recover
  NaCl ~787 kJ/mol with the Madelung sum re-read as a geometric occlusion sum, no Coulomb constant
  imported as a primitive.
- **H3 (metallic sea):** delocalised electropauses give a cohesive energy and equilibrium R for
  Na/Cu from a uniform shared-electropause pressure; ties directly to CM02 conduction.

## Strategy

**Phase 1 — Transfer criterion.** *Goal:* predict ionic vs covalent from well depths. *Method:*
compare donor self-well vs acceptor well using APS01 core radii. *Success:* correct ionic/covalent
split for ~15 reference pairs (NaCl, MgO ionic; H₂, CH₄ covalent).

**Phase 2 — NaCl lattice energy.** *Goal:* cohesive energy. *Method:* sum the pairwise occlusion
balance over the rock-salt lattice (geometric Madelung-analogue). *Success:* lattice energy within
~15% of 787 kJ/mol; correct sign.

**Phase 3 — Metallic sea.** *Goal:* cohesive E and R for one metal. *Method:* uniform delocalised
electropause pressure balanced against core occlusion. *Success:* Na bonding radius and cohesive
energy within ~25%; hands the same field to CM02.

**Phase 4 — Falsifier.** *Goal:* one novel number. *Method:* predict an un-calibrated lattice
energy (e.g. KCl or MgO) or a metallic radius down a group from APS01 k-factors.

## Success criteria

- **PASS (A):** transfer criterion + NaCl lattice energy + metallic R from one field, ≤1 flagged
  constant, plus a correct novel lattice energy.
- **QUALIFIED (C):** NaCl and Na recovered with the occlusion-pressure scale CALIBRATED(1).
  *(Expected landing.)*
- **PENDING (D):** transfer criterion shown; lattice energy only order-of-magnitude.
- **FAIL (F):** cannot cohere a lattice without importing the Coulomb constant as a primitive or a
  band wavefunction.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Transfer = deeper-well migration | ionic/covalent split correct for >=13 of 15 ref pairs (NaCl, MgO ionic; H₂, CH₄ covalent) | split wrong for >2 of 15 pairs ⇒ KILL transfer criterion (electronegativity isn't well depth) |
| Lattice = geometric occlusion sum | NaCl lattice energy 787 kJ/mol within 15%, correct (cohesive) sign | >15% off 787 kJ/mol after pivot ⇒ OPEN; wrong sign ⇒ KILL |
| Metallic = delocalised sea | Na bonding R and cohesion within 25% of measured from one uniform pressure | >25% off after pivot ⇒ OPEN; needs band theory to cohere ⇒ KILL metallic-sea hypothesis |
| No imported Coulomb primitive (firewall) | lattice energy emerges from the geometric occlusion sum alone | cohesion only matches when the Coulomb/Madelung constant is fed in ⇒ IDENTITY-PASS, capped at C |

## Dependencies

**Upstream:** CH01 (shared electropause), EMC04 (electropause/P_eff), EMC03 (handed redirection sign).
**Downstream:** CM02 conduction (the metallic sea is its substrate), CH05 energetics.
**Related:** APS01 k-factor core radii; the Li–Be "loosest dyad" handoff note
([[project_foundational_ontology_influx_monopole]]).
---

## Questions This Opens *(generative — log new ones in `CH02_VERDICT.md`)*

1. Is electronegativity *literally* the convergence-well depth — does the Pauling scale fall out of
   APS01 k-factor well depths as a one-to-one ordering?
2. Is there a continuous covalent-to-ionic spectrum set by the well-depth *difference* (partial
   ionic character = partial handoff), rather than a binary transfer?
3. Does the same delocalised-electropause "sea" that gives metallic cohesion ALSO give CM02's
   conductivity — one pressure, two observables — and can both be read off a single field?
4. What sets the occlusion-pressure scale — is it derivable from Law III geometry alone (zero
   calibrated params), or is the CALIBRATED(1) floor irreducible?
5. Does the lattice-energy occlusion sum predict the Born–Landé repulsion exponent natively, rather
   than taking it as an empirical fit?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 ionic/covalent split correct for >=15 ref pairs · P2 NaCl lattice energy within 15% of 787 kJ/mol, correct sign · P3 Na radius+cohesion within 25% · P4 novel lattice energy (KCl/MgO) within 20%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Lattice sum won't cohere without Coulomb primitive | re-derive pairwise occlusion balance from Law III geometry | **OPEN** ionic cohesion | import Coulomb constant, call it NATIVE |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · importing the Coulomb/Madelung constant as a primitive then claiming NATIVE · band-theory wavefunctions in any native chain.

---

*CH02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
