# FD02 — Derivation: Viscosity & the Quantum of Circulation from Lattice Mechanics

**Author**: James Christopher Tyndall, Melbourne · Tool: `fd02_viscosity_circulation.cpp` (compiled MSVC `/utf-8 /std:c++20`, ran clean, 5/5 checkpoints pass).

## 1. Kinematic viscosity = lattice momentum diffusion
Shear in the relay lattice transports transverse momentum across a shear plane one
spation-hop at a time. Lattice kinetic theory gives the dynamic viscosity
`μ = ⅓ ρ λ v_relay`, hence `ν = μ/ρ = ⅓ λ v_relay`. The **⅓** is the angular average
over the three lattice axes (only one of x,y,z carries flux across a given plane) —
the *same* ⅓ that appears in `P_cf = P_conv/3` in `laws.hpp`. **DERIVED** (geometry);
`λ_mfp` and `m` are **MEASURED-INPUT**, `v̄(k_B,T,m)` is **DERIVED**.
- Two-stream (R3): `ν(direct)` vs `ν = μ/ρ` identical to 0.0e+00.
- Air @293 K: `ν_pred = 1.049×10⁻⁵` vs NIST `1.510×10⁻⁵` m²/s → factor **1.44** (within 10×).
- Water: factor ~16 off — honest: mean-free-path kinetic theory is crude for a dense liquid; the gas (air) is the clean test.

## 2. Temperature exponent ν ∝ Tⁿ
Fixed-density λ (geometry-set) + `v̄ ∝ √T` ⇒ **n = 0.5** for the *dynamic-viscosity*
form `μ ∝ ρ λ v̄`. Fitted lattice exponent `0.50000` (R²=1, two-stream to 9×10⁻¹⁴).
Real air: `μ ∝ T^0.74` (Sutherland: λ grows with T), and kinematic `ν` at fixed P adds
`1/ρ ∝ T` → `ν ∝ T^1.74`. The lattice 0.5 is the **hard-sphere / fixed-λ limit**; the
deviation is a known coarse-graining limit, **not a failure**. Matches the B16 transport
exponent (0.5).

## 3. Quantum of circulation κ = h/m (core gate)
Circulation `Γ = ∮ v·dl` counts the winding enclosed (Law VI). One spation contributes
one quantum of action `h` to the loop ⇒ the irreducible circulation is `κ = h/m`. The
W=1 torus is the minimal phase-locked circulation; phase-locked W=1 pairs (E59) cannot
shed it → superfluidity. **No free integer** (R5).
- `κ = h/m_He = 9.972027×10⁻⁸` vs Vinen `9.970×10⁻⁸` m²/s → **0.020%** (two-stream `2πℏ/m_He` to 6×10⁻¹⁷).

## 4. Dissipation floor
The lattice cannot relay-diffuse momentum slower than one action quantum per spation per
tick: `ν_min ~ ℏ/m_He = 1.587×10⁻⁸` m²/s (sits just below the measured superfluid ⁴He
value → floor respected). KSS bound `η/s ≥ ℏ/(4π k_B) = 6.078×10⁻¹³` K·s: the **4π** is
the relay-step solid angle (native), but pinning the *exact* coefficient to `1/(4π)` is
**CALIBRATED(1)**; QGP measures `η/s ~ (1–2)×` the bound.

## Parameter ledger
`c, ℏ, h, k_B, ℓ_P` WHITELIST · `⅓`, `v̄`, `κ=h/m`, `n=½` DERIVED · `λ_mfp, m, ρ` MEASURED-INPUT · KSS `1/(4π)` coefficient CALIBRATED(1). Class **C** overall (κ is a clean identity; ν is a convergence; floor coefficient calibrated). Path to A: derive λ_mfp / the KSS coefficient from ROOT-SIM.
