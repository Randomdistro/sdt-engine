# APS15 — Assessment (2026-10-05)

**Classification:** `APS15_FINITE_MASS_RESPONSE_COMPUTED__IDENTITY_GIVEN_ALPHA`<br>
**Run class:** direct. Tool `aps15_reference_depth.py` (reads constants from `laws.hpp`; none redefined). Output `aps15_results.txt`; run 1 kept as `aps15_results_run1_G2_setup_error_superseded.txt`. **Canon edits:** none. **Fitted parameters:** 0.

| Gate | Result |
|---|---|
| V1–V3 | pass (infinite-mass limit 6.1e-10 from R_inf vs α-based constants; Z² = 4.000000000; Lyman-α 121.5684 nm) |
| G1 five H lines vs R_inf/(1+m_e/m_p) | ratio 1.000000000611 on every line (same offset as V1: the engine's α, ħ, m_e, c and R_inf agree to 6e-10) |
| G2 universal-R √Z failure, Z = 1–6 | reproduced exactly (√Z) after correcting my own setup error (r_n = n²a₀/Z); run 1 failed on that error |
| G3 D−H Hα shift | 0.17858 nm vs 0.179 nm (literature, memory-sourced, VERIFY): −0.24%, PASS |

## Assessment
1. G1 is an identity given the supplied α, ħ, m_e, c (ledger D22; audit F1). It confirms the engine's constants are mutually consistent; it derives nothing.
2. G3 is the non-trivial output: the isotope shift follows from the two-body reduced mass using only m_p and m_d; no new input. It is the finite-mass response the spec asked for, and it matches at 0.24%. Agreement with the standard reduced-mass result is convergence by §3.8; the model's reduced-mass seat is the same algebra, so this cannot discriminate between frameworks. The literature value must be verified before certification.
3. G2 shows what the universal-R reading costs: an ion at its own seat is needed, which is the per-ion R = L²/(μC_Z) of the continuation.
4. Not derived (G4): α, L = ħ, quantisation of n, the 1/r² regime. Child A therefore closes as COMPUTED with these listed inputs; it does not open the downstream phases.
5. Next in the chain is B (PM08 connectivity), which needs a definition of collective electron connectivity that the corpus does not hold (ledger D48).
