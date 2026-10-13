# GOM27 — Solar Deflection from Shared Depth Profile

> **Status:** PRE-REGISTERED — 2026-08-07  
> **Upstream IC:** GOM26 calibration invariant `ϟ_Sun = 1476.351201 m` (DERIVED from Horizons 2025 pairwise μ; frozen before this instrument runs).  
> **Canon edit:** none.  
> **Evidence rule:** codebase audits and prior investigation assessments are not inputs.

## 1. Objective

Test whether the same far-frame profile

```text
c_far(r) = c (1 − ϟ/r)²
n(r)     = c / c_far(r) = 1/(1 − ϟ/r)²
```

with **frozen** GOM26 `ϟ` predicts solar light deflection `δ(b)` over a pre-registered impact-parameter scan, without a new coefficient.

## 2. Weak-field analytic claim (derived before numerical unblinding)

For `z = ϟ/r ≪ 1`:

```text
n(r) = (1 − z)⁻² = 1 + 2z + 3z² + O(z³) = 1 + 2ϟ/r + O((ϟ/r)²)
```

Isotropic spherical refractive deflection at impact parameter `b` has leading term

```text
δ_wf(b) = 4 ϟ / b
```

(equivalent to engine comment `bending = 2 ∫ ∇⊥z dl` on a straight path).  
Numerical ray tracing must recover `δ_wf` in the weak field; residual is O(z) content, not a free amplitude.

## 3. Numerical method (frozen)

Turning point: `b = n(r₀) r₀`.  
Half-angle integral (u = r₀/r):

```text
φ_half = ∫₀¹ n(r₀) du / √( n(r₀/u)² − n(r₀)² u² )
δ = 2 φ_half − π
```

Scan (one pass, no mid-run drop):

```text
b/R_Sun ∈ {1.01, 1.05, 1.1, 1.2, 1.5, 2, 3, 5, 10}
```

plus limb `b = R_Sun` as a reported point (not the sole adjudicator).

## 4. Prohibited inputs

- Retuning `ϟ` after seeing `δ`  
- Importing PPN `γ` or GR `GM` as SDT inputs  
- Using prior audit/assessment Markdown as a status or number source  
- Hand-selecting a single `b` after residuals are seen

## 5. Data gate (D5)

Frozen sources under `Datasets/solar_propagation_2026-08/raw/`:

- Fomalont et al. 2009 VLBA paper (PDF/HTML) — differential source offsets vs solar elongation.  
- Classification: published reductions that fit a PPN propagation model are **MODEL-PROCESSED**.  
- Admissible use: (a) COMPUTED prediction ledger always; (b) empirical comparison only if a row supplies impact parameter / elongation and a differential angle with uncertainty that can be compared without inserting `γ` as an SDT input.  
- If only a global `γ` summary is usable → empirical status **PENDING_DATA** or **UNADJUDICATED**, never EMPIRICALLY SURVIVES.

## 6. Decision rules

1. Instrument validation before solar ledger:
   - A: reduced-`ϟ` case → `δ ≈ 4ϟ/b` within 5%  
   - B: solar `ϟ` at `b = 5 R_Sun` → `|δ − 4ϟ/b|/(4ϟ/b) < 0.02`  
   - C: step refinement `< 1e-3`  
   - D: turning identity `|n r₀ − b|/b < 1e-10`
2. Publish whole-range COMPUTED `δ(b)` vs `δ_wf(b)`.  
3. If an admissible (b, δ_obs, σ) table is frozen: exclude a bin if `|δ_pred − δ_obs| > 2σ` with no post-hoc drop.  
4. Limb literature ~1.75″ alone → at most UNADJUDICATED (single-point, reduction-dependent).

## 7. Cassini D4 side note

ODF/TDF products may be checksummed in the same dataset root. This loop does **not** adjudicate a ranging residual. D4 remains PENDING_DATA until an independent residual is reconstructed.
