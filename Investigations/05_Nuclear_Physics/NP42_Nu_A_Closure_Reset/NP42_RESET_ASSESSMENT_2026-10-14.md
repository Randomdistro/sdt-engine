# NP42 (ν(A) closure reset), Round 7 — assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `np42_reset_2.py` exists. Follows the rewritten prompt of 2026-10-12 (Round 7: H7, the ν floor ends one triton pair before a belt's closure, N_b = closure − 2; held-out system scanned once; a second form for U-233).

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (section 1 the round-6 outcome as stated there; section 2 the origin assessment; section 3 Round 7; the kept rounds 1–6 specification: definition of Z_f = A Z_p/A_p, N = A − Z_f; the three systems; the shell canon); `Datasets/nuclear/neutron_multiplicity/` README and the three CSV files' column headers. Not read: `np42_round6.py`, `np37_*`, the round result files, `NP42_ASSESSMENT.md`, `NP42_RESET_ASSESSMENT_2026-10-10.md` body. **Exposure:** the prompt states the round-6 findings (U-235 break 80.50, Δχ² ≤ 4 set 79.00–81.25; U-233 79.75, set 78.75–80.50; 82 excluded in both; U-233 χ²/dof 24.8). They are used as the validation target of my own implementation, and the U-235/U-233 runs are a **consistency check, not a test** (the prompt says so).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | form | The hockey-stick form is not defined in the prompt text (the round-6 instrument defines it). Registered here, own definition: ν(N) = a for N ≤ N*, ν = a + b (N − N*) for N > N* (continuous; parameters a, b, N*), weighted least squares with weights 1/σ², N* scanned over 60…100 in steps of 0.25, a and b profiled in closed form. The break is the end of the floor. |
| D2 | domain | The sawtooth has a rise on the light group; the floor lies at the minimum near A = 126–132 (N ≈ 77–81). The fit domain is the heavy side from the floor: **N ≥ 74** (A ≥ 121 for the A/Z used), with the sensitivity of N* to the lower edge reported for N ≥ 70, 74, 78. |
| D3 | held-out | Cf-252 (sf), Z_p = 98, A_p = 252, BJ1988 digitized curve (`CURVE`, with digitizing errors; the stated statistical errors are large near the ends, e.g. 0.85 at A = 73). Scanned once, no tuning. |
| D4 | second form | For U-233 (χ²/dof 24.8 for the hockey stick per the prompt): two alternatives registered before they are computed: **Q** (quadratic hinge) ν = a for N ≤ N*, a + b (N − N*)² above; **S** (soft hinge) ν = a + b w ln(1 + exp((N − N*)/w)), width w scanned 0.5…6 (a fourth parameter). A form is "better" if it lowers χ²/dof of the hockey stick by at least 3 units with the extra parameter counted (S) or by 3 (Q, same parameter count). |
| D5 | other belts | H7's prediction for the other belts (N* ≈ 48, 124) is not testable with these systems (fragment N rarely below 56 or above 100); recorded as not testable, not as failed. |
| D6 | the null | A shifted-closure comparison: H7 predicts N_b = 80 = 82 − 2; the alternative N_b = 82 (closure itself) is the earlier hypothesis. Reported: the profile Δχ² at 80 and at 82 in each system. |
No downgrade is made on agreement grounds.

## 2. Registered gates and quantities (fixed before the run)
**Validations.** V1: a planted break (synthetic data on the U-233 mass grid with its errors, a = 0.5, b = 0.25, N* = 80, noise from the stated errors, seed fixed) is recovered to within 0.5 in N*. V2: the complementary-fragment Z balance of the assumed Z_f (mean of Z_f(A) + Z_f(A_p − A − ν) − Z_p over the table) within 0.5 charge units is not computed (no pairing data); replaced by the check that Z_f = A Z_p/A_p gives N = 82 at A = 134.2 (U-235 parent), reported. V3 (consistency): my implementation on U-235 gives N* within 1.0 of the prompt's 80.50 and on U-233 within 1.0 of 79.75 (the form is mine, so ±1 is allowed).
**Held-out gates (Cf-252, scanned once).** G7a: the best-fit N* lies within ±2 of 80, i.e. in [78, 82]. G7b: N = 80 lies inside the Δχ² ≤ 4 set. Reported, not gated (power-limited by the digitized errors): Δχ²(82), the full Δχ² ≤ 4 interval, χ²/dof.
**Second form.** χ²/dof of H (hockey stick), Q and S on U-233; the "better" criterion of D4. Q and S are also computed on U-235 and Cf-252 for the record.
**Cascade bands.** G4 if G7a and G7b are met on Cf-252 and V3 holds; G3 if G7a only; G1 if the best break is outside [78, 82] on Cf-252 (the 80 reading does not hold on the held-out system).
**Expected landing (hand estimate before registering).** The break near 80 in Cf-252 within [78, 82] with a wide interval (digitizing errors); 82 not excluded at Δχ² > 4 (power); Q or S improves U-233 modestly (the χ²/dof of 24.8 is dominated by the floor's shape).

## 3. Results (COMPUTED; `np42_reset_2.py`, output `np42_reset_2_results.txt`; single pass, no amendment)
**Validations.** V1 (planted break N* = 80 on the U-233 grid, 38 points) recovered **80.00**: met. V2: N = 82 at A = 134.39 for the U-235 parent. V3 (consistency with round 6): U-235 best N* = 79.75 (prompt 80.50; Δχ² ≤ 4 set [79.00, 80.50]; χ²/dof 1.82; Δχ²(80) = 0.07, Δχ²(82) = 48.3); U-233 best N* = 79.00 (prompt 79.75; set [79.00, 79.00]; χ²/dof 15.5 against the prompt's 24.8; Δχ²(80) = 107, Δχ²(82) = 1141): both within the allowed 1.0: met. The lower domain edge (N ≥ 70, 74, 78) moves the best break by at most 0.5 (U-235 79.50–79.75, U-233 78.75–79.25). **82 is excluded in both U systems; N = 80 is inside the U-235 set and 1 unit above the U-233 set.**
**Held-out Cf-252 (scanned once, 17 points with N ≥ 74, digitized errors).** Best N* = **64.00** (a = −0.880, b = 0.107, χ²/dof 2.75); the Δχ² ≤ 4 set is [60, 100]: **the whole scan range**; Δχ²(80) = Δχ²(82) = 0.00. **G7a not met** (best break outside [78, 82]); G7b met only vacuously (80 inside a set that is the whole range). The floor a is negative at the best fit, which is unphysical for a multiplicity; the registered form did not constrain a ≥ 0 and it is not changed after the fact. **The Cf-252 data cannot locate the break: they neither support nor exclude H7** (power: 17 points, errors up to 0.85). By the letter of the registered bands this is **G1 for the held-out test** ("the 80 reading does not hold") but the finding is "uninformative".
**Second form (U-233).** χ²/dof: hockey stick 15.50; quadratic hinge Q 25.64 (N* 60); soft hinge S 16.84 (N* 79.00, w = 0.5, four parameters). Neither is better by the registered 3 units; the hockey stick is the best of the three forms on U-233 and the poor χ²/dof is not a hinge-shape problem of these families. On U-235: H 1.82, Q 2.70, S 1.94; on Cf-252: H 2.75, Q 2.83, S 2.20 (S best at N* = 79.50, w = 0.5, χ²/dof 2.20 — a four-parameter fit on 17 points, not read as support).
Landing: V1, V3 held; the Cf-252 interval was expected wide (held: the whole range); the best break was expected within [78, 82] (not held: 64); the second forms were expected to improve U-233 modestly (not held: neither does).

## 4. Grades
| Item | Grade |
|---|---|
| Consistency with round 6 (break near 80, 82 excluded) | **met in U-235 and U-233** (not a test: post-seen) |
| H7 on the held-out Cf-252 | **G7a not met by the letter; the data are uninformative (Δχ² ≤ 4 set = the scan range)** |
| Second form for U-233 | **no better form among Q and S** (H 15.5, Q 25.6, S 16.8) |
| H7 on other belts (N* ≈ 48, 124) | **not testable** with these systems (D5) |
| Label | **COMPUTED; held-out test inconclusive; G1 by registered letter, power-limited** |

## 5. Direction
1. A held-out test needs a system with enough points and tighter errors near N = 76–86: tabulated (not digitized) ν(A) for ²⁵²Cf(sf) or a second neutron-induced system, fetched with provenance.
2. The U-233 χ²/dof 15.5 is not a hinge-shape issue; the structure that the hockey stick misses is elsewhere in its floor region (not examined here).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
