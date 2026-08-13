# NP34b Assessment — Complete Natural Misfit Census

**Date:** 2026-08-09  
**Pre-registration:** `NP34b_PRE_REGISTRATION.md`  
**Instrument:** `np34b_complete_misfit_census.cpp`  
**Stdout:** `.audit-tmp/np34b_run.txt`  
**Canon edited:** no

## Status

`COMPLETE_NATURAL_MISFIT_CENSUS_SURVIVES`

## Results

| Check | Result |
|---|---|
| Light set L (²H, ⁶Li, ¹⁰B, ¹⁴N) | 4/4 primordial misfits |
| Heavy set H (K-40 … Ta-180m) | 5/5 primordial misfits |
| Seven grips cleared | 7/7 |
| Extra primordial odd-Z misfits | 0 |
| Primordial odd-Z census | 63 |

## Relation to NP34

NP34 excluded “exactly H”. NP34b replaces that with the pre-registered identity
`misfits = L ∪ H` under the same primordial cut. The boolean predicate is
unchanged; only the census claim is reformulated.

## Scope / Limitations

- Counting overlap (odd Z ⇒ misfit ⇔ odd–odd) remains Scope, not a rival gate.
- Survives as a NUBASE census match, not as a derivation of why L and H split
  into stable vs long-lived radioactive classes.
- `laws.hpp` comment still says “precisely the five”; updating that text is
  propose-and-wait, not performed here.
