# Reproduction
Run commands from the repository root. Preserve SOURCE_FREEZE.json and use a separate directory for a new frozen experiment.

```powershell
$run = 'Investigations/SDT_Alpha_Contact_Energy_Phase_Closure/run_2026-10-03_01'
node "$run/baseline.js"
node "$run/original_controls.js"
cmake -S $run -B "$run/build" -G 'Visual Studio 17 2022' -A x64
cmake --build "$run/build" --config Release --parallel 4
& "$run/build/Release/sdt_alpha_controls.exe" | Set-Content -Encoding UTF8 "$run/NATIVE_CONTROLS.json"
ctest --test-dir "$run/build" -C Release --output-on-failure
py -3 -B "$run/geometry.py"
py -3 -B "$run/braid_geometry.py"
py -3 -B "$run/contact_reseat.py"
py -3 -B "$run/constraints.py"
py -3 -B "$run/joint_response.py"
py -3 -B "$run/overlap_control.py"
py -3 -B "$run/magnetic_far.py"
py -3 -B "$run/path_work.py"
node "$run/radial_control.js"
py -3 -B "$run/radial_geometry.py"
node "$run/radial_energy.js"
py -3 -B "$run/assemble_report.py"
```

Toolchain: Python3.13, NumPy2.2.5, SciPy1.16.3; Node22.14.0; CMake/MSVC19.44 C++20 x64 Release. Native compiler flags /fp:strict. The build emitted a nonfatal missing pwsh post-build message; executable and CTest executed successfully. No PowerShell7 dependency was added.
Read VERDICT.md, DERIVATION.md and MECHANISM_INTERFACES.md together. No source-wide physical absence claim is based solely on a constant namespace: NP06, NP17, FLM15, actual NSEQ implementations and native observable maps were inspected. Source-comment labels, proxy scores, kinematic constraints and physical closure retain separate statuses.
