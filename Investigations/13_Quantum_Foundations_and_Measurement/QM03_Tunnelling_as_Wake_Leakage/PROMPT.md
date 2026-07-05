# QM03 — Tunnelling as Wake Leakage

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Quantum Foundations & Measurement (deterministic relay mechanics, no ψ).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can barrier penetration be reproduced as a **real relay-pressure field
   leaking through an occlusion wall** — the wake decaying but not vanishing inside the barrier, then
   re-seeding a vortex landing on the far side — so that `T ≈ e^{−2κd}`, the STM current, and the
   Geiger–Nuttall α-decay line all follow, **with the decay constant κ derived from native lattice
   occlusion-screening, not borrowed as the WKB/Schrödinger evanescent constant `√(2m(V−E))/ℏ`**? The
   firewall (§⑤): matching the WKB κ to <1% is *not* a derivation — `√(2m(V−E))/ℏ` **is** the
   Schrödinger evanescent form, so reproducing it that way recovers an imported QM result with no
   independent failure mode. Native means the screening length must fall out of the relay attenuation
   mechanics first, and only *then* be compared to the WKB value.
2. **Why does it matter?** — Tunnelling is the standard QM showcase of "the particle isn't really
   there". If SDT can make it a deterministic local leakage of a pressure field, the §8.2 census loses
   another debt; if it can only match by importing the WKB κ, that must be labelled and capped at C.
   Downstream: QM06 resonant/quasi-bound states, and the ATOMICUS α-core decay grammar.
3. **How will we find out?** — Four gated phases (§④). Phase 1 derives the decay length from
   raised-occlusion relay mechanics (PPT05) tick-by-tick **before** the WKB form is written; the WKB κ
   is a *comparison target*, never the source (§⑤ gate).
4. **What would prove us wrong?** — §⑧, three falsifiers with numeric kill triggers — including the
   firewall test: if the only route to κ is to write `√(2m(V−E))/ℏ` into the code, the mechanism is
   IMPORTED (→ C), not native.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

How does a hard solid vortex cross a barrier it classically cannot surmount? In SDT there is no
probability cloud that "is sometimes on the far side." There is a vortex and its **convergence
wake**. Can barrier penetration be reproduced as the **wake leaking through an occlusion barrier** —
the wake amplitude decaying but not vanishing inside the wall — with the vortex following the
surviving wake branch when leakage delivers enough convergence to cross? Reproduce the Gamow
exponential for α-decay and the STM tunnelling current `I ∝ e^{−2κd}`.

## SDT mechanism & hypotheses

A barrier is a region of raised occlusion (PPT05 confinement) that the vortex cannot push through
mechanically. But the wake is a relay-pressure disturbance, and a relay pressure cannot be set
exactly to zero across a finite wall — it decays as `e^{−κ x}` with a lattice decay length set by
the occlusion depth. Where the leaked wake re-emerges on the far side with residual amplitude, it
can re-seed a vortex landing there (the QM01 steering rule). Tunnelling is therefore **deterministic
leakage of a real pressure field**, local and mechanical, not a magical jump.

- **H1 (evanescent relay — FIREWALLED):** inside the barrier the wake amplitude decays exponentially
  with a screening length `ℓ_screen` set by the **occlusion depth of the raised-pressure slab**
  (PPT05), derived from relay attenuation mechanics. **Do NOT obtain κ by writing the WKB form
  `√(2m(V−E))/ℏ`** — that *is* the Schrödinger evanescent constant; reproducing it that way is an
  IMPORT with no independent failure mode and caps the grade at C (§⑤). The native claim is
  `κ_native = 1/ℓ_screen(occlusion depth)`; the WKB `√(2m(V−E))/ℏ` is a **comparison target** only.
  If `κ_native` matches WKB to <1% *after* an independent derivation, that is a genuine convergence;
  if the WKB expression is the only way to produce κ, label IMPORTED.
- **H2 (transmission = leaked fraction):** T ≈ e^{−2κd}; the `−2` is amplitude→intensity (QM04 square).
- **H3 (Gamow α-decay):** the α-cluster vortex (ATOMICUS core) leaks the Coulomb-occlusion barrier;
  log(half-life) vs `Z/√E` linear (Geiger–Nuttall) from the leaked-fraction integral ∫κ dx.

## Strategy

**Phase 1 — Evanescent wake in a barrier *(the firewalled core)*.** *Goal:* derive the decay length
`ℓ_screen` from occlusion depth. *Method:* relay pressure across a raised-occlusion slab (PPT05);
solve for the decaying mode tick-by-tick (FLM05); read off `κ_native = 1/ℓ_screen`. **The WKB form
`√(2m(V−E))/ℏ` must not appear in the derivation** — add a firewall comment; it enters only as a
post-derivation comparison row. *Success (A-grade):* `κ_native` derived from lattice mechanics alone,
then shown to match `√(2m(V−E))/ℏ` to <1% as a **convergence** (not as the source). If κ can only be
produced by writing the WKB expression, label IMPORTED → C.

**Phase 2 — Square barrier transmission.** *Goal:* T(d,E). *Method:* match leaked wake amplitudes
at both faces; intensity ratio. *Success:* `T ≈ 16 (E/V)(1−E/V) e^{−2κd}` reproduced; the `−2`
traced to the QM04 amplitude-square.

**Phase 3 — STM current.** *Goal:* `I ∝ e^{−2κd}`. *Method:* electron-vortex wake across a vacuum
gap; current = landing rate. *Success:* decade-per-Å sensitivity (≈ 1 order / 1 Å) reproduced; work-function dependence right sign.

**Phase 4 — Gamow α-decay.** *Goal:* Geiger–Nuttall line. *Method:* α-core vortex leaking the
nuclear-edge occlusion barrier; ∫κ dx over the Coulomb slope. *Success:* log T_½ vs Z/√E linear,
slope within ~10% for a U/Th/Po series.

## Success criteria (canonical A–F) + anti-tautology gate

- **PASS (A — NATIVE):** `κ_native` derived from occlusion depth (NOT the WKB form), then T, STM slope,
  and Geiger–Nuttall all native to <1% (rates) / ~10% (T_½), with the vortex-crossing (re-seeding)
  mechanism shown, not asserted.
- **QUALIFIED (C — CONVERGENCE):** exponential form native but one prefactor (16·…, or the assault
  frequency) borrowed/flagged, **or** κ is obtained via the WKB expression `√(2m(V−E))/ℏ` rather than
  derived from occlusion — the firewall trips: importing the WKB κ caps the grade at C.
- **PENDING (D):** wake leaks and decays correctly but the re-seeding → vortex-crossing only heuristic.
- **FAIL (F):** cannot get penetration without a ψ that "is" on the far side. Report; census debt stands.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction | What kills it (numeric) |
|---|------|----------------|-------------------------|
| T1 | leakage is exponential, κ **native** | T ∝ e^{−2κd}; `κ_native = 1/ℓ_screen` from occlusion depth, matching WKB to <1% as convergence | if T is not exponential in d, wake-leakage is wrong → F; if κ matches only because `√(2m(V−E))/ℏ` was written into the code, the result is IMPORTED → C (firewall trip), not native |
| T2 | STM sensitivity | ≈ 1 current decade per 1 Å gap change; work-function dependence right sign | if dI/dd is off the ~1 decade/Å scale by >½ a decade, the decay length is wrong → mechanism wrong |
| T3 | Geiger–Nuttall | log T_½ ∝ Z/√E linear from ∫κ dx; slope within ~10% on a U/Th/Po series | if the slope misses by >10% or the relation is non-linear, the α-core leakage picture fails for decay |

## Dependencies

**Upstream:** QM01 (wake + steering), PPT05 (confinement = barrier wall), FLM05 (tick evolution).
**Downstream:** QM06 (quasi-bound/resonant states), nuclear decay (ATOMICUS α-core grammar).
**Related:** QM04 (the −2 = amplitude square), [[project_paradox_census]], E-series α-decay specs.

## Questions This Opens *(generative — log new ones in `QM03_VERDICT.md`)*

1. **Does `ℓ_screen` from occlusion predict a *different* energy dependence than WKB?** If the native
   screening length scales with occlusion depth rather than `√(V−E)`, there may be a regime (very thick
   or very tall barriers) where SDT and WKB diverge — a falsifiable fork, not a degeneracy.
2. **Is the re-seeding (vortex re-appears on the far side) a discrete, timed event?** A real leakage
   model has a tunnelling *time*. Does it predict a non-zero traversal time, and does it match the
   attoclock / Hartman-effect measurements (where QM is famously ambiguous)?
3. **Does the α-core "assault frequency" come out of the relay tick rate?** Geiger–Nuttall needs a
   pre-exponential attempt frequency. If that is the orbital relay frequency of the α-core vortex (not
   a fit), the Gamow prefactor becomes native — is it?
4. **Is there a maximum barrier the wake simply cannot leak?** Occlusion saturation (two-regime,
   g→2 near contact) might give a hard cutoff with no QM analogue — observable in fusion cross-sections
   at very low energy?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — QM03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (flag any borrowed prefactor: 16·…, assault frequency)
- Engine namespaces used: PPT05 occlusion, FLM05 tick, ATOMICUS α-core grammar — NO ψ, NO WKB κ in the Phase-1 chain, NO atomic:: in the native chain
- Phase thresholds (committed before run): P1 κ_native vs WKB <1% (as convergence, not source) · P2 T form + ‑2 traced · P3 STM ~1 decade/Å · P4 Geiger–Nuttall slope ±10%
- Forbidden retroactive changes: write `√(2m(V−E))/ℏ` into Phase 1 then claim native; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P1 κ_native off WKB by >1% | refine the occlusion-screening derivation (slab depth, FLM05 mode) | **OPEN** the screening-length claim; report best | swap in `√(2m(V−E))/ℏ` to hit <1% (firewall trip → C) |
| P1 κ only obtainable via WKB form | accept **C/IMPORTED** honestly; the WKB κ is the Schrödinger form | — | claim NATIVE while writing the WKB expression |
| P3 STM slope off ~1 decade/Å by >½ decade | re-check work-function → occlusion-depth mapping | **OPEN** the decay length | widen the STM tolerance |
| P4 Geiger–Nuttall slope off >10% or non-linear | re-examine ∫κ dx over the Coulomb-occlusion slope | **OPEN** the α-core leakage picture | plug the slope |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · the WKB κ `√(2m(V−E))/ℏ` inserted into the Phase-1
  native chain · `atomic::`/GM/G in the native chain · a ψ "on the far side".

---

*QM03 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

**REASSESSMENT (2026-07-04, Harvey directive — §G GATE-CONTRABAND check) — two-channel note,
appended before the run.** No committed gate exists yet for the traversal-time question
(§Questions #2, Hartman territory); this note pre-empts a contraband one:

- The κ-decay leakage mechanics (Phases 1–4) are **pulse-channel** physics and are unaffected —
  energy flux through the barrier stays c-capped; all committed falsifiers (T1–T3) stand as written.
- **Do not import "traversal time ≥ d/c" as a kill gate.** That would enforce the rival's c-cap
  axiom on constraint propagation (§G GATE-CONTRABAND — kill the gate, not the route). Under the
  two-channel architecture (FLM14 RUN_LOG ADJ-7), a barrier slab whose spations are gear-locked
  with both faces can update the far-face re-seeding constraint in the same tick — apparent
  sub-d/c (Hartman-saturated) traversal is then a candidate *native* SDT outcome, not a paradox
  and not a kill. Attoclock / Hartman-effect data enter as MEASURED anchors to compare against,
  never as a locality axiom. If a run lands superluminal group delay, report where it lands; if it
  lands ≥ d/c, report that — both publishable.
