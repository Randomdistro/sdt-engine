# A02: Neutron Multiplicity vs Energy Scaling — Data Requirements

## 1. Excitation Function Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| σ(p,1n) vs E_p for 20+ targets spanning Z=10–90 | EXFOR | Channel 1 excitation function |
| σ(p,2n) vs E_p for same targets | EXFOR | Channel 2 excitation function |
| σ(p,3n) vs E_p for same targets | EXFOR | Channel 3 excitation function |
| σ(p,4n) vs E_p for same targets | EXFOR | Channel 4 excitation function |
| σ(p,5n)–σ(p,10n) where available | EXFOR | Higher channels |
| Peak cross-section σ_max for each channel | EXFOR | Maximum yield |
| Energy at peak (E_peak) for each channel | EXFOR | Optimal energy |
| Threshold energy (E_thr) for each channel | EXFOR / Q-value computation | Channel opening |
| FWHM of excitation function | EXFOR | Channel width |

## 2. Threshold Energies

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Q-value for each (p,xn) channel | AME2020: Q = M_target + M_p − M_product − x × M_n | Energetics |
| Coulomb barrier height for proton entry | V_C = Z_t × e² / (r₀ × (A_t^(1/3) + 1)) | Classical barrier |
| Effective threshold: E_thr = max(−Q, V_C) | Computed | Which limit applies |
| Laboratory threshold vs CM threshold | Kinematics transformation | Correct frame |
| SDT ℓ=1 wake barrier equivalent | To be derived | SDT barrier prediction |

## 3. Target Grammar Correlations

For each target, tabulate alongside excitation function data:

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Z, A, N | Standard | Identity |
| n_d (deuteron count) | ATOMICUS grammar | Scaffold composition |
| n_t (triton count) | ATOMICUS grammar | Scaffold composition |
| n_tri = N − Z | Computed | Triton metric |
| Triton fraction: n_t / (n_d + n_t) | Computed | Scaffold flexibility |
| n_o (open neutron count) = n_t | Triton Overload: each triton has one n_o | Available loose neutrons |
| Distance from magic N: |N − N_magic| | Computed | Shell closure proximity |
| Nuclear deformation β₂ | FRDM (Möller et al. 2016) | Shape parameter |
| Nuclear charge radius | Angeli & Marinova 2013 | Size |
| S_n (first neutron separation energy) | AME2020 | Ejection cost |
| S_2n (two-neutron separation energy) | AME2020 | Double ejection cost |

## 4. Systematic Survey Targets (Minimum 20)

Select targets to span the periodic table uniformly:

| Target | Z | A | N | Reason |
|--------|---|---|---|--------|
| Al-27 | 13 | 27 | 14 | Light, magic N=14 |
| Ca-40 | 20 | 40 | 20 | Double magic (Z=20, N=20) |
| V-51 | 23 | 51 | 28 | Magic N=28 |
| Fe-56 | 26 | 56 | 30 | Most abundant, near magic |
| Cu-63 | 29 | 63 | 34 | Mid-mass, non-magic |
| Ga-69 | 31 | 69 | 38 | Canonical spallation target |
| Y-89 | 39 | 89 | 50 | Magic N=50 |
| Zr-90 | 40 | 90 | 50 | Magic N=50, Z=40 |
| Mo-98 | 42 | 98 | 56 | Non-magic, mid-mass |
| Ag-107 | 47 | 107 | 60 | Non-magic |
| Sn-120 | 50 | 120 | 70 | Magic Z=50 |
| Ba-138 | 56 | 138 | 82 | Magic N=82 |
| La-139 | 57 | 139 | 82 | Magic N=82, Z=57 |
| Ce-140 | 58 | 140 | 82 | Magic N=82, Z=58 |
| Nd-142 | 60 | 142 | 82 | Magic N=82 |
| Ho-165 | 67 | 165 | 98 | Non-magic, deformed |
| Ta-181 | 73 | 181 | 108 | Non-magic, heavy |
| Au-197 | 79 | 197 | 118 | Non-magic, heavy |
| Pb-208 | 82 | 208 | 126 | Double magic (Z=82, N=126) |
| Bi-209 | 83 | 209 | 126 | Near double magic |

## 5. High-Energy Benchmark Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Average neutron multiplicity <ν> at 200 MeV | Letaw-Silberberg-Tsao systematics | High-E benchmark |
| <ν> at 800 MeV (LANSCE energy) | LANSCE measurements | Standard benchmark |
| <ν> at 1.4 GeV (J-PARC energy) | J-PARC measurements | High-E benchmark |
| <ν> vs A at fixed E | Systematic compilations | Mass dependence |
| Neutron multiplicity distribution P(x) | SINQ / SNS / LANSCE | Full distribution |
| Neutron yield per incident proton (thick target) | SINQ: ~30 n/p for Pb at 590 MeV | Practical benchmark |
