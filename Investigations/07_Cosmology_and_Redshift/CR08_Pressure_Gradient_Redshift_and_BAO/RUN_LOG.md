# RUN_LOG — CR08 Pressure-Gradient Redshift and BAO

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Executor:** HUNTER protocol.

## Golden Rule Q1 (filling the template blank)

**What don't we know?** Whether the SDT strain-redshift distance law d(z) = ln(1+z)/σ₀, with a
CONSTANT 147 Mpc physical ruler, reproduces the measured BAO angular/radial observables at
z = 0.15–2.33 and the CMB acoustic angle at z ≈ 1100.

## Pre-Run Commitments — CR08 (written BEFORE any code was compiled or run)

- Prompt completion target: **B**
- Physics class hoped: DEGENERATE — committed to **KILLED** on any observable class where the
  deviation exceeds the gate, with the miss magnitude reported.
- CALIBRATED budget: **0 in the primary run** (H₀ anchored at both 67.4 and 73.04, OBSERVED —
  no fit). One clearly-labelled sensitivity fit (best-fit H₀, 1 param) allowed for diagnosis
  only; it cannot convert a FAIL to a PASS.
- Engine namespaces: `sdt::cosmology` (strain::sigma, pre_clearing::BAO_scale, c_s),
  `law_I` (R_CMB), `measured`.
- **SDT model (fixed before run, from the PROMPT + cosmology.hpp; no shape freedom):**
  - 1+z = exp(σ₀ d)  →  d(z) = ln(1+z)·c/H₀  (static frame: D_A ≡ d, no (1+z) factors)
  - transverse observable:  θ⁻¹ ≡ D_M/r_d → SDT: d(z)/147 Mpc
  - line-of-sight observable: Δz = r_d·σ₀(1+z) → SDT "D_H/r_d" = (c/H₀)/(1+z)/147 Mpc
  - D_V/r_d = [z·(D_H/r_d)·(D_M/r_d)²]^(1/3)
  - ruler: 147 Mpc CONSTANT physical (engine bao::scale; the lattice-equilibrium claim)
- **Data (OBSERVED anchors, declared):** consolidated BOSS DR12 / eBOSS final (Alam et al.
  2021 compilation) D_M/r_d and D_H/r_d at z = 0.38, 0.51, 0.698, 1.48, 2.33; MGS D_V/r_d at
  z = 0.15; Planck 2018 acoustic angle 100θ* = 1.04109 (r_* = 144.4 Mpc). **Memory-transcribed
  (no network in this run): individual values carry ~±2% transcription risk — flagged; any
  verdict that hinges on a <5% margin must be labelled provisional. ΛCDM column (Ω_m = 0.31)
  computed ONLY as the rival OBSERVED-comparison column (HUNTER §B), never in the SDT chain.**
- **Phase thresholds (committed before run):**
  - G1 (prompt criterion 1): every survey point within 3% → PASS; any point > 5% (3% gate +
    2% anchor risk) → FAIL for that observable class; between 3–5% → provisional.
  - G2 (prompt criterion 2, "147 Mpc from c_s × t_coupled"): AUDIT ONLY — CR03 has already
    shown t_coupled ≡ BAO_scale/c_s in cosmology.hpp (circular). Committed: report as
    IDENTITY, cannot PASS.
  - G3 (CMB acoustic angle): SDT θ(1100) vs measured θ*; FAIL if off by > 5%.
  - G4 (no dark energy): trivially true for SDT; only meaningful if G1/G3 pass. No credit
    otherwise.
- Forbidden retroactive changes: swapping in a different d(z) after seeing misses (the n-free
  law is CR06's territory and is already measured there, n ≈ 0.66); widening gates; dropping
  the z = 1100 point.

## Run record

- Tool: `cr08_bao_consistency.cpp`. Output: `results.txt` = verbatim stdout.
