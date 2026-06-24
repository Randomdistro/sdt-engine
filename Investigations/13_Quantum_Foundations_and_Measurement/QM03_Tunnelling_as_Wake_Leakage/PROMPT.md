# QM03 — Tunnelling as Wake Leakage

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

How does a hard solid vortex cross a barrier it classically cannot surmount? In SDT there is no
probability cloud that "is sometimes on the far side." There is a vortex and its **convergence
wake**. Can barrier penetration be reproduced as the **wake leaking through an occlusion barrier** —
the wake amplitude decaying but not vanishing inside the wall — with the vortex following the
surviving wake branch when leakage delivers enough convergence to cross? Reproduce the Gamow
exponential for α-decay and the STM tunnelling current `I ∝ e^{−2κd}`.

## SDT mechanism & hypotheses

A barrier is a region of raised occlusion (PPT05 confinement) that the vortex cannot push through
mechanically. But the wake is a relay-pressure disturbance, and a relay pressure cannot be set
exactly to zero across a finite wall — it decays as `e^{−κ x}` with a lattice decay length set by
the occlusion depth. Where the leaked wake re-emerges on the far side with residual amplitude, it
can re-seed a vortex landing there (the QM01 steering rule). Tunnelling is therefore **deterministic
leakage of a real pressure field**, local and mechanical, not a magical jump.

- **H1 (evanescent relay):** inside the barrier the wake amplitude decays exponentially, decay
  constant `κ = √(2m(V−E))/ℏ` re-derived as a lattice occlusion-screening length (no Schrödinger).
- **H2 (transmission = leaked fraction):** T ≈ e^{−2κd}; the `−2` is amplitude→intensity (QM04 square).
- **H3 (Gamow α-decay):** the α-cluster vortex (ATOMICUS core) leaks the Coulomb-occlusion barrier;
  log(half-life) vs `Z/√E` linear (Geiger–Nuttall) from the leaked-fraction integral ∫κ dx.

## Strategy

**Phase 1 — Evanescent wake in a barrier.** *Goal:* derive the decay length. *Method:* relay
pressure across a raised-occlusion slab (PPT05); solve for the decaying mode tick-by-tick (FLM05).
*Success:* `κ = √(2m(V−E))/ℏ` recovered to <1% from lattice mechanics, no wave equation imported.

**Phase 2 — Square barrier transmission.** *Goal:* T(d,E). *Method:* match leaked wake amplitudes
at both faces; intensity ratio. *Success:* `T ≈ 16 (E/V)(1−E/V) e^{−2κd}` reproduced; the `−2`
traced to the QM04 amplitude-square.

**Phase 3 — STM current.** *Goal:* `I ∝ e^{−2κd}`. *Method:* electron-vortex wake across a vacuum
gap; current = landing rate. *Success:* decade-per-Å sensitivity (≈ 1 order / 1 Å) reproduced; work-function dependence right sign.

**Phase 4 — Gamow α-decay.** *Goal:* Geiger–Nuttall line. *Method:* α-core vortex leaking the
nuclear-edge occlusion barrier; ∫κ dx over the Coulomb slope. *Success:* log T_½ vs Z/√E linear,
slope within ~10% for a U/Th/Po series.

## Success criteria

- **PASS (A):** decay length, T, STM slope, and Geiger–Nuttall all native to <1% (rates) / ~10% (T_½).
- **QUALIFIED (C):** exponential form native but one prefactor (16·…, or the assault frequency) borrowed/flagged.
- **PENDING (D):** wake leaks and decays correctly but the re-seeding → vortex-crossing only heuristic.
- **FAIL (F):** cannot get penetration without a ψ that "is" on the far side. Report; census debt stands.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 — leakage is exponential | T ∝ e^{−2κd}, κ from occlusion depth | barrier penetration not wake-leakage |
| T2 — STM sensitivity | ≈ 1 current decade per 1 Å gap change | decay length wrong → mechanism wrong |
| T3 — Geiger–Nuttall | log T_½ ∝ Z/√E linear from ∫κ dx | α-core leakage picture fails |

## Dependencies

**Upstream:** QM01 (wake + steering), PPT05 (confinement = barrier wall), FLM05 (tick evolution).
**Downstream:** QM06 (quasi-bound/resonant states), nuclear decay (ATOMICUS α-core grammar).
**Related:** QM04 (the −2 = amplitude square), [[project_paradox_census]], E-series α-decay specs.
