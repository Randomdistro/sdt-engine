# CM05 — Superfluidity and BEC from Phase Lock

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Liquid He-4 below `T_λ = 2.17 K` flows without viscosity and circulates only in **quantised
vortices**. Bose–Einstein condensation puts a macroscopic occupation into one state. **Can
superfluidity and BEC be reproduced as a macroscopic phase-locked wake condensate — every atom's
convergence wake locked into one coherent circulation that the lattice cannot occlude — with the
circulation quantised in `κ = h/m` (FD02, clean to 0.02%)?** This is CM01's superconducting pair
condensate without charge: the *same* phase-lock mechanism, but for neutral atomic vortices, so the
expelled quantity is circulation rather than swirl-field.

## SDT mechanism & hypotheses

A normal fluid: atomic wakes are uncorrelated, each occluded → viscosity (FD02). Below `T_λ` the
wakes **phase-lock** into one condensate wake whose coherence length exceeds the occlusion scale →
zero viscosity (like CM01, but `κ = h/m` for one atom, not `h/2m`). Rotation cannot enter as smooth
flow (single-valued locked phase) — only as **quantised vortices**, each carrying one `κ`.

- **H1 (condensate = phase-locked wakes):** below `T_λ` a coherent wake spans `ξ ≫` occlusion scale
  → viscosity → 0; BEC is this macroscopic wake occupation, native (no ψ).
- **H2 (κ = h/m):** circulation quantum is the FD02 one-atom value `h/m_He` (already 0.02%); vortex
  lines carry integer `κ` by phase single-valuedness.
- **H3 (critical velocity):** Landau-type `v_c` = the relay speed at which the moving condensate can
  shed a roton/excitation = an occlusion onset; predicts the right order for He-4.

## Strategy

**Phase 1 — Phase-lock onset.** *Goal:* coherence temperature `T_λ`. *Method:* wake-locking energy
vs thermal disorder (CM04). *Success:* condensation transition exists; `T_λ` order recovered.

**Phase 2 — Zero viscosity.** *Goal:* η → 0 below `T_λ`. *Method:* coherent wake `ξ ≫` occlusion
scale averages defects to zero (mirror CM01 Phase 3). *Success:* η drops sharply at `T_λ`.

**Phase 3 — Quantised circulation.** *Goal:* `κ = h/m`. *Method:* phase single-valuedness around a
vortex; reuse FD02 result. *Success:* `κ` to <0.1%; integer vortex multiplicity.

**Phase 4 — Critical velocity.** *Goal:* `v_c`. *Method:* excitation-shedding onset (roton =
occlusion threshold). *Success:* `v_c` for He-4 within 2×; two-fluid ρ_s(T)/ρ qualitatively.

## Success criteria

- ✅ **PASS (A):** zero viscosity, κ=h/m, and `v_c` order all native, zero fits.
- ✅ **QUALIFIED (C):** transition + κ derived; `T_λ`/`v_c` absolute CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** phase-lock + κ shown; critical velocity only scaling-correct.
- ❌ **FAIL (F):** cannot get zero viscosity / quantised circulation without importing a BEC wavefunction.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | wakes phase-lock below T_λ | sharp η→0 transition | no native condensate channel |
| T2 | κ = h/m (single atom) | circulation quantised in h/m_He | the quantum is not one wake |
| T3 | v_c = excitation onset | He-4 critical velocity within 2× | superflow not occlusion-limited |

## Dependencies

**Upstream:** [[CM01]] (phase-lock mechanism; here κ=h/m not h/2m), FD02 (`κ = h/m`, 0.02%), E59
(phase-locked vortices, VERIFIED), CM04 (thermal disorder vs locking). **Downstream:** CM06
(macroscopic phase coherence → Josephson). **Related:** Meissner ≡ swirl expulsion (EMC03); here the
expelled quantity is circulation.
