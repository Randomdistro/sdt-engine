# RTM01 — The Thrust Ledger and Straight-Line Pricing

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-08-03. **Status:** pre-registered
> before instrumentation.
> **Domain:** 17 Reactions & Thrust Mechanics (RTM) — new domain, first investigation.
> **Consumes:** GOM23's validated instruments and closure table (run GOM23 first).

## 0. The question, stated exactly

For every action, an equal and opposite response. This domain treats **the forced state**:
motion held against the field's line by reaction. RTM01 asks three things at once —

- **(A) Formalism:** what does koppa charge for straightness? Derive the thrust-ledger laws
  for linear motion through a depth gradient from Law IV (the field's resistance to a change
  of vector) and the depth field z = ϟ/r, in movement-budget terms.
- **(B) Pricing:** what does the ledger cost in propellant — the price of hovering, the price
  of a straight pass, the price per metre of refusing the curve?
- **(C) The decomposition experiment:** a slow powered straight line pays only the geometric
  2 of the deflection integral; light pays the full 4 = profile-2 × geometry-2. Specify the
  experiment that splits the census's two 2s observationally (filed as E110).

## 1. Permitted inputs

`bridge::koppa_Earth`, `bridge::koppa_Sun`, `bridge::g_surface` (cross-check), c, radii,
exhaust-velocity v_ex as an engineering parameter (stated, not fitted). No G, no M, no
kilogram. The material:space reading (ϟ/r = movement-through-material : movement-through-
space, Harvey 2026-08-02) is the organising frame: the ledger prices the toll per pass.

## 2. Phases and pre-registered gates

- **P1 — ledger laws.** Hover price a(r) = c²ϟ/r²; straight-pass lateral bill
  Δv⊥ = 2c²ϟ/(bv); per-metre toll dz/dl along a straight chord. Gate: the hover row at the
  solar photosphere must reproduce `bridge::g_surface`-class 274.2 m/s² (cross-check, < 0.1%),
  and every law must be expressible in {ϟ, c, r} with zero π (GOM23 P1 discipline carried).
- **P2 — budget bookkeeping along powered paths.** The toll table z(r) along a powered
  ascent; the identity v²/c² = ϟ/r verified at every bound rung the path crosses; statement
  of which purse pays on a forced path (travel bought by reaction, not by circulation).
- **P3 — propulsion pricing.** The Tsiolkovsky hover ledger: mass ratio per unit time
  exp(a·t/v_ex) — print the Earth-surface price per day at v_ex = 4.5 km/s and state it
  plainly (the number is astronomical; that is the point — the curve is cheap, the line is
  not). Straight-pass Δv tables for Earth and Sun rows across b and v, whole-range.
- **P4 — the decomposition (E110 spec).** Pre-register the ratio law
  θ_slow/θ_light = c²/2v²; tabulate across v = 10, 30, 100, 300 km/s; write the E110
  experiment stub: SDT prediction, standard prediction, the observable, the apparatus class.
  State plainly: first-order shared form (a GR bookkeeping produces the same split via PPN);
  the earned content is the decomposition made *operational* — one instrument per factor.

## 3. Falsification table

| ID | Condition that fails this investigation |
|----|------------------------------------------|
| F1 | hover cross-check vs `bridge::g_surface` beyond 0.1% |
| F2 | budget identity broken at any rung along a powered path |
| F3 | any ledger law requiring a π or an input outside §1 |
| F4 | decomposition ratio deviating from c²/2v² in the slow limit |

## 4. Deliverables

`rtm01_thrust_ledger.cpp` (VS2022 cl, `#include <sdt/laws.hpp>`), `rtm01_results.txt`,
`RTM01_VERDICT.md`, `Experiments/E110_*.md` (the decomposition spec), domain `README.md`.
Findings inform the next RTM investigation.
