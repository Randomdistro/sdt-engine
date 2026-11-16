# FLM15-cas (Casimir as relay exclusion) — blank-slate assessment (2026-10-07)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1. Id: the folder shares the id FLM15 with `FLM15_Influx_Phase_Resistance_Ratio` (`REOPEN_2026-10-05/ID_COLLISIONS.md`); this record uses FLM15-cas.

## 0. Inputs read before the registration, and exposure
Read: `FLM15_Casimir_as_Relay_Exclusion/PROMPT.md` in full (it carries its own dated pre-registration of 2026-10-03: route, validations V1–V3, Round 1 with its prediction, Round 2 conditional on Round 1, the candidates for a, labels); `laws.hpp` (`measured`: ℏ, c, k_B, h, T_CMB; `law_I`: u_CMB, P_conv). Not read: `FLM15_ASSESSMENT.md`, `RUN_LOG.md`, `flm15_casimir_counting.cpp`, `flm15_results.txt`. The graph does not separate the two FLM15 folders; the prompt names TD06 (mode counting), L3/L4 and SAR02 as existing corpus, none of which is a supplier run here.
Exposure: the prompt states its Round 1 prediction (exponent 0, magnitude u_CMB/3, about 1e-11 of the ideal Casimir pressure at 1 µm) and the Round 2 closed form ΔE/A = −aπ²ℏc/(360d³) before any instrument. These are registered predictions of the investigation, not outcomes. The author also derived the Poisson-sum form of the Round 2 difference by hand before writing this record (it reproduces −aπ²ℏc/(360d³)); it is used below as a second route.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | Round 1 prices each gap mode with the thermal free energy at T_CMB. The mode occupations are then Bose factors at 2.7 K; the Casimir force at 0.1–10 µm is not a thermal effect at that temperature, so a thermal-pricing route has no 1/d⁴ regime by construction (the prompt predicts this). |
| D2 | construction | Round 2 prices each mode a·ℏω with a independent of ω (scale-free). The d-dependent part of sum-minus-integral is then fixed by the mode counting and by dimensional analysis; the exponent 4 follows from the absence of a length scale, and the coefficient is a·π²ℏc/120. Only a is open. |
| D3 | data | The anchor (Mohideen and Roy 1998, about 1% rms with theory including finite conductivity, roughness, temperature) tests the corrected force, not the ideal formula; the prompt states this limit. The paper is a literature reference, not a dataset in the repo; a manifest row is PENDING before it is used as data. The registered constraint a = 0.500 ± 0.005 and |s| ≲ 0.005 is taken from the prompt as stated. |
| D4 | gating | The prompt's Round 2 sets a candidate list (a = ½ zero-point, a = ½ from the 720° double cover of PPT17, a = 1) with look-elsewhere count 3 and states that none is derived. |
| D5 | data | "Plate transparency frequency 3×10¹⁵ Hz" (report-only item) is given by the prompt without a source. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** TD06 (mode counting; validated per the prompt, not run here), Law I bridge (ε), measured ℏ, c, k_B, T_CMB. **Dependents:** the benchmark catalogue row B98; the engine's "FLM15 resistance kernel" reference is the other folder. Edges: TD06 → FLM15-cas `cross-check` (the counting is reimplemented here and validated on closed forms).

## 3. Hypotheses, observables, ledger
H1 (Round 1, the seed read literally): gap-mode counting minus free counting, priced by thermal occupation at T_CMB, gives F/A = π²ℏc/(240d⁴). H2 (Round 2): the d-dependent part of sum-minus-integral with a scale-free price a·ℏω has exponent exactly 4 and coefficient aπ²ℏc/120 (energy −aπ²ℏc/(360d³)). Observable: the pressure P(d) between ideal plates, 0.1–10 µm. Ledger: ℏ, c, k_B, T_CMB MEASURED-INPUT (engine); a candidate-dependent (not derived, count 3); no calibrated parameter in Round 1; Round 2 coefficient CALIBRATED(1) if a is set to the measured value.

## 4. Registration
The registration of the prompt (2026-10-03) is adopted unchanged: routes, V1–V3 with their tolerances, the predictions, the rejection criteria (Round 1: exponent ≠ 4 or coefficient outside ±5% of π²ℏc/240; Round 2: extrapolated coefficient off by more than 1e-6 relative from π²/360 per unit a, or fitted exponent off 4 by more than 1e-6), the constraint a = 0.500 ± 0.005, the candidates and the labels. Additions fixed before the instrument existed:
- **Instrument.** Round 1: n = 0 (one polarisation) and n ≥ 1 (two polarisations) gap modes, transverse integral by the closed asymptotic form for n ≥ 1 and exact (−ζ(3)/2π)(k_BT/ℏc)² for n = 0; the exterior pressure u_CMB/3 from `law_I`; P(d) = u_CMB/3 + dF_gap/dd. Exponent fit: least squares of ln P against ln d over d = 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4, 10 µm. Round 2: E(λ) = aℏc[g(0) + 2Σ_{n≥1} g(nπ/d) − (2d/π)∫₀^∞ g] with g(q) = (1/2π)∫_q^∞ s²e^{−λs}ds = e^{−λq}(q²/λ + 2q/λ² + 2/λ³)/2π; route 1: direct sum (compensated) minus the closed integral 3/(πλ⁴); route 2 (Poisson): E(λ) = aℏc (2d/π) Σ_{k≥1} Ĝ(2kd), Ĝ(ω) = (2/(πω)) Im[(λ − iω)⁻³]. At every λ the two routes are compared. Richardson: polynomial in (λ/d)² through the five registered values.
- **Additional validation V4:** at λ/d = 0.08, route 1 and route 2 agree to 1e-8 relative; the Euler–Maclaurin limit λ → 0 of route 2 equals −π²/360 (a = 1, units ℏc/d³) to 1e-6.
- **Candidate scoring:** the force ratio to the ideal form π²ℏc/(240d⁴) is 2a; the constraint 2a = 1.000 ± 0.010 applies. Report-only: u(a = ½, ν_c = 3×10¹⁵ Hz) = aℏc k_c⁴/(4π²) with k_c = 2πν_c/c, against `law_I::P_conv`.

## 5. Gradated outputs and triggers
| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1–V4 not met | repair the instrument |
| G1 | Round 1 rejection criterion met | name the premise (thermal pricing at T_CMB) and run Round 2 (registered) |
| G2 | Round 2: exponent 4 reproduced, coefficient open in a | the price a must come from the influx premise or be measured |
| G3 | consistent within tolerance, shared-input | name the input |
| G4, G5 | not available | — |
Expected landing (the prompt's own prediction): Round 1 G1 (exponent 0, magnitude about 1e-11 of the ideal pressure); Round 2 exponent 4, coefficient aπ²ℏc/120, a open: G2.

## 6. Alternative outs
Registered in the prompt: the candidate list for a; a price ∝ ω^(1+s) giving exponent 4 + s (|s| ≲ 0.005 from the anchor). Added: a derivation of a from the lattice relay (FLM10) or from the PPT17 double cover with its own rejection criterion.

## 7. Run record

- Date 2026-10-07 (recorded 2026-10-08). Instrument `flm15cas_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; constants from `sdt::laws`). Output `flm15cas_reset_1_results.txt`. Single pass, no re-run, no amendment. The registration is the prompt's own (2026-10-03), adopted unchanged.
- **Validations met.** V1 Poisson summation at t = 0.37, 1.9: worst relative difference 2.2×10⁻¹⁶. V2 closed form of g(q) against quadrature at q = 0, 1.5, 4: 4.4×10⁻¹³. V3 ∫x³/(eˣ − 1)dx = 6.4939394023 against π⁴/15 (2.6×10⁻¹³). V4 at λ/d = 0.08 the direct sum-minus-integral (−2.7169153360×10⁻²) and the Poisson route (−2.7169153362×10⁻²) agree to 7.6×10⁻¹¹, and the λ → 0 Poisson limit −2.74155678×10⁻² equals −π²/360 to 2.6×10⁻¹³.
- **Round 1 (COMPUTED).** Thermal pricing at T_CMB = 2.7255 K: k_BT = 2.3487×10⁻⁴ eV; the exterior pressure u_CMB/3 = 1.39159×10⁻¹⁴ Pa (π²(k_BT)⁴/(45(ℏc)³) = 1.39160×10⁻¹⁴); the n = 0 gap free energy per area −1.0199×10⁻¹⁷ J/m², independent of d. For d = 0.1 … 10 µm the n = 1 occupation exponent is −26394.7 … −263.9, and P_net = 1.39159×10⁻¹⁴ Pa at every d against the ideal π²ℏc/(240d⁴) = 13.0 Pa (0.1 µm) … 1.30×10⁻⁷ Pa (10 µm): P_net/P_ideal = 1.07×10⁻¹⁵ (0.1 µm), 1.07×10⁻¹¹ (1 µm), 1.07×10⁻⁷ (10 µm). The fitted exponent of P(d) is 0.000000. The registered rejection criterion (exponent ≠ 4, or coefficient outside ±5%) is met: the thermal-pricing route is excluded.
- **Round 2 (COMPUTED).** Scale-free price aℏω per mode, E_diff/(aℏc/d³), d = 1: λ/d = 0.08: direct −2.7169153360×10⁻², Poisson −2.7169153362×10⁻² (7.6×10⁻¹¹); 0.06: −2.7276720444×10⁻², −2.7276720438×10⁻² (2.4×10⁻¹⁰); 0.04: −2.7353781712×10⁻², −2.7353781734×10⁻² (8.1×10⁻¹⁰); 0.03: −2.7380798245×10⁻², −2.7380798125×10⁻² (4.4×10⁻⁹); 0.02: −2.7400109451×10⁻², −2.7400109835×10⁻² (1.4×10⁻⁸). Richardson in (λ/d)²: E(0) = −2.7415567781×10⁻² against −π²/360 = −2.7415567781×10⁻² (relative 7.8×10⁻¹⁶). |E_diff| ∝ d^(−3.00000000), so the force exponent is 4.00000000. The instrument-level criteria (coefficient off by more than 1e-6; exponent off by more than 1e-6) are not met. Force per unit a: P = aπ²ℏc/(120d⁴); the ratio to the ideal form π²ℏc/(240d⁴) is 2a. Against the registered constraint 2a = 1.000 ± 0.010: a = ½ (zero-point quantum, a prohibited input as a derivation): consistent; a = ½ (720° double cover of the PPT17 tube, underived): consistent; a = 1: excluded (ratio 2.000). Look-elsewhere count 3, no candidate derived.
- **Report-only.** An a = ½ floor to ν_c = 3×10¹⁵ Hz (a frequency given by the prompt without a source): u = aℏck_c⁴/(4π²) = 6.2579×10³ J/m³ against `law_I::P_conv` = 2.4608×10⁴⁸ Pa (ratio 2.54×10⁻⁴⁵).
- Registration defects found in this record: none. The anchor (Mohideen and Roy 1998) is a literature reference and has no manifest row; the constraint a = 0.500 ± 0.005 is taken from the prompt as stated.

## 8. Outcome and direction

**Grades.** Round 1 (the seed read literally, thermal pricing of the gap modes at T_CMB): **G1**, excluded on the pre-registered criterion: the net pressure is the d-independent exterior radiation pressure, 10⁻¹¹ of the ideal Casimir pressure at 1 µm. The premise that produced the exclusion: pricing each mode by a Bose occupation at 2.7 K, which has no d⁻⁴ regime at micron gaps because ℏc/d ≫ k_BT. Round 2, exponent: the force exponent 4 follows from the scale-free price (E ∝ d⁻³) and is exact; it is also what dimensional analysis requires of any mechanism whose only constants are ℏ, c and d (P ∝ ℏc/d⁴), so the exponent does not discriminate between mechanisms (**G3**, shared-input: contaminating input: absence of any length scale in the price, entering by the choice a independent of ω). Round 2, coefficient: **G2**, open: the coefficient is aπ²ℏc/120, equal to the ideal value only for a = ½; the candidate a = 1 is excluded by the stated constraint, and a = ½ (two readings) is consistent with it and is derived by neither. The ζ function enters the Poisson route as ζ(4) = π⁴/90, the origin of the π² in the coefficient. No downgrade by agreement is made.

**Where the method sits against the new rules.** This prompt compares an SDT-flavoured pricing with the standard mode-counting coefficient (π²ℏc/240) and uses Bose occupations and the per-mode price aℏω, which are the standard framework's quantities. What is native in it is the premise (no characteristic length in the influx) and the claim that the plates interrupt the long relay modes. The present record therefore tests the arithmetic and the exclusion of one route; it does not derive the coefficient from a relay model.

**What changes for the dependents.** The benchmark catalogue row B98 takes from this record: the exponent 4 (dimension-forced), the coefficient aπ²ℏc/120 with a open, the thermal route excluded. Nothing claims the Casimir coefficient as derived.

**Direction.**
1. A native derivation of a: the pressure deficit between two plates from the relay modes the gap excludes, in relay terms (which wavelengths the plates interrupt; the transparency frequency of the plates as a registered input with a source), with the coefficient predicted before comparison with the measured force.
2. A registered alternative to the price per mode: a price ∝ ω^(1+s) gives exponent 4 + s; the anchor limits |s| to about 0.005 (as stated in the prompt).
3. A manifest row for the anchor measurement and for the plates' transparency frequency.

## 9. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
