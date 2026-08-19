# Redshift-Correction Bookkeeping Demonstration

A dependency-free C++20 audit harness for explicit, per-record redshift
correction bookkeeping. It accepts signed correction terms and flags that state
whether each term has already been applied by the source catalogue. This makes
double subtraction visible and testable.

This repository is not affiliated with, endorsed by, or certified by NASA,
JPL, Caltech or the SPHEREx mission. The executable is a software demonstration,
not a SPHEREx pipeline product or cosmological result.

## Withdrawal of the former solve

The former CQ18d/e/f H0 result is withdrawn. It used ten selected calibrators
below a standard Hubble-flow cut, hand-assigned position-angle factors,
double-subtracted observer-frame terms, and depended on a cosmological residual
while claiming to replace it. The numerical landing near a CMB value is not
evidence.

Those three sources remain in the folder for provenance, are excluded from
CMake, and intentionally stop compilation unless a researcher explicitly
defines `SDT_ENABLE_WITHDRAWN_CQ18`.

The rebuilt package makes no claim to resolve the Hubble tension or remove the
Great Attractor. Its only result is whether supplied correction terms were
applied exactly once.

---

## Files

| File | Purpose |
|---|---|
| `redshift_bookkeeping_demo.cpp` | Validated CSV parser, correction ledger, sensitivity output and JSON summary |
| `examples/synthetic_redshift_components.csv` | Synthetic known-answer fixture; not observational data |
| `DEMONSTRATION_PROTOCOL.md` | Pre-registered scope, schema and R0–R6 gates |
| `RUN_LOG.md` | Preserved first run and gate results |
| `cq18d/e/f_*.cpp` | Withdrawn sources retained for provenance and excluded from the build |
| `sdt/include/laws.hpp` | Complete standalone export of the canonical header |
| `CMakeLists.txt` | Standalone build configuration and export-integrity check |

The package compiles against the included `sdt/include/laws.hpp`; it does not
require the repository's `Engine/` tree. The exported header's SHA-256 is
`F0E74D150E139AF3534F5FEC4CFD3D90B85A4E9EFA08E36AAD1D1462BFE57942`.
When configured inside the repository, CMake also verifies that the export is
byte-identical to `Engine/include/sdt/laws.hpp`.

## Building

From the repository root:

```powershell
cmake -S Release/JPL_SPHEREx_H0_Correction -B build-jpl-redshift
cmake --build build-jpl-redshift --config Release
ctest --test-dir build-jpl-redshift -C Release --output-on-failure
```

GCC/Clang use the same CMake commands; omit `--config Release` for a
single-configuration generator.

## Input schema

```text
id,distance_mpc,z_input,
z_host_grav,z_host_rotation,z_observer_motion,z_other,
host_grav_already_applied,host_rotation_already_applied,
observer_motion_already_applied,other_already_applied
```

Correction terms are signed. An `*_already_applied` flag of `1` means the input
catalogue has already removed that component, so this program subtracts zero for
it. A flag of `0` means the term remains in `z_input` and is subtracted once.
Malformed values, non-binary flags, duplicate identifiers and non-positive
distances are rejected.

The program does not infer any correction from a source name, sky coordinate,
catalogue frame or target H0. Those terms and their provenance belong upstream.

## Running the synthetic demonstration

```powershell
build-jpl-redshift/Release/redshift_bookkeeping_demo.exe `
  --input Release/JPL_SPHEREx_H0_Correction/examples/synthetic_redshift_components.csv `
  --output-csv redshift_results.csv `
  --output-json redshift_summary.json `
  --fixture-gates
```

The bundled fixture contains five synthetic records generated to test the
instrument. Four low-z rows recover the registered synthetic value exactly;
one `z=0.2` row verifies that the linear `cz/d` diagnostic is suppressed outside
the declared `z <= 0.1` scope. All R0–R6 gates pass.

## Outputs

- CSV: residual redshift, corrections actually subtracted, low-z linear
  diagnostic where permitted, and leave-one-component-in sensitivity deltas.
- JSON: schema version, source path, row counts, gate statuses,
  `scientific_result=false`, and `external_target_h0=null`.
- Process status: `0` only when every active gate passes; `1` for a failed gate;
  `2` for malformed input or invocation.

---

## License

Apache 2.0 — free for research and academic use with attribution.  
See [LICENSE](LICENSE).

**Author:** James Christopher Tyndall — Melbourne, Australia
