# TD08 — Fluctuation–Dissipation and Brownian Motion

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Do Brownian motion, the Einstein relation `D=µk_BT`, and the
   fluctuation–dissipation theorem all follow from **one** relay statistic — the same disordered
   tick-to-tick throughput that *drags* a moving body also *kicks* a resting one — so that noise and
   friction are not two independent inputs but two faces of the relay bath, with their ratio fixed
   natively?
2. **Why does it matter?** — FDT is the deepest "two things are one" claim in transport. If SDT supplies
   both the kick variance and the drag mobility from a single occlusion-momentum-flux, it earns
   `D=µk_BT` with no separate noise normalisation — and closes the fluid suite (FD02 viscosity) against
   the thermal suite via Stokes–Einstein.
3. **How will we find out?** — Gated phases in §④; the Brownian walk and the drag response measured on
   the *same* relay bath, then the FDT spectrum and the FD02 closure.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers and real failure modes.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

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
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the FDT ratio (flag the relay correlation-time order-unity factor if needed)
- Engine namespaces actually used: measured::k_B, TD02 (k_BT scale), TD03 (occlusion kick),
    FD02 (ν / mobility — same relay momentum-flux)
- Phase thresholds (committed before run):
    P1 ⟨x²⟩=2Dt linear, VACF decays at relay correlation time · P2 D/(µk_BT)=1.00 ±2% at two temps
    P3 S_F(ω)=2k_BT·Re[1/µ(ω)] holds at low ω · P4 Stokes–Einstein D=k_BT/(6πηR) agrees <10% vs FD02
- Forbidden retroactive changes: normalise the noise to force D=µk_BT; widen tolerances; plug the FDT
    ratio; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 MSD not linear (`⟨x²⟩ ≁ 2Dt`) | check the per-tick kicks are uncorrelated; lengthen the run | **OPEN** anomalous diffusion | rescale to force linearity |
| P2 `D/(µk_BT) ≠ 1` beyond ±2% | confirm kick variance and drag use the **same** bath statistic | **F** — noise and drag are independent ⇒ FDT not one relay statistic | normalise the noise to hit 1 |
| P3 FDT spectrum off at low ω | check `µ(ω)` linear-response extraction | **OPEN** the spectrum | fit the prefactor to the FDT |
| P4 Stokes–Einstein off `> 10%` vs FD02 | reconcile FD02's `η` provenance; check `R` definition | **OPEN** the fluid↔thermal closure | retune `η` to close |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (FD02 `η` not ready) | **DEFER** P4; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (particle count, run length, frequency bins); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Normalising the noise to force `D=µk_BT` (the whole point is that the ratio is *fixed*, not fitted) ·
  post-hoc tolerance widening · plugging the FDT ratio · `atomic::`/GM/G in the native chain.

---

## Questions This Opens *(generative — log new ones in `TD08_VERDICT.md`)*

1. **Is `D=µk_BT` exact, or does the relay correlation time (`~t_P`-scaled) add a tiny native
   correction at short times?** Standard FDT assumes a delta-correlated bath; the lattice has a finite
   tick — is there a measurable sub-`t_P` departure?
2. **Are TD04's `α`, FD02's `ν`, and TD08's `D` literally one `⅓ v_relay λ_mfp` with three prefactors?**
   If so, heat, momentum, and mass diffusion are a single relay random-walk — a strong cross-suite
   consistency test.
3. **Does relay shot-noise set a fundamental measurement noise floor?** If every immersed body is kicked
   by the bath, is there a native thermal-noise limit (Johnson–Nyquist analogue) derivable from the same
   statistic, without borrowing circuit theory?

---

*TD08 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
