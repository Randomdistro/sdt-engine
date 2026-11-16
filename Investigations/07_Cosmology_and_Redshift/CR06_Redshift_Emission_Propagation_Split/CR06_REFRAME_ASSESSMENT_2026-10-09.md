# CR06 (redshift: emission and propagation split) — reframe assessment (2026-10-09)

Supersedes the classifications of `CR06_RESET_ASSESSMENT_2026-10-09.md` (run 1, kept visible). Direction: Harvey, 2026-10-09 — remove the artificial restrictions and gates from the prompt, re-analyse the chain, adjust, re-run. Instruments `cr06_reset_2.cpp` (profile fits, three datasets) and `cr06_reset_2b_crosscheck.py` (independent second route and representation check); outputs `cr06_reset_2_results.txt`, `cr06_reset_2b_results.txt`. Specification: `PROMPT.md`, "Reframe 2026-10-09".

## 0. Inputs, exposure, changes made
- Not blind: run 1 had fitted the 40 bins. Run 1's numbers served only as known answers for validation V6 (reproduced exactly).
- `PROMPT.md`: the dual verdict, the PASS/QUALIFIED/PARTIAL/FAIL classes, the §⑩ commitment block, pivot table and adjustment lists are struck through in place and marked withdrawn (text kept visible); the single-power restriction, the assumed prefactor convention and ΛCDM-relative scoring are withdrawn as restrictions; the reframed specification and the chain are appended.
- Data added: `Datasets/cosmology/Pantheon_DS17f_binned_sys_covariance.txt` (sha256 prefix `642391b0a56e`, manifest row written 2026-10-09; Scolnic et al. 2018 repository). The 40-bin file now carries its full covariance C = diag(dmb²) + C_sys. Second compilation: `Datasets/cosmology/PantheonPlusSH0ES.dat` (1580 non-calibrator rows with zHD ≥ 0.01; diagonal errors only, covariance not in the repository: PENDING).
- Read: `PROMPT.md`, `cosmology.hpp` (strain-rate guard), `Theory/CONDENSA_Spation_Lattice_Unification.md` §2, `Hubble/INVESTIGATION_Hubble_Tension.md` §4.3, §7.2.

## 1. The chain, re-analysed
| Link | What it asserts | Status in this record |
|---|---|---|
| 1 Endpoint ratio | 1+z is the ratio of local lattice states at the two ends; nothing happens in transit | premise from the canon (CR07, `cosmology.hpp` guard); no path ODE is used |
| 2 Common-mode rate | photon energy and event rate scale with the same ruler ratio, so D_L = r (1+z)¹ | derived from the premise (CONDENSA §2); tested only through p (below) |
| 3 Geometry | Law III inverse square; r is a physical distance | premise from Law III |
| 4 Profile | 1+z(r) along the line of sight | unknown; represented by the octave-rate function n(x), x = ln(1+z), dz/dr = (1+z)^n(x); the data determine r(z) = D_L/(1+z) up to the scale in the offset |
| 5 Emission term | source luminosity in its own lattice state | not separable from link 2 or link 4 in D_L(z) (§3.4) |
| 6 Observer | offset a = M − 5log₁₀H_eff + const | nuisance, analytic |
Run 1 broke the chain at link 4 by imposing a single power and at link 2 by taking the prefactor as a convention, then ranked the result by ΛCDM's ΔAIC. None of that is carried forward.

## 2. Instrument and attempts
Validations met in the recorded attempt: V7 parse (A, B 40 rows; C 1580 rows, z = 0.0102–2.2614); V5 covariance symmetric and positive definite; V1 r̃ against the closed form (worst 7.9×10⁻¹⁴ mag); V2 K = 3 with equal knots equals K = 1 (diff 0); V3 (toy) K = 3 truth (0.4, 0.9, 1.4) recovered; V4 (toy) 300 realisations, 1σ coverage 0.690, mean σ̂ 0.0218 against scatter 0.0216; V6 run 1 reproduced (LCDM Ω_m 0.2841, χ² 49.738; K = 1 n 0.6555, χ² 81.027). Second route (`cr06_reset_2b`, independent implementation): K = 1, 2, 3 on dataset A give χ² 47.412, 38.921, 38.668 and the same knots as the C++ tool; LCDM Ω_m 0.2963, χ² 39.298.
**Misstep recorded (attempt 1 of this run):** the tool printed the profile's n(x) and the ΛCDM local slope under one name. They are different quantities for a varying exponent: secant exponent n(x) = ln(dz/dr)/x against local slope s = d ln(dz/dr)/d ln(1+z) = n + x n′. The computation was unchanged; the report is corrected to give both for every model. In the Python check the first representability test used the local slope where the knots take the secant exponent; corrected. Both attempt-1 outputs are kept (`*_attempt1_label_fault.txt`).

## 3. Results (COMPUTED; no threshold applied to any of them)
### 3.1 Single power and profile, p = 1 (χ² with the stated covariance; offset analytic)
| Dataset | K = 1 n (χ²) | K = 2 knots (χ²) | K = 3 (χ²) | K = 5 (χ²) | flat LCDM Ω_m (χ²) |
|---|---|---|---|---|---|
| A, 40 bins, full covariance | 0.663 ± 0.036 (47.412) | 0.395 ± 0.100, 1.011 ± 0.130 (38.921) | 38.668 | 37.160 | 0.2963 [0.275, 0.318] (39.298) |
| B, 40 bins, diagonal | 0.656 ± 0.022 (81.027) | 0.298 ± 0.065, 1.075 ± 0.077 (45.601) | 45.581 | 41.861 | 0.2841 [0.272, 0.297] (49.738) |
| C, Pantheon+ 1580, diagonal | 0.720 ± 0.029 (699.271) | 0.572 ± 0.071, 1.048 ± 0.147 (693.764) | 693.626 | 692.951 | 0.3491 [0.331, 0.368] (694.146) |
Δχ² from K = 1 to K = 2: A 8.491, B 35.426, C 5.507 (one added parameter). χ²(K = 1) − χ²(LCDM): 8.114, 31.289, 5.125. χ²(LCDM) − χ²(K = 2): 0.377, 4.137, 0.382. The covariance changes the single-power fit's distance from ΛCDM from 31.3 to 8.1 in χ².
Comparators on A: Milne 77.380, de Sitter z(1+z) 401.015, EdS 532.203. Documented single powers as fits: n = 1 offset-only 130.046; n = 4 offset-only 5967.060 (on B: 324.774 and 16517.827, as in run 1).

### 3.2 The profile in the native variable
Secant exponent n(z) of the K = 2 profile against the flat-ΛCDM value at the same z (A): z = 0.1: 0.457 ± 0.080 / 0.491; 0.3: 0.564 ± 0.050 / 0.578; 0.5: 0.655 ± 0.037 / 0.657; 0.8: 0.772 ± 0.054 / 0.756; 1.2: 0.901 ± 0.093 / 0.856; 1.6: 1.008 ± 0.129 / 0.930. On C: z = 0.5: 0.735 ± 0.031 / 0.745; z = 1.2: 0.889 ± 0.081 / 0.935; z = 2.0: 1.014 ± 0.133 / 1.051. Local slope s(z) (A, K = 2): 0.421 (z = 0.02) to 1.620 ± 0.341 (z = 1.6); ΛCDM 0.463 to 1.321. For K ≥ 4 the local slope at z > 1 is unbounded (A, K = 4: 3.31 ± 1.63 at z = 1.6; C, K = 5: 6.9 ± 12.9): the data do not constrain the derivative there.
Octave rate per unit distance, q(z) = (dx/dr)/(dx/dr)₀ = e^{(n−1)x}, from the fitted knots: A K = 2: 0.988, 0.949, 0.892, 0.869, 0.875, 0.925, 1.008 at z = 0.02, 0.1, 0.3, 0.5, 0.8, 1.2, 1.6 (K = 1: 0.993 to 0.725, monotone); ΛCDM at the same z: 0.989, 0.953, 0.895, 0.870, 0.866, 0.893, 0.935. C K = 2: 0.992, 0.964, 0.919, 0.898, 0.894, 0.917, 0.960, 1.016 at z = 0.02…2.0 (K = 1: 0.994 to 0.735). The octave rate falls by about 13% by z ≈ 0.5–0.8 and recovers by z ≈ 1.6. This is the acceleration signature written in the native variable; a single power cannot show it. (Bands on q are not propagated; values are from the printed knots.)

### 3.3 Distance functions (second route, A)
Offset-removed 5 log₁₀(r_model/r_LCDM) at the 40 redshifts: K = 2: maximum 0.033 mag (z = 1.612), rms 0.006; K = 3: 0.058, 0.010; K = 1: 0.152, 0.030; median bin error 0.026 mag, 0.056 and 0.074 at z > 1. The knot family reproduces ΛCDM's χ² to three decimals when set to ΛCDM's secant exponent (K = 2, 3, 5, 9: 39.300, 39.307, 39.295, 39.302 against 39.298). The profile and ΛCDM are the same description of these data to within the bin errors; the knot values at a given z can differ from the ΛCDM value by the stated bands without changing the distance function.

### 3.4 The prefactor and the emission term are one parameter
Fitting p with a single power: p = 1.172 ± 0.284 (A), 1.176 ± 0.155 (B), 1.142 ± 0.278 (C), with n = 1.000 ± 0.567, 0.309, 0.555 (a valley: n and p trade). Fitting the luminosity drift δ (mag per unit ln(1+z)) instead: δ = +0.3735, +0.3829, +0.3089, and 1 + δ/(5 log₁₀e) = 1.172, 1.176, 1.142: the same numbers. A drift linear in ln(1+z) is algebraically a power of (1+z) in the prefactor; link 2 (derived p = 1) and link 5 (emission drift) cannot be separated by D_L(z) alone. For K ≥ 2, p is unconstrained (A: K = 2 p = 0.157 ± 1.235). With ΛCDM the fitted drift is δ = −0.124 (A; Ω_m 0.234), +0.034 (B), +0.326 (C; Ω_m 0.558) with χ² changes of 0.07, 0.03, 0.58.
Emission-term residuals on A (m_obs − m_model − a, magnitudes, 40 bins): n = 1: −0.154 to +0.143; n = 4: −0.820 to +1.701; best single power: −0.097 to +0.076 and −0.262 at z = 1.612; K = 3 and ΛCDM: within ±0.074 except −0.053 and −0.112 at z = 1.612.

## 4. Statements the data support, with their tags
- COMPUTED (A, B, C): the octave-rate profile fitted without an assumed shape has a secant exponent rising from about 0.4–0.6 at z → 0 to about 1.0 at z = 1.6–2.0, and an octave rate per unit distance that falls and recovers. A single power describes it with Δχ² = 8.5 (A, covariance), 35.4 (B), 5.5 (C) above the two-knot profile.
- COMPUTED: the two documented single-power forms are not the profile: n = 4 leaves emission-term residuals up to 1.7 mag; n = 1 needs a luminosity drift of +0.37 mag per unit ln(1+z) (p_eff = 1.17) to reach χ² = 47.05 on A.
- CONSTRUCTION (algebraic): the drift term and the prefactor power are one parameter.
- OPEN: the native profile 1+z(r); the independent measure of the rate factor (light-curve stretch against 1+z) that would separate link 2 from link 5; the Pantheon+ covariance.
No grade ladder is applied: the ladder presupposes thresholds, which are withdrawn.

## 5. Direction
1. The native d(z) is a profile 1+z(r) whose octave rate per distance has the shape in §3.2 (a fall of about 13% to z ≈ 0.5–0.8, recovery by z ≈ 1.6). A construction from the endpoint-ruler reading must produce q(z) or r(z) with its prediction fixed before it meets these data; the representation is now fixed, so a prediction can be written directly in n(x) or q(z).
2. Separating the emission term from the propagation term needs a rate observable that the Hubble diagram does not contain: supernova light-curve stretch against 1+z. PENDING data (not in `Datasets/`); it fixes p independently and turns δ into a measurement.
3. Quote exponents in the representation that the data constrain: distance functions and the secant exponent, not the local slope above z ≈ 1.
4. CR06 → GOM01 and every σ₀-integrated distance: the `cosmology.hpp` guard stands until a profile with a native origin exists; this record supplies the target shape.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
