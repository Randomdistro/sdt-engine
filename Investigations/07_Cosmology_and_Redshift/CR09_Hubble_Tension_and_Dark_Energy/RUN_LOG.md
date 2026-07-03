# RUN_LOG — CR09 Hubble Tension and Dark Energy

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Executor:** HUNTER protocol.

## Golden Rule Q1 (filling the template blank)

**What don't we know?** Whether ANY radial placement of the SDT strain enhancement
(σ_local/σ_global = 73.04/67.4 = 1.0837) survives the three observations that bracket it:
SH0ES's own Hubble-flow window, the Pantheon+ residual shape, and the BAO inverse ladder.
H₀ is NEVER derived here — both values are OBSERVED anchors; the question is geometric
consistency of the split, nothing more.

## Pre-Run Commitments — CR09 (written BEFORE any code was compiled or run)

- Prompt completion target: **B** for Phases A/C (Phase B is NOT re-run: CR12 already fitted
  Pantheon+ honestly — SDT coasting χ²=773 vs ΛCDM 681, ΔAIC≈90, DEGENERATE-not-better;
  re-fitting here would duplicate; Phase D is NOT re-run: CR08 just executed it — KILLED).
- Physics class hoped: OPEN — committed to **KILLED** for the isotropic radial-gradient
  dissolution if the z_t window scan closes to empty.
- CALIBRATED budget: **0** (nothing fitted; z_t is scanned and every value graded, not chosen).
- Engine namespaces: `sdt::cosmology::strain` (sigma_CMB, sigma_local, tension_pct),
  `law_I::R_CMB`, `measured`.
- **Model (fixed):** piecewise strain σ(d) = σ_local for d < d_t, σ_global beyond;
  ln(1+z) = σ_l·min(d,d_t) + σ_g·max(0,d−d_t). Convention-independent observables only
  (μ-differences, σ path-averages) so no luminosity-distance convention is load-bearing.
- **OBSERVED anchors (declared):** H₀ = 67.4±0.5 (Planck number, used as strain anchor, NOT
  re-derived); 73.04±1.04 (SH0ES 2022); SH0ES Hubble-flow window 0.023 < z < 0.15;
  Pantheon+ binned residual step sensitivity 0.05 mag (conservative; Brout+2022 bins are
  0.02–0.03); BAO inverse-ladder H₀ = 67.4±1.1 (eBOSS+BBN) at z = 0.38–2.33.
- **Phase thresholds (committed before run):**
  - W1 (SH0ES coverage): recovered H₀ from the piecewise model, averaged over the SH0ES
    window, must be ≥ 72.0 km/s/Mpc (within 1σ of 73.04) for the split to explain the tension.
  - W2 (SN shape): max |Δμ(piecewise) − Δμ(uniform-local)| over 0.023 < z < 2.3 must be
    < 0.05 mag (else Pantheon+ would see the step).
  - W3 (BAO ladder): implied path-averaged c·σ̄ at every BAO z (0.38–2.33) must be
    ≤ 68.5 km/s/Mpc (1σ of the inverse ladder).
  - W4 (CMB): path-average shift at z=1100 must be < 1%.
  - **Kill rule:** if NO z_t in a dense scan (0.001 → 1100, log grid) passes W1–W4 jointly,
    the isotropic radial-gradient dissolution of the tension is KILLED. Anisotropic /
    line-of-sight-variance versions (CR06's emission half) are OUT OF SCOPE and stay OPEN.
- Forbidden retroactive changes: relaxing any W gate; adding model freedom (smooth profiles
  chosen post-hoc to thread the gates would be a FISHED RECOVERY — a smooth profile is
  admissible only under a new pre-committed prompt).

## Run record

- Tool: `cr09_tension_window.cpp`. Output: `results.txt` = verbatim stdout.
