# Proposal for `hsml_os`: `SDTMetric` first-order clock rate (not applied)

Target: `C:\Users\Jimmi\OneDrive\Desktop\hsml_os\core\math\sdt_metric.hpp` (lines 19–39). Written for the owner of that repository; no file there was edited.

## Finding

`SDTMetric::dilation_factor_from_z(z)` returns `1/√(1 + z)`, with z defined as in `sdt-engine` (z·k² = 1, z = ϟ/r). The validated canon (`Engine/include/sdt/laws.hpp`, relation (3), GOM22 repair) is `dτ/dt = 1 − z`. At first order the Helix form gives a deficit of z/2 where the canon gives z.

Check (Ω_E = 4.434139×10⁻³ m, R_E = 6.371×10⁶ m, r_GPS = 2.656×10⁷ m):

- z_ground = 6.95988×10⁻¹⁰; z_GPS = 1.66948×10⁻¹⁰; Δz = 5.29040×10⁻¹⁰.
- Canon (1 − z): 5.29040×10⁻¹⁰ × 86 400 s = 45.7090 µs/day (equals the GOM20 depth term).
- Helix form: 22.8545 µs/day. Difference 22.8545 µs/day × 2.99792458×10⁸ m/s = 6851.6 m of ranging per day.

The branch `if (redshift < -0.9999) return 0.0;` returns 0 where `1/√(1 + z)` diverges, and `redshift < 0` returns 1.0; neither follows the formula.

## Proposed replacement

```cpp
/// SDT dilation factor from geometric redshift z (z·k² = 1): dτ/dt = 1 − z  (Law V budget, GOM22).
/// Domain 0 <= z <= 1; z >= 1 exhausts the movement budget (v_trans = 0) and returns 0.
/// Negative z is outside the domain and is returned as 1.0 only for continuity at z = 0.
static constexpr double dilation_factor_from_z(double z) {
    if (z <= 0.0) return 1.0;
    if (z >= 1.0) return 0.0;
    return 1.0 - z;
}
```

`dilation_factor_from_k` and `dilation_factor` call this function and need no other change.

## Acceptance test

For Ω_E = 4.434139×10⁻³ m: `(dilation_factor_from_z(z_GPS) − dilation_factor_from_z(z_ground)) × 86400 × 10⁶` equals 45.7090 within 1×10⁻⁴ relative. The speed term (−7.2122 µs/day, from the movement budget, not the depth term) is carried separately and must not be folded into this function.

## Related items in the same repository (read only)

- `docs/operators/CONNECTIONS.md` row C01 states "18 bad samples caught, 10 good passed"; `scripts/check_spherical_purity.ps1 -SelfTest` on 2026-10-16 reports 28 caught and 15 passed.
- `shell/lod.hpp` `cluster()`: all 13 spheres have radius R/3 and the outer centres stand 2R/3 out; the volume fraction per level is 13/27 = 0.4815 and the summed surface grows by 13/9 per level (9.0825 at depth 6). `proxy_of` clamps the Cauchy radius to the holding sphere, which hides an excess of R√(13/9) = 1.2019 R for a one-level cluster.
