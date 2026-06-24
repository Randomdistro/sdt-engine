# A05: Capture Cross-Section vs Grammar State — Investigation Prompt

> **Classification**: Archival data analysis + correlation study
> **Prerequisites**: ATOMICUS grammar for all stable isotopes,
> ENDF thermal capture data
> **Output format**: Correlation matrix + best predictor identification

---

## 1. Objective

Determine whether the SDT nuclear construction grammar (deuteron/triton
block counts, triton fraction, open neutron count) can predict the
thermal neutron capture cross-section σ_cap across the FULL periodic
table — explaining the 10⁹ dynamic range from Pb-208 (0.0005 b) to
Gd-157 (254,000 b) from geometric scaffold properties alone.

This is the MOST DEMANDING test of SDT grammar's predictive power.
If grammar can explain capture cross-sections, it demonstrates that the
scaffold structure IS the physics — not an approximation of it.

---

## 2. The Challenge

The thermal neutron capture cross-section varies by NINE orders of
magnitude across stable isotopes. No single conventional quantity
explains this range without fitted parameters. The conventional approach
(statistical model + optical model + shell model) uses ~5–10 parameters
per nuclide.

SDT must explain this range with ZERO fitted parameters — only grammar
properties computable from (Z, N).

---

## 3. Methodology

### Phase A: Assemble the complete dataset

For ALL ~254 stable isotopes:

1. Look up σ_cap from ENDF/B-VIII.0 at 0.0253 eV
2. Compute grammar: α, n_d, n_t, n_tri, n_deu, triton fraction, n_o
3. Compute shell properties: |N − N_magic|, even/odd classification
4. Look up nuclear properties: I, π, β₂, S_n(product)
5. Tabulate everything in a master spreadsheet

### Phase B: Global correlation matrix

Compute the Spearman rank correlation ρ (robust to outliers and
nonlinearity) between log(σ_cap) and every candidate predictor:

| Predictor | Expected sign | Physical meaning in SDT |
|----------|-------------|----------------------|
| n_t | + | More tritons → more docking antennas for incoming neutron |
| triton fraction | + | Higher t/(d+t) → more flexible scaffold |
| n_o | + | More open neutrons → more surface capture sites |
| n_deu | − | More deuterons → more rigid scaffold → harder to insert |
| |N − N_magic| | + | Farther from closure → more available slots |
| S_n(product) | + | Higher binding → more energy released → larger capture rate |
| β₂ | + | More deformed → larger effective surface |
| I (spin) | ? | Spin coupling may create selection rules |

For each, report:
- Spearman ρ
- p-value
- Whether the correlation survives when split by mass range
  (light Z<20, medium 20<Z<50, heavy Z>50)

### Phase C: Multivariate analysis

If no single predictor explains >80% of the variance:

1. Test combinations: does (n_o × |N − N_magic|) perform better than
   either alone?
2. Test ratio predictors: does (n_o / n_deu) predict log(σ)?
3. Construct a minimal multivariate model:
   log(σ_cap) = a₀ + a₁ × log(n_o) + a₂ × log(|N−N_magic|+1) + a₃ × (−1)^N
4. Report: how many parameters are needed to achieve R² > 0.7?
5. Compare: the conventional statistical model needs ~5–10 per nuclide.
   If SDT achieves similar accuracy with 3–4 UNIVERSAL parameters,
   this is a significant advance.

### Phase D: Outlier analysis

Identify the top 10 and bottom 10 outliers (largest deviations from
the best-fit model):

For each outlier:
1. Report: Z, A, N, grammar, σ_cap, predicted σ, deviation
2. Determine: is there a GRAMMAR explanation for the outlier?
   - Is it near a magic number?
   - Is it odd-odd (doubly unpaired)?
   - Does it have anomalous triton fraction?
   - Is there a known resonance just below thermal energy that
     inflates σ?

Special focus on the extreme cases:
- **Gd-157**: Why is its σ so large? Grammar analysis:
  Z=64, N=93, n_tri = 29, triton fraction = ?
  Is 93 neutrons in a specific shell configuration that creates an
  exceptionally open docking geometry?
- **Pb-208**: Why is its σ so small? Grammar analysis:
  Z=82, N=126, both magic. Does the grammar show a FULLY CLOSED
  scaffold with zero available positions?
- **He-3**: σ_cap = 5,333 b. This is the alpha completion reaction
  (He-3 + n → He-4). Grammar: He-3 has n_tri = −1 (the ONLY
  negative n_tri in nature). Does the grammar invalidity of He-3
  explain its intense neutron hunger?

### Phase E: Predictive test

Withhold 20% of the isotopes (randomly selected, stratified by mass
range) from the fitting. Use the remaining 80% to determine the
best model. Then predict σ_cap for the withheld 20%.

Report:
- Mean absolute percentage error on the holdout set
- Whether any holdout isotope deviates by >100× from prediction
- Whether the holdout performance is comparable to the training
  performance (evidence against overfitting)

---

## 4. Required Outputs

1. **Master table**: ~254 rows, one per stable isotope, with all
   grammar parameters and σ_cap

2. **Correlation matrix**: A table showing Spearman ρ and p-value
   for every single predictor vs log(σ_cap)

3. **Best single predictor**: Name it, report its ρ, plot described
   textually

4. **Multivariate model** (if needed): Formula with coefficients

5. **Outlier report**: Top 10 and bottom 10 outliers with grammar
   analysis of each

6. **Gd-157 / Pb-208 / He-3 special analysis**: One paragraph each
   explaining why their σ_cap is extreme, in grammar terms

7. **Holdout validation**: Prediction accuracy on withheld data

8. **Conclusion**: Can grammar predict capture cross-sections? If yes,
   to what accuracy? If no, what additional SDT quantity is needed?

---

## 5. Success Criteria

- [ ] All ~254 stable isotopes included
- [ ] At least one grammar predictor achieves |ρ| > 0.5
- [ ] The multivariate model achieves R² > 0.5 with ≤4 parameters
- [ ] Gd-157 and Pb-208 extremes are explained in grammar terms
- [ ] He-3's extreme σ is connected to its unique n_tri = −1 grammar
- [ ] Holdout test confirms the model generalises
- [ ] No conventional nuclear physics quantities (level density, optical
      model parameters) are used in the grammar model
- [ ] The 10⁹ dynamic range is spanned to within ±2 orders of magnitude
      by the best model
