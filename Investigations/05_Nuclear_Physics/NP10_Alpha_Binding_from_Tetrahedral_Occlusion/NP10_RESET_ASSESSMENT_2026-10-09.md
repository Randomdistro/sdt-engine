# NP10 — Alpha binding: reset record (2026-10-09)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`.

**Read before this registration:** `PROMPT.md`, `DATA_REQUIREMENTS.md`, `laws.hpp` (law_III, lock_geometry, nuclear), `graph_v2.json`, and the grade table of `REOPEN_2026-10-05/PROTOCOL.md` §5.

**Not read:** `NP10_VERDICT.md`, `RUN_LOG.md`, the results files, and the old tool source. The prompt itself quotes old numbers (NP09 −97.3%; the lock scaling ×1.01/×1.98/×6.35), and those were seen. Route chosen by me at Harvey's word ("you decide", 2026-10-09).

## 1. Dependency map
- **Suppliers in graph_v2:** none (layer 0).
- **Named by the prompt:** NP09 (single-bond energy). That supplier is not in the graph and is not used here.
- **Dependents:** CH02, NP23, NP31.

## 2. Premise audit of the prompt (recorded; not tested)
- **P1.** The prompt's total-binding route ("attractive occlusion" bonds minus E_Coulomb for p-p) is potential-energy bookkeeping, withdrawn 2026-10-07: Law III is a push, and binding is mass defect.
- **P2.** It treats the neutron as a separate particle. The engine and NP17/NP14 treat it as p + e.
- **P3.** "Charge radius" is used. Here it is the He-4 boundary radius (laws.hpp:198).
- **P4.** Far-field scale, computed from the engine at registration as the motivation for the route chosen here; it is not the test:
  - Law III between two R_p_lock boundaries at contact, (π/4)P_eff R⁴/r integrated to contact at r = 2R, gives **0.0763 MeV** against B_d = 2.224 MeV.
  - The exact shadow cap at contact (half-angle 30°) exceeds the small-angle value by 7%.
  - So the MeV scale does not come from the far-field term.

## 3. Hypothesis (the prompt's 2026-07-03 refinement, made testable)
**H-W (angular-window allocation).** The lock is engagement through narrow contact-angle windows of each nucleon's W+1 = 4 tetrahedral channels (lock_geometry::rank4). Simultaneous alignment with several partners is geometrically scarce.

**Consequence, independent of any window model.** A contact in a cluster cannot engage more than the same contact does alone. So the binding per contact is bounded by the deuteron's:

r(G) = (B/E_G)/B_d ≤ 1 for every cluster with contact graph G (E_G = number of contacts).

**Observable.** r for each admissible contact graph, compared once at the end against measured bindings:
- triton and helion: rod n–p–n (E = 2, the engine's seat law) or triangle (E = 3)
- alpha: ring (E = 4) or tetrahedron (E = 6; K₄ is the maximum)

The arrangement is not fixed: the rejection criterion must be met under every admissible graph.

**Data (MEASURED-INPUT, loaded only at the comparison step).** AME2020 via `DATA_REQUIREMENTS.md`, uncertainties at the keV level (negligible against the criterion):

| nucleus | B (MeV) |
|---|---|
| H-2 | 2.224 |
| H-3 | 8.482 |
| He-3 | 7.718 |
| He-4 | 28.296 |

**Parameter ledger.** No calibrated parameters.
- **Derived:** the channel geometry (rank4), and the contact cone half-angle θ_c = arcsin(R/2R) = 30° for equal spheres in contact.
- **Measured input:** the four bindings, R_He.

## 4. Instance (a concrete realisation of H-W, no free parameter)
**Model.**
- Each nucleon is a sphere of radius R carrying 4 rays along the rank4 channels, in an orientation chosen freely per nucleon.
- A ray engages a contact neighbour if it intersects that neighbour's sphere: angle ≤ θ_c = 30°.
- A nucleon's engagement is the maximum, over orientations, of the number of neighbours it engages.
- The cluster engagement is the sum over nucleons.

**Computed for:** pair, rod-3, triangle, square ring, tetrahedron.

**Also reported:** for the tetrahedron, the smallest achievable worst-case angle to engage all 3 neighbours.

**Check.** The instance must satisfy the bound: engagement per contact ≤ 2, the pair's value.

## 5. Pre-registration
**Validations (before any cluster is evaluated).**
- V1: channel angles all = arccos(−1/3), to 1e-12.
- V2: θ_c from the contact geometry = 30°, to 1e-12.
- V3: the optimizer on a pair returns 1 engagement per nucleon.
- V4: the optimizer on a synthetic star (3 neighbours placed exactly along 3 channel directions) returns 3.

**R1 (H-W).**
- **Excluded (G1)** if r > 1 for every admissible graph of the triton, and also for every admissible graph of the alpha.
- **Open (G2)** if r ≤ 1 for some admissible graph of either.

The rejection class is populated: any superlinear growth of binding with coordination meets it.

**R2 (instance).** It must satisfy the bound. A violation is an instrument fault (G0), not a result.

**R3 (prompt criterion, kept).** Is R_He = 2R_p_lock within 1% of the measured 1.6755 fm?
- R_p_lock is target-free (FLM07).
- This is a correspondence of a contact diameter with a boundary radius. Graded G4 if met, with discrimination stated separately.

**Not tested:**
- μ_α = 0 (no native moment model is registered).
- The prompt's 20% total-binding gate: P1 withdraws the route it was written for.

**Alternative out (registered now; run only on a G1 of R1).** A cooperative lock: a closed loop of engagements locks circulation, and saves the resistance units that an open chain spends. This follows the engine's NP33 rule, "completing the graph saves one unit" (laws.hpp:2132–2150). The next round must specify it natively before any value is loaded.

## 6. Run and results
- **Run 1.** `NP10_reset_1.cpp`, output in `NP10_reset_1_results.txt`. MSVC 19.44, single pass, no amendment.
- **Validations V1–V4:** met. V4 recovered the synthetic star with a worst angle of 0.39°, using 3×10⁶ random orientations per nucleon.
- **P4 (registration scale, computed):** 0.0763 MeV per contact from far-field Law III; the exact cap at contact is ×1.0718 the small-angle value.

**Instance (R2 met: every cluster satisfies the bound).**

| cluster | contacts E | channel engagements | per contact | best worst-angle to engage all |
|---|---|---|---|---|
| pair | 1 | 2 | 2.000 | 0.03° |
| rod-3 | 2 | 3 | 1.500 | 35.27° (centre nucleon: opposite neighbours, channels 109.47° apart) |
| triangle | 3 | 6 | 2.000 | 24.78° |
| square ring | 4 | 8 | 2.000 | 9.79° |
| tetrahedron | 6 | 8 | 1.333 | 35.30° |

**Native geometric finding.** The W+1 tetrahedral channel set cannot face the three neighbours of a regular tetrahedron at once. The channel triad sits 70.53° from its axis, and the neighbour triad sits 35.26° from it, so the miss is 35.26°, beyond the 30° contact cone. Each nucleon engages 2 of its 3 neighbours.

Under this instance the angle budget prefers the square ring or the triangle (full engagement) over the tetrahedron. This bears on the prompt's own caution that the tetrahedral placement "is a rendering, not settled structure".

**R1 (comparison; measured bindings loaded here only).** r = (B/E)/B_d:

| nucleus | rod (E = 2) | triangle (E = 3) | ring (E = 4) | tetrahedron (E = 6) |
|---|---|---|---|---|
| H-3 | 1.907 | 1.271 | — | — |
| He-3 | 1.735 | 1.157 | — | — |
| He-4 | — | — | 3.181 | 2.121 |

r > 1 under every admissible graph, for both triton and alpha. **H-W excluded (G1).**

Premise that produced it: the lock as a scarce angular resource shared among partners. The measured binding per contact rises with coordination, by 1.16× to 3.18× the deuteron's, whatever the arrangement. A shared-resource mechanism cannot do that; the lock must be cooperative. The registered alternative out (the closed-loop / graph-completion lock, NP33's "completing the graph saves one unit") opens for the next round. It is to be specified natively before any value is loaded.

**R3.** 2R_p_lock = 1.68247 fm against R_He = 1.67550 fm: +0.416%, within 1%.
- **Grade G4:** R_p_lock is target-free (FLM07, q = 4).
- **Discrimination:** not discriminating (a single radius).
- **Limitation:** the reading of R_He as a contact diameter, rather than as the NP12 bulk law, is the engine's own correspondence note (laws.hpp:2020–2023).

**Grades.** H-W G1 · instance geometry G4 (computed, internal) · R3 G4 · μ_α and the total-binding route not tested (P1).

**Downstream.** CH02, NP23 and NP31 take no lock mechanism from NP10. They may take the R3 contact diameter and the channel-geometry finding (the tetrahedral cluster is not channel-optimal).

## 7. Comparison with the archived record
Deferred to the end-of-programme pass.
