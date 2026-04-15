# E11+E45: Pressure-Gradient Redshift and BAO Scale — Data/Prompt

## DATA REQUIREMENTS
| Data | Source |
|------|--------|
| SDSS/BOSS/eBOSS BAO measurements: D_A(z), D_H(z) at z=0.15–2.33 | BOSS DR12, eBOSS |
| DESI BAO (2024) | DESI Y1 |
| CMB acoustic peak positions | Planck 2018 |
| Galaxy redshift surveys | SDSS, 6dF, WiggleZ |
| SDT strain rate σ | cosmology.hpp |
| SDT BAO scale interpretation | cosmology.hpp bao namespace |

## INVESTIGATION PROMPT

### E11: Pressure-Gradient Redshift
**Target**: Derive the distance-redshift relation from pressure gradient traversal (no metric expansion).

SDT says: z = exp(∫σ dx) − 1, where σ is the local strain rate. At low z this is linear (z ≈ σd ≈ H₀d/c, reproducing the Hubble law). At high z it curves differently from ΛCDM.

Compute SDT μ(z) for the Pantheon+ sample and compare to ΛCDM.

### E45: BAO as Lattice Standing Waves
**Target**: Show the 147 Mpc BAO scale is a lattice equilibrium length, not a frozen sound wave.

SDT: the coupled-epoch lattice (before the Clearing) supported standing waves at c/√3. The BAO scale = c_s × t_coupled = (c/√3) × 2.62×10¹⁶ s ≈ 147 Mpc. This is already in cosmology.hpp pre_clearing namespace.

### Common Methodology
1. Compute SDT angular diameter distance D_A(z) from pressure-gradient integration
2. Compare to BAO-measured D_A at each redshift bin
3. Compute SDT Hubble distance D_H(z) = c/H(z) where H varies with z
4. χ² comparison: SDT vs ΛCDM at each BAO redshift

### Success Criteria
- [ ] SDT D_A(z) matches BAO measurements within 3%
- [ ] BAO scale 147 Mpc reproduced from lattice sound speed × coupled epoch duration
- [ ] No dark energy needed in the SDT fit
