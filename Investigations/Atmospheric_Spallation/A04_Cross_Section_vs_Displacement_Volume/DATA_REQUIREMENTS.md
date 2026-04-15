# A04: Cross-Section vs Displacement Volume Scaling — Data Requirements

## 1. Total Reaction Cross-Sections

| Data Point | Source | Purpose |
|-----------|--------|---------|
| σ_total(p,A) at 100 MeV for A = 6–238 | EXFOR / Carlson systematics | Total cross-section |
| σ_total(p,A) at 200 MeV | EXFOR | Higher energy comparison |
| σ_total(p,A) at 1 GeV | EXFOR / PDG | High energy |
| σ_inelastic(p,A) at 100 MeV | EXFOR | Non-elastic (spallation) component |
| σ_inelastic(p,A) at 200 MeV | EXFOR | Higher energy |
| σ_inelastic(p,A) at 1 GeV | EXFOR | High energy |
| σ_elastic(p,A) at same energies | EXFOR | Elastic component for subtraction |
| σ_reaction = σ_total − σ_elastic | Computed | True reaction cross-section |

## 2. Nuclear Geometry Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Nuclear charge radius R_ch for all stable nuclei | Angeli & Marinova 2013 compilation | Measured size |
| Nuclear matter radius R_m (if available) | Parity-violating electron scattering (PREX/CREX) | Neutron radius |
| Nuclear skin thickness: R_n − R_p | PREX-2 (Pb-208), CREX (Ca-48) | Neutron excess at surface |
| Geometric cross-section: σ_geom = π(R_proj + R_target)² | Computed | Simplest geometric model |
| R = r₀ × A^(1/3), r₀ = 1.2–1.3 fm | Conventional parametrisation | Comparison |

## 3. SDT Displacement Volume Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| V_disp for each target nucleus | SDT: V = 3m ℓ_P³ c² / Φ | SDT size parameter |
| R_disp = (3V_disp / 4π)^(1/3) | Computed | Equivalent displacement radius |
| Comparison: R_disp vs R_ch | Computed | Do they agree? |
| R_disp for proton | SDT: 0.84124 fm | Projectile size |
| Cross-section from SDT: σ_SDT = π(R_disp,p + R_disp,target)² | Computed | SDT geometric prediction |

## 4. Grammar-Derived Size Parameters

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Grammar for each target (d, t, n_tri, n_deu) | ATOMICUS | Structure |
| Effective grammar radius: R_gram = f(alpha cores, blocks) | To be derived | Grammar-based size |
| Block packing fraction | To be derived | How densely blocks pack |
| Surface neutron count (from triton n_o) | Grammar analysis | Available interaction sites |
| Shell occupancy fraction | Grammar analysis | How full the outermost shell is |

## 5. Wake-Based Cross-Section Components

| Data Point | Source | Purpose |
|-----------|--------|---------|
| ℓ=1 wake cross-section: σ_Coulomb = π(a_C)² where a_C = Z_t e²/(2E) | Rutherford | Coulomb component |
| ℓ≥3 wake cross-section: σ_nuclear | EXFOR | Nuclear component |
| Interference between ℓ=1 and ℓ≥3 | Optical model (for comparison) | Wave effects |
| Beth (c-boundary) radius for each target | R/k² from SDT | Maximum interaction radius |
| Does σ_reaction scale with beth² or R²? | Computed | Which SDT radius matters |

## 6. Scaling Law Tests

| Data Point | Source | Purpose |
|-----------|--------|---------|
| σ vs A^(2/3) (conventional geometric scaling) | Computed | Conventional benchmark |
| σ vs R_ch² | Computed | Measured radius scaling |
| σ vs R_disp² | Computed | SDT displacement scaling |
| σ vs V_disp^(2/3) | Computed | SDT volume scaling |
| σ vs n_nucleons^(2/3) | Computed | Mass-number scaling |
| σ vs (n_d + n_t)^(2/3) | Computed | Grammar block-count scaling |
| σ vs n_o (surface neutron count) | Computed | Grammar surface scaling |
| Log-log slopes for each relationship | Computed | Power law exponent |
| Reduced chi-squared for each model | Computed | Goodness of fit |
