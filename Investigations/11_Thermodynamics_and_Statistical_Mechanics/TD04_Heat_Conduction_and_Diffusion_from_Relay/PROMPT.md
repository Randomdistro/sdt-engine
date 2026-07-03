# TD04 — Heat Conduction and Diffusion from Relay

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Is the thermal conductivity `k` a *derived* relay random-walk coefficient
   `k = ⅓ c_v v_relay λ_mfp` (with the `1/3` from lattice isotropy and `v_relay ∝ √T` from B16), so that
   Fourier's law and the diffusion equation fall out of throughput diffusion — or must `k` and `λ_mfp` be
   borrowed un-derived from kinetic theory?
2. **Why does it matter?** — TD04 is the thermal twin of FD02's viscosity: if conduction is the *same*
   `λ_mfp v_relay` machinery applied to energy, then heat transport, momentum transport (FD02), and mass
   diffusion (TD08) are one relay statistic. It also tests Wiedemann–Franz natively. Downstream: TD05,
   TD06, TD08.
3. **How will we find out?** — Gated phases in §④; native relay random-walk before any borrowed `λ_mfp`.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers and real failure modes.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## Question

Fourier's law `q = −k∇T` and the diffusion equation describe heat spreading down a gradient, but
classically `k` is a measured material property. The gap: derive conduction as **throughput diffusion**
on the relay lattice and obtain `k` from a relay mean-free-path — the direct thermal analogue of
FD02's kinematic viscosity.

## SDT mechanism & hypotheses

Heat is disordered convergence throughput; a temperature gradient is a throughput-density gradient.
Each relay tick a spation hands a share of its disordered throughput to contact neighbours, so a
gradient relaxes by a random-walk of throughput — the same `λ_mfp v_relay` machinery FD02 used for
momentum, applied now to energy.

- **H1 (Fourier from diffusion):** the per-tick neighbour exchange of disordered throughput gives a
  net current `q = −k∇T` with `k = ⅓ c_v v_relay λ_mfp`; the `1/3` is lattice isotropy (as in TD03).
- **H2 (diffusion equation):** continuity of throughput + H1 yields `∂T/∂t = α∇²T`, `α = k/(ρc_v) =
  ⅓ v_relay λ_mfp` — the thermal diffusivity is a pure relay random-walk coefficient.
- **H3 (temperature scaling & Wiedemann–Franz):** `v_relay ∝ √T` (B16, as in FD02) gives `k ∝ √T` for
  a gas; in a metal the *same* mobile relay channel carries charge and heat, so `k/(σT)` collapses to a
  universal Lorenz number `L` — derived as one transport statistic, not two.

## Strategy

1. **Fourier coefficient.** *Goal:* `k = ⅓ c_v v_relay λ_mfp`. *Method:* impose a fixed `∇T` on a
   relay slab, run per-tick throughput exchange, measure steady current `q`. *Success:* `q = −k∇T`
   linear; fitted `k` matches `⅓ c_v v_relay λ_mfp` to <2%.
2. **Diffusion equation.** *Goal:* `∂T/∂t=α∇²T`. *Method:* release a hot stripe, track the profile.
   *Success:* Gaussian spread, variance grows `∝ t` with `α = ⅓ v_relay λ_mfp` (no free knob).
3. **Material check.** *Goal:* real `k` to order-of-magnitude. *Method:* plug measured `c_v`, sound
   speed (`v_relay` proxy), and a kinetic `λ_mfp` for air and a metal. *Success:* `k_air`, `k_Cu`
   within a factor of ~2; `k ∝ √T` slope confirmed for the gas.
4. **Wiedemann–Franz.** *Goal:* universal Lorenz number. *Method:* let the same relay channel carry
   both heat and charge; compute `k/(σT)`. *Success:* `L` constant across two metals to ~10%
   (prefactor flagged if it needs a calibrated channel-count).

## Success criteria

- **PASS (Class A):** Fourier + diffusion equation derived with `k=⅓c_v v_relay λ_mfp` native, `1/3`
  from isotropy, only `k_B` and measured material inputs used; `k∝√T` exact.
- **QUALIFIED (Class C):** mechanism + scaling native; absolute `k` within ~2× and Lorenz prefactor
  flagged. *(Expected.)*
- **PENDING (Class D):** diffusion works but `λ_mfp` must be borrowed from kinetic theory un-derived.
- **FAIL (Class F):** conduction needs a phonon/field model SDT forbids.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | conduction = throughput diffusion | `q=−k∇T`, `k=⅓c_v v_relay λ_mfp` ±2% | Fourier not a relay random-walk |
| T2 | `v_relay∝√T` (B16) | gas `k∝√T` slope 0.5 | thermal transport has another T-law |
| T3 | one channel carries heat+charge | Lorenz `k/(σT)=L` const ±10% | Wiedemann–Franz needs two mechanisms |

## Dependencies

**Upstream:** [[TD01]] (`T` as throughput, mixing), FD02 (`ν=⅓λ_mfp v_relay`, `ν∝√T` from B16 — same
machinery for energy). **Downstream:** TD05 (latent heat halts conduction at a front), TD06 (radiative
vs conductive transport), TD08 (`D` and `α` are the same random-walk). **Related:** [[TD02]]
(`c_v=3/2 k_B`), [[TD03]] (the `1/3` isotropy factor).
---

## Questions This Opens *(generative — log new ones in `TD04_VERDICT.md`)*

1. **Is the Lorenz number `L` exactly `π²/3·(k_B/e)²`, and is the `e` here the unit-bridge, not a
   charge substance?** If one relay channel carries heat and handed redirection together, `L` should be
   pure geometry — can TD04 derive it without a borrowed channel-count?
2. **Does a finite relay tick set a second-sound / ballistic regime?** At scales below `λ_mfp`, Fourier
   should break into a wave-like heat pulse. Is that the native prediction, and does it match observed
   second sound?
3. **Is thermal diffusivity `α` literally TD08's mass diffusivity `D` up to a `c_v` factor?** If both are
   `⅓ v_relay λ_mfp`, heat, momentum (FD02), and mass diffusion are one number with three prefactors.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (flag the Lorenz/Wiedemann–Franz channel-count if it needs one)
- Engine namespaces actually used: measured::k_B, B16 (v_relay∝√T), FD02 (ν=⅓λ_mfp v_relay machinery)
- Phase thresholds (committed before run):
    P1 fitted k vs ⅓c_v v_relay λ_mfp within 2% · P2 variance ∝ t, α=⅓v_relay λ_mfp (no free knob)
    P3 k_air,k_Cu within 2×, gas k∝√T slope 0.5 · P4 Lorenz k/(σT)=L const within 10% (prefactor flagged)
- Forbidden retroactive changes: borrow λ_mfp un-derived then claim native; import a phonon/field model;
    widen tolerances; plug k; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 fitted `k` off `⅓c_v v_relay λ_mfp` by `> 2%` | refine the per-tick exchange / `1/3` axis-average | **OPEN** the coefficient | hand-tune `k` to the slab current |
| P2 variance not `∝ t` (sub/super-diffusive) | check the relay update is an unbiased random walk | **OPEN** the anomalous-transport regime | rescale time to force `∝ t` |
| P3 `k∝√T` slope ≠ 0.5 | confirm `v_relay∝√T` (B16) is the only T-dependence | **OPEN** a second T-law | swap in a fitted exponent |
| P4 `λ_mfp` must be borrowed un-derived | label that step **PENDING/borrowed**; grade D on the Lorenz claim | — | call a borrowed `λ_mfp` native |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (FD02 `ν` not ready) | **DEFER** the closure phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (slab size, tick count, profile bins); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Borrowing `λ_mfp` from kinetic theory un-derived and grading native · importing a phonon/field
  conduction model SDT forbids · post-hoc tolerance widening · coefficient plugs on `k`/`L` ·
  `atomic::`/GM/G in the native chain.

---

*TD04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
