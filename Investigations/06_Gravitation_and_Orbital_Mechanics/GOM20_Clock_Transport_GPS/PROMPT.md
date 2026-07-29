# GOM20 — Clock Transport: the GPS Ledger

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B61). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

GPS satellite clocks run fast by +45.9 μs/day from orbital depth and slow by −7.2 μs/day
from orbital speed: net +38.7 μs/day, corrected by design in every receiver. The prevailing
account needs two separate theories for the two terms. Measured anchor: the engineered
correction itself, documented to fractions of a microsecond.

## SDT footing

One ledger carries both terms natively. The speed term is Law V budget spending (v² at
orbital velocity); the depth term is the seat's depth on the wake, z = ϟ/r read at the
satellite's altitude versus the ground station's (L17; the same depth expression confirmed
at the solar photosphere to 0.03%). Both terms come from one formula pair sharing one
koppa — no separate frameworks, no interface between them. Existing corpus: GOM05 (depth
closure), GOM12 (koppa invariance), the B28 depth-closure tally.

## Pre-registration skeleton (complete before any tool)

- Question: does the single ledger (budget spend + depth differential on Earth's ϟ)
  reproduce +45.9/−7.2/net +38.7 μs/day from Earth's measured v_surface and R alone?
- Rejection criterion (populated): net correction off by more than the documented
  engineering tolerance — the numbers are known to sub-μs precision; there is nowhere to
  hide.
- Anchors: GPS orbital radius/period; the documented corrections.
- Tolerance: ±0.1 μs/day on the net.

## Benchmark linkage

Catalogue row B61 · a clean tally candidate from bridge:: + law_V — one of the easiest
unclimbed rungs in the suite.
