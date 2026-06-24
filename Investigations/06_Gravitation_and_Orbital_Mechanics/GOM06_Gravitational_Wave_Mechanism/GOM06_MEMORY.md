# CQ-44 · GATE G4 — Gravitational-wave memory: "she stop, but also she go forever"

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Status:** EXECUTED — `cq44_memory.cpp`, MSVC, exit 0. Conditional **Class C** (magnitude convergence;
> the breathing↔memory identity is **distinctive**).
> **Builds on:** `CQ44_DYNAMIC_CLOSURE.md` (the trace/shear split), the Depth–Closure Theorem (the trace is
> the depth `z`), CQ-43 (`Δh = −Δz`), `CQ44_POLARISATION.md` (G3 — the same `Δϟ`).

---

## The claim

After ringdown the oscillation stops, but a **permanent strain offset** remains — the **memory**. In SDT it is
the **DC part of the trace (volumetric depth) response**: the merger radiates energy, so the binary's total
displaced volume — its combined koppa `ϟ_tot` — is permanently smaller by the **radiated koppa** `Δϟ_rad`, and
the detector holds that depth offset forever.

```
Δϟ_rad = ϟ_tot · (ΔM/M)                 a LENGTH (the radiated koppa) — no G, no M
Δh_mem = η · Δϟ_rad / R                  η = O(1) sky/inclination factor
       = η · Δz(detector)                memory = permanent change in depth (CQ-43:  Δh = −Δz)
```

*"Move the sea" and the sea's volume changes by exactly what it radiated — and stays changed. That DC offset is
the memory.*

---

## The number (GW150914) — `cq44_memory.cpp`

| quantity | value | tag |
|---|---|---|
| `ϟ_⊙ = GM_⊙/c²` | 1.4766 km | MEASURED-INPUT (orbital `GM_⊙`, no G/M apart) |
| `ϟ_tot` (M=65 M_⊙) | 96.0 km | MEASURED-INPUT (⟦LIGO koppa⟧) |
| `Δϟ_rad = 3·ϟ_⊙` | **4.43 km** | DERIVED (ΔM≈3 M_⊙ radiated) |
| `Δϟ_rad/ϟ_tot` | **4.6 %** | = the **G3 breathing fraction** |
| `R` (luminosity distance) | 410 Mpc = 1.265×10²⁵ m | MEASURED-INPUT |
| `Δh_mem` (η=1) | 3.5×10⁻²² | DERIVED |
| `Δh_mem` (η≈0.2, sky-avg) | 7×10⁻²³ | DERIVED (η convergence) |
| `Δh_mem / h_peak` | **7 % … 35 %** | vs GR memory estimate **~5–20 %** → **ORDER-MATCH** |

The memory is `Δh = Δϟ_rad/R` — a **radiated length over a distance**. `GM=c²ϟ` enters once (to read the
radiated mass-energy as a koppa); G and M appear nowhere else.

---

## The distinctive result — G3 ≡ G4

The *same* `Δϟ_rad` (4.6 %) produces:
- the **AC** breathing **transient** at merger (Gate G3), and
- the **DC** permanent memory (Gate G4).

They are one quantity, high-pass vs low-pass filtered. **GR predicts the memory, but not its identity with a
breathing transient.** SDT predicts they are **correlated and equal in source** — a clean, distinctive
falsifier:
- **LISA** — per-event memory step *and* the merger-time breathing admixture, same amplitude scale;
- **PTA** — burst-with-memory ↔ scalar overlap-reduction correlation;
- **≥5-detector networks** — merger-epoch scalar polarisation tracking the memory.

---

## Detectability & honest scope

- **LIGO single event:** `Δh_mem ~ 10⁻²²` is below single-event sensitivity; detection needs **stacking**
  (~hundreds–thousands of events, matching the GR memory-detection forecast). Not yet seen — consistent.
- **Convergence vs native:** the **magnitude** `Δh = η·Δϟ_rad/R` converges with GR (same radiated energy, same
  quadrupole `η`); the **breathing↔memory identity** is native and distinctive. `η` itself is the `O(1)`
  sky/inclination factor **shared** with GR (CONVERGENCE), not a native SDT derivation — same honesty class as
  G2's `96/5`.
- **Strong-field caveat:** `Δϟ_rad` uses the *measured* radiated fraction; deriving `ΔM/M` itself from the
  strong-field merger (`z→1`) is **OPEN** (beyond the linearised Axiom R — see `CQ44_DYNAMIC_CLOSURE.md` §5).

---

## Verdict

G4 **EXECUTED**, conditional **Class C**: the memory is a permanent volumetric-depth offset
`Δh = η·Δϟ_rad/R`, magnitude order-matching GR (7–35 % vs 5–20 % of peak), expressed as a radiated **length**
with no G/M in the dynamics. Its **identity with the G3 breathing transient** (same `Δϟ_rad`) is the
distinctive, falsifiable SDT prediction. The four-gate picture is closed at convergence level; the open frontier
is the **strong-field / nonlinear** sector (`z→1`, ringdown QNMs, E68 echoes, native `ΔM/M`).
