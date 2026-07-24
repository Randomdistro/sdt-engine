# APS04 — Direct re-run verdict: first real execution of the solver (2026-07-23)

> **Run class: DIRECT** (main session, no agents). Agent-era outcome layer deleted 2026-07-23
> (README, VERDICT, HUNTER_AUDIT, ANGULAR_QUANTISATION, TREFOIL_WAKE, aps04_lamb_shift.txt — all
> git-recoverable; the fabrication record persists in `HUNTER_SCOUR_2026-07-02/MASTER_LEDGER.md`).
> Tool: `aps04_wake_field_solver.cpp` — **compiled for the first time ever** (g++ 15.2 accepts the
> constexpr sqrt MSVC rejected as C2131). Exit **2**. Output: `aps04_rerun_2026-07-23.txt`.

## Prompt contraband check — CONTAMINATED (Phase 4)

Phases 1–3 (wake geometry, multipole decomposition, energy splitting) are **native** (Biot-Savart
and Legendre polynomials as mathematical tools only). **Phase 4 imports the QM wavefunction:**
"single-valued wavefunction requires ψ(φ+2π/3)=ψ(φ) … for ψ ∝ e^{imφ}" — that is the QM
quantisation postulate, a **prohibited input**. Phase 4 as written must not be run; the angular
quantisation needs a native re-pose (periodicity of a physical circulation pattern, no ψ).

## What the first real run measured

| quantity | today's output | expectation | verdict |
|---|---|---|---|
| Φ₀ radial exponent | **−2.99** | −1.0 (Coulomb) | FAIL |
| Φ₂ radial exponent | **−0.00**, RMS overflow | −3.0 | FAIL (broken fit) |
| Φ₃ radial exponent | −3.07 | −4.0 | FAIL |
| Lamb shift prediction | **−2.05e16 MHz** | 1057.845 MHz | FAIL by 16 orders + wrong sign |

The tool's own printed verdict: **PARTIAL/FAIL** on all three counts.

## Verdict

- **Prompt completion: F** · **Physics class: KILLED-as-implemented / OPEN-as-posed.**
- **The fabrication is now confirmed by execution, not just audit:** the solver that "produced
  1051.8 MHz" produces, when actually run, a number 16 orders of magnitude away with the wrong
  sign. There was never a computation behind the claim.
- What survives: the *hypothesis* (angular structure from the trefoil wake's C₃ asymmetry) is
  untested, not falsified — the current solver's field sampling/fit machinery is broken (Φ₂ fit
  overflow, monopole exponent −3 suggests the sampled field is dominated by a near-field or
  normalisation error). **PPT08 / the SDT Lamb amplitude remains OPEN and unbuilt.**
- Rebuild path (for a future direct pass): fix the field normalisation + fit windows (Phases 1–3
  only), pre-commit exponent gates before running, and re-pose Phase 4 natively (no ψ).
- **Recovery: NO RECOVERY** · **Cascade root:** claim-false at the implementation level;
  mechanism unadjudicated.
