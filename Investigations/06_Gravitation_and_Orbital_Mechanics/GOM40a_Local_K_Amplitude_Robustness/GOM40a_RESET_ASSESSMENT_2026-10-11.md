# GOM40a (local-K amplitude robustness rerun) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom40a_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM40a/PROMPT.md` in full; the GOM37 and GOM39 records of this programme (the residual construction, the numbers of GOM37 run 1, and the finding that the GOM39 literal reading K = 1455.637 m is the instantaneous-speed value that misses the eccentricity factor by 1.40%). Not read: the archived GOM40a assessment, `RUN_LOG.md` and tools. Exposure: GOM37's run-1 numbers (amplitude ratio 2.338×10⁵, |corr| with delay rate 0.9920, with time 0.9954) are known from this programme and serve as the reproduction target.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | The delay-rate proxy f·dΔt/dt is linear in K. The amplitude ratio stdev(r⊥)/median|F·dΔt/dt| therefore scales as 1/K; the correlations with the delay rate and with time are invariant under a positive scale of the proxy. The "repair" can change the amplitude ratio by the factor 1476.350/1455.637 = 1.01423 and nothing else. The decision rule (ratio < 100 and not time-confounded) is then decided by arithmetic on GOM37's numbers; the instrument is a reproduction and a bookkeeping check, not a new measurement. |
| D2 | premise | The second case is the GOM39 literal reading (Earth instantaneous-speed K = 1455.637 m). GOM39 of this programme found that reading wrong by the eccentricity factor (the circular-speed reading gives 1477.255 m, +6.1×10⁻⁴ from the invariant). The case is run as the prompt fixes it and labelled as a documented non-invariant value; the invariant case is the GOM37 baseline. |
| D3 | scope | The prompt's decision rule applies to GOM37's Procedure A′ (level-ratio scale, train-only linear detrend). That procedure was retired in GOM37 run 1 (10⁵ Hz extrapolation residuals); it is still run here because the rule is stated for it. The amended residuals (M1, M2) are reported beside it. |
| D4 | gating | GOM37's sensitivity gate (predicted day-to-day changes against the scatter of the daily means) is also linear in K: with a 1.4% change in the prediction the gate cannot change status (ratio 0.000–0.36 stays far from 3). |
| D5 | record | The input hashes in the prompt come from the earlier programme; they are checked first as an integrity step, before any numeric field is read. A mismatch is reported and stops the run. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Integrity.** SHA-256 of the eight K252 files (ODF and label, days 157–160) and the three Horizons files against the prompt's table.
**Instrument.** The GOM37 run-1 reduction (`gom37_reset_1.cpp`) with K a run-time argument (no other change): K₁ = 1476.350 m (baseline), K₂ = 1455.637 m (GOM39 literal). Per case: Procedure A′ amplitude ratio, |corr(r⊥, dΔt/dt)|, |corr(r⊥, time)|, the delete-test; amended M1 and M2 ratios; the sensitivity gate.
**Validation.** V1: case K₁ reproduces GOM37 run 1 (A′ ratio 2.338×10⁵, |corr| 0.9920 and 0.9954) to the printed digits. V2: the ratio of the two cases' amplitude ratios equals K₁/K₂ = 1.01423 to 10⁻⁶ and the correlations agree to 10⁻¹² (the D1 identity).
**Decision.** As the prompt: `REOPEN_FOR_DEFINED_OBSERVABLE` iff either case has an A′ amplitude ratio < 100 and is not time-confounded; otherwise `LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES` (not a physical exclusion).
**Expected landing (hand estimate before registering).** Case K₁: 2.338×10⁵, 0.9920, 0.9954; case K₂: 2.371×10⁵, correlations identical; gate not met in both; outcome `LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES`.

## 3. Results (COMPUTED; instrument `gom40a_reset_1.cpp`, outputs `gom40a_reset_1_results_K1476.350.txt` and `..._K1455.637.txt`)
**Integrity.** All eleven SHA-256 hashes (eight K252 files, three Horizons files) equal the prompt's table; checked before any numeric field was read.
**Attempt log.** The first execution of the K₂ case was started from the scratchpad directory instead of the repository root, the relative data paths failed and the instrument returned `VALIDATIONS NOT MET -> G0` (one line, overwritten by the correct run); the K₂ result below is the second execution, from the repository root. K₁ ran once.
**Validations.** V1: case K₁ reproduces GOM37 run 1 (day 157: 7447 records, residual sd 2.639 Hz; A′ ratio 2.338×10⁵, |corr| 0.9920 and 0.9954, M1 and M2 ratios 8.706×10⁴ and 1.579×10⁴): met. V4 and V5 of the GOM37 reduction: met in both cases. V2 (identity D1): the K₂ outcomes are the K₁ outcomes times 1.01423 to the printed digits (A′ 2.371×10⁵ against 2.338×10⁵ × 1.01423 = 2.371×10⁵; M1 8.830×10⁴ against 8.829×10⁴; M2 1.601×10⁴ against 1.601×10⁴) and every correlation is identical at four decimals; the registered levels (10⁻⁶ on the ratio, 10⁻¹² on the correlations) are not testable from four printed digits, the identity itself is algebraic.
**Results by case.**
| Case | K (m) | A′ amplitude ratio | \|corr\| with delay rate | \|corr\| with time | Delete-test | M1 ratio | M2 ratio | Sensitivity gate (largest predicted change) |
|---|---|---|---|---|---|---|---|---|
| GOM37_FROZEN | 1476.350 | 2.338×10⁵ | 0.9920 | 0.9954 | confounded | 8.706×10⁴ | 1.579×10⁴ | not met (0.2593 Hz) |
| GOM39 literal (Earth instantaneous speed) | 1455.637 | 2.371×10⁵ | 0.9920 | 0.9954 | confounded | 8.830×10⁴ | 1.601×10⁴ | not met (0.2557 Hz) |
Outcome by the prompt's rule: neither case has an A′ ratio below 100, both are time-confounded: **LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES** (not a physical exclusion). The amended outcome is unchanged: UNADJUDICATED_BY_SENSITIVITY.
The expected landing held in every printed number (2.338×10⁵ and 2.371×10⁵; correlations identical; gates not met).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Reproduction of GOM37 run 1 | **VERIFICATION, met** | every printed GOM37 number reproduced |
| Local-K repair of the GOM37 gates | **does not clear** | the proxy is linear in K: the amplitude ratio scales as 1/K (1.4%), the correlations are scale-invariant, the gate is 3 orders from changing |
| Case K₂ = 1455.637 m | **documented non-invariant reading** | GOM39 of this programme: the instantaneous-speed value misses the eccentricity factor by −1.40%; the circular-speed reading is 1477.255 m, so the K₁ case is the right baseline |
| K (the solar invariant) | **not tested, not fitted** | no empirical status change: UNADJUDICATED_BY_SENSITIVITY |

## 5. Direction
1. The gates of GOM37 cannot be cleared by any fixed K because the failures are in the observable (the receiver-chain offset follows the record's reference frequency and ramp history), not in the K value: the repair must come from the TDF ramp and bias reconstruction (GOM_DAT9) or from segment-wise tests near conjunction (GOM37 direction 1).
2. The prompt's two-value design is retired in favour of that route; GOM40b (energy-form local-k delay) takes the same data and should be read as bookkeeping of the delay formula, not a new observation.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
