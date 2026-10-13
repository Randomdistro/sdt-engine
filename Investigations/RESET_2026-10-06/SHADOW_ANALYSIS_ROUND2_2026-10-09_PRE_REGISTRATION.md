# Shadow analysis, round 2 — zk² = 1 from spectra on independent chains (pre-registration, 2026-10-09)

Notation: Ѻ = R/k² (Harvey 2026-10-09; older files write ϟ for the same length).

> **Correction 2026-10-09 (Harvey):** removing the Sun's 1-AU term was a look at what the data say, not a ruling. Below, "under the emission reading" means one of the readings examined; it is not adopted. The observer terms stay an open question, framed by Harvey as a distortion seen through a distortion.

## Carried from 2026-10-09 (the Sun, computed in session at Harvey's direction)

Measured: 638 ± 6 m/s, González Hernández et al. 2020 (A&A 643 A146). The Sun's 1-AU term (2.96 m/s) is removed under the emission reading (z is set at emission). Earth's own term (0.21 m/s) is kept.

Result:
- z = 638.21/c = 2.1288×10⁻⁶ ± 0.0200×10⁻⁶
- Ѻ = zR☉ = 1481.0 ± 13.9 m
- zk² = 1.0030 ± 0.0094 with k from Earth's orbital kinematics (686.398); the same with k from Mercury's precession (686.404)
- deviation: 0.32σ

Other handlings of the 3.17 m/s, as done in session:

| handling | Ѻ (m) | deviation |
|---|---|---|
| subtracted | 1473.2 | −0.24σ |
| removed | 1480.6 | +0.28σ |
| added | 1487.9 | +0.81σ |
| doubled | 1495.3 | +1.34σ |

The data do not choose among them; that would need about ±1.5 m/s.

## Registered now (before any white-dwarf value is loaded)

**Systems.** Every white dwarf with all three of the following. Searched for, then taken whole; no subset is chosen after seeing values.
1. A published gravitational redshift v_gr with uncertainty.
2. A published radius with uncertainty from a route that does not use v_gr (parallax plus photometry or spectroscopy).
3. A dynamical mass from a visual-binary orbit.

Candidates known before the search: Sirius B (done in round 1, carried), 40 Eri B, Procyon B.

**Quantities.**
- Ѻ_spec = (v_gr/c)·R
- Ѻ_orbit = (M_dyn/M☉)·Ѻ☉, with Ѻ☉ = 1476.5989 m (engine, Mercury route). M_dyn/M☉ comes from Kepler's third law in AU and years, so no G enters.
- zk² = Ѻ_spec/Ѻ_orbit

Where the published v_gr is already corrected for the system velocity, it is used as published. No propagation terms are applied at the observer (white-dwarf v_gr ≫ 3 m/s).

**Criterion, per system.** abs(zk² − 1) ≤ 2σ, with σ from v_gr, R and M_dyn combined in quadrature.
- **Confirmed** if met.
- **Rejected** if not met. Each rejection is assessed for its origin (radius route, redshift systematics, or the relation).

**Across the set.** The count within 2σ is reported against the expectation of about 95%.

**Known risk, stated beforehand.** The white-dwarf radius routes may depend on model atmospheres or a mass–radius relation. Any radius taken from a mass–radius relation (which uses M) shares input with Ѻ_orbit and is excluded. Each radius's route is recorded.
