# FD01 — Navier–Stokes from Spation Relay — Analytic Derivation

**Author:** James Christopher Tyndall, Melbourne.
**Companion tool:** `fd01_navier_stokes_relay.cpp` → `fd01_results.txt` (numerics for the checkable subset).
**Status:** the term-by-term PDE bijection is ANALYTIC and lives here; the run only demonstrates the diffusion-recovery, Euler/Stokes limits, and the Ma² incompressibility scaling.

This file inherits the §0 anti-creep protocol and rules R0–R5. Every constant is ledgered (R2); no magic factor is inserted (R5).

---

## 0. Setup — the medium and its primitives

**The unit of the medium is a compressible but NOT deformable spherical spation.** Each spation is a sphere that can change its *volume* — it compresses and rebounds elastically, and that volume change is the only way it stores or passes a density/pressure change (this is what carries sound → FD05, and the `O(Ma²)` density response of §1). It does **not** change its *shape*: there is no internal shear mode, no distortion of the unit into an ellipsoid. **Volume-elastic, shape-rigid.**

The medium is a close packing of these spheres relaying contact-to-contact, with the single invariant signal speed `c = ℓ_P/t_P` (engine: `measured::c`, `measured::l_P`, `measured::t_P`; the run prints `(ℓ_P/t_P)/c = 1` exactly). The 1-D demonstration coarse-grains onto a grid of spacing `ℓ_P` ticking at `t_P`; that grid is a computational scaffold for the Laplacian, **not** a claim that the packing is cubic (the lattice-structure question is its own problem) — the derivation needs only that each sphere hands content *symmetrically* to its contacting neighbours.

**Consequence for viscosity (fixed here, used in §2).** Because the sphere is not deformable, shear stress in the flow *cannot* come from a fluid element straining — there is no element strain to have. The only way transverse momentum crosses a shear plane is the relay **hand-off between adjacent rigid spheres**. So the viscous term `ν∇²v` is forced to be an **inter-sphere relay** quantity, never an **intra-sphere deformation**: SDT shear viscosity is a relay coefficient (`ν = w·ℓ_P·c`), not an elastic-deformation modulus. This is exactly Term A below, and it is *required* by non-deformability, not assumed for convenience.

- A coarse cell `i` (a block-average over many spheres) holds a coarse velocity `u_i` (the block-averaged momentum-per-load being relayed) and a relay content `q_i` (its share of the conserved spation count / displacement load).
- Per tick, sphere-to-sphere relay exchanges content with the `2D` contacting neighbours (`D` = spatial dimension; 1-D ⇒ 2 neighbours).
- An acceleration registers as a Granular-Pulse-Invariant (GPI, FLM02) asymmetry `δ_i = a_i t_P / c` in the per-direction pulse rate; constant velocity is symmetric (free), acceleration is asymmetric (costs) — this is Newton I–III at the sphere level.

The **discrete relay update rule** (Phase 1):

```
u_i(t+t_P) = u_i(t)                                   (held content)
           + w · [ u_{i-1} − 2u_i + u_{i+1} ]          (nearest-neighbour share)
           − (t_P/ρ) · (∂P/∂x)_i                       (pressure asymmetry, Law I/III)
           − (advective shift from u·∇u)               (transport of own field)
```

`w ∈ [0, ½]` is the fraction of content handed to **each** neighbour per tick (so cell keeps `1−2w`). It is the only dimensionless lattice number; its physical value is **PENDING FD02/ROOT-SIM** (DERIVED-form, value-pending). When `w=0` and `δ=0` the rule is free streaming; the run confirms zero drift in that case.

---

## 1. Continuity → incompressibility (Phase 3)

Spation count is conserved: nothing is created or destroyed, only relayed. The discrete count balance over a cell is

```
q_i(t+t_P) − q_i(t) = − Σ_faces (outgoing − incoming)
```

Block-averaging over a box `L ≫ ℓ_P` and Taylor-expanding the face fluxes to first order in `ℓ_P/L` gives the **continuity equation**

```
∂ρ/∂t + ∇·(ρ v) = 0.                                   (T-continuity)
```

Now invoke the movement budget (Law V, `law_V`): `v_circ² + v_trans² = c²`. The translational flow speed is `|v| = Ma · c_s` with `c_s ≤ c`; the expansion parameter is `Ma = |v|/c_s`. Standard low-Mach asymptotics on (T-continuity) give the density response

```
δρ/ρ = −½ Ma² v̂²  +  O(Ma⁴),                           v̂ = v/|v| shape (O(1))
```

so density fluctuations are **second order in Ma**. Substituting into continuity and keeping leading order:

```
∇·v = −(1/ρ) Dρ/Dt = O(Ma²)   ⟹   ∇·v → 0  as  Ma → 0.
```

**This is incompressibility as spation-count conservation in the low-Mach limit, not an axiom.** The compressible correction is `O(Ma²)` and is handed to FD05 (sound).

**Numerical check (run, Phase 3):** the residual divergence the incompressible projection must remove was swept over `Ma ∈ [0.00625, 0.2]`; the fitted log-log power-law exponent is **2.000000**, confirming `‖∇·v‖ ∝ Ma²` (falsification test F2 passes). Predicted before run: ≈2.0.

---

## 2. Momentum → the NS bijection (Phase 2, the core gate)

Coarse-grain the relay update by Taylor-expanding each neighbour value about cell `i`:

```
u_{i±1} = u_i ± ℓ_P ∂_x u + ½ ℓ_P² ∂_xx u ± ⅙ ℓ_P³ ∂_xxx u + …
```

### Term A — neighbour sharing → diffusion `ν∇²v`
This is the **inter-sphere relay hand-off** of §0 — transverse momentum passed between rigid spheres across a shear plane, *not* any deformation of a sphere (the units do not strain). The symmetric share `w(u_{i-1} − 2u_i + u_{i+1})` is, by the expansion, exactly the discrete Laplacian:

```
w (u_{i-1} − 2u_i + u_{i+1}) = w ℓ_P² ∂_xx u + O(ℓ_P⁴).
```

Dividing by the tick `t_P` and generalising to `D` dimensions (the `2D` contacting neighbours assemble `∇²`):

```
relay smoothing  →  ν ∇²v,        ν = w · ℓ_P²/t_P = w · ℓ_P · c     (length × speed).
```

- The **odd-order term `± ⅙ ℓ_P³ ∂_xxx u` cancels exactly** because the share is symmetric (left and right weights equal) — so **no spurious dispersion at this order** (the F1 surplus-term test). This is why the rule must be a *symmetric* random walk: an asymmetric share would leak a `∂_xxx` term that NS lacks.
- ν is a *length × speed*; its dimensionless coefficient `w` is **PENDING FD02/ROOT-SIM**. The form is DERIVED; the value is deferred. The numerical run uses the **identity** `ν = w·dx²/dt` and recovers it from variance growth `σ²(t)=σ₀²+2νt` to a relative error of **2.9×10⁻¹⁰** (Phase 1+2), confirming the lattice Laplacian → `∇²` map.

### Term B — pressure asymmetry → `−(1/ρ)∇P`
The GPI pulse asymmetry across a cell is set by the gradient of the effective convergence throughput. The ambient field is isotropic `P_conv ≈ 2.46×10⁴⁸ Pa` (engine `law_I::P_conv`, DERIVED = Φ/ℓ_P³); only its **gradient** nets a force (Law III occlusion differences, `law_III::solid_angle_occluded`). Per unit displacement-load (mass, Law IV):

```
pressure asymmetry  →  −(1/ρ) ∇P.
```

No attractive term exists — pressure differences *are* occlusion differences.

### Term C — held content transport → `∂v/∂t + (v·∇)v`
A cell carries its own velocity field with it as the relay advects content. The material (held-content) derivative of `v` expands as

```
held transport  →  ∂v/∂t + (v·∇)v       (the inertial / advection term, GPI Newton I–III).
```

### Assembling — the bijection
Collecting Terms A, B, C at leading order in `ℓ_P/L` and `v/c`:

```
   ∂v/∂t + (v·∇)v  =  −(1/ρ)∇P  +  ν∇²v ,        ∇·v = 0.
   └── Term C ──┘     └Term B┘    └Term A┘        └─ §1 ─┘
```

**Bijection table (F1):**

| NS term | Lattice mechanism | Engine anchor | Provenance |
|---|---|---|---|
| `∂v/∂t + (v·∇)v` | held-content transport + GPI inertia | FLM02, `law_V` | DERIVED (structure) |
| `−(1/ρ)∇P` | convergence-pressure gradient / occlusion asymmetry | `law_I::P_conv`, `law_III` | DERIVED (structure); `P_conv` DERIVED value |
| `ν∇²v` | symmetric nearest-neighbour relay share (lattice Laplacian) | FLM05, FD02 | form DERIVED, coefficient `w` PENDING FD02 |
| `∇·v = 0` | spation-count conservation, low-Mach (Ma²) | `law_V` | DERIVED (limit) |
| ρ | displacement-load density | `law_IV` `V_disp` | DERIVED (not kg-fundamental) |

**Every NS term maps to exactly one lattice mechanism, and every leading-order lattice mechanism lands on exactly one NS term.** No surplus leading-order term survives (the odd-order `∂_xxx` cancels by symmetry); no NS term is missing. Checkpoint C2 holds at the structural level. The first uncancelled correction is the `O(ℓ_P²)` Burnett-order term (hyperviscosity `∝ ℓ_P² ∇⁴v`), which is `O((ℓ_P/L)²)` smaller than `ν∇²v` and is the standard SDT-distinct candidate handed to later FD work — NOT a leading-order falsifier.

---

## 3. Limits (Phase 4) — recovered from the *same* PDE, no re-derivation

- **Euler (inviscid):** set the relay-smoothing coefficient `ν → 0` (`w→0`, perfect handoff). Term A vanishes; left with `∂v/∂t + (v·∇)v = −(1/ρ)∇P`. The run evolves a profile with `ν=0` under pure advection: the peak translates exactly **100 cells** (= `U·n·Δt/Δx`), advection demonstrably alive. (The residual 5.8% amplitude drop is first-order *upwind numerical* diffusion, NOT the physical `ν` term — flagged honestly in the output; an exact-advection scheme would show zero decay.)
- **Stokes (creeping, Re≪1):** set advection `(v·∇)v → 0`. Left with `∂v/∂t = −(1/ρ)∇P + ν∇²v`; for a single Fourier mode the analytic decay is `exp(−νk²t)`. The lattice relaxation matches the analytic exponential to **0.0196%** (< 1%, falsification test F4 passes; predicted < 1%).

Both are limits of the one Phase-2 PDE, not separate models (Checkpoint C4).

---

## 4. Parameter ledger (R2)

| Quantity | Symbol | Status | Source |
|---|---|---|---|
| Signal speed | `c` | MEASURED-INPUT (SI exact) | `measured::c` |
| Planck length | `ℓ_P` | MEASURED-INPUT (Axiom R1) | `measured::l_P` |
| Planck time | `t_P` | MEASURED-INPUT | `measured::t_P` |
| Convergence pressure | `P_conv` | DERIVED (Φ/ℓ_P³) | `law_I::P_conv` |
| Density | `ρ` | DERIVED (displacement-load, Law IV) | `law_IV` `V_disp` |
| Kinematic viscosity form | `ν = w ℓ_P c` | DERIVED (form) | this derivation |
| Diffusion coefficient `w` | `w` | **PENDING FD02/ROOT-SIM** | downstream |
| Relay rule `ν` (run identity) | `w·dx²/dt` | DERIVED (identity) | run, Phase 1+2 |
| Mach amplitudes, dx, dt (demo) | — | ASSUMED (dimensionless demo units) | run |
| Fitted fluid `ν` scale | — | **CALIBRATED(0) in this run** | deferred to FD02 Phase-5 |

No magic integer or π was inserted to hit any target (R5). The only number that *could* become CALIBRATED — one fluid `ν` scale — is **deferred to the FD02 handshake**; this tool sets **zero** fluid scales.

---

## 5. What is and is not established

**Established (numerically, this run):** lattice Laplacian → `∇²` with ν recovered to 2.9e-10; `‖∇·v‖ ∝ Ma²` (exponent 2.000000); Stokes mode decay matches `exp(−νk²t)` to 0.02%; Euler advection survives `ν→0`; exact count/throughput conservation.

**Established (analytically, this file):** the term-by-term bijection NS ↔ relay mechanics with no surplus/missing leading-order term.

**Not established (honest gaps):** the *numerical value* of `w` (hence `ν`'s dimensionless coefficient) is PENDING FD02/ROOT-SIM — so Class A is not reachable here. The full multidimensional advection coarse-graining and the pressure-projection (Helmholtz) closure are stated, not numerically solved (this is a 1-D demonstration, per the spec). The Phase-5 coefficient handshake and a measured-benchmark (Poiseuille / Taylor–Green) check are explicitly deferred to FD02.

This is a **correspondence/reproduction** of a known PDE from SDT primitives — the expected honest outcome is **Class C**.
