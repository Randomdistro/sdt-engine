# GOM40b (energy-form solar K and local-k delay rate) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom40b_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM40b/PROMPT.md` in full (including the 2026-10-05 audit correction and the amendment labels C3b, C3c, which refer to an Amendment 01 not present in the prompt text); the GOM26, GOM37 and GOM39 records of this programme (the pairwise-energy estimator and its year-arc results 1476.3512 m for 2025 and 1476.8693 m for 2024, the SCE1 geometry, the delay formula and the local-k ledger). Not read: the archived GOM40b assessment, `RUN_LOG.md`, tools. Exposure: from GOM26 the energy-form K on year arcs of the Earth–Moon barycentre; from GOM39 the instantaneous-speed K 1455.637 m and the Earth@Sun speed 29 355 m/s.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | identity | C2 (K = a/k² with k = √(a/K)) is an algebraic identity (the audit correction already labels it); validation A (the eccentric mock) is a check of the estimator on a noise-free orbit. |
| D2 | input | The prompt names the geocentre (`jpl_horizons_earth_heliocentric_2002_157_160.csv`) as the Earth@Sun arc. The geocentre's velocity carries the monthly Earth–Moon wobble (about 12 m/s). The energy-equality estimator needs Δ(1/r) between epochs large enough that 2μΔ(1/r) exceeds the wobble term 2v·δv: the arc is four days near aphelion, where r changes by about 5×10⁻⁴ AU and 2μΔ(1/r) is about 7×10⁵ m²/s², the same size as 2v·δv (7×10⁵ m²/s²). The estimator is expected to be noise-limited on this arc: that is the content of the prompt's C3b (`ARC_INSUFFICIENT`) and C3c (the year route). The estimator is run as the prompt gives it, reported, and the year route is run as the registered fallback; neither is tuned. |
| D3 | gating | The audit correction asks that the recovered K be gated against a stated tolerance. Registered: the SCE1-arc K against the GOM26 invariant 1476.351 m at 6×10⁻⁴ (the working systematic of GOM39), and the year-route K (2025 calibration, 2024 hold-out, the GOM26 estimator and gates unchanged) at 1×10⁻³ for CV and 1×10⁻³ for the hold-out difference. |
| D4 | scope | C5 (the local-k ledger and Δt, dΔt/dt) is a computation from K and the geometry. The delay-rate amplitude class has no gate by the prompt's own choice (no promotion of the ODF residual); it is published in hertz for the Ka two-way link (Δf = 2F dΔt/dt, F = 32.028 GHz) so that the size can be compared with the noise of GOM37 (0.07–2.1 Hz on a constant-reference segment). |
| D5 | record | The prompt's header says "SCE1 circular proxy K was 1.4% off GOM26"; the GOM39 record of this programme found that miss to be the eccentricity factor of the instantaneous-speed reading, not a circular-speed result. Noted; no consequence here. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Validations.** A: a Kepler mock (e = 0.0167, μ = 10²⁰ m³/s², a = 1.496×10¹¹ m) sampled like the SCE1 arc (397 epochs at 900 s starting at mean anomaly 175°, i.e. near aphelion): μ recovered within 10⁻⁶ (the registered C1 level) and the usable-pair fraction reported. B: K = a/k² with k = √(a/K) for the recovered values, 10⁻¹². C: the delay formula against the closed form at a synthetic geometry, 10⁻¹².
**SCE1 arc (the prompt's route).** Pairs with |Δ(1/r)| > 10⁻¹⁵ m⁻¹ (frozen); μ = the median; K = μ/c²; a from the mean specific energy; per-epoch K_i = v_i²/(c²(2/r_i − 1/a)); CV(K_i); usable pairs. C3b: a ∈ [1.4, 1.6]×10¹¹ m, else `ARC_INSUFFICIENT`. C4: CV < 10⁻³ on a SMA-accepted arc. Continuity: |K − 1476.351|/1476.351 against 6×10⁻⁴ (reported with the gate verdict).
**Year route (C3c).** The GOM26 estimator on the 2025 EMB file (calibration) and the 2024 EMB file (hold-out): K_cal, CV, K_hold, |K_hold − K_cal|/K_cal < 10⁻³; K_cal is the K carried to C5 (frozen from that route, not from Doppler or delay).
**Conjunction ledger (C5).** For the 397 epochs of the SCE1 geometry: b(t) from the Earth and Cassini heliocentric vectors, Δt(t) = (2K/c) ln(4 r_E r_C/b²) with the year-route K, dΔt/dt by a centred difference of ±300 s with cubic interpolation of the 15-minute tables, Δf = 2F dΔt/dt in hertz; local k at the Earth, b and Cassini radii at the middle epoch. Reported: ranges at the first and last epoch and the median |Δf|.
**Decisions.** C1: A met. C2: B met (IDENTITY). C3: the K by both routes COMPUTED, not fitted. C3b/C3c: as above. C4: the CV gate on the accepted arc (on the SCE1 arc if its SMA is accepted, else not evaluable). C5: published. C6: no empirical claim.
**Expected landing (hand estimate before registering).** SCE1 arc: μ is noise-dominated (median pairwise μ off by tens of percent or the usable-pair fraction near zero at the 10⁻¹⁵ threshold); the SMA outside [1.4, 1.6]×10¹¹ m or inside it by accident; `ARC_INSUFFICIENT` most likely. Year route: K_cal = 1476.351 m, K_hold = 1476.869 m, difference 3.5×10⁻⁴ (the GOM26 values). Conjunction ledger: Δt about 6.4×10⁻⁵ s at day 157 rising by 4–5 µs over the arc (for K = 1476.35 m and one-way), Δf = 2F dΔt/dt about 1.0–1.25 Hz (GOM37's solar Doppler proxy).

## 3. Attempt 1 and Amendment 1 (validation design; registered before attempt 2)
**Attempt 1 (kept: `gom40b_reset_1_attempt1_VA_phase_error.txt`).** Validation A returned `usable pairs 0 of 78606`, μ not recovered, `VALIDATIONS NOT MET -> G0`; the run stopped before any data table was read. Cause: my mock starts at mean anomaly 175° (written in Section 2 as "near aphelion"). Day 157 of 2002 is 154.4 days after the perihelion of 3 January, i.e. M = 152.2° (r = 1.0148 AU, which matches the GOM39 value for the real arc). At 175° to 178° the mock's r changes by 9×10⁶ m and Δ(1/r) = 4×10⁻¹⁶ is below the frozen 10⁻¹⁵ threshold for every pair. A defect of my validation design, not of the claim; the data were not touched.
**Amendment 1.** The mock starts at M = 152.2° (derived from the date, not chosen to pass); the usable-pair fraction on the mock is reported (hand estimate before the rerun: Δr ≈ 7.7×10⁷ m over the arc, Δ(1/r) ≈ 3.4×10⁻¹⁵, so a fraction of order half of the pairs exceeds 10⁻¹⁵). Gates, estimator and the threshold are unchanged. The D2 sentence "near aphelion, r changes by about 5×10⁻⁴ AU" stands (5×10⁻⁴ AU = 7.5×10⁷ m), but the arc is not at aphelion.

## 4. Results (attempt 2; COMPUTED; instrument `gom40b_reset_1.cpp`, output `gom40b_reset_1_results.txt`; validations met)
**Validations.** A (Amendment 1, M = 152.2°): usable pairs 33 198 of 78 606 (42%), μ recovered to −1.1×10⁻¹⁴ (gate 10⁻⁶: met); on a year arc −3.3×10⁻¹⁶. B (K = a/k², IDENTITY): 1.1×10⁻¹⁶. C (delay formula): met.
**SCE1 arc, the prompt's route (geocentre, 397 epochs).** r from 1.014731 to 1.015255 AU; 39 355 of 78 606 pairs usable (50.1%). μ (median) = 8.332×10¹⁹ m³/s², **K = 927.11 m** (−37.2% from the GOM26 invariant 1476.351 m), a = 3.531×10¹¹ m (2.36 AU): **outside [1.4, 1.6]×10¹¹ m → ARC_INSUFFICIENT (C3b)**. The pairwise μ quantiles (10%, 50%, 90%) are 7.3, 8.3 and 9.5×10¹⁹: the spread is 25% either side, as the wobble-limited estimate of D2 predicts (2μΔ(1/r) and 2vδv are of the same size on this arc). **CV(K_i) = 1.6×10⁻⁵ (the C4 gate 10⁻³ is met) while K is 37% wrong**: the per-epoch reconstruction uses the same μ and the energy-derived a, so the CV tests the self-consistency of a Kepler arc, not the value of K. Continuity gate (6×10⁻⁴): **not met** (3.7×10⁻¹).
**Year route (C3c, GOM26 estimator, unchanged).** 2025 EMB (27 epochs, 350 of 351 pairs usable): **K_cal = 1476.351201 m**, a = 1.496262×10¹¹ m, CV 1.08×10⁻⁵; 2024 hold-out: **K_hold = 1476.869308 m**, CV 1.02×10⁻⁵; |K_hold − K_cal|/K_cal = **3.51×10⁻⁴** (gate 10⁻³: met). These reproduce the GOM26 values to the printed digits.
**Conjunction ledger (C5; K = K_cal; 391 epochs, the first and last 3 table epochs trimmed for the centred difference).** b falls from 47.20 to 34.81 R☉; the one-way Shapiro delay rises from 63.343 µs to 69.363 µs (rise 6.02 µs); Δf = 2F dΔt/dt rises from 0.943 Hz to 1.290 Hz (median 1.090 Hz). Local k at the middle epoch: Earth (1.0150 AU) 10 141.5, b (41.02 R☉) 4396.6, Cassini (7.3772 AU) 27 341.0; z = K/r = 9.72×10⁻⁹, 5.17×10⁻⁸, 1.34×10⁻⁹.
Landing against the hand estimate: the arc is noise-limited and ARC_INSUFFICIENT (held); the year route reproduces the GOM26 values (held); Δf 1.0–1.25 Hz (held for the day means; the epoch extremes are 0.94 and 1.29); the one-way delay rise was estimated at 4–5 µs and the table gives 6.0 µs (the arc is 4.1 days from the first to the last epoch, not 3, which I had used).

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 mock recovery | **VERIFICATION, met** | 10⁻¹⁴ |
| C2 K = a/k² | **IDENTITY** | 10⁻¹⁶ |
| C3 energy-form K on the SCE1 arc | **COMPUTED; ARC_INSUFFICIENT** | K = 927 m, a = 2.36 AU; the geocentre arc is wobble-limited |
| C3b | **not met** (a outside [1.4, 1.6]×10¹¹ m) | label ARC_INSUFFICIENT |
| C3c year route | **COMPUTED, met** | K_cal 1476.3512 m; hold 3.5×10⁻⁴; the same as GOM26 (a repeat of the same estimator and files, not an independent determination) |
| C4 CV < 10⁻³ | **met on the SCE1 arc but uninformative** | CV 1.6×10⁻⁵ with K 37% wrong: the gate tests arc self-consistency, not K; on the year route it is a test (1.1×10⁻⁵ with K inside 4×10⁻⁴ of the hold-out) |
| C5 local-k ledger and delay rate | **COMPUTED** | Δt 63.3 → 69.4 µs; Δf 0.94 → 1.29 Hz; compared with the 0.07–2.1 Hz noise of a constant-reference segment (GOM37) the rise of 0.35 Hz over the arc is of the size of the segment noise |
| C6 | **no empirical claim** | K not fitted to ODF, Doppler or delay |
No downgrade is made on agreement grounds.

## 6. Direction
1. The energy-form K is recoverable from a year arc of the barycentre (K_cal, hold-out 3.5×10⁻⁴) and not from the four-day geocentre arc: a short arc needs an EMB state (no Moon wobble) and a baseline in 1/r several times longer. A short-arc estimator should be gated by the SMA and by the pairwise spread (reported here), not by the CV.
2. The audit correction's request (gate on the recovered K) is met by the continuity gate on the SCE1 arc (not met) and by the hold-out on the year route (met).
3. For the solar-Doppler route the delay-rate of the ledger is 0.94 → 1.29 Hz over the arc: a segment-wise test near conjunction (b falling to a few R☉) increases it; GOM37 direction 1 stands.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
