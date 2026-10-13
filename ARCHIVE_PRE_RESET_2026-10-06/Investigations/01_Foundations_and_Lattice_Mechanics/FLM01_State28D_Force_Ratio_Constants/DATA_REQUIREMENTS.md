# FLM01 — Data Requirements

## Measured Constants (CODATA 2018, IAU, NIST)

| Constant | Symbol | Value | Unit | Source |
|----------|--------|-------|------|--------|
| Planck constant | ℏ | 1.054571817 × 10⁻³⁴ | J·s | CODATA 2018 |
| Speed of light | c | 2.99792458 × 10⁸ | m/s | CODATA 2018 |
| Electron mass | mₑ | 9.1093837015 × 10⁻³¹ | kg | CODATA 2018 |
| Proton mass | mₚ | 1.67262192369 × 10⁻²⁷ | kg | CODATA 2018 |
| Elementary charge | e | 1.602176634 × 10⁻¹⁹ | C | CODATA 2018 |
| Compton wavelength (e) | λc,e | 2.42631023867 × 10⁻¹² | m | derived: ℏ/(mₑc) |
| Compton wavelength (p) | λc,p | 1.32140985539 × 10⁻¹⁵ | m | derived: ℏ/(mₚc) |
| Classical electron radius | rₑ | 2.8179403262 × 10⁻¹⁵ | m | derived: e²/(4πε₀mₑc²) |

## Engine Constants (from laws.hpp)

| Constant | Symbol | Value | Dimension | Reference |
|----------|--------|-------|-----------|-----------|
| Transfer function | f | 2.123360 × 10⁻¹⁷ | [dimensionless] | laws.hpp:EMC01 |
| Convergence pressure | P_eff | ~10⁴⁸ | Pa | laws.hpp:bridge |

## Derived Scales (To Be Computed in FLM01)

| Scale | Symbol | Expected Range | Dimension | Purpose |
|-------|--------|-----------------|-----------|---------|
| T₅ natural scale | σ_T5 | 10⁹–10¹¹ | Pa/m | Occlusion gradient |
| Φ₅ natural scale | σ_Φ5 | 10⁻²¹–10⁻¹⁹ | J | Phase transition |

## Files to Consume

- Engine/include/sdt/laws.hpp — measured constants and force law
- Engine/include/sdt/state28d.hpp — the 28D manifold (check lines 134, 159)
- Theory/02_Inputs_and_Derivations.md — convergence pressure context
- CQ01_Transfer_Function_Derivation/INVESTIGATION.md — related f-value derivation

## No External Data Required

FLM01 is a pure derivation; no experimental data beyond CODATA 2018.
