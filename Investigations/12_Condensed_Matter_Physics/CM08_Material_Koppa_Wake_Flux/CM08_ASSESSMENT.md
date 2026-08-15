# CM08 Assessment — Material Koppa Density, Wake and Flux

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-15  
**Assessment:** VALIDATED MATERIAL LEDGER

## Result

The C0–C6 controls passed. The code now keeps three quantities separate:

1. integrated baryon/koppa source strength;
2. baryon and koppa density per volume, including the normalized \(r^{-3}\)
   helical-wake kernel;
3. conventional-equivalent magnetic flux from a separately declared
   circulating-charge and alignment control.

Density does not set magnetic alignment.

## Lithium and uranium spheres

Using measured bulk densities 534 and 19,100 kg/m³:

### Equal total inertial resistance — 1.000 kg

- Li radius: 0.07646394684 m
- U radius: 0.02320737435 m
- Both carry the same approximate baryon count and
  \(\kappa_{\rm total}=7.426160049\times10^{-28}\) m.
- Both give the same far-field acceleration at 10 m:
  \(6.674299802\times10^{-13}\) m/s².
- U has 35.76779026 times the baryon density.
- U has 10.85578933 times the surface response because its radius is smaller.

### Equal radius — 0.050 m

- Li total resistance: 0.2796017462 kg
- U total resistance: 10.00073661 kg
- U has 35.76779026 times the baryon count, total koppa and far-field
  acceleration.

Thus equal total baryon count fixes the far monopole, while compression changes
the source density, boundary response and rotational-wake geometry. Equal
volume instead admits the density ratio directly into the integrated source.

## Helical wake

The normalized rotational kernel passed the \(r^{-3}\) control: doubling the
observation radius reduced the magnitude by exactly eight within floating-point
tolerance. The exponent comes from the canonical Law-VI rotational-wake
hierarchy. Its unit surface normalization is a visualization convention, not
an absolute magnetic-amplitude prediction.

## Magnetic flux control

For one electron-equivalent loop per atom at a common angular rate and full
declared alignment:

- equal-mass U/Li loop-flux ratio: 0.008926688487;
- equal-radius U/Li loop-flux ratio: 1.051993831.

These are count controls. They are not predictions of bulk lithium or uranium
magnetism: actual values require the material's electronic circulation,
domain structure, temperature and alignment.

## Scope and provenance

The conversion \(N_b\simeq\rho V/m_p\) neglects electron mass and nuclear
binding defect. It is sufficient for the registered density contrast but not
for precision metrology.

`bridge::koppa_per_baryon` contains the measured Planck length; under
conventional metrology that length encodes \(G\). The no-\(G\)/no-\(M\) call
graph is therefore an SDT-native re-expression with this provenance risk
disclosed, not independent evidence for the force magnitude.
