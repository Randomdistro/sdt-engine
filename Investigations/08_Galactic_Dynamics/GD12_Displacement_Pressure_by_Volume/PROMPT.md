# GD12 — Displacement pressure by volume: shell depth, macro-shells, competition, emission depth

Pre-registration, 2026-10-16. Written before the tool exists and before any field is computed.
Successor to GD11 on the Operator's statement of the measure (2026-10-16). The pasted master specification
binds the work; repository gateways govern register.

## NO TWEAKING (Operator instruction, binding)

No parameter is set, changed or implied after any result is seen. No observed value is used as a target, a
calibration, or an implied-parameter computation. No threshold below is changed after a run. The only inputs are
the engine's canon quantities, GD08 geometry and GD09 counts (frozen), and one flagged shared input (the BBN baryon
ratio for the uniform ambient term). A validation fault is repaired by dated amendment before any result is
reported, never by changing a rule. Results are reported as computed. GD11's implied-product paragraph is
withdrawn for exactly this reason (GD11 assessment, Correction 1).

## The measure (Operator)

Displacement pressure is measured by volume. Each volume of displacement begets a volume of displacement. The
displaced volume is known only by shell depth. Macro-shells (averages over 100 shells) carry a close pressure
side and a far pressure side, which map the gradient. When macro-shells compete they either push each other out
of the way or raise the pressure where they meet until the volume depths are equal. Pressure is always higher in
the direction of the nearest mass, plus the general overall pressure (the Earth in the Sun's gradient).

## Definitions (canon quantities only; no cross-section, passage rate or closure constant)

D1 Displaced volume of a body of N baryons: V = N V_p, V_p = `law_IV::V_disp_p`.
D2 Shell depth: k = r/ℓ_P, the number of Planck shells from the body. The displaced volume V is carried through
   every shell (volume conservation: each shell sweeps V). Pressure by volume is the displaced volume per shell
   volume:  f(k) = V/(4π k² ℓ_P³)  (dimensionless; equal to the number of pitches the shell is shifted).
D3 Macro-shell of n = 100 shells starting at depth k₀: close side f_c = f(k₀), far side f_f = f(k₀ + n), mean over
   the n shells, gradient (f_f − f_c)/(n ℓ_P). The enumeration count k₀/n is printed. Relative close–far step:
   f_c/f_f − 1 = 200/k₀ + 10⁴/k₀² (evaluated analytically; double precision cannot resolve it by subtraction).
D4 Superposition (volumes add; two things cannot occupy the same position):
   f_total(x) = f_amb + Σ_i f_i(x). For distributed baryons Σ_i f_i(x) = (V_p/ℓ_P) Θ̃(x), Θ̃ the mean baryon column
   (GD11). f_amb is the uniform ambient term: f_amb = n_b0 V_p N, with n_b0 = η n_γ from the engine
   (`bridge::release_acoustics::eta_bbn_deuterium` × `photon_count(T_CMB)`). η is a BBN input shared with other
   chains; it is flagged, and f_amb is never used to choose anything.
D5 Competition. Source i dominates at x where f_i is largest. Two sources A, B meet where f_A = f_B (equal volume
   depth). At the meeting the pressure is the sum f_A + f_B. Pushing aside and raising until equal depth have the
   same end state, the equal-f surface. For two point bodies on a line the meeting point satisfies
   x/(D − x) = √(V_A/V_B) from A (Apollonius).
D6 Direction. ∇f points toward the nearest mass (f increases toward mass). No force direction is asserted.
D7 Emission at depth. Δf = f_total(emitter) − f_total(observer), in pitches, and the ratio f_total(emitter)/f_total(observer).
   The closure from f to the spectral position of emission is open (GD06) and is not supplied; patterns only.

## Computations

A. Shell-depth table: k, macro-shell count, f_c, f_f, relative step, gradient, at r = 1 m, R_Earth, 1 AU,
   R_Sun, 1 pc, 1 kpc, 8.15 kpc, the displacement horizon of the Galaxy, R_CMB. Spherical, one body.
B. Earth in the Sun's gradient: N_Sun = `bridge::N_baryons(bridge::koppa_Sun)`, N_Earth =
   `bridge::N_baryons(bridge::koppa_Earth)`, D = 1 AU. f_Sun at the Earth, f_Earth at its surface and at 1 AU/Earth-scale,
   gradients, the Earth–Sun meeting point, the pressure at the meeting, the Sun's gradient against the Earth's own at
   the Earth's surface. Printed as computed; no comparison with any observed radius or acceleration.
C. Galaxy: f_total on the plane, per component (Sgr A* at 5.0×10⁶³ baryon-equivalents, bulge, thick disc, thin disc
   with arm overdensity 1.32, gas), dominance partition, meeting surfaces, ∇f.
D. Tests (classification below), arms, emission patterns.

## Inputs (frozen)

GD08 `mw_arms_data.js`; GD09 `mw_baryons.js` central values; the same component profiles as GD11 (bulge
exponential h = 0.70/0.44/0.18 kpc at 27°, thin R_t 2.6 kpc z_t 0.30 kpc, thick R_T 2.0 z_T 0.90, gas scale 5.2 kpc
over 2–19 kpc, vertical 0.10 kpc numerical); arm overdensity 1.32 on thin disc and gas, measured and near-extended
tiers, counts conserved. Halo and corona excluded. No velocity, rotation, redshift or proper motion enters.

## Instrument validation (before use, known answers)

V1 macro-shell algebra: f_c/f_f against (1 + n/k₀)²; the exact relative step against 200/k₀ + 10⁴/k₀² (1e-12).
V2 volume conservation: f(k) × 4π k² ℓ_P³ equals V at every k tested (1e-12).
V3 meeting point: numerical root of f_A = f_B equals the Apollonius closed form (1e-9).
V4 mean column on a uniform ball, softening-corrected: centre and d = 0.6 a (0.5%), as GD11.
V5 gradient kernel: particle-sum ∇f on a uniform ball at d = 0.6 a against the derivative of the closed form (2%).
V6 particle sum against ray quadrature for Θ̃ at the Sun and centre on the analytic density (3%).
V7 noise: two seeds.

## Classification (pre-registered; every class populated)

T1 "Pressure is always higher in the direction of the nearest mass." Over the plane grid inside R < 15 kpc, the
   fraction of points where ∇f·(direction to the baryon-weighted centroid within 1 kpc) > 0 (T1a), and the fraction
   where ∇f·(direction to the Galactic centre) > 0 (T1b). Holds if ≥ 99%; fails if < 90%; marginal otherwise.
T2 Competition: the radius at which the Sgr A* term equals the sum of the other terms (spherical, along the plane),
   and, along each arm ridge, the radius where the bulge-regime f (Sgr A* + bulge) equals the disc-regime f
   (thick + thin + gas); the fraction of ridge nodes where the bulge regime dominates. Reported, no threshold.
T3 "Displacement pressure is pushed along the arms." ⟨|∇f·t̂|/|∇f|⟩ over measured and near-extended ridge nodes
   against the geometric ⟨|r̂·t̂|⟩ of a radial field. Supported if ≥ 0.5; not supported if within 0.05 of the
   geometric value; marginal otherwise.
T4 Ambient: f_amb against f_total at the Sun and the centre, reported as ratios. No threshold.

## Scope

A record of what the displaced-volume pressure field is on a static disc and what the meeting surfaces are. The
closure to emission position stays open and is not supplied. Nothing is matched.

---

## Amendment 1 (2026-10-16, before any field was computed; no rule, input or classification changed)

The first run stopped at validation. Two faults in the test construction, both recorded here:
- V1: (1 + 100/k₀)² − 1 cannot be formed by subtraction in double precision at k₀ ~ 10³⁴ (it returns 0; the
  PROMPT's D3 already states that double cannot resolve the step by subtraction). V1 is restated as the same
  algebraic identity tested at resolvable depths k₀ = 10³, 10⁵, 10⁸ (1e-12). At the physical depths the analytic
  relative step 200/k₀ + 10⁴/k₀² is used directly.
- V5: a single-point gradient on a Monte-Carlo ball is noise-limited at about 7% (nearest particles lie at ~0.016 kpc
  against ε = 0.03 kpc). V5 is restated as the radial component of ∇f averaged over 400 directions at d = 0.6 a,
  against the derivative of the closed form (2%).

## Amendment 2 (2026-10-16, before any field was computed; test depths only)

V5 passed after Amendment 1 (−1.1%). V1 still failed (3.8×10⁻¹¹) because the subtraction (1 + 100/k₀)² − 1 at
k₀ = 10⁸ carries a double-precision rounding of about 10⁻¹⁰ relative. V1 is restated at k₀ = 10³, 10⁴, 10⁵, where
the step is resolvable to better than 10⁻¹³. No rule, input or classification changes.

## Amendment 3 (2026-10-16, gradient instrument; no definition, threshold or classification rule changed)

First complete run (10⁶ particles, particle-sum gradient). V7 (two seeds): f_local noise 1.25%, but in-plane
|∇f| noise **26%**, because the 1/d⁴ gradient kernel is dominated by the nearest particles. Direction-based
classifications cannot be reported at that noise. Recorded for the record, not used: T1a 0.8003, T1b 0.8053;
T3 ⟨|∇f·t̂|/|∇f|⟩ = 0.538 against geometric 0.155 (a randomly oriented in-plane vector has mean |cos| = 2/π = 0.64).
The gradient for T1 and T3 is replaced by a deterministic instrument: f from fixed-direction ray quadrature on the
analytic densities (including the arm overdensity, grid-tabulated and renormalised so counts are conserved),
and ∇f by central differences of that smooth quadrature (h = 0.05 kpc). New validation:
V8 mean over ridge nodes of f(ray)/f(particle sum) − 1 within 3%;
V9 ring-mean radial derivative at R = 6–10 kpc from the ray instrument against the particle-sum ring mean (5%).
The classifications T1 and T3 are then reported whatever they are. The particle-sum f (1.25% noise), shell tables,
Earth–Sun case, dominance, ambient and emission patterns are unchanged.
