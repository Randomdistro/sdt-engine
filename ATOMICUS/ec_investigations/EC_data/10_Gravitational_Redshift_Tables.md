# Gravitational Redshift Tables (zk²=1) and Velocity Maps (v=(c/k)√(R/r))

> Navigation: [Master Table](01_All_EC_Isotopes_Master_Table.md) ·
> [Ionisation](04_Ionisation_Series.md) · [Spectral Lines](07_Spectral_Lines_And_Series.md)
>
> Investigation: [Gravitational Redshift](../INVESTIGATION_10_Gravitational_Redshift.md)

---

## Formulae

```
z = E_excitation / E_R = E / 13.606 eV     (dimensionless depth)
k = 1/√z = √(13.606 / E)                   (convergence coupling)
v = (c/k)·√(R/r) = c·√z·√(R/r)              (circulation velocity)

where:
  E_R  = 13.606 eV (Rydberg / hydrogen 1s binding)
  c    = 299,792,458 m/s
  R    = nuclear charge radius (fm)
  r    = shell radius (pm, computed from IE via Bohr model or measured)
```

### Shell radius estimation

For hydrogen-like systems: r_n = a₀ × n² / Z_eff
- a₀ = 52,917.7 fm = 52.918 pm (Bohr radius)
- Z_eff = effective nuclear charge at that shell
- From IE: Z_eff = √(IE / 13.606) × n

For multi-electron atoms, use measured radial expectation values
where available; otherwise estimate from Slater's rules.

---

## Beryllium (Z=4, R = 2.646 fm)

### Excitation States (Be I — neutral)

| State | Config | E (eV) | z = E/13.606 | k = 1/√z | v/c = (1/k)√(R/r) | r (pm) | v/c computed |
|-------|--------|--------|-------------|----------|-------------------|--------|-------------|
| Ground | 2s² ¹S₀ | 0 | 0 | ∞ | — | — | — |
| 2s2p ³P° | triplet | 2.725 | 0.2003 | 2.234 | — | 125 | (1/2.234) × √(2.646e-6/125e-3) = 0.4476 × 0.004601 = **0.002060** |
| 2s2p ¹P° | singlet | 5.277 | 0.3879 | 1.606 | — | 105 | (1/1.606) × 0.005018 = 0.6227 × 0.005018 = **0.003124** |
| 2s3s ³S | | 6.457 | 0.4746 | 1.452 | — | 220 | (1/1.452) × 0.003468 = 0.6887 × 0.003468 = **0.002388** |
| 2s3s ¹S | | 6.779 | 0.4983 | 1.416 | — | 225 | (1/1.416) × 0.003427 = 0.7062 × 0.003427 = **0.002420** |
| 2s3p ¹P° | | 7.459 | 0.5482 | 1.351 | — | 250 | (1/1.351) × 0.003253 = 0.7402 × 0.003253 = **0.002408** |
| 2s3d ³D | | 7.695 | 0.5656 | 1.330 | — | 270 | (1/1.330) × 0.003130 = 0.7519 × 0.003130 = **0.002353** |
| IE₁ | 2s² → 2s¹ | 9.323 | 0.6852 | 1.208 | — | 106 | (1/1.208) × 0.004997 = 0.8278 × 0.004997 = **0.004137** |

### Ionisation States (all four IEs as excitations from ground)

| Transition | E (eV) | z | k | Equivalent orbital r (pm) | v/c = (1/k)√(R/r) |
|-----------|--------|---|---|--------------------------|--------------------|
| 1st IE (2s outer) | 9.323 | 0.685 | 1.208 | 106 | 0.00414 |
| 2nd IE (2s inner) | 18.211 | 1.338 | 0.864 | 76 | 0.00683 |
| 3rd IE (1s outer) | 153.896 | 11.31 | 0.297 | 17.4 | 0.04154 |
| 4th IE (1s inner) | 217.718 | 16.00 | 0.250 | 13.2 | 0.05664 |

### Lyman-series analogy for Be

The "Lyman series" of Be maps transitions TO the deepest accessible state:

| Series | Transition | ΔE (eV) | λ (nm) | Analogy |
|--------|-----------|---------|--------|---------|
| "Lyman-α" | 2s2p ¹P° → 2s² ¹S₀ | 5.277 | 234.9 | UV |
| "Lyman-β" | 2s3s → ground | 6.457 | 192.0 | UV |
| "Lyman-γ" | 2s3p → ground | 7.459 | 166.2 | VUV |
| "Lyman limit" | IE₁ | 9.323 | 133.0 | VUV |

### Balmer-series analogy for Be

Transitions TO the first excited state:

| Series | Transition | ΔE (eV) | λ (nm) |
|--------|-----------|---------|--------|
| "Balmer-α" | 2s3s ³S → 2s2p ³P° | 3.732 | 332.1 | 
| "Balmer-β" | 2s3d ³D → 2s2p ³P° | 4.970 | 249.5 |

---

## Argon (Z=18, R = 3.43 fm est.)

### Excitation States (Ar I — neutral)

| State | Config | E (eV) | z = E/13.606 | k = 1/√z | r (pm) est. | v/c |
|-------|--------|--------|-------------|----------|------------|-----|
| Ground | 3p⁶ ¹S₀ | 0 | 0 | ∞ | — | — |
| 3p⁵4s ³P₂ | metastable | 11.548 | 0.849 | 1.086 | 175 | 0.004808 |
| 3p⁵4s ³P₀ | metastable | 11.723 | 0.862 | 1.077 | 175 | 0.004768 |
| 3p⁵4s ¹P₁ | resonance | 11.828 | 0.869 | 1.073 | 175 | 0.004751 |
| 3p⁵4p | various | 12.9–13.5 | 0.95–0.99 | ~1.01 | 220 | ~0.004 |
| 3p⁵4d | | 14.1 | 1.036 | 0.982 | 280 | ~0.003 |
| 3p⁵5s | | 14.2 | 1.044 | 0.979 | 350 | ~0.003 |
| IE₁ | 3p⁶ → 3p⁵ | 15.760 | 1.158 | 0.929 | 88 | 0.005803 |

### Key observation

Argon's first excitation (11.55 eV) is VERY close to the ionisation
energy (15.76 eV). The ratio: 11.55/15.76 = 0.733. Compare to
hydrogen: 10.2/13.6 = 0.750. The first excitation is consistently
~73–75% of IE₁ across elements.

---

## Calcium (Z=20, R = 3.478 fm)

### Excitation States (Ca I)

| State | Config | E (eV) | z | k | v/c est. |
|-------|--------|--------|---|---|---------|
| Ground | 4s² ¹S₀ | 0 | 0 | ∞ | — |
| 4s4p ³P°₁ | intercomb. | 1.879 | 0.138 | 2.691 | 0.01165 |
| 4s4p ¹P°₁ | resonance | 2.933 | 0.216 | 2.154 | 0.00994 |
| 4s3d ³D | | 2.709 | 0.199 | 2.240 | 0.00802 |
| 4s3d ¹D₂ | | 2.717 | 0.200 | 2.238 | 0.00801 |
| 4s5s ³S₁ | | 4.131 | 0.304 | 1.815 | 0.00547 |
| 4s5s ¹S₀ | | 4.299 | 0.316 | 1.779 | 0.00533 |
| IE₁ | | 6.113 | 0.449 | 1.492 | 0.00714 |

### Calcium excitation anomaly

Ca has its 3d states (2.71 eV) BELOW the 4p states (2.93 eV).
In hydrogen, d-states are always higher than p-states of the same
principal quantum number. This inversion is the "3d collapse" —
in SDT terms, the 3d gear orbit has fallen inside the 4p orbit
due to the deeper convergence field at Z=20.

---

## Krypton (Z=36, R = 4.19 fm)

| State | E (eV) | z | k |
|-------|--------|---|---|
| Ground | 0 | 0 | ∞ |
| 4p⁵5s ³P₂ (meta) | 9.915 | 0.729 | 1.171 |
| 4p⁵5s ¹P₁ (res.) | 10.644 | 0.782 | 1.131 |
| IE₁ | 14.000 | 1.029 | 0.986 |
| 1st exc / IE₁ | 0.709 | — | — |

---

## Xenon (Z=54, R = 4.78 fm)

| State | E (eV) | z | k |
|-------|--------|---|---|
| Ground | 0 | 0 | ∞ |
| 5p⁵6s ³P₂ (meta) | 8.315 | 0.611 | 1.279 |
| 5p⁵6s ¹P₁ (res.) | 9.447 | 0.694 | 1.200 |
| IE₁ | 12.130 | 0.892 | 1.059 |
| 1st exc / IE₁ | 0.685 | — | — |

---

## Mercury (Z=80, R = 5.50 fm est.)

| State | E (eV) | z | k |
|-------|--------|---|---|
| Ground | 0 | 0 | ∞ |
| 6s6p ³P°₀ | 4.667 | 0.343 | 1.707 |
| 6s6p ³P°₁ | 4.886 | 0.359 | 1.669 |
| 6s6p ³P°₂ | 5.461 | 0.401 | 1.579 |
| 6s6p ¹P°₁ (res.) | 6.704 | 0.493 | 1.425 |
| IE₁ | 10.438 | 0.767 | 1.142 |
| 1st exc / IE₁ | 0.447 | — | — |

### Mercury excitation anomaly

The first excitation is only 44.7% of IE₁ — much lower than
the hydrogen ratio (75%). The triplet splitting is ENORMOUS:
³P₀ to ³P₂ spans 0.794 eV. This is relativistic spin-orbit
splitting — in SDT terms, the heavy convergence field of Z=80
couples the electron's circulaltion direction to its orbital
phase far more strongly than light elements.

---

## Cross-Element Comparison: 1st Excitation / IE ratio

| Element | Z | 1st Exc (eV) | IE₁ (eV) | Ratio | k (1st exc) |
|---------|---|-------------|----------|-------|-------------|
| H | 1 | 10.20 | 13.606 | 0.750 | 1.155 |
| He | 2 | 19.82 | 24.587 | 0.806 | 0.829 |
| **Be** | 4 | 2.725 | 9.323 | **0.292** | 2.234 |
| **Ca** | 20 | 1.879 | 6.113 | **0.307** | 2.691 |
| **Ar** | 18 | 11.548 | 15.760 | **0.733** | 1.086 |
| **Kr** | 36 | 9.915 | 14.000 | **0.709** | 1.171 |
| **Xe** | 54 | 8.315 | 12.130 | **0.685** | 1.279 |
| **Ba** | 56 | 1.120 | 5.212 | **0.215** | 3.486 |
| **Yb** | 70 | 2.146 | 6.254 | **0.343** | 2.518 |
| **Hg** | 80 | 4.667 | 10.438 | **0.447** | 1.707 |

### The two families

**HIGH ratio (0.68–0.81)**: Noble gases (Ar, Kr, Xe), H, He.
These have CLOSED outer shells. The first excitation requires
promoting an electron from a closed shell — it costs nearly
as much as ionisation. The gear train is rigid.

**LOW ratio (0.21–0.35)**: Alkaline earths (Be, Ca, Ba), Yb.
These have outer s² pairs. The first excitation promotes one
s-electron to p — much cheaper than ionising it completely.
The outer gear is loosely coupled.

**Hg (0.45)**: Intermediate. The relativistically contracted 6s²
shell is tighter than Be/Ca/Ba but looser than noble gases.

### SDT interpretation

The ratio measures **gear rigidity**: how much of the total
binding (IE) is needed just to change the gear position (excite).
Noble gases have rigid gears (high ratio). Alkaline earths have
loose outer gears (low ratio). EC closure elements split into
these two families based on whether their closure is p⁶ (rigid)
or s²/d¹⁰/f¹⁴ (loose).
