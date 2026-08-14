# NSEQ06a Amendment 04 — Canonical Drift Re-freeze

**Date:** 2026-08-09  
**Cause:** `Engine/include/sdt/laws.hpp` changed after the accepted NSEQ06a run.  
**Canon action by NSEQ06a:** none; this audit does not alter canonical files.

| Input | Accepted-run SHA-256 | Current SHA-256 |
|---|---|---|
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | `64fdb5c17c34138c63426134e96f12cb716085255e300b5a79ebd98ca296d504` |

The current edit preserves the numerical arrays `{6,12,12,20,30}` and
`{4,5,6,7}`, the grouped closure values, and the `F/B/R` formulas. It renames
the triton identifiers and adds a pure-shell/stella/cuboct narrative. NSEQ06a
therefore re-runs the arithmetic gate against the new source, but it does not
convert the new prose into empirical or mechanism evidence.

The following current canonical statements exceed what NSEQ06a establishes:

1. `face-count 12→16→20 EXCLUDED`: NSEQ06a finds only that one stated ad hoc
   arithmetic continuation differs from the coded sequence. It does not exclude
   an unspecified family of face-based physical mechanisms.
2. `capacities DERIVED` and a shell formation/occupancy narrative: NSEQ06a
   establishes vector and graph-count identities, not a force law, formation
   dynamics, or a derivation of observed closure locations.
3. `FORWARD PREDICTION ... N=184`: the arithmetic extrapolation is valid, but
   the D42 graph has the recorded non-planar simple-surface debt and no physical
   contact-selection rule. It is not promoted to an adjudicated prediction.

The new canonical identifier `triton_shell_pairs` replaces
`triton_belt_pairs`. The independent parser is updated solely to read the
current source and will be re-executed with all other frozen inputs unchanged.
