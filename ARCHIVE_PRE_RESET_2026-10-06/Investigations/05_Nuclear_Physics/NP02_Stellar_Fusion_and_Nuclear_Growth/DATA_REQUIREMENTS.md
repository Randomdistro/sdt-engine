# NP02: Stellar Fusion, Nuclear Growth, and Reciprocal Shell Mirroring — Data Requirements

## 1. Fundamental Constants & Radii
All computations must use values from `sdt::laws::measured` without fitting parameter adjustments:

| Parameter | Value | Description |
|-----------|-------|-------------|
| $c$ | $299,792,458$ m/s | Speed of light |
| $\hbar$ | $1.054571817 \times 10^{-34}$ J·s | Reduced Planck constant |
| $m_e$ | $9.1093837015 \times 10^{-31}$ kg | Electron mass |
| $m_p$ | $1.67262192369 \times 10^{-27}$ kg | Proton mass |
| $R_p$ | $8.414 \times 10^{-16}$ m | Proton charge radius |
| $\alpha$ | $7.2973525693 \times 10^{-3}$ | Fine structure constant |
| $P_{\text{eff}}$ | $5.225 \times 10^{31}$ Pa | Effective convergent pressure |
| $k_B$ | $1.380649 \times 10^{-23}$ J/K | Boltzmann constant |

## 2. Benchmark Nuclides & Binding Targets

| Nuclide | Z | A | $n_d$ | $n_t$ | Measured $E_B$ (MeV) |
|---------|---|---|---|---|---------------------|
| He-4 | 2 | 4 | 0 | 0 | 28.296 |
| Li-6 | 3 | 6 | 1 | 0 | 32.0 |
| Li-7 | 3 | 7 | 0 | 1 | 39.2 |
| Be-9 | 4 | 9 | 1 | 1 | 58.2 |
| B-10 | 5 | 10 | 3 | 0 | 64.7 |
| B-11 | 5 | 11 | 2 | 1 | 76.2 |
| C-12 | 6 | 12 | 4 | 0 | 92.2 |
| O-16 | 8 | 16 | 6 | 0 | 127.6 |

## 3. Decay & EC Calibration Points

- **Be-7**:
  - Recombination Temperature: $T_{\text{rec}} \approx 10^5$ to $10^6$ K.
  - Ionization potential: $E_{\text{ion}} = 217.7$ eV (fully ionized to Li-like/He-like threshold).
- **Tl-205**:
  - Bound-beta decay gate: $E_{\text{gate}} = 2.3$ keV.
- **Re-187**:
  - Neutral half-life: $4.12 \times 10^{10}$ years.
  - Fully ionized state: half-life drops to $32.9$ years (re-allocation of winding receipt via bound-state beta decay).
