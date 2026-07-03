# CM01 — Superconductivity as Phase-Locked Vortex Pairs

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is the superconducting "2" in `Φ₀ = h/2e` a *native count of two
   phase-locked W=1 vortices* (so flux quantisation, zero drag and the isotope effect all follow
   from one lattice-mediated locking mechanism), or is it only a re-narration that silently imports
   the BCS gap / Cooper-pair postulate to do the real work? Concretely: can a pair *bind* and a
   coherent wake *out-span the defect scale* with no gap put in by hand?
2. **Why does it matter?** — CM01 is the **superconducting node of the CM stack** (README): it turns
   the E59 "phase-locked vortex pairs" stub into a worked result and defines the `Φ₀ = h/2e` count
   that CM06's Josephson `K_J = 2e/h` reuses (the *same* "2"). If the locking is real, CM05
   (superfluidity, `κ = h/m`, the uncharged twin) and CM07 (aligned wakes) inherit the mechanism;
   if it is just a relabelled BCS gap, the whole branch is borrowed.
3. **How will we find out?** — Four gated phases (§④): the single-vortex drag (P1) and the
   **lattice-wave pair binding** (P2) run *before* any flux/isotope number, so the "2" is forced by
   geometry, not assumed. Touching a BCS gap or importing `Φ₀ = h/2e` as a given caps the grade at C.
4. **What would prove us wrong?** — §⑧: four falsifiers with numeric triggers and real failure modes —
   the pair-binding test (T2) and the isotope exponent (T4) can both come out the wrong way.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

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

## 8 · Falsification Tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | Normal-state drag = occlusion scattering | finite ρ of correct order for a metal (ρ_Cu ~10⁻⁸ Ω·m, order-of-magnitude) | if occlusion drag gives `R = 0` *above* T_c, or ρ off by >3 orders → resistance has another basis; thesis dead |
| T2 | **Pair binds via lattice wave** | bound pair with `ξ ≫` defect spacing: binding energy `E_b > 0` and `ξ/a_defect > 1` from the FD05 compression-wake channel alone | if the lattice-wave channel gives `E_b ≤ 0` (no bound pair) and the only way to bind is to insert a BCS gap by hand → no native pairing channel (→ C, not A) |
| T3 | `Φ₀ = h/2e` is a native count of TWO vortices | computed flux quantum within <1% of `h/2e = 2.0678×10⁻¹⁵ Wb`; the divisor is exactly 2 (= two locked W=1 vortices), not fitted | if the native phase-count gives `h/e` or any non-2 divisor, or `Φ₀` is only reproduced by *importing* the BCS `2e` → the "2" is not two vortices |
| T4 | Isotope effect `T_c ∝ M^{−½}` | fitted exponent `α = −0.5 ± 0.1` from `c_s ∝ M^{−½}` locking energy (matches Hg/Sn elemental SC) | if the SDT exponent is `0` or `−1` (locking energy independent of, or wrongly scaled with, lattice stiffness) → locking energy is not stiffness-set |

## 9 · Implementation Notes

Double precision; dimensionless `T/T_c`. Model defects as a random-but-seeded (index-derived, not
`Math.random`) occlusion field. Plot: (a) R(T) dropping to zero at T_c; (b) field profile showing
λ_L expulsion; (c) T_c vs M on log axes (slope −½). Keep the "phonon" strictly the FD05 lattice
compression wave — naming it a phonon is fine (observable), importing a phonon *field operator* is not.
The Meissner step is EMC03 swirl expulsion (handedness), **not** a substance: never write "charge
radius"; the proton/electron scale is a boundary/wake radius. Φ₀ is a phase count, not a borrowed
unit. Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## 10 · Questions This Opens *(generative — log new ones in `CM01_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Does the FD05 frustration residual shift T_c?** If the lattice-wave channel that binds the pair
   carries the FLM08 frustration (the 0.103 r kissing-shell gap), is the locking energy — and so T_c —
   slightly off the clean-isotropy value? Is that the SDT signature distinguishing it from BCS?
2. **Is `Φ₀ = h/2e` the only divisor the lattice allows?** Could a three-vortex lock (W=1 triple)
   ever be stable, giving `h/3e`? If not, *why* does the lattice forbid it — is "2" the unique
   minimum-occlusion lock?
3. **Is high-T_c just a stiffer relay channel?** If T_c ∝ locking energy ∝ c_s, do the cuprate/hydride
   T_c records correspond to anomalously stiff compression channels — and does that predict a ceiling?
4. **Is the isotope α deviating from −½ a lattice-anharmonicity readout?** Real SC show α from 0 to
   −0.5; does SDT map the spread onto how much of the locking rides the *linear* FD05 wave vs the
   anharmonic short-k bend?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the P2 native pairing chain (T_c absolute value may be CALIBRATED(1) — list it)
- Engine namespaces actually used: law_III (occlusion drag), law_VI (vortex topology/wake), FD05 c_s, FD02 κ, EMC03 (swirl expulsion)
- Phase thresholds (committed before run):
    P1 ρ order-of-magnitude (finite, metal-like) · P2 bound pair E_b>0 AND ξ/a_defect>1 from the FD05 channel (no BCS gap)
    P3 R→0 below T_c, finite λ_L expulsion · P4 |Φ₀ − h/2e|/Φ₀ < 1% (divisor exactly 2); isotope α = −0.5 ± 0.1
- Forbidden retroactive changes: import a BCS gap into P2 then claim A; import Φ₀=h/2e as given; widen
    tolerances; plug T_c; IDENTITY-PASS; local constant namespaces; quote any moment in magnetons
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 lattice-wave channel gives `E_b ≤ 0` (no bound pair) | try the EMC03 co-rotation wake channel as the binder; report ξ | **OPEN** the pairing channel; do NOT insert a gap | import a BCS gap and grade A |
| P2 binds only if a gap is assumed | down-grade to **C** honestly (the import is the postulate) | — | claim A while importing the gap |
| P4 Φ₀ divisor ≠ 2 (gives h/e) | re-examine the phase single-valuedness count (one vortex vs the pair) | **OPEN**: report the actual divisor | retro-fit to h/2e |
| P4 isotope α ≠ −0.5 ± 0.1 | check the c_s ∝ M^{−½} locking-energy link | **OPEN** the isotope channel; report α | claim −½ when the run gives 0 |
| Rivals (BCS) match but SDT only reproduces, adds nothing | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (FD05 c_s, FLM10) | **DEFER** the affected phase; cite dependency ID | — | fabricate the binding curve |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** binding routes (FD05 compression-wake vs EMC03 co-rotation) — both are native.

### Disallowed adjustments

- Importing a BCS gap or `Φ₀=h/2e` into the native chain and grading A · post-hoc tolerance widening ·
  coefficient plugs · `atomic::`/GM/G in any native chain · quoting moments in μ_B/μ_N · burying the
  T2/T4 outcome.

---

*CM01 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
