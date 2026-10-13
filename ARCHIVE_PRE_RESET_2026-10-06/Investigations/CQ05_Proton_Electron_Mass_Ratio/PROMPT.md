# CQ05: Proton-Electron Mass Ratio — Mathematical Framework

> **Category**: Mass Spectrum / Topology → Mass
> **Status**: OPEN (blocked — requires V_disp derivation)

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| m_p/m_e | Proton-to-electron mass ratio | 1836.153 | The ratio of rest masses. One of the fundamental dimensionless constants of nature. |
| V_disp | Displaced volume | m³ | The volume of lattice displaced by a particle's vortex — determines mass via Law IV. |
| Φ | Convergence burden | 1.039×10⁻⁵⁶ J | The total relay content arriving at each spation from all N shells (Law I). |
| ℓ_P | Planck length | 1.616×10⁻³⁵ m | The lattice cell scale. |
| W | Winding number | integer | Topological winding: W=1 (electron), W=3 (proton as (2,3) trefoil). |
| R, a | Torus radii | m | Major (R) and minor (a) radii of the particle torus. |
| (p,q) | Knot type | integers | p toroidal, q poloidal wraps. Electron = (1,1), proton = (2,3). |

---

## 2. The Question

The mass from Law IV is:

```
m = Φ V_disp / (3 ℓ_P³ c²)
```

Therefore:

```
m_p / m_e = V_disp_p / V_disp_e
```

The mass ratio is the ratio of displaced volumes. **Can this ratio be derived from the (2,3) vs (1,1) equilibrium?**

---

## 3. What CQ02 Provides

From CQ02, the torus volume is:

```
V_torus = 2π² R a²
```

With R/a = √(q/p) from the mode equations:

```
For (1,1): R/a = 1,  so V_e = 2π² a_e³
For (2,3): R/a = √(3/2), so V_p = 2π² √(3/2) a_p³
```

The ratio:

```
V_p / V_e = √(3/2) × (a_p / a_e)³
```

From CQ02, a_e / a_p = (m_p/m_e) / √(5/6) ≈ 2011. So:

```
V_p / V_e = √(3/2) × (1/2011)³ = √(3/2) × 1.23×10⁻¹⁰
```

This gives V_p / V_e ≈ 1.5×10⁻¹⁰ — the proton's torus volume is **much smaller** than the electron's. And yet m_p >> m_e. This means **V_disp ≠ V_torus**.

The displacement volume is NOT the torus volume. It includes the lattice perturbation extending beyond the torus surface — the wake.

---

## 4. The (3/2)^(3/2) Conjecture

```
(3/2)^(3/2) = √(27/8) = 1.8371
```

This is 0.053% from m_p/m_e / 1000 = 1.8362. The factor of ~1000 might come from:

- α⁻¹ × factor ≈ 137 × 13.4 ≈ 1837 (not clean)
- (W+1)^n for some n: 4^5 = 1024, 4^5.07 = 1200... no
- 6π⁵ = 1836.12 — within 0.002% of m_p/m_e !

### The 6π⁵ Identity

```
6π⁵ = 6 × 305.019 = 1830.12    [actually, π⁵ = 306.02, so 6π⁵ = 1836.12]
```

Let me compute exactly: π⁵ = 3.14159²·³ = ... π² = 9.8696, π⁴ = 97.409, π⁵ = 306.020.

```
6π⁵ = 1836.12
m_p/m_e = 1836.153
Difference: 0.002%
```

This is tantalizingly close but remains a **numerical coincidence** without a derivation connecting 6, π, and the mass ratio through SDT mechanics.

---

## 5. Blocked Dependencies

To derive m_p/m_e from SDT requires:

1. **V_disp(W, p, q)**: how the displacement volume depends on topology — requires solving the full 3D lattice perturbation around each torus knot type
2. **Wake structure**: the perturbation extends beyond the torus surface by the wake radius (r_e for electron, R_p for proton), and the wake volume contributes to V_disp
3. **Self-consistency**: V_disp determines m (Law IV), m determines the Compton wavelength which sets the torus radii (CQ02), and the radii determine V_disp — a coupled system

This is a **3D topological field theory problem** that the current SDT framework formulates but does not solve.

---

## 6. Success Criteria

- [ ] m_p/m_e reproduced within 1% from vortex equilibrium
- [ ] Factor ~1836 decomposed into topology-dependent parts
- [ ] V_disp as function of (p,q) knot type derived
- [ ] If exact: m_p eliminated as independent input

## Verdict

**CQ05 OPEN (blocked).** The mass ratio requires the displaced volume ratio V_p/V_e, which requires solving the 3D lattice perturbation for each knot type. This is the hardest open problem in SDT — it connects topology to mass.
