# GD11 — Static-disc displacement cascade and macro throughput

Pre-registration, 2026-10-16. Written before the tool exists and before any field is computed.
Successor to GD10 after the Operator's ruling of 2026-10-16 (GD10 `PROMPT.md` Correction 1).
The pasted master specification of 2026-10-16 binds the work; repository gateways govern register.

## Premises (Operator, 2026-10-16)

1. The disc is plain and static, as seen. No velocity, rotation, redshift or proper motion enters
   as an input, a comparison or a calibration. Positions and baryon counts only.
2. Every central body, beginning with Sgr A* and moving outward, displaces a shell of spations, which
   displaces a shell of spations, which displaces a shell of spations. The cascade continues well past
   the visible (IR) extent of the disc.
3. Two things cannot occupy the same relative position (exclusion).
4. Matter blocks spations from the CMB.
5. Matter passes the ontic at a much slower rate.
6. Displacement breeds displacement, which breeds pressure gradients.
7. Throughput is modelled on a macro scale. Follow the mathematical structure to its conclusion.

"IR horizon" is read here as the visible extent of the disc and the radius beyond it; the table in the
tool prints the disc extent, the displacement horizon below, and the Clearing distance R_CMB together.

## Canon quantities used (all from `laws.hpp`; none redefined)

ℓ_P; N = R_CMB/ℓ_P (5.894×10⁶¹ shells); S = 4πN² boundary cells; u_CMB; ε = u_CMB ℓ_P³;
Φ = Nε; P_conv = Φ/ℓ_P³; P_rad = u_CMB/3; V_disp_p = 3 m_p ℓ_P³ c²/Φ (proton exclusion volume,
Law IV) and R_excl_p; R_p_lock (target-free proton boundary radius, Law III); the common interaction
radius of Law III (`law_III::R_charge` in the engine; written R_int here); `bridge::koppa_per_baryon`
(comparison column only); `bridge::N_baryons(bridge::koppa_Sun)` (solar-mass conversion without kilograms).
The engine marks P ∝ (1+z)⁴ a research hypothesis. It is not used.

## Structure (derived before computation)

S1 Exclusion and displaced volume. Each baryon excludes V_p = V_disp_p of spation volume, n_p = V_p/ℓ_P³
spations. Displaced spations cannot vanish; the volume is carried outward. With volume density
ρ_V(x) = n_b(x) V_p, the displacement field is curl-free with ∇·u = ρ_V and u → 0 at infinity:

  u(x) = (V_p/4π) ∫ n_b(x') (x − x') / |x − x'|³ d³x'.

Volume-flux conservation: ∮ u·dA = V_enc, the displaced volume enclosed by the surface.

S2 Cascade. For spherical equivalent shells about the Galactic centre, shell k shifts by
δ_k = V_enc(r_k)/(4π r_k²). Outside the sources each shell displaces the next with the flux conserved:
δ_{k+1} r_{k+1}² = δ_k r_k². In lattice units δ/ℓ_P is the number of spation pitches a shell is shifted.
The displacement horizon r_1 is the radius at which δ = ℓ_P: r_1 = √(V_enc/(4π ℓ_P)). Beyond r_1 the
shift is smaller than one pitch. The shift at the Clearing is δ(R_CMB)/ℓ_P = n_d/S, n_d = V_enc/ℓ_P³.

S3 Blocking. A baryon blocks inbound spations over a cross-section σ_occ. In the dilute regime
(τ ≪ 1) the blocked sky fraction at x is Θ(x) = σ_occ Θ̃(x), with Θ̃(x) the mean baryon column density
over the sky, Θ̃(x) = (1/4π) ∮ N_col dΩ = (1/4π) ∫ n_b(x')/|x − x'|² d³x'. The vector (1/4π) ∮ N_col n̂ dΩ
points toward the more-blocked sky and equals minus the displacement field divided by V_p; the blocked-sky
anisotropy and the displacement field are one field. First-order truncation error in Θ is ≤ τ_max/2, reported.
σ_occ is the open item of GD06 (XSD-B). It is not chosen. Three canon-geometric values bound it:
σ_excl = π R_excl_p², σ_p = π R_p_lock², σ_int = π R_int². Θ is reported for each and as Θ̃ (σ-free).

S4 Slow passage. Matter passes the ontic at a rate s ≪ 1 relative to vacuum. For steady flux the content
density inside matter scales as 1/s, so the macro-averaged change carries the volume fraction
φ_V = n_b V_p times (1/s − 1); the blocking limit s → 0 is the full cross-section of S3. s is PENDING;
φ_V is reported so the bound is visible.

S5 Pressure and gradients. P(x)/P_ref = 1 − (1 − s) σ_occ Θ̃(x), P_ref = P_rad at the macro scale.
Gradient ∇P = −P_ref (1 − s) σ_occ ∇Θ̃.

S6 Sheaths. The arms are the GD08 ridges (Reid 2019). Resistance per unit length along a path is
b(x) = n_b σ_occ. "Pushed along the arms" is tested as geometry of the field, not assumed:
 M1 ⟨|û·t̂|⟩ (û the displacement direction, t̂ the ridge tangent) per arm, against ⟨|r̂·t̂|⟩ (the geometric
    projection of a radial field onto the ridge);
 M2 the fraction of the outward displaced-volume flux that the sheath cross-sections (area π σ_in σ_z)
    carry along the ridge at R = 5, 8, 12 kpc;
 M3 contrast of Θ̃ and |u| on the ridge against the ring mean at the same R;
 M4 the two source regimes along each ridge: |u_bulge|, |u_disc|, their cosine (reinforce when → 1),
    and the radius at which |u_bulge| = |u_disc|.

S7 Emission at depth. The map from blocked-sky fraction to the spectral position of emission is the
GD06 closure z_d = h(Θ), h(0) = 0, monotone, dilute h ≈ h₁ Θ, h₁ PENDING. The tool reports Θ̃ and Θ
patterns (normalisation-free ratios, and per bound), and z_d per unit h₁. No pressure-to-redshift power
law is used. The ϟ_b depth-bridge value Z = ϟ_b Σ w/r is printed beside it for the same distribution as a
labelled comparison route; the two have different kernels (1/r² against 1/r), and the difference between
them is the open h(Θ) of GD06.

## Inputs (OBSERVED; GD08 geometry and GD09 counts unchanged)

Arm ridges, σ_in(R), σ_z(R): GD08 `mw_arms_data.js`. Counts (GD09 `mw_baryons.js`, central values): bulge
1.84×10⁶⁷ + bulge gas 1.31×10⁶⁶ (BH&G exponential profile, h = 0.70/0.44/0.18 kpc, 27°); thin disc 4.16×10⁶⁷
(R_t 2.6, z_t 0.30 kpc); thick 7.14×10⁶⁶ (R_T 2.0, z_T 0.90); cold gas 9.63×10⁶⁶ (scale 5.2 kpc over 2–19 kpc,
vertical 0.10 kpc numerical); Sgr A* 5.0×10⁶³ baryon-equivalents (mass conversion; baryon content not observed).
Arm overdensity 1.32 on thin disc and gas, tiers measured and near-extended, counts conserved (Drimmel &
Spergel 2001 via a review). Stellar halo and corona excluded. **Not used anywhere:** Θ₀, any rotation curve,
Gaia RV, Loeb 2022, any redshift or velocity.

## Numerical representation

Deterministic mt19937_64, ~2.4×10⁵ particles, Plummer softening 0.03 kpc. Noise from two seeds; an effect is
reported only above 3× noise.

## Instrument validation (before use, known answers)

V1 `law_IV::mass_from_V_disp(V_disp_p)` equals m_p (1e-12). V2 shell theorem for u: outside a uniform shell
|u| = V N/(4π r²) (0.5%); inside, |u| ≤ 1% of the surface value. V3 flux conservation: ∮ u·dA = V_enc over
spheres of radius 2 and 5 kpc about a ball (1%). V4 Θ̃ at the centre of a uniform sphere = n a (0.5%) and at
d = 0.6 a equals n [a/2 + (c²/2d) asinh(d/c)], c² = a² − d² (0.5%). V5 cascade recursion identity (1e-12).
V6 noise from two seeds.

## Classification criteria (pre-registered; every class populated)

For "the arms are channels for displacement along their length":
- supported if M1 ≥ 0.5 and M2 ≥ 10%;
- not supported if M1 within 0.05 of ⟨|r̂·t̂|⟩ (the field crosses the arms as a radial field does) or M2 < 1%;
- marginal otherwise.
For the displacement horizon: reported against the disc extent (15 kpc drawing limit) and R_CMB.
For validity of the dilute first-order form: τ_max ≤ 0.1 for each σ bound.

## Scope

A record of what the static-disc structure determines and what it leaves open (σ_occ, s, h₁). No value is
chosen for any of the three. No comparison with any velocity or redshift observation is made.

---

## Amendment 1 (2026-10-16, before any field was computed)

First run stopped at validation; no field was evaluated. V4 failed by −4.8% (centre) and −5.6%
(d = 0.6 a): the Plummer-softened 1/d² sum under-counts the mean column by n ε π/2 per unit
(1/4π)∮, exactly −(π/2) ε/a = −4.7% on a 1 kpc ball at ε = 0.03 kpc. The bias is analytic for a
smooth density, so the sum is corrected by raw_true = raw_sum + 2π² n ε with n the analytic local
density, and V4 is restated to test the corrected form (0.5%). Production fields apply the same
correction with the K = 1 analytic density (arm modulation changes it by < 0.1% of the column).
V6 (particle sum against ray quadrature on the analytic density at the Sun and centre, 3%) is added
as the second route for the mean column. No model rule or criterion changes.

---

## Amendment 2 (2026-10-16, numerical resolution only; no rule, input or criterion changed)

The first full run (2.4×10⁵ particles) gave node-level Monte-Carlo noise of 2.45% (Θ̃) and 3.69% (|u|),
comparable to the arm contrasts being measured. Recorded before the rerun, for the record: Sun Θ̃ =
2.106×10²⁶ m⁻², |u| = 1138.6 pitches; M1 = 0.160 against geometric 0.155; M2(8 kpc) = 9.7×10⁻⁵;
τ_max(σ_int) = 0.29; displacement horizon 272.1 kpc. The particle count is raised to 10⁶ to reduce noise
(expected factor ≈ 2). The cascade labels (0.01 and 0.1 pc printed as "0 pc") and the M4 output (adds the
fraction of nodes where the bulge field dominates) are display fixes.
