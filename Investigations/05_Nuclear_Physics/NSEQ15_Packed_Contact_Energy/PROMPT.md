# NSEQ15 — Packed contact energy (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work; errors inform the mechanism. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**G2, blocked.** The hold-out "NSEQ09 SEAL medD = 4.242 MeV" is undefined here, and NSEQ09 has not been re-run. The packed contact lengths came from the legacy control.

## 2. What the errors and new data teach
- **The far-field Law III contact gives about 0.08 MeV** (NP09/NP10 resets): about 20–30× short of nuclear contact energies. Far-field occlusion is not the contact scale.
- **The live sequencer's zero-fit unit αħc/R_p = m_e v(R_p)² (1.711 MeV)** gives binding right in order across 250 stable nuclides (cascade 2026-10-11: B6 level, ratio CV 8.5%, shape B4). The missing factor (1.5× at Li to 2.6× at Pb) grows with coordination.
- NP17 reset: per-electron seat ledgers are excluded for A ≥ 3; the carrier is the proton–proton contact, and the lock is cooperative (NP10).
- Harvey 2026-10-11/12: occlusion strength may be modulated by the displacement depth at the contact. Nuclear contacts sit beyond **hydrogen's** c-boundary (z_H ≈ 1.7) and shallow in each proton's own (z_p ≈ 0.13; PPT18).

## 3. Next round (registered order)
1. Define medD natively, or from a re-run NSEQ09, before anything else.
2. The contact energy as the NP17 round-2 O1 rule (owed): unit m_e v(R_p)², with a cooperative closure term and contraction raising binding. Registered before loading.
3. A blind test on the live sequencer's contact graphs.

## Prohibitions
- No form chosen to reach anchors (2026-10-07 rule).
- No census of candidate cells.
- No QM formalism as scaffolding.
- No potential-energy bookkeeping for binding.
- The legacy packer (`pack-nucleus.js`, NSEQ05-CONTROL-3) is not the construction; the live sequencer is `traction-gear-engine.js` (NSEQ18-WEB-1).

---

## Previous specification (kept as written)

# NSEQ15 — Packed contact energy (NSEQ14 reopen)

> **Status:** PRE-REGISTERED — 2026-08-13.  
> **Batch gates:** `PACKER_REOPEN_PRE_REGISTRATION.md`  
> **Canon edits:** none.

Hold-out SEAL medD = 4.242 MeV. Lengths from packed contacts. No B_d/B_t.

---

## Audit correction 2026-10-05 (gating)

**Finding:** The 33-word prompt carries no numeric gate (the gates sit in a separate pre-registration file), so the folder cannot be checked for pre-run commitment on its own.

**Correction:** Copy the numeric gates into the folder or link the dated pre-registration.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*


**Path pointer (2026-10-05):** the batch pre-registration named here, `PACKER_REOPEN_PRE_REGISTRATION.md`, is archived at `_archive/Investigations/00_Master_Cascade/Packer_Reopen_Batch_2026-08-13/` (with `PACKER_REOPEN_ASSESSMENT.md`); the batch gates are read from there.

**Correction to the finding above (2026-10-05):** the gates are in the archived batch pre-registration (pointer added), so this folder is verifiable; the remaining item is only that the 33-word prompt should state its own numeric gate.
