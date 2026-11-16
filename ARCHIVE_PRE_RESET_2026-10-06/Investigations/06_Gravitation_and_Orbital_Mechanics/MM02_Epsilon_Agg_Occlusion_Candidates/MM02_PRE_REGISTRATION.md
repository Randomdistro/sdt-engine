# MM02 Pre-registration — ε_agg occlusion / packing candidates

**Date:** 2026-08-11  
**Upstream:** MM01 (`EPSILON_AGG_DEBT_RECORDED`); Iteration 39 next item  
**Canon:** not edited

## Question

Is the MM01 debt `ε_agg ≔ R_g/(N·Om_H) ≈ 4.376×10⁻⁴⁰` explained by:

1. **Wrong micro unit** — additive body depth uses `koppa_per_baryon` (engine) not `Om_H`; or
2. **Occlusion/packing factor** `f` with `Om_H · f` matching the debt without fitting `R_g`?

## Held-out targets (comparison only — must not enter candidate formulas)

| Symbol | Source | Class |
|---|---|---|
| `ε_u` | MM01 proxy: `R_g/(N_u·Om_H)`, `N_u=M_☉/m_u` | COMPUTED debt |
| `ε_p` | proton census: `R_g/(N_p·Om_H)`, `N_p=M_☉/m_p` | COMPUTED debt |

Identity gate uses **`ε_p`** (same mass species as `koppa_per_baryon`).  
`ε_u/ε_p = m_p/m_u ≈ 1.007` is a disclosed census choice, not a mechanism.

`G`, `M_☉`, and `R_g` are **forbidden inside candidate constructions**.  
`l_P`, `c`, `ℏ`, `m_p`, `m_e`, `α`, `a₀`, `r_e`, `R_p` are allowed (derivation basis).

## Instrument validation (before candidates)

| Check | Expect |
|---|---|
| `Om_H = a₀ α²` | equals `r_e` within 1e-6 rel |
| `koppa_per_baryon = l_P² c m_p / ℏ` | equals `G m_p/c²` within 1e-6 rel (known-match / delete-test on G as *input*) |
| `koppa_per_baryon / Om_H` | equals `ε_p` within 1e-5 rel → IDENTITY route |
| `ε_u / ε_p` | equals `m_u/m_p` within 1e-6 rel (census accounting) |

## Pre-registered candidates (single pass; no mid-run retune)

| ID | Formula | Motivation |
|---|---|---|
| C0 | `koppa_per_baryon / Om_H` | Engine baryon depth quantum vs Om_H (relationship test) |
| C1 | `(l_P / r_e)²` | Planck-area / electron-disk |
| C2 | `4π (l_P / r_e)²` | full-sky × C1 |
| C3 | `(l_P / R_p)²` | Planck-area / proton-disk |
| C4 | `π R_p² / (4π a₀²) = R_p²/(4 a₀²)` | nucleon solid angle at Bohr scale |
| C5 | `(r_e / a₀)² = α⁴` | EM scale squared |
| C6 | `α¹⁸` | pure-α power nearest 10⁻⁴⁰ band |
| C7 | `α¹⁹` | next α power |
| C8 | `l_P² / (ƛ_p r_e)` with `ƛ_p=ℏ/(m_p c)` | algebra twin of C0 (must match C0) |

## Decision rules

| Class | Criterion |
|---|---|
| **IDENTITY** | Candidate ≡ `ε_p` by algebra / <1e-5 rel, and reduces to `koppa_per_baryon/Om_H` |
| **MATCH** | `\|log₁₀(cand/ε_p)\| < 0.05` and **not** an algebraic twin of C0/C8 |
| **ORDER** | `\|log₁₀(cand/ε_p)\| < 1.0` |
| **EXCLUDED** | else |
| **SHARED-INPUT** | Uses `l_P` in a way that only recovers `G m_p/(c² r_e)` via CODATA `l_P↔G` (disclose; not EMPIRICALLY SURVIVES) |

**EMPIRICALLY SURVIVES** is not available this run: no independent occlusion derivation of the Planck–baryon quantum without the disclosed `l_P` risk flag.

## Status vocabulary

- `EPSILON_AGG_UNIT_CORRECTED` — C0/C8 IDENTITY; packing C1–C7 no independent mechanism
- `EPSILON_AGG_UNIT_CORRECTED__C2_NUMERIC_MATCH_OPEN` — as above, plus C2 within MATCH band pending coincidence audit
- `EPSILON_AGG_PACKING_MATCH` — non-twin MATCH that survives coincidence/mechanism audit
- `EPSILON_AGG_STILL_OPEN` — if nothing IDENTITY and nothing MATCH
- `MM02_INSTRUMENT_FAIL` — validation gates fail

**C2 coincidence gate (reported, not retuned):** if `4π (l_P/r_e)²` MATCHES only because
`α m_p/m_e ≈ 4π`, record as numeric near-equality — **not** a Law III packing derivation.

## Non-goals

No `laws.hpp` edit; no solar retune; no claim that C0 deletes the `l_P↔G` risk flag.
