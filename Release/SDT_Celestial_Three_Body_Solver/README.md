# SDT Celestial and Multibody Solver 3.0.0

A deterministic C++20, C ABI and WebAssembly instrument for arbitrary
three-body initial-value problems using retarded seven-cone baryonic
occlusion. It calculates a pressure deficit, not attraction: each of
three body pairs carries two co-facing 6-around-1 cross-sections,
producing 42 directed cones. Occlusion travels at `c`; body response
uses canonical Law-IV proton/neutron displacement and reorganisation
resistance. A separately classified transported-tail route is emitted
as a non-driving `PENDING` slingshot diagnostic.

Author: James Christopher Tyndall, Melbourne.

## Included

- dependency-free versioned JSON contracts;
- arbitrary-N full 7×7 channel matrices, giving
  `49*N*(N-1)` retarded solid-angle relations per state;
- fixed-step velocity-Verlet and verification RK4;
- exact arbitrary-precision baryon GCD/packet ledger;
- finite cone/sphere intersections and eclipse shielding;
- retarded history, chunked sessions, checkpoints and resume;
- baryonic pivots, calculated pressure L1-L5 roots and point-koppa
  comparison ledger;
- synchronized NASA/JPL Horizons DE441 Sun-Earth-Moon fixture;
- twenty-five ordinary-JSON simulations spanning JPL, spacecraft,
  Trojan, figure-eight, Lagrange, hierarchical, covariance, eclipse
  and controlled slingshot cases;
- provenance-recorded Sun/Earth 98%+ composition, exact proton/neutron
  counts, weighted trefoil burden and Law-IV displacement ledgers;
- native and browser demonstrators from the same C++ source path;
- `QUALIFICATION_MANIFEST.json` with exact toolchains, floating-point
  policy, canonical-laws hash, fixture hashes and release-gate results.

## Native build

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
.\build\Release\sdt-celestial-solver.exe --celestial-self-test
.\build\Release\sdt-celestial-solver.exe examples\celestial\jpl-sun-earth-moon-j2000.sdtcase.json
```

The CLI also accepts `--chunk CASE STEPS` and
`--resume CASE CHECKPOINT STEPS`. Omitting both `duration_s` and
`max_steps` creates a caller-controlled session.

## Browser

Serve `web/` over HTTP. Open `index.html` for the fixed-three-body
instrument or `dynamics-lab/index.html` for arbitrary-N seven-circle
occlusion. Both workers invoke only the exported C++/WASM ABI;
rendering clocks never advance solver state.

## Scope

The transported anti-solar tail and stage-8 termination are `PENDING`;
they do not alter production state. The point-koppa output is an
`IDENTITY/shared-input` comparison. The
retarded finite-cone route is `COMPUTED` where its registered gates
pass. JPL values are `OBSERVED` comparisons and are not fitted. This
numerical IVP instrument is not a closed-form solution of the general
three-body problem and is not flight software.
