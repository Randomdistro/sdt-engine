# FD07 — Derivation: Circulation, Lift, and the Magnus Force from Differential Occlusion

**Author**: James Christopher Tyndall, Melbourne
**Status**: EXECUTED (standalone C++20, MSVC, double precision)
**Inherits**: §0 anti-creep protocol and rules R0–R5 verbatim.

This document records the full derivation chain whose numerical realisation is
`fd07_circulation_lift_magnus.cpp` (run log in `fd07_results.txt`). Standard
fluid-dynamics results — `L = ρUΓ`, the `2π` slope, the Magnus force, the Kutta
condition — are the **convergence targets** to *reproduce*, never inputs to
*borrow*. Where SDT supplies only the mechanism (and a textbook coefficient is
imported), it is flagged BORROWED in plain language (R5).

---

## 0. Ontology used (whitelist only)

- **Relay lattice / occlusion** (Law III): `F = (π/4) P_eff R₁²R₂²/r²` is a *push*,
  a momentum flux of convergence throughput. A fore/aft-symmetric occlusion is
  drag; a left/right-antisymmetric occlusion carries *transverse* momentum — lift.
- **ℓ=2 rotational traction** (PPT06, `law_VI::traction`): the lattice's organised
  two-lobed swirl response to a spinning vortex-knot. The engine wires this as
  `traction_ratio_proton = 3(W+1) = 12` (the rotational wake channel). Bound
  circulation `Γ` is the *continuum coarse-graining* of this channel — it is
  **induced**, not imposed.
- **Movement budget** (Law V): `v_circ² + v² = c²`, with `c = ℓ_P/t_P` the absolute
  relay ceiling. No lattice cell can exceed `c`; this forbids singular velocities.
- **Displacement-load = mass** (Law IV): `ρ` is reorganisation cost per volume,
  used to *weight* the momentum flux `ρU` and the swirl. Not kilograms-as-fundamental.
- **Circulation quantum** (FD02): `κ = h/m`; the smooth `Γ` is `N κ`, `N ≫ 1`.

**No G, no M, no GM anywhere.** Lift is a pure occlusion / momentum-flux quantity.

---

## 1. Phase 1 — Lift as occlusion asymmetry: `L = ρ U Γ`

Take a 2-D body (canonical: a cylinder of radius `a`) in a stream `U x̂`. The
steady surface occlusion (static-pressure) field splits as

    P(θ) = P_sym(θ)  +  ΔP(θ)
           └ drag ┘     └ lift (ℓ=2 antisymmetric) ┘

`P_sym` is the fore/aft (ℓ=1 radial) part: it integrates to drag and **zero**
transverse force. `ΔP` is the antisymmetric part driven by the ℓ=2 traction
(the bound swirl `Γ`). For potential flow past the cylinder with bound
circulation `Γ` the surface speed is

    v(θ) = -2U sinθ + Γ/(2πa),

and the static occlusion deficit (FD08 / Bernoulli, a momentum-flux balance) is

    p(θ) = p∞ + ½ρ(U² - v²(θ)).

The transverse resultant of the surface push `-p n̂` (n̂ = (cosθ, sinθ)) is

    L_y = -∮ p sinθ · a dθ.

The constant and `sin²θ` terms integrate to zero (symmetric ⇒ no transverse
force); only the **cross term** `(-2U sinθ)·(Γ/2πa)` survives:

    L_y = -ρ U Γ      (per unit span).

So the **magnitude** is the Kutta–Joukowski identity `|L| = ρ U |Γ|`, and the
**sign is forced** by the momentum balance: with `U` in `+x` and a CCW bound
vortex (`Γ > 0`) the surface speed `v` is largest on the `-y` face, so the
occlusion deficit `p` is *lowest* there — **lift points toward the low-occlusion
(fast-relay) face** (`-y`). This is the cross-product `L = ρ U × Γ`.

**Two-stream check (R3).** The analytic signed lift `L_y = -ρUΓ` is compared to
a direct numerical sum of `-p n̂·ŷ` over 4096 surface panels. Run log:

| quantity | value |
|---|---|
| `|L| = ρU|Γ|` (KJ magnitude) | `4.410000e+02` N/m |
| `L_y` analytic `= -ρUΓ` | `-4.410000e+02` N/m |
| `L_y` numerical (panel integral) | `-4.410000e+02` N/m |
| two-stream agreement | `-9.0e-14 %` (machine precision) |
| lift direction | `-ŷ`, toward fast-relay face ✓ |

**Checkpoint C1: PASS.** `L = ρUΓ` recovered from the occlusion asymmetry alone,
sign correct (toward the fast face), zero fitted parameters, no G/M. **NATIVE.**

---

## 2. Phase 2 — Thin-airfoil slope `dC_L/dα = 2π`  (core gate)

For a thin flat plate of chord `c` at small angle of attack `α`, enforcing the
Kutta condition on the bound vortex sheet gives

    Γ = π U c α   ⇒   L = ρUΓ = π ρ U² c α
    C_L = L / (½ρU²·c) = 2π α   ⇒   dC_L/dα = 2π   per radian.

Run log: fitted slope `= 6.283185 rad⁻¹ = 2π`, deviation `−1.4e-14 %`; per-degree
`0.10966 deg⁻¹`; zero-lift angle `α₀ = 0` for a symmetric section.

### PROVENANCE — HONEST (R1/R5)

The coefficient `π·c` in `Γ = πUcα` is the **thin-airfoil / potential-flow**
result: it is the chordwise integral of the bound-vorticity distribution under
the Kutta closure — pure **geometry of potential flow**. SDT supplies:

- the **mechanism** that lets the lattice thread a bound `Γ` at all (the ℓ=2
  traction channel, PPT06), and
- the **continuity bound** (Phase 3a) that pins the Kutta value.

SDT does **not** derive the number `2π` from first lattice principles. Therefore
the `2π` slope is reported as **BORROWED potential-flow structure**, *not* as a
pure SDT derivation (R5: no free integer or π inserted to force the slope; the
`2π` is acknowledged as imported geometry). Real (thick, viscous) sections give
`≈ 0.9–0.95 × 2π`; that deficit is the **FD06 boundary layer**, not the SDT
mechanism.

**Checkpoint C2: PASS** numerically (slope `= 2π` to `1e-14`), with the `2π`
flagged borrowed. This is the honest reason FD07 is **Class C, not Class A**.

---

## 3. Phase 3a — Kutta condition as Law-V relay continuity

At a sharp trailing edge (interior angle → 0) an **unpinned** rear stagnation
point forces the potential flow to round the corner, where the ideal surface
speed diverges as `v(s) ~ U √(L_ref/s)` (`s` = arc distance from the edge). The
lattice relays at most at `c` (Law V `v_circ²+v²=c²`). Hence the unpinned
solution would breach `v = c` at a **finite** distance

    s* = L_ref · U²/c².

Run log: for `U = 30 m/s`, `L_ref = 1 m`, `s* = 1.0e-14 m` — *sub-Planck-tiny*.
A singular relay is physically impossible, so the lattice **pins the rear
stagnation at the edge** (smooth tangential shed) — which is exactly the Kutta
condition. That pinning **uniquely fixes `Γ`** (the FD06 boundary-layer
handshake). The Kutta condition is therefore **not a separate axiom**: it is the
relay-continuity bound of Law V. **Checkpoint C3a: PASS. NATIVE mechanism.**

---

## 4. Phase 3b — Magnus force on a spinning cylinder

Spin biases the relay directly: the surface drags the lattice into an ℓ=2 swirl
of strength `Γ = 2π a U_s` (`U_s = Ω a`, the continuum of the surface drag),
giving (Phase 1) `L = ρUΓ = 2π ρ a U U_s` per unit span. On the projected area
(chord = diameter `2a`) the ideal coefficient is `C_L = 2π S`, `S = U_s/U`.

**SIGN.** Lift points toward the side where the surface motion **adds** to the
oncoming flow — that face relays fastest ⇒ lowest occlusion. For a CCW spin
(`Ω > 0`) the bottom surface moves with the flow ⇒ fast face is `-y` ⇒ lift `-y`.
This is consistent with the Phase-1 cross-product sign.

Run log (sample: `a = 0.05 m`, `U = 20 m/s`, `Ω = 600 rad/s`, `S = 1.5`):

| quantity | value |
|---|---|
| `Γ = 2π a U_s` | `9.424778` m²/s |
| `L_ideal = 2π ρ a U U_s` | `2.309071e+02` N/m |
| `C_L,ideal = 2π S` | `9.4248` |
| lift direction | `-ŷ`, toward surface-adds face ✓ |

**Magnitude.** Measured cylinder Magnus `C_L ≈ 0.5–1.5` at `S ≈ 1–3`; the ideal
`C_L = 2πS ≈ 9.4` **overpredicts** (boundary-layer separation caps the effective
`Γ`). Per the spec, the convergence test is **sign + order of magnitude**, with
the viscous deficit attributed to FD06, not the SDT mechanism. Both are met.
**Checkpoint C3b: PASS.** Magnus sign is **derivable and correct (NATIVE)**.

---

## 5. Phase 4 — Quantized limit `Γ = N κ` and the continuum

Bound circulation is `N` quanta of the FD02 circulation quantum `κ = h/m`. Using
the medium-molecule mass (N₂, ~28 u) for `m`:

    κ = h/m_N2 = 1.425e-8 m²/s,   Γ_airfoil(α=4°) = 6.58 m²/s
    ⇒ N = Γ/κ = 4.6e8 ≫ 1.

The classical airfoil is the many-quantum (`N ≫ 1`) continuum of FD02. The
two-stream check of Phase 1 (analytic `ρUΓ` vs numerical panel integration,
agreement `9e-14 %`) closes the numerical handshake. **Checkpoint C4: PASS.**

---

## 6. Parameter ledger (R2)

| Symbol | Value | Status | Role |
|---|---|---|---|
| `c = ℓ_P/t_P` | `2.998e8 m/s` | WHITELIST primitive | Law-V relay ceiling (Kutta bound) |
| `h` | `6.626e-34 J·s` | WHITELIST (conversion) | FD02 `κ = h/m` |
| `traction_ratio_proton = 3(W+1)` | `12` | SDT-DERIVED (PPT06) | ℓ=2 channel that *is* bound `Γ` |
| `ρ` (air) | `1.225 kg/m³` | MEASURED-INPUT | weights `L = ρUΓ`; **CALIBRATED(0)** (evaluate only) |
| `ν` (air) | `1.48e-5 m²/s` | MEASURED-INPUT | Reynolds context, FD06 handshake (not used in lift law) |
| `U, α, a, Ω` | sample | INPUT (geometry) | test conditions |
| `Γ = πUcα` coeff `π·c` | — | **BORROWED** (potential flow) | thin-airfoil Kutta closure → `2π` slope |
| `2π` slope | `6.283185 rad⁻¹` | **BORROWED geometry** (target reproduced) | Phase-2 convergence target |
| `L = ρUΓ`, sign, Magnus sign, Kutta-as-continuity | — | **NATIVE (Class C)** | the SDT content |

No `G`, `M`, or `GM` enters any code path (R0 clean).

---

## 7. Falsification outcomes

| Test | Predicted | Result |
|---|---|---|
| F1 — lift sign | toward low-occlusion (fast-relay) face | **PASS** (`L_y=-ρUΓ`, two-stream `9e-14 %`) |
| F2 — slope = 2π (core) | `dC_L/dα = 2π`, 2π geometric (flagged borrowed) | **PASS** (`6.283185`, dev `1e-14`; honestly labelled BORROWED) |
| F3 — Kutta as continuity | `v≤c` pins rear stagnation, fixes `Γ` | **PASS** (`s*=1e-14 m`, singular relay impossible) |
| F4 — Magnus sign/mag | toward surface-adds face; right order | **PASS** (`-ŷ`; ideal `C_L=9.4` overpredicts, viscous→FD06) |
| F5 — quantum limit | `Γ = Nκ`, `N ≫ 1` | **PASS** (`N=4.6e8`) |

---

## 8. Verdict (summary)

**Class C (QUALIFIED — convergence).** `L = ρUΓ`, the lift sign, the Magnus
sign, and Kutta-as-relay-continuity are **native** consequences of occlusion
asymmetry (Law III) + the ℓ=2 traction channel (PPT06) + the Law-V ceiling. The
`2π` lift-curve slope is **borrowed potential-flow geometry** — reproduced and
honestly labelled, not claimed as a pure SDT derivation. That single borrowed
coefficient is exactly why the verdict is C and not A. `ρ` is CALIBRATED(0). No
G/M anywhere. Downstream: the bound-circulation field and the Kelvin/Kutta
result are exported to **FD10** (shed circulation / starting vortex).
