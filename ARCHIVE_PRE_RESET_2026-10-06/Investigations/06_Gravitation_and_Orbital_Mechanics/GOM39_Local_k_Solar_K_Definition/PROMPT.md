# GOM39 — Local **k** / Solar **K** Definition (reopen Doppler–K path)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT **claim** investigation (definition / grammar closure).  
> **Upstream:** GOM36–38 used a naked frozen length **K**; path set `PENDING_DEFINITION`.  
> **Canon edits:** none.

## 0. Objective

Close the Doppler–solar-**K** **definition** gate with the corrected grammar:

| Symbol | Meaning |
|---|---|
| **k** | Dimensionless ratio at a stated main-sequence radius **R**: **k = c / v_orb(R)**. Different **R** ⇒ different **k**. |
| **K** | **c-boundary radius** (orbit reaches **c**). Length. **K ≠ k**. |
| Link | **K = R / k²** |
| Speed law | **v(r) = (c/k) √(R/r)** ⇔ local **k(r) = √(r/K)** ⇔ **K = r / k(r)²** |

**K** for the Sun is the body c-boundary. It is recovered from a chosen main sequence (**R**, **k**), not imported as a free frozen constant with **k** ignored. Along a light path, depth uses local **k(r)** (equivalently **z = 1/k(r)² = K/r**).

This investigation does **not** claim EMPIRICALLY SURVIVES on ODF residuals. It defines the object GOM36–38 mishandled.

## 1. Procedure (single pass)

1. **Validation A (known answer):** pick synthetic (**R**, **v**) → **k = c/v**, **K = R/k²**. At several **r**, form **v(r)**, **k(r)**, and check **r/k(r)² = K** (machine precision).  
2. **Validation B (two-route):** numerical ∫ **z dl** with **z = 1/k(r)²** vs exact chord integral **(2K/c)[ln(s₂+r₂)−ln(s₁+r₁)]**; far-zone asymptotic **(2K/c) ln(4 r₁ r₂ / b²)** reported as continuity check.  
3. **SCE1 Earth main sequence:** from frozen Horizons Earth@Sun vectors (DOY 157), at each sample **R = |r|**, **v = |v|**, **k = c/v**, **K = R/k²**. Publish median **k**, median **K**, CV(**K**).  
4. **Local-k ledger at conjunction radii:** with solar **K** from step 3 median, report **k(r) = √(r/K)** at Earth **R**, impact **b**, Cassini **R** — demonstrating every radius produces a different **k**.  
5. Administrative: set ODF Doppler–solar-**K** path status to **`DEFINED`** (grammar). Empirical residual adjudication remains whatever GOM36–37 already recorded (not re-promoted here).

## 2. Claims

| ID | Claim |
|---|---|
| GOM39-C1 | Notation ledger published; **k** and **K** distinct; **K = R/k²**. |
| GOM39-C2 | Validation A PASS — multi-radius **r/k(r)²** recovers **K** with max rel err **< 1×10⁻¹²**. |
| GOM39-C3 | Validation B PASS — \|Δt_num − Δt_exact\| / Δt_exact **< 1×10⁻⁶**; far-zone \|num−closed\|/closed **< 1×10⁻³**. |
| GOM39-C4 | SCE1 Earth → (**k**, **K**) COMPUTED; **K** never fitted to Doppler/delay. |
| GOM39-C5 | Local **k** at Earth / **b** / Cassini radii published and pairwise distinct. |
| GOM39-C6 | Path status → **`DEFINED`**; no EMPIRICALLY SURVIVES claim from this loop. |

## 3. Rejection / non-claims

- Matching GOM26’s 1476.35 m is **continuity** (shared DE441 kinematics), not a fit and not survival.  
- ODF residual correlation gates are **out of scope** (already UNADJUDICATED / PENDING).  
- No γ, no Bertotti coefficient, no `laws.hpp` edit.

## 4. Inputs

- `Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157.csv`  
- `Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157.csv`  
- **c** from SI (same as prior GOM tools): 299792458 m/s.

---

## Audit correction 2026-10-05 (gating)

**Finding:** Gates C1–C3 PASS an identity (K = R/k²) and its numerical recovery (3.1e-16), and the folder has no numeric physics gate (gate flag false).

**Correction:** Label them IDENTITY and gate on the SCE1 K value against an independently derived K.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
