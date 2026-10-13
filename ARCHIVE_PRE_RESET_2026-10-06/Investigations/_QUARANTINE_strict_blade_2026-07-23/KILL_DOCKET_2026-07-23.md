# KILL DOCKET — dual-front re-audit work list (2026-07-23)

**Consumed by BOTH fronts:** the strict twin (Method A, external instance — see
`STRICT_TWIN_2026-07-23/TWIN_WORK_ORDER.md`) and the recovery front (Method B, main session).
Each front processes the same 18 active items independently; verdicts meet only at reconciliation.

**This file is deliberately outcome-free.** It states what was killed and where the primary
evidence lives — never what any re-examination concluded. The `reg?` column says only whether the
item appears in the kill re-adjudication register (Method-B-side reading only; the twin does not
open the register). Rule for every row, both fronts: **READ THE SOURCE** — rule on the primary
files listed, never on this docket's one-line summaries.

**Classes:** `DN` = data-negative (real data contradicted the claim) · `ST` = strict-technicality
(killed on a purity rule — circularity, borrowed crossover, calibration taint, degeneracy,
unfalsifiability-as-posed) · `PART` = partial (headline passed, named sub-target failed).

**Scope rule (Harvey, 2026-07-23):** DN, ST, and PART kills are auditable. **Fabrications are
permanently excluded** (§X1) — nothing under an invented number re-opens, on either front.

All paths relative to repo root. Data paths are sha256-manifested in `Datasets/MANIFEST.md`
(verify hash before use — OneDrive staleness).

---

## Tier 1 — campaign-adjacent (data in hand; highest value)

| ID | item | class | reg? | killed claim (one line) | primary sources | data |
|---|---|---|---|---|---|---|
| D01 | GD05 / E46 galaxy rotation | DN | n | canonical 3D eclipse model fails real SPARC rotation curves (RMS 66%); earlier "success" traced to a circular mock; twin-regime variant rode a borrowed MOND crossover | `Investigations/08_Galactic_Dynamics/GD05_Galaxy_Rotation_Curves/` · `Experiments/E46_Galaxy_Rotation_Curves_from_Eclipse_Saturation/` | `Datasets/stellar/SPARC_full_175.mrt` + `SPARC_meta.txt` |
| D02 | CR10/CR11/CR12 + E42/E49 distance-law cluster | DN | n | cubic-redshift/EdS distance law loses to ΛCDM on Pantheon (ΔAIC ≈ 90); dark-energy-dissolution claim degenerate with expansion | `Investigations/07_Cosmology_and_Redshift/CR10_Cubic_Redshift_Volumetric_Rung/` · `CR11_Reciprocity_and_the_Tolman_Test/` · `CR12_Pantheon_Distance_Law/` · `Experiments/E42_Hubble_Constant_from_Pressure_Gradient/` · `Experiments/E49_Dark_Energy_as_Residual_Pressure_Gradient/` | `Datasets/cosmology/PantheonPlusSH0ES.dat` |
| D03 | CR08 BAO standing waves | DN | n | static exponential-strain BAO law: χ² = 131.7 vs ΛCDM 8.2; CMB acoustic angle off by ×2.21 | `Investigations/07_Cosmology_and_Redshift/CR08_Pressure_Gradient_Redshift_and_BAO/` | in-folder inputs (no BAO table cached; see MUST-FETCH) |
| D04 | CR09 H₀ / dark-energy gradient | DN | n | isotropic radial κ-gradient account of the Hubble tension killed 0/122 by the exact pincer test | `Investigations/07_Cosmology_and_Redshift/CR09_Hubble_Tension_and_Dark_Energy/` | `Datasets/cosmology/PantheonPlusSH0ES.dat` |
| D05 | E106 lumiopause first data test | DN (marginal) | n | derived 20,857 AU lumiopause predicted an aphelion pile-up; first test on osculating aphelia (4069-comet JPL SBDB pull) showed a 3–10k AU peak declining smoothly through 20,857 — no pile-up; osculating-vs-original 1/a and a-vs-Q ambiguities unresolved in that test | `Experiments/E106_Oort_Cloud_Lumiostasis/` | `Datasets/solar_system/JPL_SBDB_comets.json` · MUST-FETCH F3 (original 1/a) |
| D06 | E107 / GOM07 redshift fork | ST/DN | n | the +6.6 vs +3.7 m/s Jovian H₃⁺ fork collapsed: under depth-closure ϟ ≡ GM/c², both frameworks give ~5.9 m/s; the claimed 1.8× split was asserted, not derived. Open question for audit: can ϟ_J be derived from surface kinematics ≠ GM_J/c²? | `Experiments/E107_Reflected_Light_Gravitational_Redshift_Fork/` · `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM07_Reflected_Light_Gravitational_Redshift/` | none needed (derivation audit) |

## Tier 2 — register-queue obligations

| ID | item | class | reg? | killed claim (one line) | primary sources | data |
|---|---|---|---|---|---|---|
| D07 | NP12 / E33 charge-radius scaling | DN | y | linear law R = Z·R_p: 890.8% RMS against 908 measured radii | `Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/` · `Experiments/E33_Nuclear_Charge_Radius_Scaling__Z__Rp/` | `Datasets/nuclear/IAEA_ground_states_radii.csv` |
| D08 | NP06 gear-frequency binding | ST | y | gear-frequency binding functional killed in the agent wave | `Investigations/05_Nuclear_Physics/NP06_Gear_Frequency_Binding_Functional/` | `Datasets/nuclear/AME2020_mass_excess.txt` |
| D09 | NP21 binding-curve resistance landscape | ST | y | geometric-floor resistance landscape killed in the agent wave | `Investigations/05_Nuclear_Physics/NP21_Binding_Curve_Resistance_Landscape/` | `Datasets/nuclear/AME2020_mass_excess.txt` |
| D10 | CR06 emission/propagation split | ST | y | redshift emission-vs-propagation split falsified in the agent wave | `Investigations/07_Cosmology_and_Redshift/CR06_Redshift_Emission_Propagation_Split/` | in-folder inputs |
| D11 | SAR04 main-sequence k-gradient | ST | y | L ∝ M^3.5 emergence claim killed (ordering claim survives on file) | `Investigations/09_Stellar_Astrophysics_and_Radiation/SAR04_Stellar_Main_Sequence_k_Gradient/` | `Datasets/stellar/stellar_partial.csv` |
| D12 | PM02 Faraday/Lenz from changing swirl | ST | y | induction-from-swirl mechanism killed in the strike-force wave (executor was agent class) | `Investigations/14_Plasma_Physics_and_Magnetism/PM02_Faraday_Induction_and_Lenz_from_Changing_Swirl/` | in-folder inputs |
| D13 | OP07 solar lens artifact | ST | y | multi-λ lens-artifact experiment killed; the kill itself produced a corrected experiment design (monotone R(λ) + limb pile-up) — audit whether the kill or only the correction stands | `Investigations/15_Optics_and_Photonics/OP07_Solar_Lens_Artifact_Experiment/` | in-folder inputs |

## Tier 3 — nuclear data-negatives, cross-checks, partials

| ID | item | class | reg? | killed claim (one line) | primary sources | data |
|---|---|---|---|---|---|---|
| D14 | NP09 / E29 deuteron binding from occlusion | DN | y | occlusion route to the 2.224 MeV deuteron binding missed by −97.3% | `Investigations/05_Nuclear_Physics/NP09_Deuteron_Binding_from_Occlusion/` · `Experiments/E29_Deuteron_Binding/` | `Datasets/nuclear/AME2020_mass_excess.txt` |
| D15 | NP14 / E39 p–n mass difference | DN (partial) | n | sign and mechanism earned; magnitude off −23.3% (cascade root logged as RESISTANCE-MAGNITUDE) | `Investigations/05_Nuclear_Physics/NP14_Proton_Neutron_Mass_Difference/` · `Experiments/E39_Proton_Neutron_Mass_Difference_from_Topology/` | `Datasets/nuclear/AME2020_mass_excess.txt` |
| D16 | NP05 Gate G1 price of displacement | ST | y | linear E = price × volume-deficit functional failed Gate G1 (price constancy, spread 45.4×) and G4 (blind-predict); halt ruled | `Investigations/05_Nuclear_Physics/NP05_Gate_G1_Price_of_Displacement/` (frozen stages + `sealed/answers.json` — fully re-executable) | in-folder volumes |
| D17 | NP15 + NP28 moment/magnetism cluster | ST | y | NP15: vortex-route magnetic moments bracket Schmidt-line values (−9.4% / +11.0%) without predicting them; composites degenerate beyond A=4. NP28: intrinsic-spin sufficiency falsified; arrangement-moment model failed blind (cc = −0.40) | `Investigations/05_Nuclear_Physics/NP15_Nuclear_Magnetic_Moments_from_Vortex/` · `Investigations/05_Nuclear_Physics/NP28_Spin_vs_Arrangement/` | `Datasets/nuclear/NUBASE2020.txt` · `Datasets/nuclear/magnetic_moments_compact.txt` (unparsed snapshot — OBSERVED anchors only) |
| D18 | GOM09 / E97 Earth-core seismic | PART | y | interior g(r) matched PREM at 1.82% RMS, but the named seismic targets failed their own gate (v_p 11.5%, v_s 28.0%) | `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM09_Earth_Core_Seismic_Speed/` · `Experiments/E97_Earth_Core_Seismic_Speed_from_Lattice_Compression/` | MUST-FETCH F7 (PREM) — until cached, audit-only |

---

## §X1 — FABRICATIONS: permanently excluded (both fronts, no exceptions)

Harvey decision 2026-07-23: an invented number has nothing underneath it to recover; re-opening
fabrications is how laundering restarts. **Do not audit, do not recover, do not cite as
precedent:** APS04 (Lamb 1051.8), CR05 (hardcoded H₀), PPT08A (frozen solver), PPT09
(verdict-over-tool), OP01 (retro-loosened gate), Hubble/17_Pantheon_Proof (rank-1 retro-relabel),
PV_canon μ_n (target-in/target-out), B04/laws.hpp Lamb literal (already removed), and GD04
(banner-over-FAIL — fabrication taint controls over its ST features).

## §X2 — Already taken through direct supervised re-adjudication: not in this wave

SAR03, QM05, GOM16 — each already received a direct (non-agent) re-examination cycle; details
are Method-B-side (register). Excluded to avoid conflicting rulings on directly-adjudicated
items. The twin does not process these.

## §X3 — Deferred to wave 2 (with re-entry triggers)

| item | one-line reason | re-entry trigger |
|---|---|---|
| E99 tidal Q=2.31 | calibration-taint audit needs tidal harmonic data | MUST-FETCH F8 cached |
| E83 lattice resonance | voided as *unfalsifiable-as-posed* — needs a native re-draft, not an audit | QM02-family relay-floor rewrite |
| NP10 saturated-occlusion wall | structural kill; surviving (Z−1)! tour lock is OPEN, not killed | new carrier for the wall claim |
| NP13 / E35 Fe-56 vs Ni-62 | thesis unsupported on first run | new grammar-efficiency observable |
| NP20 binding closure | closure false with 2 knobs — OPEN, not cleanly killed | knob-closure derivation |
| GOM01 factor-4 | PARTIAL (transfer function un-derived) | occlusion transfer-function derivation |
| GOM10 / GOM12 input precision | PARTIAL — near-certain to clear with ephemeris-grade inputs | ephemeris-grade rerun |
| GOM13 Cavendish altitude | narrow-scope ruling on file; surviving count-typed G2 unmeasurably small | measurable G2 route |
| SAR01 Le Sage thermal | kill stands on file at ×2.3e17; scope refinement already recorded | buffer-class carrier |
| FLM06 seed theorem | standing narrow-scope ruling with a named re-open trigger | FLM14 action-per-turn carrier |
| E102 near-Sun leg | degenerate with GR by design (consistency test, not a fork) | §6 discriminators via E106/E108 |
| E104 Casimir–Cavendish hybrid | corrected amplitude ~1e-9, below lock-in floor | reachable-amplitude redesign |
| E109 dip laws (λ∝R^⅓, λ∝ϟ) | voided inside E109 §11–12; the exact-number FIR minimum is separate and live | new cross-stellar sample with resolved minima |

---

*Docket assembled 2026-07-23 from the kill records themselves (verdict files, run logs, register
row existence). Both fronts: the one-liners above are indexing aids, not evidence — the ruling
material is the primary sources column.*
