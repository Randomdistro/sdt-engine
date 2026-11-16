# Chapter 25 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch25_hydrogen_from_the_circulation_boundary.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The hydrogen rung of the engine as a circulation-boundary construction and as a spectral ladder: the rung relations $v_{Zn}=Z\alpha c/n$, $r_{Zn}=n^2a_0/Z$, the boundary length $\mathrm{Om}_Z=Zr_e$, the depth $z=\mathrm{Om}/r$ and the ratio $k=c/v$ (the product $zk^2=1$ is an identity of the definitions and is not an independent test, per the author's ruling of 2026-11-03 that $z$ is here only a defined geometric ratio); the rotation-field function `atomic::rotation_field_velocity(r)=c\alpha\sqrt{a_0/r}`; the rebuilt Rydberg constant `atomic::R_inf_derived`$=m_ec\alpha^2/(2h)$; the finite-nucleus reduced-mass factor `reduced_mass_factor`$=m_{\rm nuc}/(m_e+m_{\rm nuc})$ and the isotope shifts it predicts; and the order of the infinite-nucleus approximation. No measured spectral line is loaded: the engine's own comparison with a line list (hydrogen within 12.5 ppm, hydrogen-like $Z\le30$ within 263 ppm) is engine-recorded and not re-run, because the dataset is not part of this instrument.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the reduced-mass factor equals $1/(1+m_e/m_{\rm nuc})$ for $m_{\rm nuc}=m_p,m_d,m_t,m_h$ and tends to 1 for a very heavy nucleus ($10^{6}m_p$) to $10^{-9}$ of $m_e/m_{\rm nuc}$ | $10^{-15}$ for the algebraic form |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | the ladder for $Z=1\ldots5$, $n=1\ldots10$: with $\mathrm{Om}_Z=v^2r/c^2$ from `bohr_velocity`, `bohr_radius`: $\mathrm{Om}_Z=Zr_e$; $z=\mathrm{Om}/r=(Z\alpha/n)^2$; $zk^2=1$ (identity of the definitions, reported as such); and the engine function `rotation_field_velocity` evaluated at the closed radius $r_{Zn}$ equals `bohr_velocity(Z,n)`$/\sqrt Z$, so it agrees with the ladder for $Z=1$ and differs by the factor $\sqrt Z$ for $Z>1$ (the function has no $Z$ argument) | relative $10^{-14}$ | yes — agreement for $Z>1$ would reject the registered finding |
| T2 | spectral scale. (a) `R_inf_derived`$/R_\infty=1$ to $10^{-9}$ and $\mathrm{Ry}=hcR_\infty/e$ to $10^{-9}$ (both **shared-input**: the stored CODATA $R_\infty$ and $\mathrm{Ry}$ are themselves computed from $\alpha,m_e,c,h$; they test the consistency of the stored set); (b) for hydrogen with $m_{\rm nuc}=m_p$ the two engine routes agree: `emission_wavelength_m(1,1,2,m_p)` equals $hc/(E_2-E_1)$ from `level_energy_eV(1,\cdot,m_p)` to $10^{-9}$, and likewise $n=2\to3$; (c) the leading-order wavelengths of Lyman-$\alpha$ and Balmer-$\alpha$ for hydrogen are printed (not compared with a measured value) and their ratio equals $5/27$ exactly (Rydberg combination, $\tfrac{5/36}{3/4}$ inverted) | as stated | yes |
| T3 | isotope shifts from one nuclear response. $\lambda_H/\lambda_D=\mu_D/\mu_H$ with $\mu=m_{\rm nuc}/(m_e+m_{\rm nuc})$ (exact); printed: the fractional shift and the Balmer-$\alpha$ shift in nm for H→D, H→T, D→T and for hydrogen-like helion ($Z=2$, $m_h$) against an infinite nucleus. The infinite-nucleus approximation $\mu\approx1-m_e/m_{\rm nuc}$ has error $(m_e/m_{\rm nuc})^2$: relative to that value, to $10^{-6}$ for $m_p,m_d,m_t,m_h$ | as stated | yes |
| T4 | order of the first omitted correction. $(Z\alpha/n)^2$ for $Z=1,n=1$ in ppm is printed; the engine's stated remainder (a movement-budget term of order $(Z\alpha)^2$) is therefore a relative size of this order and is not a numerical coefficient | reported only | — |

Reported, not criteria: wavelengths, shifts, ppm sizes.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch25_hydrogen_from_the_circulation_boundary`

## Record of run 1; correction of the second V1 line (2026-11-10)

Run 1 (`ch25_run1_output.txt`) met every T-criterion and the first V1 line, and failed the second V1 line ($6.1\times10^{-9}$ against $10^{-9}$). The line evaluates $1-\mu$ for a nucleus of mass $10^6m_p$, where $1-\mu\approx5.4\times10^{-10}$; the subtraction from 1 resolves that quantity only to about $2\times10^{-7}$ of itself in double precision, so the registered tolerance was unattainable by this construction. It is an instrument defect, not a finding on the object. The line is repaired with a nucleus of mass $10^3m_p$ ($m_e/m\approx5.4\times10^{-7}$, resolution about $2\times10^{-10}$) and the comparison of $(1-\mu)/(m_e/m)$ with its exact value $1/(1+m_e/m)$ at tolerance $10^{-8}$. Run 2 is the run of record.
