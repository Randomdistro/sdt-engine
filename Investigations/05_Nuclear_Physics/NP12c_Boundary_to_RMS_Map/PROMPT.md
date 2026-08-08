# NP12c — Boundary → RMS observable map (Phase A freeze)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT claim investigation (derivation / reopen gate from Iteration 26).  
> **Upstream:** NP12b `PROXY_REPRODUCED_UNDER_UNDERIVED_SURFACE_CHARGE_MAPPING`.  
> **Canon edits:** none (propose-and-wait for any `laws.hpp` comment hygiene).

## 0. Objective

Freeze whether SDT presently supplies an **executable native map**

```text
R_pred_RMS(A) = Map( R_boundary(A); profile, charge-weighting, finite-proton )
```

with every parameter from the measured whitelist + packing geometry only — **before**
any holdout comparison to IAEA RMS charge radii.

Phase A does **not** adjudicate EMPIRICALLY SURVIVES / EXCLUDED against radii.
Phase B (holdout) opens only after Phase A freezes a derived Map.

## 1. Grammar

| Symbol | Meaning |
|---|---|
| `R_boundary(A)` | `nuclear_boundary_radius(A) = R_p (A/η)^{1/3}`, `η = π/√18` |
| IAEA `radius` | RMS charge radius (Angeli & Marinova / IAEA ground-state table) |
| Map | native conversion from boundary construction → predicted RMS observable |

## 2. Phase A procedure (single pass)

1. **Source census:** search `laws.hpp`, `Theory/`, `Laws/` for any derived
   boundary→RMS map, charge-density profile, or periphery-charge strength.  
2. **Candidate ledger (formal only):** list maps that appear in prior NP12 work
   with classification DERIVED / UNDERIVED / GEOMETRIC-IDENTITY / WITHDRAWN.  
3. **Instrument validation:** analytic uniform-sphere identity
   `⟨r²⟩^{1/2}/R = √(3/5)` — known-answer check (math only).  
4. **Derivation gate:** accept Map only if every coefficient is DERIVED or
   MEASURED-INPUT with no IAEA radius used.  
5. **Holdout seal (Phase B prep):** freeze data path + hash + split rule **without**
   computing holdout residuals in this loop.

## 3. Claims

| ID | Claim |
|---|---|
| NP12c-C1 | Source census completed; locations recorded. |
| NP12c-C2 | Uniform-sphere √(3/5) identity validated (math instrument). |
| NP12c-C3 | Identity map `R_RMS = R_boundary` classified **UNDERIVED** (surface-charge endpoint; periphery strength not derived). |
| NP12c-C4 | Uniform map `R_RMS = √(3/5) R_boundary` classified **GEOMETRIC-IDENTITY under uniform density** — density premise itself **UNDERIVED** as an SDT nuclear charge law. |
| NP12c-C5 | No executable native Map freezes in this loop ⇒ Phase A status **`MAP_UNDERIVED`**; Phase B **SEALED**. |
| NP12c-C6 | No retrofit conversion fitted to IAEA; no EMPIRICALLY SURVIVES claim. |

## 4. Rejection of shortcuts

- Do not revive `√(3/5)` as a fit factor to improve RMS residual.  
- Do not relabel the IAEA column as “boundary radius.”  
- Do not edit `laws.hpp` correspondence comments in this loop.

## 5. Phase B (sealed — not executed here)

When a native Map freezes:

- Data: `Datasets/nuclear/IAEA_ground_states_radii.csv` (hash in NP12b source freeze).  
- Split: holdout = odd mass number `A` with `A ≥ 16`; calibration diagnostics (if any)
  use even `A` only — **no coefficient update from either half**.  
- Gate: pre-register `RMS_rel(holdout)` threshold in a new amendment before opening.
