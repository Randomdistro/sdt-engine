# NSEQ06a Amendment 03 — Report Hash Correction

**Date:** 2026-08-09  
**Effect on verdict:** none

The results report initially transcribed the canonical-payload SHA-256 as the
script SHA-256. Validation caught the mismatch before handoff.

| Item | Incorrectly recorded | Verified value |
|---|---|---|
| `nseq06_independent_replication.py` SHA-256 | `ff2a5cbae6d6a76f3be9f69ff0cad861df334cb1b81db187f5a5fc2eb3a1587b` | `e8cf18b76648beac4d45607c95bb16a6f69a61297f377e217efcc621a8b6f374` |
| Result JSON file SHA-256 | unchanged | `21c6528331f5336c0af9393bd8d4ff5ae58a22dd0080a63699e2ce7a868b17e4` |
| Result canonical-payload SHA-256 | unchanged | `ff2a5cbae6d6a76f3be9f69ff0cad861df334cb1b81db187f5a5fc2eb3a1587b` |

The script, frozen inputs, result JSON, formal gates, and verdict were not
modified. Only the report metadata was corrected.
