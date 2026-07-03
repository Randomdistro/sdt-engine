# RUN_LOG — NP15: Nuclear Magnetic Moments from Vortex Geometry

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only. μ_N is a **borrowed unit** (flagged; used as the
> OBSERVED comparison yardstick only, per repo rule).

## Pre-Run Commitments — NP15

- Prompt completion target: B
- Physics class hoped: NATIVE; honest floor accepted: OPEN / DEGENERATE
- CALIBRATED budget: **0**
- Engine namespaces: `measured` (μ anchors, lines 194–199), `law_VI::winding` (g_proton),
  `law_VI::topology` (v_T, v_P of the (2,3) trefoil), nuclear grammar (block rules)
- **Blind threshold re-commit (per PROMPT §⑩ NOTE):** the deuteron gate is **5%**, chosen
  blind as the same bar as every other composite — explicitly NOT the known 2.6% discrepancy.

## Committed μ_p candidate formulas (geometric rationale BEFORE any number)

All in μ_N via the engine identity `g_proton = R_p m_p c/ℏ` (≈ (W+1)); trefoil mode speeds
`v_T = c√(2/5)`, `v_P = c√(3/5)` from `topology::` (PPT01, class A).

| ID | Formula (μ/μ_N) | Prior rationale |
|----|------------------|-----------------|
| C1 | `g_proton` = m_p c R_p/ℏ | charge rides the outer rim at c (naive rim current loop, radius R_p) |
| C2 | `g_proton × v_T/c` | only the toroidal circulation bounds a net loop area (poloidal loop moments cancel around the torus); loop at boundary radius R_p |
| C3 | `g_proton × v_P/c` | poloidal-dominant variant (3 poloidal turns per circuit for W=3) |
| C4 | `g_proton × (v_T/c) × R_major/R_p`, R_major = R_p·√(3/2)/(1+√(3/2)) | as C2 but the loop at the mode-locked major radius (aspect R/a = √(q/p), boundary = R+a) |
| C5 | `g_proton × √(v_T v_P)/c` | **FLAGGED-POST-HOC**: noticed numerically during design; "effective helical speed = geometric mean of mode speeds" has NO derivation. Recorded for the look-elsewhere ledger; **cannot produce a PASS** regardless of proximity — best outcome [OPEN] numerology-risk. |

**Decision rule:** a candidate PASSES only if within **5%** of +2.7928 AND its rationale
column was written here first. C5 is excluded from PASS by construction. If none of C1–C4
passes → μ_p is **OPEN** (report the bracket honestly). **No post-hoc mixing, averaging,
or new exponents after seeing the numbers.**

## μ_neutron

The PROMPT's charge-separated-uncharged-trefoil route is **premise-dead** (NP17: neutron =
proton + internal electron). NP20 already executed the NP17-native route: magnitude =
IDENTITY, sign assumed via sense=−1 → OPEN. **Commitment: NP15 does NOT re-fish μ_n.** It
inherits NP20's OPEN and prints the required gearing as the named debt. Any new μ_n number
here without a new mechanism would be re-fishing.

## Committed composite block rules (grammar-native pairing; gate 5% each, blind)

| Nucleus | Grammar blocks | Committed rule | Anchor (μ_N) |
|---|---|---|---|
| d | 1 deuteron (p+n aligned, S=1) | μ_d = μ_p + μ_n | +0.857421 (engine) |
| t | triton block: p + (n,n) antipaired | μ_t = μ_p | +2.979 (engine) |
| h (He-3) | (p,p) antipaired + n | μ_h = μ_n | −2.128 (engine) |
| α | (p,p)+(n,n) both antipaired, tetrahedral | μ_α = 0 | 0.0 (engine) |
| Li-7 | α + t (α silent) | μ = μ_t(pred) = μ_p | +3.256427 (Stone 2019, OBSERVED, typed literature anchor — flagged) |
| Be-9 | 2α + n (α silent) | μ = μ_n | −1.1778 (Stone 2019, OBSERVED, typed literature anchor — flagged) |

**Degeneracy declaration (before running):** these additive rules coincide with the standard
impulse-approximation/Schmidt limits. Wherever the number matches, the class ceiling is
**DEGENERATE** (no SDT-discriminating content) unless the trefoil geometry adds something
the rival lacks. This is declared now so a match cannot be inflated into NATIVE later.

## μ_n/μ_p ratio
Measured −0.68497. −2/3 admissible ONLY with a prior geometric derivation; none exists in
SDT (SU(6) is the rival's machinery, inadmissible). Commitment: report proximity as
unexplained numerology, class OPEN; no pass.

## Forbidden retroactive changes
Widen 5%; mix C1–C4 after the fact; promote C5; new μ_n magnitude without mechanism;
claim NATIVE where the rival predicts the same number.

## Planned outputs
`np15_magnetic_moments.cpp` → MSVC → `np15_results.txt` (redirected) → `NP15_VERDICT.md`.
