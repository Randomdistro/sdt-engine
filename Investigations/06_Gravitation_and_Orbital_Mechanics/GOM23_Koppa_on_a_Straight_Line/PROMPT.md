# GOM23 — Koppa on a Straight Line

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-08-03. **Status:** pre-registered
> before instrumentation (this file precedes the tool).
> **Domain:** 06 Gravitation & Orbital Mechanics. **Feeds:** RTM01 (Reactions & Thrust
> Mechanics — the findings here inform the thrust-ledger investigation).

## 0. The question, stated exactly

Koppa was earned on closed paths: ϟ = v²r/c², the orbital ledger. This investigation asks
whether the same length is recoverable through measurement chains that contain **no closed
path, no period, and no π in any line** — and whether the straight-line family lands on the
same ϟ the circular ladder carries.

**Founding distinction (ruling, 2026-08-03).** Free fall is not straight. A dropped body, a
sungrazer, an e→1 comet — these *follow the field's own line*. A straight line is defined
against the far lattice (star-fixed), and inside a depth gradient it is the **forced** state:
it must be bought, continuously, by reaction. The far-field is where Newton I holds;
inside a gradient the free path is the curve and straightness costs. Consequently every
field-following route is demoted to a consistency appendix here, and the primary instruments
are **reaction instruments** — the normal force, the powered ascent, the null-steered line.

## 1. declared dependencies

`bridge::koppa_Earth`, `bridge::koppa_Sun` (comparison anchors only — the recovery chains must
not consume them); measured g₀ = 9.80665 m/s² with its centrifugal content stated; R_E; tower
height h; E_ion(H), m_e; c. No G, no M, no kilogram in any recovery chain. Shared-form caveat
mandatory wherever a recovered number coincides with a GM-derived value.

## 2. Phases and pre-registered gates

- **P1 — π-audit.** Enumerate every recovery chain and every constant it consumes. Gate:
  **zero π anywhere** — the demonstration that the census's π-coefficients belong to sampling
  geometries, not to the length.
- **P2 — instruments validated on known answers.**
  - I1 *the scale*: standing still is thrust; a = c²ϟ_E/R² vs measured g. Gate: within
    0.5% of the g-band once the centrifugal term (−0.034 m/s² equatorial) is stated.
  - I2 *the tower*: two clocks on a plumb line; Δν/ν = ϟ·h/r² at h = 450 m. Gate: matches
    the gh/c² identity and the measured chronometric-levelling class (~4.9×10⁻¹⁴).
  - I3 *photoionisation*: radial escape from the hydrogen seat; ϟ_H = a₀/k² with
    k = c/√(2E_ion/m_e). Gate: r_e within 0.1%, the finite-proton seat offset stated.
- **P3 — synthetic ascent extraction.** Simulate a powered vertical ascent over a known ϟ;
  recover ϟ from (proper acceleration − kinematic acceleration)·r²/c² along the profile.
  Gate: recovery < 0.1%. This validates the extraction algebra; **real launch telemetry is a
  named data requirement, owed** — the synthetic pass licenses the instrument, not the result.
- **P4 — the null-steered line.** A body held on a straight line at speed v, impact
  parameter b: closed form Δv⊥ = 2c²ϟ/(bv). Gate: the numerical lateral-impulse integral
  along the line matches the closed form < 0.5% at X/b ≥ 10³.
- **P5 — closure table.** Straight-line ϟ vs circular-ladder ϟ per rung (Earth, Sun, hydrogen),
  whole-range, single pass. Gate: every row < 1%.

## 3. Appendix A — field-following routes (consistency only)

The drop (ϟ = gR²/c² via the *force* reading is P2-I1; via fall-timing it is field-following),
the sungrazer v = c√(2ϟ/r), and the e→1 degenerate ellipse. Reported as consistency with the
orbital family. **Not straight; never cited as the straight-line result.**

## 4. Falsification table

| ID | Condition that fails this investigation |
|----|------------------------------------------|
| F1 | any π irreducibly present in a recovery chain |
| F2 | numerical lateral impulse ≠ closed form beyond gate |
| F3 | synthetic ascent recovery ≠ injected ϟ beyond 0.1% |
| F4 | any closure-table row splits beyond 1% (straight vs circular) |
| F5 | I1–I3 disagree with their known answers beyond stated gates |

## 5. Deliverables

`gom23_straightline.cpp` (VS2022 cl, `#include <sdt/laws.hpp>`), `gom23_results.txt` (real
stdout), `GOM23_VERDICT.md` (dual verdict, register-compliant), `DATA_REQUIREMENTS.md`
(real ascent telemetry, named source class).
