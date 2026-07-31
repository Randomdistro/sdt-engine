# α — fine-structure ratio (the koppa rung of hydrogen)

> **J. C. Harvey, Melbourne — 2026-07-30.** Measured anchor: 1/α = 137.035999084
> (CODATA 2018). Whitelist entry: `laws.hpp:126,138`. Primary records: APS05
> (`Investigations/04_Atomic_Physics_and_Spectroscopy/APS05_Alpha_from_Fine_Gross_Ratio/`,
> direct re-run 2026-07-23) and PPT02 seat closure
> (`Investigations/02_Particle_Physics_and_Topology/PPT02_Fine_Structure_from_Topology/`).
> Re-run: `../derivelist_results.txt` §[2].

## Role in the framework

α is not a coupling dialed into the universe — it is the **koppa rung of
hydrogen's ground state**: k_H = 1/α = 137 on the same ladder as
koppa_Sun (k = 686) and every other seat, ϟ = v²R/c², z·k² = 1 at every rung.
The engine-confirmed reading: ϟ_H = α²a₀ = r_e (re-run: exact).

## Derivation routes on record — this is where it came from

The framework's α was read off the hydrogen spectrum, two independent routes
(APS05, gates pre-registered in the spec, both PASS):

**Route B — pure fine/gross frequency ratio.** No m_e, no e, no h anywhere:
α² = 16·(Δν_2P / cR∞), both frequencies measured.

```
1/α = 136.912   (−0.0905% vs CODATA; gate ≤0.2% PASS)
```

The −0.09% residual is real higher-order structure in the measured 2P
splitting — reported, not tuned away.

**Route A — Law V virial seat.** The ionisation limit of any H series through
the movement budget: α = √(2E_ion/m_e c²).

```
1/α = 137.0726  (+0.0267%; the proton-free hydrogen seat — reduced-mass
                 idealisation deliberately NOT applied; CODATA 137.036 is the
                 proton-nailed-to-infinity idealisation)
```

**The rung reading (PPT02 seat closure, 2026-06-20).** From the raw measured
spectrum, α never used in the computation: v = √(2E/m_e), k = c/v → k = 137.07,
and the whole series collapses onto one rung index k_n = 137.07·n across Lyman,
Balmer and Paschen. The native α² mechanism: 1−√(1−α²) = ½α² to +0.0013% — the
fine/gross α² scale is the second-order movement-budget term, no spin-orbit
operator imported.

## Scope / Limitations / Residuals

- Both routes **extract** α from spectra; neither derives it. The geometric
  derivation (E51/OP-3) is open. α, being dimensionless, is not blocked by the
  Seed Theorem (contrast ℓ_P) — a derivation is permitted, just not yet earned.
- The CONDENSA closed-form search is **excluded**: no clean a·πᵇ form exists
  for α (contrast 6π⁵ for the mass ratio, which is unique at 19 ppm).
- E_ion and α carry the same information through the Rydberg relation — reading
  the seat does not change the input count; it trades the abstract coupling for
  a concrete observable.

## Status

**Line drawn — through "free parameter", not through "input".** α is read
directly off the hydrogen spectrum, two ways, to 0.1%; the statement "α is a
free parameter pulled from nowhere" is excluded. It remains on the input list
by count until the geometric route closes. c was settled off the same ladder
(see `01_c_speed_of_light/`).
