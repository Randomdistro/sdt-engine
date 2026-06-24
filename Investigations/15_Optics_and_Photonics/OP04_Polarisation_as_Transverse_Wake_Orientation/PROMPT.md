# OP04 — Polarisation as Transverse Wake Orientation

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

In SDT light is an emission with a real **transverse** structure — the relay impulse displaces the
lattice sideways as it advances (GOM06 transverse channel), and that displacement has an
orientation and a handedness (EMC03 ± redirection). **Can linear, circular, and elliptical
polarisation, Malus's law `I = I₀cos²θ`, optical activity (rotation of the plane), and
birefringence all be reproduced as the transverse orientation/handedness of the emission's wake —
with no photon spin operator and no Jones-matrix postulate, those being the targets?** Polarisation
becomes a geometric property of how the relay impulse is oriented in the plane perpendicular to its
travel, and a polariser is a lattice that only re-relays one transverse orientation.

## SDT mechanism & hypotheses

The emission carries a transverse displacement vector (linear) or a rotating one (circular,
handedness from EMC03). A polariser is anisotropic closure: it relays the projection of the
transverse displacement onto its pass-axis and dumps the orthogonal component.

- **H1 (linear = fixed transverse orientation):** Malus follows from projecting the transverse
  displacement amplitude onto the pass-axis, `A→A cosθ`, so `I ∝ cos²θ` — geometry, zero fit.
- **H2 (circular = handedness):** left/right circular = the two EMC03 handednesses of the rotating
  transverse wake; linear = equal superposition; the quarter-wave plate is a closure-anisotropic
  relay that retards one transverse axis by a quarter relay-wavelength.
- **H3 (optical activity = chiral lattice):** a handed (chiral) medium relays the two handednesses
  at slightly different `c_local`, rotating the linear plane by `Δφ ∝ (n_L−n_R)L` — same closure
  mechanism as OP01, now handedness-split. Birefringence = orientation-split `n`.

## Strategy

**Phase 1 — Transverse state algebra.** *Goal:* a native description of polarisation states from the
transverse displacement vector. *Method:* GOM06 transverse channel + EMC03 handedness. *Success:*
linear/circular/elliptical states represented without importing Jones calculus (recover it as a limit).

**Phase 2 — Malus.** *Goal:* `I=I₀cos²θ`. *Method:* project displacement onto polariser pass-axis.
*Success:* `cos²θ` exact; crossed-polariser extinction and the three-polariser "revival" reproduced.

**Phase 3 — Retarders & circular.** *Goal:* quarter/half-wave plate action. *Method:* anisotropic
closure retards one axis. *Success:* QWP turns linear↔circular; HWP rotates linear by 2θ.

**Phase 4 — Optical activity (stretch).** *Goal:* plane rotation in a chiral medium. *Method:*
handedness-split `c_local`. *Success:* rotation `∝ L` with correct sign; sugar-solution magnitude to order.

## Success criteria

- **PASS (A):** Malus, circular states, QWP/HWP, and rotation sign all from transverse orientation + handedness, zero fits.
- **QUALIFIED (C):** the above with retardance/`Δn` magnitudes CALIBRATED via measured material anisotropy (expected).
- **PENDING (D):** linear + Malus recovered, circular/retarders only schematic.
- **FAIL (F):** polarisation cannot be carried by the transverse wake without a spin postulate.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 Malus | `I=I₀cos²θ`; crossed → 0; 3-polariser revival | polarisation not transverse-orientation |
| T2 QWP | linear ↔ circular conversion | retarder ≠ anisotropic closure |
| T3 optical activity | rotation ∝ L, handed sign correct | handedness ≠ EMC03 ± redirection |

## Dependencies

**Upstream:** OP01 (n=1/(1−z)), [[project_cq47_repulsion_inverse]] (handedness), GOM06 (transverse
channel, [[project_cq44_gravitational_waves]]). **Downstream:** OP06 (polarised laser modes), LCD/
waveplate engineering, polarisation lensing. **Related:** Law V movement budget (transverse vs
forward partition), OP02 (Brewster produces polarised reflection).
