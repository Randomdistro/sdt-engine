# GOM39 Assessment — Local **k** / Solar **K** Definition

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom39_local_k_definition.py`  
**Stdout:** `.audit-tmp/gom39_run.txt`  
**Canon edited:** no

## 1. Scope

Close the ODF Doppler–solar-**K** **definition** gate after GOM36–38 used a naked
frozen length. Grammar: **k = c/v_orb(R)**, **K = R/k²** (c-boundary),
**v(r) = (c/k)√(R/r)**. Not an EMPIRICALLY SURVIVES residual claim.

## 2. Claim ledger

| ID | Status |
|---|---|
| GOM39-C1 | **PASS** — ledger published; **k ≠ K** |
| GOM39-C2 | **PASS** — max rel err **3.1×10⁻¹⁶** on multi-radius **K** recovery |
| GOM39-C3 | **PASS** — \|num−exact\|/exact **7.6×10⁻¹¹**; \|num−closed\|/closed **8.5×10⁻⁷** |
| GOM39-C4 | **PASS** — SCE1 Earth **k** median **1.021250×10⁴**; **K** median **1455.637 m**; CV(**K**) **1.8×10⁻⁷**; not Doppler-fitted |
| GOM39-C5 | **PASS** — **k**(Earth)=1.021×10⁴, **k**(b)=4.647×10³, **k**(Cas)=2.753×10⁴ |
| GOM39-C6 | **PASS** — path → **`DEFINED`**; residual status unchanged |

## 3. Headline numbers

| Quantity | Value | Label |
|---|---:|---|
| Synthetic main-sequence **K** (AU, 29780 m/s) | 1476.160 m | COMPUTED |
| SCE1 Earth **K** median (\|v\|, \|r\|) | 1455.637 m | COMPUTED |
| vs GOM26 IC 1476.35 m | \|Δ\|/**K** = 1.40×10⁻² | continuity only (eccentric circular proxy) |
| Conjunction **b** | 45.17 R_☉ | COMPUTED |
| Δt(**K**_Earth) closed | 6.331×10⁻⁵ s | COMPUTED |

Instantaneous **K = v²r/c²** on Earth’s eccentric orbit is not the GOM26 energy
invariant; the **1.4%** offset is expected and is not a fit target.

## 4. Path status

| Path | Status |
|---|---|
| ODF Doppler vs solar **K** | **DEFINED** (grammar: local **k**, **K = R/k²**) |
| Empirical Doppler residual vs solar depth | **UNADJUDICATED** (GOM36–37; not re-opened here) |
| Type-37 range vs solar **K** | **RANGE_K_UNRESOLVED** (GOM38) |

## 5. Next

1. Optional: reconstruct solar **K** via GOM26 energy form on the same SCE1
   Earth arc (invariant, not circular proxy), then re-express delay-rate with
   local **k(r)** — still no residual promotion without a viable IF/scale path.  
2. BF080 / GOM25 / GOM20 as previously ranked.
