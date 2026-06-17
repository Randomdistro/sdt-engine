# Fluid Dynamics — SDT lattice mechanics (FD01–FD10)

> **Author:** James Christopher Tyndall, Melbourne. **Status:** SPEC (10 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

In SDT the only ontology is a **granular relay lattice of spations** passing convergence
throughput between contacting neighbours at one tick (`c = ℓ_P/t_P`). That lattice **is** a
granular/compressible fluid — so classical fluid dynamics is not an imported theory, it is the
**continuum coarse-graining of spation relay mechanics**. These ten investigations test that
claim end to end: each reproduces a standard fluid-dynamics result as a *convergence target*
(never a borrowed input), narrating the mechanism in SDT primitives (occlusion, traction,
displacement cascade, movement budget, koppa) and flagging every gap OPEN rather than fitting it.

## Dependency stack (build/run order — bottom feeds top)

```
FD01  Navier–Stokes from spation relay        ← the FD root (rests on ROOT-SIM, CQ08, CQ10)
  │
  ├─ FD02  Viscosity & the circulation quantum  (ν = ⅓ λ_mfp v_relay; κ = h/m; η/s floor)
  │     │
  │     ├─ FD03  Reynolds transition            (Re = advection / relay-smoothing rate ratio)
  │     │     └─ FD04  Kolmogorov −5/3 cascade   (= the volume-conserved displacement cascade)
  │     ├─ FD05  Sound, shocks & the c/√3 ceiling (c_s=√(dP/dρ); Mach cone ≡ Cherenkov shock)
  │     └─ FD06  Boundary layer & no-slip        (from CQ14 traction; δ ∼ √(νx/U))
  │           ├─ FD07  Circulation, lift, Magnus (differential occlusion; L = ρUΓ; slope 2π)
  │           ├─ FD09  Drag as occlusion shadow  (Stokes 6πμRv; drag crisis = BL transition)
  │           └─ FD10  Vortex shedding / Strouhal (lattice relaxation; St ≈ 0.2 from gear freq)
  └─ FD08  Bernoulli from the movement budget   (½ρv²+P+ρgz = const; ties to v²+v_circ²=c²)

  ⇒ FD11  Tesla Steam Generator (APPLIED CAPSTONE) — a real bladeless turbine whose drive IS
          spation traction; composes FD06 (boundary layer) + FD02 (ν) + FD05 (steam nozzle)
          + FD08 (energy budget) + FD09 (windage) into one buildable, falsifiable machine,
          with a modern-materials build spec (MATERIALS_AND_PARTS.md).
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **FD01** | Navier–Stokes from Spation Relay | coarse-grained per-spation relay; ∇P=convergence-pressure gradient, ν∇²v=relay diffusion, ∇·v=0=spation-count conservation | reproduce NS term-for-term + Euler/Stokes limits; bijection gate |
| **FD02** | Viscosity & the Quantum of Circulation | momentum diffusion `ν=⅓λ_mfp v_relay`; one-spation winding | air/water ν; superfluid κ=h/m; ν∝√T (B16); η/s≳ħ/4πk_B |
| **FD03** | Reynolds Transition as a Relay Ratio | Re = advective transport / relay smoothing (two rates of one medium) | pipe Re_crit≈2300; flat-plate Re_x≈5×10⁵; Taylor–Couette |
| **FD04** | Kolmogorov Cascade from Displacement | the volume-conserved displacement cascade (strain ∝1/r³) at constant flux | E(k)∝ε^{2/3}k^{−5/3} derived (not assumed); microscale η≥ℓ_P |
| **FD05** | Sound, Shocks & the c/√3 Ceiling | compression relay wave `c_s=√(dP/dρ)`; shock = super-relay disturbance | air 343 m/s; c/√3 limit (CQ39); boom ≡ Cherenkov (E57) |
| **FD06** | Boundary Layer from Traction | CQ14 spation traction grips the wall ⇒ no-slip (derived, not imposed) | Blasius δ/x=5/√Re_x; C_f=0.664/√Re_x |
| **FD07** | Circulation, Lift & Magnus | asymmetric wake (CQ14 ℓ=2); bound Γ = differential traction | Kutta–Joukowski L=ρUΓ; thin-airfoil slope 2π; Magnus sign |
| **FD08** | Bernoulli from the Movement Budget | streamline convergence-pressure budget partition (Law V) | ½ρv²+P+ρgz=const; Venturi; Pitot; compressible correction |
| **FD09** | Drag as an Occlusion Cross-Section | Law III occlusion of convergent momentum flux (front−wake) | Stokes 6πμRv; C_D(Re) curve incl. drag crisis at Re≈3×10⁵ |
| **FD10** | Vortex Shedding & Strouhal | lattice relaxation / traction oscillation (CQ41 gear-frequency) | St=fD/U≈0.2 plateau; f∝U/D; lock-in |
| **FD11** | Tesla Steam Generator *(applied capstone)* | bladeless turbine driven by spation traction (FD06) on smooth disks; composes FD02/FD05/FD08/FD09 | optimal disk gap ~0.4 mm; η_rotor(λ) peak; **viscosity signature** dη/dRe<0 (vs bladed); + modern-materials build spec |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`law_I::P_conv` · `law_III` occlusion (`F_occlusion`, `solid_angle_occluded`) · `law_IV` `V_disp`
· `law_V` movement budget (`v_circ²+v²=c²`) · `bridge` (`koppa`, `k`, `z`, `depth_closure`) ·
`law_VI::traction` (CQ14: `T=3(W+1)`, wake ℓ=1/2/3) · `law_VI::topology` · `law_VI::confinement`.
Prior results leaned on: **B16** (transport ν∝√T, exponent 0.5), **CQ39** (c/√3 radiation-fluid
sound speed), **E57** (Cherenkov shock), **E59** (superfluid phase-locked vortices), **CQ41**
(gear-frequency binding), **CQ08/CQ10/ROOT-SIM** (the granular-relay root), and the
**displacement cascade** (volume-conserved shell-by-shell, strain ∝ 1/r³).

## Method discipline

Each investigation reports results with certification labels (`DERIVED` / `COMPUTED` /
`CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard-FD
number is always the thing to *reproduce*, never to *borrow*; measured fluid properties
(ρ, μ, ν, sound speed) are legitimate measured-unit inputs/tools — like spectral lines — but the
mechanism must be SDT-native. A clean kill outranks a forced pass (R4).
