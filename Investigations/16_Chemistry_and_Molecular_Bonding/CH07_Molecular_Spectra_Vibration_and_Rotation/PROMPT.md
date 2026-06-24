# CH07 — Molecular Spectra (Vibration & Rotation)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Atomic emission is k-ladder rung structure (APS01); molecules add two new spectral channels.
**Can IR / Raman vibrational lines be derived as oscillations of the bond-wake (the shared
electropause flexing along its axis), and microwave rotational lines as whole-molecule rotation of
the wake field — recovering the CO stretch ~2143 cm⁻¹, the CO rotational constant B, and the
ν ∝ √(k/μ) mass dependence — with no normal-mode wavefunctions and no rigid-rotor eigenfunctions,
only wake mechanics?** The spectrum is the bond-wake's mechanical resonance, not a quantum
eigenstate ladder.

## SDT mechanism & hypotheses

A shared electropause (CH01) is a pressure-balance surface with a restoring stiffness: displace
the two nuclei along the bond and the occlusion balance pushes back — a harmonic oscillation whose
frequency is set by the electropause stiffness k and the reduced nuclear mass μ. That oscillation
*is* the vibrational line. Rotating the whole wake field about the centre of mass costs movement
budget ([[law_V]]) quantised by the wake winding (PPT06/APS04), giving evenly spaced rotational
lines with spacing 2B. The quantisation that makes lines discrete is the same wake-winding
quantisation that quantises atomic rungs — one mechanism, three channels (electronic/vib/rot).

- **H1 (vibration = bond-wake stiffness):** ω = √(k_electropause/μ); recover the CO/HCl/H₂ stretch
  frequencies from electropause stiffness (from CH01 well curvature) and reduced mass.
- **H2 (rotation = wake-field rotation):** rotational constant B = ħ/(4πcI) emerges from
  wake-winding-quantised whole-molecule rotation; recover CO/HCl B and the 2B line spacing.
- **H3 (one quantisation):** the discreteness of vib + rot lines is the PPT06/APS04 wake-winding
  quantisation, the same that sets atomic rungs (APS01) — no separate quantum postulate per channel.

## Strategy

**Phase 1 — Vibration.** *Goal:* stretch frequencies. *Method:* electropause well curvature (CH01)
→ k; ω=√(k/μ). *Success:* CO 2143 cm⁻¹, HCl 2886 cm⁻¹, H₂ 4401 cm⁻¹ within ~10%; correct √(k/μ)
ordering and isotope shift (HCl→DCl).

**Phase 2 — Rotation.** *Goal:* B and line spacing. *Method:* wake-winding-quantised rotation of
moment of inertia I=μR². *Success:* CO B≈1.93 cm⁻¹, HCl B≈10.6 cm⁻¹ within ~10%; even 2B spacing.

**Phase 3 — Unification.** *Goal:* one quantiser. *Method:* show vib + rot discreteness = PPT06/APS04
winding. *Success:* the same winding integer indexes all three channels; no per-channel postulate.

**Phase 4 — Falsifier.** *Goal:* a novel line. *Method:* predict an un-fit frequency or B (e.g. N₂,
CO₂ bend, or an isotopologue shift) from stiffness + mass alone.

## Success criteria

- **PASS (A):** vib frequencies + rot B + isotope shifts from electropause stiffness & mass under
  one winding quantiser, plus a correct novel line.
- **QUALIFIED (C):** CO/HCl vib & rot within ~10% with the stiffness scale CALIBRATED(1).
  *(Expected landing.)*
- **PENDING (D):** vibrations recovered; rotation only schematic.
- **FAIL (F):** spectra require normal-mode / rigid-rotor wavefunctions.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Vib = bond-wake oscillation | CO 2143 cm⁻¹, ν∝√(k/μ), isotope shift | vibration needs normal-mode ψ |
| Rot = wake-field rotation | CO B≈1.93 cm⁻¹, even 2B spacing | rotation needs rigid-rotor ψ |
| One quantiser | one winding integer indexes all 3 channels | each channel needs its own postulate |

## Dependencies

**Upstream:** CH01 (electropause stiffness/well), APS01 (k-ladder atomic spectra it extends),
PPT06/APS04 (wake winding = the quantiser). **Downstream:** spectroscopic identification, astro
molecular lines. **Related:** CM04 (phonons — lattice wake oscillation is the solid-state analogue).
