# GOM_DAT6 (DSS-25 type-12 predicted Doppler geometry, solar K fixed) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom_dat6_reset_1.cpp` exists. Class: VERIFICATION (data and geometry) plus a COMPUTED prediction; no SDT survival or exclusion is claimed.

## 0. Inputs read and exposure
Read: `GOM_DAT6/PROMPT.md` in full (including the 2026-10-05 gate correction and id alias: the claim ids GOM33-C* are those of GOM_DAT6); the GOM_DAT8, GOM36 and GOM37 records of this programme (the identification of the two-way Ka predictor, the offset and the interpolation erratum). Not read: archived GOM_DAT6/GOM33 results. Exposure: from GOM_DAT8 the level medians on day 157 (|obs| 50 244 Hz; the prompt-literal predictor 170 409 Hz, ratio 3.39) and the identification F = 32.028 GHz with a constant offset of −2.51 MHz; these are the known answers the instrument is expected to reproduce.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | gate | The original C4 gate (factor 10) passes a 3.39 ratio; the corrected gate (5%, or the documented turnaround factor exactly) fails it. Both are evaluated and reported: the gate as corrected decides. |
| D2 | construction | The observable is `[B/|B|]·[count rate − |Fb·K + B|]` (the label): a count rate minus a receiver-chain bias term. Its **level** therefore carries a constant that is not a geometric quantity; only the **change** of the observable is a geometric Doppler. A level comparison with a geometric prediction can fail at 3.4× or 51× without any scale error in the geometry. The registered primary comparison is therefore the change-based one (regression of the observable on the prediction: slope and correlation over the window), with the level comparison reported as the prompt gives it. |
| D3 | input | C1: the Cassini state is obtained from the Horizons DSS-25 table (15-minute and 5-minute); the SPK of the volume is not used. C2: the DSS-25 geodetic position (E-lon 243.1246368°, lat 35.337612°, alt 0.959628 km) is read from the Horizons site record in the table header (a measured input with the Horizons site database as provenance; not a published DSN station table such as the TRK-2-25 volume). The provenance is stated, not upgraded. |
| D4 | scope | C5 is reported separately: the solar-K delay-rate term for K = 1476.35 m (frozen, never fitted). |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Window.** Day 157, K252 ODF, type 12, valid, receive = transmit = 25 (7447 records expected).
**Predictors.** P_lit = −2·(ṙ_rx/c)·f_ref (f_ref = 2 116 648 992 Hz, the ODF reference; the prompt-literal first-pass form), with ṙ_rx the Horizons DSS-25 range rate by 4-point cubic interpolation of the 15-minute table; P_2w = (2/c)·F·ṙ_2w, F = 32.028 GHz, ṙ_2w = ½[ṙ(t) + ṙ(t − RTLT)], RTLT = 2·delta·AU/c (GOM_DAT8's identification; sign as found there).
**Validations.** V1: row count equals the label ROWS and time tags increase. V2: coverage of the Horizons table over the window and over t − RTLT. V3: cubic interpolation of the 15-minute table at the 5-minute epochs reproduces the 5-minute deldot to 10⁻⁷ relative (GOM37 V4). V4: the sign and magnitude of ṙ_rx cross-checked against delta(t): −(delta(t+Δ) − delta(t−Δ))/(2Δ) from the table against deldot to 10⁻³ (a known-answer consistency).
**Statistics.** Level: median |P|/median |obs| for P_lit and P_2w; the original gate (ratio in [0.1, 10]) and the corrected gate (|ratio − 1| ≤ 0.05). Change-based: ordinary-least-squares slope of obs on P_2w and Pearson correlation over the window (with the offset free), and the same for P_lit; the fitted offset reported. C5: Δf = 2F·dΔt/dt for K = 1476.35 m (centred difference ±150 s, GOM37 geometry): window mean and range.
**Decisions.** C1 met iff V2; C2 stated as MEASURED-INPUT with provenance; C3 COMPUTED; C4 as corrected (≤ 5% on the level) with the change-based slope reported beside it; C5 COMPUTED, K frozen; C6 met if no γ and no Bertotti residual is used.
**Expected landing (hand estimate before registering; this is the known answer from GOM_DAT8).** P_lit level ratio 3.39 (original gate met, corrected gate failed); P_2w level ratio about 51 (both gates failed: the level carries the −2.51 MHz bias); change-based slope of obs on P_2w equal to 1.000 within 10⁻³ with correlation above 0.999 and an offset near −2.51 MHz; slope for P_lit about 0.29 (the prompt-literal scale error); Δf window mean about +0.99 Hz.

## 3. Results (COMPUTED / VERIFICATION; instrument `gom_dat6_reset_1.cpp`, output `gom_dat6_reset_1_results.txt`; single pass, no amendment; validations met)
**Validations.** V1: 7447 rows = label ROWS, time tags increasing (met). V2: the Horizons table covers the window and the window minus the round-trip light time (met). V3: cubic interpolation of the 15-minute table at the 5-minute epochs, worst relative 8.65×10⁻⁹ (met). V4: d(delta)/dt against deldot, worst relative 2.0×10⁻⁵ (gate 10⁻³: met).
**C1 met** (Horizons DSS-25 table, dependency recorded). **C2** MEASURED-INPUT, provenance the Horizons site record (E-lon 243.1246368°, lat 35.337612°, alt 0.959628 km); not a published DSN station table, stated as such.
**Level (7447 records).** median |obs| = 50 244.3 Hz; median |P_lit| = 170 408.8 Hz (ratio **3.3916**); median |P_2w| = 2 560 414.8 Hz (ratio **50.96**). Original gate (ratio in [0.1, 10]): P_lit met, P_2w not met. **Corrected gate (|ratio − 1| ≤ 0.05): P_lit not met, P_2w not met.**
**Change-based.** obs on P_2w: **slope 0.99994, correlation 1.000000, offset −2 510 006.5 Hz.** obs on P_lit: slope −15.012, correlation −0.99963, offset −2 507 703.1 Hz.
**C5 (reported separately, K = 1476.35 m frozen, not fitted).** Δf = 2F dΔt/dt over the window: mean +0.9867 Hz, range 0.9837 to 0.9897 Hz.
Landing against the registered known answers: P_lit level ratio 3.39 and P_2w ≈ 51 (held); obs on P_2w slope 1.000 with correlation > 0.999 and offset near −2.51 MHz (held: 0.99994, 1.000000, −2.510 MHz); Δf mean +0.99 Hz (held). **Not held:** the P_lit change-based slope, which I registered as about 0.29; that figure is the level ratio of GOM37's procedure, not a slope. The slope is −15.012: P_lit uses the 2.1166 GHz reference where the counted frequency shift follows the 32.028 GHz downlink carrier (32.028/2.1166 = 15.13; the receive-only range rate in P_lit differs from the two-way one by the diurnal term, giving 15.01), with the sign opposite to the prompt's convention. My hand estimate was wrong in kind.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 ephemeris coverage | **VERIFICATION, met** | table spans the window and the round trip |
| C2 station coordinates | **MEASURED-INPUT** | Horizons site record; provenance stated |
| C3 classical two-way Doppler | **COMPUTED** | P_2w with F = 32.028 GHz reproduces the observable's change to slope 0.99994, correlation 1.000000 |
| C4 level gate, as corrected (≤ 5%) | **not met** (3.39 and 50.96) | the level of the observable contains a receiver-chain constant (−2.51 MHz, GOM_DAT8/GOM_DAT9); the 3.4× of the prompt-literal predictor is a carrier choice (2.1166 against 32.028 GHz) plus that constant, not a missing geometric factor |
| C5 solar-K Doppler term | **COMPUTED, K frozen** | +0.9867 Hz mean |
| C6 | **met** | no γ, no Bertotti residual |
Excluded from physics tallies (the prompt's alias note).

## 5. Direction
1. The corrected gate cannot be met by any geometric prediction at the level: the observable minus the prediction is a constant of the receiver chain. The gate that tests the geometry is the change-based one (slope and correlation), as GOM_DAT8 found; GOM_DAT9 owes the reconstruction of the constant from the ramp and bias records.
2. The 0.0165-Hz range of Δf over a 2-hour window against the 0.07–2.1 Hz segment noise (GOM37) confirms again that a single constant-reference window cannot test the solar term.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
