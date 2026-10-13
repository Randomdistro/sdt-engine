# NP12f round 2: radii of the live packing construction (2026-10-12)

**Registration:** `PROMPT.md` §4 (rewritten 2026-10-12, before the instrument). Instrument `np12f_round2_live.js`. Output `np12f_round2_live_results.txt`.

## Run log
- **Launch 1, 2026-10-12:** interrupted at row 603 (A ≈ 164) when the session ended. No summary was written, so it is not counted as a run. The partial rows were seen; that is recorded as exposure. The gate was fixed before launch 1 and is unchanged.
- **Before launch 1** the control line was corrected to the registered form (NP30's law read directly, without a √(3/5) factor I had added), and the IAEA Z-column lookup was simplified. No output existed at that point.
- **Launch 2:** a full single pass, completed.

## Results
- **Validations:** V1 (tetrahedron RMS), V2 (n_p = Z and n = A for every build; 0 failures) and V3 (²⁰⁸Pb read) met. 18 rows were outside the canonical grammar (the sequencer refuses them); 890 nuclides were built.

| set | n | median ρ | median ratio pred/meas | bands |
|---|---|---|---|---|
| A ≤ 6 | 5 | 29.2% | 0.708 | B4 1, B5 2, B6 2 |
| 7 ≤ A ≤ 39 | 51 | 23.2% | 1.227 | B2 1, B3 5, B4 11, B5 15, B6 19 |
| **A ≥ 40** | **834** | **27.3%** | **1.273** | B3 4, B4 29, B5 557, B6 244 |

- **Gate (median ρ over A ≥ 40):** 27.3% > 10%. **EXCLUDED: the live construction's static proton positions do not carry nuclear size.** Built nuclei are about 27% too large, uniformly across the heavy range.
- **Zero-parameter control** (NP30 close-pack law R = R_p (A/η)^(1/3)): median ρ **2.01%** on the same A ≥ 40 set.
- **Light end,** as registered (E3): too small (²H and ³H have one proton, so R_pt = 0; ⁴He 0.87).

## Post-run diagnostic (not a registered gate)
Along isotope chains (761 steps, A ≥ 40):
- the construction's radius grows **0.57% per step on average**, against a measured 0.19%;
- **390 of 761 steps (51%) have the opposite sign** to the measured change.
- Example: ⁴⁰Ca → ⁴⁸Ca. Measured 3.4776 → 3.4771 fm (flat); construction 3.154 → 4.346 fm (+38%).

The construction's size response to added neutrons is uncorrelated with the measured one. It is the reverse of the triton-contraction rule, under which tritons draw the boundary in. This parallels the binding diagnostic (cascade 2026-10-11: contraction wired with the wrong sense).

## Grades and consequences
| Item | Grade |
|---|---|
| Live construction carries size (static reading) | **G1, excluded** (27%) |
| Close-pack law | 2.0%, re-verified (exposed number class; consistent with NP12) |

**Sequencer defects (propose-only; Release not edited):**
- uniform +27% size;
- chain response uncorrelated with measurement;
- H1 envelope 1.085 R_p and untraced constants (PPT18);
- the contraction sense (cascade).

**Downstream:**
- NSEQ18's registered O3 gate (radii) is now answered: **not met**.
- NP12 round 2 uses the close-pack law with the triton-contraction term, not the built construction.
