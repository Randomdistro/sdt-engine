# GOM20 Canonical Authority Correction - 2026-08-09

**Status:** `PENDING_MECHANISM`; empirical SDT verdict `UNADJUDICATED`.
**Scope:** correction of a source-authority inference. This document introduces
no experimental or observational conclusion.

## Correction

The prior readiness audit stated that two present functions formed an unresolved
canonical clock-law fork. The premise of textual coexistence was true; the
conclusion of equal admissibility was false. It was based on a header inventory
only and did not inspect the repair provenance or compiled-source consumers.

The corrected classification is
`REPAIRED_LINEAR_ENGINE_DEFAULT_WITH_GOM20_BINDING_ABSENT`:

- `law_V::gravitational_time_dilation` still contains a square-root rate, but
  its exact qualified name has no caller in the frozen compiled-source census.
- `depth_closure::clock_rate(z) = 1 - z` is marked in GOM22 as applied to canon
  and is called by the benchmark suite and GOM22 executable source.
- The GOM20 prompt and mechanism amendment name neither routine. Consequently,
  GOM20 does not bind its proposed satellite terms to the active rate law.

The legacy routine is retained as a source-hygiene concern. It must not be
silently deleted or treated as an active GPS mechanism without a canonical
change decision and a consumer review.

## Frozen authority basis

| Source | SHA-256 | Role |
|---|---|---|
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | Public canonical header containing both routines and the GOM22 repair block |
| `GOM22_ASSESSMENT_2026-07-30.md` | `2361629a18296d7bef4009f4118ac3f2e07f9d5b4dc41f96629c264fd0356de5` | Records the 2026-07-30 repair as applied to canon |
| `Benchmarks/B01_B25/benchmarks_suite.cpp` | `ec33026c916a051731a2ceabdfe9559c5e3137a1c3717135a7f0d24ed3c981bf` | Compiled consumer of the repaired linear routine |
| `GOM20_GPS_MECHANISM_AMENDMENT_01.md` | `d772bcf1190b2acec57f8f055f7740f89579be2a7907505ff4923d5889b7f84c` | Required GOM20 ingredients, without a binding equation |

## Reproducible source census

The audit scans exact qualified calls in UTF-8 source files with extensions
`.cpp`, `.cc`, `.cxx`, `.hpp`, and `.h` beneath `Benchmarks`, `Compiler`,
`Experiments`, `Investigations`, `Papers`, `Theory`, `Laws`, `Engine`, and
`Release`. This is a source-text census, not a C++ semantic proof.

| Qualified call | Callers found |
|---|---|
| `law_V::gravitational_time_dilation(...)` | none |
| `depth_closure::clock_rate(...)` | `Benchmarks/B01_B25/benchmarks_suite.cpp`; `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM22_Shapiro_Velocity_Profile/gom22_shapiro_profile.cpp` |

The automated result is stored in `gom20_gps_anchor_audit_results.json`. Its
authority hashes and prior GPS-source hashes both pass; the direct-observation
gate remains false.

## Error origin and repair trail

1. The prior audit inferred an unresolved branch solely from two header bodies.
   This omitted the GOM22 repair marker and caller evidence.
2. The corrective audit added frozen authority hashes, repair-marker checks, a
   qualified-call census, and a specific GOM20 binding check.
3. The first corrective call-census run failed with `re.PatternError` because
   the Python regular expression was over-escaped. It produced no result file.
   The expression was corrected, `py_compile` passed, and the audit was rerun.
4. The rerun confirms the repaired-linear engine default but also confirms that
   the required GOM20 rate binding is absent.

## Remaining falsifiability gate

This correction removes one falsely stated ambiguity; it does not manufacture a
testable GPS prediction. Before retrieving or fitting a direct clock series, a
model-author equation must explicitly compose the active rate law with all five
required terms: polar-radius `koppa`, baryon-volume exclusion, spation-shell
exclusion, inverse-square fall-off, and movement budget. It must additionally
fix dimensions, signs, normalizations, reference surface, initial states,
coordinate time, frames, uncertainty propagation, and a no-retuning rule.

Until that gate is met, the only rigorous result is
`NON_IDENTIFIABLE_BEFORE_PREDICTION`, not physical acceptance or rejection.
