# NP34 Assessment — Triton Parity NUBASE Census

**Date:** 2026-08-09  
**Pre-registration:** `NP34_PRE_REGISTRATION.md`  
**Instrument:** `np34_triton_parity_nubase.cpp`  
**Stdout:** `.audit-tmp/np34_run.txt`  
**Canon edited:** no

## Status

`TRITON_PARITY_EXCLUDED`

The pre-registered whole-range claim — that among primordial odd-Z NUBASE
entries the misfit set is **exactly** the five named quasi-stables — fails.

## Provenance

| Source | SHA-256 | Gate |
|---|---|---|
| `Datasets/nuclear/NUBASE2020.txt` | `1585a5ee…df9859` | PASS |
| `Engine/include/sdt/laws.hpp` | `ae41f3cb…255835b` | PASS |

Predicate validation `(19,40)/(11,23)/(2,4)` PASS.

## Results

| Check | Result |
|---|---|
| Expected misfits present and flagged | 5/5 PASS |
| Expected grips present and cleared | 7/7 PASS |
| Extra primordial odd-Z misfits | **4** → FAIL |

Extra members (primordial, odd Z, `triton_parity_misfit==true`):

| Nuclide | Z | A | n_t |
|---|---:|---:|---:|
| ²H | 1 | 2 | 0 |
| ⁶Li | 3 | 6 | 0 |
| ¹⁰B | 5 | 10 | 0 |
| ¹⁴N | 7 | 14 | 0 |

Primordial odd-Z census size: 63. Expected five + these four light stable
odd–odd species exhaust the misfit hits under the frozen cut.

## Interpretation

1. **B38b is not a whole-range test.** It only asserts the predicate on twelve
   hand-picked pairs. That row can PASS while the comment claim “precisely the
   five” fails against NUBASE.
2. **What is excluded** is the census identity as written in
   `laws.hpp` / B38b prose (exactly those five natural misfits). The boolean
   counting rule itself still flags every odd-Z even-`n_t` case, including the
   four light stables.
3. **Not excluded by this run:** ATOMICUS grammar, grip clearance of the seven
   named mono-isotopes, or the five heavy quasi-stables as a *subset* of misfits.
4. **Counting overlap:** for odd Z, misfit ⇔ odd–odd under standard `n_t`.
   Recorded as Scope; not used as a rival rejection criterion.

## Reformulation path (propose-and-wait; not executed here)

Any reopen must freeze a new claim **before** re-inspection, for example a mass
cut (`A ≥ 40`) or an explicit “long-lived radioactive odd-odd” class that names
the four light stables as a separate stable odd–odd set. Widening the expected
misfit list after this run is not allowed for this adjudication.

## Cascade

Investigation-level: whole-range “precisely five” claim **excluded**. Suite
B38b remains a hand-list check only until the comment/claim is revised under
propose-and-wait.
