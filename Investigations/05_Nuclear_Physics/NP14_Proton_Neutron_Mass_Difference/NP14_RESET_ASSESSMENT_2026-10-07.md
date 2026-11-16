# NP14 — blank-slate assessment (2026-10-07)

> **WITHDRAWN AS AN ASSESSMENT — 2026-10-07, at Harvey's direction.** This record compares and does not investigate. Reasons: (1) the registered test set {1, ½, 3/5, 1/10} consists of electrostatic energy partitions (field energy outside a sphere; total and interior energy of a uniform ball). These are Standard-framework source models, not SDT quantities; the record's own direction item 1 says so, and they were used as the test set regardless. (2) The instrument starts from the measured Δm and the measured surplus (the β-decay Q-value) and scans fractions of αℏc/R_p for agreement (a census to see what fits, with 43 candidate fractions). A census measures how likely a numerical coincidence is; it does not derive anything, and it has no native mechanism to test. (3) The prompt's own framing (a "Coulomb self-energy", a "charged" proton) was taken as the hypothesis instead of being restated in native terms. No result below is claimed as evidence for or against a mechanism. Grade: none (withdrawn); the question is OPEN with no native mechanism specified. What remains as COMPUTED arithmetic only: E_w = αm_pc²/(W+1) = 1.711726 MeV; Δm c² = 1.293333 MeV; surplus 0.782334 MeV (MEASURED-INPUT differences of CODATA masses). A re-specification from the native quantities (mass as throughput reorganisation cost, Law IV; the internal W = 1 circulation of the neutron, NP17; exclusion volumes V_disp) is required before NP14 is run again; the measured Δm is to be loaded only in a final comparison against a prediction fixed beforehand by that mechanism. The text below is kept as written and is withdrawn. Superseded by `NP14_NATIVE_ASSESSMENT_2026-10-07.md`.


Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1.

## 0. Inputs read before the pre-registration, and exposure
Read: `NP14/PROMPT.md` (including its 2026-10-05 gating note) and `DATA_REQUIREMENTS.md`; `laws.hpp` (`measured` masses, α, ℏ, c; `law_III::R_p_lock`; the winding block); the graph (NP14: layer 0, reach 101; consumers in the nuclear chain). Not read: `NP14_VERDICT.md`, `RUN_LOG.md`, `np14_mass_difference.cpp`, `np14.exe`, `np14_results.txt`.
Exposure: (i) the gating note gives the earlier outcome as numbers (a composite m_e + surplus within −14.08% of Δm; the surplus alone −23.28%); (ii) the prompt states the ratio 1.293/1.71 = 0.756; (iii) before writing §4 the author noticed by hand that 3/4 = W/(W+1) lies within 1% of that ratio and that ½ lies within 10% of the surplus ratio. The registered physical set below was written from the source models named in the prompt's methodology (step 2, "fraction of E_em outside V_disp"), and 3/4 enters only as a member of the census, with the census size as its look-elsewhere count.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | The prompt's quantity "Coulomb self-energy αℏc/R_p" is the interaction energy scale of the hydrogenic coupling at the boundary radius, E_w = αℏc/R_p; "the fraction outside V_disp" depends on a source model that the prompt does not give. |
| D2 | premise | The prompt states the neutron model must follow NP17 (neutron = proton + internal electron); NP17 is not run here. The surplus s = m_n − m_p − m_e is a measured difference (the neutron β-decay Q-value) and is not derived by this prompt. |
| D3 | gating | The corrected gate is on the surplus alone (±20%). The original gate on Δm = m_n − m_p (±20%) is reported as well. |
| D4 | gating | Hypotheses B (circulation partition shift) and C (a stabilisation term from the wake) have no registered quantity in the prompt; they are not instrumented. |
| D5 | wording | The prompt and data file speak of a "charged" proton and a "charge" stabilisation; per the register these are read as the presence or absence of the ℓ = 1 wake. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** none among the investigations (graph); NP17 (neutron structure, deferred); the lock integer W+1 = 4 (FLM07, open supplier). **Dependents:** per graph (nuclear chain). Edges: NP17 → NP14 `required` for the surplus derivation (deferred); FLM07 → NP14 `cross-check` (R_p enters E_w).

## 3. Hypotheses, observable, ledger
H_A (prompt Hypothesis A): the mass difference is the energy of the proton's ℓ = 1 wake outside V_disp, a fraction ξ of E_w: Δm c² = ξ E_w, with ξ a geometric factor of a registered source model. Gate (corrected): s c² = ξ E_w within 20%; original gate: Δm c² = ξ E_w within 20%.
Observable: r_Δ = Δm c²/E_w, r_s = s c²/E_w. Data: engine masses m_p, m_n, m_e (MEASURED-INPUT, CODATA); E_w = αℏc/R_lock = α m_pc²/(W+1) (lock R_p), and αℏc/R_p with the measured R_p. Ledger: no calibrated parameter; ξ from a registered set (look-elsewhere count reported).

## 4. Pre-registration (written before `np14_reset_1.cpp` exists)

**Validations (not met ⇒ G0).**
- V1 (known answers): m_n − m_p = 1.29333 MeV and m_ec² = 0.510999 MeV to 1e-5 relative; αℏc = 1.43996 MeV fm to 1e-5; E_w computed two ways (αℏc/R_lock and α m_pc²/4) agree to 1e-12.
- V2 (census machinery): a planted fraction found in its band; for 20000 log-uniform numbers over 6 decades the sliding-band mean count equals N × (band width in log10)/(span) within 5%.

**Tests.**
- T1 (COMPUTED): E_w, r_Δ, r_s; the same with the measured R_p.
- T2 (COMPUTED, physical source models): P = {1 (point-source interaction energy), ½ (quadratic field energy outside a spherical boundary), 3/5 (uniform ball, total), 1/10 (uniform ball, interior)}; predictions ξE_w for Δm and for s and their relative deviations. Rejection criterion R1: H_A (Δm) rejected if no member of P is within 20% of Δm. Criterion R2: H_A (s) rejected if no member of P is within 20% of s. Look-elsewhere count 4; chance fraction: the fraction of band positions (sliding a band of the same relative width over log-uniform positions across the range of P) that contain at least one member.
- T3 (COMPUTED, census): all distinct fractions a/b with 1 ≤ a, b ≤ 8 (look-elsewhere count = their number): count within 20% (gate band) and within 1% of r_Δ and of r_s; chance baseline by sliding a band of the same width over the 5th–95th percentile of the candidate values; the members within 1%. Criterion R3: a ±20% agreement is non-discriminating if the count in the gate band is ≥ 3 or the chance fraction is > 0.05; a ±1% agreement is non-discriminating if the count in the ±1% band is ≥ 1 and the chance fraction exceeds 0.05.
- T4 (COMPUTED, named form): ξ = W/(W+1) = 3/4 (member of the census, flagged as selected after the exposure of §0): Δm c² = W α m_pc²/(W+1)² against the measured Δm c², residual in keV and in units of the engine mass uncertainty (the masses are CODATA constants with relative uncertainty ~1e-10; the residual is not a measurement error).
- T5: the surplus derivation from the neutron structure (NP17): DEFERRED. Hypotheses B and C: not instrumented (D4).

**Whole-range single pass.** Every member of each set is evaluated once.

## 5. Gradated outputs and triggers
| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1 or V2 not met | repair the instrument |
| G1 | R1 or R2 met | name the premise (the source model of the wake) and open the alternatives of §6 |
| G2 | R1/R2 not met but R3 non-discriminating, or the surplus derivation deferred | NP17 and a derivation of ξ decide |
| G3 | consistent within tolerance, shared-input | name the contaminating input |
| G4, G5 | not available | — |
Expected landing (stated with the exposure of §0): R1 met for Δm (no member of P within 20%), R2 not met for s (½ is within 10%), R3 non-discriminating; G2 overall.

## 6. Alternative outs
1. A derivation of ξ from the neutron structure of NP17 (the internal W = 1 circulation inside the W = 3 boundary): register ξ as a function of that geometry before comparing with s.
2. A second observable on the same rule: the A = 3 mirror pair (³H − ³He) or the ⁷Li–⁷Be pair, with the same E_w scaling and no per-pair adjustment.
3. The shift of the equilibrium R/a (Hypothesis B) as a registered quantity from the PPT01 closure with and without the ℓ = 1 wake constraint (EMC03 sign).

## 7. Run record

- Date 2026-10-07. Instrument `np14_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; constants from `sdt::laws`). Output `np14_reset_1_results.txt`. Single pass, no re-run, no amendment.
- **Validations met.** V1: m_n − m_p = 1.293333 MeV; m_ec² = 0.510999 MeV; αℏc = 1.43996 MeV fm; E_w = 1.71172556 MeV by both routes. V2: planted 3/7 found; sliding-band mean 587.251 against 587.076 expected (0.03%).
- **T1 (COMPUTED).** Δm c² = 1.293333 MeV; surplus s = Δm c² − m_ec² = 0.782334 MeV; E_w = αℏc/R_lock = 1.711726 MeV (measured R_p: 1.711391 MeV); r_Δ = 0.755572, r_s = 0.457044 (measured R_p: 0.755720, 0.457133).
- **T2 (COMPUTED, physical source models).** ξ = 1: 1.711726 MeV (+32.35% vs Δm, +118.80% vs s); ξ = ½: 0.855863 MeV (−33.83%, +9.40%); ξ = 3/5: 1.027035 MeV (−20.59%, +31.28%); ξ = 1/10: 0.171173 MeV (−86.77%, −78.12%). Within 20%: Δm: none; s: ξ = ½ (+9.40%); chance fraction for the surplus 0.1328 (at least one of four members lands in a 20% band at random positions about 13% of the time). R1 met (H_A for Δm rejected on the registered set); R2 not met (H_A for the surplus not rejected).
- **T3 (COMPUTED, census).** 43 distinct fractions a/b, 1 ≤ a, b ≤ 8. Target r_Δ: within 20%: 8 (chance mean 4.72, fraction 0.0788); within 1%: 1 (3/4, −0.74%; chance mean 0.216, fraction 0.216). Target r_s: within 20%: 4 (chance mean 4.72, fraction 0.7361); within 1%: 0 (chance fraction 1.0). R3 met in every case: agreement at ±20% is non-discriminating for both targets, and the single ±1% hit on Δm (3/4) is at chance (fraction 0.216).
- **T4 (COMPUTED).** ξ = W/(W+1) = 3/4 (selected after the exposure): Δm c² = Wαm_pc²/(W+1)² = 1.283794 MeV against 1.293333 MeV; residual −9.538 keV (−0.738%); the engine masses are known to about 1e-10, so the residual is not a measurement error.
- **T5.** Surplus derivation from the neutron structure (NP17): DEFERRED. Hypotheses B and C: not instrumented.
- Registration defects found: none.

## 8. Outcome and direction

**Grades.** H_A for Δm (prompt's original gate): **G1**, excluded on the registered source models (no member of {1, ½, 3/5, 1/10} within 20%; 3/5 misses by −20.59%). H_A for the surplus (corrected gate): **G2**, open: ξ = ½ lies within the 20% gate (+9.40%), but one of four registered members landing in a 20% band has a chance fraction of 0.13, no derivation connects the surplus to the exterior wake energy, and the surplus is a measured difference (the neutron β-decay Q-value) that the prompt does not derive. The numerical coincidence ξ = 3/4 = W/(W+1) on Δm (−0.74%, residual 9.5 keV) is one of 43 census members and sits at chance (fraction 0.22); it carries a residual outside the mass uncertainty and was selected after the exposure of §0. No downgrade by agreement is made.

**What changes for the dependents.** The nuclear chain takes no derived neutron–proton mass difference from NP14: Δm is a measured input (MEASURED-INPUT, `measured::m_n`, `m_p`); the surplus relation to the ℓ = 1 wake energy is a hypothesis with one registered model within the gate and no derivation. Edges: NP17 → NP14 `required` (deferred); FLM07 → NP14 `cross-check`.

**Direction for the next layer of theory.**
1. A native expression of the "wake energy outside V_disp" (the occlusion-pressure deficit of the Law III kernel integrated outside the boundary R_p), registered before any comparison; the quadratic field-energy fraction ½ used in T2 is an imported source model, not an SDT quantity.
2. The surplus from NP17's neutron structure (the internal W = 1 circulation inside the W = 3 boundary): register ξ as a function of that geometry first.
3. A second observable on the same rule with no per-pair adjustment: the mirror pairs ³H–³He and ⁷Li–⁷Be, with E_w scaled by the mirror geometry.
4. Hypothesis B (the shift of the equilibrium R/a without the ℓ = 1 wake) as a registered PPT01-closure calculation once EMC03 fixes the wake sign.

## 9. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
