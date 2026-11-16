# NP12f — Nuclear radii from the packing construction (specification rewritten 2026-10-11)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The 2026-08-13 text and its audit block are kept below the line, superseded.

## 1. Question
Do the proton centres of the **live** packing construction (`traction-gear-engine.js`, NSEQ18-WEB-1), folded with one proton boundary, reproduce the measured nuclear boundary radii? The old question was asked of `pack-nucleus.js`, which is now a legacy control.

## 2. What is established
| # | Result | Source |
|---|---|---|
| E1 | The legacy control `pack-nucleus.js` (NSEQ05-CONTROL-3, dnn = 1.45 fm) is **excluded (G1)** on a registered gate (≥ 5 of 6 within 5%): only 2 of 6 met. ¹²C +1.8%, ¹⁶O −2.1%; ⁴He −40.8%, ⁹Be −10.4%, ⁴⁸Ca +70.6%, ⁵⁶Fe +65.6%. Origin: fixed shell steps (2D, 2.2D) make radius grow with shell count, not A^(1/3). | `NP12f_RESET_ASSESSMENT_2026-10-10.md` |
| E2 | The live construction builds every A ≥ 4 nucleus as one α 4-ring plus a tree of dock and internal contacts (E = A). It scales positions by a contraction factor (1.05 at light triton opening → 0.97 at closures). | NP17 addendum 2026-10-10; cascade 2026-10-11 |
| E3 | NP30 §9: binding is fixed by the **contact-instant** geometry, size by the **swept** extent of the rotating units. Static point positions under-predict light-nucleus size (deuteron −40%), with the error falling to +0.2% at ²⁰⁸Pb. | NP30 §9 |
| E4 | Close-pack law R(A) = R_p (A/η)^(1/3), with r₀ → 0.9300 fm, hits the heaviest nuclei to ±0.16%. Triton contraction approaches it. | NP30 §6 |
| E5 | The contraction factor also multiplies the engine's **binding**, producing 23 wrong-sign isotope steps. A radius-side quantity is being used on the binding side. | cascade 2026-10-11 (sequencer defect, propose-only) |

## 3. Errors, and what they teach
- **X1.** The registered target was a construction already marked legacy. Before registering, check the construction's own header and version.
- **X2.** A static point RMS is the wrong observable for light nuclei (E3). A test that ignores the swept extent will fail at light A for a known reason. The registration must state which reading (static or swept) is under test, and expect the light-A deficit if static.

## 4. Round 2 (registered here; not yet run; the live engine's radii have not been looked at)
**Observable.**
- R_pt² = (1/Z) Σ |r_i − r̄_p|² over the live construction's proton centres (`buildNuclide(Z, A)`, positions × contraction as the engine places them).
- R_pred = √(R_pt² + R_p²), with R_p = 0.8414 fm.
- Static reading only; the swept extent is owed (E3).

**Set.** Every nuclide in `Datasets/nuclear/IAEA_ground_states_radii.csv` that the grammar admits and the engine builds. Whole range, single pass.

**Cascade (as 2026-10-11).** B1 ≤ 0.1% … B7 > 200%.
- Registered expectation from E3: B5–B6 for A ≤ 6, improving with A.
- **Gate for "the construction carries size":** median ρ ≤ 3% (B3) over A ≥ 40.
- **Exclusion:** median ρ > 10% over A ≥ 40.

**Validations.**
- V1: on a synthetic regular tetrahedron the four vertices share one RMS, to 1e-12.
- V2: n_p = Z and n = A for every build.
- V3: an IAEA reader check on ²⁰⁸Pb (5.5012 fm).

**Comparison with E4.** Report the close-pack law on the same set, as the zero-parameter control.

## 5. Prohibitions
- Physical ρ_q is not claimed.
- No radius-side quantity is read as binding.
- The legacy control is not used as the construction.
- The word "charge" is not used.
- Release is read, never edited.

---

## Superseded specification (2026-08-13, kept as written)

# NP12f — Packer proton point-RMS (NP12e reopen)

> **Status:** PRE-REGISTERED — 2026-08-13. **IAEA sealed.**  
> **Batch gates:** `PACKER_REOPEN_PRE_REGISTRATION.md`  
> **Canon edits:** none.

Centres from `packNucleus`, not STATED ATOMICUS tables. Physical `ρ_q` not claimed.

---

## Audit correction 2026-10-05 (gating)

**Finding:** The folder has no numeric gate (34-word prompt) and passes "n = A, n_p = Z on the frozen set", a tautology of the construction.

**Correction:** Register a numeric gate against measured RMS radii before the IAEA file is unsealed.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*


**Path pointer (2026-10-05):** the batch pre-registration named here, `PACKER_REOPEN_PRE_REGISTRATION.md`, is archived at `_archive/Investigations/00_Master_Cascade/Packer_Reopen_Batch_2026-08-13/` (with `PACKER_REOPEN_ASSESSMENT.md`); the batch gates are read from there.
