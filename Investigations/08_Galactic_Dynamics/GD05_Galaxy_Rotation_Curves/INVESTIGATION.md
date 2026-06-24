# GD05: Galaxy Rotation Curves from Eclipse Saturation — Results

> **Status:** EXECUTED — model **does not pass** on real data (honest negative result)
> **Data:** SPARC master table (Lelli, McGaugh & Schombert 2016, AJ 152, 157), 135 galaxies with measured V_flat
> **Model:** Canonical SDT 3D volumetric eclipse-saturation engine (`galactic.hpp::predicted_velocity_3d`, GOM03)
> **Certification:** CALIBRATED (1 fitted parameter: `kappa_area`); zero-parameter status NOT achieved
> **Author:** James Christopher Tyndall, Melbourne
> **Run artifact:** `gd05_run_output.txt` (full console capture)

---

## 1. What was wrong before this run

The previous GD05 pass reported `[SUCCESS] RMS < 20%`. That result was an artifact, for two independent reasons:

1. **Circular test data.** `generate_mock_sparc.py` produced each galaxy's "measured" `v_flat` from the *same* SDT formula (`v = c·√(0.5·koppa_g/r_sat)`) that the test then verified against. The only residual was the 5% Gaussian noise the generator injected — so "RMS ≈ 5%" measured the noise amplitude and nothing else.
2. **Deprecated, calibrated 2D path.** The driver called `v_flat()` / `eclipse_fraction()` / `koppa_gal()`, all marked `[[deprecated]]` in `galactic.hpp`, which bake in the empirical `Sigma_sat = 175 M_sun/pc^2` anchor that GOM03 was written to remove.

This rerun replaces both: **real** rotation velocities from SPARC, fed only the baryonic geometry, through the **3D** model. A built-in self-check confirms the driver's predictor reproduces the committed engine `predicted_velocity_3d` to **0.00% drift**.

## 2. Data provenance

- Source: Vizier catalogue `J/AJ/152/157/table1` (the published SPARC master table; astroweb.cwru.edu was unreachable at run time).
- Per galaxy: `Rdisk` → `h_R`, `Vflat` → observed flat velocity, `Q` → quality flag.
- Baryonic mass (standard SPARC convention): `M_bar = 0.5·L[3.6]·1e9 + 1.33·M_HI·1e9` (Υ*[3.6] = 0.5 M☉/L☉; ×1.33 for helium in the gas).
- Reproducible via `parse_sparc_mrt.py` → `sparc_175.csv`.
- Filtering: `Vflat > 0` and `h_R > 0`, dedupe by name. **135** galaxies (the driver reports 0 dropped — the CSV was already filtered upstream).

## 3. Model (unchanged from GOM03, used as committed)

For baryonic disk `ρ(r,z) = ρ0·e^(−r/h_R)·e^(−|z|/h_z)`:

```
Λ(r)   = M_bar / (4π h_R h_z) · (1 − e^(−r/h_R))      horizontal column
τ(r)   = kappa_area · Λ(r) / m_p                        eclipse optical depth
f_occ  = ½ (1 − e^(−τ))                                 eclipse fraction (→ ½)
v_lim² = c² · (koppa_per_baryon · N_baryons) / (2r)     = G·M_bar / (2r)
v_SDT  = max_r [ v_lim(r) · √(2 f_occ(r)) ]
```

- `koppa_per_baryon = ℓ_P²·c·m_p/ℏ = 1.242e-54 m` — **DERIVED** (reproduces G·M/c² exactly).
- `kappa_area = 9.1e-29 m²` — **CALIBRATED** to the 175 M☉/pc² threshold (≈1.37·σ_Thomson; the code comment says so explicitly).
- `h_z = h_R / 10` baseline (the ratio the calibration assumes; Kregel+2002 give ~7.3 empirically).

## 4. Results (135 galaxies, committed engine, calibrated κ)

| Metric | Value | Target |
|---|---|---|
| RMS residual | **66.0 %** | < 20 % |
| Mean residual (bias) | **+57.6 %** | ~0 |
| Median \|residual\| | 68.0 % | — |
| BTFR slope (SDT) | **1.33** | ~4 |
| BTFR slope (observed data) | 3.19 | 3.5–4.0 |

Positive residual = SDT **under-predicts** v_flat — by roughly a factor of 2–3, for essentially every galaxy (e.g. DDO170 60→6 km/s, ESO079-G014 175→36, UGC12506 234→80, UGCA444 37→1.7). The shortfall is near-uniform across quality classes:

| Quality | n | RMS | bias |
|---|---|---|---|
| Q1 | 87 | 65.4 % | +57.8 % |
| Q2 | 42 | 67.1 % | +61.3 % |
| Q3 | 6 | 67.7 % | +29.7 % |

### Ablation — cross-section `kappa_area`
| κ_area | RMS | BTFR slope |
|---|---|---|
| 0.5×Thomson | 76.8 | 1.32 |
| Thomson σ_T | 69.5 | 1.32 |
| calibrated 9.1e-29 | 66.0 | 1.33 |
| 2× calibrated | 60.4 | 1.33 |
| 10× calibrated | 94.2 | 1.36 |

RMS is non-monotonic (best near 2× calibrated, then sharply worse at 10× as the brightest galaxies flip to over-prediction), but **the BTFR slope is pinned at ~1.3 regardless** — no choice of κ moves it toward 4.

### Ablation — disk axial ratio `h_R/h_z`
| h_R/h_z | RMS | BTFR slope |
|---|---|---|
| 5 | 73.6 | 1.32 |
| 7.3 | 69.5 | 1.32 |
| 10 | 66.0 | 1.33 |
| 20 | 60.4 | 1.33 |

`kappa_area` and `h_z` are **degenerate** — both enter only through the product `kappa_area·(h_R/h_z)` — so they shift RMS in lock-step and neither touches the BTFR slope.

## 5. Why it fails (structural, not a tuning miss)

The velocity law reduces to `v_SDT² = G·M_bar · f_occ / r` with `f_occ ≤ ½`. So the eclipse factor can only ever take the velocity **down** from the baryonic Keplerian scale `√(G·M_bar/r)` — it has no mechanism to supply the *extra* velocity that a flat rotation curve demands (the "missing mass"). Maximising over r picks the baryonic peak attenuated by `√(2 f_occ) ≤ 1`; the result sits a factor of ~2–3 below the observed flat velocity, most visibly for the diffuse dwarfs/LSBs that are precisely the dark-matter-dominated systems. And because `v_SDT` scales as roughly `M_bar / h_R^{1.5}` (fixed by the gravitational sector), the predicted Tully-Fisher slope is locked near 1.3 — the eclipse normalization cannot bend it toward the observed ~3.2 / theoretical ~4.

## 6. Verdict against the GD05 success criteria

- [x] ≥50 galaxies fitted — **135** real SPARC galaxies
- [ ] RMS residual < 20% — **FAIL (66%)**
- [ ] BTFR slope ≈ 4 — **FAIL (1.33)**
- [~] Zero free parameters — **NOT met**: 1 fitted parameter (`kappa_area`), and it doesn't rescue the fit anyway
- [x] Identify which class fails and why — **all classes under-predict ~uniformly**; mechanism caps v at the baryonic Keplerian scale

**Conclusion.** As currently formulated, SDT 3D eclipse saturation does not reproduce galaxy rotation curves: it systematically under-predicts by ~2–3× and yields the wrong Tully-Fisher slope. This is a genuine falsification signal for the *current velocity law*, not a data or implementation problem (self-check drift 0.00%). GD05's own spec anticipates this branch: "If not confirmed: the eclipse saturation model needs refinement."

## 7. What a refinement must change

The fix has to live in the **velocity law**, not the eclipse normalization. Any candidate must (a) allow `v > v_baryonic,Keplerian` at large r, and (b) bend the M_bar–v relation from slope ~1.3 toward ~4. Directions for a follow-up CQ: a response that *amplifies* with optical depth instead of saturating below ½, or a different mapping from eclipse deficit to convergence-pressure imbalance. The gravitational coupling (`koppa_per_baryon`) is sound and should be retained.

## 8. Files

- `gd05_sparc_rotation_curves.cpp` — this driver (real data + canonical model + ablations + self-check).
- `parse_sparc_mrt.py`, `sparc_175.csv`, `sparc_table1.tsv` — real data + reproducible fetch.
- `gd05_run_output.txt` — full console output of the run.
- **Superseded / misleading:** `generate_mock_sparc.py`, `sparc_mock.csv`, `create_real_sparc_sample.py`, `sparc_real_data.csv` (the circular mock and the tiny hand-coded sample). Recommend deletion.
