# CR03 — Transfer-function closure: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md; the EMC01 reset record's summary in RESET STATUS (supplier-side, permitted). **Not opened:** CR03_VERDICT.md, esults.txt, RUN_LOG.md, the old tool.

## Run
- Instrument: `cr03_reset_1.cpp`; output in `cr03_reset_1_results.txt`.
- **Attempt 1** used the prompt's a_rad expression verbatim. Output kept: `cr03_reset_1_results_attempt1_prompt_formula.txt`.

**Finding in the prompt.** Its a_rad = 2π⁵k_B⁴/(15h³c²) is the **Stefan–Boltzmann constant σ** (5.670374e-8 W m⁻² K⁻⁴), not the radiation constant. The radiation constant is a = 4σ/c = 8π⁵k_B⁴/(15h³c³). Attempt 1 therefore missed f by about 7.5e7.

**Attempt 2** (correct a, from k_B, ħ and c):
- **Stage 1:** P_eff = m_p² m_e² c⁵/(4παħ³) = **5.227252e31 Pa**, the same as the engine's law_III::P_eff (relative 1.2e-9, constant rounding). The reduction is exact: R_p_lock = 4ħ/(m_p c), r_e = αħ/(m_e c).
- **Radiation constant:** a from {k_B, ħ, c} = 7.565733e-16; the engine's stored measured::a_rad = 7.565700e-16 (relative 4.4e-6, a rounded stored value).
- **Stage 2:** f = m_p² m_e² c⁵ ℓ_P/(4παħ³ R_CMB a T_CMB⁴) = **2.124180e-17**. The engine's _transfer = 2.124189e-17; the 4.4e-6 difference is entirely the stored a_rad rounding. **f ∝ R_CMB⁻¹** is confirmed.

## Outcome
- **The algebraic closure is verified:** CONSTRUCTION, an exact reduction.
- **R_CMB is isolated as the single class-X input:** G3, shared-input. The contaminating input is R_CMB, the observed cosmological scale (measured::R_CMB), entering at laws.hpp:249–276. This agrees with the EMC01 reset.
- **Stage 3 (deriving R_CMB): open.** It is carried by CR05 and the cosmology chain; CR05 is held for a fresh session.
- **Propose-and-wait (canon):** measured::a_rad is stored to 5 figures (7.5657e-16). Computed from the engine's exact SI k_B, h and c, it is 7.565733e-16. A canon edit would remove the 4.4e-6 inconsistency. **Not edited.**

## Comparison with the archived record
Deferred.
