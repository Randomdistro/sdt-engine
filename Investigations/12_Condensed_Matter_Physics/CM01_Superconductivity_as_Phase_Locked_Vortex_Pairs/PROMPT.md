# CM01 — Superconductivity as Phase-Locked Vortex Pairs

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

---

## 1 · Executive Summary

Resistance in SDT is **occlusion drag**: a moving vortex (conduction electron) is scattered by
lattice irregularities, dumping organised throughput into disordered throughput (heat). **Can zero
resistance, the Meissner effect, flux quantisation, and the isotope effect be reproduced as
phase-locked vortex pairs gliding through the spation lattice without scattering — a collective
relay mode the lattice irregularities cannot grip?** This turns the L8 correspondence stub (E59,
"phase-locked vortex pairs") into a worked result. **We expect:** below a critical relay-coherence
temperature, two W=1 vortices lock their wakes into a single coherent circulation that the lattice
defects cannot occlude (drag → 0); flux threads in quanta of the one-vortex circulation
`κ = h/(2m)` (the pair); and `T_c` shifts with ionic mass because the lattice relay stiffness (the
"phonon" channel, natively a lattice compression wave) sets the locking energy → the isotope effect.

## 2 · Physical Context

A normal conductor: vortices drift, each independently occluded by lattice disorder → finite drag →
resistance and Joule heat (disordered throughput, see TD01). A superconductor: pairs of vortices
phase-lock their convergence wakes (the attraction is mediated by the lattice compression wave —
SDT's native "phonon"), forming a collective mode whose wavelength exceeds the defect scale, so
defects average out and cannot occlude it — drag vanishes. The Meissner effect is the pair
condensate **occluding** an applied swirl field out of its bulk (EMC03 surplus/handedness expelling
the external circulation). Flux quantisation is the single-valuedness of the locked wake phase
around a loop — an integer count, native.

Variables: pair circulation `κ_pair = h/2m`; coherence length `ξ` (relay phase-coherence range);
penetration depth `λ_L` (swirl-expulsion scale); critical temperature `T_c`; ionic mass `M`
(isotope); lattice relay stiffness (compression-wave speed, FD05 `c_s`). Targets to reproduce:
`R=0`, Meissner, `Φ₀ = h/2e`, `T_c ∝ M^{−½}`.

## 3 · Theoretical Framework

Build on: Law III (occlusion = drag), Law V, Law VI (vortex topology, traction, wake), PPT06, APS04,
EMC03 (handedness/expulsion), FD02 (`κ = h/m` clean to 0.02%), FD05 (lattice sound `c_s`), TD01
(heat = disordered throughput), E59 (phase-locked pairs, VERIFIED stub). **Forbidden:** BCS
wavefunction/gap-as-postulate, Cooper-pair as ψ, gauge symmetry breaking as ontology, phonons as
imported quanta (use the native lattice compression wave). Flux quantum `Φ₀`, Meissner, `T_c(M)`
are targets.

Working hypotheses:
- **H1 (pairing via lattice wave):** two vortices lower their combined occlusion by riding a shared
  lattice compression wake; binding energy sets the gap scale.
- **H2 (zero drag):** the locked pair's coherent wake spans `ξ ≫` defect spacing → defect occlusion
  averages to zero → `R = 0` below `T_c`.
- **H3 (flux quantum):** phase single-valuedness of the pair wake around a loop ⇒ `Φ = n·κ_pair`,
  i.e. `Φ₀ = h/2e` — the "2" is **two locked vortices**, native, not a Cooper postulate.
- **H4 (isotope effect):** locking energy ∝ lattice stiffness ∝ `c_s ∝ M^{−½}` ⇒ `T_c ∝ M^{−½}`.

## 4 · Investigation Strategy

**Phase 1 — Single-vortex drag.** Compute occlusion scattering of one drifting vortex off lattice
disorder → resistivity scale. *Success:* finite `R` with correct order; defines the normal state.

**Phase 2 — Pair locking.** Two vortices + shared compression wake; find the locking binding energy
and coherence length `ξ`. *Success:* bound pair exists below a relay-coherence temperature `T_c`.

**Phase 3 — Zero resistance + Meissner.** Show the locked mode's `ξ ≫` defect scale kills occlusion;
show the condensate expels an applied swirl (penetration depth `λ_L`). *Success:* `R→0`; field
expelled with finite `λ_L`.

**Phase 4 — Flux quantum + isotope.** Phase single-valuedness → `Φ₀ = h/2e` (native count); vary
ionic mass via `c_s(M)`. *Success:* `Φ₀` to <1%; `T_c ∝ M^{−½}` exponent recovered.

## 5 · Success Criteria

- ✅ **PASS (Class A):** R=0, Meissner, Φ₀=h/2e, and the −½ isotope exponent all native, zero fits.
- ✅ **QUALIFIED (Class C):** relations reproduced; `T_c` absolute value CALIBRATED(1) but the
  scaling and Φ₀ derived. (Expected landing.)
- ⚠️ **PENDING (Class D):** pairing + zero-drag shown; flux quantum or isotope only scaling-correct.
- ❌ **FAIL (Class F):** cannot get zero resistance without importing a BCS gap.

## 6 · Outputs

1. `CM01_DERIVATION.md` — drag → pairing → zero-R/Meissner → Φ₀=h/2e → isotope.
2. `cm01_superconductivity.cpp` — standalone C++20: drag vs T, pair binding, Φ₀, T_c(M).
3. `cm01_results.txt` — R(T) curve; λ_L; Φ₀ vs h/2e; T_c vs M^{−½}.
4. `CM01_VERDICT.md` — A/C/D/F with the native-vs-borrowed ledger (phonon = lattice wave, flagged).

## 7 · Dependencies & References

**Upstream:** PPT06, APS04, EMC03, FD02 (κ), FD05 (c_s), TD01 (heat), E59. **Downstream:** Josephson
(E85, defines the volt), quantum Hall (E86, defines the ohm), magnetism (14_Plasma_and_Magnetism).
**Related:** Meissner ≡ EMC03 swirl expulsion; flux quantum ≡ native phase count.

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | drag = occlusion scattering | finite R normal state, correct order | resistance has another basis |
| T2 | pairs phase-lock via lattice wave | bound pair, ξ ≫ defect scale | no native pairing channel |
| T3 | Φ₀ = h/2e is a native count | flux quantised in pair-circulation | the "2" is not two vortices |
| T4 | T_c ∝ M^{−½} | isotope exponent ≈ −0.5 | locking energy not stiffness-set |

## 9 · Implementation Notes

Double precision; dimensionless `T/T_c`. Model defects as a random-but-seeded (index-derived, not
`Math.random`) occlusion field. Plot: (a) R(T) dropping to zero at T_c; (b) field profile showing
λ_L expulsion; (c) T_c vs M on log axes (slope −½). Keep the "phonon" strictly the FD05 lattice
compression wave — naming it a phonon is fine (observable), importing a phonon *field operator* is not.
