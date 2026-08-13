# NSEQ06 Amendment 01 — Source Re-freeze

**Date:** 2026-08-09  
**Reason:** the initial execution refused to run because two untracked proposal
files changed after the pre-registration hash capture. No result had been
generated, so a documented re-freeze is permitted.

| Item | Original SHA-256 | Re-frozen SHA-256 | Effect on NSEQ06 |
|---|---|---|---|
| `NSEQ01_Sequencer_Rules_Freeze/NSEQ01_ASSESSMENT.md` | `c3e3bb1d8ce82d309894450c0cbca896b31380c4b389c81950c83e7374d5b296` | `6c6b6bb628868bfa4b1a6c0f7fc3c99951f9d8618b1008b9c63e433eba2c4541` | comparison-only upstream ledger; formal geometry gates unchanged |
| `NSEQ05_Pure_Shell_Stella_Cuboct_Relations/nseq05_pure_shell_stella_cuboct.py` | `746e631042c32c7a1bcaf25d92a7bb1b00d0ee1963c4c50f2ee42f3877b49d36` | `4a91adfc6262876e7902a50554fdb56b12bb676a38aa9af617e7d961db992e92` | comparison-only proposal; it explicitly selects one triangle and one six-cycle Q-Q branch |

All other frozen source hashes were rechecked and matched the original table.
The two replacements were rehashed twice after a short delay with identical
values. The NSEQ06 script now rejects any later change to these re-frozen
sources before producing output.

This amendment does not convert a coded capacity ledger into observational
evidence and does not relax any falsifier in `NSEQ06_PRE_REGISTRATION.md`.
