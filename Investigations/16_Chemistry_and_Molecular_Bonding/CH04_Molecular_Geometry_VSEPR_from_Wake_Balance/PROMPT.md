# CH04 — Molecular Geometry (VSEPR) from Wake Balance

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the full VSEPR ladder (104.5° / 107° / 109.5° / 180° / 120° / 90°) can be derived across many molecules as wake-torque equilibria around a central atom — lone-pair wakes heavier than bond-pair wakes — with **no sp³/sp²/sp hybridisation invoked anywhere as mechanism**.
2. **Why does it matter?** — Geometry is just the angular configuration that zeroes the net wake torque, deepening CH01-H3; it feeds CH05 (reaction geometry deformation) and CH06 (residual-wake directions), and proves molecular shape needs no hybrid orbitals at all.
3. **How will we find out?** — Gated phases in §④: symmetric solids from equal wakes, the lone-pair compression ladder with one ratio, an extended hypervalent + multiple-bond set, then a novel small-angle outlier — running the native minimiser **before** any orbital-symmetry import.
4. **What would prove us wrong?** — §⑧ numeric triggers: angles unreproducible without hybridisation; the compression needing a second knob; the novel outlier missed.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is **minimising the summed pairwise wake-torque over unit direction
vectors and getting the angles OUT** — with exactly **ONE** ratio `w_lone/w_bond` as the only knob.
The trivial identity to avoid: assuming the tetrahedral / trigonal / octahedral target angles (or
declaring sp³ = 109.5° by fiat), or adding a second fitted parameter per molecule.

> **If the 104.5/107/109.5 ladder only appears because a second knob was tuned, or because
> hybrid-orbital angles were assumed, that is a fit, not a derivation — caps the grade at C.**

The single `w_lone/w_bond` ratio is **CALIBRATED(1)**; it must reproduce the **whole** ladder, and
the novel outlier (Phase 4) must be **predicted with that same ratio, not refit**.

## Question

CH01-H3 sketched bent water from wake cancellation. **Can the full VSEPR ladder —
104.5° / 107° / 109.5° / 180° (linear) / 120° (trigonal) / 90°–120° (trigonal bipyramidal) / 90°
(octahedral) — be derived across many molecules as wake-torque equilibria around a central atom,
with lone-pair wakes weighted more heavily than bond-pair wakes, and with no sp³/sp²/sp
hybridisation invoked anywhere?** Geometry is the angular configuration that zeroes the net wake
torque, not a hybrid orbital set.

## SDT mechanism & hypotheses

Around a central atom each bonding direction carries a bond-pair wake (shared with a second
nucleus, partially cancelled) and each lone direction carries a lone-pair wake (no second nucleus,
fully active, therefore **stronger**, [[project_cq47_repulsion_inverse]]). These active wakes repel
by occlusion ([[law_III]]); the molecule settles where the summed pairwise wake interaction is
minimised — the wake-torque equilibrium. Because lone wakes are heavier, they open wider and
squeeze the bond angles below the symmetric value: 109.5° (0 lone) → 107° (1 lone) → 104.5°
(2 lone), the classic compression, with a single lone/bond weight ratio as the only knob.

- **H1 (equilibrium = torque zero):** geometry minimises Σ pairwise wake interaction over the unit
  direction vectors; the symmetric solids (linear/trigonal/tetrahedral/bipyramidal/octahedral)
  fall out for all-equal wakes.
- **H2 (lone-pair weighting):** one ratio w_lone/w_bond > 1 reproduces the 109.5/107/104.5 ladder
  and the analogous compressions in PCl₅, SF₄, ClF₃, XeF₄.
- **H3 (multiple bonds):** a double/triple bond is a fatter shared wake (heavier than a single),
  widening its angle — predicts the O=C=O linearity and H₂C=O ~120° opening order.

## Strategy

**Phase 1 — Symmetric solids.** *Goal:* recover ideal geometries. *Method:* minimise Σ wake
interaction for N equal wakes (N=2…6). *Success:* 180/120/109.5/90 within <1° for equal wakes.

**Phase 2 — Lone-pair ladder.** *Goal:* the compression series. *Method:* one w_lone/w_bond ratio.
*Success:* H₂O 104.5°, NH₃ 107°, CH₄ 109.5° to ≤1° with a single CALIBRATED(1) ratio.

**Phase 3 — Extended set.** *Goal:* hypervalent + multiple-bond cases. *Method:* same minimiser,
same ratio, fatter wakes for multiple bonds. *Success:* SF₄ seesaw, ClF₃ T-shape, XeF₄ square,
CO₂ linear, H₂CO ~120° all qualitatively + within a few degrees.

**Phase 4 — Falsifier.** *Goal:* a novel angle. *Method:* predict an angle not used to set the
ratio (e.g. H₂S 92°, PH₃ 93°, or OF₂ 103°) — these small-angle outliers are the real test.

## Success criteria

- **PASS (A):** symmetric ladder + lone-pair compression + the extended set with one ratio, plus a
  correct novel angle (H₂S/PH₃-class outlier).
- **QUALIFIED (C):** 104.5/107/109.5 + symmetric solids with the ratio CALIBRATED(1); extended set
  qualitative. *(Expected landing.)*
- **PENDING (D):** symmetric solids only; lone-pair compression qualitative.
- **FAIL (F):** angles cannot be reproduced without hybridisation.

## Falsification tests

| Test | Predicted outcome | If FAIL (numeric kill trigger) |
|------|-------------------|--------------------------------|
| Equal wakes → solids | 180/120/109.5/90 exact | symmetric solids off >1° for equal wakes ⇒ geometry isn't wake-torque |
| Lone heavier → compression | 104.5/107/109.5 from one ratio | needs a second knob to hit 104.5/107/109.5 ⇒ lone-pair effect is a hybridisation artefact |
| Novel outlier | H₂S 92°/PH₃ 93° predicted, not fit | novel H₂S/PH₃ angle missed by >~5° with the fixed ratio ⇒ fit-only |
| Firewall — one ratio does it all | the SAME `w_lone/w_bond` yields the whole ladder AND the novel angle | any second knob, or a per-molecule refit of the ratio, is needed ⇒ caps the grade at C (fit, not derivation) |

## Dependencies

**Upstream:** CH01 (wake cancellation, H3), CH03 (which wakes are lone vs bonding), PPT06/APS04
(wake multipole), EMC03 (lone wake stronger). **Downstream:** CH05 (reaction = wake
reconfiguration of these geometries), CH06 (residual wake outside the geometry). **Related:** the
period-2 map ([[project_foundational_ontology_influx_monopole]]).
---

## Questions This Opens *(generative — log new ones in `CH04_VERDICT.md`)*

1. Is `w_lone/w_bond` **derivable** from EMC03 — the ratio of a fully-active lone wake to a
   partly-cancelled bond wake — giving **zero** calibrated parameters? [[project_cq47_repulsion_inverse]]
2. Does the same minimiser predict bond-**LENGTH** ratios, not just angles, from the same wake field?
3. Do the small-angle outliers (H₂S 92°, PH₃ 93°) trace to **heavier central atoms with weaker bond
   wakes** — a k-factor / APS01 trend rather than a separate effect?
4. Does the wake-torque field predict **ring strain** and other non-VSEPR distortions where the
   classic rules struggle?
5. Can the minimiser handle **multiple central atoms** (conformational / dihedral angles) from the
   same wake field, extending CH04 to whole molecular conformations?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 symmetric solids 180/120/109.5/90 within <1° for equal wakes · P2 H2O 104.5°/NH3 107°/CH4 109.5° to <=1° with ONE w_lone/w_bond · P3 SF4/ClF3/XeF4/CO2/H2CO within a few ° same ratio · P4 novel outlier (H2S ~92° or PH3 ~93°) within a few °, NOT refit
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Ladder needs a 2nd knob beyond `w_lone/w_bond` | re-derive lone-wake weight from EMC03 (fully-active vs partly-cancelled) | **OPEN/KILL** if irreducible | add per-molecule fudge, claim one-ratio |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · assuming hybrid-orbital target angles then claiming NATIVE · adding a 2nd fitted knob beyond `w_lone/w_bond` · refitting the ratio on the Phase-4 novel angle.

---

*CH04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
