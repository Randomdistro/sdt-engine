# E30: Alpha Binding from Tetrahedral Occlusion — Investigation Prompt

> **Classification**: Pure calculation (depends on E29)
> **Experiment file**: Experiments/E30_Alpha_Binding.md
> **Target**: Reproduce B_α = 28.296 MeV from tetrahedral packing

---

## 1. The Question

He-4 (the alpha particle) has binding energy 28.296 MeV — anomalously large compared to its neighbours. SDT describes it as a tetrahedral arrangement of 2 protons + 2 neutrons, forming 6 occlusion bonds (every nucleon bonded to every other). Can the total occlusion energy of this tetrahedral geometry reproduce 28.296 MeV?

## 2. Methodology

### Step 1: Tetrahedral geometry

Place 4 nucleons at the vertices of a regular tetrahedron. The edge length d is determined by equilibrium between:
- Attractive ℓ≥3 occlusion (inward)
- Repulsive centrifugal pressure from circulation (outward)
- For the two protons: repulsive ℓ=1 Coulomb

The measured He-4 charge radius (1.6755 fm) constrains d:
- R_charge = d × √(3/8) → d ≈ 2.73 fm for the tetrahedron edge
- OR: R_charge = 2R_p → d is the proton-proton distance ≈ 2R_p × √(8/3)

### Step 2: Count bonds and compute total energy

6 bonds in a tetrahedron:
- 4 × p-n bonds (each at distance d)
- 1 × p-p bond (distance d, with Coulomb repulsion reducing the net)
- 1 × n-n bond (distance d, pure occlusion)

Total binding = 4×E_pn + 1×(E_pp − E_Coulomb) + 1×E_nn

Where:
- E_pn = occlusion bond energy from E29
- E_pp = same occlusion, minus Coulomb repulsion
- E_nn = occlusion between two neutrons (no Coulomb)
- E_Coulomb = k_e e²/d = 1.44 MeV·fm / d

### Step 3: Consistency checks

1. Does 4×E_pn + E_nn + (E_pp − E_C) = 28.296 MeV?
2. Is B_alpha / 6 ≈ 4.72 MeV per bond reasonable compared to B_d = 2.224 MeV per bond? (Yes if closer packing → stronger occlusion)
3. Does the predicted R_He = 2R_p (1.683 fm) match measured 1.6755 fm? (0.43% — already in laws.hpp)
4. Does the tetrahedral symmetry explain μ_alpha = 0 (all magnetic moments cancel)?

### Step 4: Hierarchy test

Compute from the same geometry:
- B(He-3) = 3 p-n bonds + 0 p-p + ... (only 3 nucleons — triangle)
- B(H-3) = 3 p-n bonds (triangle geometry)
- Compare predicted ratio B_alpha / B_triton to measured 28.296 / 8.482 = 3.34

## 3. Success Criteria

- [ ] Total binding energy predicted within 20% of 28.296 MeV
- [ ] R_He predicted within 1% of measured
- [ ] μ_alpha = 0 explained by tetrahedral symmetry
- [ ] B_alpha / B_triton ratio reproduced
- [ ] Bond energy per edge is self-consistent with E29 deuteron result
