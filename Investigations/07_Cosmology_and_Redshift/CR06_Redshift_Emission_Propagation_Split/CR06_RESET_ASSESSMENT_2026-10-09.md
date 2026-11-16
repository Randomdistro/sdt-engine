# CR06 (redshift: emission and propagation split; propagation law against the Pantheon bins) — blank-slate assessment (2026-10-09)

> **[SUPERSEDED 2026-10-09 at Harvey's direction.]** This run used the prompt's gates (exclusion at Δχ² > 9, PASS/FAIL classes, bend fraction 0.9, stability and held-out criteria) and a single-power transit family with the prefactor taken as a convention. Its computed numbers stand as computed; its classifications (G1 exclusions, RC1–RC4, "FAIL") are withdrawn. Current record: `CR06_REFRAME_ASSESSMENT_2026-10-09.md`. Text below kept visible.

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07. Instrument `cr06_reset_1.cpp` (registration in its header, fixed before any data row was read); output `cr06_reset_1_results.txt`. Attempt 1 stopped at a validation (kept as `cr06_reset_1_results_attempt1_G0.txt`); attempt 2 is the recorded run, single pass over the whole range.

## 0. Inputs read and exposure
Read: `CR06/PROMPT.md` (whole); `data/pantheon_binned_DS17f.txt` (the file the prompt names; sha256 `DE0A0DD9CA2EFC55E4BAA28F6B72C149C635D82B752E7B547493541D966EFE27`; only the header before the registration); `cosmology.hpp` (strain-rate and age blocks, with the "NO-DERIVED-d(z)" provenance guard), `laws.hpp` (Law I), `Theory/00_Ruleset.md`, `CONDENSA_Spation_Lattice_Unification.md` §2; `Hubble/INVESTIGATION_Hubble_Tension.md` §4.3 and §7.2-7.3 (the document the prompt cites for the n = 4 law; read for the statement of the law, nothing else). Not read: `CR06_VERDICT.md`, `cr06_results.txt`, `cr06_redshift_fit.cpp`. The prompt's 2026-10-05 correction block states that an earlier fit gave n ≈ 0.66; it is a statement inside the specification and chose no test.
Prior exposure carried over from the SAR02 session: the REOPEN STATUS and first LEDGER rows (no CR06 content).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | The fitted family dz/dr = κ(1+z)ⁿ is a transit law: the photon's redshift at a point on the path sets the rate of further shift. `cosmology.hpp` records that no derived d(z) exists and that an in-flight compounding law may not be cited as an SDT derivation (the CR07 endpoint-ruler reading: nothing happens in transit). The exponent therefore has no native derivation to compare with; the question "derive n" has no instrument. |
| D2 | premise | The n = 4 law takes κ ∝ T(z)⁴ with T(z) = T_CMB(1+z). T(z) is an emission-epoch mapping (`cosmology.hpp`: "not a transit history"). Using it as a transit property is the premise the data are asked to test. |
| D3 | construction | D_L = (1+z)·r is used for every model. For a static medium the exponent p of the prefactor is a separate native question (energy loss alone gives ½; energy loss with arrival-rate dilation gives 1). It enters the fitted n (§3.5). |
| D4 | data | The file carries diagonal errors only; the covariance is not in the repository (PENDING). Absolute χ²/dof is not a gate; differences between models are used. One offset a = M − 5log₁₀H₀ + const per model absorbs H₀ and the absolute magnitude, so the test is of shape only. |
| D5 | record | "Linear" in the prompt's table, D = z(1+z), is flat ΛCDM with Ω_m = 0 (de Sitter), not a kinematic-linear model. |
| D6 | record | The header states "EXECUTED-honest" and "Dual verdict … KILLED"; the audit block states OWED. Register terms are those of the gateway; the status is OPEN as recorded here. |
No downgrade is made on agreement grounds.

## 2. Dependencies
Suppliers: none among the investigations (layer 0). Constants taken: none (dimensionless shapes). Consumers: GOM01 (graph edge) and, through the strain-rate block, every tool that cites a σ₀-integrated distance (guarded in `cosmology.hpp`). Cross-record: CR09 Route B fits an exponent named n in its own registration; the two are not compared here.

## 3. Five questions, ledger, results

**1. What do we not know?** A distance–redshift relation natively consistent with the endpoint-ruler reading of redshift. What the data show here is which of the documents' candidate transit laws survive and what exponent a single-power family would need.
**2. Why does it matter?** The strain-rate block, R_CMB and the shell count N inherit class X until a d(z) exists (`cosmology.hpp`); the Hubble-tension account rests on a κ(r) profile.
**3. By what methods?** Two candidate laws with zero shape parameters (N1: n = 1; N4: n = 4), the n-free diagnostic, and four comparators at the same fidelity; one offset each; whole-range fit; three held-out splits; exact profile intervals.
**4. What would prove us wrong?** (a) Indicators: an exponent that changes with the range fitted; a prefactor convention that moves the exponent. (b) Mathematics: RC1–RC4 (header). (c) What it breaks: if both candidates are excluded, the κ(1+z)ⁿ transit family does not carry the SDT redshift–distance relation and the d(z) must come from the endpoint construction.
**5. Done when** each candidate has a criterion outcome on the whole range and on held-out data, the exponent's stability is recorded, and the direction for a native d(z) is stated in numbers.

**Three-column ledger**
| | Standard account | SDT candidate (prediction registered first) | Discriminating observable |
|---|---|---|---|
| distance law | flat ΛCDM, Ω_m fitted (1 shape parameter) | N1 and N4, no shape parameter; n-free as diagnostic | the shape D_L(z) over z = 0.014–1.612; a native d(z) would fix it without a fit |
| flux–distance prefactor | (1+z)¹ from arrival-rate dilation and energy loss | not derived (D3) | light-curve stretch versus (1+z) |
| absolute scale | H₀ and M degenerate in the offset | offset, not tested | an absolute anchor independent of the shape |

### 3.1 Validations (attempt 2)
V5 file: 40 rows, z = 0.014–1.612. V1 family closed form against midpoint quadrature: worst relative difference 3.41×10⁻¹¹. V2 LCDM(Ω_m = 1) against the EdS closed form 4.0×10⁻¹⁴, LCDM(Ω_m = 0) against z(1+z) 2.2×10⁻¹⁶. V3 (toy) noiseless n = 2.5, a = 3.7 recovered to 1×10⁻⁸, χ² 1.2×10⁻²⁵. V4 (toy) 200 noisy realisations of n = 4: mean n̂ 3.9987, scatter 0.0328.
**Misstep recorded (attempt 1, G0):** V2 as first registered compared LCDM(Ω_m = 0) with Milne. Flat ΛCDM at Ω_m = 0 is de Sitter, z(1+z); Milne is the open empty model and is not a flat-ΛCDM limit. The registered known answer was wrong; the instrument was not. Attempt 1 stopped at validation, before any fit; its output is kept. Corrected in the header (dated) and re-run.

### 3.2 Full-data fit (COMPUTED; N = 40)
| Model | shape parameter | offset a | χ² | χ²/dof | ΔAIC |
|---|---|---|---|---|---|
| ΛCDM(Ω_m) | Ω_m = 0.2841 | 23.80277 | 49.738 | 1.309 | 0 |
| n-free | n = 0.6555 | 23.83028 | 81.027 | 2.132 | 31.289 |
| Milne | – | 23.88822 | 169.240 | 4.339 | 117.502 |
| N1 (n = 1) | – | 23.91797 | 324.774 | 8.328 | 273.036 |
| Linear (de Sitter) | – | 23.65850 | 1060.323 | 27.188 | 1008.585 |
| EdS | – | 24.04209 | 1468.972 | 37.666 | 1417.234 |
| N4 (n = 4) | – | 24.60766 | 16517.827 | 423.534 | 16466.089 |
- n-free: n̂ = 0.6555 (CALIBRATED(1)), Δχ² = 1 interval [0.6339, 0.6772].
- **RC1:** χ²(N1) − χ²(n-free) = 243.747 → excluded; χ²(N4) − χ²(n-free) = 16436.800 → excluded. Class: both excluded.
- Bend: χ²(Milne) − χ²(ΛCDM) = 119.502 > 9, so the data show a bend. Fractions f = [χ²(Milne) − χ²(model)]/119.502: N1 −1.302 (N1 fits worse than Milne by 155.5), N4 −136.805, n-free 0.738 (< 0.9).
- **RC2** (prompt's classes, lower-χ² candidate N1): FAIL. The n-free diagnostic does not reach the bend criterion either (f = 0.738; ΔAIC 31.3 > 10).
- N4: residuals run from −31σ at z ≈ 0.03 to +46σ at z ≈ 0.95. Its distance shape r = [1 − (1+z)⁻³]/3 saturates at ⅓; the data keep rising.
- Residuals of the n-free fit: −3.68σ at z = 1.612, −1.85σ at 1.234, −2.62σ at the second bin (z = 0.019): structure at both ends of the range.
- Look-elsewhere: 7 models, 2 candidates.

### 3.3 Held-out (parameters from the train bins only)
| Split | N1 test χ² | N4 test χ² | n-free test χ² | ΛCDM test χ² | Milne test χ² |
|---|---|---|---|---|---|
| S1 lowest 20 → highest 20 | 434.8 | 26829.0 | 635.5 | 312.7 | 153.4 |
| S2 even → odd | 171.8 | 8547.9 | 56.0 | 34.6 | 98.4 |
| S2′ odd → even | 154.9 | 8034.6 | 27.3 | 15.8 | 71.1 |
- **RC4:** N1 and N4 are not predictively consistent with ΛCDM (test χ² above ΛCDM by more than 9 on every split). The n-free test χ² exceeds ΛCDM's by 322.8 (S1), 21.4 (S2), 11.5 (S2′). On S1 (extrapolation to high z) the parameter-free Milne model has the lowest test χ² of the seven.
- **RC3:** n̂ from the train bins: S1 0.237 [0.135, 0.340]; S2 0.637 [0.605, 0.668]; S2′ 0.673 [0.643, 0.703]; full 0.656. S2 and S2′ agree with the full value (differences 0.019, 0.017; combined σ 0.038, 0.037). S1 does not (difference 0.418, combined σ 0.104). The exponent is stable under interpolation and not under extrapolation: **RC3 not met.**

### 3.4 What the data require locally
Using the ΛCDM comparator fit as a smooth description of the data (a comparator-dependent description, not a derivation), the local exponent n_eff(z) = d ln(dz/dr)/d ln(1+z) = 1.5 Ω_m(1+z)³/[Ω_m(1+z)³ + 1 − Ω_m] with Ω_m = 0.2841 is 0.426 (z = 0), 0.518 (0.1), 0.699 (0.3), 0.859 (0.5), 1.141 (1.0), 1.314 (1.612). A constant exponent (N1: 1, N4: 4, n-free: 0.6555) cannot follow a rise from 0.43 to 1.3; this is consistent with the S1/S2 instability above.

### 3.5 Prefactor sensitivity (reported, not selected)
n-free fit with D = (1+z)ᵖ r: p = 0.5: n̂ = −0.2596, χ² 98.143; p = 1: n̂ = 0.6555, χ² 81.027; p = 2: n̂ = 2.8066, χ² 121.419. The fitted exponent moves by about 3 across the prefactor convention; the χ² prefers p = 1 within this family (Δχ² +17.1 and +40.4). The exponent and the prefactor power are not separately determined by the shape.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| N4 (n = 4, κ ∝ T⁴ as a transit law) | **G1, excluded** | Δχ² = 16436.8 against the best single power; χ² = 16517.8 against 49.7 for ΛCDM; not predictive on any split. Premise producing it: T(z) = T_CMB(1+z), an emission-epoch mapping, used as a transit property with κ constant in the path (D2) |
| N1 (n = 1) | **G1, excluded** | Δχ² = 243.7; fits worse than the parameter-free Milne model (324.8 against 169.2). Premise producing it: constant octaves per unit distance and a transit form (D1) |
| n-free exponent n̂ = 0.6555 [0.634, 0.677] | **G2, open** | CALIBRATED(1); no native derivation; not stable under extrapolation (RC3), moves with the prefactor convention (§3.5); χ² 31.3 AIC units above ΛCDM; bend fraction 0.738 |
| "derive n from the closure evolution" | **G2, open** | the engine holds no derived d(z) (`cosmology.hpp` guard); the candidate transit family is excluded in its two documented forms |
| Flux–distance prefactor p | **G2, open** | the data prefer p = 1 within this family; its native origin (arrival-rate dilation) is not derived |
| Emission half (per-source λ shift) | not tested | outside this instrument (the prompt's scope note) |
No label in this record downgrades a result for agreement with a Standard-Model formula.

## 5. Direction
1. **A native d(z) built from the endpoint-ruler reading,** not a transit ODE. It has to supply (a) the ruler ratio 1+z between observer and emitter as a function of position, (b) the flux–distance rule (the prefactor power), and (c) a local exponent that rises from about 0.4 at z = 0 to about 1.3 at z = 1.6 (§3.4) without a fit. Registration comes first: the prediction of r(z) is fixed from the construction, then compared once with these bins.
2. **Data:** the Pantheon covariance (PENDING in `Datasets/`) before any χ² is read as a goodness of fit; light-curve stretch against (1+z) as the observable for the prefactor.
3. **What this changes downstream.** GOM01 and every consumer of a σ₀-integrated distance stay at class X (`cosmology.hpp` guard stands). The Hubble-tension account that relies on κ ∝ (1+z)⁴ has no support from this test: its distance law is excluded on these data.
4. **Stability check outstanding:** repeat the exponent stability test (RC3) on an independent supernova compilation that is not in `Datasets/` (PENDING), to separate a property of these 40 bins from a property of the family.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
