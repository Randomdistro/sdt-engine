# PM01 — Magnetism as Collective Vortex Circulation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is `B` a *genuine emergent quantity* — the curl of a coarse-grained
   wake-circulation velocity that exists with or without us naming it — or are we just relabelling the
   pre-existing `qv×B` and writing "swirl" over "field"? Concretely: can the **Lorentz force sign**
   (the ± that distinguishes electron from proton deflection) be **forced by EMC03 handedness alone**,
   *before* any `B` symbol is introduced — or does the sign have to be put in by hand to match
   experiment? If it has to be put in by hand, magnetism is borrowed narration and PM01 fails its own test.
2. **Why does it matter?** — If `∇·B=0` becomes a **theorem** (curl of a flow has no divergence; H3) and
   the Lorentz sign is **derived** from handedness, then the monopole prohibition (E58) and one half of
   Maxwell stop being postulates and become consequences of the throughpole ontology. PM01 is the root of
   the whole plasma stack: PM02 (changing swirl), PM03 (relay-pulse waves), PM04 (`ω_p` magnetised
   limit), PM06 (cyclotron occlusion orbit), PM07 (MHD back-traction) all consume PM01's `w` and its
   sign convention. A wrong sign here propagates to all six.
3. **How will we find out?** — Four gated phases (§④). The **native** wake-circulation field and the
   handedness sign matrix (P1→P3) run **before** any `qv×B` is written down; the SI map to `qv×B`/`B`-in-
   tesla happens only on the *final* line. Quoting any moment in µ_B/µ_N at any earlier step is an
   automatic units FAIL (§5), not a soft downgrade.
4. **What would prove us wrong?** — §⑧, four falsifiers, each with the numeric outcome that kills it
   (wrong Ampère exponent, non-zero `∇·B`, a sign cell that matches experiment only by hand, a moment
   that needs µ_B).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired sign cell.

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
**Forbidden inputs:** B as a primitive field, magnetic monopoles, magnetons/µ_B/µ_N/Bohr-magneton,
spinors, virtual photons, gauge potentials-as-ontology, G/M-as-fundamental, QM wavefunctions as the
deflection mechanism. The Maxwell relations and `qv×B` are **targets**.

**Anti-tautology firewall (the load-bearing distinction).** Two steps look alike and must be kept
apart. (i) The *trivial identity*: once you have written `B`, "magnetism is `qv×B`" is true by
definition and teaches nothing. (ii) The *load-bearing derivation*: building `w = Σ wakes`, taking its
curl, and getting the `1/r` Ampère profile **and the deflection sign** out of EMC03 handedness, with
**no `B`/`qv×B`/magneton consumed anywhere in the chain**. Importing the answer — reading any `B` in
tesla, any µ_B/µ_N, or hard-coding the Lorentz sign to match experiment — **caps the grade at C**. The
SI map (`B_native → B` in tesla, `→ qv×B`) is allowed only on the final reporting line, clearly tagged.

**Native-before-borrowed (mandatory ordering).** Native yardsticks first: per-vortex circulation `Γ_v`
(from κ = h/m and PPT06 traction), the electron-wake circulation, koppa-style closure. Only after the
native quantity is computed and the sign matrix is closed may an SI conversion appear. **Any magnetic
moment expressed in µ_B or µ_N — at any phase before the final line — is an automatic units FAIL** (the
`[[feedback_no_borrowed_units]]` rule), not a soft downgrade. The electron moment is to be quoted as a
wake-circulation quantity; B17 already gives a *dimensionless* g-factor (2.0023), which is fine to cite.

> **Engine tension flagged for Harvey (do not fake around):** `laws.hpp:197–199` stores the neutron /
> nuclear magnetic moments in **nuclear magnetons** (`measured::mu_N = −1.913…` in µ_N), and benchmark
> B17 reports the g-factor dimensionlessly but the nuclear-moment bench is magneton-based. So the
> no-magneton rule is currently **aspirational vs the engine**: PM01 must not introduce magnetons, but
> it cannot claim the engine is already magneton-free. State this explicitly in `PM01_VERDICT.md`.

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

## 5 · Success Criteria (canonical A–F) + anti-tautology / units gate

- ✅ **PASS (Class A):** Ampère `1/r` + `∇·B=0` (structural) + Lorentz **direction and ± sign** all
  derived natively from summed wakes and EMC03 handedness, **with no `B`/`qv×B`/magneton consumed in the
  chain**; result stated entirely in wake-circulation units; the SI map appears only on the final line.
  CALIBRATED budget = 0.
- ✅ **QUALIFIED (Class C):** the relations are obtained but only by **taking `qv×B` (or a `B` in tesla)
  as given**, or the deflection sign is matched by hand rather than forced by handedness, or one
  coarse-graining coefficient is convergence-matched. **Importing the answer caps the grade at C.**
- ⚠️ **PENDING (Class D):** swirl→`B_native` mapping shown but Lorentz magnitude only scaling-correct,
  or the magnetosphere phase deferred.
- ❌ **FAIL (Class F):** cannot get `v×B` structure/sign without re-importing a primitive `B`; **OR any
  magnetic moment is expressed in µ_B/µ_N before the final reporting line** (units violation — hard FAIL,
  not a downgrade); OR `∇·B ≠ 0` to numerical precision.

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

## 8 · Falsification Tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | B = wake-swirl curl | summed-wake azimuthal field scales as `r^{-1}` (Ampère) | fitted exponent ≠ −1 by >2% over a decade in `r` → B is not the curl of circulation; thesis dead |
| T2 | ∇·B=0 is structural | `\|∇·B_native\|` ≤ 1e-12 of `\|∇×w\|` everywhere (curl of a flow) | any node with `\|∇·B\|/\|∇×w\|` > 1e-9 → a monopole sneaked in → throughpole ontology (E58) breaks |
| T3 | Lorentz sign from handedness | sign matrix (±carrier × ±field) = 4/4 cells match observed `qv×B` sign, **forced by EMC03**, no by-hand flip | any cell that only matches after a hand-inserted sign flip → force law not occlusion-derivable → C, not A |
| T4 | moment is native circulation | electron moment = wake circulation; g-factor = B17's 2.0023 **dimensionless**, no µ_B/µ_N in the number | the moment can only be written in µ_B/µ_N → automatic units FAIL (no soft downgrade) |
| T5 | magnetosphere geometry | dipole tilt scale ~11° and magnetopause standoff ~10 R⊕ order-correct from traction, all SDT-native | standoff off by >1 order, or geometry needs µ₀-as-postulate / a dynamo axiom → magnetosphere not traction-derivable |

## 9 · Implementation Notes

Double precision; keep everything in native circulation units until a single, clearly-labelled final
conversion line. Visualise: (a) streamlines of `w` around a current; (b) test-vortex trajectory
curving in the field; (c) magnetosphere cross-section. Watch the sign bookkeeping in Phase 3 — the
handedness convention must be fixed once (EMC03) and used consistently. A native Class-C beats any
result that quotes a magneton (instant R-units violation). **Firewall comment in code:** mark the P1–P3
native chain `// NO B-in-tesla / NO qv×B / NO µ_B,µ_N here`; any SI cross-check is tagged `IMPORTED`.

## 10 · Questions This Opens *(generative — log new ones in `PM01_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing PM01 well.

1. **Is the electron g-factor's 0.00232 anomaly a wake-circulation correction?** If `B` is `∇×w`, the
   "anomalous" part should be the higher-ℓ (ℓ=2,3) terms of the electron's own wake (APS04). Does the
   B17 value fall out of the wake multipole expansion with no Schwinger `α/2π` series imported?
2. **Does `∇·B=0`-as-theorem make E58 (no monopole) and the throughpole ontology literally the same
   statement?** If a monopole is a divergence of a curl, it is a mathematical impossibility, not a
   missing particle. Can PM01 state that identity precisely enough to retire E58 as a separate result?
3. **What sets the µ₀ value natively?** SDT maps `B_native → B` in tesla only at the end; the conversion
   constant *is* µ₀. Is µ₀ a relay-stiffness ratio (like ε₀ is in PM03), and does `c² = 1/(µ₀ε₀)` then
   become a single relay-speed statement rather than two independent constants?
4. **Is the 11° dipole tilt a frustration residual?** The CRN kissing-shell gap (0.103 r, 7.356°
   deficit; FLM08) is a candidate geometric origin for a non-axial core circulation. Is the planetary
   dipole offset that deficit, or a convection accident?
5. **Does the no-magneton rule force a rewrite of the engine's nuclear-moment storage?** Given
   `laws.hpp:197–199` is in µ_N, what is the native wake-circulation expression for the neutron moment,
   and would adopting it change benchmark B17/B-class results? (Hand to Harvey — engine edit, not this prompt.)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (list any in the final SI map)
- Engine namespaces actually used: law_III, law_V, law_VI (traction/topology), bridge (koppa), magnetosphere.hpp
- Phase thresholds (committed before run):
    P1 Γ_v native (no µ_B/µ_N) · P2 Ampère exponent −1 ±2%, ∇·B/∇×w ≤ 1e-9 · P3 sign matrix 4/4 from handedness · P4 standoff order-correct
- Forbidden retroactive changes: import qv×B/B-in-tesla into the native chain then claim A; quote any moment in µ_B/µ_N pre-final-line; hand-flip a Lorentz sign cell; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM01)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 Ampère exponent ≠ −1 by >2% | refine coarse-graining mesh; check wake-sum convergence | **OPEN** the curl-of-`w` ↔ Ampère link; report exponent | retro-fit exponent to −1 |
| P2 `∇·B/∇×w` > 1e-9 anywhere | hunt the numerical divergence source (stencil, boundary) | **KILL** H3 honestly; a real non-zero divergence breaks E58 | average the divergence away |
| P3 a sign cell only matches by hand | re-derive the EMC03 focus/defocus handedness for that carrier | down-grade to **C** (sign imported, not forced) | hand-flip the cell and claim A |
| Any moment reachable only in µ_B/µ_N | seek the wake-circulation expression first | **units FAIL** — record it, do not soften | quote the magneton and call it native |
| P4 magnetosphere needs µ₀-postulate/dynamo axiom | restrict to traction-derivable geometry only | **DEFER** P4; note the missing native piece | import µ₀/dynamo as primitive |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM01 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
