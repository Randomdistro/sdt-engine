# TD03 — Ideal Gas and Pressure from Occlusion

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

`PV = Nk_BT` is the canonical ideal-gas law, usually got from a kinetic-theory or partition-function
argument. The gap: derive it from Law III occlusion — the momentum flux a relay gas deposits on a
wall — with no imposed Boltzmann ensemble and no continuum velocity distribution assumed.

## SDT mechanism & hypotheses

A gas particle is a hard solid vortex carrying a wake of disordered throughput. Pressure is not a
fluid abstraction: it is the **rate of convergence-momentum delivered to a boundary** as vortices
strike it and the wall occludes their incoming throughput (Law III, `F_occlusion`,
`solid_angle_occluded`). Temperature `k_BT` (from [[TD02]]) sets the mean disordered throughput per
DoF, hence the mean impact momentum.

- **H1 (pressure = occlusion momentum-flux):** `P = (1/3) n m ⟨v²⟩` arises because each wall element
  occludes the one-sided convergence-momentum current of the relay gas; the factor `1/3` is the
  three-axis isotropy of the lattice, *derived* not assumed.
- **H2 (ideal-gas law):** substituting TD02's `½m⟨v²⟩ = (3/2)k_BT` gives `PV = Nk_BT` with `k_B` the
  only input — the ensemble never appears.
- **H3 (Dalton & limits):** partial pressures add because occlusion momentum-fluxes from distinct
  species superpose linearly; departures from ideality appear when vortex wakes overlap (finite-size /
  co-volume), recovering a van-der-Waals-shaped first correction natively.

## Strategy

1. **Single-wall flux.** *Goal:* `P = ⅓ n m ⟨v²⟩`. *Method:* count convergence-momentum delivered per
   tick to a boundary cell from a relay gas of tagged vortices; average over the lattice's three axes.
   *Success:* the `1/3` falls out of isotropy with no inserted geometric factor.
2. **Ideal-gas law.** *Goal:* `PV=Nk_BT`. *Method:* fold in TD02's equipartition `½m⟨v²⟩=(3/2)k_BT`.
   *Success:* `PV/(Nk_BT) = 1.000 ± 10⁻³` across a decade of `N` and `T`; `c_v = (3/2)k_B` recovered.
3. **Dalton & equation-of-state.** *Goal:* additivity + first non-ideal term. *Method:* mix two
   species; then crowd the box until wakes overlap. *Success:* `P_total = ΣP_i` to 1%; a positive
   co-volume correction `P(V−Nb)=Nk_BT` emerges with `b ∼ ` vortex-wake volume (flagged, order-unity).
4. **Input audit.** *Goal:* confirm whitelist. *Method:* delete-test on `k_B`. *Success:* result is
   `k_B ×` pure number; no ensemble, no `h`, no partition function anywhere in the chain.

## Success criteria

- **PASS (Class A):** `PV=Nk_BT` derived from occlusion momentum-flux + TD02 equipartition, only `k_B`
  whitelisted, the `1/3` native; zero fitted parameters.
- **QUALIFIED (Class C):** ideal law clean; the non-ideal `b` coefficient is order-unity / flagged.
  *(Expected.)*
- **PENDING (Class D):** pressure law numerically correct but the `1/3` needs a calibrated isotropy step.
- **FAIL (Class F):** `PV=Nk_BT` only reproducible by importing a Maxwell–Boltzmann ensemble.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | pressure = occlusion momentum-flux | `P=⅓nm⟨v²⟩`, `1/3` from isotropy | factor must be inserted by hand |
| T2 | occlusion + TD02 → ideal gas | `PV/(Nk_BT)=1±0.1%` over decade in N,T | law needs an imposed ensemble |
| T3 | wakes overlap → co-volume | positive `b∼` wake volume, Dalton additive | non-ideality wrong sign / Dalton fails |

## Dependencies

**Upstream:** [[TD02]] (equipartition `½m⟨v²⟩=(3/2)k_BT`), Law III occlusion (`F_occlusion`,
`solid_angle_occluded`). **Downstream:** TD04 (conduction in a relay gas), TD05 (gas↔condensed EoS),
TD08 (Brownian kicks are the same momentum-flux). **Related:** [[TD01]] (microstate counting),
FD09 (drag as occlusion cross-section — same Law III machinery, momentum balance).
