# TD08 — Fluctuation–Dissipation and Brownian Motion

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Brownian motion, the Einstein relation `D = µk_BT`, and the fluctuation–dissipation theorem (FDT) tie
random jiggling to systematic drag — but in standard theory the noise and the friction are introduced
as separate inputs. The gap: derive both from **one relay statistic** — the same disordered tick-to-tick
throughput that drags a body also kicks it, so fluctuation and dissipation are the two faces of the
relay bath, not two assumptions.

## SDT mechanism & hypotheses

An immersed body is a hard vortex bombarded each tick by disordered relay throughput (heat, [[TD01]]).
The *mean* one-sided imbalance of that bombardment when the body moves is drag (an FD02/FD09 occlusion
momentum-flux); the *fluctuating* part when it is at rest is the random kick — they are the **same**
relay shot-noise, so their ratio is fixed.

- **H1 (Brownian = relay shot-noise):** uncorrelated per-tick throughput kicks give a random walk with
  `⟨x²⟩ = 2Dt`; `D` is set by the kick variance and the relay correlation time `~t_P`-scaled.
- **H2 (Einstein relation):** because the *same* relay momentum-flux supplies both the kick variance
  and the mobility `µ` (drag), their ratio collapses to `D = µk_BT` — FDT is the statement that one
  relay statistic governs both, derived not imposed.
- **H3 (cross-check with FD02):** the drag mobility uses FD02's `ν`, so `D = k_BT/(6πηR)` (Stokes–
  Einstein) must come out *consistently* with the independently-derived viscosity — a closure test
  spanning the fluid and thermal suites.

## Strategy

1. **Brownian walk.** *Goal:* `⟨x²⟩=2Dt`. *Method:* simulate a tagged vortex kicked by a relay bath at
   `T` (kicks from TD03's occlusion momentum-flux). *Success:* linear MSD, `D` extracted; velocity
   autocorrelation decays on the relay correlation time.
2. **Einstein relation.** *Goal:* `D=µk_BT`. *Method:* measure `D` (free diffusion) and `µ` (response
   to a steady force) on the *same* bath. *Success:* `D/(µk_BT)=1.00 ± 2%` across two temperatures —
   noise and drag share one statistic.
3. **FDT spectrum.** *Goal:* the full theorem. *Method:* compare the force-noise power spectrum to the
   dissipative response. *Success:* `S_F(ω) = 2k_BT · Re[1/µ(ω)]` (the FDT) holds at low ω; white at
   low frequency, rolling off at the relay tick.
4. **Stokes–Einstein closure.** *Goal:* tie to FD02. *Method:* feed FD02's `η` into `D=k_BT/(6πηR)`,
   compare to Phase-1 `D`. *Success:* agreement within the combined ~10% budget — one medium, two suites.

## Success criteria

- **PASS (Class A):** `⟨x²⟩=2Dt`, `D=µk_BT`, and the FDT all from one relay shot-noise statistic, only
  `k_B` whitelisted; Stokes–Einstein closes with FD02 to <10%.
- **QUALIFIED (Class C):** Einstein relation + FDT native; the relay correlation time carries one
  flagged order-unity factor. *(Expected.)*
- **PENDING (Class D):** Brownian walk reproduced but FDT ratio needs a calibrated noise normalisation.
- **FAIL (Class F):** noise and drag require independent inputs — FDT not a single relay statistic.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | Brownian = relay shot-noise | `⟨x²⟩=2Dt` linear, VACF decays at `t_P`-scale | jiggling not from tick noise |
| T2 | one statistic → Einstein | `D/(µk_BT)=1±2%`, two temps | noise & drag are independent |
| T3 | FD02 closure | Stokes–Einstein `D=k_BT/6πηR` agrees <10% | fluid and thermal suites inconsistent |

## Dependencies

**Upstream:** [[TD02]] (`k_BT` scale), FD02 (`ν`, mobility — same relay momentum-flux), [[TD03]]
(occlusion kick). **Downstream:** colloid/diffusion modelling, noise floors in measurement, TD04
(`D` and thermal diffusivity `α` are the same random-walk). **Related:** [[TD01]] (the bath is
disordered throughput), FD09 (drag as occlusion cross-section — the dissipative half of this statistic).
