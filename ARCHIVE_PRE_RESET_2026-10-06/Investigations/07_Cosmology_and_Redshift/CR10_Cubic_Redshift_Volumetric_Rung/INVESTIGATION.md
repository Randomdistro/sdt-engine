# CR10 — The Cubic Redshift: what is z³ for?

**J. C. Harvey, Melbourne — 2026-06-24.** Domain: `07_Cosmology_and_Redshift`.
Tool: `cr10_cubic_redshift.cpp` (engine-coupled) → **5 PASS / 0 FAIL**.

> **Method (as commissioned).** An *excessively detailed, recursively expansive AND reductive* investigation.
> Every node is a **CLAIM** with a numeric **TEST**.
> - **if FAIL** → ask **WHY**, then **TRY** an alternative, and recurse.
> - **if PASS** → **ANALYSE**: find the cause, then the cause of the cause (**cause^n**), reducing to a **ROOT**.

---

## Thesis under test

`z` is not an arbitrary variable. It is *the* SDT variable — the **linear closure deficit**:

```
z = ϟ/r = (v/c)² = 1 − ℓ_P(r)/ℓ_P,∞ = 1 − c_local/c_∞
```

Because `z` is linear in the length-deficit, its powers **ladder through the dimensions of space**:

| power | scales | the SDT quantity |
|---|---|---|
| z¹ | **length** deficit | the redshift / depth itself |
| z² | **area** | already `(v/c)²` — the movement-budget / energy rung |
| **z³** | **volume** | the rung this investigation is about |

**Prediction:** `z³` is "the volumetric rung," and it should appear wherever the **3-ness of space** enters —
both in **real space** (matter density) and in **momentum / k-space** (blackbody photon number).

### The closure ladder (computed)

| regime | z | z² | z³ |
|---|---|---|---|
| Earth surface | 6.95×10⁻¹⁰ | 4.83×10⁻¹⁹ | 3.36×10⁻²⁸ |
| Sun surface | 2.12×10⁻⁶ | 4.50×10⁻¹² | 9.54×10⁻¹⁸ |
| proton surface | **3.349** | 11.2 | 37.6 |

The proton already warns us: `z > 1` there (super-c internal circulation, `v = 1.830c`). Keep that in view.

---

## ARM A — z³ as REAL-space volume (the density of matter)

This arm lands on the standing correction that **matter is substantive (crushed), not a void.**

### A1 — CLAIM: spation number density `n(r)/n_∞ = (1 − z)⁻³`

**TEST.** From depth-closure `ℓ_P(r) = ℓ_P,∞(1 − z)`, volume ∝ `(1−z)³`, so density ∝ `(1−z)⁻³`.
- Earth: `(1−z)⁻³ − 1 = 2.1×10⁻⁹` (≈ 3z, negligible)
- Sun: `6.4×10⁻⁶`
- proton: `1 − z = 1 − 3.349 = −2.349`

> **FAIL.** At the proton `z = 3.35 > 1`, so `(1−z)⁻³` is the cube of a negative — unphysical.

**WHY.** `ℓ_P = ℓ_P,∞(1−z)` is the **first-order (weak-field)** closure; it is invalid once `z ≥ 1`. The proton's
super-c circulation puts it *past the linear horizon* — the linearization, not the physics, broke.

**TRY (a) — exponential closure** `ℓ_P = ℓ_P,∞ e^{−z}` (positive for all z; → `(1−z)` for small z). Then density
`∝ e^{3z}`. At the proton `e^{3·3.349} = 2.3×10⁴`.
> **FAIL.** `4.6×10⁴` does not reach the proton's known spation count (~6×10⁵⁹). Wrong handle entirely.

**TRY (b) — drop the `(1−z)` form; count cells geometrically.** How many *vacuum* spation-cells fit inside the
proton's charge radius: `N_geo = (4/3)π R_p³ / ℓ_P³`.
- `R_p/ℓ_P = 5.21×10¹⁹`, so `N_geo = 5.91×10⁵⁹`.
> **PASS.** Reproduces the proton spation number (5.91×10⁵⁹ vs the known 5.9×10⁵⁹) to 0.2%.

**ANALYSE — and this settles a long-open ambiguity.** There are *two* proton "volumes," both z³-class, that were
being confused:

| count | value | what it measures | radius |
|---|---|---|---|
| `N_geo = V_charge/ℓ_P³` | **5.91×10⁵⁹** | how **big** the proton is | `R_p = 8.41×10⁻¹⁶ m` |
| `N_disp = V_disp/ℓ_P³` | **4.34×10⁴⁶** | how much **throughput** it reorganises (Law IV) | `R_excl = 3.52×10⁻²⁰ m` |

Both are `V/ℓ_P³` (z³ volume counts). They differ by `(R_p/R_excl)³ = 1.36×10¹³` — purely **which radius is
cubed.** The geometric extent and the mass-cost displacement are different volumes; neither is wrong, and z³ is
the language that makes that explicit.

**CAUSE** → `N = V/ℓ_P³` ⇐ counting cells that fill a volume.
**CAUSE²** → a volume is *three* lengths multiplied ⇐ space is 3-dimensional.
**ROOT** → **z³ here = real-space three-dimensionality (cells per volume).**

### A2 — CLAIM: the weak-field `(1−z)⁻³` is useful where it *doesn't* break — as a gradient

**TEST.** `d/dr[(1−z)⁻³] = 3(1−z)⁻⁴ dz/dr` is a **density gradient = a gradient-index lens.**
> **PASS.** Non-zero (Sun-surface scale `≈ 9×10⁻¹⁵ m⁻¹`) → refraction.
**ROOT** → z³'s **radial derivative** is the gradient-index optics of the closure medium (the solar lens-artifact
handle).

---

## ARM B — z³ as the cosmological `(1+z)³` "expansion" signature

### B1 — CLAIM: `u_CMB ∝ (1+z)⁴` is proof of expansion — `(1+z)³ [volume] × (1+z) [energy]`

**TEST.** Does a **static** SDT universe (uniform octave redshift, *no* expansion) give `(1+z)⁴`?
Engine blackbody values check out: `u(T₀) = 4.17×10⁻¹⁴ J/m³`, `n_γ(T₀) = 411 cm⁻³`.

> **FAIL?** Naïve static = redshift only → `u ∝ (1+z)¹`; the `(1+z)³` looks like it *needs* expansion.

**WHY.** Because we assumed `(1+z)³ = real-space expansion volume`.

**TRY — is the `(1+z)³` actually momentum / k-space phase volume, not real space?**
A uniformly-redshifted blackbody **stays a blackbody** at `T' = T₀(1+z)` (Tolman 1934 — true for *any* uniform
redshift, including static). Then `n_γ ∝ T³` and `u ∝ T⁴` follow. Recomputed from `T(z) = T₀(1+z)` alone:

| z | T(z) | n/n₀ | u/u₀ |
|---|---|---|---|
| 1 | 5.451 | 8 = 2³ | 16 = 2⁴ |
| 3 | 10.90 | 64 = 4³ | 256 = 4⁴ |
| 1100 | 3001 | 1.33×10⁹ | 1.47×10¹² |

> **PASS** (max error `0.0`). Static SDT reproduces `u ∝ (1+z)⁴` with **no expansion**: the `(1+z)³` is `n_γ ∝ T³`.

**ANALYSE — cause^n:**
- **CAUSE** → `u ∝ (1+z)⁴` ⇐ Stefan–Boltzmann `u = aT⁴` with `T ∝ (1+z)`
- **CAUSE²** → `T ∝ (1+z)` ⇐ a blackbody stays a blackbody under uniform redshift (Tolman)
- **CAUSE³** → `n_γ ∝ T³` ⇐ density of states `g(ν) ∝ ν²`, integrated to `T³`
- **CAUSE⁴** → `g(ν) ∝ ν²` ⇐ a sphere of radius `k` in 3-D k-space has surface `∝ k²`
- **ROOT** → **z³ here = momentum / k-space three-dimensionality** (NOT real-space expansion).

> **PAYOFF.** *"`u ∝ (1+z)⁴` proves expansion" is false.* It proves **uniform redshift + blackbody**, which
> SDT-static has. The `(1+z)³` is k-space phase volume. **The headline `(1+z)⁴` evidence is degenerate** between
> expansion and static-uniform-redshift.

### B2 — CLAIM: where does z³ as *real-space* volume actually discriminate static vs expansion?

Two non-degenerate handles — and both are honestly **OPEN**:

**D1 — Tolman surface brightness.** `Σ_bol ∝ (1+z)⁻⁴` (expanding, via Etherington `d_L=(1+z)²d_A`) vs
`(1+z)⁻²` (naïve static tired-light, `d_L=(1+z)d_A`). The 2-power gap **is** the reciprocity factor.
- **TRY:** Etherington reciprocity needs only {effective metric, geodesics, photon conservation}. SDT's closure
  gradient is a refractive index `n(r) = 1/(1−z)`; a gradient-index medium **conserves étendue** ⇒ reciprocity
  holds ⇒ `Σ ∝ (1+z)⁻⁴` *statically.* **→ DISCHARGED in [CR11](../CR11_Reciprocity_and_the_Tolman_Test/INVESTIGATION.md):**
  the optical metric is `n_eff=(1−z)⁻²` (validated — it reproduces the `1.75″` solar deflection), Etherington
  gives `(1+z)⁻⁴`, *but the result is **degenerate*** (the aging-glass optical metric ties ΛCDM); it also
  **kills** the path-local tired-light `(1+z)⁻²` for SDT. Surface brightness ties; **counts (D2) decide.**

**D2 — galaxy number counts.** `N(<z) ∝ real-space volume ∝ d(z)³`. Low-z Euclidean baseline `N ∝ z³`; the
high-z **deviation** tests the SDT distance law `d(z)`. **[OPEN — this is the CONDENSA Pantheon+ `d(z)` item.]**

### Data anchor (the linchpin)

`T_CMB(z) = T₀(1+z)` is **measured** to `≈ (1+z)^{1.0}` (Sunyaev–Zel'dovich toward clusters + molecular-cloud
excitation out to z≈3; FIRAS at z=0). Given `T ∝ (1+z)`, both `u ∝ (1+z)⁴` and `n_γ ∝ (1+z)³` are *forced* by
blackbody thermodynamics — **independent of whether the `(1+z)` came from expansion or static octave-relaxation.**

---

## Reduction to root

> **z³ is the signature of three-dimensionality itself.** It appears wherever the "3" of space enters:
> - **real space:** cells per volume → matter density, the proton's `5.9×10⁵⁹`.
> - **momentum (k) space:** `g(ν) ∝ ν²` → `T³` → the cosmic `(1+z)⁴`.

The cosmological `(1+z)⁴`, read everywhere as "expansion volume," is in fact **k-space phase volume** — so a
static, uniformly-redshifting SDT reproduces it exactly, and z³ shows that this most-famous expansion evidence is
**degenerate.** The genuine, non-degenerate fights live in the **real-space** z³ (number counts; surface-brightness
reciprocity), and there SDT's refractive closure medium *plausibly* supplies the missing powers for free — but
that is owed, not done.

## Ledger

**[EARNED]**
- z³ as the volumetric rung of the closure ladder (length/area/volume ↔ z/z²/z³).
- the proton spation count `5.9×10⁵⁹ = V_charge/ℓ_P³`, and the resolution of the two-count ambiguity
  (geometric extent vs displacement cost — different radii cubed, ratio `1.4×10¹³`).
- **static SDT reproduces `u ∝ (1+z)⁴` exactly**, with the `(1+z)³` identified as k-space (not expansion) →
  the `(1+z)⁴` "expansion proof" is degenerate.

**[OPEN]**
- the Etherington/étendue reciprocity proof in the closure medium (would deliver Tolman `Σ ∝ (1+z)⁻⁴` statically).
- the SDT distance law `d(z)` and galaxy number counts vs Pantheon+ (the real discriminant).
- the exact (non-linear) closure law that replaces `(1−z)` for `z ≥ 1` (the proton interior).

**[KILLED]**
- `(1−z)⁻³` as the proton density law (breaks at `z > 1`); and `e^{−z}` closure as the proton-count handle
  (gives `10⁴`, not `10⁵⁹`).

## Run it

```bat
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
   Investigations\07_Cosmology_and_Redshift\CR10_Cubic_Redshift_Volumetric_Rung\cr10_cubic_redshift.cpp
cr10_cubic_redshift.exe        :: → 5 PASS / 0 FAIL; prints the full recursion tree
```
