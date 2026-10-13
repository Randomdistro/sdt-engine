# GD03 (galactic spation topology) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gd03_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GD03/PROMPT.md` (the zone table, the four closure levels, the structural requirements, the prohibited inputs, the adversarial tests, the audit correction; the per-zone prose of Zones 1–12 and sections 4, 7, 8 were not read in full); `laws.hpp` (`bridge::k_hydrogen`, `k_proton_surface`, `k_Earth`, `k_Sun`, `koppa_*`); the GOM25 record of this programme (the domain rule 0 ≤ z < 1) and the GOM23 record. Not read: `VERDICT.md`, `RUN_LOG.md`, `*.cpp`, the result files. Exposure: the audit correction states the earlier outcome (Level 3 fails at Sgr A*; Level 4 fails its own anchors; the tool's banner printed PASS).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | Level 1 (zk² = 1) is an identity when z = (v/c)² and k = c/v are both made from the same v; the prompt says so ("trivially true by construction"). It is not a test at any zone. (It is a test only where z is spectroscopic and k dynamical, independent chains, as in GOM25; not in this table.) |
| D2 | gating | Level 2 (the same Ϟ from any probe distance) and Level 3 (parent invariance from at least 3 independent probes with σ/μ < 1%) need observed orbits or rotation curves: eight planetary elements, the S-star orbits (with a distance), the Milky Way rotation curve, Laniakea probes. None is local as observation; the local `SDT_ephemeris.csv` is a model output of the earlier solar-system programme, not an observation, and using it as a probe would be circular. PENDING with named data. |
| D3 | gating | Level 4 asks for a derivation: the contact-drag coefficient of the shell-by-shell wake "determined by the 12-around-1 packing geometry and the octahedral gap mobility", then the aggregation of about 10⁶⁸ baryons into a rotation curve. The prompt names the coefficient as "the key unknown". No derivation exists to run; the level is OWED, and the earlier banner "Level 4 PASS — proves flat rotation" had no basis. |
| D4 | premise | Zone 1 has z = 1/k² = 3.35 at the proton surface (k = 0.5464, v = 1.83c). The single-formula requirement (3.7: z = (v/c)² from the proton interior to the Clearing) places z > 1 inside the proton. The propagation profile c(1 − z)² used elsewhere in the framework is defined only for 0 ≤ z < 1 (GOM25 decision 5). The requirement and the domain rule cannot both hold at Zone 1. Recorded as a tension to be resolved by the author, not decided here. |
| D5 | premise | The prompt describes the dipole component of the wake with a word on the banned list (active prose, `GATEWAY_BEHAVIOURAL.md` §1). It is not repeated here; "ℓ = 1 component" is used. The identification of the ℓ-components with electricity, magnetism and bonding are assignments (classifications), not computed. |
| D6 | construction | τ = 1/3 (3.5) is the identity τ = 1/d in d = 3; a check of arithmetic. The force-law scale invariance (3.6) lists four cases whose "correct force" is the quantity the case is built from (g from ϟ_Sun, Coulomb from R_charge): circular. |
| D7 | gating | The measurable gap in the audit correction ("flat rotation curves and the central S-star convergence from koppa depths alone, with a koppa census that is not circular") is a statement of the whole programme. The rotation-curve part belongs to GD05/GD06 (SPARC); the S-star part needs orbital elements. Not decidable here. |
No downgrade is made on agreement grounds.

## 2. Registered quantities and outputs (fixed before the run)
**Run.** (a) The zone table for the engine-defined and the labelled-observed boundaries: v, k = c/v, z = (v/c)², Ϟ = v²R/c², zk² to 12 significant figures. Engine rows: hydrogen ground state (v = αc, R = a₀), proton surface (k = `k_proton_surface`, R = `R_p`), Earth surface (`v_Earth`, `R_Earth`), Sun surface (c/`k_Sun`, `R_Sun`). Observed rows (labelled OBSERVED, typed): Milky Way at the solar circle (v = 220 km/s, R = 8 kpc, IAU conventions), S2 at periapsis (v ≈ 7650 km/s, R = 120 AU). (b) The domain gate of GOM25 (0 ≤ z < 1) applied to every row. (c) τ = 1/d for d = 1, 2, 3 as arithmetic. (d) The banner computed from the gate results by code: Level 1 met (identity); Level 2, 3: PENDING; Level 4: OWED; Conditions B (τ), C (bonding overlap), D (z continuity) status.
**Validations.** V1: zk² = 1 to 12 digits for synthetic velocities spanning 10⁻⁸c to 1.8c. V2: `k_hydrogen` equals 1/α and `koppa_hydrogen` equals α²a₀ in `laws.hpp`.
**Gates.** Condition A (closure): zk² = 1 to 10⁻¹² at every row (identity). Condition B (τ = 1/3): arithmetic. Condition C (bar–arm bonding overlap > 0): no definition of the overlap in the portion read: not run. Condition D (z continuous, one formula): z = (v/c)² is one formula by construction; the domain rule fails at the proton surface (D4).
**Expected landing.** All zk² = 1 (identity); the proton-surface row has z = 3.35 and fails the domain gate; Levels 2–3 PENDING; Level 4 OWED; the banner prints "Level 1 identity only".

## 3. Results (COMPUTED; instrument `gd03_reset_1.cpp`, output `gd03_reset_1_results.txt`; single pass, no amendment; validations met)
**Validations.** V1 met (zk² − 1 = 2.2×10⁻¹⁶ over v = 10⁻⁸c … 1.8c); V2 met.
**Zone table.** | boundary | source | v/c | k | z | Ϟ = v²R/c² (m) | zk² | 0 ≤ z < 1 |
|---|---|---|---|---|---|---|---|
| hydrogen ground state | engine | 7.297353×10⁻³ | 137.036 | 5.325×10⁻⁵ | 2.817940×10⁻¹⁵ | 1.000000000000 | yes |
| proton surface | engine | 1.830057 | 0.546431 | 3.349109 | 2.817940×10⁻¹⁵ | 1.000000000000 | **no** |
| Earth surface | engine | 2.638×10⁻⁵ | 37 905.2 | 6.960×10⁻¹⁰ | 4.434139×10⁻³ | 1.000000000000 | yes |
| Sun surface | engine | 1.457×10⁻³ | 686.3 | 2.123×10⁻⁶ | 1.477046×10³ | 1.000000000000 | yes |
| Milky Way, solar circle | OBSERVED (220 km/s, 8 kpc) | 7.338×10⁻⁴ | 1362.7 | 5.385×10⁻⁷ | 1.329366×10¹⁴ | 1.000000000000 | yes |
| S2 at periapsis | OBSERVED (~7650 km/s, ~120 AU) | 2.552×10⁻² | 39.19 | 6.512×10⁻⁴ | 1.168929×10¹⁰ | 1.000000000000 | yes |
Five of six rows lie in the domain; the proton-surface row (z = 3.349) does not. τ = 1/d: 1, 0.5, 0.333333 (arithmetic).
**Observations from the table (not gates).** (i) The proton-surface Ϟ equals r_e exactly because `k_proton_surface = (1/α)√(R_p/a₀)` is built from a₀ and α: Ϟ = R_p/k² = α²a₀ by definition, so the hydrogen and proton rows agree by construction, not by measurement. (ii) The S2 row's instantaneous v²R/c² (1.17×10¹⁰ m) is 1.84 times the orbital invariant GM/c² for a 4.3×10⁶ M☉ centre (6.4×10⁹ m): for an ellipse v²r_p = GM(1 + e) with e ≈ 0.88; the same epoch dependence as the Earth's 1.2% in GOM25. A Level-3 probe from an eccentric orbit must use the Kepler invariant (4π²a³/(T²c²), with π from the period, a sampling geometry), not the instantaneous v²R/c².
**Banner (computed from the gate results).** Level 1: met (identity by construction, not a test). Level 2: PENDING. Level 3: PENDING. Level 4: OWED. Condition A: met (identity). Condition B: arithmetic. Condition C: not defined in the portion read. Condition D: the single formula z = (v/c)² gives z > 1 at the proton surface and the (1 − z)² profile domain rule rejects it (tension).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Level 1, Condition A | **VERIFICATION (identity)** | zk² = 1 from one v; not a test (D1) |
| Level 2 | **PENDING** | needs observed multi-distance probes |
| Level 3 | **PENDING** | data requirements named below; the local ephemeris is a model output |
| Level 4 | **OWED** | the contact-drag coefficient is the named unknown (D3); no derivation to run |
| Condition B (τ = 1/3) | **VERIFICATION (arithmetic)** | 1/d (D6) |
| Condition C | **not run** | overlap undefined in the portion read |
| Condition D (one formula, continuous z) | **G2, tension** | z > 1 at the proton surface against the (1 − z)² domain rule (D4) |
| Audit correction (banner from gate results) | **done** | the banner is computed by code |
| Measurable gap (flat curves and S-star convergence, non-circular census) | **OWED** | rotation curves belong to GD05/GD06; S-star orbits need elements with a distance |

## 5. Data requirements and direction
1. Level 3, solar system: observed semi-major axes and sidereal periods of the eight planets from a stated primary source (not the model ephemeris), giving Ϟ = 4π²a³/(T²c²) per planet; expect scatter at the 10⁻³ level ordered by planet mass (the parent Ϟ includes the planet).
2. Level 3, Sgr A*: orbital elements (a, P) of at least three S-stars with their uncertainties and the common distance; Ϟ ∝ D³, so the scatter across stars tests the elements only.
3. Level 3, disk: a rotation curve at R = 3–15 kpc from a stated primary source; the enclosed Ϟ(R) = v²R/c² is monotone for any non-decreasing v R, so the test needs a stated falsifier beyond monotonicity.
4. Level 4: derive the drag coefficient from the lattice before any aggregation; resolve the z > 1 tension at Zone 1 (D4).

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
