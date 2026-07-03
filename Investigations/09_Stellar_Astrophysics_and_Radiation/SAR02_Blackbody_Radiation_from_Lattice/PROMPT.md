# SAR02–SAR02: Blackbody Radiation from Lattice — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| Planck spectrum B(ν,T) | Standard formula | Textbook |
| Stefan-Boltzmann constant σ | 5.670374×10⁻⁸ W/(m²K⁴) | CODATA |
| Wien displacement constant | 2.898×10⁻³ m·K | CODATA |
| CMB spectrum (FIRAS) | Blackbody T=2.7255 K (0.01% precision) | COBE FIRAS |
| Radiation constant a | 7.5657×10⁻¹⁶ J/(m³K⁴) | CODATA |
| SDT mode counting | Spation lattice modes per unit volume | To derive |

## INVESTIGATION PROMPT

**Target**: Derive the Planck/blackbody spectrum from SDT lattice mode counting.

### SDT Interpretation
The blackbody spectrum is NOT about "quantised oscillators" (Planck's original). In SDT:
- The spation lattice has a discrete set of modes (like phonons in a crystal)
- Each mode can carry energy in units of ε = hν (this is the lattice's natural quantisation — it's a LATTICE PROPERTY, not a particle property)
- The Planck distribution arises from counting lattice modes + Boltzmann statistics
- No photons needed — just lattice modes

### Three Derivations (SAR02, E62, SAR02)

**SAR02 — Planck spectrum**:
1. Count lattice modes in frequency interval dν: n(ν) = 8πν²/c³ (same as electromagnetic mode counting, because the lattice IS the medium)
2. Average energy per mode at temperature T: ⟨ε⟩ = hν / (exp(hν/kT) − 1)
3. Spectrum: u(ν) = n(ν) × ⟨ε⟩ → standard Planck function

**E62 — Stefan-Boltzmann**:
1. Total energy density: u = ∫ u(ν) dν = aT⁴
2. Show a = 8π⁵k⁴/(15c³h³) emerges from the lattice mode integral
3. SDT interpretation: a = (number of modes per volume) × (average energy per mode) at temperature T

**SAR02 — Wien's law**:
1. Peak of u(ν): ∂u/∂ν = 0 → ν_max = 2.821 kT/h
2. Equivalently λ_max T = 2.898×10⁻³ m·K
3. SDT: the peak is where the mode density × occupation factor is maximised — a purely geometric/statistical result

### Success Criteria
- [ ] Planck spectrum derived from lattice mode counting
- [ ] σ and a reproduced from the mode integral
- [ ] Wien constant reproduced
- [ ] The derivation uses only lattice properties (no "quantum" postulates beyond lattice discreteness)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_I luminosity, SAR02 mode counting
- Phase thresholds (committed before run): 0.01%
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

*SAR02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
