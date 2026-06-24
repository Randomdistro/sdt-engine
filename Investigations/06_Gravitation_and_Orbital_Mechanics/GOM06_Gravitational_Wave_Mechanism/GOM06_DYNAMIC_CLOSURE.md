# CQ-44 · The Dynamic (Radiative) Extension of the Depth–Closure Theorem

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Status:** EXECUTED — supplies the coefficients G2/G3/G4 had left pending; one posited axiom (the radiative
> shear sector), everything downstream is convergence with linearised GR.
> **Extends:** the **Depth–Closure Theorem** (static sector, `laws.hpp::depth_closure`) into the propagating
> regime. **Resolves:** the G3 polarisation question at its root (why the radiated field is a genuine tensor).

---

## 0. Why a dynamic extension is needed

The Depth–Closure Theorem is **static**: `z(r)=ϟ/r` satisfies Laplace's equation in vacuum (`∇²z=0`, the
1/r potential). It governs redshift, orbits, lensing, Shapiro — everything that does **not** propagate. But a
gravitational wave *propagates*, and the static theorem says nothing about:
- the radiative coefficient of the chirp (G2's `96/5`),
- the polarisation content (G3 — is the radiated field scalar or tensor?),
- the memory amplitude (G4).

All three were correctly left **PENDING** because they live in a sector the static theorem does not contain.
This note adds that sector with **one posit**, then shows the three coefficients follow.

---

## 1. The one posit — the radiative axiom

> **Axiom R (radiative closure).** The relay-lattice deformation is a rank-2 **strain tensor** `ε_ij`. Its
> disturbances propagate by the relay at the local speed `c` (one tick, one spation — CQ-43 C4). A static load
> produces a static strain (the Depth–Closure solution); a *time-varying* load launches a propagating strain
> that obeys the relay wave operator `□ = (1/c²)∂_t² − ∇²`.

This is the minimal dynamical completion: the same medium, the same speed, now with a time-derivative. It adds
**no new constant** — the source normalisation is fixed by matching the static limit to the koppa `z=ϟ/r`.

---

## 2. The decomposition that resolves G3

Split the strain into its **trace** (volumetric) and **traceless** (shear) parts:

```
ε_ij = (1/3) θ δ_ij  +  σ_ij ,      θ = tr ε  (volumetric),   σ_ij = traceless shear
```

| part | physical meaning | source moment | static/radiative | polarisation |
|---|---|---|---|---|
| **θ** (trace, volumetric) | the **depth** `z` — local closure `ℓ_P(r)=ℓ_P,∞(1−z)`; `θ ≈ −3 z` | **monopole** = total displaced volume `ϟ_tot` | **static** (`∇²θ`=source, 1/r) | breathing (scalar) |
| **σ_ij** (traceless, shear) | the **gravitational wave** — shape distortion at fixed volume | **quadrupole** `Q_ij` | **radiative** (`□σ_ij`=source) | **transverse-traceless `h₊,h×`** |

**This is the resolution of G3 at its root.** The depth `z` (the Depth–Closure scalar) is the **trace** —
the volumetric/breathing part. The **radiative degree of freedom is the traceless shear `σ_ij`**, a genuine
spin-2 tensor — so the gravitational wave is **tensor-polarised by construction**, not a scalar field wearing
an `ℓ=2` angular pattern. *This is exactly E48's "transverse lattice rigidity" and the literal content of
"move the sea, don't make waves": the sea's **volume** (trace `θ`) is the static field; its **shape** (shear
`σ`) is the wave.*

The earlier G3 conservation argument (`CQ44_POLARISATION.md`) and this one are the **same fact seen twice**:
the breathing channel is the trace, the trace is sourced by the conserved monopole (total displaced volume), so
the only radiated trace is the **change** `Δθ ∝ Δϟ` during merger. The shear carries the wave; the trace carries
the (suppressed) breathing and the memory.

---

## 3. The coefficients, now supplied (convergence)

With Axiom R, the shear sector is `□σ_ij^{TT} = −(source)_ij`, source normalised so the static trace reproduces
`z=ϟ/r`. This is **structurally identical** to linearised GR's `□h̄_ij = −(16πG/c⁴)T_ij` with the single
substitution **`GM → c²ϟ`** (the koppa bridge). Therefore the standard weak-field radiative results follow **by
convergence** — SDT and GR reduce to the *same* TT wave equation for the potential, sourced by the *same*
quadrupole kinematics:

- **Chirp coefficient (G2's `96/5`).** The orbit-averaged quadrupole luminosity `dE/dt ∝ ⟨Q⃛_ij²⟩` gives
  `df/dt = (96/5) π^{8/3} (ϟ_c/c)^{5/3} f^{11/3}` — the `96/5` is the quadrupole-geometry factor, **shared**
  (convergence), now grounded rather than borrowed-as-target. `ϟ_c = Gℳ_c/c²` is the chirp koppa.
- **Strain amplitude.** `h ≈ (4 ϟ_μ/R)(π f ϟ_tot/c)^{2/3}` with `ϟ_μ = Gμ/c²` (reduced-mass koppa) — purely
  lengths, `c`, `f`; **no G, no M**.
- **G3 coefficient `κ`.** The radiated breathing fraction is `ε_scalar = κ·(Δϟ/ϟ)` with `κ = O(1)` the same
  sky/inclination factor as the memory (§4) — no longer an unknown, just the quadrupole-geometry `O(1)`.

**Honest label.** Axiom R is a **posit** (the radiative completion); *given it*, these coefficients are
**CONVERGENCE** (shared with GR), not independent first-principles SDT derivations. What is **native and
distinctive** is the trace/shear identification (§2) and the G3↔G4 unification (§4) — predictions GR does not
make.

---

## 4. The distinctive output: memory = trace DC offset = the breathing's twin (feeds G4)

The trace `θ` (depth) is conserved while no energy leaves. Inspiral+merger radiate energy → the total displaced
volume drops by the radiated koppa:

```
Δϟ_rad = ϟ_tot · (ΔM/M) = (E_rad/c²)·(G/c²)      [a LENGTH; G only via the bridge GM=c²ϟ]
```

This single `Δϟ_rad` produces **both** halves of the trace response:
- **AC (G3):** a breathing **transient** during merger, amplitude `~ Δϟ_rad/R`;
- **DC (G4):** a **permanent** depth offset at the detector, `Δh_mem = η · Δϟ_rad/R` — the sea staying moved.

They are the same quantity (`Δϟ_rad`) low-pass vs high-pass filtered. **GR predicts the memory but not its
identity with a breathing transient; SDT predicts they are correlated** — a clean, distinctive falsifier (LISA
per-event; PTA burst-with-memory; ≥5-detector polarisation). Numbers in `CQ44_MEMORY.md`.

---

## 5. Ledger & scope

| result | status |
|---|---|
| trace/shear split → tensor GW (G3 root) | **DERIVED** (native; Axiom R + decomposition) |
| `96/5` chirp coeff, strain amplitude (G2) | **CONVERGENCE** given Axiom R (shared with GR via `GM=c²ϟ`) |
| `κ` breathing coeff (G3) | **CONVERGENCE** (= memory `O(1)` factor) |
| memory `Δh=η·Δϟ_rad/R` (G4) | **CONVERGENCE** magnitude; **DISTINCTIVE** identity with the breathing |
| strong-field `z→1` (near c-boundary) departures | **OPEN** (linearised theory breaks; needs full nonlinear `z`) |

**The honest boundary:** everything here is the *weak-field, far-zone* completion, which is exactly where SDT
*should* converge with GR (both are wave equations for the potential). The genuinely new physics is (i) the
trace/shear identification that makes the polarisation tensor *natively*, and (ii) the breathing↔memory
identity. The **strong-field** regime (`z→1`, the merger interior, ringdown QNM spectrum, E68 echoes) is **not**
covered by Axiom R's linearisation and remains open.
