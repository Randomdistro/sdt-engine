# PM03 — EM Waves as Coupled Relay Pulses

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use native wake-circulation units, koppa, traction `T=3(W+1)`.

## Question

An EM wave is not a self-sustaining pair of primitive fields — in SDT it is an **emission**: a
propagating relay phase-impulse, with the swirl (B, PM01) and the emission phase (the "E" channel)
**transversely coupled** through one lattice. **Can Maxwell's wave equation and the propagation speed
`c` be recovered from coupled relay pulses, with `c = ℓ_P/t_P` set by lattice relay — without
`µ₀ε₀` as a primitive product?** Here `c` is the relay tick, and `1/√(µ₀ε₀)` must *emerge* as its
relabelling, not be assumed.

## SDT mechanism & hypotheses

A transverse displacement in the lattice carries two coupled signatures: a circulation (swirl, PM01)
and a phase-emission. Each acts as the other's source as the pulse advances at one relay tick, so the
disturbance is self-propagating at `c` — the same `c` that limits occlusion and the movement budget.

- **H1 (wave eqn from coupling):** the PM02 induction term (∂swirl/∂t drives emission) plus the PM01
  Ampère term (emission flux drives swirl) close into `∂²ψ/∂t² = c²∇²ψ` for the transverse mode.
- **H2 (c from relay, not µ₀ε₀):** the propagation speed is `ℓ_P/t_P`; show `1/√(µ₀ε₀)` is this same
  tick in SI clothing, so the EM speed and the gravitational/occlusion `c` are **one** quantity.
- **H3 (transverse-only, impedance):** longitudinal relay = compression (sound, FD05, `c/√3`);
  the EM mode is the **transverse** lattice-rigidity mode (GOM06) → polarisation + a native impedance.

## Strategy

**Phase 1 — Coupled equations.** Write the PM01⊕PM02 relay-update rules; eliminate to a 1-D wave eqn.
*Goal:* `∂²ψ/∂t²=c²∂²ψ/∂x²`. *Method:* finite-difference lattice; measure dispersion. *Success:*
phase speed = `c` to <0.1%; non-dispersive over the resolved band.

**Phase 2 — c without µ₀ε₀.** Identify `c` as `ℓ_P/t_P`; map onto `1/√(µ₀ε₀)`. *Goal:* identity.
*Method:* symbolic relabel + numeric check. *Success:* ratio `c_SDT / (1/√(µ₀ε₀)) = 1.0000`.

**Phase 3 — Transverse rigidity & impedance.** Use GOM06 to fix the transverse mode. *Goal:* native
impedance + two polarisations. *Method:* mode analysis. *Success:* impedance form recovered; `Z₀`
expressed natively (no µ_B, no µ₀-as-primitive); transverse ⊥ confirmed.

**Phase 4 — Energy & momentum.** Poynting flux as relay throughput transport. *Goal:* `S = ψ²·c`.
*Method:* energy ledger of the pulse. *Success:* radiation pressure direction-correct; `E=pc` for the pulse.

## Success criteria

- ✅ **PASS (A):** wave eqn + `c` + transversality all native, zero fitted params; `c=1/√(µ₀ε₀)` shown identity.
- ✅ **QUALIFIED (C):** wave eqn & `c` native; impedance carries one flagged coarse-graining factor. *(Expected.)*
- ⚠️ **PENDING (D):** non-dispersive transverse mode shown but `c`-identity only numerical, not derived.
- ❌ **FAIL (F):** cannot propagate without re-inserting primitive `E`,`B`, or `µ₀ε₀`.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Phase speed | = `c` non-dispersive | EM mode not a pure relay tick |
| `c = 1/√(µ₀ε₀)` | identity ratio 1.0000 | EM `c` ≠ occlusion `c` → two media |
| Transverse only | longitudinal mode = sound (`c/√3`), not light | EM not the GOM06 transverse mode |

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl source), [[PM02_Faraday_Induction_and_Lenz_from_Changing_Swirl]] (∂swirl/∂t source), GOM06 (transverse lattice rigidity).
**Downstream:** [[PM06_Cyclotron_and_Synchrotron_from_Differential_Occlusion]] (radiation), [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]] (Alfvén/wave coupling), 15_Optics.
**Related:** FD05 (longitudinal sound `c/√3`), E58 (∇·B=0), [[feedback_no_borrowed_units]].
