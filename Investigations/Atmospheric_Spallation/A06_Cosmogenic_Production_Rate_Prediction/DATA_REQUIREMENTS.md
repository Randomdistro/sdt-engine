# A06: Cosmogenic Production Rate Prediction — Data Requirements

## 1. Cosmogenic Isotopes to Predict

| Isotope | Z | A | Half-life | Primary production | Application |
|---------|---|---|-----------|-------------------|-------------|
| C-14 | 6 | 14 | 5,730 y | N-14(n,p)C-14 | Radiocarbon dating |
| Be-7 | 4 | 7 | 53.22 d | N/O spallation | Atmospheric tracer |
| Be-10 | 4 | 10 | 1.387 My | N/O spallation | Exposure dating, ice cores |
| H-3 (tritium) | 1 | 3 | 12.32 y | N/O spallation | Hydrological tracer |
| Na-22 | 11 | 22 | 2.602 y | Ar-40 spallation | Atmospheric tracer |
| Cl-36 | 17 | 36 | 301,000 y | Ar-40(n,αp)Cl-36 | Groundwater dating |
| Al-26 | 13 | 26 | 717,000 y | Si spallation (rocks) | Surface exposure dating |
| Mn-53 | 25 | 53 | 3.7 My | Fe spallation (rocks) | Exposure dating |
| Kr-81 | 36 | 81 | 229,000 y | Kr-80(n,γ)Kr-81 | Groundwater dating |
| I-129 | 53 | 129 | 15.7 My | Xe spallation (atmosphere) | Hydrospheric tracer |

## 2. Input Physics: Cosmic Ray Spectrum

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Differential proton flux dΦ/dE at top of atmosphere (TOA) | AMS-02 (Aguilar et al. 2015, 2021) | Primary input |
| Energy range: 0.1 GeV – 1 TeV | AMS-02 | Full relevant range |
| Solar modulation parameter φ | Usoskin et al. force-field model | Solar cycle correction |
| φ at solar minimum: ~400 MV | Literature | Minimum modulation |
| φ at solar maximum: ~1200 MV | Literature | Maximum modulation |
| Long-term average φ: ~600 MV | Steinhilber et al. 2012 | Average production rate |
| Helium + heavier cosmic ray contribution | AMS-02 / ACE-CRIS | ~10–15% correction |
| Secondary neutron flux in atmosphere | Goldhagen et al. 2004 | For (n,x) reactions |

## 3. Spallation Cross-Sections for Each Product

### C-14 production chain:
| Reaction | σ data source | Energy range |
|----------|-------------|-------------|
| N-14(n,p)C-14 | ENDF/B-VIII.0 | Thermal → 20 MeV |
| O-16(p,x)C-14 (direct) | EXFOR | 30 MeV → 3 GeV |
| N-14(p,x)C-14 | EXFOR | 30 MeV → 3 GeV |
| Neutron production: N-14(p,x)n, O-16(p,x)n | EXFOR / TENDL | All spallation neutrons |

### Be-7 production:
| Reaction | σ data source |
|----------|-------------|
| N-14(p,x)Be-7 | EXFOR (Sisterson, Michel) |
| O-16(p,x)Be-7 | EXFOR |
| N-14(n,x)Be-7 | EXFOR (limited) |

### Be-10 production:
| Reaction | σ data source |
|----------|-------------|
| N-14(p,x)Be-10 | EXFOR (Nishiizumi, Sisterson) |
| O-16(p,x)Be-10 | EXFOR |

### H-3 production:
| Reaction | σ data source |
|----------|-------------|
| N-14(p,x)H-3 | EXFOR |
| O-16(p,x)H-3 | EXFOR |
| N-14(n,H-3)C-12 | ENDF (threshold ~4 MeV) |

### Cl-36 production:
| Reaction | σ data source |
|----------|-------------|
| Ar-40(p,x)Cl-36 | EXFOR |
| Ar-40(n,αp)Cl-36 | ENDF / EXFOR |
| K-39(n,α)Cl-36 | ENDF (in rocks) |
| Ca-40(n,x)Cl-36 | ENDF (in rocks) |

## 4. Atmospheric Transport Parameters

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Atmospheric density profile ρ(h) | US Standard Atmosphere 1976 | Column integration |
| Scale height H ≈ 8.5 km | Standard | Exponential approximation |
| Total column depth: 1030 g/cm² | Standard | Full atmosphere |
| Interaction length for protons in air: λ_p ≈ 80 g/cm² | PDG | Primary attenuation |
| Nuclear interaction length for neutrons in air: λ_n ≈ 150 g/cm² | Literature | Neutron transport |
| Atmospheric mixing time (stratosphere): ~1–2 years | Transport models | Isotope redistribution |
| Atmospheric mixing time (troposphere): ~weeks | Transport models | Washout timescale |

## 5. Measured Production Rates (Benchmarks)

| Isotope | Production rate (atoms/cm²/s) | Source | Uncertainty |
|---------|------------------------------|--------|-------------|
| C-14 | 2.02 ± 0.04 | Kovaltsov et al. 2012 | ±2% |
| Be-7 | 0.062 ± 0.006 | Masarik & Beer 2009 | ±10% |
| Be-10 | 0.0188 ± 0.004 | Masarik & Beer 1999 | ±20% |
| H-3 | 0.25 ± 0.05 | Craig & Lal 1961 / Masarik & Beer 2009 | ±20% |
| Cl-36 | 0.0012 ± 0.0003 | Phillips 2000 (in rocks, latitude-adjusted) | ±25% |
| Na-22 | (3.6 ± 1.0) × 10⁻⁵ | Lal & Peters 1967 | ±30% |

## 6. SDT Parameters

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Grammar of each target (N-14, O-16, Ar-40) | ATOMICUS | Scaffold identity |
| Grammar of each product | ATOMICUS or compute | Product identity |
| Grammar transition for each reaction | Computed | Grammar cost of production |
| V_disp for each target | SDT formula | Geometric cross-section |
| R_disp for each target | SDT formula | Interaction radius |
| k-number of cosmic ray protons at each energy | k = c/v | Coupling parameter |
| SDT-predicted spallation cross-section (from A04) | A04 results | Parameter-free σ |
