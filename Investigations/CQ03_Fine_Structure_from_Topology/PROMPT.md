# CQ03: Fine Structure Constant from Topology — Codebase Question

## THE QUESTION (from Theory/03_Open_Problems.md, Problem 3)

Can α = 1/137.036 be derived from the W=1 torus geometry?

## Context from Codebase
- Theory/01_Closure: α = v_P/v_T at the W=1 equilibrium
- winding namespace: g_electron = r_e × m_e × c / ℏ = α (exact)
- The electron's wake-to-quantum ratio IS α
- Conjecture: α is the geometric ratio of poloidal to toroidal circulation at the simplest stable torus

## INVESTIGATION PROMPT

### Target
Prove or disprove: α = v_P / v_T for the W=1 equilibrium torus.

### Methodology
1. From CQ02's mode equations, extract v_P/v_T at the W=1 solution
2. If v_P/v_T = 1/137.036: α is DERIVED, eliminating it as an independent input
3. The terminal input set then becomes: ℓ_P, T_CMB, d=3 (three spatial dimensions)

### What This Would Mean
If α is derivable from topology, SDT reduces its input count from 6 to 3. The independent inputs become:
- ℓ_P (lattice scale)
- T_CMB (lattice energy)
- d = 3 (spatial dimensionality)

Everything else — m_e, m_p, α, R_p — would be DERIVED from the equilibrium conditions of genus-1 tori in a d=3 lattice.

### Success Criteria
- [ ] v_P/v_T computed for the W=1 equilibrium
- [ ] If = α within 1%: strong evidence for derivability
- [ ] If ≠ α: identify what additional ingredient is needed
- [ ] Calculate sensitivity: dα/d(R/a) — how precisely must R/a be known?
