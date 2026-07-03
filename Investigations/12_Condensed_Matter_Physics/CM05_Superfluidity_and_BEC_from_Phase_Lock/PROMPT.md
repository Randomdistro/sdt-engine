# CM05 — Superfluidity and BEC from Phase Lock

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can He-4 superfluidity and BEC be reproduced as a **macroscopic
   phase-locked wake condensate** — every atom's convergence wake locked into one coherent
   circulation the lattice cannot occlude, circulation quantised in `κ = h/m` (FD02, clean to 0.02%) —
   with **no BEC wavefunction ψ imported as the mechanism**? Concretely: does a coherent wake
   genuinely out-span the occlusion scale to give `η → 0` at `T_λ`, and is the circulation quantum
   the *single-atom* `h/m_He` (not the `h/2m` pair of CM01)?
2. **Why does it matter?** — CM05 is the **uncharged twin of CM01** (README): the same phase-lock
   mechanism without handed redirection, so the expelled quantity is circulation rather than the
   swirl field. If it works with `κ = h/m`, it confirms the lock is a generic wake phenomenon and
   feeds CM06's macroscopic phase coherence (Josephson); if it needs ψ, CM01's pairing is suspect too.
3. **How will we find out?** — Four gated phases (§④): phase-lock onset (P1) and the zero-viscosity
   span (P2) run from the wake-coherence mechanism *before* the circulation number is quoted;
   importing a Gross–Pitaevskii / BEC ψ as the mechanism caps the grade at C.
4. **What would prove us wrong?** — §⑧: three falsifiers with numeric triggers and real failure
   modes — the viscosity drop (T1) and the circulation quantum (T2) can both come out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

## Question

Liquid He-4 below `T_λ = 2.17 K` flows without viscosity and circulates only in **quantised
vortices**. Bose–Einstein condensation puts a macroscopic occupation into one state. **Can
superfluidity and BEC be reproduced as a macroscopic phase-locked wake condensate — every atom's
convergence wake locked into one coherent circulation that the lattice cannot occlude — with the
circulation quantised in `κ = h/m` (FD02, clean to 0.02%)?** This is CM01's superconducting pair
condensate without charge: the *same* phase-lock mechanism, but for neutral atomic vortices, so the
expelled quantity is circulation rather than swirl-field.

## SDT mechanism & hypotheses

A normal fluid: atomic wakes are uncorrelated, each occluded → viscosity (FD02). Below `T_λ` the
wakes **phase-lock** into one condensate wake whose coherence length exceeds the occlusion scale →
zero viscosity (like CM01, but `κ = h/m` for one atom, not `h/2m`). Rotation cannot enter as smooth
flow (single-valued locked phase) — only as **quantised vortices**, each carrying one `κ`.

- **H1 (condensate = phase-locked wakes):** below `T_λ` a coherent wake spans `ξ ≫` occlusion scale
  → viscosity → 0; BEC is this macroscopic wake occupation, native (no ψ).
- **H2 (κ = h/m):** circulation quantum is the FD02 one-atom value `h/m_He` (already 0.02%); vortex
  lines carry integer `κ` by phase single-valuedness.
- **H3 (critical velocity):** Landau-type `v_c` = the relay speed at which the moving condensate can
  shed a roton/excitation = an occlusion onset; predicts the right order for He-4.

## Strategy

**Phase 1 — Phase-lock onset.** *Goal:* coherence temperature `T_λ`. *Method:* wake-locking energy
vs thermal disorder (CM04). *Success:* condensation transition exists; `T_λ` order recovered.

**Phase 2 — Zero viscosity.** *Goal:* η → 0 below `T_λ`. *Method:* coherent wake `ξ ≫` occlusion
scale averages defects to zero (mirror CM01 Phase 3). *Success:* η drops sharply at `T_λ`.

**Phase 3 — Quantised circulation.** *Goal:* `κ = h/m`. *Method:* phase single-valuedness around a
vortex; reuse FD02 result. *Success:* `κ` to <0.1%; integer vortex multiplicity.

**Phase 4 — Critical velocity.** *Goal:* `v_c`. *Method:* excitation-shedding onset (roton =
occlusion threshold). *Success:* `v_c` for He-4 within 2×; two-fluid ρ_s(T)/ρ qualitatively.

## Success criteria

- ✅ **PASS (A):** zero viscosity, κ=h/m, and `v_c` order all native, zero fits.
- ✅ **QUALIFIED (C):** transition + κ derived; `T_λ`/`v_c` absolute CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** phase-lock + κ shown; critical velocity only scaling-correct.
- ❌ **FAIL (F):** cannot get zero viscosity / quantised circulation without importing a BEC wavefunction.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | Wakes phase-lock below T_λ | a sharp viscosity collapse at a transition T of correct order (`T_λ ≈ 2.17 K`, within ~2×), with coherent-wake span `ξ ≫` occlusion scale | if the wake-coherence mechanism gives no transition (η stays finite to T→0), or a transition only appears once a BEC ψ is *imported* → no native condensate channel; thesis dead |
| T2 | `κ = h/m` for ONE atom | circulation quantum = `h/m_He = 9.97×10⁻⁸ m²/s`, within 0.1% (reuses FD02's 0.02%); the divisor is 1 (single atom), **not** the CM01 pair-2 | if the native count gives `h/2m` (pair) or a non-integer multiplicity for He-4 → the quantum is not one wake |
| T3 | `v_c` = excitation-shedding onset | He-4 critical velocity within 2× of the measured roton value (~60 m/s ideal; ~0.1–10 m/s practical) as an occlusion threshold | if SDT gives a `v_c` off by >2 orders, or superflow that is not occlusion-limited at all → superflow not occlusion-set |

## Dependencies

**Upstream:** CM01 (phase-lock mechanism; here κ=h/m not h/2m), FD02 (`κ = h/m`, 0.02%), E59
(phase-locked vortices, VERIFIED), CM04 (thermal disorder vs locking). **Downstream:** CM06
(macroscopic phase coherence → Josephson). **Related:** Meissner ≡ swirl expulsion (EMC03); here the
expelled quantity is circulation.

## Implementation notes

Double precision; `T/T_λ` dimensionless, κ in m²/s, η relative to the normal value. The condensate is
a macroscopic occupation of one wake mode — **never** import a BEC ψ as the mechanism (a Gross–Pitaevskii
field as machinery is the forbidden step; reproducing it as a target is fine). Circulation is a phase
count, not a borrowed unit. Keep measured He-4 properties (`T_λ`, `m_He`, roton gap) in one labelled
MEASURED-INPUT block; textbook values are the convergence target. Author attribution in all generated
files: **J. C. Harvey, Melbourne.**

## Questions This Opens *(generative — log new ones in `CM05_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Why `h/m` here but `h/2m` in CM01?** Is the single-vs-pair divisor purely the carrier identity
   (neutral atom vs handed electron pair), and can CM05 + CM01 together make "the divisor counts the
   locked bodies" a sharp, testable rule across superfluid/superconductor/BEC?
2. **Is the λ-transition the same coherence threshold as CM01's T_c and CM07's T_C?** All three are
   "alignment/lock energy vs CM04 thermal disorder". Is there one universal `k_B T_crit ≈ E_lock`
   law with only the lock energy changing?
3. **Is the roton a short-k FD05/lattice feature?** The critical velocity is set by the lowest
   excitation; is the roton minimum the same short-wavelength bend in the FD05 dispersion that sets
   CM04's Debye cutoff — one curve, two phenomena?
4. **Does the He-3 (fermionic) case force the pair-2 back in?** He-3 superfluidity is at much lower T
   and pairs; does SDT predict He-3 reverts to the CM01 `h/2m` lock while He-4 stays `h/m`, from the
   atom's wake topology alone?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the κ chain (T_λ and v_c absolute values may be CALIBRATED(1) — list them)
- Engine namespaces actually used: FD02 κ, law_III (occlusion), law_VI (wake), CM01 lock mechanism, CM04 thermal disorder, EMC03 expulsion
- Phase thresholds (committed before run):
    P1 transition at T_λ within ~2×, ξ ≫ occlusion scale · P2 η → 0 sharply below T_λ (no imported ψ)
    P3 |κ − h/m_He|/κ < 0.1%, divisor = 1 · P4 v_c within 2×
- Forbidden retroactive changes: import a BEC/Gross–Pitaevskii ψ as mechanism then claim A; widen
    tolerances; plug T_λ or v_c; IDENTITY-PASS; local constant namespaces; quote circulation in borrowed units
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 no transition from the wake-coherence mechanism | try the CM01 lock-energy form with κ=h/m; recheck thermal-disorder coupling (CM04) | **OPEN** the condensate channel; do NOT insert ψ | import a BEC ψ and grade A |
| P2 η → 0 only with an imported ψ | down-grade to **C** honestly (ψ is the postulate) | — | claim NATIVE while importing ψ |
| P3 κ divisor ≠ 1 (gives h/2m) | re-examine single-atom phase single-valuedness vs the pair count | **OPEN**: report the divisor | retro-fit to h/m |
| P4 v_c off >2× | recheck the excitation/roton onset as an occlusion threshold | **OPEN** v_c; report it | claim within-2× by widening |
| Rivals (Landau/GP) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (CM01/CM04 not run) | **DEFER** the affected phase; cite dependency ID | — | fake the transition |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** lock routes (FD05 wake-coherence vs CM01 lock-energy form), both native.

### Disallowed adjustments

- Importing a BEC/Gross–Pitaevskii ψ as the mechanism and grading A · post-hoc tolerance widening ·
  coefficient plugs · `atomic::`/GM/G in any native chain · quoting circulation in borrowed units.

---

*CM05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
