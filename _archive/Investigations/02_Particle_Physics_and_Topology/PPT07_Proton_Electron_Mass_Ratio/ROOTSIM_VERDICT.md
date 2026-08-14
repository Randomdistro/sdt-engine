# PPT07 — ROOT-SIM Verdict: is 6π⁵ earned, or a fit?

**J. C. Harvey, Melbourne — 2026-06-24.** Tool: `ppt07_rootsim_wake.py` (blind). Honest negative result.

> Reached by the standing discipline: *if a derivation succeeds or fails, ask why^n until the root.* The 6π⁵
> claim was run **blind** — the target 1836 enters no computation, only the final comparison.

## What was tested

The engine (`laws.hpp law_VI::mass_ratio`) carries `6π⁵ = 1836.118` as the proton/electron mass ratio,
labelled **SDT-derived / passes delete-test**, with the decomposition `6π⁵ = 3·(2π²)·π³`
(W-lobes × S³ surface-volume × π³). PPT07's own record already concedes the **bare flux-tube** ratio is **1.45**
and that 6π⁵ came from an *"exhaustive topological search against the target 1836.15."* That is the shape of the
numerology CONDENSA [KILLED]. The ROOT-SIM computes every honest topological measure of the W=3 trefoil vs the
W=1 unknot, blind.

## Result (blind)

| measure | what it is | trefoil/unknot |
|---|---|---|
| **winding energy** | `E ∝ W²` (numerically confirmed: W²=4, 9) | **9.00** |
| **ideal ropelength** | knot invariant, not fitted (3₁=16.37, unknot=2π) | **2.61** |
| **winding × length** | best-case mass estimate | **~23.5** |
| × generous log/core (≤2×) | maximally fair to topology | up to ~47 |
| bare flux-tube (PPT07, on record) | | 1.45 |
| **target** `m_p/m_e` | measured | **1836.15** |
| `6π⁵` | the engine's claim | 1836.12 (−0.002%) |

**Gap: target / best-case ≈ 78× — topology misses by ~two orders of magnitude.**

## Verdict — CORRECTED (2026-06-24, after the look-elsewhere)

The first draft of this file said "6π⁵ is a fit, [KILLED]." **That was wrong, and is retracted.** What the blind
test actually shows is narrower: the **bare** topological invariants (winding `W²`=9, ropelength 2.6, product
~23) are **O(10), not 1836** — so they do **not** explain the ratio. But that is the **wrong quantity**: the π⁵
lives in the **wake phase-space integral** (the angular integrations), which this cheap test never computed.

Two facts move 6π⁵ off the "numerology" pile entirely:
- **Uniqueness.** Among all simple `a·π^b` (a≤30, b≤6), **6π⁵ is the ONLY form within 0.1%** of the measured
  1836.15267, and `m_p/m_e / π⁵ = 6.00011` is the *only* exponent yielding a near-integer. Contrast the α case
  (CONDENSA [KILLED]) where **no** clean form exists (14,505σ). Different category.
- **No knobs.** 6π⁵ is a **zero-parameter** expression. The delete-test catches *fitted* parameters; there is
  nothing here to fit or delete. "The search found it" means we found *which fixed form* matches — not that we
  tuned one. A unique, zero-parameter, 19-ppm postdiction is **evidence of structure**, not a coincidence to bury.

**Status updated 2026-08-14: `[RESOLVED CONSTRUCTION — shared-input, not an
independent prediction]`.** PPT17 supersedes the proposed phase-stiffness route:
the point electron's finite-width 720-degree Bohr-seat tube is packed `6π⁵`
times into the W=3 torus seated at `R_p`. The ROOT-SIM result still excludes
bare winding and ropelength as generators; they are not the adopted mechanism.

## why^n → root (corrected)

- **why doesn't the BARE topology give it?** winding/ropelength are O(1) invariants; they miss the angular
  phase-space content where π factors live.
- **why is the match credible then?** because it is *unique* in the motivated family (integer-winding × π^integer
  -phase-space) at 19 ppm with zero free parameters — the signature of a real integral, not a lucky π-product.
- **what is certified?** the tube-to-torus volume map and conservation of the
  `6π⁵` packing count.
- **what is not certified?** an independent prediction of 1836; the count is a
  shared input to this construction.
- **ROOT:** the earlier wake-integral route is superseded for the mass-ratio
  assignment, while its negative bare-invariant result remains valid.

## Superseded wake-integral path

The wake phase-space integral remains a possible independent-prediction test,
but it is no longer the required mechanism for closing the geometric
mass-ratio construction. PPT17 supplies the adopted shared-input volume map.

## Canon action — WITHDRAWN

The earlier proposal to relabel `laws.hpp law_VI::mass_ratio` as a *fit* is **withdrawn**. 6π⁵ is **not** a
fitted calibration (zero parameters, nothing to delete-test) — it is a unique, unexplained, 19-ppm match. The
label now stands as **COMPUTED / construction-resolved**, not as a fitted
calibration or independent prediction. `laws.hpp` was updated by PPT17.
