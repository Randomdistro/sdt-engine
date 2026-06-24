# Q04: Neutron Capture Mechanism — Data Requirements

## 1. Free Neutron Properties

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Neutron mass: 939.5654 MeV/c² | CODATA | Displacement volume of free neutron |
| Neutron V_disp | SDT formula: 3m_n ℓ_P³ c²/Φ | Exclusion region size |
| Neutron magnetic moment: −1.913 μ_N | CODATA | ℓ=2 wake strength (only long-range coupling) |
| Neutron mean lifetime: 878.4 ± 0.5 s | PDG 2023 (beam+bottle average) | Decay clock — free neutrons are metastable |
| Neutron de Broglie wavelength at thermal energy | λ = h/√(2m_n kT) | SDT: lattice relay wavelength at thermal k-number |
| Neutron kinetic energy at thermalisation | ~0.025 eV at 293 K | Movement budget partition at capture |
| Neutron k-number at thermal velocity | k = c/v_thermal ≈ 1.36 × 10⁵ | Very high k — nearly all circulation |
| Neutron k-number at 1 MeV | k = c/v ≈ 21.6 | Low k — mostly translational |
| Neutron charge radius (formal): 0 | Definition | No ℓ=1 wake — no Coulomb barrier to entry |

## 2. Target Nucleus Properties (Capture Targets)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Thermal neutron capture cross-section σ_cap(0.025 eV) for all stable isotopes | ENDF/B-VIII.0, JENDL-5 | The observable to predict |
| Resonance integral I_res for all stable isotopes | ENDF/B-VIII.0 | Integrated resonance capture |
| Individual resonance parameters (E_r, Γ_n, Γ_γ) | Atlas of Neutron Resonances (Mughabghab) | Fine structure of capture |
| Nuclear construction grammar (d, t) for all stable isotopes | ATOMICUS/isotopes/ | Scaffold state at capture |
| n_tri and n_deu for all stable targets | ATOMICUS grammar | Grammar state |
| Triton fraction for all stable targets | Computed: n_t/(n_d + n_t) | Correlation candidate |
| Nuclear spin I of target ground state | NNDC | Spin coupling at capture |
| Nuclear parity of target | NNDC | Symmetry constraint |
| Nuclear charge radius | Angeli & Marinova | Geometric size |
| Number of neutron vacancies in next shell | NNDC shell model (for comparison) | Available "slots" for neutron |

## 3. Capture Product Properties

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Product isotope (A+1) grammar (d, t) | ATOMICUS or compute | Grammar state after capture |
| Product Δn_tri vs parent | Computed | Grammar change from +1n |
| Product stability | NNDC | Stable vs radioactive product |
| Product decay mode if unstable | NNDC | EC, β⁻, β⁺? |
| Prompt gamma energies from capture | ENDF/B-VIII.0 capture γ library | De-excitation spectrum |
| Prompt gamma multiplicity | ENDF / EGAF database | How many γ rays per capture |
| Isomeric state population fractions | NNDC | Which nuclear level is populated |

## 4. Cross-Section Anomalies

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Elements with anomalously LARGE σ_cap | ENDF: Gd-157 (254,000 b), Xe-135 (2.65 Mb), Sm-149 (40,140 b) | Outlier analysis |
| Elements with anomalously SMALL σ_cap | ENDF: magic-number nuclei (O-16, Ca-40, Pb-208) | Closure rigidity |
| Odd-A vs even-A systematic | ENDF | Pairing effect on capture |
| Odd-N vs even-N systematic | ENDF | Neutron pairing |
| σ_cap vs distance from magic N | ENDF + NNDC | Shell effect correlation |
| 1/v law adherence range | ENDF | Low-energy scaling behaviour |
| Departure from 1/v at resonances | Mughabghab Atlas | Resonance structure |

## 5. SDT Geometric Quantities

| Data Point | Source | Purpose |
|-----------|--------|---------|
| ℓ=2 wake range and coupling at nuclear surface | SDT derivation needed | Only long-range coupling for neutron |
| ℓ≥3 wake structure at nuclear surface | SDT derivation needed | Structure bond initiation range |
| Convergence pressure gradient at R_nuc | SDT | Funnelling effect on approaching neutron |
| Beth (c-boundary) of target nuclei | R/k² | Maximum capture distance |
| "Available slot" geometry in scaffold | SDT grammar analysis | Where does the neutron attach? |
| Grammar transition energy (target → product) | Computed from grammar rules | Energy released in scaffold rearrangement |

## 6. Comparative Reaction Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| (n,γ) capture vs (n,n') scattering cross-sections | ENDF | Capture vs bounce probability |
| (n,p) cross-sections | ENDF | Neutron-induced proton emission (rare) |
| (n,α) cross-sections | ENDF | Neutron-induced alpha emission |
| Radiative capture width Γ_γ vs neutron width Γ_n | Mughabghab | Which process dominates at resonances |
| Neutron scattering lengths (coherent, incoherent) | NIST Neutron Scattering Lengths table | Interaction geometry |
