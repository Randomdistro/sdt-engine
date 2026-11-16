# QM02 — VERDICT: Uncertainty as Relay Bandwidth

**J. C. Harvey, Melbourne — 2026-07-04.**
Tool: `qm02_relay_bandwidth.py` (L=8192 lattice, machinery only). Real stdout: `qm02_results.txt`.
Pre-commitments: `RUN_LOG.md` (frozen 2026-07-03; ADJ-1 = pre-run scope note, no threshold touched).

## What was actually derived (machinery, no quantum object anywhere)

A wake pulse is a real displacement field; its elastic energy density is f² (Law-I strain energy —
classical mechanics of any strained medium, not a probability rule). Question run: does the
energy-weighted width product Δx·Δk have a floor of ½ for every buildable pulse?

1. **Continuum regime (width ≥ 3a): floor holds, Gaussian uniquely saturates.**
   Gaussians σ=3..100a: product = 0.5000 (saturation, <1% incl. cell term). Box W=64: 3.815.
   Triangle W=64: 0.5512. Exponential s=16: 0.7133. Gates P1a all PASS as committed. The ½ is
   classical bandwidth machinery — no ψ, no commutator, no operator appears in the tool.
2. **Lattice-scale probe (pre-registered danger case): the point-lattice HAS NO floor.**
   Single-site pulse: 0.0000; σ=0.3a: 0.1466 — the floor is genuinely beaten if spations are
   points. Pre-registered pivot (not retro): a spation has finite extent a, so a one-cell pulse
   carries Δx ≥ a/√12. Under that definition the floor survives everywhere (min 0.5048; delta
   0.5236). Gate P1b PASS. **Finding: granularity itself enforces the floor at the cutoff —
   the uncertainty floor and the finite spation are the same fact.**
3. **Time axis:** Gaussian-in-time Δt·Δω = 0.5000; damped emission pulse: Δt = τ exactly,
   spectral FWHM·τ = 1.0001 (gate ±2% PASS) → Γ = ℏ/τ for QM06, inheriting exactly one borrow.
4. **Lattice fingerprint (new, honest):** floor = ½(1 + O(a²/Δx²)). At lab scales the correction
   is ~10⁻⁵⁰: a real prediction, unfalsifiable at current precision — stated as such, not sold.

## The located ℏ entry point (the question this run answers)

**ℏ enters exactly once, and never as a commutator.** The pulse machinery is dimensionless in
(x,k) and produces the ½. The conversion Δk → Δp uses k = mv/ℏ, obtained from: FD02 measured
circulation κ = h/m (OBSERVED anchor, 0.02%) + the substrate phase-gradient identity
v = (κ/2π)∇φ (superfluid substrate kinematics — a postulate of the substrate model, NOT yet
derived from tick mechanics). That single identity is the **flagged borrow** that caps the grade
at C, per the prompt's own expected landing. `[x,p]=iℏ` appears nowhere.

**Scope (FLM14 ADJ-7):** this floor binds the **pulse channel only**. The geared constraint
channel (uncapped, no free energy) carries no pulse bandwidth; the theorem says nothing about it.
QM02 therefore does NOT conflict with FLM14's same-tick constraint propagation.

## Determinism claim (T3): PASS

Nothing in the chain required the vortex's own (x,p) to spread — only the wake's spectrum. The
vortex keeps sharp per-tick values; "uncertainty" is the wake's bandwidth. No ontic randomness owed.

## HUNTER §D — seven questions (on the OPEN closure: Phase 3 + the k→p bridge)

1. **Why open?** The ½ is produced; the coefficient ℏ is not — the machinery has no momentum
   scale until the wake dispersion (how spatial frequency maps to vortex momentum) is supplied.
   Exact locus: the single line p = ℏk.
2. **Recoverable?** In principle yes: derive v = (κ/2π)∇φ from tick-relay mechanics. Per HUNTER
   §G.3 the FLM14 rotation DOF is a new carrier the old "can't be built clean" proofs never
   examined — status OPEN-again, not foreclosed.
3. **What did the target fail to account for?** Vortex–wake phase-locking: how the dragged
   wake's phase advances per tick as a function of vortex speed.
4. **Errored premise?** None proven errored. This is a **closure debt** (an un-derived kinematic
   identity), not a wrong premise. Phase 3 (spreading packet) is the same debt on the time axis.
5. **What freedom corrects it?** The proportionality flow ∝ phase-gradient with coefficient κ/2π.
6. **Native quantity or knob?** Native candidate: κ is already a measured, quantised SDT anchor
   (FD02, 0.02%). Owed: the mechanics forcing that coefficient. Not a knob — nothing was tuned here.
7. **Cascade?** **YES** — same root as QM01 Phase-1 (λ = h/p as the wake relay period) and QM03's
   mass-gap identification (E = ℏω). Root id: **WAKE-DISPERSION** (owner: ROOT-SIM/FLM14 rotation
   dynamics).

**Recovery grade: PARTIAL** — route named (derive the phase-gradient identity from tick
mechanics), freedom native-candidate, not yet justified. Correction is CLOSE, not amputate.

## New questions logged

1. Is the a²/12 cell term observable in any engineered lattice analog (photonic/phononic crystal
   at its own cutoff)? The floor-restoration at the cutoff is testable in analog systems even if
   not at ℓ_P.
2. Does the entropic form of the band-limit hold on the cell definition too, and does it undercut
   or match the variance form at the cutoff?

---
**Prompt completion B · Physics class CONVERGENCE (½ floor NATIVE machinery; ℏ attaches via one
flagged borrow; Phase 3 OPEN) · Recovery PARTIAL · Cascade root WAKE-DISPERSION**
