# NP34b Complete Natural Misfit Census — Pre-Registration

**Date:** 2026-08-09  
**Upstream:** Iteration 26 `TRITON_PARITY_EXCLUDED` (exactly-five claim)  
**Branch:** `triton_parity_misfit` reformulated census  
**Canon edited:** no

## Objective

NP34 excluded the claim that primordial odd-Z misfits are exactly five
quasi-stables. The reformulated claim, frozen here before re-parse:

Among the pre-registered primordial set **P**, the odd-Z members with
`triton_parity_misfit==true` are **exactly**

```text
L ∪ H
L = {(1,2), (3,6), (5,10), (7,14)}     # light stable odd–odd
H = {(19,40), (23,50), (57,138), (71,176), (73,180)}  # long-lived radioactive odd–odd (Ta as isomer)
```

and the seven grips remain primordial with misfit false.

This is a census identity, not a coefficient fit. No shell-model comparator.

## Provenance gate

| Source | SHA-256 | Bytes |
|---|---|---:|
| `Datasets/nuclear/NUBASE2020.txt` | `1585a5eea86c5e17e90307c7e6e786d060049c4039e392a261ff6db977df9859` | 761,906 |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | 97,482 |

## Primordial cut (unchanged from NP34)

Ground state (`i=0`), except Ta-180m `(Z,A,s)=(73,180,m)`.  
Natural if `T==stbl` or `IS=` abundance `> 0`.

## Expected grips (must be in P, misfit false)

`(11,23)`, `(13,27)`, `(15,31)`, `(21,45)`, `(23,51)`, `(25,55)`, `(27,59)`.

## Decision

| Condition | Classification |
|---|---|
| Provenance pass; misfit set among primordial odd-Z equals exactly `L∪H`; all grips clear | `COMPLETE_NATURAL_MISFIT_CENSUS_SURVIVES` |
| Provenance pass; any missing member of `L∪H`, any grip failure, or any extra primordial odd-Z misfit | `COMPLETE_NATURAL_MISFIT_CENSUS_EXCLUDED` |
| Hash failure | `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION` |
| Parser failure | `INSTRUMENT_OR_DOMAIN_FAILURE` |

## Instrument validation

Same as NP34: `(19,40)` true, `(11,23)` false, `(2,4)` false; plus `(1,2)` true.

## Scope

Confirms only this reformulated census against NUBASE2020. Does not by itself
authorize a `laws.hpp` comment rewrite (propose-and-wait). Does not reopen NP34's
excluded “precisely five” wording as if it had survived.
