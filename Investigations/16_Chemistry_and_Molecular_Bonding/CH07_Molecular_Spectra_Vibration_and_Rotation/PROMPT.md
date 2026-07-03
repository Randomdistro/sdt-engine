# CH07 — Molecular Spectra (Vibration & Rotation)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether IR/Raman vibrational lines can be derived as oscillations of the bond-wake (the shared electropause flexing along its axis) and microwave rotational lines as whole-molecule rotation of the wake field — recovering the CO stretch ~2143 cm⁻¹, the CO rotational constant B, and the ν∝√(k/μ) mass dependence — with NO normal-mode wavefunctions and NO rigid-rotor eigenfunctions, only wake mechanics.
2. **Why does it matter?** — The spectrum is the bond-wake's mechanical resonance, not a quantum eigenstate ladder; it EXTENDS atomic emission ([[project_cq03_scroller]] APS01) to two new channels, CONSUMES the CH01 electropause stiffness, and TIES the CM04 phonon picture — all unified under one wake-winding quantiser (PPT06/APS04).
3. **How will we find out?** — Gated phases in §④: vib frequencies from the CH01 well curvature → k, then ω=√(k/μ); rot B from wake-winding-quantised whole-molecule rotation; demonstrate one winding integer indexes all three channels; then a novel un-fit line. Native wake mechanics BEFORE any per-channel quantum postulate or `atomic::`/rival import.
4. **What would prove us wrong?** — §⑧ numeric kill triggers: spectra require normal-mode / rigid-rotor wavefunctions, or each channel needs its own postulate.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is getting the stiffness **k** from the CH01 electropause **WELL CURVATURE** (d²U/dR² at R_e) — an INDEPENDENT quantity — and predicting ν=√(k/μ) OUT. The harmonic-oscillator formula ν∝√(k/μ) is itself classical mechanics and a near-IDENTITY, so it carries no gradeable content on its own. The gradeable content is (a) that the SDT well supplies the *right* k, and (b) that ONE wake-winding quantiser does all three channels.

> **Using ν=√(k/μ) with k read back off the measured frequency is circular — k MUST come from the CH01 well curvature independently, or the grade caps at C.**

One stiffness scale MAY be CALIBRATED(1); declare it explicitly. The √(k/μ) ORDERING across CO/HCl/H₂ and the HCl→DCl isotope shift must be PREDICTED (not back-fit), and the single-quantiser claim (Phase 3) must be DEMONSTRATED, not asserted.

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

| Test | Predicted outcome | If FAIL (numeric kill trigger) |
|------|-------------------|---------|
| Vib = bond-wake oscillation | CO 2143 cm⁻¹, ν∝√(k/μ), HCl→DCl isotope shift | CO/HCl/H₂ stretch off >10% with k from the CH01 well, or √(k/μ) ordering wrong ⇒ vibration needs normal-mode ψ |
| Rot = wake-field rotation | CO B≈1.93 cm⁻¹, even 2B spacing | B off >10% or spacing not even 2B ⇒ rotation needs rigid-rotor ψ |
| One quantiser | one winding integer indexes all 3 channels | channels need separate quantisers ⇒ each channel needs its own postulate |
| Firewall: k from CH01 well, not back-solved | k = d²U/dR² at R_e (independent), ν predicted OUT | k can only be recovered by back-solving from the measured ν ⇒ tautology, grade caps at C |

## Dependencies

**Upstream:** CH01 (electropause stiffness/well), APS01 (k-ladder atomic spectra it extends),
PPT06/APS04 (wake winding = the quantiser). **Downstream:** spectroscopic identification, astro
molecular lines. **Related:** CM04 (phonons — lattice wake oscillation is the solid-state analogue).
---

## Questions This Opens *(generative — log new ones in `CH07_VERDICT.md`)*

1. Does the anharmonicity (the Morse-like bend, overtone spacing) come from the SHAPE of the CH01 electropause well natively, or must it be added by hand?
2. Does the SAME well curvature predict bond length, bond energy AND vibration — one curve, three observables — tying CH01 to CH07?
3. Is the winding quantiser that sets B the SAME integer ladder as the APS01 atomic rungs — one quantiser spanning atoms and molecules?
4. Does vibration-rotation coupling (centrifugal distortion) fall out of the flexing wake, or does it require a separate correction term?
5. Are the selection rules (IR-active vs Raman-active) a wake-symmetry consequence rather than a transition-dipole rule?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 CO 2143 / HCl 2886 / H2 4401 cm⁻¹ within 10%, correct √(k/μ) ordering + HCl→DCl isotope shift · P2 CO B≈1.93 / HCl B≈10.6 cm⁻¹ within 10%, even 2B spacing · P3 one winding integer indexes all three channels (no per-channel postulate) · P4 novel line (N2 / CO2 bend / isotopologue) within committed tol
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| k from well curvature gives wrong ν | re-examine CH01 well shape (anharmonicity / electropause stiffness) | **OPEN** the vib link | back-solve k from measured ν, call it predicted |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · reading k back off the measured frequency (circular) instead of from CH01 well curvature · claiming NATIVE on ν=√(k/μ) alone (it is classical) · a separate quantum postulate per channel.

---

*CH07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
