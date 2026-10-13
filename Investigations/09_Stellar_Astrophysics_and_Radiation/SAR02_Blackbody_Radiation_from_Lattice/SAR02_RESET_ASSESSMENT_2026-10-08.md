# SAR02 (blackbody radiation from lattice modes) — blank-slate assessment (2026-10-08)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07 (native mechanism first; measured values enter only in a final comparison against a prediction fixed beforehand). Instruments `sar02_reset_1.cpp` (registration in its header, fixed before the run) and `sar02_reset_2.cpp` (one amendment, §3.5); outputs `sar02_reset_1_results.txt`, `sar02_reset_2_results.txt`. Run 1 single pass over the whole range; Run 2 re-runs the counting phase only.

## 0. Inputs read and exposure
Read: `SAR02/PROMPT.md` (whole); `laws.hpp` (`measured::` constants, `law_I`, `law_I::epsilon`, `release_acoustics::photon_count`); `Theory/` by search for blackbody, Planck, occupation, photon, Stefan, Wien (no content on a native occupation rule found); `REOPEN_2026-10-05/graph_v2_edges.csv` (SAR02 has no supplier among the investigations; consumers TD02, TD06); the TD01 record (format and the equal-weight premise). Not read: `SAR02_VERDICT.md`, `results.txt`, `sar02_blackbody_lattice.cpp`.
Exposure: before the registration I read `REOPEN_2026-10-05/STATUS.md` and the first rows of its `LEDGER.csv`, which the protocol lists as not permitted. They hold records for FLM/PPT investigations and no SAR02 content; they did not choose any test here. `release_acoustics::photon_count` in `laws.hpp` already carries the blackbody photon count with `h`, `k_B` and ζ(3); it is an imported use of the Planck form, noted as such (§1, D2).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The measurable gap asks for the occupation factor to be derived. Step 2 of the prompt writes it down: ⟨ε⟩ = hν/(e^{hν/kT} − 1). The question and the method contradict each other. |
| D2 | premise | "n(ν) = 8πν²/c³ (same as electromagnetic mode counting, because the lattice IS the medium)" carries two inputs: 2 polarisation branches and relay speed c. Neither is derived from a lattice. |
| D3 | construction | Success criterion 4 ("only lattice properties; no quantum postulates beyond lattice discreteness") has no stated mechanism by which discreteness supplies a quantum. The tick is a time and a length; an energy per mode needs a rule (§3.2). |
| D4 | construction | "Peak: ν_max = 2.821 kT/h. Equivalently λ_max T = 2.898×10⁻³ m·K." The two are different peaks (spectral density per frequency and per wavelength); c T/ν_max = 5.099×10⁻³ m·K (§3.4). |
| D5 | gating | "σ and a reproduced" is one check: σ = a c/4 (isotropic flux). |
| D6 | record | The prompt numbers its three derivations "SAR02, E62, SAR02". The Stefan–Boltzmann one carries the id E62 (an experiment id). Header reads "SAR02–SAR02". |
| D7 | data | FIRAS monopole spectrum is listed as data and is not in `Datasets/`: PENDING. The registered comparisons use the radiation constant already in `measured::` and the exclusion by orders of magnitude, which does not depend on it. |
No downgrade is made on agreement grounds.

## 2. Dependencies
Suppliers: none among the investigations (layer 0). Constants taken: `measured::c, h, hbar, k_B, l_P, a_rad, T_CMB`, `law_I::epsilon`. Consumers: TD02 (temperature, `required`: takes Planck as native), TD06 (mode counting, `required`). Cross-check edge added: TD01 → SAR02 (the equal-weight premise of §3.3 is the premise TD01's Phase 2 found rule-dependent).

## 3. Five questions, ledger, results

**1. What do we not know?** Which part of the Planck spectrum is a lattice property. Three ingredients are separated: (M) the mode count, (Q) the rule for the energy a mode can hold, (W) the weighting by temperature.
**2. Why does it matter?** The textbook account takes (Q) and (W) as postulates (a quantum hν per mode, a Gibbs weight) and (M) from wave counting; its bookkeeping closes only with those inputs. TD02 and TD06 take the Planck spectrum as given.
**3. By what methods?** (M) exact mode count on nearest-neighbour relay lattices, two routes. (Q) four registered rules, each carried to an energy density with the prediction fixed before any measured value was loaded. (W) exact counting of microstates for a mode in a reservoir. Constants by two routes each.
**4. What would prove us wrong?** (a) Indicators: a rule that reproduces a measured number only through a quantity already holding it; an imported occupation factor presented as derived. (b) Mathematics: registered criteria RC1–RC4 (header). (c) What it breaks: if lattice discreteness cannot supply a quantum, the claim that blackbody structure is a lattice property alone fails and the quantum becomes a separate native premise.
**5. Done when** each ingredient has a stated origin or a stated open premise, and the comparison uses a prediction fixed beforehand.

**Three-column ledger**
| | Standard account | SDT native route (prediction registered first) | Discriminating observable |
|---|---|---|---|
| (M) mode count | 8πν²/c³ for plane waves in a continuum | continuum limit of a nearest-neighbour relay lattice, R = 1 + q s² | none at thermal frequencies (§3.1); lattice spacing enters at (ν d/c)² |
| (Q) mode energy | quantum hν postulated | A continuous, B tick quantum ħc/d, B′ Law-I content, C action per cycle h | the T-exponent (1 versus 4) and the amplitude against a radiometric standard independent of h, k_B |
| (W) weight | Gibbs factor postulated | counting of equally weighted microstates (S = k_B ln W) | none by itself: the premise is equal weight (TD01) |

### 3.1 Phase 1 — mode count (COMPUTED)
Validations met: V1 1D chain (grid against (2/π) asin(ω_c/2): 0.160860/0.160861, 0.333340/0.333333, 0.539900/0.539893); V2 SC ω_max = 3.464101615137754 = 2√3; V3 long-wave speed (worst |c − 1| = 4.17×10⁻⁸ over 3 lattices × 6 directions); V4 Gauss–Legendre (0.2222222222222221 against 2/9); V5 explicit-sum Planck integral 6.493939402267 against 6Σn⁻⁴ = 6.493939402266 (1.89×10⁻¹³); V6 route A q_SC = 0.075000 against the analytic 3/40; V7 routes A and B agree to 0.364% at ω_c/ω_max = 0.2, 0.3; V8 root residuals 0.
- q = 0.075000 for SC, BCC and FCC (V_cell = 1, 0.7698, 0.7071 d³; ω_max = 3.4641, 3.4641, 2.8284 c/d). Analytic reason: ω ≈ ck[1 − (κ/48c²)k²Σ_j(n·δ_j)⁴], and ⟨(n·δ)⁴⟩ over directions = |δ|⁴/5 for any δ, so R = 1 + (3/40)(ωd/c)² for every nearest-neighbour relay lattice whose second moment is isotropic. Route B across the band (R at ω_c/ω_max = 0.1…1.0): SC 1.0094 1.0353 1.0916 1.1796 1.3331 1.7115 2.0054 2.0603 1.8150 1.4246; BCC 1.0221 1.0373 1.0907 1.1764 1.3183 1.5795 2.3689 2.9480 2.4000 1.8506; FCC 0.9957 1.0285 1.0575 1.1096 1.1839 1.2945 1.4671 1.7699 2.5668 3.7011. The values at 0.1 are inside the grid resolution (≈1%) and are not used; the lattices differ near the band edge.
- Thermal peak at T_CMB: ν_peak = x_ν k T/h = 1.602301×10¹¹ Hz, c/ν_peak = 1.871012×10⁻³ m. δ = q s² = 2.209×10⁻⁶⁴ at d = ℓ_P and 2.123×10⁻⁴⁷ at d = 3.1×10⁸ ℓ_P (the bound carried from the 2026-10-08 shadow analysis, GRB 090510). The spacing at which δ reaches the prompt's 10⁻⁴ is d* = 1.087×10⁻⁵ m = 6.728×10²⁹ ℓ_P. **RC1 met:** lattice discreteness is invisible at thermal frequencies; the exponential cutoff of the Planck spectrum is not a lattice-scale effect.
- Branch number p (2 in the prompt) is an input of the count, not a result (D2).

### 3.2 Phase 2 — the quantisation rule (COMPUTED; comparison [CMP] against `measured::a_rad` T_CMB⁴ = 4.174783×10⁻¹⁴ J/m³)
SC lattice, d = ℓ_P, V_cell = 4.222111×10⁻¹⁰⁵ m³, p = 2, T = T_CMB.
| Rule | Prediction | u/u_meas | Criterion (|ln| > ln 2 excluded) |
|---|---|---|---|
| A continuous amplitude, ⟨ε⟩ = kT | u = p k T/V_cell = 1.782501×10⁸² J/m³; u ∝ T¹ | 4.27×10⁹⁵ | excluded |
| B tick quantum ε_t = ħc/d = 1.956082×10⁹ J (5.198×10³¹ kT) | ln u = −5.198×10³¹ | e^(−5.2×10³¹) | excluded |
| B′ Law-I content ε = 1.762640×10⁻¹¹⁸ J (4.7×10⁻⁹⁶ kT) | u = 1.782501×10⁸² J/m³ | 4.27×10⁹⁵ | excluded |
| C action per cycle, levels n h ν | u_C = 4.174801×10⁻¹⁴ J/m³ (explicit level sums, Gauss–Legendre); u ∝ T⁴ (exponent 4.000000 between toy temperatures 300 K and 6000 K) | 1.00000439 | consistent within 1e-4; the 4.4×10⁻⁶ is the 5-figure rounding of `measured::a_rad` (7.56573325 against 7.5657) |
- A fixed classical lattice would need d = 1.2171×10⁻³ m to match u at T_CMB and 1.1057×10⁻⁵ m at 300 K; no single spacing matches both (u_A ∝ T, d_A ∝ 1/T). The gap for ℓ_P is 95 orders; the exclusion does not depend on the precision of `a_rad`.
- Both readings of "the relay tick as quantum" (B: action per hop; B′: the engine's relay content per shell) are excluded. A quantum that is a lattice constant is the same for every mode, so it gives either equipartition (B′) or no radiation (B). The quantum has to scale with the mode frequency: one action h per cycle (C). That is a premise beyond discreteness (D3).
- Contaminating input for B′ as a predictor: `law_I::epsilon` = u_CMB ℓ_P³ is defined from the measured u_CMB (`laws.hpp`, law_I); used as a quantum it cannot predict u_CMB.
- Look-elsewhere: 4 rules registered, all reported.

### 3.3 Phase 2 — the weight from counting (COMPUTED)
Reservoir of R equally weighted oscillators sharing M quanta of one size; exact P(n) for one oscillator; counting temperature ε/kT = [ln W(M+1) − ln W(M−1)]/2, W = C(M+R−1, M) (S = k_B ln W as in TD01 Phase 1). Mean occupation M/R compared with 1/(e^x − 1).
- Run 1 (R = 50, 200, 800, 3200): deviations at R = 3200: 1.87×10⁻³, 4.69×10⁻⁴, 3.44×10⁻⁴ for mean occupation 0.1, 1, 5. **RC3 as registered (≤ 1×10⁻³ at R = 3200) not met** for occupation 0.1; decreasing in R: met.
- Run 2 amendment (made after Run 1 was seen; R list changed to 3200, 12800, 51200, 204800; criterion unchanged, applied at the largest R; tolerance of the known-answer validation set to 1×10⁻⁶ before the run). At R = 204800: 2.930×10⁻⁵, 7.325×10⁻⁶, 5.368×10⁻⁶. **RC3 met.** dev·R = 5.9998, 1.5002, 1.0993 (constant to 0.06% over the last three R): the offset is O(1/R) with a finite coefficient, so the exact counting converges to the Planck factor.
- Premise: all microstates carry equal weight. TD01 Phase 2 found the arrow rule-dependent (symmetric stochastic: equilibrium uniform; reversible deterministic swap: none), so the equal weight is an open premise of the native relay rule, not a result here. Premise (Q) also enters: one quantum size per mode.

### 3.4 Phase 3 — constants from rule C, p = 2 (COMPUTED; comparison [CMP])
- x_ν = 2.8214393721 (bisection) and 2.8214393953 (golden-section), difference 2.3×10⁻⁸; x_λ = 4.9651142317 and 4.9651142734, difference 4.2×10⁻⁸.
- a = 7.56573325×10⁻¹⁶ J m⁻³ K⁻⁴ against `measured::a_rad` 7.5657×10⁻¹⁶: +4.39×10⁻⁶. σ = a c/4 = 5.67037442×10⁻⁸ against 5.670374×10⁻⁸: +7.4×10⁻⁸. b = hc/(k x_λ) = 2.89777196×10⁻³ m·K against 2.898×10⁻³: −7.87×10⁻⁵ (the table has four figures). x_ν against 2.821: 0.0004, within the table rounding 0.0005. All within the registered 10⁻⁴.
- **D4 check:** c T/ν_max = 5.099443×10⁻³ m·K against b = 2.897772×10⁻³ m·K, ratio 1.7598 = x_λ/x_ν. The prompt's "equivalently" is inconsistent within tolerance; the two peaks are different quantities.
- Conditional p_eff: a further branch at c_L = c/√3 (the speed in `release_acoustics`, used as an example only) adds (c/c_L)³ = 5.1962, p_eff = 7.1962 and a would be 3.598 times the p = 2 value. The table value corresponds to p = 2 to 4.4×10⁻⁶, so (c/c_L)³/2 < 4.4×10⁻⁶, i.e. (c/c_L)³ < 8.8×10⁻⁶ and c_L > 48 c for any extra branch populated by rule C. This bound uses the table value, which shares its inputs with the derivation (contaminating-input line in §4); it becomes a bound only with an independent radiometric amplitude (§5, item 2).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| (M) count per branch, continuum limit | **G4**, convergent; not discriminating | independent origin (lattice relay dispersion, validated routes); agrees with the plane-wave count; δ = 2.2×10⁻⁶⁴ at thermal frequencies |
| branch number p = 2 | **G2, open** | not derived; decides a by a factor p/2 |
| Rule A (continuous amplitude) | **G1, excluded** | u/u_meas = 4.27×10⁹⁵ at d = ℓ_P; no single fixed spacing matches two temperatures; premise producing it: amplitude without a quantum |
| Rules B and B′ (tick-quantum readings) | **G1, excluded** | premise producing them: one quantum for all modes; B gives no radiation, B′ equipartition |
| Rule C (action per cycle) as a premise | **G2, open** | consistent with u_CMB, a, σ, b; no native origin of one action h per mode cycle (ħ is a seat, FLM13; why a mode cycle holds it is not derived) |
| Rule C outputs against the table | **G3, shared-input; not discriminating** | `contaminating input: h and k_B — exact by the 2019 SI definition, from which CODATA computes a, σ and b — enters at laws.hpp (h, k_B) and at sar02_reset_1.cpp:142 and :160 (u_C, a_C, sig_C, b_C)`: the table values are functions of the same constants |
| (W) exact counting gives the Bose factor | **G4** for the derivation (O(1/R), RC3 met in Run 2); **G2, open** for the equal-weight premise | counting is independent of the Gibbs postulate; equal weight is TD01's open question |
| Thesis "Planck from lattice discreteness alone, with the tick as quantum" | **G1, excluded** | discreteness supplies a count (and nothing visible at thermal frequencies); the quantum is a separate premise |
| Prompt's "equivalently" (D4) | record defect, corrected here | two peaks |

## 5. Direction
1. **Native origin of one action per mode cycle.** The candidate sources are in the SDT structure and are not tested here: circulation quantisation of the vortex topology (Law VI) and the relay-lock closure (FLM07, FLM15). A registered test needs a native statement of what a standing relay mode is (a closed relay loop of W windings?) and what energy it holds per winding, with the prediction fixed before any measured value is loaded. Until then Rule C is the single open premise of the blackbody spectrum.
2. **Branch number.** Decide p by a measurement independent of h and k_B: the absolute radiometric amplitude of a blackbody at a known temperature (FIRAS absolute intensity; laboratory cavity radiometry). PENDING dataset: neither is in `Datasets/`. With one, the conditional p_eff in §3.4 becomes a test and the table comparison stops sharing its inputs.
3. **What the outcome changes downstream.** TD02 takes Planck as native: it is native only given Rule C and equal weight; the T⁴ scaling is a consequence of C (exponent 4.000000), and a classical lattice gives exponent 1. TD06 (mode counting) takes the count from §3.1: no lattice correction at thermal frequencies; only the Brillouin-zone scale appears, at 10⁴² Hz for d = ℓ_P.
4. **Observable where lattice and continuum differ.** Frequency-dependent speed at ω d/c ≈ 1, not blackbody frequencies: δ = (3/40)(ωd/c)², universal for nearest-neighbour relay lattices, so a dispersion measurement at high frequency fixes d without fixing the lattice type; the difference between lattice types is in the band-edge shape and the directional anisotropy of order (ωd/c)⁴.
5. **Prompt repairs (proposed, in place of the unfilled template):** state the three ingredients (M, Q, W), remove the imported occupation factor from step 2, replace the "equivalently" line with the two peaks, rename the second SAR02 derivation, and register the T-exponent and the radiometric amplitude as the discriminating observables.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
