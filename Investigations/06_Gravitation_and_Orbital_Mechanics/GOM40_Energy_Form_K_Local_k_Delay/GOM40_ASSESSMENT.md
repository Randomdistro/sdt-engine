# GOM40 Assessment — Energy-form **K** + local-**k** delay-rate

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom40_energy_form_k.py`  
**Stdout:** `.audit-tmp/gom40_run.txt`  
**Amendments:** `AMENDMENT_01.md` (SMA sanity + dual arc)  
**Canon edited:** no

## 1. Scope

Recover solar **K** by GOM26 pairwise-μ / energy form; express SCE1 conjunction
delay-rate with local **k(r) = √(r/K)**. No ODF residual promotion.

## 2. Claim ledger

| ID | Status |
|---|---|
| GOM40-C1 | **PASS** — eccentric mock |
| GOM40-C2 | **PASS** — **K = a/k²** identity |
| GOM40-C3 | **PASS** — dual route executed; **K** not ODF-fitted |
| GOM40-C3b | **ARC_INSUFFICIENT** — SCE1 Earth 4-day: **a = 3.53×10¹¹ m**, **K = 927.1 m** (discarded) |
| GOM40-C3c | **PASS** — EMB 2025 year: **K = 1476.354 m**, **a = 1.496×10¹¹ m**, **k = 1.006719×10⁴** |
| GOM40-C4 | **PASS** — year CV(**K_recon**) = 1.06×10⁻⁵ |
| GOM40-C5 | **PASS** — local-**k** + **Δt**, **dΔt/dt** published |
| GOM40-C6 | **PASS** — no EMPIRICALLY SURVIVES |

## 3. Headline

| Quantity | Value | Label |
|---|---:|---|
| SCE1 energy **K** | 927.11 m | COMPUTED — **ARC_INSUFFICIENT** |
| SCE1 **K_inst** median | 1455.60 m | COMPUTED (circular proxy) |
| Year EMB energy **K** | 1476.354 m | DERIVED (GOM26-class) |
| Year main-sequence **k** | 1.006719×10⁴ | DERIVED (**k = √(a/K)**) |
| Conjunction **b** median | 41.08 R_☉ | COMPUTED |
| **Δt** median | 6.615×10⁻⁵ s | COMPUTED |
| \|f_Ka · dΔt/dt\| median | 0.585 Hz | COMPUTED (amplitude class) |

**Finding:** A ~4-day conjunction Earth arc cannot recover energy-form **μ**
(ill-conditioned **Δ(1/r)**). Local-**k** delay-rate for SCE1 must use a
year-class energy **K** (or equivalent long-arc invariant), not a short-arc
pairwise estimate. Instantaneous **v²r/c²** on SCE1 remains a proxy (~1.4%
low), not the invariant.

## 4. Path status

| Path | Status |
|---|---|
| Grammar (**k**, **K = R/k²**) | DEFINED (GOM39) |
| Energy-form **K** for SCE1 delay | **YEAR_IC** (GOM40 / GOM26) — SCE1 short-arc excluded |
| Empirical Doppler residual | UNADJUDICATED (GOM36–37) |

## 5. Next

1. BF080 / GOM25 mechanism (access-limited).  
2. GOM20 author clock equation (mechanism-limited).  
3. Benchmark detox propose-and-wait.
