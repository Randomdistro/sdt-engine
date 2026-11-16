# RTM02 — Verdict (dual)

> **Author:** J. C. Harvey, Melbourne. Direct run 2026-08-03, main session, no agents.
> Tool: `rtm02_velocity_mass.cpp` (VS2022 cl `/std:c++20 /O2 /W4`, zero warnings,
> RUN_EXIT=0). Output: `rtm02_results.txt`. Pre-registration: `PROMPT.md` before the tool.
> Instrument repairs during bring-up, disclosed: an out-of-range constant (1e999 → 1e300),
> and the v_circ computation refactored to c·√((1−f)(1+f)) for conditioning at f → 1, with
> the G1a gate moved one notch (1e-10% → 1e-9%) to sit above double-precision cancellation
> noise rather than inside it. No physics content changed by either repair.

## Prompt completion: **A** — all five phases executed, 9/9 gates PASS, 0 FAIL.

## Physics class: **NATIVE (derivation route + decomposition + floor theorem) · SHARED-FORM (numerical values)**

**The thesis, now arithmetic.** From the movement budget alone — v_circ² + v² = c², no
dilation postulate — the ledger's mass is geared resistance:

```
m(v) = m_rest · c/v_circ          (G1a: equals 1/√(1−v²/c²) across the range)
Δm   = E_k/c²  identically        (G1c: the invested movement IS the added mass)
```

Accelerating a quantum adds resistance without adding one baryon or one unit of rest
displacement. **Velocity derives mass; presence and volume are the invariable quanta** —
P4 shows the baryons-per-newton-second column falling five orders across the v_ex sweep
while the per-quantum rest displacement column does not move at all.

**The two ledgers, kept apart (P2).**
- *Open ledger* (propellant-only): momentum per unit rest mass = (c/v_circ)·v_ex.
  Reproduces RTM01's anchor: 10^81.87 per day at chemical v_ex (G2a, 0.0009%).
- *Closed ledger* (mass-energy complete): the energy invested in gearing the exhaust is
  itself expended mass, and the gearing **cancels exactly** — momentum per unit total
  expended mass = v_ex, never more (G2b, machine precision).

**The theorem (pre-registered, now earned):** no closed ledger buys momentum cheaper than
c. The price floor of reaction is the relay speed; the photon rocket sits exactly on the
floor at exp(a·t/c) = 1.002834 per day for the Earth hover row, at a power price of
2.943 GW per hovering kilogram.

**The sweep (P3).** The 10^81.9 is not a law of nature — it is chemistry's position on the
v_ex axis. The whole 84-order span from 10^81.9 down to 1.0028 is bought with velocity of
output, not with more matter: ion 10^7.4, 1000 km/s ≈ 2.34, 0.1c ≈ 1.029, 0.9c ≈ 1.003,
floor 1.0028. Closed-ledger descent onto the floor is monotone (G3).

**The trade (P5).** For a fixed mission Δv the energy-optimal expulsion speed emerges at
0.6275·Δv from its own stationarity equation — not inserted.

## Scope / Limitations / Residuals

- Every numerical form coincides with special-relativistic rocket mechanics: **shared form,
  cannot discriminate.** The native content is the route (Law V purse arithmetic), the
  presence/volume-vs-resistance decomposition, and the floor read as relay economics.
- The open ledger prices propellant only; its "cheaper than the floor" rows at high v_ex
  are exactly the rows where the unpriced energy bill diverges — the two ledgers must never
  be quoted interchangeably.
- v_ex is an engineering variable throughout; nothing was fitted.

## Cascade

The floor theorem and the two-ledger split are the standing frame for any future RTM
propulsion claim: a proposal quoting a reaction price below exp(a·t/c) on a closed ledger
is excluded by arithmetic before any engineering is discussed.
