# TD05 — Phase Transitions and Latent Heat from Reconfiguration

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Melting and boiling absorb latent heat at a fixed temperature — energy goes in but `T` does not rise.
Classically this is a free-energy crossing. The gap: derive a phase transition as a **lattice-packing
reconfiguration threshold** and latent heat as the **reorganisation cost** (Law IV flavour) of
repacking the vortex assembly into a looser configuration.

## SDT mechanism & hypotheses

Matter is hard solid vortices held in a packing by their mutual wakes and the surrounding spation
pressure. A phase is a packing motif (close-packed solid → mobile-but-bonded liquid → free gas). When
disordered throughput (heat) reaches a threshold, the packing can no longer hold and the assembly
**reconfigures**; the latent heat is the Law IV cost to reorganise the throughput bookkeeping of every
bond broken — paid at constant `T` because it buys configuration, not kinetic throughput.

- **H1 (transition = packing threshold):** melting occurs when per-vortex disordered throughput exceeds
  the wake-binding throughput holding the lattice motif; `T_m` is that threshold, not a fit.
- **H2 (latent heat = reorganisation cost):** `L = N_bonds × Δε_reorg`, the Law IV `V_disp` change
  between motifs; it absorbs heat at constant `T` because the throughput goes into configuration `W`
  (raising entropy `ΔS=L/T`, [[TD01]]), not into `½k_BT` per DoF.
- **H3 (Clausius–Clapeyron from pressure balance):** the coexistence line `dP/dT = L/(TΔV)` is the
  spation-pressure balance between the two packings — derived from occlusion equilibrium (Law III),
  not assumed thermodynamically.

## Strategy

1. **Threshold transition.** *Goal:* a sharp `T_m`. *Method:* heat a 2D/3D toy vortex packing; watch
   order parameter (motif coherence) collapse. *Success:* discontinuous motif loss at a definite
   `T_m`; hysteresis ↔ first-order character.
2. **Latent heat ledger.** *Goal:* `L` from reorganisation. *Method:* count bonds broken × `Δε_reorg`
   (Law IV `V_disp`) across the transition; compare to `T_m ΔS`. *Success:* `L = T_m ΔS` self-consistent;
   heat absorbed at flat `T` on the trace.
3. **Order-of-magnitude check.** *Goal:* real `L`. *Method:* set `Δε_reorg` from a measured bond
   energy proxy for one solid and one liquid→gas. *Success:* `L_melt`, `L_vap` within a factor of ~3
   of tabulated values; `L_vap ≫ L_melt` ordering reproduced (more bonds broken).
4. **Coexistence line.** *Goal:* Clausius–Clapeyron. *Method:* vary spation pressure (occlusion load),
   re-find `T_m`. *Success:* `dP/dT = L/(TΔV)` slope recovered to ~15%.

## Success criteria

- **PASS (Class A):** sharp transition + `L=T_mΔS` + Clausius–Clapeyron all from reconfiguration and
  Law III/IV, zero fitted parameters beyond the one measured bond-energy proxy.
- **QUALIFIED (Class C):** mechanism + `L_vap≫L_melt` ordering + slope native; absolute `L` within ~3×.
  *(Expected.)*
- **PENDING (Class D):** transition sharp but `L` magnitude needs a calibrated bond count.
- **FAIL (Class F):** the transition only appears with an imported Landau free-energy / order-parameter
  field SDT forbids.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | transition = packing threshold | sharp `T_m`, motif collapse, hysteresis | no threshold / continuous only |
| T2 | latent heat = reorg cost | `L=T_mΔS`, heat at flat `T`, `L_vap≫L_melt` | `L` not a configuration cost |
| T3 | coexistence = pressure balance | `dP/dT=L/(TΔV)` ±15% | Clausius–Clapeyron must be imported |

## Dependencies

**Upstream:** Law IV (`V_disp`, reorganisation cost), Law III (occlusion/spation-pressure balance),
[[TD01]] (`ΔS=L/T`). **Downstream:** condensed-matter suite (12) crystal structure & melting; equation
of state in [[TD03]] (non-ideal/co-volume term is the same wake-overlap physics). **Related:** CM04
(lattice packing / structural transitions), [[project_spation_lattice_structure_fork]] (FCC vs
icosahedral packing motifs that set which solid phase is stable).
