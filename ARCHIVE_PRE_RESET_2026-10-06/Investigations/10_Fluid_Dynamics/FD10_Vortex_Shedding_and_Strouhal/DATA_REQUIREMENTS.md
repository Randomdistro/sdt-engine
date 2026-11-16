# FD10 — Vortex Shedding and the Strouhal Number — Data Requirements

All values below enter as **MEASURED-INPUT in measured units** (legitimate, like spectral lines): they are
the *convergence targets to reproduce* and the dimensional inputs for the relaxation clock — never fitted free
shedding constants. The *mechanism* remains SDT-native. Tag every use DERIVED / MEASURED-INPUT / CALIBRATED(n)
(R2). Target CALIBRATED ≤ 1 (a low-Re shape parameter at most).

## 1. The Strouhal–Reynolds Curve (primary convergence target, Phases 2 & 4)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| `St(Re)` for a smooth circular cylinder over `~40 < Re < 2×10⁵` | Roshko 1954 (NACA Report 1191) | Primary `St(Re)` curve: the plateau AND the low-Re rise |
| Refined `St(Re)` and the laminar-shedding discontinuities (`Re ≈ 64–180`) | Williamson 1988/1996 (*J. Fluid Mech.* / *Annu. Rev. Fluid Mech.* 28:477) | High-precision low-Re bend; mode-A/mode-B transitions |
| Plateau value `St ≈ 0.20–0.21` over `300 < Re < 2×10⁵` (subcritical) | Roshko / Williamson / Norberg compilations | The single number Phase 2 must reproduce (factor-2 / ±20 % gate) |
| Roshko empirical fit `St = 0.212(1 − 21.2/Re)` (`Re ≈ 50–150`) | Roshko 1954 | Functional-form *test* for the Phase-4 low-Re bend (compare, do not borrow) |
| Williamson–Brown / Fey et al. `St = St_∞ + m/√Re` style fits | Williamson 1996; Fey, König & Eckelmann 1998 | Cross-check of the derived `St(Re)` exponent `p` |

## 2. Frequency–Velocity Scaling (Phase 3)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| `f` vs `U` Strouhal lines at fixed `D` (constant-`St` lines) | Standard wind-tunnel/towing-tank cylinder data | Confirm `f ∝ U` with slope `St_∞/D` |
| `f` vs `D` at fixed `U` (multiple cylinder diameters) | Cylinder-array / anemometry references | Confirm `f ∝ 1/D` |
| `Re`-independence of `St` across the plateau | Norberg 2003 (*J. Fluids Struct.* 17:57) compilation | Verify no hidden `Re`-drift on the plateau |

## 3. Lock-In / Entrainment Data (Phase 5)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Synchronisation (lock-in) range vs forcing amplitude for a transversely oscillated cylinder | Koopmann 1967 (*J. Fluid Mech.* 28:501); Bishop & Hassan 1964 | Map the Arnold-tongue capture band vs amplitude `A` |
| Lock-in band as a function of `f_drive/f_natural` and amplitude ratio `A/D` | Williamson & Roshko 1988 (*J. Fluids Struct.* 2:355); Govardhan & Williamson 2000 | Bracket the measured capture band with the CQ41 beat model |
| Vortex-induced-vibration (VIV) lock-in range / response branches | Sarpkaya 2004 (*J. Fluids Struct.* 19:389) review | Secondary lock-in cross-check |

## 4. Boundary-Layer / Separation Geometry (feeds the clock, Phase 1)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Separation angle on a circular cylinder vs `Re` (laminar `≈80°`, turbulent `≈120°` from front stagnation) | Achenbach 1968 (*J. Fluid Mech.* 34:625) | Sets `D_eff/D` and the FD06 input to `τ_relax` |
| Base-pressure coefficient and formation-length `L_f` vs `Re` | Williamson 1996; Roshko 1954 | Wake-width / formation-region scale for the relaxation time |

## 5. Reference Fluid Properties (dimensional inputs, MEASURED-INPUT)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Kinematic viscosity `ν` of air at 20 °C, 1 atm (1.516×10⁻⁵ m²/s) | NIST / Sutherland | Convert tunnel `(U, D)` to `Re = UD/ν` for the FD03 gate |
| Kinematic viscosity `ν` of water at 20 °C (1.004×10⁻⁶ m²/s) | NIST / IAPWS-IF97 | Towing-tank `Re` conversion, second-medium consistency |

## 6. Engine-Internal Constants (NOT external — listed for traceability)

| Quantity | Source | Note |
|----------|--------|------|
| ℓ_P, t_P, c = ℓ_P/t_P | `sdt::laws::measured` / `law_I` | Relay scale, tick, signal speed — derivation basis inputs |
| Traction `ℓ=2` wake demand `ω_demand` | `law_VI::traction` (PPT06) | Source of the bound circulation and `τ_relax` |
| Movement-budget cap `v_circ²+v_trans²=c²` | `law_V` | Vortex spin-up cap before detachment |
| Gear-frequency `Δω` / relaxation-energy scale | **CQ41** (upstream) | The shedding clock; coefficient handed in, not fitted here |
| Separation geometry `δ*`, `D_eff/D` | **FD06** (upstream) | Geometric input that fixes `τ_relax/τ_adv` and hence `St_∞` |

## Notes
- No proprietary or restricted datasets are required; all items are published reference curves (Roshko,
  Williamson, Norberg, Achenbach, Koopmann) or standard NIST fluid properties.
- The `St ≈ 0.2` plateau and the Roshko/Williamson `St(Re)` curve are used **only as targets to reproduce**,
  never as inputs to the derivation (R5: never import a result as a borrowed shedding constant).
- If the Phase-4 low-Re fit forces more than one fitted shape parameter, the result is capped at Class C and the
  extra calibration must be documented explicitly in `FD10_VERDICT.md`.
