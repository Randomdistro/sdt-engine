# GOM43 Assessment — Deterministic Dynamics Solver Foundation

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-18  
**Assessment:** NATIVE/WASM CORE QUALIFIED · ARBITRARY-N 7×7 OCCLUSION COMPUTED · DISPLACEMENT EXPLICIT · TAIL PENDING

## Result

The versioned case/result contracts, deterministic fixed-step runners,
streaming C ABI and native/WebAssembly paths passed their registered gates.

The point N-body route directly reuses `sdt::dynamics`. GOM42's pair,
circular, stable-triangle, figure-eight, invariant and collision gates passed,
and the missing GOM10-style eccentric-orbit, RK4 cross-check,
three-dimensional rotation and Lagrange-root gates also passed.

The investigation-scope rigid module passed:

- quaternion normalization and zero-force-chain gates;
- simple-pendulum small-angle period;
- finite-amplitude elliptic-integral period and energy drift;
- double-link and five-link position/velocity residual gates;
- timestep-halving convergence;
- malformed-chain classification.

## Classification

- **VALIDATED:** the koppa point N-body kernel and deterministic runner for the
  declared inverse-square, collision-stop and fixed-step scope.
- **CONDITIONAL:** the coplanar open-chain revolute rigid-body path under a
  case-declared local uniform acceleration.
- **QUALIFIED:** native/WebAssembly output parity. The circular-pair result was
  byte-identical, including trajectory SHA-256. The simple-pendulum trajectory
  differed only in elementary-function rounding: maximum absolute and relative
  numeric residual `1.665335e-15`; both native and WASM runs passed all gates.
- **COMPUTED:** the GOM43-C retarded seven-cone celestial route, including
  exact baryon packets, c-retardation, Law-IV resistance, eclipse shielding,
  medium impulse, pivots, pressure roots and checkpoint replay.
- **COMPUTED:** the GOM43-E arbitrary-N route, including full
  \(7\times7\) target/source channel matrices for every ordered body pair,
  fixed solid-angle quadrature, c-retardation, angular shielding union,
  Law-IV resistance, Law-V response and checkpoint replay.
- **NOT IMPLEMENTED:** adaptive stepping, flexible links, contacts/rebounds,
  damping, friction, motors, closed-loop mechanisms, general spatial hinge
  networks and flexible shadow media outside the registered seven-cone route.

## Celestial qualification

All six editable whole-range fixtures completed with 42 directed cones,
exact packet reconstruction, channel closure, c-retardation and body-plus-
medium momentum closure:

- DE441 Sun-Earth-Moon one-minute maximum residual:
  `0.004105650979 m`, `0.0001350577363 m/s`;
- translated/rotated covariance residual: `8.195638657e-08 m`;
- total-eclipse shield limiting value: `1.0`;
- maximum registered retarded residual across the fixture campaign:
  `9.094947018e-13 s`;
- figure-eight finite-retardation closure observation:
  `4.511755046e6 m` RMS and `1.571491375 m/s` RMS after one registered
  point-koppa period.

The figure-eight difference is exposed as the finite-retardation result; it
was not removed by tuning. The celestial DE441 native and WASM outputs were
byte-identical, including trajectory SHA-256
`d707d1035e5c50c2f7fb316b877fca950a9ccf4844290b0757c1f7cdf7c0940a`.

The public instrument additionally exposes twenty-five versioned JSON simulations.
All twenty-five passed the native one-step catalog gate with exact packet
reconstruction, 42 directed cones and channel closure. The set includes the
six whole-range fixtures plus reverse, inclined, rotated, translated, RK4,
hierarchical and eclipse-limiting controls. These are distinct declared
initial-value problems; transformed controls are labelled `COMPUTED`, not
additional observed systems.

## Displacement and slingshot extension

Contract 2.1 adds exact material-derived proton/neutron ledgers without
changing the 2.0 cases or `laws.hpp`. The qualified production route now
reports each body's rest, engaged and effective Law-IV displacement volumes
instead of leaving the displacement implicit in a scalar resistance ratio.

The Sun/Earth composition ledgers cover `99.913%` and `99.61%` of registered
atomic mass respectively and reconstruct exact integer \(N_p\), \(N_n\) and
weighted trefoil burden. They calculate
\(K_{\rm SDT}=2.9992003355950517\times10^{-6}\).

The anti-solar concentration branch is not promoted to production:

- stages \(n=0\ldots8\) conserve \(\Omega_nK_n\);
- stage 8 gives `7.1666433969°` and `4.2633591558e9 m` at the registered
  Earth/Sun separation;
- stage 8 remains a candidate because no terminal local-equalisation gate was
  derived;
- the supplied equal-radius position-angle endpoint value and its telescoping
  finite-difference integral are `PENDING` and `IDENTITY/shared-input`;
- the branch is non-driving, so its on/off ablation leaves canonical state
  unchanged by construction.

The controlled campaign passed `34/34` displacement/slingshot gates and the
expanded catalog passed `25/25` one-step structural gates. Six literature
flyby rows are retained as `OBSERVED` comparisons and `NOT-EXECUTED`; their
published summary data do not contain the equal-radius heliocentric position
vectors required by the registered endpoint formula.

## Arbitrary-N seven-circle execution

Contract 3.0 replaces the laboratory point-body production route with finite
pair-facing sections. A state with \(N\) bodies evaluates
\(49N(N-1)\) relations. Exact centre/outer baryon allocations use
\(1/9\) and \(4/27\) weights and reconstruct every decimal-string input.

Direct qualification produced:

- 2 bodies: `98` directed channel relations;
- 3 bodies: `294`;
- 7 bodies: `2058`;
- fixed axial-disc quadrature relative residual:
  `7.2478245627394244e-11`;
- native CTest: `3/3`;
- browser unit tests: `6/6`; Playwright: `4/4`;
- native/WASM v3 fixture parity: byte-identical, trajectory SHA-256
  `4b950b970d09bd6a7f262825eb964bc748e4b1ec1dbdee49f5445493c8f08fd0`.
- 1,000 bodies, one step: `48,951,000` channel relations in
  `19.0634498 s`, passing the registered `<60 s` M12 threshold.

The browser renders the selected ordered pair as fourteen physical channel
circles and one batched set of all forty-nine calculated links. It computes
every other ordered-pair matrix in the same C++/WASM state and exposes them
through the pair selector. No barycentre or point source enters the v3 force
calculation or its occlusion graphics.

For states above 64 bodies, pair/channel detail serialization is bounded while
the solver still evaluates the registered relation count. Native large-N
execution parallelizes independent target rows; each row keeps fixed source
and channel order. The Emscripten path remains serial.

## Provenance

The native Release build used MSVC 19.44.35223.0 and embedded laws-header
SHA-256
`b421252498795ad4967801dfa479b54df81f26e0d633edba33c19f54fd9e0cc8`.
The browser worker build used pinned Emscripten 6.0.6 / Clang 24.0.0. Its
circular-pair trajectory hash matched native at
`6a91610b3a55b75c899b4dbe35f5de00a81aac938a132556a1da71def592f53e`.
The simple-pendulum native and WASM trajectory hashes were respectively
`1f640f0a1950908482a82a7a1014498f663f64945fa6515e022cadf56b0bd4da`
and
`32fdffe77b03be895475683ece0f215a32db56bee8c73bc2cb6258af60e91b52`;
the declared tolerance comparison passed.
The full selected numerical record is in
`native_self_test_summary.json`; thresholds and correction history are in
`PROMPT.md` and `RUN_LOG.md`.

The UI package vendors Three.js 0.185.1 under its MIT licence and pins
Playwright Test 1.62.1 for browser validation. The Emscripten and browser
toolchain caches remain outside the repository. Ninja 1.13.0 was installed as
an external build tool. The approved `Engine/include/sdt/occlusion.hpp`
contains reusable seven-circle geometry and Law-V response. `laws.hpp` was
not edited. A standalone release, website instrument and byte-mirrored
`docs/` assets were published.

## Promotion

Only the geometry/response primitives are promoted to
`Engine/include/sdt/occlusion.hpp`. The v3 contract, decimal ledgers,
retarded session, diagnostics and application remain at the
investigation/release boundary.

