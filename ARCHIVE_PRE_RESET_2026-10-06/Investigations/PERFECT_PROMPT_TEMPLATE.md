# THE PERFECT INVESTIGATION PROMPT — Template & Inheritance Root

> **Status:** GOLD-STANDARD for all `Investigations/**/PROMPT.md` files (2026-06-27 revision).
> **Execution:** When *running* any prompt, also follow `PROMPT_EXECUTION_PROTOCOL.md` verbatim.
> **Principle:** *It is a bad plan that cannot be altered* — every prompt includes §⑩ pivot tables
> and pre-committed thresholds so failures become **PIVOT / KILL / OPEN**, not silent rewrites.

## What This Document Is

This is the **inheritance root** for investigation prompts. Use it to:

1. **Review** existing prompts — measure against §①–§⑩
2. **Author** new prompts — copy structure; fill domain content; **mandatory §⑩**
3. **Run** investigations — pre-commit thresholds → execute → adjust per protocol

**Standard header for every `PROMPT.md`:**

```markdown
> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC | ACTIVE | RESOLVED.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
```

---

## ⓪ The Golden Rule — five questions answered up front

Every prompt opens with these five answers (FLM10 pattern):

1. **What don't we know?** (the gap — one sentence)
2. **Why does it matter?** (stack position, downstream blockers)
3. **How will we find out?** (phases, native mechanism first)
4. **What would prove us wrong?** (≥3 falsifiers with numeric triggers)
5. **How will we know we're done?** (dual verdict: prompt completion + physics class)

If any answer is missing, the prompt is **not runnable**.

---

## The Gold-Standard Structure

Every investigation PROMPT must have exactly these sections, in this order:

### 1. Executive Summary (100–150 words)

**Purpose**: Immediately answer: "What is this investigation about, and why should we care?"

**Must include**:
- One sentence stating the question
- Why it matters (what theory gap does it close?)
- Expected outcome (what will we know after?)

**Example**:
> The State28D manifold has 28 degrees of freedom but some normalisations are hardcoded (10¹⁰ Pa/m, 10⁻²⁰ J). **Are these derived from first principles or fitted?** Resolving this determines whether SDT is a minimal theory or has absorbed empirical constants. **We expect**: both scales emerge uniquely from convergence pressure and topological transitions, using only CODATA 2018 constants.

### 2. Physical Context (250–400 words)

**Purpose**: Establish the conceptual ground. New readers should understand what system we're studying.

**Must include**:
- **Conceptual diagram or analogy** — not math yet, plain language
- **The key variables** — define all symbols, dimensions, ranges
- **Why this system matters** — how it connects to other parts of SDT

**Example**:
> The State28D is a 7-level hierarchy: point → line → plane → sphere → **torus** → dynamics → energy. 
> 
> The critical coupling is Level 5 (toroidal structure, dimension: pressure gradient [Pa/m]) to Level 6 (phase transitions, dimension: energy [J]).
> 
> Two scales appear hardcoded: 1e10 Pa/m and 1e-20 J. Are these natural scales of the system, or fitted?

### 3. Theoretical Framework (400–600 words)

**Purpose**: Show the equations and constraints that govern the system.

**Must include**:
- **Axioms or first principles** — what are we building on?
- **Key theorems** — what must be true?
- **Constraints** — what boundaries are fixed?

**Do NOT**:
- Borrow from other frameworks without permission (no QM wavefunctions, no field theory jargon unless proven identical)
- Introduce new fitted parameters (use only CODATA 2018, IAU, measured observables)
- Assume results from uncompleted CQ investigations

**Example**:
> From Law I: ε = u₀ ℓ_P³ (elementary convergence content)
> From Law III: F = (π/4) P_conv R₁² R₂² / r² (occlusion force)
> From Law IV: m = Φ V_disp / (ℓ_P³ c²) (mass as displacement volume)
> 
> Constraint: All scales must be expressible using only {ℏ, c, e, m_e, m_p, ℓ_P, T_CMB}.

### 4. Investigation Strategy (800–1200 words — be excessive)

**Purpose**: Break the problem into concrete phases. A reader must implement without guessing.

**Must include for EACH phase**:
- **Goal** — one measurable outcome
- **Method** — exact equations, `laws.hpp` namespaces/functions, algorithm steps
- **Pre-committed success metric** — numeric threshold written **before** run (e.g. `< 1%`, not "close")
- **Failure trigger** — what relative error or sign failure invokes PIVOT
- **Gate** — Phase N+1 forbidden until PASS-GATE or documented DEFER
- **Expected duration** — rough estimate
- **Explicitly OUT OF SCOPE** for this phase (prevents scope creep in both directions)

**Example**:
> **Phase 1: Pressure Scale Decomposition (1–2 hours)**
> - Goal: Compute convergence pressure at atomic and nuclear scales
> - Method: Use Φ = Nε and V_disp from PPT01 to calculate P at electron vs proton radii
> - Success: Pressure gradient dP/da within 1 order of magnitude of 1e10 Pa/m
> 
> **Phase 2: Topological Energy (1–2 hours)**
> - Goal: Derive energy cost of winding transitions
> - Method: Use kinetic energy m v_T² / 2 with v_T from PPT01 velocity budget
> - Success: Energy scale within 50% of 1e-20 J
> 
> **Phase 3: Numerical Verification (2–3 hours)**
> - Goal: Implement both scales in a standalone C++ tool
> - Method: Compute from first principles, compare against hardcoded values
> - Success: RMS error < 20%, no fitted parameters

### 5. Success Criteria (200–300 words)

**Purpose**: Define exactly what "done" looks like. Use the **canonical classification labels**.

**Must include**:
- **PASS (Class A: Derived)** — the best outcome
- **QUALIFIED (Class C: Convergence)** — good, with approximations
- **QUALIFIED PENDING (Class D: Computed)** — still useful, but not complete
- **FAIL (Class F)** — investigation didn't work

**Each level must have**:
- Quantitative metric (e.g., "within 20%", "no fitted parameters")
- What you'd publish at this level
- What needs to happen next

**Example**:
> ✅ **PASS**: Constants derived from Φ, F, m formulas alone. Match hardcoded values to ±20%. No fitted constants beyond CODATA 2018.
> 
> ✅ **QUALIFIED**: Constants derived with 1–2 approximations (e.g., neglecting relativistic corrections). Match to ±50%. Mark intermediate steps as CALIBRATED.
> 
> ⚠️ **QUALIFIED PENDING**: Constants traced to specific SDT laws. Match to ±1 order of magnitude. Physical interpretation incomplete.

### 6. Outputs (150–300 words)

**Purpose**: Be specific about what files the investigation will produce.

**Must include**:
- File names (**exact** — if renamed, ADJ entry required)
- Format (CSV, markdown, C++, etc.)
- What each contains
- **`RUN_LOG.md`** — mandatory for every run (see `PROMPT_EXECUTION_PROTOCOL.md`)

**Example**:
> 1. **CQ04_DERIVATION.md** — Step-by-step symbolic derivation from Laws I–IV
> 2. **cq04_scales_from_sdt.cpp** — Standalone C++20 tool computing both scales
> 3. **cq04_results.txt** — Table: [scale name | theoretical value | hardcoded value | % error]
> 4. **CQ04_VERDICT.md** — Classification (PASS / QUALIFIED / etc.) with reasoning

### 7. Dependencies & References (150–250 words)

**Purpose**: Locate this work within the landscape. What must be read first? What else depends on this?

**Must include**:
- **Upstream** — what CQ/E/Theory must be done first?
- **Downstream** — what can't start until this is done?
- **Related** — what should be read in parallel?

**Example**:
> **Upstream (Required)**:
> - PPT01: Velocity budget and R/a for each winding
> - Law III: Occlusion force definition
> - Law IV: Displacement volume and mass formula
> 
> **Downstream (Blocked)**:
> - PPT03: Mass ratio m_p/m_e (needs correct V_disp scaling)
> - GD01: Galaxy dynamics (needs correct phase transition scale)
> 
> **Related (Informative)**:
> - EMC01: Transfer function universality
> - NP09–NP11: Nuclear binding energies

### 8. Falsification Tests (150–250 words)

**Purpose**: Show how the investigation could fail. What would prove the hypothesis wrong?

**Must include**:
- 3–5 **specific tests** with predicted outcomes
- What observational or computational failure would mean
- How to recover if a test fails

**Example**:
> | Test | Hypothesis | Predicted Outcome | If FAIL |
> |------|-----------|------------------|--------|
> | T1 | T_5 is topological (depends on R/a only) | Derive from PPT01 geometry, match ±50% | T_5 depends on unknown parameter |
> | T2 | Phi_5 is kinetic (m v_T²) | Compute from m_e, v_T; match ±50% | Phi_5 has different physical basis |
> | T3 | Both are unique | Try alternative normalisations; none fit | Multiple valid scales exist (ambiguous) |

### 9. Implementation Notes (200–300 words)

**Purpose**: Practical advice for whoever codes this up.

**Should cover**:
- **Numerical stability** — watch for (overflow, underflow, division by zero)
- **Testing strategy** — how to verify intermediate results
- **Tool recommendations** — C++, Python, Mathematica?
- **Visualisation hints** — plots that would be informative

**Example**:
> Use **double precision** (C++ double, not loat). The scales span 60 orders of magnitude.
> 
> Implement **dimensionless ratios** to avoid absolute value overflow: (P_nuc / P_atom) not P_nuc alone.
> 
> Plot 1: T_5 vs (particle radius ratio) — check if curve is monotonic (topology-based) or jagged (empirical).
> 
> Plot 2: Phi_5 vs (v_T / c) — check if proportional to kinetic energy.

---

### ⑩ Adaptive Execution Protocol (300–600 words — MANDATORY)

**Purpose**: The plan must survive contact with numbers. Define **what may change** when a phase fails.

**Must include**:

1. **Pre-Run Commitment Block** (copy into `RUN_LOG.md` before coding):

```markdown
## Pre-Run Commitments — <ID>
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|…]
- CALIBRATED budget: [0 or list each param]
- Phase thresholds: [P1: …, P2: …, …]
- Forbidden retroactive changes: [list]
```

2. **Pivot table** — for each falsification test / phase failure, list:

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|-------------------|------------------------|----------------|--------------------|

3. **Allowed adjustments** — numerics, alternative native routes, phase splits

4. **Disallowed adjustments** — retro-PASS, PLUG, IDENTITY-PASS, borrow-smuggle

5. **Dual verdict reminder** — Prompt completion vs Physics class (see execution protocol)

**Example pivot row:**
> Phase 1 T1 FAIL (|n_water − n_pred| > 5%): **PIVOT** to bound-vortex z from `bridge::koppa_hydrogen` and `atomic::bohr_radius` — not to input `n=1.333`. If still >5%: **OPEN** matter-index mechanism; do not PASS Phase 1.

---

## How to Use This Template

### **To direct Claude to create an investigation:**

Copy this entire document and fill in each section with your specific problem. Example:

> You are the media specialist. Create the ultimate investigation for CQ07_Neutrino_Magnetic_Moment using the template at [url]. Key facts: neutrino has μ_ν ≡ 0 in SDT but standard model allows nonzero. Question: is there a measurement that will falsify one or the other?

### **To evaluate a PROMPT in the wild:**

Run through this checklist:
- [ ] Executive summary is <150 words and answers "why should we care?"
- [ ] Physical context includes ALL key variables with dimensions
- [ ] Theoretical framework uses ONLY SDT axioms (no borrowed terminology)
- [ ] Strategy has 3–5 concrete phases with quantitative success metrics
- [ ] Success criteria use canonical labels (A/C/D/F)
- [ ] Outputs list exact file names and formats
- [ ] Dependencies map upstream/downstream/related
- [ ] Falsification tests would actually disprove the hypothesis
- [ ] Implementation notes are actionable (not "test it good")
- [ ] §⑩ pivot table exists with numeric triggers
- [ ] Pre-run commitment block is copy-paste ready
- [ ] `RUN_LOG.md` listed in §⑥ outputs
- [ ] Dual verdict (prompt vs physics) specified in §⑤

---

**Validated against:** FLM10 (excessive detail + gates), CR10 (recursive pivot), FD01 (honest Class C demo), physics audit 2026-06-27.

**Status**: GOLD-STANDARD · inherits `PROMPT_EXECUTION_PROTOCOL.md` on every run.
