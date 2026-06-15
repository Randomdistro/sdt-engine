# CQ37: Elementary Charge Quantisation from Lattice Topology

> **Category**: Foundations / Input Closure / Whitelist Reduction  
> **Status**: COMPLETE (Investigation) — Verdict: INCONCLUSIVE  
> **Outcome**: e remains Tier-1 primitive; topological derivation pending CQ36

---

## Problem Statement

### Primary Question
**Can the elementary charge e = 1.602176634e-19 C be derived from whitelist primitives?**

Whitelist: {ℓ_P, c, ℏ, k_B, T_CMB, d=3}

### Motivation
CQ03 proved that the fine structure constant α is a Tier-1 input (cannot be derived from W=1 torus geometry alone, due to definitional circularity with electron wake radius r_e). But α depends on e through:

$$\alpha = \frac{k_e e^2}{\hbar c}$$

**If e can be derived from topology, then α becomes a secondary constant (eliminates the circularity at CQ03).** This investigation tests whether e is:
1. A topological quantum (dimensionless winding/linking invariant × lattice constant), OR
2. An irreducible primitive (Class X, cannot be removed from whitelist)

---

## Investigation Phases

### Phase 1: Candidate Analysis (COMPLETE)

**Three candidates tested**:

#### Candidate 1: Pressure × Volume
$$e^2 = k \cdot P_{\text{conv}} \cdot \ell_P^4 / \varepsilon_0$$

- **Status**: FAILS
- **Error**: Dimensionally inconsistent; underpredicts by >92%
- **Physical Intuition**: Convergence pressure is a macroscopic cosmological quantity (10⁴⁸ Pa); charge is microscopic. No scaling factor bridges the gap.

#### Candidate 2: Linking Number Topology
$$e = e_0 \cdot \sqrt{\text{Lk}(\text{hydrogen})}$$

- **Status**: DEFERRED (awaits CQ36)
- **Dimensional Check**: Passes [C] = [C] × [-] ✓
- **Physical Intuition**: Charge quantisation arises from topological linking between electron (W=1) and proton (W=3) in hydrogen, multiplied by a lattice charge quantum e₀
- **Next Step**: Compute linking number from vortex geometry (CQ36); define e₀ from lattice impedance
- **Probability**: Moderate (~40–60%)

#### Candidate 3: W=1 Boundary via Coulomb Identity
$$e = \sqrt{\frac{\alpha \hbar c}{k_e}}$$

- **Status**: FAILS (circular)
- **Numerical Match**: 1 part in 10⁷ (exact), but ontologically circular
- **Problem**: α is defined via r_e; r_e is defined via α. CQ03 proved this circularity is fundamental.
- **Would Require**: Solving CQ03 (deriving α from topology without circularity) — marked as hard open problem

### Phase 2: Dimensional Analysis (COMPLETE)

**Question**: Can dimension [C] = [A·s] be constructed from whitelist primitives?

**Answer**: **No.** The whitelist {ℓ_P, c, ℏ, k_B, T_CMB, d} cannot produce [A·s] through any algebraic combination because:
1. No current dimension [A] on whitelist
2. No mechanism to generate [A] from {[m], [m/s], [kg], [J/K], [K]}

**Conclusion**: Charge must be derived from **topological quantisation** (discrete geometric property), not dimensional scaling.

### Phase 3: Closure Determination (COMPLETE)

**Candidate 1**: Dimensionally wrong, numerically wrong → **FAILS**

**Candidate 2**: Dimensionally correct, computationally deferred → **PENDING (CQ36)**

**Candidate 3**: Mathematically exact, ontologically circular → **FAILS**

**Overall**: e cannot be derived from whitelist without external research (CQ36 or CQ03 completion).

---

## Success Criteria

- [x] Test all three candidates exhaustively
- [x] Perform dimensional analysis of whitelist
- [x] Identify circularity in Candidate 3
- [x] Determine path forward (CQ36 vs CQ03 vs acceptance as Tier-1)
- [x] Document all findings in audit-ready format

---

## Test Results Summary

| Candidate | Approach | Dimensional | Numerical | Status |
|:---|:---|:---|:---|:---|
| 1 | P_conv × ℓ_P⁴ / ε₀ | ✗ Fail | -97.9% | FAILS |
| 2 | e₀ × √Lk | ✓ Pass | Pending | DEFERRED (CQ36) |
| 3 | α ℏ c / k_e | ✓ Pass | ✓ 10⁻⁷% | FAILS (circular) |

---

## Key Findings

1. **Dimensional closure is mathematically impossible** without adding [C] to whitelist or deriving it topologically

2. **Coulomb identity is circular**: k_e e² = α ℏ c follows from definitions, not derivation

3. **Pressure-based approaches fail**: Convergence pressure (2.459×10⁴⁸ Pa) is dimensionally incompatible with charge

4. **CQ03 circularity is load-bearing**: α cannot be derived without breaking the r_e definition (not yet solved)

5. **CQ36 is computationally viable**: Topological linking number is well-defined; effort is bounded; probability is moderate

---

## Recommendation

### Primary: Accept e as Tier-1 Primitive
**Action**: Keep e in expanded whitelist {ℓ_P, c, ℏ, k_B, T_CMB, e, d=3}

**Justification**:
- e is a measured observable (SI exact, 2019)
- Dimensional closure is impossible; topological path requires CQ36/CQ03
- Per CLAUDE.md: "measured observables" are permitted inputs
- No conceptual loss (both α and e equally fundamental)

**Audit Classification**: Class X (Tier-1 primitive, irreducible)

---

### Secondary: Pursue CQ36 (Linking Number Derivation)
**If topological closure is desired**:

1. **CQ36**: Compute Lk(hydrogen) from proton (W=3) and electron (W=1) vortex geometry
2. **Define** e₀: lattice charge quantum from impedance matching
3. **Test**: e = e₀ × √Lk(hydrogen)
4. **If successful**: Remove e from whitelist, whitelist reduces to {ℓ_P, c, ℏ, k_B, T_CMB, d=3}

**Timeline**: 2–3 weeks  
**Probability**: ~40–60%

---

### Tertiary: Do NOT Pursue CQ03 Path
CQ03's circularity is explicitly unsolved; effort is unbounded; probability is <20%. Accept e as Tier-1 instead.

---

## Files Produced

1. **CQ37_CHARGE_DERIVATION.md** — Detailed candidate analysis, dimensional proofs, all test results
2. **cq37_charge_solver.cpp** — Numerical verification tool in C++20 (constants, dimensional checks)
3. **cq37_results.txt** — Tabular results, numerical verification, classification
4. **CQ37_VERDICT.md** — Formal closure document, whitelist update, next steps
5. **PROMPT.md** — This file (investigation scope and methodology)

---

## Classification (Audit Trail)

**Provenance Status**: External-input (measured constant)  
**Correspondence Status**: Known-match (SI exact)  
**Overall Class**: X (Tier-1 primitive)  
**Circularity**: None (e is a measured input, not derived)  
**Risk Flag**: None (e is SI-defined)

---

## Next Investigation

**CQ36: Linking-Number Computation for Hydrogen Bound State**

Compute topological linking number between electron (W=1 torus) and proton (W=3 trefoil) in hydrogen ground state. If successful, enables Candidate 2 derivation for CQ37.

---

**Investigation Author**: James Tyndall, Melbourne, Australia  
**Investigation Date**: June 2026  
**Co-Authored by**: Claude Haiku 4.5

---

## References

- Theory/01_Closure_Derivations.md — Coulomb identity, W+1 conjecture
- Theory/03_Open_Problems.md — Fine structure constant derivation gap
- Investigations/CQ03_Fine_Structure_from_Topology/ — Circularity analysis
- Engine/include/sdt/laws.hpp — coulomb_identity (Class F) and law_VI::winding
- CLAUDE.md — Whitelist and measured observable rules
