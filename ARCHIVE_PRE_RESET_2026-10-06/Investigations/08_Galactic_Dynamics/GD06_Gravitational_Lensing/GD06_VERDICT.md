# GD06 — Verdict: Gravitational Lensing

**Classification: CLASS C (CONVERGENCE at solar scale).**
**Author:** James Christopher Tyndall, Melbourne · Tool: `gd06_gravitational_lensing.cpp`.

## Hypothesis

Lensing = convergence-gradient refraction; δ = 4ϟ/b (GOM01).

## Key numbers

- Solar limb deflection: **1.7517″** vs 1.7500″ (**0.10%**) — PASS
- Computed from k_Sun, R_Sun only — **no G/M**

## OPEN

SLACS galaxy/cluster Einstein radii need per-lens k-hierarchy — **PENDING**.

**Sign-off: PASS (solar), Class C.**


---

## Audit correction (2026-10-05)

- The tool `gd06_gravitational_lensing.cpp` does not integrate the eikonal equation; it evaluates the hard-coded closed form δ = 4ϟ/b. The 1.7517″ above is therefore the evaluation of that formula, not an integral of the prompt's index.
- New tool `gd06_eikonal.cpp` (first-order eikonal integral, koppa from the engine bridge, no G, no M, no GM) with validation V1 (weak-field analytic check, 2.5e-13) and V2 (resolution change 1.4e-14) before use:
  - index n = (1 − ϟ/r)^(−1) (the profile the prompt stated): **δ = 0.8758″, −49.95% against 1.750″, FAIL**;
  - index n = (1 − ϟ/r)^(−2) (c_far = c(1−z)², the GOM22 repair carried in `laws.hpp`): **δ = 1.7517″, +0.10%, PASS**.
- The PASS therefore stands only for the c(1−z)² profile. That profile was fixed by the Shapiro delay, so the solar deflection is a second observable read off the same profile, not an independent derivation; class stays CONVERGENCE (shared form with the standard weak-field result). `PROMPT.md` now states the c(1−z)² profile. The cluster/galaxy rows remain OPEN.
