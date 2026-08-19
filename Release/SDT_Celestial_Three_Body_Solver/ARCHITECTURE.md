# GOM43 Solver Architecture

**Author:** James Christopher Tyndall, Melbourne  
**Boundary:** reusable seven-circle geometry in the engine; sessions and
contracts remain investigation/application code

## Data flow

```text
*.sdtcase.json
    |
    v
strict C++ parser and dimensional/structural validation
    |
    +-- point_nbody ------> sdt::dynamics ------> Verlet or verification RK4
    |
    `-- articulated_rigid -> quaternion links --> revolute RATTLE projection
    |
    v
fixed-step recorder -> canonical JSON -> SHA-256 -> *.sdtresult.json
```

Contract `2.0.0` adds a third branch:

```text
celestial_three_body
    -> exact decimal baryon packet ledger
    -> six directed body interactions
    -> seven finite cones per direction (42 total)
    -> c-retarded history interpolation
    -> third-body apparent-disc eclipse overlap
    -> Law-IV engaged-volume resistance
    -> Verlet or verification RK4
    -> body + medium impulse ledger
    -> chunk/checkpoint/resume
```

The pressure deficit is integrated toward the missing external pressure. No
attractive force or force centre is encoded. Baryonic pivots are diagnostics,
not force origins.

Contract `3.0.0` adds arbitrary-N multibody occlusion:

```text
sdt_occlusion_nbody
    -> exact decimal baryon ledger per body
    -> 1 centre + 6 outer circles per pair-facing body section
    -> full 7 x 7 matrix for every ordered body pair
    -> 49*N*(N-1) retarded solid-angle relations per state
    -> nearest-channel angular coverage union
    -> Law-IV displacement resistance
    -> Law-V parallel/perpendicular response below c
    -> Verlet or verification RK4
    -> medium impulse + chunk/checkpoint/resume
```

No barycentre or point centre drives this branch. Every resultant is the sum
of finite channel-area relations to the surrounding blocked angular domain.

Both native and Emscripten targets compile the same `solver.cpp`,
`celestial.cpp`, `occlusion_nbody.cpp`, `self_tests.cpp`, `c_api.cpp` and
headers. There is no
JavaScript numerical path. The Web Worker allocates UTF-8 case JSON, calls the
C ABI, copies the returned UTF-8 result and releases it with `solver_free`.

The celestial website loads `cases/celestial/catalog.json`, then fetches the
selected versioned case as ordinary JSON. The twenty simulations are generated
deterministically by `build_celestial_preset_catalog.py`; scene code contains
no per-case dynamics.

## Source boundaries

- `Engine/include/sdt/dynamics.hpp` remains the validated point-gravity spine.
  GOM43 calls its acceleration, velocity-Verlet, fixed RK4 and invariant
  functions without modification.
- `Engine/include/sdt/occlusion.hpp` is the approved reusable GOM43-E
  seven-circle geometry surface. It provides the deterministic pair frame,
  channel offsets, fixed disc quadrature and Law-V response while reading all
  physical constants and laws from `laws.hpp`.
- `include/sdt_solver/multibody.hpp` is investigation-scope code. It stores
  rigid-link centre state as position, unit quaternion, linear velocity and
  world angular velocity. Inertial mass/inertia and optional koppa source
  strength are separate members.
- `include/sdt_solver/json.hpp` is a dependency-free strict JSON parser and
  canonical writer. Object keys are sorted, duplicate keys are rejected and
  non-finite JSON numbers cannot enter a case.
- `src/solver.cpp` validates version `1.0.0`, executes one of the two solver
  paths, records diagnostics and hashes the canonical input and trajectory.
- `src/celestial.cpp` validates version `2.0.0`, owns arbitrary-precision
  baryon packets, finite cones, retardation, eclipse shielding, Law-IV
  resistance, pressure roots and streaming sessions.
- `src/occlusion_nbody.cpp` validates version `3.0.0`, owns dynamic-N
  retardation/history, exact seven-channel allocations, all 49 ordered-pair
  relations, angular shielding union, Law-IV resistance, Law-V response and
  the high-range session registry.
- `src/self_tests.cpp` executes the frozen K, N and R qualification ladder.
- `src/c_api.cpp` provides `run_case`, `self_test`, `solver_manifest` and
  `solver_free`. Each returned string is an independent `malloc` allocation.
- `src/cli.cpp` is the native file/self-test/manifest interface.
- `src/wasm_entry.cpp` supplies the Emscripten linker target; it contains no
  alternate solver.

## Determinism contract

- Fixed timestep, integral step count and integral recording cadence.
- Stable input ordering from case arrays; no parallel force reduction.
- Native large-N runs may evaluate independent target rows with OpenMP. Each
  target retains fixed source/channel order and no floating-point reduction is
  shared between targets. Emscripten remains serial.
- Canonical JSON uses sorted object keys and 17-digit finite-double output.
- No adaptive stepping, random state, wall clock, locale-dependent number
  conversion or rendering-clock integration.
- Builds disable floating-point contraction and do not enable fast-math.
- Byte-identical replay is required within one build. Native/WASM parity is a
  tolerance-and-hash gate for the UI phase because JavaScript engines and
  native compilers can differ in elementary-function rounding.

The trajectory hash covers the canonical trajectory array, including step,
time, IDs and every recorded state component. The input hash covers the
canonical normalized case. CMake computes the laws-header SHA-256 at configure
time and compiles it into every manifest and result.

For more than 64 bodies, result serialization omits the potentially unbounded
pair/channel detail arrays while reporting the exact evaluated relation count.
The registered 1,000-body one-step fixture evaluates `48,951,000` relations;
the browser therefore remains bounded without changing the computed state.

## Point N-body path

The point path is the GOM42 kernel:

\[
\mathbf a_i=c^2\sum_{j\ne i}\kappa_j
\frac{\mathbf r_j-\mathbf r_i}{|\mathbf r_j-\mathbf r_i|^3}.
\]

Production cases use velocity-Verlet. Fixed RK4 is available as a declared
verification integrator. Collision radii are stop boundaries, not a rebound or
contact model.

## Articulated path

Version 1 supports one world-rooted, root-to-tip open chain. Each joint:

- makes parent and child body-fixed anchors coincident;
- declares one unit world hinge axis;
- projects child orientation to quaternion twist about that axis;
- projects angular velocity onto that axis;
- iterates position and anchor-velocity correction to the declared tolerance.

A single world-rooted hinge uses the same holonomic state with an exact
quaternion position/velocity projection and velocity-Verlet angular update.
Longer chains use deterministic Gauss-Seidel RATTLE-style position and
velocity impulses with full body-frame diagonal inertia transformed to world
coordinates.

Local uniform acceleration is conditional physics. The case must attach a
provenance classification and description; `v_surface_m_s` and `radius_m` may
be supplied together when the acceleration was obtained from
\(g=v_{\rm surface}^2/R\).

## Build paths

Native MSVC:

```powershell
cmake -S Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver -B build-gom43
cmake --build build-gom43 --config Release --parallel
ctest --test-dir build-gom43 -C Release --output-on-failure
```

Emscripten after activating a pinned SDK:

```powershell
cmake -S Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver `
  -B build-gom43-wasm `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_TOOLCHAIN_FILE=Investigations/06_Gravitation_and_Orbital_Mechanics/GOM43_Deterministic_Dynamics_Solver/cmake/emscripten-toolchain.cmake
cmake --build build-gom43-wasm --parallel
```

The WASM build emits `sdt-dynamics-core.js` and
`sdt-dynamics-core.wasm`. The module is worker-only, modularized as
`createSdtDynamicsModule`, has no filesystem, allows memory growth and exports
  the solver and session functions plus allocation functions.

## Physics status

- **VALIDATED:** point N-body kernel and fixed-step runner, subject to the
  declared case and collision-stop scope.
- **CONDITIONAL:** coplanar open-chain rigid links under a declared local
  uniform acceleration.
- **COMPUTED:** the registered retarded seven-cone celestial route and explicit
  Law-IV proton/neutron displacement ledger.
- **COMPUTED:** the arbitrary-N full 7×7 retarded solid-angle route where the
  GOM43-E M0-M12 gates pass.
- **PENDING:** transported anti-solar displacement-tail concentration,
  endpoint slingshot formulation and terminal-stage selection. This branch
  cannot modify production state.
- **NOT IMPLEMENTED:** adaptive stepping, closed loops, general spatial hinge
  networks, flexible links, damping, friction, motors and collision response.

## Contract 2.1 displacement branch

`sdtcase-2.1.0` is backward-compatible at the dispatcher boundary: existing
2.0 cases retain 2.0 outputs. A 2.1 body may carry exact decimal-string
`proton_count` and `neutron_count` values. Their sum must reconstruct the
declared baryon count before execution. The native and WASM core computes:

\[
V_0=N_pV_{\rm disp}(m_p)+N_nV_{\rm disp}(m_n),\qquad
V_{\rm eng}=V_0d,\qquad V_{\rm eff}=V_0(1+d),
\]

where \(d\) is the already calculated seven-cone occlusion depth. Resistance
continues through canonical `law_IV::resistance_from_engaged_volume`.

The optional slingshot block binds host, flyby and runner IDs, an equal-radius
endpoint, reference Sun/Earth separation and a flyby koppa comparison input.
It emits the instantaneous anti-solar axis, \(x_{\rm pause}\), nine conserved
solid-angle stages, endpoint position angles, canonical impulse/energy
ledgers, straight-line control and non-driving on/off ablation. The scene
renders these values only after C++/WASM calculation; no renderer value is
returned to the solver.

## Engine boundary

The approved `sdt/occlusion.hpp` promotion contains geometry and response
primitives only. Contract parsing, exact decimal ledgers, retarded history,
sessions, diagnostics and browser state remain in GOM43. `laws.hpp` was not
edited.

