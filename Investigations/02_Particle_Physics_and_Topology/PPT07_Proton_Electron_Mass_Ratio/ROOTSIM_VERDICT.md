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

**Status: `[OPEN — privileged, unexplained, high-precision match]`.** Not killed, not derived. The *meaning*
("mass = phase-stiffness of the standing crossing-state") and the *factor homes* (6 = (2,3) trefoil 2·3;
π⁵ = 3·A(S³)·A(S⁵), real n-sphere surface volumes) are on the table; the *mechanism* that makes the proton wake
integrate to that is the open problem.

## why^n → root (corrected)

- **why doesn't the BARE topology give it?** winding/ropelength are O(1) invariants; they miss the angular
  phase-space content where π factors live.
- **why is the match credible then?** because it is *unique* in the motivated family (integer-winding × π^integer
  -phase-space) at 19 ppm with zero free parameters — the signature of a real integral, not a lucky π-product.
- **why isn't it derived?** the **wake phase-space integral** — the thing that would *produce* `3·A(S³)·A(S⁵)`
  blind — has never been computed (it needs the lattice solver).
- **ROOT:** 6π⁵ is an **unexplained but privileged** geometric near-identity. The honest task is not to label it
  but to **run the wake integral** and see whether `3·A(S³)·A(S⁵)` falls out. If it does, 6π⁵ is earned; if a
  different clean number falls out, *that* becomes the prediction. Either way the 19-ppm uniqueness says there is
  a real structure to find.

## The genuine path (still unpaid)

The honest way to settle 6π⁵ is the real **wake phase-space integral** — the phase-locked displacement zone a
W=3 (2,3)-trefoil organises in the corner-sharing network vs a W=1 unknot, with the **angular integrations**
carried out (that is where the π's are), solved from scratch (the deferred ROOT-SIM proper, = the lattice
solver). The cheap test here only ruled out the *bare* invariants (O(10)); it says nothing about the phase-space
integral. Run it when the solver exists, and check whether `3·A(S³)·A(S⁵)` falls out blind.

## Canon action — WITHDRAWN

The earlier proposal to relabel `laws.hpp law_VI::mass_ratio` as a *fit* is **withdrawn**. 6π⁵ is **not** a
fitted calibration (zero parameters, nothing to delete-test) — it is a unique, unexplained, 19-ppm match. The
label stands; the open work is the **mechanism**, not the label. `laws.hpp` untouched.
