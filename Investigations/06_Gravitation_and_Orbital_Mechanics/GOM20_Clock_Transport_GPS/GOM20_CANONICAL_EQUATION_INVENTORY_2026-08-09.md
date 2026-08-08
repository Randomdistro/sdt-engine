# GOM20 Canonical Equation Inventory - 2026-08-09

**Purpose:** freeze the in-repository mathematical source set before assessing
whether GOM20 can make a direct clock prediction. This is an internal-model
inventory, not observational evidence and not a physical verdict.

## Frozen sources

| File | SHA-256 | Relevant content |
|---|---|---|
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | Law IV exclusion volume, Law V clock laws, Earth `koppa`, baryon-count functions, depth closure |
| `Engine/include/sdt/magnetosphere.hpp` | `c94a5bd43170234a2447d6de246503a729f30413b55374f0bcdab4fbc5c3fc87` | Earth `koppa` constant using its declared Earth radius |
| `Engine/include/sdt/state28d.hpp` | `552575a8abcfe8839452f9882b6a5fed0943ad7b8cb1e2b98b7e7861cef41935` | Shell state fields, without a clock-rate composition |
| `Laws/LAW_OF_VORTEX_TOPOLOGY_QUANTISATION.md` | `76234eaa1c03124cb63e50597e6020fe57ee700171aa534bf96d6327d67d8bcf` | Movement-budget statement `v_circ^2 + v_t^2 = c^2` |
| `GOM20_GPS_MECHANISM_AMENDMENT_01.md` | `d772bcf1190b2acec57f8f055f7740f89579be2a7907505ff4923d5889b7f84c` | Author-supplied required recovery ingredients |

## Available equations

| Identifier | Frozen expression / interface | Declared inputs |
|---|---|---|
| `law_V::gravitational_time_dilation` | `sqrt(1 - z R / r)` | dimensionless `z`, radii `R` and `r` in metres |
| `depth_closure::depth` | `z = koppa / r` | `koppa` and `r` in metres |
| `depth_closure::clock_rate` | `1 - z` | dimensionless local depth `z` |
| `law_IV::V_disp_from_mass` | `3 m l_P^3 c^2 / Phi` | mass in kg; canonical `Phi` |
| `bridge::N_baryons_from_koppa` | `(v^2 R / c^2) / koppa_per_baryon` | observed orbital speed and radius |
| `bridge::N_baryons` | `koppa_body / koppa_per_baryon` | length-valued `koppa` |
| `law_V` / Law V text | `v_circ^2 + v_trans^2 = c^2` | two velocities in m/s |

## Explicit absences

The canonical engine has no identifier containing `polar radius`, `radius
polar`, or `R_polar`. Its listed Earth value instead uses `R_Earth = 6.371e6 m`.
There is also no canonical function that combines Earth baryon count, Earth
volume, a spation-shell exclusion, inverse-square fall-off, and movement budget
into a dimensionless satellite-to-ground clock ratio.

The inventory preserves the distinction between a primitive equation and the
new GOM20 recovery chain. It does not infer a missing composition or replace
the author-required polar radius with the existing mean-radius constant.
