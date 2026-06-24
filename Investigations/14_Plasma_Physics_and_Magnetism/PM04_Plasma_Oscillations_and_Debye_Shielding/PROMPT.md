# PM04 — Plasma Oscillations and Debye Shielding

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use native wake-circulation units, koppa, traction `T=3(W+1)`.

## Question

A plasma is a population of free vortices (electrons) in a relay lattice. Displace them and the
collective occlusion pulls back; thermal agitation smears the response over a length. **Can the
plasma frequency `ω_p` and the Debye length `λ_D` be derived as the natural restoring oscillation and
screening scale of the collective vortex population — from occlusion + the movement budget, with no
imported `E` field and no magneton?** Charge enters only as EMC03 handedness; the restoring push is
the same Law-III occlusion that holds the electron at the electropause.

## SDT mechanism & hypotheses

Bulk-displace the vortex population and you uncover a net occlusion imbalance (surplus on one side,
deficit on the other, EMC03); that imbalance pushes the population back, overshoots, and rings — a
collective oscillation. A test vortex's wake is screened because nearby vortices rearrange to occlude
its convergence surplus over a thermal smear-length.

- **H1 (ω_p as restoring ring):** rigid displacement `δ` of `n` vortices → restoring occlusion push
  `∝ n δ` → SHM at `ω_p`; recover the `ω_p ∝ √(n/m)` form (the `e²/ε₀` group = native occlusion gain).
- **H2 (λ_D as smear length):** thermal velocity (movement budget, Law V) vs restoring push sets a
  screening length; recover `λ_D ∝ √(T/n)` and the **exponential** screening of a test wake.
- **H3 (Bohm sheath / dispersion):** Langmuir dispersion `ω²=ω_p²+3k²v_th²` from relay propagation of
  the restoring imbalance — a finite relay speed gives the thermal correction natively.

## Strategy

**Phase 1 — Restoring oscillation.** Rigid-shift a vortex slab; compute the net occlusion push.
*Goal:* `ω_p`. *Method:* slab model + SHM fit. *Success:* `ω_p` matches the standard form to <1%
(native gain identified, not the SI `e²/ε₀m`).

**Phase 2 — Screening length.** Add a thermal velocity distribution (Law V budget). *Goal:* `λ_D`.
*Method:* balance smear vs restoring. *Success:* `λ_D` form recovered; test-wake potential
**exponential** with decay `λ_D` to <2%.

**Phase 3 — Dispersion.** Propagate the imbalance at finite relay speed. *Goal:* `ω(k)`.
*Method:* lattice dispersion. *Success:* `ω²=ω_p²+3k²v_th²` slope (the factor-3) reproduced or flagged.

**Phase 4 — Coupling check.** Tie `ω_p`/`λ_D` to PM01 swirl (magnetised plasma → upper-hybrid).
*Goal:* `ω_uh²=ω_p²+ω_c²`. *Method:* add PM01 field. *Success:* upper-hybrid form recovered.

## Success criteria

- ✅ **PASS (A):** `ω_p`, `λ_D`, exponential screening all native from occlusion+budget, zero fitted params.
- ✅ **QUALIFIED (C):** forms reproduced; the O(1) dispersion factor (3) flagged as coarse-graining. *(Expected.)*
- ⚠️ **PENDING (D):** `ω_p` ring shown but `λ_D` only scaling-correct.
- ❌ **FAIL (F):** cannot get a restoring oscillation without re-importing a primitive `E` field.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Restoring ring | SHM at `ω_p ∝ √(n/m)` | collective occlusion not restoring → no plasma freq |
| Screening | exponential, decay `λ_D ∝ √(T/n)` | wake not screenable by population → Debye fails |
| Magnetised limit | upper-hybrid `ω_p²+ω_c²` | swirl & population don't co-couple |

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl, occlusion), TD02 (statistical
ensemble / thermal distribution), EMC03 (handedness, surplus/deficit), electropause (Law-III restoring push).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]], [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]].
**Related:** Law V movement budget (`v_circ²+v²=c²`), [[feedback_no_borrowed_units]].
