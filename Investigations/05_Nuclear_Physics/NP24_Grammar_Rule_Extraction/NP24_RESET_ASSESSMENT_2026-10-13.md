# NP24 (grammar rule extraction: stability band, ionisation ladder) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `np24_reset_1.py` exists.

## 0. Inputs read and exposure
Read: `NP24/PROMPT.md` in full (the five questions; coordinate system of §①; data §②; candidate rules R1–R6, S1–S3, I1–I3 declared in §③; phases P0–P5; falsifiers F1–F6; the four-root sort; the 2026-10-05 correction: recount of 3558 ground-state rows and 3213 grammar-valid isotopes, 0 conservation failures, "these identities are an invertible map of (Z, N) and are not independent evidence"). Data read for format only: `Datasets/nuclear/AME2020_mass_excess.txt` (the file's own format description), `NUBASE2020.txt` (column table), `ionisation_energies.json` (keys Z, lists of eV). Not read: `NUBASE_GRAMMAR_SWEEP.txt`, `NUBASE_NULL_TEST.txt`, the technical reports (`TECHNICAL_REPORT*.md`), `np24_grammar_count_check.py`, `nubase2020.txt` of the folder.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | not evaluable | The residual ε = (BE_pred − BE_meas)/BE_meas is "from the κ-shadow model". No blind implementation of that model exists in this programme (the shadow-overlap sequencer is an earlier tool whose residuals are an earlier result). **P1 (residual map) and P2 (R1–R6, F1, F2, F6) are PENDING_MODEL**, not run. |
| D2 | construction | The map (Z, A) → (u, v) with v = Z − 2, u = 5Z − 2A − 2 is an invertible relabeling. A "band in (u, v)" (S1) restates a range of A per element; it can be non-trivial only as a rule that predicts the band from v with few parameters. Registered as such (below). The grammar identities (A = 4 + 2n_d + 3n_t, Z = 2 + n_d + n_t) cannot fail: IDENTITY rows. |
| D3 | S3 | The decay-channel contours are computed from AME2020 mass excesses: Q_β⁻(Z, A) = ME(Z, A) − ME(Z+1, A), Q_EC(Z, A) = ME(Z, A) − ME(Z−1, A) (keV). A nuclide is inside the single-step band when Q_β⁻ ≤ 0 and Q_EC ≤ 0 with both neighbours measured (a mass excess marked "#" is an estimate and is not used). This band is built from masses alone, independent of the list of stable nuclei, so F3 and F4 are not circular. |
| D4 | I-block | The ionisation ladder: z = IE/13.59844 eV and k = 1/√z. I1 (hydrogenic null): for the last electron (stage s = Z) z = Z²; deviation from Z² is reported (relativistic and screening terms are not modelled). I3 (grammar coupling) is tested as the prompt states: a ladder feature correlates with the nuclear (n_d, n_t) of the stable isotope **and beats the atomic-only null I2 out of sample**. Registered operationalisation: feature r_Z = ln IE₁(Z) − ½[ln IE₁(Z−1) + ln IE₁(Z+1)] (a Z-only second difference, interior elements with a stable isotope); nuclear variable f_t = n_t/(n_d + n_t) of the most abundant stable isotope (abundance from the NUBASE IS= field); fit r = b·f_t on even Z, evaluate R² on odd Z, and the reverse; null = 5000 permutations of f_t across elements; I3 passes iff both out-of-sample R² exceed the 95th percentile of the permuted R² and are positive. |
| D5 | contraband | The four-root sort applies to any rule that reproduces the semi-empirical mass formula: a winner "∝ (N − Z)²/A" is DEGENERATE-labelled (F6). Not reached here (P2 pending). |
No downgrade is made on agreement grounds.

## 2. Registered quantities and decisions (fixed before the run)
**P0.** Count ground-state rows in AME2020 and in NUBASE2020 (isomer index 0); grammar-valid (Z ≥ 3, n_d ≥ 0, n_t ≥ 0); conservation failures (expected 0, IDENTITY); the expected counts from the prompt's own correction: 3558 and 3213.
**P3.** For each element Z = 3 … 99: the A-range of stable nuclides (NUBASE `stbl`), the A-range of the Q-band (both Q ≤ 0, both neighbours measured), and the u-range of each. F3: the fraction of stable nuclei (with determinable Q) inside the Q-band ≥ 90%. F4: the number of rows whose stable-range edges coincide with the Q-band edges to within 1 u-unit (identical A, since u changes by 2 per unit A); reported as a count and distribution of edge offsets in A. S1 as a rule: the midpoint of the stable u-range regressed on v with a quadratic, fitted on even-Z rows and evaluated on odd-Z rows (and reverse), out-of-sample R². F3 passes at ≥ 90%; F4 passes at ≥ 90% of rows (the prompt: "band edges match the contours within 1 u-unit").
**P4.** I1 deviations for the last electron for all Z with the full ladder; the I3 test as in D4.
**P1, P2, P5:** PENDING_MODEL (D1); the rules ledger lists S-block and I-block only.
**Expected landing (hand estimate before registering).** P0: 3558 and 3213, no conservation failure. P3: every stable nuclide satisfies Q_β⁻ ≤ 0 and Q_EC ≤ 0 (that is what stable means; a few decay-suppressed exceptions are possible), so F3 holds near 100%; F4: the Q-band is wider than the stable range in most rows (many Q ≤ 0 nuclides are α, p or n unstable or just long-lived), so most rows do not coincide within one A; the S1 midpoint rule has a high R² (u_mid is smooth in v). P4: z_last/Z² close to 1 with a few-% rise at large Z; I3 fails (no out-of-sample signal), the expected outcome the prompt itself names.

## 3. Attempt 1 and Amendment 1 (unregistered data condition; registered before attempt 2)
**Attempt 1 (kept: `np24_reset_1_attempt1_empty_ladder_crash.txt`).** P0 and P3 ran and printed (below, unchanged in attempt 2); the run stopped in P4 with an `IndexError`: `ionisation_energies.json` has elements with an empty list (no measured ionisation energy), which my loader did not anticipate. Amendment 1: elements with an empty list are skipped for IE₁ (they cannot enter the I3 feature) and the number of such elements is reported. Registered quantities and gates unchanged.
**Attempt 2 (COMPUTED / VERIFICATION; `np24_reset_1.py`, output `np24_reset_1_results.txt`).** One element (Z = 85, astatine) has an empty list among 104; the others have lists.
**P0 (IDENTITY / VERIFICATION).** AME2020: 3558 ground-state rows; NUBASE2020: 3558 ground-state rows; 253 stable. Grammar-valid (Z ≥ 3, n_d ≥ 0, n_t ≥ 0): **3213** in both; conservation failures **0** (the identities cannot fail). The prompt's counts (3558, 3213) reproduce.
**P3, F3 met.** Stable nuclides with Z ≥ 3: 249; Q determinable (measured neighbours): 246; inside the single-step band (Q_β⁻ ≤ 0 and Q_EC ≤ 0): **245 (99.6%)**. The one outside: ¹²³Te (Q_EC = +51.9 keV, Q_β⁻ = −1228 keV), a nuclide the evaluation lists as stable although the EC channel is open (decay not observed). This is nearly a restatement of what "stable" means (D3 said so); F3 is met because the band is built from masses alone and the stable list was not used to build it.
**P3, F4 not met.** Of 78 elements with a stable range and a band, the stable-range edges coincide with the band edges (same A at both ends) in **62 (79.5%)**; below the 90% criterion. Offsets (stable min − band min, band max − stable max, in A): (0,0) 62; (0,2) 6; (2,0) 4; (1,0) 1; (0,4) 1; (4,0) 1; (3,0) 1; (2,−2) 1. In the 16 rows that do not coincide the band extends one to four mass units beyond the stable range at one end (the isotopes with Q ≤ 0 that are unstable by α, p, n or double-β channels or by a long half-life), plus one case where the band is narrower (offset −2).
**S1 as a rule (u_mid quadratic in v).** Fit on even Z, evaluated on odd Z: R² = 0.8485 (rms 2.26 u-units); reverse: R² = 0.9136 (rms 1.80). This restates the smoothness of the valley of stability in Z (D2): the mid-A of the valley is a smooth function of Z, expressed in the relabeled coordinates; it is not independent evidence for the grammar as a coordinate system.
**P4, I1.** Last-electron z/Z² for the 29 complete ladders: 1.0000 (H), 1.0004 (He), 1.0006 (Li), 1.0030 (Si), 1.0033 (P), 1.0100 (Co), 1.0107 (Ni), 1.0115 (Cu): the hydrogenic null holds to 1.2% over Z = 1…29, rising with Z as the relativistic correction (Zα)² would (not modelled; the Cu value (Zα)² = 4.5×10⁻³ is of the same order, not a fit).
**P4, I3 does not beat I2.** 78 elements with a stable isotope and an IE₁ on both neighbours; feature r_Z (the Z-only second difference of ln IE₁) against f_t = n_t/(n_d + n_t) of the most abundant stable isotope. Fit on even Z, test on odd Z: R² = −0.758 (permutation null 95th percentile −0.521); fit on odd Z, test on even Z: R² = −1.381 (null 95th percentile −0.773). Both out-of-sample R² are negative and **below** the null 95th percentile: **no grammar coupling in the ladder (the cross-scale claim fails; F5)**. The prompt names this as the expected outcome.
**P1, P2 (R1–R6, F1, F2, F6) and P5: PENDING_MODEL** (no blind κ-shadow model).
Landing against the hand estimate: P0 3558 and 3213 (held), F3 near 100% (held), S1 high R² (held), I1 near 1 with a rise (held), I3 fails (held). Not held: **F4**: I estimated that most rows would not coincide; 79.5% do (the criterion at 90% is still not met).

## 4. Grades
| Item | Grade |
|---|---|
| P0 recount (3558, 3213, 0 failures) | **IDENTITY / VERIFICATION, met** |
| F3 stable nuclei inside the mass-derived Q band | **met (99.6%)**, near-tautological by definition |
| F4 band edges equal the contours (within 1 u-unit) | **not met (79.5% of 78 rows, criterion 90%)** |
| S1 band as a rule | **R² 0.85–0.91 out of sample; restates the valley's smoothness** (shared-input: invertible map of (Z, N)) |
| I1 hydrogenic null | **holds to 1.2% for Z ≤ 29** |
| I3 grammar coupling beats the atomic-only null | **NO (F5): the cross-scale claim fails; NP24 is nuclear-only** |
| P1, P2, P5 (residual rules) | **PENDING_MODEL** |

## 5. Direction
1. The residual-rule half (R1–R6) needs a blind implementation of the shadow-overlap model; until then F1, F2, F6 and the rules ledger are not evaluable.
2. F4's 20% of rows that differ are the rows with additional Q ≤ 0 isotopes beyond the stable range; a ledger of those nuclides by decay channel would say which channels bound the band (a descriptive follow-up using NUBASE decay modes).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
