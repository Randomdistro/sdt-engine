# NP04B — Three-Neutron Genesis Gate *(energetics PASS · kinetics UNRESOLVED)*

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP04B] NP04B — Three-Neutron Genesis Gate *(energetics PASS · kinetics UNRESOLVED)*: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## 1. Objective
Test the forward genesis `3 free neutrons → triton (¹H nucleus) + e⁻ + ν̄ₑ` on **two separate gates that must not be conflated**:
- **Energy gate (F0):** is the assembly exothermic? — *answerable now.*
- **Kinetic gate (F0b):** does it actually proceed at a non-negligible rate? — *not yet derivable.*

## 2. The energy gate (F0) — passes
```
Q(3n → t + e⁻ + ν̄ₑ) = Q_n + B(³H)
                     = 0.7823 + 8.482  =  9.264 MeV   (exothermic ⇒ ENERGY GATE: PASS)
```
Derivation (pure conservation): `3m_n = M_nuc(t) + m_e + Q`, with `M_nuc(t) = m_p + 2m_n − B(t)` ⇒ `Q = (m_n−m_p−m_e) + B(t) = Q_n + B(t)`.

**Sequential decomposition** (the physically realisable path, since the di-neutron is unbound):
```
step 1   n → p + e⁻ + ν̄ₑ        +Q_n          = +0.782 MeV   (rate-limiting: τ_n ≈ 880 s)
step 2   p + n → d + γ           +B(²H)        = +2.224 MeV   (radiative capture)
step 3   d + n → t + γ           +[B(t)−B(d)]  = +6.258 MeV   (radiative capture)
                                  ───────────────────────────
                          Σ = Q_n + B(t) = 9.264 MeV  ✓  (= F0, no double-count)
```

## 3. The kinetic gate (F0b) — unresolved
The energy being available says nothing about the rate. F0b requires what SDT has **not** yet derived:
- **3-body simultaneity / density** — three neutrons must coincide; in any dilute regime this is rare.
- **Weak split timing** — step 1 is gated by the slow free-neutron β-decay (`τ_n ≈ 880 s`); neutrons escape/decay-away competing.
- **Proton-keystone requirement** — the di-neutron is unbound (NP04A-F2), so genesis *cannot* proceed by `n+n`; it must route through a proton (step 1 first). The proton is the obligatory keystone.
- **Radiative-capture cross-sections** (steps 2–3) — these live in the BBN / stellar-nucleosynthesis regime and are not yet expressible in occlusion units.

**KINETIC GATE: UNRESOLVED (class F).** Energetics allowed; rate/probability not predicted.

## 4. Verification stages
- **F0** — compute `Q(3n→t) = Q_n + B(t)`; confirm exothermic; print the sequential decomposition and its sum-check. *(tool: `cq29b_genesis_gate.cpp`)*
- **F0b** — enumerate the kinetic suppressors above; declare UNRESOLVED with explicit failure criteria (no fabricated rate). A future stage may attempt step 2–3 cross-sections in occlusion units — that is the open work.

## 5. Data requirements
| quantity | value | gate |
|---|---|---|
| `Q_n = m_n−m_p−m_e` | 0.7823 MeV | F0 |
| `B(²H)` deuteron | 2.224 MeV | F0 step 2 |
| `B(³H)` triton | 8.482 MeV | F0 |
| **`Q(3n→t+e+ν̄) = Q_n + B(³H)`** | **≈ 9.264 MeV** | **F0** |
| 3n capture kinetics (rate/barrier/σ) | **UNRESOLVED** — energy allowed, rate not predicted | **F0b** |

## 6. Provenance (`FORMULATIONS_PROVENANCE_AUDIT.md`)
| # | result | provenance | correspondence | input_dependency | class |
|---|---|---|---|---|---|
| F0 | `Q(3n→t+e+ν̄) = Q_n + B(t) = 9.264 MeV` | conservation-derived | novel-pathway energy gate | measured masses + B(t) | **C-flagged** |
| F0a | sequential `Σ(steps 1–3) = Q_n+B(t)` (no double-count) | conservation-derived | known-match | measured | **C** |
| F0b | actual `3n` capture rate / probability | unresolved | novel-prediction | density + topology + weak timing | **F** |

**Tally (NP04B):** C 1 · C-flagged 1 · F 1.

*Author attribution: James Christopher Tyndall, Melbourne.*
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP04B
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

*NP04B · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
