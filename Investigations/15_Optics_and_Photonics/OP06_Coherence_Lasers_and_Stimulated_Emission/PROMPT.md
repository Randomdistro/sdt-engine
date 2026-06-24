# OP06 — Coherence, Lasers and Stimulated Emission

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

A laser is the cleanest macroscopic coherence in physics, normally explained by bosonic photon
statistics and stimulated emission of identical quanta. SDT has no photon-boson. **Can optical
coherence be reproduced as phase-locked relay emissions — many vortices re-emitting in lock-step,
the laser being a macroscopic relay phase-lock exactly analogous to the superconducting phase-lock
of [[CM01]] — recovering the lasing threshold, gain saturation, the Schawlow–Townes linewidth, and
`g⁽²⁾(0)=1` coherence, with stimulated emission being one emission triggering an in-phase re-emission
from an excited vortex rather than the cloning of a boson?** Coherence becomes a phase-lock order
parameter on the emitting lattice, the same order-parameter idea as superconductivity (E59).

## SDT mechanism & hypotheses

Each excited vortex can dump its stored displacement as an emission. Left alone the dumps are
random-phase (thermal light). A passing emission can *trigger* an excited vortex to re-emit
**in phase** (stimulated emission = phase-locked relay trigger). A cavity feeds the emission back so
the whole gain medium locks to one relay phase above threshold — a phase transition.

- **H1 (coherence = phase-lock order parameter):** define a relay phase-lock order parameter on the
  emitters; coherent (laser) above a critical inversion, incoherent (thermal) below — a phase
  transition, like CM01's superconducting condensate.
- **H2 (stimulated emission = in-phase trigger):** an incoming emission triggers an excited vortex to
  re-emit at the same relay phase; gain `g ∝ (N₂−N₁)`; threshold when round-trip gain = cavity loss.
- **H3 (Schawlow–Townes linewidth):** residual spontaneous (random-phase) dumps perturb the locked
  phase, giving `Δν_ST = πhν(Δν_c)²/P` — linewidth as phase-diffusion of the lock, not a quantum limit.
- **H4 (photon statistics ⇒ relay statistics):** `g⁽²⁾(0)=1` (coherent) and `=2` (thermal) follow
  from whether the emissions are phase-locked or independent — no boson bunching postulate.

## Strategy

**Phase 1 — Phase-lock order parameter.** *Goal:* define coherence natively. *Method:* relay-phase
order parameter over emitters (cf. CM01). *Success:* coherent/thermal as two phases of one model;
`g⁽²⁾(0)` 1 vs 2 recovered.

**Phase 2 — Gain & threshold.** *Goal:* lasing threshold. *Method:* in-phase trigger gain vs cavity
loss. *Success:* threshold inversion and slope efficiency reproduced for a model 4-level gain medium.

**Phase 3 — Linewidth.** *Goal:* Schawlow–Townes. *Method:* phase-diffusion from residual random
dumps. *Success:* `Δν_ST ∝ 1/P` scaling and prefactor to order.

**Phase 4 — Coherence length (stretch).** *Goal:* temporal/spatial coherence. *Method:* phase-lock
correlation time from OP03's relay sum. *Success:* coherence length `c/Δν` recovered.

## Success criteria

- **PASS (A):** threshold, gain, linewidth, and `g⁽²⁾` from one relay phase-lock, zero boson statistics.
- **QUALIFIED (C):** the above with gain-medium level energies/cross-sections as MEASURED inputs (expected).
- **PENDING (D):** coherence/threshold recovered, Schawlow–Townes only schematic.
- **FAIL (F):** coherence cannot arise without importing bosonic photon statistics.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 g⁽²⁾(0) | =1 coherent, =2 thermal from phase-lock | coherence needs a boson postulate |
| T2 threshold | round-trip gain = loss; sharp turn-on | stimulated emission ≠ in-phase trigger |
| T3 Schawlow–Townes | `Δν_ST ∝ 1/P` | linewidth not phase-diffusion of the lock |

## Dependencies

**Upstream:** OP03 (relay-Huygens phased sum), OP05 (emission↔vortex exchange = the gain event).
**Downstream:** quantum-optics reframes, frequency combs, optical clocks. **Related:** [[CM01]]
(superconducting phase-lock — the same order-parameter idea), E59 (superfluid/phase-locked
condensate), [[project_cq43_variable_closure]] (cavity `c_local`).
