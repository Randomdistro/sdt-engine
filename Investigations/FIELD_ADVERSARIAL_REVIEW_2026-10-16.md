# FIELD-GROUP ADVERSARIAL REVIEW — all investigation fields, 2026-10-16

Register: master specification supplied by the Operator (hierarchy Hidden Mechanisms → Assumption Breaks → Leverage Points → Strategic/IP → Failure Modes). Sources: `Investigations/RESET_2026-10-06/LEDGER.csv` (125 rows), `STATUS.md`, per-field `PROMPT.md` state blocks, current-session NSEQ16/18/19, GOM41/42, SAR09 and PPT16 records, and `Engine/include/sdt/laws.hpp`. Certification tags: DERIVED, COMPUTED, IDENTITY, CALIBRATED, OBSERVED, PENDING. No manuscript (6.1) and no deployment package (6.2) is issued: no field holds a closed, error-checked solution to an open mechanism, and no verified named point of contact exists in the record.

## 0. Scope limits and specification checks

- **Coverage.** 291 investigation folders in 21 field directories (18 numbered fields plus 3 duplicate-numbered directories). Folder identifiers with at least one ledger row: 87 of 291; 87 ÷ 291 = 0.2990, so 29.9 %. Fields with zero ledger rows: `00_Master_Cascade` (4 folders), `04_Atomic_and_Spectroscopy` (2), `09_Particle_Physics_and_Topology` (2). Fields below 15 % coverage: `10_Fluid_Dynamics` 1/12 = 8.3 %, `12_Condensed_Matter_Physics` 1/8 = 12.5 %, `13_Quantum_Foundations_and_Measurement` 1/8 = 12.5 %, `15_Optics_and_Photonics` 1/10 = 10 %, `08_Galactic_Dynamics` 1/10 = 10 %.
- **Non-physics ledger rows.** SPEC AUDIT 17 + PREMISE AUDIT 4 + DEFERRED 5 + PENDING 1 + DISSOLVED 1 = 28 rows of 125; 28 ÷ 125 = 0.224, so 22.4 % of ledger rows record a specification or premise defect, with no physics gate run.
- **Constants in the specification versus `laws.hpp`.** ℓ_P = 1.616255×10⁻³⁵ m stored (line 99). t_P = ℓ_P ÷ c = 1.616255×10⁻³⁵ ÷ 2.99792458×10⁸: 1.616255 ÷ 2.99792458 = 0.539125, so t_P = 5.39125×10⁻⁴⁴ s; matches the quoted 5.39124×10⁻⁴⁴ s to the rounding of the quoted digits. N = R_CMB ÷ ℓ_P (line 252), 5.894×10⁶¹ in the comment. V_disp values 9.988×10⁻⁶² and 1.834×10⁻⁵⁸ m³ present (lines 770, 774). The hydrogen interaction radius sqrt(R_p_lock × r_e) is defined at lines 478–486 under a symbol named with a word excluded from active SDT prose by the repository gateway; the radius is referred to here by formula only.
- **Back-check ledgers named in the specification.** Superseded: the Operator located the Helix sources in the sibling repository `hsml_os` (`docs/operators/CONNECTIONS.md`, 37 rows C01–C37; `shell/lod.hpp`; `core/math/globe.hpp`; `scripts/check_spherical_purity.ps1`). The first draft recorded the files as absent and the benchmark file as holding 66 rows against 88; both entries were wrong for the full tree. Corrections and the executed checks are in Addendum 2026-10-16-B below.
- **Pronoun constraint.** Applied to the file text; the scan result is appended at the end.

## X. Cross-field mechanisms (group of groups)

**X1. Shared-form results graded as results.** koppa numerically equals the Newtonian GM/c² (GOM25 G3, GOM26 COMPUTED shared-form, GOM27, RTM01 limb 1.75170 ″ against 4 koppa/R 1.75169 ″); Casimir exponent 4.00000000 (FLM15), Planck-law constants a, σ, b (SAR02 G4), Saha balance (CR14), the muon budget (PPT16 G4, +0.21 σ), RTM02 closed ledgers (cannot fail), GD03 zk² = 1 to 2×10⁻¹⁶ (IDENTITY). No entry discriminates between SDT and the standard formula; every entry is tagged IDENTITY or convergent. Results capable of discrimination, with outcomes neutral or unfavourable: PPT04 (one-sided neutrino-moment bound), NP12 (radius), NSEQ18 O1–O3, NP16A04.

**X2. Unsourced constants in construction layers.** `nuclear-inputs.js` carries `tritonOpeningScale` 1.05 and `tritonClosingScale` 0.95, absent from `laws.hpp` (grep, zero matches). The engine nucleon carries strand diameter 0.06 fm and straight-helix length 5.28 fm with no record (PPT18 K2). FLM01: State28D scales 1×10¹⁰ Pa/m and 1×10⁻²⁰ J not derivable, 0 of 10 outputs within 20 %. Repair, common to the three: a provenance scan extracting every numeric literal from `Release/HTML_SDT_Website/js/*.js` and `docs/js/*.js`, resolving every literal to a `laws.hpp` symbol or a dated record, and failing the build on an unresolved literal. Tier of the present constants: CALIBRATED with no calibration record.

**X3. Winding ambiguity gates at least eight investigations.** Candidate windings and the dimensionless aspect √(q/p): (2,3) → √1.5 = 1.22474, v_T/c = √0.4 = 0.63246; (4,5) → √1.25 = 1.11803; W = 3 → √3 = 1.73205, v_T/c = 0.5; engine H1 R/a = 19.8 and braid-spec R/a = 0.62 ÷ 0.22 = 2.818. Blocked or conditional on the ruling: PPT01, PPT12, PPT13, PPT14, PPT15, PPT18, NSEQ16 G8, NP17b. Repair: a decision table (one row per winding, columns: aspect, v_T, nucleon envelope ≤ R_p, downstream gate outcomes) completed for the Operator's ruling; the ruling is the single input missing.

**X4. Sensitivity shortfall before data acquisition.** GOM36, GOM36-run2, GOM37 and GOM25 carry UNADJUDICATED. GOM36: predicted Doppler +0.988 Hz against residual sd 1.43 Hz; 0.988 ÷ 1.43 = 0.691. Repair: gate every observational investigation on a Fisher bound σ_K = σ_obs ÷ |∂obs/∂K| computed and registered before data are opened; refuse acquisition where the bound exceeds the effect.

**X5. Search limits recorded as structure.** NSEQ19: 250 of 296 nuclides packed at registered settings, 46 at relaxed settings; 46 ÷ 296 = 0.1554. GOM42 P1: great-inequality period 473.15 yr against 938.68 yr; (473.15 − 938.68) ÷ 938.68 = −465.53 ÷ 938.68 = −0.4959; traced to initial conditions, not to the native inputs. Repair: report a result only with the search or initial-condition sensitivity attached.

**X6. Count degeneracy.** For the grammar A = 4 + 2n_d + 3n_t and Z = 2 + n_d + n_t, so N = A − Z = 2 + n_d + 2n_t; every count-based correlate is an invertible relabelling of (Z, N) (NP24-A). Counts are never independent evidence.

**X7. Structural duplication of fields.** `04_Atomic_and_Spectroscopy` (AS01, AS02), `08_Thermodynamics_and_Information` (an empty stub `TD09_Freedom_Ledger_of_Binding`, created by a misdirected write; removal awaits the Operator's approval), `09_Particle_Physics_and_Topology` (NU01, NU02) duplicate numbering of `04_`, `11_` and `02_`. Identifier collisions: two `FLM15` folders, two `GD06` folders, two `NP21` folders.

## 00 — Master Cascade (CLM recompute; Outstanding closure iterations 42, 43, 44)

- Hidden Mechanisms: pre-registration plus script pairs (`clm_cascade_recompute.py`, `outstanding_closure_suite.py`, `run_iteration44.py`); no ledger rows; contents not reviewed in the present pass.
- Assumption Breaks: iteration folders 42–44 ahead of the reset programme imply closure claims with provenance predating the blank-slate rules.
- Leverage Points: re-enter the three iterations through the reset protocol (registration → validation → single pass) before any citation.
- Strategic/IP: no citable status; hold from external use.
- Failure Modes: stale claims propagating through the cascade into field summaries.

## 01 — Foundations and Lattice Mechanics (16 folders; 3 with ledger rows)

- Hidden Mechanisms: FLM15 Casimir push from relay exclusion: net pressure P_net = u_CMB ÷ 3 = 1.3916×10⁻¹⁴ Pa, 1.07×10⁻¹¹ of the ideal plate pressure at 1 µm; E_diff(0) = −π²/360 = −0.027416 in dimensionless units; the force exponent 4.00000000 is geometry of a 1/d⁴ law, shared by the standard result. FLM01 State28D: P_conv 2.46×10⁴⁸ Pa with two normalisation scales not derivable.
- Assumption Breaks: thermal pricing excluded at Round 1 (FLM15 G1); the 1.07×10⁻¹¹ suppression relative to ideal means the SDT push is eleven orders below the measured Casimir force at 1 µm, so the relay-exclusion push reads as eleven orders below the ideal plate pressure at laboratory spacing. FLM02–FLM14 (13 folders) have no reset record.
- Leverage Points: derive the two State28D scales from `law_I` quantities (P_conv, ℓ_P, N) by dimensional closure before any State28D output is reported; run FLM02–FLM14 through the reset protocol in dependency order.
- Strategic/IP: lattice-solver (FLM10 ROOT-SIM) is the only software-grade asset; separate the lattice solver from unproven physics claims in any filing.
- Failure Modes: FLM06 clearing geometry for ℓ_P is a tombstone and stays excluded; 10 of 10 State28D outputs outside 20 % voids any field-solver benchmark.

## 02 — Particle Physics and Topology (16 folders; 9 with ledger rows)

- Hidden Mechanisms: PPT09 classification (Alexander polynomials Δ(2,3) = 1 − t + t², Δ(2,5) = 1 − t + t² − t³ + t⁴; 25 of 25 coprime pairs consistent) is a knot-theory identity, IDENTITY. PPT14: M₀ = 1.786524×10⁻²⁴ kg = 1.0022 TeV; M₀ ÷ m_p = 1.786524×10⁻²⁴ ÷ 1.672622×10⁻²⁷ = 1068.1; the two routes agree because the two routes consume the same P_conv; G3 shared-input. PPT16: τ_pred = 64.3720 ± 0.0104 µs at c/v_circ = 29.300229; fractional offset against the weighted measurement +9.3×10⁻⁵; shared with special relativity.
- Assumption Breaks: PPT12 (lepton moments), PPT13 (pion), PPT15 (handedness) are specification-incomplete: no self-drafting integral, no metastable-rung rule in `law_VI`, an undefined hand-pricing parameter. PPT08 withdrew the sign (annotated 2026-10-07) while retaining c₂ = −0.34796 and ΔE(eq − pol) = −1412.6 Hz = 1.3×10⁻⁶ of 1057.845 MHz. PPT01 carries two protons: W = 3 and (2,3).
- Leverage Points: (a) the winding decision table of X3; (b) PPT12 repair: define the self-drafting integral J_sd = ∮ U·dℓ over the declared wake geometry with an explicit coefficient and register the coefficient before comparing with g = 2(1 + α/2π) = 2 × 1.0011614 = 2.0023228; (c) PPT13: a metastable-winding rule is a new law_VI clause and needs the Operator's ruling, never a fitted rung landing on 273 m_e.
- Strategic/IP: the knot-classification table (PPT09) and the Law V budget (PPT16) are the defensible items; the two items are shared-form and carry no novelty claim.
- Failure Modes: choosing a rung to hit a mass is a census; PPT04's one-sided bound (detection ≥ 10⁻¹¹ µ_B excludes both readings) is the only exclusion-capable result in the field.

## 03 — Electromagnetism (4 folders; 2 with ledger rows)

- Hidden Mechanisms: EMC01 P_eff = m_p² m_e² c⁵ ÷ (4π α ħ³) = 5.227252×10³¹ Pa. The expression contains the measured α, so P_eff is α rewritten in pressure units; the Coulomb-defined comparison agrees within 0.039 % because the definition is shared. EMC02: the elementary unit is an SI-exact bridge and the question dissolved.
- Assumption Breaks: (W+1)_eff = 4.00078 ± 0.00903 is consistent with 4 within 0.00078 ÷ 0.00903 = 0.086 σ; no discrimination.
- Leverage Points: report P_eff as IDENTITY with α as the single calibrated input; EMC03 (repulsion as inverse of convergence) and EMC04 have no record and need a registered observable (a force-law difference at contact) before a run.
- Strategic/IP: no route independent of α.
- Failure Modes: counting P_eff as a derived α (circular).

## 04 — Atomic Physics and Spectroscopy (17 folders; 4 with ledger rows; plus the duplicate `04_Atomic_and_Spectroscopy`)

- Hidden Mechanisms: APS10 dodecardinal solver is native (no wavefunction) but the coefficient forms were isolated against the measured values in earlier work (rewritten-prompt record); first-ionisation errors Z = 2–10: +3.90, −4.85, −5.25, −0.58, +0.17, +0.75, −0.49, −1.48, −1.88 %; sorted absolute values 0.17, 0.49, 0.58, 0.75, 1.48, 1.88, 3.90, 4.85, 5.25 give median 1.48 % (fifth of nine). APS10b: 45 higher ionisations, median 1.62 %, maximum 8.63 %, monotone 45 of 45.
- Assumption Breaks: APS08 (Zeeman) and APS09 (Stark) rest on selection rules and spin algebra (excluded formalism); APS11 seat offsets 0.27, 0.41, 0.45 fm are not constant across H n = 2, H n = 3, He⁺ n = 2.
- Leverage Points: the Operator's isotope hypothesis (deuteron or triton at the valence module position correlating with atomic observables) is testable only with isotope-resolved data. Repository holds per-element ionisation energies (not isotope-resolved), isotope-resolved radii and magnetic moments. Structural table for the tin chain, from n_t = A − 2Z and n_d = 3Z − A − 2 with Z = 50: A = 112: n_d 36, n_t 12; 114: 34, 14; 116: 32, 16; 118: 30, 18; 120: 28, 20; 122: 26, 22; 124: 24, 24 (check Z = 2 + n_d + n_t = 50 at every row). Shell occupancy by the registered schedule (cumulative deuteron capacity 6, 18, 30, 50; triton capacity 8, 18, 30): A = 118 closes the third deuteron shell (n_d = 30) and the second triton shell (n_t = 18) simultaneously; A = 112–116 sit with D20 partial (6, 4, 2) and T10 partial (4, 6, 8); A = 120–124 sit with D12-cuboct partial (10, 8, 6) and T12 open (2, 4, 6). A pre-registered prediction needs the Operator's stated direction and size per observable; the table is the construction input.
- Strategic/IP: ionisation fits to 1.5 % without wavefunctions are a computed capability, tagged COMPUTED, not DERIVED.
- Failure Modes: look-elsewhere across ten tin isotopes and many observables; a direction must be registered first.

## 05 — Nuclear Physics (70 folders; 22 with ledger rows; NSEQ16/18/19 current session)

- Hidden Mechanisms: (1) native mass-defect lists (NP17): d 1.442246, t 6.917143, h 6.935735, α 26.731023 MeV; the neutron term is carried twice on the {2p,2n} list (28.296 MeV for α). (2) The live sequencer builds one alpha 4-ring plus a tree (E = A) and places modules by largest clearance first: extent 12.4 R_p at A = 40 against a close-packed 3.78 + 1 = 4.78 R_p. (3) NSEQ19 contact-only stacking packs 296 of 296 to rms radii 1.04–1.07 × close-packed; (0.7405 ÷ 0.64)^(1/3) = 1.157^(1/3) = 1.050, the random-packing cube root, so the size match is hard-sphere convergence. (4) The r₀-type ratio rises with triton count (+3.8 mfm per triton) where the corpus trend falls (−4 to −11 mfm per triton); a like-contact-allowed control gives +3.2 mfm, excluding like-exclusion as the cause.
- Assumption Breaks: NP12 boundary radius: Z·R_p premise RMS 890.8 % (EXCLUDED), canon law 4.96 %; NP12b required η_d = 0.652 against the NP30 bracket 0.473–0.561; NP12f live construction 27.3 % radius error. NP08: Hoyle offset 379.4524 keV ÷ 7654.2 keV = 0.04957, i.e. 4.96 %. NP16A04: zero-parameter V_disp cross-section 3.1×10⁻⁷ to 2.0×10⁻⁶ mb EXCLUDED on magnitude. NP40: 1235 of 2249 pairs with Q_EC > 0 is 54.9 %; every one of 988 primary EC nuclides positive (known answer met). NP42: the break sits near N* ≈ 80, not at 82. NSEQ18: 23 of 171 binding steps non-positive; 0 of 147 even-even moments vanish; the three-slot cap was absent from the gate. NSEQ16: the nucleon envelope 1.0848 R_p exceeds the NP30 definition (R_p is the extent), the contact test is centre-distance only, and the slip gate cannot fail for any direction.
- Leverage Points: (a) NSEQ19 repair functional E = ½κ Σ|r_i − c|² − ε N_c with ε = αħc ÷ R_p = (197.3270 × 0.00729735 = 1.439965 MeV·fm) ÷ 0.8414 fm = 1.7114 MeV per contact; λ = ε ÷ κ is one CALIBRATED parameter; calibrate on the T8 slope and hold out T10 and the 60 NP12 chains. (b) Required closure tightening: ratio shift −0.0084 to −0.0159 per triton; over 8 tritons at A = 64 (rms_cp = 0.7746 × 4.421 = 3.425 R_p) the rms must fall by 0.23 to 0.43 R_p. (c) Engine repair set (propose-only): degree ≤ 3 gate (applied), envelope ≤ R_p, per-nuclide wake residuals, compact-first placement, contraction applied to geometry, constants traced (X2). (d) The O-18 enumeration (13 of 15 triton-seat pairs build under the sequential docking; refusals are order effects) must be repeated under an order-independent placement before any seat statement is cited.
- Strategic/IP: the three-slot hard-sphere stacker with an independent checker is a reusable verification instrument; no physical claim attaches. Separate the stacker (algorithm) from nuclear interpretation.
- Failure Modes: grammar counts as evidence (X6); sphere stand-ins for a 5544-tour filament (filament radius and packing unspecified: 1386 filaments per 0.06 fm strand gives radius ≤ 0.00077 fm at the hexagonal packing limit); static geometry with no flow, no meshing phase and no internal electron; 22 of 70 folders reset-recorded.

## 06 — Gravitation and Orbital Mechanics (56 folders; 16 with ledger rows)

- Hidden Mechanisms: koppa_Sun = 1476.3512 m (GOM26 calibrated) against 1476.8693 m (holdout): (1476.8693 − 1476.3512) ÷ 1476.3512 = 0.5181 ÷ 1476.3512 = 3.51×10⁻⁴. Two K routes in GOM39 give 1455.637 and 1477.255 m: (1477.255 − 1455.637) ÷ 1476.351 = 21.618 ÷ 1476.351 = 0.01464, a 1.46 % spread. GOM23: g = 9.81828 m/s² against 9.80665: 0.01163 ÷ 9.80665 = 0.001186, +0.119 %. GOM20: net GPS 38.4969 µs/day against engineered 38.5971: 0.1002 ÷ 38.5971 = 0.26 %.
- Assumption Breaks: GOM36/37/25 UNADJUDICATED_BY_SENSITIVITY (X4); GOM38 observable runs 1.1253 × the model range rate; GOM42 P1 great-inequality failure traced to initial conditions; GOM41 Q1 RMS 29.2 % (Earth +0.91 %, Jupiter −0.98 %, Saturn +2.87 %, Mars +22 %, Uranus +66 %, Neptune −18 %) and the displacement-depth profile equals the uniform profile since z = 7×10⁻¹⁰ to 2×10⁻⁸ at planetary surfaces; GOM_DAT9 receiver-tuning offset open.
- Leverage Points: (a) Fisher-bound gate (X4) before any further Doppler or range campaign: required S/N ≥ 3 against 0.691 present. (b) GOM42 successor: ±3000-yr integration, joint linear + quadratic + sinusoid fit, calibrate the linear coefficient only. (c) GOM41: a load- or pressure-scaling engagement variable with the λ-style single parameter held out against Uranus and Neptune. (d) The ODF decode chain (GOM_DAT1–9, validated on known answers) is a finished supplier asset.
- Strategic/IP: GPS clock ledger from one Ѻ without G or M (GOM20, 0.26 %) and deflection to 1.750880 ″ (GOM27) are shared-form with general relativity; defensible as native routes, not as improvements. 40 of 56 folders lack any reset record (56 − 16 = 40).
- Failure Modes: koppa ≡ GM/c² numerically (X1); sensitivity-limited observables; 56-folder breadth with 16 reset records.

## 07 — Cosmology and Redshift (17 folders; 8 with ledger rows)

- Hidden Mechanisms: P₀ = aT₀⁴ ÷ 3 = 1.391594×10⁻¹⁴ Pa, identity 4×10⁻¹⁶ (CR16): restatement of FIRAS. CR03 reduces f = P_eff ÷ P_conv to seat constants plus one class-X input, R_CMB. CR06: fitted exponent n = 0.663 ± 0.036 (K = 1), full-covariance χ² 47.412 against ΛCDM 39.298; K = 2 knots 0.395 and 1.011 give 38.921.
- Assumption Breaks: ΔAIC (K = 1 against ΛCDM, equal parameter count) = 47.412 − 39.298 = +8.114, ΛCDM preferred; K = 2, if the two knot values are free: ΔAIC = (38.921 − 39.298) + 2 × (2 − 1) = −0.377 + 2 = +1.623, ΛCDM still preferred. CR04 targets inconsistent by 9.527×10²⁶ ÷ 4.4×10²⁶ = 2.165. CR09 lowest-z bin residual +0.063 mag (5.4 standard errors) structured. CR14/15 z_rec is CALIBRATED(1) in every ionisation reading.
- Leverage Points: parity table (parameter count, χ², AIC, BIC) for every cosmological comparison with all fitted knots declared; CR03: R_CMB is the framework's one cosmological scale and is recorded as such until a native route (BAO physical shells; N = R_CMB ÷ ℓ_P) is registered with a look-elsewhere count.
- Strategic/IP: no-expansion redshift as octaves is a distinct model; claims of removing dark energy are unsupported while ΔAIC favours ΛCDM.
- Failure Modes: free exponent absorbing structure; saturating-opacity ceilings not yet tied to an observable; CR05 not instrumentable as specified.

## 08 — Galactic Dynamics (10 folders; 1 with ledger rows)

- Hidden Mechanisms: GD03 zk² = 1 to 2×10⁻¹⁶ at six rows is IDENTITY; periapsis v²R/c² = 1.84 × GM/c² (1 + e) is an S2 consistency (one galaxy-scale test).
- Assumption Breaks: the legacy 66 % RMS rotation-curve model (L18) is a tombstone; 9 of 10 folders (rotation curves, lensing, arm topology, baryon inventory) have no reset record, so no current rotation-curve claim stands.
- Leverage Points: single registered rotation-curve test on the SPARC set with the native depth profile fixed before data load, parameter count declared, ΔAIC against a baryon-only baseline.
- Strategic/IP: no strategic content until a rotation-curve run passes a held-out split.
- Failure Modes: circular mock successes; borrowed crossover shapes.

## 09 — Stellar Astrophysics and Radiation (10 folders; 9 with ledger rows)

- Hidden Mechanisms: SAR02 recovers a, σ, b with u_C ÷ u_meas = 1.00000439 from the lattice mode count: the identity of the Planck integral; RC3 met only at R = 204800 after an amendment made after Run 1 (R = 3200 failed).
- Assumption Breaks: SAR04 monotonic k against L not met within FGK (ρ = +0.42 on 123 DUNES stars); SAR03/06 are candidate-fraction censuses; SAR07/08 incomplete; SAR10 deferred. SAR09: steady isotropic absorption excluded at all dust temperatures 100–1500 K (W3 excess 10–340 × allowed); the Round 2 spin-phase instrument failed (n_D = 7 minima, needed 20; planted 0.2 % signal not recovered; P = 0.8962 d against 0.8806 d).
- Leverage Points: SAR09 local-reference redesign (dips on flux against an upper envelope; threshold from point-to-point scatter; per-event rotation phase from adjacent quiet cadences); a discriminating statistic needs a native fine-structure prediction for redirection (owed with the lens-formulation derivation).
- Strategic/IP: redirection against absorption is a testable discriminator only after a prediction exists.
- Failure Modes: post-run amendments; a Rayleigh test on rotation-modulated minima passes under uniform occultation.

## 10 — Fluid Dynamics (12 folders; 1 with ledger rows)

- Hidden Mechanisms: FD12 registration defect: sweep λ/L ∈ [1/4, 16] with ℓ_c = λ*/2 gives L/ℓ_c = 2L/λ ∈ [2 × 1/16, 2 × 4] = [1/8, 8].
- Assumption Breaks: the strong class needs L/ℓ_c ∈ [24, 96]; both pass classes are empty under the sweep.
- Leverage Points: repair sweep λ/L ∈ [2/96, 2/24] = [1/48, 1/12]; planted-optimum validation on a synthetic response curve before the physics sweep (recover λ* to one grid step).
- Strategic/IP: FD01–FD11 (Navier–Stokes from relay, Reynolds transition, Kolmogorov −5/3, Bernoulli, drag, Strouhal, bladeless turbine) are 11 unreviewed claims; no claim is citable.
- Failure Modes: empty pass classes; Bernoulli and drag identities graded as results.

## 11 — Thermodynamics and Statistical Mechanics (9 folders; 2 with ledger rows)

- Hidden Mechanisms: TD09 T_flip = 0.062445 MeV (two routes agree to 3×10⁻¹⁶: shared inputs) shifts to 0.02428 MeV on the native list {p, e, d}: (0.02428 − 0.062445) ÷ 0.062445 = −0.038165 ÷ 0.062445 = −0.611; g_d spread 0.0238–0.0247 MeV. TD01 monotone KL in 8 of 8 but Shannon entropy falls (8.9882 → 8.7018 at β = 0.5).
- Assumption Breaks: TD01 is framed as an arrow of time; the repository rule is movement only, no time direction; the framing needs rewriting before reuse. Old-list Saha weights are imported.
- Leverage Points: replace statistical weights with constituent hand counts stated natively; TD02–TD08 unreviewed.
- Strategic/IP: no strategic content.
- Failure Modes: BBN-band comparison is framework-dependent and was not used as a gate.

## 12 — Condensed Matter Physics (8 folders; 1 with ledger rows)

- Hidden Mechanisms: CM08 gates C0–C6 compare formulas against restatements of the same formulas (Ѻ = N_b Ѻ_b, 1/R² surface acceleration, r⁻³ kernel, flux ∝ count × radius, alignment zero).
- Assumption Breaks: VERIFICATION of identities is not a physics gate; the susceptibility-ratio gate (for example Li against U) is owed with cached data.
- Leverage Points: native circulation and alignment rule stated first; one numeric gate with cascade bands.
- Strategic/IP: superconductivity, band structure, phonons, superfluidity, Hall and ferromagnetism (CM01–CM07) have no record; no claim is citable. Isotope-resolved magnetic and crystallographic prediction (the Operator's per-isotope programme) depends on a construction value law not yet existing.
- Failure Modes: identity gates read as support.

## 13 — Quantum Foundations and Measurement (8 folders; 1 with ledger rows)

- Hidden Mechanisms: QM08 gives only a reading (subset selection over route-definite arrivals).
- Assumption Breaks: no arrival model per gating configuration, no tolerance, no rejection criterion.
- Leverage Points: sequential-occupancy arrival generator (FLM14) with visibility per pairing computed and a tolerance committed first; no wavefunction formalism as scaffolding.
- Strategic/IP: QM01–QM07 (double slit, uncertainty, tunnelling, Born, Bell, spectra, spin) unreviewed in the reset record; no citable claim.
- Failure Modes: narrating results through excluded formalism.

## 14 — Plasma Physics and Magnetism (8 folders; 2 with ledger rows)

- Hidden Mechanisms: PM03 identity 2.2×10⁻¹⁴, V1 8×10⁻²⁵, v_peak/c 0.9959–1.0000; C = 1.05 unstable (Courant-type bound); 3-D cubic C = 1/√3 shows axis-diagonal v_p/c = −2.8×10⁻² at |q| = 1; Lorentz-violation scale at 31 GeV with dx = ℓ_P is dv/c = −1.8×10⁻³⁷.
- Assumption Breaks: PM08 has no native definition of collective connectivity; the loop terms feeding SAR10 are undefined.
- Leverage Points: define the connectivity object as a graph quantity on the NSEQ19 contact graph (degree sequence, component count under a stated cut) and register one observable.
- Strategic/IP: the lattice dispersion bound of 10⁻³⁷ at 31 GeV is a sub-observational claim; no discriminating test.
- Failure Modes: dispersion artefacts of the discretisation read as physics (axis-diagonal anisotropy of 2.8×10⁻²).

## 15 — Optics and Photonics (10 folders; 1 with ledger rows)

- Hidden Mechanisms: OP08 Faraday rotation requires handed-speed splitting under imposed circulation; no model exists; depends on OP01 (matter index) and OP04.
- Assumption Breaks: no tolerance; the Verdet-constant route needs index dispersion data for at least two media.
- Leverage Points: single native definition of hand shared with NP30 §5 and PPT15 (one definition, not two); then Verdet constants for two cached media with tolerance committed first.
- Strategic/IP: OP07 (solar lens artefact falsifier) is the field's one discriminator candidate and is unreviewed; CK01, CK02 unidentified.
- Failure Modes: two incompatible hand definitions.

## 16 — Chemistry and Molecular Bonding (9 folders; 2 with ledger rows)

- Hidden Mechanisms: CH09 gate (correlation ≥ 0.85 with atomic radius) is passed by any Z-monotone trend inside periods: the gate is not a test.
- Assumption Breaks: no native radius definition committed; CH08 (electron affinity) is a specification with no model and no table.
- Leverage Points: commit a native radius definition (outer-seat reach from the dodecardinal solver, the APS10 object), register a held-out period, and use rank statistics within periods plus a between-period jump test (alkali onsets).
- Strategic/IP: CH01–CH07 (bond types, geometry, energetics, spectra) unreviewed.
- Failure Modes: non-discriminating correlation gates.

## 17 — Reactions and Thrust Mechanics (2 folders; 2 with ledger rows)

- Hidden Mechanisms: RTM01 hover g = v_E² ÷ R_E = 9.81828 m/s² (+0.119 %); Sun 274.2783 m/s²; decomposition ratio c² ÷ 2v² to 1.2×10⁻⁹; limb deflection 1.75170 ″ against 1.75169 ″. RTM02 closed ledgers are special-relativistic rocket mechanics in native vocabulary.
- Assumption Breaks: the measured propellant-fraction gate is PENDING_DATA (no cached launch-vehicle mass-ratio set with an independent measured Δv); without independent Δv the test reduces to the rocket equation compared with the rocket equation.
- Leverage Points: dataset with trajectory-measured stage burnout velocities (Saturn V stage masses and burnout velocities from mission reports) cached with provenance; gate: predicted mass ratio from Δv and v_ex within the dataset uncertainty, labelled convergent in advance.
- Strategic/IP: hover price 10^81.87 per day at 4.5 km/s is a ledger identity, not a propulsion advantage.
- Failure Modes: g from the 4-figure engine v_Earth carries about 2×10⁻⁴ rounding.

## Priority queue across fields (Leverage ordering)

1. Winding ruling (X3): unlocks PPT12–15, PPT18, NSEQ16 G8, NP17b.
2. Provenance scan of numeric literals in construction layers (X2).
3. NSEQ19 contact-attraction arm with T8 calibration and T10 plus NP12 chain hold-out (field 05).
4. Fisher-bound gate for all observational campaigns (X4).
5. Re-register FD12, CH09, SAR09 Q3 with the repairs stated above.
6. Reset-protocol entry for the 204 folders without a ledger row, starting with fields at or below 15 % coverage.

## Appendix — verification log

- Pronoun scan: regex over all prose (code spans excluded) for personal, possessive, reflexive, demonstrative, relative, interrogative and indefinite forms; residual matches are determiners, numerals, symbols (He⁺, r_i) and quoted identifiers only.
- Arithmetic recomputed in the text: 87 ÷ 291 = 0.2990; 28 ÷ 125 = 0.224; t_P = 5.39125×10⁻⁴⁴ s; (473.15 − 938.68) ÷ 938.68 = −0.4959; 0.988 ÷ 1.43 = 0.691; (1476.8693 − 1476.3512) ÷ 1476.3512 = 3.51×10⁻⁴; (1477.255 − 1455.637) ÷ 1476.351 = 0.01464; (0.02428 − 0.062445) ÷ 0.062445 = −0.611; 379.4524 ÷ 7654.2 = 0.04957; 9.527 ÷ 4.4 = 2.165; ΔAIC +8.114 and +1.623; icosahedral edge ratio 4 ÷ √(10 + 2√5) = 4 ÷ 3.80423 = 1.05146, neighbour gap 2 × 1.05146 − 2 = 0.1029 (not used above; retained for the 13-sphere cluster back-check in a repository holding the Helix sources).
- Not executed: Helix-side checks (section 4), CONNECTIONS.md back-check (5.1), deployment package (6.2), manuscript (6.1).

# Addendum 2026-10-16-B — unknown and unfinished sections executed (Helix sources, CONNECTIONS ledger, benchmark ledger, Master Cascade)

Sources read: `hsml_os/docs/operators/CONNECTIONS.md`, `shell/lod.hpp`, `core/math/globe.hpp`, `core/math/sdt_metric.hpp`, `scripts/check_spherical_purity.ps1`, `CLAUDE.md`; the `sdt-engine` benchmark source compiled fresh into scratch (`benchfresh/bench_fresh.exe`; repository files untouched); `00_Master_Cascade/*`. No file in `hsml_os` was edited.

## B.1 Hidden Mechanisms

**H1. The prebuilt benchmark executable contradicts the source.**
- `build/Benchmarks/Release/sdt-benchmarks.exe` prints the banner "Five-Law Framework v5.0" and RESULTS 49/65 (75.4 %), 16 failed (B03, B04, B06 ×9, B11 ×2, B14 ×3).
- A fresh compile of `Benchmarks/B01_B25/benchmarks_suite.cpp` prints "Six-Law Framework", 66/66 earned predictions passed, plus 19 construction checks, plus 3 PENDING note-only rows: 66 + 19 + 3 = 88 rows, matching the specification's 88-row ledger. The earlier statement of 66 rows counted earned predictions only.
- Tier tags on the 69 PASS lines with a prediction or pending tag: COMPUTED 30, DERIVED 36, PENDING 3 (30 + 36 + 3 = 69); the remaining 19 rows carry CONSTRUCTION.

**H2. Gate drift between the stale binary and the current source (same row names).**
- B03 H n = 2 fine structure: stale SDT 9.05652×10⁻⁵ eV against EXP 4.528×10⁻⁵ (error 100.0115 %, tolerance 5 %); current SDT 4.52826×10⁻⁵ (error 0.0057 %, tolerance 1 %). The model changed by exactly the factor 2; the tolerance tightened.
- B06 first ionisation: stale He 39.3205 eV (59.92 % error); current He 25.5454 eV (3.90 %); per-row tolerance 5 % → 15 %, with a new whole-range gate (median 1.4769 % ≤ 5 %, maximum 5.2520 % ≤ 15 %). Row Be (5.2520 %) passes the new per-row bar and failed the old.
- B14 R_flat: values identical (Milky Way 6.25, NGC 3198 7, NGC 2403 4.5, M33 4 kpc; errors 4.1667 %, 2.7778 %, 2.2727 %, 0 %); tolerance 1 % → 12 % (a factor 12). Three rows move FAIL → PASS by tolerance alone. The source comment (line 845) justifies "about 12 % for a single-ratio rule".
- B11: stale rows Earth J2 +59.3239 % and Jupiter J2 +202.5760 % (uniform model) are replaced by GOM41 Q1 boundary rows, Earth +0.9098 % and Jupiter +2.1087 %, tagged PENDING PASS at 3 % tolerance. The other four corpus bodies are absent (Mars +22.0 %, Saturn +2.9 %, Uranus +65.5 %, Neptune −18.0 % in this programme's Round 2), and gate 6 as a whole is NOT MET (3 of 6 within 10 %, RMS 29.2 %). Jupiter reference J2 in B11: 0.0146964; NASA-sheet value used in Round 2: 0.014736; (0.014736 − 0.0146964) ÷ 0.0146964 = 0.0000396 ÷ 0.0146964 = 0.00269, a 0.27 % reference disagreement.

**H3. B17 does not discriminate.** Electron g: EXP 2.00231930; SDT 2.00232 (form g = 2(1 + α/2π)); tolerance 0.12 %. The Dirac value g = 2 gives |2 − 2.0023193| ÷ 2.0023193 = 0.0023193 ÷ 2.0023193 = 0.0011583, i.e. 0.1158 %, below the 0.12 % tolerance. The row passes with the entire anomalous moment removed. Tier DERIVED is unearned at this tolerance; the Master Cascade already classes the same quantity EXCLUDED_CIRCULAR (CLM-24: first-order Schwinger term only, higher coefficients imported).

**H4. The stored Planck length carries G numerically.** ℓ_P² c³ ÷ ħ with ℓ_P = 1.616255×10⁻³⁵ m, c = 2.99792458×10⁸ m/s, ħ = 1.054571817×10⁻³⁴ J·s:
- ℓ_P² = 2.612280×10⁻⁷⁰ m²;
- c³ = 2.694400×10²⁵ m³/s³;
- product: 2.612280 × 2.694400 = 7.03853, so 7.03853×10⁻⁴⁵;
- divided by ħ: 7.03853×10⁻⁴⁵ ÷ 1.054571817×10⁻³⁴ = 6.6743×10⁻¹¹ m³ kg⁻¹ s⁻².
The recovered value equals the CODATA gravitational constant. N = R_CMB ÷ ℓ_P (line 252) and koppa_per_baryon = ℓ_P² ÷ proton_wake (line 1059) depend on G through the stored number although the symbol G never appears. Tier of ℓ_P: CALIBRATED against a G-defined external value (FLM06 excluded the derivation; Axiom R1 stands). The Master Cascade entry MM03 ("l_P↔G risk") is confirmed by arithmetic.

**H5. Three time-dilation laws in three places, one definition of z.** `laws.hpp` lines 2647 and 2696: dτ/dt = (1 − z) (Law V budget, REPAIRED). `laws.hpp` line 860 (T11): √(1 − v²/c²). `hsml_os/core/math/sdt_metric.hpp` lines 19–30: 1/√(1 + z), with z·k² = 1 stated in the same header (the same definition of z). `Papers/Depth_Closure_Theorem/02_EPJC_DRAFT.md` line 79: √(1 − z) (stale). First-order deficits: (1 − z) gives z; 1/√(1 + z) and √(1 − z) give z/2.

## B.2 Assumption Breaks

**A1. The Helix metric halves the validated clock term.** With Ω_E = 4.434139×10⁻³ m (GOM20 ledger), R_E = 6.371×10⁶ m and r_GPS = 2.656×10⁷ m:
- z_ground = 4.434139×10⁻³ ÷ 6.371×10⁶ = 6.95988×10⁻¹⁰;
- z_GPS = 4.434139×10⁻³ ÷ 2.656×10⁷ = 1.66948×10⁻¹⁰;
- Δz = 6.95988×10⁻¹⁰ − 1.66948×10⁻¹⁰ = 5.29040×10⁻¹⁰;
- (1 − z) form: 5.29040×10⁻¹⁰ × 86 400 s = 4.5709×10⁻⁵ s = 45.7090 µs/day (equals the GOM20 depth term);
- 1/√(1 + z) form: 22.8545 µs/day;
- difference 22.8545 µs/day × 2.99792458×10⁸ m/s = 6851.6 m of ranging per day.
The branch `if (redshift < -0.9999) return 0.0` returns 0 where 1/√(1 + z) diverges (z → −1), and `redshift < 0` returns 1.0: the guards do not follow the formula. The second-order split between 1/√(1 + z) and √(1 − z) at the Earth's ground is z²/2 = 2.42×10⁻¹⁹, below optical-clock reach (about 10⁻¹⁸). The first-order factor 2 is the testable conflict, and GOM20 already decides the conflict in favour of (1 − z).

**A2. The specification's 13-sphere description contradicts the code.** In `lod.hpp` `cluster()`, all 13 spheres have radius R/3 (r = R(1 − 2t/3) at t = 1); the twelve outer centres stand 2R/3 from the centre along the icosahedron's vertices. Outer-to-centre distance 2R/3 = R/3 + R/3 (touching); outer centre 2R/3 plus radius R/3 = R (touching the seed's surface). The phrase "12 outer 2/3 r spheres" in the specification is the centre offset, not a radius. Adjacent outer spheres: edge ÷ circumradius = 4 ÷ √(10 + 2√5) = 4 ÷ 3.80423 = 1.05146, so the centre separation is 1.05146 × 2R/3 = 0.70097 R against the touching distance 2R/3 = 0.66667 R: a gap of 0.03431 R = 5.146 % of a sphere diameter.

**A3. Recursion changes filled volume and area geometrically.** Volume fraction per level: 13 × (1/3)³ = 13/27 = 0.48148. Similarity dimension ln 13 ÷ ln 3 = 2.564949 ÷ 1.098612 = 2.3347. Surface factor per level: 13 × (1/3)² = 13/9 = 1.44444; at `max_depth` = 6: 1.44444⁶ = 9.0825; volume fraction at depth 6: 0.48148⁶ = 0.012459. The Cauchy proxy radius √(S/4π) of the 13-cluster's summed surfaces is R√(13/9) = 1.2019 R, exceeding the holding sphere; `proxy_of` clamps with `std::min(b->radius, …)`. The sum-of-surfaces rule double counts occluded area (a non-convex union does not satisfy the convex-body Cauchy identity); the clamp hides the excess.

**A4. CONNECTIONS evidence is dated.** 37 rows: Gated 30, Gated (in flight) 2, Runs 2, Not wired 3 (C16, C17, C26). The header records the last review on 2026-10-08 against a dirty working tree. Row C01 states "18 bad samples caught, 10 good passed"; the gate run on 2026-10-16 reports 28 bad caught and 15 good passed, so the evidence column of C01 lags the gate.

## B.3 Leverage Points (solve-first)

**L1. `SDTMetric` repair (propose-only; the Helix repository is not edited).** dilation_factor_from_z(z) = 1 − z for 0 ≤ z < 1; return 0 for z ≥ 1 (Law V budget exhausted: v_trans² = c²(1 − z) = 0); reject z < 0 explicitly. Acceptance test: GPS depth term 45.7090 µs/day for Ω_E = 4.434139×10⁻³ m, tolerance 1×10⁻⁴ relative.

**L2. Benchmark ledger.**
(a) Rebuild or remove the stale `sdt-benchmarks.exe` (removal only on per-item approval).
(b) Restore the B14 tolerance to the registered 1 %, or document 12 % as a pre-registered single-ratio bar with the date and the data justifying the change.
(c) B17: tighten the tolerance below the anomaly, gate ≤ 0.01 % (1×10⁻⁴): g = 2 fails (0.1158 % > 0.01 %) and 2(1 + α/2π) = 2.0023228 passes (|2.0023228 − 2.0023193| ÷ 2.0023193 = 3.5×10⁻⁶ ÷ 2.0023193 = 1.7×10⁻⁶, i.e. 0.00017 %).
(d) B11: list all six corpus rows with signed residuals.

**L3. Provenance of ℓ_P.** Tier ℓ_P as CALIBRATED(1) in the provenance ledger with the arithmetic of H4 attached; keep FLM06 as the record of the failed derivation.

**L4. Amalgamation 5.1: ATOMICUS traction graph × Helix 13-sphere cluster.**
- The engine D12-pre shell (`geometry: 'ico'`, 12 directions) and the Helix icosahedron have identical pair-angle spectra: 30 pairs at 63.435°, 30 at 116.565°, 6 at 180° (computed from both).
- A central sphere with 12 kissing neighbours carries 12 contacts, 4× the three-slot cap (12 ÷ 3 = 4). The nuclear D12 shell therefore cannot be a contact shell around the core; the NSEQ19 stacker agrees, with the 12-unit shell standing off the core.
- Proposal: seed the D12-pre placement of the stacker with the 12 icosahedral directions (already the engine's seat directions) and test whether the 46 first-pass failures (early-shell docking) pack at registered settings. No speed claim before the test.

**L5. Spherical purity numerics (specification 4.1).** float64, r₁ = 6.371×10⁶ m, r₂ = r₁ + 1 m. At Δσ = 10⁻⁷ rad the stable chord (r₂ − r₁)² + 4r₁r₂ sin²(Δσ/2) gives 1.185705 m and the law of cosines gives 1.185854 m (relative error 1.26×10⁻⁴). At Δσ = 10⁻⁹ rad the stable chord is 1.0000203 m and the law of cosines returns exactly 1.000000 m (relative error 2.03×10⁻⁵, the arc term lost). The estimate made beforehand (0.6 % at the first case) overstated the loss; the measured error is 1.26×10⁻⁴. The rule is correct in direction and smaller in size than estimated.

**L6. Hardware grounding (specification 5.2), invention separated from deployment.** Core algorithmic invention: the haversine/chord test and the 13-sphere cluster test. The chord identity needs one sine of Δσ/2, one multiply-add chain and one square root. CORDIC rotation reaches an angular resolution of 2⁻³⁰ = 9.3×10⁻¹⁰ rad after 30 iterations, a pipeline depth of 30 stages before the square root. The cluster test spans 13⁶ = 4 826 809 leaves at depth 6, capped by `LodOptions::budget` (60 000 records). No silicon claim is made beyond these counts.

## B.4 Strategic/IP consequences

- Defensible: the equal-sphere icosahedral cluster with an exact 5.146 % neighbour gap as a LOD primitive (Helix), and the coincidence with the nuclear D12 seat set (SDT); the G-recovery arithmetic as a provenance disclosure, findable by hostile review in minutes.
- Not claimable: derived electron g (B17 passes with g = 2); "zero G" while ℓ_P is the CODATA value; the Helix dilation law as SDT-validated (factor 2 against the GPS ledger).
- Filing posture (conservative lock-down): hold any external statement of the SDT clock law until both repositories agree on (1 − z).

## B.5 Failure Modes

- Cross-repository drift: three clock laws, two reference J2 values, a stale executable.
- Tolerance edits as the route from FAIL to PASS (B14 ×12, B06 ×3).
- The Helix evidence column (CONNECTIONS C01) behind the gate described.
- `hsml_os` carries a separate `CLAUDE.md` rule set and an uncommitted working tree owned by other instances; no edit is made from the current session.

## B.6 Master Cascade (`00_Master_Cascade`): contents and unfinished items

| Item | Terminal class on file (2026-08-11) | Present status |
|---|---|---|
| CLM-12 N·Ω_H limb | EXCLUDED (~10³⁹ ″) | stands |
| CLM-14 Jovian heat | EXCLUDED (scalar 3.7×10²⁵ is not watts) | stands |
| CLM-16 Refsdal 3.25 yr | DOC EXCLUDED (~1 yr) | stands |
| CLM-17, NU01 scalar ν loss | EXCLUDED_MODEL, mechanism UNDERDETERMINED | stands; NU02 (iteration 44) pre-registered, no outcome file |
| CLM-18 limb | CONDITIONAL 1.751 ″ | superseded by GOM27: 1.750880 ″ (COMPUTED, shared-form) |
| CLM-19, CLM-20 | EXCLUDED | stands |
| CLM-24 electron g−2 | EXCLUDED_CIRCULAR | benchmark B17 still tagged DERIVED (H3) |
| MM03 / MM04 koppa origin | PARKED_PERMANENT | strengthened by H4; MM04 outcome absent |
| AS02 native A_s | PARKED_PERMANENT | stands |
| CR01, CK01, CK02 Cherenkov n(ω) | UNDERDETERMINED | no outcome file for CK01 or CK02 |
| NSEQ13, NSEQ14 contact energy | UNDERDETERMINED | hold-out "NSEQ09 SEAL medD = 4.242 MeV" undefined in the present record (also flagged at NSEQ15) |
| GW01 chirp | IDENTITY_DISCLOSED | stands; the 96/5 coefficient is not SDT-derived |
| OM02, OM03, OM04 Cassini | PARKED_PARTIAL_FETCH, DEFINITION_BLOCKED | the GOM_DAT1–9 and GOM37–40 chain now decodes the ODF payload; the RSR payload is still absent; adjudication still UNADJUDICATED_BY_SENSITIVITY |

Unfinished inside the folder: iteration 43 holds a pre-registration only (five claims: MM04, OM03, NU01, CK01, NSEQ13; no script, no assessment). Iteration 44 holds a pre-registration and a 1 051-byte runner with no assessment file (four claims: NU02, CK02, NSEQ14, OM04). Leverage: route the open rows through the reset protocol and do not cite the August terminal classes directly; nine claims have no recorded outcome.

## B.7 Verification log

- Fresh benchmark run: exit 0; 66/66 earned, 19 construction, 3 PENDING note-only. Stale binary run: exit 1; 49/65.
- Purity gate `-SelfTest`: "28 bad samples caught, 15 good samples passed".
- Pair-angle spectra (node; engine `completeShellDirections` against Helix `icosahedron()` rebuilt from the header): both {63.435° ×30, 116.565° ×30, 180° ×6}.
- Arithmetic recomputed above: G = 6.6743×10⁻¹¹; 45.7090 and 22.8545 µs/day; 6851.6 m/day; 0.1158 % for g = 2; 13/27, 13/9, ln 13 ÷ ln 3.
- Pronoun scan repeated on this addendum; residual matches are determiners and symbols only.
