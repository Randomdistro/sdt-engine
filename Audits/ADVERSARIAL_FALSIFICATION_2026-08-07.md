# Adversarial Falsification Record — 2026-08-07

## Scope and status

**Task.** Attack the current SDT engine and its live benchmark claims.  This record
tests claim independence, executable integrity, algebraic behaviour, stated initial
conditions, and mechanism-to-instrument correspondence.  It does not treat agreement
with another theory as a failure condition.

**Result.** The current suite is executable and its printed numerical summary is
reproduced.  It does **not** support its headline as a count of independent earned
predictions: three live passing rows are typed or identity-based validations, and the
relay-speed mechanism has an unguarded domain failure.  These findings exclude the
affected claims as validation evidence; they do not by themselves exclude every SDT
claim.

**Initial conditions and evidence standard.**

- Repository state at start: `6e091f6`; pre-existing untracked website ZIP files were
  not touched.
- Canonical files under `Engine/include/sdt/` and `Laws/` were read only.
- The test requires only the repository source, MSVC Build Tools 2022, and no network.
- The benchmark run was compiled from the current source with `/std:c++20 /O2`.
- No new physical constants, fitted values, or modified tolerances were introduced.

## Reproduction log

### Environment check

1. `g++` is not on `PATH`; the README's GCC command cannot run in this environment.
2. `cmake` is installed, but neither root `CMakeLists.txt` nor
   `Benchmarks/CMakeLists.txt` exists.  The README's advertised `cmake -B build` path
   therefore fails before configuration.
3. MSVC Build Tools is installed at
   `C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools`.

### Current-source execution

From the repository root:

```text
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
cl /nologo /std:c++20 /EHsc /O2 /I Engine\include /Fe:.audit-tmp\benchmarks.exe Benchmarks\B01_B25\benchmarks_suite.cpp
.audit-tmp\benchmarks.exe
```

Observed final summary:

```text
RESULTS: 56/67 earned predictions passed (83.6%)
+ 11 consistency identities (definitional; NOT predictions)
+ 2 CALIBRATED (class E, documented; not earned)
0 genuine fail · 11 PENDING (known-open, flagged)
```

The 11 PENDING failures are B06 (nine first-ionisation rows, 6.6%–501.3%) and
B11 (Earth/Jupiter `J2`, 59.3%/202.6%).  Their exclusion from `real_fail` is
implemented intentionally; this audit does not reclassify them.

## Finding F-01 — typed values still count as earned predictions

### Claim falsified

`B15` is labelled `COMPUTED` and `B16` is labelled `DERIVED`, so both contribute to
the `56/67` earned-prediction numerator.

### Mechanism and counterexample

`B15_bao_scale()` assigns `double r_s_sdt = 147.0;` and compares it with 147.09 Mpc.
There is no calculation from the claimed pressure-wave mechanism.  `B16_transport()`
assigns `double exponent_sdt = 0.5000;` and compares that same value with 0.5 three
times.  In each case, replacing every framework expression upstream of the literal
leaves the PASS unchanged.  The output is therefore not independent of the asserted
answer.

This is a recurrence, not a newly discovered class: the primary source
`Investigations/HUNTER_SCOUR_2026-07-02/BENCH_ENGINE.md` already classified B15 and
B16 as hand-written literals and proposed that they be retired from earned counts.
The current source still tallies them.

### Origin of error

The benchmark's certification enum is applied at the call site without an enforced
provenance check.  A comment saying “from detailed SDT computation” is accepted in
place of a dependency-carrying expression or a linked direct assessment.

### Recovery required

Until a deterministic, source-visible calculation is supplied and validated on an
independent held-out observable:

- B15 must be `PENDING`/note-only, not `COMPUTED`.
- B16 must be `PENDING`/note-only, not `DERIVED`.
- The earned denominator and numerator must exclude all four rows.

The required initial conditions for recovery are an explicit decoupling/release time,
sound/relay propagation law, and a dataset plus fitting protocol for each transport
coefficient.  The mechanism must output the values before their comparison anchors are
read.

**Grade:** NO RECOVERY in the current suite; a route to recovery is stated, but no
source-visible calculation presently exists.

## Finding F-02 — B25's “exact NR” row remains a borrowed literal

### Claim falsified

`B25` labels `He binding exact NR [eV]` as `COMPUTED` and counts its PASS.

### Mechanism and counterexample

The row assigns `double E_exact = -79.0052;` and compares it to `-79.005`.  It has no
SDT computation.  The earlier direct audit identifies that literal as the Pekeris
non-relativistic result.  The delete test is decisive: no engine value participates in
the result, so the displayed agreement survives removal of all model mechanism.

### Origin of error

The old audit's correction was not propagated into this live row.  The label changed
from the previously noted issue class, but the source dependency did not change.

### Recovery required

Remove the row from the earned tally immediately.  A future replacement must expose a
native Hamiltonian/energy functional, boundary conditions, numerical method,
convergence test, and a prediction not used to set any coefficient.

**Grade:** NO RECOVERY in the current suite.

## Finding F-03 — B29 is explicitly an identity but is tallied as a computed prediction

### Claim falsified

`B29` counts the GW150914 ISCO-frequency match as `COMPUTED` evidence.

### Mechanism and counterexample

The benchmark feeds `bridge::f_GW_isco(96.0e3)` with the comment that 96 km comes from
the measured 65-solar-mass merger frame.  The engine itself states that this is the
`GM ≡ c²ϟ` bridge applied to the pre-existing ISCO formula and calls it an
“ALGEBRAIC IDENTITY.”  Thus the same observed merger scale is transformed into a
frequency and checked against the frequency from that merger.  It is a unit/variable
re-expression, not an independent prediction.

### Origin of error

`laws.hpp` carries the correct circularity disclosure, but the benchmark label does
not consume it.  The failure is a provenance propagation failure, not a numerical
discrepancy.

### Recovery required

Relabel B29 `IDENTITY` and exclude it from earned counts.  A genuine test requires a
pre-event rule deriving the binary length scale from independent SDT observables, then
predicting a held-out waveform feature (including phase evolution, not only ISCO).

**Grade:** PARTIAL.  The relation is internally consistent; its predictive status is
not earned.

## Finding F-04 — relay-speed map fails as a global mechanism without a domain condition

### Claim falsified

The adopted relation presents `c_far = c_inf (1 - z)^2` and
`depth_from_c_far = 1 - sqrt(c_far/c_inf)` as a relay-speed law and inverse while
claiming a wall at `z = 1`.

### Counterexamples

The implementation accepts all real `z` and has no precondition or guard.

| Input depth | `c_far/c_inf` | returned inverse depth | failure |
|---:|---:|---:|---|
| 1.5 | 0.25 | 0.5 | wrong branch |
| 2.0 | 1.00 | 0.0 | depth aliases to far field |

For all `z > 1`, the squared profile rises again after its zero; it therefore does
not itself define an impenetrable wall or a one-to-one speed-depth relation.  Its
documented inverse silently selects the `z ≤ 1` branch.  The claimed physical domain
may be intended to be `0 ≤ z ≤ 1`, but that is not stated as an initial condition,
enforced in code, or derived from the profile.

### Mechanism-to-instrument mismatch

`shapiro_delay()` evaluates only the first-order expression
`(2ϟ/c) ln(4r1r2/b²)`.  It does not integrate the adopted squared profile.  At solar
depth this is numerically adequate to first order, but it cannot validate the
second-order form selected by the mechanism.  The source's own named discriminant is
a compact-object observation; the current B39 result cannot decide that fork.

### Origin of error

The GOM22 repair correctly diagnosed the prior factor-of-two shortfall, but the
replacement promoted a local first-order agreement into a global profile without
specifying its branch/domain and without changing the instrument to evaluate the full
profile.

### Recovery required

1. State and enforce the physical domain before calling `c_far` or its inverse.
2. Give a mechanism for what happens at and below `z = 1`; otherwise do not call it a
   wall.
3. Replace B39's first-order closed-form check with an exact path integral of the
   proposed profile, including declared ray geometry and endpoint conditions.
4. Pre-register a compact-object dataset and the second-order decision rule between
   `(1-z)^2` and `(1-2z)`.

**Grade:** PARTIAL.  Solar first-order agreement remains a correspondence; the stated
global mechanism is false without the missing domain condition.

## Finding F-05 — advertised build mechanism is false

### Claim falsified

The README and benchmark source advertise CMake builds from the repository root.

### Counterexample

No root `CMakeLists.txt` and no `Benchmarks/CMakeLists.txt` exists.  `cmake -B build`
cannot configure this repository.  The direct MSVC command above is the reproducible
current build path.

### Recovery required

Either add and test the advertised CMake project or correct every build instruction
to the direct compiler path, including the actual benchmark filename.

**Grade:** NO RECOVERY in the current documentation.

## Cascade and corrected ledger

The shared root is **provenance is descriptive rather than machine-enforced**.  A
source file can disclose identity, measured input, calibration, or literal origin,
while the benchmark call site still tallies it as earned.  This root produces F-01,
F-02, and F-03.

The minimal structural correction is a benchmark registration API requiring:

1. input-dependency class;
2. mechanism source or direct-assessment reference;
3. prediction target declared before comparison;
4. whether the target or an equivalent observable occurs in the input chain; and
5. an explicit `IDENTITY`, `CALIBRATED`, `OBSERVED`, or `PENDING` exclusion path.

The registry should reject an earned label for a raw literal unless an independently
verified derivation function is supplied.  This is a proposed correction only; canon
and benchmark source were not changed in this audit.

## What remains unexcluded

This record does not adjudicate the model's remaining derivations solely from these
failures.  In particular, B01/B02, B07, and other rows may still be valid
calculations from their declared inputs; each needs its own delete test and
independence ledger.  The current headline must not be used as evidence for them until
the tally is reclassified.

## Audit-of-audit limitations

- No external dataset was downloaded; all evidence is current-source inspection and
  local execution.
- The full historical investigation corpus was not exhaustively retested.
- No CMake project was reconstructed, because that would conceal rather than document
  the advertised-build failure.
- No canonical source was edited without authorization.
