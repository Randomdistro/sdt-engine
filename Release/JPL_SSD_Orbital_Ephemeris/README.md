# Horizons Kinematics Demonstration

A dependency-free C++20 demonstration that reads a NASA/JPL Horizons geometric
vector table, estimates the central kinematic length `koppa = mu/c²`, propagates
the first state with a two-body velocity-Verlet kernel, and reports residuals
against every supplied Horizons state.

This repository is not affiliated with, endorsed by, or certified by NASA,
JPL, Caltech, Horizons, or SPICE. The executable is a research demonstration,
not mission-navigation or flight software.

## What this establishes

The program establishes that a Horizons state history can be consumed and
re-expressed using:

```text
koppa = mu/c²
a(r)  = -c² koppa r/|r|³
```

The form is algebraically equivalent to using the central gravitational
parameter `mu`. It does not improve DE441, replace an ephemeris, remove the need
for perturbations, or provide independent evidence merely by agreeing with the
data that supplied its estimate.

The value of the demonstration is operational: explicit provenance,
whole-range residuals, deterministic output, no hidden fit, and a compact
length-valued parameter that never separates `G` and source mass.

## Files

| File | Purpose |
|---|---|
| `jpl_horizons_demo.cpp` | Horizons parser, radial estimator, two-body propagator and CSV/JSON writer |
| `examples/jpl_horizons_earth_heliocentric_2002_157_160.csv` | Unedited 397-row DE441 Earth/Sun fixture |
| `DEMONSTRATION_PROTOCOL.md` | Pre-registered scope, algorithm and pass/fail gates |
| `RUN_LOG.md` | Preserved first run and gate results |
| `sdt/include/laws.hpp` | Complete standalone export of the canonical constants and T17 bridge functions |
| `CMakeLists.txt` | Standalone build configuration and export-integrity check |

The package compiles against the included `sdt/include/laws.hpp`; it does not
require the repository's `Engine/` tree. The exported header's SHA-256 is
`F0E74D150E139AF3534F5FEC4CFD3D90B85A4E9EFA08E36AAD1D1462BFE57942`.
When configured inside the repository, CMake also verifies that the export is
byte-identical to `Engine/include/sdt/laws.hpp`.

## Building

From the repository root:

```powershell
cmake -S Release/JPL_SSD_Orbital_Ephemeris -B build-jpl-orbit
cmake --build build-jpl-orbit --config Release
ctest --test-dir build-jpl-orbit -C Release --output-on-failure
```

GCC/Clang use the same CMake commands; omit `--config Release` for a
single-configuration generator.

## Running the bundled demonstration

```powershell
build-jpl-orbit/Release/jpl_horizons_demo.exe `
  --input Release/JPL_SSD_Orbital_Ephemeris/examples/jpl_horizons_earth_heliocentric_2002_157_160.csv `
  --output-csv horizons_results.csv `
  --output-json horizons_summary.json `
  --fixture-gates
```

For another Horizons table, omit `--fixture-gates`. The parser requires
`VECTORS`, geometric Cartesian states, CSV-format rows bounded by `$$SOE` and
`$$EOE`, and `KM-S` output units.

## Outputs

- CSV: one reference state and one propagated state per input epoch, with
  position and velocity residuals.
- JSON: source metadata, estimator, integrator, cadence, row count, residual
  extrema and every gate result.
- Process status: `0` only when every active gate passes; `1` for a failed gate;
  `2` for malformed input or invocation.

## Registered reference run

The complete bundled DE441 interval produced:

- 397 rows at a nominal 900-second cadence;
- median `koppa = 1483.389092 m`;
- relative median absolute deviation `0.00064297`;
- maximum two-body position residual `1237.233 km`;
- maximum velocity residual `0.00563532 km/s`;
- all registered O0–O5 gates passed.

The residual is expected: the demonstration uses one central parameter and does
not model Earth–Moon motion, planetary perturbations, relativity or DE441's
complete force model.

## License

Apache 2.0 — free for research and academic use with attribution.  
See [LICENSE](LICENSE).

**Author:** James Christopher Tyndall — Melbourne, Australia
