# GOM26 (solar koppa orbital invariant) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom26_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM26/PROMPT.md` in full; the GOM25 record of this programme (the 1.22% epoch variation of the instantaneous v²r/c², the regression constant A/2 = 1.476399 km, the surface-shift comparison 633.7 m/s against 638 ± 6 m/s); the headers of the two vector files. Not read: `GOM26_ASSESSMENT.md`, `GOM26_C4_MULTI_YEAR_*`, `RUN_LOG.md`, `gom26_koppa_invariant.cpp`. Exposure: the GOM25 result in this programme (an invariant near 1.4764 km from a regression, a different estimator). Frozen files (MD5): `jpl_horizons_emb_sun_vectors_2025.csv` 7280c315d7f129d2a6ec64d82c3ba21b (calibration, 27 rows from 2025-01-01 TDB); `jpl_horizons_emb_sun_vectors_2024.csv` 533bd9998529c2f03ac92ffa50c230fa (held out, 27 rows from 2024-01-01 TDB; a distinct, genuine year).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | gating | `N_eff` in σ_μ = 1.4826·MAD/√N_eff is not defined. The 351 pairs are built from 27 epochs and are not independent. Registered: N_eff = N = 27 (the epochs); sensitivity with N_eff = the number of retained pairs is reported. |
| D2 | gating | "CV" is not defined. Registered: sample standard deviation (n − 1) over the mean. |
| D3 | gating | The spectral map v_pred = cϟ/R_Sun omits the observer term −cϟ/r (3 m/s) that GOM25's amendment 01 restored. The registered equation is followed; the difference is reported. R_Sun: the IAU nominal 6.957×10⁸ m primary; 695 658 km as a sensitivity (σ_pred is from μ only, as the prompt says). |
| D4 | premise | C1 and C2 assume Keplerian two-body kinematics for the EMB–Sun relative orbit (the prompt says this is a kinematic premise of the repair, not an SDT law). The relative orbit is perturbed (the planets act on the EMB and on the Sun); the invariance gate tests how far. The pairwise estimator uses only r and |v| (no direction), and the estimates for pairs with nearly equal r are noisy; the median is used as specified. |
| D5 | record | The relation ϟ = μ/c² is a definition of the constant of the orbit; ϟ is then identical to the Kepler constant GM/c² numerically. The chain uses neither G nor M, as the prompt requires. The numerical equality with the standard value is convergence (shared form), not independent evidence of anything beyond the Kepler relation. |
| D6 | gating | The Cassini side-probe (SCE1 ATDF) stays PENDING_DATA: the ODF is decoded in this programme (GOM_DAT8) but an independent geometry and clock reconstruction (ATDF/TDF decode, ramp, Fbias) is not done. |
No downgrade is made on agreement grounds.

## 2. Registered quantities, validations, decisions (fixed before the run)
**Estimator (frozen by the prompt).** μ_ij = (v_j² − v_i²)/(2(1/r_j − 1/r_i)) for pairs with |Δ(1/r)| > 10⁻¹⁵ m⁻¹ (SI units); μ = the median; σ_μ = 1.4826·MAD/√N_eff (D1); ϟ = μ/c²; E_i = v_i²/2 − μ/r_i; a = −μ/(2⟨E⟩); ϟ_i = v_i²/(c²(2/r_i − 1/a)); CV = sd/mean of the ϟ_i (D2).
**Decisions.** C1/C2 (invariance gate): CV on the calibration year < 10⁻³; μ positive and finite; usable pairs ≥ 50%; otherwise NO RECOVERY. C3: v_pred = cϟ/R_Sun; EXCLUDED if |v_pred − 638| > 2√(σ_pred² + 6²), else COMPATIBLE (adjudication UNADJUDICATED), σ_pred = v_pred·σ_μ/μ. C4: |ϟ_hold − ϟ_cal|/ϟ_cal < 10⁻³ with ϟ_hold from the 2024 file by the same estimator (not re-tuned); the intra-year odd/even split is reported as a descriptive additional hold-out. No retuning of ε, the CV threshold, the 2σ rule or R.
**Validations (before the targets are read).** A: a near-circular Kepler mock (e = 0.01, arbitrary μ = 10²⁰ m³/s², a = 1.5×10¹¹ m, 27 samples at 14-day cadence): μ recovered within 10⁻⁸, CV < 10⁻⁶. B: an eccentric mock (e = 0.0167): same thresholds. C: delete-test: ϟ is printed before `bridge::koppa_Sun` or any HARPS value is read.
**Descriptive, after ϟ is printed.** The ratio to `bridge::koppa_Sun`; the quantile spread of the pairwise μ_ij; the GOM25 regression constant A/2 = 1.476399 km compared with the new ϟ; the instantaneous v²r/c² mean (1.477262 km) compared with the invariant.
**Expected landing (hand estimate before registering).** ϟ ≈ 1.4766 km (the standard solar constant with the barycentre's mass added); CV of the ϟ_i about 10⁻⁵ (planetary perturbation of the relative energy); v_pred ≈ 636.3 m/s; COMPATIBLE with 638 ± 6; C4 at the 10⁻⁵ level. The rejection class (CV > 10⁻³; |ϟ_hold − ϟ_cal| > 10⁻³) is populated by the instantaneous-form variation of 1.2% found in GOM25.

## 3. Results (COMPUTED; instrument `gom26_reset_1.cpp`, output `gom26_reset_1_results.txt`; single pass, no amendment; validations met)
**Validations.** A (e = 0.01) and B (e = 0.0167): μ recovered to 3.3×10⁻¹⁶ and 7.8×10⁻¹⁶, CV 4×10⁻¹⁶ (met). C (the delete-test): ϟ was printed before `bridge::koppa_Sun` or any HARPS value was used.
**Calibration (2025, 27 epochs).** 351 pairs, 350 usable (99.7%). μ = 1.326878288×10²⁰ m³/s²; σ_μ = 1.88×10¹⁶ (relative 1.42×10⁻⁴, N_eff = 27) or 5.2×10¹⁵ (3.9×10⁻⁵, N_eff = usable pairs). Semi-major axis a = 1.496262×10¹¹ m (1.000189 AU). **Invariant ϟ = μ/c² = 1476.3512 m; CV of the ϟ_i = 1.08×10⁻⁵** (gate 10⁻³: met), against the 1.22% of the instantaneous v²r/c² (GOM25).
**Held out (2024, 27 epochs).** μ = 1.327343939×10²⁰; **ϟ = 1476.8693 m**; CV 1.02×10⁻⁵; **|ϟ_hold − ϟ_cal|/ϟ_cal = 3.51×10⁻⁴** (gate 10⁻³: met). Intra-year odd/even split (descriptive): 1476.3847 and 1476.3411 m, relative difference 2.95×10⁻⁵.
**Spectral map.** v_pred = cϟ/R_Sun = **636.192 m/s** (R = 6.957×10⁸ m); σ_pred = 0.090 m/s; |v_pred − 638| = 1.81 m/s; threshold 2√(σ_pred² + 6²) = 12.00 m/s: **COMPATIBLE** (UNADJUDICATED). Sensitivity: R = 695 658 km gives 636.231 m/s; with the observer term (GOM25's amendment 01) 633.234 m/s (difference 2.96 m/s).
**Descriptive (after the print).** ϟ/`bridge::koppa_Sun` = 0.999530; ϟ against the GOM25 regression constant A/2 (1.476399 km): 0.999968; against the instantaneous mean (1.477262 km): 0.999383. For comparison with the standard constant (quoted, not an input): μ_cal/GM_IAU = 0.999815 and μ_hold/GM_IAU = 1.000165, so the two years straddle it at −1.9×10⁻⁴ and +1.7×10⁻⁴.
The expected landing held for ϟ (≈ 1.4766 km), the CV (the estimate 10⁻⁵ was met at 1.1×10⁻⁵) and the spectral result; it did not hold for C4: the estimate was 10⁻⁵ and the measured year-to-year difference is 3.5×10⁻⁴.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1/C2 invariant exists and equals μ/c² (CV gate) | **G3, COMPUTED; shared-form** | CV 1.08×10⁻⁵ against 1.2% for the instantaneous form; the Kepler energy relation is the premise (D4) and the constant equals GM/c² numerically (D5) |
| C3 spectral compatibility | **COMPATIBLE, UNADJUDICATED** | 636.19 against 638 ± 6; the HARPS summary retains its 3D-model and wavelength nuisances; not discriminating against GM/(Rc²) |
| C4 hold-out | **met at 3.5×10⁻⁴ (gate 10⁻³)** | the year-to-year difference is 2.5× the pairwise σ_μ (N_eff = 27) and 9× the σ_μ with N_eff = pairs: the invariant carries a systematic of about 4×10⁻⁴ from the departure of the EMB–Sun relative orbit from a two-body orbit; the quoted statistical σ_μ understates it |
| D4 Cassini side-probe | **PENDING_DATA** | independent geometry and clock reconstruction not done |
The repair (replace the instantaneous v²r/c² by the orbital invariant) works in the registered sense: the epoch variation of 1.2% in GOM25 is removed (to 10⁻⁵), the spectral comparison is unchanged in outcome (636.2 against 633.7 m/s previously, both compatible with 638 ± 6), and the hold-out agrees to 4×10⁻⁴.

## 5. Direction
1. Adopt the invariant as an investigation-level derived initial condition (the prompt's downstream rule: C1–C4 pass), with its systematic of 4×10⁻⁴; canon adoption propose-and-wait.
2. State σ_ϟ for later tests as 4×10⁻⁴ (the year-to-year spread), not the pairwise statistical σ_μ.
3. The two-body premise is the weak point: a fit that includes the planetary perturbation (or a multi-year baseline) would show whether the systematic is the perturbation; not registered here.
4. Cassini side-probe: unchanged (the ATDF/TDF decode and the independent geometry are owed).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
