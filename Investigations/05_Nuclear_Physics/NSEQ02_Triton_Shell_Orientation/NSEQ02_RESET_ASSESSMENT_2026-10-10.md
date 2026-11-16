# NSEQ02 (triton shell orientation) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `nseq02_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `NSEQ02/PROMPT.md` in full (including the 2026-10-05 audit correction). Not read: `NSEQ02_ASSESSMENT.md`, `nseq02_orientation.cpp`, the dependent NSEQ03 folder, and the sequencer's source (the string `beltPlane` was searched only to see where it occurs; it appears in no live tool, only in audit notes and NSEQ03, none opened). Exposure: the prompt states the author correction (the equatorial-ring "belt" orientation was an LLM assumption).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | C2 (layout built), C1 (ledger published) and C5 (status label) are constructions or documentation; the audit correction says so and asks for them to be labelled VERIFICATION. They cannot fail. |
| D2 | premise | C3 ("with r_open > r_close the mean opening radius exceeds the closing one") is satisfied by the inputs 1.05 and 0.95; it tests nothing. What the radius rule does change is geometric: two tetrahedra of different circumradius interlinked at the 70.53° cube-edge angle; the inter-seat distances are computed. |
| D3 | gating | The audit correction asks for "a numeric gate on a measured nuclear quantity". Orientation does not enter any capacity, binding or radius as built (the capacity 8 = B(3) is a count; the orientation is a placement of the 8). No such gate can be written for an orientation alone; recorded as OWED with what it would need (a model that maps a seat geometry to a measurable, e.g. the shadow-overlap model of NP17/NP35). |
| D4 | premise | The sequencer's first belt is described as "4 antipodal pairs, 8 directions in one plane"; the spacing is not given. The comparison used is the coplanarity of the arrangement (second-moment tensor with a zero eigenvalue), which holds for any spacing; the regular octagon (45° spacing) is the maximal-spread example. The sequencer source is not opened. |
| D5 | record | A polar-aligned stella octangula is the eight vertices of a cube with a body diagonal along the pole axis. Its 28 pairwise angles are fixed by the cube: 12 at arccos(1/3) = 70.5288°, 12 at arccos(−1/3) = 109.4712°, 4 at 180°. This is stated before the run so that the construction is not mistaken for a finding. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Author layout (A).** Opening tetrahedron: north pole (0,0,1) and three vertices at z = −1/3 (latitude −19.4712°), azimuth 0°, 120°, 240°. Closing tetrahedron: south pole (0,0,−1) and three at z = +1/3 (latitude +19.4712°), azimuth 60°, 180°, 300°. Radius rule: opening 1.05, closing 0.95 (relative units).
**Comparators.** (B) Flat hex-bipyramid: poles plus six at z = 0, azimuth 0°, 60°, …, 300° (the rejected misread). (C) Planar arrangement: four antipodal pairs in the plane z = 0 (regular octagon, 45° spacing, as the example).
**Quantities.** Pairwise angular separations and the histogram; minimum angle; regularity of each tetrahedron (six equal edges); the second-moment tensor Σ u uᵀ of the eight unit vectors and its eigenvalues (isotropy); partition sizes; mean radii; inter-seat distances with the radius rule (opening–opening, closing–closing, nearest opening–closing, antipodal opening–closing); the count 8 against B(3) = 2(3+1).
**Validations (known answers).** V1: all unit vectors have norm 1 to 10⁻¹⁵. V2: the angle between unit vectors of a regular tetrahedron is arccos(−1/3) = 109.471221° and between adjacent cube vertices arccos(1/3) = 70.528779° (analytic constants compared with the computed values to 10⁻¹²). V3: the 8 vertices of (A) coincide with the cube vertices (±1,±1,±1)/√3 rotated so that a body diagonal is along z (tested through the pair-angle histogram 12/12/4 and the isotropic tensor, eigenvalues each 8/3).
**Gates.** C1–C6 as VERIFICATION rows; the numeric gate of the audit correction: OWED (D3).
**Expected landing (hand estimate).** (A) regular tetrahedra, histogram 12/12/4, isotropic tensor (8/3, 8/3, 8/3), min angle 70.53°; (B) not regular (edges at 90° and 120°), tensor (3, 3, 2), min angle 60°; (C) tensor (4, 4, 0), coplanar, min angle 45°; opening–opening distance 1.7147, closing–closing 1.5513, nearest cross 1.1576 (from d² = r₁² + r₂² − 2r₁r₂/3), antipodal cross 2.000.

## 3. Results (COMPUTED; instrument `nseq02_reset_1.cpp`, output `nseq02_reset_1_results.txt`; single pass, no amendment; all validations met)
**Validations.** V1 met (1.1×10⁻¹⁶); V2 met (tetrahedron angle 109.471221°, deviation 2.8×10⁻¹⁴; cube-edge angle 70.528779°); V3 met (histogram 12/12/4, isotropic tensor 8/3 ×3).
**(A) Author dual tetrahedra.** 8 vectors, 28 pairs: 70.5288° ×12, 109.4712° ×12, 180° ×4; minimum angle 70.5288°. Both tetrahedra regular (all six edge angles 109.471221°); partition 4 + 4; band latitudes −19.4712° (opening) and +19.4712° (closing). Second-moment eigenvalues 2.666667 ×3 (isotropic): the arrangement is the eight vertices of a cube with a body diagonal along the pole axis.
**(B) Flat hex-bipyramid (rejected misread).** Histogram 60° ×6, 90° ×12, 120° ×6, 180° ×4; minimum 60°; eigenvalues 2, 3, 3 (not isotropic); the tetrahedron from a pole and three alternate equatorial vertices has edge angles 90°–120°: **not regular**.
**(C) Planar (four antipodal pairs in z = 0, regular octagon as the example).** Histogram 45° ×8, 90° ×8, 135° ×8, 180° ×4; eigenvalues 0, 4, 4: **coplanar**; distinct from (A) for any spacing (a zero eigenvalue), so C4 holds as a geometric fact.
**Radius rule.** Opening 1.05 > closing 0.95 (restates the inputs). Opening–opening distance 1.7146, closing–closing 1.5513; nearest opening–closing 1.1576 (at 70.5288°); farthest 2.0000 (antipodal, r₁ + r₂).
**Capacity identity.** 8 = B(3) = 2(3 + 1): a count. **Numeric gate of the audit correction: OWED** (D3).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 split ledger, C5 status label, C6 no canon edit | **VERIFICATION, met** | documentation |
| C2 author layout (2 poles + 6 band vertices, two regular tetrahedra, partition 4 + 4) | **VERIFICATION, met; G3 COMPUTED geometry** | the layout is the cube-vertex arrangement; every angle is fixed by it |
| C3 radius rule | **VERIFICATION (restates inputs)** | the geometric consequences (distances) computed |
| C4 sequencer first belt coplanar and distinct | **VERIFICATION, met for any planar arrangement** | zero second-moment eigenvalue; the sequencer source not opened |
| Numeric gate on a measured nuclear quantity | **OWED** | orientation enters no measurable as built; needs a seat-geometry-to-measurable model (NP17/NP35) |
| Rejected misread (flat hex-bipyramid) | **VERIFICATION: tetrahedra not regular** | edge angles 90°–120° |

## 5. Direction
1. Treat the eight-seat shell as the cube-vertex arrangement with a body diagonal on the pole axis; the 70.53° near neighbours across the two tetrahedra and the antipodal pairs (four) are its fixed contacts. NSEQ03 can take the geometry as given.
2. The numeric gate asked by the audit requires a model in which seat geometry changes a measured quantity (shadow overlap, binding, radius); that belongs to NP17 and NP35 and is not available to an orientation record.
3. The nomenclature "belt" should stay retired in text that describes the shell.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
