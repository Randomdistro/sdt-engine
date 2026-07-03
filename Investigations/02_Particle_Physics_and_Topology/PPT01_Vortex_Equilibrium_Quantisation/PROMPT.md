# PPT01: Vortex Equilibrium Quantisation — Mathematical Framework

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [PPT01] PPT01: Vortex Equilibrium Quantisation — Mathematical Framework: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Definitions

| Symbol | Name | Value/Range | Meaning |
|--------|------|-------------|---------|
| v_T | Toroidal velocity | [0, c] m/s | Speed of circulation around the torus major axis (the "long way around") |
| v_P | Poloidal velocity | [0, c] m/s | Speed of circulation around the torus minor axis (the "short way around", cross-section rotation) |
| v_C | Translational velocity | [0, c] m/s | Centre-of-mass speed of the particle through the lattice |
| R | Major radius | m | Distance from the torus centre to the tube centre |
| a | Minor radius | m | Radius of the tube cross-section |
| W | Winding number | 1, 2, 3, ... | Number of poloidal loops completed per toroidal revolution |
| (p,q) | Torus knot type | integers | p toroidal wraps, q poloidal wraps; knot iff gcd(p,q)=1 and min(p,q)≥2 |
| c | Speed of light | 2.998×10⁸ m/s | Maximum propagation speed in the lattice |
| ℏ | Reduced Planck constant | 1.055×10⁻³⁴ J·s | Quantum of angular momentum |
| m | Particle mass | kg | Determined by the torus geometry via de Broglie/Compton self-consistency |

---

## 2. The Question

A particle in SDT is a self-sustaining vortex on a genus-1 torus (a doughnut). The vortex circulates with two independent angular velocities — toroidal (around the ring) and poloidal (around the tube). Law V constrains the total speed budget:

```
v_T² + v_P² + v_C² = c²
```

This says: the sum of the squares of all velocity components equals c². This is not a relativistic approximation — it is the **exact budget** of the movement allocation (Law V: a spation cannot relay faster than c in any combination of modes).

**Which values of R/a give self-consistent, stable equilibria?**

---

## 3. Derivation of the Mode Equations

### Step 1: Helical Coupling

A circulation on the torus surface traces a helix. If the helix completes W poloidal loops for every 1 toroidal loop, the ratio of poloidal to toroidal velocity is determined by geometry:

The path length for one toroidal revolution = 2πR.
The path length for W poloidal loops = W × 2πa.
These are traversed in the same time T, so:

```
v_T = 2πR / T       (toroidal speed)
v_P = W × 2πa / T   (poloidal speed)
```

Dividing:

```
v_P / v_T = W × (a / R)     ... (1)
```

This is purely geometric — the velocity ratio equals the winding number times the inverse aspect ratio.

### Step 2: Compton Self-Consistency

The torus is not an arbitrary container — it IS the particle. The radii R and a are determined by the circulation, and the circulation is determined by the radii. This is the self-consistency condition: the torus geometry must equal the de Broglie wavelength of its own circulation.

For the toroidal mode, the de Broglie wavelength λ_T = h/(m v_T) must equal the circumference 2πR:

```
2πR = h / (m v_T)
R = ℏ / (m v_T)         ... (2)
```

Similarly for the poloidal mode:

```
2πa = h / (m v_P)
a = ℏ / (m v_P)         ... (3)
```

Dividing (2) by (3):

```
R/a = v_P / v_T          ... (4)
```

The aspect ratio equals the velocity ratio. This is a **consequence** of self-consistency, not an assumption.

### Step 3: Solve the Coupled System

Substituting (4) into (1):

```
v_P / v_T = W × (a / R) = W × (v_T / v_P)
```

Multiplying both sides by v_P:

```
(v_P)² = W × (v_T)²     ... (5)
```

The poloidal velocity squared is W times the toroidal velocity squared. The poloidal mode carries more energy for higher winding numbers.

### Step 4: Apply the Budget (at rest, v_C = 0)

```
v_T² + v_P² = c²
v_T² + W × v_T² = c²        [substituting (5)]
v_T² (1 + W) = c²
```

Solving:

```
v_T = c / √(1 + W)          ... (6)
v_P = c √W / √(1 + W)       ... (7)   [from (5)]
R/a = √W                     ... (8)   [from (4) and (5)]
```

**The aspect ratio is the square root of the winding number.** This is an exact result — no approximations.

### Step 5: Budget Verification

```
v_T² + v_P² = c²/(1+W) + Wc²/(1+W) = c²(1+W)/(1+W) = c²  ✓
```

The budget closes exactly for all W. This is algebraically guaranteed.

---

## 4. The Mass Spectrum

From equation (2):

```
m = ℏ √(1+W) / (R c)      ... (from R = ℏ/(m v_T) and v_T = c/√(1+W))
```

Or equivalently from (3):

```
m = ℏ √(1+W) / (a c √W)
```

These are consistent: dividing gives R/a = √W, confirming (8).

The mass depends on **two** quantities:
1. **W** (discrete) — the winding number, which is a topological integer
2. **R or a** (continuous) — the physical size, determined by V_disp (Law IV)

Therefore: **the mass spectrum is discrete in topology, continuous in size.** Specific mass values (m_e, m_p) require knowing the displacement volume.

---

## 5. Generalisation to (p,q) Torus Knots

The simple winding W assumes p=1 (one toroidal loop). For a general (p,q) torus knot with p toroidal and q poloidal wraps:

```
v_P / v_T = (q/p) × (a/R)     [generalised coupling]
```

Combined with self-consistency a/R = v_T/v_P:

```
(v_P)² = (q/p) × (v_T)²
v_T² (1 + q/p) = c²
v_T = c √p / √(p+q)           ... (9)
v_P = c √q / √(p+q)           ... (10)
R/a = √(q/p)                   ... (11)
```

A (p,q) curve is a **true knot** (cannot be deformed to a point) only if gcd(p,q) = 1 AND both p ≥ 2 and q ≥ 2. Otherwise it is an unknot.

| (p,q) | Name | Knotted? | Stable? |
|-------|------|----------|---------|
| (1,1) | Unknot | No | Confined by V_disp only → **electron** |
| (1,2) | Unknot (2-wrap) | No | **Unstable** — decays |
| (2,3) | Trefoil | **Yes** | **Topologically protected** → **proton** |
| (2,5) | Solomon's seal | Yes | Candidate (heavier particle?) |
| (3,4) | (3,4) knot | Yes | Candidate |

---

## 6. Key Results

1. **Budget closure** is exact for all (p,q) — algebraically guaranteed.
2. **Electron** = (1,1) unknot: v_T = v_P = c/√2, R/a = 1 (fat torus, equal partition).
3. **Proton** = (2,3) trefoil: v_T = 0.632c, v_P = 0.775c, R/a = 1.225. Topologically knotted — eternal stability.
4. **W=2** is unstable: unknotted, lighter than electron at same a, no known particle.
5. **Mass ratio** m_p/m_e = 1836.15 does NOT follow from topology alone — it requires V_disp (→ PPT03).
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT01
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

*PPT01 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
