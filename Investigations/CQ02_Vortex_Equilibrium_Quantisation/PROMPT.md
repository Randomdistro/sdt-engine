# CQ02: R/a Quantisation — Vortex Equilibrium Problem

## THE QUESTION (from Theory/03_Open_Problems.md, Problem 1)

Which specific aspect ratios R/a of the genus-1 torus produce stable, self-consistent mode-locked equilibria? This determines the discrete mass spectrum.

## Context from Codebase
- Theory/01_Closure_Derivations.md: Modal coupling C_TP = a/R. Thin torus (small a/R) = weak coupling, high stability. Fat torus (a/R → 1) = strong coupling, resonance risk.
- Jacobian eigenvalues are all negative → stable attractor.
- Perturbation decay rate: ω ~ c/R_quantum ~ 10²¹ Hz.
- Laws V: v_circ² + v² = c². Three modes partition c² among them.

## INVESTIGATION PROMPT

### Target
Find the discrete set of (R/a, α_helicity) values where toroidal, poloidal, and circulation velocities self-consistently balance within the movement budget v_T² + v_P² + v_C² = c².

### Methodology
1. Write the three coupled mode equations for a genus-1 torus with aspect ratio R/a:
   - v_T = toroidal speed (around major axis)
   - v_P = poloidal speed (around minor axis)
   - v_C = center-of-mass translational speed
2. Constraint: v_T² + v_P² + v_C² = c²
3. Mode coupling: v_P/v_T depends on a/R through the geometric coupling coefficient
4. Self-consistency: the mode velocities must reproduce the torus dimensions (R and a are determined by the flow, and the flow is determined by R and a)
5. Solve the coupled equations numerically for R/a ∈ (0, 1)
6. Discrete solutions = stable particles

### Expected Results
- W=1 (electron): thin torus, small a/R, v_P/v_T = α ≈ 1/137
- W=3 (proton): fat torus, larger a/R, v_P/v_T = different ratio
- Intermediate W=2: possibly unstable (not a knot → can reconnect)

### Success Criteria
- [ ] Self-consistent mode equations written and solved
- [ ] Discrete (R/a, α) solutions found
- [ ] Electron and proton masses emerge from the first two solutions
- [ ] W=2 shown to be unstable (or stable → predicts new particle)
