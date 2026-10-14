# SAR09 (KIC 8462852), Round 2: Q3 spin-phase coherence — registration and assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–3 are the registration, written **before** `sar09_reset_2.py` exists. Sections 4 onward are filled in after the run.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (state after the reset; X1–X2; Round 2: Q2, Q3, escape (b)); `SAR09_RESET_ASSESSMENT_2026-10-10.md` and `sar09_reset_1.py` (the Kepler loading, the V1 and V2 definitions; the Q1 result); `C:\sdt-data\kic8462852\DATA_MANIFEST.md`. Not read: `SAR09_ASSESSMENT_2026-07-30.md`, `RUN_LOG.txt`, `sar09_gamut.py`, the paper tarballs.

Exposure: the prompt states V2's result (rotation 0.8806 d) and V1's dips; no fine-structure phase has been looked at. Kepler light-curve values entered only through the reset run's printed V1/V2 numbers.

Q2 (colour-ratio variability) is **not run in this round**: its prediction for redirection ("the chromatic form derived from the lens formulation for an F3 photosphere") has not been written (the prompt says it must be written first; no such derivation is on file), and the published ratios are in tarball figures and prose, not machine-readable tables (DATA_MANIFEST gap 1).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | confound in the registered statistic | A Rayleigh test on the phases of dip-minima of a light curve that still carries the star's own rotation modulation is expected to be significant under **both** accounts: an opaque or absorbing cloud that covers the disc in proportion multiplies the rotating flux by a smooth factor and leaves the modulation at its phase. The prompt's contrast ("redirection predicts phase coherence; debris on Keplerian orbits does not") holds only for fine structure that is not the rotation modulation itself. Registered handling: the Rayleigh gate is run as the prompt specifies, with a positive control on out-of-dip cadences (the rotation modulation alone), a synthetic null, and a reported, not graded, amplitude ratio; a gate pass is labelled "coherent, not discriminating" unless the ratio test below separates it. |
| D2 | undefined terms | "Dip fine structure" and "dip-minimum phases" are not defined in the prompt. Definitions are fixed in Section 2. |
| D3 | rotation baseline | A phase fold across 1500 d needs P to about 10⁻⁵ d (1700 cycles); V2 gives 0.88 d only to its 0.02 d tolerance. The fold uses a period fitted on the same data (Section 2), and its uncertainty is carried. |

## 2. Registered definitions, gates, controls (fixed before the run)
**Data.** Kepler long-cadence PDCSAP_FLUX, all 18 files in `C:\sdt-data\kic8462852\`, finite TIME and flux, each file divided by its median (the V1/V2 convention). Segments split at time gaps > 0.5 d.

**Envelope and residual.** Within each segment E(t) = running median over a 3.0 d window (3.4 rotation periods, so the rotation modulation is not absorbed into the envelope). Residual r = f/E − 1. Smoothed residual r_s = 3-cadence boxcar (1.5 h).

**Sets.** Dip set D: cadences with E < 0.99 (deficit ≥ 1 % against the envelope's own scale; normalised flux units). Quiet set O: cadences with E ≥ 0.995 and f ≥ 0.99.

**Rotation period.** Lomb–Scargle on f in O, search 0.80–0.96 d on a grid of 2×10⁻⁶ d, then parabolic refinement of the peak. Reported with its formal width (≈ P²/T_baseline). V2's 0.88 ± 0.02 d tolerance is the validation.

**Minima.** A cadence i of segment s is a minimum if r_s[i] is the minimum of r_s within ±0.22 d (±0.25 P) and r_s[i] ≤ −3σ_O, with σ_O = 1.4826 × MAD of r_s over O. Phase φ_i = frac((t_i − t₀)/P) (t₀ arbitrary; the test is invariant).

**Statistic.** Rayleigh: R̄ = |n⁻¹ Σ exp(2πiφ_i)|, Z = n R̄², p = exp(√(1 + 4n + 4(n² − n²R̄²)) − (1 + 2n)) (Zar 1974 approximation). **Gate G-Q3 (prompt): p < 0.01 for the minima in D**, n ≥ 20 required (otherwise "not testable").

**Controls and validations.**
- **V-A (period).** Strongest quiet-set peak within 0.02 d of 0.88 d.
- **V-B (positive control on real data).** The same minima-and-Rayleigh statistic on O, with n_O reported: the rotation modulation alone must give p < 0.01 (expected; it is the rotation signal).
- **V-C (synthetic, planted coherent).** Gaussian noise with σ_O, a sinusoid of amplitude 0.2 % at the fitted P on the Kepler time stamps, minima and Rayleigh as above: recovered p < 10⁻⁶.
- **V-D (synthetic null).** Same time stamps, noise only, 200 realisations: fraction with p < 0.01 between 0 % and 3 %.
- **V-E (look-elsewhere).** The D minima folded at 200 trial periods uniform in 0.70–1.10 d excluding |P_trial − P| < 0.01 d: report the fraction with Z ≥ Z_obs. The gate counts as met only if p < 0.01 **and** this fraction < 0.01.
- **Reported, not graded.** (i) Phase offset between the D minima's mean phase and the O minima's mean phase (circular difference), with a 95 % bootstrap interval. (ii) Modulation amplitude in D against O: A_D/A_O from a fit of r = a cos 2πφ + b sin 2πφ in each set, compared with the covering-factor expectation 1 − (mean D deficit) if the rotation modulation is carried by a smooth occulting factor.

**Hand estimates before the run.** n_D: a few hundred (D covers about 10 % of 70 000 cadences, ~7 000, with a minimum every ≥ 0.44 d at 3σ), p tiny if the rotation modulation survives the envelope at the dips, because the amplitude ratio stays near (1 − deficit). Expected: gate met by D1's construction; the discriminating content, if any, is in the offset and A_D/A_O.

**Label in advance:** a pass is "coherent, not discriminating" (D1). A non-detection (p ≥ 0.01 or fraction ≥ 0.01) is recorded as "no coherence found in D at this threshold" without a mechanism claim.

## 3. Prohibitions applied
No dust model tuned; no redirection claim without its own registered magnitude (none made); registered thresholds are not moved after the fold.

## 4. Results (attempt 1; `sar09_reset_2.py`, output `sar09_reset_2_results.txt`; 9 s run)
- Segments 51, cadences 63 856 (segments shorter than two filter windows were dropped by my loader, against 69 778 in the manifest).
- **V-A met in letter:** quiet-set Lomb–Scargle peak P = 0.896172 d (within 0.02 d of 0.88; width 5.5×10⁻⁴ d). It differs from the 0.8806 d the reset run reported for V2 (different quiet-set definition and search range).
- Dip set D (E < 0.99): **520 cadences**; quiet set O: 62 693 cadences. Minima at 3σ_O (σ_O = 1.48×10⁻⁴): **n_D = 7** (gate needs ≥ 20), n_O = 105.
- **G-Q3: not testable (n_D = 7 < 20); Z = 0.25, p = 0.79; look-elsewhere fraction 0.84.** No coherence statement can be made from this.
- **V-B NOT MET:** the quiet-set minima give p = 0.068. Fold of the residual on P: A_O = 2.1×10⁻⁶ (the rotation modulation vanishes on the fold, i.e. it is not phase-coherent at this single P over 1461 d).
- **V-C NOT MET:** a planted 0.2 % coherent sinusoid returned n = 0 minima (p = 1). V-D met (null false-alarm 0.000; median n_D = 13).

## 5. Why this is an instrument failure and not a result
Three defects in my registration, found in the output, each independent:
1. **The envelope removes the dips.** A 3.0 d running median follows a dip only when the dip occupies more than half the window (1.5 d), and tracks it with a lag. Only 520 cadences (0.8 %) enter D; I did not inspect which dips they belong to, so which events are missing is not established here. The dips must be defined on the flux against an upper envelope, not on a median.
2. **The 3σ_O threshold is self-defeating.** σ_O is a robust scatter of the same residual that carries any coherent signal; for a planted 0.2 % sinusoid σ_O rises to the signal's own scale and no minimum passes −3σ_O (V-C, n = 0). The threshold must be set from the white-noise floor (point-to-point scatter), not from the total quiet-set scatter.
3. **A single global fold is invalid for this star.** The rotation modulation does not survive a fold at one period over four years (A_O = 2×10⁻⁶; the quiet-set peak lies at 0.896 d against 0.8806 d from V2, a 1.7 % difference worth about 28 cycles across the baseline). Phase coherence must be tested against a **local** rotation reference measured next to each dip (D3 in Section 1 anticipated the precision, not the loss of coherence itself).

The two validations that bear on the claim (V-B and V-C) fail, so G-Q3 is withheld on its own terms. Nothing in this run supports or excludes surface-tied redirection.

## 6. What a runnable Q3 needs (proposal; not registered or run)
- Dips defined on the flux against a running upper envelope (deficit ≥ 1 %), fine structure taken after a boxcar baseline of one rotation period (this keeps the fundamental in the residual for any dip profile longer than P).
- The detection threshold from the point-to-point scatter.
- For each dip event, a rotation phase measured from quiet cadences immediately before and after (fixed P; both references must agree within a registered tolerance, otherwise the event is excluded), and the Rayleigh test run on the fine-structure phases **relative to that local reference**, pooled over events.
- Still under D1: a pass means "coherent with the star's rotation", which uniform occultation also gives. A discriminating statistic needs a native prediction for the fine-structure amplitude and phase of redirection, which is owed (the lens-formulation derivation named in the prompt for Q2 is the same dependency).

## 7. Grades
| Item | Grade |
|---|---|
| Q3 spin-phase coherence | **instrument not valid (V-B, V-C not met); G-Q3 not testable (n_D = 7); no result** |
| Q2 colour ratios | **not run**: the redirection prediction is unwritten and the ratios are not machine-readable |
| Escape (b) covering fraction | not run |
| Cause of failure | my registered definitions (envelope, threshold, global fold), recorded as attempt 1 |

## 8. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
