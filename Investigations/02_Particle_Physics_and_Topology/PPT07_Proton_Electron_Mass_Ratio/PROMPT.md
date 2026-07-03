# INVESTIGATION PROMPT: Deriving the Proton-Electron Mass Ratio (m_p / m_e ≈ 1836.15) from Pure Vortex Topology

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [PPT07] INVESTIGATION PROMPT: Deriving the Proton-Electron Mass Ratio (m_p / m_e ≈ 1836.15) from Pure Vortex Topology: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## 1. Objective
To mathematically derive the proton-electron mass ratio ($m_p / m_e \approx 1836.15$) purely from the volumetric and topological scaling of $W=1$ (simple torus) and $W=3$ (trefoil knot) vortices within the SDT spation phase-relay lattice. The goal is to mathematically prove that 1836.15 is not an arbitrary constant, but a strict geometric requirement of spatial topology.

## 2. SDT Axiomatic Foundation
In the Standard Model, the mass ratio is an unexplained, dimensionless free parameter. 
Under Spatial Displacement Theory (Law IV), inertial mass is defined as the cost of throughput reorganization:

$$m = \frac{\Phi \cdot V_{disp}}{3 \ell_P^3 c^2}$$

Because $\Phi$, $\ell_P$, and $c$ are global invariants of the spation lattice, the mass ratio between any two particles is strictly equivalent to the ratio of their exclusion volumes (the physical volume of lattice they displace):

$$\frac{m_p}{m_e} = \frac{V_{disp}(W=3)}{V_{disp}(W=1)}$$

## 3. The Core Physical Question
If the electron is a stable $W=1$ topological defect (a simple torus) and the proton is a stable $W=3$ topological defect (a trefoil knot), why does the geometric transition from $W=1$ to $W=3$ result in a volume expansion of exactly 1836.15267? 

What is the geometric or fluid-dynamic constraint in the spation lattice—driven by the universal convergence pressure $P_{conv} = 2.46 \times 10^{48}$ Pa—that locks a $W=3$ knot into being ~1836 times larger than a $W=1$ loop?

## 4. Required Mathematical Deliverables

Your task is to build the mathematical proof. You must construct a formal response containing the following steps:

### Phase 1: Toroidal Parametrization ($W=1$)
1. Define the geometric volume $V_{disp}$ of a spation torus. 
2. Establish the stability constraint for the electron: At what ratio of major radius ($R_{maj}$) to minor radius ($r_{min}$) does the internal circulation velocity equal $c$ while balancing the external convergence pressure ($P_{conv}$)?
3. Extract the normalized volume $V_1$ as a function of the lattice parameters.

### Phase 2: Trefoil Parametrization ($W=3$)
1. Parametrize a trefoil knot embedded in the same nearest-neighbour lattice. A trefoil has three lobes and self-intersections (or minimum separation distances) that a simple torus lacks.
2. Define the geometric volume $V_{disp}(W=3)$. Note that the minor radius (cross-section of the flux tube) must accommodate the same spation density constraints.
3. Establish the stability constraint for the $W=3$ knot. Because the flux tube must wind over and under itself three times, the major radius cannot arbitrarily shrink. What is the minimum topological clearance required to prevent the phase-relay flux from short-circuiting across the lobes?

### Phase 3: The Volume Ratio Equation
1. Combine the stability constraints of $W=1$ and $W=3$.
2. Formulate the explicit volumetric ratio: 
   $$f(W) = \frac{V_{disp}(3)}{V_{disp}(1)}$$
3. Evaluate the geometric constants (e.g., integrating the length of the trefoil curve vs the circle, multiplying by the cross-sectional area changes forced by curvature constraints). 

### Phase 4: Resolution of 1836.15
1. Isolate the mathematical origin of the number 1836.15. 
2. A known topological approximation suggests $(3/2)^{3/2} \times 10^3 \approx 1837.12$. Does this approximation emerge organically from your geometric integration of the trefoil knot? Is there an exact analytical expression involving $\pi$, the winding number $W$, and the golden ratio or other topological constants?

## 5. Adversarial Constraints (STRICT)
- **NO EMPIRICAL ANCHORS:** You may not use the measured mass of the proton ($1.672 \times 10^{-27}$ kg) or the electron ($9.109 \times 10^{-31}$ kg) anywhere in your derivation. You must derive the *ratio* purely from geometry.
- **NO STANDARD MODEL:** Do not invoke Higgs mechanisms, QCD, quarks, or binding energy. The proton is a continuous spation vortex, not a composite of three quarks.
- **DIMENSIONAL CONSISTENCY:** Ensure all volumetric calculations maintain proper $L^3$ dimensionality and scale correctly with $\ell_P$.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_VI winding, bridge::k_*, PPT01 equilibrium
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

*PPT07 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
