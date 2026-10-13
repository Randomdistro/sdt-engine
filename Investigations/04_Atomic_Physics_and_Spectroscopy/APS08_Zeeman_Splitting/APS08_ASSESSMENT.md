# APS08 Assessment — Zeeman splitting from wake orientation

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `aps08_zeeman_routes.cpp`<br>
**Stdout:** `aps08_results.txt`<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)" and its Round 3 block; run record `RUN_LOG.md`

## Status

`APS08_NORMAL_PATTERN_COMPUTED__ANOMALOUS_BOUNDARY_LOCATED`

- The normal triplet follows from route orientation with the field as a circulation at eB/2m.
- The diagonal route-class coupling is excluded for the anomalous pattern.
- What the anomalous pattern needs is identified as a rule for the magnitude of route angular momentum, which SDT does not yet supply.

## Attempt ledger

| Round | Question | Outcome |
|---|---|---|
| 1 | Normal pattern from route orientation | 3 components, 13.996 GHz/T; Larmor equivalence verified numerically |
| 2 | Anomalous pattern from APS04's diagonal route classes | Excluded: three p levels instead of a doublet; 2, 1, 2 components instead of 4 and 6 |
| 3 | Which magnitude rule makes a vector model reproduce the doublets | Integer and half-shifted rules rejected; q(q + 1) reproduces the standard values by construction |
| 4 | Not run | Candidates listed below |

## Instrument validation

Four known-answer checks passed before any physics round:
- **V1.** Direct integration of a Kepler route in a weak magnetic field: L precesses about B at 5.0000e-6 for B = 1e-5 and 1.0001e-5 for B = 2e-5, against the Larmor value B/2, ratio 2.0002.
- **V2, zero field.** The reference spin–orbit model returns eigenvalues −1 (×2) and +1/2 (×4).
- **V2, weak field.** First-order shifts g_J m_J ω_L with g_J = 4/3 and 2/3 to 1e-3.
- **V3.** The cluster-and-count routine returns 3 components on the singlet case.

## Round 1 — normal pattern

The field enters as a collective circulation of the medium at Ω_B = eB/(2m_e), with e and m_e the
unit-bridge and mass-seat inputs. Direct integration (V1) confirms that a bound Kepler route in a
magnetic field responds as a route in a medium rotating at that rate, at first order in B. A
route with azimuthal order m (m₃ = 3m) is displaced in frequency by mΩ_B/2π. For the Cd
643.847 nm line (singlets, upper d class m = −2…2, lower p class m = −1…1, Δm = 0, ±1) the
nine allowed transitions collapse to three distinct shifts, −1, 0, +1 in units of Ω_B/2π.

From the engine's e, m_e and h: Ω_B/2π = 13.996 GHz per tesla = 0.46686 cm⁻¹ per tesla, and
Δλ = 0.01935 nm per tesla at 643.847 nm. No magneton unit was used.

Provenance: the pattern follows from Larmor's theorem in the form "a magnetic field is an
imposed circulation at eB/2m". That is convergent with the standard normal pattern and does not
discriminate against it. The component count is an enumeration over the route classes, and the
class structure of d routes (m = −2…2 as m₃ = −6…6) is an extension of APS04's p and s
enumeration, not a separate result. A measured splitting was not retrieved, so no comparison with
data is made (stated limit).

## Round 2 — the anomalous pattern

Basis: s routes (m = 0, spin ±½) and p routes (m = −1, 0, 1, spin ±½), with the electron's
handed circulation entering as spin ±½ and g_s = 2 (an input; its derivation belongs to
PPT12). Weak field ω_L = 1e-4 ξ.

| Model | Zero-field p manifold | Line groups and components |
|---|---|---|
| M_diag (diagonal route classes, ξ m s_z) | 3 levels at −ξ/2, 0, +ξ/2 | 2, 1, 2 components (shifts ±1, 0, ±1) |
| M_vec (rotation-invariant coupling; reference only) | doublet at −ξ and +ξ/2 (2 + 4) | D1: 4 at ±2/3, ±4/3 (intensities 2:1:1:2); D2: 6 at ±1/3, ±1, ±5/3 (intensities 1:3:2:2:3:1) |

M_diag fails both anchors named in the seed: the zero-field structure (observed: a doublet) and
the component counts (observed: 4 and 6). The rejection criterion is met. With a coupling that
depends only on the projections of the route axis and the electron's axis, every line group
shows only the normal spacing, so no anomalous pattern can appear however ξ is chosen. A
coupling that depends on the relative orientation of the two axes is required, and M_vec
supplies one. M_vec is the standard account's angular-momentum algebra, used here only to
produce the target pattern with its intensities. It is not offered as an SDT derivation. The
computed intensities are the model's own and were not compared with measured intensities.

## Round 3 — which magnitude rule

A semiclassical vector model in which both axes precess about their resultant gives
g_J = 1 + (g_s − 1)(J² + S² − L²)/(2J²) and needs a squared magnitude for each angular momentum.

| State | Coupling | g (observed doublet value) | R1 integer | R2 shifted ½ | R3 q(q + 1) |
|---|---|---:|---:|---:|---:|
| ²S₁/₂ | none | 2.00000 | 2.00000 | 1.87500 (−6.3%) | 2.00000 |
| ²P₁/₂ | anti-aligned | 0.66667 | 0.00000 (−100%) | 0.87500 (+31%) | 0.66667 |
| ²P₃/₂ | stretched | 1.33333 | 1.33333 | 1.34375 (+0.8%) | 1.33333 |
| ²D₃/₂ | anti-aligned | 0.80000 | 0.66667 (−16.7%) | 0.84375 (+5.5%) | 0.80000 |
| ²D₅/₂ | stretched | 1.20000 | 1.20000 | 1.20833 (+0.7%) | 1.20000 |
| ²F₅/₂ | anti-aligned | 0.85714 | 0.80000 (−6.7%) | 0.87500 (+2.1%) | 0.85714 |
| ²F₇/₂ | stretched | 1.14286 | 1.14286 | 1.14844 (+0.5%) | 1.14286 |

Na D1 and D2 under each rule: R1 gives 2 components for D1 (target 4) and 6 matching for D2; R2
gives the right counts at wrong positions; R3 gives 4 and 6 at the target positions. The
rejection criterion is met for R1 and R2. The target values are the standard g-values, which are
what R3 computes, so R3's agreement is by construction. The observed doublet g-values were not
retrieved; the comparison is with the standard values, which the observed patterns have long
confirmed, and that confirmation is cited from the literature in general and not checked here.

**What the result shows.** The integer-magnitude vector model is exact for every stretched state
(J = L + S) and wrong for every anti-aligned state (J = L − S). The failures sit in the
configurations where the electron's own circulation opposes the route's. The rule that repairs it
replaces |q|² by q(q + 1) = q² + q: a term linear in the magnitude is added. SDT would need a
geometric statement that produces that linear term for the angular momentum of a route and of
the electron's circulation. None exists in the corpus.

**Link to APS09.** The Stark route in APS09 needed an offset of one unit in the projection
(m = n − 1) and one further constant. Both investigations stop at the same place: a classical
route with integer angular momentum is the large-quantum-number limit of the observed structure,
and the O(1) corrections come from a rule for how route angular momentum is counted. Whether one
rule supplies both is a hypothesis. By algebra on the recalled formula, the projection offset fixes
the n² and n terms of the APS09 bracket and a constant 19 remains, so the hypothesis is only partly
supported and the constant is not explained by it.

## Limitations

1. No measured Zeeman data were retrieved. The normal spacing is compared with the standard value,
   and the anomalous patterns with the standard g-values, not with measurements.
2. The electron's g_s = 2 is an input. Its derivation (PPT12) is open.
3. M_vec and the magnitude rule R3 are the standard account's form. Round 2 and Round 3 show what
   SDT has to reproduce, not that it does.
4. The route enumeration for d classes extends APS04's s and p enumeration.
5. Zero-field fine-structure splittings (ξ) are not computed; they are inputs.

## Alternatives considered

- **Orientation-energy coupling with a magnitude supplied by route geometry.** Replace ξ m s_z by
  an energy that depends on the angle between the route axis and the electron's axis, and fix the
  magnitudes from the geometry of the seat (for example the circumference counts that give the
  lobe-lock classes). R1 is the case in which the magnitudes are the integer quantum numbers and
  it fails; any version of this alternative has to show why the magnitudes carry the extra linear
  term.
- **Observed g-values as inputs for the anti-aligned states.** This reproduces the anomalous
  patterns with a table of four to seven measured numbers per atom and is CALIBRATED, not derived.
  It would let the Zeeman pattern be used as a tool while the derivation is open.
- **Strong-field check.** In the Paschen–Back limit M_diag's additive shifts give the normal
  triplet again. Measured Paschen–Back transitions (for example Li D lines at a few tesla)
  would test whether the route classes carry the correct strong-field limit even though they
  fail the weak-field one. Data not retrieved.

## Open

- A route-geometry statement that gives |q|² = q(q + 1) for route angular momentum.
- Measured Zeeman patterns (normal and anomalous) with fields stated, into `Datasets/`.
- The derivation of g_s = 2 (PPT12).
