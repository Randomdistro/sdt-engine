# FD02 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD02_VERDICT.md`,
> `FD02_DERIVATION.md`, `fd02_results.txt` deleted 2026-07-26 (git-recoverable).
> Tool: `fd02_viscosity_circulation.cpp`, g++ 15.2 -O2, exit **0**.
> Output: `fd02_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN, with two honest self-demotions already in the prompt:** κ = h/m is flagged "essentially
structural… a consistency check, not an independent prediction" (⓪.2), and the KSS 1/(4π) is
DERIVED-or-CALIBRATED(1), never silent. QGP appears as a measured convergence benchmark by its
community name only — no rival axioms enter the chain. `h`/`ℏ`/`k_B` are whitelist.

## What the direct run measured

| gate | committed | today | honest verdict |
|---|---|---|---|
| C1 ν = ⅓λv (two-stream) | identical | 0.000e+00 diff; ⅓ = same angular average as P_cf = P_conv/3 | PASS |
| C2 air AND water within 10× | both ≲10× | air 1.44× off; **water 16.5× off** | **FIRED as committed** (see below) |
| C3 exponent 0.5 ± 0.05 | lattice model | 0.50000 analytic-vs-numerical of the same model | internal consistency only |
| C4 κ = h/m_He <1% | no free integer | 9.972027e-08 vs Vinen 9.970e-08 — 0.020% | PASS (identity-class) |
| C5 η/s floor | derived or CALIBRATED(1) | floor present; 4π geometry native; exact KSS pin **CALIBRATED(1)** | PASS (Class C path) |

## Corrections this verdict applies to the tool's own summary

1. **C2 was re-scoped after firing.** The pre-committed gate (§④ P2) requires BOTH fluids within
   a factor 10. Water misses at 16.5×. The tool's summary line grades "air within 10× &
   air>water: pass" — that is a retro-narrowing of a fired gate. Recorded here as: **C2 FIRED on
   water**; the physical reading (mean-free-path kinetic theory is a dilute-gas model; water is a
   dense liquid) is defensible and was pre-noted, but the gate as written fails and the honest
   next step is a dense-liquid λ_mfp model, not a pass stamp.
2. **C3 carries no empirical power as run.** The 0.5 exponent is the model fitted to itself
   (analytic vs numerical of the same rule). The empirical fact is real air: μ ~ T^0.74
   (Sutherland), ν ~ T^1.74 at fixed P — both printed honestly. The lattice 0.5 is the
   hard-sphere fixed-λ limit, a statement of the model, not a measurement matched.

## Verdict

- **Prompt completion: B** (all five phases executed with printed predictions; C2 grading
  corrected here).
- **Physics class: CONVERGENCE (Class C) with named misses.** Banked: air ν to 1.44× with the ⅓
  derived from the same angular average the engine already uses; κ = h/m_He at 0.020% as a
  forced identity (no free integer — the winding argument allows nothing else); dissipation
  floor present with native 4π geometry and the exact KSS coefficient honestly CALIBRATED(1).
  Open/misses: water 16.5× (dense-liquid λ_mfp model owed); real-gas exponent 0.74 vs lattice
  0.5 (Sutherland λ(T) not derived); FD01 handshake at coefficient level still open.
- **Recovery:** n/a · **Cascade root:** λ_mfp from knot density (ROOT-SIM class) — the same
  closure FD01 waits on.
