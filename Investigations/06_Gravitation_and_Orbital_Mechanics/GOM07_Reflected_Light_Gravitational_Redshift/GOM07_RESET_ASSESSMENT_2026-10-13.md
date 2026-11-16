# GOM07 (reflected-light redshift; stamp versus observer term) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `gom07_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `GOM07/PROMPT.md` in full (the three questions; §0 reader's contract; phases P0–P3; falsifiers); the first sections of `INVESTIGATION.md` (the thesis: emission stamp versus gradual climb; the statement that rigorous cancellation-GR also predicts flat); `Engine/include/sdt/laws.hpp` `depth_closure` (z_spectral = z_emit − z_obs, clock_rate 1 − z, z_spectral_Sun = ϟ_Sun/R_Sun); the repo lines that take a side (a grep of `Engine/`, `Papers/`, `Theory/`, `Laws/`, the benchmarks and the E102/E107 folders for z_spectral, emission stamp, observer term); GOM26, GOM27 and GOM39 of this programme (ϟ_Sun = 1476.351 m). Not read: the three old scripts and their rerun outputs (`gom07_*`), the archived verdict. The prompt quotes the earlier slope "−1.11 ± 1.28" and "Io−Callisto 0.78 m/s"; they are used only as the prompt's stated gate and known answer.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | data | P0 asks for the provenance of the Lanza et al. (2016) table and P1 for its regression. The table is not in the repository (the datasets folder has no Lanza file). P0's provenance print and P1's Part-B regression are **PENDING_DATA**; a fetch is a separate decision (published table, no machine-readable source named). The gates "slope within ±0.2 of −1.11" would compare with an earlier result and are not evaluable here. |
| D2 | computable | The §3 prediction table (SDT-flat 633.35 against the naive-climb column), P2 (cost-benefit of ±0.2 m/s) and P3 (the formalisation of both readings at three benchmarks, the list of repo lines, the decision matrix) need no table. |
| D3 | inputs | Planetary depths ϟ = M/m_p × `koppa_per_baryon` (the native census route, no G): masses from `Datasets/solar_system/solar_system_mass_inventory.md` (four significant figures); the Sun's ϟ = 1476.351 m (GOM26) and the engine's `bridge::koppa_Sun` for comparison. Radii and moon orbital radii are **not in the repository**: entered as census inputs (Venus 6.0518×10⁶ m, Jupiter equatorial 7.1492×10⁷ m, Earth 6.371×10⁶ m, Io orbit 4.217×10⁸ m, Callisto orbit 1.8827×10⁹ m), typed from standard values and labelled as such, to be verified against a source file; the results quoted to 1% are insensitive to their last digits. |
| D4 | readings | Stamp reading S: the shift observed is c·z_emit, with z_emit the total depth at the emission point. Observer-term reading O (the engine's z_spectral): c·(z_emit − z_obs), z_obs the depth at the observer. For the weak-field additive case the total depth at a point is the sum of the wells there (Sun's well plus the body's own). Each benchmark is computed under both. |
| D5 | contract | E107's death (any shared-redshift fork between SDT and GR is degenerate when the observer term is kept) is controlling: no shared-redshift fork is proposed; the only open ground is observer-position dependence. P3 is propose-only: no edit of `laws.hpp` or the Depth-Closure paper. |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Reflection table.** c·z for: the Sun (ϟ = 1476.351 m, R = `measured::R_Sun`); the naive-climb additions c ϟ_body/R_body for Venus and Jupiter; for the Galilean moons the jovian depth at the orbital radius c ϟ_J/a (naive-climb reflection from a moon's own well is added with ϟ_moon/R_moon, reported). Known-answer check: c ϟ_J (1/a_Io − 1/a_Callisto) against the prompt's 0.78 m/s within 5%.
**P2.** The precision that separates the naive-climb Jupiter prediction from the flat one (c ϟ_J/R_J) in units of the stated floor 1.5 m/s, and what ±0.2 m/s resolves for the Io−Callisto gradient (0.78 m/s).
**P3 benchmarks.** (B1) the solar surface seen from Earth; (B2) the solar surface seen from 0.046 AU (Parker depth); (B3) Jupiter's ionosphere emission seen from Earth. For each: z_emit (own well plus the Sun's well at that distance), z_obs (the observer's own well plus the Sun's well at the observer), S = c z_emit, O = c (z_emit − z_obs), their difference, and the size of the observer term.
**Repo lines.** The grep result is listed with the side each line takes.
**Decision.** Per the prompt: P3 ends in a matrix with the costs of each option; no unilateral choice. If S and O agree to < 1 mm/s at every benchmark the tension is illusory (F2). F3: no canon file is edited.
**Expected landing (hand estimate before registering).** c ϟ_Sun/R_Sun = 636.2 m/s (GOM26); B1: S 636.2, O 633.2 (observer term 3.0 m/s, the Sun's well at 1 AU plus Earth's own 0.2 m/s); B2: S 636.2, O 571.8 (observer term 64 m/s); B3: S about 6.5 m/s, O about 3.3 m/s; Io−Callisto 0.78 m/s.

## 3. Results (COMPUTED / propose-only; `gom07_reset_1.cpp`, output `gom07_reset_1_results.txt`, memo `GOM07_STAMP_VS_OBSERVER_2026-10-13.md`; single pass, no amendment)
**P0/P1: PENDING_DATA.** The Lanza 2016 table is not in the repository; the provenance print and the Part-B regression (and the gates against the earlier slope) are not evaluated.
**§3 prediction table.** c·ϟ_Sun/R_Sun = 636.192 m/s (GOM26 invariant; the engine's `bridge::koppa_Sun` gives 636.492). Naive-climb additions: Venus +0.179 m/s (636.371); Jupiter +5.909 m/s (642.102). **Known answer: Io − Callisto = 0.7774 m/s against the prompt's 0.78 (within 0.3%: met)**; with the moons' own wells 0.7784. The planetary depths from N_b × `koppa_per_baryon`: Jupiter 1.4092 m, Venus 3.61 mm, Earth 4.43 mm.
**P2.** Jupiter's 5.91 m/s is 3.94 × the stated 1.5 m/s floor; Io − Callisto 0.777 m/s is 3.9σ for ±0.2 m/s. A follow-up buys the refutation of the naive one-way climb only.
**P3.** Stamp S / observer-term O (m/s): B1 636.192 / 633.025 (observer term 3.167); B2 (0.046 AU) 636.192 / 571.875 (64.317); B3 (Jupiter H₃⁺) 6.478 / 3.311 (3.167). The readings differ by the observer term at every benchmark: **F2 does not fire; the tension is real.** The repo takes both sides (formula (4) and the papers say O; `z_spectral_Sun`, the B-suite value and the `clock_rate` comment compare the stamp with the measured value, i.e. S); a stale line `dτ/dt = √(1 − z)` remains in `02_EPJC_DRAFT.md` line 79. The decision matrix and the ruling requested are in the memo.
The expected landing held in every item (636.2; 633.2 against found 633.0 because the observer term includes Earth's own well; 571.8; B3 6.5 and 3.3; 0.78).

## 4. Grades
| Item | Grade |
|---|---|
| P0, P1 (Lanza table and regression) | **PENDING_DATA** |
| §3 prediction table, Io − Callisto known answer | **COMPUTED, met (0.3%)** |
| P2 cost-benefit | **COMPUTED: 3.9σ at the stated floors; kills only the naive climb** |
| P3 tension | **real (S and O differ by the observer term, 3.2 to 64 m/s)**; matrix filed; **ruling requested** (propose-only, no canon edit) |
| F3 canon edited | **no** |

## 5. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
