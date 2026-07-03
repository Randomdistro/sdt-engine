# CR08+CR08: Pressure-Gradient Redshift and BAO Scale — Data/Prompt

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
| Data | Source |
|------|--------|
| SDSS/BOSS/eBOSS BAO measurements: D_A(z), D_H(z) at z=0.15–2.33 | BOSS DR12, eBOSS |
| DESI BAO (2024) | DESI Y1 |
| CMB acoustic peak positions | Planck 2018 |
| Galaxy redshift surveys | SDSS, 6dF, WiggleZ |
| SDT strain rate σ | cosmology.hpp |
| SDT BAO scale interpretation | cosmology.hpp bao namespace |

## INVESTIGATION PROMPT

### CR08: Pressure-Gradient Redshift
**Target**: Derive the distance-redshift relation from pressure gradient traversal (no metric expansion).

SDT says: z = exp(∫σ dx) − 1, where σ is the local strain rate. At low z this is linear (z ≈ σd ≈ H₀d/c, reproducing the Hubble law). At high z it curves differently from ΛCDM.

Compute SDT μ(z) for the Pantheon+ sample and compare to ΛCDM.

### CR08: BAO as Lattice Standing Waves
**Target**: Show the 147 Mpc BAO scale is a lattice equilibrium length, not a frozen sound wave.

SDT: the coupled-epoch lattice (before the Clearing) supported standing waves at c/√3. The BAO scale = c_s × t_coupled = (c/√3) × 2.62×10¹⁶ s ≈ 147 Mpc. This is already in cosmology.hpp pre_clearing namespace.

### Common Methodology
1. Compute SDT angular diameter distance D_A(z) from pressure-gradient integration
2. Compare to BAO-measured D_A at each redshift bin
3. Compute SDT Hubble distance D_H(z) = c/H(z) where H varies with z
4. χ² comparison: SDT vs ΛCDM at each BAO redshift

### Success Criteria
- [ ] SDT D_A(z) matches BAO measurements within 3%
- [ ] BAO scale 147 Mpc reproduced from lattice sound speed × coupled epoch duration
- [ ] No dark energy needed in the SDT fit
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CR08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: cosmology.hpp, z_spectral, CR10 cubic rung
- Phase thresholds (committed before run): 3%
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

*CR08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
