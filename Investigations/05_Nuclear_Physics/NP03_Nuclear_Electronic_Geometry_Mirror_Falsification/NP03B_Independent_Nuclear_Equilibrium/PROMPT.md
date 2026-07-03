# NP03B — Independent Nuclear Equilibrium *(positions, ELECTRON-BLIND)*

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP03B] NP03B — Independent Nuclear Equilibrium *(positions, ELECTRON-BLIND)*: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Purpose.** Produce 3-D nuclear block positions from grammar + packing equilibrium **only** — zero electron input. This is the substrate the whole mirror test rests on; its electron-blindness is the *non-circularity guarantee*.

**Inputs.** `(n_d, n_t)` block count from NP03A **only**.
**Outputs.** Per isotope: solved 3-D positions of the `n_d+n_t` blocks around the α-core, the achieved `θ_min`, the kissing radius, and a determinism hash.

**Method.** Tammes/Thomson relaxation (max-min angular separation) of `N = n_d+n_t` points on the sphere; kissing radius `r = sin(θ_min/2)/(1−sin(θ_min/2))`. Must reproduce `packing.hpp` presets as **emergent** equilibria: `N=4→109.47° (tetra)`, `6→90° (octa)`, `8→antiprism`, `12→icosa`. Tritons take the maximally-separated sites.

**HARD BAN (the whole point).**
```
NO SUBSHELLS, NO Aufbau order, NO electron-shell radius, NO 2n².
Any electron-ordered placement must be named contaminated_visual_mockup_only()
and is barred from this stage.
```

**Fixed metrics.** (i) convergence to Thomson minimum (energy plateau); (ii) `θ_min` within <2% of `packing.hpp`/known Tammes values; (iii) **determinism** — fixed seed ⇒ identical hash; (iv) zero electron quantities in any dependency.

**Null model (carried to NP03E).** Random sphere placement with **no** relaxation — the baseline geometry the real mirror score must beat.

**Failure criteria.** Any position depends on an electron quantity; non-deterministic output; divergence from `packing.hpp` presets; tritons not maximally separated.

**Reuses.** `packing.hpp` (Tammes/kissing/min-angular-pair), the verified equilibrium solver. **Provenance:** class **B** (SDT-derived, internal-only, electron-blind by construction).
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP03B
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 2%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP03B · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
