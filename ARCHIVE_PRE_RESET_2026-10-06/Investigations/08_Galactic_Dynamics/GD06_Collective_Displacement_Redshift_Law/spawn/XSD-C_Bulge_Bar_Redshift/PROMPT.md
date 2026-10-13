# XSD-C — Θ_bulge@star: the dense-vs-dilute verdict + the redshift/rotation symmetry
### (spawned by GD06 · feeds Phase 3 · home 08 Galactic · REBUILT on the solid-angle instrument 2026-07-13)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPAWNED-SPEC (rebuilt). **Inherits:** GD06 The Two Rules + §③; `HUNTER_PROTOCOL.md` §A–§K.
> **Engine:** `laws.hpp` OBSERVED only. **No G/M/a₀/MOND/ΛCDM. Real data only, no mocks. Θ computed by solid-angle integration, not a proxy.**

## ⓪ Five questions
1. **What don't we know?** — **The sky-fraction Θ_bulge a bulge/bar covers at an embedded/nearby star**, and therefore which branch of h(Θ) it sits in: **dilute** (Θ≪1, z_d≈0.1%, disk rotation uncorrupted) or **dense** (Θ→1, z_d dominates, "redshift = speed" false).
2. **Why?** — This is Harvey's "same as a high-Z atom" under test, done as the actual angular integral. It decides whether the bulge's inner "rotation"/dispersion is partly a depth redshift and whether dark matter fully dissolves into sky-coverage.
3. **How?** — Build Θ_bulge(𝐱) by integrating the bulge's covered sky at star positions from **M/L-free** surface photometry (boundary sky-areas, GD06 σ_occ rule), with saturation; apply the King-calibrated h(Θ) (GD06 Phases 1–2); predict Δcz(center−disk) with zero free parameters; then deconvolve depth from rotation.
4. **Wrong if?** — Θ_bulge lands dilute: the 0.1% stands, disk rotation is NOT corrupted, report it honestly against the hypothesis. Or predicted z_d exceeds any allowed spectrum (SCALE-BROKEN below cluster scale).
5. **Done when?** — a dense/dilute verdict with predicted Δcz on record, and the redshift/rotation separation resolved (or spawned as C2).

## 1. Framework — the integral and the symmetry fork
Θ_bulge(𝐱) = (1/4π)∮[1−e^{−τ_bulge(𝐱,n̂)}]dΩ, τ_bulge from the stellar boundary sky-areas along each ray (M/L-free number column from surface brightness). **The symmetry fork (decisive):** the **isotropic** Θ (depth redshift) is common-mode — same on approaching/receding sides at a radius ⟹ **cancels in the antisymmetric rotation extraction** (lands in systemic velocity), **survives in the dispersion σ** (line width) and in any **line-of-sight-asymmetric** term (inclined disk: near/far sides sample different Θ columns). So:
- **Bulge σ** ("pressure support") is the clean channel — dense Θ broadens it as a depth spread, not motion.
- **Disk rotation** (antisymmetric) is protected *unless* inclination breaks the symmetry (→ **XSD-C2**).
Predict all three: Δcz(systemic center−edge), the z_d contribution to σ_bulge, the near/far asymmetry vs inclination.

## 2. Method (gated, real data)
- **P1** For SPARC-bulged galaxies + ellipticals with published photometry, compute Θ_bulge@star via the GD06 Θ-engine (boundary sky-areas, saturation). Tag OBSERVED.
- **P2** Evaluate z_d=h(Θ_bulge) with GD06's calibrated h; **pre-commit** the dense/dilute branch boundary Θ* before computing. Output Δcz predictions, zero free parameters.
- **P3** Deconvolve the inner velocity field as (antisymmetric rotation)+(symmetric z_d(r)); measure the residual central symmetric excess; **metric:** predicted vs measured within error.
- **P4** Dense ⟹ spawn **XSD-C2** (full inclination deconvolution); dilute ⟹ close honestly.

## Dependency map
| Item | Where | Enters as | Live |
|---|---|---|---|
| h(Θ), h′,h″ | GD06 P1–2 / XSD-A,B | calibrated law | ⚠ dep |
| Θ-engine | XSD-B P0 | the integrator | ⚠ dep |
| bulge surface brightness, σ, inclination | SPARC + photometry (OBSERVED) | Θ_bulge + test data | ⚠ pull |
| mass=occlusion=pressure-gradient | GD05 verdict | ontological premise | ✔ |
| systemic-velocity extraction pipeline | rotation-curve method | the symmetry channel | ✔ |

## ⑧ Falsifiers
| Test | Predicted | FAIL → root |
|---|---|---|
| dense ⟹ σ excess | z_d spread ~ measured σ_bulge fraction | if σ fully kinematic → dilute (honest) |
| center systemic excess | Δcz(center−edge)=c·h(Θ_bulge) | root-1/2: law or Θ wrong |
| disk rotation protected | antisymmetric part unchanged by z_d | if disk corrupted → inclination term → **C2** |
| Θ computed not proxied | Θ from the solid-angle integral | root-1: any volume/koppa proxy = wrong instrument |

## ⑨.E · ⑩
root-1/2/3/4 as GD06. **Pivot:** borderline Θ_bulge ⟹ report the interval + Θ*, don't force a verdict. **Forbidden:** claiming "disk speed false" if dilute; any G/M/a₀; mocks; fitting z_d to the observed excess (must be carried from the atom via GD06); a Θ proxy instead of the integral.

*XSD-C · the crux, as the real angular integral. Dense or dilute is DERIVED from the King-plot h(Θ); and the symmetry fork says the bulge σ, not the disk rotation, is where a true z_d first shows.*
