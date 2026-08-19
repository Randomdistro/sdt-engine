# GOM43 — Deterministic Dynamics Solver Foundation

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · INSTRUMENT NOT YET RUN  
**Date:** 2026-08-16

## Question

Can the validated `sdt::dynamics` koppa N-body kernel and a constrained
three-dimensional rigid-link path be exposed through one deterministic,
portable case/result contract suitable for native and browser WebAssembly
execution?

This investigation qualifies a numerical instrument. It does not promote the
new rigid-body implementation into `Engine/include/sdt/`, and it does not add
flexible beams, contact dynamics, friction, adaptive stepping or closed-loop
mechanisms.

## Frozen architecture

- Point bodies call `Engine/include/sdt/dynamics.hpp` directly.
- Point-body production stepping is fixed-step velocity-Verlet. Fixed RK4 is
  retained as an independent verification route.
- Rigid links use centre position, unit quaternion, linear velocity, angular
  velocity, inertial mass and body-frame diagonal inertia.
- `koppa_m` is optional gravitational source strength and is never inferred
  from rigid-body inertia or inertial mass.
- Open-chain revolute joints constrain coincident body-fixed anchors and a
  declared world hinge axis. Position and velocity constraints are corrected
  iteratively in a deterministic RATTLE-style pass.
- Laboratory pendulums use a declared local uniform acceleration. Its
  provenance records the supplied `v_surface` and `R` when
  \(g=v_{\rm surface}^2/R\) is used.
- Certified execution uses a declared fixed timestep, integer step count and
  integer recording cadence. Rendering clocks never enter the solver.
- C++ owns parsing, validation, execution, classification and hashing. The C
  ABI owns returned buffers until `solver_free` is called.

## Portable contract

Contract version `1.0.0` is frozen in:

- `contracts/sdtcase-1.0.0.schema.json`
- `contracts/sdtresult-1.0.0.schema.json`

Every accepted case supplies a case ID, problem class, inertial Cartesian
frame, force providers, complete initial state, fixed-step declaration,
recording cadence, tolerances and pre-registered gates. Every result returns
the canonical normalized case, solver build ID, laws-header SHA-256, input
hash, terminal status, executed steps, events, diagnostics, gate outcomes,
trajectory and trajectory SHA-256.

Unknown object members, non-finite values, duplicate IDs, unsupported contract
versions, fractional step counts and malformed open chains are rejected before
execution.

## Registered validation gates

Thresholds are fixed before implementation.

### K — contract and determinism

1. **K0 — parser rejection.** Invalid JSON, an unsupported version, an unknown
   problem class, duplicate IDs, a non-unit hinge axis, non-positive timestep,
   non-integral duration/timestep, and an impossible recording cadence each
   return `invalid_case` without executing a step.
2. **K1 — replay determinism.** Two native executions of the same normalized
   case in one build produce byte-identical normalized input, trajectory and
   trajectory hash.
3. **K2 — provenance.** Manifest and every successful result contain a
   64-lowercase-hex laws SHA-256, solver build ID, contract version, compiler
   identity and deterministic floating-point policy.
4. **K3 — C ABI ownership.** `run_case`, `self_test` and `solver_manifest`
   return valid UTF-8 JSON in independently releasable buffers.

### N — koppa N-body qualification

GOM42 V0–V6 are repeated through the shared runner where practical and retain
their registered thresholds.

1. **N0 — pair kernel.** Koppa-weighted acceleration symmetry and
   inverse-square scaling residuals are each at most \(10^{-14}\).
2. **N1 — circular pair.** Over 100 periods at \(P/2000\), maximum separation
   drift is at most \(5\times10^{-5}\) and relative energy drift at most
   \(5\times10^{-6}\).
3. **N2 — eccentric pair.** For \(e=0.5\), 50 periods at \(P/8000\): relative
   energy and angular-momentum drift are each at most \(2\times10^{-5}\);
   measured periapsis and apoapsis are within \(2\times10^{-4}\) of their
   registered values.
4. **N3 — convergence and cross-route.** Timestep halving reduces one-period
   Verlet final-state error by a factor of at least 3.5. Verlet and RK4 final
   states agree within \(2\times10^{-4}\) of registered position and velocity
   scales.
5. **N4 — stable Lagrange triangle.** GOM42's stable source ratio over 20
   periods at \(P/4000\): side drift at most \(10^{-4}\), barycentre drift at
   most \(10^{-10}\) of one side.
6. **N5 — figure eight.** One period at \(P/50000\): RMS position and velocity
   closure errors each at most \(2\times10^{-5}\).
7. **N6 — rotation invariance.** A fixed three-dimensional rotation of the
   figure-eight fixture agrees with the rotated planar result within
   \(10^{-11}\) of registered position and velocity scales.
8. **N7 — Lagrange roots.** Collinear restricted-three-body residuals are at
   most \(10^{-12}\); L4/L5 distances and \(60^\circ\) geometry agree within
   \(10^{-10}\).
9. **N8 — invariants.** Across N1, N2, N4 and N5, normalized momentum drift is
   at most \(10^{-11}\) and normalized angular-momentum drift at most
   \(10^{-10}\).
10. **N9 — contact stop.** A head-on pair returns `collision` before supplied
    contact boundaries overlap.

### R — rigid multibody qualification

1. **R0 — zero-force chain.** A displaced three-link zero-force chain run for
   10,000 steps keeps maximum joint position residual at most \(10^{-9}\) m,
   velocity residual at most \(10^{-9}\) m/s and quaternion norm residual at
   most \(10^{-12}\).
2. **R1 — simple pendulum, small angle.** A one-metre pendulum at
   \(\theta_0=0.05\) rad under declared \(g=9.80665\ {\rm m\,s^{-2}}\), with
   \(\Delta t=5\times10^{-4}\) s, reproduces
   \(T_0=2\pi\sqrt{L/g}\) within \(2\times10^{-3}\).
3. **R2 — finite amplitude.** At \(\theta_0=1.0\) rad with the same length,
   acceleration and timestep, the measured period agrees with
   \(4\sqrt{L/g}K(\sin^2(\theta_0/2))\) within \(3\times10^{-3}\); relative
   mechanical-energy drift is at most \(2\times10^{-3}\).
4. **R3 — double pendulum constraints.** A two-link non-singular fixture run
   for 20 seconds keeps maximum position residual at most \(2\times10^{-8}\) m,
   velocity residual at most \(2\times10^{-8}\) m/s and quaternion norm
   residual at most \(10^{-12}\).
5. **R4 — sectioned chain.** A five-link non-singular fixture run for 10
   seconds satisfies the same residual gates as R3 and terminates normally.
6. **R5 — timestep convergence.** For the small-angle single pendulum, halving
   the timestep reduces final angle error against a finer reference by a
   factor of at least 1.8.
7. **R6 — singular and malformed cases.** Zero inertia, zero link length,
   disconnected/cyclic joint declarations, coincident duplicate joint
   anchors, and a constraint solve that exceeds its registered iteration
   budget return classified failures and no unclassified state.

## Rejection criteria

The instrument is not qualified if a gate fails, if a trajectory requires
case-specific timestep adjustment after execution, if softening or adaptive
stepping is introduced, if browser and native builds execute different source
paths, or if rigid inertia is presented as gravitational source strength.

## Labels and scope

- **VALIDATED:** koppa point N-body path only after N0–N9 pass.
- **CONDITIONAL:** local-uniform-acceleration rigid pendulum path only after
  R0–R6 pass; the approximation and acceleration provenance remain attached.
- **NOT IMPLEMENTED:** flexible bodies, contacts/rebounds, friction, damping,
  motors, closed loops, general spatial hinge networks, adaptive stepping,
  ephemeris ingestion and shadow-cone corrections.

