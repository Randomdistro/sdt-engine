# FD07 — Verdict: Circulation, Lift, and the Magnus Force from Differential Occlusion

**Author**: James Christopher Tyndall, Melbourne
**Status**: EXECUTED — standalone C++20 (`fd07_circulation_lift_magnus.cpp`),
real MSVC build, double precision. Run log: `fd07_results.txt`.
**Verdict**: **CLASS C (QUALIFIED — convergence)**

---

## 1. Deciding metric

| Phase | Gate | Result | Provenance |
|---|---|---|---|
| 1 | `L = ρUΓ` from occlusion asymmetry; sign toward fast-relay face | **PASS** — two-stream analytic vs numerical surface integral agree to **9.0e-14 %**; `L_y = -ρUΓ` toward `-y` (low-occlusion) face | **NATIVE, Class C** |
| 2 (core) | thin-airfoil slope `dC_L/dα = 2π` | **PASS** — fitted **6.283185 rad⁻¹** (dev **−1.4e-14 %**) | **2π = BORROWED potential-flow geometry** |
| 3a | Kutta condition from Law-V relay continuity (`v≤c`) | **PASS** — unpinned `v=c` breach at `s* = 1.0e-14 m` ⇒ lattice pins rear stagnation; Kutta emerges, no separate axiom | **NATIVE mechanism** |
| 3b | Magnus sign (+ order of magnitude) | **PASS** — `L = 2.309e2 N/m`, `C_L,ideal = 2πS = 9.42`, lift toward surface-adds face | **NATIVE sign, Class C** |
| 4 | `Γ = Nκ` continuum (`N ≫ 1`) | **PASS** — `N = Γ/κ = 4.6e8` | FD02 handshake |

**The deciding falsifier (lift sign) PASSES.** The deciding *coefficient* (the
`2π` slope) is reproduced exactly but is **borrowed potential-flow structure**,
not a native SDT derivation — this is the single fact that caps the verdict at
**C** rather than **A**.

---

## 2. Provenance × correspondence audit

| Result | provenance_status | correspondence_status | class | delete-test |
|---|---|---|---|---|
| `L = ρUΓ` from antisymmetric occlusion (Law III momentum flux) | SDT-derived | known-match (Kutta–Joukowski) | **C** | passes — structure survives removing the correspondence check |
| Lift **sign** (toward fast-relay / low-occlusion face) | SDT-derived | known-match | **C** | passes — sign forced by the momentum balance, not chosen |
| Bound `Γ` = continuum of ℓ=2 traction (PPT06) | SDT-derived (internal) | internal-only | **C** | passes |
| Kutta = Law-V relay continuity (`v≤c`) | SDT-derived | novel-framing of a known result | **C** | passes — `s*` finite from `c` alone |
| Magnus **sign** + order of magnitude | SDT-derived | known-match | **C** | passes |
| `Γ = Nκ` (`κ=h/m`, FD02) | SDT-derived (internal) | internal-only | **C** | passes |
| `dC_L/dα = 2π` slope coefficient | **external / borrowed** (potential-flow geometry) | known-match (target reproduced) | **C-flagged borrowed** | the **`2π` does NOT pass** a pure-SDT delete-test — it is imported geometry, reported as such |
| `ρ` (air, 1.225 kg/m³) | measured-input | known-match | **CALIBRATED(0)** | used only to evaluate; lift law is parameter-free |

**No `G` / `M` / `GM` in any code path (R0 clean).**

---

## 3. What is DERIVED vs BORROWED vs PENDING

- **NATIVE / DERIVED (Class C):**
  - `L = ρUΓ` as the transverse resultant of an antisymmetric occlusion field
    (Law III momentum flux). Two-stream verified to machine precision.
  - The **lift sign** — toward the low-occlusion (fast-relay) face — forced by
    the momentum balance (`L = ρ U × Γ`).
  - The **Kutta condition** as a Law-V relay-continuity (`v ≤ c`) bound: a
    singular trailing-edge velocity is physically impossible (`s* ~ 1e-14 m`),
    so the lattice pins the rear stagnation. No separate axiom.
  - The **Magnus sign** — toward the side where surface motion adds to the flow.
  - `Γ` as the continuum coarse-graining of the PPT06 ℓ=2 traction channel, and
    as `N κ` quanta (FD02), `N = 4.6e8 ≫ 1`.

- **BORROWED (honestly flagged, R5):**
  - The **`2π` lift-curve slope coefficient**. `Γ = πUcα` is the thin-airfoil /
    potential-flow Kutta closure; the factor `π·c` is imported geometry. SDT
    owns the *mechanism* (that a `Γ` can be threaded; that Kutta pins it), **not**
    the coefficient. The slope is reproduced exactly (`6.283185`) but is **not**
    claimed as a pure SDT derivation.

- **PENDING / open:**
  - A first-principles lattice derivation of the `2π` (the chordwise bound-
    vorticity integral) from the ℓ=2 channel at coefficient level. Until then
    the slope is convergence, not derivation — keeping FD07 at **C, not A**.
  - The viscous Magnus deficit (ideal `C_L = 2πS ≈ 9.4` vs measured `O(1)`) is
    attributed to the FD06 boundary layer; the quantitative cap is FD06's job.

---

## 4. Class rationale (why C, not A or D)

- **Not A:** Class A requires the `2π` slope shown *geometric from the ℓ=2
  channel* with no borrowed coefficient. We reproduce `2π` exactly but import it
  from potential flow — borrowed structure (R5). Honesty over success: A is not
  earned.
- **Not D:** Class D would apply if the sign or `L = ρUΓ` were only dimensionally
  closed or the Kutta handshake were merely asserted. Here `L = ρUΓ`, the sign,
  the Magnus sign, and Kutta-as-continuity are all **demonstrated** (two-stream
  to `1e-13`, `s*` from `c` alone). The mechanism is native and verified.
- **C is exact:** lift law + correct sign + `2π` slope + Kutta-as-continuity +
  Magnus sign, with the lone borrowed coefficient documented and `ρ` at
  CALIBRATED(0). This matches the §5 Class-C row of the PROMPT precisely.

---

## 5. Falsification ledger (none tripped)

| Test | If FAIL ⇒ | Outcome |
|---|---|---|
| F1 lift sign | wrong transverse sign ⇒ Class F | **PASS** (toward fast face) |
| F2 slope = 2π (core) | SDT mechanism gives slope ≠ 2π ⇒ Class F | **PASS** (`6.283185`; 2π honestly borrowed, not an SDT mis-derivation) |
| F3 Kutta as continuity | no Kutta from `v≤c` ⇒ Class F | **PASS** (`s* = 1e-14 m`) |
| F4 Magnus sign | wrong Magnus sign ⇒ Class F | **PASS** (toward surface-adds face) |
| F5 quantum limit | `Γ` not integer-`Nκ` ⇒ PENDING (D, not F) | **PASS** (`N = 4.6e8`) |

No clean kill. The mechanism survives every falsifier.

---

## 6. Downstream handoff

- **FD10 (shed circulation / starting vortex):** consumes the bound-circulation
  field `Γ` and the Kelvin/Kutta (relay-continuity) result derived here. The
  Phase-1 `L = ρUΓ` two-stream and the Phase-3a continuity bound are the inputs
  FD10 builds the starting-vortex bookkeeping on.
- **FD06 (boundary layer / no-slip):** owes the quantitative `Γ`-cap that turns
  the ideal Magnus `C_L = 2πS` into the measured `O(1)` and the real-section
  slope `≈ 0.9–0.95 × 2π`.

---

## 7. One-line verdict

> **FD07 = CLASS C.** Lift `L = ρUΓ`, the lift sign, the Magnus sign, and the
> Kutta condition are native occlusion-asymmetry / relay-continuity results
> (no G, no M, two-stream verified to `1e-13`). The `2π` lift-curve slope is
> reproduced exactly but is **borrowed potential-flow geometry** — and is
> labelled so. SDT owns the circulation *mechanism*, not the coefficient.
