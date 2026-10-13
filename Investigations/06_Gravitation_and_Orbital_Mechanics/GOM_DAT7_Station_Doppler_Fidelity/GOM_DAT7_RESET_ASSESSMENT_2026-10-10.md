# GOM_DAT7 (DSS-25 station LOS and band/turnaround Doppler fidelity) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom_dat7_reset_1.cpp` exists. Results are section 3 onward.

## 0. Inputs read and exposure
Read: `GOM_DAT7/PROMPT.md` in full (including the 2026-10-05 audit correction); the headers of the geocentric Horizons table; and, from this programme, `GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md` (the ODF decode, the label's observable formula, and the DAT8 results). Not read: every other file in the GOM_DAT7 folder (`GOM_DAT7_ASSESSMENT.md`, `RUN_LOG.md`, `gom_dat7_station_doppler.py`). Exposure: DAT8's results are known and bear directly on this prompt (the observable carries a constant offset of −2.51 MHz; the identified carrier is 32.028 GHz; the two-way geometry is needed). Predictions below are therefore partly derived from DAT8 and are labelled as such.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | C4 compares median levels (|f_pred|/|obs|, median|obs − f_pred|). The label's formula makes the observable a count rate minus a reference term (a bias placed on the receiver), and DAT8 found a constant offset of −2.51 MHz under a 30.6 kHz change. A level gate cannot pass for a predictor that is a true Doppler shift (about 2.5 MHz) while the observable is 35–66 kHz. The gate tests the bias, not the predictor. |
| D2 | gating | The audit correction asks for an absolute fidelity threshold but does not give one. Registered: level gate G-abs: |median|f|/median|obs| − 1| < 0.15 and median|obs − f|/median|obs| < 0.15 (the DAT8 form). |
| D3 | premise | The prompt applies "turnaround ρ = 209/15 when Item 11/12 = Ka" with `f_up` = the reference frequency (Items 18–19). In the label 209/15 is the receiver-side K of the observable formula for Ka; the Ka transmitter ratio is T1/T2 = 14/15; and Items 18–19 (2.1166 GHz here, exciter band S) is an exciter-scale frequency, not the uplink carrier. ρ·f_ref = 29.49 GHz therefore mixes scales. Both branches (primary ρ·f_ref and the documented Ka downlink 32.028 GHz) are run as the prompt requires. |
| D4 | gating | Predictor A (geocentre LOS, GOM33 form) is not defined in the prompt. Registered: f_A = −2(ṙ_geo/c)·f_ref, ṙ_geo = (r·v)/|r| from the geometric state vectors of Cassini relative to the Earth's centre, TDB converted to UTC by −64.184 s (TT−UTC for 2002); light-time is not corrected (the table has no epochs before 20:30; the bound is (dṙ_geo/dt)·δ/c, evaluated from the table slope). |
| D5 | record | A receive-time range rate omits the transmit-epoch diurnal term (DAT8: 252 Hz rms against 2.6 Hz with the two-way average). The prompt's predictors are receive-time; two-way variants are added for the change-based gate. |
| D6 | record | Per the prompt's own alias these rows are VERIFICATION and are outside the physics tallies; solar K is not used. |
No downgrade is made on agreement grounds.

## 2. Registered quantities, validations, gates
**Selection and decode.** As GOM_DAT8 Phase A (type 12, valid, receiving and transmitting station 25; 7447 records). Time tags are UTC.
**Predictors.** A: f_A = −2(ṙ_geo/c)·f_ref. B1 (primary, prompt): f_B1 = −2(ṙ_rx/c)·(209/15)·f_ref with ṙ_rx the DSS-25 `deldot` at the receive time. B2 (sensitivity, prompt): f_B2 = −2(ṙ_rx/c)·32.028×10⁹. Two-way variants B1w, B2w with ṙ_2w = ½[deldot(t) + deldot(t − RTLT)] (RTLT = 2·delta·AU/c, 15-min table for the up-leg). f_ref = 2 116 648 992 Hz (the records' constant).
**Validations.** VC1: the geocentric |r_geo| equals the DSS-25 `delta`·AU to 10⁻⁴ relative at all 31 epochs (the station-to-centre offset is at most 6378 km of 1.25×10⁹ km). VC2: |ṙ_geo − deldot_DSS25| < 0.5 km/s at all epochs (bounded by the Earth's equatorial rotation speed, 0.465 km/s). VC3: 7447 records selected (DAT8). VC4: RTLT in 8300–8400 s.
**Gates.**
- G-rel (prompt C4, relative): for B (each of B1, B2): median|f_B|/median|obs| closer to 1 than 3.37, or median|obs − f_B| smaller than median|obs − f_A|.
- G-abs (the audit correction, absolute): as in D2.
- C4 (corrected) = G-rel and G-abs.
- G-chg (native, from the label formula and DAT8): for each predictor and both signs, R = Δobs/Δf over each third (mean of the first and last 100 records within the third) and over the whole span (first and last 300 records); a predictor passes iff |R − 1| < 0.05 in all four windows. Reported for A, B1, B2, B1w, B2w.
**Residual summary (prompt C5).** min, median, max, standard deviation of obs − f_B (sign as defined) for B1 and B2; and, descriptive, of obs − s·f − mean for the two-way variants after the sign and the constant offset are removed.
**Light-time bound for A.** (dṙ_geo/dt) · δ/c from the table slope, reported.
**Expected landing (partly derived from DAT8).** G-abs and G-rel fail for A, B1, B2 (levels: |f_A|/|obs| ≈ 3.4, |f_B1|/|obs| ≈ 47, |f_B2|/|obs| ≈ 51; the residual of B is about 2.5 MHz against about 0.12 MHz for A, so the relative branch also fails); G-chg: B2w passes (R ≈ 1.000); B1w gives R ≈ 1.086 and fails; A and the receive-time variants fail. The rejection class is populated by A, B1 and the receive-time variants.

## Grades available
VERIFICATION rows (not in the physics tallies): met / not met per gate, with the contaminating input named.

## 3. Results (COMPUTED; instrument `gom_dat7_reset_1.cpp`, output `gom_dat7_reset_1_results.txt`; single pass, no amendment)
**Validations.** VC1 met (|r_geo|/(delta·AU) − 1 worst 2.4×10⁻⁵ at 31 epochs, geocentre interpolated to UTC); VC2 met (|ṙ_geo − deldot| worst 0.203 km/s); VC3 met (7447); VC4 met (RTLT 8345.3–8345.9 s). Light-time bound for A: dṙ_geo/dt = −4.77×10⁻⁶ km/s², times δ/c (4173 s) = −0.0199 km/s (0.17% of ṙ).
**Level gates (median |obs| = 50 244.3 Hz).** | predictor | median|f|/median|obs| | median|obs − f| (Hz) | G-rel | G-abs | C4 |
|---|---|---|---|---|---|
| A (geocentre, f_ref) | 3.364 | 219 266 | baseline | not met | baseline |
| B1 (DSS-25 rx, 209/15·f_ref) | 47.26 | 2 424 606 | not met | not met | **not met** |
| B2 (DSS-25 rx, 32.028 GHz) | 51.32 | 2 628 778 | not met | not met | **not met** |
| B1w (two-way) | 46.92 | 2 407 927 | not met | not met | not met |
| B2w (two-way) | 50.96 | 2 610 665 | not met | not met | not met |
A's ratio 3.364 reproduces the prompt's quoted 3.37. The expected landing held: the level gates fail for every predictor because the observable is 35–66 kHz and a true Doppler shift is about 2.5 MHz (D1).
**Residual summary (prompt C5, obs − f_B as defined).** B1: min 2 394 436, median 2 424 606, max 2 453 451, mean 2 424 385, sd 17 146 Hz. B2: min 2 597 326, median 2 628 778, max 2 658 783, mean 2 628 536, sd 17 856 Hz.
**Change-based gate G-chg (R = Δobs/Δf; thirds, whole span).** A: +60.5, +62.0, +61.0, +61.2 (fails; carrier 15× too small for the Ka downlink). B1: −1.006, −1.078, −1.161, −1.078. B2: −0.927, −0.993, −1.069, −0.993. B1w: −1.0866, −1.0866, −1.0859, −1.0863 (the carrier ρ·f_ref = 29.49 GHz is 7.9% below the identified 32.03 GHz; 1.0863 = 32.036/29.49). **B2w: −1.0006, −1.0006, −0.9999, −1.0002: PASS with the sign flipped**, the only predictor that meets G-chg. B1 passes the 5% window in one third only (receive-time geometry).
**Descriptive (offset removed; sign flipped).** sd of obs + f − mean: A 9040 Hz; B1 684; B2 252.5; B1w 706; **B2w 2.64 Hz** (offset −2 510 174.27 Hz, as DAT8). B1w's sd (706 Hz) exceeds B2's (252 Hz) because the wrong carrier leaves a 7.9% scale error on a 30.6 kHz change (2.4 kHz peak) that the two-way geometry cannot cancel.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 DSS-25 range rate available for the window | **VERIFICATION, met** | 31 epochs; consistent with the geocentre to 2.4×10⁻⁵ and 0.20 km/s |
| C2 band IDs decoded | **VERIFICATION, met** | Ka/Ka, exciter S (DAT8 Phase A); the 209/15 turnaround is the label's receiver-side K, not a carrier ratio to f_ref (D3) |
| C4 (prompt, relative and corrected absolute) | **VERIFICATION, not met** for B1, B2 and the two-way variants | level comparison tests the bias of the observable (D1), not the predictor |
| G-chg (native) | **VERIFICATION, met for B2w only (sign flipped); G3 shared-input** | contaminating inputs: the Horizons Cassini ephemeris (may be fitted to DSN radiometric data of this class); the carrier 32.028 GHz from the prompt |
| Primary branch (ρ·f_ref = 29.49 GHz) | **VERIFICATION, not met** | scale 7.9% low (R = 1.086); f_ref is exciter-scale |
All rows are VERIFICATION (prompt id alias), outside the physics tallies; solar K was not used.

## 5. Direction
1. Replace the level gate by the change-based gate for every later Doppler comparison (GOM36 and the conjunction analysis): levels contain the DSN bias.
2. Take the two-way geometry (receive-time range rate plus the transmit-epoch range rate from a table reaching RTLT earlier) as the predictor; the receive-time form leaves 252 Hz of diurnal structure.
3. The carrier is the Ka downlink 32.028 GHz = (14/15) × 34.316 GHz; the prompt's ρ·f_ref route (29.49 GHz) mixes an exciter-scale frequency with a receiver constant and should not be used.
4. The offset −2 510 174 Hz and the sign flip belong to GOM_DAT9 (TDF ramp and Fbias).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.


## 7. ERRATUM 2026-10-11 (interpolation) and corrected numbers
Same cause as GOM_DAT8 §8: linear interpolation of the range-rate tables (worst 6–20 Hz in the observable). Repeated with 4-point cubic interpolation, nothing else changed (`gom_dat7_reset_1b.cpp`, output `gom_dat7_reset_1b_results.txt`; VC1–VC4 met).
**Corrected change-based gate.** B2w (two-way, 32.028 GHz): **R = −0.9999 in all three thirds and the whole span** (previously −1.0006, −1.0006, −0.9999, −1.0002); flipped sign PASS, unchanged outcome. B1w (209/15·f_ref): **R = −1.0859 in every window** (previously −1.0866, −1.0866, −1.0859, −1.0863); fails, unchanged. The receive-time predictors (A, B1, B2) fail as before (R values unchanged to 4 digits).
**Corrected descriptive residuals (offset removed, sign flipped).** B2w: **sd 0.57 Hz** (previously 2.64), offset −2 510 170.48 Hz; B1w 703.8 Hz (previously 705.8); B2 252.7 Hz (252.5); B1 683.6 Hz (683.9); A 9039.9 Hz (unchanged). The level gates (G-rel, G-abs, C4) are unchanged in outcome: median |f|/median |obs| and the level residuals move in the 5th digit. The statement of §5 (2) that the receive-time form leaves 252 Hz while the two-way average leaves 2.6 Hz becomes 252 Hz against 0.57 Hz.
