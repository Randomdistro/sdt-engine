# Shadow analysis of the paste-math evaluation and the algebra demos — assessment (2026-10-08)

**Object.** `PASTE_MATH_EVALUATION_2026-10-07.md` with its tool and output in `paste_math_eval/`, and `paste_algebra_demos/` (2026-10-08).

**Pre-registration.** `SHADOW_ANALYSIS_2026-10-08_PRE_REGISTRATION.md`. One dated amendment was made before the instrument existed. It re-registered S3 to the paper that supplies the redshift, replaced a prohibited ΛCDM distance in S8, and fixed S9's prediction.

**Instrument.** `shadow_analysis/shadow_1.cpp`, output in `shadow_1_results.txt` (MSVC 19.44, single pass). Validations V1–V3 were met. 7 of 9 checks were confirmed; 2 were rejected under my own tolerances (origin of each given below).

## 1. Errors in the work under review, and where each comes from

The downgrade trace for each label is given in the form procedural §3.8 requires.

**E1. Evaluation C7 ("c from orbital geometry").** The conclusion is right but both reasons given were wrong.
- "Reflects that 42.98 is the value general relativity predicts" is not an admissible reason (behavioural §3.8).
- The ±0.04″/cy is an old uncertainty. EPM2017 gives a formal 8 µas/cy, with a realistic figure 10–50× larger (Iorio, arXiv:1810.13415, search result, not read in full).

S1 confirms that R_Sun cancels: the closure reduces to c_cl = v_E·√(6π·AU/(δφ·a(1−e²))). Its only length scales are AU and a_Mercury, and v_E carries AU/yr. So the admissible trace is:

`contaminating input: AU and a_Mercury in metres — measured by radar and spacecraft ranging (light-time × c; τ_AU = 499.004784 s) — enter at laws.hpp:195, 1233, 1253`

What the closure tests is the dimensionless 6π precession law, not a value of c. The engine comment "c is NOT a free input" (laws.hpp:1216) is therefore a canon item: it is proposed below, not edited.

**E2. Evaluation C3 and C7 treated as separate results.** S2 confirms they are one fact. c_closure/c − 1 = (ϟ_M/ϟ_E)^(−1/2) − 1 = 8.9322×10⁻⁶ exactly, where ϟ_M/ϟ_E − 1 = −1.786×10⁻⁵. The session accepted the number in C3 and downgraded it in C7.

**E3. Evaluation §3 and the tool output still read "zk² = 1 is CONSTRUCTION".** The header correction withdrew the label, but it was not marked where it stands. Under the gateway, the check (z and k built from one v) is CONSTRUCTION; the relation on independent chains is not. Annotated in place today.

**E4. Sirius B.** The correction block pairs Barstow 2005's redshift (80.42 ± 4.83 km/s) with Joyce et al. 2018's mass (1.017 ± 0.025). These come from two papers.
- The demos then used R = 5.84×10⁶ m (0.00839 R☉, source unrecorded) and got 1.061 M☉.
- S3 with the 2018 pair (80.65 ± 0.77 km/s, 0.803 ± 0.011 R☉/100, read directly) gives ϟ = 1502.87 m, which is 1.0178 ± 0.0170 in solar units against the dynamical 1.018 ± 0.011: −0.01σ. Confirmed.
- **Origin of the +4%:** the radius (×1.0454); the redshift contributes ×0.9971.
- Joyce et al.'s equation (3), M = v_gr·R/0.636, is the same form as ϟ = zR in solar units.

**E5. Evaluation C2 ("the density statement is inconsistent").** S4 confirms the paste's ρ/ρ₀ = 1 − Ω₀/(4πr³) equals 1 − ε_θθ of the incompressible field exactly, at every radius tested. Read as the tangential linear spation density, it is consistent with the incompressible premise; the radial one is 1 + 2u/r. The evaluation's inconsistency, and demo F7's logarithmic divergence, hold only under the volume-density reading. The tool had already computed ε_θθ (C2 output line 17).

**E6. Demo F1 (l_P from G against the engine's l_P to 1.5×10⁻⁸).** Shared input. S5 shows the stored l_P² differs from ħG/c³ by −2.96×10⁻⁸, which is the stored precision. The line also writes G as an input, against the fixed direction (behavioural §3.8).

`contaminating input: l_P — the CODATA 2018 value is computed as √(ħG/c³) with G = 6.67430e-11 — enters at laws.hpp:99`

**E7. Demo G1 ("ϟ = a₀α² = r_e").** `laws.hpp:130` defines r_e = α²a₀, so the printed agreement is that definition.

**E8. Demo F8 B (the Sun's baryon count against M/m_p, −1.2×10⁻⁴).** S5 decomposes the demo's 0.999881 into three factors:
- Q = R_p/(4ƛ_p) = 1.000195
- ϟ_Mercury/ϟ_GM = 0.999982
- (GM☉/G)/1.989×10³⁰ = 0.999703

The census agreement is carried by the FLM07 relation the engine already records (laws.hpp:132) and by the demo's rounded solar mass. It is not a solar census.

S5 itself was **rejected** under its 1e-12 tolerance (difference 3.0×10⁻⁸). The residual equals the stored l_P precision; my criterion did not allow for it, so the reduction holds to that precision.

**E9. Demo C2 B (Earth's drag through the CMB at orbital speed).** S6: at the CMB-frame speed of 370 km/s the drag is 8.76×10⁻³ N, 12.42× the demo's figure. The conclusion (negligible) is unchanged.

S6 was **rejected** under its 1e-6 tolerance: the ratio exceeds 370/29.78 by 1.5×10⁻⁶. That excess is the γ² factor of S7. My criterion assumed the linear regime.

**E10. Demo D3 B (GPS).** GM = g·R² with g = 9.80665 already contains the centrifugal and latitude reduction, and the ground clock's rotation is omitted. The demo's net is +38.45 µs/day. Not recomputed.

**E11. Demo lines that cannot fail.**
- A5 A, E2 A, F4 A, and E3 B (2^log₂x = x) are tautologies.
- E1 B: λ cancels analytically.
- B4's spherical case is the same 1-D check as the plane wave.
- B3 B prints the literal `3.0` as a ratio (`paste_algebra_demos_1.cpp:63`).

These carry no evidential weight (procedural §3.1, §3.4).

**E12. The demos file as a whole.** No pre-registration or run log. Tags are [ext]/[B] instead of the §3.6 set. Constants are defined locally (EPS0, MU0, GNEWT, R_EARTH while `bridge::R_Earth` exists at laws.hpp:1040, M_EARTH).

**E13. Demo C1 A (CMB dipole).** The 370 km/s is itself inferred from the dipole, so T₀β against the dipole is shared input. It is not claimed as a match.

**Checked and standing:**
- evaluation C1, C4 (integrator; linear in β), C5 (margin 1/(1+6x); a pure 1/r³ term renormalises L², so there is no innermost stable orbit), C6
- demos D1 (photon-sphere cosh growth), D2, D4, F5, F6 (8πμA²/R₀³), F7 (the integral as stated)

## 2. Results that held, and where else their form applies

**S7 (confirmed, newly identified).** The drag the demos computed is F = −(4/3)uσγ²β exactly: the ratio column equals γ² to 2.6×10⁻¹¹. The 4/3 is (u + P)/u for isotropic radiation. The same factor appears in:
- the inverse-Compton power (4/3)σcγ²β²u
- Poynting–Robertson drag
- the engine's own `release_acoustics::equality_loading = 3/4` and its c/√(3(1+R)) sound speed

Correspondence only; the native statement is momentum flux through a moving cross-section.

**S9 (confirmed).** A solar prediction from the Mercury ϟ alone, with no fit:
- c·ϟ(1/R☉ − 1/AU) − c·ϟ_⊕/R_⊕ = 636.299 − 2.959 − 0.209 = 633.131 m/s
- measured: 638 ± 6 m/s (González Hernández et al. 2020, A&A 643 A146), a deviation of +0.81σ

Inverted, the spectrum alone gives ϟ☉ = 1487.9 ± 13.9 m against 1476.60 m from the precession. This fills the PENDING solar row of the evaluation's correction (4), at 0.9%.

**S8 (confirmed).** A lattice of spacing ℓ_P, with group velocity v_g = c·cos(kℓ/2), delays the 30.53 GeV photon of GRB 090510 by at most 9.0×10⁻¹⁸ s. That uses the bound L ≤ R_CMB with no cosmological model. The observed bound is 0.859 s (Fermi LAT, arXiv:1008.2913). The bound would be reached only at a spacing of 3.1×10⁸ ℓ_P, so the data permit any spacing below that, a native upper bound.

**Targets recorded, nothing loaded:**
- **ϟ from precession on other systems.** The double pulsar J0737−3039, PSR B1913+16, and S2 around Sgr A*. Not discriminating at first order.
- **The 1/r³ law with β = 6.** It has no innermost stable orbit, where general relativity has one at 6ϟ. This is the discriminating item. Targets: the inner edge of relativistic Fe Kα lines, and continuum fitting of X-ray binaries.
- **The a = 2 light law.** Targets: Cassini's γ bound, VLBI and Gaia deflection, pulsar Shapiro range (J1614−2230; ties to GOM17), strong-lens Einstein radii.
- **ϟ = zR on further white dwarfs.** Targets: 40 Eri B, Procyon B, Gaia wide binaries.
- **Two dilatation centres in an isotropic medium.** By the elasticity result [B], they do not interact at first order, so the force between bodies must come from occlusion (Law III), not from the displacement. The second-order r⁻⁶ correspondence with the London form is to be registered as a test, not claimed.
- **Radial : tangential strain = −2 : 1 (from E5).** This is a native factor 2. **Limitation:** it falls as r⁻³, so by itself it cannot give n − 1 ∝ 1/r. Recorded as C-010.
- **R_term ∝ √N_b (C-008).** A census against SMBH and bulge masses, with a look-elsewhere count.
- **R_p = (W+1)ƛ_p beyond the proton.** Pre-register before computing.

## 3. Canon proposal (propose-and-wait; nothing in `Engine/` edited)

**P-SA1.** `laws.hpp:1214–1231`, GOM04 block. The block currently says "c is NOT a free input … passes delete-test — c is an OUTPUT". Proposed wording:

> The closure fixes the dimensionless relation δφ·a(1−e²)/(6π AU) = (v_E/c)², a test of the 6π precession law. The metre values of AU and a_Mercury come from ranging light-times × c, so c is not recovered independently. R_Sun cancels.

The closure itself, and its agreement of 8.9×10⁻⁶ (= half the two-route ϟ difference), are unchanged.

## 4. Sources

Read directly:
- Joyce et al. 2018, MNRAS, arXiv:1809.01240 (Table 3, §3.1.7)

From search results or abstracts, not read in full:
- González Hernández et al. 2020, A&A 643 A146
- Ackermann et al. / Fermi LAT GRB 090510 bound, arXiv:1008.2913
- Iorio, arXiv:1810.13415 (EPM2017 Mercury uncertainty)

Unverified: the source of the demos' 5.84×10⁶ m radius; the elasticity non-interaction result.
