# NP12c Assessment — Boundary → RMS Map (Phase A)

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` (working tree dirty)  
**Instrument:** `np12c_boundary_rms_map_audit.py`  
**Stdout:** `.audit-tmp/np12c_run.txt`  
**Canon edited:** no

## 1. Scope

Iteration-26 reopen gate: freeze a native boundary→RMS Map before any holdout
radii adjudication. Phase A is derivation census + formal classification only.

## 2. Claim ledger

| ID | Status |
|---|---|
| NP12c-C1 | **PASS** — census; no executable Map in `laws.hpp` / Theory / Laws |
| NP12c-C2 | **PASS** — √(3/5) identity (MC rel 6.6×10⁻⁴) |
| NP12c-C3 | **PASS** — identity map **UNDERIVED** |
| NP12c-C4 | **PASS** — uniform √(3/5) map geometric under **underived** density premise |
| NP12c-C5 | **PASS** — Phase A = **`MAP_UNDERIVED`**; Phase B **SEALED** |
| NP12c-C6 | **PASS** — no IAEA fit; no EMPIRICALLY SURVIVES |

## 3. Headline

**`MAP_UNDERIVED / PHASE_B_SEALED`**

**Superseded for the scalar map by Iteration 28 / NP12d:**
`UNDERDETERMINED — BOUNDARY IS NOT A SUFFICIENT STATE VARIABLE`
(`R_B` alone cannot fix `R_RMS`; missing object is topology→`ρ_q`, not a
coefficient `k`).

Missing freedom (OPEN debt): an SDT-derived nuclear charge-density / periphery
profile (and finite-proton treatment if required) that converts
topology into a predicted RMS charge radius without using the IAEA table.

| Candidate | Class |
|---|---|
| `R_RMS = R_boundary` | UNDERIVED (surface-charge endpoint) |
| `R_RMS = √(3/5) R_boundary` | geometric under uniform density; density UNDERIVED |
| Native `Map(R_boundary; ρ_ch, …)` | ABSENT in canon |

## 4. Cascade

| Item | Status |
|---|---|
| NP12b direct proxy number | retained as DIRECT_PROXY_REPRODUCED |
| Physical support for boundary law vs IAEA RMS | **UNADJUDICATED** (unchanged) |
| Phase B holdout (odd `A`, `A≥16`) | sealed; threshold not yet registered |
| `laws.hpp` “known-match 4.96% RMS” comment | propose-and-wait hygiene (I26 correction) |

## 5. Seven questions (map debt)

1. Exact miss: no Map function — observable mismatch, not arithmetic.  
2. Observable: IAEA RMS charge radius.  
3. Premise: treating boundary radius as RMS without derived charge profile.  
4. Inherited from NP12 periphery-charge underived debt.  
5. Freedom needed: derived `ρ_ch(r)` / periphery weight (+ finite proton if used).  
6. That freedom is presently OPEN — not DERIVED in whitelist sources.  
7. Downstream: any “survives” claim for `nuclear_boundary_radius` vs IAEA RMS.

**Recovery grade:** OPEN (precise missing mechanism registered).

## 6. Next

1. Author / theory derivation of charge-profile Map (or explicit axiom) — then
   freeze and open Phase B.  
2. Do not retrofit a conversion to the present IAEA table.  
3. Parallel: propose-and-wait comment hygiene on `nuclear_boundary_radius`.
