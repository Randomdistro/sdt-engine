# EMC04 — Electropause verdict

**Author:** James Christopher Tyndall, Melbourne<br>
**Status:** `P_eff` DERIVED (Class C)<br>
**Instrument:** `emc04_electropause.cpp` (MSVC C++20, exit 0)<br>
**Output:** `emc04_rerun_2026-07-23.txt`

## Result

- `m_e(αc)²/a₀`, Coulomb comparison and engine occlusion agree at ratio
  `1.0000000000`.
- FLM07 selects the target-free lock boundary
  `R_p,lock=4ℏ/(m_pc)=0.841236 fm` before measured-radius comparison.
- Electropause inversion gives `P_eff=5.227252e31 Pa`.
- `4αℏc/(πR_p,lock²r_e²)` agrees exactly with the engine form.
- `m_p²m_e²c⁵/(4παℏ³)` agrees to `1.2e-9` relative.
- The measured proton boundary is comparison-only; its residual is `0.0195%`.

## Scope

The prediction path contains no `k_e`, `e`, or measured `R_p`. It inherits the
mass/action seat, the spectroscopic α rung, and FLM07's
minimum-resistance-path premise. `f_transfer=P_eff/P_conv` is computed from
this numerator but remains conditioned on the observed Clearing boundary in
`P_conv`.
