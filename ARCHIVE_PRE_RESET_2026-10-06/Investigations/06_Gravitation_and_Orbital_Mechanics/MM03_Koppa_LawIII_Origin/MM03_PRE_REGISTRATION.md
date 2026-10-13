# MM03 Pre-registration — Law-III origin of `koppa_per_baryon` without `l_P↔G`

**Date:** 2026-08-11  
**Upstream:** MM02 (`EPSILON_AGG_UNIT_CORRECTED__C2_NUMERIC_MATCH_OPEN`)

## Objective

Determine whether any Law-III / occlusion expression yields
`koppa_per_baryon ≈ 1.242×10⁻⁵⁴ m` **without**:

- using measured `G` as an input;
- using the CODATA identity `G = l_P² c³/ℏ` (which encodes `G` into `l_P`);
- fitting to `R_g,☉` or `M_☉`.

## declared dependencies for candidate formulas

`c`, `ℏ`, `m_p`, `R_p`, `α`, `a₀`, `r_e`, `P_conv`, `Φ`, `f_transfer`,
`R_charge`, Law-III `P_eff` — but **not** `l_P` if the formula algebraically
reduces to `G m_p/c²` via the CODATA Planck definition.

## Pre-registered candidates

| ID | Formula | Expected class if it matches |
|---|---|---|
| K0 | `l_P² c m_p/ℏ` | ENGINE IDENTITY (SHARED-INPUT risk) — baseline |
| K1 | `ℏ/(m_p c)` | Compton length — wrong scale |
| K2 | `R_p³ / a₀²` | geometric mix |
| K3 | `R_p² / a₀` | |
| K4 | `r_e · (R_p/a₀)²` | |
| K5 | `r_e · α⁴` | |
| K6 | `r_e · (m_e/m_p)` | |
| K7 | `ℏ/(m_p c) · α²` | |
| K8 | `R_charge³ / a₀²` | |
| K9 | `f_transfer · r_e` | needs Law-III f |

## Decision

- **SURVIVES** only if a candidate matches `K0` within 1e-3 rel **and**
  delete-tests show it does not reduce to `G m_p/c²` via `l_P↔G`.
- **PARKED_OPEN** if no independent Law-III route exists — keep engine
  formula with disclosed risk flag (honest status).
- Do not promote C2 packing coincidence.

## Forbidden

Fitting a free coefficient to solar depth. Calling K0 “derived from Law III.”
