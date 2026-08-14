# Master-Protocol Coverage Ledger — 2026-08-07

## Scope declaration

This ledger starts execution of the user-supplied **SDT Total Research,
Falsification, Reformulation, and Empirical Coverage Protocol**.  It records
what was actually inspected and what remains queued.  It must not be read as a
claim that every file has received a line-by-line scientific review.

The repository contains **2,307 tracked files**.  A complete tracked-path
inventory and root-level grouping were generated before choosing the first
test.  The largest groups are `Investigations` (1,204 paths), `ATOMICUS`
(465), `Release` (158), `docs` (131), `Experiments` (107), `Hubble` (52), and
`Datasets` (43).  Release and `docs` trees are treated as derived mirrors until
their source of record is identified; they cannot independently validate a
claim.

## Rules applied in this run

1. Use only measured or observational inputs for empirical comparison.  A
   published fit or ephemeris is permitted only with its processing dependency
   recorded.
2. Do not reject an SDT claim because another framework uses different terms.
   Test the mechanism that SDT actually states, with independently observed
   targets.
3. A calculation of an expected value from an input inserted by the model is
   not a measurement and cannot be labelled a successful prediction.
4. Preserve negative results, state the error origin, and distinguish
   `FORMAL`, `UNADJUDICATED`, `PENDING_DATA`, `EXCLUDED`, and `SUPPORTED`.
5. No canonical law is edited by this audit.  Proposed repairs belong in an
   investigation record and require the repository's propose-and-wait process.
6. **Codebase audits are not inputs.** Prior audit Markdown, agent synopses, and
   internal verdict ledgers are provenance or session outputs only. They do not
   supply measured values, claim statuses, tolerances, or rejection criteria.
   Admissible inputs are: frozen datasets with checksums, `laws.hpp` (as the
   hypothesis under test), and direct instrument stdout from this session.

## Read coverage: active solar-propagation claim graph

The following sources were read because they state, implement, or consume the
solar propagation mechanism selected for the first cycle:

| Node | Source of record | Status | Finding relevant to this run |
|---|---|---|---|
| Depth definition | `Engine/include/sdt/laws.hpp` | read | `z = koppa/r` and `koppa = v^2 R/c^2` are the implemented mechanism. |
| Propagation profile | `Engine/include/sdt/laws.hpp` | read | Adopted profile is `c_far = c(1-z)^2`; its stated domain is not guarded in code. |
| Timing observable | `Engine/include/sdt/laws.hpp` | read | `shapiro_delay()` implements the leading-order logarithmic expression. |
| Prior timing audit | `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM22_Shapiro_Velocity_Profile/` | read | Its asserted observed delay is calculated from `GM_Sun/c^2`, not retrieved timing data. |
| Redshift claim | `Papers/Depth_Closure_Theorem/00_THREAD_DISTILLATION.md` | read | Claims solar spectral shift equals the surface depth. |
| Prior redshift test | `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM07_Reflected_Light_Gravitational_Redshift/` | read | Correctly documents a reflection degeneracy; it does not independently establish the solar amplitude. |
| Solar optics/lensing | `Experiments/E109_Solar_Spectral_Prism/` and `Investigations/15_Optics_and_Photonics/OP07_Solar_Lens_Artifact_Experiment/` | indexed | Scheduled for the next mechanism branch after timing-data readiness is settled. |

## Whole-repository routing

| Repository region | Role in the master protocol | Current state |
|---|---|---|
| `Engine`, `Laws`, `Theory`, `Papers` | candidate axioms, equations, and claim provenance | source-map scan started; active solar chain read |
| `Investigations`, `Experiments`, `Hubble` | prior tests, counterexamples, and executable instruments | all paths inventoried; solar chain read first |
| `Datasets` | provenance, frozen raw inputs, manifests | catalog and fetch rules read; new dataset root pre-registered |
| `Benchmarks` | assertion and circularity audit | inventory only this cycle; no status imported from prior audit prose — detox requires direct row re-trace |
| `ATOMICUS`, `Compiler`, `Release`, `docs` | independent source or generated/distribution material | inventory complete; deduplication/source-of-record audit queued |

## First falsification loop

`GOM25_Solar_Depth_Propagation_Audit` is the first bounded loop.  It was chosen
because it connects an independently observable orbital state, a surface
spectral observable, and a claimed non-local propagation marker.  Its
pre-registration fixes inputs and decision rules before any new external data
are downloaded.

## Known false or overstated statements retained for audit

1. GOM22's wording that a 247.24 microsecond value is "measured" is false in
   that instrument: line 55 computes it from a `GM_Sun` input and the same
   propagation expression under test.  Origin: target construction rather than
   data ingestion.  Corrective action: treat GOM22's numerical comparison as
   `FORMAL` only and retrieve a traceable timing dataset before an empirical
   verdict.
2. The current exact profile and its leading-order timing function are not the
   same expression.  Origin: an `O(z^2)` expansion is described as an exact
   empirical reproduction.  Corrective action: numerically integrate the
   adopted profile and report approximation residue separately.
3. The inverse `depth_from_c_far()` uses the principal square root without a
   documented `0 <= z <= 1` domain guard.  Origin: an inverse branch is offered
   beyond the physical domain.  Corrective action: test boundary and
   out-of-domain behaviour; do not silently extend it.

## Next gate

No empirical result will be declared until the GOM25 pre-registration is
written, external observations are frozen with checksums, and the instrument
is independently recomputed from those files.

## Gate cleared — Iteration 1

Pre-registration, dataset freeze (`Datasets/solar_propagation_2026-08/MANIFEST.md`),
instrument validation, and direct execution are recorded in:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM25_Solar_Depth_Propagation_Audit/GOM25_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_1_2026-08-07.md`

Headline: spectral amplitude COMPATIBLE but UNADJUDICATED for mechanism
confirmation; Shapiro-like marker PENDING_DATA; instantaneous koppa IC debt
PARTIAL; `c_far` domain unguarded FORMAL DEFECT.

## Gate cleared — Iteration 2

GOM25 §19 reformulation re-audited as GOM26 (orbital-invariant ϟ):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM26_Solar_Koppa_Orbital_Invariant/GOM26_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_2_2026-08-07.md`

Headline: Keplerian invariant `ϟ = μ/c²` collapses CV ~1.18% → ~1×10⁻⁵
(C1/C2 PASS); INTRA_YEAR hold-out PASS; spectral still COMPATIBLE/UNADJUDICATED;
D4 still PENDING_DATA; multi-year Sun-centered hold-out OPEN (Horizons API /
wrong-center incidents). IC recovery: RECOVERED at investigation level. No canon edit.

## Gate cleared — Iteration 3

Shared-profile deflection with frozen GOM26 ϟ (GOM27). Audits not used as inputs.

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM27_Solar_Deflection_Shared_Profile/GOM27_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_3_2026-08-07.md`

Headline: COMPUTED δ(b) ledger (limb 1.750844″); whole-range empirical
PENDING_DATA (Fomalont products MODEL-PROCESSED); D4 still PENDING_DATA.

## Gate cleared — Iteration 7

GOM26 multi-year C4 on frozen 2024 EMB(3)–Sun(10) Horizons vectors:

- `Audits/MASTER_PROTOCOL_ITERATION_7_2026-08-07.md`
- `.audit-tmp/gom26_multiyear_run.txt`

Headline: `|Δϟ|/ϟ = 3.51×10⁻⁴ < 10⁻³` → COMPATIBLE (DE441 construction check).

## Gate cleared — Iteration 8

Cassini ODF structural path (alternate to TDF):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM28_Cassini_ODF_Structural_Census/GOM28_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_8_2026-08-08.md`

Headline: ODF **STRUCTURE_PASS**; residual still PENDING_DATA; TDF remains
STRUCTURE_PARTIAL.

## Gate cleared — Iteration 9

ODF orbit-data field census (metadata only):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM29_Cassini_ODF_Field_Census/GOM29_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_9_2026-08-08.md`

Headline: **FIELD_CENSUS_PASS** — 7447× two-way Doppler (type 12), FORMAT ID 2,
DSS-25, ~2 h on 2002-157. Residual still PENDING_DATA.

## Gate cleared — Iteration 10

ODF observable Hz decode + multi-day freeze list:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM30_Cassini_ODF_Observable_Decode/GOM30_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_10_2026-08-08.md`

Headline: **OBSERVABLE_DECODE_PASS** (median obs ≈ 50.244 kHz); 7/8 multi-day
ODFs PENDING_FETCH; residual still PENDING_DATA.

## Gate cleared — Iteration 11

Multi-day CORS_0021 ODF decode (local `v10` volume):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM31_Cassini_ODF_Multiday_Decode/GOM31_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_11_2026-08-08.md`

Headline: **MULTIDAY_DECODE_PASS** — 8/8 ODFs HAVE; 451022 rows decoded;
GOM30 PENDING_FETCH cleared; residual still PENDING_DATA / PENDING_RECONSTRUCTION.

## Gate cleared — Iteration 12

ODF observable unit-path adjudication:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM32_ODF_Observable_Unit_Path/GOM32_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_12_2026-08-08.md`

Headline: **UNIT_PATH_ENGINEERING_DOPPLER_HZ** — Items 4–5 are engineering
Doppler (kHz class), not µHz ODP residuals; predicted-Doppler residual still
PENDING_RECONSTRUCTION.

## Gate cleared — Iteration 13

Geometric predicted Doppler magnitude gate:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM33_Predicted_Doppler_Geometry/GOM33_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_13_2026-08-08.md`

Headline: **GEOM_DOPPLER_MAGNITUDE_PASS** — `|f_geom|/|obs|` ≈ 3.37 on P0;
solar **K** frozen/unused; station/ramp residual still PENDING_RECONSTRUCTION.

## Gate cleared — Iteration 14

DSS-25 station LOS + band/turnaround fidelity (now `GOM_DAT7`):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT7_Station_Doppler_Fidelity/GOM_DAT7_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_14_2026-08-08.md`

Headline: **STATION_DOPPLER_FIDELITY_FAIL** — station LOS ruled out as ~3.4× gap
source; \|corr(obs,f_pred)\|≈0.9996; scale≈−0.295 diagnostic.

## Gate cleared — Iteration 15

Discrete documented scale/sign hypotheses (now `GOM_DAT8`):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT8_ODF_Doppler_Scale_Convention/GOM_DAT8_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_15_2026-08-08.md`

Headline: **SCALE_CONVENTION_UNRESOLVED** — H0–H7 none PASS.

## Gate cleared — Iteration 16

GOM_DAT9 ramp/Fbias + GOM36 claim test:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT9_ODF_Ramp_Fbias_Reconstruction/GOM_DAT9_ASSESSMENT.md`
- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM36_Conjunction_Residual_vs_Solar_K/GOM36_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_16_2026-08-08.md`
- Index: `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT_META.md`

Headline: **FBIAS_RECON_UNRESOLVED**; GOM36 corr gate fired but **delete-test
confounded with time** (corr(r,t)≈corr(r,dΔt/dt)); amplitude 0.03 Hz vs ~15 kHz
→ **UNADJUDICATED**, not EMPIRICALLY SURVIVES.

## Gate cleared — Iteration 17

Multi-day time-detrended residual vs solar **K**:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM37_Multiday_Detrended_Solar_K_Residual/GOM37_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_17_2026-08-08.md`

Headline: **UNADJUDICATED** — b∈[35.4,42.7] R_☉; corr still time-confounded;
amp_ratio 7×10⁶; Doppler–solar-K path blocked pending definition or range path.

## Gate cleared — Iteration 18

Type-37 range / light-time vs frozen solar **K**:

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM38_Range_LightTime_Solar_K/GOM38_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_18_2026-08-08.md`

Headline: **RANGE_K_UNRESOLVED** (793× type-37; Δt_K/σ~1e−5); ODF
Doppler–solar-**K** path set **PENDING_DEFINITION**.

## Gate cleared — Iteration 19

Local **k** / solar **K** definition (**K = R/k²**; **k ≠ K**):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM39_Local_k_Solar_K_Definition/GOM39_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_19_2026-08-09.md`

Headline: **LOCAL_K_K_DEFINITION_PASS** — multi-radius **K** recovery and
local-**k** delay ∫ validated; path **DEFINED**; residual still UNADJUDICATED.

## Gate cleared — Iteration 20

Energy-form **K** + local-**k** delay-rate (GOM40, Amendment 01):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM40_Energy_Form_K_Local_k_Delay/GOM40_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_20_2026-08-09.md`

Headline: **ENERGY_FORM_K_YEAR_PASS / SCE1_ARC_INSUFFICIENT** — 4-day Earth
arc cannot recover **μ**; year EMB **K = 1476.354 m**, **k = 1.006719×10⁴**;
delay-rate amp class ~0.6 Hz @ Ka; no residual promotion.

## Gate cleared — Iteration 21

Benchmark detox B15/B16/B25 **applied** to suite:

- `Audits/BENCHMARK_DETOX_B15_B16_B25_2026-08-07.md` (suite-edit section)
- `Benchmarks/B01_B25/benchmarks_suite.cpp`
- `Audits/MASTER_PROTOCOL_ITERATION_21_2026-08-09.md`

Headline: **BENCHMARK_DETOX_APPLIED** — earned **50/61 (82.0%)**; 6 note-only
PENDING; 0 genuine fails; historical 56/67 retired. No `laws.hpp` edit.

## Gate cleared — Iteration 25

NP12b close-pack `nuclear_boundary_radius` vs frozen IAEA radii:

- `Investigations/05_Nuclear_Physics/NP12b_ClosePack_Radius_Reproduction/NP12b_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_25_2026-08-09.md`

Headline: **CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION** —
`RMS_rel(A≥16)=0.0370`; retracted `Z·R_p` 244× worse (diagnostic). Cassini
RSR/TLM left downloading; residual branch still deferred.

## Gate cleared — Iteration 26

NP34 whole-range `triton_parity_misfit` vs frozen NUBASE2020:

- `Investigations/05_Nuclear_Physics/NP34_Triton_Parity_NUBASE_Census/NP34_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_26_2026-08-09.md`

Headline: **TRITON_PARITY_EXCLUDED** — five quasi-stables + seven grips match,
but primordial misfits also include ²H, ⁶Li, ¹⁰B, ¹⁴N. B38b hand-list is not a
whole-range proof.

## Gate cleared — Iteration 27

NP34b reformulated census `misfits = L ∪ H` vs NUBASE2020:

- `Investigations/05_Nuclear_Physics/NP34b_Complete_Natural_Misfit_Census/NP34b_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_27_2026-08-09.md`

Headline: **COMPLETE_NATURAL_MISFIT_CENSUS_SURVIVES** — 9/9 misfits, 7/7 grips,
0 extras. Canon comment update still propose-and-wait.

## Gate cleared — Iteration 34

NSEQ05 pure-shell expansion + stella→cuboct→14→42:

- `Investigations/05_Nuclear_Physics/NSEQ05_Pure_Shell_Stella_Cuboct_Relations/NSEQ05_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_34_2026-08-09.md`
- `Audits/RELATIONSHIP_CORRECTIONS_2026-08-09.md`

Headline: **PURE_SHELL_STELLA_CUBOCT_RELATIONS_SURVIVE** — link-rule beats
face-rule; 14 orients T₁₄; D₄₂ orientation bit OPEN; laws.hpp comments
propose-and-wait.

## Gate cleared — Iteration 26

NP12b observable admissibility:

- `Investigations/05_Nuclear_Physics/NP12b_ClosePack_Radius_Reproduction/NP12B_OBSERVABLE_ADMISSIBILITY_AUDIT_RESULTS_2026-08-09.md`
- `Audits/MASTER_PROTOCOL_ITERATION_26_2026-08-09.md`

Headline: **PROXY_REPRODUCED_UNDER_UNDERIVED_SURFACE_CHARGE_MAPPING** — physical
boundary-law support corrected to **UNADJUDICATED**.

## Gate cleared — Iteration 27

NP12c Phase A boundary→RMS Map freeze:

- `Investigations/05_Nuclear_Physics/NP12c_Boundary_to_RMS_Map/NP12c_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_27_2026-08-09.md`

Headline: **MAP_UNDERIVED / PHASE_B_SEALED** — no executable native Map in
canon; identity and uniform candidates classified; holdout not opened; no
retrofit fit.

## Gate cleared — Iteration 28

NP12d underdetermination + topology→RMS redirect:

- `Investigations/05_Nuclear_Physics/NP12d_Topology_Charge_Second_Moment/NP12d_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_28_2026-08-09.md`

Headline: **UNDERDETERMINED — BOUNDARY IS NOT A SUFFICIENT STATE VARIABLE** —
`μ_λ` proves any `R_RMS ∈ [0,R_B]` at fixed boundary; NP12 path **O3**;
topology layer **O2**; correct arrow topology→`ρ_q`→`R_RMS`; IAEA sealed.

## Gate cleared — Iteration 29

NP12e frozen proton centres → point-proton RMS (IAEA sealed):

- `Investigations/05_Nuclear_Physics/NP12e_Frozen_Proton_Centres_Point_RMS/NP12e_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_29_2026-08-09.md`

Headline: **POINT_PROTON_RMS_FROZEN_SET / PHYSICAL_CHARGE_RMS_UNDERDETERMINED** —
He/Be/C/O COMPUTED; ⁷Li table incomplete; C/O stated `R_{p,RMS} > R_boundary`;
no `ρ_q`; IAEA sealed.

## Gate cleared — Iteration 30

Nuclear Packing Sequencer rules freeze (author redirect off QED charge radius):

- `Investigations/05_Nuclear_Physics/NSEQ01_Sequencer_Rules_Freeze/NSEQ01_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_30_2026-08-09.md`

Headline: **SEQUENCER_RULES_FROZEN** — R1–R8; 217 grammar rows; packing smoke
PASS; NP12 IAEA-RMS path labelled **WRONG_OBSERVABLE** (enmeshment/shadow is
the native nuclear story).

## Gate cleared — Iteration 31

NSEQ02 triton shell orientation (belt nomenclature / planar seating stale):

- `Investigations/05_Nuclear_Physics/NSEQ02_Triton_Shell_Orientation/NSEQ02_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_31_2026-08-09.md`

Headline: **BELT_ORIENTATION_STALE** — capacities/grammar/open–close packing
retained; polar dual tetrahedra (`r_open > r_close`) PASS geometry test;
sequencer coplanar belt ruled out as orientation; NSEQ01 R5 amended; no canon
edit (propose-and-wait).

## Gate cleared — Iteration 32

NSEQ03 dual-tetra seating applied to packing sequencer (site + docs mirror):

- `Investigations/05_Nuclear_Physics/NSEQ03_Dual_Tetra_Sequencer_Rewrite/NSEQ03_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_32_2026-08-09.md`

Headline: **DUAL_TETRA_SEQUENCER_APPLIED** — Ca-48 poles+±19.47° bands,
`r_open>r_close`; packing smoke PASS; capacities retained; `laws.hpp`
nomenclature proposal awaiting approval.

## Gate cleared — Iteration 33

NSEQ04 shadow-union κ·ΔA + public belt→shell copy sweep:

- `Investigations/05_Nuclear_Physics/NSEQ04_Shadow_Union_Kappa/NSEQ04_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_33_2026-08-09.md`

Headline: **SHADOW_KAPPA_REPORTED** — κ=31.45 MeV/fm² on N=217
(CALIBRATED(1)); R²(BE)≈0.79 but R²(BE/A)≪0; light nuclei over-bound;
`laws.hpp` rename still held for explicit approve phrase.

## Gate cleared — Iteration 34

NSEQ05 pure-shell incidence (stella→cuboct→14; V/E vs face; sequencer rewrite):

- `Investigations/05_Nuclear_Physics/NSEQ05_Pure_Shell_Incidence/NSEQ05_ASSESSMENT.md`
- `Audits/MASTER_PROTOCOL_ITERATION_34_2026-08-09.md`

Headline: **PURE_SHELL_INCIDENCE_FORMALIZED** — species order
T₈→D₁₂→T₁₀→…; link rule PASS; face rule EXCLUDED; T₁₄=cuboct face normals;
14→42 graph PASS with D₄₂ `3V−6` OPEN debt; sequencer interleaved + cuboct/T14
live; `laws.hpp` still propose-and-wait.

## Gate cleared — Iteration 35

Author-approved canon apply: geometric shell replaces Gemini “belt” model:

- `Engine/include/sdt/laws.hpp` (shell schedule + completion law comments/symbols)
- `Audits/MASTER_PROTOCOL_ITERATION_35_2026-08-09.md`

Headline: **BELT_MODEL_WITHDRAWN_GEOMETRIC_SHELL_CANON** — capacities unchanged;
`triton_shell_*` symbols live; B38 updated; compile check PASS.

## Gate cleared — Iteration 36

NSEQ07 D₄₂ genus-1 topology:

- `Investigations/05_Nuclear_Physics/NSEQ07_D42_Genus1_Topology/`
- `Audits/MASTER_PROTOCOL_ITERATION_36_2026-08-09.md`

Headline: **D42_GENUS1_TOPOLOGY_SURVIVES** — surface χ=2 + 6 Q–Q ⇒ genus-1.

## Gate cleared — Iteration 37

NSEQ09 blind δ₂ₙ from pure-shell F/B/R:

- `Investigations/05_Nuclear_Physics/NSEQ09_Blind_Delta2n_Pure_Shell/`
- `Audits/MASTER_PROTOCOL_ITERATION_37_2026-08-11.md`

Headline: **BLIND_DELTA2N_SURVIVES** — SEAL vs OPEN_D split earned.

## Gate cleared — Iteration 38 / 38b

NSEQ10 QQ branch selection; then C3 rule-win withdrawn:

- `Audits/MASTER_PROTOCOL_ITERATION_38_2026-08-11.md`
- `Audits/MASTER_PROTOCOL_ITERATION_38b_NSEQ10_CORRECTION_2026-08-11.md`

Headline: NSEQ10 C3 win **WITHDRAWN**; replaced by NSEQ11.

## Gate cleared — Iteration 39

NSEQ11 axis/around Shared ∪ K₂,₂ matching:

- `Investigations/05_Nuclear_Physics/NSEQ11_Axis_Around_Branch_Rule/`
- `Audits/MASTER_PROTOCOL_ITERATION_39_2026-08-11.md`

Headline: **AXIS_AROUND_BRANCH_RULE_SURVIVES** — no C3 machinery.

## Archive detox — companion benchmarks tree

Full subfolder pass of
`C:\Users\Jimmi\Spatial_Displacement_Theory\SDT\benchmarks`
(nine agent folders + tracking CSVs):

- `Audits/LEGACY_BENCHMARKS_ARCHIVE_CROSSWALK_2026-08-11.md`

Headline: companion CERTIFIED stamps **void**; residual archive fails =
B04 He⁺/calibrated Lamb, B17 Curie, B21/B24 screening–occlusion, B34
binding, B59 muon (sheet overclaim). Next leverage remains **ε_agg** (MM01).

## Gate cleared — Iteration 40

MM02 ε_agg candidate screen (unit correction):

- `Investigations/06_Gravitation_and_Orbital_Mechanics/MM02_Epsilon_Agg_Occlusion_Candidates/`
- `Audits/MASTER_PROTOCOL_ITERATION_40_2026-08-11.md`

Headline: **EPSILON_AGG_UNIT_CORRECTED** — wrong micro unit was `Om_H`;
engine quantum is `koppa_per_baryon`; packing candidates do not earn a
mechanism; C2 numeric MATCH = `α m_p/m_e ≈ 4π` coincidence. Law-III origin
of `koppa_per_baryon` without `l_P↔G` remains OPEN (MM03).

## Gate cleared — Iteration 41

Spine close (2026-08-11) and TT flip-axis (2026-08-12):

- `Audits/MASTER_PROTOCOL_ITERATION_41_2026-08-11.md`
- `Audits/MASTER_PROTOCOL_ITERATION_41_2026-08-12.md`

Headline: MM03 koppa Law-III **PARKED_OPEN**; AS01 Rydberg/Compton **SURVIVES**
(length-Om plug EXCLUDED); OM01 shared-om **CONDITIONAL**; NSEQ13 TT flip-axis
**EXCLUDED** (observed inversion not rescued).

## Gate cleared — Iteration 42

Outstanding-closure terminal classes (2026-08-11) and native `A_s` screen
(2026-08-12):

- `Audits/MASTER_PROTOCOL_ITERATION_42_2026-08-11.md`
- `Audits/MASTER_PROTOCOL_ITERATION_42_2026-08-12.md`

Headline: unlabeled OPEN rows closed to terminal classes; AS02
**REMAINS_IMPORTED**; GW01 chirp **IDENTITY_DISCLOSED** / coeff
UNDERDETERMINED. No EMPIRICALLY SURVIVES promotions.

## Gate cleared — Iteration 43

Five ranked debts executed (MM04 / OM03 / NU01 / CK01 / NSEQ13 occupation):

- `Audits/MASTER_PROTOCOL_ITERATION_43_2026-08-12.md`
- `Audits/OUTSTANDING_FAILED_AFTER_07-22_CORRECTIONS_2026-08-09.md`

Headline: MM04 **PARKED_PERMANENT**; OM03 **DEFINITION_BLOCKED**; NU01 scalar
**EXCLUDED**, mechanism UNDERDETERMINED; CK01 constitutive **OPEN**; NSEQ13
occupation MeV **UNDERDETERMINED**. Stop: remaining work needs new ontology
or new data.

## Gate cleared — Iteration 44

Reopen-condition push (not a rerun of I43 candidate classes):

- `Investigations/00_Master_Cascade/Outstanding_Closure_Iteration44/`
- `Audits/MASTER_PROTOCOL_ITERATION_44_2026-08-13.md`
- `.audit-tmp/i44_run.txt`

Headline: NU02 **APPEARANCE_CONDITIONAL**; CK02
**PACKING_NUMERIC_MATCH__CONSTITUTIVE_OPEN**; NSEQ14 **UNDERDETERMINED**;
OM04 **RSR_PAYLOAD_ABSENT**. Koppa / A_s / GOM06 distinctive tests / PSP02
TNF / D42 comment remain gated.
