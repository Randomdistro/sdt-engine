# NSEQ16 repair — Atomicus contact construction

**Author:** James Christopher Tyndall, Melbourne  
**Registered:** 2026-08-15, before repair instrumentation  
**Status:** PRE-REGISTERED REPAIR · NSEQ05 PROMOTION WITHDRAWN

## Defect that triggered the repair

The NSEQ05 website packer cannot serve as the SDT geometry. It:

- assigns octahedral, icosahedral, cuboctahedral and Fibonacci shell seats;
- advances arbitrary radial tiers instead of solving rim contact;
- records a nearest graph edge without requiring that edge to touch;
- does not carry one H→O construction history;
- has no alpha-defined polar axis governing every later seat.

The first NSEQ16 comparison did not detect this because
`evaluateNseq05()` checked contact handedness and slip but omitted contact
distance, unlisted overlap, poles and construction order. Its
`TRACTION_CONSISTENT_UNDERDETERMINED` classification is withdrawn.

NSEQ05 remains available only as a legacy geometric control. It is not an
Atomicus structure and cannot drive a public nucleus after this repair.

## Frozen Atomicus construction

### Modules

- H-1: one proton rotor.
- H-2: one touching `p-n` deuteron.
- H-3: one touching `n-p-n` triton.
- He-4: one alpha `p-n-p-n` four-cycle.
- Li-7 through O-16: one alpha plus only the constitutional deuteron and
  triton modules.

For \(Z\ge2\),

\[
n_d=3Z-A-2,\qquad n_t=A-2Z.
\]

Every internal module edge and every docking edge has centre separation
\(2R_p\). Like-like contact is prohibited. A recorded edge that does not
touch is not a contact.

### Alpha poles

The alpha four-cycle lies in the equatorial plane. Its ring normal defines
the north/south polar axis. The ring alternates `p-n-p-n`; opposite like
members are not in contact. This axis, not a cube axis introduced by a later
shell, governs every subsequent seat.

### H→O seat ledger

The post-alpha seat count is not a second composition rule:

\[
n_d+n_t=Z-2.
\]

This is a sequence of whole-atom constructions indexed by the atom’s valence
position. At each Li→O stage, the constitutional nuclear modules are re-seated
as one spherical code. “Li”, “Be”, “B”, “C”, “N” and “O” therefore name the
complete atom at that stage; they are not identities assigned to individual
nuclear modules. Triton-bearing isotopes substitute constitutional triton
modules in that stage’s construction; they do not create a second seat family.
In particular, Li-7 is `alpha+t` and Be-9 is `alpha+d+t`.

Each added seat re-solves the whole spherical code. No module carries an
element-name label.

| Satellite count | Atom at this valence position | Constitutional population | Required nuclear seating at that atomic stage |
|---:|---|---|---|
| 1 | Li-7 | `t` | first equatorial seat |
| 2 | Be-9 | `d+t` | equatorial opposition pair |
| 3 | B-11 | `2d+t` | equidistant equatorial triangle; the third seat is unpaired |
| 4 | C-12 | `4d` | all four seats re-seat into offset up/down tropical tetrahedral geometry |
| 5 | N-14 | `5d` | trigonal-bipyramidal spherical code |
| 6 | O-16 | `6d` | octahedral spherical code; the sixth seat pairs at the orientation opened in the third stage |

The constitutional transition is also part of the ledger:

```text
Li-7  α+t
Be-9  α+d+t
B-11  α+2d+t
C-12  α+4d       (the prior t plus the added proton reorganises as 2d)
N-14  α+5d
O-16  α+6d
```

Element names select no fitted angle. The coordinates are exact spherical
codes oriented by the alpha poles and the pairing table above.

### Construction search

Modules are added in the declared ledger order. For each required seat:

1. select an already placed opposite-type rim as an anchor;
2. place the module centre on the whole atom’s registered seat ray;
3. rotate its internal contacting line about that centre, preserving exact
   \(2R_p\) internal spacing, until the first module rim lies exactly \(2R_p\)
   from the anchor;
4. reject an anchor/orientation if any unlisted pair overlaps or touches;
5. prefer a surviving alpha anchor, then choose deterministically by maximum
   clearance, minimum radial distance and lowest node index.

No radial tier, cuboctahedral shell, Fibonacci fallback or post-placement
“bond” is permitted.

## Frozen comparison routes

Two readings of each completed contact construction are evaluated:

1. the direction of each added proton centre relative to the target
   spherical seat; and
2. the direction of each constitutional deuteron/triton module centre
   relative to the same target.

Only route 2 may become the Atomicus nucleus. Route 1 tests whether the same
pairing pattern is merely a proton-count spherical code. These are
shared-input readings of one contact graph, not independent evidence.

## Repair gates

| Gate | Requirement |
|---|---|
| R0 | H-1 through O-16 inventory equals \(A,Z\); module counts equal the grammar. |
| R1 | The alpha has one explicit polar axis and a `p-n-p-n` contact cycle; like diagonals remain \(>2R_p\). |
| R2 | Li→O follows one \(Z-2\) spherical-code ledger; Li-7 and Be-9 carry the registered triton substitutions, and the fourth seat triggers whole-set tropical re-seating. |
| R3 | Every listed edge is unlike-type and has distance \(2R_p\) within \(10^{-10}R_p\). |
| R4 | No unlisted pair is at or below \(2R_p(1+10^{-10})\); every non-seed node touches at least one listed neighbour. |
| R5 | The graph is connected and bipartite; the no-slip residual is below \(10^{-10}\). |
| R6 | All declared and realised module-centre directions close on the unit-sphere seats around the alpha pole axis; no cube/cuboctahedral/Fibonacci seating fallback is called. |
| R7 | Proton-centre and module-centre residuals are both reported against the same seats; their shared inputs are explicit. |
| R8 | The corrected evaluator rejects NSEQ05 on real contact/order/pole gates. |
| R9 | Repeated builds are byte-stable; mirror JavaScript files are identical. |

## Decision

- Any R0–R9 failure: `ATOMICUS_CONTACT_CONSTRUCTION_REJECTED`.
- R0–R9 pass: `ATOMICUS_CONTACT_CONSTRUCTION_CANDIDATE`.

A passing candidate may drive the explicitly labelled experimental 3D
walkthrough. It is not promoted to a binding-energy law, charge-radius law,
or unique measured nuclear reconstruction. Interleaving remains a geometric
mass-defect ledger until an independently gated energy map exists.
