# RUN_LOG — SAR01 Le Sage Thermal Budget

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Executor:** HUNTER protocol.

## Pre-Run Commitments — SAR01 (written BEFORE any code was compiled or run)

- Prompt completion target: **B** (all three ledgers computed; recycling mechanism either shown or honestly OPEN)
- Physics class hoped: NATIVE (evasion shown) — but committed to **KILLED** on any ledger that
  produces heating > 10× geothermal with no conservation line, and **OPEN** if the evasion
  rests on an axiom rather than a derivation.
- CALIBRATED budget: **0** (no fitted parameters; all inputs from `sdt::laws` + measured anchors)
- Engine namespaces: `law_I` (Phi, P_conv, shell cancellation), `law_III` (P_eff, f_transfer,
  F_occlusion), `law_IV` (V_disp), `bridge` (koppa route to Earth mass — no G, no M-in-kg input)
- Measured anchors (declared): geothermal heat flow 47 TW (Davies & Davies 2010, OBSERVED);
  L_Sun = 3.828e26 W (law_II); R_Earth = 6.371e6 m; v_surf_Earth = 7909 m/s (bridge);
  v_surf_Sun = 436762 m/s (bridge/GOM04); 1 AU (measured).
- **Phase thresholds (committed before run):**
  - **Ledger A (classical absorption Le Sage):** the minimum absorbed power to supply the
    Sun→Earth force by momentum absorption is P ≥ F·c. If P_A > 10 × 47 TW, classical
    absorption is **KILLED** as the SDT force carrier. (Expected: killed — this is the
    known Poincaré catastrophe; the point is to put the SDT number on it.)
  - **Ledger B (prompt's own formula, πR_E² · f · P_conv · c):** same 10× geothermal gate.
    If it fails, the conclusion is that f-coupling CANNOT be an absorptive coupling, and the
    prompt's step-1 formula is rejected as a heating term.
  - **Ledger C (SDT relay ledger):** state exactly where the energy goes, line by line, from
    laws.hpp. PASS only if every line cites an engine relation; any line that rests on an
    axiom (not a derivation) must be flagged and the sub-verdict is OPEN, not NATIVE.
  - **Empirical bound:** compute the maximum thermalisation efficiency η of the occluded
    flux allowed by the 47 TW budget. Report as a falsifiable number, no gate.
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant
  namespaces; re-labelling a catastrophic ledger as "recycled" without an engine line.

## Run record

- Tool: `sar01_lesage_budget.cpp` (single file, `#include <sdt/laws.hpp>` only)
- Compile: MSVC cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include
- Output: `results.txt` = verbatim stdout.

### ADJ-001
Earth mass is obtained **natively** via the koppa bridge (m = ϟ_Earth/ϟ_baryon × m_p,
bridge::N_baryons_from_koppa) rather than the prohibited M-in-kg input. The Sun→Earth force
uses bridge::g_at_radius (v²R/r²) — no G anywhere in the chain.
