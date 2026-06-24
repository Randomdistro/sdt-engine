# PM02 — Faraday Induction and Lenz from Changing Swirl

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use native wake-circulation units, koppa, traction `T=3(W+1)`.

## Question

A loop of relay lattice threaded by a **time-varying collective swirl** (PM01's `w`) develops a drive
on its own vortices. **Can Faraday's `EMF = −dΦ/dt` and Lenz's sign be derived as the relay
back-reaction to a changing wake-circulation — with the minus sign forced by occlusion, not
postulated?** No primitive `E`/`B` fields, no flux rule imported: flux Φ is the count of swirl
streamlines through the loop, EMF is the net circulation drive on the loop's carriers.

## SDT mechanism & hypotheses

When the collective swirl threading a loop changes, the relay throughput available to the loop's
vortices is redistributed; conservation of circulation forces a compensating drive (the induced EMF),
and the loop's own induced swirl **occludes** the change that produced it (Lenz back-reaction).

- **H1 (EMF = −dΦ/dt):** define `Φ ≡ ∮ w·dA` (native swirl flux); show the induced circulation drive
  on the loop equals the time-derivative of threaded swirl, recovering `EMF = −dΦ/dt` term-for-term.
- **H2 (Lenz = occlusion back-reaction):** the **minus sign** is the EMC03 handedness of the induced
  wake — it always occludes the driving change (energy cannot be created by reshuffling throughput).
- **H3 (motional ≡ transformer):** loop-motion-through-static-swirl and static-loop-in-changing-swirl
  are one mechanism (relative wake change), unifying `qv×B` (PM01) with `−dΦ/dt`.

## Strategy

**Phase 1 — Swirl flux & the count.** Build PM01's `w` for a solenoid; define Φ as streamline count.
*Goal:* native Φ(t). *Method:* sum wakes, integrate over loop. *Success:* Φ matches `B·A` form to <1%.

**Phase 2 — Induced drive.** Vary the source; compute the relay-conservation circulation drive on a
test loop. *Goal:* `EMF`. *Method:* finite-difference dΦ/dt vs measured carrier drive. *Success:*
`|EMF + dΦ/dt|/|EMF| < 1%`; transformer turns-ratio `V₂/V₁ = N₂/N₁` exact.

**Phase 3 — Lenz sign.** Resolve the induced wake handedness (EMC03). *Goal:* sign always opposing.
*Method:* sign matrix over (dΦ/dt > 0, < 0) × (loop handedness). *Success:* 4/4 cells oppose the change.

**Phase 4 — Eddy brake.** Drag a conductor through the swirl. *Goal:* retarding force. *Method:*
induced-wake occlusion on the bulk. *Success:* drag `∝ v` direction-correct; energy ledger closes.

## Success criteria

- ✅ **PASS (A):** `EMF=−dΦ/dt` + Lenz sign + motional≡transformer all native, zero fitted params.
- ✅ **QUALIFIED (C):** relations reproduced with one flagged coarse-graining coefficient. *(Expected.)*
- ⚠️ **PENDING (D):** EMF magnitude scaling-correct but sign needs an external convention.
- ❌ **FAIL (F):** cannot get the minus sign without re-importing a primitive field / Faraday's law.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Induced drive = `−dΦ/dt` | matches to <1% over varied dΦ/dt | EMF not relay-conservation-derivable |
| Lenz sign always opposes | 4/4 sign cells oppose the change | minus sign not from occlusion → postulate remains |
| Motional ≡ transformer | one mechanism reproduces both | two unrelated effects → no unification |

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (B=∇×w, Lorentz=occlusion), PPT06
(traction), EMC03 (handedness sign). **Downstream:** [[PM03_EM_Waves_as_Coupled_Relay_Pulses]]
(the ∂B/∂t source term), [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]] (frozen-in flux).
**Related:** E58 (monopole forbidden → ∇·B=0 closes the Maxwell pair), [[feedback_no_borrowed_units]].
