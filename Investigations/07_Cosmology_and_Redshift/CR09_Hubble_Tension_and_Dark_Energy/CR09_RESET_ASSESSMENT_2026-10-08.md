# CR09 (the Hubble tension and dark energy) — blank-slate assessment (2026-10-08)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07. The prompt bundles eight routes (A–H) and its own 2026-10-05 note says it cannot receive a single assessment. This record runs Route B (the raw supernova magnitudes) and records the status of the other seven.

## 0. Inputs read and exposure
Read: `CR09/PROMPT.md` in full except the final audit block read at line 402; `Datasets/cosmology/PantheonPlusSH0ES.dat` (header and first row; 579 KB); `laws.hpp` comments on R_CMB. Not read: `CR09_ASSESSMENT.md`, `RUN_LOG.md`, `cr09_routeB_rawmB.py`, `cr09_routeB_results.txt`.
Exposure: the prompt states that the propagation power n ≈ 0.66 was fitted in CR06, that n = 4 "missed the raw curve, χ²/dof 424", and that the mismatch direction is "~8.4%". All three were read before this registration. The registered shape scan includes n = 0.66 and n = 4 as members of one grid; neither value is used to choose the grid.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The prompt's §3 gives the structure 1 + z_obs = (1 + z_emit)(1 + z_prop), 1 + z_prop = exp(∫σ dx), and R_CMB = ln(1 + z)/σ₀; it does not write d(z) with the exponent n. The role of n is read here as the exponent of the distance in the strain integral, 1 + z = exp(σ₀dⁿ), so d = (ln(1 + z)/σ₀)^(1/n); n = 1 is the exponential law. This reading is registered and is the one shape parameter of §3 ("1 shape parameter, the propagation power n"). |
| D2 | construction | The distance modulus is μ = 5 log₁₀[d_L/10 pc] with one reciprocity factor: d_L = (1 + z)d. With σ₀ absorbed into the absolute magnitude, m_B = M + 5 log₁₀[(1 + z)(ln(1 + z))^(1/n)] + α x₁ − β c. Free: n (shape), and the nuisance M, α, β (SALT2 standardisation, "SDT's own α, β (Tripp)": fitted, not taken from the bias-corrected column). |
| D3 | data | The file holds 1701 light curves (some supernovae appear more than once, with different surveys) and its full covariance is not in the repo. A diagonal error model is used and the limitation is reported: χ²/dof is approximate, and repeated supernovae are not independent. |
| D4 | gating | The prompt asks for "χ²/dof against the raw magnitudes and the residual structure" without a numerical threshold; thresholds are registered below. |
| D5 | method | Routes A, C, D, F, H need native derivations the prompt only names (the gradient geometry for the mismatch; the physical shell of CR08/CR13; the z³ map; the line-of-sight compression), and Route E assembles sibling records that are run in their own turns. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers named:** CR01, CR06, CR07, CR08, CR10, CR11, CR12, CR13, FLM06; Law I, koppa structures. **Dependents:** CR12, FLM-series cosmological items (graph: reach 39). Route B uses the raw data and the §3 structure; CR06's fitted n is not taken as an input.

## 3. The five questions (Route B)
**1. What do we not know?** Whether the distance law of §3 (octave telescoping plus one reciprocity factor, with one shape exponent) reproduces the raw apparent magnitudes of the Hubble-flow supernovae within their scatter.
**2. Why does it matter?** The framework has no expansion and no dark energy; the curvature of the magnitude–redshift relation is what the standard reading calls acceleration. If the §3 law with one shape parameter tracks the raw magnitudes, that curvature has a native description; if it does not, the propagation term of §3 is wrong at the stated parameter count.
**3. By what methods?** A fresh instrument fits the registered family to the raw `mB` with the standardisation parameters fitted, scans the single shape exponent n over a registered grid, and reports χ²/dof and the residual structure. No rival model is fitted.
**4. What would prove us wrong?** (a) Failure indicators: a free parameter beyond n, M, α, β; the error model tuned until χ²/dof = 1; a residual trend with z that the shape scan cannot remove. (b) Falsifying mathematics: the thresholds of §4. (c) What it breaks: if no n gives a tracking fit, the single-power propagation term (CR06, CR07, CR10 consumers) is excluded at this parameter count.
**5. Done when** χ²/dof and the binned residuals for the best n, the shape-scan table, and the grade are recorded, and the other routes have a stated status.

## 4. Pre-registration (written before `cr09_reset_1.cpp` exists)
**Data and selection.** `PantheonPlusSH0ES.dat`, columns `zHD`, `mB`, `mBERR`, `x1`, `c`, `IS_CALIBRATOR`; keep IS_CALIBRATOR = 0 and zHD > 0.01 (the prompt); do not use `m_b_corr`.
**Model.** m_B = M + 5 log₁₀[(1 + z)(ln(1 + z))^(1/n)] + a x₁ + b c, with (M, a, b) by weighted linear least squares at each n and n from 0.20 to 3.00 in steps of 0.01 (281 values; look-elsewhere count 281 for the one shape).
**Errors.** σ_i² = mBERR_i² + σ_int². σ_int fixed before the fit by a model-independent rule: on the subset 0.01 < zHD < 0.08, fit m_B = M + 5 log₁₀[z(1 + z/2)] + a x₁ + b c (the second-order low-redshift form; at z < 0.08 the unknown second-order coefficient changes this by under 4% of its own term), take the weighted rms of the residuals, and set σ_int² = max(0, rms² − ⟨mBERR²⟩).
**Validations (not met ⇒ G0).** V1: the linear solver recovers the exact (M, a, b) from noise-free synthetic data generated with known values (to 1e-9). V2: on synthetic data from n = 0.66 with noise 0.10 mag (500 points, z uniform in 0.01–2, deterministic generator), the scan returns n within ±0.05. V3: the parser reads 1701 rows.
**Tests and gates.**
- T1 (COMPUTED): the best-n χ²/dof, the best n, and the shape-scan values at n = 0.5, 0.66, 1, 2, 4.
- T2 (COMPUTED): mean residual and its standard error in eight bins of z (equal counts); a bin is "off" if |mean residual| > 3 standard errors.
- Gate (registered reading): the law **tracks** the raw magnitudes if best χ²/dof ≤ 1.2 and no bin is off; **structured residual** if 1.2 < χ²/dof ≤ 2 or any bin is off; **excluded at this parameter count** if χ²/dof > 2 for every n in the grid.
**Grades.** G0 validation not met; G1 excluded (χ²/dof > 2 at every n); G2 structured residual (open); G3 tracks, CALIBRATED(1) (n fitted) with the nuisance parameters a, b, M stated; G4, G5 not available (n is fitted).
Expected landing: not stated (no hand evaluation was made).

## 5. Status of the other routes
| Route | Status in this record |
|---|---|
| A (mismatch sign and size from the split) | not run: the gradient geometry g(x) is not defined in the prompt; a native definition is required first |
| B (raw mB(z)) | run below |
| C (BAO angles from a physical shell) | not run: the shell (CR08) is a sibling record; the BAO data exist only as `BOSS_DR12_BAO_Alam2017_Table3.csv` (a table of 938 bytes) |
| D (CMB peak angles from a physical shell) | not run: no shell definition; the prompt itself warns against an invented shell |
| E (sibling consistency) | after the siblings are run |
| F (acceleration as the z³/octave structure) | partly addressed by B's shape scan; the map to u ∝ (1 + z)⁴ is not drawn |
| G (CMB energy density returns ℓ_P) | not run here (FLM06 supplier) |
| H (line-of-sight temperature effect) | not run: the compression law is not defined in the prompt |

## 6. Run record

- Date 2026-10-08. Instrument `cr09_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; run from the repository root). Attempt 1 returned G0: V2 failed because the synthetic data had x₁ = c = 0 for every point, which makes the normal matrix singular (the shape scan returned nothing); a fault of my validation setup, not of the object. Output kept as `cr09_reset_1_results_attempt1_G0.txt`. The generator was corrected (nonzero x₁ and c with known coefficients 0.14 and 3.1) and the instrument re-run: **Run 1** (registered form), output `cr09_reset_1_results.txt`.
- **Amendment 1 (made after Run 1 was seen).** Run 1's lowest-redshift bin was off by more than 3 standard errors, and the registered error model omitted the peculiar-velocity variance, which dominates at z ≈ 0.01–0.02. Run 2 adds (5/ln 10 × VPECERR/(c·zHD))² to the variance of each supernova and re-derives σ_int by the same registered local rule. Because the amendment follows the sight of Run 1, Run 2 is not blind; both runs are reported, and the grade is taken from the registered reading in both. Output `cr09_reset_1_results_vpec.txt`.
- **Validations met (both runs).** V1: exact recovery of (M, a, b) = (23.7, 0.14, 3.1) to 10 digits. V2: from synthetic n = 0.66, noise 0.10 mag, 500 points, the scan returns n = 0.66. V3: 1701 rows read; the Hubble-flow selection (IS_CALIBRATOR = 0, zHD > 0.01) keeps 1580.
- **Run 1.** σ_int rule on 0.01 < zHD < 0.08 (N = 606): weighted rms 0.1591 mag, ⟨mBERR²⟩^(1/2) = 0.0438 mag, σ_int = 0.1530 mag. Best n = 0.98: χ² = 1592.22, χ²/dof = 1.0103 (dof = 1576); M = 24.0244, a = −0.1360, b = 2.5754. Shape scan, χ²/dof (dof = N − 3 at fixed n): n = 0.50: 230.48; 0.66: 60.10; 1.00: 1.0615; 2.00: 63.95; 4.00: 139.79. Binned residuals (mean in mag, standard error, in standard errors): z 0.0102–0.0224: +0.0632, 0.0116, +5.43; 0.0224–0.0327: −0.0157, −1.36; 0.0327–0.0744: −0.0118, −1.02; 0.0745–0.1852: −0.0075, −0.65; 0.1852–0.2586: −0.0257, −2.23; 0.2586–0.3382: −0.0148, −1.28; 0.3385–0.5102: +0.0027, +0.23; 0.5110–2.2614: +0.0106, +0.93. One bin off by more than 3 standard errors. Registered reading: **structured residual**.
- **Run 2 (peculiar-velocity variance added).** σ_int rule: weighted rms 0.1553 mag, ⟨err²⟩^(1/2) = 0.0782 mag, σ_int = 0.1342 mag. Best n = 0.98: χ² = 1783.67, χ²/dof = 1.1318; M = 24.0207, a = −0.1313, b = 2.5487. Shape scan: n = 0.50: 241.47; 0.66: 62.87; 1.00: 1.1982; 2.00: 67.54; 4.00: 147.33. Binned residuals in standard errors: +4.98 (mean +0.0649 mag), −0.92, −0.86, −0.45, −2.27, −1.25, +0.48, +1.23. One bin off. Registered reading: **structured residual**.

## 7. Outcome and direction

**Grade.** Route B: **G2, open (structured residual)** on the registered reading in both runs. Findings behind the grade:
- The single shape exponent is strongly constrained: χ²/dof is 1.01–1.13 at the best n = 0.98 and rises to 60 at n = 0.66, 64–68 at n = 2, 140–147 at n = 4 and 230–241 at n = 0.5. With the registered reading of n, the data prefer n = 1: the law d = ln(1 + z)/σ₀ with one reciprocity factor (d_L = (1 + z) ln(1 + z)/σ₀) has no shape freedom, and with M, a, b fitted it gives χ²/dof = 1.06 (Run 1) and 1.20 (Run 2).
- The prompt's n ≈ 0.66 and its n = 4 are not reproduced under the registered reading of n (D1); "n" in CR06 is therefore either a different parameter or a different construction, which this record cannot settle.
- One bin is off: the lowest-redshift bin (0.0102 < zHD < 0.0224) lies +0.063 to +0.065 mag fainter than the fitted law (+5.4 and +5.0 standard errors), and adding the peculiar-velocity variance does not remove it. The other seven bins lie within 2.3 standard errors. Possible causes not tested here: a coherent local flow, the redshift convention (zHD against zCMB or zHEL), survey zero points (the file has a survey column; per-survey offsets would add free parameters beyond the declared count), selection near the survey boundaries.
- Limits of the test: diagonal errors (repeated supernovae are correlated; the full covariance is not in the repository); the error scale σ_int (0.13–0.15 mag, from the local rule) is large and makes χ²/dof near 1 easy; the discriminating power lies in the shape scan, which separates n = 1 from the neighbouring values by a factor of 50.
No rival model was fitted. No downgrade by agreement is made.

**What changes for the dependents.** CR12 and the consumers of the z_prop law take from this record: with the registered reading, n = 1 (the octave-telescoping exponential law) is the shape the raw magnitudes choose, with a residual at the lowest redshifts that the law does not account for; the single-power n = 0.66 form is not supported under this reading.

**Direction.**
1. Settle what "n" means in CR06 against the registered reading (D1) before the sibling records are run.
2. Test the lowest-redshift offset with the survey column and the redshift convention registered first (zHD, zCMB, zHEL), with the declared parameter count stated for each variant.
3. The other routes need native definitions first: the gradient g(x) for Route A (with the near-end sampling stated before any slope is compared), the physical shell for C and D (derived from the CR08 physics before any measured peak angle is loaded), the compression law for H.
4. A manifest row for the BOSS BAO table (938 bytes; the DESI DR1 values the prompt cites are not in the repository).

## 8. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
