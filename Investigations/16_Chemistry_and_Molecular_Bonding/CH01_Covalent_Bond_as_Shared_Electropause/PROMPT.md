# CH01 — The Covalent Bond as a Shared Electropause

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

---

## 1 · Executive Summary

EMC04 showed the Bohr radius is an **electropause** — the pressure-balance boundary where the inward
convergence push on an electron equals the outward movement-budget, holding it kinematically with no
charge invoked ([[project_electropause_peff_derivation.md]]). **Can the covalent bond be derived as a
*shared* electropause — two nuclei whose convergence wakes overlap so that one electropause surface
encloses both, with bond length, bond energy, and molecular geometry following from wake overlap and
the period-2 wake-cancellation map, no orbitals and no valence-bond wavefunction?** This extends the
electropause from atom to molecule and turns the dyad/wake-cancellation notes
([[project_foundational_ontology_influx_monopole]]) into quantitative chemistry. **We expect:** H₂'s
bond length and dissociation energy fall out of the two-proton shared-electropause balance; the
covalent bond is "shared" because the merged wake has one common pressure-balance surface; and
molecular shape (VSEPR-like angles) follows from **wake cancellation** — paired fore/aft wakes go
silent, lone wakes repel — reproducing the bent/pyramidal/tetrahedral geometries natively.

## 2 · Physical Context

An isolated atom holds its electron(s) at the electropause: convergence push inward, movement budget
outward, balanced at a₀-scale. Bring two nuclei close and their convergence wakes overlap; between
them the combined inward push deepens, and a **single** electropause surface can enclose the shared
electron pair sitting in the internuclear well. That shared boundary *is* the covalent bond — its
length is where the net axial push between the nuclei balances their mutual occlusion repulsion
(EMC03 like-pair surplus), its depth is the bond energy. Molecular geometry then comes from how the
remaining wakes around a central atom **cancel or reinforce**: the period-2 map (B–O, C–F, N–Ne;
paired fore/aft = silent, lone = active) generalises to bonding/lone-pair directions, giving the
familiar 104.5°/107°/109.5° angles as wake-balance equilibria, not hybridised orbitals.

Variables: internuclear distance `R`; shared-electropause radius; bond energy `D_e`; equilibrium
angle θ; lone-pair vs bond-pair wake strength; reduced electropause balance `F_in(R)=F_out(R)`.
Targets: H₂ (R_e = 0.741 Å, D_e = 4.52 eV), H₂O (104.5°), NH₃ (107°), CH₄ (109.5°), bond-length
trends down a group.

## 3 · Theoretical Framework

Build on: EMC04 (electropause, P_eff from centripetal balance), EMC03 (like/unlike surplus-deficit,
handedness sign), PPT06/APS04 (wakes/multipole), the period-2 wake-cancellation map (memory), Law III
(occlusion), Law V (movement budget). **Forbidden:** molecular orbitals, LCAO, hybridisation,
valence-bond wavefunctions, exchange integrals, electron "clouds." The bond length/energy and VSEPR
angles are **targets**.

Working hypotheses:
- **H1 (shared electropause):** for two protons the combined convergence field has a single
  pressure-balance surface enclosing the electron pair; solve `F_in(R)=F_out(R)` for R_e.
- **H2 (bond energy = electropause well depth):** `D_e` = work to separate the shared electropause
  back into two atomic ones; predict H₂ `D_e` from the merged-vs-separate budget.
- **H3 (geometry = wake balance):** around a central atom, bonding wakes + lone wakes settle into
  the angular configuration that cancels net wake torque; lone pairs (stronger, no second nucleus to
  share) push bonds closer → 104.5° (2 lone), 107° (1 lone), 109.5° (0 lone) — the VSEPR ladder.
- **H4 (trends):** bond length grows down a group as the core electropause radius grows (APS01 k-factors).

## 4 · Investigation Strategy

**Phase 1 — H₂ shared electropause.** Two-proton convergence field; find the single pressure-balance
surface; solve for R_e. *Success:* R_e within a few % of 0.741 Å, no charge, no orbital.

**Phase 2 — Bond energy.** Merged-vs-separate movement-budget difference. *Success:* `D_e` within
~20% of 4.52 eV; correct sign (bound).

**Phase 3 — VSEPR geometry.** Central atom + N bonding wakes + L lone wakes; minimise net wake
torque. *Success:* H₂O 104.5°, NH₃ 107°, CH₄ 109.5° recovered to a few degrees from the lone/bond
wake-strength ratio (one calibrated ratio allowed, flagged).

**Phase 4 — Trends + falsifier.** Bond length down a group via core electropause radius; predict one
**novel** number (e.g. a bond angle or length not used to calibrate) as a falsifier.

## 5 · Success Criteria

- ✅ **PASS (Class A):** H₂ R_e and D_e and the VSEPR ladder from electropause + wake balance, ≤1
  flagged ratio; a correct novel prediction.
- ✅ **QUALIFIED (Class C):** R_e and angles recovered with the lone/bond ratio CALIBRATED(1); D_e to
  ~20%. (Expected landing.)
- ⚠️ **PENDING (Class D):** shared electropause + R_e shown; geometry only qualitative.
- ❌ **FAIL (Class F):** cannot bind two atoms without importing an orbital/exchange term.

## 6 · Outputs

1. `CH01_DERIVATION.md` — shared electropause; R_e; D_e; VSEPR from wake cancellation; trends.
2. `ch01_covalent_bond.cpp` — standalone C++20: H₂ balance solver, VSEPR angle minimiser, trend table.
3. `ch01_results.txt` — R_e/D_e vs measured; H₂O/NH₃/CH₄ angles; one novel falsifier value.
4. `CH01_VERDICT.md` — A/C/D/F; ledger confirming no orbital/wavefunction entered.

## 7 · Dependencies & References

**Upstream:** EMC04 (electropause/P_eff), EMC03 (surplus/deficit sign), PPT06/APS04 (wakes), APS01
(k-factor core radii), period-2 wake-cancellation map. **Downstream:** ionic/metallic bonding, the
PV_canon chemistry/molecules volumes, reaction energetics, crystal geometry (12_Condensed_Matter).
**Related:** the Li–Be "loosest dyad" and "Be waits for O" notes ([[project_foundational_ontology_influx_monopole]]).

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | bond = shared electropause | H₂ R_e ≈ 0.741 Å from balance | bond not an electropause merge |
| T2 | D_e = well-depth difference | H₂ D_e ≈ 4.5 eV, bound sign | binding has another basis |
| T3 | geometry = wake cancellation | 104.5/107/109.5° from lone/bond ratio | VSEPR needs hybrid orbitals |
| T4 | novel prediction | an un-calibrated angle/length matches | model only fits, doesn't predict |

## 9 · Implementation Notes

Double precision; work in a₀ and eV. Solve the H₂ balance by root-finding `F_in(R)−F_out(R)=0` (bracket
around 0.7–0.8 Å). For VSEPR, represent each wake as a unit vector with a strength weight and minimise
Σ pairwise wake-interaction over angles (lone weight > bond weight is the one allowed calibrated knob).
Plot: (a) F_in/F_out vs R crossing at R_e; (b) D_e well; (c) angle vs lone/bond ratio with the three
molecules marked. The discipline: a bent water molecule from *wake cancellation* is the native win —
do not reach for sp³ hybridisation to "explain" 104.5°; that is the borrowed picture this replaces.
