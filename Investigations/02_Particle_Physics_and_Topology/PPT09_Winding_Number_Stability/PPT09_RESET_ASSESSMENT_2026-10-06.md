# PPT09 — blank-slate assessment (2026-10-06)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1.

## 0. Inputs read before the pre-registration, and exposure
Read: `PPT09/PROMPT.md`; `PPT01/PROMPT.md` (supplier specification); `laws.hpp` (law_VI `winding`, `topology`, law_III, `measured`); the dependency graph (`graph_v2*.csv/json`: PPT09 is layer 0, reach 107; consumers FD02 and NP17; suppliers: none among the investigations; the prompt names PPT01, PPT05 (optional), Laws III, V, VI). Not read: the old `INVESTIGATION.md`, `PPT09_VERDICT.md`, `PPT09_KNOT_CLASSIFICATION.md`, `PPT09_TREFOIL_STABILITY_PROOF.md`, `ppt09_occlusion_integral.cpp`, `ppt09_reconnection_pathway.txt`, `README.md`.
Exposure: (i) `PROMPT.md` carries a banner "RETRACTED-FABRICATED → OPEN" and an audit-correction block naming the earlier outcome as "classification COMPUTED, stability OPEN"; (ii) `laws.hpp` lines 2240–2249 (canon, a permitted input) state outcomes of this investigation: a first-order energy integral giving W=2 equal to two W=1 and no determined barrier, lifetime or reconnection direction. Both were read before this registration. The registered tests below were written to test the prompt's claims, and the T2 conventions were fixed by the mass-conservation argument in §4, not chosen to reproduce the canon comment; the comparison with the archived record is made only after the run (§9).
Also known to the author from earlier drafts in this session: the PPT01 draft found that closure lengths depend on a rule not fixed by the budget. The PPT01 prompt fixes the closure by Compton self-consistency (R = ℏ/(m v_T), a = ℏ/(m v_P)); that is the only closure used here.

## 1. Prompt analysis
The prompt asks why W=2 is absent while W=1 and W=3 are present, with four phases (knot classification; occlusion integral; reconnection pathway; trefoil stability proof) and expected results "W=2 reconnects; W=3 eternally stable; barrier ≈ 0.1 GeV; absolute topological obstruction".

| # | Class | Observation |
|---|---|---|
| D1 | premise | "Topological protection" is a statement about smooth (isotopy) deformation. A medium that allows vortex lines to reconnect changes knot type by a crossing change or a smoothing. Whether a trefoil is protected is then a question about the energy of the reconnection event, not about the invariant. The prompt's Approach A (invariant), B (linking) and C (energy) are therefore not three proofs of one claim. |
| D2 | construction | Approach B: linking number is defined for two or more components. A trefoil has one component. The statement "cannot split into 2×(1,1) without violating linking number conservation" has content only for the products of a reconnection, which is what T3 enumerates. |
| D3 | gating | Phase 2 asks for E_conf = ∫P_eff dV over the vortex envelope and a ratio V_occ(1,2) ≥ 1.05 × 2V_occ(1,1). The scale at which (1,2) is compared with 2×(1,1) is not stated (equal ƛ, equal a, or equal total mass). With uniform P_eff the ratio reduces to a volume ratio and P_eff cancels. |
| D4 | gating | Phase 3 needs an energy for two sub-vortices after a reconnection: their interaction sign (EMC03) and the reconnection barrier (FLM10). The prompt's own pivot table says: upstream dependency missing ⇒ DEFER, cite the dependency. |
| D5 | premise | The prompt's W (poloidal loops per toroidal revolution; proton W=3) and the (p,q) partition used by the engine (v_P²/v_T² = q/p, proton 1.5) are not the same number for the proton. PPT01's prompt §3 derives v_P² = W v_T² with W = 3; §5 generalises to q/p. The engine's `topology::` block uses q/p. This investigation uses (p,q) and q/p throughout. |
| D6 | data | The prompt's references call R_p the "charge radius" and cite CODATA 2018; no datum enters this investigation. |

No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** PPT01 (closure geometry, taken from its prompt; the PPT01 outcome is an open supplier for the proton size, which does not enter the ratios tested here); Law VI (W+1 conjecture, not used); Law III (P_eff, cancels). **Dependents:** FD02, NP17 (graph); the engine comment at `laws.hpp:2240` cites this classification. Edge classes: PPT01 → PPT09 `required` for geometry; PPT05 → PPT09 `cross-check` (the prompt says optional).

## 3. Hypotheses, observables, ledger
H1 (Phase 1): for coprime (p,q), the Alexander polynomial Δ ≠ 1 iff min(p,q) ≥ 2. Observable: Δ computed by two independent routes; knot determinant |Δ(−1)|.
H2 (Phase 2): the envelope volume of (1,2) is at least 1.05 × twice that of (1,1), so separation lowers the P_eff-weighted envelope energy.
H3 (Phase 3/4): there is no finite sequence of reconnections taking the trefoil to 2×(1,1) (absolute protection), while (1,2) → 2×(1,1) is one event. Observable: number of reconnection events N_ev (oriented smoothing or crossing change at a crossing of the braid diagram) to reach the two-component unlink, with components, linking numbers and Δ of every intermediate state.
Parameter ledger: no measured input, no calibrated parameter. Constants from the engine: c, ℏ, m_e, m_p (conversions only). Controls: unknot, Hopf link, 2-unlink, figure-eight, cinquefoil.

## 4. Pre-registration (written before `ppt09_reset_1.cpp` exists)

**Instrument.** Laurent-polynomial arithmetic with integer coefficients; reduced Burau representation of the braid group B_p, (p−1)×(p−1) matrices over Z[t,t⁻¹]; Alexander polynomial of a braid closure Δ(β) = det(I − ψ(β)) / (1 + t + … + t^(p−1)), exact division; unit normalisation (shift to lowest exponent 0; sign so Δ(1) > 0, or the leading coefficient > 0 when Δ(1) = 0). Components from the permutation; linking numbers lk = ½ Σ (crossing signs between two components). Torus knot T(p,q) = closure of (σ_1…σ_{p−1})^q on p strands. Route 2 for Δ(T(p,q)): (t^{pq} − 1)(t − 1)/((t^p − 1)(t^q − 1)) by exact polynomial division.

**Validations (any not met ⇒ G0, the object is not assessed).**
- V1: ψ(σ_i)ψ(σ_i⁻¹) = I exactly for p = 2, 3, 4, all i; braid relations σ_iσ_{i+1}σ_i = σ_{i+1}σ_iσ_{i+1} and σ_iσ_j = σ_jσ_i (|i−j| ≥ 2) exactly for p = 4.
- V2: known answers: closure of σ_1 on 2 strands (unknot): Δ = 1; σ_1²: Δ = 1 − t (Hopf), 2 components, lk = 1; σ_1³: 1 − t + t² (trefoil); σ_1⁵: 1 − t + t² − t³ + t⁴; σ_1⁰ on 2 strands (2-unlink): Δ = 0, lk = 0; (σ_1σ_2⁻¹)² on 3 strands: 1 − 3t + t² (figure-eight); determinants 3, 5, 5 for trefoil, cinquefoil, figure-eight.
- V3: invariance: Δ unchanged (after normalisation) under conjugation by σ_i and under the Markov stabilisation β → βσ_p^{±1} (p → p+1) for the control braids.

**Tests.**
- T1 (COMPUTED, Phase 1): for (p,q) ∈ {(1,1), (1,2), (2,3), (2,5), (3,4)} and all coprime (p,q) with 1 ≤ p ≤ 4, 1 ≤ q ≤ 9: Δ by both routes, determinant, components, torus-diagram crossing count. Rejection criterion R1: H1 is rejected if any coprime pair in the range violates "Δ ≠ 1 iff min(p,q) ≥ 2", or if the two routes disagree. Standard knot-table values for the five named pairs: (2,3) 1 − t + t²; (2,5) 1 − t + t² − t³ + t⁴; (3,4) 1 − t + t³ − t⁵ + t⁶; (1,1), (1,2) 1. Non-coprime control: components = gcd(p,q) for (2,2), (2,4), (3,3), (3,6).
- T2 (COMPUTED, Phase 2): geometry from the PPT01 closure with the (p,q) partition: v_T = c√(p/(p+q)), v_P = c√(q/(p+q)), R = ℏ/(m v_T), a = ℏ/(m v_P) for mass m; envelope volume V = 2π²Ra². Three scale conventions for the comparison of (1,2) with 2×(1,1): S1 equal mass (equal ƛ); S2 mass conserved, m_(1,2) = 2 m_(1,1); S3 equal minor radius a. Primary: S2, because a reconnection conserves the total reorganisation cost (Law IV) and the decay product masses sum to the parent's. Rejection criterion R2: H2 is rejected if the S2 ratio V(1,2)/(2V(1,1)) < 0.95; classes: ≥ 1.05 (H2 supported), 0.95–1.05 (equal within 5%), < 0.95 (opposite sign). S1 and S3 are reported with the primary; look-elsewhere count 3. Ratios are independent of P_eff and ƛ; a numerical energy E = P_eff V is printed for the electron scale from `law_III::P_eff` only as the magnitude of the scale mismatch (report-only).
- T3 (COMPUTED, Phase 3 topology and Phase 4 Approach B): for the braid diagrams of T(2,1) ≅ T(1,2) (σ_1), T(2,3) (σ_1³), T(2,5) (σ_1⁵) and T(3,4) ((σ_1σ_2)⁴): every single oriented smoothing (delete one letter) and every single crossing change (invert one letter): resulting components, linking numbers, Δ. For the 2-strand family the closures of σ_1^n are classified completely (n = 0: 2-unlink; n = ±1: unknot; ±2: Hopf; ±3: trefoil; …), so N_ev (breadth-first over the two operations, target n = 0) is exact within the registered move set; for T(3,4) only the invariants are reported. Rejection criterion R3: H3 (absolute protection) is rejected if N_ev(trefoil → 2-unlink) is finite within the registered move set (the class "infinite" is populated: no sequence reaches n = 0 only if the move set cannot change n by 1 or 2, which is checked by the enumeration).
- T4 (statements, no instrument beyond T1–T3): Approach A holds as isotopy invariance (V3); Approach B is evaluated on the products of T3; Approach C requires an energy of the reconnection event: DEFERRED to FLM10 (reconnection barrier on the per-spation lattice) and EMC03 (interaction sign of two co-wound sub-vortices).

**Whole-range single pass.** T1 over all listed (p,q); T2 over the three conventions; T3 over the four braids and both operations.

**Amendment 1 (2026-10-06, after attempt 1, before any object result was computed).** Attempt 1 returned G0: V2 reported "MISMATCH" for the Hopf link and the figure-eight. The instrument's values were −1 + t and −1 + 3t − t², which equal the registered answers 1 − t and 1 − 3t + t² times −1. The Alexander polynomial is defined up to units ±t^k; the registered normalisation (Δ(1) > 0, or leading coefficient > 0 when Δ(1) = 0) puts the two expected values in the forms −1 + t and −1 + 3t − t². The registered expected strings were written in a different unit from the registered normalisation; the instrument is consistent with the normalisation. Correction: the expected strings in V2 are the normal forms above. No threshold, tolerance or criterion is changed, and no result on the object (T1–T3) had been computed in attempt 1 (validations stop the run). Attempt 1 output is kept: `ppt09_reset_1_results_attempt1_G0.txt`.

## 5. Gradated outputs and triggers

| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1, V2 or V3 not met | repair the instrument |
| G1 | R2 met (S2 ratio < 0.95) or R3 met (finite N_ev) | name the premise (E = P_eff V_env; the isotopy reading of protection) and start the alternative routes in §6 |
| G2 | T4 Approach C and the Phase 3 energy curve deferred; stability spectrum open | FLM10 and EMC03 outcomes decide |
| G3 | consistent within tolerance, shared-input | not expected |
| G4 | T1 consistent with the knot-table values, independent origin (knot mathematics) | state that it tests the mathematics, not the (p,q) ↔ particle assignment |
| G5 | not available | — |

Expected landings (stated before the run): T1 G4; H2 G1 (the three conventions give volume ratios below 1 by hand-evaluation of the closed forms, written before computing the values: ratio of ƛ³-scaled volumes with ƛ_(1,2)/ƛ_(1,1) ≤ 1.15); H3 G1 (the trefoil reaches the 2-unlink in two events); Phase 3 energy G2.

## 6. Alternative outs
1. An energy functional from the per-spation lattice (FLM10) for the reconnection of two strands of one torus; barrier ΔE and a rate; rejection criterion registered there.
2. A circulation-weighted envelope (tube around the knot path, tube radius from the closure) instead of the solid torus; the ratio registered before computing.
3. The interaction sign of the two co-wound products (EMC03) to fix whether separation lowers or raises the energy.

## 7. Run record

- Date 2026-10-06. Instrument `ppt09_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; Laurent-polynomial arithmetic, reduced Burau representation; constants from `sdt::laws` only for the report-only scale line). Attempt 1: G0 (V2), output kept as `ppt09_reset_1_results_attempt1_G0.txt`; Amendment 1 (§4) corrected the unit of two registered expected strings. Attempt 2: all validations met; output `ppt09_reset_1_results.txt`. Single pass over the registered range.
- **Validations met.** V1: Burau inverses (p = 2–4), braid relations and far commutation (p = 4) hold exactly. V2: unknot Δ = 1; Hopf −1 + t (2 components, lk = 1, det 2); trefoil 1 − t + t² (det 3); cinquefoil 1 − t + t² − t³ + t⁴ (det 5); 2-unlink Δ = 0, lk = 0; figure-eight −1 + 3t − t² (det 5). V3: Δ unchanged under conjugation and Markov stabilisation for the three control braids.
- **T1 (COMPUTED, Phase 1).** (1,1) and (1,2): Δ = 1 (unknots; the torus diagram of (1,2) as T(2,1) has one crossing); (2,3): 1 − t + t² (det 3, 3 crossings); (2,5): 1 − t + t² − t³ + t⁴ (det 5); (3,4): 1 − t + t³ − t⁵ + t⁶ (det 3, 8 crossings). The Burau route and the closed formula agree on all 25 coprime pairs with 1 ≤ p ≤ 4, 1 ≤ q ≤ 9; Δ ≠ 1 iff min(p,q) ≥ 2 holds for all 25 (0 violations). The five named values equal the standard knot-table values. Non-coprime controls: components = gcd(p,q) for (2,2), (2,4), (3,3), (3,6). Rejection criterion R1 not met: H1 consistent.
- **T2 (COMPUTED, Phase 2).** Envelope V = 2π²Ra², R = ℓ/(v_T/c), a = ℓ/(v_P/c): (1,1) at ℓ = 1: R = a = 1.41421 (R/a = 1, a horn torus), V = 55.8309; (1,2) at ℓ = 1: R = 1.73205, a = 1.22474, R/a = 1.41421, V = 51.2840. V(1,2)/(2V(1,1)): S1 (equal mass) 0.45928; S2 (mass conserved, ℓ_2 = ℓ_1/2, primary) 0.05741; S3 (equal minor radius, ℓ_2 = 1.15470 ℓ_1) 0.70711. Rejection criterion R2 met: the primary ratio is below 0.95 (class "opposite sign"); the other two conventions are below 0.95 as well; none is within 1e-6 of 1. Look-elsewhere count 3. The expectation in §5 that ℓ_(1,2)/ℓ_(1,1) ≤ 1.15 was imprecise for S3 (the value is √(4/3) = 1.1547); the sign of the result is unaffected. Report-only: with `law_III::P_eff` = 5.2273e31 Pa the electron-scale envelope V(1,1) = 3.2149e-36 m³ gives P_eff V = 1.6805e-4 J = 1.049e9 MeV, about 2e9 times m_ec².
- **T3 (COMPUTED, Phase 3 topology and Phase 4 Approach B).** Single events on the braid diagrams (oriented smoothing / crossing change): T(2,1) ≅ T(1,2), σ_1: smoothing → 2 components, Δ = 0, lk = 0 (the 2-unlink); crossing change → unknot. T(2,3): smoothing → Hopf link (Δ = −1 + t, lk = 1); crossing change → unknot. T(2,5): smoothing → 2-component link (Δ = −1 + t − t² + t³, lk = 2); crossing change → trefoil Δ. T(3,4): smoothing → 2 components (Δ = −1 + t − t⁴ + t⁵, lk = 2); crossing change → Δ = 1 − t + t² − t³ + t⁴ (the cinquefoil polynomial). Two-strand family, move set {smoothing: n → n − sgn n; crossing change: n → n − 2 sgn n}, target n = 0: N_ev = 1, 1, 2, 2, 3, 3, 4, 4, 5 for n = 1…9; the move set is consistent with the Δ and component counts of the actual words (n = 1…6). W=2 (n = 1): N_ev = 1; trefoil (n = 3): N_ev = 2; T(2,5) (n = 5): N_ev = 3. Rejection criterion R3 met: N_ev(trefoil → 2-unlink) is finite.
  Argument, not run: a crossing change is a smoothing followed by the inverse smoothing with the opposite sign, so counted in single reconnections (each changes n by ±1 in this family) the number of events is |n| (W=2: 1; trefoil: 3; cinquefoil: 5). The conclusion (R3) holds under either count.
- **T4.** Approach A: Δ is an isotopy invariant (V3); a reconnection is not an isotopy. Approach B: the trefoil has one component and no linking number; its single smoothing is a Hopf link with lk = 1, which an isotopy cannot separate. Approach C: DEFERRED.

## 8. Outcome and direction

**Grades.** Phase 1 classification: **G4** (consistent with the knot-table values, independent origin: knot mathematics; it tests the mathematics, not the (p,q) ↔ particle assignment). H2 (envelope-volume preference): **G1**, excluded on the pre-registered primary form and on both secondary conventions. The premise that produced it: the functional E = P_eff × V_env and the scale at which (1,2) is compared with 2×(1,1) are not given by the prompt; P_eff (`law_III::P_eff`, `laws.hpp:461`) is the electropause pressure of the proton lock and gives 1e9 MeV at the electron-scale envelope. No downgrade by agreement is made. H3 (absolute topological protection of the trefoil): **G1**, excluded: a finite sequence of reconnection events takes the trefoil to 2×W=1 (2 events in the registered move set, 3 single reconnections). Stability spectrum, barrier, lifetime, reconnection direction (Phase 3 energy, Approach C): **G2**, open, decided by FLM10 (reconnection barrier) and EMC03 (interaction sign of the co-wound products).

**What changes for the dependents.**
- FD02 and NP17 take no "W=2 forbidden by topology" and no "trefoil eternally stable by topology" from PPT09: both are premises about the energy of a reconnection event, open. The topological content that stands is the classification (T1) and the event counts (T3).
- The `laws.hpp` `winding` comment about this classification is consistent with T1; this record does not edit canon.
- PPT01 → PPT09 edge confirmed `required` (geometry); PPT05 → PPT09 `cross-check`.

**Direction for the next layer of theory.**
1. A reconnection-energy functional with the topological event count N as an input (W=2: 1, trefoil: 3, cinquefoil: 5): register a hypothesis that barrier height grows with N and test it on FLM10 once it exists. An equal-energy result for W=2 and 2×W=1 under any mass-conserving convention holds by construction of the mass sum (CONSTRUCTION) and discriminates nothing.
2. A local pressure P(r) at the electron scale (or a mass-based functional from Law IV) in place of the proton-scale P_eff, before any envelope-volume energy is used.
3. The (p,q) ↔ particle assignment: knot type alone does not select the particles; the closure mass scale (PPT01/PPT03) and the reconnection barrier do.

## 9. Comparison with the archived record
Deferred: the archived PPT09 files are opened in the end-of-programme comparison pass, after the layer sequence is complete, so that no archived finding enters a later pre-registration.
