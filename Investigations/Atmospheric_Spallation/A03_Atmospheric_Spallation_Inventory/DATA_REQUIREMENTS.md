# A03: Atmospheric Spallation Inventory — Data Requirements

## 1. Primary Atmospheric Targets

| Target | Z | A | N | Abundance in atmosphere | Number density at sea level |
|--------|---|---|---|------------------------|-----------------------------|
| N-14 | 7 | 14 | 7 | 78.084% × 99.632% | 4.19 × 10²⁵ /m³ |
| N-15 | 7 | 15 | 8 | 78.084% × 0.368% | 1.55 × 10²³ /m³ |
| O-16 | 8 | 16 | 8 | 20.946% × 99.757% | 5.33 × 10²⁴ /m³ |
| O-17 | 8 | 17 | 9 | 20.946% × 0.038% | 2.03 × 10²¹ /m³ |
| O-18 | 8 | 18 | 10 | 20.946% × 0.205% | 1.10 × 10²² /m³ |
| Ar-36 | 18 | 36 | 18 | 0.934% × 0.3336% | 7.94 × 10¹⁹ /m³ |
| Ar-38 | 18 | 38 | 20 | 0.934% × 0.0629% | 1.50 × 10¹⁹ /m³ |
| Ar-40 | 18 | 40 | 22 | 0.934% × 99.604% | 2.37 × 10²³ /m³ |

## 2. Grammar of Each Atmospheric Target

| Data Point | Source | Purpose |
|-----------|--------|---------|
| N-14 grammar: α, d, t, n_tri, n_deu | ATOMICUS/isotopes/007_N14.md | Scaffold state |
| N-15 grammar | ATOMICUS/isotopes/007_N15.md | Scaffold state |
| O-16 grammar | ATOMICUS/isotopes/008_O16.md | Scaffold state |
| O-17 grammar | ATOMICUS/isotopes/008_O17.md | Scaffold state |
| O-18 grammar | ATOMICUS/isotopes/008_O18.md | Scaffold state |
| Ar-36 grammar | ATOMICUS/isotopes/018_Ar36.md | Scaffold state |
| Ar-40 grammar | ATOMICUS/isotopes/018_Ar40.md | Scaffold state |

## 3. All Spallation Products from N-14

| Reaction | Product | Product Z | Product A | Source |
|----------|---------|-----------|-----------|--------|
| N-14(p,pn)N-13 | N-13 | 7 | 13 | EXFOR |
| N-14(p,2pn)C-12 | C-12 | 6 | 12 | EXFOR |
| N-14(p,3p2n)B-10 | B-10 | 5 | 10 | EXFOR |
| N-14(p,3p3n)B-9→(decay)→... | B-9 | 5 | 9 | EXFOR |
| N-14(p,α)C-11 | C-11 | 6 | 11 | EXFOR |
| N-14(p,2p)C-13 | C-13 | 6 | 13 | EXFOR |
| N-14(p,pα)B-10 | B-10 | 5 | 10 | EXFOR |
| N-14(p,2pα)Li-7 | Li-7 | 3 | 7 | EXFOR |
| N-14(p,spallation)→Be-7 | Be-7 | 4 | 7 | EXFOR |
| N-14(p,spallation)→Be-10 | Be-10 | 4 | 10 | EXFOR |
| N-14(p,spallation)→H-3 | H-3 | 1 | 3 | EXFOR |
| All other measured products | Various | Various | Various | EXFOR comprehensive search |

## 4. All Spallation Products from O-16

| Reaction | Product | Product Z | Product A | Source |
|----------|---------|-----------|-----------|--------|
| O-16(p,pn)O-15 | O-15 | 8 | 15 | EXFOR |
| O-16(p,2pn)N-14 | N-14 | 7 | 14 | EXFOR |
| O-16(p,α)N-13 | N-13 | 7 | 13 | EXFOR |
| O-16(p,pα)C-12 | C-12 | 6 | 12 | EXFOR |
| O-16(p,spallation)→Be-7 | Be-7 | 4 | 7 | EXFOR |
| O-16(p,spallation)→Be-10 | Be-10 | 4 | 10 | EXFOR |
| O-16(p,spallation)→C-11 | C-11 | 6 | 11 | EXFOR |
| O-16(p,spallation)→C-14 | C-14 | 6 | 14 | EXFOR (minor) |
| O-16(p,spallation)→Li-6 | Li-6 | 3 | 6 | EXFOR |
| O-16(p,spallation)→Li-7 | Li-7 | 3 | 7 | EXFOR |
| All other measured products | Various | Various | Various | EXFOR comprehensive search |

## 5. Cross-Section Data for Each Product

| Data Point | Source | Purpose |
|-----------|--------|---------|
| σ(E) for each reaction channel on N-14 | EXFOR | Energy-dependent yield |
| σ(E) for each reaction channel on O-16 | EXFOR | Energy-dependent yield |
| Integrated yield (σ × flux) over cosmic ray spectrum | Computed | Production rate |
| Cosmic ray proton spectrum at top of atmosphere | AMS-02 | Flux weighting |
| Atmospheric depth profile (g/cm²) | Standard atmosphere | Column-integrated yield |

## 6. Measured Cosmogenic Production Rates

| Isotope | Measured production rate | Source | Purpose |
|---------|------------------------|--------|---------|
| C-14 | 2.02 ± 0.04 atoms/cm²/s | Kovaltsov et al. 2012 | Benchmark |
| Be-7 | 0.062 atoms/cm²/s | Masarik & Beer 2009 | Benchmark |
| Be-10 | 0.018–0.021 atoms/cm²/s | Masarik & Beer 1999 | Benchmark |
| H-3 (tritium) | 0.25 atoms/cm²/s | Craig & Lal 1961 | Benchmark |
| Na-22 | 3.6 × 10⁻⁵ atoms/cm²/s | Lal & Peters 1967 | Benchmark |
| Al-26 | ~1.1 × 10⁻⁴ atoms/cm²/s (in meteorites) | Nishiizumi 1987 | Benchmark (not atmospheric) |

## 7. Grammar for Each Product (to be computed)

For every spallation product identified in Sections 3–4:
- Z, A, N
- Alpha core, d, t, n_tri, n_deu
- Grammar validity (n_tri ≥ 0 AND n_deu ≥ 0)
- Decay mode (if unstable)
- Stable endpoint grammar
- Whether the product originates from losing ONLY n_o neutrons
