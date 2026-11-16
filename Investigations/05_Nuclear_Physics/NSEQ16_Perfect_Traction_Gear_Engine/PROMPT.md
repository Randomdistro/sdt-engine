# NSEQ16 — Perfect traction-gear engine (construction verification) (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**Deferred:** gates G0–G7 (bipartite p–n contacts, zero contact slip, Möbius reversal control) need `traction-gear-engine.js` driven in full by node.

## 2. New data and what it teaches (2026-10-10 to 2026-10-12)
- **The live sequencer was driven by node on 2026-10-10/11** (records: NP17 addendum; `NP17_.../CASCADE_ASSESSMENT_2026-10-11.md`; PPT18 stage 1). Findings:
  - The light seeds ²H, ³H and ³He are **CALIBRATED(8/9)**, fitted exactly to their own B, μ and Q.
  - The zero-fit universal ledger (wake contact coupling × αħc/R_p × contraction) is **B6 on all 250 stable nuclides**: right order, with ratio CV 8.5%, missing a factor that grows with coordination.
  - **Wrong-sign binding** in 23 of 173 isotope steps: contraction multiplies binding and also lowers the wake coupling.
  - Every A ≥ 4 graph is **one α 4-ring plus a tree** (E = A).
  - μ(⁴He) = 1.65 μN against 0.
  - The H1 nucleon envelope reaches **1.085 R_p**, using untraced constants (0.06 fm strand, 5.28 fm helix). Canon-consistent sizes (PPT18 stage 2a): R = 0.444 fm and a = 0.397 fm for (4,5).
  - **No EC grammar:** ⁷Be, ¹¹C and ⁸B are refused.
- The braid repair's registered sizes (R = 0.62, a = 0.22, b = 0.16 R_p) violate canon's aspect law for (4,5) (2.82 against 1.12; PPT18 K2).

## 3. Next round (registered order)
1. Drive G0–G7 by node on the current engine version, using the `selfTest` hooks plus contact-slip controls. These are constructions: no physics content until a value law exists.
2. Add **G8 (registered now): canon consistency.** Nucleon envelope ≤ R_p; aspect R/a = √(q/p) for the declared winding; every size traced to a record. Currently **not met** (PPT18).
3. A proposal (Release is not edited) to replace the H1 constants with canon-consistent sizes once Harvey rules the winding.

## Prohibitions
- No census over candidate predictors.
- Grammar counts are not evidence (NP24).
- No data substitution without a label.
- Release is read, never edited (proposals only).
- The word "charge" is not used.

---

## Previous specification (kept as written)

# NSEQ16 — Contact Perfect-Traction Orbital Gear Engine

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-15  
**Status:** PRE-REGISTERED · PARALLEL EXPERIMENT · CANON EDITS: NONE

> **Historical protocol.** The implementation defects found after this seal
> are repaired under [PROMPT_REPAIR.md](PROMPT_REPAIR.md). The G-gate decision
> labels below are retained as provenance and are withdrawn from current use.

## Question

Can the constitutional alpha/deuteron/triton grammar be rendered as one
contact gear assembly in which every listed contact is proton-neutron,
all nucleon rims share one toroidal period, and counter-rotation gives zero
contact-point slip?

This experiment is parallel to NSEQ05. It does not replace the registered
pure-shell packer. NSEQ05 coordinates are unavailable to the forward
construction and are loaded only for the post-seal comparison.

## Frozen inputs

- `R_p` and the proton `(p,q)=(2,3)` mode from the engine data.
- For `Z >= 2`: `n_d = 3Z-A-2`, `n_t = A-2Z`.
- Special seed units: H-1 is one proton, H-2 is `p-n`, H-3 is `n-p-n`.
- Alpha is a `p-n-p-n` four-cycle; deuteron is `p-n`; triton is `n-p-n`.
- Like-like contact is prohibited. Every registered contact must be `p-n`.
- All rim contacts use centre separation `2R_p`. No binding energy is
  assigned to a rendered contact.

The whole-range isotope sequence is:

```text
H-1, H-2, H-3, He-4, Li-7, Be-9, B-11, C-12, N-14, O-16
```

For Li through O, the grammar supplies one through six satellite modules.
Their unlabeled maximum-separation seat controls are respectively polar,
antipodal, equatorial triangle, tetrahedron, trigonal bipyramid and
octahedron. Element names do not enter the seat generator.

## Kinematics

The assembly has a common rigid toroidal phase. Proton and neutron rims have
equal angular-speed magnitude and opposite hand. For a contact normal
`n_ij`, the registered no-slip residual is

```text
u_i = omega_i x (+R_p n_ij)
u_j = omega_j x (-R_p n_ij)
slip_ij = |u_i-u_j| / (omega R_p)
```

The common rigid motion cancels because both descriptions refer to the same
contact point. Relative local motion is allowed only if it closes on the same
master period.

## Four-tour and electron candidates

The pulled four-tour ring is frozen as

```text
phi(u) = 4u
psi(u) = pi + u
r(u) = ((R+a cos psi) cos phi,
        (R+a cos psi) sin phi,
         a sin psi),  0 <= u <= 2pi
```

It visits inner, under, outer and over after successive major tours. This is
a `(4,1)` torus curve, not the canonical `(2,3)` trefoil. The two remain
separate selectable candidates unless a deformation proof relates the
physical constructions.

Each neutron carries an internal Möbius director control. Its centreline
closes after `2pi`; its director reverses after `2pi` and closes after `4pi`.
This is a kinematic orientation control, not a derived electron force.

Interleaving is reported as a geometric contact ledger. NSEQ15 did not derive
a MeV scale from packed contact length, so NSEQ16 must not convert contact
count, shared arc or displayed overlap into mass defect energy.

## Validation gates

All tolerances are fixed before the instrument is written.

1. **G0 — inventory.** Every case has exactly `A` nucleons and `Z` protons;
   module counts equal the constitutional grammar.
2. **G1 — seat known answers.** Minimum angles for 2–6 seats reproduce
   `180°, 120°, acos(-1/3), 90°, 90°` within `1e-10` rad.
3. **G2 — contact graph.** Every nontrivial assembly is connected and
   bipartite; every edge is `p-n`; every nucleon has at least one contact.
4. **G3 — rim contact and traction.** Every listed contact distance is
   `2R_p` within `1e-10 R_p`; maximum normalized slip is `<1e-10`.
5. **G4 — common clock.** Every nucleon has the same toroidal speed magnitude;
   all signed phases close after one common period within `1e-10`.
6. **G5 — four-tour curve.** Endpoint closure is `<1e-10 R_p`; the quarter
   states occur in the order inner, under, outer, over.
7. **G6 — Möbius action.** Position closes and the director reverses at
   `2pi`; both position and director close at `4pi`, each within `1e-10`.
8. **G7 — determinism and resolution.** Repeated construction is byte-stable;
   doubling curve resolution changes closure metrics by `<1e-12`.
9. **G8 — discriminatory comparison.** After sealing G0–G7, run the same
   traction evaluator on NSEQ05 for He through O. If both geometries satisfy
   the same constraints, the placement is `UNDERDETERMINED`; it is not
   promoted merely because both can roll.

## Populated rejection controls

- A transverse same-handed contact must have nonzero slip and fail G2.
- Replacing one `p-n` edge by a like-like edge must invalidate bipartiteness.
- Removing the Möbius half-twist must fail the `2pi` reversal control.
- A topology label that equates `(4,1)` with `(2,3)` fails G5.

## Decision

- G0–G7 all pass and NSEQ05 fails the same frozen evaluator:
  `TRACTION_GEOMETRY_CANDIDATE`; retain as parallel pending independent data.
- G0–G7 all pass and NSEQ05 also passes:
  `TRACTION_CONSISTENT_UNDERDETERMINED`.
- Any G0–G7 failure: `TRACTION_ENGINE_REJECTED`, naming the failed gate.

No result in this experiment authorizes an edit to `laws.hpp`.
