# CM07 — Ferromagnetism as Aligned Vortex Wakes

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can spontaneous magnetisation, the Curie temperature `T_C`, domains,
   and the hysteresis loop be reproduced from **aligned wake circulation** — the "exchange
   interaction" being the occlusion energy of neighbouring wakes co-rotating vs opposing — with
   **everything quoted in native wake-circulation units and NOT a single Bohr magneton**? Concretely:
   is the moment quantum the electron's *own wake circulation* (a count of aligned wakes), and does
   `k_B T_C ≈ z J` order Fe/Co/Ni correctly without ever borrowing `μ_B`/`μ_N`?
2. **Why does it matter?** — CM07 is the **magnetism node** and the suite's hardest units test: the
   no-magnetons rule is *absolute* here ([[feedback_no_borrowed_units]]). If magnetism falls out as a
   wake-circulation count, the whole 14_Plasma_and_Magnetism branch inherits native units; if any
   result is quotable only in `μ_B`, that is an automatic FAIL on the units rule, regardless of how
   well the numbers match.
3. **How will we find out?** — Four gated phases (§④): the exchange energy `J` from wake co-rotation
   (P1) and the Curie point from `J` vs CM04 thermal disorder (P2) run in native wake-circulation
   units *before* any comparison to measured moments; introducing `μ_B`/`μ_N` anywhere in the
   mechanism is an automatic FAIL, not a Class-C downgrade.
4. **What would prove us wrong?** — §⑧: three falsifiers with numeric triggers and real failure
   modes — the exchange sign (T1), the `T_C` ordering (T2), and the native-units moment (T3) can each
   come out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

## Question

A ferromagnet is, in SDT, a region where the **wake circulations of many vortices are co-aligned**:
the same handedness ([[project_cq47_repulsion_inverse]]) repeated across a domain so their
circulations add into a macroscopic net wake. **Can spontaneous magnetisation, the Curie
temperature `T_C`, domains, and the hysteresis loop be reproduced from aligned wake circulation —
the "exchange interaction" being the energy cost of neighbouring wakes co-rotating vs opposing —
with everything quoted in native wake-circulation units and NOT a single Bohr magneton?** The
no-magnetons rule is absolute here ([[feedback_no_borrowed_units]]): magnetisation is a count of
aligned wakes × the electron's own wake circulation, never `μ_B`.

## SDT mechanism & hypotheses

Each W=1 vortex carries a handed wake (EMC03). When neighbours co-rotate, their wakes reinforce
(lower combined occlusion) → an alignment-favouring "exchange" energy `J`. Thermal disorder (CM04)
randomises alignment; above `T_C` it wins. Domains form because a uniformly aligned bulk pays a
long-range wake-field cost — splitting into domains lowers it. Hysteresis is the irreversibility of
unpinning domain walls (occlusion-pinned at defects).

- **H1 (exchange = co-rotation energy):** alignment energy `J` = wake reinforcement of co-rotating
  neighbours; sign of `J` (ferro vs antiferro) = whether co- or contra-rotation lowers occlusion.
- **H2 (Curie point):** `k_B T_C ≈ z J` (z = coordination) — thermal disorder beats wake alignment;
  predict `T_C` ordering for Fe/Co/Ni and `M(T) → 0` at `T_C` (mean-field exponent ½ near T_C).
- **H3 (native magneton):** the moment quantum is the electron's **own wake circulation** (koppa /
  `r_e` scale), and `M` is an integer count of aligned wakes — expressed natively, never in `μ_B`.

## Strategy

**Phase 1 — Exchange energy.** *Goal:* derive `J` from wake co-rotation. *Method:* occlusion of two
neighbouring co- vs contra-rotating wakes (EMC03 handedness). *Success:* `J > 0` (alignment favoured)
for Fe/Co/Ni; sign flip gives antiferro.

**Phase 2 — Curie temperature.** *Goal:* `T_C`. *Method:* alignment energy vs CM04 thermal disorder
(mean field). *Success:* `T_C` ordering Fe/Co/Ni correct; magnitudes within 2×.

**Phase 3 — Spontaneous M(T).** *Goal:* `M(T)`. *Method:* self-consistent alignment fraction.
*Success:* `M(T) → 0` at `T_C`; native-unit magnetisation curve (no magnetons anywhere).

**Phase 4 — Domains + hysteresis.** *Goal:* loop shape. *Method:* domain-wall pinning at occlusion
defects; unpinning threshold = coercive field. *Success:* hysteresis loop with finite coercivity;
remanence; domains as wake-field minimisers.

## Success criteria

- ✅ **PASS (A):** `J`, `T_C` ordering, `M(T)`, and a native-unit hysteresis loop, zero fits, zero magnetons.
- ✅ **QUALIFIED (C):** exchange + `M(T)` derived; `T_C` magnitude CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** alignment + Curie point shown; hysteresis only qualitative.
- ❌ **FAIL (F):** cannot get spontaneous M / `T_C` without importing spin operators — **or** any
  result is quotable only in magnetons (automatic FAIL on the units rule).

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | Exchange = wake co-rotation occlusion | `J > 0` (alignment lowers occlusion) for Fe/Co/Ni; sign flips to `J < 0` for a known antiferromagnet (Cr, MnO) | if co-rotation gives `J ≤ 0` for the ferromagnets (or no sign distinction between ferro and antiferro) → alignment is not occlusion-set; thesis dead |
| T2 | `k_B T_C ≈ z J` | `T_C` **ordering** Co(1388 K) > Fe(1043) > Ni(627) recovered; magnitudes within 2×; `M(T) → 0` at `T_C` with mean-field exponent β = ½ ± 0.1 | if the ordering inverts (e.g. Ni > Fe), or magnitudes are off >2× from one z·J rule, or M(T) does not vanish at T_C → Curie point is not the disorder threshold |
| T3 | Moment = native wake circulation (NO magnetons) | the per-site moment and `M(T)` are expressed entirely as a count of aligned wakes × the electron wake circulation (koppa / r_e scale); the per-atom moment ratio Fe:Co:Ni reproduced | **automatic FAIL** if any result is quotable *only* in `μ_B`/`μ_N`, or a magneton enters the mechanism — the moment must be an integer wake count, not an irreducible borrowed unit |

## Dependencies

**Upstream:** CM01 (wake locking), EMC03 (handedness ± → wake sign), Law VI (wake circulation,
traction), CM04 (thermal disorder vs alignment). **Downstream:** magnetism suite
(14_Plasma_and_Magnetism); domain physics. **Related:** [[feedback_no_borrowed_units]] (absolute:
native wake-circulation units, NO magnetons); APS04 (angular/wake structure).

## Implementation notes

Double precision; `T/T_C` dimensionless; **all magnetic quantities in native wake-circulation units
(electron wake circulation / koppa / r_e scale) — NEVER `μ_B`, `μ_N`, or any magneton**, not even as a
display convenience (this is absolute, [[feedback_no_borrowed_units]]). Magnetisation is the alignment
count × the electron's own wake circulation. The "field" expelled / aligned is EMC03 handedness, not a
borrowed gauge vector; `e` is the unit-bridge, never a charge substance ("magnetic charge"/"charge
radius" forbidden). No spin operators, no Heisenberg-Hamiltonian field machinery as mechanism (those are
targets to reproduce). Keep measured `T_C`, lattice/coordination data in one labelled MEASURED-INPUT
block. Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## Questions This Opens *(generative — log new ones in `CM07_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Why Fe/Co/Ni and not the next-door elements?** Is the J>0 ferromagnetic window a specific
   wake-overlap geometry (a coordination-×-wake-radius ratio), and does it predict *which* elements
   and alloys are ferromagnetic — including why Mn metal is not but MnBi is?
2. **Is the per-atom moment ratio Fe:Co:Ni a clean wake count?** Measured moments are non-integer in
   μ_B (2.2, 1.7, 0.6). Expressed in native wake circulation, do they become a cleaner ratio — and is
   the "non-integer" appearance just an artefact of the borrowed magneton unit?
3. **Are domains a wake-field minimisation with a native length scale?** Does the domain-wall width
   come out as a relay/wake coherence length (akin to CM01 ξ), giving a parameter-free domain size?
4. **Is the same `k_B T_crit ≈ E_lock` law as CM01/CM05?** Curie (CM07), superconducting (CM01) and
   λ (CM05) transitions are all alignment/lock energy vs CM04 thermal disorder. Is there one universal
   threshold relation with only the lock energy changing — testable across the three domains?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the exchange/M(T) chain (T_C magnitude may be CALIBRATED(1) — list it). MAGNETON budget: 0 (absolute)
- Engine namespaces actually used: law_III (occlusion), law_VI (wake circulation/traction), EMC03 (handedness), CM04 thermal disorder
- Phase thresholds (committed before run):
    P1 J>0 for Fe/Co/Ni, J<0 for an antiferromagnet · P2 T_C ordering Co>Fe>Ni AND within 2×, β = ½ ± 0.1
    P3 M(T)→0 at T_C, curve in native wake-circulation units (zero magnetons) · P4 finite coercivity + remanence
- Forbidden retroactive changes: introduce μ_B/μ_N anywhere (automatic FAIL); import spin operators /
    Heisenberg Hamiltonian as mechanism then claim A; widen tolerances; plug T_C; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 J ≤ 0 for Fe/Co/Ni | re-examine the co-rotation occlusion geometry (wake overlap, EMC03 sign) | **OPEN** the exchange channel; report J | flip the sign by hand to force J>0 |
| P1 no ferro/antiferro sign distinction | check whether contra-rotation truly raises occlusion | **OPEN**: report both signs | claim a flip that the run does not show |
| P2 T_C ordering inverts | recheck z·J (coordination × exchange) and CM04 disorder coupling | **OPEN**: report the ordering | retro-fit z or J per element |
| any quantity expressible only in μ_B | **STOP** — this is the units-rule FAIL, not a pivot; re-derive in native wake units | mark **KILLED** on the units rule, report honestly | quote the result in magnetons and grade anything ≥ C |
| Rivals (Heisenberg/mean-field) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (CM01/CM04 not run) | **DEFER** the affected phase; cite dependency ID | — | fake T_C |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** exchange routes (direct wake-overlap occlusion vs EMC03 handedness energy), both native.

### Disallowed adjustments

- Introducing μ_B/μ_N/magnetons anywhere (automatic FAIL) · importing spin operators / a Heisenberg
  Hamiltonian as mechanism and grading A · post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G
  in any native chain · "magnetic charge" substance language.

---

*CM07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
