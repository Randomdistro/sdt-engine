# FD02 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD02_VERDICT.md`,
> `FD02_DERIVATION.md`, `fd02_results.txt` deleted 2026-07-26 (git-recoverable).
> Tool: `fd02_viscosity_circulation.cpp`, MSVC C++20, exit **1** because C2 fails.
> Output: `fd02_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN, with two explicit self-demotions already in the prompt:** κ = h/m is flagged "essentially
structural… a consistency check, not an independent prediction" (⓪.2), and the KSS 1/(4π) is
DERIVED-or-CALIBRATED(1), never silent. QGP appears as a measured convergence benchmark by its
community name only — no rival axioms enter the chain. `h`/`ℏ`/`k_B` are derivation basis.

## What the direct run measured

| gate | committed | today | verdict |
|---|---|---|---|
| C1 ν = ⅓λv (two-stream) | identical | 0.000e+00 diff; ⅓ = same angular average as P_cf = P_conv/3 | PASS |
| C2 air AND water within 10× | both ≲10× | air 1.44× off; **water 16.5× off** | **FAIL as registered** (see below) |
| C3 exponent 0.5 ± 0.05 | lattice model | 0.50000 analytic-vs-numerical of the same model | internal consistency only |
| C4 κ = h/m_He <1% | no free integer | 9.972027e-08 vs Vinen 9.970e-08 — 0.020% | PASS (identity-class) |
| C5 η/s floor | derived or CALIBRATED(1) | floor present; 4π geometry native; exact KSS pin **CALIBRATED(1)** | PASS (Class C path) |

## Corrections this verdict applies to the tool's own summary

1. **C2 was re-scoped after failing.** The pre-registered gate (§④ P2) requires BOTH fluids within
   a factor 10. Water misses at 16.5×. The tool's summary line grades "air within 10× &
   air>water: pass" — that is a retro-narrowing of a failed gate. Recorded here as: **C2 FAIL on
   water**; the physical reading (mean-free-path kinetic theory is a dilute-gas model; water is a
   dense liquid) is defensible and was pre-noted, but the gate as written fails and the required
   next step is a dense-liquid λ_mfp model, not a pass stamp.
2. **C3 carries no empirical power as run.** The 0.5 exponent is the model fitted to itself
   (analytic vs numerical of the same rule). The empirical fact is real air: μ ~ T^0.74
   (Sutherland), ν ~ T^1.74 at fixed P — both printed explicitly. The lattice 0.5 is the
   hard-sphere fixed-λ limit, a statement of the model, not a measurement matched.

## Verdict

- **Prompt completion: B** (all five phases executed with printed predictions; C2 grading
  corrected here).
- **Physics class: CONVERGENCE (Class C) with named misses.** Banked: air ν to 1.44× with the ⅓
  derived from the same angular average the engine already uses; κ = h/m_He at 0.020% as a
  forced identity (no free integer — the winding argument allows nothing else); dissipation
  floor present with native 4π geometry and the exact KSS coefficient CALIBRATED(1).
  Open/misses: water 16.5× (dense-liquid λ_mfp model owed); real-gas exponent 0.74 vs lattice
  0.5 (Sutherland λ(T) not derived); FD01 handshake at coefficient level still open.
- **Recovery:** n/a · **Cascade root:** λ_mfp from knot density (ROOT-SIM class) — the same
  closure FD01 waits on.

## B16 extension — 2026-08-15

The tool now executes the later frozen full-curve gate before reading the
transport comparisons.  One Bondi argon boundary and the FLM15 `6/7`
relay-lock fraction feed all three hard-lock collision moments.

- Collision-integral and doubled-resolution residuals are below `4e-15`.
- Argon dynamic-viscosity whole-curve RMS is `9.715%`.
- Argon thermal-conductivity whole-curve RMS is `9.675%`.
- Argon self-diffusivity whole-curve RMS is `7.809%`.
- Every curve has the measured monotonic sign.

This advances B16's three rows to `COMPUTED`.  The fixed-pressure exponents are
`0.5`, `0.5`, and `1.5`, respectively; the former diffusivity `0.5` was missing
the `n(T) proportional to 1/T` factor.

The broader FD02 verdict remains qualified because the independent dense-water
factor-ten gate still fails at `16.52`.  The B16 dilute-monatomic closure
does not settle that liquid-state mechanism.
