# E97: Earth Core Seismic Speed from Lattice Compression — Data Requirements

## 1. PREM Seismic Velocity Profile

The Preliminary Reference Earth Model (Dziewonski & Anderson, 1981) is the
canonical radially-symmetric model of Earth's interior. It provides v_p(r),
v_s(r), and ρ(r) at every depth.

### P-wave velocities (compressional)
| Depth (km) | Radius (km) | v_p (km/s) | Region | Source |
|-----------|-------------|-----------|--------|--------|
| 0 | 6371 | 5.80 | Upper crust | PREM |
| 15 | 6356 | 6.80 | Lower crust | PREM |
| 35 | 6336 | 8.04 | Uppermost mantle (Moho) | PREM |
| 100 | 6271 | 8.05 | Lithosphere | PREM |
| 220 | 6151 | 8.56 | Low-velocity zone base | PREM |
| 400 | 5971 | 8.91 | 410-km discontinuity | PREM |
| 670 | 5701 | 10.27 | 670-km discontinuity | PREM |
| 1000 | 5371 | 11.42 | Mid-lower mantle | PREM |
| 1500 | 4871 | 12.12 | Lower mantle | PREM |
| 2000 | 4371 | 12.78 | Lower mantle | PREM |
| 2500 | 3871 | 13.25 | D" layer approach | PREM |
| 2891 | 3480 | 13.72 | CMB (mantle side) | PREM |
| 2891 | 3480 | 8.06 | CMB (core side — liquid!) | PREM |
| 3500 | 2871 | 8.95 | Outer core | PREM |
| 4000 | 2371 | 9.58 | Outer core | PREM |
| 4500 | 1871 | 10.07 | Outer core | PREM |
| 5000 | 1371 | 10.44 | Outer core | PREM |
| 5150 | 1221 | 10.36 | ICB (liquid side) | PREM |
| 5150 | 1221 | 11.04 | ICB (solid side) | PREM |
| 5500 | 871 | 11.19 | Inner core | PREM |
| 6000 | 371 | 11.26 | Deep inner core | PREM |
| 6371 | 0 | 11.26 | Centre | PREM |

### S-wave velocities (shear)
| Depth (km) | v_s (km/s) | Notes | Source |
|-----------|-----------|-------|--------|
| 0 | 3.20 | Crust | PREM |
| 35 | 4.49 | Upper mantle | PREM |
| 670 | 5.57 | Transition zone base | PREM |
| 2891 | 7.26 | CMB (mantle side) | PREM |
| 2891 | 0.00 | CMB (core side) — S=0 in liquid! | PREM |
| 5150 | 0.00 | ICB (liquid side) | PREM |
| 5150 | 3.50 | ICB (solid side) | PREM |
| 6371 | 3.67 | Centre | PREM |

### Density profile
| Depth (km) | ρ (kg/m³) | Region | Source |
|-----------|----------|--------|--------|
| 0 | 2,600 | Crust | PREM |
| 35 | 3,380 | Upper mantle | PREM |
| 670 | 4,380 | Lower mantle top | PREM |
| 2891 | 5,566 | CMB (mantle side) | PREM |
| 2891 | 9,903 | CMB (core side) | PREM |
| 5150 | 12,166 | ICB (liquid side) | PREM |
| 5150 | 12,764 | ICB (solid side) | PREM |
| 6371 | 13,088 | Centre | PREM |

### Pressure profile
| Depth (km) | Pressure (GPa) | Source |
|-----------|---------------|--------|
| 0 | 0 | Surface |
| 35 | 1.0 | PREM integration |
| 400 | 13.4 | PREM |
| 670 | 23.8 | PREM |
| 2891 | 135.8 | CMB | 
| 5150 | 328.9 | ICB |
| 6371 | 363.9 | Centre |

## 2. Earth Structural Parameters

| Quantity | Value | Uncertainty | Source |
|----------|-------|------------|--------|
| Mean radius R_E | 6,371,000 m | ±10 m | IERS |
| Inner core radius | 1,221,000 m | ±1,000 m | PREM |
| Outer core radius | 3,480,000 m | ±2,000 m | PREM |
| Total mass M_E | 5.9722 × 10²⁴ kg | ±0.0006 | IERS |
| Mean density | 5,514 kg/m³ | | Computed |
| Core density (average) | ~11,000 kg/m³ | | PREM |
| Central pressure | 363.9 GPa | ±5 GPa | PREM / ab initio |
| Central temperature | 5,000–6,000 K | ±500 K | Mineral physics |
| Geothermal gradient (surface) | ~25 K/km | ±5 | Measured |
| Core-mantle heat flow | 10–15 TW | ±5 TW | Seismology/geodynamics |

## 3. SDT Parameters Required

| Quantity | Formula | Value | Source |
|----------|---------|-------|--------|
| P_conv | Φ / ℓ_P³ | 2.459 × 10⁴⁸ Pa | laws.hpp law_I |
| f (transfer function) | P_eff / P_conv | 2.125 × 10⁻¹⁷ | laws.hpp law_III |
| k_Earth | c / v_surface_orbital | c / 7909 ≈ 37,904 | magnetosphere.hpp |
| ϟ_Earth (c-boundary) | R_E / k² | 0.0044 m ≈ 4.4 mm | magnetosphere.hpp |
| z_Earth | 1/k² | 6.96 × 10⁻¹⁰ | bridge law |
| v_orbital at surface | √(GM/R) | 7,909 m/s | bridge / measured |
| Convergence pressure at depth r | P_convergence(r) = to be derived | — | THIS INVESTIGATION |
| Spation scale at depth r | ℓ_s(r) = ℓ_P × f(P_local/P_conv) | — | THIS INVESTIGATION |

## 4. Standard Model Comparison Data

The standard explanation for seismic velocities is purely material-property-based:

| Formula | Name | Parameters |
|---------|------|-----------|
| v_p = √((K + 4G/3) / ρ) | P-wave velocity | K=bulk modulus, G=shear modulus, ρ=density |
| v_s = √(G / ρ) | S-wave velocity | G=shear modulus, ρ=density |
| K(P,T) | Equation of state | Birch-Murnaghan or Vinet |
| G(P,T) | Shear modulus | Mineral physics data |

### Key standard-model benchmarks
| Layer | K (GPa) | G (GPa) | v_p (km/s) | v_s (km/s) |
|-------|---------|---------|-----------|-----------|
| Upper mantle | 130 | 68 | 8.05 | 4.49 |
| Lower mantle | 650 | 290 | 13.0 | 7.0 |
| Outer core (liquid Fe) | 1300 | 0 | 8–10 | 0 |
| Inner core (solid Fe) | 1400 | 150 | 11.0 | 3.5 |

## 5. Modern Seismic Observations (Beyond PREM)

| Feature | Value | Source | SDT relevance |
|---------|-------|--------|--------------|
| Inner core anisotropy | v_p 3% faster along polar axis | Morelli et al. 1986 | Does convergence gradient have axial asymmetry? |
| Inner core super-rotation | 0.1–0.3°/year faster than mantle | Song & Richards 1996 | Differential wake coupling? |
| D" layer ultra-low velocity zones | v_p drops 10% in patches at CMB | Garnero et al. 1998 | Convergence channelling at CMB? |
| Post-perovskite transition | v_s jump at 2600 km depth | Murakami et al. 2004 | Phase lock to convergence threshold? |
| 410 km discontinuity | v_p jump from 8.05 → 8.91 km/s | Global seismology | Olivine→wadsleyite = convergence threshold? |
| 670 km discontinuity | v_p jump from 8.91 → 10.27 km/s | Global seismology | Ringwoodite→perovskite = convergence threshold? |

## 6. Archival Seismic Travel Time Data

| Dataset | Source | Content |
|---------|--------|---------|
| ISC-GEM Global Instrumental Catalogue | ISC | Relocated earthquakes 1900–present |
| IRIS DMC waveforms | IRIS | Broadband seismograms for P/S picks |
| ak135 travel time tables | Kennett et al. 1995 | Reference travel times for teleseismic phases |
| IASP91 model | Kennett & Engdahl 1991 | Alternative reference model |
| Global CMT catalogue | Lamont-Doherty | Centroid moment tensors for major earthquakes |
