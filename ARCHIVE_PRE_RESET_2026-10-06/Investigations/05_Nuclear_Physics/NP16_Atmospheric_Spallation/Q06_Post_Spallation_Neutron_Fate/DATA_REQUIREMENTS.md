# Q06: Post-Spallation Neutron Fate — Data Requirements

## 1. Free Neutron Propagation

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Neutron energy at ejection: 1–20 MeV (spallation), 0.1–2 MeV (evaporation) | EXFOR / spallation models | Initial condition |
| Neutron scattering cross-section in N₂: σ_s(E) | ENDF/B-VIII.0 | Atmospheric thermalisation |
| Neutron scattering cross-section in O₂: σ_s(E) | ENDF/B-VIII.0 | Atmospheric thermalisation |
| Elastic scattering angular distribution | ENDF | Energy loss per collision |
| Average energy loss per elastic collision: ΔE/E = 2A/(A+1)² | Kinematics | Thermalisation rate |
| Number of collisions to thermalise from 2 MeV in air | Computed (~20 for N-14) | Thermalisation path length |
| Mean free path in air at sea level: ~10 cm at thermal, ~1 m at 1 MeV | ENDF + air density | Propagation distance |
| Mean free path in atmosphere at altitude | Exponential atmosphere model | Altitude-dependent fate |
| Neutron lifetime: 878.4 s | PDG | Decay clock (most captured before decay) |

## 2. Thermalisation Physics

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Moderation ratio (ξ = avg logarithmic energy loss) for N-14 | ξ = 1 − (A−1)²ln((A+1)/(A−1))/(2A) | Slowing-down efficiency |
| Moderation ratio for O-16 | Same formula | Comparison |
| Fermi age τ_F (slowing-down area) in air | MCNP / literature | Spatial spread during thermalisation |
| Thermalisation time in atmosphere | ~100 μs at sea level | Temporal scale |
| Thermal equilibrium energy at altitude | kT = 0.025 eV (sea level), ~0.018 eV (tropopause) | Final energy |
| Maxwell-Boltzmann distribution at thermal equilibrium | Standard | Final energy spectrum |

## 3. Capture Targets in Atmosphere

| Data Point | Source | Purpose |
|-----------|--------|---------|
| N-14 thermal capture cross-section: σ_cap = 1.83 b | ENDF | Dominant atmospheric absorber |
| N-14(n,p)C-14 cross-section: σ = 1.83 b (this IS the capture) | ENDF | C-14 production reaction |
| O-16 thermal capture cross-section: σ_cap = 0.000190 b | ENDF | Minor absorber |
| Ar-40 thermal capture cross-section: σ_cap = 0.660 b | ENDF | Trace absorber |
| ⁴⁰Ar abundance in atmosphere: 0.934% | CRC Handbook | Available Ar target mass |
| N₂ number density at sea level: 2.1 × 10²⁵ /m³ | Ideal gas law | Target density |
| O₂ number density at sea level: 5.6 × 10²⁴ /m³ | Ideal gas law | Target density |
| H₂O content vs altitude | Standard atmosphere model | Additional moderator/absorber |

## 4. Capture Products and Decay Chains

| Data Point | Source | Purpose |
|-----------|--------|---------|
| C-14 production rate: ~2 atoms/cm²/s | Literature (Lingenfelter 1963, Kovaltsov 2012) | Benchmark observable |
| C-14 half-life: 5,730 y | NNDC | Equilibrium inventory |
| C-14 global inventory: ~62 tonnes | Literature | Steady-state check |
| C-14 grammar (d, t, n_tri, n_deu) | ATOMICUS/isotopes/006_C13.md → +1n | Grammar after capture |
| N-15 (from N-14 + n → N-15 + γ — minor channel) production | ENDF | Alternative capture product |
| Ar-41 (from Ar-40 + n → Ar-41) production | ENDF | Trace product |
| H-3 production from N-14(n,³H)C-12 | ENDF σ = 0.0 (threshold reaction ~4 MeV) | Tritium production |
| Be-7 production from O-16 spallation | EXFOR | Light fragment production |

## 5. Geomagnetic and Altitude Effects

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Geomagnetic cutoff rigidity vs latitude | IGRF + Störmer theory | Where cosmic rays reach atmosphere |
| Cosmic ray flux vs altitude (Pfotzer maximum at ~15 km) | Balloon data (Regener-Pfotzer) | Peak spallation altitude |
| Atmospheric depth vs altitude: 1030 g/cm² at sea level | Standard atmosphere | Column density |
| Neutron flux vs altitude | Goldhagen et al. 2004 | Measured neutron profile |
| Neutron flux vs geomagnetic latitude | Neutron monitor network (NMDB) | Latitude effect |
| Aircraft-altitude neutron dose rates | CARI-7 model (FAA) | Practical application |

## 6. Ground-Level Neutron Fate

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Thermal neutron flux at Earth's surface: ~10⁻² /cm²/s | Literature | Surviving neutrons |
| Neutron capture in soil minerals (Si, Al, Fe, Ca, Na, K) | ENDF cross-sections | Ground-level capture targets |
| Neutron capture in water (H: σ = 0.332 b, O: σ = 0.000190 b) | ENDF | Ocean capture |
| Cosmogenic nuclide production in rocks (Be-10, Al-26, Cl-36) | Gosse & Phillips 2001 | Surface exposure dating |
| Neutron activation analysis applications | IAEA Technical Documents | Practical use of capture |

## 7. SDT Geometric Quantities

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Free neutron k-number during thermalisation | k = c/v at each energy | Coupling evolution |
| Convergence gradient of Earth's atmosphere | SDT: from Earth's displacement field | Background lattice environment |
| ℓ=2 wake coupling between neutron and N-14 | SDT derivation needed | Capture geometry |
| Grammar transition N-14 + n → C-14 + p | ATOMICUS grammar | SDT description of the (n,p) reaction |
| Grammar transition: why (n,p) on N-14 but (n,γ) on most others | SDT derivation needed | Selectivity question |
