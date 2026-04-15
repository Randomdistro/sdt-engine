# A05: Capture Cross-Section vs Grammar State — Data Requirements

## 1. Thermal Neutron Capture Cross-Sections

| Data Point | Source | Purpose |
|-----------|--------|---------|
| σ_cap(n_th) for ALL stable isotopes (Z=1–83, 90, 92) | ENDF/B-VIII.0 | The complete dataset |
| Temperature: 0.0253 eV (293 K Maxwellian) | Standard | Thermal point |
| Uncertainty on each σ_cap | ENDF | Weighting in correlation |
| Resonance integral I_res for each isotope | ENDF | Epithermal benchmark |
| Total number of stable isotopes: ~254 | NNDC | Dataset size |
| σ_cap values spanning: 0.0003 b (Pb-208) to 2.65 × 10⁶ b (Xe-135*) | ENDF | Dynamic range |

Note: * Xe-135 is not stable but is included for extreme outlier analysis.

## 2. Grammar Data for All Stable Isotopes

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Alpha core count for each isotope | ATOMICUS formula | Core structure |
| Deuteron count n_d | ATOMICUS formula | Block count |
| Triton count n_t | ATOMICUS formula | Block count |
| n_tri = N − Z | Computed | Triton metric |
| n_deu | Computed | Deuteron metric |
| Triton fraction: n_t / (n_d + n_t) | Computed | Key correlation candidate |
| n_o (open neutron count = n_t) | Per Triton Overload | Surface docking sites |
| Grammar validity (check) | Computed | Sanity |

## 3. Shell Structure Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Shell occupancy: N relative to magic numbers (2,8,20,28,50,82,126) | Computed | Shell closure proximity |
| Distance to nearest magic N: |N − N_magic| | Computed | Quantitative measure |
| Which shell the last neutron occupies | NNDC shell model (for comparison) | Level identification |
| Whether the target is even-N, odd-N | Computed | Pairing effect |
| Whether the target is even-Z, odd-Z | Computed | Proton pairing |
| Even-even, even-odd, odd-even, odd-odd classification | Computed | Full parity classification |

## 4. Nuclear Properties

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Ground state spin I | NNDC | Spin coupling |
| Ground state parity | NNDC | Symmetry |
| Nuclear deformation β₂ | FRDM (Möller et al.) | Shape |
| First excited state energy | NNDC | Level density indicator |
| Level density at neutron separation energy | Mughabghab Atlas | Conventional benchmark |
| S_n (neutron separation energy of A+1 product) | AME2020 | Energy released in capture |
| Neutron scattering length (coherent) | NIST table | Interaction geometry |

## 5. Product Grammar After Capture

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Product (A+1) grammar: d, t, n_tri, n_deu | Computed | Grammar change |
| Δn_tri = n_tri(A+1) − n_tri(A) | Computed | Grammar shift |
| Δn_deu = n_deu(A+1) − n_deu(A) | Computed | Grammar shift |
| Product stability | NNDC | Stable or radioactive? |
| Product decay mode (if radioactive) | NNDC | EC, β⁻, stable? |

## 6. Extreme Outlier Data

| Isotope | Z | A | σ_cap (b) | Grammar | Why extreme? |
|---------|---|---|-----------|---------|-------------|
| Gd-157 | 64 | 157 | 254,000 | ? | Largest stable-isotope σ |
| Sm-149 | 62 | 149 | 40,140 | ? | Second largest |
| Eu-151 | 63 | 151 | 9,198 | ? | Third |
| Cd-113 | 48 | 113 | 20,600 | ? | Large for medium Z |
| B-10 | 5 | 10 | 3,835 | ? | Large for light nucleus |
| He-3 | 2 | 3 | 5,333 | ? | Enormous for Z=2 |
| Pb-208 | 82 | 208 | 0.000490 | ? | Smallest (double magic) |
| O-16 | 8 | 16 | 0.000190 | ? | Very small (double magic) |
| Ca-40 | 20 | 40 | 0.410 | ? | Small (double magic) |
| C-12 | 6 | 12 | 0.00353 | ? | Very small (N=Z=6) |

## 7. Correlation Test Variables

All pairs to test:

| Variable 1 | Variable 2 | Expected relationship |
|-----------|-----------|---------------------|
| σ_cap | n_t (triton count) | Positive? |
| σ_cap | triton fraction | Positive? |
| σ_cap | n_o (open neutrons) | Positive? |
| σ_cap | |N − N_magic| | Positive? (farther from magic → larger σ) |
| σ_cap | n_deu | Negative? (more deuterons → more rigid → smaller σ) |
| σ_cap | I (ground state spin) | Possible spin coupling |
| σ_cap | S_n (product separation energy) | Positive? (more energy released → larger σ) |
| σ_cap | β₂ (deformation) | Positive? (deformed → more surface → larger σ) |
| σ_cap | even/odd N | Systematic? |
| log(σ_cap) | 1/|N − N_magic| | Power law near magic? |
