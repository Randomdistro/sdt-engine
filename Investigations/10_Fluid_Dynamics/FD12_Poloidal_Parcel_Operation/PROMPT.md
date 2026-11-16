# FD12 — The poloidal parcel operation (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the next step. Harvey's claim and the 2026-07-26 gates are kept below the line. The claim is unchanged; the gates are superseded where stated.

## 1. State after the reset audit (`FD12_RESET_ASSESSMENT_2026-10-10.md`)
- **P2 is a registration defect, found before any computation: its pass classes are empty under its own sweep.**
  - The sweep is λ/L ∈ {1/4 … 16} with ℓ_c = λ*/2, so it gives L/ℓ_c ≤ 8.
  - G2-STRONG needs L/ℓ_c ∈ [24, 96] and G2-ORDER needs [10, 200].
  - Every outcome would be G2-FAIL. A criterion that cannot pass is not a test.
- **P1 is blocked on its supplier.** It needs the "FD01-earned relay/NS lattice", and FD01 has not been re-run under the reset protocol. A plain Navier–Stokes solver would not test the relay claim. P1's class is capped at consistency (Lamb dipole).

## 2. What the defect teaches
The pipe's L/ℓ_c ≈ 48 lies outside any sweep that only spans wavelengths comparable to L. The operation's coherence length must therefore be either:
- **(i)** much shorter than the wave forcing it, i.e. set by the parcel's own roll and not by the imposed wavelength; or
- **(ii)** a 3-D spanwise-streak scale, which the 2-D surrogate cannot represent.

Each is a different claim about what sets the roll, and the re-registration must choose one before running.

## 3. Re-registration (round 2; to be fixed before any tool runs)
- **P2-i (2-D, roll-set):** extend the sweep to λ/L ∈ {1/64 … 16} (log-spaced, 11 values), so that L/ℓ_c reaches 128 and the pass bands [24, 96] and [10, 200] are reachable. Convention ℓ_c = λ*/2, unchanged. Same gates.
- **P2-ii (3-D, streak-set):** an explicit spanwise-periodic optimum in a 3-D channel. Only if Harvey reads the claim as 3-D; "2D-like" in the claim points to P2-i.
- **Validation added:** a planted-optimum test on a synthetic response curve. The analysis must recover λ* to one grid step before the physics sweep runs.
- **P1:** after FD01 is re-run (supplier). Then G1a and G1b as registered, with the diffusion-only control.

## 4. Prohibitions
- No widening of the bands after a run.
- No change to the ℓ_c convention after seeing λ*.
- No fields as primitives.
- No time-arrow framing: parcels travel, stall, roll and rebound.

---

## Superseded gates and original claim (2026-07-26, kept as written)

# FD12 — The Poloidal Parcel Operation (Harvey 2026-07-26)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, written BEFORE the tool (gates below are
> pre-commitments). **Run class target: DIRECT** (main session, no agents).
> **Inherits** R0–R5 anti-creep verbatim (derivation basis inputs; no rival axioms; honesty over success).

## The claim (Harvey, verbatim core)

All fluid movement is a 2D-like poloidal operation, from the singular molecule to the macro
volume: the centre carries momentum; the parcel moves forward, pushes what is ahead, stalls
aside, is moved aside, clears the bath for what is coming, rolls back along the length of the
moving fluid, and is caught in the rotating toroidal vortex. The apparent rotation constricts
the poloidal channel and slightly reduces pressure as stalled momentum converts to lateral ring
movement — mixing. Variations in this one operation create all flow variation.

## Why it has teeth

If the operation is universal, it must supply the numbers the FD suite left calibrated:
FD03's coherence length (the poloidal roll dimension — pipe demands L/ℓ_c ≈ 48), FD10's
shedding clock, FD04's cascade self-similarity. First outing tests the two cheapest.

## Phases and PRE-COMMITTED gates

**P1 — Does the operation exist as the natural organisation?** Release a compact forward-momentum
slug (radius a, speed U, Re_slug = Ua/ν = 150 committed) in a quiescent 2-D bath (the poloidal
plane — the claim is explicitly "2D-like") using the FD01-earned relay/NS lattice. Run a
diffusion-only control (advection off, same IC).
- **G1a (formation):** two opposite-sign vorticity extrema, magnitudes within 15%.
- **G1b (self-propulsion):** vorticity-weighted centroid advances ≥ 1.0·a while the control
  advances < 0.1·a.
- **G1c (roll-back):** return flow u < −0.05·U_pair at flank probes (|y−y₀| ∈ [1.5a, 3a]).
- **G1d (closed cell / carried bath):** centre jet u_core ≥ 1.3·U_pair (co-moving recirculation).
Honest class ceiling for P1: **consistency/convergence** — vortex-pair self-organisation is
known physics (Lamb dipole); what P1 establishes is that the SDT relay lattice produces the
operation with all four signatures, i.e. the picture is the lattice's own behaviour, not an
overlay. It cannot, alone, discriminate.

**P2 — THE DISCRIMINATOR: forward coherence length.** Linearised perturbation on plane
channel flow U(y) = U₀(1−(2y/L)²) at Re = U₀L/ν = 1000 (below transition — transient-growth
regime), rigid no-slip walls. Sweep perturbation wavelength λ/L ∈ {1/4, 1/2, 1, 2, 4, 8, 16};
measure the energy gain G(λ) = max_{t ≤ 10·L/U₀} E(t)/E(0). The operation's selected roll is
λ* = argmax G; **committed convention (before any run): ℓ_c = λ*/2** (one roll = half a
wavelength). Prediction exported: Re_crit = (L/ℓ_c)².
- **G2-STRONG:** L/ℓ_c ∈ [24, 96] (factor 2 around pipe's back-solved 48) → the roll IS the
  coherence length.
- **G2-ORDER:** L/ℓ_c ∈ [10, 200] → right order, geometry factor owed.
- **G2-FAIL:** outside [10, 200], **or** G(λ) monotone (no interior maximum → no finite roll
  selected) → the identification *as posed* is recorded dead. No re-scoping after the number.
Caveat declared now: this is a 2-D planar surrogate for the pipe; a genuine geometry factor
(planar vs axisymmetric) may sit between the two — if G2-ORDER passes but G2-STRONG fails, the
axisymmetric rerun is the named next step, not an excuse.

**Deferred (not gated here):** ring-within-ring cascade statistics; shedding-clock identity;
tracer mixing entrainment. Each needs its own pre-commit.

## Outputs
`fd12_poloidal_parcel.cpp` (one tool, both phases, prints every gate) →
`fd12_rerun_<date>.txt`, `FD12_VERDICT_DIRECT_<date>.md`.

## Forbidden
Tuning Re_slug/Re/domain after seeing results; changing the ℓ_c convention after P2 runs;
grading G1 as evidence FOR the picture over rival readings; silently dropping the control.
