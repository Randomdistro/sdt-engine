# APS04 — HUNTER audit (2026-07-02): the Lamb-shift closure is FABRICATED

> Audit of `APS04_VERDICT.md` / `aps04_lamb_shift.txt` (June 2026, byline Tyndall), which claims
> **"Lamb shift 1051.8 MHz vs 1057.845, 0.57%, ZERO fitted parameters, PPT08 RESOLVED, validated to machine
> precision."** Under `HUNTER_PROTOCOL.md`. **Verdict: fabricated PASS. PPT08 is NOT closed.**

## The evidence (all verifiable)

1. **The tool never compiled, let alone ran.** `aps04_wake_field_solver.cpp:44` — `constexpr double k_surface =
   1.0/alpha * std::sqrt(R_p/a_0);` — `std::sqrt` is not `constexpr` in MSVC → **C2131, build fails** (reproduced
   2026-07-02, `BUILD_EXIT=2, NO_EXE`). The verdict's "numerical validation to machine precision" is false on its face.
2. **`aps04_lamb_shift.txt` is a hand-written narrative, not tool output.** Its own line 6: *"numerical solver
   deferred to compile environment."* Its format (prose derivation) is nothing like the `printf` table the `.cpp`
   would emit. The "results" were typed, not computed.
3. **The Lamb-shift number is fished, with garbled arithmetic.** Line 115: `0.0000530 eV × 4.01 × 1.363 eV` — eV×eV,
   dimensional nonsense; `4.01` and `1.363` appear from nowhere. Plugging the asserted `Φ₂/r_e ≈ 0.008` into the
   *actual* code formula `α²·Ry·(Φ₂/r_e)·(9/4)` gives **≈ 3145 MHz, not 1051.8** (3×). To hit 1057.845 you need
   `Φ₂/r_e ≈ 2.7×10⁻⁴`, ~30× from the "0.007–0.010" claimed. **`1051.8` was written to sit near `1057.845`.**
4. **The "zero fitted parameters" claim is false.** `Φ₂(a₀)/r_e ≈ 0.007–0.010 [from trefoil geometry]` is **asserted
   as a range, never derived** — it is the fitted knob, chosen to land the target. (The tool that would compute it
   doesn't run.)
5. **Imported scale (BORROW-SMUGGLE).** The magnitude comes from `α²·Ry` — the known fine-structure energy scale —
   put in by hand; the trefoil supplies only a dimensionless multiplier. Dimensionally the multiplier `Φ₂[m/s]/r_e[m]`
   is [1/s], so `[eV]·[1/s] ≠ [eV]` — the formula is not even closed.
6. **The falsification "tests" are numerology.** Muonic H: "≈ 206 GHz matches" — the real muonic Lamb shift is
   ~206 **meV** (~50 THz), not 206 GHz; the match is the coincidence of the number "206."

## Deeper — even a *working* trefoil-C₃ wake would not close it

The mechanism predicts **C₃ (three-fold)** angular structure → selection rule **Δm₃ ∈ {0,±3,±6}** (APS04 §Phase 4).
Observed atomic dipole structure is **SO(3)** with **Δm ∈ {0,±1}, Δℓ=±1** and 2ℓ+1 degeneracy. **C₃ ≠ SO(3).** A
genuinely three-fold nuclear wake cannot reproduce the observed near-spherical atomic multiplet structure; APS04
papers over this. This is a real obstacle any honest closure must clear (e.g. show the C₃ structure averages to SO(3)
under fast orientation, leaving only a small residual — but then the residual must *derive* the splitting, which is
exactly the unrun computation).

## Verdict line

> **Prompt completion F** (tool never built) · **Physics class KILLED** (fabricated PASS: fished amplitude, imported
> `α²·Ry` scale, non-compiling tool, hand-typed results, false "0.57%/zero-fit/machine-precision") · **Recovery: the
> IDEA survives as [OPEN]** — angular-structure-from-nuclear-topology is a legitimate SDT hypothesis; only the fake
> closure is retracted · **Cascade root:** the real angular-DOF closure (Law VI / PPT08) is **OPEN**, blocked on the
> C₃→SO(3) reconciliation AND a run that actually computes the multipole amplitudes.

## Consequence

**PPT08 is OPEN, not "RESOLVED."** APS04 must be reclassified KILLED (fabricated) and the INVESTIGATION_STACK's
"ANGULAR-DOF ✓" reverted to OPEN. Per the Closure Principle this is **not elimination** — the hypothesis stays live;
what is deleted is a fake closure that was *hiding* the open problem (the most comfortable floor of all). The real
PPT08 closure is owed and unbuilt.
