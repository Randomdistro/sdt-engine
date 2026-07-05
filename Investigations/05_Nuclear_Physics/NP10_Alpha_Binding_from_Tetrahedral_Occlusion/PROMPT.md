# NP10: Alpha Binding from Tetrahedral Occlusion — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP10] NP10: Alpha Binding from Tetrahedral Occlusion — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Question

He-4 (the alpha particle) has binding energy 28.296 MeV — anomalously large compared to its neighbours. SDT describes it as a tetrahedral arrangement of 2 protons + 2 neutrons, forming 6 occlusion bonds (every nucleon bonded to every other). Can the total occlusion energy of this tetrahedral geometry reproduce 28.296 MeV?

## 2. Methodology

> **FARMER correction (2026-07-03, J.C.Harvey directive):** the transcription below carried only the
> FAR-FIELD occlusion route (the NP09 scalar bond, since failed −97.3%) and dropped the branch's
> founding mechanism — **occlusion SATURATION at contact**. The occlusion principle of the CMB
> throughput: every location receives the full convergent influx of the boundary sphere (growing
> 2 ly/yr in diameter) *unless blocked — and blocking is the work*. At nucleon contact (d ≈ 2R_p)
> each nucleon shadows ~half its partner's sky: this is the SATURATED regime (two-regime law,
> g → 2 near contact), where the bond energy is the full unoccluded-hemisphere pressure asymmetry,
> not the 1/r² far-field residual. Saturation is natively **coordination-dependent** — three
> contacts occlude more solid angle of a nucleon's sky than one — which is precisely the lock
> scaling measured by the 2026-07-03 run (×1.01 deuteron → ×1.98 triton → ×6.35 alpha, flat
> per-bond factors falsified). **The next run must test the saturated-occlusion solid-angle ledger
> as the lock term.**
>
> **Refinement (Harvey, same day):** the ledger is likely NOT a broad solid-angle area — the
> limited rim distance of the poloidal flow means contact area is very small and **contact ANGLE
> is the premium resource**. Treat the lock as an *angular-window allocation* problem: engagement
> in narrow rim-windows (FLM07 glancing-transfer locus), where simultaneous alignment for many
> partners is geometrically scarce — a native route to nonlinear coordination-dependence. The
> tetrahedral placement itself is a rendering, not settled structure — do not hard-code it as a
> premise; let the angle budget pick the arrangement.

### Step 1: Tetrahedral geometry

Place 4 nucleons at the vertices of a regular tetrahedron. The edge length d is determined by equilibrium between:
- Attractive occlusion — **saturated-regime solid-angle shadowing at contact (primary, per the correction above)**; far-field ℓ≥3 only beyond contact
- Repulsive centrifugal pressure from circulation (outward)
- For the two protons: repulsive ℓ=1 Coulomb

The measured He-4 boundary radius (1.6755 fm; lit. "charge radius") constrains d:
- R_boundary = d × √(3/8) → d ≈ 2.73 fm for the tetrahedron edge
- OR: R_boundary = 2R_p → d is the proton-proton distance ≈ 2R_p × √(8/3)

### Step 2: Count bonds and compute total energy

6 bonds in a tetrahedron:
- 4 × p-n bonds (each at distance d)
- 1 × p-p bond (distance d, with Coulomb repulsion reducing the net)
- 1 × n-n bond (distance d, pure occlusion)

Total binding = 4×E_pn + 1×(E_pp − E_Coulomb) + 1×E_nn

Where:
- E_pn = occlusion bond energy from NP09
  — NOTE (2026-07-03): NP09's scalar-occlusion route FAILED (−97.3%) and FLM12-D1 ruled the linear volume-price out at 34×; revise the premise before execution.
- E_pp = same occlusion, minus Coulomb repulsion
- E_nn = occlusion between two neutrons (no Coulomb)
- E_Coulomb = k_e e²/d = 1.44 MeV·fm / d

### Step 3: Consistency checks

1. Does 4×E_pn + E_nn + (E_pp − E_C) = 28.296 MeV?
2. Is B_alpha / 6 ≈ 4.72 MeV per bond reasonable compared to B_d = 2.224 MeV per bond? (Yes if closer packing → stronger occlusion)
3. Does the predicted R_He = 2R_p (1.683 fm) match measured 1.6755 fm? (0.43% — already in laws.hpp)
4. Does the tetrahedral symmetry explain μ_alpha = 0 (all magnetic moments cancel)?

### Step 4: Hierarchy test

Compute from the same geometry:
- B(He-3) = 3 p-n bonds + 0 p-p + ... (only 3 nucleons — triangle)
- B(H-3) = 3 p-n bonds (triangle geometry)
- Compare predicted ratio B_alpha / B_triton to measured 28.296 / 8.482 = 3.34

## 3. Success Criteria

- [ ] Total binding energy predicted within 20% of 28.296 MeV
- [ ] R_He predicted within 1% of measured
- [ ] μ_alpha = 0 explained by tetrahedral symmetry
- [ ] B_alpha / B_triton ratio reproduced
- [ ] Bond energy per edge is self-consistent with NP09 deuteron result
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP10
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 0.43%, 20%, 1%
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

*NP10 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
