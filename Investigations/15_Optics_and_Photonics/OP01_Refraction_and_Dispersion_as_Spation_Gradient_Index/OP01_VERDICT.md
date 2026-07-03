# OP01 — Verdict: Refraction as Gradient Index

**Classification: CLASS C (CONVERGENCE).**
**Author:** James Christopher Tyndall, Melbourne · Tool: `op01_refraction.cpp`.

## Hypothesis

n = 1/(1−z); Snell's law from Fermat on closure ratio; solar vacuum n from k-hierarchy.

## Key numbers

- Snell reciprocity (air→water): **PASS**
- n_sun = 1/(1 − 1/k²) ≈ **1.000002** — COMPUTED
- n(water) = 1.333: **OBSERVED** input

Dispersion n(λ): **PENDING**.

**Sign-off: OPEN/PARTIAL — rebuilt tool exits 1: Snell FAIL at the committed 1e-9 gate; radial eikonal 0.836″ vs 1.75″ (52% FAIL); the "GOM01 path integral 1.7517″" row exists in no source; committed results were a Python replay (no compiler in PATH). Honest survivor: matter-index Phase 1 is legitimately OPEN.**
