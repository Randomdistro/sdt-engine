# PPT03: Proton-Electron Mass Ratio — Mathematical Framework

> **Author:** J. C. Harvey, Melbourne. **Status:** OPEN (blocked) · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K · §0 anti-creep.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on any canon flag.
> **Run:** Pre-commit in `RUN_LOG.md`; sort every failure into the four roots (§⑨.E) before the next phase.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Why m_p/m_e = 1836.15267, and whether it is 6π⁵ (19 ppm) for a *mechanistic* reason.** The ratio equals the **displaced-volume ratio** V_disp,p / V_disp,e (Law IV), which is unsolved because V_disp for a knot ≠ its torus volume — the *wake* dominates.
2. **Why does it matter?** — m_p is one of 8 whitelist inputs. Deriving the ratio removes it (8→7) and, with PPT02's α, closes the atomic dimensionless sector. Sibling to PPT02 (charge gear ↔ mass gear).
3. **How will we find out?** — Three routes (§④): A solve V_disp(p,q) via the 3D lattice solver (FLM10); B give 6π⁵ a native mechanism (6 and π⁵ from trefoil geometry); C mass-as-dwell-cost (FLM14 rotation). Native before any rival.
4. **What would prove us wrong?** — §⑧. If V_disp cannot be computed without a fitted wake scale, or 6π⁵ fails the look-elsewhere correction, the ratio stays an input — honestly OPEN, not fished.
5. **How will we know we're done?** — Dual verdict (A–F × NATIVE/…/OPEN). "Derived" only if V_disp,p/V_disp,e = 1836.15 falls out of topology with **no fitted length** (delete-test).

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| m_p/m_e | mass ratio | 1836.15267 | dimensionless; the target |
| V_disp | displaced volume | m³ | lattice displaced by the vortex → mass via Law IV. **≠ V_torus** (§3) |
| Φ | convergence burden | 1.039×10⁻⁵⁶ J | relay content per spation from all N shells (Law I) |
| W, (p,q) | winding / knot | int | electron = (1,1) W=1; proton = (2,3) W=3 trefoil |
| R, a | torus radii | m | major/minor; R/a = √(q/p) (PPT01) |

---

## 2. The Question (mass = reorganisation cost; ratio = cost ratio)

Law IV: `m = Φ · V_disp / (3 ℓ_P³ c²)` ⟹ `m_p/m_e = V_disp,p / V_disp,e`.
**Movement reading:** mass is the field's resistance to a change of vector — the *reorganisation cost* of the knot. The ratio is a **ratio of costs**, not of stuff. Deriving it ≡ deriving why the (2,3) trefoil costs 1836× the (1,1) loop to move.

## 3. Why V_disp ≠ V_torus (the wake dominates — earned, keep)

`V_torus = 2π²Ra²`; with R/a = √(q/p): V_e = 2π²a_e³, V_p = 2π²√(3/2)a_p³.
From PPT01 a_e/a_p ≈ 2011 ⟹ V_p/V_e = √(3/2)·(1/2011)³ ≈ 1.5×10⁻¹⁰ — proton torus **smaller**, yet m_p ≫ m_e. **Therefore V_disp is dominated by the wake perturbation beyond the torus surface, not the torus.** This is the crux and the hard part.

## 4. The 6π⁵ target — arithmetic corrected

> ### ⚠ NUMERIC-HYGIENE FLAG (in-prompt, self-contained)
> The prior draft's §4 was internally contradictory ("6 × 305.019 = 1830.12", "π⁵ = 3.14159²·³").
> **Corrected exact figures:** π⁵ = 306.0197, **6π⁵ = 1836.1181**, m_p/m_e = 1836.15267 →
> **Δ = 0.0019% (19 ppm).** This is the unique zero-parameter match on record (memory: survives the
> look-elsewhere test; bare α-style fits do not). It is **[OPEN], mechanism untested** — not numerology,
> not a result, until 6 and π⁵ are given a trefoil-native origin.

**Candidate decompositions to test (declare before run, don't fish):** 6 = 2×3 (poloidal×toroidal of the (2,3) knot? crossing count?); π⁵ = five π-factors (one per compactified phase loop? d=3 space + 2 circulation angles?). A decomposition is only admissible if each factor maps to a *counted* geometric feature — otherwise it is a PLUG.

## 5. Blocked dependency — re-open condition named (§G.3)

V_disp(W,p,q) requires the full 3D lattice perturbation around each knot — a coupled self-consistency (V_disp→m→λ_C→radii→V_disp). **Prior status "formulates but does not solve" is not an impossibility; the re-open condition is FLM10 (the per-spation lattice solver), itself un-enacted.** When FLM10 delivers a perturbation field, Route A becomes runnable.

---

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| m_p | `laws.hpp measured::` | **INPUT** (the target to remove) | ✔ |
| Law IV `m = Φ V_disp/(3ℓ_P³c²)` | `laws.hpp` law_IV | mechanism | ✔ |
| PPT01 torus radii R/a=√(q/p), a_e/a_p | Investigations/02 | UPSTREAM — verify on file | ⚠ |
| **FLM10 3D lattice solver** | Investigations/01 | **UPSTREAM (Route A)** — un-enacted | ⚠ dep |
| **FLM14 rotation / mass-as-dwell** | Investigations/01 | UPSTREAM (Route C) — un-verdicted | ⚠ dep |
| PPT02 α (gear sibling) | Investigations/02 | cross-check, not input | informative |
| r_e as "electron wake" | `laws.hpp:144`, and §3 line "wake radius r_e for electron" | **MISLABEL** — see CANON_FLAGS #1/#2 | ⚠ flag |

**Dependency risk:** Routes A and C both stand on un-enacted upstream (FLM10, FLM14). If unavailable → **DEFER** with the ID; never fake-PASS a borrowed V_disp.

---

## ④ Strategy — three declared routes

**Route A — V_disp from the 3D wake (via FLM10).** Solve the lattice perturbation for (1,1) and (2,3); integrate V_disp beyond each torus; ratio must → 1836.15 with no fitted wake scale. *Metric:* ratio within 1% (Class C) / 0.1% (Class A). *Expected:* DEFER until FLM10 lands.
**Route B — 6π⁵ mechanism.** Derive 6 and π⁵ as counted trefoil features (crossings, phase loops); *metric:* both factors mapped to geometry, product = 1836.12 with zero free integers. *Kill:* any factor that is tuned, not counted → PLUG → KILL Route B.
**Route C — mass-as-dwell-cost (FLM14).** If mass = reorganisation cost = time the knot dwells re-forming per tour, the ratio is a dwell ratio. *Metric:* dwell(2,3)/dwell(1,1) = 1836 from tour geometry. Cross-gate: must not break PPT02's α gear.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | V_disp ratio (Route A) = 1836 ± 1% with no fitted length | root-2 (FLM10) or root-1 |
| T2 | 6π⁵ factors each map to a counted feature | root-1 (numerology) if not |
| T3 | look-elsewhere: no *other* simple πᵃ·bᶜ within 19 ppm of 1836.15 | root-1 if the match is not unique |
| T4 | Route C dwell ratio preserves PPT02 α | root-4 (contraband) if it needs QM mass |

## ⑨.E Four-root sort (run on every failure)
root-1 claim false (KILL route) · root-2 dependency (FLM10/FLM14/PPT01 — ROOT-RELOCATE) · root-3 prompt under-specified (recurse §K) · root-4 gate contraband (kill the gate). Log in RUN_LOG; shared roots once in INVESTIGATION_STACK.

## Brainstorm — overlooked factors
- **Two gears, one lattice.** α (charge gear, PPT02) and 6π⁵ (mass gear) may be two projections of one reconnection count — joint delete-test, not an input swap.
- **π⁵ and d=3.** Five π's in a 3-space + 2-angle knot is suggestive; count the loops explicitly before believing it.
- **The 2011 factor** (a_e/a_p) is itself α-and-mass-laden — check Route B doesn't smuggle m_p back through PPT01's radii (circularity, mirror of PPT02's gate).
- **Wake, not torus** is the whole game — do not let any route quietly use V_torus.

## ⑤ Success / ⑥ Outputs
Class A: ratio from topology, no fitted length, m_p removed. Class C: ≤1 documented approximation. **Class D/OPEN (honest floor):** V_disp mechanism mapped, 6π⁵ mechanism attempted, ratio still input but routes advanced. Outputs: `RUN_LOG.md`, `ppt03_massratio_routes.cpp`, `PPT03_DERIVATION.md`, `PPT03_VERDICT.md`.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — PPT03 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 (m_p is the thing removed, not a knob)
- Routes this session: [A|B|C]; non-fitted seed per route named
- Upstream verify-on-file: FLM10 perturbation, FLM14 dwell, PPT01 radii
- Phase thresholds: A 1%/0.1%; B factors-counted; C dwell 1%
- Forbidden: V_torus as V_disp; fished π-decompositions; widen tolerance post-run; import QM mass
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| FLM10 solver unavailable | DEFER Route A, cite FLM10 | ship OPEN, routes mapped | fabricate V_disp |
| 6π⁵ factor tuned not counted | try next counted decomposition | KILL Route B (root-1) | PLUG the factor |
| ratio off > committed % | four-root sort (§⑨.E) | OPEN, name root | RETRO-PASS |
| Route uses V_torus | switch to wake integral | OPEN wake mechanism | call V_torus the answer |

**Disallowed:** post-hoc tolerance widening · coefficient plugs · V_torus-as-V_disp · `atomic::`/GM in native chain · QM mass import.

---

*PPT03 · §K-deepened 2026-07-13 · hardest open problem in SDT (topology→mass); three routes declared; 6π⁵ arithmetic corrected; r_e mislabel flagged to CANON_FLAGS.*
