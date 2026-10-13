# NP06 — Assessment (2026-10-05)

**Classification:** `NP06_SPEC_NUMBERS_CONFIRMED__P1_NOT_RUN_MESH_DELTA_OMEGA_UNDEFINED`<br>
**Run class:** direct. Tool `np06_arithmetic.py` (constants read from `laws.hpp`); output `np06_arithmetic_results.txt`. Pre-run commitments in `RUN_LOG.md`. **Canon edits:** none. **Fitted parameters:** 0.

## Step 0 — the spec's stated numbers (gate: within 1%)
| Quantity | This run | Spec |
|---|---|---|
| B_d | 2.224566 MeV | 2.224 MeV |
| Δω = B_d/ħ | 3.3797e21 rad/s | 3.38e21 (−0.009%) |
| k at proton surface | 0.54643, c/k = 1.8301 c | 1.83 c |
| Ω_rim = c/(k R_p) | 6.5205e23 rad/s | 6.52e23 (+0.008%) |
| Δω/Ω_rim | 5.1832e-3 | 5.2e-3 (−0.32%) |
All five confirmed. Also computed: Δω/Ω_rim = 0.7103 α (29% below α, as the spec says); B_d divided by the engine's interaction scale αħc/R_p = 1.7114 MeV is 1.2999. These are stated, not interpreted; the spec forbids fishing the ratio and no look-elsewhere census was registered.

## P1 precondition not met
P1 needs a mesh Δω computed from packing geometry without using E. A repo-wide search finds none: `laws.hpp` records the gear-frequency binding as a "successor under test" (comment at the B_deuteron block), `AUDIT_DEPENDENCY_GRAPH.md` lists it as "awaits implementation", the NSEQ16–18 gear engine (`traction-gear-engine.js`) contains no angular-rate or frequency quantity, and FD10 cites NP06 as if Δω were established. The PROMPT's own "OWED POINTER" (locate the result that the gear frequency is the movement of the binding) did not resolve to any file. This is root-3 (Δω definition ambiguous) in the PROMPT's own sort. Any Δω computed now would have to be defined by this run; the PROMPT forbids deriving it from E and a definition invented to land on 3.38e21 would be the circular result it warns against. P1–P3 therefore stand unrun.

## What would unblock it (propose-only)
- Locate the Operator's result referred to by the OWED POINTER, or state the intended Δω definition (for example: the beat between meshed rim rates at the lock distance D = 2R_p + R_p/3 with the shared electron at the node, in terms of the gear engine's pose data).
- Dependent items that cite NP06 for Δω: FD10 (vortex shedding Strouhal) and CQ32's successor row in the dependency audit.

## Gate summary
T1–T5 not evaluated (need Δω). No falsifier fired; no correspondence result exists yet.
