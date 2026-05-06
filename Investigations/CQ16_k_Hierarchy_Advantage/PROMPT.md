# CQ16: The k-Hierarchy Advantage — Mathematical Framework

> **Category**: Foundations / Gravitational Variables / Cross-Scale Bridge
> **Status**: RESOLVED (15/15 pass)

---

## 1. Definitions

| Symbol | Name | Formula | Meaning |
|--------|------|---------|---------|
| k | Velocity ratio | c / v | The ratio of the speed of light to the characteristic velocity v at a body's surface. k is dimensionless and runs continuously across all scales. |
| v | Surface velocity | c / k | The velocity of circulation or orbital motion at the body's surface. For superluminal bodies (k < 1), this is a phase velocity, not a group velocity. |
| z | Spation depth | v² / c² = 1/k² | The fractional convergence deficit at the body's surface. z measures how "loaded" the lattice is. |
| ϟ (koppa) | c-boundary | v²R / c² = R/k² | The radius at which v = c. One number encodes the entire gravitational field. Units: metres. |
| G | Newton's constant | 6.674×10⁻¹¹ m³kg⁻¹s⁻² | The coupling constant in F = Gm₁m₂/r². Known to only 22 ppm — the worst-measured fundamental constant. |
| M | Mass | kg | The "gravitational mass" of a body. Only knowable via GM/G, inheriting G's 22 ppm uncertainty. |
| GM | Gravitational parameter | m³/s² | The product G×M, measurable to ~10⁻¹⁰ relative precision from orbital dynamics. In SDT: GM = ϟc². |
| α | Fine structure constant | 7.297×10⁻³ | = e²/(4πε₀ℏc). In SDT: k_hydrogen = 1/α. |
| r_e | Classical electron radius | 2.818×10⁻¹⁵ m | = α²a₀ = αƛ_Ce. In SDT: ϟ_hydrogen = r_e (the koppa identity). |
| a₀ | Bohr radius | 5.292×10⁻¹¹ m | Radius of the hydrogen ground-state orbit. |
| R_p | Proton charge radius | 8.414×10⁻¹⁶ m | From muonic hydrogen spectroscopy. SDT predicts: R_p = 4ℏ/(m_p c) to 0.02%. |

---

## 2. The Thesis

**GM requires an orbital test particle to exist as a measurement.**

If nothing orbits a body — no satellite, no flyby, no radar bounce — then GM is operationally undefined. You cannot measure it.

**k = c/v requires only the body itself.**

Every body with a surface velocity v has a well-defined k. Every body with a radius R has a well-defined ϟ = v²R/c². No test particle needed.

This means:
- k describes the proton (GM_proton ≈ 10⁻³⁷ — never measured, never will be)
- k describes the electron (GM_electron ≈ 10⁻⁴¹ — meaningless)
- k describes isolated neutron stars (GM requires a companion)
- k connects nuclear physics to stellar physics (GM has no cross-scale bridge)

---

## 3. Mathematical Framework

### 3.1 The k-Hierarchy Table

k = c/v is one formula applied at every scale:

| Body | v | k = c/v | R | ϟ = v²R/c² | ϟ equals... |
|------|---|---------|---|------------|-------------|
| Proton surface | 1.831c | 0.5464 | 8.414×10⁻¹⁶ m | 2.818×10⁻¹⁵ m | **r_e** |
| Hydrogen (n=1) | αc | 137.036 | 5.292×10⁻¹¹ m | 2.818×10⁻¹⁵ m | **r_e** (same!) |
| Sun | 4.368×10⁵ m/s | 686.3 | 6.957×10⁸ m | 1477 m | r_S/2 |
| Earth | 7909 m/s | 37,905 | 6.371×10⁶ m | 4.43×10⁻³ m | 4.43 mm |
| Moon | 1680 m/s | 178,448 | 1.737×10⁶ m | 5.46×10⁻⁵ m | 0.055 mm |

**k spans from 0.5464 to 178,448 — a factor of 326,000 — with ONE formula.**
GM has a different, unrelated value for each body with no connection between entries.

### 3.2 The Koppa Identity: ϟ_hydrogen = r_e

This is the central prediction that GM structurally cannot make.

**Derivation:**

The hydrogen ground state has v = αc (the Bohr velocity), R = a₀ (the Bohr radius).

```
ϟ_hydrogen = v² R / c²
           = (αc)² · a₀ / c²
           = α² · a₀
```

Now, α² · a₀ can be rewritten using the definition of a₀:

```
a₀ = ℏ / (m_e α c)     [Bohr radius from ℏ, m_e, α, c]
```

Substituting:

```
α² · a₀ = α² · ℏ / (m_e α c) = α ℏ / (m_e c)
```

But αℏ/(m_e c) = α × ƛ_Ce (the reduced Compton wavelength of the electron). And by definition:

```
r_e = α × ƛ_Ce = α ℏ / (m_e c) = 2.818 × 10⁻¹⁵ m
```

Therefore:

```
ϟ_hydrogen = α² a₀ = α ƛ_Ce = r_e     ✓
```

**The c-boundary of the hydrogen atom IS the classical electron radius.** This is an exact algebraic identity.

**What does GM give?** GM_proton = G × m_p = 6.674×10⁻¹¹ × 1.673×10⁻²⁷ = 1.12×10⁻³⁷ m³/s². Dividing by c²: 1.24×10⁻⁵⁴ m. This is 10³⁹ times SMALLER than the Planck length. It has no physical meaning at any measurable scale.

### 3.3 The G-Uncertainty Problem

G = 6.67430(15)×10⁻¹¹ m³ kg⁻¹ s⁻².

The number in parentheses (15) is the standard uncertainty in the last two digits. The relative uncertainty is:

```
δG/G = 0.00015×10⁻¹¹ / 6.67430×10⁻¹¹ = 2.2×10⁻⁵ = 22 ppm
```

This makes G the **worst-measured fundamental constant in physics**. Every other constant (c, ℏ, e, α, k_B) is known to parts per billion or better.

GM_Sun is known to ~10 significant figures from planetary ephemerides (DE440, via radar ranging to spacecraft). But:

```
M_Sun = GM_Sun / G
```

This division injects G's 22 ppm uncertainty into M_Sun, destroying 5 orders of magnitude of precision. We LOSE information by decomposing GM.

**SDT's approach**: ϟ = v²R/c². No G. No M. No decomposition. No precision loss.

### 3.4 The (p,q) Proton Radius Prediction

From the winding namespace:

```
R_p = (W+1) ℏ / (m_p c) = 4ℏ / (m_p c)
```

where W = 3 is the trefoil winding number. This predicts:

```
R_p = 4 × 1.0546×10⁻³⁴ / (1.6726×10⁻²⁷ × 2.998×10⁸) = 8.412×10⁻¹⁶ m
```

Measured: 8.414×10⁻¹⁶ m. **Agreement: 0.02%.**

GM cannot predict the proton charge radius. It does not know what a proton IS.

---

## 4. Capability Comparison

| Capability | k / ϟ | GM |
|------------|-------|-----|
| Describe the proton | **YES** (k=0.546) | NO (GM unmeasurable) |
| Describe the electron | **YES** (k=137) | NO (GM meaningless) |
| Describe isolated bodies | **YES** (v and R suffice) | NO (needs orbiter) |
| Connect nuclear → stellar | **YES** (one formula) | NO (different numbers) |
| Predict R_p | **YES** (0.02%) | NO |
| Predict stellar rotation | **YES** (v_rot=πv²/c) | NO |
| Predict pressure domain | **YES** (r_domain) | NO |
| Predict orbital dynamics | **YES** (ϟc²=GM) | YES |
| Need G (22 ppm) | **NO** | YES |
| Need separate M | **NO** | YES |
| Need test particle | **NO** | YES |

---

## 5. Verdict

GM is ϟ × c². It is a **derived quantity** — the projection of the c-boundary onto the macroscopic measurement scale. Newton found the projection. SDT found the source.
