# PM01 — Magnetism as Collective Vortex Circulation

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use SDT-native yardsticks (the vortex's own wake,
> koppa, traction `T=3(W+1)`). "Stop sneaking GM — and µ_B — into my model."

---

## 1 · Executive Summary

In SDT there is no magnetic field as a primitive and no magnetic charge (the monopole is
topologically impossible, E58; the convergence flow is a **throughpole**, never a source,
[[project_foundational_ontology_influx_monopole]]). **Can the magnetic field, the Lorentz force,
and a planetary magnetosphere be reproduced as the collective circulation of vortex wakes in the
relay lattice — B as a swirl-density field, not a fundamental?** This closes the gap flagged in the
conceptual-contamination audit (magnetism = native result wrapped in borrowed narration). **We
expect:** B emerges as the curl of the coarse-grained wake-circulation velocity of moving/aligned
vortices; the Lorentz force `qv×B` falls out as **differential occlusion** on a vortex crossing a
swirl gradient; and Earth's dipole geometry follows from `magnetosphere.hpp` traction, with the
field strength expressed natively (per-vortex circulation × number density), never in magnetons.

## 2 · Physical Context

A moving solid vortex drags a handed convergence wake (PPT06 traction, APS04 multipole). Many vortices
moving together (a current) or aligned (a magnet) sum their wakes into a **collective circulation
field** — a literal swirl in the relay throughput. What electromagnetism calls **B** is the
coarse-grained density/curl of that swirl; what it calls a **field line** is a streamline of relay
circulation. There is no second substance: the same lattice that carries occlusion (→ gravity,
Coulomb) carries circulation (→ magnetism). The electron's magnetic moment is the circulation of its
*own* W=1 wake (B17 already gives a native g-factor) — to be quoted as a wake-circulation quantity,
not µ_B.

Variables: vortex circulation `Γ_v` (one-vortex, from κ = h/m and traction T); number density `n`;
drift velocity `u`; collective swirl velocity `w(r)`; "B" ≡ coarse-grained `∇×w` in native units;
test-vortex velocity `v`; Earth core convergence gradient (from `magnetosphere.hpp`, GOM02 koppa).

## 3 · Theoretical Framework

Build on: Law III (occlusion), Law V (movement budget), Law VI (`law_VI::traction` T=3(W+1), wake
ℓ=1/2/3; `law_VI::topology`), PPT06, APS04, B17 (native g), `Engine/include/sdt/magnetosphere.hpp`.
**Forbidden inputs:** B as a primitive field, magnetic monopoles, magnetons/µ_B, spinors, virtual
photons, gauge potentials-as-ontology. The Maxwell relations and `qv×B` are **targets**.

Working hypotheses:
- **H1 (B = swirl density):** define `B_native ≡ (handedness)·∇×w`, w = Σ vortex wakes; show a
  straight current gives the `1/r` azimuthal circulation (Ampère's law as relay flux conservation).
- **H2 (Lorentz = differential occlusion):** a vortex of velocity `v` crossing a swirl gradient is
  occluded asymmetrically (more relay throughput blocked on one flank) → a sideways push exactly
  `∝ v×(∇×w)`, sign set by **relative handedness** (the EMC03 focus/defocus sign,
  [[project_cq47_repulsion_inverse]]). Magnitude in native units; map to `qv×B` only at the end.
- **H3 (no monopole, by construction):** `∇·B_native ≡ 0` because a swirl field is the curl of a
  flow — there is nothing to diverge from. Maxwell's "no magnetic charge" is then a **theorem**, not
  an observation (E58 reframed).
- **H4 (magnetosphere):** Earth's dipole = the collective circulation of the convecting core's
  vortex population, shaped by the solar-wind occlusion front; recover dipole tilt and the
  bow-shock standoff geometry from traction, no µ₀, no dynamo-as-postulate.

## 4 · Investigation Strategy

**Phase 1 — One vortex, one wake.** Compute a single moving vortex's circulation field from PPT06
traction. *Success:* `Γ_v` in native units; confirm B17 g-factor as this wake's circulation (quoted
natively, **not** in µ_B).

**Phase 2 — Collective field of a current.** Sum N drifting vortices; coarse-grain to `w(r)`; take
the curl. *Success:* azimuthal `B_native ∝ I/r` (Ampère) and the `∇·B_native = 0` identity exact.

**Phase 3 — Lorentz force from occlusion.** Send a test vortex across the Phase-2 field; compute the
asymmetric occlusion push. *Success:* force `= v×(∇×w)` in direction and magnitude; **sign from
handedness** matches the observed `qv×B` sign for + and − carriers (EMC03 lock).

**Phase 4 — Earth's magnetosphere.** Drive `magnetosphere.hpp` with the core convergence gradient +
solar-wind occlusion. *Success:* dipole geometry, ~11° tilt scale, magnetopause standoff order-of-
magnitude — all native; flag every measured input (solar-wind density, core radius) as MEASURED.

## 5 · Success Criteria

- ✅ **PASS (Class A):** Ampère + ∇·B=0 + Lorentz direction/sign all derived natively, zero fitted
  parameters; result stated entirely in wake-circulation units.
- ✅ **QUALIFIED (Class C):** relations reproduced with one flagged coarse-graining coefficient;
  magnetosphere geometry order-correct. (Expected landing.)
- ⚠️ **PENDING (Class D):** swirl→B mapping shown but Lorentz magnitude only scaling-correct.
- ❌ **FAIL (Class F):** cannot get `v×B` sign/structure without re-importing a primitive B.

## 6 · Outputs

1. `PM01_DERIVATION.md` — B as swirl-curl; Ampère/∇·B as relay theorems; Lorentz as occlusion.
2. `pm01_magnetism.cpp` — standalone C++20: current → field → test-vortex deflection; native units.
3. `pm01_results.txt` — Ampère `B(r)` table; Lorentz sign matrix (±carrier × ±field); magnetosphere
   standoff estimate vs measured.
4. `PM01_VERDICT.md` — A/C/D/F; explicit ledger confirming **no magneton** entered any number.

## 7 · Dependencies & References

**Upstream:** PPT06 (traction), APS04 (wake multipole), EMC03 (handedness sign), B17 (native g),
`magnetosphere.hpp`. **Downstream:** induction/Faraday (changing swirl), EM waves as relay
circulation pulses, condensed-matter magnetism (12_Condensed_Matter). **Related:** E58 (monopole
forbidden), CONCEPTUAL_CONTAMINATION_AUDIT (magnetism Pass-1 finding), [[feedback_no_borrowed_units]].

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | B = wake-swirl curl | Ampère 1/r from summed wakes | B not reducible to circulation |
| T2 | ∇·B=0 is structural | identically zero (curl of a flow) | monopole sneaks in → ontology breaks |
| T3 | Lorentz = differential occlusion | `v×B` direction + correct ± sign | force law not occlusion-derivable |
| T4 | moment is native circulation | g-factor matches B17 with no µ_B | borrowed-unit dependence remains |

## 9 · Implementation Notes

Double precision; keep everything in native circulation units until a single, clearly-labelled final
conversion line. Visualise: (a) streamlines of `w` around a current; (b) test-vortex trajectory
curving in the field; (c) magnetosphere cross-section. Watch the sign bookkeeping in Phase 3 — the
handedness convention must be fixed once (EMC03) and used consistently. A native Class-C beats any
result that quotes a magneton (instant R-units violation).
