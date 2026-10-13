# CR05 (spation pressure tensor; H₀ closure) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Registration and outcome in one record: no instrument was built.

## 0. Inputs read and exposure
`CR05/PROMPT.md`: the five questions (the measurable gap added 2026-10-05: can the spation pressure tensor and its freeze-out close the observed local slope H₀ and the transfer function within 5%, or is closure excluded as recorded), the original specification (Phases 1–5), the pre-run block, the 2026-10-05 correction (keep the retraction; re-run only after the question field is filled). Not read: `CR05_VERDICT.md`, the five phase files, `EXECUTION_SUMMARY.txt`, `cr05_pressure_solver.cpp`. The prompt's status is RETRACTED-FABRICATED → OPEN. Exposure from this programme: CR14 noted that `cr05_pressure_solver.cpp:93` uses n_b ∝ (1+z)³.

## 1. Analysis of the phases as specified
| Phase | What the specification needs | Status here |
|---|---|---|
| 1 pressure tensor eigenvalues "in an expanding lattice", P ∝ a⁻³ | an expansion a(t) and a lattice stress model; neither is native (the framework has no expansion) and no lattice stress tensor is defined in the prompt | not instrumentable; the only computable content is P_N = N⁴P₀, an identity once T_N = N T₀ and P₀ = a T₀⁴/3 (CR16, COMPUTED, 4×10⁻¹⁶) |
| 2 adiabatic law, γ from topology | γ = 4 for a photon gas is Stefan–Boltzmann (CR16); "from topology" is not derived | γ = 4 reproduced as the identity above; topology origin not supplied |
| 3 Hubble equation: candidates A (H² ∝ P_conv ρ), B (Lk(t) P/a³), C (ω_BAO² coupling) compared with Planck 67.4 | ρ, Lk(t), ω_BAO and the coupling constants are undefined in the prompt; the comparison value is a ΛCDM fitted output (struck as a target in CR16) | not instrumentable; the target is contraband |
| 4 freeze-out at z_rec ≈ 1100 (linking number drops 4×) | z_rec = 1100 is a struck target; the 4× is an assertion; CR15 found the postulate set gives no transition there | not instrumentable |
| 5 transfer-function closure (f = P_eff/P_conv has no CLASS X dependency) | a classification of f's inputs; P_eff and P_conv are engine quantities (f = 2.1×10⁻¹⁷ from `law_III::P_eff` 5.23×10³¹ Pa and `law_I::P_conv` 2.46×10⁴⁸ Pa), the class bookkeeping needs the document | f numeric only |
Premise findings: (i) the specification's H₀ route requires an expanding lattice, which the framework's cosmology rejects (the Hubble tension record: emission and propagation conflated, no expansion); (ii) every numerical target is a ΛCDM output; (iii) the retraction stands.

## 2. Outcome
**OPEN, not instrumentable as specified; retraction stands.** Computed for the record: f = P_eff/P_conv = 5.2273×10³¹/2.4608×10⁴⁸ = 2.12×10⁻¹⁷ (engine constants; from the FLM01 pass, same inputs). Owed before a re-run: a native H₀ statement (what sets the local slope in a framework without expansion), with its observable and its comparison value chosen without a ΛCDM output; the question field then binds the phases.
