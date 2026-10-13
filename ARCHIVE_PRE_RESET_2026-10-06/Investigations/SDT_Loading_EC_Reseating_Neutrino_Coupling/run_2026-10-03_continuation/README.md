# Reproduction and artifact ownership

All new execution artifacts reside in the continuation directory. Canonical engines, release sources, public instruments and prior Phase 0 outputs remain preserved. The parent RUN_LOG.md receives appended execution records.

Toolchain: Node v22.14.0, CMake, Visual Studio 2022 MSVC 19.44.35223.0, x64 Release, C++20. Python launcher execution was unavailable; Node performed source hashing and output assembly.

From the repository root:

```powershell
$run = 'Investigations/SDT_Loading_EC_Reseating_Neutrino_Coupling/run_2026-10-03_continuation'
cmake -S $run -B "$run/build" -G 'Visual Studio 17 2022' -A x64
cmake --build "$run/build" --config Release --parallel 4
ctest --test-dir "$run/build" -C Release --output-on-failure
cmake -S $run -B "$run/build-canonical" -G 'Visual Studio 17 2022' -A x64 -DSDT_CANONICAL=ON
cmake --build "$run/build-canonical" --config Release --parallel 4
ctest --test-dir "$run/build-canonical" -C Release --output-on-failure
node "$run/compression_quadrature.js"
```

run.js freezes sources and executes the original nuclear validator through a scoped result-write redirect. The script refuses an existing SOURCE_FREEZE.json; another investigation run requires a distinct directory and preserved prior freeze. Original nuclear validator returns failure for four missing canonical tokens. construction_bridge.json records inventory/degree controls independently of energy and clock claims. finalize.js consumes execution receipts and assembles the scientific-status artifacts; no missing values are supplied as predictions.

Read VERDICT.md together with QUALIFICATION_NOTES.md. Native solver pass labels concern registered numerical gates. Source-comment hash differences, construction assertions, calibration, physical prediction and held-out validation remain separate.
