# NP17b — Packed geometry binding: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`
- the archived batch pre-registration (specification; the batch assessment was not opened)
- `pack-nucleus.js`

**Not opened:** `NP17b_ASSESSMENT.md`, `np17b_packed_binding.py`, `RUN_LOG.md`.

## Premise note
The construction is now labelled "Legacy NSEQ05 geometric comparison control … not the Atomicus nucleus" (CONTROL-3, 15 Aug, after the 13 Aug batch registration). Results bear on the control only.

## G1 (batch gate, carried)
Li-6 packed deuteron, E = 3αħc / D_pn, against 2.224 MeV. MATCH if rel < 0.20.

Node `packNucleus(6, 3)`: the deuteron unit's internal p–n distance is **1.4500 fm** (dnn, frozen). With αħc = 1.4400 MeV·fm (batch value), E = 3 × 1.4400 / 1.4500 = **2.979 MeV**, rel **+0.339**.

**G1 FAIL.** The other p–n contacts in the same build give larger energies, so they are listed, not selected:
- α internal, 1.0017 fm: 4.313 MeV
- rest bond, 1.2046 fm: 3.586 MeV

**Origin.** The energy follows from the frozen dnn = 1.45 fm. The gate tests whether that geometric constant fixes the deuteron with the 3αħc/d form, and it does not, by 34%.

## G2: not run
G2 needs the NP17 "packed pairwise report" rule. NP17 has not been rerun under this protocol, and its old record may not be opened.

**Grades:** G1 → G1 (excluded, on the control). G2 → G2 (open, supplier NP17).
