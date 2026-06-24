# QM06 — Discrete Spectra from Standing Wakes

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Why are atomic energy levels discrete? Standard QM imposes quantised action / boundary conditions on
ψ. SDT has no ψ. Can the **n-ladder** of energy levels be reproduced as **standing-wake boundary
conditions** on a bound vortex orbit — the convergence wake of the orbiting vortex must close on
itself (integer number of relay wavelengths around the path) or it destructively self-cancels?
Reproduce the hydrogen Rydberg/Balmer series and level degeneracies with **no quantised-action
postulate**, connecting to APS01 emissions and the PPT02 koppa-ladder picture of α.

## SDT mechanism & hypotheses

A vortex bound in an atom orbits at a least-resistance radius (PPT01 equilibrium). Its wake travels
with it and wraps the orbit. Only orbits whose circumference is an integer number of wake
wavelengths sustain a **standing wake**; all others self-destruct over many ticks. This is the SDT
content of "quantisation": not an action axiom, but a **resonance survival condition** on a real
relay field — the exact same closure logic as PPT02 (α = koppa of the H ground rung, k = 1/α = 137).

- **H1 (closure quantisation):** `2πr_n = n λ_n` with λ = h/p (QM01) ⇒ `m v r = nℏ` emerges as a
  **standing-wake** condition, not the Bohr postulate — same equation, native origin.
- **H2 (Rydberg from closure + occlusion balance):** combine closure with the PPT01 occlusion-vs-
  centripetal balance (the electropause, [[project_electropause_peff_derivation]]) ⇒
  `E_n = −Ry/n²`, Ry derived from `m_e, c, α` already in the engine.
- **H3 (lines = wake-mode transitions):** emission = a vortex dropping between standing-wake modes,
  radiating one wake pulse of `ΔE = hν` (APS01); Balmer/Lyman series and degeneracy g_n = n² recovered.

## Strategy

**Phase 1 — Standing-wake closure.** *Goal:* derive `2πr = nλ`. *Method:* propagate the orbital wake
tick-by-tick (FLM05) around a closed path; find which radii self-reinforce. *Success:* only integer-n
orbits survive ≥10⁴ ticks; non-integer decay — quantisation as **resonance survival**, no postulate.

**Phase 2 — Hydrogen ladder.** *Goal:* `E_n = −13.6/n² eV`. *Method:* closure + electropause balance
(PPT01). *Success:* Rydberg reproduced to <0.1% from `m_e, c, α`; r_n = n²a₀ native.

**Phase 3 — Spectral series.** *Goal:* Balmer/Lyman/Paschen. *Method:* `ΔE = E_n−E_m` → λ (APS01).
*Success:* Hα 656.3 nm, series limits, degeneracy g_n = n² all to <0.1%.

**Phase 4 — Beyond H (scope).** *Goal:* alkali quantum defect / fine structure direction. *Method:*
core-occlusion shift of the standing-wake radius. *Success:* quantum defect sign + rough magnitude;
flag fine structure OPEN (ties to QM07 handedness).

## Success criteria

- **PASS (A):** closure → n-ladder native; Rydberg + Balmer to <0.1% from engine constants, no action axiom.
- **QUALIFIED (C):** ladder reproduced but Ry leans on one flagged engine import (e.g. α as the input). (Expected.)
- **PENDING (D):** standing-wake closure shown but the energy formula only heuristic.
- **FAIL (F):** discreteness needs an imposed quantisation axiom. Report; relay-resonance picture failed.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 — only integer orbits survive | non-integer-n wakes self-cancel within ~10⁴ ticks | quantisation not a standing-wake fact |
| T2 — Rydberg native | E_n = −13.6 eV/n² to <0.1% from m_e,c,α | level structure not from closure+balance |
| T3 — series wavelengths | Hα 656.3 nm, g_n=n² degeneracy | wake-mode transition picture wrong |

## Dependencies

**Upstream:** APS01 (emissions/spectral ladder), PPT01 (vortex equilibrium), QM01 (λ=h/p wake).
**Downstream:** QM07 (fine structure = handedness split), molecular/band spectra.
**Related:** [[project_cq03_scroller]] (α = koppa of the H rung — same closure logic), [[project_electropause_peff_derivation]] (the balance that sets a₀).
