# CM08 — Material koppa and wake flux (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**VERIFICATION (identities); physics gate owed (G2).** Gates C0–C6 compare formulas with themselves (Ѻ = N_b Ѻ_b; 1/R² surface acceleration; r⁻³ kernel; flux ∝ count × radius; alignment zero).

## 2. What the errors and new data teach
- The engine-side material Ѻ is an identity. Any physics needs electronic circulation and alignment. PPT18 (2026-10-12) and the APS ladders are where native circulation rules are being built.

## 3. Next round (registered order)
1. A native circulation and alignment rule for a material, stated first.
2. A numeric physics gate: measured magnetisation or susceptibility ratios (e.g. Li against U), cached with provenance, compared once with cascade bands.

## Prohibitions
- No census over candidate forms (2026-10-07 rule).
- No imported source models (PREM, polytropes, quantum-number labelling) as native tests.
- No G or GM.
- The word "charge" is not used.

---

## Previous specification (kept as written)

# CM08 — Material Koppa Density, Helical Wake and Flux Controls

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · INSTRUMENT RUN — assessment VALIDATED MATERIAL LEDGER (controls C0–C6 passed; the controls are VERIFICATION, there is no physics gate yet) (see CM08_ASSESSMENT.md) [status line corrected 2026-10-05]  
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

---

## Audit correction 2026-10-05 (record / status)

**Finding:** The status line reads "INSTRUMENT NOT YET RUN" although controls C0–C6 passed and results exist, and the equal-mass and equal-size flux controls compare a value to the same formula (relative error 0 and 2e-16).

**Correction:** Update the status and label the controls VERIFICATION, with a numeric physics gate added.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
