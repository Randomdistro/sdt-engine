# E29: Deuteron Binding from Occlusion Geometry

> **Category**: Nuclear Physics
> **Difficulty**: TRIVIAL
> **Status**: Calculable now

---

## 1. Background

The deuteron is the simplest nuclear system: one proton + one neutron. SDT's occlusion force F = (π/4) P_eff R₁² R₂² / r² should predict the binding energy from the measured charge radii and separation.

## 2. SDT Prediction

The deuteron binding energy (2.224 MeV) is derivable from the occlusion geometry of one proton and one neutron at the measured separation of 2.14 fm.

## 3. Standard Prediction

Standard: deuteron binding from nuclear potential models (Yukawa, AV18, etc.).

## 4. Observable

Calculate occlusion binding energy from R_p = 0.841 fm, R_n ≈ equivalent, separation = 2.14 fm. Compare to measured 2.224 MeV.

## 5. Apparatus

Computational. Use law_III::F_occlusion from laws.hpp.

## 6. Feasibility

**TRIVIAL** — pure calculation.

## 7. Impact

- **If confirmed**: Reproducing 2.224 MeV from occlusion geometry would ground the nuclear force in convergent pressure.
- **If not confirmed**: If the energy differs significantly: occlusion geometry alone may not capture the full nuclear interaction.
