# GOM26 Assessment — Solar Koppa Orbital Invariant

**Date:** 2026-08-07  
**Model version:** investigation-level Keplerian invariant IC (no `laws.hpp` edit)  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom26_koppa_invariant.cpp`  
**Source SHA-256:** `D86CBF15D14802D5AB1423AAA4D2BA2583AEB54742EA4E98FC8EC1853494494E`  
**Compiler:** MSVC via VS 2022 Build Tools, `/std:c++20 /O2`  
**Stdout:** `.audit-tmp/gom26_run.txt`  
**Canon edited:** no

## 1. Scope

Re-audit of the GOM25 §19 reformulation: replace instantaneous `ϟ_i = v²r/c²` by a Keplerian orbital invariant `ϟ = μ/c²` recovered from EMB–Sun state vectors.

## 2. Coverage status

| Layer | Status |
|---|---|
| Pre-registration | complete (`PROMPT.md`) |
| Instrument validation A/B | PASS |
| D1-cal invariance (C1/C2) | executed — gate PASS |
| Hold-out (C4) | **Multi-year PASS** — 2024 EMB(3) vs Sun(10) frozen (`c194718c…`); see Iteration 7 / `.audit-tmp/gom26_multiyear_run.txt` |
| Spectral (C3) | COMPATIBLE; confirmation UNADJUDICATED |
| D4 ATDF / ODF | TDF STRUCTURE_PARTIAL; ODF STRUCTURE_PASS (GOM28) — residual still PENDING_DATA |

## 3. Claim ledger

| Claim ID | Status |
|---|---|
| GOM26-C1 | **DERIVED / formal gate PASS** — CV(`ϟ_i`) ≈ 1.06×10⁻⁵ ≪ 10⁻³ on 2025 calibration year |
| GOM26-C2 | **DERIVED** — full-year `μ_cal = 1.326881×10²⁰ m³/s²` → `ϟ = 1476.354 ± 0.058 m` |
| GOM26-C3 | **COMPATIBLE / UNADJUDICATED** — `v_pred = 636.194 ± 0.025 m/s` vs `638 ± 6 m/s` |
| GOM26-C4 | **COMPATIBLE** multi-year — `ϟ_2024 = 1476.872 m`; `\|Δϟ\|/ϟ = 3.51×10⁻⁴ < 10⁻³` (DE441 construction check, not SDT empirical survival) |
| GOM26-D4 | **PENDING_DATA** — residual not reconstructed |

## 4–7. Mechanism, equations, ICs, parameters

As pre-registered in `PROMPT.md`. Constitutive premise: two-body energy conservation on the relative orbit. Not an SDT-derived law; it is the repair’s kinematic assumption.

| Input | Value | Label |
|---|---:|---|
| `ϟ_cal` | 1476.348 m | DERIVED |
| `σ_ϟ` | 0.117 m | COMPUTED (robust SE) |
| CV recon (cal) | 9.94×10⁻⁶ | COMPUTED |
| CV inst (cal) | 1.18×10⁻² | COMPUTED (GOM25 debt) |
| `v_pred` (IAU R) | 636.191 m/s | COMPUTED |
| HARPS summary | 638 ± 6 m/s | OBSERVED summary + MODEL-PROCESSED nuisances |

## 8. Data provenance

- D1-cal: existing GOM25 Horizons EMB–Sun 2025 file (checksum in solar_propagation MANIFEST).
- D1-hold multi-year: first retrieval was **Earth-centered** (Caussols) — quarantined as wrong-center; subsequent API attempts returned VLADD errors. Pre-registered INTRA_YEAR fallback used.
- D3: paper summary only (same as GOM25).
- D4: TDF byte-count matches label; not a timing product.

## 9–11. Pre-registration / validation / commands

```text
cl /nologo /std:c++20 /EHsc /O2 /I Engine\include /Fe:.audit-tmp\gom26.exe ^
  Investigations\...\GOM26_...\gom26_koppa_invariant.cpp
.audit-tmp\gom26.exe Datasets\...\jpl_horizons_emb_sun_vectors_2025.csv INTRA_YEAR
```

Validation A/B PASS before targets.

## 12–15. Results, delete-test, formal, empirical

- Instantaneous CV 1.18% → reconstructed CV 9.9×10⁻⁶ (three orders collapse).
- Delete-test: `bridge::koppa_Sun` printed unused (1477.046 m); HARPS not an input to `μ`.
- Spectral amplitude remains numerically compatible with tighter `σ_pred` (no elliptic CV inflation).
- No EMPIRICALLY SURVIVES promotion (atmosphere/lab-λ nuisances unchanged).

## 16. Classification summary

- Empirically surviving predictions: none newly earned  
- Empirically excluded: none  
- Formal recovery of IC definition: **RECOVERED** at investigation level under Keplerian premise + INTRA_YEAR hold-out  
- Unadjudicated: spectral mechanism confirmation  
- Pending data: multi-year Sun-centered hold-out; Cassini residual  
- Open: canon adoption of invariant `ϟ`; shared-profile deflection scan  

## 17. Root cause (seven questions) — GOM25 elliptic CV

1. Failed: magnitude stability of instantaneous `v²r/c²` (±1.2%).  
2. Observable: constant solar depth should not track Earth eccentricity sampling.  
3. Premise: identifying solar `ϟ` with instantaneous elliptical samples.  
4. Local to orbital→depth map.  
5. Freedom: Keplerian invariant `ϟ=μ/c²` from the same vectors.  
6. Freedom class: DERIVED under stated two-body premise (not a bare knob).  
7. Downstream: redshift, Shapiro, lensing claims that freeze a single solar `ϟ`.

**Recovery class:** RECOVERED (investigation IC) with stated premises and hold-out caveat.

## 18. Cascade

| Downstream | Impact |
|---|---|
| GOM25-C1 | Instantaneous form remains COMPUTED but superseded as preferred IC by GOM26 invariant for future shared-profile tests |
| Engine `bridge::koppa_Sun` | Numerically close (1477.05 vs 1476.35); canon unchanged |
| Spectral public claims | Still COMPATIBLE/UNADJUDICATED |
| Shapiro/D4 | Still PENDING_DATA |

## 19–20. Reformulation / re-audit

This iteration *is* the re-audit. No further coefficient introduced. Next reformulation not required for the IC debt; next leverage is D4 residual + deflection scan using frozen `ϟ_cal`.

## 21–22. Remaining debt / next tests

1. Retrieve valid multi-year EMB–Sun vectors (Sun center) and re-run C4 without INTRA_YEAR.  
2. TRK-2-25 decode + geometry/clock for Cassini SCE1 residual (highest information for §XII).  
3. Shared-profile solar deflection vs impact parameter with frozen invariant `ϟ`.  
4. Benchmark detox (B15/B16/B25) in parallel.
