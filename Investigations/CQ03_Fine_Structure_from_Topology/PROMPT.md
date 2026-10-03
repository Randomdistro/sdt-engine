# CQ03: Fine Structure Constant from Topology — Mathematical Framework

> **Category**: Foundations / Coupling Constants / Input Reduction
> **Status**: RESOLVED (11/11 pass) — α is NOT derivable from topology

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| α | Fine structure constant | 7.2974×10⁻³ (= 1/137.036) | The dimensionless coupling strength of electromagnetism: how strongly charges interact via the lattice |
| g | Wake-to-quantum ratio | R_wake × mc/ℏ [dimensionless] | The ratio of a particle's wake radius to its reduced Compton wavelength. g measures how far the lattice perturbation extends in quantum units. |
| r_e | Classical electron radius | 2.818×10⁻¹⁵ m | = αℏ/(m_e c). The radius at which the EM self-energy equals m_e c². In SDT: the electron's wake radius. |
| ƛ_Ce | Reduced Compton wavelength (electron) | 3.862×10⁻¹³ m | = ℏ/(m_e c). The quantum coherence scale of the electron — the distance over which the electron's wavefunction is phase-coherent. |
| R_p | Proton charge radius | 8.414×10⁻¹⁶ m | The proton's wake radius. From muonic hydrogen: 0.8414 fm. |
| ƛ_Cp | Reduced Compton wavelength (proton) | 2.103×10⁻¹⁶ m | = ℏ/(m_p c). The proton's quantum coherence scale. |
| e | Elementary charge | 1.602×10⁻¹⁹ C | The charge quantum. In SDT: the magnitude of the topological charge of a single lattice defect. |
| k_e | Coulomb constant | 8.988×10⁹ N·m²/C² | = 1/(4πε₀). Mediates the strength of charge-charge interaction through the lattice. |
| W | Winding number | integer | The topological winding of the vortex tube. W=1 for electron, W=3 for proton (as (2,3) trefoil). |
| a₀ | Bohr radius | 5.292×10⁻¹¹ m | = ℏ/(m_e cα). The orbit radius where centripetal force balances Coulomb. |

---

## 2. The Question

CQ02 showed the electron is a (1,1) unknot with equal mode partition: v_T = v_P = c/√2. The winding namespace in laws.hpp shows:

```
g_electron = r_e × m_e × c / ℏ = α     (exact algebraic identity)
g_proton   = R_p × m_p × c / ℏ ≈ 4     (= W+1 for trefoil, 0.02% agreement)
```

**Can α = 1/137.036 be derived from the (1,1) torus geometry alone?**

If yes → the minimal SDT input set reduces from {ℓ_P, T_CMB, α, d=3} to {ℓ_P, T_CMB, d=3}.

---

## 3. The g-Number Framework

### 3.1 Definition of g

For any particle with wake radius R_wake and mass m:

```
g = R_wake × m × c / ℏ = R_wake / ƛ_C
```

g is dimensionless. It counts how many reduced Compton wavelengths fit inside the wake radius. Equivalently: what fraction of the quantum coherence scale is occupied by the lattice perturbation.

### 3.2 The Proton: g = 4 (Topological)

```
g_proton = R_p × m_p × c / ℏ = 8.414×10⁻¹⁶ × 1.673×10⁻²⁷ × 2.998×10⁸ / 1.055×10⁻³⁴
        = 4.0008
```

This is W+1 = 3+1 = 4 to 0.02%. The trefoil knot (2,3) has 3 crossings; the wake extends W+1 = 4 Compton lengths. This is a **topological** result — it follows from the knot structure.

### 3.3 The Electron: g = α (Electromagnetic)

```
g_electron = r_e × m_e × c / ℏ = r_e / ƛ_Ce = α = 7.2974×10⁻³
```

This is NOT an integer. If the W+1 rule applied universally, g_electron should be W+1 = 2. Instead it is 274× smaller:

```
r_e / [(W+1)ℏ/(m_e c)] = r_e / (2ƛ_Ce) = α/2 ≈ 1/274
```

The electron's actual wake radius is α/2 times the topological prediction. This reduction factor IS the electromagnetic coupling.

### 3.4 Interpretation

| Particle | Topology | g | Type |
|----------|----------|---|------|
| Proton | (2,3) trefoil (knotted) | 4 = W+1 (integer) | Topological |
| Electron | (1,1) unknot (not knotted) | α ≈ 1/137 (non-integer) | Electromagnetic |

- **Proton**: the trefoil is topologically protected. The wake radius is fixed by the crossing number. g is an integer.
- **Electron**: the unknot is topologically trivial. The wake radius is determined by the self-interaction of the charge with the lattice. g = α.

---

## 4. Derivation Attempts (All Circular)

### Attempt 1: g-ratio

```
α = 4 × g_electron / g_proton = 4 × (r_e m_e) / (R_p m_p)
```

Exact (to 0.02%), but this just RESTATES the g definitions. Not a derivation.

### Attempt 2: Bohr radius

```
α = ƛ_Ce / a₀ = ℏ / (m_e c a₀)
```

Exact, but a₀ = ℏ/(m_e cα), so α = ℏ/(m_e c × ℏ/(m_e cα)) = α. **Circular.**

### Attempt 3: P_eff

```
α = (π/4) P_eff R_charge⁴ / (ℏc)
```

Exact, but P_eff is DEFINED by k_e e² = αℏc. **Circular.**

### Attempt 4: Lattice constants only

Substitute f = 4αℏcℓ_P/(πR_p²r_e²R_CMBu_CMB) into P_eff = f × P_conv:

```
α = (π/4)(f P_conv) R_charge⁴ / (ℏc)
  = (π/4)[4αℏcℓ_P/(πR_p²r_e²R_CMBu_CMB)] × [R_CMBu_CMB/ℓ_P] × R_p²r_e² / (ℏc)
  = α × 1
```

Every factor cancels. **Circular.** α cannot be extracted from the SDT identities because it is woven into ALL of them.

---

## 5. Why α Cannot Be Derived (Current Framework)

α = k_e e² / (ℏc). This contains the elementary charge e. In the current SDT framework:

- ℏ and c are base invariants (Tier 0)
- k_e = 1/(4πε₀) is a unit-system constant
- **e is an independent input** — the charge quantum

Unless e can be derived from lattice topology (the question for CQ10: Topological Charge Quantisation), α remains irreducible.

### SDT Input Hierarchy

| Tier | Constants | Source |
|------|-----------|--------|
| 0 (SI exact) | c, ℏ, k_B, e | Defined since 2019 |
| 1 (measured) | α, m_e, m_p | CODATA 2018 |
| 2 (cosmological) | ℓ_P, T_CMB | CODATA / FIRAS |
| 3 (derived) | a₀, r_e, R_p, R_y | From Tiers 0–2 via SDT |

**α sits in Tier 1. It is NOT reducible to Tier 2.** The minimal input set is {ℓ_P, T_CMB, e, d=3}, not {ℓ_P, T_CMB, d=3}.

---

## 6. Success Criteria

- [x] v_P/v_T computed for W=1: equals 1 (not α)
- [x] α shown to be g_electron (wake-to-quantum ratio), not a mode velocity ratio
- [x] Proton g = W+1 = 4 (topological, 0.02%)
- [x] All derivation attempts shown to be circular
- [x] Sensitivity analysis: dα/d(R/a) is undefined — α does not depend on aspect ratio
- [x] Input hierarchy established: α requires e as independent input → CQ10

## Verdict

**CQ03 RESOLVED.** α cannot be derived from W=1 geometry. It is the electromagnetic coupling constant, requiring the charge quantum e. Reducing to 3 inputs requires CQ10.
