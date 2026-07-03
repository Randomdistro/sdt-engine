# RUN_LOG — NP12: Nuclear Charge Radius Scaling (Z-linear vs A^1/3)

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE the analysis tool.**
> Terminology: "charge radius" appears ONLY as the rival instrument label ⟦R_ch, RMS charge
> radius⟧ for the measured data column; SDT-side quantities are boundary radii.

## Data (REAL, downloaded — not simulated)

- `charge_radii_iaea.csv` — downloaded 2026-07-03 from IAEA, `https://www-nds.iaea.org/radii/charge_radii.csv`
  (the Angeli & Marinova 2013 ADNDT compilation as served by IAEA, 957 records + header).
- Filter committed: Z ≥ 1, `radius_val` present and > 0 (drops the neutron row and blanks).
- Success criterion from PROMPT: N ≥ 250 isotopes. (File has ~900; will report actual N.)
- Data are **RMS** radii ⟨r²⟩^{1/2}. Pre-declared consequence: the PROMPT's rival "1.2·A^(1/3)"
  is the equivalent-sharp-surface convention, NOT an RMS quantity — it is expected to
  overshoot RMS data by ≈ √(5/3) ≈ 1.29. Both forms are scored (M2, M3 below) so the rival
  is not strawmanned.

## Committed models (all fixed BEFORE any fit/metric is computed)

| ID | Formula (fm) | Provenance | Params |
|----|--------------|-----------|--------|
| M1 | R = Z · R_p (R_p = 0.8414) | SDT canon (`nuclear::nuclear_charge_radius`, laws.hpp) | 0 |
| M2 | R = 1.2 · A^(1/3) | PROMPT's rival as written (sharp-surface convention) | 0 |
| M3 | R = √(3/5) · 1.2 · A^(1/3) = 0.9295 · A^(1/3) | unit-consistent rival (RMS of uniform sphere of M2 radius) | 0 |
| M4a | R = √(3/5) · R_p · (A/η)^(1/3) = 0.7207 · A^(1/3), η = π/√18 | SDT-native recovery candidate, uniform-charge limit: A nucleon spheres of radius R_p close-packed (NP17 3D packing), charge uniform | 0 |
| M4b | R = R_p · (A/η)^(1/3) = 0.9304 · A^(1/3) | same cluster, surface-charge limit (committed rationale: p-p handed-redirection repulsion pushes protons to the periphery; direction native, strength un-derived) | 0 |
| M5 | R = k_Z · Z^(1/3), k_Z fitted | diagnostic only — CALIBRATED(1), motivated a priori by the chain-flatness logic (if N does not move ⟦R_ch⟧, the third natural scaling is Z^(1/3)) | 1 |

**Pre-declared degeneracy:** M4b (0.9304·A^(1/3)) and M3 (0.9295·A^(1/3)) differ by 0.09% —
this dataset CANNOT distinguish them. If M4b fits, its class ceiling is CONVERGENCE/DEGENERATE
with the rival's fair form; the SDT content would be *deriving the coefficient* from
{R_p, π/√18} with zero fitting — not beating the rival's curve shape.
**Pre-declared bracket rule:** M4a/M4b are limits; picking one after seeing metrics is
forbidden. Both are reported; landing of one limit = bracket-consistency, NOT a PASS.

## Committed metrics + gates

- Phase B: N, RMS absolute (fm), RMS relative (%), R² for every model, full set + Z-bands
  (1–8, 9–20, 21–50, 51–92). Winner = lowest RMS relative. Expected honest outcome, declared
  now: **M1 loses catastrophically** (linear-Z vs cube-root data); if RMS(M1) > 3× the best
  zero-param model, **M1 = KILLED as a global law** (canon impact: `nuclear::` — report,
  propose-and-wait, NO canon edit).
- Phase C gates (PROMPT, committed): chain spread (max−min)/mean of ⟦R_ch⟧ for Ca (Z=20),
  Sn (Z=50), Pb (Z=82): **< 2%** → Z-constancy essentially correct within chains; **> 5%** →
  A^(1/3) captures chains better. Also print each chain's A^(1/3)-predicted spread for the
  same A-range (committed comparison — flatness cuts BOTH ways).
- Phase D: mean |residual| vs best A^(1/3)-family model at magic Z ∈ {2,8,20,28,50,82} vs
  non-magic — report only (no gate).
- Phase E: R/Z vs Z (M1 predicts constant 0.8414): report min/median/max and monotone drift.

## Forbidden retroactive changes
Choosing M4a-vs-M4b post hoc; adding models after metrics are seen; softening the KILL rule;
editing laws.hpp; fitting anything beyond the declared k_Z.

## Planned outputs
`np12_radius_scaling.py` (python; reads the CSV + engine values cited inline) →
`np12_results.txt` (redirected stdout) → `NP12_VERDICT.md`.
