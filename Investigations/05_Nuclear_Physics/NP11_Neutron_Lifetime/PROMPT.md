# NP11: Neutron Lifetime from Lattice Topology — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP11] NP11: Neutron Lifetime from Lattice Topology — Data/Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| Neutron beam lifetime | 888.0 ± 2.0 s | Yue et al. 2013 |
| Neutron bottle lifetime | 878.4 ± 0.5 s | Serebrov 2018 |
| Neutron lifetime discrepancy | ~8.6 s (4.6σ) | The "neutron lifetime puzzle" |
| n → p + e⁻ + ν̄_e Q-value | 0.782 MeV | m_n − m_p − m_e |
| Proton W=3, Neutron W=3 | Same topology | SDT |

## INVESTIGATION PROMPT

**Target**: Derive the neutron lifetime (~880 s) from the SDT topological transition rate: a W=3 uncharged trefoil rearranges to a W=3 charged trefoil + W=1 torus + open winding.

> NOTE (2026-07-03): the neutron model must follow NP17 (neutron = proton + internal electron), not a bare W=3 trefoil.

### SDT Interpretation
Beta decay (n → p + e⁻ + ν̄_e) is NOT a "quark transformation." It is:
1. The uncharged W=3 trefoil (neutron) is metastable — it LACKS the ℓ=1 wake stabilisation
2. The trefoil slowly rearranges: it develops an ℓ=1 wake (becomes proton)
3. The excess energy (1.293 MeV) is released as a W=1 torus (electron, 0.511 MeV) + open winding (antineutrino) + kinetic energy
4. The lifetime = 1/(rearrangement rate)

### Key Question
What determines the ~880 s timescale? In SDT:
- The neutron is trapped in a metastable topological state
- The rearrangement requires tunnelling through a topological barrier
- The barrier height relates to the energy cost of creating the ℓ=1 wake
- The rate ∝ exp(−barrier / kT) where T is the neutron's internal circulation "temperature"

### The Lifetime Puzzle
The 8.6 s discrepancy between beam and bottle measurements suggests either:
- SDT: different boundary conditions (lattice coupling in bottle walls vs free space) affect the decay rate
- Standard: dark decay channel n → p + χ (dark particle)
- SDT prediction: does lattice coupling to container walls modify the topological transition rate?

### Success Criteria
- [ ] Neutron lifetime order of magnitude reproduced from topological argument
- [ ] The 8.6 s beam/bottle discrepancy addressed
- [ ] The decay products (p + e + ν̄) explained as topology rearrangement
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP11
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
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

*NP11 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
