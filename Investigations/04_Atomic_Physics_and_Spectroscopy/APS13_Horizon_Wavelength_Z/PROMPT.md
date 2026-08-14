# APS13 — Horizon z as wavelength modifier

> **Author:** J. C. Harvey, Melbourne. **Status:** EXPLORATORY 2026-08-13.  
> **Canon edits:** none. **Pre-registration:** skipped at author direction.  
> **Calibration:** allowed if the result is a predictor on held-out Z / ion stage / excitation.  
> **Engine:** constants from `Engine/include/sdt/laws.hpp` only.  
> **Upstream miss:** APS12 identified the line *as* `½ m_e c² Δz`. That is the Rydberg/APS01 chain rewritten. This file tests the claim APS12 did not test.

Vocabulary: excluded / ruled out / falsified / withdrawn. Shared-input, not an evidence-label. Assessment: `APS13_ASSESSMENT.md`.

---

## The claim

The nucleus sits behind the atom’s c-boundary and behaves as a black hole. Electronic light is **the same electron wavelength**, altered by gravitational `z` at the emitting seat. A heavier nucleus, or a stripped ion, changes that `z`. Set excitations should then be predictable.

That is three sentences. APS12 tested a fourth: the photon *is* the depth energy. The investigation keeps those objects apart and scores them on the atom’s own seats, its own series, and its own ions. No other body.

## What “proper” means here

1. **Name the horizon.** `z = 1` at `r = ϟ`. Through-going laboratory light is not born inside. The proton sits inside hydrogen’s koppa. State the numbers before any spectrum.
2. **Split the letter `z`.** Do not score one formula and call it gravitational redshift.
3. **Test “same wavelength.”** Take one observed line as the rest wavelength of a named excitation. Push it through each `z`-map to another species at the *same* excitation. That is the claim. Recovering Rydberg from `½mc²Δz` is not.
4. **Allow calibration** on a named training slice. The test is the hold-out, not the training residual.
5. **Occupancy is the unpaid payload.** H-like `Z²` is the stretch `λ ∝ 1/z` at fixed `(n_i, n_f)`. Multi-electron `ϟ_felt` is what would make this nuclear gravitation rather than a one-electron seat chain.

## Four maps (do not blend)

Reference is the atom: hydrogen’s own `ϟ`, its own `z_n`, then the same excitation on its own H-like ions.

| ID | Rule | Reading on the atom |
|---|---|---|
| **A fractional** | `λ / λ_ref = (1 + z) / (1 + z_ref)` | Same line, seats differ only by a factor `(1+z)` |
| **B clock / relay** | `ν ∝ (1−z)` or `ν ∝ (1−z)²` | Same line, tick or hop closed at that seat |
| **C energy-as-depth** | `hν = ½ m_e c² Δz` | The line *is* the seat kinetic. Rydberg algebra. |
| **D stretch** | `λ / λ_ref = Δz_ref / Δz` | Same rest wavelength, inverse depth. On H, series from Lyα. On H-like, `λ(Z) = λ(H)/Z²`. |

A and B are fractional modifiers of a line the atom already made. C is APS12. D is “same wavelength altered by `z`” as a stretch across that atom’s seats and ions. C and D share a closed form with Bohr–Rydberg; origin is koppa depth, not Coulomb. Correspondence is not provenance.

Law V exact binding `E = mc² [(1−√(1−z_lo)) − (1−√(1−z_hi))]` is map C at all orders. APS12 logged it and did not score it. Here it is a scored H-like predictor, zero extra parameters.

## Geometry (must print) — one body at a time

Hydrogen against hydrogen: `ϟ = r_e = α² a_0`. Proton `R_p` inside that koppa: `z_p = r_e/R_p > 1`. Electron seats `r_n = a_0 n²`, `z_n = ϟ/r_n = α²/n²`. Fill `R_p/ϟ`. How many koppa-radii out is n=1: `r_1/ϟ = 1/α²`.

H-like ion Z against *that ion’s* koppa: `ϟ_Z = Z r_e`, `r_n = a_0 n²/Z`, `z_n = (Z α / n)²`, fill `R(A)/ϟ_Z`. Last electron: upper seat at infinity, `z_∞ = 0`.

No other body.

## Discriminators

**D0 — hydrogen against itself.** Rest = H I Lyα. Predict H I Lyβ (3→1) and Hα (3→2) from hydrogen’s own `z_n` under A, B, D. Fractional/clock that cannot make the series from one H line are excluded on hydrogen alone.

**D1 — same excitation, the H-like family.** Rest = H I Lyα. Predict He II and Li III 2→1. That is the same well, deeper `ϟ_Z`, not a second mechanism.

**D2 — H-like 2→1 across Z.** Stretch from H only: `λ(Z) = λ_H / Z²`. Also Law V from engine constants, no fit. Fe XXVI 2→1 centroid is the high-Z row (APS12 hold-out 0.178074 nm). A one-parameter remainder `1 + a (Zα)²` may be fitted on Z=1,2,3 and tested on Fe. If `a` lands on the Law V series, it is not a new scale.

**D3 — occupancy, calibrated.** Training: complete IE series of Z ∈ {2,4,6,8,10}. Hold-out: Z ∈ {3,5,7,9,11,12,18,20,26} where json has the stage. Model: `Z_eff = Z − σ_n (N_e − 1)`, `IE = Ry Z_eff² / n²`, `σ_n` = median inverted σ on training rows at that principal n (Madelung freeze as APS12). One number per n. Predict hold-out IE. A model that fits train and misses hold-out is not predictive. Comparators on the same hold-out: S_bare (`Z_eff=Z`), S_ion (`Z_eff=` ion stage), and a single global σ. No `Z_eff` inverted from the hold-out row and reused as its own prediction.

**D4 — grammar (report).** On hold-out residuals, list `n_d`, `n_t` of the common isotope. No claim unless a named grammar rule beats σ_n on the hold-out.

## Data

- `Datasets/nuclear/ionisation_energies.json` (NIST snapshot in-repo).
- H I / He II / Li III / Fe XXVI wavelengths as in APS12 T1 (OBSERVED stickers). No new NIST scrape required for D1–D2.
- Engine literals only. No 1051.8. No packer `dnn` retune.

## Tags

MEASURED-INPUT · DERIVED · COMPUTED · CALIBRATED(n) · OBSERVED · PENDING. Training σ_n is CALIBRATED(n_shells). Law V H-like is DERIVED. Stretch from H Lyα is CALIBRATED(1) if λ_H is the scale, or OBSERVED×DERIVED if λ_H is the rest sticker and Z² is koppa depth.

## Out of scope

Lamb. Fine-structure doublets as a scored target. Saha. Canon. Slater σ as a mechanism (a same-fidelity comparator may be *scored*, not imported into the chain).

## Done when

Tables exist for geometry, D0, D1, D2, D3; each map is MATCH / miss / identity-with-Rydberg / OPEN; calibration count is stated; hold-out residuals are the verdict. Dual: this prompt was executed · physics class of each map.
