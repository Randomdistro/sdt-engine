# CH04 — Molecular Geometry (VSEPR) from Wake Balance

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

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

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Equal wakes → solids | 180/120/109.5/90 exact | geometry needs orbital symmetry |
| Lone heavier → compression | 104.5/107/109.5 from one ratio | lone-pair effect is hybridisation artefact |
| Novel outlier | H₂S 92°/PH₃ 93° predicted, not fit | model only fits, doesn't predict |

## Dependencies

**Upstream:** CH01 (wake cancellation, H3), CH03 (which wakes are lone vs bonding), PPT06/APS04
(wake multipole), EMC03 (lone wake stronger). **Downstream:** CH05 (reaction = wake
reconfiguration of these geometries), CH06 (residual wake outside the geometry). **Related:** the
period-2 map ([[project_foundational_ontology_influx_monopole]]).
