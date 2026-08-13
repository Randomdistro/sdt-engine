# MM02 Assessment — ε_agg unit correction + packing screen

**Date:** 2026-08-11  
**Instrument:** `mm02_epsilon_agg_candidates.py`  
**Stdout:** `.audit-tmp/mm02_run.txt`  
**Pre-reg:** `MM02_PRE_REGISTRATION.md`  
**Canon edited:** no

## Status

`EPSILON_AGG_UNIT_CORRECTED__C2_NUMERIC_MATCH_OPEN`

## Validation (direct)

| Gate | Result |
|---|---|
| `Om_H = a₀α² = r_e` | PASS |
| `koppa_per_baryon = l_P² c m_p/ℏ` vs `G m_p/c²` | PASS (delete-test on G as input) |
| `C0 = koppa_per_baryon/Om_H` ≡ `ε_p` | PASS (IDENTITY) |
| `ε_u/ε_p = m_u/m_p` (MM01 census vs proton) | PASS |

MM01’s `≈4.376×10⁻⁴⁰` used `m_u`; proton-consistent debt is `ε_p ≈ 4.408×10⁻⁴⁰`.

## Candidate screen

| ID | Class | Note |
|---|---|---|
| C0, C8 | **IDENTITY** | `koppa_per_baryon/Om_H` — SHARED-INPUT risk via CODATA `l_P↔G` (disclosed in `laws.hpp`) |
| C2 | **MATCH** (0.05 dex) | `4π(l_P/r_e)²`; residual = `α m_p/m_e / 4π ≈ 1.066` — **coincidence, not Law III** |
| C3, C6 | ORDER | not mechanism |
| C1, C4, C5, C7 | EXCLUDED | |

## Relationship correction

| Wrong | Correct |
|---|---|
| Body depth = `N · Om_H` with `Om_H = α² a₀ = r_e` | `Om_H` is the **EM** c-boundary, not the gravitational baryon quantum |
| Need a packing factor `ε_agg` multiplying `Om_H` | Engine additive quantum is already `koppa_per_baryon = l_P² c m_p / ℏ` |
| | `Om_body = N_p · koppa_per_baryon` recovers `R_g` by known-match |

The “ε_agg ≈ 4.4×10⁻⁴⁰” figure is the **ratio of two micro lengths** (`koppa_per_baryon / r_e`), not an occlusion attenuation derived from packing geometry.

## What is still OPEN

1. **Law III derivation** of `koppa_per_baryon` that does not lean on the disclosed `l_P↔G` risk flag (MM03).  
2. C2 is **not** promoted: numeric MATCH only because `α m_p/m_e ≈ 4π`.  
3. No EMPIRICALLY SURVIVES on solar depth from this run.

## Forbidden claims (still)

- Fitting a coefficient to `R_g` and calling it derived.  
- “Packing derives ε_agg” from C2.  
- Treating C0 IDENTITY as deletion of the `l_P` circularity disclosure.
