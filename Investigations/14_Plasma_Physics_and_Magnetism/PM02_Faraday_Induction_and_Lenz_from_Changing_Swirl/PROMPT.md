# PM02 — Faraday Induction and Lenz from Changing Swirl

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is **Lenz's minus sign** a *forced consequence* of EMC03 handedness (the
   induced wake must occlude the change that drove it, because throughput cannot be created by
   reshuffling) — or is it, as in textbook EM, a separately-postulated sign chosen to satisfy energy
   conservation? If the minus has to be inserted to make the energy ledger close rather than *falling
   out of* occlusion handedness, PM02 has explained nothing new.
2. **Why does it matter?** — Faraday's `−dΦ/dt` is one of the two source terms of the wave equation PM03
   needs; PM07's frozen-in induction equation is the ideal limit of this same back-reaction. If the
   minus sign is native here, the entire induction half of Maxwell becomes a relay-conservation theorem,
   and the motional/transformer EMFs unify with PM01's `qv×B` instead of being a separate "flux rule".
3. **How will we find out?** — Four gated phases (§④); the native swirl-flux count and the
   occlusion-handedness sign matrix (P1→P3) run **before** any `−dΦ/dt` is written as a rule; the loop
   carries no primitive `E`/`B`.
4. **What would prove us wrong?** — §⑧, each falsifier states the numeric outcome that kills it (EMF
   off >1%, a Lenz cell that doesn't oppose, motional ≠ transformer, an energy ledger that only closes
   with a hand-inserted sign).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired sign cell.

## Question

A loop of relay lattice threaded by a **time-varying collective swirl** (PM01's `w`) develops a drive
on its own vortices. **Can Faraday's `EMF = −dΦ/dt` and Lenz's sign be derived as the relay
back-reaction to a changing wake-circulation — with the minus sign forced by occlusion, not
postulated?** No primitive `E`/`B` fields, no flux rule imported: flux Φ is the count of swirl
streamlines through the loop, EMF is the net circulation drive on the loop's carriers.

## SDT mechanism & hypotheses

When the collective swirl threading a loop changes, the relay throughput available to the loop's
vortices is redistributed; conservation of circulation forces a compensating drive (the induced EMF),
and the loop's own induced swirl **occludes** the change that produced it (Lenz back-reaction).

- **H1 (EMF = −dΦ/dt):** define `Φ ≡ ∮ w·dA` (native swirl flux); show the induced circulation drive
  on the loop equals the time-derivative of threaded swirl, recovering `EMF = −dΦ/dt` term-for-term.
- **H2 (Lenz = occlusion back-reaction):** the **minus sign** is the EMC03 handedness of the induced
  wake — it always occludes the driving change (energy cannot be created by reshuffling throughput).
- **H3 (motional ≡ transformer):** loop-motion-through-static-swirl and static-loop-in-changing-swirl
  are one mechanism (relative wake change), unifying `qv×B` (PM01) with `−dΦ/dt`.

**Anti-tautology firewall.** The *trivial identity* is: once `Φ` and Faraday's rule are written, `EMF =
−dΦ/dt` is a definition. The *load-bearing* step is deriving the **minus sign** from EMC03 occlusion
handedness alone, with no Faraday rule and no primitive `E`/`B` consumed — and showing the energy ledger
then closes *as a consequence*, not as the thing that fixed the sign. Importing Faraday's law, or
choosing the sign to make energy conserve, **caps the grade at C**. **Native-before-borrowed:** `Φ` is a
swirl-streamline *count* (PM01 native units); any `B·A` in tesla·m² or any µ_B/µ_N appears only on the
final SI map line, never in the sign derivation. No primitive fields, no G/M-fundamental, no QM
wavefunction as the induction mechanism.

## Strategy

**Phase 1 — Swirl flux & the count.** Build PM01's `w` for a solenoid; define Φ as streamline count.
*Goal:* native Φ(t). *Method:* sum wakes, integrate over loop. *Success:* Φ matches `B·A` form to <1%.

**Phase 2 — Induced drive.** Vary the source; compute the relay-conservation circulation drive on a
test loop. *Goal:* `EMF`. *Method:* finite-difference dΦ/dt vs measured carrier drive. *Success:*
`|EMF + dΦ/dt|/|EMF| < 1%`; transformer turns-ratio `V₂/V₁ = N₂/N₁` exact.

**Phase 3 — Lenz sign.** Resolve the induced wake handedness (EMC03). *Goal:* sign always opposing.
*Method:* sign matrix over (dΦ/dt > 0, < 0) × (loop handedness). *Success:* 4/4 cells oppose the change.

**Phase 4 — Eddy brake.** Drag a conductor through the swirl. *Goal:* retarding force. *Method:*
induced-wake occlusion on the bulk. *Success:* drag `∝ v` direction-correct; energy ledger closes.

## Success criteria

- ✅ **PASS (A):** `EMF=−dΦ/dt` + Lenz sign + motional≡transformer all native, zero fitted params.
- ✅ **QUALIFIED (C):** relations reproduced with one flagged coarse-graining coefficient. *(Expected.)*
- ⚠️ **PENDING (D):** EMF magnitude scaling-correct but sign needs an external convention.
- ❌ **FAIL (F):** cannot get the minus sign without re-importing a primitive field / Faraday's law.

## Falsification tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | Induced drive = `−dΦ/dt` | `\|EMF + dΦ/dt\|/\|EMF\|` < 1% across ≥5 different `dΦ/dt`; transformer ratio `V₂/V₁ = N₂/N₁` exact | residual > 1% (not a numerics artefact) → EMF is not relay-conservation-derivable; thesis dead |
| T2 | Lenz sign from occlusion | sign matrix (dΦ/dt ≷ 0) × (loop handedness) = **4/4 cells oppose** the driving change, forced by EMC03 | any cell that opposes only after a hand-inserted sign → the minus is still a postulate → C, not A |
| T3 | Motional ≡ transformer | one relative-wake-change mechanism reproduces both EMFs; the two agree to <1% on a shared geometry | the two need different mechanisms / disagree >1% → no unification with PM01's `qv×B` |
| T4 | Eddy-brake energy ledger | drag `∝ v`, direction-correct; dissipated power = mechanical work input to <2% (no created throughput) | ledger off >2% or drag sign wrong → induced wake is not occluding the change → Lenz mechanism false |

## Questions This Opens *(generative — log new ones in `PM02_VERDICT.md`)*

Not required for the verdict; this is the payoff.

1. **Is Lenz = "no perpetual motion" the same statement as "throughput is conserved"?** If the minus
   sign is forced because the induced wake cannot create throughput, then the second law's
   irreversibility and Lenz's sign may be one relay-conservation principle. Can PM02 state that identity?
2. **Does the induction `−dΦ/dt` term plus PM01's `∇×w` close exactly two of Maxwell's four equations
   natively?** If so, the remaining two (`∇·E`, displacement current) are the PM03/PM04 targets — does
   the relay ontology predict the displacement-current term, or merely accommodate it?
3. **Is mutual/self-inductance a wake-overlap geometry?** Inductance `L` is currently an SI black box;
   in SDT it should be the geometric overlap of two circulation wakes. Does `L` fall out of wake
   geometry with no µ₀ except in the final unit conversion?
4. **Does the eddy-brake drag connect to FD02 relay diffusion?** The induced-wake dissipation should be
   the same relay-smoothing that PM05/PM07 call "resistivity". Is the brake coefficient FD02's η?

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (B=∇×w, Lorentz=occlusion), PPT06
(traction), EMC03 (handedness sign). **Downstream:** [[PM03_EM_Waves_as_Coupled_Relay_Pulses]]
(the ∂B/∂t source term), [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]] (frozen-in flux).
**Related:** E58 (monopole forbidden → ∇·B=0 closes the Maxwell pair), [[feedback_no_borrowed_units]].
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces actually used: law_III (occlusion), law_V (movement budget), bridge; PM01 swirl `w`
- Phase thresholds (committed before run): P1 Φ-count vs B·A <1% · P2 EMF residual <1% + turns-ratio exact · P3 Lenz 4/4 from handedness · P4 eddy ledger <2%
- Forbidden retroactive changes: import Faraday's rule / a primitive E,B into the sign chain then claim A; choose the minus to make energy close; quote any moment in µ_B/µ_N pre-final-line; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM02)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 EMF residual > 1% | refine `dΦ/dt` finite-difference; check streamline-count discretisation | **OPEN** the relay-conservation ↔ `−dΦ/dt` link | retro-fit EMF to `−dΦ/dt` |
| P3 a Lenz cell needs a hand sign | re-derive the induced-wake EMC03 handedness for that case | down-grade to **C** (minus is imported, not forced) | hand-flip the cell and claim A |
| P3 sign only closes via energy argument | check whether occlusion *predicts* the sign before energy is invoked | mark sign **CONVERGENCE** (energy-fixed), not NATIVE | claim native while the sign came from energy |
| P4 eddy ledger off > 2% | tie dissipation to FD02 relay diffusion η; recompute | **DEFER** P4; note the missing diffusion link | bury the open energy gap |
| Motional ≠ transformer > 1% | check the relative-wake-change frame is identical | **OPEN** the unification; report both EMFs | claim unification without the cross-check |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
