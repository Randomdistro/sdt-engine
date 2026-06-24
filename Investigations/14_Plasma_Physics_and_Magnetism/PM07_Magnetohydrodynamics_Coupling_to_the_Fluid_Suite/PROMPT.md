# PM07 — Magnetohydrodynamics Coupling to the Fluid Suite

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use native wake-circulation units, koppa, traction `T=3(W+1)`.

## Question

The FD suite already derives fluid mechanics as continuum spation relay. A conducting fluid threaded
by a swirl field (PM01) is **that same lattice carrying circulation while it flows**. **Can ideal
magnetohydrodynamics be assembled as the FD fluid equations coupled to the wake-circulation field —
with Alfvén waves as transverse lattice+swirl modes, frozen-in flux as wake advection, and magnetic
pressure/tension as native traction — rather than the MHD equation set imported wholesale?** MHD is a
TARGET; no magneton, no primitive B, no resistive-Ohm postulate (resistivity = FD02 relay diffusion).

## SDT mechanism & hypotheses

A swirl field embedded in a flowing relay lattice is advected by it (the wakes ride the flow = frozen-in);
the swirl exerts a back-traction on the fluid (magnetic pressure ⊥ + tension ∥ the swirl streamlines).
Couple FD01's Navier–Stokes (relay momentum) to PM01's swirl and the ideal-MHD set assembles natively.

- **H1 (frozen-in = wake advection):** in the low-relay-diffusion limit (FD02 → 0) the swirl flux
  through any co-moving lattice loop is conserved — the wakes advect with the flow; recover the
  ideal induction equation `∂B/∂t = ∇×(v×B)` as PM01⊕FD01 with no Ohm's-law postulate.
- **H2 (Alfvén = transverse lattice+swirl mode):** the GOM06 transverse rigidity *plus* swirl tension
  gives a restoring force → a wave at `v_A = B/√(µ₀ρ)` (native: swirl tension over lattice inertia).
- **H3 (magnetic pressure/tension = traction):** the `B²/2µ₀` pressure and tension are PPT06 wake
  traction resolved ⊥ and ∥; recover the Maxwell stress tensor as relay traction, plug into FD08 budget.

## Strategy

**Phase 1 — Couple the sets.** Add PM01 swirl back-traction to FD01 Navier–Stokes. *Goal:* ideal-MHD set.
*Method:* assemble momentum + induction. *Success:* the ideal-MHD equations reproduced term-for-term;
each term named in FD/PM primitives (bijection gate).

**Phase 2 — Frozen-in flux.** Drive FD02 relay diffusion → 0. *Goal:* flux conservation. *Method:*
co-moving loop integral. *Success:* swirl flux conserved to <0.5%; finite diffusivity gives slip ∝ η.

**Phase 3 — Alfvén waves.** Perturb a uniform-field fluid. *Goal:* `v_A`. *Method:* GOM06 + tension
dispersion. *Success:* `v_A = B/√(µ₀ρ)` form to <1%; non-dispersive; transverse; magnetosonic modes recovered.

**Phase 4 — Magnetic pressure/tension.** Resolve PM01 traction ⊥/∥. *Goal:* Maxwell stress. *Method:*
PPT06 traction projection. *Success:* `B²/2µ₀` pressure + tension recovered; pinch/sausage stability order-correct.

## Success criteria

- ✅ **PASS (A):** ideal-MHD set + frozen-in + `v_A` + magnetic stress all native, zero fitted params.
- ✅ **QUALIFIED (C):** set assembled; one flagged coupling coefficient in the stress projection. *(Expected.)*
- ⚠️ **PENDING (D):** induction + frozen-in shown but Alfvén speed only scaling-correct.
- ❌ **FAIL (F):** cannot couple without importing the MHD set or a primitive B as a closure.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Frozen-in | flux conserved as FD02 η→0; slip ∝ η | swirl not advected by flow → not wake-borne |
| Alfvén | `v_A = B/√(µ₀ρ)`, transverse, non-dispersive | swirl tension + GOM06 don't make a wave |
| Magnetic stress | `B²/2µ₀` pressure + tension from traction | MHD stress not reducible to PPT06 traction |

## Dependencies

**Upstream:** FD01 (Navier–Stokes / relay momentum), [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl
back-traction), [[PM03_EM_Waves_as_Coupled_Relay_Pulses]] (wave coupling), GOM06 (transverse rigidity), FD02 (relay diffusion ≡ resistivity).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]] (breaks frozen-in flux), dynamo / magnetosphere modelling.
**Related:** FD05 (sound → magnetosonic), FD08 (energy budget + magnetic pressure), PPT06 (traction), [[feedback_no_borrowed_units]].
