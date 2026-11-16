# Chapter 59 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch59_contracts_and_deterministic_sessions.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). The GOM43 solver is not in the engine tree; this instrument consumes the engine's `sdt::dynamics` and a reference validator written here from the text of `SPHERICAL_CONTRACT_4_0_0.md`, and reads the registration document `SPHERICAL_REGISTRATION_2026-10-21.md` as text. It does not run or certify the GOM43 solver.

Object. (a) Contract 4.0.0 as a versioned behaviour: `arena_spherical` SI input, body `locus` $[r,\theta,\varphi]$, `velocity_locus` null or $[{\rm speed},\theta,\varphi]$, null denoting zero velocity, a radius-zero place refused, 2 to 64 bodies, `velocity_verlet` only, handle space $[0x2000000000000000,0x4000000000000000)$ for 4.0.0 and $0x4000000000000000$ upward for 3.0.0. A reference validator written from that text is exercised on constructed cases: valid, and malformed in each stated way. (b) Deterministic sessions: bitwise replay concerns the same build, arithmetic environment and declared state; a fixed iteration order is part of the declaration, because floating-point addition is not associative: permuting the order of the bodies changes the bit pattern of the accelerations while retaining numerical agreement. (c) Checkpoints: a retarded interaction needs the source history; a checkpoint that holds the full history resumes bitwise-identically to an uninterrupted run, while one that holds only the latest positions does not. (d) Recorded scope limitations: the registration document records one unmet gate (E1, impulse clause $2.34\times10^{-9}$ against $10^{-9}$) and no WebAssembly build; the supplemental normalisation of system momentum does not erase the registered result. Inputs: constructed numbers; the engine's `dynamics::accelerations`; no physical value is read.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | SHA-256("abc") $=$ `ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad`; the engine's two-body acceleration of body 1 toward a source of strength $\varpi$ at distance $r$ is $c^2\varpi/r^2$ | exact; $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | replay and order. Two runs of 2000 steps of `dynamics::step` from the same initial state of 5 bodies give the same trajectory hash; the accelerations of 8 bodies computed in 6 random orders of the body list agree to $10^{-13}$ relative after mapping back and differ in at least one bit | as stated | yes |
| T2 | checkpoints. A toy retarded two-body system (delay 20 steps, 1000 steps): an uninterrupted run, a run checkpointed at step 500 with the full history and resumed, and a run checkpointed at step 500 with only the latest positions and resumed; the first two have identical hashes; the third differs by more than $10^{-6}$ in position at step 1000 | as stated | yes |
| T3 | contract validator. 12 constructed cases: the valid case is accepted; radius $0$; radius NaN; 1 body; 65 bodies; integrator `fixed_rk4`; `contract_version` "5.0.0"; `frame.type` not `arena_spherical`; a non-finite angle; a body at the arena centre (radius 0 in `locus`); a `velocity_locus` of magnitude $0$ given as a vector (refused: zero velocity must be null); and a null `velocity_locus` (accepted) | the valid and null-velocity cases are accepted and each of the 10 malformed cases is refused with a distinct reason; handle routing: $0x2000000000000001\to$4.0.0, $0x3fffffffffffffff\to$4.0.0, $0x4000000000000000\to$3.0.0, $0x4000000000000001\to$3.0.0, $0x1fffffffffffffff\to$refused | yes |
| T4 | recorded scope. The registration text contains "E1", "2.34e-9" and "1e-9" in one sentence recording a gate not met, and "no WebAssembly build" (in the stated limits); the contract text (section 6) contains "No WebAssembly build of 4.0.0 yet" and "Integrator `velocity_verlet` only" | as stated | yes |

Reported, not criteria: the hashes, the permutation differences, the position difference of the latest-only checkpoint.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch59_contracts_and_deterministic_sessions`
