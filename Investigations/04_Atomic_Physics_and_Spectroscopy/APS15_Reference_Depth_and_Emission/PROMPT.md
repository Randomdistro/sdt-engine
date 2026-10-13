# APS15 — Reference depth, seat response and emission (child A of SDT_Loading_EC_Reseating_Neutrino_Coupling)

**Author:** J. C. Harvey, Melbourne. **Opened:** 2026-10-05, direct execution. **Id/placement:** proposed (see `Investigations/SDT_Loading_EC_Reseating_Neutrino_Coupling/SPLIT_PLAN.md`).
**Dependencies:** `DEPENDENCY_LEDGER_v2.csv` rows D22, D29, D31, D32, U01–U06 (APS01, APS05, APS06, APS07, APS13, APS14), U12 (FLM13). Inputs from `laws.hpp` only: c, ħ, α, m_e, m_p, m_d, R_inf.

## What we do not know
Whether the reference-depth relation, with the seat set by a two-body balance, gives hydrogenic emission including finite-mass (isotope) response, and which of its results are independent of the supplied α.

## Model (stated once, no fitting)
Atomic coupling C_Z = Z·α·ħ·c (ledger D22: this is the supplied α, by construction of P_eff). Two-body reduced mass μ = m_e·M/(m_e+M). Fixed action L = nħ. Seat R_n = L²/(μ C_Z); orbital energy E_n = −μ C_Z²/(2 L²). Line wavelength 1/λ = (E_u − E_l)/(2πħc).

## Gates (fixed before running)
- **G1 (identity check, expected to pass by construction):** H Balmer-α and Lyman-α from the model vs R_H = R_inf/(1 + m_e/m_p) to relative 1e-9. Recorded as an identity given α, not as a derivation.
- **G2 (universal-R failure reproduced):** with a universal R = a_0 the ion wavelength is too long by exactly √Z (Phase 0 P0-3); He⁺ ratio 1.41421 to 1e-6. Whole-range: Z = 1…6.
- **G3 (finite-mass response, the non-trivial output):** D−H Balmer-α wavelength shift Δλ_{D−H} = λ_H − λ_D from the two masses m_p, m_d only, compared with the literature value 0.179 nm (vacuum), memory-sourced, **VERIFY before certification**; tolerance 2%.
- **G4 (what is NOT derived, stated up front):** α, L = ħ, n quantisation, and the 1/r² regime are inputs. No gate can turn them into outputs; they are listed, not tested.

## Instrument validation
V1 reduced-mass limit: M → ∞ returns R_inf to 1e-12. V2 Z² scaling at infinite mass. V3 closed-form λ(2→1) for H (121.5 nm class) within 1e-3 of a direct 1/(R_H·0.75).

## Pivot table
| Outcome | Next |
|---|---|
| G1 pass, G3 pass | record: finite-mass response follows from the two-body seat with no new input; the content of the chain is α supplied |
| G3 fail | assess: m_d definition (nuclear vs atomic), vacuum/air wavelength, then new dated round |
| G2 fail | instrument error, check Z handling |

## Dated correction (2026-10-05, run 1)
G2 as first coded used r_n = n²a₀ for every ion, which is not the Phase 0 configuration (each ion at its own seat r_n = n²a₀/Z with a universal R = a₀). Run 1 therefore returned a ratio Z, not √Z, and G2 FAILED on an instrument error. The setup is corrected to r_n = n²a₀/Z, k = 1/(α√Z); run 1 output is kept as `aps15_results_run1_G2_setup_error_superseded.txt`. No gate value was changed.
