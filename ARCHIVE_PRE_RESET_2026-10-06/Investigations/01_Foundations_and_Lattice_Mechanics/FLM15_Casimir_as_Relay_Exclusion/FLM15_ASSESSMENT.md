# FLM15 Assessment — the Casimir push from relay exclusion

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `flm15_casimir_counting.cpp`<br>
**Stdout:** `flm15_results.txt`<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)"; run record `RUN_LOG.md`

## Status

`FLM15_LITERAL_ROUTE_EXCLUDED__FLOOR_SPECIFIED`

- Round 1 (the seed read literally) is excluded: the rejection criterion was met by 11 orders of magnitude.
- Round 2 isolates what any SDT account of the force has to supply. Counting supplies the geometry; the occupation per mode is outstanding.

## Attempt ledger

| Round | Route | Outcome |
|---|---|---|
| 1 | Gap-mode counting, TD06 counted occupation at T_CMB, ε = hν | Excluded. d-independent pressure 1.39e-14 Pa |
| 2 | Same counting, scale-free price a·ħω per mode, any constant a | Geometry derived. Exponent 4 and π²/360 per unit a; a not supplied |
| 3 | not run | Discriminating tests of a floor hypothesis, listed below |

## Instrument validation

Four known-answer checks passed before any physics round: Poisson summation of the Gaussian
theta series to 1e-13 (V1); the closed-form mode kernel against quadrature to 1e-9 (V2); the
counted Bose integral against π⁴/15 to 1e-8 (V3); and the direct sum-minus-integral against its
Poisson-dual series at three cutoffs to 1e-8 (V4, added after the fault recorded in `RUN_LOG.md`).

## Round 1 — result and failure analysis

At T_CMB = 2.7255 K the thermal energy is k_BT = 0.235 meV. The lowest gap mode with k_z ≠ 0
sits at ħω = πħc/d, 0.31 eV at d = 1 µm, so its counted occupation is of order 10^(−1146). Only the
n = 0 mode is populated and it does not depend on d. What remains is the free-space term:

|P| = (π²/45)(k_BT)⁴/(ħc)³ = u_CMB/3 = **1.3916e-14 Pa**, independent of d (fitted exponent
0.000000), against the ideal-plate pressure 1.30e-3 Pa at 1 µm (ratio 1.07e-11).

This is the exterior radiation pressure on a gap that is nearly empty of thermal quanta. It is a
real effect of the counted spectrum and it is not a Casimir force: wrong exponent, wrong
magnitude, and it does not grow as the plates approach.

**What the failure isolates.** The seed priced each mode "with the established ε-bridge".
ε = hν fixes the size of one quantum. It does not say how many quanta occupy a mode, and TD06's
counted occupation at the engine's temperature says: essentially none above 10⁻³ eV. The
sentence "count the modes the gap admits, subtract, price the difference" therefore has two
independent ingredients, one geometric and one about occupation, and Round 1 shows that the
occupation supplied by T_CMB cannot carry the measured force.

## Round 2 — what counting does supply

Pricing every mode at a·ħω with a independent of ω, the sum over gap modes minus the free-space
integral is, per unit area,

ΔE/A = −a · π²ħc / (360 d³),  P = −a · π²ħc / (120 d⁴).

| Quantity | Result | Route |
|---|---|---|
| coefficient per unit a | −0.027415567 vs −π²/360 = −0.027415568 (4e-8) | direct sum + Richardson in λ² |
| same, at λ/d = 0.08 … 0.02 | agrees to 1.4e-8 or better | Poisson-dual series, independent |
| exponent | 4 exactly | scale-free price; energy per area scales as d⁻³ |
| a = 1/4, 1/2, 1 | P/P_ideal = 0.5, 1, 2 | follows from the coefficient |

Two routes reach the coefficient and agree to better than the pre-registered 1e-6 gate. The
exponent is a consequence of the premise that the price carries no characteristic length: a
price ∝ ω^(1+s) gives d^−(4+s) by dimensional analysis. That premise is SDT's own (the influx is
scale-free; every shell contributes equally). In that sense the exponent 4 is derived, not
assumed.

The amplitude is not derived. Constraint from the anchor (Mohideen and Roy 1998, about 1% rms
over 0.1–0.9 µm, a factor 9 in d): a = 0.500 ± 0.005 and |s| ≲ 0.005. Setting a to the
measured value makes the coefficient CALIBRATED(1).

**Capacity check (report-only).** A floor of a = 1/2 extending to a plate-transparency
frequency of 3e15 Hz carries 6.3e3 J/m³, about 2.5e-45 of Law I's P_conv. The floor does not
strain the engine's relay pressure; the engine also does not generate it.

**Finite cutoff (report-only).** With a cutoff at the skin-depth scale (22 nm) the local exponent
is 3.77, 3.97, 3.998, 3.9997 at d = 0.1, 0.3, 1, 3 µm. The departure from 4 at 0.1 µm is the
size of the finite-conductivity correction that the 1998 experiment had to include, so a
cutoff-free comparison is only meaningful for d ≳ 1 µm.

## Candidates for a (registered before scoring; look-elsewhere count 3)

| Candidate | Status |
|---|---|
| a = 1/2 as the zero-point quantum of each mode | Reproduces the measured value. It enters as an input borrowed from the standard account; recorded as the rival form, not as a derivation |
| a = 1/2 from the 720° double cover of the Bohr-seat tube (PPT17) | Reproduces the measured value. No derivation exists; the number was available before the hypothesis, so it is a retrodiction |
| a = 1 (one full tick per mode) | Excluded: the force would be twice the measured value, about 100σ at 1% |

## Limitations

1. The anchor for the coefficient is the ideal-plate formula. The measured force agrees with
   theory only after finite-conductivity, roughness and temperature corrections, so the 1%
   figure constrains the corrected theory, not the ideal one directly. Its transcription here is
   from a secondary summary; the primary paper was not retrieved.
2. The route assumes ideal reflecting plates. SDT's own picture is that plates interrupt relay
   modes; no relay-transparency model exists, so the ideal limit cannot be tested against real
   materials here.
3. The result does not distinguish the SDT floor from the standard zero-point account:
   identical counting gives identical numbers. Discrimination needs an observable on which they differ.

## Alternatives considered, not yet run (Round 3 candidates)

- **Same factor, second observable.** If a = 1/2 is a property of relay modes and not of the
  Casimir geometry, the same half quantum should enter the self-interaction that PPT12 prices
  (the α/2π term of g − 2). A derivation of a from the wake self-drafting integral there would
  fix a here without a further parameter. This links FLM15 to PPT12 and is the most direct route
  to removing the calibration.
- **Plate material dependence.** A relay-occlusion picture predicts the force follows relay
  transparency, not electromagnetic reflectivity. Measured forces against material and
  thickness (including thin and partially transparent films) are a differentiating dataset; none
  is cached.
- **Thermal sector.** With occupation ⟨n⟩ + a, the thermal correction is the same as the
  standard result. It does not discriminate, so it is not a priority.

## Open

- Derivation of a (or of its absence): the occupation of a relay mode at zero temperature.
- Primary Mohideen–Roy and Lamoreaux data in `Datasets/` with a manifest row.
- Whether TD06's counted occupation should be restated with an explicit zero-temperature floor.
  This is a change to an existing investigation's framing and is not made here.
