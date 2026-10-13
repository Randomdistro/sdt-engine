# GOM39 (local k and the solar K definition) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom39_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM39/PROMPT.md` in full (including the 2026-10-05 audit correction); the GOM25, GOM26 and GOM36 records of this programme (the epoch variation of the instantaneous v²R/c², the orbital invariant 1476.351 m with a = 1.000189 AU, the SCE1 geometry); the local Earth and Cassini heliocentric vector tables for day 157. Not read: `GOM39_ASSESSMENT.md`, `RUN_LOG.md`, `gom39_local_k_definition.py`. Exposure: from GOM25/26 the Earth's instantaneous v²R/c² varies by 1.2% over the year and equals the invariant only with the factor (2 − R/a).
**Notation.** Harvey's ruling of 2026-10-09: R/k² is written Ѻ (Om). The prompt's K is that quantity. Earlier records of this programme (GOM23–GOM37) wrote ϟ for it and are not renamed; this record writes K (the prompt's symbol) and Ѻ where the quantity R/k² is meant.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | C1–C3 (the notation ledger, the identity r/k(r)² = K, the chord integral) are identities and calculus (the audit correction: IDENTITY). Validation A cannot fail by construction; Validation B is a quadrature check. |
| D2 | premise | Step 3 defines k = c/v_orb(R) "at a stated main-sequence radius" and takes v = |v| from the Earth state vectors. For the main sequence of a body on an ellipse, v_orb(R) in the speed law v(r) = (c/k)√(R/r) is the speed of the **circular** orbit at radius R (the law is v ∝ r^(−1/2)). The instantaneous speed at the radius R equals the circular speed times √(2 − R/a). The literal procedure therefore returns K_inst = Ѻ(2 − R/a), not Ѻ. Both are computed: the literal (R1) and the corrected reading (R2) with the factor (2 − R/a). |
| D3 | gating | The audit correction asks for a gate of the SCE1 K against an independently derived K. Registered: K_R2 = K_inst/(2 − R/a) with a from the one-year pairwise estimator of GOM26 (a = 1.496262×10¹¹ m) against the GOM26 invariant 1476.351 m, tolerance 4×10⁻⁴ (the year-to-year systematic of GOM26). The two share the same ephemeris family (DE441 kinematics): a continuity check, as the prompt itself says (C6 non-claim), not independent evidence. The SCE1 window alone (2.5 hours, R almost constant) cannot determine the invariant; it determines only K_inst. |
| D4 | gating | C5 asks that the local k at the Earth, impact-parameter and Cassini radii are pairwise distinct: k(r) = √(r/K) is strictly increasing in r, so distinctness is the statement that the three radii differ (arithmetic). |
| D5 | record | The status "DEFINED" for the Doppler–K path is administrative: the definition is closed by this record; the empirical status stays as GOM36/37 recorded (UNADJUDICATED_BY_SENSITIVITY). |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Validation A.** A synthetic main sequence R = 1.496×10¹¹ m, v = 29 780 m/s: k = c/v, K = R/k²; for r = 10⁹ … 10¹³ m (nine values) v(r) = (c/k)√(R/r), k(r) = c/v(r), K_r = r/k(r)²; gate max relative error < 10⁻¹².
**Validation B.** The impact parameter b = 45.17 R_sun (the GOM36 value), the chord from s₁ = −√(r₁² − b²) to s₂ = +√(r₂² − b²) with r₁ = 1.0148 AU (Earth) and r₂ = 7.37 AU (Cassini): Δt_num = (2/c)∫ z dl with z = K/r, by composite Simpson in l (2×10⁶ intervals) with K = 1476.35 m, against Δt_exact = (2K/c)[ln(s₂ + r₂) − ln(s₁ + r₁)]; gate relative < 10⁻⁶. Far-zone asymptotic (2K/c) ln(4 r₁ r₂/b²) against the exact value for b = 0.01 r₁ (gate < 10⁻³ relative) and for the SCE1 b (reported).
**SCE1 main sequence.** From the 31 five-minute Earth@Sun state vectors of day 157: R = |r|, v = |v|, k = c/v, K = R/k² (R1, literal): median k, median K, CV(K); R2: K_R2 = K/(2 − R/a) with a = 1.496262×10¹¹ m (GOM26); gate |K_R2 median/1476.351 − 1| < 4×10⁻⁴. K is never fitted to Doppler or delay.
**Local-k ledger.** k(r) = √(r/K) at the Earth's R, the impact parameter b (from the Earth and Cassini vectors at the middle sample) and Cassini's R, with K = 1476.351 m (primary, R2) and with the literal K_inst median (sensitivity); pairwise distinct.
**Outcome form.** C1–C3 IDENTITY / calculus; C4 COMPUTED with the D2 finding; C5 arithmetic; C6 administrative. No physics grade beyond COMPUTED.
**Expected landing (hand estimate before registering).** K_inst ≈ 1455.6 m (R = 1.0148 AU, v = 29.36 km/s), k ≈ 1.0×10⁴ (R/K = 1.03×10⁸, k = √ of that ≈ 10 130 for R; c/v = 10 211); (2 − R/a) = 0.9854; K_R2 ≈ 1476.4 m, within 4×10⁻⁴ of 1476.351; k(r): about 10 130 (Earth), 4 610 (b), 27 300 (Cassini); Validation B passes at 10⁻⁹ or better.

## 3. Results (COMPUTED; instrument `gom39_reset_1.cpp`, output `gom39_reset_1_results.txt`; single pass, no amendment; validations met)
**Validation A (IDENTITY).** Synthetic R = 1.496×10¹¹ m, v = 29 780 m/s: k = 10 066.906, K = 1476.1809 m; r/k(r)² over r = 10⁹ … 10¹³ m: worst relative 2.2×10⁻¹⁶ (gate 10⁻¹²: met).
**Validation B (calculus).** Chord at the SCE1 geometry (b = 45.17 R_sun, r₁ = 1.0148 AU, r₂ = 7.3726 AU): numerical Simpson 6.410042003×10⁻⁵ s against exact 6.410042003×10⁻⁵ s, relative 4.0×10⁻¹⁴ (gate 10⁻⁶: met). Far-zone asymptotic (2K/c)·ln(4r₁r₂/b²): for b = 0.01 r₁ relative 2.0×10⁻⁶ (gate 10⁻³: met); at the SCE1 b relative 1.7×10⁻³ (reported).
**SCE1 Earth main sequence (31 samples, day 157; R = 1.0148 AU, v = 29 355.45 m/s).**
- **R1 (literal, instantaneous speed):** median k = **10 212.50**; median K = **1455.637 m**; CV(K) = 1.8×10⁻⁷. Against the GOM26 invariant (1476.351 m): **−1.403×10⁻²**: the literal procedure misses by the eccentricity factor, as registered (D2).
- **R2 (circular-speed reading):** (2 − R/a) = 0.98537 with a = 1.496262×10¹¹ m (GOM26); median K = **1477.255 m**; CV = 4.1×10⁻⁶; against 1476.351 m: **+6.12×10⁻⁴**. **The registered gate (4×10⁻⁴) is not met.** The mismatch is 6×10⁻⁴: R2 mixes a 2002 state with a semi-major axis from 2025 (a change of 10⁻³ in a changes (2 − R/a) and K by 10⁻³, comparable to the miss), and GOM26 found the invariant to depend on the year at 3.5×10⁻⁴ (2024 against 2025). Against GOM26's 2024 value (1476.869 m) R2 is +2.6×10⁻⁴. The SCE1 window alone cannot determine a; its R-range is 0.01%.
**Local-k ledger** (K = 1476.351 m; the literal K_inst in brackets): Earth R = 1.0148 AU (218.2 R_sun): k = **10 140.6** [10 212.5], z = K/r = 9.725×10⁻⁹; impact parameter b = 0.2101 AU (45.17 R_sun): k = **4 613.8** [4 646.5], z = 4.698×10⁻⁸; Cassini R = 7.3726 AU (1585.4 R_sun): k = **27 332.5** [27 526.3], z = 1.339×10⁻⁹. Pairwise distinct (yes). The literal and the corrected readings differ by 0.7% in k.
The expected landing held for R1 (1455.6 m predicted, 1455.64 found), the local-k values and Validation B; for R2 the prediction was a pass within 4×10⁻⁴ (found 6.1×10⁻⁴).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 notation ledger (k ≠ K; K = R/k², written Ѻ in the 2026-10-09 convention) | **IDENTITY** | definitions |
| C2 Validation A | **IDENTITY, met** | 2.2×10⁻¹⁶ |
| C3 Validation B | **calculus, met** | 4×10⁻¹⁴; far-zone 2×10⁻⁶ |
| C4 SCE1 Earth → (k, K) COMPUTED, K never fitted | **COMPUTED; literal reading misses the invariant by 1.4% (D2); corrected reading +6.1×10⁻⁴: the registered 4×10⁻⁴ gate NOT MET** | continuity with GOM26 at the 10⁻³ level, epoch-mixed; shared ephemeris family (DE441), not independent |
| C5 pairwise distinct local k | **arithmetic, met** | k(r) = √(r/K) is increasing in r |
| C6 path status | **DEFINED (grammar)**; empirical status unchanged (UNADJUDICATED_BY_SENSITIVITY) | administrative |
Finding: the definition requires the circular-speed reading. v_orb(R) in v(r) = (c/k)√(R/r) is the circular speed at R; the instantaneous speed on an ellipse gives K(2 − R/a). The K carried by the framework to the Doppler/delay path must be the invariant; its epoch-to-epoch spread is at least 3.5×10⁻⁴ (GOM26) and 6×10⁻⁴ (this record).

## 5. Direction
1. Write the definition with the circular speed (or equivalently with the orbit's invariant μ/c²) and not the instantaneous state speed; where only an instantaneous state is available, K needs the orbit's a (D2).
2. Carry σ_K/K ≈ 6×10⁻⁴ (not 4×10⁻⁴) as the working systematic of the solar K until a perturbation-aware invariant is built (GOM26 direction 3).
3. GOM40a and GOM40b take the local-k/K definition from here.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
