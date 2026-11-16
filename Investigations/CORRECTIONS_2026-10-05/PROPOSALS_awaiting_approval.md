# Proposals that need the Operator's word (nothing below was done)

Standing rules kept: no edits to `Engine/include/sdt/` or `Laws/`; no deletion or renaming without approval; ids and placement are propose-only.

## Renames and ids
1. **FLM15 id collision.** `01_Foundations_and_Lattice_Mechanics/FLM15_Casimir_as_Relay_Exclusion` and `FLM15_Influx_Phase_Resistance_Ratio` share an id (the engine's "FLM15 resistance kernel" means the second). Proposal: rename the Casimir folder to the next free FLM id and update catalogue row B98.
2. **GD06 id collision.** `GD06_Collective_Displacement_Redshift_Law` and `GD06_Gravitational_Lensing`. Proposal: renumber the lensing folder (its results now rest on the eikonal tool added today).
3. **GOM_DAT1–9 claim ids.** Claims are written `GOM28…GOM35`; alias notes were added instead of renaming (earlier text is not rewritten). Proposal: rename claim ids in a later pass once the Operator agrees.
4. **Loading-chain children** (APS15, PM08, NP40, NP41, SAR10) and **NP42**: ids and placement still proposed.

## Canon items (engine; propose-only)
5. `laws.hpp` carries two independent literals for the same length, `r_e` and `α²a_0` (relative 1.94e-12); APS12 widened an instrument identity gate (1e-12 to 1e-11) because of it. Proposal: derive `r_e` from `α²a_0` (or the reverse) in `laws.hpp` so the identity holds exactly.
6. The celestial solver's `QUALIFICATION_MANIFEST.json` hash is stale against `laws.hpp` (ledger D52). Proposal: regenerate the manifest and re-qualify before it is cited.

## Splits and models that need a decision
7. **CR09** bundles eight routes (A–H) in one prompt. Proposal: one folder per route with its own gate (Route B has run: raw-m_B fit, see its assessment).
8. **Seeds with no model** (PPT12–15, GOM20, GOM21, SAR07, SAR08, QM08, OP08): each correction block states the definition and tolerance that must exist before a tool is written; the mechanisms themselves are the Operator's to supply or approve.
9. **Heavier derivations owed:** CM02 (τ from a defect cross-section), CH01 (the F_in(R) = F_out(R) root-find), GOM19 (f(q) from the radiated part of the binding), GOM06 (chirp length from measured f(t), not catalogue masses), QM06 (wake-survival test), NP24 (the sweep script).
