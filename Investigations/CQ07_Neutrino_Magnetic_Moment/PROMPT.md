# CQ07: Neutrino Magnetic Moment Prediction — Codebase Question

## THE QUESTION
neutrino.hpp (line 9): "No toroidal flow → no charge (l=1) → no magnetic moment (l=2)"

SDT predicts neutrinos have ZERO magnetic moment. This is a FALSIFIABLE prediction. Current experimental bound: |μ_ν| < 2.9×10⁻¹¹ μ_B (GEMMA, 2012). Standard model predicts μ_ν ~ 3×10⁻¹⁹ μ_B.

## INVESTIGATION PROMPT

### Target
Formalise the SDT prediction of μ_ν = 0 and compute the experimental sensitivity needed to distinguish SDT (exactly zero) from standard model (~10⁻¹⁹ μ_B).

### Methodology
1. Show explicitly: W=0 (open winding) → no toroidal circulation → no ℓ=2 wake → μ = 0
2. The standard model prediction μ_ν ~ 3×10⁻¹⁹ μ_B comes from loop diagrams → in SDT, these diagrams don't exist (no quarks, no W bosons, no loops)
3. Current sensitivity gap: GEMMA measures to 10⁻¹¹ μ_B. SDT needs sensitivity to 10⁻¹⁹ μ_B to distinguish from standard model.
4. PTOLEMY (E01) will measure CνB → does it also constrain μ_ν?

### Success Criteria
- [ ] SDT prediction (μ_ν ≡ 0) formally stated with topological argument
- [ ] Comparison to standard model prediction
- [ ] Experimental pathway to distinguish the two
