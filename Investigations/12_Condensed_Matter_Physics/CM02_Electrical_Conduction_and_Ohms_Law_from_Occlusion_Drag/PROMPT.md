# CM02 — Electrical Conduction and Ohm's Law from Occlusion Drag

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

A conduction electron is a **drifting W=1 vortex** in the relay lattice. As it drifts it is
**occluded** (Law III) by lattice irregularities — thermal displacements and static defects —
each collision dumping organised drift-throughput into disordered throughput (heat). **Can Ohm's
law (`V = IR`), the Drude conductivity form (`σ = ne²τ/m`), and the metallic temperature law
(`ρ ∝ T`) be reproduced from occlusion-drag scattering of drifting vortices — and can the ohm be
*defined natively* from lattice relay quantities rather than imported?** This is the normal-state
root the whole suite stands on (see [[project_two_regime_and_occlusion_saturation]]).

## SDT mechanism & hypotheses

Drift velocity is the steady balance of the applied convergence-pressure push against occlusion
drag: between collisions the vortex accelerates; each occlusion event randomises its drift. Mean
free time `τ` = mean relay path / drift-relevant relay speed. Resistance is literally the rate of
organised → disordered throughput conversion = Joule heat.

- **H1 (Drude form is native):** balancing push vs occlusion-drag over a mean relay time gives
  `σ = ne²τ/m` with `τ` an occlusion mean-free-time — no kinetic-theory borrow.
- **H2 (metallic ρ∝T):** thermal lattice displacement (FD05 amplitude ∝ T) grows the occlusion
  cross-section linearly → `ρ ∝ T` above θ_D; residual ρ₀ from static defects (Matthiessen add).
- **H3 (native ohm):** the ohm is expressible from relay throughput quantities (and closes against
  CM06's `R_K = h/e²`), so Ohm's law is a throughput-conservation statement, not a fitted constant.

## Strategy

**Phase 1 — Single-vortex drift.** *Goal:* derive `v_drift` from push/drag balance. *Method:*
occlusion force vs applied gradient over one mean relay time. *Success:* `v_drift ∝ E` (linear),
mobility `μ = eτ/m` recovered.

**Phase 2 — Drude conductivity.** *Goal:* assemble `σ = ne²τ/m`. *Method:* n drifting vortices,
carrier density from measured material; predict σ for Cu/Ag/Al. *Success:* σ within 2× of measured
for 3 metals using only τ from occlusion geometry.

**Phase 3 — Temperature law.** *Goal:* `ρ(T)`. *Method:* tie occlusion cross-section to FD05
thermal-displacement amplitude. *Success:* linear ρ∝T above θ_D; ρ₀ residual; Matthiessen additivity.

**Phase 4 — Native ohm + heat.** *Goal:* define the ohm from relay quantities; show R = Joule rate.
*Method:* express resistance via throughput per quantum; cross-check vs `h/e²`. *Success:* ohm
expressed natively to <1%; `P = I²R` = throughput-disorder rate.

## Success criteria

- ✅ **PASS (A):** Drude form, ρ∝T exponent, and native ohm all derived, zero fits.
- ✅ **QUALIFIED (C):** forms + scaling native; one O(1) cross-section coefficient CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** drift + Drude shown; ρ(T) or native ohm only scaling-correct.
- ❌ **FAIL (F):** cannot get linear ρ∝T or σ within 2× without importing band-theory machinery.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | drift = push/drag balance | `v_drift ∝ E`, mobility eτ/m | conduction not occlusion-limited |
| T2 | ρ∝T from thermal occlusion | linear ρ above θ_D; ρ₀ residual | cross-section not thermal-amplitude-set |
| T3 | ohm is native throughput | R expressible from relay quanta, ≈ h/e² scale | ohm is an irreducible import |

## Dependencies

**Upstream:** Law III (occlusion = drag), [[project_two_regime_and_occlusion_saturation]], FD05
(`c_s`, thermal displacement), CM04 (lattice substrate). **Downstream:** [[CM01]]
(superconductivity = this drag → 0), CM03 (band/gap), CM06 (ohm metrology, E86). **Related:** TD01
(heat = disordered throughput); PPT06 (traction).
