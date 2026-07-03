# RUN_LOG — GOM10 Three-Body Lagrange Points from Koppa

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.

## Pre-Run Commitments — GOM10 (written BEFORE first compile/run)

- Prompt completion target: B
- Physics class hoped: **IDENTITY + CONVERGENCE, honestly labelled.** The PROMPT itself
  concedes (§Step 2) that μ_ϟ = ϟ₂/(ϟ₁+ϟ₂) is numerically M₂/(M₁+M₂). Every collinear-point
  position that follows is therefore the classical CR3BP result re-derived in koppa
  notation. The verdict will label the μ-substitution IDENTITY, and the L-point geometry
  CONVERGENCE. The only potentially non-identical content is (a) whether the koppa
  inventory built from (v_surf, R) reproduces the observed L1/L2 distances (an OBSERVED
  anchor: SOHO/JWST at ~1.5e6 km) and (b) the L4/L5 Routh stability criterion
  27μ(1−μ) < 1 (μ < 0.03852) checked against the OBSERVED existence of Jupiter Trojans.
- CALIBRATED budget: 0
- Note on engine policy: the tool defines a LOCAL `constexpr double c` and local Body
  structs instead of `#include <sdt/laws.hpp>` — this violates the PROMPT's "no local
  constant namespaces" header rule. Logged as a defect, tool still compiled AS-IS first
  (the guardrail for this folder). The numeric values used (c, v_surf, R) match
  laws.hpp/measured to the digits printed.
- Phase thresholds (committed before run, from PROMPT §6):
  - Sun–Earth L1 distance within **1%** of Hill-sphere/known ~1.5e6 km
  - L4/L5 at exactly 60° and equidistant (|r/a − 1| < 1e-6, geometric necessity)
  - Stability criterion μ < 0.0385 reproduced; Sun–Jupiter μ (~9.5e-4) must come out
    STABLE, consistent with observed Trojans (OBSERVED anchor)
  - μ_ϟ(Sun–Earth) within 0.1% of mass ratio M_E/(M_S+M_E) = 3.003e-6 (falsification
    condition #1 in the PROMPT — this is the bridge-identity check)
- Pre-declared audit flags:
  1. Any "SDT vs known" L1/L2 agreement is a CONVERGENCE with Newtonian CR3BP, since the
     solver `f_rot` IS the classical rotating-frame equation with μ swapped in. It must
     not be sold as an SDT prediction beating GR.
  2. F₁₂ = c²ϟ₁ϟ₂/D² printed as "N" is dimensionally NOT newtons (c²ϟϟ/D² has units of
     m·s⁻²·(m)·... = check: [c²][m][m]/[m²] = m²/s² — an acceleration times length, not a
     force). Pre-flagged as a dimensional error to be called out if printed.
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS as physics.

## Build log

- 2026-07-03: compiled AS-IS, zero source edits. MSVC 19.44.35223 x64. Exit 0.

## Run log

- 2026-07-03: `gom10_lagrange.exe` → exit 0, full stdout in `results.txt`.
- Gates:
  - Sun–Earth L1 = 1,490,933 km vs known ~1.5e6 km: **−0.60%** → PASS (<1%). Against the
    precise value 1.4915e6 km it is ~0.03%.
  - Sun–Earth L2 = 1,500,905 km: +0.06% → PASS. Earth–Moon L1 = 58,026 km vs ≈58,000: +0.04% → PASS.
  - L4/L5: 60.00°, equidistant ratio 1.00000000 → PASS (geometric necessity).
  - Stability: μ(SE)=3.00e-6, μ(EM)=1.216e-2, μ(SJ)=9.318e-4, all < 0.0385 → STABLE;
    consistent with OBSERVED Jupiter Trojans and Earth Trojan 2010 TK7. PASS (OBSERVED anchor).
  - **μ_ϟ vs mass ratio (falsification cond. #1, committed 0.1%): FAIL as stated.**
    μ_ϟ(SE) = 2.99961e-6 vs μ_mass = 3.00327e-6 (CODATA/IAU GM values) → **−0.122%**.
    Root cause traced: ϟ_Sun = 1478.235 m from the rounded input v_surf = 437,000 m/s
    (3–4 s.f.), vs GM_Sun/c² = 1476.63 m. A 3-s.f. velocity input cannot deliver a 0.1%
    ratio. The check is INCONCLUSIVE-at-this-input-precision, not evidence of a bridge
    systematic. Gate recorded as failed; NOT retro-widened.
- Audit flag 2 CONFIRMED: tool prints `F₁₂ = c²ϟ₁ϟ₂/D² = 2.63e-05 N` for Sun–Earth.
  Dimensions of c²ϟϟ/D² are m²/s², not newtons; the true Sun–Earth force is ~3.5e22 N.
  This row is a dimensional error in the tool (its own source comments admit "this isn't
  clean"). Recorded as a defect; does not contaminate the L-point solve, which never
  uses F₁₂.
- Kepler convergence: T(SE) = 365.07 d, T(EM) = 27.29 d from Ω = √(c²(ϟ₁+ϟ₂)/a³) — the
  same GM identity, labelled CONVERGENCE.
