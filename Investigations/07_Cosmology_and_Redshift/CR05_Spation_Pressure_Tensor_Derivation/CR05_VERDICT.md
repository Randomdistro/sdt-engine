# CR05 — Spation Pressure Tensor Derivation

> **Author:** James Christopher Tyndall, Melbourne
> **Status:** H₀/transfer closure EXCLUDED; pressure and freeze-out mechanisms OPEN
> **Instrument:** `cr05_pressure_solver.cpp`

## Direct result

The instrument does not derive H₀. It imports `67.4 km s⁻¹ Mpc⁻¹` and Planck Ω normalisations into its bootstrap-FLRW branch. Its native pressure-balance route gives

\[
H_0=1.2486\times10^{49}\ {\rm km\,s^{-1}\,Mpc^{-1}},
\]

and the comoving-distance calculation gives

\[
r_c(z_{\rm rec})=4.691\times10^{26}\ {\rm m},
\]

which is 50.8% below the comparison value `9.527e26 m`.

## Scope

- Candidate A diverges; candidates B and C require an external normalisation.
- Candidate D imports the Friedmann structure, H₀ and Ω values; it is not an SDT derivation.
- `P(z)=P_conv(1+z)^4`, `gamma_eff=4`, and a fourfold recombination freeze-out are hypotheses in this instrument, not independently derived laws.
- `R_CMB` remains observed, so `f=P_eff/P_conv` remains Class E and inherits the hydrogen calibration.
- No CR05 acceleration-floor or framework-closure consequence is certified.

## Reopening condition

Supply a dimensionally closed pressure-to-rate equation that predicts H₀ without H₀, `R_CMB`, Ω normalisations or Friedmann coefficients as inputs. Freeze the cosmological comparison data, run the whole redshift range once, and require the registered H₀ and distance residual gates.
