# QM01 — Deterministic Double-Slit from the Lattice Relay

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol (`INVESTIGATION_STACK.md` §0) and rules R0–R5 verbatim.
> **This is the single largest standing debt in the SDT paradox census** (`PARADOX_CENSUS.md` §8.2 #1):
> SDT owes a *deterministic* account of the double-slit pattern, the Born rule, and Bell correlations.

---

## 1 · Executive Summary

A particle in SDT is a **hard, localised solid vortex** travelling through a granular relay
lattice — never a wavefunction, never a probability cloud, never "both slits at once." **Can the
two-slit interference pattern, the Born rule (intensity ∝ amplitude²), and single-particle build-up
be reproduced from deterministic lattice relay mechanics alone — the vortex going through exactly
one slit while its convergence wake passes through both?** Resolving this converts SDT's biggest
liability into a result: it would show wave–particle "duality" is a **shadow of a wrong premise**
(the collapsing ψ) rather than a fact the theory must absorb. **We expect:** the *carrier wake*
(the convergence pulse the vortex rides) diffracts through both apertures and steers the vortex to
landing sites whose density reproduces the cos²(πd sinθ/λ) fringe to <1%, with the de Broglie
wavelength λ = h/p emerging as the wake's relay wavelength, not an imposed postulate.

## 2 · Physical Context

The lattice is a relay of spations passing convergence throughput at one tick (`c = ℓ_P/t_P`). A
moving vortex is not alone: it drags a **wake** — a coherent disturbance in the relay field ahead of
and around it (the same wake that does PPT06 traction and APS04 multipole work). Two channels travel
together: the **solid vortex** (carries the mass, the charge-handedness, the "which-slit" fact) and
its **wake pulse** (carries the phase, spreads, diffracts). This is structurally a *pilot-wave/relay*
ontology — but it must be **derived from SDT primitives, not borrowed from de Broglie–Bohm**: the
"pilot" is the literal convergence wake, the guidance equation is least-resistance steering down the
wake's pressure gradient (the same rule that makes orbits least-resistance paths, [[project_cq43_variable_closure]]).

Key variables: vortex momentum `p` (and λ = h/p, to be *derived* as the wake relay wavelength, not
assumed); slit separation `d`, width `a`; screen distance `L`; landing coordinate `x`; wake phase
`φ(x)` accumulated along each path; relay tick `t_P`, spacing `ℓ_P`. The pattern intensity `I(x)`
is a *count* of vortex landings, never a squared abstract amplitude.

## 3 · Theoretical Framework

Build only on: Law I (convergence throughput, `P_conv`), Law III (occlusion), Law V (movement
budget `v² + v_circ² = c²`), Law VI (vortex topology + wake/traction, PPT06/APS04), and the relay
state-machine (FLM02 GPI, FLM05 tick-by-tick contact/gap). **Forbidden as inputs:** wavefunction,
ψ, Schrödinger evolution, Born postulate, superposition-as-ontology, "measurement collapse,"
Hilbert space. These are the *targets to reproduce*, never the machinery.

Working hypotheses:
- **H1 (two channels):** the vortex passes one slit; the wake — a convergence-pressure pulse —
  is broad enough (width set by the relay coherence length) to enter **both** slits and self-overlap
  on the far side.
- **H2 (relay wavelength):** the wake's spatial period is λ = h/p with h emerging from the lattice
  action quantum (one-vortex circulation `κ = h/m`, already clean in FD02 to 0.02%) — so de Broglie
  is a **relay dispersion relation**, not a postulate.
- **H3 (Born rule as residence density):** the vortex steers down the wake pressure gradient; the
  long-run landing density equals the wake intensity (overlap of the two slit-pulses), giving
  `I(x) ∝ |pulse_A + pulse_B|²` **as a count**, not as an axiom. The square is geometric (energy
  density of a superposed pressure field ∝ amplitude²), the SDT-native origin of "Born."
- **H4 (which-way destroys fringes natively):** any interaction that reads the vortex's slit
  (occludes one wake branch) removes that branch from the overlap — decoherence is **wake
  spoiling**, mechanical and local, with no observer and no collapse.

## 4 · Investigation Strategy

**Phase 1 — Relay wake kinematics (derive λ).** Model a vortex of momentum `p` moving through the
relay; compute the spatial period of its convergence wake from the tick mechanics (FLM02/FLM05).
*Success:* recover λ = h/p to <1% with h traced to `κ = h/m`, **no fitted wavelength**.

**Phase 2 — Single-slit envelope.** Pass the wake through one aperture of width `a`; compute the
far-field pulse from relay Huygens construction (each spation on the slit re-emits one tick).
*Success:* recover the sinc² single-slit envelope, width ∝ λL/a, from relay summation alone.

**Phase 3 — Two-slit overlap + vortex steering.** Two apertures; sum the two wake pulses; release
N vortices one at a time, each entering one slit (50/50) and steered by the *total* wake gradient to
a landing `x`. Histogram the landings. *Success:* histogram → cos²(πd x/λL)·sinc² to RMS <1% over
N≳10⁴; **single-particle build-up** reproduced (sparse dots early, fringe emerges late).

**Phase 4 — Which-way / decoherence.** Add a wake-spoiling interaction at one slit; show the fringe
*continuously* washes out as spoiling strength rises (visibility V vs spoiling), recovering the
complementarity relation `V² + D² ≤ 1` (distinguishability D) as a **mechanical** trade, no collapse.

**Phase 5 (stretch) — Bell scope memo.** Write (not necessarily run) the honest position on Bell:
does a *local* relay-wake model evade Bell's theorem, and if not, what non-local relay feature (the
throughpole's instantaneous in/out, [[project_foundational_ontology_influx_monopole]]) is invoked,
and is that a debt or a feature? **Mark OPEN if no clean local route exists — do not fabricate.**

## 5 · Success Criteria

- ✅ **PASS (Class A):** Phases 1–4 native; λ=h/p derived; fringe + build-up + decoherence to <1%
  with zero fitted parameters; Born square shown as superposed-pressure energy density.
- ✅ **QUALIFIED (Class C):** pattern reproduced but the amplitude-squared step or λ borrows one
  flagged coefficient; build-up + which-way qualitatively correct. (This is the expected landing.)
- ⚠️ **PENDING (Class D):** relay wake diffracts and overlaps, but vortex-steering → Born density
  shown only heuristically; flag the gap.
- ❌ **FAIL (Class F):** the two-channel model cannot produce fringes without re-importing ψ.
  Report it honestly; the census debt stands.

## 6 · Outputs

1. `QM01_DERIVATION.md` — relay-wake kinematics, λ=h/p, single/double-slit summation, Born-as-count.
2. `qm01_double_slit.cpp` — standalone C++20: relay Huygens wake + one-at-a-time vortex steering;
   emits `qm01_pattern.csv` (x, count) and a visibility-vs-spoiling table.
3. `qm01_results.txt` — fringe RMS vs analytic; build-up snapshots at N = 10², 10³, 10⁴.
4. `QM01_VERDICT.md` — A/C/D/F with the honest disposition of the Born and Bell sub-claims.

## 7 · Dependencies & References

**Upstream:** FLM02 (GPI), FLM05 (tick state machine), PPT06/APS04 (the wake), FD02 (κ=h/m clean),
ROOT-SIM (per-contact rule — the deepest dependency; flag where Phase 1 leans on its unproven core).
**Downstream:** QM measurement/Bell follow-ons; any "quantum" correspondence (tunnelling, uncertainty
as relay bandwidth). **Related:** `PARADOX_CENSUS.md` §8.2 (#1 debt), E81 (electron diffraction,
VERIFIED — lattice scattering), [[project_foundational_ontology_influx_monopole]] (no ψ, no collapse).

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | λ is the relay wake period | λ = h/p ± 1% with no fitted scale | de Broglie not native; relay dispersion wrong |
| T2 | fringe = wake overlap count | cos²·sinc² to <1% over 10⁴ vortices | two-channel model insufficient |
| T3 | build-up is one-at-a-time | sparse→fringe with strictly one slit per vortex | "both slits" smuggled back in |
| T4 | decoherence = wake spoiling | V falls continuously with spoiling; V²+D²≤1 | needs observer/collapse → census debt persists |

## 9 · Implementation Notes

Use double precision; work in dimensionless `x/(λL/d)`. Seed the per-vortex slit choice and steering
from a deterministic but varying source (index-derived, **not** `Math.random`) so the build-up is
reproducible. Plot: (a) landing histogram vs analytic overlay; (b) visibility vs spoiling strength;
(c) three build-up panels. **Do not** insert the cos² by hand — it must fall out of summing two relay
pulses. The discipline (R4): a clean Class-C with an honestly-flagged amplitude-square borrow beats a
forced "A" that hides a ψ.
