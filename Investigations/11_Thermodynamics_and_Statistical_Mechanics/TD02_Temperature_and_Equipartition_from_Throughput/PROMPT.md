# TD02 — Temperature and Equipartition from Throughput

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Does temperature have a *native* lattice meaning — `k_BT ≡ ⟨ε_dis⟩` per
   spation degree of freedom, the mean disordered relay throughput — that **coincides** with the
   entropic `1/T = ∂S/∂E` of TD01's `S=k_B ln W`; and does the exponential occupation `exp(−ε/k_BT)`
   fall out of **native relay counting** (a most-probable distribution of throughput quanta over cells),
   or can it only be obtained by importing the canonical-ensemble / partition-function machinery the
   suite README forbids as an input?
2. **Why does it matter?** — TD02 is the keystone of the whole suite: TD03 (ideal gas), TD07 (Landauer
   `k_BT ln2`), TD08 (Einstein `D=µk_BT`) all consume `k_BT` and, downstream, the occupation factor. If
   the Boltzmann factor is **imported**, that contamination propagates into TD03's "no ensemble" claim
   and TD06's "derived occupation" claim — so this prompt must firewall it here, once.
3. **How will we find out?** — Four gated phases (§Strategy). The **two-definition concordance** (P1)
   and the **most-probable-distribution counting** (P3) run on the TD01 toy lattice with `k_B` as the
   only whitelisted input; P3's native route (Lagrange-multiplier maximisation of `ln W` at fixed total
   throughput) must produce `exp(−ε/k_BT)` *without* writing down a canonical reservoir.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers and real failure modes,
   including the **anti-tautology** firewall (F3/F4): if the exponential can only be reached via the
   microcanonical→canonical reservoir argument, the derivation is IMPORTED and the grade is capped at C.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

TD01 made entropy a literal microstate count; what *is* temperature on the lattice, and why does
each quadratic degree of freedom get exactly `½k_BT`? The gap: derive `T` and equipartition from
relay throughput sharing alone, **without imposing a Boltzmann distribution, a partition function, or
the canonical-ensemble (microcanonical→canonical reservoir) construction** — those are the README's
forbidden inputs, and writing the Boltzmann factor down via a reservoir *is* importing the answer.

## SDT mechanism & hypotheses

Heat is disordered convergence throughput. A hot region carries more random tick-to-tick throughput
per spation than a cold one. Temperature is therefore not a primitive — it is the **mean disordered
relay throughput per spation degree of freedom**, and `k_B` is the measured unit-bridge that converts
throughput (in SDT energy units) to kelvin, exactly as `e` bridges handed redirection to coulombs.

- **H1 (T = throughput/DoF):** `k_BT ≡ ⟨ε_dis⟩` per spation DoF; the thermodynamic `1/T = ∂S/∂E`
  (TD01's `S=k_B ln W`) returns the *same* `T`, proving the two definitions coincide.
- **H2 (equipartition from even sharing):** because the relay redistributes throughput to contact
  neighbours with no preferred channel, at the spread maximum every quadratic DoF holds `½k_BT` —
  equipartition is the stationary point of TD01's mixing, not a separate postulate.
- **H3 (Boltzmann factor from native counting — the load-bearing claim, DERIVE do not import):** the
  most-probable way to distribute a fixed pool of throughput quanta over many equivalent relay cells
  (maximise `ln W` at fixed total throughput, TD01's combinatorics) yields a single-cell occupation
  `∝ exp(−ε/k_BT)` with `1/k_BT` the Lagrange multiplier enforcing the throughput budget. **This must
  be obtained from the lattice's own state-count, NOT by writing down a canonical reservoir** — the
  microcanonical→canonical "system + bath" derivation is the textbook ensemble the README forbids and
  is precisely the answer being smuggled in. (See the ANTI-TAUTOLOGY firewall in §Strategy.)

## ANTI-TAUTOLOGY firewall (the one test that can fail)

There are two ways to "get" `exp(−ε/k_BT)`. They are not equal:

- **NATIVE (earns A):** start from TD01's literal `W(E,N)` for the toy lattice, find the occupation
  that maximises `ln W` at fixed total throughput (Lagrange multiplier `β`), and *measure* `β=1/k_BT`
  against the P1 concordance temperature. The exponential is an **output** of relay counting.
- **IMPORTED (capped at C):** assume a "tagged DoF + large reservoir at temperature `T`" and expand the
  reservoir entropy `S_res(E−ε) ≈ S_res(E) − ε/T` to read off `exp(−ε/k_BT)`. This **is** the canonical
  ensemble; it presupposes a pre-defined `T` and a Boltzmann-distributed bath. **Using it caps the grade
  at C and the result is labelled IMPORTED**, no matter how good the fit.

The firewall: P3 must not instantiate a reservoir whose states are already Boltzmann-weighted. The
occupation must come from counting equivalent cells, not from `S_res(E−ε)`. If the native route cannot
produce the exponential, say so and grade C — do not reach for the reservoir and call it derived. This
contamination is the exact thing TD03 ("no ensemble appears") and TD06 ("derived, not postulated")
inherit; closing it here protects both.

## Strategy

1. **Two-definition concordance.** *Goal:* show kinetic and entropic `T` agree. *Method:* on the
   TD01 toy lattice compute `T_kin = ⟨ε_dis⟩/(½k_B)` per DoF and `T_ent = (∂S/∂E)⁻¹`. *Success:*
   `|T_kin − T_ent|/T < 10⁻³` across the energy range. *(This is native — it uses only TD01 counting.)*
2. **Equipartition.** *Goal:* `½k_BT` per quadratic DoF. *Method:* seed lattice blocks with unequal
   DoF energies, relax per-tick, measure stationary per-DoF energy. *Success:* `⟨E_i⟩ = ½k_BT ± 1%`
   for every DoF independent of initial split. *(Equipartition is the stationary point of TD01 mixing,
   not a separate postulate.)*
3. **Boltzmann factor from native counting *(the firewalled core)*.** *Goal:* derive `exp(−ε/k_BT)`.
   *Method:* maximise `ln W` for the TD01 toy lattice at fixed total throughput (Lagrange `β`); read the
   single-cell occupation; compare `β` to P1's `1/k_BT`. **Forbidden:** the system+reservoir
   `S_res(E−ε)` expansion (that is the imported ensemble — see firewall). *Success (A):* native
   most-probable occupation `∝ exp(−βε)` with `β=1/k_BT` matching P1 to `R²>0.999`; `c_v=3/2 k_B`
   recovered. *If only the reservoir route works:* label **IMPORTED**, grade **C**, do not claim A.
4. **Temperature scale audit.** *Goal:* confirm `k_B` is the *only* whitelisted input. *Method:*
   delete-test — recompute with `k_B` symbolic. *Success:* every result is `k_B × (pure number)`; no
   `h`, no partition function `Z`, no ensemble object anywhere in the native chain.

## Success criteria

- **PASS (Class A):** `T_kin=T_ent` (P1), `½k_BT` per DoF (P2), **and** the Boltzmann factor obtained
  from native `ln W` maximisation (P3) with `β=1/k_BT` matching P1 — all with only `k_B` whitelisted,
  zero fitted parameters, **and no reservoir `S_res(E−ε)` expansion anywhere**.
- **QUALIFIED (Class C):** P1 + P2 native, but the `exp(−ε/k_BT)` reached only via the
  microcanonical→canonical reservoir argument → the factor is **IMPORTED** (firewall fired); or one
  flagged ergodicity/coarse-graining step. *(Honest expected landing if the native counting stalls.)*
- **PENDING (Class D):** equipartition holds numerically but the Boltzmann-factor route is unexecuted.
- **FAIL (Class F):** `T` cannot be defined without importing an ensemble or partition function — i.e.
  P1 concordance itself fails (`T_kin ≠ T_ent`), so there is no native temperature to anchor `β`.

## Falsification tests (each has a real failure mode + numeric trigger)

| # | Test | SDT prediction | If it fails (numeric trigger) |
|---|------|----------------|-------------------------------|
| T1 | Two-definition concordance | abs(`T_kin − T_ent`)/T `< 10⁻³` across the energy range | if `> 10⁻³`, temperature has no single throughput basis → **F** (no anchor for `β`) |
| T2 | Even sharing → equipartition | `⟨E_i⟩ = ½k_BT ± 1%`, init-independent, every DoF | if any DoF deviates `> 1%` or depends on the initial split, a channel is privileged; sharing is not even |
| T3 | **Boltzmann from native counting** | `ln W` maximisation gives `∝ exp(−βε)`, `β=1/k_BT` to `R²>0.999` | if the native most-probable distribution is **not** exponential (residual `R²<0.999`), the relay does not generate MB → **F** |
| T4 | **Anti-tautology firewall** | the exponential is reached **without** the reservoir `S_res(E−ε)` expansion | if the only route to `exp(−ε/k_BT)` is the canonical-reservoir construction, the factor is **IMPORTED** → grade **capped at C**, never A |

## Dependencies

**Upstream:** [[TD01]] (`S=k_B ln W`, relay mixing, the literal `W(E,N)` counting P3 maximises),
Law I (`ε`, throughput), FLM02/FLM05 (relay ticks). **Downstream:** TD03 (ideal gas needs `T` **and
inherits the firewall** on "no ensemble"), TD06 (occupation factor — inherits the firewall on "derived,
not postulated"), TD07 (Landauer needs `k_BT`), TD08 (Einstein `D=µk_BT`).
**Related:** SAR02 (Stellar suite, lattice mode counting), FD02 (`v_relay`, `λ_mfp` reused in TD04/TD08).
---

## Questions This Opens *(generative — log new ones in `TD02_VERDICT.md`)*

These are not required for the verdict; they are the payoff of doing it well.

1. **Is `β` the Lagrange multiplier *literally* a relay-budget shadow price?** If `1/k_BT` is the cost
   of one extra throughput quantum, does a `∇T` then read as a `∇β` — a spatial gradient in that shadow
   price — connecting TD02's `β` to TD04's Fourier current and TD08's drift?
2. **Does the lattice's tetrahedral frustration (FLM08) perturb equipartition?** Continuum isotropy gives
   exactly `½k_BT` per DoF; the frustrated CRN might over- or under-share by a small residual. Is there
   a measurable departure from equipartition at the spation scale (a heat-capacity fingerprint)?
3. **Where does quantum freeze-out come from with no `ℏ`-oscillator?** Real `c_v` drops below `3/2 k_B`
   as DoFs "freeze" at low `T`. If the relay has a minimum throughput quantum `ε`, does discreteness
   alone reproduce the Einstein/Debye freeze-out — i.e. is the freeze-out *the lattice gap*, not QM?
4. **Is `T_kin = T_ent` ever broken on purpose?** In a steady relay current (driven, not equilibrium)
   the two definitions can separate — is that separation the native definition of a non-equilibrium
   temperature, and does it match the effective temperatures used in glasses (FLM09 aging)?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (k_B is the only whitelisted input; list any flagged step)
- Engine namespaces actually used: measured::k_B, law_I::epsilon, TD01 microstate counting W(E,N)
- Phase thresholds (committed before run):
    P1 |T_kin−T_ent|/T < 1e-3 · P2 per-DoF ½k_BT ±1%, init-independent
    P3 native exp(−βε), β=1/k_BT, R²>0.999 (NOT via reservoir) · P4 every result = k_B × pure number
- Forbidden retroactive changes: reach for the canonical-reservoir S_res(E−ε) expansion and grade A;
    import a partition function Z; widen tolerances; plug β; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 concordance gap `> 1e-3` | check the per-DoF energy bookkeeping; refine the `∂S/∂E` estimate | **F** — no native temperature anchor | widen the 1e-3 gate |
| P3 native `ln W` max does not give an exponential (`R²<0.999`) | try a finer/larger toy lattice; check the throughput-budget constraint | **OPEN** the relay→MB question; grade D | reach for the reservoir and call it derived |
| P3 native route stalls, reservoir route works | label the Boltzmann factor **IMPORTED**; grade **C** honestly | — | claim A while using `S_res(E−ε)` |
| P2 a DoF deviates `> 1%` or depends on init | check the mixer for a privileged channel (FLM02 GPI) | **OPEN** an anisotropy fingerprint | average the deviation away |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (TD01 toy lattice not ready) | **DEFER**; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (lattice size, tick count, energy mesh); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes (e.g. direct enumeration for small N,E vs Lagrange maximisation) — both must avoid the reservoir.

### Disallowed adjustments

- Using the microcanonical→canonical reservoir to produce `exp(−ε/k_BT)` and grading A · importing a
  partition function `Z` or any pre-Boltzmann-weighted bath · post-hoc tolerance widening · coefficient
  plugs · `atomic::`/GM/G in the native chain · burying the firewall outcome (T4).

---

*TD02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
