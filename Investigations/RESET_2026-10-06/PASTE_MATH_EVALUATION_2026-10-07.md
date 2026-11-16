# Evaluation of the mathematics in the pasted text (2026-10-07)

> **CORRECTION 2026-10-08 (shadow analysis, `SHADOW_ANALYSIS_2026-10-08_ASSESSMENT.md`).** Original text left in place; each item below is also marked where it stands.
> - **C7:** the reason "reflects that 42.98 is the value general relativity predicts" is withdrawn as inadmissible, and the ±0.04″/cy uncertainty is superseded. The admissible trace is that AU and a_Mercury enter in metres from ranging light-times × c, while R_Sun cancels. So the closure tests the 6π law, not c.
> - **C3/C7:** these are one fact, with c_cl/c = (ϟ_M/ϟ_E)^(−1/2).
> - **C2:** the paste's ρ equals 1 − ε_θθ, the tangential density, and is consistent under that reading.
> - **Correction (3) above:** the mass 1.017 ± 0.025 is from Joyce et al. 2018 (80.65 ± 0.77 km/s, 0.00803 R☉), not Barstow et al. 2005. That pair gives 1.0178 ± 0.0170 against the dynamical 1.018 ± 0.011.
> - **Correction (4):** the solar spectroscopic datum is now checked: 638 ± 6 m/s measured against 633.13 m/s predicted (+0.81σ).

> **CORRECTION 2026-10-07, at Harvey's challenge on zk² = 1.** Check C3 and the verdict "zk² = 1 is CONSTRUCTION" are corrected as follows; the original text below is left in place. (1) The identity I checked (z = ϟ/r and k = c/v built from one v, to 2×10⁻¹⁶) is the algebra of the definitions. That is not how the relation is used. With z the measured spectroscopic shift Δλ/λ and k = c/v from an independent dynamical or kinematic determination, zk² = 1 could have failed and is a test; the gateway's own rule (behavioural §1, the CONSTRUCTION entry) says such a relation is never labelled CONSTRUCTION. The verdict line is withdrawn. (2) What the relation gives: ϟ = zR, so GM-equivalent c²ϟ = c²zR and the surface circular speed v = c√z, from one spectrum and a radius, with no G, no mass and no orbit; the route through orbital dynamics needs a period and a semi-major axis (and a mass needs G in addition). In that sense it is the faster route, and "my calculation plus the observation" is what yields GM. (3) How well it has been tested, from searches (not read in full): the Sun, where the measured line shift is dominated by the convective blueshift (about −300 m/s at disc centre against a gravitational +636 m/s at infinity, 633 m/s at Earth), with the convective correction uncertain by tens of m/s up to about 100 m/s; and Sirius B, where Hubble Balmer-line spectroscopy gave a redshift of 80.42 ± 4.83 km/s (about 6%) and a redshift-derived mass of 1.017 ± 0.025 solar masses against a dynamical 1.018 ± 0.011 [Barstow et al., MNRAS 362, 1134 (2005), via a search result]. So, as an independent-chain test, zk² = 1 stands at the level of a few per cent to ten per cent in the cases I found. For the Sun it is not the better route in precision: GM from orbits is known to about 1 part in 10¹⁰. It is the better route where no orbit is available (isolated stars, white dwarfs). (4) The engine's comment (`laws.hpp:2725`) that the solar value "equals the observed GM/(c²R) to 0.03%" refers to GM and R, not to a spectroscopic redshift; the spectroscopic test of the Sun is therefore not in the repository (a manifest row for a measured solar gravitational redshift, with the convective correction stated, is PENDING). (5) The expression typed in the message, "delta lambda / lambda × (R/k)^(R/k) = 1", is not zk² = 1; I read it as zk² = 1 (equivalently zR/ϟ = 1 with ϟ = R/k²). If it carries something else, I have not evaluated it.

Instrument: `paste_math_eval/paste_math_eval_1.cpp`; output `paste_math_eval/paste_math_eval_1_results.txt` (MSVC 19.44, constants from `sdt::laws`). Validations first (VA orbit integrator on the Newtonian case: precession −1.4e-12 rad/orbit and energy drift 8e-13; VB deflection quadrature against the analytic form: 1.3e-9), then the checks. Check C1b was added after the first run, at the end of the C1 block, and is marked so; no criterion was changed after a result was seen. Register: "consistent / inconsistent within the stated tolerance", CONSTRUCTION, derived / not derived.

## 1. What the pasted text shows as mathematics, and what it only asserts
The pasted text contains equations in three places: the single-sphere displacement derivation, the velocity law with its identity (v = (ck)√(R/r), zk² = 1), and the displayed formulas that the other system wrote for what the historical figures "would" do. Everything else in your messages is a statement of results without the derivation in the text.

| Claim | Mathematics shown in the paste? | Evaluated here |
|---|---|---|
| Gravity from the displacement of one sphere (volume bookkeeping, shells to one spation thick) | Yes (derivation) | C1, C1b, C2 |
| v = (ck)√(R/r); zk² = 1; redshift, "octave" | Yes (two formulas) | C3 |
| The 1/r² and 1/r³ forces in a modified Kepler III; Mercury | Stated, not derived | C4, C5 |
| Shapiro delay, gravitational redshift, pressure-dependent light speed | Stated, not derived | C6, C3 |
| c from orbital geometry | Not in the paste; in the engine (`laws.hpp:1214–1265`) | C7 |
| n-body "solved"; Coulomb, Riemann, Casimir, the pillars of relativity; nuclear gear structure; magnetism as thrust; the particle zoo; singularities eliminated; the cycle of expansion and recompression; the feather and the bowling ball | Asserted; no equations | §4 |

## 2. Results

### C1 — arithmetic of the displacement derivation: reproduced
With R₀ = 8.4×10⁻¹⁶ m: Ω₀ = 2.4827×10⁻⁴⁵ m³; N_disp = Ω₀/((π/6)ℓ_P³) = 8(R₀/ℓ_P)³ = 1.123×10⁶⁰; R_term = √(R₀³/(3ℓ_P)) = 3.496×10⁻⁶ m (3.504×10⁻⁶ m with R_lock). The pasted 1.1×10⁶⁰ and 3.5 µm are correct. Two notes: (a) the count divides by the volume of one sphere, (π/6)ℓ_P³, which assumes 100% filling; with close packing (cell ℓ_P³/√2) the count is 8.316×10⁵⁹, a factor 0.7405 of the pasted value; (b) R_term does not depend on that choice, because it uses only ℓ_P as the shell thickness.

### C1b — scaling with the number of baryons (added after the first run)
Volumes add, so R_term(N_b) = R_term(1)√N_b. R_term equals the causal depth R_CMB = 9.527×10²⁶ m at N_b* = 7.43×10⁶⁴ baryons (N_b*·m_p = 1.24×10³⁸ kg, about 6×10⁷ solar masses with the IAU value used as a conversion only). Bodies with fewer baryons have a displacement field that falls below one ℓ_P per shell inside the causal depth; bodies with more keep it above one ℓ_P per shell to the boundary. This is a computed consequence of the construction as pasted; it depends on R₀³, ℓ_P and R_CMB, and I make no claim about what it means. It is recorded in the coincidences addendum as an item to watch (C-008).

### C2 — the displacement field and the density statement
For an incompressible volume source u_r = Ω/(4πr²) the divergence is zero outside the source (worst |∇·u|/(u/r) = 9.8×10⁻¹³, rounding), and the strains are ε_rr = −2Ω/(4πr³) and ε_θθ = ε_φφ = +Ω/(4πr³) with zero trace. Consequences:
- **Correct in the paste:** the 1/r² displacement from volume conservation; the shear energy density scaling as r⁻⁶ and a finite self-energy from R₀ outward.
- [2026-10-08: holds only for the volume-density reading; the stated ρ equals 1 − ε_θθ exactly (shadow S4)] **Inconsistent with the same premise:** the statement that the spation density varies as ρ₀(1 − Ω₀/(4πr³)). With ∇·u = 0 the density is constant outside the source. If the medium is compressible the displacement field is a different problem, and the 1/r² form no longer follows.
- **Not shown:** the step from a displacement field to a force. The 1/r² of a displacement is the 1/r² of conserved volume through a sphere; the 1/r² of a force needs the occlusion argument (the solid angle of the shadow, πR²/r², which is Law III) or a gradient of a conserved quantity (the strain, ∝ 1/r³, is the natural candidate and is the 1/r³ you cite).
- **Not shown:** the refractive index n = 1 + αΩ₀/r. Nothing in the displacement field gives that form.

### C3 — the velocity law, zk² = 1, and the redshift
- v = c√(ϟ/r) is the circular-orbit speed of an inverse-square attraction with c²ϟ = GM, so Kepler's third law follows exactly: T² = 4π²r³/(c²ϟ).
- [2026-10-08: the label applies to this check only, not to the relation; see the 2026-10-07 correction] zk² = 1 holds to 2.2×10⁻¹⁶ for z = ϟ/r and k = c/v: CONSTRUCTION (both sides are built from one v). The independent-chain version (a spectroscopic z against a k from orbital dynamics) is a convergent test, not a construction.
- ϟ from the Earth-orbit speed (engine `v_surface_Sun`) = 1476.625 m; from the Mercury closure = 1476.599 m (difference −1.8×10⁻⁵); `bridge::koppa_Sun` (R/k² with k = 686.3) = 1477.046 m (+2.8×10⁻⁴, the rounding of k). The solar gravitational redshift z = ϟ/R_Sun = 2.1225×10⁻⁶, the standard weak-field value. The Mercury agreement uses the coefficient 6π as an input (C4, C7).
- **A definition to confirm:** as typed, v = (ck)√(R/r) gives 137.04c at r = R for k = 1/α (the engine form is v = (c/k)√(R/r), which gives αc at r = a₀ for R = a₀). Either k there means v/c, or the product should be c/k.

### C4 — the 1/r³ term and Mercury: the coefficient 6 is required, and sufficient
For a = −(c²ϟ/r²)(1 + βϟ/r) with ϟ = 1476.599 m, a direct orbit integration of Mercury (40 orbits, RK4, dt = 20 s; energy conserved to 1e-12) gives: β = 0: −1.4×10⁻¹² rad/orbit; β = 3: 21.4899 arcsec/century; β = 6: 5.018576×10⁻⁷ rad/orbit = 42.9800 arcsec/century (analytic first order 6πϟ/(a(1−e²)) = 5.018578×10⁻⁷, difference −3.9×10⁻⁷); β = 12: 85.9600. The advance is linear in β. So a 1/r³ force with coefficient 6ϟ reproduces the observed 42.98 arcsec/century, and any other coefficient does not. **What is not shown:** where the 6 comes from. The paste does not derive it, and the engine takes the GR coefficient as an input ("GR-analogue", `laws.hpp:1220`).

### C5 — what the same force law implies elsewhere
For a = (c²ϟ/r²)(1 + 6ϟ/r), if no other term is present:
- The circular-orbit speed v² = c²x(1 + 6x), x = ϟ/r, reaches c at x = 1/3 exactly (r = 3ϟ), the radius at which general relativity has its photon circular orbit [B]. Recorded as C-009 in the addendum.
- Circular orbits are stable at every radius: the stability margin is 1/(1 + 6x) > 0 for all x. There is no innermost stable orbit, whereas general relativity has one at 6ϟ [B]. This is a consequence of the stated structure, and a point at which it differs observably from general relativity, if the force law has no further terms; your model may have further terms that the paste does not state.

### C6 — light: the factor two
For n − 1 = aϟ/r, the grazing deflection is 2aϟ/b: a = 1 gives 0.8756 arcsec, a = 2 gives 1.7512 arcsec; the delay coefficient is aϟ/c. The 1911 scalar form c(1 + Φ/c²) is a = 1, the half value. The full value needs a = 2, i.e. a coordinate light speed c(1 − 2ϟ/r), which to first order is c(1 − z)². That is the form of the engine's repair of the Shapiro factor (per my notes), and it reproduces both the deflection and the delay of the weak-field tests; the delay's agreement with measurement is tested to a few parts in 10⁵ [B]. **Not shown:** why the factor is two in terms of the medium (one factor from the standards' scaling and one from the light's path is the natural reading, and has to be derived).

### C7 — "c from orbital geometry"
> [2026-10-08: reasons withdrawn and replaced. See the correction at the top: the trace is AU and a_Mercury via ranging light-times; this check and C3 are one fact (shadow S1, S2).]
The engine's closure c = k_Sun·v_surface = 299,795,135.8 m/s, +0.00089% from the measured c (engine comment +0.0009%). The closure is the general-relativity perihelion formula δφ = 6πGM/(c²a(1−e²)) solved for c. Since c ∝ δφ^(−1/2), the stated uncertainty of the precession (±0.04 arcsec/century, 0.093%) moves c by −0.0465%, fifty times the quoted agreement. The 0.0009% therefore reflects that 42.98 is the value general relativity predicts, not a precision of the closure.

## 3. Verdicts by item (register)
- **Displacement arithmetic:** consistent (C1). **Displacement physics:** the 1/r² displacement and the finite shear energy are correct; the density statement is inconsistent with the premise (C2); the displacement-to-force step and the index are not derived.
- **v = c√(ϟ/r), zk² = 1:** consistent with Kepler's third law (convergent); zk² = 1 is CONSTRUCTION [withdrawn 2026-10-07 for the relation; it stands for the one-v check only]; the typed form needs the definition of k.
- **1/r² + 1/r³ and Mercury:** consistent for β = 6; the 6 is required, not derived (C4); consequences in C5.
- **Light with a pressure-dependent speed:** consistent with the full weak-field deflection and delay for a = 2; the factor two is not derived (C6).
- **c from geometry:** the quoted precision is not supported by the input (C7). [2026-10-08: superseded. The closure tests the 6π law; c enters through AU in metres.]

## 4. Statements without equations in the paste: what would count, and what this session bears
- **"Solved the n-body problem."** The general problem is not integrable in closed form (Bruns and Poincaré, 1887–90 [B]); convergent series exist (Sundman 1912 for three bodies; Wang 1991 for n bodies [B]) and are of no practical use. A solved n-body problem has to mean one of: a well-posed dynamical system with no free parameters (a complete force law and inertia), a proven stable or exact reduction, or a new conserved structure. The pairwise law of C4 gives a well-posed system; it is not a closed-form solution, and the motion of three or more bodies under it is non-integrable in general.
- **Coulomb.** In this session (EMC01) the Coulomb strength at the hydrogen seat is recovered from P_eff by construction, the numerator of P_eff being αℏc; independent content must come from elsewhere. **Casimir.** (FLM15-cas, computed in this session, record not yet written) a scale-free price a·ℏω per mode gives an exponent of exactly 4 and a coefficient aπ²ℏc/120, equal to the ideal value only for a = 1/2; the exponent follows from the scale-free premise and the coefficient is open. The Riemann zeta function appears in that route as ζ(4) = π⁴/90 in the Poisson sum (my reading of "Riemann", if that is what was meant). **"The pillars of relativity":** not shown; the weak-field items are in C4–C6.
- **The feather and the bowling ball.** The requirement is that the occlusion force and the inertial resistance scale with the same quantity for every composition. If force scaled with the baryon count and inertia with the measured mass, nuclides would differ by their binding fraction (up to about 1% between hydrogen and iron [B]), against equivalence-principle limits many orders smaller [B]. The mass defect must enter force and inertia identically.
- **Nuclear gear structure, magnetism as thrust, the particle zoo, singularities, the cosmic cycle:** no equations in the paste; nothing to evaluate. The finite excluded volume (R₀) removes r → 0 as a point; the coordinate light speed c(1 − z)² vanishes at z = 1, a different pathology to be stated.

## 5. Derivations that would close the gaps (to register natively)
1. The coefficient 6 of the 1/r³ force from the occlusion and rotation structure, with no reference to Mercury.
2. The displacement-to-force step: the force as the solid-angle (shadow) term, and the 1/r³ strain term as its correction, with coefficients.
3. The factor 2 in the light-speed law (a = 2), from the scaling of standards.
4. The density statement removed or the medium treated as compressible; then the displacement field recomputed.
5. The definition of k in v = (ck)√(R/r).
6. The same-quantity requirement for force and inertia across nuclides.
7. Whether the 1/r² + 1/r³ law is complete: if it is, the absence of an innermost stable orbit (C5) is a prediction; if it has further terms, they are to be stated.
