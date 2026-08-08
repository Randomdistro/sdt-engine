# GOM26 — Solar Deflection from the Shared Depth Profile

> **Status:** PRE-REGISTERED — 2026-08-07  
> **Depends on:** GOM25b frozen invariant `ϟ_Sun = 1476.664 m` (no retuning)  
> **Canon edit:** none

## 1. Objective

Test whether the same `c_far = c(1 − ϟ/r)²` profile that survived the GOM25b
spectral compatibility check predicts solar light deflection as a function of
impact parameter, without introducing a new coefficient.

## 2. Mechanism (operational)

Ray path in the far-frame refractive picture implied by variable relay speed:

```text
n(r) = c / c_far(r) = 1 / (1 − ϟ/r)²     for 0 ≤ ϟ/r < 1
```

Compute the deflection angle `δ(b)` by numerical ray tracing (Snell / eikonal
or impact-parameter ODE) for impact parameters covering at least

```text
b ∈ [1.01, 1.05, 1.1, 1.2, 1.5, 2, 3, 5, 10] R_Sun
```

in one pass. Weak-field analytic expansion must be derived before unblinding
any observational comparator table.

## 3. Prohibited inputs

- Fitting a deflection amplitude after looking at data  
- Importing a GR/PPN γ parameter as an SDT input  
- Changing ϟ from the GOM25b freeze  
- Using only the b = R_Sun point

## 4. Data gate

Locate a primary or minimally processed solar-deflection dataset with stated
impact parameter (or solar offset) and uncertainty. If only a single limb
value with model-dependent reduction is available, label MODEL-PROCESSED and
cap status at UNADJUDICATED even if numerically close.

## 5. Decision rules (pre-registered)

1. Instrument validation on a constant-n null path (δ=0) and on a known analytic
   weak-field refractive profile before solar application.  
2. Whole-range residual report vs the held-out deflection table.  
3. Exclusion if any pre-registered b-bin fails a 2σ residual rule with no
   post-hoc bin drop.  
4. If no admissible table is frozen this cycle → PENDING_DATA; still publish
   the SDT `δ(b)` curve as a COMPUTED prediction ledger.

## 6. Downstream

Success does not promote spectral UNADJUDICATED → EMPIRICALLY SURVIVES.  
Failure excludes the shared-profile claim for deflection under this n(r).
