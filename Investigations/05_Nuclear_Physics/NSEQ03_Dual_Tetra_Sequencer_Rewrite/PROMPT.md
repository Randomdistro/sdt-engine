# NSEQ03 — Dual-tetra triton seating applied to sequencer

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Upstream:** NSEQ02 (`BELT_ORIENTATION_STALE`); author “continue”.  
> **Canon:** sequencer HTML orientation rewrite only; `laws.hpp` propose-and-wait.

## Claims

| ID | Claim |
|---|---|
| NSEQ03-C1 | Site + `docs/` sequencer triton seating uses dual-tetra shells. |
| NSEQ03-C2 | Packing smoke: He/C/O/Fe/U nucleon count = A, protons = Z. |
| NSEQ03-C3 | Ca-48 (`n_t=8`): first shell not coplanar; poles present; `r_open>r_close`. |
| NSEQ03-C4 | Capacities still 8,10,12,14… (schedule counting unchanged). |
| NSEQ03-C5 | `laws.hpp` not edited; nomenclature proposal filed. |

---

## Audit correction 2026-10-05 (gating)

**Finding:** Claims such as "BELT_PAIRS / beltPlane gone" and "nucleon count = A" are code-state checks scored PASS, with no numeric gate.

**Correction:** Treat them as unit tests of the sequencer and keep them out of the physics tally.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
