# CM08 — Material Koppa Density, Helical Wake and Flux Controls

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · INSTRUMENT NOT YET RUN  
**Date:** 2026-08-15

## Question

What changes, and what must not change, when lithium and uranium spheres are
compared at:

1. equal total inertial resistance (the same bulk mass / baryon count), and
2. equal geometric radius (the same volume)?

The instrument separates three ledgers:

- baryon count and baryon-to-volume density;
- the normalized \(r^{-3}\) rotational/helical wake kernel;
- conventional-equivalent magnetic flux for a declared circulating-charge
  control.

The third ledger is not inferred from bulk density. Actual material magnetism
requires electronic circulation and alignment data.

## Registered measured controls

- Lithium bulk density: \(534\,\mathrm{kg\,m^{-3}}\)
- Uranium bulk density: \(19\,100\,\mathrm{kg\,m^{-3}}\)
- Representative mass numbers: Li-7 and U-238

These values are local measured inputs in the investigation tool. They are not
added to `sdt::laws::measured`.

## Engine relations

\[
V=\frac43\pi R^3,\qquad
N_b\simeq\frac{\rho V}{m_p},\qquad
n_b=\frac{N_b}{V}
\]

\[
\kappa_{\rm body}=N_b\kappa_b,\qquad
\rho_\kappa=\frac{\kappa_{\rm body}}{V},\qquad
a(r)=\frac{c^2\kappa_{\rm body}}{r^2}.
\]

The \(m_p\) conversion neglects electron mass and nuclear mass defect at this
material-comparison fidelity. The approximation is printed in the assessment.

The normalized rotational wake uses the Law-VI \(r^{-3}\) exponent:

\[
a_{\rm wake}(r)
=c^2\kappa_{\rm body}\frac{R}{r^3}
f_{\rm align},
\quad
\phi=w\theta+\frac{2\pi z}{p}-\omega t.
\]

Its unit coefficient fixes a visualization normalization at \(r=R\); it is
not an absolute magnetic-amplitude derivation.

For a declared circular current loop,

\[
\Phi_B
=\pi k_e q_{\rm circ}\omega R/c^2,
\]

obtained from \(\mu_0=4\pi k_e/c^2\),
\(I=q_{\rm circ}\omega/(2\pi)\), and the loop-centre field. A comparison
control assigns one electron-equivalent circulation per atom at the same
\(\omega\) and alignment. This is a count control, not a claim about lithium
or uranium magnetic order.

## Registered gates

1. **C0 — equal mass.** For 1.000 kg spheres, lithium and uranium must have
   equal `koppa_total` and equal far-field acceleration to relative
   \(10^{-12}\).
2. **C1 — equal mass density contrast.** The uranium/lithium baryon-density
   ratio must equal \(19100/534\) to relative \(10^{-12}\).
3. **C2 — equal volume.** At radius 0.050 m, the uranium/lithium total koppa
   and far-field acceleration ratios must equal \(19100/534\) to relative
   \(10^{-12}\).
4. **C3 — surface response.** At equal mass, the surface-acceleration ratio
   must equal \((R_{\rm Li}/R_{\rm U})^2\) to relative \(10^{-12}\).
5. **C4 — wake scaling.** Doubling observation radius must divide normalized
   rotational-wake magnitude by eight to relative \(10^{-12}\).
6. **C5 — flux count control.** With one electron-equivalent loop per atom
   and common \(\omega\), equal-volume U/Li flux must equal the atom-count
   ratio times the common-radius ratio; equal-mass flux must equal the
   atom-count ratio times \(R_{\rm U}/R_{\rm Li}\), each to relative
   \(10^{-12}\).
7. **C6 — ledger separation.** Setting alignment to zero must make both the
   rotational wake and magnetic flux zero while leaving `koppa_total`,
   baryon density and far-field acceleration unchanged.

## Rejection criteria

The model is rejected if equal baryon count changes the far-field monopole,
if density is used to infer magnetic alignment, if the normalized wake is
reported as an absolute measured field, or if any element-specific coefficient
is fitted to the comparison.
