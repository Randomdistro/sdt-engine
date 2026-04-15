# E35: Fe-56 vs Ni-62 Grammar Efficiency — Data/Prompt

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| B/A for Fe-56 | 8.790 MeV/n | AME2020 |
| B/A for Ni-62 | 8.795 MeV/n | AME2020 |
| Fe-56 grammar | 5α + 6d + 6t (26p, 30n) | ATOMICUS |
| Ni-62 grammar | 5α + 6d + 9t (28p, 34n) | ATOMICUS |
| Fe-56 cosmic abundance | Most abundant metal | Solar abundances |
| Ni-62 abundance | ~3.6% of nickel | NNDC |
| Triton fraction: Fe-56 | 6t / (6d + 6t) = 50% | Grammar |
| Triton fraction: Ni-62 | 9t / (6d + 9t) = 60% | Grammar |

## INVESTIGATION PROMPT

**Target**: Explain why Fe-56 is more cosmically abundant than Ni-62 despite Ni-62 having higher B/A.

### SDT Prediction
Fe-56's grammar is MORE symmetric (equal d and t count) → geometrically optimal. Ni-62 has a triton excess → less symmetric scaffold.

### Methodology
1. Compute the "grammar efficiency" metric for both: symmetry = |n_d − n_t| / (n_d + n_t)
2. Fe-56: |6−6|/12 = 0 (perfect symmetry)
3. Ni-62: |6−9|/15 = 0.2 (asymmetric)
4. Extend to ALL stable nuclei: compute B/A vs grammar symmetry
5. Is the most abundant isotope at each Z always the most symmetric?
6. Do magic numbers (Z=2,8,20,28,50,82) correspond to grammar symmetry maxima?

### Success Criteria
- [ ] Fe-56's abundance explained by grammar symmetry
- [ ] Correlation between grammar symmetry and natural abundance established
- [ ] Pattern extended to all elements Z=1–83
