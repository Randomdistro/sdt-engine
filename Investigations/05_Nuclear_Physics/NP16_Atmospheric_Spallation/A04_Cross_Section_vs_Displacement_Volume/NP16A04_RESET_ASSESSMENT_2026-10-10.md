# NP16A04 — Cross-section against displacement volume: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md, laws.hpp law_IV. No old record exists.

## Registration
The prompt's SDT hypothesis is σ_SDT = π(R_disp,p + R_disp,t)², with V_disp = 3mℓ_P³c²/Φ (law_IV) and R_disp = (3V/4π)^(1/3). It has zero parameters.

**Gate fixed before the run (the prompt states no number).** σ_SDT must be within a factor of 10 of measured reaction cross-sections.
- Measured p + nucleus reaction cross-sections are of order 10²–10³ mb across A = 6–238 [B: literature order of magnitude; no dataset in the repo].
- Reference scale for that order: π(R_p(1 + A^(1/3)))² from the engine's R_p.
- **Excluded** if the predicted magnitude is off by more than 10³ at every A.

## Run

p16a04_reset_1.cpp; output in 
p16a04_reset_1_results.txt. V1 met: V_disp(m_p) from the engine equals 3m_p c²/P_conv.

| target A | R_disp,p + R_disp,t (m) | σ_SDT (mb) | nuclear-size scale (mb) | ratio |
|---|---|---|---|---|
| 6 | 9.93e-20 | 3.10e-7 | 177 | 1.75e-9 |
| 12 | 1.16e-19 | 4.22e-7 | 241 | 1.75e-9 |
| 56 | 1.70e-19 | 9.08e-7 | 518 | 1.75e-9 |
| 238 | 2.54e-19 | 2.02e-6 | 1152 | 1.75e-9 |

R_disp(proton)/R_p = **4.19e-5**.

**Outcome: the zero-parameter V_disp hypothesis is EXCLUDED (G1) on magnitude, by about 10⁹ at every A.** The law-IV displacement radius is 10⁻⁵ of the nucleon boundary, so it cannot set a geometric cross-section. The A^(1/3) shape is shared: the ratio is constant at 1.75e-9.
- The prompt's grammar-scaling alternative (R_gram with three fitted radii r_α, r_d, r_t) needs the measured dataset (EXFOR/PDG reaction cross-sections, not in the repo): **PENDING_DATA**.
- Contaminating-input note: none. The exclusion is a native magnitude.

## Comparison with the archived record
Deferred.
