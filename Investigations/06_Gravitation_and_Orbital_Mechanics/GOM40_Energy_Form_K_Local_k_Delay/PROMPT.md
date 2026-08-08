# GOM40 — Energy-form solar **K** + local-**k** delay-rate (SCE1)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT **claim** investigation (invariant reconstruction + delay-rate expression).  
> **Upstream:** GOM39 defined **K = R/k²**; SCE1 circular proxy **K** was 1.4% off GOM26.  
> **Canon edits:** none.

## 0. Objective

Recover solar **K** on the SCE1 Earth@Sun arc by the **GOM26 energy / pairwise-μ**
route (not instantaneous **v²r/c²**), then express conjunction delay and
delay-rate using local **k(r) = √(r/K)** with that **K**.

Still **no** ODF residual promotion, no **K** fit to Doppler/delay, no γ.

## 1. Grammar (locked)

- **k = c / v_orb(R)** at main sequence **R** (here: recovered SMA **a**).  
- **K = R / k²** = **μ / c²** (c-boundary length).  
- **v(r) = (c/k) √(R/r)**; local **k(r) = √(r/K)**; **z(r) = 1/k(r)² = K/r**.  
- Shapiro (engine): **Δt = (2K/c) ln(4 r₁ r₂ / b²)** ≡ local-**k** integral.

## 2. Procedure (single pass)

1. **Validation A:** eccentric Kepler mock recovers **μ**, **K** (rel **μ** < 1×10⁻⁶).  
2. **Validation B:** from recovered (**a**, **K**), **k = √(a/K)**; check **K = a/k²**.  
3. Load frozen multi-day Earth@Sun vectors `…_2002_157_160.csv`.  
4. Pairwise **μ** (GOM26): skip pairs with \|Δ(1/r)\| ≤ 1×10⁻¹⁵ m⁻¹; median **μ**; **K = μ/c²**.  
5. Mean specific energy → **a**; reconstruct **k_i** and CV(**K_recon**).  
6. Continuity: \|**K** − 1476.35\| / 1476.35 reported (not a fit gate).  
7. Conjunction geometry (Earth+Cassini heliocentric): **b(t)**, **Δt(t)** via **K**;  
   **dΔt/dt**; local **k** at Earth / **b** / Cassini.  
8. Publish delay-rate amplitude class only — **no** corr(obs,·) gate.

## 3. Claims

| ID | Claim |
|---|---|
| GOM40-C1 | Validation A PASS (eccentric mock). |
| GOM40-C2 | Validation B PASS — **K = a/k²** identity. |
| GOM40-C3 | Dual-arc energy-form **K** COMPUTED; **K** not fitted to ODF. |
| GOM40-C3b | SMA **a ∈ [1.4, 1.6]×10¹¹ m** or label **`ARC_INSUFFICIENT`** (Amendment 01). |
| GOM40-C3c | Year EMB D1-cal route if SCE1 insufficient (Amendment 01). |
| GOM40-C4 | CV(**K_recon**) < 1×10⁻³ on the accepted (SMA-OK) arc. |
| GOM40-C5 | Local-**k** ledger + **Δt**, **dΔt/dt** published for conjunction samples. |
| GOM40-C6 | No EMPIRICALLY SURVIVES / residual-correlation claim. |

## 4. Inputs

- `Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157_160.csv`  
- `Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157_160.csv`  
- **c** = 299792458 m/s
