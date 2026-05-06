# CQ03: Fine Structure Constant from Topology — INVESTIGATION RESULTS

> **Status**: RESOLVED (NEGATIVE RESULT)
> **Date**: May 2026
> **Tool**: `cq03_fine_structure.cpp` (570 lines, 11/11 proofs pass)

---

## Question
Can α = 1/137.036 be derived from the W=1 torus geometry?

## Answer: NO

**α is NOT derivable from topology.** It is the electromagnetic coupling constant of an unknotted charge to the lattice. Its value requires the elementary charge e as an independent input.

### The Key Distinction

| Particle | g-number | Type | Meaning |
|----------|----------|------|---------|
| Proton (2,3 trefoil) | g = 4 = W+1 | Topological (integer) | Wake fixed by knot crossings |
| Electron (1,1 unknot) | g = α ≈ 1/137 | Electromagnetic (non-integer) | Wake fixed by charge coupling |

The proton's wake extends exactly 4 Compton lengths (topologically protected). The electron's wake extends only α Compton lengths (electromagnetically limited). The factor α/2 ≈ 1/274 between the actual and topological values IS the EM coupling.

### Circularity of All Derivation Attempts

Every attempt to extract α from SDT identities reduces to α = α:
- g-ratio: α = 4(r_e m_e)/(R_p m_p) — restates the g definitions
- Bohr: α = ℏ/(m_e ca₀) — a₀ contains α
- P_eff: α = (π/4)P_eff R⁴/(ℏc) — P_eff is defined from αℏc
- Lattice: substituting f into P_conv — all factors cancel to 1

### Input Hierarchy Conclusion

The minimal SDT input set is **{ℓ_P, T_CMB, e, d=3}**, not {ℓ_P, T_CMB, d=3}. Reducing to 3 inputs requires CQ10: Topological Charge Quantisation (deriving e from lattice defect structure).

## Proof Results (11/11 PASS)

| Proof | Description | Result |
|-------|-------------|--------|
| CQ03-1a | g_electron = α | **PASS** (exact) |
| CQ03-1b | α from Coulomb coupling | **PASS** (exact) |
| CQ03-1c | r_e = α²a₀ | **PASS** (exact) |
| CQ03-1d | r_e = αℏ/(m_e c) | **PASS** (exact) |
| CQ03-1e | g_proton ≈ 4 = W+1 | **PASS** (0.02%) |
| CQ03-2a | g_electron = α | **PASS** (exact) |
| CQ03-2b | g_proton ≈ 4 | **PASS** (0.02%) |
| CQ03-3a | α from g-ratio | **PASS** (0.02%) |
| CQ03-3b | α from Bohr radius | **PASS** (exact) |
| CQ03-3c | α from P_eff | **PASS** (exact) |
| CQ03-3d | α from radius/mass ratios | **PASS** (0.02%) |

## Verdict

**CQ03 RESOLVED (negative result).** α requires e. The charge quantum is an independent input. Forward dependency: CQ10.
