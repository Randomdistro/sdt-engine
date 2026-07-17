# GD01: Eclipse Saturation Model — Derivation & Implementation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on any new engine header. **NO G, NO M.**
> **Run:** Pre-commit per phase in `RUN_LOG.md`; four-root sort (§⑨.E) on every FAIL.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **The eclipse-saturation model is referenced (`galactic.hpp`) but never implemented, and the version that WAS tried fails real SPARC (~66%, GD05).** The gap: a *mass-free* occlusion→rotation law with a **natively derived saturation crossover** (not MOND's a₀).
2. **Why does it matter?** — GD05 (the SPARC test) is blocked on this model. Its zero-param dark-matter-replacement claim stands or falls here.
3. **How will we find out?** — Derive Ω_disk(r), the saturation criterion, and v(r) in **mass-free** `c²/k²·(occlusion)` terms (this prompt already uses the right form — keep it, it is *better* than GD05's GM line), then implement (standalone or a proposed header).
4. **What would prove us wrong?** — §⑧: if v(r) needs GM/M; if the crossover needs an imported a₀; if Ω_disk saturation can't produce flat curves without a fitted screen density.
5. **How will we know we're done?** — Model derived mass-free, crossover named natively, implemented and handed to GD05 for the SPARC run.

> ### ⚠ CONSISTENCY NOTE (this prompt is the cleaner one)
> GD01's rotation law is already **mass-free**: `v(r)² = (c²/k²)·Ω_disk(r)/(4π)·R_gal/r` — occlusion solid
> angle × koppa hierarchy, **no GM**. GD05's prior `v_flat² = GM·f` was contraband (flagged there). **GD01's
> form is canonical; GD05 must adopt it.** The remaining risk is `Σ_crit` (the convergence-opacity density)
> and the saturation crossover — those must be derived, not fitted (Route B).

## THE GAP
`galactic.hpp` does **not** exist in the Engine (only laws/cosmology/neutrino/magnetosphere/state28d). The eclipse model is referenced but uncomputed. **Adding `galactic.hpp` is propose-only (needs Harvey);** GD05 already carries standalone `.cpp` tools — the model can live there first and be proposed for the header once earned.

## What to derive (mass-free)
1. **Ω_disk(r):** solid angle occluded by an extended disk for an observer at radius r in-plane — `Ω_disk(r) = ∫ f(Σ(r'), h, z₀, r) dA`.
2. **Saturation criterion:** radius where Ω_disk → 2π; `r_sat` from disk scale length h, scale height z₀, and `Σ_crit` (the convergence-opaque density — **derive `Σ_crit`, do not fit it**).
3. **Rotation velocity:** `v(r)² = (c²/k²)·Ω_disk(r)/(4π)·R_gal/r`. Below saturation → v ∝ √(occluded column / r) (rising); at saturation → v_flat = const.
4. **BTFR normalization:** `v_flat² = (c²/k²)·(1/2)·R_gal/r_sat`; v_flat must depend only on the baryonic *column geometry* (not GM) → slope-4 BTFR.

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| `galactic.hpp` | Engine — **does not exist** | propose-only header | ⚠ |
| GD05 standalone tools + SPARC data | Investigations/08 | the consumer/test | ✔ |
| naive-eclipse ~66% fail | GD05 results | control result to respect | ✔ |
| GOM14 mass-free koppa-density | Investigations/06 | the no-GM anchor | ✔ |
| FLM10 isotropy of the medium | Investigations/01 | why 4π convergence is isotropic | ✔ |
| Σ_crit, saturation crossover | this model | **must be derived (Route B)** | ⚠ |
| k-hierarchy, ϟ = v²R/c² | `laws.hpp` bridge | mass-free gravity | ✔ |

## ④ Strategy
**A — Solid-angle occlusion.** Compute Ω_disk(r) from Σ(r'), h, z₀ by direct integration; verify Ω→2π at large r. *Metric:* Ω monotone, saturating.
**B — Derive Σ_crit and the crossover (the hard part).** The convergence-opaque density and the rise→flat crossover must come from occlusion physics (convergence-floor depth), **not** MOND a₀. *Metric:* Σ_crit expressed in `{c, k, ℓ_P}` terms, no fit. *Expected:* this is the open — if it can't be derived, GD05 stays DEGENERATE.
**C — Implement + hand to GD05.** Standalone first; propose `galactic.hpp` if earned.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | Ω_disk(r) → 2π (saturates) mass-free | root-1 |
| T2 | Σ_crit derived from {c,k,ℓ_P}, not fitted | root-3/root-4 (a₀ contraband) — the gate |
| T3 | v(r)² uses c²/k², never GM | root-4 (BORROW-SMUGGLE) |
| T4 | crossover native, feeds GD05 to RMS<25% | root-2 (feeds GD05) |

## ⑨.E Four-root sort
root-1 claim false (saturation geometry) · root-2 dependency (galactic.hpp, GD05, GOM14) · root-3 prompt (Σ_crit under-specified) · root-4 contraband (a₀/GM). Σ_crit is a **named OPEN closure** if it won't derive — do not fit it and call it done.

## Brainstorm — overlooked factors
- **GD01 is cleaner than GD05** — its c²/k² form is the canonical one; the deepening's job is to make GD05 adopt it and to *derive Σ_crit*.
- **Σ_crit is the whole ballgame** — it is where a₀ would sneak in. Derive it from convergence-floor depth (the twin-regime floor) or concede DEGENERATE.
- **Propose-only header** — resist the urge to write `galactic.hpp`; keep it in GD05's standalone tools until Harvey rules.
- **Isotropy dependency (FLM10)** — the 4π convergence being isotropic is a FLM10 output; the eclipse model assumes it.

## ⑤ Success / ⑥ Outputs
Class A: model derived mass-free, Σ_crit + crossover native, implemented, GD05 fed. Class C/OPEN: Ω_disk + v(r) clean, Σ_crit fitted (flagged). Outputs: `RUN_LOG.md`, `gd01_eclipse_saturation.cpp`, `GD01_DERIVATION.md`, `GD01_VERDICT.md`, proposed `galactic.hpp` block (for Harvey).

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — GD01 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 (Σ_crit derived, not fitted)
- Phases: A Ω_disk · B derive Σ_crit/crossover · C implement→GD05
- Forbidden: GM/M; MOND a₀ as Σ_crit; writing galactic.hpp to the Engine without Harvey
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| Σ_crit won't derive | flag OPEN, ship Ω_disk + v(r) | GD05 DEGENERATE honest | fit Σ_crit to SPARC |
| tempted to write galactic.hpp | keep in GD05 tools; propose block | — | edit Engine without OK |
| v(r) wants GM | recast c²/k² occlusion | STOP contraband | use GM |

**Disallowed:** GM/M · MOND a₀ · fitting Σ_crit · writing `galactic.hpp` to the Engine · post-hoc tolerance widening.

---

*GD01 · §K-deepened 2026-07-13 · the mass-free c²/k² occlusion form is canonical (GD05 must adopt it); Σ_crit + the saturation crossover must be DERIVED not fitted; galactic.hpp is propose-only.*
