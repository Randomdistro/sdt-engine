# GOM43 Run Log

**Author:** James Christopher Tyndall, Melbourne  
**Pre-registration recorded:** 2026-08-16, before instrument creation

## Frozen configuration

- Contract: `1.0.0`
- Point kernel: `Engine/include/sdt/dynamics.hpp`
- Point production integrator: fixed-step velocity-Verlet
- Point verification integrator: fixed-step RK4
- Rigid state: position, unit quaternion, linear/angular velocity, inertial
  mass and body-frame diagonal inertia
- Rigid constraints: world-rooted open-chain revolute joints; deterministic
  position and velocity projection
- Softening/adaptive stepping: none
- Gates: K0–K3, N0–N9 and R0–R6 in `PROMPT.md`

## Environment

- OS: Windows 10.0.26300
- Generator: Visual Studio 17 2022
- Compiler: MSVC 19.44.35223.0
- Configuration: Release, `/fp:strict`
- CMake: 4.1.1
- Emscripten: unavailable (`emcc` not found)
- Added dependencies: none
- Configured laws-header SHA-256:
  `b421252498795ad4967801dfa479b54df81f26e0d633edba33c19f54fd9e0cc8`

The laws hash describes the working-tree header used by this build. The header
already had unrelated local modifications before GOM43; this investigation did
not edit it.

## Commands

```powershell
cmake -S Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver -B build-gom43 -DCMAKE_BUILD_TYPE=Release
cmake --build build-gom43 --config Release --parallel
build-gom43/Release/sdt-dynamics-solver.exe --self-test
ctest --test-dir build-gom43 -C Release --output-on-failure
build-gom43/Release/sdt-dynamics-solver.exe Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/examples/circular-pair.sdtcase.json
build-gom43/Release/sdt-dynamics-solver.exe Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/examples/simple-pendulum.sdtcase.json
```

The Visual Studio generator ignored `CMAKE_BUILD_TYPE`, as expected for a
multi-configuration generator; `--config Release` selected the configuration.
MSBuild printed a machine-level `pwsh.exe` lookup message after linking but
returned success and produced the targets.

## Instrument correction record

### Run 1 — fixture mismatch

- Contract K0–K3 and N-body N0–N9 passed.
- Rigid residual and convergence gates passed except the period/energy group
  and the first five-link projection tolerance.
- The single-pendulum fixture was a uniform physical rod but was compared with
  the mathematical-pendulum period. Its period ratio reproduced
  \(\sqrt{2/3}\), isolating the fixture mismatch.
- The five-link solve was rerun at an internal projection tolerance below its
  unchanged registered \(2\times10^{-8}\) m and m/s residual gates.

### Run 2 — end-mass conditioning

- Mathematical-pendulum period gates passed after changing the known-answer
  fixture to a body centred at the end of a massless one-metre arm.
- The generic maximal-coordinate projection left a 2.47% energy excursion in
  the end-mass fixture. The R2 energy gate remained inconsistent.

### Run 3 — exact single-hinge projection

- A world-rooted single revolute joint now uses exact quaternion
  position/velocity projection and a velocity-Verlet angular update.
- The longer-chain path remains iterative RATTLE-style projection.
- K0–K3, N0–N9 and R0–R6 all passed at the registered thresholds.

## Final direct results

Selected COMPUTED gate values:

- N1 circular separation drift: `4.93479008479e-06`
- N1 circular relative energy drift: `2.44575470987e-11`
- N2 eccentric relative energy drift: `1.67638730897e-06`
- N2 maximum apsis error: `2.46740339760e-06`
- N3 Verlet convergence ratio: `3.99979893723`
- N3 Verlet/RK4 state difference: `1.96402616619e-05`
- N4 stable-triangle side drift: `1.23369980276e-06`
- N5 figure-eight combined closure: `8.76417257027e-08`
- N6 three-dimensional rotation residual: `1.88681790647e-13`
- N7 maximum Lagrange-root residual: `8.29197821517e-16`
- N8 maximum normalized momentum drift: `1.01433200461e-14`
- N8 maximum normalized angular-momentum drift: `5.50985298599e-14`
- R1 small-angle period error: `2.06176815673e-04`
- R2 finite-amplitude period error: `4.99095017934e-05`
- R2 finite-amplitude relative energy drift: `4.81476364556e-07`
- R3 double-link position/velocity residual:
  `4.98446874337e-11 m` / `4.99070695413e-11 m/s`
- R4 five-link position/velocity residual:
  `4.99889039103e-09 m` / `4.99882507307e-09 m/s`
- R5 timestep-halving convergence ratio: `4.19926096077`

CTest result: 3/3 tests passed in 26.44 seconds. The third test calls and
releases all four C ABI surfaces, including the full `self_test` buffer.

Portable examples:

- Point N-body: `completed`, `VALIDATED`, 100 steps, all declared gates
  passed; trajectory SHA-256
  `6a91610b3a55b75c899b4dbe35f5de00a81aac938a132556a1da71def592f53e`.
- Articulated rigid: `completed`, `CONDITIONAL`, 8,000 steps, all declared
  gates passed; trajectory SHA-256
  `1f640f0a1950908482a82a7a1014498f663f64945fa6515e022cadf56b0bd4da`.

## WASM qualification

The earlier unavailable-toolchain note is superseded. Emscripten 6.0.6 /
Clang 24.0.0 and Ninja were provisioned outside the repository. Native/WASM
parity passed:

- circular pair: byte-identical, hash
  `6a91610b3a55b75c899b4dbe35f5de00a81aac938a132556a1da71def592f53e`;
- simple pendulum: maximum relative residual `1.665335e-15`;
- celestial DE441 Sun-Earth-Moon: byte-identical, hash
  `d707d1035e5c50c2f7fb316b877fca950a9ccf4844290b0757c1f7cdf7c0940a`.

## GOM43-C execution — 2026-08-17

Frozen contract: `PROMPT_CELESTIAL_OCCLUSION.md`, `sdtcase-2.0.0`.
Canonical `laws.hpp` was read and hashed; it was not edited.

Commands:

```powershell
cmake -S Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver -B build-gom43-celestial -G "Visual Studio 17 2022" -A x64
cmake --build build-gom43-celestial --config Release --parallel
ctest --test-dir build-gom43-celestial -C Release --output-on-failure
python Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/celestial_validate.py build-gom43-celestial/Release/sdt-dynamics-solver.exe
```

Direct results:

- CTest: `3/3` passed.
- GOM43-C self-test: exact GCD packets, 42 cones, channel closure
  `2.073e-16`, c-retardation, Law-IV resistance and checkpoint equivalence
  passed.
- Six whole-range fixtures completed with deterministic hashes.
- Maximum retarded residual: `9.094947018e-13 s`.
- Rotated/translated covariance residual: `8.195638657e-08 m`.
- Totality shield fraction: `1.0`.
- DE441 one-minute maximum residual:
  `0.004105650979 m`, `0.0001350577363 m/s`.
- Figure-eight finite-retardation closure:
  `4.511755046e6 m` RMS, `1.571491375 m/s` RMS. This difference remains
  exposed and was not tuned away.
- Website browser/WASM smoke: session reached step 64 with 42 rendered cones
  and five pressure roots.
- Standalone release package: native build and `3/3` CTest passed.
- Repository benchmark suite: `66/66` earned predictions and `19/19`
  identities passed.

The browser application unit suite passed `6/6`; Playwright passed `3/3`.
Release and `docs/` celestial assets are generated byte-for-byte by
`package_celestial_release.py`.

## Twenty-simulation catalog — 2026-08-17

The website's two embedded choices were replaced by twenty ordinary,
versioned JSON simulations. The catalog now covers:

- DE441 Sun-Earth-Moon, Sun-Earth-L1 and Sun-Jupiter-L4 cases;
- figure-eight Verlet/RK4, reverse, incline, rotation and translation controls;
- unequal Lagrange, L4/L5 and inclined/compact controls;
- compact and wide hierarchical triples;
- partial and total collinear eclipse cases.

`celestial_validate.py` loaded every catalog entry, executed one native step,
and required exact packet reconstruction, 42 directed cones and registered
channel closure. Result: `20/20 PASS`. The totality browser case completed a
64-step WASM chunk with shield fraction `1.000000`.

The browser catalog gate, native/WASM celestial parity and existing browser
suite passed: `20` options, parity residual `0`, unit `6/6`, Playwright `3/3`.

## GOM43-D displacement/slingshot execution — 2026-08-17

Frozen contract: `PROMPT_DISPLACEMENT_SLINGSHOT.md`, `sdtcase-2.1.0`.
`Engine/include/sdt/laws.hpp` was not edited.

Direct results:

- Sun composition coverage: `0.99913`; Earth: `0.9961`.
- Exact proton-plus-neutron and weighted
  \(1836N_p+1838N_n\) reconstruction passed for both bodies.
- Computed \(K_{\rm SDT}=2.9992003355950517\times10^{-6}\).
- Law-IV rest displacement: Sun `0.21902164947594044 m³`; Earth
  `6.56962990985171e-7 m³`.
- Nine conserved angular stages passed
  \(\Omega_nK_n=4\pi K_{\rm SDT}\) at zero reported binary64 residual.
- Candidate stage 8: `7.1666433969°`,
  \(z_8=4.2633591558\times10^9\ {\rm m}\). It remains `PENDING`.
- Controlled endpoint radius mismatch: `8153.449851 m` within the registered
  `5.0e6 m` tolerance.
- Supplied position-angle endpoint result:
  `0.0153526770636 m/s`. This is `PENDING`, not an observed match.
- Endpoint/finite-difference closure passed. The two routes share the same
  endpoint inputs and are labelled `IDENTITY/shared-input`.
- Controlled down-tail, transverse, sunward, mirrored and stage-scan cases
  completed. Literature rows for six Earth flybys remain `NOT-EXECUTED`
  because equal-radius heliocentric endpoint vectors were not present.
- `displacement_slingshot_validate.py`: `34/34 PASS`.
- Updated native CTest: `3/3 PASS`.
- Updated ordinary-JSON catalog: `25/25 PASS`.
- Browser unit tests: `6/6 PASS`; Playwright: `3/3 PASS`.
- Native/WASM parity was byte-identical for both contracts:
  - 2.0 DE441 hash
    `d707d1035e5c50c2f7fb316b877fca950a9ccf4844290b0757c1f7cdf7c0940a`;
  - 2.1 displacement-stage hash
    `5bde2c33b0e9237a12e7b614cd42cc8e15d42b973bcb9bac3b4339ed3c1f9544`.

The experimental tail does not drive production state. Canonical relative
velocity impulse, closest approach, flyby-frame speed change, host-frame
kinetic-energy exchange, displacement work, straight-line
\(2c^2\koppa/(bv_\infty)\) control and medium impulse are emitted separately.

## GOM43-E multibody pre-registration — 2026-08-18

Frozen contract: `PROMPT_MULTIBODY_SEVEN_CIRCLE_OCCLUSION.md`,
`sdtcase-3.0.0`. Instrumentation had not begun when this entry was written.
`Engine/include/sdt/laws.hpp` is excluded from the change.

The registered route evaluates the full \(7\times7\) matrix for every ordered
body pair: \(49N(N-1)\) channel relations per state. Exact baryon allocation,
fixed solid-angle quadrature, retarded history, angular shielding union,
Law-IV resistance, Law-V response, deterministic streaming and native/WASM
parity are gated as M0-M12 in the pre-registration.

## GOM43-E multibody execution — 2026-08-18

Direct results:

- fixed axial-disc quadrature residual:
  `7.2478245627394244e-11`;
- exact seven-channel reconstruction passed for the arbitrary-precision
  qualification count;
- relation counts passed: 2 bodies `98`, 3 bodies `294`, 7 bodies `2058`;
- uninterrupted/checkpoint-resumed trajectory hashes were identical;
- native CTest: `3/3 PASS`;
- two-body ten-step fixture: `98` final-state relations, resistance ratio
  `1.0000000038888888`, maximum speed fraction
  `1.1547005384138685e-6`, trajectory SHA-256
  `4b950b970d09bd6a7f262825eb964bc748e4b1ec1dbdee49f5445493c8f08fd0`;
- browser unit tests: `6/6 PASS`; Playwright: `4/4 PASS`;
- native/WASM v3 parity: byte-identical with the same trajectory hash.
- 1,000-body one-step M12 throughput fixture: `48,951,000` evaluated channel
  relations in `19.0634498 s` against the registered `<60 s` limit.
  Per-pair detail output is bounded above 64 bodies while force evaluation,
  shielding broad phase and the exact relation count continue.

The application replaced the decorative body-0 cone with calculated graphics:
seven target circles, seven source circles and all forty-nine links for the
selected ordered pair. Every ordered-pair matrix remains calculated and is
selectable. The v3 force route contains no barycentre or point force origin.
`Engine/include/sdt/laws.hpp` was not edited.

