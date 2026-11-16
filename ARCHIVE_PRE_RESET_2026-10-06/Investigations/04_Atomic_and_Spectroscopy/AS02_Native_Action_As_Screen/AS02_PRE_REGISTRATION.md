# AS02 Pre-registration — Native action scale A_s screen

**Date:** 2026-08-12  
**Commit:** `3d2de341f711891662133d0e3ecf5ae51a19d48d`  
**Upstream:** AS01 (`A_s` OPEN); Iteration 41 open ledger  
**Canon edits:** none (propose-and-wait)

## Objective

Determine whether a native SDT action invariant `A_s` can be assembled from the
measured derivation basis **without importing** `ℏ` / `h`, such that the Compton mass
link `λ_C = A_s / (m_e c)` recovers NIST `λ_C` within pre-registered tolerance.

## Claim under test

- **CLM-AS02a:** There exists a dimensionless combination of
  `{ℓ_P, c, k_B, T_CMB, α, m_e, m_p, a_0, r_e}` (no `ℏ`) that equals `ℏ`
  within `rel < 1e-3` as a derived quantity (not identity by construction).
- **CLM-AS02b:** Engine `R_inf_derived = m_e c α² / (2h)` remains an
  independent prediction after deleting `h` from inputs (delete-test).

## Hypotheses (pre-registered candidates only)

Candidates are pure dimensional products with **integer** powers in
`{−3…+3}` of at most three measured lengths/masses/temps, times α powers
`{0, ±1, ±2}`, targeting action units `kg·m²/s`. No post-hoc coefficient
beyond the combinatorial product itself.

Pre-registered families (exhaustive within bounds below):

| ID | Form | Notes |
|---|---|---|
| H0 | `ℏ` (control) | MEASURED-INPUT; must match itself |
| H1 | `m_e c a_0` | Bohr action scale |
| H2 | `m_e c r_e` | EM c-boundary scale |
| H3 | `m_e c λ_C_target` | CIRCULAR — hold-out leak; report then EXCLUDE |
| H4 | `m_p c ℓ_P` | Planck×baryon |
| H5 | `k_B T_CMB · a_0 / c` | thermal×length/c |
| H6 | `m_e c a_0 α` | H1×α |
| H7 | `m_e c a_0 α²` | H1×α² = `m_e c r_e` ≡ H2 |
| H8 | `m_e c ℓ_P` | electron×Planck |
| H9 | `m_e c a_0 / α` | H1/α |

No fitted float multipliers. If none of H1–H9 (except H0/H3) match `ℏ` to
`rel < 1e-3`, claim **UNDERDETERMINED / OPEN** — not EMPIRICALLY EXCLUDED
(absence of derivation ≠ empirical falsification of SDT).

## Decision rules

| Outcome | Condition |
|---|---|
| `AS02_NATIVE_AS_SURVIVES` | One of H1,H2,H4–H9 matches `ℏ` with `rel < 1e-3` AND delete-test on `h` for Rydberg fails to break OR an alternate Rydberg without `h` matches NIST |
| `AS02_AS_REMAINS_IMPORTED` | No non-circular candidate matches; Rydberg delete-test fails |
| `AS02_INSTRUMENT_FAIL` | Control H0 fails |

## Hold-outs

- NIST `λ_C`, `R_∞` used only as comparison columns.
- `ℏ` used only as target for candidates and as H0 control — never as a
  free coefficient inside H1–H9.

## Forbidden post-hoc moves

- Introduce a fitted `κ` to force `κ·H_i = ℏ`.
- Promote C2-style α m_p/m_e ≈ 4π coincidence as “derivation”.
- Edit `laws.hpp`.

## Downstream

If AS_REMAINS_IMPORTED: park `A_s` as MEASURED-INPUT (`ℏ`) with risk flag on
any claim of action-independence; Cherenkov/Casimir energy independence stays OPEN.
