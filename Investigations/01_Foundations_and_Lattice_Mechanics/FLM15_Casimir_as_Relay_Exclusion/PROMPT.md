# FLM15 — The Casimir Push from Relay Exclusion

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B98). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Two conducting plates a micron apart are pushed together with pressure ∝ 1/d⁴ — the Casimir
result, measured to ~1% (Lamoreaux and successors). The prevailing account books it as
vacuum-energy mode exclusion.

## SDT footing

This should be the most SDT-shaped phenomenon in the catalogue: it is occlusion with plates.
The medium relays in all wavelengths; between close conductors the long relay modes cannot
run (the plates interrupt them), so fewer modes push outward from the gap than push inward
from outside — a literal shadow force, the same bookkeeping as L4 with mode-counting instead
of solid angle. TD06's counted mode density (0.003% against 8πν²/c³) is the exact instrument
this needs: count the modes the gap admits, subtract, price the difference with the
established ε-bridge, and the 1/d⁴ with its π²/240 coefficient either falls out of the
counting or it does not. Existing corpus: TD06 (mode counting, validated), L3/L4 (the push),
SAR02.

## Pre-registration skeleton (complete before any tool)

- Question: does gap-mode counting minus free counting, priced by the Law-I bridge, produce
  F/A = π²ℏc/240d⁴ — coefficient included — with nothing fitted?
- Rejection criterion (populated): exponent ≠ 4, or coefficient off beyond tolerance (the
  measured 1% leaves no room).
- Anchors: Lamoreaux-class measurements; the standard coefficient.
- Tolerance: exponent exact; coefficient ±5% opening, ±1% target.

## Benchmark linkage

Catalogue row B98 · the highest-probability near-term win in the catalogue: the instrument
already exists and is validated (TD06).

## Pre-registration (2026-10-03, before the instrument exists)

**Method note.** Rounds are registered as they are designed. Round 1 is the seed read
literally. Round 2 is registered now as conditional on Round 1 meeting its rejection
criterion, so that its design is fixed before Round 1's numbers are produced. Any further
round receives its own dated block; every round stays in the attempt ledger in
`FLM15_ASSESSMENT.md`, including those that fail.

**Route.** Mode counting between ideal parallel plates: integer k_z = nπ/d (two polarisations
for n ≥ 1, one for n = 0), continuous transverse wavevector, minus the same counting for free
space over the same region. Constants from `sdt::laws::measured` (ℏ, c, k_B, T_CMB, h).

**Instrument validation (before any physics round).**
(V1) Poisson summation: Σₙ e^(−π n² t) = t^(−1/2) Σₖ e^(−π k² /t) at two values of t, 1e-13
relative — checks the sum-minus-integral machinery on a case with an exact answer.
(V2) The closed form g(q) = (1/2π)∫_q^∞ s² e^(−λs) ds against numerical quadrature at three
q, 1e-9 relative.
(V3) The counted Bose integral ∫ s³ n̄ ds = (kT/ħc)⁴ π⁴/15 against quadrature, 1e-8 relative
(validates the thermal occupation integral used in Round 1).

**Round 1 (literal seed).** Price each gap mode with TD06's counted occupation at the
engine's vacuum temperature T_CMB, using the free energy kT ln(1 − e^(−ħω/kT)) per mode.
- *Predicted before running:* the n ≥ 1 gap modes sit at ħω ≥ πħc/d (0.31 eV at d = 1 µm)
  against k_BT_CMB = 0.23 meV, so their occupation is below 1e-1000. Only the n = 0 mode is
  populated and it is d-independent. The net force is the exterior radiation pressure
  u_CMB/3 = (π²/45)(k_BT)⁴/(ħc)³ ≈ 1.39e-14 Pa, independent of d (fitted exponent 0 ± 0.001),
  about 1e-11 of the ideal Casimir pressure at 1 µm.
- *Rejection criterion (the seed's own, populated by the prediction above):* exponent ≠ 4 or
  coefficient outside ±5% of π²ħc/240.
- Anchor: ideal-plate coefficient π²ħc/240 (the standard form). Measured corroboration:
  Mohideen and Roy, *Phys. Rev. Lett.* **81**, 4549 (1998), sphere-plate, 0.1–0.9 µm,
  about 1% rms agreement with theory including finite conductivity, roughness and
  temperature corrections. That agreement tests the corrected force, not the ideal formula
  directly; this is a stated limit of the anchor.

**Round 2 (conditional on Round 1's rejection criterion being met).** Question: which
vacuum occupation spectrum does the measured force require, and which part of it do counting
and the SDT scale-free influx premise (no characteristic length) supply?
- Price each mode a·ħω with a independent of ω (scale-free). Compute the d-dependent part of
  the sum-minus-integral with an exponential regulator e^(−λs), λ/d = 0.08, 0.06, 0.04, 0.03,
  0.02, Richardson-extrapolated to λ → 0.
- *Predicted before running:* ΔE/A = −a π² ħc /(360 d³), so P = −a π²ħc/(120 d⁴); exponent
  exactly 4 for any constant a; coefficient equals the ideal value only at a = 1/2.
  By dimensional analysis a price ∝ ω^(1+s) gives exponent 4 + s.
- *Rejection criterion:* the extrapolated coefficient departs from π²/360 per unit a by more
  than 1e-6 relative (an instrument-level criterion), or the fitted exponent departs from 4
  by more than 1e-6.
- *Constraint recorded from the anchor:* a = 0.500 ± 0.005 and |s| ≲ 0.005, from 1% over a
  factor 9 in d.
- *Candidates for a, registered before scoring (look-elsewhere count = 3):* a = 1/2 (zero-point
  quantum, a prohibited input as a derivation, recorded as the rival form); a = 1/2 from the
  720-degree double cover of PPT17's Bohr-seat tube (underived hypothesis, recorded as such);
  a = 1 (one full tick per mode). Only the measurement discriminates among them; none is
  derived by this run.
- *Report-only:* the energy density of an a = 1/2 floor extending to the plates' transparency
  frequency (3×10¹⁵ Hz) against Law I's P_conv.

**Labels.** Round 1: COMPUTED, exclusion of the literal route. Round 2: the exponent is
DERIVED from the scale-free premise by counting; the coefficient is CALIBRATED(1) if a is
set to the measured value, and is not claimed as derived.

---

## Audit correction 2026-10-05 (record / status)

**Finding:** Two investigation folders carry the id FLM15 (Influx_Phase_Resistance_Ratio and Casimir_as_Relay_Exclusion), so the engine's "FLM15 resistance kernel" reference is ambiguous.

**Correction:** Rename the Casimir folder (propose-only) and update the catalogue row B98.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
