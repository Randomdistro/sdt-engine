# APS09 Assessment — Stark response from seat displacement

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `aps09_stark_route.cpp`<br>
**Stdout:** `aps09_results.txt` (final), `aps09_results_run1_round3_superseded.txt` (kept; see `RUN_LOG.md`)<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)" and its Round 3 blocks

## Status

`APS09_LINEAR_STRUCTURE_COMPUTED__QUADRATIC_BOUNDARY_LOCATED`

- The linear Stark structure follows from the classical geometry of the seat ladder, with one rule asserted (the quantisation of the eccentricity projection).
- The core-induced quadratic term has a derived closed form.
- Hydrogen's own second-order response is not reproduced by the classical route. The shortfall is quantified and decomposed below.

## Attempt ledger

| Round | Question | Outcome |
|---|---|---|
| 1 | Linear coefficient and level structure from the orbit-averaged field energy | Coefficient derived and verified; level count and pattern follow from an asserted labelling |
| 2 | Does a core splitting suppress the linear term and produce a quadratic one? | Yes. Closed form ΔE₂ = −ω²(n²−ℓ²)/(4κℓ²) verified to 0.31% |
| 3, first run | n = 1 second-order shift, circular routes at every orientation | Not evaluable: routes with L not along the field plunge through the nucleus |
| 3, redesign | n = 1…4, stable family (L along the field) | Classical shift −n⁶/2; ratio to the standard value 0.22 → 0.61; classical route rejected at n = 1 |
| 4 | Not run | Candidates listed below |

## Instrument validation

Six known-answer checks passed before any physics round: Kepler conservation over 60 orbits
(drift 6e-12); orbit-averaged position −(3/2)aε to 3e-15 over five orientations; secular rate
against the full dynamics (−7.196e-5 against −7.200e-5); the so(4) Poisson brackets of L and the
scaled Runge–Lenz vector to 1e-10; secular invariants over 10⁶ steps; and adiabatic switching
on a first-order case to 0.47%. Two faults in my own set-up are recorded in `RUN_LOG.md` (the V6
test orbit, and the V5 gate).

## Round 1 — linear term

**Derived.** For a route of semi-major axis a = n²a₀ (the engine's seat radius, speed αc/n)
the orbit-averaged position is −(3/2)aε, so the first-order energy is

ΔE₁ = −(3/2) n² ε_z e a₀ F, and with ε_z = k/n, ΔE₁ = −(3/2) n k e a₀ F.

Numerical averaging against this closed form agrees to 5e-15 for n = 2…5 and every k. With the
engine's e, a₀, h the unit is e a₀/h = 1.27954 MHz per V/cm, so the n = 2 outer components sit at
±3.8386 MHz per V/cm and the n = 3 outer components at ±11.5159 MHz per V/cm. The standard
form of the hydrogen coefficient is 3 e a₀ F at n = 2. This is convergence with that form and
with the classical (Bohr–Sommerfeld–Epstein) treatment. It is not a comparison with a
measurement: a measured table was not retrieved.

**What the level structure does and does not show.** The levels k = n₁ − n₂ with
n = n₁ + n₂ + |m| + 1 give n² states for every n and, at n = 2, the pattern −3, 0, 0, +3.
Both are consequences of the parabolic labelling, which is asserted here and not derived from
the seat definition. The count criterion in the pre-registration therefore could not have failed,
and its meeting is not evidence. Two statements are genuinely structural:
- At n = 2 the |m| = 0 sector is the m₃ = 0 class of APS04's enumeration (2s and the polar 2p):
  two routes that mix and give ±3. The |m| = 1 sector is the lobe-locked m₃ = ±3 class, which
  does not mix and stays at 0. The grouping by APS04's own classes matches the grouping by |m|.
- The classical continuum allows ε_z up to 1 (an L = 0 route through the nucleus), which would
  give ±6 at n = 2. The structure of the standard account has ±3, so a rule excluding L = 0
  routes (k ≤ n − 1) is required and is not derived here. Round 3 shows the field itself drives
  m = 0 routes through the nucleus. That is a suggestive link to a seat definition (a route
  through the core is not a zero-cost closed route) and it is only a link, not a derivation.

## Round 2 — degeneracy and the quadratic term

With H = ω_S A_z + κL² (the field acting on the route's constants, and a core term that lifts
the l degeneracy), an adiabatic ramp gives:

| Test | Registered | Result |
|---|---|---|
| κ = 0: ΔE against ω_f A_z(0) | 1e-4 | 1.00000 |
| linear term at κℓ/ω_f = 50 | below 5% | 1.1% |
| L along z: ΔE₂ against −ω²(n²−ℓ²)/(4κℓ²) | 2% | within 0.31% across eight (ω, κ) points |
| fitted exponent in the field coupling | 2 ± 0.03 | 1.9986 |
| fitted exponent in the core splitting | −1 ± 0.03 | −0.9995 |

This is the linear/quadratic distinction the seed asks for: the linear term needs degenerate
routes, a core splitting removes it, and the quadratic term then goes as F²/κ. If the core
splitting scales as n⁻³ (the Rydberg scaling of core-induced shifts), the closed form gives
ΔE₂ ∝ n⁷, the scaling reported for Rydberg polarisabilities. That consequence is not tested
here: κ was not derived from a core model and no measured non-hydrogenic coefficient was
retrieved. No absolute quadratic coefficient is claimed.

## Round 3 — hydrogen's own second-order response

**First run (not evaluable).** At θ = 0° the n = 1 shift is −0.500002 F², exactly F² scaling.
Circular routes with L at 60° and 90° to the field are not adiabatically continuable. With A = 0
the field drives dA/dt = ω_S(ẑ × L) ≠ 0 at first order; the eccentricity grows to 1 and the route
plunges through the nucleus. The registered orientation average could not be formed. Any value
printed for it in the superseded output is a plunge artefact.

**Redesign (stable family: circular, L along the field).**

| n | ΔE₂/F² computed | predicted −n⁶/2 | ratio | standard value (k = 0, m = n − 1) | classical / standard |
|---:|---:|---:|---:|---:|---:|
| 1 | −0.5000 | −0.5 | 1.00005 | −2.25 | 0.2222 |
| 2 | −32.0015 | −32 | 1.00005 | −78 | 0.4103 |
| 3 | −364.518 | −364.5 | 1.00005 | −688.5 | 0.5294 |
| 4 | −2048.10 | −2048 | 1.00005 | −3360 | 0.6096 |

The classical prediction −n⁶/2 is met to 5e-5 at every n, and every run scales as F² to 1.0001.
The standard value is −(n⁴/16)(17n² − 3k² − 9m² + 19) from the textbook treatment (recalled; a
reference, not a measurement). Against it the classical route falls short by a factor 4.5 at
n = 1 and the ratio rises monotonically, 8n²/(8n² + 18n + 10) = 1 − 2.25/n + …, toward 1.
The classical route is the large-n limit of the standard result and its low-n failure is
O(1/n). The rejection criterion for "the classical seat route reproduces the ground-state
polarisability" is met: 0.222 against the required 1 ± 0.05.

**Where the n = 1 shortfall comes from** (using the standard formula as reference).
At n = 1 the difference between −0.5 and −2.25 is 1.75 F², of which 19/16 = 1.1875 (68%) is the
constant term and 9/16 = 0.5625 (32%) is the offset between the classical L_z = n and the
standard state's m = n − 1. The constant term has no classical counterpart in this route; it
is a correction that is higher order in the action quantum. In SDT language it is whatever the
route model omits about how the electron's own circulation (the wake self-drafting of PPT12)
changes the effective angular momentum of a route at low n.

*Correction recorded 2026-10-03 (same day, after the APS08 work).* The structure of the gap is
sharper than stated above. Writing the classical form as −(n⁴/16)(17n² − 3k² − 9m²), which the
computation confirms at m = n (it gives −n⁶/2, the values in the table), and inserting the
standard state's projection m = n − 1 with k = 0, the bracket is 8n² + 18n − 9. The standard
bracket is 8n² + 18n + 10. The two agree in the n² and n terms and differ by exactly the constant
19. So the whole shortfall splits into (i) the projection offset, which accounts for the n and
the n² structure, and (ii) one n-independent constant, 19. The classical route at m = n − 1 is
not itself a stable route (it is the tilted circular family of Round 3 Part A, which is not
adiabatically continuable), so this is algebra on the recalled formula, not a computation;
only the m = n values are computed.

**A second structural finding.** The classical m = 0 routes are not stable seats in a field.
APS04 places the 1s seat in the m₃ = 0 class. Under an imposed redirection gradient the
classical m = 0 route is driven through the core. A route at fixed orientation therefore cannot
be the 1s seat in a field, and the orientation average that would repair this was the quantity
Round 3 could not form. The seat concept at 1s needs either an orientation-distributed route
family or a correction that regularises the L → 0 limit. Neither exists in the corpus.

## Limitations

1. No measured Stark or polarisability table was retrieved. Every comparison is with the
   standard account's closed forms, stated as such. Retrieval of measured hydrogen patterns and
   a non-hydrogenic polarisability is outstanding.
2. The parabolic quantisation (k, m integers with n₁, n₂ ≥ 0) is asserted. The state count and the
   n = 2 pattern follow from it and are not independent evidence.
3. The route is classical. It reproduces the first-order structure exactly and the second-order
   structure only in the large-n limit.
4. Round 2's core term κL² is a model of a lifted degeneracy, not a derived core potential.

## Alternatives considered

- **Orientation-distributed 1s route.** Replace the single oriented circular route by the family
  of all orientations and ask whether a regularised average reproduces −9/4. Round 3 shows the
  unregularised average is undefined (plunge). A regularisation needs a cutoff on L that the
  seat definition would have to supply.
- **Shift in the angular quantity.** A half-unit (Langer-type) offset in L_z does not reproduce
  the standard result: 17n² − 9(n − ½)² = 8n² + 9n − 9/4, against 8n² + 18n + 10. A one-unit
  offset, the standard state's projection m = n − 1, reproduces the n² and n terms exactly
  (8n² + 18n − 9) and leaves the constant 19. This closes all of the gap except one constant.
  APS08 finds the same kind of missing ingredient on the spin–orbit side (a rule for the
  magnitude of route angular momentum, |q|² = q(q + 1)); whether it also fixes the constant 19
  here is not tested.
- **Self-drafting correction.** If the 19-term is a wake self-interaction correction to route
  angular momentum, the same correction enters g − 2 (PPT12) and the Casimir floor (FLM15). A
  derivation from the wake geometry would then fix all three. This is the most economical
  hypothesis and the least developed.

## Open

- Measured hydrogen Stark tables and a non-hydrogenic polarisability into `Datasets/`.
- Derivation (or exclusion) of the k ≤ n − 1 rule from the seat definition.
- A seat description of 1s that is stable under an imposed gradient.
- Round 4 candidates: (a) test the n⁷ scaling consequence of Round 2 against measured Rydberg
  polarisabilities once retrieved; (b) a core model for κ(n, l) from a polarisable core.
