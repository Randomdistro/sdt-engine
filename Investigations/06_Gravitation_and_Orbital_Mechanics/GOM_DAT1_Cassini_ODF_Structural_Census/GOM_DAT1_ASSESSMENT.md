# GOM28 Assessment — Cassini SCE1 ODF Structural Census

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom28_odf_census.py`  
**Source SHA-256:** `796D6A44FC950417C277045CE23726294EAB0FA916FD8D2D6B54D0C9983CF157`  
**Stdout:** `.audit-tmp/gom28_run.txt`  
**Canon edited:** no

## 1. Scope

Fail-closed structural validation of the frozen Cassini SCE1 ODF sample against
its paired PDS3 label. No Doppler, range, delay, or theory residual is decoded.

## 2. Claim ledger

| Claim ID | Status |
|---|---|
| GOM28-C1 | **PASS** — `36 × 7616 = 274176` bytes |
| GOM28-C2 | **PASS** — 34 × 8064-byte blocks |
| GOM28-C3 | **PASS** — all label `ODF*A*` header pointers decode to declared keys `{101,107,109,2030,105,-1}`; undeclared = none |
| GOM28-C4 | **PASS** (spacecraft id 82); creation-time integer decode **UNADJUDICATED** (no revision-matched TRK-2-18 fixture) |
| GOM28-C5 | **PENDING_DATA** — residual intentionally not extracted |

## 3. Instrument validation

| Test | Result |
|---|---|
| A synthetic big-endian header | PASS |
| B no partial record | PASS |
| Manifest SHA-256 gate | PASS |

## 4. Correction retained

First run used a `header_like` heuristic on data-table pointers and falsely
flagged ASCII data words as undeclared headers (`STRUCTURE_FAIL`). Rule was
corrected before adjudication: only label tables matching `ODF*A*` are headers;
`*B*`/`*C*` are data and skipped. Re-run → `STRUCTURE_PASS`.

## 5. Classification

**`STRUCTURE_PASS / PENDING_RECONSTRUCTION`.**

ODF is a cleaner structural path than the TDF (which remains
`STRUCTURE_PARTIAL` on a label vs TRK-2-25 format conflict). This does **not**
license a Shapiro-like empirical claim.

## 6. Next gate

Pre-register TRK-2-18 observable-field decode on a **non-conjunction** ODF
fixture (Doppler/range groups only), validate against known engineering values,
then attempt solar-conjunction residual reconstruction with independent
geometry/clock/media inputs. Do not fit `ϟ`, profile exponent, or delay amplitude.
