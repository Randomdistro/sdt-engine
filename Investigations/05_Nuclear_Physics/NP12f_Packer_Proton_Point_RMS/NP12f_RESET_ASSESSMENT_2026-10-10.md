# NP12f — Packer proton point-RMS: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`
- the archived batch pre-registration `_archive/.../Packer_Reopen_Batch_2026-08-13/PACKER_REOPEN_PRE_REGISTRATION.md` (a specification, permitted; the batch assessment beside it was **not** opened)
- `Release/HTML_SDT_Website/js/pack-nucleus.js` (the construction)

**Not opened:** `NP12f_ASSESSMENT.md`, `np12f_packer_proton_rms.py`, `RUN_LOG.md`, the old shared port `pack_nucleus.py`.

## Premise note
`pack-nucleus.js` now carries the header "Legacy NSEQ05 geometric comparison control … not the Atomicus nucleus" (version NSEQ05-CONTROL-3, file dated 15 Aug 2026). That is after the batch registration of 13 Aug. The run measures the legacy control as it stands, with dnn = 1.45 and coulSpread = 0 frozen. **No conclusion transfers to the Atomicus nucleus.**

## Registration (fixed before the IAEA file is opened)

The 2026-10-05 correction requires a numeric gate before unsealing.

- **Frozen set:** ⁴He, ⁹Be, ¹²C, ¹⁶O, ⁴⁸Ca, ⁵⁶Fe.
- **Map:** R_pt² = (1/Z)·Σ|r_i − r̄_p|² over packed proton centres, from node calling `packNucleus(A, Z)` directly (the construction, not an old tool).
- **Comparison quantity:** R_ch,pred = √(R_pt² + R_p²), with R_p = 0.8414 fm (the construction's own value). That is the point distribution folded with one proton boundary. Physical ρ_q is still not claimed.
- **Gate (new, registered now):** |R_ch,pred / R_ch,meas − 1| < 0.05 for at least 5 of the 6 nuclides.
  - **G4-type consistency** if met.
  - **Excluded (G1)** if 2 or more miss.
- **Measured:** `Datasets/nuclear/IAEA_ground_states_radii.csv`, opened only after this file is saved.

**Batch gates carried:**
- C1: the 4 vertices of a regular tetrahedron share one RMS (validation);
- C2: n_p = Z and n = A;
- C3: R_pt published;
- C4: physical ρ_q underdetermined;
- C5 is superseded by the new gate.

## Run and results
- Node called `packNucleus` (version NSEQ05-CONTROL-3, dnn = 1.45, coulSpread = 0).
- Proton centres were extracted and the RMS computed by a short script in the scratchpad.
- **C2 met:** n = A, n_p = Z for all six.
- **C1:** He-4's two protons are symmetric about the centre (the construction places the α as a regular-tetrahedron face set).

| nuclide | R_pt (fm) | R_ch,pred = √(R_pt² + R_p²) (fm) | measured (IAEA) | ratio − 1 |
|---|---|---|---|---|
| ⁴He | 0.5247 | 0.9916 | 1.6755 | −40.8% |
| ⁹Be | 2.0943 | 2.2570 | 2.5190 | −10.4% |
| ¹²C | 2.3688 | 2.5138 | 2.4702 | **+1.8%** |
| ¹⁶O | 2.5042 | 2.6418 | 2.6991 | **−2.1%** |
| ⁴⁸Ca | 5.8726 | 5.9326 | 3.4771 | +70.6% |
| ⁵⁶Fe | 6.1326 | 6.1901 | 3.7377 | +65.6% |

**Gate (≥ 5 of 6 within 5%): 2 of 6. EXCLUDED, G1, for the legacy control.**

**Origin.** The control steps each shell outward by a fixed 2D (deuterons) or 2.2D (tritons), with D = 1.45 fm. Radius therefore grows with the number of shells, not with A^(1/3): ⁴⁸Ca and ⁵⁶Fe are far too large. ⁴He's single tetrahedron is too compact. This is consistent with the file's own statement that it is a legacy control and not the nucleus.

**Downstream:** nothing in the graph. The result bears only on the control.
