# RTM02 — Velocity-Derived Mass and the Expulsion Ledger

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-08-03. **Status:** pre-registered
> before instrumentation.
> **Domain:** 17 Reactions & Thrust Mechanics. **Consumes:** RTM01 (the hover price
> 10^81.9/day at v_ex = 4.5 km/s is the anchor this investigation must reproduce, then alter).

## 0. The thesis, stated exactly

Propulsion is reactionary action priced purely by the **vector resistance of the expelled
quanta at their speed of expulsion**. The mathematics is rebuilt to show:

**velocity derives mass.** Presence (the baryon count N) and volume (the per-quantum
displacement at rest) are the invariable quanta of matter — they never change with speed.
What the reaction ledger reads as "mass" is resistance-to-vector-change, and resistance is
a function of the quantum's movement state. Law IV gives the rest resistance; Law V gears
it: a quantum at travel speed v holds circulation v_circ = √(c²−v²), and its resistance
gears as c/v_circ. Accelerating a quantum therefore **adds ledger-mass without adding a
single baryon or a single unit of rest displacement** — the added resistance is the
invested movement itself, worn as mass.

## 1. Permitted inputs

`bridge::koppa_Earth` (the hover row), c, R_E, v_ex as the swept engineering variable,
`law_IV` rest-resistance forms for the invariance statement. No G, no M as fundamentals;
no time-dilation postulate — the gearing must come from the movement budget alone.

## 2. Phases and pre-registered gates

- **P1 — the gearing law.** From v_circ² + v² = c² alone: resistance m(v) = m_rest·(c/v_circ).
  Gates: (a) c/v_circ ≡ 1/√(1−v²/c²) to machine precision across the range; (b) the
  classical limit m(v)→m_rest as v→0; (c) the added resistance Δm = m_rest(c/v_circ − 1)
  equals the invested movement E_k/c² identically — velocity deriving mass, as arithmetic.
- **P2 — two expulsion ledgers, kept apart.**
  - *Open ledger* (energy external, propellant-only bookkeeping): momentum per unit rest
    mass expelled = (c/v_circ)·v_ex. Hover mass ratio per time t: exp(a·t·v_circ/(c·v_ex)).
    Gate: reproduces RTM01's 10^81.9/day at v_ex = 4.5 km/s within 0.1 in the exponent.
  - *Closed ledger* (energy carried onboard, mass-energy complete): the energy invested in
    gearing the exhaust is itself expended mass, and the gearing **cancels exactly**:
    momentum per unit total expended mass = v_ex, never more. Gate: the cancellation to
    machine precision. Consequence, pre-registered as the investigation's theorem:
    **the price floor of reaction is the relay speed** — no closed ledger buys momentum
    cheaper than c, so the minimum hover price is exp(a·t/c) per unit time, with the
    photon rocket sitting exactly on the floor.
- **P3 — the sweep: altering 10^81.9 with velocity of output.** The hover price per day
  across v_ex = 4.5 km/s (chemical) → 50 km/s (ion) → 10³ km/s → 0.01c → 0.1c → 0.5c →
  0.9c → the c floor, both ledgers, whole-range single pass. Gate: monotone descent onto
  exp(a·t/c) = the floor row; photon-rocket power price stated (W per kg hovered).
- **P4 — the invariance split.** Per unit of momentum delivered: the baryon count expelled
  falls as the gearing rises while per-quantum rest displacement is untouched — presence
  and volume invariant, resistance velocity-derived. Print the N-per-newton-second column
  against v_ex.
- **P5 — the energy trade.** For a fixed mission Δv on the open ledger, the energy-optimal
  expulsion speed: minimise E(v_ex) = ½(e^{Δv/v_ex}−1)·v_ex² numerically. Gate: the
  minimum satisfies its own stationarity equation (self-consistent root), and the known
  scaling v_ex ≈ 0.63·Δv emerges rather than being inserted.

## 3. Falsification table

| ID | Condition that fails this investigation |
|----|------------------------------------------|
| F1 | gearing from Law V ≠ 1/√(1−v²/c²) anywhere in range |
| F2 | Δm ≠ E_k/c² (velocity-derived mass broken as arithmetic) |
| F3 | RTM01's 10^81.9 anchor not reproduced at chemical v_ex |
| F4 | closed-ledger γ-cancellation fails, or any closed ledger beats the c floor |
| F5 | optimum v_ex fails its own stationarity equation |

## 4. Scope, stated up front

The numerical forms coincide with special-relativistic rocket mechanics — shared form,
cannot discriminate on these numbers. The native content: the derivation route (movement
budget, no dilation postulate), the presence/volume-vs-resistance decomposition, and the
price-floor theorem read as relay economics.

## 5. Deliverables

`rtm02_velocity_mass.cpp` (VS2022 cl), `rtm02_results.txt`, `RTM02_VERDICT.md`,
domain README row.
