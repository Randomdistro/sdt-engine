# GOM44 — Registered endpoint formula on Earth flybys, with equal-depth controls

**Author:** J. C. Harvey, Melbourne. **Registered:** 2026-10-16, before any endpoint value was computed.
**Status:** PRE-REGISTERED. **Canon edits:** none. **Upstream:** `GOM43/PROMPT_DISPLACEMENT_SLINGSHOT.md` (position-angle endpoint formula, `PENDING` because the equal-radius heliocentric vectors were missing); `Datasets/DATA_REGISTER_2026-10-16.md` (the vectors, measured Δv∞ values, tracking times).

## Disclosure
The measured Δv∞ values (Anderson et al. 2008; Hoffmann & Budnik 2026) were read before this registration. The endpoint values of the formula were not computed before it. Every rule below is fixed before the tool runs; none is adjusted afterwards. A rule that needs retuning partway is itself the finding.

## 1. Question
Does the formula already registered for GOM43,

Δv∞ = v∞ K_SDT [ (D/R_☉,in)² cosψ_in − (D/R_☉,out)² cosψ_out ],

reproduce the measured Earth-flyby Δv∞ — including the flybys whose entry and exit sit at the same relative pressure depth, for which the bracket is near zero and the formula predicts no anomaly?

## 2. Definitions (fixed)
- K_SDT = 2.9992003355950517×10⁻⁶ (GOM43 RUN_LOG line 195; burden ratio B⊕/B☉). Not refitted.
- D = 1 au = 1.495 978 707×10¹¹ m (`measured::AU`).
- Endpoint j: the instant at which the geocentric spacecraft distance equals R_ref, inbound (j = in) and outbound (j = out).
- R_☉,j: heliocentric distance of the spacecraft at endpoint j.
- ρ̂_j: unit vector Earth → spacecraft at endpoint j. t̂_j: unit vector Sun → Earth at the same instant. cosψ_j = ρ̂_j · t̂_j.
- Bracket B = (D/R_☉,in)² cosψ_in − (D/R_☉,out)² cosψ_out. Pressure depth at the endpoint is the solar term (D/R_☉,j)² times the geometric projection cosψ_j; the Earth term cancels at equal geocentric radius.
- v∞: inbound osculating hyperbolic excess speed from the Horizons state at 12 h before closest approach (same rule for every flyby).
- P = v∞ K_SDT B, the prediction, in mm/s.
- **R_ref = 50 000 km, primary, single pass.** R_ref = 20 000 km and 100 000 km are reported as sensitivity only and are never used to select.
- Sensitivity on the R_☉ definition: Earth's heliocentric distance in place of the spacecraft's. Reported only.

## 3. Data (all cached; see the register)
Geocentric and heliocentric ICRF state vectors from JPL Horizons (10-minute step, ±30 h), one table pair per flyby. Measured Δv∞ and σ: Anderson 2008 Table I (six flybys); Rosetta III 0.004 ± 0.044 (ASTG II); Juno 0 ± 0.8; MESSENGER 0.02 ± 0.01; the census of Hoffmann & Budnik 2026 for the rest. Where a null flyby has no published σ, the tolerance is 0.5 mm/s (Anderson's stated detectability scale, "less than 1 mm/s").

## 4. Classes (assigned by rule, not by inspection)
- **A (anomalous):** |Δv∞,obs| ≥ 3σ_obs.
- **N (null):** |Δv∞,obs| ≤ 2σ_obs, or ≤ 0.5 mm/s when σ is unpublished.
- **E (equal-depth control):** the lowest tercile of |B| over all flybys computed at R_ref = 50 000 km (ties broken by smaller |B|).
- Flybys with no published Δv∞ (value "?" in the census) are computed and listed, with no class A/N membership and no gate.

## 5. Gates (all registered; each can fail)
1. **G1 instrument.** (a) A synthetic trajectory symmetric about the Earth–Sun line gives B = 0 within 10⁻¹². (b) A synthetic trajectory with a known closed-form B reproduces it within 10⁻⁹. (c) At every endpoint |r_geo| = R_ref within 1 m. (d) Earth's heliocentric distance at every flyby lies in 0.983–1.017 au. (e) For the six Table I flybys the Horizons asymptote geometry reproduces Table I as stated in the register (V1–V2, V15).
2. **G2 anomalous class.** Every A member: |P − Δv∞,obs| ≤ 2σ_obs.
3. **G3 null class.** Every N member: |P| ≤ 2σ_obs (or 0.5 mm/s).
4. **G4 equal-depth control.** Every E member that is also in A fails the formula (the formula predicts no anomaly where an anomaly is measured). The formula passes G4 only if no E member is in A and every E member satisfies |P| ≤ 2σ_obs (or 0.5 mm/s).
5. **G5 rank.** Spearman ρ(P, Δv∞,obs) ≥ 0.7 over all flybys with a published Δv∞, with the exact permutation p-value reported.

The formula is stated consistent within the registered tolerance only if G2–G5 are all met. Any unmet gate is reported as inconsistent within the stated tolerance for that gate, with the numbers. Classification of the formula remains `PENDING` regardless of outcome; passing a gate on shared geometry is not independent evidence by itself.

## 6. Rejection classes populated
A is populated (Galileo I, NEAR, Rosetta I at minimum); N is populated (Rosetta II, Rosetta III, Juno, MESSENGER at minimum). A criterion cannot be met by every outcome: P ≈ 0 fails G2; P ≠ 0 fails G3.

## 7. Outputs
`flyby_depth_control.csv` (per flyby: endpoints, R_☉, cosψ, B, v∞, P, Δv∞,obs, σ, class), `RUN_LOG.md` (verbatim tool output), `GOM44_ASSESSMENT.md` (conclusions with the numbers).
