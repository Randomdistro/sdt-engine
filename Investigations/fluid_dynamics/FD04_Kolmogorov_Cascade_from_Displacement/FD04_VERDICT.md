# FD04 — Verdict: The Kolmogorov −5/3 Cascade as the Displacement Cascade

**Author:** James Christopher Tyndall, Melbourne
**Status:** EXECUTED — compiled (MSVC `cl /std:c++20 /EHsc /O2`) and run; output in `fd04_results.txt`, derivation in `FD04_DERIVATION.md`.

---

## Decision

> **CLASS A for the EXPONENT** — the `−5/3` spectral exponent is cleanly **DERIVED** from a constant-energy-flux dimensional analysis on the volume-conserved displacement cascade, with **no inserted exponent**.
>
> **QUALIFIED to CLASS C overall** — because the Kolmogorov constant `C_K (≈1.5)` is **OPEN/PENDING** (not derived from a lattice shell count) and intermittency is **OPEN** (not predicted, not fabricated). The exponent is the result; the prefactor is not.

This is exactly the disposition `PROMPT.md §5` defines: the exponent chain is exact and the measured/synthetic slope match is within `−1.667 ± 0.05`, the microscale is DERIVED and floored, but `C_K` and intermittency remain open ⇒ **C (QUALIFIED — convergence)**, with the exponent itself earning Class A.

---

## The deciding metric

| Quantity | Predicted (pre-registered, R1) | Result | Verdict |
|---|---|---|---|
| spectral exponent `b` | `−5/3 = −1.666667` | **`−1.6666666667`** (2×2 dimensional solve, computed not typed) | **DERIVED ✓** |
| ε-power `a` | `2/3 = 0.666667` | `0.6666666667` | DERIVED ✓ |
| velocity exponent | `+1/3` | `0.333333 ± 9.5×10⁻¹⁷` (ledger fit) | DERIVED ✓ |
| numeric slope (independent fit) | `−1.667 ± 0.03` | `−1.666804 ± 6×10⁻⁴` over ~3 decades | PASS ✓ |
| inertial width exponent | `Re^{3/4}` | `0.750000 ± 3.9×10⁻¹⁵` | DERIVED ✓ |
| microscale floor | `η ≥ ℓ_P` | `η(ε_max) = ℓ_P = 1.616255×10⁻³⁵ m` exactly; ordinary fluids `η/ℓ_P ∼ 10³⁰` | PASS ✓ |
| `C_K` | (held open) | not derived; not fitted to 1.5 | **OPEN/PENDING** |
| intermittency | (held open) | `−5/3` is leading order only | **OPEN** |

All five checkpoints C1–C5 PASS (C5 = intermittency catalogued OPEN, the honest pass).

---

## Provenance × correspondence audit (Theory/05 spine)

- **provenance_status: SDT-first (derived).** The `−5/3` is produced from SDT primitives only: volume-conserved displacement cascade (axiom 1) → constant flux (Law I/III relay, axiom 2) → `u_ℓ ∝ ℓ^{1/3}` → dimensional closure on `{E, ε, k}`. The only external numbers are `c`, `ℓ_P` (whitelist) and the per-dataset measured `ν, ε` (measured-units inputs, legitimate per R2). No G, no M, no fields, no wavefunctions entered.
- **correspondence_status: known-match (convergence).** `−5/3`, `η = (ν³/ε)^{1/4}`, `Re^{3/4}` are the canonical Kolmogorov K41 results (Grant–Stewart–Moilliet 1962 tidal channel; Saddoughi–Veeravalli 1994; Comte-Bellot–Corrsin 1971; Kaimal 1972). These are the **convergence targets reproduced, never borrowed**.
- **Delete-test (C is not plagiarism):** removing the correspondence check (the comparison to K41) leaves the derivation unchanged — the exponent still falls out of the 2×2 dimensional solve. The match is convergence, not import.

**Projected class:** A (exponent) / C (overall, prefactor pending).

---

## What is DERIVED vs OPEN

| Item | Label |
|---|---|
| `E(k) ∝ k^{−5/3}` spectral exponent | **DERIVED** (Class A) |
| `u_ℓ = (εℓ)^{1/3}` eddy-velocity law | **DERIVED** |
| `η = (ν³/ε)^{1/4}`, `u_η = (νε)^{1/4}`, `t_η = (ν/ε)^{1/2}` | **DERIVED** |
| `L/η ∝ Re^{3/4}` inertial-range width | **DERIVED** |
| `η ≥ ℓ_P` spation floor | **DERIVED** (deep-limit `ν → ℓ_P·c`) |
| `ν = (geom)·ℓ_P·c` | REFERENCED (FD02) — not re-derived here |
| `ε` per dataset | MEASURED-INPUT (reported forcing; NOT fitted to spectrum) |
| `C_K ≈ 1.5` (prefactor) | **OPEN / PENDING** — needs a lattice shell-count derivation |
| intermittency correction (`≈ −1.71`) | **OPEN** — not predicted, not fabricated |

---

## Honesty notes (R1/R2/R4/R5)

- **R5 (anti-numerology):** the `5/3` is the **output** of a linear solve on the dimensions `[E]=L³T⁻²`, `[ε]=L²T⁻³`, `[k]=L⁻¹`. It is never typed in. The compensated-spectrum plateau (≈1.0002) is a flatness *diagnostic only* and is explicitly **not** claimed as `C_K`.
- **R2 (ledger):** every constant is tagged; the only fitted-looking numbers (`ν, ε`) are measured inputs in measured units, exactly as spectral lines are legitimate inputs.
- **R4 (clean kill outranks forced pass):** the core gate C2 would have returned Class F had the dimensional solve produced any exponent `≠ −5/3`; it did not, so the PASS is earned, not retrofitted.
- **R1 (predict before fit):** predictions `+1/3`, `−5/3`, `Re^{3/4}` were logged to stdout before any fitting code ran.

---

## Downstream handoffs

FD04 is currently a leaf of the FD branch (no downstream unblocked). Two future items are now sharply posed:

1. **`C_K` from lattice geometry** — a shell-count / coarse-graining argument that fixes the prefactor `≈1.5` would upgrade FD04 from C to A (CALIBRATED(0)). Candidate follow-up: FD04b.
2. **Intermittency** — whether the volume-conserved cascade admits a multiplicative-cascade correction to higher-order structure functions, or whether the leading-order `−5/3` is the whole SDT prediction. Held OPEN.
