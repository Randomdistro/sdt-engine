# FD07 — Data Requirements

**Investigation**: FD07 — Circulation, Lift, and the Magnus Force from Differential Occlusion
**Author**: James Christopher Tyndall, Melbourne

All external data here are **MEASURED-INPUT** (fluid properties and aero/Magnus observables, in their measured units). The SDT mechanism — lift as the transverse resultant of an `ℓ=2`-driven occlusion asymmetry — is native; these numbers are the **convergence targets** the differential-occlusion model must reproduce, never coefficients to be borrowed (R5). Predict-before-look (R1): commit the derived value to the run log before unsealing the measured one.

## 1. Fluid property inputs (set ρ for the lift magnitude)

| Quantity | Symbol | Value (representative) | Units | Use | Source |
|---|---|---|---|---|---|
| Density, dry air (15 °C, 1 atm) | `ρ` | 1.225 | kg m⁻³ | weights `L = ρUΓ` and Magnus magnitude | ISA standard atmosphere / NIST |
| Density, water (20 °C) | `ρ` | 998.2 | kg m⁻³ | liquid Magnus cross-check (optional) | NIST |
| Kinematic viscosity, air (15 °C) | `ν` | 1.48×10⁻⁵ | m² s⁻¹ | Reynolds number context; FD06 boundary-layer handshake | NIST / ISA |

These set the *scale* of the predicted force only; the lift law itself (`L = ρUΓ`, slope `2π`) is parameter-free. Tag CALIBRATED(0) if `ρ` is used merely to evaluate, CALIBRATED(1) only if one scale is genuinely fitted — and document it.

## 2. Lift / circulation convergence targets (what the model must hit)

| Quantity | Value | Units | Tolerance | Notes |
|---|---|---|---|---|
| Ideal thin-airfoil lift-curve slope | `dC_L/dα = 2π = 6.2832` | rad⁻¹ | 3 sig figs | **primary Phase-2 target**; the falsifier |
| Per-radian in per-degree | `≈ 0.1097` | deg⁻¹ | 3 sig figs | convenience form for plotting |
| Measured slope, real 2-D sections (e.g. NACA 0012, high Re) | `≈ 0.10–0.11` (`≈ 5.7–6.3`) | deg⁻¹ (rad⁻¹) | qualitative | `≈ 0.9–0.95 × 2π`; the deficit is FD06 boundary-layer thickness, NOT the SDT mechanism |
| Zero-lift angle, symmetric section | `α₀ = 0` | deg | exact | symmetric section ⟹ no relay bias at α=0 ⟹ Γ=0 |
| Kutta–Joukowski relation | `L = ρUΓ` | N m⁻¹ | exact (analytic) | Phase-1 target; analytic identity, not a fit |

## 3. Magnus observables (sign + order of magnitude)

| Quantity | Value (representative) | Units | Use | Source |
|---|---|---|---|---|
| Spinning-cylinder circulation | `Γ = 2π a U_s`, `U_s = Ω a` | m² s⁻¹ | Phase-3 Magnus `Γ` | ideal-flow relation (analytic target) |
| Magnus lift, spinning cylinder | `L = 2π ρ a U U_s` (ideal) | N m⁻¹ | sign + magnitude check | classical Magnus / Kutta–Joukowski |
| Measured Magnus lift coefficient `C_L(S)` | `C_L ≈ 0.5–1.5` at spin ratio `S = U_s/U ≈ 1–3` | – | order-of-magnitude convergence (viscous reduces the ideal `4π²`-type estimate) | spinning-cylinder/ball wind-tunnel literature |
| Magnus sign rule | lift toward the side where surface motion ADDS to the oncoming flow | – | **the deciding falsifier** | standard observation; SDT must reproduce the direction |

The ideal `L = 2πρaUU_s` overpredicts measured cylinder Magnus lift (boundary-layer separation caps the effective `Γ`); the FD07 convergence test is **sign + order of magnitude**, with the viscous deficit attributed to FD06, not the SDT mechanism.

## 4. Internal (SDT) inputs — not external

- `c`, `ℓ_P`, `t_P`, `P_conv` — from `Engine/include/sdt/laws.hpp` (`sdt::laws::law_I`, `law_III`). dependency-traced primitives + derived; not datasets.
- `law_VI::traction` (PPT06 `ℓ=2` channel) — the bound-circulation mechanism; **internal result**, re-used here.
- `law_V` (`v_circ²+v_trans²=c²`) — the `v ≤ c` ceiling that gives the Kutta condition; internal.
- `κ = h/m` — circulation quantum from **FD02** (internal); used for the `Γ = Nκ` limit.
- Boundary-layer / no-slip pinning — from **FD06** (internal); supplies the physical Kutta closure.

## 5. Acquisition notes

- Air/water density and viscosity are textbook-stable; hard-code with citation in the MEASURED-INPUT block of `fd07_circulation_lift_magnus.cpp`. No live dataset fetch required.
- The `2π` ideal slope and `L = ρUΓ` are *analytic* targets (no dataset). Measured section slopes (NACA 0012 etc.) are a single representative figure for the qualitative boundary-layer comparison — abstracted from standard airfoil tables (e.g. Abbott & von Doenhoff) or a public XFOIL/wind-tunnel polar; one value per check suffices for the D/C-level test.
- Magnus data are order-of-magnitude only; a single representative `C_L(S)` point plus the sign rule lands the verdict. No precision aero dataset is required to falsify on sign or slope.
