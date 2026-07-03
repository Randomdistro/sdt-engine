# PM04 — Plasma Oscillations and Debye Shielding

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can the **plasma frequency `ω_p`** be recovered as a genuine restoring
   *occlusion* oscillation — i.e. does the `e²/ε₀` group in `ω_p = √(ne²/ε₀m)` reappear as a **native
   Law-III occlusion gain** computed from the vortex population, with **no `E` field and no µ_B
   imported** — or can we only reproduce the *form* `ω_p ∝ √(n/m)` while the gain factor is borrowed?
   If the gain has to be set to `e²/ε₀` by hand, PM04 has matched a scaling, not derived a mechanism.
2. **Why does it matter?** — `ω_p` and `λ_D` are the two scales that define what a plasma *is*; they
   gate PM05 (the heated/screened population after reconnection), PM07 (MHD validity), and the
   magnetised limit (upper-hybrid) that links back to PM01. A native restoring gain here means
   collective EM in matter is the same Law-III occlusion that holds the electron at the electropause.
3. **How will we find out?** — Four gated phases (§④); the slab restoring push and the thermal smear
   length (P1→P2) are computed from occlusion + the Law-V movement budget **before** any SI `e²/ε₀m` is
   written; the SI map is the final line only.
4. **What would prove us wrong?** — §⑧, each falsifier states the killing number (`ω_p` off the form,
   screening not exponential, λ_D scaling wrong, upper-hybrid not additive).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase.

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

**Anti-tautology firewall.** The *trivial* path is to write `ω_p = √(ne²/ε₀m)` and call the slab model
an illustration of it. The *load-bearing* path is to compute the restoring occlusion push on a
rigidly-displaced vortex slab **from Law III alone**, read off the native gain, and only *then* observe
that it equals the SI group `e²/ε₀` — never the reverse. **Importing `e²/ε₀m` (or a primitive `E`
field) as the restoring constant caps the grade at C.** The factor-3 in the Langmuir dispersion is
flagged as a coarse-graining O(1) until derived. **Native-before-borrowed / forbidden:** no `E` field
primitive, no µ_B/µ_N/magneton anywhere, no G/M-fundamental, no QM wavefunction as the screening
mechanism; charge enters only as EMC03 handedness (surplus/deficit), the SI `e` only in the final map.

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

## Falsification tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | Restoring ring | slab SHM at `ω_p`, native gain matches `ne²/ε₀m` form to <1%; restoring force linear in displacement `δ` | `ω_p` off the form >1%, or force not `∝ δ` → collective occlusion is not restoring → no plasma frequency |
| T2 | Debye screening | test-wake potential **exponential**, e-folding `λ_D ∝ √(T/n)` recovered to <2% | screening not exponential, or `λ_D` scaling exponents wrong → the population cannot screen a wake → Debye fails |
| T3 | Langmuir dispersion | `ω² = ω_p² + 3k²v_th²`; the coefficient comes out ≈3 (flag if borrowed) | coefficient not ≈3 and not derivable → thermal correction not from finite relay speed |
| T4 | Magnetised limit | upper-hybrid `ω_uh² = ω_p² + ω_c²` (additive) once PM01 field is added | the two do not add in quadrature → swirl and population do not co-couple |

## Questions This Opens *(generative — log in `PM04_VERDICT.md`)*

1. **Is the native restoring gain the same `e²/ε₀` that PM03 maps for ε₀ and the electropause uses for
   the electron?** If one occlusion gain reappears in `ω_p`, the electropause binding, and `c²=1/µ₀ε₀`,
   then "charge coupling strength" is a single relay property in three disguises.
2. **Does the Debye smear length connect to the electropause radius?** Both are an occlusion balance
   against an agitation; is `λ_D` the thermal-population analogue of the single-electron boundary?
3. **Where does Landau damping live in the relay picture?** Collisionless damping has no obvious relay
   analogue — is it the resonance between the restoring ring and the Law-V movement-budget tail, and is
   it native or an open gap?
4. **Does the factor-3 in `ω²=ω_p²+3k²v_th²` share the FD05 `1/3` origin (3-D isotropy)?** If so, the
   thermal-pressure 3 and the radiation-sound 3 are one dimensionality statement.

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl, occlusion), TD02 (statistical
ensemble / thermal distribution), EMC03 (handedness, surplus/deficit), electropause (Law-III restoring push).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]], [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]].
**Related:** Law V movement budget (`v_circ²+v²=c²`), FD05 (the `1/3` isotropy factor), [[feedback_no_borrowed_units]].
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces actually used: law_III (occlusion gain), law_V (movement budget / v_th), bridge; PM01 swirl, TD02 ensemble
- Phase thresholds (committed before run): P1 ω_p form <1% (native gain, no e²/ε₀ import) · P2 exponential screening, λ_D <2% · P3 dispersion coeff ≈3 · P4 upper-hybrid additive
- Forbidden retroactive changes: import e²/ε₀m or a primitive E into the restoring chain then claim A; quote any moment in µ_B/µ_N; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM04)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 `ω_p` off form > 1% | refine slab discretisation; check restoring linearity | **OPEN** the occlusion-gain ↔ `e²/ε₀` link | import `e²/ε₀m` and call it native |
| P2 screening not exponential | check thermal smear vs restoring balance | **KILL** H2; Debye screening not population-derivable | force an exponential fit |
| P3 dispersion coeff ≠ 3 | tie to FD05 isotropy `1/3`; recompute finite relay speed | mark coeff **CONVERGENCE** (borrowed) | plug 3 and claim native |
| P4 upper-hybrid not additive | check PM01 field coupling sign/geometry | **OPEN** the magnetised limit | claim co-coupling without the quadrature check |
| Landau damping has no relay analogue | scope it OUT; note as Question 3 | **OPEN** collisionless damping | pretend it is derived |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
