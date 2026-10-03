# A02: Neutron Multiplicity vs Energy Scaling — Investigation Prompt

> **Classification**: Archival data analysis
> **Prerequisites**: A01 (grammar audit), excitation function data from EXFOR
> **Output format**: Correlation analysis with SDT scaling law proposal

---

## 1. Objective

Determine whether SDT grammar parameters (triton count, open neutron
count, triton fraction, shell closure proximity) can predict the neutron
multiplicity in (p,xn) spallation reactions as a function of incident
proton energy, WITHOUT using fitted parameters from conventional
nuclear physics (level density parameter, optical model potentials, etc.).

---

## 2. Scope

For a systematically chosen set of 20 targets spanning Z=13–83
(see DATA_REQUIREMENTS.md for the full list), collect all available
(p,xn) excitation function data from EXFOR and test whether the
following SDT quantities predict:

1. The THRESHOLD ENERGY for each (p,xn) channel
2. The PEAK CROSS-SECTION of each channel
3. The MAXIMUM MULTIPLICITY at any given energy
4. The AVERAGE MULTIPLICITY <ν> at standardised energies (200 MeV,
   800 MeV, 1.4 GeV)

---

## 3. Methodology

### Phase A: Data collection and tabulation

For each of the 20 targets:

1. Download all (p,xn) excitation functions from EXFOR (x = 1 to max)
2. For each channel, extract: E_thr, E_peak, σ_peak, FWHM
3. Tabulate the target grammar parameters: n_d, n_t, n_tri, n_deu,
   triton fraction, n_o, |N − N_magic|, β₂, R_nuc, S_n, S_2n

### Phase B: Threshold energy correlations

For each channel opening (x = 1,2,3,4,...):

1. Plot E_thr(p,xn) vs the cumulative SDT ejection cost:
   - SDT hypothesis: E_thr(x) = Σᵢ₌₁ˣ E_bond(nᵢ)
   - Where E_bond(n_o) = ℓ≥3 coupling only (lower)
   - And E_bond(n_c) = ℓ≥3 coupling + scaffold bridge (higher)
   - First approximation: E_bond ≈ S_n from AME2020

2. Correlate E_thr with grammar parameters:
   - Does E_thr scale with triton fraction? (more tritons → lower per-
     neutron cost for the first few ejections, because n_o are cheap?)
   - Does E_thr jump at shell closures? (magic N → all neutrons are
     tightly bound → high threshold?)
   - Does E_thr correlate with n_deu? (more deuterons → more rigid
     scaffold → higher threshold?)

3. Compute correlation coefficients (Pearson r, Spearman ρ) for each
   candidate predictor

### Phase C: Peak cross-section correlations

For the dominant channel at E = 40 MeV:

1. Plot σ_peak vs target grammar parameters
2. Hypothesis: σ_peak ∝ n_o (more open neutrons → larger probability
   of ejection → larger cross-section)
3. Alternative: σ_peak ∝ R_nuc² (purely geometric — larger nucleus →
   larger cross-section)
4. Test: is grammar (n_o) a better predictor than geometry (R²)?
   Compute both correlations and report which is tighter.

### Phase D: Maximum multiplicity at fixed energy

At E_p = 200 MeV (standard comparison point):

1. For each target, determine x_max (the highest channel with
   measurable cross-section, σ > 0.1 mb)
2. Plot x_max vs:
   - A (mass number) — conventional scaling
   - N (neutron number) — neutron availability
   - n_o (open neutron count) — SDT grammar prediction
   - n_t (total triton count) — SDT grammar prediction
   - N − N_magic (distance from magic) — shell effect

3. Fit each: x_max = a × (predictor) + b
4. Report R² for each fit
5. Identify which predictor explains the most variance

### Phase E: The SDT scaling law

From Phases B–D, propose a unified formula:

$$\\langle\\nu\\rangle(E, Z, A) = f(n_o, n_t, S_n, E)$$

Requirements:
- Must use ONLY grammar-derived quantities (not level density, not
  optical model)
- Must reduce to zero below threshold
- Must saturate at high energy (can't eject more neutrons than exist)
- Must show shell closure effects (reduced ν near magic N)

Compare the formula's predictions against ALL 20 targets at ALL
measured energies. Report:
- Mean absolute deviation
- Maximum deviation
- Whether any systematic trend in the residuals suggests a missing
  parameter

---

## 4. Required Outputs

1. **Data table**: 20 rows (one per target), with columns for Z, A, N,
   n_d, n_t, n_tri, n_deu, triton fraction, n_o, |N−N_magic|, β₂,
   R_nuc, S_n, S_2n, E_thr(p,1n), E_thr(p,2n), σ_peak(p,1n),
   σ_peak(p,2n), x_max(200 MeV), <ν>(200 MeV)

2. **Correlation matrix**: A matrix showing Pearson r between every pair
   of grammar parameters and every measured observable

3. **Best predictor identification**: Which grammar parameter(s)
   provide the best prediction of multiplicity? Rank them.

4. **Proposed scaling law**: Closed-form expression with justification

5. **Residual analysis**: Plot of (predicted − measured) vs A, Z, N
   to check for systematic biases

6. **Shell closure analysis**: Separate plot showing how ν deviates
   from the scaling law at magic numbers (N=20, 28, 50, 82, 126)

---

## 5. Success Criteria

- [ ] Data collected for ≥18/20 targets (some may lack EXFOR coverage)
- [ ] At least one grammar parameter achieves R² > 0.7 with x_max
- [ ] Threshold energies are reproduced within 30% for ≥15 targets
- [ ] Shell closure effects are visible in the data and captured by
      the scaling law
- [ ] The scaling law uses only grammar + measured constants (c, ℏ)
- [ ] Residual analysis shows no systematic trend with A or Z
