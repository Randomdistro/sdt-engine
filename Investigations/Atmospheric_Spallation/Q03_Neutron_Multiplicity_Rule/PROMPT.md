# Q03: Neutron Multiplicity Rule — Investigation Prompt

> **Classification**: Theoretical derivation with systematic archival test
> **Prerequisites**: Q01, Q02, nuclear construction grammar
> **Output format**: Quantitative rule with verification against EXFOR data

---

## 1. Background

When a proton of energy T_p strikes a target nucleus (Z, A), the number
of neutrons ejected (the "multiplicity" x in the (p,xn) channel) depends
on the incident energy and the target properties. Conventional nuclear
physics describes this through:

1. **Compound nucleus evaporation**: The excitation energy E* = T_p + Q
   is shared among all nucleons. Neutrons evaporate one at a time, each
   carrying away ~2T MeV (where T = E*/a, a = A/8 MeV⁻¹). The number
   ejected ≈ E* / (S_n + 2T). This is a fitted statistical model.

2. **Intranuclear cascade**: At higher energies (> 200 MeV), the proton
   undergoes a cascade of binary nucleon-nucleon collisions inside the
   nucleus, directly ejecting fast neutrons before the compound
   equilibrates. The remaining excitation then evaporates additional
   slow neutrons.

SDT must replace BOTH descriptions with a geometric rule that predicts
multiplicity from first principles — from the scaffold grammar, the
projectile's k-number, and the target's shell structure.

---

## 2. The Core Question

**Given a target nucleus described by its construction grammar (α core +
d blocks + t blocks) and an incident proton with k-number k = c/v,
what geometric rule determines the exact number of neutrons ejected?**

Sub-questions:

1. Is the multiplicity simply the number of "open" neutrons (n_o from
   triton blocks) that are geometrically accessible to the projectile?
2. Does the multiplicity scale with the triton fraction (n_t / (n_d + n_t))?
3. Is there a threshold energy per neutron that corresponds to a specific
   scaffold bond energy in SDT?
4. Do shell closures (magic numbers) create "rigid" scaffolds that resist
   multiple neutron ejection?
5. Does the neutron skin thickness (excess neutrons at the nuclear surface)
   directly determine the multiplicity ceiling?

---

## 3. Methodology

### Phase A: Sequential ejection energy analysis

For the canonical target Ga-69 (Z=31, N=38):

1. Look up sequential neutron separation energies from AME2020:
   - S_1n(Ga-69): energy to remove the 38th neutron
   - S_2n(Ga-69→Ga-68→Ga-67): cumulative energy for 2 neutrons
   - S_3n, S_4n, etc.

2. Compute the grammar at each step:
   - Ga-69: compute d, t, n_tri, n_deu
   - Ga-68 (−1n): recompute grammar. Which block lost a neutron?
     If a triton lost its n_o → becomes a deuteron (t→d)
     If a deuteron lost its neutron → becomes a bare proton (impossible
     in stable scaffold? Or does it immediately restructure?)
   - Ga-67 (−2n): recompute grammar

3. Map the separation energy jumps to grammar transitions:
   - Does S_1n correspond to removing n_o from the outermost triton?
   - Does S_2n show a discontinuity if the 2nd removal hits a
     different block type?
   - Do the separation energy jumps align with shell boundaries
     identified by ionisation energy discontinuities (INV 17 §7)?

### Phase B: Systematic correlation search

For ALL targets where (p,xn) data exists in EXFOR (minimum 50 targets):

1. Tabulate: Z, A, N, n_d, n_t, n_tri, n_deu, triton fraction,
   number of open neutrons n_o

2. For each target, record: maximum observed multiplicity x_max
   at T_p = 200 MeV (standardised comparison energy)

3. Plot and correlate:
   - x_max vs n_o (open neutron count)
   - x_max vs triton fraction
   - x_max vs N − Z (neutron excess)
   - x_max vs N mod magic (distance from shell closure)
   - x_max vs nuclear deformation β₂

4. Identify which SDT parameter provides the tightest correlation
   with multiplicity

### Phase C: Threshold energy rule

For each (p,xn) channel on each target:

1. Compute the threshold energy from SDT:
   - Each neutron ejection requires overcoming the ℓ≥3 scaffold bond
   - The first n_o neutrons should require LESS energy (fewer bonds)
   - The n_c neutrons should require MORE energy (scaffold bridge bond
     must break)
   - Predict: E_threshold(x) = Σᵢ₌₁ˣ E_bond(nᵢ), where E_bond depends
     on whether nᵢ is n_o or n_c

2. Compare SDT-predicted thresholds against measured thresholds from EXFOR

3. If the SDT thresholds match within measurement uncertainty, this
   confirms the geometric bond model

### Phase D: Shell closure rigidity test

At magic numbers (N = 20, 28, 50, 82, 126), the scaffold is expected
to be maximally rigid (minimum triton fraction? maximum deuteron pairing?
full shell closure in grammar?)

Test:
1. Do targets at or near magic N show LOWER multiplicity at fixed energy
   compared to mid-shell targets?
2. Is the multiplicity suppression at magic N quantitatively predicted
   by the grammar (all-deuteron scaffolds at magic N should have NO
   open neutrons)?
3. Does the multiplicity jump when crossing a magic number (e.g., going
   from N=50 to N=51, does the first triton appear, creating the first
   n_o)?

### Phase E: Derive the multiplicity formula

From Phases A–D, synthesise a single formula:

$$x_{\\text{max}}(E, Z, A) = f(\\text{grammar parameters}, k_{\\text{projectile}})$$

This formula must:
- Use ONLY SDT-permitted quantities (no fitted parameters from
  conventional nuclear physics)
- Reproduce the measured x_max for all tested targets within ±1 neutron
- Correctly predict the energy threshold for each channel opening
- Reduce to x = 0 below the (p,1n) threshold
- Predict new multiplicity values for targets not yet measured

---

## 4. Required Outputs

1. **Sequential grammar table**: For Ga-69, Y-89, Pb-208 — show the
   grammar state after removing 1, 2, 3, 4, 5 neutrons sequentially.
   Identify which block type loses a neutron at each step.

2. **Correlation matrix**: A table showing the Pearson correlation between
   x_max(200 MeV) and: n_o, triton fraction, N−Z, β₂, distance from
   magic N. Identify the dominant predictor.

3. **Threshold comparison table**: For 10 canonical targets, compare
   SDT-predicted (p,xn) threshold energies against EXFOR measurements.

4. **Multiplicity formula**: A closed-form expression for x_max(E, Z, A)
   using only grammar parameters.

5. **Prediction table**: Multiplicity predictions for 5 targets where
   EXFOR data exists but was NOT used in the derivation (holdout test).

---

## 5. Success Criteria

- [ ] The multiplicity formula uses only SDT-permitted quantities
- [ ] The formula reproduces x_max to within ±1 across at least 20 targets
- [ ] Threshold energies are predicted to within 20% of EXFOR values
- [ ] Shell closure effects are correctly captured by grammar properties
- [ ] The holdout test confirms ≥4 out of 5 predictions within ±1
- [ ] The formula explains why heavier targets produce more neutrons
      (more tritons → more n_o → more accessible ejection channels)
