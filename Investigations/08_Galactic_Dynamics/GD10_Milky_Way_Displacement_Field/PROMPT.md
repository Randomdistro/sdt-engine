# GD10 — Milky Way Displacement Field: bulge shells, arm sheaths, equalisation, emission depth

Pre-registration, 2026-10-16. Written before the tool exists and before any field is computed.
Operator specification: the pasted master specification of 2026-10-16 (adversarial posture,
`sdt::laws` bindings, tombstones, certification tiers) binds this investigation; the repository
gateways govern register (CONSTRUCTION, not IDENTITY, for the label of a true-by-construction relation).

## Object

Model the Galaxy's displacement field as the Operator described it, in the smallest form the canon
allows, then compute its effect on emissions at depth:

1. the bulge as recursive displacement shells;
2. the spiral arms as curved sheaths of displacement (GD08 geometry);
3. a compounding of spation pressure where bulge and arm fields overlap;
4. equalisation: displacement pushed along each sheath from higher pressure to lower;
5. the effect on the spectral position of emission from sources at depth.

Steady state only. No time evolution, no arrow of time: the equalised field is a stationary solution.

## Native definitions (canon, from `laws.hpp`; no constant added)

- Per-baryon displacement length ϟ_b = `bridge::koppa_per_baryon` (1.2419×10⁻⁵⁴ m).
- Depth in the dilute limit: Z(x) = ϟ_b Σ_i w_i / |x − x_i| (Depth-closure z = ϟ/r, superposed over
  baryons; each baryon displaces). Rotation bridge: v_c²/c² = −R ∂Z/∂R.
- Closure composition: (1+z) multiplies across shells and across emitter→observer. Pair shift
  (1+z_pair) = (1+Z_emit)/(1+Z_obs).
- Pressure at local depth: P = P_conv (1+Z)⁴ (Law II form). **H1 (hypothesis):** Law II's z may be
  replaced by the local depth Z. Not canon; labelled.
- No G, no M(kg), no dark matter, no ψ, no metric, no exponential eclipse factor 1−exp(−r/λ_s) (tombstone).

## Hypothesis H2 — equalisation along sheaths (the Operator's mechanism, minimal form)

Displacement is pushed along each arm sheath from higher pressure to lower, so pressure differences
along the sheath relax. On the ridge arc length s the equalised depth Z_eq solves

  Z_eq − λ² d²Z_eq/ds² = Z_dil,  reflecting ends,

a conserving operator (∫Z ds unchanged). λ is the equalisation length. **λ is not fitted.** It is
scanned λ ∈ {0.5, 1, 2, 4, 8, 16} kpc plus the two limits λ→0 (no equalisation, the dilute field) and
λ→∞ (each sheath at its mean depth). Results are reported as a function of λ, never at a chosen λ.
Off the ridge the field is Z_eq(x) = Z_dil(x) + g(d) ΔZ(nearest node), g = exp(−d²/2σ_in²),
d the distance to the nearest ridge node, σ_in from GD08.

Conduits: tiers measured + near-extended (GD08 flags 1 and 0) are primary. A second run adds the
continued far-side tier (flag 2) to the conduit only; the far side carries no baryon excess in either run.

## Bulge as recursive shells

Bulge baryons are placed in the BH&G 2016 exponential profile ρ ∝ exp(−s), s = |(x/h_x, y/h_y, z/h_z)|,
(h_x, h_y, h_z) = (0.70, 0.44, 0.18) kpc, major axis 27° (GD08). Nested shells at s = 0.5, 1, 2, 3, 4, 6, 10.
Per shell: baryon count, ϟ_k = ϟ_b N_k, the depth it adds at the outer edge of each shell inside which
it is nested, additively and by multiplicative closure composition. The recursion records how much the
composition differs from the sum (the compounding).

## Inputs (OBSERVED; each from the cited source, GD08/GD09 values unchanged)

- Arm ridges, σ_in(R), σ_z(R): GD08 `mw_arms_data.js` (Reid 2019 Table 2, §3). R₀ = 8.15 kpc, Sun at z = +5.5 pc.
- Baryon counts, central values (GD09 `mw_baryons.js`): bulge stellar 1.84×10⁶⁷ + bulge gas 1.31×10⁶⁶
  in the bulge profile; thin disc 4.16×10⁶⁷ (R_t 2.6, z_t 0.30 kpc); thick disc 7.14×10⁶⁶ (R_T 2.0, z_T 0.90);
  cold gas disc 9.63×10⁶⁶ (exponential scale 2 R_t = 5.2 kpc over 2–19 kpc, BH&G 2016 §6.4.4; vertical
  scale 0.10 kpc is a numerical choice with no effect at R ≫ z).
- Excluded: stellar halo (0.9% of stellar mass, profile not read) and hot corona (suspected, profile
  model-dependent). Their omission lowers Z by an amount stated in the assessment.
- Arm overdensity: arm/interarm K-band contrast 1.32 (Drimmel & Spergel 2001, cited by a review; the
  review notes it may be underestimated; kinematic estimates ±20% at the solar radius). Applied to
  thin-disc and gas particles as a Gaussian cross-section, σ_in(R), on tiers 0 and 1 only, with total
  counts conserved. A run with contrast 1 is the baseline.
- Comparison values (loaded after the model is fixed): Θ₀ = 236 ± 7 km/s (Reid 2019 Table 3, fit A5);
  Loeb 2022 estimate −0.024 km/s per kpc for the Galactic redshift gradient at 8 kpc (a theoretical
  estimate, standard-physics route); Gaia RV scatter ~300 m/s (HARPS–Gaia wide-binary comparison).

## Numerical representation

Deterministic mt19937_64, ~2.4×10⁵ equal-weight particles per component set, Plummer softening
0.03 kpc. Monte-Carlo noise is measured from two independent seeds; an effect is reported only where it
exceeds 3× that noise.

## Instrument validation (before use, known answers)

- V1 point baryon: Z = ϟ_b N/r to 1e-3.
- V2 shell theorem: uniform shell, outside Z = ϟ_b N/r (0.5%), inside Z constant (1%).
- V3 uniform thin disc, on axis: Z = (2ϟ_b N/a²)(√(z²+a²) − z) (1%).
- V4 equalisation operator: λ→0 identity, λ→∞ mean, ∫Z ds conserved to 1e-9.
- V5 radial-gradient routine: rotation bridge on a point mass returns v²/c² = ϟ_b N/r (1e-3).
- V6 closure composition: product of (1+Z_k) equals the single-step value for a shared locus (1e-12).

## Comparisons (single pass, one criterion each)

- C1 baryon-only rotation bridge at R₀: v_c²/c² from the dilute field against (Θ₀/c)². Criterion:
  |ratio − 1| ≤ σ_comb, with σ_comb the quadrature sum of the stars-plus-cold-gas uncertainty (8%, GD09)
  and 2 × 3% for Θ₀. The ratio is reported either way.
- C2 the mechanism: ratio after bulge shells + arm contrast + equalisation (every λ) against the same
  criterion. Equalisation conserves ∫Z ds and compounding enters at O(Z²) with Z ~ 10⁻⁶; this registers
  the expectation that neither closes a first-order gap. The result is reported as computed.
- C3 emission-depth gradient at R₀: c ∂Z/∂R from the dilute field against Loeb's 0.024 km/s per kpc
  (convergence note only; no threshold).

## Outputs (emission at depth)

Pair shift c·z_pair (m/s) for emitters on a grid of Galactic longitude (0–350°, 10° steps) and distance
(2, 4, 6, 8, 10 kpc), for the dilute field, the arm-contrast field and the equalised fields; arm-ridge
profiles c·Z(s); sheath-versus-interarm contrast; ΔP/P = 4Z; and the effect of equalisation against the
Gaia RV scatter.

## Scope

A record of what the specified mechanism does inside the canon's nonlinearity. No claim that the
equalised field is the real field, and no fitting of λ. Dark matter is not an input and not an output.

---

## Amendment 1 (2026-10-16, before any field was computed)

First run stopped at validation; no field was evaluated. Two instrument faults, recorded in place:
- V6: the coded tolerance was 1e-18, below double-precision rounding of (1+Z) at Z ~ 1e-7; the
  registered tolerance (1e-12) is restored. The shell compounding is computed with log1p/expm1.
- V4b: the tridiagonal solver is ill-conditioned at λ = 10⁶ kpc (relative error 4.9×10⁻²). The λ→∞
  limit used in the model is the closed-form sheath mean (weighted by cell length), not the solver, so
  V4b is restated as: the solver at λ = 10³ kpc (≫ every sheath length) approaches the closed-form mean
  to 10⁻³ relative. The scan λ ≤ 16 kpc is far inside the solver's conditioned range.
No threshold in C1–C3 and no model rule is changed.

---

## Correction 1 (2026-10-16, Operator ruling; withdrawals stay visible)

The Operator ruled that GD10 conflated depth Z and speed terms with background pressure and
velocity by redshift, and that the disc is to be treated as a plain static disc with no
preconception about its velocity. Recorded as withdrawn from GD10:
- C1 and C2 (rotation-bridge comparison with Θ₀): withdrawn as a test of the mechanism; the
  comparison imports a velocity premise the static disc does not carry.
- The presentation of depth as c·Z in m/s and pair shifts as velocities: withdrawn.
- H1 (P = P_conv (1+Z)⁴ at local depth): withdrawn. The engine (`laws.hpp`, law_I) marks the
  P ∝ (1+z)⁴ closure a research hypothesis, not an engine law, and its sign (higher z, higher
  pressure) is opposite to GD06's local relation (pressure deficit gives depth).
- Retained as computed, not as the Operator's mechanism: the dilute depth-bridge field Z = ϟ_b Σ w/r
  and the equalisation operator H2, as a record of what that route gives.
Successor: GD11 (static-disc displacement cascade and macro throughput).
