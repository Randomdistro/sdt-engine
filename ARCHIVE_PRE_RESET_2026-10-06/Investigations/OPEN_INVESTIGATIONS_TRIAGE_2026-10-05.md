# Open investigations triage — 2026-10-05

**Method:** every folder under `Investigations/NN_*/` with a `PROMPT.md` and no file whose name contains VERDICT, ASSESSMENT, RESULTS, results, run_log or RUN_LOG: 42 of 208. This is a file-name test, so a folder that records results under another name is counted as open. The classes below use only what is on disk (code and output files, prompt length, stated status); nothing was run for this table.

## A. Specification seeds with no model (11): not runnable without inventing the mechanism

- PPT12_Lepton_Magnetic_Moments
- PPT13_Pion_Mass_and_Decay
- PPT14_Heavy_Resonance_Masses
- PPT15_Handedness_Asymmetry_CP
- GOM21_Frame_Dragging_GPB
- SAR07_White_Dwarf_Mass_Radius
- SAR08_Pulsar_Timing_Stability
- QM08_Quantum_Eraser
- OP08_Faraday_Rotation
- CH08_Electron_Affinity_Trends
- CH09_Atomic_Radius_Canonical

## B. Code and/or outputs on disk, no verdict file (22): read what the files hold, then write the assessment

- FLM02_Granular_Pulse_Mechanics — code: flm02_granular_pulse_mechanics.cpp, flm02_local_update_theorem.cpp, flm02_measure_closure.cpp; other: INVESTIGATION.md
- FLM05_Lattice_Pulse_Propagation — code: flm05_lattice_pulse.cpp, flm05_torus_derives_mass.cpp; other: INVESTIGATION.md
- PPT06_Spation_Traction_from_Trefoil — code: ppt06_mass_ratio_solver.cpp, ppt06_spation_traction.cpp; other: INVESTIGATION.md
- PPT07_Proton_Electron_Mass_Ratio — code: ppt07_rootsim_wake.py; other: INVESTIGATION.md
- NP02_Stellar_Fusion_and_Nuclear_Growth — code: np02_stellar_fusion_growth.cpp; other: DATA_REQUIREMENTS.md, np02_output.txt
- GOM01_Spation_Depth_Engine — code: gom01_spation_depth_engine.cpp; other: gom01_rerun_2026-07-24.txt
- GOM02_k_Hierarchy_Advantage — code: gom02_k_hierarchy.cpp; other: gom02_rerun_2026-07-24.txt
- GOM03_Lunar_Orbital_Kinematics — code: gom03_lunar_pendulum.cpp; other: gom03_rerun_2026-07-24.txt
- GOM04_Koppa_Closure — code: Deriving_c_From_Mercurial_Precession.cpp, gom04_koppa_closure.cpp; other: gom04b_rerun_2026-07-24.txt, gom04_rerun_2026-07-24.txt
- GOM05_Variable_Spation_Closure — code: gom05_variable_closure.cpp, sundiver.js; other: gom05_rerun_2026-07-24.txt, GOM05_VARIABLE_CLOSURE.md
- GOM06_Gravitational_Wave_Mechanism — code: gom06_binary_decay.cpp, gom06_chirp_from_koppa.cpp, gom06_echoes.cpp; other: gom06_chirp_rerun_2026-07-24.txt, gom06_echoes_rerun_2026-07-24.txt, gom06_memory_rerun_2026-07-24.txt
- GOM07_Reflected_Light_Gravitational_Redshift — code: gom07_partB_lanza2016.py, gom07_reflection_redshift.py, gom07_sun_well.py; other: gom07_partB_rerun_2026-07-24.txt, gom07_predictions_rerun_2026-07-24.txt, gom07_sunwell_rerun_2026-07-24.txt
- GOM08_Mercury_Precession_from_k_Hierarchy — code: gom08_mercury_precession.cpp; other: DATA_REQUIREMENTS.md, gom08_rerun_2026-07-24.txt
- GOM09_Earth_Core_Seismic_Speed — code: gom09_backward.cpp, gom09_seismic.cpp, gom09_trefoil_test.cpp; other: DATA_REQUIREMENTS.md, gom09_backward_rerun_2026-07-24.txt, gom09_seismic_rerun_2026-07-24.txt
- GOM10_Three_Body_Lagrange_from_Koppa — code: gom10_lagrange.cpp; other: gom10_rerun_2026-07-24.txt, PROMPT_nbody_equilibria.md
- GOM11_Ocean_Tidal_Analysis — code: gom11_ocean_tidal.cpp; other: gom11_rerun_2026-07-24.txt
- GOM12_Solar_System_Convergence_Budget — code: gom12_convergence_budget.cpp; other: gom12_rerun_2026-07-24.txt
- GOM13_Occlusion_Altitude_Cavendish — code: gom13_preflight.cpp; other: gom13_rerun_2026-07-24.txt
- GOM14_Koppa_Density_Multiplanet_Consistency — code: koppa_consistency.py; other: gom14_rerun_2026-07-24.txt, koppa_multiplanet.csv
- GOM41_Planetary_Quadrupole_from_Phase_Resistance — code: gom41_planetary_quadrupole.cpp; other: -
- GD01_Eclipse_Saturation_Model — code: gd01_eclipse_saturation.cpp; other: INVESTIGATION.md
- QM01_Deterministic_Double_Slit_from_Lattice_Relay — code: qm01_bell_local_vs_throughpole.py; other: QM01_BELL_MEMO.md

## C. Specification with documents but no code (2)

- NP24_Grammar_Rule_Extraction — nubase2020.txt, NUBASE_GRAMMAR_SWEEP.txt, NUBASE_NULL_TEST.txt
- GD06_Collective_Displacement_Redshift_Law — GD06_TECHNICAL_REPORT.md, PLAIN_LANGUAGE_REPORT.md

## D. Full specification, nothing else on disk (5): runnable if the data and model are in the repo

- NP06_Gear_Frequency_Binding_Functional
- NP31_Orbital_Reach_Binding
- GOM19_Merger_Ledger_Grammarless_Baseline
- GOM24_Cassini_Ring_Moon_Corpus
- CR09_Hubble_Tension_and_Dark_Energy

## E. Created 2026-10-05 as children of the loading/EC split (2)

- SAR10_Bulk_Feedback_Stability_and_Escape (blocked: see SDT_Loading_EC_Reseating_Neutrino_Coupling/SPLIT_PLAN.md)
- PM08_Plasma_Connectivity_and_Contact_Loading (blocked: see SDT_Loading_EC_Reseating_Neutrino_Coupling/SPLIT_PLAN.md)

APS15, NP40 and NP41 (also created today) have assessments and are not in this table. NP42 is an unrelated test.

## Progress after the triage (2026-10-05)
Class D: **NP06** — spec numbers confirmed; P1 not run (no Δω definition in the repo); `NP06_ASSESSMENT.md`. **NP31** — exploratory: engine contact counts show the factorial-to-linear change at A = 4; routes A–C not run; `NP31_ASSESSMENT.md`. **GOM19** — P3 nuclear column and fixed-q composition check computed (all six anchors reproduce to ≤ 0.06%); P1 (mechanism, f(q)) not derived, a* fork OPEN; `GOM19_ASSESSMENT.md`. **GOM24** needs PDS Cassini ISS frames (not in repo, not fetched) and **CR09** was not opened: both remain unrun. These folders still lack a file named VERDICT; their assessments use the ASSESSMENT name.
Addendum: GOM19 also ran P1c/P2 against the GWTC table (f = η/4 level met at q < 1.5, shape not met; slope 2.49 [2.01, 3.26] vs 1). CR09 Route B ran on raw Pantheon+ m_B: zero-knob law leaves a monotonic 0.15 mag residual (T3 = systematic residual); other CR09 routes not run.
Addendum 2: GOM41 had been run on 2026-08-15 (results inside its PROMPT); reproduced exactly on 2026-10-05 (`GOM41_ASSESSMENT.md`). Class B therefore contains folders already run under another file arrangement; GOM01–GOM14 carry `*_rerun_2026-07-24.txt` outputs and have not been re-run here.

Addendum 3 (headline lines read from the existing `*_rerun_2026-07-24.txt` outputs; not re-run here): GOM01 27/27 proofs passed; GOM02 15/15; GOM05 4/4; GOM06 chirp −0.52% (PASS, stated as an algebraic identity of the koppa bridge, Class C), memory order-match; GOM08 Mercury PASS < 0.1%, Class C convergence; GOM11 tidal 0.3–0.4%, Class C; GOM12 two gated PASS, three gated FAIL, one identity, two OPEN; GOM13 pre-flight 47× > 10×. GOM03, GOM04, GOM07, GOM09, GOM10, GOM14 outputs carry no one-line status and need reading in full. These are records of runs already made; they are open in the triage only because no file is named VERDICT or ASSESSMENT.
