# RTM01 — Verdict (dual)

> **Author:** J. C. Harvey, Melbourne. Direct run 2026-08-03, main session, no agents.
> Tool: `rtm01_thrust_ledger.cpp` (VS2022 cl `/std:c++20 /O2 /W4`, zero warnings,
> BUILD_EXIT=0 after one MSVC range-for fix, RUN_EXIT=0). Output: `rtm01_results.txt`.
> Pre-registration: `PROMPT.md` before the tool. Consumes GOM23's validated instruments.

## Prompt completion: **A** — all four phases executed, 3/3 gates PASS, 0 FAIL.

## Physics class: **NATIVE (the ledger formalism + the pricing) · SHARED-FORM (first-order values) · SPEC (E110)**

**The determination.** The forced state has a price list, and it is three lines long:

```
hover      a(r)    = c²ϟ/r²          the reaction to stand still
passage    Δv⊥     = 2c²ϟ/(bv)       the reaction to pass straight
toll       dz/dl   = ϟ/r²            the per-metre bill of the line
```

all in {ϟ, c, r, b, v} — zero π, zero G, zero kilogram. The Sun hover row closes on the
engine's own surface figure at 0.028% (274.278 vs 274.2 m/s²). The budget identity
v²/c² = ϟ/r holds exactly at the surface rung, with the bookkeeping stated: on a forced
path the travel purse is paid by reaction, tick by tick — the field's line is free, the
straight line costs.

**The pricing (P3).** Hovering at Earth's surface on chemical exhaust costs a mass ratio of
10^81.9 per day — the astronomical number is the finding, stated plainly: the curve is free,
the line is not. The straight-pass bill runs from 6.3 km/s (Earth, b = 2R) down to
125 m/s (b = 100R), and 59 km/s for a 30 km/s straight line past the Sun at 1 AU.

**The decomposition (P4 → E110).** A slow powered line pays only the geometric 2 of the
deflection; light pays profile-2 × geometry-2 = 4. The ratio law
θ_slow/θ_light = c²/2v² verified to machine precision across 10–300 km/s. Filed as
**E110** — the census's two 2s, one instrument per factor.

## Scope / Limitations / Residuals

- First-order, every number here is shared form (a PPN bookkeeping produces the same split);
  the earned content is the ledger formalism, the π-free pricing, and the decomposition made
  operational. No discrimination is claimed.
- v_ex = 4.5 km/s is a stated engineering parameter, not a fitted quantity.
- The hover ledger assumes constant a over the burn (exact at fixed r; the ascent case is
  GOM23 P3's instrument).

## Cascade

Findings inform the next RTM investigation. Live candidates surfaced by this run: the
reaction-side reading of Law IV along accelerated (non-radial) lines; the powered-spiral
ledger (the path between the free curve and the paid line); and the E110 mission envelope.
