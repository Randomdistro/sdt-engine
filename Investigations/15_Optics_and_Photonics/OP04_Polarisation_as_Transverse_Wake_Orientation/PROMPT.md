# OP04 — Polarisation as Transverse Wake Orientation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether linear/circular/elliptical polarisation, Malus's law, optical
   activity, and birefringence are *derivable* from the geometric orientation and handedness of the
   emission's transverse wake (GOM06 transverse channel + EMC03 ± redirection) — with **no photon
   spin operator and no Jones-matrix postulate** — or whether SDT can only re-skin the Jones calculus.
2. **Why does it matter?** — Polarisation is the textbook home of "photon spin." If it is just the
   transverse displacement vector projected and retarded by anisotropic closure, SDT removes spin-1
   from the photon ontology and hands OP06 a native polarised-mode description; OP02's Brewster
   reflection becomes the same projection. If the transverse wake cannot carry it, a spin postulate
   creeps back in and the no-photon-particle programme weakens.
3. **How will we find out?** — Four gated phases: a native transverse-state algebra (recovering Jones
   only as a limit) **before** any Jones matrix is invoked; Malus by projection; QWP/HWP by
   anisotropic-closure retardance; optical activity by handedness-split `c_local`. Recovering Malus by
   *applying* a Jones polariser matrix caps the grade at C (anti-tautology gate).
4. **What would prove us wrong?** — §Falsification, numeric: Malus off `cos²θ` by >0.1% (or crossed
   extinction floor not at machine zero); three-polariser revival absent; QWP fails linear↔circular;
   optical-activity rotation with the wrong handed sign.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

The load-bearing step is that **a polariser is anisotropic closure** that re-relays only the
projection of the transverse displacement onto its pass-axis and dumps the orthogonal component —
so `A→A cosθ` and `I∝cos²θ` are *geometry*, derived, not the Malus law restated. The handedness of
circular light must come from EMC03's ± redirection, **not** from an assigned photon spin ±ℏ. The
Jones calculus is the CONVERGENCE target: recovering it as a limit is the payoff; *using* a Jones
matrix to produce Malus or QWP action is the identity and caps the grade at **C** (row IMPORTED). No
"charge" substance enters: the transverse orientation is a displacement geometry, the handedness a
relay redirection.

## Question

In SDT light is an emission with a real **transverse** structure — the relay impulse displaces the
lattice sideways as it advances (GOM06 transverse channel), and that displacement has an
orientation and a handedness (EMC03 ± redirection). **Can linear, circular, and elliptical
polarisation, Malus's law `I = I₀cos²θ`, optical activity (rotation of the plane), and
birefringence all be reproduced as the transverse orientation/handedness of the emission's wake —
with no photon spin operator and no Jones-matrix postulate, those being the targets?** Polarisation
becomes a geometric property of how the relay impulse is oriented in the plane perpendicular to its
travel, and a polariser is a lattice that only re-relays one transverse orientation.

## SDT mechanism & hypotheses

The emission carries a transverse displacement vector (linear) or a rotating one (circular,
handedness from EMC03). A polariser is anisotropic closure: it relays the projection of the
transverse displacement onto its pass-axis and dumps the orthogonal component.

- **H1 (linear = fixed transverse orientation):** Malus follows from projecting the transverse
  displacement amplitude onto the pass-axis, `A→A cosθ`, so `I ∝ cos²θ` — geometry, zero fit.
- **H2 (circular = handedness):** left/right circular = the two EMC03 handednesses of the rotating
  transverse wake; linear = equal superposition; the quarter-wave plate is a closure-anisotropic
  relay that retards one transverse axis by a quarter relay-wavelength.
- **H3 (optical activity = chiral lattice):** a handed (chiral) medium relays the two handednesses
  at slightly different `c_local`, rotating the linear plane by `Δφ ∝ (n_L−n_R)L` — same closure
  mechanism as OP01, now handedness-split. Birefringence = orientation-split `n`.

## Strategy

**Phase 1 — Transverse state algebra.** *Goal:* a native description of polarisation states from the
transverse displacement vector. *Method:* GOM06 transverse channel + EMC03 handedness. *Success:*
linear/circular/elliptical states represented without importing Jones calculus (recover it as a limit).

**Phase 2 — Malus.** *Goal:* `I=I₀cos²θ`. *Method:* project displacement onto polariser pass-axis.
*Success:* `cos²θ` exact; crossed-polariser extinction and the three-polariser "revival" reproduced.

**Phase 3 — Retarders & circular.** *Goal:* quarter/half-wave plate action. *Method:* anisotropic
closure retards one axis. *Success:* QWP turns linear↔circular; HWP rotates linear by 2θ.

**Phase 4 — Optical activity (stretch).** *Goal:* plane rotation in a chiral medium. *Method:*
handedness-split `c_local`. *Success:* rotation `∝ L` with correct sign; sugar-solution magnitude to order.

## Success criteria

- **PASS (A):** Malus, circular states, QWP/HWP, and rotation sign all from transverse orientation + handedness, zero fits.
- **QUALIFIED (C):** the above with retardance/`Δn` magnitudes CALIBRATED via measured material anisotropy (expected).
- **PENDING (D):** linear + Malus recovered, circular/retarders only schematic.
- **FAIL (F):** polarisation cannot be carried by the transverse wake without a spin postulate.

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | Malus by projection | `I=I₀cos²θ` exact; crossed-polariser extinction at machine zero | transmitted `I` off `cos²θ` by >0.1% at any θ, or crossed floor not ≤1e-12·I₀ ⇒ polarisation is not transverse-orientation projection |
| F2 | Three-polariser revival | inserting a 45° polariser between crossed pair restores `I₀/8` | revival absent or magnitude off `I₀/8` by >1% ⇒ projection picture wrong |
| F3 | Quarter-wave plate | linear↔circular conversion; ellipticity within 1% of ideal QWP | QWP does not produce circular (DOC<0.99), or HWP rotation ≠ 2θ ⇒ retarder is not anisotropic closure |
| F4 | Optical activity sign | rotation `Δφ ∝ (n_L−n_R)L`, **handed sign set by EMC03** | rotation magnitude not ∝L, **or the handed sign is wrong** ⇒ handedness ≠ EMC03 ± redirection |
| F5 | Anti-tautology | Malus/QWP produced by projection+retardance, not by a Jones matrix | if Malus/QWP only reproducible by applying a Jones polariser/retarder matrix ⇒ Class capped at **C**, row IMPORTED |
| F6 | No spin postulate | the whole table runs on transverse displacement + EMC03 handedness | if any result needs an assigned photon spin ±ℏ or a Stokes-parameter axiom as mechanism ⇒ no-photon-particle claim fails here |

## Dependencies

**Upstream (required):** OP01 (`n=1/(1−z)`, handedness-split `c_local` for activity/birefringence),
GOM06 (transverse channel — the wake displacement vector, [[project_cq44_gravitational_waves]]),
EMC03 (± redirection = the two handednesses, [[project_cq47_repulsion_inverse]]), **Law V** (transverse
vs forward budget). **Downstream (unblocked):** OP06 (polarised laser modes), LCD/waveplate
engineering, polarisation lensing. **Lateral:** OP02 (Brewster produces polarised reflection — same
projection). **Framework:** `Theory/00_Ruleset.md`, `Theory/05` audit spine.

## Questions This Opens *(generative — log new ones in `OP04_VERDICT.md`)*

1. **Is "photon spin ±1" exactly EMC03 handedness?** If left/right circular = the two ± redirections
   of the rotating wake, does the spin-1 selection rule in atomic transitions (OP05/QM06) become a
   handedness-matching condition with no spin operator?
2. **Is birefringence the same `n(z)` as OP01, just orientation-split?** If `n_o,n_e` are two
   anisotropic-closure indices, can calcite's `Δn` be predicted from lattice anisotropy rather than
   tabulated — tying OP04 to the matter-index question OP01 left OPEN?
3. **Does optical activity bound a chiral lattice asymmetry?** If `(n_L−n_R)` comes from a handed
   closure, is there a smallest measurable rotation that bounds intrinsic vacuum chirality (cf. cosmic
   birefringence searches)?
4. **Is the QWP retardance a relay-tick count?** Is "a quarter-wave of retardation" literally one
   transverse axis lagging by `N/4` relay ticks — making waveplate thickness a spation-count?
5. **Does the transverse budget cap polarisation purity?** Via Law V, is there a forward/transverse
   partition limit that forbids perfectly circular light at grazing relay angles — a testable
   ellipticity floor?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the projection chain (material `Δn`/retardance = MEASURED-INPUT if used)
- Engine namespaces used: depth_closure:: (n, c_local), law_V:: (transverse budget), EMC03 handedness
- Phase thresholds (committed before run):
    P1 native state algebra (Jones recovered as limit) · P2 Malus `cos²θ` ≤0.1%, crossed ≤1e-12,
    3-polariser revival `I₀/8` ±1% · P3 QWP linear↔circular DOC≥0.99, HWP 2θ · P4 activity ∝L, sign correct
- Forbidden retroactive changes: apply a Jones matrix then claim A; assign photon spin ±ℏ as
    mechanism; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (numeric triggers; optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P2 Malus off `cos²θ` by >0.1% | recheck projection of the transverse displacement amplitude | **KILL** H1 | tune to fit `cos²θ` |
| Malus only via Jones matrix | down-grade to **C**; tag row IMPORTED | — | claim A while applying Jones |
| P3 QWP DOC<0.99 | re-derive single-axis retardance from anisotropic closure (relay-tick lag) | **OPEN** retarder action | borrow a Jones retarder as mechanism |
| P4 activity handed sign wrong | re-anchor the sign to EMC03 ± redirection, not a chosen convention | **OPEN** the chiral-lattice link | flip the sign by fiat to match data |
| Any result needs photon spin ±ℏ | re-express via transverse orientation + handedness | **KILL** the no-spin claim, report it | smuggle a spin operator / Stokes axiom |
| Material `Δn` needed but unpredicted | use measured `Δn` as MEASURED-INPUT (C-class on magnitude) | **DEFER** the magnitude | call a fitted `Δn` "derived" |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
