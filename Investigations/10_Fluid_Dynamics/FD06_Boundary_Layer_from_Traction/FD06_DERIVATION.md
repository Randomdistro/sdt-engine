# FD06 — Derivation: The Boundary Layer and No-Slip from Spation Traction

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: EXECUTED (Class C)
**Author**: James Christopher Tyndall, Melbourne

*Inherits the §0 anti-creep protocol and rules R0–R5. Inputs are the whitelist only; the Blasius constants are convergence targets to reproduce, never inputs to borrow.*

---

## 0. What is native vs reproduced (state it up front — R1/R4)

| Result | Status | Provenance |
|---|---|---|
| **No-slip** `u(wall)=u_wall` | **NATIVE (Class C)** | Stable fixed point of the PPT06 relay-traction update; `λ_s ≪ ℓ_P` |
| **`δ ∝ √(νx/U)` scaling** (exponent ½) | **NATIVE (Class C)** | Relay-diffusion (normal) vs advection (streamwise) — pure FD01 bookkeeping |
| **Prefactors** `δ/x=4.91`, `C_f=0.664`, `f''(0)=0.332`, `H=2.59` | **REPRODUCED** | Eigenvalue/outputs of the Blasius similarity ODE; **not** SDT geometry alone |
| Metric benchmark scale `ν` (air) | **CALIBRATED(1)** | One measured fluid scale; FD02 would make it CALIBRATED(0) |

The honesty line: SDT *derives the mechanism and the scaling law*; the *numerical prefactors* are the universal similarity-solution constants that any correct boundary-layer theory must reproduce. We reproduce them by solving the ODE — we do not claim them as SDT-geometric outputs.

---

## 1. No-slip as a spation-traction fixed point (NATIVE)

### 1.1 The grip
A solid wall is matter: a saturated spation wake. Its surface demands a tangential
angular rate `ω_demand` of each contacting spation; the lattice relays at most
`ω_max(R) = c/R`. The unrelayed mismatch is the **traction ratio** (PPT06, `law_VI::traction`):

```
T = ω_demand / ω_max = 3R_p/λ_C = 3(W+1) = 12   (proton, W=3)
```

verified live in code: `ω_demand = 3 m_p c²/ℏ = 4.276e24 rad/s`,
`ω_max(R_p)=c/R_p = 3.563e23 rad/s`, ratio `T = 12.0023 ≈ 12` (engine `traction_ratio_proton`).
The same mismatch that drives the superluminal phase demand `v_phase = 1.830 c` at `R_p`
is the mechanical grip a macroscopic wall exerts on the first free spation layer.

### 1.2 The fixed point
Coarse-grained, the grip is a per-relay-tick relaxation of the wall-adjacent layer
toward the wall velocity:

```
u_{n+1} = u_n + g_tr (u_wall − u_n),    g_tr = 1 − 1/T = 0.9167   (cap-bounded < 1)
```

The grip rate is set by the mismatch `T` and capped by the relay limit (one cannot
relay more than the full deficit in one tick). Setting `Δu = 0` gives the **unique fixed
point** `u* = u_wall`. Linearising, the multiplier is `(1 − g_tr) = 1/T = 0.083`, so
`|1 − g_tr| < 1` ⟹ **stable and monotone**. From a pure-slip start `u₀ = U`:

```
u_n = U (1 − g_tr)^n = U · 12^{−n}
```

which collapses to `u/U ~ 10⁻⁶⁶` after a few tens of ticks. The result is independent
of the exact `g_tr` for any `g_tr ∈ (0,1]` — what matters is that `T` is large enough
that the multiplier `1/T` is small.

### 1.3 Residual slip length
The surviving slip velocity carried over one relay step `ℓ_P` (the only length in the
lattice) is the slip length `λ_s = (u_residual/U)·ℓ_P`. With `u_residual/U ~ 10⁻⁶⁶`,
`λ_s ≪ ℓ_P`: **continuum no-slip**. The relay settling time `t_relax ~ 33 t_P ~ 1.8e-42 s`
is `~10⁻³⁹` of any advective time `x/U`, so the wall layer is **pinned instantaneously**.

> **No-slip is an output of the traction grip, not an axiom.** This is the FD06 native
> result that textbook fluid mechanics simply *imposes*. (Checkpoint C1, falsifier F1
> does not trigger.)

---

## 2. The Blasius scaling `δ ∝ √(νx/U)` (NATIVE, exponent ½)

### 2.1 Diffusion-vs-advection balance
The gripped wall deficit spreads **normal** to the wall by the *same* nearest-neighbour
relay that carries viscosity (FD01 `ν∇²u`, FD02 supplies `ν`). In 1-D normal diffusion the
penetration depth after time `t` is the standard random-walk result:

```
δ ~ √(ν t)
```

Meanwhile the bulk flow **advects** each gripped layer downstream (FD01 `(v·∇)v`), so the
time elapsed since a layer left the leading edge is `t = x/U`. Substituting:

```
δ(x) ~ √(ν x / U)      ⟺      δ/x ~ 1/√Re_x ,   Re_x = Ux/ν
```

This is the **Blasius balance stated in pure relay terms**: *normal relay-diffusion of the
traction grip vs streamwise advection.* No new physics — the half-space restriction of FD01.

### 2.2 Numerical confirmation of the exponent
An explicit relay-diffusion lattice (`∂_t u = ν ∂_yy u`, wall pinned by §1's fixed point,
free stream `U`), integrated to `t = x/U` at each station, gives a `0.99U` locus whose
log-log fit has slope **0.5000** (target ½). The collapsed group `δ√(Re)/x = 3.64` is the
prefactor of pure 1-D diffusion (the erf-profile 99% locus). It is **not** the Blasius 4.91
because pure normal-diffusion omits the streamwise advection coupling `f f''`; Phase 2
therefore certifies only the **exponent**, and hands the prefactor to §3. (Checkpoint C2,
falsifier F2 does not trigger.)

---

## 3. The Blasius prefactors by similarity solution (REPRODUCED)

### 3.1 The similarity reduction
Introduce `η = y √(U/(νx))` and `u/U = f'(η)`. The flat-plate (zero-pressure-gradient)
momentum balance reduces to the **Blasius ODE**:

```
f''' + ½ f f'' = 0 ,     f(0)=f'(0)=0 ,   f'(∞)=1
```

The boundary conditions are exactly the SDT inputs: `f'(0)=0` is the §1 no-slip fixed
point; `f'(∞)=1` is the free stream; `f(0)=0` is wall impermeability. **The only thing the
ODE adds is the universal shape** — and its eigenvalue `f''(0)` is a pure number, not an
SDT-geometric quantity.

### 3.2 RK4 + shooting (the reproduction)
We integrate with RK4 (step `1e-4`, `η_max=10`) and shoot on `s=f''(0)` by the secant
method until `f'(η_max)=1`:

```
f''(0) = 0.3320573372            (target 0.33206,  −0.001%)
```

From the converged profile (all within 0.05% of the published Blasius values):

| Quantity | Formula | Computed | Target | Error |
|---|---|---|---|---|
| Wall gradient | `f''(0)` | 0.332057 | 0.33206 | −0.001% |
| 99% thickness | `δ/x = η₉₉/√Re_x` | η₉₉ = **4.9100** | 4.91 (≈5.0) | exact (−1.8% vs rounded 5.0) |
| Displacement | `δ* = 1.721 √(νx/U)` | 1.720788 | 1.7208 | −0.001% |
| Momentum | `θ = 0.664 √(νx/U)` | 0.664115 | 0.6641 | +0.002% |
| Shape factor | `H = δ*/θ` | 2.591100 | 2.59 | +0.042% |
| Skin friction | `C_f = 2f''(0)/√Re_x` | 0.664115 | 0.6641 | +0.002% |
| Plate drag | `C_D = 4f''(0)/√Re_L` | 1.328229 | 1.328 | +0.017% |

### 3.3 Skin friction is the traction shear
The wall shear stress is the traction shear `τ_w = μ(∂u/∂y)|₀ = μU√(U/(νx)) f''(0)`. Forming
`C_f = τ_w/(½ρU²)` with `μ=ρν` gives `C_f = 2f''(0)/√Re_x = 0.664/√Re_x`. The skin friction
is **the integrated wall grip**, not a fitted drag law. (Checkpoints C3/C4, falsifiers F3/F4
do not trigger — every prefactor is within <2×, in fact within 0.05%.)

> **The prefactor `5.0`/`4.91` and `0.664` are the similarity-solution eigenvalue.** SDT
> hands the ODE its boundary conditions (no-slip, free stream) and its scaling variable
> (`√(νx/U)`); the universal number on top is reproduced, not derived from lattice geometry.

---

## 4. Dimensional benchmark and transition (Phase 5)

For air (`ν=1.5e-5 m²/s`, the single CALIBRATED(1) scale) at `U=10 m/s`, `x=0.20 m`
(`Re_x=1.33e5`): `δ = 2.69 mm`, `C_f = 1.82e-3`. The laminar→turbulent transition is the
point where advection outruns relay-traction smoothing; its canonical order
`Re_x,crit ~ 5e5` is an order-of-magnitude check, and the mechanism is handed to **FD03**.

---

## 5. Parameter ledger

| Symbol | Value | Status | Source |
|---|---|---|---|
| `T = 3(W+1)` | 12 | DERIVED | `law_VI::traction::traction_ratio_proton` (PPT06) |
| `ω_demand` | 4.276e24 rad/s | DERIVED | `3 m_p c²/ℏ` (whitelist) |
| `ω_max(R_p)` | 3.563e23 rad/s | DERIVED | `c/R_p` (whitelist) |
| `g_tr = 1−1/T` | 0.9167 | DERIVED | from `T`, relay-cap-bounded |
| `δ` exponent | ½ | DERIVED | diffusion-vs-advection (FD01) |
| `f''(0)` | 0.332057 | REPRODUCED | Blasius ODE eigenvalue (RK4+shoot) |
| `δ/x` prefactor (η₉₉) | 4.9100 | REPRODUCED | Blasius ODE |
| `C_f` prefactor | 0.6641 | REPRODUCED | `2 f''(0)`, Blasius ODE |
| `H` | 2.5911 | REPRODUCED | `δ*/θ`, Blasius ODE |
| `ν` (air) | 1.5e-5 m²/s | **CALIBRATED(1)** | NIST tabulated; → CALIBRATED(0) via FD02 |
| `ℓ_P`, `t_P`, `R_p`, `m_p`, `c`, `ℏ` | — | MEASURED-INPUT | `sdt::laws::measured` whitelist |

**Calibration budget used: 1** (the fluid `ν`, benchmark only). Everything that enters the
*mechanism* and the *scaling* is DERIVED at CALIBRATED(0).

---

## 6. Downstream handoffs
- **FD03** — critical `Re_x` (advection outrunning relay-traction smoothing).
- **FD07** — bound circulation `Γ` = integrated wall traction (lift).
- **FD09** — drag crisis = boundary-layer transition; adverse-`∇P` separation.
- **FD10** — vortex shedding from a separated boundary layer.
- **FD11** — the bladeless Tesla turbine drive *is* this wall traction (already built).
