# GOM25 (solar depth and propagation audit) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–3 are the registration, written before `gom25_reset_1.cpp` exists. Results are section 4 onward.

## 0. Inputs read and exposure
Read: `GOM25/PROMPT.md` in full (including Amendment 01); `laws.hpp` (`depth_closure::depth`, `shapiro_delay`); the CDS ReadMe of the HARPS-LFC tables (column definitions and the published summary 638 ± 6 m/s); the first 12 rows of table A.2 and 6 of table A.1 and the header and first rows of the Horizons CSV (to fix the formats). Not read: every other file in the folder (`GOM25_ASSESSMENT.md`, `GOM25_RESULTS_2026-08-07.md`, `GOM25_D4*`, `PROMPT_B_INVARIANT_KOPPA.md`, the `.py`/`.cpp` tools), and the dataset folders' manifests beyond the two rows naming the files. Exposure: the file names of the folder were listed. The data are the raw inputs of D1 and D3 (`Datasets/solar_propagation_2026-08/raw/`), not results.
**Hand estimate made before registering:** ϟ ≈ v²r/c² for the Earth–Moon barycentre ≈ 1.476 km; v_pred = c ϟ (1/R − 1/r) ≈ 636.1 − 3.0 = 633 m/s. Stated so the landing is not mistaken for a surprise.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | gating | σ_pred is not defined in decision rule 1. The orbit-to-orbit variation of ϟ_i (about ±1.2%) moves v_pred by about ±7 m/s, comparable to σ_obs = 6 m/s, while the radius uncertainty alone moves it by 0.13 m/s. The decision depends on which is σ_pred. Both are registered (§2). |
| D2 | gating | "weighted mean" of v_pred,i: the weights are not specified; equal weights are registered (the 14-day rows are equally spaced). |
| D3 | gating | The comparator is a processed summary (638 ± 6 m/s) whose value depends on a CO5BOLD 3D atmosphere and on recalibrated laboratory wavelengths (NIST); the prompt labels it UNADJUDICATED. A decision of COMPATIBLE or EXCLUDED is therefore conditional on that nuisance, and the adjudication label stays UNADJUDICATED whatever the arithmetic gives. |
| D4 | record | The form ϟ/R − ϟ/r equals the first-order shift GM/(Rc²) once ϟ = GM/c² (a relation the chain does not assume; ϟ here comes from v and r of an orbit). The comparison therefore cannot discriminate this chain from the standard first-order expression: agreement is convergence, not a test between them. What it does test is the closure of two independent observation chains: spectroscopy (z_spec) against orbital dynamics (ϟ from v, r). |
| D5 | gating | D4 (timing readiness) asks for a located primary product and, if none, PENDING_DATA. A Cassini SCE1 ODF/TDF product exists locally; decoding it and the timing test belong to the GOM_DAT chain and are not run here. |
| D6 | record | Decision rule 3 compares the exact integral with `shapiro_delay`, which the engine labels leading order. Agreement of the two is a statement about the series expansion, not an observation. |
No downgrade is made on agreement grounds.

## 2. Registered quantities, validations, criteria (fixed before the run)
**Inputs.** D1: the 27 rows of `jpl_horizons_emb_sun_vectors_2025.csv` (EMB relative to the Sun, ecliptic J2000, km and km/s). D2: R = 695 700 km (IAU nominal, no uncertainty) and R = 695 658 ± 140 km (direct). D3: (A) the published summary 638 ± 6 m/s; (B) the mean of `v_fit_3D_n` over the 97 lines of table A.2 (equal weights; also the weighted mean; standard error = sd/√n); (C) the mean of `v_core_obs` over the 188 lines of table A.1, reported without a decision (the convective shift is not modelled in it).
**Quantities.** ϟ_i = |v_i|² |r_i| / c² (c = 299 792 458 m/s exact). v_pred,i = c ϟ_i (1/R − 1/|r_i|). Mean and standard deviation over the rows; CV of ϟ_i; leave-one-out range; first-half and second-half means; the regression ϟ_i = A + B |r_i| (reported; A/2 and −A/(2B) as exploratory orbital invariants, not used in the decision).
**Validations (must be met before any prediction is read).** V1: the regression of ϟ_i on |r_i| has R² ≥ 0.999 and −A/(2B) within 0.5% of 1 AU (IAU exact; the vis-viva relation v²r = k(2 − r/a) uses no G or M, so this checks the table and the arithmetic). V2: the quadrature reproduces ∫_{−L}^{L} ds/√(s²+b²) = 2 asinh(L/b) and ∫ ds/(s²+b²) = (2/b) atan(L/b) to relative 1e-10. V3: the domain gate accepts z = 0 and 0.5 and rejects z = 1, 1.5, −0.01 and NaN. V4: the 27 JD values are spaced by 14.0 days to 1e-6.
**Decision 1 (depth transfer).** For comparator A and B: EXCLUDED if |mean(v_pred) − v_obs| > 2 √(σ_pred² + σ_obs²), else COMPATIBLE. Primary σ_pred = |v_pred| · 140/695 658 (direct-radius uncertainty; the table precision, 16 printed digits, is negligible). Sensitivity σ_pred (epoch) = √(σ_R² + sd(v_pred,i)²). The chain is called COMPATIBLE only if both give COMPATIBLE; EXCLUDED if the primary excludes. Adjudication label: UNADJUDICATED (D3). Closure statistic Q = v_obs/mean(v_pred) with its uncertainty, the independent-chain form of z_spec · (R/ϟ) = 1 at the surface.
**Decision 2 (input consistency).** CV of ϟ_i reported; whether the variation is the linear-in-r vis-viva variation (V1) and so identified as the orbit rather than noise.
**Decision 3 (exact propagation).** Straight path from r₁ = 1 AU to r₂ = 1 AU on the opposite side of the Sun at impact parameters b = 2, 5, 20 R (R = 695 700 km), ϟ = the mean of ϟ_i. Δt_exact = ∫ [1/(c(1 − ϟ/r)²) − 1/c] ds using z(2 − z)/(1 − z)² (no cancellation), Simpson in the angle φ (s = b tan φ) with N = 2000 and 4000 intervals; compared with `depth_closure::shapiro_delay(ϟ, r₁, r₂, b)` (LEADING_ORDER) and with the second-order term (3ϟ²/c)(atan(s₁/b) + atan(s₂/b))/b. Reported: values, relative differences, quadrature convergence. No observation is claimed.
**Decision 4 (timing).** Not run: PENDING (the GOM_DAT chain).
**Decision 5 (domain).** Every z (at R, at each r_i) must be in [0, 1); otherwise rejected, not interpreted.
**Error model reported:** radius uncertainty (σ_R), table precision (negligible), row exclusion, spectral comparators A/B/C spread, quadrature convergence.
**Rejection class populated?** For Decision 1 the class "EXCLUDED" is populated only by an offset greater than about 12 m/s (2%) from 638; the amendment-01 variant without the −z(r_observer) term differs by only 3 m/s, so it would not be separated. This is stated now: the test cannot separate the two forms of the chain, nor ϟ/R from GM/(Rc²).
**Expected landing (from the hand estimate):** v_pred ≈ 633 m/s, COMPATIBLE with A (4.8 m/s against a threshold near 12 m/s); B not estimated.

## 3. Grades available
G0 validation unmet; G1 excluded on a registered criterion; G2 open; G3 supported with the shared input named; G4 and G5 not available from this audit.

## 4. Results (COMPUTED; instrument `gom25_reset_1.cpp`, output `gom25_reset_1_results.txt`; single pass, no amendment)
**Validations.** V1 met (koppa_i = A + B|r_i| with R² = 0.999999; −A/(2B) = 1.00016 AU); V2 met (1.6e-16 and 4.4e-16); V3 met; V4 met.
**D1 and Decision 2.** 27 rows. ϟ_i (km): mean 1.477262, sd 0.018010, **CV 1.219%**, range 1.452096 to 1.501286, with |r| from 1.4710×10⁸ to 1.5209×10⁸ km. The variation is the orbit's: it is linear in |r| to R² = 0.999999 (the vis-viva relation, which uses no G or M). The intercept A/2 = 1.476399 km is the constant of that relation (exploratory orbital invariant; it equals the mean of ϟ_i to 0.06%, the difference being the equal-time sampling of an eccentric orbit).
**Decision 5.** All z in [0, 1): z(R_Sun) from 2.0872×10⁻⁶ to 2.1579×10⁻⁶.
**Decision 1.** v_pred,i: mean 633.622 m/s (R = 695 700 km) and 633.661 m/s (R = 695 658 km); sd over the rows 7.689 m/s (range 622.9 to 643.9); leave-one-out range 633.23 to 634.04; first half 634.40, second half 632.90. Exploratory invariant form (A/2, r = a): 633.29 m/s.
| comparator | v_obs | difference from 633.661 | primary σ_pred 0.128 (threshold) | epoch σ_pred 7.690 (threshold) | Q = v_obs/v_pred |
|---|---|---|---|---|---|
| A published 638 ± 6 | 638.00 | +4.34 m/s | COMPATIBLE (12.00) | COMPATIBLE (19.51) | 1.0069 ± 0.0095 |
| B table A.2 mean of v_fit_3D_n (97 lines) | 637.70 ± 5.56 | +4.04 m/s | COMPATIBLE (11.12) | COMPATIBLE (18.98) | 1.0064 ± 0.0088 |
| C table A.1 mean of v_core_obs (188 lines) | 351.15 ± 10.53 | −282.5 m/s | no decision | no decision | n/a |
The weighted mean of B is 642.44 ± 0.35 m/s (equal-weight mean 637.70, median 636.0, sd over lines 54.7): the choice of weights moves B by 4.7 m/s (0.7%), the same size as the difference from the prediction. The expected landing (633 m/s, COMPATIBLE with A) holds.
**Decision 3 (r₁ = r₂ = 1 AU, opposite sides, ϟ = 1.477262 km).** Exact against `shapiro_delay` (LEADING_ORDER), one way: b = 2R: 105.8604 µs against 105.8607 µs, exact/leading − 1 = −3.26×10⁻⁶ (second-order term 4.63×10⁻⁷ of the delay); b = 5R: 87.79757 µs, −3.01×10⁻⁵; b = 20R: 60.43294 µs, −7.07×10⁻⁴. Quadrature N = 2000 against 4000 differs by 4.3×10⁻⁶ (b = 2R), 1.4×10⁻⁷ (5R), 6.5×10⁻¹⁰ (20R); by Richardson the N = 4000 error at b = 2R is about 3×10⁻⁷, so the b = 2R difference is resolved to about 10% and the other two clearly. The difference is the finite-path end term of ∫ds/r (b²/4r² per end) and is the same in the first-order standard treatment; it is not an SDT-specific signal. Round trip at b = 2R: 211.72 µs. No observation is claimed.
**Decision 4.** PENDING (not run here).

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| Decision 1, depth transfer koppa(orbit) → z_spec(surface) | **G3, shared-input, UNADJUDICATED** | COMPATIBLE with both comparators under both σ_pred (differences 4.3 and 4.0 m/s against thresholds 11–20 m/s); closure Q = 1.0069 ± 0.0095 of two independent chains (orbital dynamics, spectroscopy). Contaminating inputs: the CO5BOLD 3D atmosphere and NIST wavelengths inside comparators A and B (table C, without a convective model, sits 283 m/s lower: the model subtraction is 45% of the signal); the DE441 dynamical solution behind the state vectors; R_Sun from the IAU convention. Not discriminating against GM/(Rc²) (D4 of the prompt analysis): agreement is convergence |
| Decision 2, input consistency | **COMPUTED** | the 1.22% variation of ϟ_i is the eccentric orbit (linear in r, R² = 0.999999); the declared instantaneous form needs the orbital invariant A/2 = 1.4764 km (or an epoch-averaged ϟ); with it v_pred = 633.29 m/s |
| Decision 3, exact against leading-order delay | **COMPUTED (series statement)** | −3.3×10⁻⁶ to −7.1×10⁻⁴ relative over b = 2–20R; not an observation |
| Decision 4, timing | **PENDING** | GOM_DAT chain |
| Decision 5, domain | met | z ≈ 2.1×10⁻⁶ |

## 6. Direction
1. The 4.3 m/s (0.7%) residual between 633.7 and 638 is smaller than every uncertainty in the comparator; it cannot be read as signal or as failure. What would resolve it is a surface shift with no convective model: the solar line-lens record (Harvey's direction, lensing from inside) bears on this and is the natural next step for D3; this audit does not use it.
2. Fix the orbital invariant for the chain: write ϟ = A/2 (the vis-viva constant) in place of the instantaneous v²r/c² (1.22% epoch variation, 7.7 m/s). That is a statement about the declared form and needs a native reading of what the constant is (candidate: the Kepler constant, already carried as ϟ in the koppa ladder).
3. The geometric correction to the log delay (finite endpoints) belongs in any Cassini-class comparison (GOM_DAT chain, GOM26); nothing SDT-specific enters at the 10⁻⁶ level in the second-order term.
4. The selection of weights in the 97-line mean moves the comparator by 4.7 m/s; any adjudication needs the per-line weights registered beforehand (a line-by-line model-free analysis belongs with the solar line-lens work).

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
