# RUN_LOG — SAR04 Stellar Main Sequence from k-Gradient

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Executor:** HUNTER protocol.

## Pre-Run Commitments — SAR04 (written BEFORE any code was compiled or run)

- Prompt completion target: **C** (data deviation forces an ADJ, see ADJ-001)
- Physics class hoped: CONVERGENCE — committed to **KILLED** on the "MS is a monotonic
  k-sequence" claim if the monotonicity gate fails, and to labelling any L(k) exponent as
  **measured, not derived** (there is no SDT derivation of it on the table; claiming one
  post-hoc would be a fished exponent).
- CALIBRATED budget: **0** fitted physics parameters. The L(k) power-law slope is a FIT and
  will be reported as a fit.
- Engine namespaces: `bridge` (k_Sun = 686.3, koppa), `law_II` (pressure_domain), `measured`.
- **k convention (committed):** the engine defines k_Sun = 686.3 = c / v_circ(R_Sun) with
  v_circ = 436,762 m/s — the surface CIRCULAR-orbit velocity, NOT the escape velocity. The
  PROMPT's formula "k = c/√(2GM/R)" contradicts its own claim "Sun: k = 686.3" (escape-velocity
  k of the Sun would be 485). We follow the ENGINE (v_circ). Flagged as a prompt inconsistency.
- **GM usage disclosed:** stellar v_circ = √(G·M_sol·(M/M☉)/R) uses G·M☉ as a CONVERSION from
  the catalogue's solar-unit masses (legacy GM_equivalent conversion, permitted for
  conversions only). Equivalent native form: v_circ = v_circ,☉ · √((M/M☉)/(R/R☉)) — the tool
  uses THIS form, so no G appears anywhere.
- **Phase thresholds (committed before run):**
  - T1 (monotonic k-sequence): Spearman rank correlation between k and T_eff-order must
    satisfy |ρ| ≥ 0.90 across the full O–M table for PASS; 0.7–0.9 PARTIAL; below KILLED.
  - T2 (L(k) relation): log-log least squares; "identified" requires R² ≥ 0.90. The slope is
    reported as MEASURED.
  - T3 (solar point): k(G2V) from the table must land within 3% of engine k_Sun = 686.3.
  - T4 (L ∝ M^3.5 emergence): PASS only if the L(k) fit + k-definition REPRODUCE the M–L slope
    without importing the empirical R(M) relation as a separate input. (Analytic expectation:
    impossible, because k ≡ f(M/R) — the test makes the entanglement explicit. Committed to
    reporting this as NOT EMERGENT if so.)
- Forbidden retroactive changes: widen ρ/R² gates; drop table rows after seeing results;
  claim the fitted slope as derived.

## ADJ-001 (data deviation, declared before run)

The prompt asks for ≥50 stars from GAIA DR3 / Torres 2010 / Eker 2018. None of those datasets
exist in this repo and this run has no network. Substitute: **16 canonical main-sequence
spectral-type calibration bins (O5–M8)** — M/M☉, R/R☉, L/L☉, T_eff transcribed from the
standard calibration (Carroll & Ostlie App. G / Pecaut & Mamajek 2013 values, memory-
transcribed, OBSERVED class, ±10–20% per bin). Rank statistics (Spearman, log-log slope) are
robust to bin-level errors of this size; per-star precision claims are NOT made. **Verify
against the printed sources before any publication use.** Prompt criterion "≥50 stars" is
therefore NOT met — completion capped at C by this deviation.

## Run record

- Tool: `sar04_ms_k_gradient.cpp`. Output: `results.txt` = verbatim stdout.
