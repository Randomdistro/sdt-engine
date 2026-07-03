# GOM08: Mercury Precession from k-Hierarchy — Investigation Prompt

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

---

## 1. The Question

GR explains Mercury's anomalous perihelion precession as spacetime curvature near the Sun. SDT must reproduce the same 42.98"/century from the k²-gradient (convergence pressure profile) without invoking curved spacetime.

## 2. Methodology

### Step 1: The SDT velocity profile

From bridge namespace: v(r) = (c/k)√(R_Sun/r)

This is Keplerian at large r but incorporates the k-factor. The precession arises when the effective potential deviates from pure Keplerian at small r.

The key: near the Sun, the convergence gradient introduces a correction to the effective potential. This correction has the same functional form as GR's Schwarzschild correction because BOTH arise from the same velocity-field profile.

### Step 2: Derive the correction

The SDT effective potential for radial motion:

$$V_{\text{eff}}(r) = -\frac{c^2 R}{k^2 r} + \frac{L^2}{2r^2} - \frac{c^2 R L^2}{k^2 r^3 c^2}$$

The last term is the SDT correction (from the k-gradient modifying the angular momentum coupling). This is identical in form to the GR Schwarzschild correction:

$$V_{\text{GR}}(r) = -\frac{GM}{r} + \frac{L^2}{2r^2} - \frac{GM L^2}{r^3 c^2}$$

Since GM = c²R/k² (bridge law), these are ALGEBRAICALLY IDENTICAL.

### Step 3: Compute the precession

$$\delta\phi = \frac{6\pi c^2 R_{\text{Sun}}}{k^2 c^2 a(1-e^2)} = \frac{6\pi R_{\text{Sun}}}{k^2 a(1-e^2)}$$

Substitute:
- R_Sun = 6.957 × 10⁸ m
- k² = 686.3² = 471,008
- a = 5.7909 × 10¹⁰ m  
- e = 0.2056
- (1−e²) = 0.9577

$$\delta\phi = \frac{6\pi \times 6.957 \times 10^8}{471008 \times 5.7909 \times 10^{10} \times 0.9577}$$

Convert to arcseconds per century (multiply by 415 orbits/century and 206265 arcsec/radian).

### Step 4: Verify the algebraic identity

Show explicitly that the SDT precession formula and the GR formula give the same number because GM_equiv = c²R/k² maps one to the other exactly.

## 3. Critical Discussion

The result will NECESSARILY match GR, because the bridge law ensures GM = c²R/k². The SDT contribution is not a new prediction — it's a demonstration that the k-gradient formalism reproduces the same effective potential.

The DISTINGUISHING test would be: does SDT predict a different precession rate for objects with different internal structure at the same orbit? (GR says no — equivalence principle. SDT might say yes if the k-coupling depends on the orbiting body's own displacement field.)

## 4. Success Criteria

- [ ] Precession computed from SDT parameters (k, R_Sun, orbital elements)
- [ ] Result matches 42.98"/century to within 0.1"
- [ ] Algebraic equivalence to GR formula demonstrated
- [ ] Discussion of WHERE SDT and GR could diverge (if anywhere)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
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

*GOM08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
