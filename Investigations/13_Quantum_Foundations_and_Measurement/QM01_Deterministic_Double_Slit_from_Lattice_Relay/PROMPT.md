# QM01 — Deterministic Double-Slit from the Lattice Relay

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Quantum Foundations & Measurement (deterministic relay mechanics, no ψ).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can the two-slit fringe, *single-particle build-up*, and the
   amplitude-square (Born) intensity be produced by a **deterministic** relay model — one hard vortex
   through exactly one slit, its convergence wake through both — to <1% of `cos²(πd sinθ/λ)`, with
   λ = h/p emerging as the wake's relay period, **without ever instantiating a wavefunction, a
   superposition-of-states, or a collapse**? Or does the fringe demand a ψ that is genuinely "at both
   slits", in which case the wave–particle debt is real and must be paid, not narrated away.
2. **Why does it matter?** — This is debt #1 in `Audits/PARADOX_CENSUS.md` §8.2 and the gate for the whole
   QM block: QM02 (band-limit), QM03 (wake leakage), QM04 (Born square), QM05 (Bell), QM07 (spin) all
   reuse this engine's vortex-plus-wake steering. If QM01 fails natively, every downstream QM unit
   inherits the ψ it imports.
3. **How will we find out?** — Five gated phases (§④). Phase 1 derives λ from tick kinematics
   **before** any analytic fringe is written; the cos² must *emerge* from summing two relay pulses,
   never be inserted by hand (the §⑤ anti-tautology gate: writing the cos² into the code caps at C).
4. **What would prove us wrong?** — §⑧, four falsifiers each with the numeric outcome that kills the
   thesis (non-native λ; fringe RMS that cannot reach <1% without a hand-placed cos²; build-up that
   needs the vortex in both slits; decoherence that needs an observer rather than a mechanical
   wake-spoil).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

---

## §K ADDENDUM (2026-07-13) — this prompt was already §K-grade; two current-§K additions

> **This prompt is gold-standard** (the 2026-06-29 10× upgrade — filled §⓪, anti-tautology gate, five gated
> phases, four falsifiers, downstream QM-block dependency map). No rewrite. Two additions only:

**(1) Harvey's framing (2026-07-13) — Bell violation is INEVITABLE, not a debt to fear.** *"It is all movement.
All the energy in the universe is movement under a perfect pressure regime so precise that Bell's-theorem
violations are an inevitability."* → **Phase 5 (Bell) is no longer tentative.** The perfect pressure regime is
**one synchronised medium**; correlations exceed the local-hidden-variable bound **because the medium is not a
collection of separate locals** — it is a single throughpole ledger (in one side, out the other; the synchronous
channel, memory: *communication = desynchronisation*). So the honest Phase-5 position is: a *strictly local* relay
model **cannot** evade Bell — and that is **correct and predicted**, not a failure. The non-local feature (the
throughpole's instantaneous in/out) is the **FEATURE** (SDT's sharpest falsifiable divergence from QM: the
synchronous-channel fork), not a liability. **Do NOT** narrate it away or fabricate a local route; **do** state it
as a prediction and name the experiment that separates synchronous-channel from standard QM.
- *Anti-fake guard:* "inevitable" is a licence to *derive the CHSH value from the pressure regime*, **not** to
  assert it. Phase 5 must show the S > 2 correlation *emerges* from the shared-medium relay, or mark it OPEN.

**(2) The mislabel proof — Born-as-count IS movement.** H3's "Born rule as residence density" is the local
instance of the general proof Harvey names: **every "energy/charge/amplitude" is movement.** The Born intensity is
a *count of vortex landings* = a residence rate = **movement counted at the screen**. The "charge-handedness the
vortex carries" (§2) is likewise **a rate at a distance** — it *will* degenerate to movement (handed redirection),
exactly as "charge radius" does. Keep the interchange test live: if any step needs |ψ|² as an abstract amplitude
rather than a movement count, that is the imported term popping out.

**Four-root error-refinement loop (§K.2):** on every fired falsifier, sort before the next phase —
root-1 claim false (two-channel can't make fringes → ψ debt real) · root-2 dependency (FLM02/FLM05 relay, FD02 κ,
FLM10 isotropy) · root-3 prompt (phase mis-scoped, cos² hand-placed) · root-4 contraband (ψ / superposition /
observer-collapse smuggled as a "mechanical" phrase). Log per failure; the ψ-debt root once in `PARADOX_CENSUS`.

---

## 1 · Executive Summary

A particle in SDT is a **hard, localised solid vortex** travelling through a granular relay
lattice — never a wavefunction, never a probability cloud, never "both slits at once." **Can the
two-slit interference pattern, the Born rule (intensity ∝ amplitude²), and single-particle build-up
be reproduced from deterministic lattice relay mechanics alone — the vortex going through exactly
one slit while its convergence wake passes through both?** Resolving this converts SDT's biggest
liability into a result: it would show wave–particle "duality" is a **shadow of a wrong premise**
(the collapsing ψ) rather than a fact the theory must absorb. **We expect:** the *carrier wake*
(the convergence pulse the vortex rides) diffracts through both apertures and steers the vortex to
landing sites whose density reproduces the cos²(πd sinθ/λ) fringe to <1%, with the de Broglie
wavelength λ = h/p emerging as the wake's relay wavelength, not an imposed postulate.

## 2 · Physical Context

The lattice is a relay of spations passing convergence throughput at one tick (`c = ℓ_P/t_P`). A
moving vortex is not alone: it drags a **wake** — a coherent disturbance in the relay field ahead of
and around it (the same wake that does PPT06 traction and APS04 multipole work). Two channels travel
together: the **solid vortex** (carries the mass, the charge-handedness, the "which-slit" fact) and
its **wake pulse** (carries the phase, spreads, diffracts). This is structurally a *pilot-wave/relay*
ontology — but it must be **derived from SDT primitives, not borrowed from de Broglie–Bohm**: the
"pilot" is the literal convergence wake, the guidance equation is least-resistance steering down the
wake's pressure gradient (the same rule that makes orbits least-resistance paths, [[project_cq43_variable_closure]]).

Key variables: vortex momentum `p` (and λ = h/p, to be *derived* as the wake relay wavelength, not
assumed); slit separation `d`, width `a`; screen distance `L`; landing coordinate `x`; wake phase
`φ(x)` accumulated along each path; relay tick `t_P`, spacing `ℓ_P`. The pattern intensity `I(x)`
is a *count* of vortex landings, never a squared abstract amplitude.

## 3 · Theoretical Framework

Build only on: Law I (convergence throughput, `P_conv`), Law III (occlusion), Law V (movement
budget `v² + v_circ² = c²`), Law VI (vortex topology + wake/traction, PPT06/APS04), and the relay
state-machine (FLM02 GPI, FLM05 tick-by-tick contact/gap). **Forbidden as inputs:** wavefunction,
ψ, Schrödinger evolution, Born postulate, superposition-as-ontology, "measurement collapse,"
Hilbert space. These are the *targets to reproduce*, never the machinery.

Working hypotheses:
- **H1 (two channels):** the vortex passes one slit; the wake — a convergence-pressure pulse —
  is broad enough (width set by the relay coherence length) to enter **both** slits and self-overlap
  on the far side.
- **H2 (relay wavelength):** the wake's spatial period is λ = h/p with h emerging from the lattice
  action quantum (one-vortex circulation `κ = h/m`, already clean in FD02 to 0.02%) — so de Broglie
  is a **relay dispersion relation**, not a postulate.
- **H3 (Born rule as residence density):** the vortex steers down the wake pressure gradient; the
  long-run landing density equals the wake intensity (overlap of the two slit-pulses), giving
  `I(x) ∝ |pulse_A + pulse_B|²` **as a count**, not as an axiom. The square is geometric (energy
  density of a superposed pressure field ∝ amplitude²), the SDT-native origin of "Born."
- **H4 (which-way destroys fringes natively):** any interaction that reads the vortex's slit
  (occludes one wake branch) removes that branch from the overlap — decoherence is **wake
  spoiling**, mechanical and local, with no observer and no collapse.

## 4 · Investigation Strategy

**Phase 1 — Relay wake kinematics (derive λ).** Model a vortex of momentum `p` moving through the
relay; compute the spatial period of its convergence wake from the tick mechanics (FLM02/FLM05).
*Success:* recover λ = h/p to <1% with h traced to `κ = h/m`, **no fitted wavelength**.

**Phase 2 — Single-slit envelope.** Pass the wake through one aperture of width `a`; compute the
far-field pulse from relay Huygens construction (each spation on the slit re-emits one tick).
*Success:* recover the sinc² single-slit envelope, width ∝ λL/a, from relay summation alone.

**Phase 3 — Two-slit overlap + vortex steering.** Two apertures; sum the two wake pulses; release
N vortices one at a time, each entering one slit (50/50) and steered by the *total* wake gradient to
a landing `x`. Histogram the landings. *Success:* histogram → cos²(πd x/λL)·sinc² to RMS <1% over
N≳10⁴; **single-particle build-up** reproduced (sparse dots early, fringe emerges late).

**Phase 4 — Which-way / decoherence.** Add a wake-spoiling interaction at one slit; show the fringe
*continuously* washes out as spoiling strength rises (visibility V vs spoiling), recovering the
complementarity relation `V² + D² ≤ 1` (distinguishability D) as a **mechanical** trade, no collapse.

**Phase 5 (stretch) — Bell scope memo.** Write (not necessarily run) the honest position on Bell:
does a *local* relay-wake model evade Bell's theorem, and if not, what non-local relay feature (the
throughpole's instantaneous in/out, [[project_foundational_ontology_influx_monopole]]) is invoked,
and is that a debt or a feature? **Mark OPEN if no clean local route exists — do not fabricate.**

## 5 · Success Criteria (canonical A–F) + anti-tautology gate

- ✅ **PASS (Class A — NATIVE):** Phases 1–4 native; λ=h/p **derived** from tick kinematics (h traced
  to `κ=h/m`, FD02); the fringe `cos²·sinc²` *emerges* from summing two relay wake pulses (not
  inserted), build-up is strictly one-slit-per-vortex, decoherence is mechanical wake-spoiling; all to
  <1% with zero fitted parameters. Born square shown as superposed-pressure energy density.
- ✅ **QUALIFIED (Class C — CONVERGENCE):** pattern reproduced but the amplitude-square step or λ
  borrows one flagged coefficient; build-up + which-way qualitatively correct. **Anti-tautology gate:
  writing `cos²` (or `|ψ|²`, or a ψ object) into the code and then "recovering" it caps the grade at
  C — that is the answer imported, not the mechanism derived.** This is the expected landing.
- ⚠️ **PENDING (Class D):** relay wake diffracts and overlaps, but vortex-steering → Born density
  shown only heuristically; flag the gap.
- ❌ **FAIL (Class F):** the two-channel model cannot produce fringes without re-importing ψ /
  superposition / collapse. Report it honestly; the census debt stands.

## 6 · Outputs

1. `QM01_DERIVATION.md` — relay-wake kinematics, λ=h/p, single/double-slit summation, Born-as-count.
2. `qm01_double_slit.cpp` — standalone C++20: relay Huygens wake + one-at-a-time vortex steering;
   emits `qm01_pattern.csv` (x, count) and a visibility-vs-spoiling table.
3. `qm01_results.txt` — fringe RMS vs analytic; build-up snapshots at N = 10², 10³, 10⁴.
4. `QM01_VERDICT.md` — A/C/D/F with the honest disposition of the Born and Bell sub-claims.

## 7 · Dependencies & References

**Upstream:** FLM02 (GPI), FLM05 (tick state machine), PPT06/APS04 (the wake), FD02 (κ=h/m clean),
ROOT-SIM (per-contact rule — the deepest dependency; flag where Phase 1 leans on its unproven core).
**Downstream:** QM measurement/Bell follow-ons; any "quantum" correspondence (tunnelling, uncertainty
as relay bandwidth). **Related:** `Audits/PARADOX_CENSUS.md` §8.2 (#1 debt), E81 (electron diffraction,
VERIFIED — lattice scattering), [[project_foundational_ontology_influx_monopole]] (no ψ, no collapse).

## 8 · Falsification Tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction | What kills it (numeric) |
|---|------|----------------|-------------------------|
| T1 | λ is the relay wake period | λ = h/p ± 1% with h from `κ=h/m`, **no fitted scale** | if the derived wake period misses h/p by >1%, or only matches once a wavelength is fitted, de Broglie is not native — relay dispersion is wrong (→ C at best) |
| T2 | fringe = wake-overlap **count** | `cos²·sinc²` to RMS <1% over ≥10⁴ landings, cos² **emergent** from summing two pulses | if RMS stays >1% with pulse-summation, **or** <1% is only reached once a `cos²` / `ψ²` term is written into the steering, the two-channel model is insufficient (the latter is an IMPORTED answer → C) |
| T3 | build-up is one-at-a-time | sparse dots → fringe with **exactly one slit per vortex** (50/50), fringe coherent | if a coherent fringe requires the vortex to traverse both slits (or be a delocalised packet), "both slits at once" is smuggled back in → F |
| T4 | decoherence = wake spoiling | visibility V falls **continuously** with spoiling strength; `V²+D²≤1` recovered mechanically | if V drops only via an inserted observer/collapse term, or `V²+D²>1`, the which-way result needs ψ-collapse → census debt persists (F on the decoherence sub-claim) |

## 9 · Implementation Notes

Use double precision; work in dimensionless `x/(λL/d)`. Seed the per-vortex slit choice and steering
from a deterministic but varying source (index-derived, **not** `Math.random`) so the build-up is
reproducible. Plot: (a) landing histogram vs analytic overlay; (b) visibility vs spoiling strength;
(c) three build-up panels. **Do not** insert the cos² by hand — it must fall out of summing two relay
pulses. **Guardrail for the central test:** no ψ object, no `superposition` state, no `collapse` call
anywhere in the steering chain — the vortex carries a definite (x, p, slit) at every tick. The
discipline (R4): a clean Class-C with an honestly-flagged amplitude-square borrow beats a forced "A"
that hides a ψ. Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## 10 · Questions This Opens *(generative — log new ones in `QM01_VERDICT.md`)*

These are *not* required for the verdict; they are the point of doing it well.

1. **Is the relay coherence length a measurable cutoff?** The wake must be broad enough to span both
   slits; that width is set by the relay coherence length. Does it predict a *maximum slit separation*
   beyond which fringes vanish — a number testable against matter-wave interferometry (C₆₀, large
   molecules)?
2. **Does "single slit per vortex" survive delayed-choice?** If which-slit is decided after the vortex
   passes, the wake-spoiling story (H4) makes a *local mechanical* prediction. Does it differ from the
   QM delayed-choice result, and is that a fork or a degeneracy?
3. **Is the Born square here the *same* square as QM04's elastic energy density?** If yes, QM01 and
   QM04 share one geometric origin; if the coefficients differ, one of them is borrowing.
4. **Can the build-up rate (dots/second → fringe) be predicted, not just the final pattern?** A
   relay-steering model has a real per-vortex timescale; does it match observed single-electron
   build-up movies?
5. **Does the wake-spoiling `V²+D²≤1` saturate or fall short of the QM equality?** A mechanical model
   may give an inequality strictly *inside* the QM bound — a measurable deficit, the QM-foundations
   analogue of QM05's expected Bell shortfall.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — QM01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (list any flagged borrow, e.g. the amplitude-square step)
- Engine namespaces used: measured (h via κ=h/m from FD02), law_V, law_VI/traction (wake) — NO ψ, NO atomic:: in the fringe chain
- Phase thresholds (committed before run): P1 λ ±1% (h from κ=h/m ±0.02%) · P2 sinc² shape · P3 fringe RMS <1% over ≥10⁴ · P4 V continuous, V²+D²≤1
- Forbidden retroactive changes: write cos²/ψ²/superposition/collapse into the steering then claim A; widen RMS tolerance; plug the fringe; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols (h, κ) | STOP — report blocker | Fit to target |
| P1 derived λ off h/p by >1% | alternative native dispersion route (FLM02 GPI vs FLM05 tick) | **OPEN** the relay-wavelength claim; cap at C | fit a wavelength scale, then claim native |
| P3 fringe RMS >1% from pulse-summation | refine relay Huygens mesh / steering integrator | **OPEN**; report best RMS, do not insert cos² | hand-place cos²/ψ² to hit <1% (that is IMPORTED → C) |
| P3 fringe only forms if vortex is in both slits | re-examine the two-channel split (wake width vs slit gap) | **KILL** H1 / mark the both-slits debt | smuggle a delocalised packet and call it the vortex |
| P4 V²+D²>1, or V needs an observer term | re-derive spoiling as pure wake occlusion | **OPEN**; report the deficit honestly | add a collapse/observer term to force complementarity |
| Bell route (P5) finds no clean local model | **OPEN** → hand to QM05; do not fabricate | — | claim a local Bell violation (R4 breach) |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy (FLM02 vs FLM05 wake derivation).

### Disallowed adjustments

- Post-hoc tolerance widening · cos²/ψ²/superposition/collapse inserted into the native chain ·
  `atomic::`/GM/G in the fringe chain · burying the T3/T4 debt outcome.

---

*QM01 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
