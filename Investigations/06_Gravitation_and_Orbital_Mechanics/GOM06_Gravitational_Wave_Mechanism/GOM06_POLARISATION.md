# CQ-44 · GATE G3 — Polarisation: why "move the sea" does not "make (scalar) waves"

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Status:** EXECUTED — kill-condition **AVOIDED**; conditional **Class C** with a novel falsifiable prediction
> **Grounded on:** the **Depth–Closure Theorem** (the spation rheology James fixed for this gate),
> CQ-40 (equation of state), CQ-42 (z=1 self-boundary), CQ-43 (variable closure `ℓ_P(r)=ℓ_P,∞(1−z)`).

---

## 0. The gate, and why it is the kill gate

G3 asks the one question that can kill the whole "move the sea" picture:

> Does the SDT gravitational wave carry only GR's **two transverse-traceless tensor modes** (`h₊`, `h×`),
> or does it leak a **scalar "breathing"** (and/or longitudinal) mode?

A breathing mode at order-unity amplitude is **excluded**: Hulse–Taylor and the double pulsar match
quadrupole-only GR orbital decay to ~0.1 %, and GW170817's multi-detector polarisation disfavours scalar/vector
content. If SDT's mechanism honestly forces such a mode, the model is dead (R4).

**The danger is real and structural.** The Depth–Closure Theorem makes SDT's *static* gravitational field a
**scalar** — the convergence depth `z(r) = ϟ/r`, with `ℓ_P(r)=ℓ_P,∞(1−z)`, `c_local=c(1−z)`, `dτ/dt=√(1−z)`.
A scalar-structured gravity generically radiates a breathing mode (the classic scalar–tensor signature, e.g.
Brans–Dicke). So G3 cannot be waved through — it must be **derived**.

---

## 1. What the Depth–Closure Theorem fixes (and what it does not)

**Fixes (the static/quasi-static sector):**
- one master scalar `z = ϟ/r`; closure tightens with load (H2) — the lattice is **compressible**, not a rigid
  floor;
- **one** propagation speed, the relay tick `c_local` (C4) — there is *no* separate, faster compression
  channel (the textbook `c_P=√((K+4μ/3)/ρ) ≫ c_S` split does **not** apply to a fixed-rate relay).

**Does not fix:** the **radiative** (propagating, dynamic) polarisation content. That is G3's job, and "one
speed" alone does **not** settle it — a massless field propagating at `c` still carries whatever
polarisations its **source multipole structure** allows. The resolution is therefore not kinematic (speed) but
**conservation-structural** (which multipoles can radiate).

---

## 2. The derivation — multipoles of the displacement-load

The source is the **displacement-load distribution** of the binary (Law IV mass = displaced convergence
volume). Expand its radiated depth-perturbation `δz(r,n,t)` in multipoles `ℓ = 0,1,2,…`:

| ℓ | source moment | conserved? | radiates? | detector polarisation |
|---|---|---|---|---|
| 0 (monopole) | **total `ϟ_tot = Σϟᵢ`** | **yes** (total displacement-load fixed) | **NO** (`d/dt ϟ_tot = 0`) | would be **breathing/scalar** |
| 1 (dipole) | momentum `Σϟᵢ rᵢ` | **yes** (centre-of-load) | **NO** | would be vector |
| 2 (quadrupole) | `Q_ij = Σϟᵢ(rᵢ rᵢ − ⅓r²δ)` | **no** (orbit modulates it at 2ω) | **YES — leading** | **transverse-traceless = `h₊,h×`** |

**The key SDT step.** The monopole moment is the *total* convergence depth `ϟ_tot`, and SDT conserves total
displacement-load: a moving sea conserves its volume. Hence **`d/dt ϟ_tot = 0` ⟹ no monopole radiation ⟹ no
breathing mode** — to the exact extent that total `ϟ` is conserved. Likewise momentum conservation kills the
dipole. The first **non-conserved** moment is the quadrupole, whose far field is intrinsically the `ℓ=2`,
transverse-traceless pattern — **GR's two tensor modes**. This is *why* "moving the sea" radiates shear, not
breathing: the breathing channel is the conserved monopole, and a conserved quantity cannot radiate.

This is the native content of "move the sea, **don't make waves**": the sea's *volume* (monopole) is fixed —
no scalar wave; only its *shape* (quadrupole) varies — tensor shear.

---

## 3. The residual scalar mode — and why it is not fatal (it is the memory)

The monopole is conserved **only as long as the binary radiates no energy.** During inspiral+merger, energy
*is* carried off, so the **total displacement-load decreases**: the final remnant's `ϟ_f` is less than the
initial `ϟ_i` by the radiated fraction. That change in the monopole is the **only** scalar/breathing source:

```
breathing admixture  ε_scalar  ~  Δϟ_tot / ϟ_tot  =  E_radiated / E_total
```

For **GW150914**: `M_i ≈ 65 M_⊙`, `M_f ≈ 62 M_⊙` (≈ 3 M_⊙ radiated) ⟹ **ε_scalar ~ 3/65 ≈ 4.6 %**.

Two things make this **survive the bounds**:
1. It is a **merger-epoch transient** tied to the *rate of change* of the monopole — it is **not** a steady
   inspiral radiation channel, so it does **not** appear in the Hulse–Taylor / double-pulsar orbital-decay
   budget (which constrains slow, weak-field inspiral where `Δϟ/ϟ` per orbit is ~`10⁻¹²`). The pulsar bound and
   a few-% merger breathing transient are **not in conflict**.
2. It is bounded by the radiated fraction (≤ ~10 % even for the most extremal mergers), never order-unity.

**The G3↔G4 identity (the elegant part).** The same `Δϟ_tot` that sources the breathing transient is the
**permanent change in the depth field** that constitutes the memory (G4): `Δh_mem = −Δz ∝ Δϟ_tot/r`. *The
breathing whisper and "she go forever" are the same quantity* — the net displacement-load the merger sheds.
"Move the sea" leaves the sea's volume changed by exactly what it radiated; that DC offset is the memory, and
its transient is the only scalar wave.

---

## 4. Verdict

- **Kill condition (order-unity scalar mode): AVOIDED.** The breathing channel is the conserved monopole;
  conservation of total displacement-load forbids it except for the radiated fraction `~Δϟ/ϟ`.
- **Leading radiation = quadrupole = the two tensor modes `h₊,h×`** — convergence with GR/data (Class C).
- **Novel, falsifiable SDT prediction:** a **scalar/breathing admixture `~ E_rad/E_total` (~few %) confined to
  the merger epoch**, *correlated with the memory offset* (same `Δϟ`). Distinct from GR (pure tensor + a
  separate, smaller nonlinear memory) and from generic scalar–tensor theories (steady inspiral scalar channel,
  already excluded). Tests: multi-detector (≥5) merger-time polarisation; LISA per-event memory↔breathing
  correlation; PTA scalar overlap-reduction function on the stochastic background.

**Honest pending (the coefficient, as with G2's 96/5):** the *exact* proportionality `ε_scalar = κ·(Δϟ/ϟ)`
requires the **dynamic extension of the Depth–Closure Theorem** (the radiative depth field, retarded `z(r,t)`),
which the static theorem does not supply. The **structural** result — monopole-conserved ⟹ no breathing except
from radiated `Δϟ`, quadrupole ⟹ tensor — is robust (it rests only on conservation + multipole order, the same
footing as the no-monopole/no-dipole theorems in GR). Class **C**, kill-condition avoided, coefficient pending.

---

## 5. Parameter ledger (R2)

| quantity | value | tag |
|---|---|---|
| `ϟ_tot` (GW150914) | ≈ 96 km (`= (M_i/M_⊙)·ϟ_⊙`) | MEASURED-INPUT (LIGO koppa) |
| radiated fraction `Δϟ/ϟ` | ≈ 4.6 % (3/65 M_⊙) | MEASURED-INPUT (LIGO) |
| `ε_scalar` (breathing admixture) | `~ Δϟ/ϟ` ≈ few % | DERIVED (structural); coefficient `κ` PENDING |
| monopole, dipole radiation | 0 | DERIVED (conservation of load, momentum) |
| quadrupole → `h₊,h×` | leading | DERIVED (multipole order) / CONVERGENCE with GR |

**Target state CALIBRATED(0):** met for the structural result (no fitted parameter); the coefficient `κ` is
PENDING the dynamic theorem, not fitted.
