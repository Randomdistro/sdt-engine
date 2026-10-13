# NP35 F3 — spontaneous-fission hold-out, assessment (2026-10-05)

**Classification:** `NP35_F3_SF_HOLDOUT_PARTIAL__8_OF_9_MATCH_ONE_ORDER_NONE_EXCLUDED`<br>
**Pre-registration:** `NP35_SF_HOLDOUT_PRE_REGISTRATION.md` (predictions asserted equal to its table before any yield file was opened). Tool `np35_sf_holdout.py` (reuses `np35_flay_sim.py` functions unchanged); output `np35_sf_holdout_results.txt`. The one code edit after the first run was an ENDF header-field offset (the energy count is in L1), a parser fix; no gate or prediction changed.
**Data:** ENDF/B-VIII.0 SFY, MF 8 MT 454, MD5/SHA1 matching NNDC's published values; each system's yields sum to 2.00. **Canon edits:** none. **Fitted parameters:** 0.

| System | A_H_pre (F3) | obs A_H | ΔA_H | class | obs A_L | A_L_pre − A_L_obs |
|---|---|---|---|---|---|---|
| U-238 | 134 | 141.5 | −7.5 | MATCH | 95.3 | +8.7 |
| Cm-244 | 135 | 137.4 | −2.4 | MATCH | 104.5 | +4.5 |
| Cm-246 | 134 | 137.7 | −3.7 | MATCH | 104.6 | +7.4 |
| Cm-248 | 134 | 138.5 | −4.5 | MATCH | 105.4 | +8.6 |
| Cf-250 | 135 | 141.4 | −6.4 | MATCH | 106.7 | +8.3 |
| Cf-252 | 134 | 142.2 | −8.2 | ORDER | 107.1 | +10.9 |
| Es-253 | 135 | 142.3 | −7.3 | MATCH | 106.3 | +11.7 |
| Fm-254 | 135 | 138.6 | −3.6 | MATCH | 110.0 | +9.0 |
| Fm-256 | 135 | 137.1 | −2.1 | MATCH | 113.6 | +7.4 |

## Gates as registered
- **H1 (all nine MATCH): not met** — 8 MATCH, 1 ORDER (Cf-252, |ΔA_H| = 8.2 against the < 8 threshold). None EXCLUDED (threshold 20).
- **H2 (observed A_H in [128, 148], none < 120 or > 160): met.**
- **H3 (|slope| of observed A_H vs A* < 0.25): met** — slope −0.022 (stationary heavy peak, as NP35 G4 reported for the neutron-induced eight).
- **H4 (A_L_pre − A_L_obs in [1, 8] for each): not met** — values 4.5–11.7; six of nine exceed 8; none negative or above 12 (the EXCLUDED conditions).

## Assessment
1. F3's heavy-remnant location (N = 82, A_H_pre 134–135) holds on a second fission mode and on nine fissioners from U-238 to Fm-256 to within 2–8 mass units, with a stationary heavy peak, no retuning. The pre-registered strict reading (all nine MATCH) is missed by 0.2 mass units on Cf-252; it is recorded as ORDER, not widened.
2. The sign is uniform: observed heavy centroids sit 2–8 above the predicted pre-neutron remnant, i.e. the heavy fragment carries a few nucleons beyond the N = 82 remnant, consistent with a jacket, but observed A_H is post-neutron and A_H_pre pre-neutron, so the size of the offset conflates the jacket and emission; no ν is predicted (NP35 limitation unchanged).
3. H4 (light residue) fails on the SF set more than on the neutron-induced eight (there only Th-232 failed). The light-side residue grows with A* (4.5 at Cm-244 to 11.7 at Es-253), a trend to explain rather than a gate to relax.
4. Limits: ENDF SFY for Es-253 and Fm-254/256 are England–Rider extrapolations; Cf-252 and U-238 are the best-constrained, and Cf-252 is the one at ORDER. Z_H is parent composition (NP36 excluded the seating route); target-exposed to the heavy-peak location.
5. Combined with NP35's neutron-induced result (G2–G4), F3 is now CONDITIONAL across 17 systems on A_H, with the light residue (G5/H4) the unresolved column.

## Not done
Pu-240/242(sf), Cm-242/245 and others in the F12 list are not in this sublibrary (nine materials only). Bernas ²³⁸U+p fragment table (NP37) is still owed.
