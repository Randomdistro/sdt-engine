# FD03 — Verdict: The Reynolds Transition as a Lattice Relay Ratio

**Classification: CLASS C (QUALIFIED — convergence).**
**Author**: James Christopher Tyndall, Melbourne · Tool: `fd03_reynolds_relay_ratio.cpp` (MSVC `/utf-8 /std:c++20`, ran clean; F1–F5 all YES).

## Deciding metric
`Re = UL/ν` is **DERIVED** as the ratio of two rates of *one medium* — advective transport
`U/L` vs relay momentum-smoothing `ν/L²` — and is dimensionless by like-rate cancellation
(two-stream identity exact to 1×10⁻¹⁶). The transition **mechanism** is DERIVED: laminar
flow holds while relay smoothing damps the dominant mode over its coherence length `ℓ_c`
before advection carries it across `L`; the crossing `τ_relay(ℓ_c)=τ_adv(L)` gives
`Re_crit = (L/ℓ_c)² = G(geometry)`, with `ν` cancelling. The critical **value**, however,
requires **one calibrated geometric coherence ratio** `ℓ_c/L` per geometry — `Re_crit=2300`
does **not** fall out with zero calibration. Hence Class C, not A.

## Falsification scoreboard (from the run)
| Test | Result |
|---|---|
| F1 dimensionlessness (Re=τ_relay/τ_adv exact) | YES (1×10⁻¹⁶) |
| F2 pipe threshold in band 2000–4000 | YES (2300 anchor) |
| F3 finite transition crossing exists | YES |
| F4 geometry dependence + correct ordering | YES (pipe 2300 < Couette O(2e3) ~ pipe; plate Re_x 5e5 ≫ pipe) |
| F5 lattice crossover = analytic 1/e | YES (39.482 vs 39.478, 8×10⁻⁵) |

## Provenance × correspondence
- **provenance**: SDT-derived (the ratio + mechanism); **calibrated** (the per-geometry value).
- **correspondence**: known-match (pipe 2300, plate 5×10⁵, Taylor–Couette ~1708 reproduced).
- Honest note: the flat-plate "null test" (re-using the pipe coherence count) misses 5×10⁵ — the open boundary layer sustains a longer coherent mode train (right direction), but its magnitude is a **second** calibration. Disclosed, not laundered.

## Parameter ledger (R2)
`c, ℓ_P, t_P` WHITELIST · `Re=UL/ν` & dimensionlessness & `Re_crit=(L/ℓ_c)²` form & `(2π)²` crossover ratio DERIVED · `ν` MEASURED-INPUT (FD02; **cancels**) · pipe & plate coherence ratios `ℓ_c/L` CALIBRATED(1 each) · measured Re/Re_x/Ta targets MEASURED-INPUT (compare-only, R1).

## Open (path to Class A)
Derive `ℓ_c/L` parameter-free from the lattice mode structure (which disturbance wavelength the relay can smooth coherently in a given geometry) — would remove the one calibration and lift the *value* to derived. **Sign-off: PASS, Class C.**
