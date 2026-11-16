# E47: Gravitational Lensing from Convergence Gradient — Data/Prompt

## DATA REQUIREMENTS
| Data | Source | Content |
|------|--------|---------|
| Strong lensing arcs | HST SLACS survey | Einstein radii for ~100 galaxy lenses |
| Weak lensing shear profiles | DES Y3 / KiDS DR4 | Tangential shear γ_t(r) around clusters |
| Microlensing events | OGLE/MOA | Point-mass lens events |
| Measured deflection at solar limb | Eddington 1919 / modern VLBI | 1.75" for Sun |
| Cluster masses (X-ray) | Chandra/XMM | Gas-based mass estimates |
| SDT lensing prediction | Convergence gradient bends photon paths | To derive |

## INVESTIGATION PROMPT

**Target**: Derive gravitational lensing as convergence-gradient refraction and compare to measured lensing angles.

### SDT Mechanism
Photons are lattice deformations propagating through the spation medium. Near a massive body, the convergence gradient changes the effective lattice spacing → the photon path curves toward the denser medium (less convergence → more compression → slower effective propagation speed).

This is REFRACTION, not spacetime curvature. The deflection angle should be:

$$\alpha = \int \frac{d \ln(n)}{dr} \times b \ dl$$

where n(r) is the effective refractive index = 1 / √(1 − 2z R/r) and b is the impact parameter.

For the Sun: α = 4GM/(c²b) = 4R_Sun/(k²b) → 1.75" at the limb.

### Methodology
1. Derive the SDT refractive index profile n(r) from the k-gradient
2. Compute deflection angle via refraction integral
3. Verify 1.75" at solar limb
4. Apply to galaxy-scale lenses using the SLACS sample
5. For galaxy clusters: does SDT predict the correct Einstein ring radius WITHOUT dark matter?

### Success Criteria
- [ ] Solar deflection reproduced: 1.75" ± 0.01"
- [ ] Galaxy-scale Einstein radii predicted within 20% of observed
- [ ] Cluster lensing: can SDT match lensing mass without dark matter?
