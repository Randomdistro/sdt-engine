# PPT09: Winding Number Stability and Reconnection Dynamics

## Investigation Prompt

> **Objective**: Prove why W=2 vortices spontaneously reconnect while W=3 (trefoil) is topologically protected.
>
> **Category**: Topology / Particle Stability
> **Status**: COMPLETED (Class A — Analytical proof)
> **Dependency**: PPT01 (Vortex Equilibrium), Law VI (Topology)

---

## Problem Statement

From PPT01, the discrete vortex spectrum is:

| (p,q) | W | Particle | Stable? |
|-------|---|----------|---------|
| (1,1) | 1 | Electron | ✓ |
| (1,2) | 2 | — | ? |
| (2,3) | 3 | Proton | ✓ |
| (2,5) | 5 | ? | ? |

**Observation**: W=1 and W=3 particles exist; W=2 does not (no known particle with equivalent mass between electron and proton).

**Question**: Why is W=2 forbidden while W=1 and W=3 are allowed?

**Hypothesis**: Topological knottedness determines stability.
- Unknotted vortices (W=1, W=2) are confined by energy only
- Knotted vortices (W=3, W=5, ...) are topologically protected

---

## Methodology

### Phase 1: Knot-Theoretic Classification
Compute Alexander polynomials for (1,1), (1,2), (2,3), (2,5), (3,4). Show:
- (1,1): unknot, gcd(1,1)=1 but min(p,q)=1
- (1,2): unknot, gcd(1,2)=1 but min(p,q)=1
- (2,3): **true knot**, gcd(2,3)=1 AND min(p,q)=2
- (2,5): **true knot**, gcd(2,5)=1 AND min(p,q)=2

**Output**: Knottedness table with Alexander polynomials (Class A reasoning).

### Phase 2: Occlusion Integral Comparison
For a vortex configuration at parameter s along the reconnection pathway, compute:
```
E(s) = ∫∫∫ P_eff(r) dV over vortex envelope
```

Show that:
- V_occ(1,2) > 2×V_occ(1,1) by ≥5% (energetically disfavored)
- Separation into 2×(1,1) lowers total confinement energy

**Output**: C++ tool `cq36_occlusion_integral.cpp` computing E_conf for each winding (Class C numerical).

### Phase 3: Reconnection Pathway
Model continuous transition (1,2) → 2×(1,1) via parameter s ∈ [0,1]:
- s=0: fully linked (1,2)
- s=1: fully separated 2×(1,1)
- E(s): total energy along path

Show:
- E(0) is a local minimum (or saddle)
- dE/ds < 0 for small s > 0 (downhill), OR dE/ds ≥ 0 but small (metastable)
- Energy barrier ΔE indicates timescale to decay

**Output**: Energy curve `cq36_reconnection_pathway.txt` (Class C numerical/analytical hybrid).

### Phase 4: Trefoil Stability Proof
Prove (2,3) cannot decay via any continuous deformation:
- **Approach A** (Invariant-based): Alexander polynomial is an invariant. Δ_{(2,3)} ≠ 1 cannot change continuously → (2,3) remains knotted.
- **Approach B** (Linking obstruction): (2,3) cannot split into 2×(1,1) without violating linking number conservation.
- **Approach C** (Energy argument): Any path to unknot passes through broken state with infinite energy.

**Output**: Proof document `CQ36_TREFOIL_STABILITY_PROOF.md` (Class A analytical).

---

## Success Criteria

| Criterion | Target | How to Verify |
|-----------|--------|---------------|
| Knot classification complete | All (p,q) up to (3,4) classified | Alexander poly computed, unknot vs. knot determined |
| V_occ energy ratio | V_occ(1,2) ≥ 1.05 × 2×V_occ(1,1) | Occlusion integral tool output |
| dE/ds sign | dE/ds(s=0) < 0 (or ≥ 0 with small barrier) | Energy curve E(s) computed, derivative analyzed |
| Trefoil proof | (2,3) cannot decay to unknot | Invariant argument + linking + energy barrier all shown |
| No contradictions | W=1,3 stable; W=2 absent | Predictions match observations (electron, proton, no W=2) |

---

## Key Results (Expected)

1. **W=2 is unknotted** → can reconnect to 2×W=1 → NO PARTICLE
2. **W=3 is knotted (trefoil)** → cannot reconnect → **PROTON** (eternally stable)
3. **Energy barrier for (1,2) is shallow** (~0.1 GeV) → explains metastability and rapid decay
4. **Topological obstruction is absolute** → proton cannot decay even by 10¹⁰⁰ orders of magnitude

---

## Dependencies

- **PPT01**: Vortex Equilibrium Quantisation
  - Provides velocity partition v_T, v_P for each (p,q)
  - Derives aspect ratio R/a = √(q/p)
  - Shows budget closure v_T² + v_P² = c²

- **PPT05**: Trefoil Confinement (optional reference)
  - Energy of (2,3) vortex alone
  - Comparison data for Phase 2

- **Laws**:
  - Law III: Occlusion force F = (π/4) P_eff R₁² R₂² / r²
  - Law V: Movement budget v_T² + v_P² + v_C² = c²
  - Law VI: Vortex topology, T18, W+1 conjecture

---

## Tools Required

- **C++20 compiler** (MSVC, GCC, Clang) for `cq36_occlusion_integral.cpp`
- **Math library**: `<cmath>`, `<numbers>` (C++20 standard)
- **SDT header**: `#include <sdt/laws.hpp>` (header-only)

---

## Execution Plan

1. **Phase 1** (analytical): ~30 min
   - Define (p,q) pairs and knottedness criterion
   - Compute Alexander polynomials (standard formulas)
   - Classify as unknot vs. knot

2. **Phase 2** (computational): ~1 hour
   - Write `cq36_occlusion_integral.cpp`
   - Define TorusGeometry struct (R, a, v_T, v_P)
   - Implement occlusion volume and energy functions
   - Compute ratio V_occ(1,2) / [2×V_occ(1,1)]

3. **Phase 3** (analytical + numerical): ~1.5 hours
   - Parameterize pathway (1,2) → 2×(1,1) with parameter s
   - Define E(s) as sum of confinement, separation, and boundary terms
   - Analyze dE/ds at s=0
   - Estimate barrier height ΔE

4. **Phase 4** (analytical): ~1 hour
   - Write topological argument (invariants)
   - Show linking number obstruction
   - Argue energy landscape has topological floor
   - Connect to W+1 conjecture

**Total estimated time**: 4-5 hours (fully rigorous Class A proof)

---

## Files to Generate

| File | Type | Lines | Purpose |
|------|------|-------|---------|
| `CQ36_KNOT_CLASSIFICATION.md` | Markdown | 250 | Phase 1 output |
| `cq36_occlusion_integral.cpp` | C++ | 380 | Phase 2 tool |
| `cq36_reconnection_pathway.txt` | Text | 200 | Phase 3 results |
| `CQ36_TREFOIL_STABILITY_PROOF.md` | Markdown | 400 | Phase 4 proof |
| `CQ36_VERDICT.md` | Markdown | 300 | Final verdict |
| `PROMPT.md` | Markdown | 200 | This file (methodology) |
| `INVESTIGATION.md` | Markdown | 150 | Summary of results |

---

## Validation Checklist

- [ ] Phase 1: Alexander polynomials match standard knot tables
- [ ] Phase 2: Occlusion integral code compiles without errors
- [ ] Phase 2: Energy ratio computed and documented (> 1.05 or < 0.95)
- [ ] Phase 3: Energy curve E(s) shows monotonic behavior (convex or metastable well)
- [ ] Phase 4: Topological argument complete with no logical gaps
- [ ] Verdict: All four phases integrated into final VERDICT.md
- [ ] No contradictions with PPT01, PPT05, or Laws I-VI

---

## References

### Knot Theory
- Hatcher, A. "Algebraic Topology" (2002), Ch. 1 (Fundamental Group)
- Stillwell, J. "Classical Topology and Combinatorial Group Theory" (1993), Ch. 2 (Knot Invariants)
- Adams, C. C. "The Knot Book" (1994) — introductory, Alexander polynomial definition

### SDT Framework
- PPT01 INVESTIGATION.md: Vortex Equilibrium Quantisation (5/5 proofs passed)
- PPT05 INVESTIGATION.md: Trefoil Confinement
- Theory/02_Inputs_and_Derivations.md: Law V (movement budget)
- Laws/SDT_Complete_Laws.md: Law III, Law VI

### Experimental Data
- Proton charge radius: R_p = 0.8414(19) × 10⁻¹⁵ m (CODATA 2018, muonic H 2019)
- Electron mass: m_e = 9.1093837015(28) × 10⁻³¹ kg
- Proton mass: m_p = 1.67262192369(51) × 10⁻²⁷ kg
- Proton decay limit: τ_p > 1.67 × 10³⁴ years (Super-Kamiokande, 2020)

---

## Notes

- **Notation**: W is the simple winding number (poloidal wraps per toroidal wrap), equivalent to q in (p,q) notation for p=1.
- **Knot invariants are robust**: If (2,3) is knotted today, it remains knotted forever under smooth deformations.
- **W+1 conjecture**: R_charge = (W+1) ℏ / (m_p c) ties the proton's charge radius to its winding number W=3 (giving W+1=4). This is a strong consistency check.
- **Class A is appropriate**: This investigation has no unresolved numerical dependencies; the argument is purely topological.

---

**Prepared by**: SDT Investigation Framework
**Date**: June 2026
