# Planar CMB Solid-Angle Occlusion Audit

## Purpose

Replace the Keplerian display with a one-Mercury-period numerical experiment. The only driving acceleration is a planar pressure deficit from the measured CMB radiation pressure. JPL Horizons supplies the initial state and sealed terminal comparison state; it never supplies a force or in-run position.

## Frozen inputs

- State vectors: NASA/JPL Horizons API 1.3, DE441, Solar System Barycenter, geometric vectors, Ecliptic of J2000.0, TDB.
- Start: JD 2451545.0 TDB.
- Terminal comparison: JD 2451632.969 TDB.
- Duration: 87.969 days.
- Bodies: Sun and eight planets.
- Source radii and target inertial masses: NASA/JPL Planetary Fact Sheet values recorded in `Datasets/solar_occlusion_2026-08-19/jpl_de441_ecliptic_j2000_mercury_orbit.json`.
- CMB temperature: 2.7255 K.
- Radiation constant: 7.5657e-16 J m^-3 K^-4.
- Pressure: `P = a T^4 / 3 = 1.39159419e-14 Pa`.

## Force contract

For target `i` and source `j`, use the exact apparent solid angle of the observed source radius:

`Omega_ij = 2 pi [1 - sqrt(1 - (R_j / r_ij)^2)]`.

With all incident directions otherwise equal, the implemented pressure-deficit magnitude is:

`F_ij = P (pi R_i^2) Omega_ij / (4 pi)`.

Only its J2000 ecliptic component is applied: `a_i = sum_j project_xy(F_ij n_ij) / m_i`. There is no `G`, `GM`, Kepler propagation, fitted gain, effective cross-section, or conventional gravity term.

Unblocked source caps use the analytic solid angle. When a foreground apparent disc overlaps a source cap, a deterministic 2,048-ray equal-area spherical quadrature computes the source's visible fraction before its contribution is added. This corrects the pair-sum double count but is numerical, not analytic.

## Run result

| Quantity | Result |
| --- | ---: |
| Velocity-Verlet timestep | 3,600 s |
| Accepted steps | 2,112 |
| Peak Mercury acceleration | 1.95890289e-29 m/s^2 |
| Peak body-system force imbalance | 2.39701350e-10 N |
| Foreground-cap screenings | 10 |
| Mercury terminal difference from JPL | 1.97544829 AU |

The terminal discrepancy falsifies the specific no-fit mechanism implemented here: measured CMB radiative pressure acting on geometric planetary discs with a planar solid-angle resultant cannot produce the observed Mercury arc.

It does not by itself falsify a broader hypothesis that introduces an effective pressure or an effective occlusion cross-section, because neither quantity is observationally fixed in this experiment. Supplying either to reduce the discrepancy would be a new, independently testable force-law commitment rather than a result of this run.

## Reproduction

1. Run `python Prototypes/Convergence_ABC_Influx_Toy/tools/fetch_jpl_planar_occlusion_data.py` from the repository root.
2. Serve the repository root, not the prototype subdirectory.
3. Open `Prototypes/Convergence_ABC_Influx_Toy/index.html`.

JPL documents the Horizons vector endpoint and query parameters at [Horizons API documentation](https://ssd-api.jpl.nasa.gov/doc/horizons.html). The raw responses are retained under `Datasets/solar_occlusion_2026-08-19/raw`.
