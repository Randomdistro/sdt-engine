# CQ04: State28D Force Ratio Constants — Derivation from Pure SDT

## Executive Summary

The State28D manifold assigns physical scales to the 28 degrees of freedom across 7 hierarchical levels. Two characteristic scales appear as normalisations in the force and phase calculations:

- **10³⁰ Pa·m** — pressure × length scale at the boundary between nuclear and atomic regimes
- **10⁻⁹ J** — energy scale of topological transitions in the convergence field

**Question**: Are these constants derived from SDT axioms (Laws I–VI + measured constants), or are they fitted parameters?

**Method**: Derive both from convergence pressure Φ = Nε, occlusion force F = (π/4)P_conv R₁² R₂²/r², and mass as displacement volume reorganisation.

**Expected Outcome**: Both constants emerge as unique values from the ratio of nuclear to atomic displacement volumes and the convergence energy density.

---

## Physical Setup

### Elementary Convergence Content

From Law I:
\varepsilon = u_0 \ell_P^3 = aT_0^4 \ell_P^3

where:
- a = 7.5657 × 10⁻¹⁶ J/m³/K⁴ (radiation constant, CODATA 2018)
- T₀ = 2.725 K (CMB temperature)
- ℓ_P = 1.616255 × 10⁻³⁵ m (Planck length)

This gives: ε ≈ 6.5 × 10⁻¹¹² J

### Convergence Burden at Any Point

From Law I (Theorem 1):
\Phi = \mathcal{N} \varepsilon = \frac{R_{CMB}}{\ell_P} \cdot \varepsilon

where R_CMB ≈ 4.4 × 10²⁶ m (comoving distance to recombination).

This is the local pressure integrated over the full convergent domain from all four 4π steradians.

### Occlusion Force Law

From Law III:
F = \frac{\pi}{4} P_{\text{conv}} \cdot R_1^2 \cdot R_2^2 \cdot r^{-2}

where P_conv is the **convergence pressure** associated with Φ. The question becomes: **What is P_conv as a function of scale?**

### Displacement Volume & Mass

From Law IV:
m = \frac{\Phi \cdot V_{\text{disp}}}{\ell_P^3 \cdot c^2}

Particles have discrete topologies (W=1 electron, W=3 proton from CQ02). Each topology determines its exclusion volume V_disp. The mass is:
m \propto V_{\text{disp}}

---

## The Mystery Constants

### Where do 10³⁰ Pa·m and 10⁻⁹ J appear?

**In state28d.hpp line 134** (occlusion screening):
`cpp
double gradation_screening = std::tanh(std::abs(T_5) / 1e10);
`

T_5 is the **pressure gradient** in the torus structure [Pa/m]. The hardcoded normalisation is 1e10 Pa/m.

**Question 1**: Is 1e10 Pa/m actually a derived scale, or fitted?

**In state28d.hpp line 159** (phase transition):
`cpp
double transition_factor = 1.0 + std::abs(Phi_5) / 1e-20;
`

Phi_5 is the **phase transition energy** [J]. The hardcoded normalisation is 1e-20 J.

**Question 2**: Is 1e-20 J actually 10⁻⁹ expressed differently, or a different scale entirely?

**Question 3**: Do both scales emerge from the ratio of atomic to nuclear regimes?

---

## Derivation Strategy

### Phase 1: Pressure Scale Decomposition

The convergence pressure P_conv varies with scale due to the displacement volume it couples to.

At the **atomic scale** (electron, a_e ~ 10⁻¹⁵ m):
P_{\text{atom}} = \frac{\Phi \cdot \varepsilon}{a_e^3}

At the **nuclear scale** (proton, a_p ~ 10⁻¹⁸ m):
P_{\text{nuc}} = \frac{\Phi \cdot \varepsilon}{a_p^3}

The **pressure gradient** between them:
\frac{dP}{da} = \frac{P_{\text{atom}} - P_{\text{nuc}}}{a_e - a_p}

Over a characteristic torus size (~ a_e to a_p):
T_5 \sim \frac{\Phi \cdot \varepsilon}{(a_e - a_p) \cdot a_e^3}

Compute this and see if it yields 10¹⁰ Pa/m (or 10³⁰ Pa·m when multiplied by a length scale).

### Phase 2: Topological Energy Scale

A vortex topology transition (e.g., W=2 → W=1 + decay) requires breaking and reconnecting the knot structure.

The energy to flip a toroidal winding is related to the circulatory kinetic energy:
E_{\text{topo}} \sim m v_T^2 / 2

where v_T comes from the velocity budget v_T² + v_P² = c² (from CQ02).

For an electron:
- v_T = c/√2 (from CQ02, W=1)
- m_e = (Φ/ℓ_P³c²) × V_e

The topological energy scale:
\Phi_5 \sim \frac{1}{2} m_e \left(\frac{c}{\sqrt{2}}\right)^2 = \frac{m_e c^2}{4}

This is **rest energy / 4**. Compute numerically and see if it relates to 10⁻⁹ J (and how).

### Phase 3: Dimensional Cross-Check

Verify dimensional consistency:
- T_5 has dimension [Pa/m] = [J/m⁴]
- Phi_5 has dimension [J]
- Their ratio: [J/m⁴] / [J] = [1/m⁴]

Check whether the hardcoded values respect this and scale properly with particle sizes.

### Phase 4: Numerical Calculation

1. Compute P_atom and P_nuc from convergence pressure formula
2. Calculate pressure gradient T_5
3. Compute topological energy Phi_5 from velocity budget
4. Compare against hardcoded scales
5. If within 1 order of magnitude: **QUALIFIED**
6. If within 20%: **PASS**

---

## Success Criteria

✅ **PASS** (Class A: Derived from SDT axioms):
- Both 10³⁰ Pa·m and 10⁻⁹ J derived analytically from Φ = Nε, occlusion force, and velocity budget
- Numerical match within **20%**
- No fitted parameters; only CODATA 2018 constants used

✅ **QUALIFIED** (Class C: Convergence):
- Constants derived with 1–2 approximations (e.g., neglecting shell corrections)
- Match within **50%**
- Mark intermediate constants as CALIBRATED

⚠️ **QUALIFIED PENDING** (Class D: Computed):
- Constants traced to specific SDT equations
- Match within **1–2 orders of magnitude**
- Physical meaning partially resolved

❌ **FAIL** (Class F):
- Constants cannot be derived from SDT alone
- Appear to be fitted empirically
- Suggests theory has missing degrees of freedom

---

## Outputs

1. **CQ04_DERIVATION.md** — Complete symbolic derivation from Laws I–IV
2. **cq04_scales_from_sdt.cpp** — C++ tool computing scales from convergence pressure
3. **cq04_results.txt** — Numerical table: theory values vs hardcoded
4. **CQ04_VERDICT.md** — Pass/Qualified classification

---

## References (Pure SDT)

- **Law I**: Shell cancellation, Φ = Nε
- **Law III**: Occlusion force F = (π/4)P_conv R₁² R₂²/r²
- **Law IV**: Mass = Φ V_disp / (ℓ_P³ c²)
- **Law V**: Velocity budget v_T² + v_P² = c²
- **Law VI**: Topology determines stability (W=1, W=3 only)
- **CQ02**: Derived v_T, v_P, R/a for each winding
- **Theory/02**: Convergence pressure and coupling constants

---

**Status**: READY — USING PURE SDT FRAMEWORK (NO QM BORROWING)
