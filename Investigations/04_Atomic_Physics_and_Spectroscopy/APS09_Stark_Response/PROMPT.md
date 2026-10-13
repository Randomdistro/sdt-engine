# APS09 — Stark response (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**G2, open; the registered rounds are not run.** The classical Kepler route with Runge–Lenz is admissible and verified (V4). But the **discrete** pattern is imported through the asserted parabolic labelling ε_z = k/n. Classically, the orbit-averaged shift is continuous in ε_z.

## 2. What the errors and new data teach
- The native candidate exists but is unfinished. APS04 route classes put 2s and polar 2p in the m₃ = 0 sector (mixing, ±), and lobe-locked routes at 0. The ±3·e·a₀·F coefficient needs ε_z = ±½ for those routes, which the route geometry has not yet given.
- Sequential occupancy (FLM14) is the native picture of which routes a seat holds.

## 3. Next round (registered order)
1. A native rule for which eccentricities a seat route can hold (from APS04 route classes or the wake geometry), stated before any field is applied.
2. Cache the hydrogen Stark tables with provenance.
3. One comparison of the pattern and coefficient, with cascade bands.

## Prohibitions
- No census over candidate forms (2026-10-07 rule).
- No imported source models (PREM, polytropes, quantum-number labelling) as native tests.
- No G or GM.
- The word "charge" is not used.

---

## Previous specification (kept as written)

# APS09 — Stark Response from Seat Displacement

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B96). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Spectral lines shift and split in an applied electric field — linear in field for hydrogen
(its rung-2 routes respond directly), quadratic for most atoms. Measured anchors: hydrogen
Balmer Stark components (classic tabulations), helium quadratic coefficients.

## SDT footing

An applied field is an imposed handed-redirection gradient (L12): it tilts the wake the
electron drafts on, displacing seats and re-pricing routes. Hydrogen's linear response is the
signature that its rung-2 route classes (APS04's m₃ basis) mix at first order — the same
degeneracy-of-routes fact that makes the 2S–2P interval measurable. Existing corpus: APS01
(seat ladder), APS04 (route classes), EMC04 (P_eff — the pressure scale the field perturbs).

## Pre-registration skeleton (complete before any tool)

- Question: does seat displacement under an imposed redirection gradient give hydrogen's
  linear coefficient and the general quadratic form, forward from wake geometry?
- Rejection criterion (populated): hydrogen linear coefficient off beyond committed
  tolerance, or the linear/quadratic distinction failing to fall out of route mixing.
- Anchors: hydrogen Stark tables; one non-hydrogenic quadratic coefficient.
- Tolerance: to be committed here before instrumentation.

## Benchmark linkage

Catalogue row B96 · suite coverage roster · tally on computed number only.

## Pre-registration (2026-10-03, before the instrument exists)

**Method note.** Rounds are registered as they are designed; Round 2 is registered now as a
fixed follow-on whatever Round 1 shows, so that its design does not depend on Round 1's
numbers. Further rounds receive their own dated blocks. All rounds stay in the attempt ledger
of `APS09_ASSESSMENT.md`.

**Route.** Classical mechanics of the SDT seat: a closed circulation at radius r = n²a₀ with
speed αc/n (`sdt::laws::atomic::bohr_radius`, `bohr_velocity`), i.e. a Kepler route with
semi-major axis a = n²a₀. The field acts as a uniform force on the route. No wavefunction,
no operator algebra. The Runge–Lenz vector A = nε (ε the eccentricity vector) and the
angular momentum L are the classical constants of the Kepler route; their Poisson brackets
are classical mechanics and are verified numerically (V4) rather than assumed.

**Instrument validation (before any physics round).**
(V1) Kepler integration at F = 0: energy, L and A conserved to 1e-9 over 60 orbits (ε = 0.6).
(V2) Orbit-averaged position ⟨r⟩ = −(3/2)aε, by numerical averaging over the orbit against the
closed form, for five eccentricity vectors, 1e-10.
(V3) Secular rates against the full dynamics: for n = 2, ε = 0.6, F = 2e-5 a.u., the mean dL/dt
over 20 whole orbits of the full integration against −(3/2)nF (ẑ × A), within 2%.
(V4) Poisson brackets {L_i,L_j} = ε_ijk L_k, {L_i,A_j} = ε_ijk A_k, {A_i,A_j} = ε_ijk L_k by
central differences of the explicit phase-space functions at a random point on a fixed-energy
shell, 1e-6.

**Round 1 — linear term and level structure.** The first-order energy of a route is the orbit
average of the field energy: ΔE = −(3/2) n² ε_z e a₀ F. A route with ε_z = k/n gives
ΔE = −(3/2) n k e a₀ F, k integer with the parabolic labelling n = n₁ + n₂ + |m| + 1,
k = n₁ − n₂ (the labelling is ASSERTED here, not derived; it is tested only by the state count).
- *Predicted before running:* levels equally spaced by (3/2) n e a₀ F (correction recorded
  2026-10-03 before the instrument was written: the first draft read "3 e a₀ F n"; the n = 2
  pattern below is unaffected); multiplicity n − |k| in the m-resolved count, total n² for
  n = 1…6; at n = 2 the pattern ΔE/(e a₀ F) = −3, 0, 0, +3
  (multiplicities 1, 2, 1). The m₃ = 0 sector of APS04's n = 2 route enumeration holds two
  routes (2s and the polar 2p) that mix at first order and give ±3; the lobe-locked m₃ = ±3
  routes do not mix and stay at 0. Coefficient e a₀/h from engine constants:
  1.2796 MHz per V/cm per unit, so the n = 2 outer components sit at ±3.839 MHz per V/cm.
- *Rejection criterion (populated):* total count ≠ n² for any n ≤ 6; level spacing not uniform;
  n = 2 pattern ≠ (1, 2, 1); the extreme eccentric route k = n (a route through the nucleus,
  L = 0) is required to reproduce the measured n = 2 splitting (it would give ±6, a factor 2
  too large).
- Anchors: the hydrogen linear Stark pattern and coefficient 3 e a₀ F at n = 2 in the standard
  form. A measured table was not retrieved; the comparison is therefore recorded as
  convergence with the standard coefficient, not as a test against data (stated limit).

**Round 2 — degeneracy and the quadratic term.** Add a core term κL² to the secular route
Hamiltonian H = ω_S A_z + κ L², ω_S = −(3/2)nF (a core that lifts the l degeneracy, as the
quantum defect does for a non-hydrogenic atom). Secular equations:
dL/dt = ω_S (ẑ × A), dA/dt = ω_S (ẑ × L) + 2κ (L × A).
Adiabatic ramp of ω_S from 0 to ω_f over a time ≥ 400/ω_f and ≥ 50/κ; energy shift
ΔE = H_final − H_initial.
- *Predicted before running:* (i) κ = 0: ΔE = ω_f A_z(0) (linear). (ii) κ ≫ ω_f: for a state with
  L along z (|L| = ℓ, L_z = ℓ), second-order classical perturbation of the secular system gives
  ΔE₂ = −ω_f² (n² − ℓ²) / (4 κ ℓ²), quadratic in the field and inverse in the core splitting.
  (iii) The linear term of a state with A_z(0) ≠ 0 is suppressed below 5% of ω_f A_z(0) once
  κ ≥ 50 ω_f/ℓ.
- *Rejection criterion:* κ = 0 energy departs from ω_f A_z(0) by more than 1e-4 relative; the
  large-κ shift departs from the closed form by more than 2%; fitted exponents leave
  ω_f: 2 ± 0.03 or κ: −1 ± 0.03; the linear term is not suppressed below 5%.
- Anchor for the quadratic coefficient: none is claimed. Hydrogen's ground-state polarisability
  (9/2 a₀³) and a non-hydrogenic coefficient are not computed in this run; the failure mode of
  the classical route at low n is analysed in the assessment, not tested here.

**Labels.** Round 1: COMPUTED; convergent with the classical (Epstein) and quantum linear Stark
patterns; not discriminating against them. Round 2: DERIVED structure (linear needs route
degeneracy; quadratic ∝ F²/κ), no absolute quadratic coefficient claimed.

### Round 3 — registered 2026-10-03 after Rounds 1 and 2 were run

Reason: Round 2's quadratic term is the core-induced one. Hydrogen's own ground-state response
(no core splitting; the n-mixing second-order term) is not covered by Round 2, and the seed
asks for the general quadratic form. Round 3 tests whether the classical seat route alone
reproduces it.

- *Question:* does the classical seat route reproduce the n = 1 second-order shift of hydrogen,
  ΔE₂ = −(9/4)F² a.u. (polarisability 9/2 a₀³)?
- *Instrument:* the full Kepler-plus-field dynamics validated in V1 and V3. A circular route
  (a = 1) with its angular momentum at angle θ to the field (θ = 0°, 60°, 90°); the field is
  switched on adiabatically (quintic ramp over 600 orbits) to F_f = 1e-3 and 2e-3 (a.u.); the
  energy shift is E_final (field term included) minus E_initial. The shift for a circular route
  is a quadratic form in the field, so ΔE₂/F² = c₀ + c₂cos²θ and its orientation average is
  c₀ + c₂/3.
- *Added validation (V6, before Round 3):* a known-answer check of the switching method on a
  first-order case: n = 2, ε = 0.5 with ε ∥ z, F = 2e-4, expected ΔE = −(3/2)n²εF = −3F to 1%.
- *Predicted before running:* the classical value falls well short of the exact 9/4. The
  expected order is 1 (between 0.5 and 1.5) for the orientation average, with the θ = 90°
  route (L ⟂ field) the largest; ΔE₂ scales as F² (ratio of the two field strengths 4.00 ± 0.05).
- *Rejection criterion:* the hypothesis "the classical seat route is sufficient for the
  ground-state polarisability" is rejected if the orientation-averaged |ΔE₂|/F² differs from
  9/4 by more than 5%. Its rejection class is populated (the prediction above lies outside it).
- *Anchor and limit:* 9/4 is the exact value of the standard account, which is not a measurement.
  A measured hydrogen polarisability was not retrieved, so Round 3 is a comparison with the
  standard account's value, stated as such.
- *Recorded for reference, not registered as a prediction:* a closed form recalled from the
  classical (Epstein) literature, −(n⁴/16)(17n² − 3k² − 9m²), would give −17/16 at θ = 90°
  and −1/2 at θ = 0°.

#### Round 3 redesign — registered 2026-10-03, after the first Round 3 run and before the rerun

*What the first run showed (output kept as `aps09_results_run1_round3_superseded.txt`).* At
θ = 0° the shift is −0.500002 F² at F_f = 1e-3 and −0.500006 F² at 2e-3 (exact F² scaling).
At θ = 60° the shifts do not scale as F² (−1.112, −1.030) and at θ = 90° the run ended with a
non-physical energy (2e8): the circular route with L not along the field is not adiabatically
continuable. With A = 0 the field drives dA/dt = ω_S (ẑ × L) ≠ 0 at first order, so the
eccentricity grows to 1 within the ramp and the route plunges through the nucleus. The
orientation average registered above therefore cannot be formed; the registered rejection
criterion was not evaluable as designed. The cause is the design (circular routes at every
θ are not invariant tori of the field problem), not the switching method, which V6 validates.

*Redesigned Round 3.* Only routes that are equilibria of the secular field flow are used:
circular (ε = 0) with L along the field (dA/dt = ω_S ẑ × L = 0). Family n = 1, 2, 3, 4 with
a = n², switching to F_f = 0.004/n⁴ over 600 orbits, each run carrying an instability
diagnostic (maximum eccentricity and minimum radius; a run with ε_max > 0.9 or r_min < 0.05 is
labelled non-continuable and not scored).
- *Predicted before running:* ΔE₂/F² = −n⁶/2 within 1% (the first-run value at n = 1 is
  −0.500, so the n = 1 entry is not a blind prediction; n = 2, 3, 4 are: −32, −364.5, −2048).
  F² scaling at each n (ratio of two field strengths 4.00 ± 0.05).
- *Reference values, not registered as predictions:* the standard account's exact second-order
  shift, −(n⁴/16)(17n² − 3k² − 9m² + 19) F² (Landau–Lifshitz, recalled), evaluated for the
  quantum states nearest the circular routes (k = 0, m = n − 1). The classical route has
  L_z = n and the quantum state has m = n − 1; this offset of one unit in the angular
  momentum is part of what is being measured.
- *Question for the comparison:* does the ratio classical/standard rise toward 1 as n grows
  (the correspondence limit), and how large is the shortfall at n = 1, 2?
- *Rejection criterion:* the hypothesis "the classical seat route reproduces the ground-state
  polarisability" is rejected if |ΔE₂|/(9/4 F²) differs from 1 by more than 5% for the n = 1
  stable member. The prediction above places it outside that band (rejection expected).
  The correspondence statement is rejected if the ratio does not increase monotonically with n.

---

## Audit correction 2026-10-05 (gating)

**Finding:** The pre-registered count criterion could not have failed because the seat definition fixes the count (stated in the record).

**Correction:** Replace it with a criterion independent of the seat definition, such as component spacing at a stated field.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
