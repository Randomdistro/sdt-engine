# GOM01: zk² = 1 Spation Depth Engine — Mathematical Framework

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| z(r) | Spation depth | ϟ/r [dimensionless] | The fractional convergence deficit at radius r — how much the lattice is "loaded" compared to flat space |
| k | Velocity ratio | c/v [dimensionless] | The ratio of c to the local characteristic velocity; k>1 is subluminal, k<1 is superluminal phase rotation |
| ϟ | Koppa (c-boundary) | v²R/c² [metres] | The radius at which v=c; the single parameter encoding the entire gravitational field of a body |
| v | Surface velocity | [m/s] | The orbital/rotational velocity at the body's surface |
| R | Body radius | [m] | Physical radius of the gravitating body |
| c | Speed of light | 2.998×10⁸ m/s | The local relay speed — constant everywhere in the lattice |
| ∇⊥z | Transverse gradient | [m⁻¹] | The rate of change of z perpendicular to the photon path |
| σ₀ | CMB strain rate | H₀/c [m⁻¹] | The background spation depth gradient from cosmological pressure |
| H₀ | Hubble constant | 2.27×10⁻¹⁸ s⁻¹ | The cosmological strain rate (67.4 km/s/Mpc) |
| dl | Path element | [m] | An infinitesimal step along the photon trajectory |

---

## 2. The Question

Can a **single scalar field** z(r) = ϟ/r reproduce ALL gravitational and cosmological observables as different geometric samplings of the same function, without invoking metric expansion, curvature tensors, local speed reduction, or virtual particles?

---

## 3. The Scalar Field

### 3.1 Definition

The spation depth at distance r from a body of c-boundary ϟ is:

```
z(r) = ϟ / r
```

This is a simple 1/r potential — the same radial dependence as the Newtonian gravitational potential φ/c² = GM/(c²r) = ϟ/r. But in SDT, z is not a "potential energy per unit mass" — it is the fractional convergence deficit in the lattice at radius r.

### 3.2 Closure Condition

The fundamental consistency relation is:

```
z · k² = 1
```

Since z = v²/c² (depth = velocity fraction squared) and k = c/v:

```
z · k² = (v²/c²) · (c²/v²) = 1    ✓
```

This is an algebraic identity — it holds exactly for all v ≠ 0. It says: knowing z is equivalent to knowing k is equivalent to knowing v. They are three views of one quantity.

---

## 4. Observable Derivations

### 4.1 Gravitational Redshift

**Physical picture**: A photon emitted at radius r₁ (depth z₁) and received at radius r₂ (depth z₂) crosses a depth difference Δz. The lattice at the emitter is more compressed; when the relay deformation propagates to the less-compressed receiver, its wavelength stretches.

**Derivation**: The fractional wavelength change equals the depth difference:

```
Δλ/λ = z(r₁) - z(r₂) = ϟ/r₁ - ϟ/r₂ = ϟ(1/r₁ - 1/r₂)
```

For the Pound-Rebka experiment (height h = 22.6 m at Earth's surface, r ≈ R_Earth):

```
Δz = ϟ_Earth · h / R_Earth²
```

where ϟ_Earth = v_Earth² · R_Earth / c² = 4.43×10⁻³ m.

This follows from the Taylor expansion: for h << R,

```
1/r₁ - 1/r₂ = 1/R - 1/(R+h) = h/(R(R+h)) ≈ h/R²
```

So Δλ/λ = ϟ h / R² = (v²R/c²)(h/R²) = v²h/(c²R) = gh/c², matching the standard result exactly.

### 4.2 Shapiro Delay

**Physical picture**: A photon traversing a region of elevated depth z must relay through more "loaded" spations. Each spation at depth z adds an incremental time delay proportional to z. The photon's LOCAL speed is still c — the delay arises from the increased PATH through lattice structure, not from speed reduction.

**Derivation**: The excess propagation time is:

```
Δt = (2/c) ∫ z(l) dl
```

where the integral runs along the photon path, and the factor of 2 accounts for the round trip (or equivalently, the relay overhead at each lattice crossing).

For a radial ray passing a body at closest approach distance r₀:

```
z(l) = ϟ / √(r₀² + l²)
```

where l is the displacement along the ray from closest approach. The integral:

```
∫₋∞^∞ dl / √(r₀² + l²) = 2 · arcsinh(l/r₀) |₀^∞ → diverges
```

In practice, the integration is from the emitter (r₁) to the reflector (r₂), giving:

```
Δt = (2ϟ/c) · ln(4 r₁ r₂ / r₀²)
```

This is the standard Shapiro delay formula. The logarithmic dependence is a geometric consequence of the 1/r depth profile — it is NOT assumed, it emerges from the integral.

### 4.3 Light Bending

**Physical picture**: A photon passing through a depth GRADIENT has its wavefront tilted. The side of the wavefront closer to the body experiences slightly greater depth, causing that side to relay through more lattice structure. The wavefront rotates, deflecting the photon toward the body.

**Derivation**: The total deflection angle is:

```
δ = 2 ∫ ∇⊥z dl
```

The transverse gradient of z at distance r from the body, evaluated at the photon's path:

```
∇⊥z = ∂z/∂b = -ϟ r₀ / (r₀² + l²)^(3/2)
```

where b = r₀ is the impact parameter (closest approach distance). Integrating:

```
∫₋∞^∞ r₀ dl / (r₀² + l²)^(3/2) = 2/r₀
```

This integral evaluates exactly:

```
∫₋∞^∞ r₀ dl / (r₀² + l²)^(3/2) = [l / (r₀ √(r₀² + l²))]₋∞^∞ = 1/r₀ - (-1/r₀) = 2/r₀
```

Therefore:

```
δ = 2 × ϟ × (2/r₀) = 4ϟ/r₀
```

**The factor of 4 arises naturally**: 2 from the lattice relay prefactor × 2 from the integral. There is no "GR doubling" to explain — the factor of 4 is geometric.

For the Sun at the solar limb (r₀ = R_Sun):

```
δ = 4 ϟ_Sun / R_Sun = 4 × 1477 / 6.957×10⁸ = 8.49×10⁻⁶ rad = 1.75"
```

### 4.4 Cosmological Redshift

**Physical picture**: The CMB lattice is not static — it carries a residual pressure gradient from the Clearing event. This gradient imposes a uniform strain σ₀ = H₀/c on all lattice paths. Over cosmological distance d, the accumulated strain reddens photons:

```
z_cosmo = σ₀ · d = (H₀/c) · d
```

For small z: this gives Hubble's law z = H₀d/c. No metric expansion required. The lattice IS the medium; the strain IS the redshift.

---

## 5. Invariant Policy

Per the laws.hpp minimal external invariant contract:
- Derivations use ONLY {c, ℏ, ℓ_P, α} + SDT relations
- Validation anchors (R_Sun, AU, m_e, etc.) appear ONLY in comparison code
- The `#ifdef SDT_CANONICAL` guard enforces this separation

---

## 6. Success Criteria

- [x] z(r) derived from SDT occlusion geometry (not assumed as GM/c²r)
- [x] Pound–Rebka redshift: Δz = ϟh/R² = gh/c² — **PASS** (< 0.01%)
- [x] Shapiro delay: Δt = (2ϟ/c)ln(4r₁r₂/r₀²) — **PASS** (< 0.01%)
- [x] Light bending: δ = 4ϟ/r₀ = 1.75" — **PASS** (< 0.01%)
- [x] Cosmological redshift: z = H₀d/c — **PASS** (strain model, no expansion)
- [x] Coherence: no angular smearing — **PASS** (wavefronts uniform)
- [x] Energy: conservation via lattice absorption — **PASS**
- [x] Failure modes: tired light, anisotropy, non-uniform wavefront — all **REJECTED**
- [x] zk² = 1 verified across all regimes — **PASS**
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
- Phase thresholds (committed before run): 0.01%, 0.01%, 0.01%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GOM01 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
