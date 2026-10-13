# NP12e Assessment — Frozen proton centres / point-proton RMS

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` (working tree dirty)  
**Instrument:** `np12e_frozen_proton_rms.py`  
**Stdout:** `.audit-tmp/np12e_run.txt`  
**Amendments:** `AMENDMENT_01.md`  
**Canon edited:** no · **IAEA:** sealed

## 1. Scope

O2 branch of NP12d: compute point-proton `R_{p,RMS}` from frozen ATOMICUS
proton-centre tables. Continuous `ρ_q` not claimed.

## 2. Claim ledger

| ID | Status |
|---|---|
| NP12e-C1 | **PASS** |
| NP12e-C2 | **PASS** (4 nuclides; ⁷Li `TABLE_INCOMPLETE`) |
| NP12e-C3 | **PASS** |
| NP12e-C4 | **PASS** (Tammes-4 value-degenerate; asymmetric span 1.30) |
| NP12e-C5 | **PASS** — physical charge RMS still UNDERDETERMINED |
| NP12e-C6 | **PASS** |

## 3. Headline

**`POINT_PROTON_RMS_FROZEN_SET / PHYSICAL_CHARGE_RMS_UNDERDETERMINED`**

| Nuclide | `R_{p,RMS}` (fm) | `R_boundary(A)` (fm) | Provenance |
|---|---:|---:|---|
| ⁴He | 1.449569 | 1.476334 | STATED_ATOMICUS_TABLE |
| ⁹Be | 2.050305 | 1.934545 | STATED_ATOMICUS_TABLE |
| ¹²C | 2.776314 | 2.129242 | STATED_ATOMICUS_TABLE |
| ¹⁶O | 3.551584 | 2.343534 | STATED_ATOMICUS_TABLE |
| ⁷Li | — | — | **WITHDRAWN** `TABLE_INCOMPLETE` |

## 4. Findings

1. Point-proton second moments are COMPUTED where tables list exactly `Z` protons.  
2. For ¹²C and ¹⁶O, stated-table `R_{p,RMS} > R_boundary(A)` — either the tables
   are not constrained by `nuclear_boundary_radius`, or that symbol is not a
   charge-support bound (consistent with NP12d).  
3. Unlabelled regular tetra packing does not vary pair-RMS; asymmetric centres do.  
4. No `ρ_q` ⇒ physical charge RMS remains UNDERDETERMINED.  
5. IAEA not opened — no EMPIRICALLY SURVIVES.

## 5. Next

1. Derive / regenerate ATOMICUS proton centres from packing+grammar with
   proton-subset labels (so tables are DERIVED, not STATED) — still IAEA sealed.  
2. Or freeze continuous `ρ_q` / intra-proton form factor.  
3. Only then Phase B holdout.
