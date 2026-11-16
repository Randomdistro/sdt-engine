# APS03 — Universal Drafting Crossover Assessment

**Author:** James Christopher Tyndall, Melbourne<br>
**Executed:** 2026-07-23; B34 extension 2026-08-15<br>
**Instrument:** `aps03_drafting_crossover.cpp`

## Current status

- **B34 convergence floor:** `COMPUTED`, conditioned on the observed Clearing
  boundary.
- **Cross-scale crossover:** `QUALIFIED`; the asymptotes and candidate floor
  have SDT mechanisms, but the interpolation shape remains borrowed.
- **Open dependencies:** atomic exposure geometry, a deep stellar-floor
  corpus, and an SDT derivation of the crossover shape.

## B34 forward result

The current instrument evaluates

```text
normal convergence gradient = P_conv/(3 R_CMB)
engaged volume fraction      = 6/7
engaged resistance density   = [(P_conv/3)(6/7)V]/(V c^2)
a_floor                       = 7 c^2/(6 R_CMB)
```

The angular `1/3` is the isotropic second moment. The `6/7` is the FLM15
relay-lock volume integral. Neither coefficient is fitted.

Results:

- analytic floor: `1.10060639e-10 m/s²`;
- independent finite-volume floor: `1.10060639e-10 m/s²`;
- quadrature residual: `1.586e-11`;
- comparison floor: `1.20e-10 m/s²`;
- residual: `8.28%` against the pre-registered `20%` gate.

The full SPARC pilot remains stable at `24.0%` RMS with BTFR slope `3.58`.
The C+A+B binned collapse remains `8.8%`. The wrong-solid-angle control gives
`24.1%` RMS and the scrambled-exposure control gives `156.9%`, each exceeding
twice the live-model residual as required.

## Scope

No expansion-rate value, body-source mass parameter, or measured
low-acceleration target enters the B34 forward function. However, `R_CMB` is
an external boundary and shares cosmological provenance with the conventional
expansion-rate correspondence. B34 is therefore `COMPUTED` with shared-input
risk, not an independent cosmological derivation.

The broader universal-curve claim remains qualified. The galactic floor slope
passes, but the provisional atomic exposure variable has the wrong-sign floor
slope and the stellar corpus has no floor-regime members. The borrowed
interpolation is a comparison model, not an SDT law.
