# c — speed of light (relay speed)

> **J. C. Harvey, Melbourne — 2026-07-30.** Measured anchor: 299 792 458 m/s (SI exact).
> derivation basis entry: `laws.hpp:110`. Re-run: `../derivelist_results.txt` §[1].

## Role in the framework

c is the relay speed of the spation lattice — the one speed at which every
nearest-neighbour hand-off proceeds (Law I), the budget ceiling of Law V
(v_circ² + v² = c²), and the conversion between the lattice's time-tick and
length-step. Nothing in the framework travels; the relay does, at c, always.

## Derivation routes on record

**1. Spectroscopic (primary).** One hydrogen ladder, measured twice: as a
frequency (comb metrology → cR∞ = 3.2898419602508×10¹⁵ Hz) and as a wavenumber
(length metrology → R∞ = 1.0973731568160×10⁷ m⁻¹). Their ratio is the relay
speed. Re-run: **c = 2.9979245800×10⁸ m/s, deviation −0.0000%.** This is the
route through which the framework's c was settled: the fine-structure ratio α
comes off the same spectrum (see `04_alpha_fine_structure/`), and with α and the
seat velocity in hand the ladder closes at one speed (Law V movement budget,
APS05 Route A: v_seat = αc).

**2. Orbital closure (GOM04, tallied B27) — WITHDRAWN as a derivation.**
c = k_Sun·v_surface from Mercury's precession lands at 2.99795×10⁸ m/s
(+0.0009%). **Provenance objection, recorded 2026-07-30:** the ephemeris
orbital elements consumed by `bridge::k_from_precession` (`laws.hpp:812-828`) —
Mercury's eccentricity and the precession rate — are produced by ephemeris fits
that model light propagation with c. c therefore enters upstream of the closure.
The route is retained as a cross-domain **consistency check only** (proton to
Sgr A* on one law is still the point; it is not an independent origin for c).

**3. SI status.** Since 1983 the metre is *defined* from c: the numerical value
is a unit bridge, not a measurement. The physical content is that ONE relay
speed closes every hydrogen line, every orbit, and every emission gear
(λ = 2L(c/v), APS07).

## Scope / Limitations / Residuals

- Route 1 is an extraction from data (two metrologies of one ladder), not a
  derivation from axioms. No route derives the SI numeral — none can, since the
  numeral is definitional.
- The FLM13 reduced-derivation basis line "c ← Mercury precession" is superseded by
  this record: the closure survives as consistency, the provenance moves to the
  spectrum.

## Status

**Line drawn.** c is a unit bridge with an earned physical role (the relay
speed, Law I/V). Not an open mystery; nothing left to derive.
