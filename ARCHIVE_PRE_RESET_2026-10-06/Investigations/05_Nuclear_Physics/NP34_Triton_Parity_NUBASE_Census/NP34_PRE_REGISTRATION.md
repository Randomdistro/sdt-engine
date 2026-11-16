# NP34 Triton Parity Lock — NUBASE2020 Whole-Range Census

**Date:** 2026-08-09  
**Branch:** `sdt::laws::nuclear::triton_parity_misfit`  
**Role:** master-protocol Iteration 26  
**Canon edited:** no

## Objective

B38b only checks twelve hand-picked `(Z,A)` pairs. This audit asks whether the
same predicate, over a pre-registered primordial census from frozen NUBASE2020,
flags **exactly** the five claimed natural odd-odd quasi-stables and clears
every other primordial odd-Z nuclide (including the seven mono-isotopic grips).

Rejection uses the NUBASE abundance/stability record only. No shell-model or
pairing comparator is a pass/fail input.

## Provenance gate

| Source | SHA-256 | Bytes | Class |
|---|---|---:|---|
| `Datasets/nuclear/NUBASE2020.txt` | `1585a5eea86c5e17e90307c7e6e786d060049c4039e392a261ff6db977df9859` | 761,906 | NUBASE2020 evaluated nuclear properties (Kondev et al. 2021) |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b` | 97,482 | Hypothesis under test |

Hash failure → `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION`.

## Fixed predicate

```text
n_t = A − 2Z
triton_parity_misfit(Z,A) ⇔ (Z odd) ∧ (n_t ≥ 0) ∧ (n_t even)
```

Implemented only via `nuclear::triton_parity_misfit`. No coefficient freedom.

## Primordial census (frozen before parse)

Include a NUBASE row in set **P** if **all** hold:

1. Mass number `A` and atomic number `Z` parse from columns AAA / ZZZi.
2. Ground-state rule: isomer index digit `i` (4th character of ZZZi) is `0`,
   **except** the single pre-registered isomer `(Z,A)=(73,180)` with isomer
   marker `s='m'` (Ta-180m).
3. Naturally occurring marker: half-life field is `stbl`, **or** the BR field
   contains `IS=` with parsed abundance `> 0`.

No half-life floor beyond those markers. No post-hoc isomer additions.

## Pre-registered expected sets

Among primordial odd-Z members of **P**:

| Class | Exact members (Z,A) |
|---|---|
| Expected misfits | `(19,40)`, `(23,50)`, `(57,138)`, `(71,176)`, `(73,180)` |
| Expected grip clears (must be primordial and not misfit) | `(11,23)`, `(13,27)`, `(15,31)`, `(21,45)`, `(23,51)`, `(25,55)`, `(27,59)` |

## Decision

| Condition | Classification |
|---|---|
| Provenance pass; expected misfits ⊆ P and all misfit=true; grips ⊆ P and all misfit=false; no other primordial odd-Z with misfit=true | `TRITON_PARITY_SURVIVES_WHOLE_RANGE` |
| Provenance pass; any missing expected member, any grip failing, or any extra primordial odd-Z misfit | `TRITON_PARITY_EXCLUDED` |
| Hash failure | `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION` |
| Parser failure after hashes | `INSTRUMENT_OR_DOMAIN_FAILURE` |

Scope note: for odd Z under the standard grammar, misfit ⇔ odd–odd. That
counting overlap is recorded; it is not a rejection criterion. The claim under
test is the census match to the named natural set.

## Instrument validation (before full parse)

`triton_parity_misfit(19,40)==true`, `(11,23)==false`, `(2,4)==false`.

## Out of scope

Cassini residual, NP21 retune, NP12b light-A residual, BF080, GOM20.
