# AS02 Assessment — Native action scale A_s

**Date:** 2026-08-12  
**Commit:** `3d2de341f711891662133d0e3ecf5ae51a19d48d`  
**Instrument:** `as02_native_action_screen.py`  
**Stdout:** `.audit-tmp/as02_run.txt`  
**Pre-reg:** `AS02_PRE_REGISTRATION.md`  
**Canon edited:** no

## Status

`AS02_AS_REMAINS_IMPORTED`

## Validation

| Gate | Result |
|---|---|
| H0 control | PASS |
| First run | **INSTRUMENT_FAIL** (cp1252 Unicode) — preserved; encoding-only fix; no hypothesis change |
| Second run | exit 0 |

## Candidate screen

| ID | vs ℏ | Classification |
|---|---|---|
| H0 | control | MEASURED-INPUT |
| H1, H2, H4, H5, H7–H9 | MISS (`rel ≥ 0.99`) | EXCLUDED as native A_s |
| H3 | hold-out leak | CIRCULAR |
| H6 `α m_e c a_0` | MATCH (`rel ~6e-10`) | **IDENTITY** (Bohr/α definition path) — SHARED-INPUT, not new mechanism |

## Delete-tests

- Mass-form Rydberg `m_e c α²/(2h)`: deleting `h` leaves the formula undefined.
- Bohr form `α/(4π a_0)` and Compton `2π a_0 α` match NIST **only** because `a_0` and `α` are measured inputs — they do not invent an independent action.

## Root cause (seven questions)

1. **What failed:** magnitude — no non-identity whitelist product recovers ℏ.  
2. **Observable:** Compton / action scale linking mass to length.  
3. **Premise:** “A_s can be derived from {ℓ_P,c,k_B,T_CMB,α,m_e,m_p,a_0,r_e} without ℏ.”  
4. **Local or inherited:** local to action ontology; AS01 spine still CONDITIONAL.  
5. **Freedom to repair:** new axiom for discrete action, or accept ℏ as MEASURED-INPUT.  
6. **Freedom class:** OPEN (axiom) or MEASURED-INPUT (ℏ).  
7. **Downstream:** Cherenkov/Casimir “action-independent” energy claims; any native A_s narrative.

## Recovery

**OPEN** — not EMPIRICALLY EXCLUDED. Absence of a combinatorial derivation is not a measurement rejection. Parked until an axiom-level or lattice-level action quantisation is stated and pre-registered.

## Forbidden claims

- “SDT derives ℏ from α,a_0,m_e” when that is the Bohr identity rearranging measured inputs.  
- Promoting any MISS candidate with a post-hoc fitted κ.
