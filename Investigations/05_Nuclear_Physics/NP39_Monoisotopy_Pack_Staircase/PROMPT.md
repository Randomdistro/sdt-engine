# NP39 — Monoisotopy and the pack staircase (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work; errors inform the mechanism. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**G2, blocked on a supplier.** The gates count shell fills of the NSEQ05 pack against NP23's frozen sets; NP23 has not been re-run, and its sets cannot be rebuilt without guessing C1.

## 2. What the errors and new data teach
- The NSEQ05 pack is now a **legacy control** (NP12f: radii fail 4/6; NP17b: deuteron +34%). The live sequencer carries the canon shell schedule: 2 → D6 → 8 → D12 → 20 → T8 → 28 → D12 → 40 → T10 → 50 → D20 → 70 → T12 → 82 → D30 → 112 → T14 → 126.
- Grammar and shell counts are maps of (Z, N) (NP24). A staircase defined on them is shared-input unless it predicts something the counts do not contain.

## 3. Next round (registered order)
1. NP23 re-run (supplier), giving the frozen singles and doubles sets.
2. Recast the staircase on the **live** schedule.
3. A registered observable beyond membership. Candidate: monoisotopic elements fall at belt-opening positions of the live schedule. Before any comparison, write which positions are predicted and how many monoisotopic elements chance would put there (look-elsewhere count).

## Prohibitions
- No form chosen to reach anchors (2026-10-07 rule).
- No census of candidate cells.
- No QM formalism as scaffolding.
- No potential-energy bookkeeping for binding.
- The legacy packer (`pack-nucleus.js`, NSEQ05-CONTROL-3) is not the construction; the live sequencer is `traction-gear-engine.js` (NSEQ18-WEB-1).

---

## Previous specification (kept as written)

# NP39 — Monoisotopy vs NSEQ05 pack staircase

> **Status:** PRE-REGISTERED — 2026-08-13. Direct execution.  
> **Batch gates:** `_archive/Investigations/00_Master_Cascade/Packer_Reopen_Batch_2026-08-13/PACKER_REOPEN_PRE_REGISTRATION.md (archived location; path corrected 2026-10-05)`  
> **Canon edits:** none.

NP23 mapped width-1 windows. This loop tests whether the interleaved pack order
(α → D6 → D12 → T8 → …) places those soles at a shared pack-stop class.
Not a native WHICH-A. dnn frozen.

---

## Audit correction 2026-10-05 (data / provenance)

**Finding:** The batch gates are held in `Packer_Reopen_Batch_2026-08-13/PACKER_REOPEN_PRE_REGISTRATION.md`, which does not exist at that path, so the pre-registration cannot be verified.

**Correction:** Restore the batch pre-registration file or copy its gates into this folder.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
