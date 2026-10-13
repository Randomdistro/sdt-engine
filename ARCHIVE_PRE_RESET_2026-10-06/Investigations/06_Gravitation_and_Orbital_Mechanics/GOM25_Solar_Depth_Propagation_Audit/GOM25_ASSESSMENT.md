# GOM25 Assessment — Solar Depth and Non-Local Propagation

**Date:** 2026-08-07  
**Model version:** engine `depth_closure` as at commit `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom25_solar_depth_audit.cpp`  
**Source SHA-256:** `415c7140f165c20a91bc3efd8777f5fbd04e8d755c906a2e3c94e3612e0fda76`  
**Compiler:** MSVC Build Tools 2022 (`cl /std:c++20 /O2`), VsDevCmd x64  
**Stdout:** `.audit-tmp/gom25_run.txt`  
**Canon edited:** no

## 1. Scope

First data-admissible loop of the master protocol (§XII solar program). Tests the implemented chain

```text
koppa_i = |v_i|² |r_i| / c²
z(r) = koppa / r
c_far = c (1 − z)²
z_spec ≈ koppa / R_Sun   or   koppa(1/R_Sun − 1/r_obs)
```

against frozen Horizons vectors and HARPS-LFC line tables. Does not edit `laws.hpp`. Does not treat agreement with GR as success or failure.

## 2. Coverage status (this iteration)

| Layer | Status |
|---|---|
| Pre-registration | complete (`PROMPT.md`) |
| Dataset freeze + checksums | complete (`Datasets/solar_propagation_2026-08/MANIFEST.md`) |
| Instrument validation A/B/C | PASS |
| D1 orbital depth distribution | executed (27 epochs) |
| D3 spectral comparator | executed with MODEL-PROCESSED warning |
| D4 ranging residual | PENDING_DATA |
| Exact vs leading-order delay | FORMAL only |

## 3. Claim ledger (this loop)

| Claim ID | Exact claim | Status |
|---|---|---|
| GOM25-C1 | Instantaneous `koppa_i = v²r/c²` from EMB–Sun state vectors is the solar depth input | COMPUTED from TRACEABLE DERIVED ephemeris; CV = 1.20% over one year — **not an orbital invariant** |
| GOM25-C2 | Surface spectral shift `v = c·koppa/R_Sun` matches HARPS 638±6 m/s | Numerically **COMPATIBLE** under pre-registered 2σ rule; empirical confirmation capped at **UNADJUDICATED** (CO⁵BOLD / lab-λ nuisances) |
| GOM25-C3 | Depth differential `c·koppa(1/R−1/r)` is the spectral observable | COMPATIBLE vs 638±6; same UNADJUDICATED cap |
| GOM25-C4 | `shapiro_delay()` equals the exact `c_far` path integral | **FORMAL:** solar weak-field relative residue ~1.8×10⁻⁷; leading-order label retained; not observational evidence |
| GOM25-C5 | Cassini ATDF alone adjudicates a Shapiro-like marker | **PENDING_DATA** |
| GOM25-C6 | `c_far` / `depth_from_c_far` defined for all real z | **FORMAL DEFECT:** `z>1` returns positive `c_far` again (unguarded) |

## 4. Mechanism (operational)

State: solar koppa length ϟ, heliocentric radius r, impact parameter b.  
Relay profile: `c_far(r) = c(1 − ϟ/r)²` for `0 ≤ z < 1`.  
Spectral map: dimensionless depth differential → velocity via `v = c z_spec`.  
Timing map: excess light time `∫(1/c_far − 1/c) dl` along a declared path.

## 5. Equations and units

| Symbol | Meaning | Units | Origin in this run |
|---|---|---|---|
| c | SI speed of light | m/s | MEASURED-INPUT (exact) |
| r, v | EMB–Sun geometric state | m, m/s | TRACEABLE DERIVED (DE441) |
| ϟ | `v² r / c²` | m | COMPUTED |
| R_Sun | IAU nominal / Haberreiter | m | CONVENTIONAL / OBSERVED |
| z | ϟ/r | 1 | DEFINITION |
| c_far | c(1−z)² | m/s | DERIVED (engine relation 2) |
| v_spec | c z_spec | m/s | COMPUTED prediction |

## 6. Initial / boundary conditions

- Domain: `0 ≤ z < 1` enforced in the instrument; engine function unguarded.  
- Path: straight-line superior-conjunction geometry for formal delay integral only.  
- Endpoint sync / one-way vs two-way: **not** fixed for D4 (blocked on data readiness).  
- Orbital invariant: **not** stated in the tested instantaneous formula — see root cause §17.

## 7. Parameter ledger

| Input | Value | Label |
|---|---:|---|
| D1 mean ϟ | 1477.262 m | COMPUTED |
| D1 ϟ CV | 1.196% | COMPUTED |
| engine `bridge::koppa_Sun` (unused) | 1477.046 m | DERIVED (engine); delete-test only |
| R_Sun IAU | 6.957×10⁸ m | CONVENTIONAL |
| R_Sun phot | (6.95658±0.00140)×10⁸ m | OBSERVED |
| HARPS paper summary | 638 ± 6 m/s | OBSERVED summary |
| HARPS a2 EW&lt;180 recompute | 642.44 ± 0.35 m/s | OBSERVED + MODEL-PROCESSED |

## 8. Data provenance

See `Datasets/solar_propagation_2026-08/MANIFEST.md`. Full SHA-256 recorded for every raw file. Cassini TDF checksum verified; content not decoded.

## 9. Pre-registration

`PROMPT.md` fixed decision rules before this instrument executed. No tolerance widening after comparison. No coefficient introduced after comparison.

## 10. Instrument validation

| Test | Result |
|---|---|
| A unit conversion / circular mock | PASS (0 relative error) |
| B path-integral step refinement | PASS (1.4×10⁻¹²) |
| C inverse branch on `0≤z<1` | PASS |
| C unguarded `z>1` | FORMAL DEFECT confirmed |

## 11. Commands

```text
call "...\VsDevCmd.bat" -arch=x64 -host_arch=x64
cl /nologo /std:c++20 /EHsc /O2 /I Engine\include ^
  /Fe:.audit-tmp\gom25.exe ^
  Investigations\06_Gravitation_and_Orbital_Mechanics\GOM25_Solar_Depth_Propagation_Audit\gom25_solar_depth_audit.cpp
.audit-tmp\gom25.exe
```

## 12. Full-range results

| Quantity | Mean | Min | Max |
|---|---:|---:|---:|
| ϟ_i [m] | 1477.26 | 1452.10 | 1501.29 |
| v_pred (IAU R) [m/s] | 636.58 | 625.74 | 646.94 |
| v_pred (phot R) [m/s] | 636.62 | — | — |
| v_pred (depth diff) [m/s] | 633.62 | — | — |

All four pre-registered spectral comparisons satisfy `|Δ| < 2σ_combined` → COMPATIBLE.

## 13. Delete / circularity

Prediction path does not call `bridge::koppa_Sun`, `GM`, or `shapiro_delay` for the spectral test. Difference between D1 mean ϟ and unused engine ϟ is 1.5×10⁻⁴ relative. GOM22’s prior construction of a “measured” delay from `GM/c²` remains excluded as empirical evidence (MASTER ledger item).

## 14. Formal stress

- Dimensional closure of `ϟ = v²r/c²`: OK.  
- Domain wall at z=1: formula zero, inverse undefined for `c_far≤0`; values `z>1` incorrectly revive positive `c_far`.  
- Weak-field limit: numerical ≈ leading log to 10⁻⁷.  
- Strong-field / horizon fork (`c(1−z)²` vs `c(1−2z)`): not probed by solar data (as previously recorded).

## 15. Empirical comparison

Solar spectral amplitude is numerically compatible with the depth map under the stated inputs. Because the primary line-shift product embeds a 3D atmospheric model, this loop does **not** promote the claim to EMPIRICALLY SURVIVES.

## 16. Classification summary

- EMPIRICALLY SURVIVES: none in this loop  
- EMPIRICALLY EXCLUDED: none in this loop  
- COMPATIBLE / UNADJUDICATED: GOM25-C2, C3  
- FORMAL DEFECT: GOM25-C6; GOM25-C4 labelled LEADING_ORDER  
- PENDING_DATA: GOM25-C5  
- COMPUTED / TRACEABLE DERIVED: GOM25-C1  

## 17. Root-cause analysis (seven questions)

**On instantaneous koppa scatter (mechanism debt, not empirical exclusion):**

1. Failed exactly: magnitude stability — ϟ varies ±1.2% over the year.  
2. Observable: a constant solar surface depth should not inherit Earth’s orbital eccentricity sampling.  
3. Premise: identifying solar ϟ with instantaneous `v²r/c²` on an elliptical state vector.  
4. Local to the orbital → depth map; spectral residual absorbs it into prediction σ.  
5. Freedom: replace instantaneous form by an orbital invariant (e.g. time-averaged or vis-viva `a`-based ϟ) stated before comparison.  
6. That freedom is DERIVED from orbital geometry, not a bare knob — if pre-registered.  
7. Downstream: any claim using a single solar ϟ (redshift, Shapiro, lensing) inherits the same IC debt until the invariant is fixed.

**Recovery class:** PARTIAL — repair route clear; requires a new pre-registration and held-out check (e.g. multi-year invariant stability, then spectral re-test without widening σ by the elliptic CV).

## 18. Cascade ledger update

| Downstream | Impact |
|---|---|
| GOM22 “247.24 μs measured” | Remains non-empirical; D4 still PENDING_DATA |
| `depth_closure::shapiro_delay` | Remains LEADING_ORDER approximation of `c_far` integral |
| Engine C1 solar redshift headline | Numerically compatible; confirmation still UNADJUDICATED |
| Benchmark earned-count (F-01/F-02) | Unchanged; orthogonal formal findings stand |
| Public solar-propagation claims | Must cite COMPATIBLE/UNADJUDICATED + PENDING_DATA, not “measured Shapiro from profile” |

## 19. Reformulation (proposed, not applied)

Smallest repair: define

```text
ϟ_Sun := ⟨v² r / c²⟩_T   or   ϟ_Sun := n² a³ / c²
```

from the same Horizons vectors, freeze it as the sole solar depth input, re-run spectral and formal delay tests, and demand a new held-out marker (impact-parameter scan or multi-messenger timing) before any EMPIRICALLY SURVIVES label.

## 20. Re-audit of reformulation

Not executed this iteration (no canon edit; repair remains OPEN pending explicit authorization to adopt an invariant definition in the investigation record and re-run).

## 21. Impact on open-problem / benchmark ledgers

Adds IC debt “solar ϟ orbital invariant” beside existing open items (B15/B16/B25 literals; unguarded domain; Shapiro data readiness).

## 22. Remaining debt and next highest-value test

1. **Decode Cassini SCE1 ATDF + reconstruct geometry** to obtain an admissible one-way/two-way residual (D4). Highest information value for the coupled lensing/delay program.  
2. Pre-register orbital-invariant ϟ and re-run GOM25 spectral test with held-out year.  
3. Shared-profile solar deflection vs impact parameter (no retuning after spectral freeze).  
4. Continue benchmark detox (B15/B16/B25) in parallel — formal, not empirical.


## Solar-koppa extension

**Date:** 2026-08-07  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Pre-registration:** `PROMPT_B_INVARIANT_KOPPA.md`  
**Instrument SHA-256:** `095de47c3fcaefbd303dea6ddadbf69a09555617b695d7c49e9c6387bde0e4f9`  
**Stdout:** `.audit-tmp/gom25b_run.txt`  
**Canon edited:** no

## Failed model frozen

Instantaneous `ϟ_i = v_i² r_i / c²` (GOM25): mean 1477.26 m, **CV = 1.196%**.

## Repair executed

```text
a = (r_min + r_max)/2
ϟ_vv,i = v_i² / [c² (2/r_i − 1/a)]
ϟ_Sun = mean(ϟ_vv,i)
```

No `G`, `M`, or `bridge::koppa_Sun` in the prediction path.

## Validation

| Test | Result |
|---|---|
| Circular mock ϟ_inst = ϟ_vv | PASS (1.5×10⁻¹⁶) |
| Elliptic mock CV_vv ≪ CV_inst | PASS (0 vs 1.18%) |

## Hold-out / quality gates (pre-registered)

| Gate | Value | Threshold | Result |
|---|---:|---:|---|
| CV_vv / CV_inst (2025) | 1.15×10⁻⁵ / 1.20×10⁻² | CV_vv < 0.1 CV_inst | PASS |
| H1 vs H2 \|Δ\|/ϟ | 6.98×10⁻⁶ | < 5×10⁻⁴ | PASS |
| 2024 vs 2025 \|Δ\|/ϟ | 2.20×10⁻⁵ | < 5×10⁻⁴ | PASS |

2024 Horizons table frozen:  
`raw/jpl_horizons_emb_sun_vectors_2024.csv`  
SHA-256 `bae3494660ca2dee27e70b6baebf631396f03940c2018946dc3952a49a5c0de4`.

## Spectral re-test

| Quantity | Value | Label |
|---|---:|---|
| ϟ_Sun (2025) | 1476.664 m | COMPUTED |
| σ_ϟ (hold-out) | 0.023 m | COMPUTED |
| v_pred depth-diff (IAU R) | 633.37 ± 0.13 m/s | COMPUTED |
| v_obs (HARPS summary) | 638 ± 6 m/s | OBSERVED + MODEL-PROCESSED deps |
| Decision | COMPATIBLE (\|Δ\|=4.63 < 2σ=12.00) | confirmation still **UNADJUDICATED** |

Prediction σ no longer inflated by elliptic instantaneous CV.

## Classification

| Item | Status |
|---|---|
| Instantaneous-ϟ IC debt | **RECOVERED** at investigation level (held-out) |
| Canon `bridge::koppa_Sun` | unchanged; propose-and-wait if adoption desired |
| Spectral depth map | COMPATIBLE / **UNADJUDICATED** |
| New freedom class | DERIVED from state-vector geometry (`a` from r extrema) |

## Root-cause closure (seven questions — repair audit)

1. Failure was magnitude instability of instantaneous ϟ (±1.2%).  
2. Observable: solar surface depth should not track EMB eccentricity.  
3. Premise: `ϟ = v²r/c²` instantaneous.  
4. Local to orbital→depth map.  
5. Freedom: vis-viva invariant with geometric `a`.  
6. Freedom is DERIVED (no fitted amplitude).  
7. Downstream: redshift, Shapiro, lensing should consume invariant ϟ, not instantaneous.

## Remaining debt

1. Cassini/admissible delay residual still PENDING_DATA.  
2. Shared-profile deflection vs impact parameter not yet run.  
3. Residual CV ~10⁻⁵ may reflect `(r_min+r_max)/2` vs true SMA and EMB lunar wobble — register as second-order open if a tighter invariant is needed.  
4. Spectral confirmation still blocked by atmospheric/lab-λ pipeline.
