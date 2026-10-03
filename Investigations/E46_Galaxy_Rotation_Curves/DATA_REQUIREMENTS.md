# E46: Galaxy Rotation Curves from Eclipse Saturation — Data Requirements

## Galaxy Data
| Source | Content | Count |
|--------|---------|-------|
| SPARC database (Lelli et al. 2016) | Rotation curves + mass models for 175 galaxies | 175 |
| Galaxy luminosities (3.6 μm Spitzer) | Baryonic mass tracer | Per galaxy |
| HI 21-cm rotation curves | Outer rotation measurements | Per galaxy |
| Galaxy distances | Redshift-independent distances | Per galaxy |
| Surface brightness profiles | Σ(r) in M_Sun/pc² | Per galaxy |

## Per Galaxy Required
| Quantity | Source |
|----------|--------|
| V_obs(r) — observed rotation curve | SPARC |
| V_disk(r) — disk contribution (from 3.6μm) | SPARC mass model |
| V_gas(r) — gas contribution | SPARC HI data |
| V_bar(r) = √(V_disk² + V_gas²) — total baryonic | Computed |
| M_bar — total baryonic mass | SPARC |

## SDT Model Parameters
| Quantity | Formula | Source |
|----------|---------|--------|
| Eclipse saturation radius r_sat | Where solid angle of disk = 2π (half sky) | SDT galactic model |
| v_flat prediction | (c/k_gal)√(R_gal/r_sat) | bridge::v_orbital |
| k_galaxy | c / v_surface | From central velocity |
| Convergence recycling from disk | L_disk / (4π F_CMB) | law_II |
