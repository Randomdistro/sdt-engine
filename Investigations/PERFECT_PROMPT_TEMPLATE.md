# THE PERFECT INVESTIGATION PROMPT — A Template for Directing Claude

## What This Document Is

This is a **meta-guide**: a document that describes the structure and quality of an exemplary investigation prompt. Use this to:

1. **Review existing CQ/E investigations** — measure them against this standard
2. **Direct Claude to create new investigations** — copy this structure and fill in the blanks
3. **Improve vague research questions** into actionable investigations

---

## The Gold-Standard Structure

Every investigation PROMPT should have exactly these sections, in this order:

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

### 4. Investigation Strategy (600–800 words)

**Purpose**: Break the problem into concrete phases. A reader should be able to hand this to a programmer and get executable work.

**Must include**:
- **Phase 1, 2, 3, ...** — serial or parallel work blocks
- **For each phase**: Goal, Method, Success metric (quantitative!)
- **Expected duration** — rough estimate
- **Intermediate checkpoints** — when to verify, when to pivot

**Example**:
> **Phase 1: Pressure Scale Decomposition (1–2 hours)**
> - Goal: Compute convergence pressure at atomic and nuclear scales
> - Method: Use Φ = Nε and V_disp from CQ02 to calculate P at electron vs proton radii
> - Success: Pressure gradient dP/da within 1 order of magnitude of 1e10 Pa/m
> 
> **Phase 2: Topological Energy (1–2 hours)**
> - Goal: Derive energy cost of winding transitions
> - Method: Use kinetic energy m v_T² / 2 with v_T from CQ02 velocity budget
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

### 6. Outputs (100–200 words)

**Purpose**: Be specific about what files the investigation will produce.

**Must include**:
- File names (exact)
- Format (CSV, markdown, C++, etc.)
- What each contains

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
> - CQ02: Velocity budget and R/a for each winding
> - Law III: Occlusion force definition
> - Law IV: Displacement volume and mass formula
> 
> **Downstream (Blocked)**:
> - CQ05: Mass ratio m_p/m_e (needs correct V_disp scaling)
> - CQ06: Galaxy dynamics (needs correct phase transition scale)
> 
> **Related (Informative)**:
> - CQ01: Transfer function universality
> - E29–E31: Nuclear binding energies

### 8. Falsification Tests (150–250 words)

**Purpose**: Show how the investigation could fail. What would prove the hypothesis wrong?

**Must include**:
- 3–5 **specific tests** with predicted outcomes
- What observational or computational failure would mean
- How to recover if a test fails

**Example**:
> | Test | Hypothesis | Predicted Outcome | If FAIL |
> |------|-----------|------------------|--------|
> | T1 | T_5 is topological (depends on R/a only) | Derive from CQ02 geometry, match ±50% | T_5 depends on unknown parameter |
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

---

## The Golden Rule

**Every investigation prompt must answer these five questions in the first two pages:**

1. **What don't we know?** (the gap)
2. **Why does it matter?** (the stakes)
3. **How will we find out?** (the method)
4. **What would prove us wrong?** (the falsification)
5. **How will we know we're done?** (the success metric)

If a prompt doesn't clearly answer all five, it's not ready to hand to an investigator.

---

**This template was validated against:**
- CQ01, CQ02, CQ04 (exemplary prompts in sdt-engine)
- E29–E31 (successful experimental derivations)
- Industry research standards (ARPA-E, DoE reviews)

**Status**: GOLD-STANDARD TEMPLATE FOR ALL FUTURE INVESTIGATIONS
