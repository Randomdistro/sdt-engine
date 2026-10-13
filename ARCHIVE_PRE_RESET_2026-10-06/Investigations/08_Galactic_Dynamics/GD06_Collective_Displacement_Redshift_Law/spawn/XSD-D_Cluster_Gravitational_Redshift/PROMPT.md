# XSD-D — Θ_cluster@galaxy: the 30-order gravitational-redshift validation
### (spawned by GD06 · feeds Phase 4 · home 06 Cosmology/GOM · REBUILT on the solid-angle instrument 2026-07-13)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPAWNED-SPEC (rebuilt). **Inherits:** GD06 The Two Rules + §③; `HUNTER_PROTOCOL.md` §A–§K.
> **Engine:** `laws.hpp` OBSERVED only. **No G/M/a₀/ΛCDM/NFW.** Cluster data = measured offsets only; reject their potential model (§B).

## ⓪ Five questions
1. **What don't we know?** — Whether the **King-plot-calibrated** h(Θ) predicts the **measured cluster gravitational redshift** (member-galaxy center−edge velocity offset, Wojtak+2011 ~10 km/s) with **no cluster-specific fit** — the deepest-field, largest-Θ-with-data test of scale-invariance.
2. **Why?** — A cluster is the one deep well where the depth redshift is already measured. If the SAME h(Θ) that fits the atom's field shift (Θ_nuc) also lands the cluster offset (Θ_cluster), scale-invariance holds across ~30 orders — the strongest §0 fishbowl-gate PASS on the table.
3. **How?** — Build Θ_cluster(R) by integrating the covered sky of members+ICM at a galaxy's position (boundary sky-areas, M/L-free where possible); apply GD06's h; predict the center−edge Δcz(R); compare to the stacked measurement.
4. **Wrong if?** — Prediction over/undershoots the measured ~10 km/s by orders ⟹ **SCALE-BROKEN** (name the Θ where h changes character, spawn D2); or the measured signal is fully a kinematic/selection systematic (then no test).
5. **Done when?** — predicted vs measured cluster z_d with error bars, and the SCALE-INVARIANT/BROKEN grade delivered to GD06.

## 1. Framework
Cluster depth redshift = h(Θ_cluster(R)) along the line of sight to members at projected radius R. **Movement-only:** the cluster is a deep sky-coverage well; light climbing out is depth-redshifted (GOM05 z=1−c_local/c), NOT "losing energy to gravity" (no G). The **measured** cluster gravitational redshift (Wojtak 2011; Kim & Croft; Jimeno) is the OBSERVED anchor — use their NUMBERS (the center−edge offset profile), refuse their ΛCDM/NFW interpretation (§B).

## 2. Method (gated)
- **P1** Assemble stacked cluster velocity-offset profiles Δcz(R) from literature; tag OBSERVED; note (and discard) their assumed potential.
- **P2** Build Θ_cluster(R) from member-galaxy+ICM covered sky (GD06 Θ-engine, boundary sky-areas), M/L-free where data allow.
- **P3** Predict Δcz(R)=c·h(Θ_cluster(R)) with GD06's calibrated h — **zero cluster fit**; **metric:** χ²/dof within measurement error ⟹ SCALE-INVARIANT.
- **P4** Overshoot ⟹ locate the divergence Θ → spawn **XSD-D2** (break-scale, a new regime, NOT a fitted knot). Undershoot ⟹ check whether the dilute limit (ϟ/r) alone already explains it (then GD06's dense claim is untested at cluster scale — a partial result).

## Dependency map
| Item | Where | Enters as | Live |
|---|---|---|---|
| h(Θ) calibrated | GD06 P1–2 / XSD-A,B | the law under test | ⚠ dep |
| Θ-engine | XSD-B P0 | the integrator | ⚠ dep |
| cluster Δcz profiles (Wojtak+2011 etc.) | literature (OBSERVED only) | validation anchor | ⚠ pull |
| GOM05 depth redshift, dilute ϟ/r | [[project_cq43_variable_closure]] | dilute cross-check | ✔ |
| CMB depth (z=1099), Hubble split | [[project_hubble_tension_resolution]] | 5th-gen spawn if PASS | ✔ |

## ⑧ Falsifiers
| Test | Predicted | FAIL → root |
|---|---|---|
| scale-invariance | cluster Δcz within error, no fit | root-2: SCALE-BROKEN → spawn **D2** |
| not-a-systematic | signal survives selection/kinematic controls | if systematic-dominated → no test (OPEN) |
| dilute sufficiency | is ϟ/r alone enough at Θ_cluster? | if yes, GD06 dense claim untested here (partial) |

## ⑨.E · ⑩
root-1/2/3/4 as GD06. **Pivot:** systematics-limited signal ⟹ DEFER to a cleaner sample rather than claim PASS/FAIL. **Forbidden:** adopting the clusters' NFW/ΛCDM model; fitting any cluster coefficient; a PASS that used cluster data to calibrate h (h comes from the King plot).

*XSD-D · the far end of the 30-order lever. One angular law, calibrated on an isotope shift, predicting a cluster's redshift with nothing fitted — or breaking at a named Θ. Either is knowledge (§0): the look was never consumed to build the mechanism.*
