# FD04 — Derivation: The Kolmogorov −5/3 Cascade as the Displacement Cascade

**Author:** James Christopher Tyndall, Melbourne
**Status:** EXECUTED (compiled MSVC `/std:c++20`, run verbatim — see `fd04_results.txt`)
**Inherits:** §0 anti-creep protocol + rules R0–R5 (whitelist inputs `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}`; no G/M; no fields/wavefunctions; certification labels on every result; honesty over success).

---

## 0. One-line thesis

The turbulent inertial-range cascade is the SDT **volume-conserved displacement cascade** in rate-form. A large eddy is a large displaced lattice volume; the lattice relays only to contacting neighbours at one tick, so the eddy cannot dissipate directly — it **hands its displaced volume down** to a finer nested displacement at a fixed rate `ε`. The inertial range is the band where this handoff is conservative (no injection, no dissipation): a **constant-flux pipe**. From constant flux alone the `−5/3` exponent is forced.

---

## 1. SDT axioms used (no new primitives)

1. **Displacement cascade with volume conservation** (verified SDT result). A displaced lattice volume propagates outward shell-by-shell with the displaced volume conserved → amplitude `u(r) ∝ 1/r²`, strain `ε_strain(r) ∝ 1/r³`. Turbulence's inertial range is the **per-unit-time** form of this same conservative handoff. (Distinct from the koppa depth `z = ϟ/r ∝ 1/r` — the cascade is steeper, volume-conserving.)
2. **Constant-flux invariant** (Law I / Law III relay). No injection and no dissipation in the interior ⇒ energy passed per unit mass per unit time `ε` is **scale-independent**: `ε(ℓ) = const` for `η ≪ ℓ ≪ L`.
3. **Movement budget** (Law V). `v_circ² + v_trans² = c²` caps every eddy velocity at `c`; the cascade is finite and bounded, not runaway.
4. **Relay smoothing = dissipation** (FD02, Law III). The diffusion term `ν∇²v` outcompetes inertial handoff at small scales; the crossover defines the microscale. `ν = (geom)·ℓ_P·c` referenced from FD02.

Upstream dependencies: the displacement-cascade result, FD01 (NS root), FD02 (`ν`), engine `laws.hpp` (`measured::c`, `measured::l_P`). **No constant that `laws.hpp` exposes is redefined.**

---

## 2. The chain (each link DERIVED, no inserted exponent)

### Step A — eddy velocity from constant flux

The displacement handed down per unit time at scale `ℓ` is the eddy's kinetic content `u_ℓ²` divided by its turnover (relay) time `τ_ℓ = ℓ/u_ℓ`. Constant flux (axiom 2):

```
ε = u_ℓ² / τ_ℓ = u_ℓ³ / ℓ = const     ⟹     u_ℓ = (ε ℓ)^{1/3} ∝ ℓ^{1/3}.
```

This is the **only** `u_ℓ(ℓ)` consistent with volume-conserved shell-by-shell handoff at fixed rate. *(Program Phase 1: a 24-shell log-uniform ledger `ℓ_n = L·2^{−n}` confirms `ε_n = u_n³/ℓ_n` constant to 5.6×10⁻¹⁶ and recovers the fitted exponent `0.333333 ± 9.5×10⁻¹⁷`.)*

### Step B — spectrum by dimensional flux closure on `{ε, k}` (THE result)

Write the spectrum as a power law in the cascade invariant and the wavenumber:

```
E(k) = C_K · ε^a · k^b .
```

Dimensions (in Length L, Time T):

```
[E]   = L³ T⁻²       (energy per unit mass per unit wavenumber)
[ε]   = L²  T⁻³       (energy flux per unit mass = dissipation rate)
[k]   = L⁻¹ T⁰        (wavenumber)
```

Matching L and T powers gives a **2×2 linear system** for `(a, b)`:

```
a·(2) + b·(−1) = 3        (Length balance)
a·(−3) + b·(0) = −2       (Time balance)
```

Solving (the program does this by Cramer's rule — the numbers are **computed, never typed**):

```
a = 2/3,   b = −5/3.
```

Hence

```
E(k) = C_K · ε^{2/3} · k^{−5/3}.
```

The exponent `−5/3` is **forced** by the dimensions of `{E, ε, k}`, which encode `u_ℓ ∝ ℓ^{1/3}`, which was forced by constant flux, which was forced by volume conservation. A clean chain with **no fitted exponent**.

*Program Phase 2a output:* `a = 0.6666666667`, `b = −1.6666666667` (agrees with `2/3`, `−5/3` to 1×10⁻¹⁰).
*Program Phase 2b cross-check (R3 two-stream):* a synthetic constant-flux spectrum built from the **derived** `u_ℓ` (with 1% scatter) re-fits a log-log slope of `−1.666804 ± 6×10⁻⁴` over ~3 decades — independent of the analytic solve. The compensated spectrum `E(k)·k^{5/3}/ε^{2/3}` is flat (4.2% spread), the cleanest `−5/3` signature.

### Step C — dissipation microscale and the ℓ_P floor

Relay smoothing balances inertial handoff where the scale-local Reynolds number is order unity, `Re_ℓ = u_ℓ ℓ / ν ∼ 1`. With `u_ℓ = (εℓ)^{1/3}`:

```
(εℓ)^{1/3} ℓ / ν = 1   ⟹   ℓ^{4/3} = ν / ε^{1/3}   ⟹   η = (ν³/ε)^{1/4}.
```

Companion scales: `u_η = (νε)^{1/4}`, `t_η = (ν/ε)^{1/2}` — all **DERIVED, not inserted**. Inertial-range width `L/η ∝ Re^{3/4}` (program Phase 3 fit: exponent `0.750000 ± 3.9×10⁻¹⁵`).

**Spation floor.** In the deep limit `ν → ν_lattice ∼ ℓ_P·c` (FD02 form), the smallest `η` the lattice permits is one shell, `η = ℓ_P`. The `ε` that would drive `η` down to `ℓ_P` is `ε_max = ν³/ℓ_P⁴ = 1.667×10⁶⁰ m²/s³`; at that `ε`, `η = ℓ_P = 1.616255×10⁻³⁵ m` exactly. **No physical `ε` gives `η < ℓ_P`** — the lattice has no finer shell. For ordinary fluids `η/ℓ_P ∼ 10³⁰–10³¹` (sample microscales `η ∼ 10⁻⁴ m`), enormously above the floor.

---

## 3. Parameter ledger (R2)

| Symbol | Meaning | Status | Source |
|---|---|---|---|
| `c` | speed of light = ℓ_P/t_P | MEASURED-INPUT (whitelist) | `laws.hpp measured::c` |
| `ℓ_P` | Planck length (lattice shell) | MEASURED-INPUT (whitelist) | `laws.hpp measured::l_P` |
| `a = 2/3` | power of ε in E(k) | **DERIVED** (2×2 dimensional solve) | this work, Step B |
| `b = −5/3` | spectral exponent | **DERIVED** (2×2 dimensional solve) | this work, Step B |
| `u_ℓ ∝ ℓ^{1/3}` | eddy velocity law | **DERIVED** (constant flux) | Step A |
| `η = (ν³/ε)^{1/4}` | dissipation microscale | **DERIVED** (`Re_ℓ ∼ 1`) | Step C |
| `L/η ∝ Re^{3/4}` | inertial-range width | **DERIVED** | Step C |
| `ν` | kinematic viscosity | MEASURED-INPUT / referenced FD02 (`ν = geom·ℓ_P·c`) | FD02, fluid tables |
| `ε` | cascade invariant (dissipation rate) | MEASURED-INPUT per dataset (NOT fitted to spectrum) | reported forcing |
| `C_K ≈ 1.5` | Kolmogorov constant (prefactor) | **OPEN / PENDING** — not derived from a lattice shell count | — |
| intermittency | anomalous-scaling correction to `−5/3` | **OPEN** — not predicted, not fabricated | — |

R5 anti-numerology compliance: the `5/3` is never inserted. It is the output of a linear solve on the dimensions of `{E, ε, k}`. `C_K` is **not** fitted to 1.5 (the program sets `C_K = 1` for the synthetic and reports the compensated plateau ≈ 1.0002 only as a flatness diagnostic, explicitly labelled "NOT C_K").

---

## 4. What is the result, and what is honestly open

- **The result is the EXPONENT `−5/3`** (and the companion `u_ℓ ∝ ℓ^{1/3}`, microscale `η = (ν³/ε)^{1/4}`, width `Re^{3/4}`, floor `η ≥ ℓ_P`). Each falls out of volume-conserved constant flux with no fitted exponent — **Class A for the exponent**.
- **`C_K ≈ 1.5` is NOT derived here.** Deriving the prefactor would require a lattice/shell-count geometry argument (a future FD04b or CQ). Held PENDING.
- **Intermittency is OPEN.** Real flows show a small anomalous steepening (`≈ −1.71` for high-order moments). SDT's volume-conserved cascade as posed predicts no such correction at leading order; the correction is **not fabricated**, it is flagged OPEN.

This matches the Phase tables in `PROMPT.md`: the chain *volume conservation → constant flux → `u_ℓ ∝ ℓ^{1/3}` → −5/3* is delivered; `C_K` and intermittency stay OPEN.
