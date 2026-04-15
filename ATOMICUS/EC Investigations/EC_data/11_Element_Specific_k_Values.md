# Element-Specific Convergence Constants (k = c/v₀)

> Navigation: [Redshift Tables](10_Gravitational_Redshift_Tables.md) ·
> [Ionisation](04_Ionisation_Series.md)
>
> Investigation: [Empirical Validation](../INVESTIGATION_15_Velocity_Formula_Empirical_Validation.md)

---

## The Corrected Formula

```
k = c / v₀                    (element-specific coupling constant)
v₀ = √(2 × IE₁ / mₑc²) × c   (ground state valence velocity from IE)
v = (c/k) × √(R/r)            (circulation velocity at any excitation)

where:
  R = ground state orbital radius (from IE₁ via Bohr)
  r = excited state orbital radius (from excitation energy)
  mₑc² = 511,000 eV (electron rest mass energy)

For hydrogen: k = 1/α = 137.036 (exact)
```

### Ground state orbital radius

```
R = a₀ × n² / Z_eff

where:
  a₀ = 52,918 fm = 52.918 pm (Bohr radius)
  n = principal quantum number of valence shell
  Z_eff = n × √(IE₁ / 13.606)  (from IE)
  → R = a₀ × n / √(IE₁ / 13.606) = a₀ × n × √(13.606 / IE₁)
```

---

## Master Table: All EC Closure Elements

| Element | Z | IE₁ (eV) | v₀/c | **k = c/v₀** | Z_eff | n | R (pm) |
|---------|---|----------|------|-------------|-------|---|--------|
| H | 1 | 13.606 | 0.007298 | **137.04** | 1.000 | 1 | 52.92 |
| He | 2 | 24.587 | 0.009810 | **101.94** | 1.344 | 1 | 39.37 |
| **Be** | 4 | 9.323 | 0.006041 | **165.54** | 1.656 | 2 | 127.8 |
| **Ar** | 18 | 15.760 | 0.007854 | **127.34** | 3.229 | 3 | 49.17 |
| **Ca** | 20 | 6.113 | 0.004891 | **204.44** | 2.676 | 4 | 316.4 |
| **Kr** | 36 | 14.000 | 0.007402 | **135.10** | 4.052 | 4 | 210.8 |
| **Cd** | 48 | 8.994 | 0.005933 | **168.55** | 4.086 | 5 | 323.8 |
| **Xe** | 54 | 12.130 | 0.006891 | **145.13** | 4.738 | 5 | 279.6 |
| **Ba** | 56 | 5.212 | 0.004516 | **221.44** | 3.710 | 6 | 515.1 |
| **Yb** | 70 | 6.254 | 0.004948 | **202.12** | 4.062 | 6 | 469.3 |
| **Hg** | 80 | 10.438 | 0.006392 | **156.44** | 5.241 | 6 | 363.4 |

---

## Hydrogen — Complete Verification

k(H) = 137.036, R = a₀ = 52.92 pm

Excited state radii: rₙ = n² × a₀

| State | n | r = n²a₀ (pm) | R/r = 1/n² | √(R/r) | v = (c/k)√(R/r) | v/c | Bohr v/c | Match? |
|-------|---|--------------|-----------|---------|-----------------|-----|----------|--------|
| Ground | 1 | 52.92 | 1.000 | 1.000 | c/137.036 | 0.007297 | 0.007297 | **EXACT** |
| Ly-α | 2 | 211.7 | 0.2500 | 0.5000 | c/274.07 | 0.003649 | 0.003649 | **EXACT** |
| Ly-β | 3 | 476.3 | 0.1111 | 0.3333 | c/411.11 | 0.002432 | 0.002432 | **EXACT** |
| Ly-γ | 4 | 846.7 | 0.0625 | 0.2500 | c/548.14 | 0.001824 | 0.001824 | **EXACT** |
| Ly-limit | ∞ | ∞ | 0 | 0 | 0 | 0 | 0 | **EXACT** |

The formula v = (c/k)√(R/r) reproduces the ENTIRE hydrogen spectrum exactly.
This is not an approximation. It is an identity with the Bohr model.

---

## Beryllium — Excitation State Mapping

k(Be) = 165.54, R = 127.8 pm (2s ground state)

### Extracting excited state radii from energies

Remaining binding at excited state = IE₁ - E_exc.
Effective quantum number: n_eff = Z_eff × √(13.606 / (IE₁ - E_exc))
Excited radius: r = a₀ × n_eff² / Z_eff

| State | E_exc (eV) | Binding (eV) | n_eff | r (pm) | R/r | v/c = (1/k)√(R/r) | v (km/s) |
|-------|-----------|-------------|-------|--------|-----|-------------------|----------|
| Ground 2s² | 0 | 9.323 | 2.000 | 127.8 | 1.000 | 0.006041 | 1,811 |
| 2s2p ³P° | 2.725 | 6.598 | 2.378 | 180.8 | 0.707 | 0.005078 | 1,523 |
| 2s2p ¹P° | 5.277 | 4.046 | 3.034 | 294.6 | 0.434 | 0.003979 | 1,193 |
| 2s3s ³S | 6.457 | 2.866 | 3.604 | 415.7 | 0.307 | 0.003349 | 1,004 |
| 2s3s ¹S | 6.779 | 2.544 | 3.826 | 468.6 | 0.273 | 0.003155 | 946 |
| 2s3p ¹P° | 7.459 | 1.864 | 4.469 | 639.2 | 0.200 | 0.002702 | 810 |
| 2s3d ³D | 7.695 | 1.628 | 4.781 | 731.6 | 0.175 | 0.002524 | 757 |
| IE₁ limit | 9.323 | 0 | ∞ | ∞ | 0 | 0 | 0 |

### Keplerian verification

Every excited state (further from nucleus, larger r) has LOWER velocity.
The profile is strictly Keplerian: v ∝ √(1/r).

| Transition | Velocity ratio | Radius ratio | √(R/r) check |
|-----------|----------------|-------------|--------------|
| ground → 2s2p ³P° | 1,811/1,523 = 1.189 | 127.8/180.8 = 0.707 | √0.707 = 0.841 ✗ |

Wait — v_ground/v_exc = (c/k)/(c/k × √(R/r)) = 1/√(R/r).
So v_ground/v_exc = √(r/R).
1,811/1,523 = 1.189 and √(180.8/127.8) = √1.414 = 1.189 ✓ **EXACT**

The formula reproduces the Keplerian velocity ratio perfectly.

---

## Argon — Excitation State Mapping

k(Ar) = 127.34, R = 49.17 pm (3p ground state, very compact)

| State | E_exc (eV) | Binding (eV) | n_eff | r (pm) | v/c |
|-------|-----------|-------------|-------|--------|-----|
| Ground 3p⁶ | 0 | 15.760 | 3.000 | 49.17 | 0.007854 |
| 3p⁵4s ³P₂ | 11.548 | 4.212 | 5.811 | 184.2 | 0.004055 |
| 3p⁵4s ¹P₁ | 11.828 | 3.932 | 6.010 | 197.1 | 0.003925 |
| 3p⁵4p | 12.9 | 2.86 | 7.047 | 271 | 0.003348 |
| IE₁ limit | 15.760 | 0 | ∞ | ∞ | 0 |

### Key observation

Argon's first excitation requires jumping from 3p⁶ at r=49 pm to 4s at
r=184 pm. This is a 3.75× jump in radius — a massive gap with nothing
in between. The "gear rigidity" manifests as a SPATIAL GAP: no excitation
orbit exists close to the ground state. You must jump FAR to excite.

This is why ρ(Ar) = 0.733 is high — to excite at all, you need 73% of
the energy needed to fully ionise.

---

## Mercury — Excitation State Mapping

k(Hg) = 156.44, R = 363.4 pm (6s ground state)

| State | E_exc (eV) | Binding (eV) | n_eff | r (pm) | v/c |
|-------|-----------|-------------|-------|--------|-----|
| Ground 6s² | 0 | 10.438 | 6.000 | 363.4 | 0.006392 |
| 6s6p ³P°₀ | 4.667 | 5.771 | 8.063 | 658.3 | 0.004751 |
| 6s6p ³P°₁ | 4.886 | 5.552 | 8.220 | 684.3 | 0.004658 |
| 6s6p ³P°₂ | 5.461 | 4.977 | 8.682 | 763.3 | 0.004413 |
| 6s6p ¹P°₁ | 6.704 | 3.734 | 10.023 | 1017.5 | 0.003822 |
| IE₁ limit | 10.438 | 0 | ∞ | ∞ | 0 |

### Triplet splitting mapped spatially

| State | r (pm) | Δr from ³P₀ | v/c |
|-------|--------|-------------|-----|
| ³P₀ | 658.3 | 0 | 0.004751 |
| ³P₁ | 684.3 | +26.0 | 0.004658 |
| ³P₂ | 763.3 | +105.0 | 0.004413 |

The spin-orbit splitting of the ³P state maps to a **physical separation**
of 26–105 pm. The J=2 state sits 105 pm FURTHER from the nucleus than
J=0. In SDT terms: higher angular momentum = wider orbit = slower velocity.

---

## Cross-Element k-Value Pattern

| Element | Closure type | k | k/α⁻¹ (= k/137.036) |
|---------|-------------|---|---------------------|
| H | (reference) | 137.04 | 1.000 |
| He | 1s² | 101.94 | 0.744 |
| Ar | 3p⁶ (rigid) | 127.34 | 0.929 |
| Kr | 4p⁶ (rigid) | 135.10 | 0.986 |
| Xe | 5p⁶ (rigid) | 145.13 | 1.059 |
| Be | 2s² (loose) | 165.54 | 1.208 |
| Cd | 4d¹⁰ | 168.55 | 1.230 |
| Hg | 5d¹⁰/6s² | 156.44 | 1.142 |
| Ca | 4s² (loose) | 204.44 | 1.492 |
| Yb | 4f¹⁴/6s² | 202.12 | 1.475 |
| Ba | 6s² (loose) | 221.44 | 1.616 |

### The pattern

Noble gas closures (rigid gears) have k CLOSE to α⁻¹:
- Ar: 0.929 × α⁻¹
- Kr: 0.986 × α⁻¹ (nearly exact!)
- Xe: 1.059 × α⁻¹

Loose closures (s², f¹⁴) have k MUCH LARGER than α⁻¹:
- Be: 1.208 × α⁻¹
- Ca: 1.492 × α⁻¹
- Ba: 1.616 × α⁻¹

**k/α⁻¹ IS the gear rigidity diagnostic.**
k close to 137 = rigid, tightly coupled to the EM field.
k >> 137 = loose, weakly coupled.
This directly maps the previously identified gear families.

### Kr is almost exactly α⁻¹

k(Kr) = 135.10 vs α⁻¹ = 137.036. Ratio = 0.986.
Krypton's valence electron is coupled to the EM field at almost
exactly the hydrogen strength. This makes Kr the most
"hydrogen-like" noble gas — a potential benchmark element.
