# NSEQ17 — Light-nucleus wake mesh (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**Deferred:** a calibrated wake mesh with 8–9 parameters per nucleus against 2–3 observables. A held-out observable per nucleus is required before a re-run means anything.

## 2. New data and what it teaches (2026-10-10 to 2026-10-12)
- **Confirmed by running the engine (2026-10-10):** `fitLightNucleus` returns CALIBRATED(8) for ²H and CALIBRATED(9) for ³H and ³He, with **zero residuals** on B, μ (and Q for ²H). An exact fit with more parameters than targets carries no information.
- No derived light nucleus exists anywhere in the construction (NP17 reset). The NP17 round-2 O1 rule is the route to one.

## 3. Next round (registered order)
1. Re-register with **one held-out observable per nucleus**, not used in the fit:
   - the radius for ³H and ³He (IAEA: 1.759 and 1.966 fm);
   - the radius for ²H (2.142 fm), with Q kept out of the fit for ²H.
2. A fresh calibration, then the held-out comparison once, with cascade bands.
3. Parameter count reduced to at most the number of fitted observables. Otherwise the result is labelled not identifiable.

## Prohibitions
- No census over candidate predictors.
- Grammar counts are not evidence (NP24).
- No data substitution without a label.
- Release is read, never edited (proposals only).
- The word "charge" is not used.

---

## Previous specification (kept as written)

# NSEQ17 — Light-Nucleus Wake-Mesh Calibration

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED before instrumentation  
**Scope:** H-2, H-3, and He-3 only

## Question

Can independently calibrated, phase-locked assemblies of the canonical four-circuit
nucleon wake reproduce the measured mass defect and magnetic dipole moment of H-2,
H-3, and He-3 while retaining closed flow, low numerical divergence, and the
constitutional no-neutron–neutron-contact rule?

H-2 additionally calibrates its electric quadrupole moment. Charge radius is excluded.
Spin/parity is not a fit input; rotational periodicity and handedness are reported as a
diagnostic with no promotion unless a native mapping is supplied.

## Measured inputs

All masses and magnetic moments come from `sdt::laws::measured`, updated to the
CODATA 2022 adjustment. Binding energies are computed from the constituent and bound
nuclear masses, not entered independently.

The H-2 electric quadrupole target is:

`Q_d = 0.285699 fm²`

Source: Pachucki, *Hyperfine Structure of the First Rotational Level in H2, D2 and HD
Molecules and the Deuteron Quadrupole Moment* (2020), Eq. 24. This is an OBSERVED
spectroscopy input, not a CODATA constant.

## Fixed construction

1. Every nucleon is one complete canonical `(4,3)` four-tour circulation.
2. Every nucleon carries four closed wake circuits:
   `crown → convergence → throat+poloidal split → tail → skirt → exterior → crown`.
3. Composite flow is formed by rigidly transforming complete closed circuits.
4. `U = curl(A)` is retained. No source or sink is added at a mesh interface.
5. H-3 is `n-p-n`; its neutron wakes may not contact one another.
6. He-3 is `p-n-p`.
7. Self-energy is excluded from binding. Only pairwise wake cross-terms enter.

## Calibration parameters and bounds

H-2 uses six fitted quantities:

- centre separation: `[1.40, 2.60] Rp`;
- relative tilt: `[45°, 135°]`;
- toroidal phase: `[0, 2π)`;
- poloidal roll phase: `[0, 2π)`;
- energy bridge: `[0.01, 100] MeV / overlap-unit`;
- magnetic bridge: `[-20, 20] μN / geometric-moment-unit`.

H-3 and He-3 each use seven fitted quantities:

- common centre separation: `[1.40, 2.80] Rp`;
- outer opening angle: `[120°, 180°]`;
- relative tilt: `[45°, 135°]`;
- toroidal phase: `[0, 2π)`;
- poloidal roll phase: `[0, 2π)`;
- the same energy-bridge bounds;
- the same magnetic-bridge bounds.

Each isotope is calibrated independently, as directed. A deterministic bounded
coordinate search with frozen initial seeds and step schedule is used. At each pose,
the two dimensional bridge coefficients are profiled analytically and rejected if
outside their registered bounds.

## Observables

### Binding

On a fixed integration stencil:

`I_mesh = -Σ_(i<j) ∫ U_i · U_j dV`

with self terms omitted. The calibrated binding is:

`B_model = K_E I_mesh`.

### Magnetic dipole

Overlap modifies the signed circuit ledger while preserving split/rejoin closure.
The effective moment is evaluated by:

1. `μ_integral = 1/2 ∫ r × J_eff dV`;
2. an exterior axial/equatorial `1/r³` dipole fit.

The dimensional bridge `K_μ` is visible in the ledger. No final-field normalisation is
permitted after the fit.

### H-2 electric quadrupole

The trace-free axial second moment of the normalized proton circulation is evaluated
directly in `fm²`:

`Q_zz = ∫ ρ_p (3z²-r²) dV / ∫ρ_p dV`.

No charge-radius target enters.

## Registered tolerances and rejection criteria

- split and rejoin residual: `≤ 1e-12`;
- relative numerical divergence: `≤ 1%`;
- magnetic integral/far-field disagreement: `≤ 5%`;
- fitted target relative residual: `≤ 1e-4`;
- deterministic rerun parameter difference: `≤ 1e-12`;
- H-3 neutron–neutron overlap: `< 10%` of its weaker p–n overlap;
- no fitted coefficient may sit within `1e-6` of a registered bound.

The calibration is rejected if any conservation, dimensional, route-agreement,
determinism, coefficient-bound, or neutron–neutron criterion is not met.

## Classification

All target-matched values are `CALIBRATED(n)`, where `n` is the isotope parameter count
above. Wake topology and conservation checks are `COMPUTED`. Measured inputs are
`MEASURED-INPUT` or `OBSERVED` as stated. Spin/parity remains `PENDING`.

---

## Audit correction 2026-10-05 (gating)

**Finding:** Each of H-2, H-3 and He-3 is calibrated with 8–9 parameters to 2–3 observables (binding, moment, quadrupole) and then "reproduces" them to nine digits, which any under-determined fit does, and the prompt has no numeric gate.

**Correction:** Hold out at least one observable per nucleus (for example the quadrupole or radius) and gate the prediction on that.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
