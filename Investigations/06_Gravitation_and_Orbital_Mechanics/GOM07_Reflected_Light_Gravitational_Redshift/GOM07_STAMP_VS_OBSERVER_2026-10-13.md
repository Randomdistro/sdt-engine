# GOM07 P3: emission stamp versus observer term — decision memo for Harvey (2026-10-13)

Propose-only. No canon file is edited. Numbers from `gom07_reset_1.cpp` (output `gom07_reset_1_results.txt`); depths ϟ = N_b × `koppa_per_baryon` (no G) for the planets, ϟ_Sun = 1476.351 m (GOM26). Radii and moon orbits for the planets are census inputs typed from standard values (to be checked against a source file).

## The two readings
- **S (emission stamp).** The shift observed is c·z_emit, set at the source and not re-acquired on the way or at arrival; z_emit is the total depth at the emission point.
- **O (observer term; the engine's `depth_closure::z_spectral`).** The shift is c·(z_emit − z_obs), the depth differential between emitter and observer.

## Numbers (m/s)
| Benchmark | S | O | observer term |
|---|---|---|---|
| B1 solar surface seen from Earth | 636.192 | 633.025 | 3.167 |
| B2 solar surface seen from 0.046 AU (Parker depth) | 636.192 | 571.875 | 64.317 |
| B3 Jupiter ionosphere (H₃⁺) seen from Earth | 6.478 | 3.311 | 3.167 |
The readings do not converge anywhere: they differ by the observer term (F2 does not fire; the tension is real).

## What each option costs
| | Option A: keep the observer term (O) | Option B: pure stamp (S) |
|---|---|---|
| Solar reference | 633.03 m/s: within 0.3 m/s of the prompt's 633.35 baseline; the local reference (638 ± 6, the gate used in GOM26) cannot separate 633.0 from 636.2 | 636.19 m/s: 3.2 m/s (0.5%) above O and 2.8 m/s above the 633.35 baseline; also inside 638 ± 6 |
| Relation to GR | **O is the GR form** wherever a shared redshift is measured: E107's death generalises; no shared-redshift observable can ever fork SDT from GR; the genuine split can only be observer-position dependence | S differs from GR by the observer term: **B2 differs by 64 m/s** (a Parker-class measurement would decide), B1/B3 by 3.2 m/s |
| Reflection (GOM07 proper) | flat (the reflector's well cancels), same as cancellation-GR: the test refutes only the naive climb | flat by construction; same refutation of the naive climb only |
| Repo lines that must change | none for z_spectral; the comment at `laws.hpp` clock_rate ("reproduces 636.3 m/s against 633 measured") and `depth_closure::z_spectral_Sun` compare the **stamp** to the measured value, which is reading S: reword to O (633.0) or label as the stamp | `laws.hpp` formula (4) `z_spectral(z_emit, z_obs)` and `SDT_LLM_UPTAKE.md` line 185 and `Papers/Depth_Closure_Theorem/02_EPJC_DRAFT.md` line 79 (z_spectral = z_emit − z_obs) must drop the observer term; the GOM25/GOM26 amendments (observer term) are then withdrawn; Corollary C1 stays (it is the stamp) |
| Risk | SDT's solar C1 ("0.03%") is the stamp; its comparison with the observed 633 is already 0.5% off in S and exact in O: Option A puts the observed-side number within 0.3 m/s of the 633.35 baseline | B2 has a differentiating prediction (a testable fork) at the price of departing from GR at the Parker depth by 64 m/s |

## The repo takes both sides today
- `laws.hpp` formula (4) `z_spectral = z_emit − z_obs` (O) and `depth_closure::z_spectral_Sun = ϟ_Sun/R_Sun` (S, the benchmark B-suite value 2.1225e-6 at line 1227 of `benchmarks_suite.cpp`), and the `clock_rate` comment (S compared with the measured value).
- `SDT_LLM_UPTAKE.md` (O), `02_EPJC_DRAFT.md` (O), GOM07 `INVESTIGATION.md` thesis (S: "set at emission, stable").
- **Stale line found on the way:** `02_EPJC_DRAFT.md` line 79 still carries dτ/dt = √(1 − z), which the engine replaced by (1 − z) in GOM22 (the √ gives half the measured solar redshift).

## P2 (cost-benefit of an ESPRESSO-class follow-up)
Jupiter's naive-climb addition is 5.91 m/s, 3.9 × the stated 1.5 m/s floor; Venus 0.18 m/s; the Io − Callisto gradient 0.777 m/s (reproducing the prompt's 0.78) needs ±0.2 m/s to reach 3.9σ. What it buys: the refutation of the **naive one-way climb** only. What it cannot buy: any separation of the emission stamp from cancellation-GR (both flat), or of S from O (a shared redshift measured at one observer).

## Ruling requested
Which reading is the framework's (A or B); if B, the observer-position test at a Parker-class depth (B2, 64 m/s) is the single place where the choice is empirical.
