# PPT08 — blank-slate assessment (2026-10-07)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1.

> **ANNOTATION 2026-10-07, at Harvey's challenge on attractive laws.** The instrument sums a wake potential Φ = −κ Σ w/|X − x| and averages it over circular orbits as a "first-order orbit energy". That is a potential-energy construction of the Standard framework. In SDT the electron is pushed by the pressure difference across shadows; there is no stored potential. The G1 on H1 (E(equatorial) < E(polar), "more bound") and the energy language of H2 rest on that framing and are withdrawn as SDT results. What stands as geometry: the second-moment tensor of the (2,3) source (oblate: s_z < s_xy), the r⁻³ scaling of the anisotropy, and the absence of an m = 3 azimuthal mode under circular-orbit averaging with n → −n symmetry. What is open: the sign and size of the orbit-orientation effect once the response is stated as a pressure push (a force on the orbiting body integrated over its path, with the sign set by the handed redirection of EMC03), and the identification of the s and p seats.

## 0. Inputs read before the pre-registration, and exposure
Read: `PPT08/PROMPT.md`; `laws.hpp` (`measured`, `law_VI` multipole exponents and Lamb entries at lines 2570–2587, the open-problems block); `Datasets/MANIFEST.md` (no Lamb or muonic entry); the dependency graph (PPT08 is layer 0, reach 103; consumers APS01, APS02, FLM11; the prompt names PPT01, PPT06, Law VI). Not read: `PPT08_VERDICT.md`, `PPT08_KOPPA_TARGET.md`, `ppt08_results.txt`, `ppt08_trefoil_wake.py`, the `PPT08A_Per_Spation_Rolling_Mechanics` folder.
Exposure: (i) canon comments state that the Lamb intervals are OBSERVED-INPUT and not SDT-derived, that the PPT08 "koppa map" is a re-expression of the H interval, and that an absolute Lamb interval "remains open"; they also give the wake power-law exponents (monopole −1, quadrupole −3, three-fold harmonic −4); (ii) before writing §4 the author evaluated by hand the second-moment formula of §4 for the closure geometry and obtained a sign (equatorial below polar) and a size of order 1 kHz at r = 4a₀. The registered tests below test those hand results and the prompt's claims; the expected landing in §5 is stated with that disclosure.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | "Wake field" is not defined. The prompt writes Φ_wake = Φ₀ + Φ₂P₂(cosθ) + Φ₃cos3φ with unspecified radial functions (and uses P₂ and cos 3φ, i.e. imported angular functions, although §0 prohibits them). A definition is registered below from Law III (inverse-square kernel) and the (2,3) path. |
| D2 | construction | The identification equatorial orbit ↔ s, polar orbit ↔ p is the hypothesis; the test is on the sign of E(equatorial) − E(polar). |
| D3 | gating | The prompt's mechanism (§3.3) predicts E(equatorial) > E(polar) "because the electron interacts more strongly". With a kernel of the same sign as the monopole, a stronger interaction means a more bound orbit. The sign is a computable property of the source geometry. |
| D4 | gating | Size of the trefoil is not fixed by the prompt; PPT01's closure (R = ℏ/(m v_T), a = ℏ/(m v_P)) is the supplier's specification. |
| D5 | data | Lamb interval 1057.845 MHz (H n = 2) and 14041.13 MHz (He⁺ n = 2) are in the engine as OBSERVED anchors. Muonic hydrogen: no muon mass in the engine and no datum in `Datasets/`; P2 is deferred. Deuterium (P1) needs the deuteron geometry (NP17 and NP06 packing). Positronium (P3): the mechanism has no source by construction; there is no populated rejection class from this mechanism alone. |
| D6 | premise | Orbit-energy dependence on orientation is a classical first-order average over a circular orbit; no angular-momentum operator or wavefunction is used. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** PPT01 (closure geometry; from its prompt), PPT06 (declared; the 1.831c seat is not used here), Law VI (W = 3, (2,3) path), Law III (inverse-square kernel). **Dependents:** APS01, APS02, FLM11 (graph); the canon wake-exponent comment. Edge classes: PPT01 → PPT08 `required` (size); PPT06 → PPT08 `cross-check` (unused); NP17 → PPT08 `required` for P1 (deferred).

## 3. Hypothesis, observable, ledger
H1: the three-fold wake of the (2,3) trefoil gives orbit energies that depend on the orbit's orientation with E(equatorial) > E(polar) (the sign of the 2S–2P interval). H2: the size of the splitting at r = 4a₀ (n = 2, r_n = n²a₀) is within a factor 10 of 1057.845 MHz (the gap statement; the acceptance gate of the prompt is 10%). H3: the lowest azimuthal anisotropy of the orbit energy is the three-fold harmonic of the wake.
Observable: ΔE = E(orbit normal ∥ z) − E(orbit normal ⊥ z), in Hz (E/h), for circular orbits of radius r about the source centre. Data: `law_VI::lamb_shift_measured_MHz` (OBSERVED anchor). Ledger: coupling κ = αℏc (the monopole, the hydrogen well scale; MEASURED-INPUT α, ℏ, c); source weights uniform per unit arclength of the (2,3) path (registered choice); sizes from the PPT01 closure with m_p (G1, primary) and with outer extent R + a = R_p (G2, secondary; look-elsewhere count 2). No calibrated parameter.

## 4. Pre-registration (written before `ppt08_reset_1.cpp` exists)
**Model.** Source points x_i (i = 1…N) uniformly in arclength on the torus knot x(t) = ((R + a cos qt) cos pt, (R + a cos qt) sin pt, a sin qt), (p,q) = (2,3), weights w_i = 1/N. Wake potential Φ(X) = −κ Σ w_i /|X − x_i| (Law III inverse-square force, integrated). First-order orbit energy for a circular orbit of radius r with unit normal n: E(n) = ⟨Φ⟩ over the circle, evaluated by quadrature. Route 2 (second moments): with S = Σ w_i x_i x_iᵀ, Q = 3S − tr(S) I, E(n) = −κ/r + κ nᵀQn/(4r³) + O(r⁻⁴); equatorial n = ẑ and polar n ⊥ ẑ give ΔE = E(ẑ) − E(⊥) = 3κ(s_z − s_xy)/(4r³) with s_z = S_zz, s_xy = S_xx = S_yy.

**Validations (not met ⇒ G0).**
- V1 (ring, known answer): for a uniform ring of radius R in the equatorial plane and r/R = 50, route 1 (numerical orbit averages) equals the analytic leading term ΔE = −3κR²/(8r³) to 5e-3 relative; for a single source at the origin ⟨Φ⟩ = −κ/r exactly.
- V2 (convergence): the numerical anisotropy at r/R = 20 changes by < 1e-9 relative between (N, M) = (20000, 720) and (80000, 2880) (N source points, M orbit points).
- V3 (second moments): for the (2,3) path, S computed by quadrature equals s_z = a²/2 and s_xy = (R² + a²/2)/2 to 1e-6 (analytic known answer for q ≠ 2p, 2q ≠ 2p).
- V4 (symmetry): rotating the source by 2π/3 about z leaves every E(n) unchanged to 1e-12, and E(n) = E(−n).

**Tests.**
- T1 (COMPUTED): ΔE(r) at r/R = 20, 40, 80 by route 1; the coefficient c₂ = ΔE·r³/κ extrapolated to r/R → ∞ by Richardson in (R/r)²; route 2 value of c₂ = 3(s_z − s_xy)/4. Agreement of the two routes within 1%. Geometries G1 (primary) and G2.
- T2 (sign, criterion R1): H1 is rejected if ΔE < 0 (E(equatorial) < E(polar)) in both routes on the primary geometry. Classes populated: ΔE > 0, ΔE < 0, |ΔE| below 1e-6 of its magnitude.
- T3 (magnitude, criterion R2): ΔE/h at r = 4a₀ from route 2 (scaling ΔE ∝ r⁻³ from T1) against 1057.845 MHz; H2 is rejected if |ΔE|/h lies outside [0.1, 10] × 1057.845 MHz. Report-only: He⁺ n = 2 (r = 2a₀, κ → 2κ) against 14041.13 MHz.
- T4 (azimuthal anisotropy, criterion R3): E(φ_n) for polar normals n = (cos φ_n, sin φ_n, 0) at r/R = 10, 20, 40: Fourier modes m = 0…12. H3 (the lowest azimuthal anisotropy is m = 3) is rejected if |c₃| < 1e-6 |c₆| with c₆ resolved above 1e-12 of the monopole term; the scaling of |c₆|/(κ/r) with r/R is fitted (exponent). Classes populated: m = 3 present, absent (m = 6 lowest), no azimuthal anisotropy resolved.
- T5: P1, P2 DEFERRED (D5); P3 not a test of this mechanism (D5).

**Whole-range single pass.** All radii and both geometries are computed once from the registered rule.

**Amendment 1 (2026-10-07, before any instrument existed or ran).** (a) V3 as registered quotes closed-form second moments, s_z = a²/2 and s_xy = (R² + a²/2)/2. Those hold for weights uniform in the curve parameter t. The registered model weights are uniform per unit arclength, and the speed |x′(t)|² = a²q² + p²(R + a cos qt)² varies with cos qt, which correlates with sin²qt; the closed form is therefore not the known answer for the registered model. Correction: V3 validates the quadrature on the parameter-uniform weighting (closed form, 1e-6); the registered model keeps arclength weights and route 2 uses S integrated numerically with those weights (N = 84000 nodes, speed-weighted trapezoid). The parameter-uniform weighting is reported as a sensitivity (second weighting, look-elsewhere count 2 for the weights). (b) Quadrature sizes: (N, M) = (21000, 720) and (84000, 2880), N a multiple of 3 so that a rotation by 2π/3 about z maps nodes onto nodes (V4); sizes are numerics, not criteria. No threshold, tolerance or rejection criterion is changed.

## 5. Gradated outputs and triggers
| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1–V4 not met | repair the instrument |
| G1 | R1 or R2 met | name the premise (source weights and kernel; the equatorial ↔ s identification; the size of the source) and start the alternatives of §6 |
| G2 | R1, R2 not met but P1/P2 deferred | NP17, muonic data decide |
| G3 | consistent within tolerance, shared-input | not expected |
| G4, G5 | not available | — |

Expected landing (stated with the exposure of §0): G1 on R1 and R2; R3 met (m = 6, not m = 3).

## 6. Alternative outs
1. A source with non-uniform weights from the lattice (the traction wake of PPT06, per-spation relay solver FLM10) in place of uniform weights per arclength; registered with its own criterion.
2. Orbit sizes and the proton-centre pressure-work amplitude from the polar-dyad geometry (APS14 per the canon note): needed for an absolute 2S–2P interval.
3. A repulsive (deficit) sign of the wake relative to the monopole (EMC03): reverses the sign of ΔE; registered with EMC03's outcome, not chosen here.

## 7. Run record

- Date 2026-10-07. Instrument `ppt08_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; constants and the Lamb anchors from `sdt::laws`). Attempt 1: all validations met, object values complete, but the He⁺ report-only printf omitted its value argument (the build warning was misread); output kept as `ppt08_reset_1_results_attempt1_printf_fault.txt`. Attempt 2: argument added; every other number identical; output `ppt08_reset_1_results.txt`. Amendment 1 (§4) preceded both runs. Single pass over the registered range.
- **Validations met.** V1: ring at r/R = 50: numerical E(z) − E(x) = −3.000281e-6 κ/R against the analytic −3/(8r³) = −3.000000e-6 (ratio 1.00009); single-source monopole residual 8e-17. V2: anisotropy at r/R = 20 for (N, M) = (21000, 720) and (84000, 2880): −4.3522146418e-5 both, relative difference 2.4e-12. V3: parameter-uniform weights give s_z = 0.33333333 and s_xy = 0.66666667, equal to the closed forms. V4: rotation by 2π/3 and n → −n change every E(n) by at most 1.0e-15 relative.
- **T1 (COMPUTED).** (2,3) knot, arclength weights, a/R = √(2/3) = 0.81650. D(r) = (E(z) − E(x)) r³/(κR²): −0.34817717 (r/R = 20), −0.34801413 (40), −0.34797364 (80); Richardson (r⁻² terms removed): −0.34795979 (20, 40), −0.34796015 (40, 80), −0.34796017 (second order). Route 2 (arclength second moments): s_z = 0.32657564, s_xy = 0.79052253, c₂ = 3(s_z − s_xy)/4 = −0.34796017; the routes agree to 5.7e-10. Parameter-uniform weights (sensitivity): c₂ = −0.25 (0.7185 of the arclength value); both are negative.
- **T2, T3 (COMPUTED).** κ = αℏc = 2.3071e-28 J m; ΔE = E(equatorial) − E(polar) = κ c₂ R²/r³ at r = 4a₀. G1 (closure, R = 3.3253e-16 m, a = 2.7151e-16 m): ΔE = −9.360e-31 J = −1412.56 Hz, 1.335e-6 of 1057.845 MHz; He⁺ (r = 2a₀, 2κ): −22601 Hz, 1.61e-6 of 14041.13 MHz. G2 (R + a = R_p, R = 4.6320e-16 m): −2740.87 Hz (2.59e-6); He⁺: −43854 Hz (3.12e-6). Rejection criterion R1 met (ΔE < 0 on both routes: E(equatorial) < E(polar)); R2 met (the magnitude is outside [0.1, 10] × 1057.845 MHz by a factor of 7.5e5 below the lower bound on G1). Look-elsewhere count 2 geometries × 2 weightings; every combination gives a negative sign and a magnitude of order 1 kHz.
- **T4 (COMPUTED).** E(φ_n) for polar normals, Fourier modes in units of the monopole: m = 6 relative to the monopole: 1.012e-7 (r/R = 10), 1.670e-9 (20), 2.645e-11 (40); the ratios between successive radii, 60.6 and 63.1, correspond to r^−5.92 and r^−5.98 (the ℓ = 6 scaling r⁻⁶). The modes m = 1–5 sit at the rounding floor (6e-17 to 4e-16 of the monopole) at all three radii, as does m = 12 at r/R ≥ 20. |c₃|/|c₆| = 1.7e-9 (r/R = 10), 1.0e-7 (20), 8.3e-6 (40). Rejection criterion R3: met at r/R = 10 and 20 (ratios below 1e-6); at r/R = 40 the ratio is 8.3e-6 because c₆ is only 1e5 above the rounding floor that sets |c₃| (the registered resolution threshold of 1e-12 for c₆ was too permissive for the 1e-6 ratio); the floor comparison and the exact symmetry argument (n → −n with the three-fold rotation) give m = 3 absent at all three radii. At r = 4a₀ the m = 6 amplitude relative to the monopole is (R/r)⁶ of order 1e-35 (arithmetic, R/r = 1.6e-6).
- **T5.** P1 (deuterium) and P2 (muonic hydrogen): DEFERRED (no deuteron geometry; no muon mass in the engine and no muonic datum in `Datasets/`). P3 (positronium): not a test of this mechanism (no source by construction).
- Registration defects found in this record: V3's closed-form known answers did not apply to the registered weights (Amendment 1, before any run); the T4 resolution threshold above; the attempt-1 printf. None changes a criterion's outcome.

## 8. Outcome and direction

**Grades.** H1 (E(equatorial) > E(polar)): **G1**, excluded on the pre-registered form: the sign is negative on both routes, both geometries and both weightings. H2 (2S–2P interval within a factor 10 of 1057.845 MHz): **G1**, excluded: ΔE/h = −1.41 kHz (G1), 1.3e-6 of the measured value; the leading anisotropy scales as κR²/r³ with R ≈ 3e-16 m against r = 2e-10 m. H3 (lowest azimuthal anisotropy is the three-fold harmonic): **G1**, excluded: in circular-orbit energies the lowest azimuthal anisotropy is m = 6 (n → −n and the three-fold symmetry remove m = 3), amplitude ∝ r⁻⁶. P1, P2: **G2**, deferred. The premises that produced the exclusions: (i) a wake of the same sign as the monopole with weights uniform per unit arclength; the source is oblate (s_z = 0.3266 < s_xy = 0.7905), so the equatorial orbit is the more bound one; (ii) the identification of the s seat with the equatorial circular orbit; (iii) the source size set by the PPT01 closure or by R_p. No downgrade by agreement is made.

**What changes for the dependents.**
- APS01, APS02, FLM11 take no native s/p angular degree of freedom from PPT08: with the registered kernel the sign is opposite and the size is 6 orders too small; the three-fold harmonic does not survive circular-orbit averaging.
- The canon wake exponents are consistent with what is computed for ℓ = 2 (E ∝ r⁻³ from the quadrupole moment, the numerical D(r) is constant to 3e-4 over r/R = 20…80); the ℓ = 3 exponent (−4) appears in the potential but not in circular-orbit energies. This record does not edit canon.
- Edges: PPT01 → PPT08 `required` (size); PPT06 → PPT08 `cross-check` (unused); EMC03 → PPT08 `required` for the sign of the wake relative to the monopole (open); NP17 → PPT08 `required` for P1.

**Direction for the next layer of theory.**
1. The sign of ΔE is the product of the sign of (s_z − s_xy) and the sign of the wake relative to the monopole; register EMC03's sign rule before any further sign claim. A deficit-type (opposite-sign) wake reverses ΔE but not its size.
2. The prompt's s seat is a state without orbital rotation: a classical analogue is a radial-plunge orbit through the source region, whose energy shift depends on the dwell time at r ≲ R, an observable not tested here (it carries a finite-size term, not the r⁻³ tail). Register it with its own criterion; the size gap of 1e6 can only be closed by a term that is not the far-field tail.
3. An absolute interval needs a source amplitude from the lattice (FLM10, the polar-dyad geometry in the canon note on APS14), not a monopole-normalised uniform-weight path.
4. P1 and P2 need NP17's deuteron geometry and a muon seat with a registered datum.

## 9. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
