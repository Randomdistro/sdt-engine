# Chapter 59 — Contracts and Deterministic Sessions

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: a *contract* is a versioned specification of input, output and behaviour; a *session* is a created, advanced, checkpointed and resumed state of a solver; "bitwise replay" means identical bit patterns of the recorded state; a *handle* identifies a session. Executable companion: `Textbook/examples/ch59_contracts_and_deterministic_sessions.cpp`; pre-registration and captured output in `Textbook/validation/`. The GOM43 solver is not in the engine tree. The instrument uses the engine's `sdt::dynamics`, a reference validator written here from the text of `SPHERICAL_CONTRACT_4_0_0.md`, a toy retarded system, and the registration document read as text. It does not run or certify the GOM43 solver. All numbers are constructed (no measured input).

## 59.1 State contracts

Contract 3.0.0 retains the existing inertial state interface. Contract 4.0.0 uses `arena_spherical` SI input with body `locus` $[r,\theta,\varphi]$ and `velocity_locus` equal to null or $[{\rm speed},\theta,\varphi]$. Null denotes zero velocity; a radius-zero place is refused; the caller chooses an arena centre away from the bodies. The spherical version supports 2–64 bodies and velocity Verlet only; the larger-body broad phase and the alternative integrator are not part of its declared scope. A version number therefore specifies behaviour, not merely field spelling. Handles of 4.0.0 lie in $[0x2000000000000000,\,0x4000000000000000)$ and those of 3.0.0 from $0x4000000000000000$ upward.

**Executed (T3).** The reference validator accepted the valid case and the case with a null `velocity_locus`, and refused each of ten malformed cases with a stated reason: radius $0$; radius NaN; one body; 65 bodies; integrator `fixed_rk4`; `contract_version` "5.0.0"; `frame.type` `inertial_cartesian`; a non-finite polar angle; a body at the arena centre; a `velocity_locus` of magnitude $0$ given as a vector (zero velocity must be null). There are 8 distinct refusal reasons (radius $0$, radius NaN and the centre case share one). Handle routing: $0x2000000000000001$ and $0x3fffffffffffffff$ go to 4.0.0; $0x4000000000000000$ and $0x4000000000000001$ to 3.0.0; $0x1fffffffffffffff$ is refused. This is a specification-conformance exercise on the contract text; the registered refusals of the solver itself (E7) are recorded in its own registration.

## 59.2 Sessions and replay

Create, advance, checkpoint, resume and destroy must preserve enough history for retarded evaluation. A checkpoint that contains only the latest positions is insufficient when the force depends on earlier source events. Canonical serialisation and a fixed iteration order support trajectory hashing. Bitwise replay concerns the same build, arithmetic environment and declared state; a different compiler or execution order can give a different bit pattern while the numerical agreement stays; cross-platform determinism needs its own specification and test.

**Replay and order (T1).** Two runs of 2000 steps of `dynamics::step` from the same declared state of five bodies give the same trajectory hash, `53ff9020183b71f2337b3bbc69051ee94a2095e5267f4863f1124f39a186f875` (this build; V1 reproduced the SHA-256 test vector and the two-body acceleration $c^2\varpi/r^2$ to $1.5\times10^{-16}$). The accelerations of eight bodies computed with the body list in six random orders agree to $1.7\times10^{-16}$ relative after mapping back, and $58$ of $144$ components differ in at least one bit: floating-point addition is not associative, so the order of summation is part of the declared state. The engine fixes it by body index.

**Checkpoints and history (T2).** In a toy retarded two-body system (acceleration along the separation to the source position 20 steps earlier, magnitude about $1/d^2$; 1000 steps of $0.01$) an uninterrupted run, a run checkpointed at step 500 with the full history and resumed, and a run checkpointed at step 500 with only the latest positions and resumed behave as follows: the full-history resume equals the uninterrupted run bitwise ($x=\pm9.619907449$); the latest-only resume ends at $\pm9.620207246$, a position difference of $6.0\times10^{-4}$ (registered: above $10^{-6}$). A checkpoint must carry the source history that the force will still read.

## 59.3 Recorded scope limitations

The spherical registration (2026-10-21) records successful replay and geometry checks, and one unmet registered clause. The text, read by the instrument (T4), says: in attempt 1 the gates G1 and E1 were not met; G1 was a defect of the check (the Cartesian-to-locus conversion used $\theta=\mathrm{acos}(z/r)$, whose error near the poles is about $\sqrt\epsilon$: $1.2\times10^{-5}$ for polar observers against $1.6\times10^{-12}$ with $\mathrm{atan2}$, the effect measured in Chapter 58) and was corrected without changing a gate; in attempt 2 G1 is met (200 000 trials, 0 mismatches) and the registered E1 impulse clause is **not met** ($2.34\times10^{-9}$ against $10^{-9}$), reported as such. The registration explains that the body impulse of the Sun–Earth pair is a residual of cancelling terms ($1.2\times10^{25}$ kg m/s against the Earth's $mv=1.8\times10^{29}$ kg m/s) and that a supplementary gate against $mv$ ($1.6\times10^{-13}$) was added after the failure and met; the registered number was not moved. The supplementary normalisation does not erase the registered result.

The recorded source also lists what is not built: a WebAssembly build of 4.0.0 (Emscripten absent), CLI session routing for 4.0.0, OpenMP use for the spherical evaluation, and the 4.0.0 entry in the built-in self-test composition. A textbook description must not promote those unbuilt surfaces into available features. The instrument confirmed that the registration states "no WebAssembly build" and the contract states "No WebAssembly build of 4.0.0 yet" and "Integrator `velocity_verlet` only". The checks that determine conformance are: malformed-input refusal, valid-case completion, checkpoint replay, version routing and bounded history retention; this chapter exercised the first, the third and the fourth on stand-ins and did not run the solver (R59.1).

## 59.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| contract text, registration text | GOM43 folder | read as source text |
| validator cases, handles, toy retarded system | Sections 59.1–59.2 | CONSTRUCTION (no measured input) |
| hashes, differences, bit counts | Sections 59.2 | COMPUTED (this build) |
| gate numbers ($2.34\times10^{-9}$, $1.6\times10^{-13}$, $200\,000$) | registration | quoted from the registration (not re-executed) |

**Residuals.**

* **R59.1 — the solver.** The GOM43 solver was not run; refusal cases, checkpoint replay and version routing were exercised on a reference validator and toy models.
* **R59.2 — cross-platform determinism.** Only the same-build replay was tested.
* **R59.3 — bounded history retention.** No history-retention limit was derived or tested.
* **R59.4 — the registered numbers.** The gate results quoted from the registration were not reproduced here.
* **R59.5 — unbuilt surfaces.** The WebAssembly build, CLI routing, OpenMP use and the self-test entry for 4.0.0 do not exist.

## 59.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch59_contracts_and_deterministic_sessions
```

Criteria were registered in `Textbook/validation/ch59_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch59_run1_output.txt`) met every criterion. Run 2 (`ch59_run2_output.txt`) repeats it after a comment-only edit of the instrument (a wording change in a source comment) with identical output and is the run of record.

## 59.6 Exercises and answers

**Exercise 1.** Why is a version number more than a field name?

*Answer.* It fixes behaviour: the supported body count, integrator, handle space and the refusal rules, which differ between 3.0.0 and 4.0.0.

**Exercise 2.** Why must the summation order be part of the declared state?

*Answer.* Floating-point addition is not associative; reordering the bodies changed bits in 58 of 144 components.

**Exercise 3.** Why does the latest-only checkpoint fail for a retarded force?

*Answer.* The force reads source positions from earlier steps; a checkpoint that substitutes the present position for the earlier ones changes those inputs.

**Exercise 4.** Route the handle $0x3fffffffffffffff$.

*Answer.* To 4.0.0 (it is below $0x4000000000000000$ and at or above $0x2000000000000000$).

**Exercise 5.** Why was the registered E1 impulse ratio ill-conditioned?

*Answer.* It divides a small difference by a residual of cancelling terms: the contracts differ by $2.9\times10^{16}$ kg m/s, which is $1.6\times10^{-13}$ of $mv$ and $2.3\times10^{-9}$ of the residual.

**Exercise 6.** What does a supplementary gate added after a failure establish?

*Answer.* That the bodies' impulses agree to rounding on the better-conditioned scale; it does not change the registered result, which stays reported as not met.

## 59.7 Scope

Established: that the contract's stated refusals and routing can be written as an executable validator; that same-build replay is bitwise reproducible and order-dependent in the last bits; that a retarded system needs its history in a checkpoint; what the registration records as met, unmet and unbuilt.

Not established: the solver's own conformance (R59.1), cross-platform determinism (R59.2), a history-retention limit (R59.3) and the unbuilt surfaces (R59.5).

*Where it leads.* Chapter 60 separates the numerical errors of quadrature, retardation and convergence and tests the order estimate on controlled cases.
