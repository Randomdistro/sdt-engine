# FD05 — Derivation: Sound, Shocks, and the c/√3 Ceiling

**Author**: James Christopher Tyndall, Melbourne · Tool: `fd05_sound_shocks.cpp` (MSVC `/utf-8 /std:c++20`, ran clean; all 5 phases PASS).

## 1. Ordinary sound = a compression relay wave
A local densification `ρ→ρ+δρ` raises lattice pressure by `δP=(dP/dρ)δρ`; the disturbance
heals into neighbouring cells at the relay-limited speed `c_s = √(dP/dρ)`. **DERIVED**
mechanism; the equation-of-state slope (`γRT` for a gas, `K/ρ` for a liquid) is
**MEASURED-INPUT**.
- air 20 °C: `√(γRT) = 343.31` vs 343.2 m/s (+0.031%)
- water 20 °C: `√(K/ρ) = 1477.8` vs 1481 m/s (−0.215%)

## 2. The c/√3 ceiling (native, zero free parameters) — Class A
Law I fixes the radiation/relay-gas pressure as `P_rad = u/3` (isotropic). The relativistic
inertia is the energy density, `ρ_eff c² = u`. Therefore
```
c_s² = dP/d(ρ_eff c²) = d(u/3)/du = 1/3   ⇒   c_s = c/√3 = 1.730853×10⁸ m/s.
```
No fitted parameter. This is the maximal lattice sound speed and **equals the CR04
pre-Clearing (BAO) coupled-lattice sound speed** — FD05 derives it as the high-stiffness
asymptote of the *same* `c_s=√(dP/dρ)`.

## 3. One curve from gas to radiation
Define stiffness `w = P/(ρc²) = (c_s/c)²`. Every fluid is a point on `c_s = c√w`; the
ceiling is `w = 1/3`. Air (`w~10⁻¹²`) → water (`~10⁻¹¹`) → radiation (`1/3`) all lie on it;
none exceeds `c/√3`.

## 4. Mach cone & shock criterion
A source at `v > c_s` piles compression fronts (each expanding at `c_s`) onto a cone of
half-angle `sinθ = c_s/v = 1/M` (reproduced to 0.00° vs textbook for M=1…10). Onset at
`M=1` (relay-smoothing threshold). Shock thickness cannot be thinner than the relay can
re-equilibrate: `δ ~ (3–5)λ ≈ 204–340 nm` in air STP (measured weak-shock widths ~200 nm).

## 5. Sonic boom ≡ Cherenkov (E57) — Class A native unification
One criterion: a disturbance forced past the **local** relay speed of its mode forms a
conical shock, `v > c_relay(mode)`.
- compression mode → `c_relay = c_s` → **sonic boom** (`sinθ = c_s/v`)
- phase/light mode → `c_relay = c/n` → **Cherenkov** (E57, VERIFIED; `cosθ_C = 1/(nβ)`)

Same geometry, complementary reference: `θ_boom + θ_C = 90°` (numeric check: 56.464° + 33.536° = 90.000°). The boom and Cherenkov radiation are the **same lattice shock** at different relay speeds.

## Parameter ledger
`c, ℓ_P` & `P_rad=u/3` (law_I) WHITELIST/DERIVED · `c/√3`, the `1/3` slope, Mach angle, boom≡Cherenkov criterion DERIVED (zero params) · `γ, R, K, ρ, λ_mfp, n` MEASURED-INPUT. **Class A** for the c/√3 ceiling and the boom≡Cherenkov unification; **Class C** for ordinary sound (a clean compressibility convergence).
