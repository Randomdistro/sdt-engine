# NP31 — Assessment (2026-10-05)

**Classification:** `NP31_ROUTES_NOT_RUN__ENGINE_CONTACT_COUNT_SHOWS_CROSSOVER_AT_A4_EXPLORATORY`<br>
**Run class:** direct, exploratory (see `RUN_LOG.md`). **Canon edits:** none. **Fitted parameters:** 0.

## What was checked
1. **PROMPT §2 table reproduces.** Needed multiplier B_meas/B_d from the sequencer table agrees with the PROMPT to ≤ 0.03% (He-4 12.72, Be-9 26.15; Fe-56 221.28 against 221.34).
2. **Engine contact counts (unchanged NSEQ16–18 engine):**

| Nucleus | contacts | kinds | (n−1)! | needed × | needed ÷ contacts |
|---|---|---|---|---|---|
| H-2 | 1 | internal | 1 | 1.00 | 1.00 |
| H-3 | 2 | internal | 2 | 3.81 | 1.9 |
| He-3 | 2 | internal | — | — | — |
| He-4 | 4 | alpha | 6 | 12.72 | 3.18 |
| Li-7 | 7 | alpha 4, dock 1, internal 2 | 720 | 17.64 | 2.52 |
| Be-9 | 9 | alpha 4, dock 2, internal 3 | 40320 | 26.15 | 2.91 |
| C-12 | 12 | alpha 4, dock 4, internal 4 | 3.99e7 | 41.43 | 3.45 |
| O-16 | 16 | alpha 4, dock 6, internal 6 | — | 57.37 | 3.59 |
| Fe-56 | 56 | (NP41 round 3) | 1.3e73 | 221.28 | 3.95 |

## Assessment
- The engine's contact graph is a chain for A ≤ 3 (n − 1 contacts: 1, 2), a closed four-contact ring at He-4, and then one contact per added nucleon (contacts = A for every nuclide from He-4 up, NP41). So its count matches (n − 1)! at d and t, falls below it at the alpha (4 against 6), and is extensive above: the factorial-to-linear change sits at A = 4 as a property of the construction, with no binding datum entering the count. This is the shape NP31's Route A asks for, and it is observed here, not derived: the engine's graph comes from the NSEQ construction rules (grammar and tetrahedral/icosahedral packing), not from a stated tour-reach definition, so Route A's requirement (a geometric definition of the reach) is not met.
- The needed multiplier per contact is not flat: 1.0 (d), 1.9 (t), 3.18 (α), then 2.5 → 3.95 from Li-7 to Fe-56. That is the same fact as NP41's per-contact normalisation (engine coupling ≈ 3.05 MeV per contact against B/A ≈ 8.3 MeV) and its light-nucleus tail; a count alone does not pay the binding ladder.
- Route B (residence-law derivation of "energy ∝ tour count") and Route C (11.6 mfm per triton from the same interleave) require the packing geometry in length units and an FLM14 residence argument; neither is in the repo as an executable object. They are not run, and no pass is claimed.
- Shared-input note (NP24): a contact count equal to A is the same information as A, so extensiveness above the alpha is not independent evidence of a tour cap.

## Next (propose-only)
Register a geometric definition of the tour reach in terms of the engine's pose data (neighbours within one rim-circumference of the electron's destination set), compute it with no binding data for A = 2…16, and test the crossover as an output with a null counting rule; then Route C needs a length derivation from the same poses.
