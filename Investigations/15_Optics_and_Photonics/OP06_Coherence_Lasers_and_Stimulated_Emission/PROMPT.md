# OP06 — Coherence, Lasers and Stimulated Emission

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether optical coherence (lasing threshold, gain saturation, the
   Schawlow–Townes linewidth, `g⁽²⁾(0)=1`) is *derivable* as a macroscopic relay phase-lock —
   many vortices re-emitting in lock-step, the same order-parameter physics as the CM01
   superconducting phase-lock — **with no bosonic photon statistics and no field quantisation**, or
   whether SDT must import boson bunching / a quantised cavity mode to get coherence.
2. **Why does it matter?** — The laser is the cleanest macroscopic coherence in physics and the
   standard story rests entirely on identical-boson statistics. If coherence is a phase-lock order
   parameter on the emitting lattice, SDT unifies the laser with superconductivity/superfluidity (CM01,
   E59) under one order-parameter idea and stimulated emission becomes an in-phase relay trigger, not
   boson cloning. If it cannot, the no-photon-particle thread (OP03/OP05) breaks at the coherence step.
3. **How will we find out?** — Four gated phases: define the relay phase-lock order parameter and get
   `g⁽²⁾` 1-vs-2 from lock-vs-independent **before** any photon-statistics formula; gain/threshold from
   in-phase trigger vs cavity loss; Schawlow–Townes as phase-diffusion of the lock; coherence length
   as the stretch. Recovering `g⁽²⁾` by writing the bosonic coherent/thermal result caps the grade at C
   (anti-tautology gate).
4. **What would prove us wrong?** — §Falsification, numeric: `g⁽²⁾(0)` not 1.00 (coherent) / 2.00
   (thermal) within 1%; threshold not sharp (round-trip gain = loss); `Δν_ST` not ∝ 1/P; or coherence
   that only arises once boson bunching is assumed.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

The load-bearing claim is that **coherence is a phase-lock order parameter** (a phase transition on
the emitter lattice, the CM01 mechanism), and **stimulated emission is one relay emission triggering
an in-phase re-emission from an excited vortex** — *not* the cloning of an identical boson into an
occupied mode. The discriminator `g⁽²⁾(0)=1` (locked) vs `=2` (independent) must fall out of *whether
the emissions are phase-locked*, derived, not from the bosonic coherent-vs-thermal formula written
down. **Writing the boson `g⁽²⁾` result, or quantising the cavity mode to get the statistics, is the
identity — it caps the grade at C (row IMPORTED).** No second quantisation, no photon-number Fock
states, and no photon-particle enter as mechanism; gain-medium level energies/cross-sections are
MEASURED-INPUT.

## Question

A laser is the cleanest macroscopic coherence in physics, normally explained by bosonic photon
statistics and stimulated emission of identical quanta. SDT has no photon-boson. **Can optical
coherence be reproduced as phase-locked relay emissions — many vortices re-emitting in lock-step,
the laser being a macroscopic relay phase-lock exactly analogous to the superconducting phase-lock
of [[CM01]] — recovering the lasing threshold, gain saturation, the Schawlow–Townes linewidth, and
`g⁽²⁾(0)=1` coherence, with stimulated emission being one emission triggering an in-phase re-emission
from an excited vortex rather than the cloning of a boson?** Coherence becomes a phase-lock order
parameter on the emitting lattice, the same order-parameter idea as superconductivity (E59).

## SDT mechanism & hypotheses

Each excited vortex can dump its stored displacement as an emission. Left alone the dumps are
random-phase (thermal light). A passing emission can *trigger* an excited vortex to re-emit
**in phase** (stimulated emission = phase-locked relay trigger). A cavity feeds the emission back so
the whole gain medium locks to one relay phase above threshold — a phase transition.

- **H1 (coherence = phase-lock order parameter):** define a relay phase-lock order parameter on the
  emitters; coherent (laser) above a critical inversion, incoherent (thermal) below — a phase
  transition, like CM01's superconducting condensate.
- **H2 (stimulated emission = in-phase trigger):** an incoming emission triggers an excited vortex to
  re-emit at the same relay phase; gain `g ∝ (N₂−N₁)`; threshold when round-trip gain = cavity loss.
- **H3 (Schawlow–Townes linewidth):** residual spontaneous (random-phase) dumps perturb the locked
  phase, giving `Δν_ST = πhν(Δν_c)²/P` — linewidth as phase-diffusion of the lock, not a quantum limit.
- **H4 (photon statistics ⇒ relay statistics):** `g⁽²⁾(0)=1` (coherent) and `=2` (thermal) follow
  from whether the emissions are phase-locked or independent — no boson bunching postulate.

## Strategy

**Phase 1 — Phase-lock order parameter.** *Goal:* define coherence natively. *Method:* relay-phase
order parameter over emitters (cf. CM01). *Success:* coherent/thermal as two phases of one model;
`g⁽²⁾(0)` 1 vs 2 recovered.

**Phase 2 — Gain & threshold.** *Goal:* lasing threshold. *Method:* in-phase trigger gain vs cavity
loss. *Success:* threshold inversion and slope efficiency reproduced for a model 4-level gain medium.

**Phase 3 — Linewidth.** *Goal:* Schawlow–Townes. *Method:* phase-diffusion from residual random
dumps. *Success:* `Δν_ST ∝ 1/P` scaling and prefactor to order.

**Phase 4 — Coherence length (stretch).** *Goal:* temporal/spatial coherence. *Method:* phase-lock
correlation time from OP03's relay sum. *Success:* coherence length `c/Δν` recovered.

## Success criteria

- **PASS (A):** threshold, gain, linewidth, and `g⁽²⁾` from one relay phase-lock, zero boson statistics.
- **QUALIFIED (C):** the above with gain-medium level energies/cross-sections as MEASURED inputs (expected).
- **PENDING (D):** coherence/threshold recovered, Schawlow–Townes only schematic.
- **FAIL (F):** coherence cannot arise without importing bosonic photon statistics.

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | `g⁽²⁾(0)` from lock | `=1.00` (phase-locked/laser), `=2.00` (independent/thermal) | `g⁽²⁾(0)` off 1.00 (laser) or 2.00 (thermal) by >1% from the lock model ⇒ coherence needs a boson-statistics postulate |
| F2 | Lasing threshold | sharp turn-on where round-trip gain = cavity loss; slope efficiency above | no sharp threshold, or turn-on not at gain=loss ⇒ stimulated emission is not an in-phase relay trigger |
| F3 | Schawlow–Townes | linewidth `Δν_ST ∝ 1/P` (phase-diffusion of the lock); prefactor to order | `Δν_ST` scaling not 1/P (exponent off 1 by >10%), or prefactor wrong by >×3 ⇒ linewidth not phase-diffusion |
| F4 | Order-parameter ≡ CM01 | the lasing transition uses the *same* phase-lock order parameter as the superconducting one | if the laser needs a distinct mechanism from CM01/E59 ⇒ the order-parameter unification is falsified |
| F5 | Anti-tautology | `g⁽²⁾` / threshold from the lock, not from boson statistics or a quantised mode | if `g⁽²⁾` is reproduced only by writing the bosonic coherent/thermal result or quantising the cavity ⇒ Class capped at **C**, row IMPORTED |

## Dependencies

**Upstream (required):** OP03 (relay-Huygens phased sum = the coherence machinery), OP05
(emission↔vortex exchange = the single gain event), **CM01** (superconducting phase-lock — the *same*
order-parameter, [[project_cq43_variable_closure]] for cavity `c_local`). **Lateral:** E59
(superfluid/phase-locked condensate — order-parameter cross-check). **Downstream (unblocked):**
quantum-optics reframes, frequency combs, optical clocks. **Framework:** `Theory/00_Ruleset.md`,
`Theory/05` audit spine, Law VI (the excited vortex as emitter).

## Questions This Opens *(generative — log new ones in `OP06_VERDICT.md`)*

1. **Is the laser threshold literally a CM01 critical point?** If the lasing transition and the
   superconducting transition share one order parameter, does the laser have a measurable critical
   exponent — and does it match the CM01/E59 universality class?
2. **Is the Schawlow–Townes limit the SDT coherence floor, or beatable?** If linewidth is
   phase-diffusion of the lock, is there a deeper relay-coherence limit below `Δν_ST`, or is
   Schawlow–Townes the true floor with no "quantum limit" language needed?
3. **Does `g⁽²⁾` interpolate continuously across threshold?** The lock picture should give a smooth
   2→1 crossover in `g⁽²⁾(0)` through threshold — is the measured crossover shape a discriminator
   against the boson-statistics account?
4. **Is "photon antibunching" (g⁽²⁾<1) reachable at all in SDT?** Single-emitter antibunching is the
   one regime the lock picture may *not* mimic with a boson story removed — does SDT predict it as a
   single-vortex dead-time, and does that match measured single-emitter `g⁽²⁾(0)`?
5. **Does cavity `c_local` (variable closure) shift the mode comb?** If the cavity alters relay speed
   (OP01/[[project_cq43_variable_closure]]), is there a tiny SDT correction to the free-spectral-range
   that an optical-clock comb could bound?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the lock chain (gain-medium level energies/cross-sections = MEASURED-INPUT)
- Engine namespaces used: CM01 phase-lock order parameter, law_VI:: (excited vortex emitter), depth_closure:: (cavity c_local)
- Phase thresholds (committed before run):
    P1 g⁽²⁾(0)=1.00/2.00 ±1% from lock-vs-independent · P2 sharp threshold at gain=loss ·
    P3 Δν_ST ∝ 1/P (exponent 1±10%), prefactor to ×3 · P4 coherence length c/Δν recovered
- Forbidden retroactive changes: write the boson g⁽²⁾ result or quantise the cavity then claim A;
    import boson bunching as mechanism; widen tolerances; IDENTITY-PASS; local constant namespaces
```

### Pivot table (numeric triggers; optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P1 `g⁽²⁾(0)` off 1.00/2.00 by >1% | recheck the lock-vs-independent emission statistics | **KILL** H1 (coherence=lock) | write the bosonic g⁽²⁾ and call it derived |
| `g⁽²⁾` only via boson statistics | down-grade to **C**; tag row IMPORTED | — | claim A while importing boson bunching |
| P2 threshold not sharp / not at gain=loss | re-derive in-phase-trigger gain vs cavity loss | **OPEN** the threshold | tune the inversion to force a knee |
| P3 `Δν_ST` exponent ≠ 1 | re-examine phase-diffusion of the lock (random dumps) | **OPEN** the linewidth | relabel the standard ST formula as derived |
| P4 lock ≠ CM01 order parameter | check whether the laser needs a distinct mechanism | **OPEN**/report the unification break | force-fit the two to look identical |
| Single-emitter g⁽²⁾<1 needed | model as single-vortex dead-time (antibunching) | **DEFER** the antibunching case | claim the lock alone explains it if it can't |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP06 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
