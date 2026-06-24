# FD01 — Navier–Stokes from Spation Relay — Data Requirements

All values below enter as **MEASURED-INPUT in measured units** (legitimate, like spectral lines): they are
tools for the Phase-5 coefficient handshake and benchmark check, never fitted free parameters. The *mechanism*
remains SDT-native. Tag every use DERIVED / MEASURED-INPUT / CALIBRATED(n) (R2). Target CALIBRATED ≤ 1.

## 1. Reference Fluid Properties (for the ν handshake, Phase 5)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Kinematic viscosity ν of water at 20 °C, 1 atm (1.004×10⁻⁶ m²/s) | NIST / IAPWS-IF97 | Primary `ν` calibration scale (≤1 fitted) |
| Dynamic viscosity μ and density ρ of water at 20 °C | NIST / IAPWS-IF97 | `ν = μ/ρ` cross-check |
| Kinematic viscosity ν of air at 20 °C, 1 atm (1.516×10⁻⁵ m²/s) | NIST / Sutherland | Second-fluid consistency (no extra fit) |
| Speed of sound c_s in water (1481 m/s) and air (343 m/s) at 20 °C | NIST | Mach number `Ma=v/c_s` for Phase-3 incompressibility limit |

## 2. Viscosity Temperature Law (for the B16 √T exponent check)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| ν(T) for a dilute gas (e.g. argon/air) over 200–1000 K | NIST / Sutherland's law | Test SDT/B16 prediction `ν ∝ √T` (exponent 0.5) |
| Measured viscosity-temperature exponent for the chosen gas | Kinetic-theory tables | Compare to SDT exponent 0.5 |

## 3. Macroscopic Benchmark Flows (for the limit-recovery and end-to-end check)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Hagen–Poiseuille analytic profile (pressure-driven pipe/channel) | Analytic (closed form) | Phase-4 Stokes-limit two-stream comparison |
| Taylor–Green vortex decay rate at a stated Re | Analytic / standard DNS reference | End-to-end NS check: predicted decay from derived ν vs known rate |
| Stokes-flow relaxation of a single Fourier mode (decay = e^(−ν k² t)) | Analytic | Phase-4 lattice-vs-analytic <1% test |
| Reynolds-number transition data (laminar→turbulent, pipe Re≈2300) | Standard fluids references | Sanity bound on the advection/diffusion ratio mapping (`Re`) |

## 4. Engine-Internal Constants (NOT external — listed for traceability)

| Quantity | Source | Note |
|----------|--------|------|
| ℓ_P, t_P, c = ℓ_P/t_P | `sdt::laws::measured` / `law_I` | Relay scale, tick, signal speed — whitelist inputs |
| P_conv ≈ 2.46×10⁴⁸ Pa | `law_I::P_conv` | Ambient convergence pressure (gradient → −∇P/ρ) |
| Movement-budget cap v_circ²+v_trans²=c² | `law_V` | Low-Mach expansion parameter (Phase 3) |
| ν coefficient (geometry-fixed) | **FD02** (downstream) | Must match the value emitted by FD01 coarse-graining to <1% |

## Notes
- No proprietary or restricted datasets are required; all items are standard reference values or closed-form
  analytic results.
- DNS references (Taylor–Green) are used only as a *target to reproduce*, never as an input to the derivation
  (R5: never import a result as a borrowed target).
- If the Phase-5 handshake forces more than one fitted scale, the result is capped at Class C and the extra
  calibration must be documented explicitly in `FD01_VERDICT.md`.
