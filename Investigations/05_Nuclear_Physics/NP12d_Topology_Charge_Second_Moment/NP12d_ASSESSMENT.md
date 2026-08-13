# NP12d Assessment — Topology / charge second moment

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` (working tree dirty)  
**Instrument:** `np12d_topology_rms_audit.py`  
**Stdout:** `.audit-tmp/np12d_run.txt`  
**Canon edited:** no · **IAEA:** sealed

## 1. Scope

Strengthen NP12c: prove boundary radius is not a sufficient state variable for
RMS charge radius; redirect the native object to topology → `ρ_q` → `R_RMS`.

## 2. Claim ledger

| ID | Status |
|---|---|
| NP12d-C1 | **PASS** — `μ_λ` ⇒ `R_RMS = R_B√λ` on `[0, R_B]` |
| NP12d-C2 | **PASS** — shell/uniform ratio `√(5/3) ≈ 1.291` at fixed `R_B` |
| NP12d-C3 | **PASS** — all analytic fixtures |
| NP12d-C4 | **PASS** — NP12 path **O3**; topology layer **O2** |
| NP12d-C5 | **PASS** — status below |
| NP12d-C6 | **PASS** — IAEA sealed; no fitted `k` |

## 3. Headline status

**`UNDERDETERMINED — BOUNDARY IS NOT A SUFFICIENT STATE VARIABLE`**

(replaces / strengthens NP12c `MAP_UNDERIVED` for the `R_boundary`-only map)

If `nuclear_boundary_radius` is only mechanical/exclusion, even
`R_RMS ≤ R_B` is not established.

## 4. Correct native arrow

```text
nuclear topology → ρ_q(r) → R_RMS
```

not

```text
R_boundary → k · R_boundary
```

Point-proton reduction (when proton centres `{r_i}` are frozen):

```text
R_{p,RMS}² = (1/Z) Σ |r_i − r̄_p|²
```

## 5. Topology census

| Layer | Finding |
|---|---|
| `laws.hpp` `nuclear_boundary_radius` | outer `R(A)` only — **O3** for NP12 scalar path |
| Engine `ρ_q` / Map | **absent** |
| `packing.hpp` presets | nucleon-center geometries — **O2** (no intra-proton `ρ_q`; no general proton-subset labelling) |
| ATOMICUS element tables | coordinate tables present; **no** `ρ_q` definitions in sample |

**Physical charge RMS:** UNDERDETERMINED until `ρ_q` (or frozen proton centres +
stated point-proton approximation) is derived.  
**Point-proton RMS:** DERIVABLE only where proton centres are explicitly frozen.

## 6. Next

**Parked (Iteration 30):** author framing — IAEA “charge radius” is a QED
measurement formulation; native nuclear construction is the **packing
sequencer** (enmeshment / shadow ΔA). See NSEQ01. This underdetermination
result still stands against any `R_boundary → k·R_RMS` shortcut; it is not the
primary construction test.
