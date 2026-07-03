# NP14: Proton-Neutron Mass Difference from Topology — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP14] NP14: Proton-Neutron Mass Difference from Topology — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Question

Both proton and neutron are W=3 trefoil tori. The proton is charged (has ℓ=1 wake), the neutron is not. Yet the neutron is HEAVIER by 1.293 MeV. Why?

> NOTE (2026-07-03): the neutron model must follow NP17 (neutron = proton + internal electron), not a bare W=3 trefoil.

In SDT, mass = Φ V_disp / (3 l_P³ c²). So the neutron has a LARGER exclusion volume. The question is: what topological property of the uncharged trefoil gives it a larger V_disp?

## 2. Hypotheses

### Hypothesis A: Missing ℓ=1 wake → Redistributed energy
The proton's ℓ=1 wake (Coulomb field) extends to infinity and carries energy. This energy is OUTSIDE V_disp — it's in the wake, not the body. The neutron, lacking the ℓ=1 wake, has all its energy concentrated in the body (higher V_disp).

Test: Coulomb self-energy of the proton = α ℏc / R_p ≈ 1.71 MeV. If the proton's ℓ=1 wake carries ~1.71 MeV externally, and the neutron retains this energy internally:
Δm_predicted = (some fraction of) 1.71 MeV. Does ~1.293 / 1.71 = 0.756 correspond to a geometric factor?

### Hypothesis B: Different circulation partition
Without the ℓ=1 wake constraining the external pressure profile, the neutron's trefoil equilibrium settles at a slightly different R/a ratio, giving a different V_disp.

### Hypothesis C: Charge stabilisation
The proton's charge (ℓ=1 wake) provides additional stabilisation that slightly compresses V_disp. Remove charge → V_disp expands by ΔV → mass increases by Δm.

## 3. Methodology

1. Compute proton electromagnetic self-energy: E_em = α ℏc / R_p
2. Compute what fraction of E_em is "outside" vs "inside" V_disp
3. For the neutron: E_em = 0 externally, all retained internally
4. Δm = E_em(external) / c² → compare to 1.293 MeV
5. If this doesn't match: investigate the R/a equilibrium shift

## 4. Success Criteria

- [ ] A specific topological mechanism identified for the mass difference
- [ ] Δm predicted within 20% of 1.293 MeV
- [ ] The mechanism explains WHY the uncharged particle is heavier (not lighter)
- [ ] Consistent with the W+1 radius conjecture (both W=3)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP14
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 20%
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

*NP14 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
