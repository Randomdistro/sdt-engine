# Thermodynamics & Statistical Mechanics — SDT lattice statistics (TD01–TD09)

> **DIRECT RE-RUN 2026-07-26** (see `../DIRECT_RERUN_FD_TD_2026-07-26.md` and each
> `TD##_VERDICT_DIRECT_2026-07-26.md`): agent-era verdict layer deleted and re-earned in the
> main loop. **TD09 added (Harvey 2026-07-26): the Freedom Ledger of Binding** — second law
> restated as freedom-seeking (no math change); gate PASSED: ledger flip T = 0.0624 MeV lands
> inside the measured BBN deuterium bottleneck (0.06–0.09 MeV), zero fits; Saha-convergent,
> disclosed. TD01's arrow-of-time debt RE-POSED as the freedom-climb theorem.
>
> **Author:** J.C. Harvey, Melbourne. **Status:** EXECUTED — TD01 (earlier run, Class C qualified);
> **TD02–TD08 executed 2026-07-03** (see each `TD##_VERDICT.md`): all land **CONVERGENCE-class**
> (TD07/TD08 partially NULL-SDT-CONTENT; TD05's count-ledger KILLED at fixed density), capped by the
> shared cascade roots **TD-ROOT-1** (ε-scale invisibility — the suite's mechanisms are substrate-blind)
> and **TD-ROOT-3** (ε = hν asserted, not derived) — logged once in `../INVESTIGATION_STACK.md` §3b.
> The one NATIVE, falsifiable lattice fingerprint: TD03's rank-4 FLM08 observable ([1/9, 7/27] band vs
> continuum 1/5). Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

In SDT the only ontology is a **granular relay lattice of spations** passing convergence
throughput between contacting neighbours at one tick (`c = ℓ_P/t_P`). **Heat is disordered
convergence throughput** — relay activity not organised into a vortex or a coherent wake. So
thermodynamics is not an imported theory: it is the **statistics of relay throughput on a lattice
that is already discrete at ℓ_P**. There is no continuum to coarse-grain, no phase-space to assume,
and no quantised-oscillator postulate to bolt on — the lattice literally *has* a finite, countable
set `W` of micro-arrangements for any macrostate. These eight investigations test that claim end to
end: each reproduces a standard statistical-mechanics result as a *convergence target* (never a
borrowed input), narrating the mechanism in SDT primitives (occlusion, throughput sharing, relay
mean-free-path, reconfiguration cost, movement budget) and flagging every gap OPEN rather than
fitting it. The imposed ensemble, the partition-function-as-axiom, the Liouville continuum, and the
"entropy = disorder" hand-wave are **forbidden as inputs** — they are exactly the things to derive.

## Dependency stack (build/run order — bottom feeds top)

```
TD01  Entropy & arrow of time from lattice microstates   ← the TD root (S=k_B ln W, H-theorem)
  │       (rests on FLM02/FLM05 relay ticks, SAR02–SAR02 mode counting)
  │
  ├─ TD02  Temperature & equipartition from throughput    (k_BT = throughput/DoF; ½k_BT per DoF)
  │     │
  │     ├─ TD03  Ideal gas & pressure from occlusion       (PV=Nk_BT from Law III momentum flux)
  │     ├─ TD07  Information thermodynamics & Landauer      (k_BT ln2 per bit; demon pays relay)
  │     └─ TD08  Fluctuation–dissipation & Brownian motion  (D=µk_BT; tick noise = dissipation)
  │
  ├─ TD04  Heat conduction & diffusion from relay          (q=−k∇T; k from relay mean-free-path)
  │       (analogue of FD02 viscosity — same λ_mfp v_relay machinery)
  │
  ├─ TD05  Phase transitions & latent heat from reconfig   (packing thresholds; L = reorg cost)
  │
  └─ TD06  Blackbody thermodynamics from lattice modes     (Planck/SB/Wien; consolidates SAR02–SAR02)
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **TD01** | Entropy & Arrow of Time from Lattice | literal count `W` of relay microstates; per-tick neighbour mixing → big basin | `S=k_B ln W` exact; `S(t)` monotone; H-theorem without Stosszahl |
| **TD02** | Temperature & Equipartition from Throughput | `k_BT` = mean disordered relay throughput per spation DoF; even sharing | `½k_BT` per quadratic DoF; `1/T=∂S/∂E`; Maxwell–Boltzmann emerges |
| **TD03** | Ideal Gas & Pressure from Occlusion | Law III occlusion momentum-flux of a relay gas on the walls | `PV=Nk_BT` derived (no imposed ensemble); Dalton; `c_v=3/2 k_B` |
| **TD04** | Heat Conduction & Diffusion from Relay | throughput diffusion down a `∇T`; `k=⅓ c_v v_relay λ_mfp` | Fourier `q=−k∇T`; air/metal `k`; `k∝√T`; Wiedemann–Franz |
| **TD05** | Phase Transitions & Latent Heat from Reconfiguration | lattice-packing threshold; `L` = Law IV reorganisation cost of repacking | melt/boil `L` order-of-magnitude; Clausius–Clapeyron `dP/dT=L/TΔV` |
| **TD06** | Blackbody Thermodynamics from Lattice Modes | lattice mode counting (already discrete → no quantised oscillator) | Planck law; Stefan–Boltzmann `σ`; Wien `b`; consolidates SAR02–SAR02 |
| **TD07** | Information Thermodynamics & Landauer | erasing a bit dumps organised throughput as heat; demon pays to sort | Landauer `k_BT ln2`/bit; demon closes; reversible compute = no relay cost |
| **TD08** | Fluctuation–Dissipation & Brownian Motion | relay-tick shot noise kicks an immersed body; same statistic as drag | Einstein `D=µk_BT`; FDT `⟨x²⟩=2Dt`; `D∝T/η` cross-check vs FD02 |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`law_I::P_conv` / `ε` (throughput quantum `ε=u₀ℓ_P³`) · `law_III` occlusion (`F_occlusion`,
`solid_angle_occluded`) — pressure of the relay gas on a wall · `law_IV` `V_disp` (mass as organised
throughput cost — the latent-heat reorganisation ledger) · `law_V` movement budget (`v_circ²+v²=c²`)
· `bridge` (`koppa`, `k`, `z`). **dependency-traced input:** `k_B` — the entropy↔throughput unit-bridge,
exactly as `e` is the charge unit-bridge (measured, not derived). Prior results leaned on:
**SAR02–SAR02** (lattice mode counting → Planck, Stefan–Boltzmann, Wien — TD06 consolidates these),
**FD02** (transport `ν=⅓λ_mfp v_relay`, `ν∝√T` from B16 — TD04/TD08 reuse the same machinery),
**FLM02/FLM05/ROOT-SIM** (the granular-relay tick root). Heat-death-vs-recharge ties to
[[project_sdt_cyclic_cosmology]] (the cosmological arrow and the thermodynamic arrow are one relay
asymmetry).

## Method discipline

Each investigation reports results with certification labels (`DERIVED` / `COMPUTED` /
`CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard
statistical-mechanics number is always the thing to *reproduce*, never to *borrow*; measured
material properties (heat capacities, conductivities, latent heats, `σ`) are legitimate
measured-unit inputs/tools — like spectral lines — but the mechanism must be SDT-native. The
ensemble, the partition function, and `S=disorder` are **targets, not machinery**: if a result can
only be obtained by importing one of them, that is a recorded gap, not a pass. A clean kill outranks
a forced pass (R4).
