# GD05: Galaxy Rotation Curves from Eclipse Saturation — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** RESULTS-ON-FILE (mixed), UN-VERDICTED · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on canon flags. **NO G, NO M** (§ contraband flag).
> **Run:** Pre-commit per phase in `RUN_LOG.md`; four-root sort (§⑨.E) on every FAIL.
---

## ⓪ The Golden Rule — five questions (answered, and partly ALREADY answered)

1. **What don't we know?** — **Whether SDT reproduces SPARC rotation curves with ZERO free parameters and a NATIVE (non-MOND) crossover.** *Partly answered on file:* the naive 3D eclipse model **FAILS real SPARC (RMS ~66%)** — the earlier "success" was a **circular mock**; the twin-regime **M4 convergence-floor** law reaches **RMS 23.8%, BTFR 3.58** but its crossover **borrowed MOND-simple** (contraband, not yet zero-param).
2. **Why does it matter?** — This is SDT's dark-matter replacement. A MOND-borrowed crossover means the a₀ scale is imported — the whole zero-param claim hinges on deriving that crossover natively (or via the mass-free koppa-density route).
3. **How will we find out?** — Three routes (§④): A naive eclipse (control — known ~66%); B M4 convergence-floor with the MOND crossover **purged/derived**; C **mass-free koppa-density** (GOM14, the honest no-GM route).
4. **What would prove us wrong?** — §⑧: if only a MOND-borrowed crossover reaches <25% RMS, the native mechanism is unproven (honest OPEN/DEGENERATE); if v_flat needs GM, the model is contraband.
5. **How will we know we're done?** — Dual verdict; RMS on ≥50 real SPARC galaxies with a **named, non-imported** crossover; BTFR slope + normalization from geometry, not fit.

> ### ⚠ GM CONTRABAND FLAG (fixed in-prompt this pass)
> The prior §2 wrote **`v_flat² = GM_bar,total × f(geometry)`** — **G and M are forbidden as fundamentals**
> (BORROW-SMUGGLE). Recast everything mass-free: gravity is occlusion, **g = v²/R**, **koppa ϟ = v²R/c²**
> (≡ GM/c², a *conversion only*). The rotation law must read in **v_surface, R, and koppa-density** terms —
> never GM. See Route C (GOM14 mass-free koppa-density: 693 systems, 5.9% vs 50.7% shuffled).

## 1. The Question
Rotation curves flatten (v→const) instead of falling as r^(−1/2). Standard physics invokes dark-matter halos. SDT: **eclipse saturation** — beyond a critical radius the convergence deficit from the disk direction saturates (Ω_disk → 2π), giving constant orbital velocity. Can this reproduce SPARC from **visible baryons only, zero free parameters, no G/M**?

## 2. Methodology (recast mass-free)

**Phase A — Eclipse saturation (control).** At radius r, convergence arrives from 4π; the disk occludes a fraction; Ω_disk grows with r; at Ω_disk ≥ 2π the deficit saturates → v_flat. *Known result: naive 3D version RMS ~66% on real SPARC — keep as the control, do not re-mock it.*
**Phase B — M4 convergence-floor (the live route).** The twin-regime (bulge ⊕ disk) M4 floor law (RMS 23.8%, BTFR 3.58). **The crossover must be DERIVED, not borrowed from MOND-simple.** Movement-only: v²(r) = c²·(occlusion deficit fraction)·(geometry) — a koppa-density, not GM.
**Phase C — Mass-free koppa-density (GOM14).** Score each system by koppa-density (v²R/c² per baryon column), no mass assigned. *On file: 5.9% (real) vs 50.7% (shuffled) — the mechanism has signal.* Extend to the full SPARC set.
**Phase D — BTFR.** M_bar ∝ v_flat⁴. Must emerge from saturation geometry with correct slope (≈4) AND normalization, **without** a fitted a₀.

---

## 2A. SCOPE EXPANSION (Harvey 2026-07-13) — the winding constraint makes this a TWO-COMPONENT problem

> **The datum that breaks the one-component model.** Fitting v(r) is *too narrow a model*. A flat (or
> quasi-flat) curve means Ω(r) = v/r ∝ 1/r — strong differential rotation. Run it forward or backward and a
> **material** spiral arm shears by ΔTurns = [Ω(r_in) − Ω(r_out)]·T/2π. **Measured on the real SPARC sample
> (`gd05_sdt_streak.cpp`, winding block): median ΔTurns = 62 over 10 Gyr** (inner disk makes ~78 absolute
> windings; outer log-slope β = dln v/dln r = 0.29). **A material arm winds up ~62× → it cannot be material.**
> This holds for the observed curve, the SDT streak curve, a dark-matter halo, and MOND alike — *any* law that
> fits the rotation data. **So the winding problem is not about what flattens the curve. It says the spiral arms
> are a STANDING PATTERN, not co-moving matter.** ("Flat rotation of independent orbiters" is self-refuting.)

**The expanded model: ONE occlusion medium, TWO outputs.** The spation substrate is a reconfigurable lightspeed
**superfluid** (2026-06-25 upgrade; particles = quantised vortices, Onsager–Feynman). A rotating superfluid disk
naturally supports **both** a mean flow **and** persistent standing patterns. Galactic dynamics is those two:

- **Component 1 — the mean occlusion field → the rotation curve.** The disk's 360° streak occlusion sets the
  quasi-flat v(r) (§2). *Refinement from the data:* observed β = 0.29, so real curves *rise slightly*; the pure
  streak (β→0) is **too flat** — part of the 35% residual. The target profile is quasi-flat, not flat.
- **Component 2 — a standing occlusion/density wave → the spiral arms.** The arms are a **compression pattern in
  the superfluid**, rotating rigidly at a **single pattern speed Ω_p**, *decoupled from the material orbital
  Ω(r)*. Because the pattern turns as one body, it **does not wind** — spiral persistence is automatic. The arm
  is where the medium is compressed → **enhanced occlusion** → it *looks like extra mass along the arm that is
  not there* (the SDT reading of the "density wave"; no material over-density is required, only an occlusion one).

**Why this is the SDT-native resolution (not borrowed density-wave theory).** Lin–Shu density waves are *posited*
patterns needing a self-gravity feedback loop. SDT's medium is a superfluid, which *hosts* rotating standing
patterns as a matter of substrate physics (like patterns in rotating superfluid He / persistent vortex arrays).
The **same medium** that occludes to flatten the curve carries the standing wave that makes the arms. One
substrate, two phenomena — dark matter *and* the winding dilemma dissolved together, mass-free.

**New observables the expanded model must engage (co-primary with RMS):**
- **Pattern speed Ω_p and the corotation radius R_co** (where Ω(r) = Ω_p): arms live between the inner and outer
  Lindblad-type resonances of the medium; predict R_co from the occlusion-wave dispersion, not fit it.
- **Pitch angle i** vs the local shear (β): tighter arms where shear is higher; the model predicts i(R) from Ω_p
  and the curve, testable against measured pitch angles.
- **Arm number m** (2-armed vs multi): the allowed standing-wave modes of the superfluid disk.
- **The occlusion-excess along arms**: arms should show extra *occlusion* (lensing/redshift depth) without extra
  baryons — a falsifiable SDT-vs-ΛCDM fork (ΛCDM needs a real stellar+gas over-density; SDT predicts an
  occlusion-only enhancement).

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| eclipse saturation model | GD01 (galactic.hpp **does not exist**) | UPSTREAM — propose-only header | ⚠ dep |
| **M4 convergence-floor twin-regime** | `gd05_twin_regime.cpp` | RESULTS on file (23.8%) | ✔ |
| **MOND-simple crossover** | borrowed in twin-regime | **CONTRABAND — derive or purge** | ✖ flag |
| **GOM14 mass-free koppa-density** | Investigations/06 | Route C (no-GM, 5.9% vs 50.7%) | ✔ use |
| APS03 drafting crossover | Investigations | 21.5% RMS; a₀-required inference dead | ✔ ref |
| SPARC real data | `sparc_real_data.csv` | measured anchor (v_obs, Σ) | ✔ |
| g = v²/R, ϟ = v²R/c² | `laws.hpp` bridge | mass-free gravity | ✔ |
| v_flat² = GM·f | prior §2 | **KILLED (GM contraband)** | ✖ dead |

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | ≥50 real SPARC, RMS < 25%, mass-free | root-1 (mechanism) or root-2 (crossover) |
| T2 | crossover DERIVED, not MOND-borrowed | root-4 (a₀ contraband) — the key gate |
| T3 | BTFR slope≈4 + normalization from geometry, no fit | root-1 |
| T4 | koppa-density beats shuffled control (GOM14) | root-1 if signal vanishes on full set |
| T5 | no GM anywhere in the chain | root-4 (BORROW-SMUGGLE) |

## ⑨.E Four-root sort
root-1 claim false (eclipse/floor mechanism wrong) · root-2 dependency (GD01 header, GOM14) · root-3 prompt (crossover under-specified) · root-4 contraband (MOND a₀, GM). The MOND-borrow is root-4 — **derive the crossover natively or label DEGENERATE**; do not keep the borrowed a₀ and claim zero-param.

## Brainstorm — overlooked/newly-discovered factors
- **The honest state is mixed, not a win.** Naive eclipse fails (66%); the 23.8% floor law borrows MOND. Say so. The real open is *deriving the crossover* — that is where the a₀-scale must come from natively (convergence-floor depth), or the dark-matter replacement is incomplete.
- **Mass-free is the way through** (GOM14). GM smuggles the very mass SDT denies. The koppa-density (v²R/c² per baryon column) is the native observable — push Route C to the full sample.
- **a₀-required inference is dead at old strength** (APS03 retraction): the floor needs *wide binaries*, not just galaxies, to decide. Note the wider decidable.
- **Circular-mock trap** (the prior 8.8%→retracted): never validate against a mock built from the model. Real SPARC only.

## ⑤ Success / ⑥ Outputs
Class A: ≥50 real SPARC RMS<25%, crossover derived, BTFR from geometry, no GM. Class C/DEGENERATE (likely current): floor law works but crossover borrowed — honest. Outputs: `RUN_LOG.md`, `gd05_sparc_rotation_curves.cpp`, `gd05_twin_regime.cpp`, `GD05_DERIVATION.md`, `GD05_VERDICT.md`, CANON_FLAGS row (GM/MOND).

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — GD05 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (a₀/crossover is the thing to DERIVE, not fit)
- Routes: A eclipse(control ~66%) · B M4 floor(purge MOND crossover) · C koppa-density(GOM14)
- Data: real SPARC only (sparc_real_data.csv) — NO mock
- Forbidden: GM/M anywhere; MOND a₀ as an input; validating on a self-mock; claiming zero-param with a borrowed crossover
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| crossover needs MOND a₀ | derive floor depth natively (root-4) | DEGENERATE, honest | keep a₀, claim zero-param |
| v_flat wants GM | recast as koppa-density | STOP — contraband | use GM |
| RMS > 25% mass-free | try koppa-density route C | OPEN the mechanism | fit a halo |
| result from a mock | rerun on real SPARC | void the run | report mock as data |

**Disallowed:** GM/M · MOND a₀ import · self-mock validation · post-hoc tolerance widening · zero-param claim with borrowed crossover.

---

*GD05 · §K-deepened 2026-07-13 · GM contraband purged; naive eclipse fails (66%), M4 floor 23.8% borrows MOND (derive the crossover or label DEGENERATE); mass-free koppa-density (GOM14) is the honest route; real SPARC only.*
