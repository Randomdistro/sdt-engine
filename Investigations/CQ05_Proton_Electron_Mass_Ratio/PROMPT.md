# CQ05: Proton-Electron Mass Ratio Derivation — Codebase Question

## THE QUESTION (from Theory/03_Open_Problems.md, Problem 4 + laws.hpp line 636)

m_p/m_e = 1836.15. The codebase notes this is approximately (3/2)^(3/2) × 10³ = 1837.12 (0.053% off).

Can this ratio be derived from the W=3 vs W=1 equilibrium?

## Context
- Electron: W=1, simple torus, g(W=1) = α ≈ 1/137
- Proton: W=3, trefoil, g(W=3) = 4
- Mass from SDT: m = Φ V_disp / (3 l_P³ c²)
- So m_p/m_e = V_disp_p / V_disp_e

## INVESTIGATION PROMPT

### Target
Derive m_p/m_e = 1836.15 from the ratio of W=3 to W=1 equilibrium displacement volumes.

### Approach 1: Vortex volume scaling
V_disp should scale with the torus volume = 2π²Rar². For different R/a at each W:
- V_disp(W=1) = 2π² R₁ a₁² 
- V_disp(W=3) = 2π² R₃ a₃²
- m_p/m_e = (R₃ a₃²) / (R₁ a₁²)

This requires the R/a equilibrium from CQ02.

### Approach 2: Mode energy scaling
The total circulation energy at each W equilibrium:
- E(W=1) = ½ m_e c² (all as rest energy)
- E(W=3) = ½ m_p c²
- Ratio = how the movement budget partitions differently for W=1 vs W=3

### The (3/2)^(3/2) conjecture
(3/2)^(3/2) = √(27/8) = 1.8371. The factor ~1000 could be:
- (W+1)^n = 4^n for some n?
- α^(-1) × (W-dependent factor)?

### Success Criteria
- [ ] m_p/m_e reproduced within 1% from vortex equilibrium
- [ ] The factor ~1836 decomposed into W-dependent and topology-dependent parts
- [ ] If exact: this eliminates m_p as an independent input (derivable from m_e and W)
