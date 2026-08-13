# PSP01 Assessment — depth at Parker perihelion vs observed radio

**Date:** 2026-08-12  
**Instrument:** `psp01_parker_depth.py`  
**Stdout:** `.audit-tmp/psp01_run.txt`  
**Formulas:** `laws.hpp` `depth_closure` (GOM22 Shapiro repair)  
**Canon edited:** no

## Status

`PSP_DEPTH_PREDICTED__EMPIRICAL_MATCH_UNADJUDICATED`

## Geometry

| Quantity | Value |
|---|---|
| Closest approach | **9.86 \(R_\odot\)** from centre |
| Altitude above photosphere | **8.86 \(R_\odot\)** ≈ 6.16×10⁶ km |
| Working \(\Omega_\odot\) | 1476.625 m (B39 / GOM22) |

## Depth predictions (Shapiro spine)

| Quantity | Formula | At PSP perihelion |
|---|---|---|
| Displacement depth | \(z=\Omega/r\) | **2.153×10⁻⁷** |
| vs photosphere | \(z_\odot=\Omega/R_\odot\) | 2.123×10⁻⁶ (~10× deeper at surface) |
| Oscillation ratio (clock) | \(d\tau/dt=1-z\) | \(1-2.153\times10^{-7}\) |
| Spectral depth differential (Earth obs) | \(z_\mathrm{spec}=z_\mathrm{psp}-z_\oplus\) | **2.054×10⁻⁷** ≈ **61.6 m/s** equiv. |
| Relay speed | \(c_\mathrm{far}=c(1-z)^2\) | deficit \((c-c_\mathrm{far})/c=4.31\times10^{-7}\) |
| Shapiro marker (order) | \((2\Omega/c)\ln(\ldots)\) | ~44–89 µs one-way (geometry-dependent) |

## Do redshift / \(c_\mathrm{far}\) “match Parker observations”?

**No empirical match can be claimed.**

1. **No published PSP gravitational-redshift science result** isolates \(z_\mathrm{spec}\) or \(c_\mathrm{far}\) the way Viking/Cassini pin Shapiro’s coefficient, or the way solar-surface C1 is graded in B28/B39.
2. **Navigation includes Shapiro** as a modeled light-time term for all deep-space craft — that is routine OD, not a Parker test of SDT’s depth formulas.
3. **Kinematic Doppler overwhelms depth:** \(v\sim191\,\mathrm{km/s}\) ⇒ \(\beta\sim6.4\times10^{-4}\) vs \(z_\mathrm{spec}\sim2\times10^{-7}\) (**~3000×**). Without a maser-class one-way compensation experiment (RadioAstron-style), the depth ratio is buried.
4. **Near-Sun radio residuals are plasma-dominated** (scintillation, phase noise, spectral broadening), not a clean depth-ratio measurement.
5. **Closest approach is often out of contact**; beacon/telemetry after the dive does not cleanly sample “signals sent from perihelion depth” as a science frequency standard.

## What *is* earned in-repo (not from Parker)

| Gate | Anchor |
|---|---|
| Solar-surface redshift = depth | B28/B39 C1 (~633 m/s) |
| Shapiro from \(c_\mathrm{far}=c(1-z)^2\) | B39 / GOM22 (~247 µs RT grazing) |

Parker at 9.86 \(R_\odot\) is a **predicted** depth \(z\sim2.15\times10^{-7}\); comparing that prediction to PSP radio data remains **UNADJUDICATED**.
