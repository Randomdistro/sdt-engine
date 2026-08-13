# NP12d — Topology → charge second moment (IAEA sealed)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT claim investigation (formal + topology census).  
> **Upstream:** NP12c `MAP_UNDERIVED`; user strengthening — boundary not a sufficient state variable.  
> **Canon edits:** none. **IAEA:** sealed (not opened).

## 0. Objective

1. Prove, without IAEA, that **boundary radius alone does not uniquely determine**
   RMS charge radius (underdetermination).  
2. Redirect the native object from scalar `R_boundary → k·R_boundary` to

```text
nuclear topology → ρ_q(r) → R_RMS
```

with

```text
r_q = ∫ r ρ_q d³r / ∫ ρ_q d³r
R_RMS² = ∫ |r − r_q|² ρ_q d³r / ∫ ρ_q d³r
```

and point-proton reduction when proton centres `{r_i}` exist:

```text
R_{p,RMS}² = (1/Z) Σ_i |r_i − r̄_p|²
```

3. Validate the RMS instrument on analytic fixtures only.  
4. Inspect ATOMICUS / packing / engine topology. Classify one of three outcomes
   (below). No fit. No `√(3/5)` smuggled as a conversion coefficient for NP12.

## 1. Underdetermination claim (pre-data)

Assume charge support inside a ball of radius `R_B`. For normalized non-negative
`ρ_q`,

```text
R_RMS² = ∫ r² ρ_q d³r / ∫ ρ_q d³r
```

Same `R_B`, different answers:

| Density | `R_RMS` |
|---|---|
| uniform ball | `√(3/5) R_B` |
| thin surface shell | `R_B` |

Family `μ_λ = (1−λ) δ_0 + λ σ_{R_B}`, `0 ≤ λ ≤ 1`:

```text
R_RMS(μ_λ) = R_B √λ
```

so every value in `[0, R_B]` occurs at fixed `R_B`.

Therefore: **`R_B` is not a sufficient state variable for `R_RMS`.**

If `nuclear_boundary_radius` is only a mechanical/exclusion boundary (not a charge
support bound), even `R_RMS ≤ R_B` is **not established**.

## 2. Instrument validation (analytic fixtures)

| Fixture | Expected |
|---|---|
| Central point | `R_RMS = 0` |
| Thin shell radius `R` | `R_RMS = R` |
| Uniform sphere radius `R` | `R_RMS = √(3/5) R` (geometry of fixture, not an NP12 conversion) |
| Known discrete points | analytic point-set RMS |
| Translation invariance | `R_RMS` unchanged under `r → r+a` |
| Rotational invariance | unchanged under orthogonal `Q` |
| Uniform scale `r → s r` | `R_RMS → s R_RMS` |

## 3. Topology census outcomes (exactly one)

| ID | Outcome |
|---|---|
| O1 | Topology specifies `ρ_q` → compute native RMS; freeze before Phase B |
| O2 | Proton positions present, no intra-proton charge geometry → point-proton RMS **DERIVED** where `{r_i}` frozen; physical charge RMS **UNDERDETERMINED** |
| O3 | Only outer boundary → NP12 path **formally incapable** of predicting RMS until another state variable is derived |

## 4. Claims

| ID | Claim |
|---|---|
| NP12d-C1 | Underdetermination: `μ_λ` family yields `R_RMS = R_B√λ` (analytic). |
| NP12d-C2 | Uniform vs shell at fixed `R_B` disagree (`√(3/5)` vs `1`). |
| NP12d-C3 | All analytic RMS fixtures PASS. |
| NP12d-C4 | Topology census completed; outcome O1/O2/O3 assigned with evidence paths. |
| NP12d-C5 | Status strengthened to **`UNDERDETERMINED — BOUNDARY IS NOT A SUFFICIENT STATE VARIABLE`** for the `R_boundary`-only map. |
| NP12d-C6 | IAEA sealed; no fitted `k`; no EMPIRICALLY SURVIVES. |

## 5. Non-claims

- Does not kill close-pack `A^{1/3}` geometry as a boundary construction.  
- Does not open Phase B radii comparison.  
- Does not edit `laws.hpp`.
