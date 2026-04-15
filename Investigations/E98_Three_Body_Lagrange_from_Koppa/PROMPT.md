# E98: Three-Body Lagrange Points from Koppa — Investigation Prompt

> **Classification**: Analytical derivation + numerical validation
> **Parent**: E97 (Earth Core Seismic Speed — Koppa framework)
> **Engine dependencies**: laws.hpp (bridge::koppa, bridge::g_surface, bridge::g_interior)
> **Constitutional constraints**: No G, No M, No GM, No QM

---

## 1. Objective

Derive the positions of all five Lagrange points (L1–L5) for the Sun–Earth and
Earth–Moon systems using ONLY the koppa framework:

    ϟ = v²R/c²     (c-boundary)
    g = v²/R        (surface acceleration)

The classical three-body problem requires G and M. SDT replaces these with
throughput transit-time equalisation: the Lagrange points are where the
phase delay through one body's shadow cone equals the phase delay through
the other's.

The "unsolvable" three-body problem becomes DETERMINISTIC when restated as
a pressure-field superposition problem.

---

## 2. Background

### 2.1 The Classical Problem

The restricted three-body problem (two massive bodies + test particle)
admits five equilibrium points (Lagrange 1772). Their positions depend on
the mass ratio μ = M₂/(M₁ + M₂):

- **L1**: between the bodies, distance r₁ from M₂ where:
  `r₁/a ≈ (μ/3)^(1/3)` (Hill sphere)
- **L2**: beyond M₂, same approximate distance
- **L3**: opposite M₂, behind M₁
- **L4, L5**: 60° ahead/behind M₂ in its orbit (equilateral triangle)

The full three-body problem (three comparable masses) is chaotic in
Newtonian gravity. No general closed-form solution exists.

### 2.2 SDT Interpretation

In SDT, there are no "masses" and no "gravitational force." There is:
1. Each body's **koppa** (shadow depth): ϟᵢ = vᵢ²Rᵢ/c²
2. Each body's **shadow cone**: the region of reduced throughput behind it
3. The **transit time** of convergent throughput through each body

The Lagrange points are where:
- **L1**: Transit time through body A's shadow = transit time through body B's
  shadow, along the connecting axis
- **L4/L5**: Throughput from A and B arrives at the test point with EQUAL
  phase delay from both directions

The key insight: the "mass ratio" μ is NUMERICALLY IDENTICAL to the
"koppa ratio" ϟ₂/(ϟ₁ + ϟ₂) because mass IS throughput reorganisation
cost (Law IV). But the SDT derivation uses ϟ, not M.

### 2.3 Why SDT Makes the Three-Body Problem Tractable

The classical three-body problem is chaotic because three point-mass
gravitational fields superpose nonlinearly. In SDT:

1. The convergence field is CONTINUOUS (no point singularities)
2. Each body's contribution is a smooth pressure deficit (shadow cone)
3. The superposition of smooth fields is smooth
4. The dynamics reduce to pressure-wave interference

For three comparable-mass bodies, SDT predicts:
- Stable orbits exist where the phase-delay contours form closed surfaces
- The "chaos" arises from the RESOLUTION LIMIT of the phase-delay
  interference pattern, not from fundamental indeterminacy
- At sufficiently large separations, the three-body system is always
  reducible to nested two-body shadow interactions

---

## 3. Derivation

### Step 1: Koppa for each body

For each body i in the system:
```
ϟᵢ = vᵢ² Rᵢ / c²
gᵢ = vᵢ² / Rᵢ = c² ϟᵢ / Rᵢ²
```

Sun–Earth:
```
ϟ_Sun   = 437000² × 6.957e8 / c² = 1.478 × 10⁶ m = 1478 km
ϟ_Earth = 7909² × 6.371e6 / c²   = 4.434 × 10⁻³ m = 4.43 mm
```

Earth–Moon:
```
ϟ_Earth = 4.434 × 10⁻³ m
ϟ_Moon  = 1680² × 1.7374e6 / c²  = 5.456 × 10⁻⁵ m = 0.055 mm
```

### Step 2: The koppa ratio replaces the mass ratio

Classical: μ = M₂/(M₁ + M₂)
SDT:      μ_ϟ = ϟ₂/(ϟ₁ + ϟ₂)

Since ϟ = v²R/c² and GM = v²R (bridge law):
ϟ = GM/c² → μ_ϟ = GM₂/(G(M₁+M₂)) = M₂/(M₁+M₂) = μ

The koppa ratio IS the mass ratio. But derived from v and R, not G and M.

### Step 3: L1 from transit-time equalisation

At L1, the throughput transit time from the Sun equals the transit time
from the Earth along the connecting axis. The transit time through a
body's shadow at distance d is:

```
τ(d) = ϟ / d     (dimensionless phase delay fraction)
```

At L1 (distance d₁ from Earth, D-d₁ from Sun):

```
ϟ_Sun / (D - d₁) = ϟ_Earth / d₁
d₁ = D × ϟ_Earth / (ϟ_Sun + ϟ_Earth)
```

Wait — this gives the barycentric position, not L1. The L1 condition is
the GRADIENT equality:

```
d(τ_Sun)/dr = d(τ_Earth)/dr  at r = r_L1
ϟ_Sun / (D - r)² = ϟ_Earth / r²
r³ / (D - r)³... → Hill sphere formula
```

This reduces to the classical result but derived from ϟ, not M.

### Step 4: L4/L5 stability from shadow interference

L4 and L5 are stable (for μ < 0.0385) because the throughput from both
bodies arrives with equal phase delay. The test particle sits in a
pressure minimum (saddle point) where perturbations are restored by
the Coriolis-equivalent of the rotating pressure field.

In SDT, the stability criterion is:
```
ϟ₂ / (ϟ₁ + ϟ₂) < 0.0385
```

### Step 5: Full three-body (Sun–Earth–Moon)

Compute the throughput field at every point on the Sun–Earth–Moon plane:
```
g(x,y) = Σᵢ c²ϟᵢ rᵢ_hat / rᵢ²
```

where rᵢ is the distance from point (x,y) to body i. Find the equilibrium
points (∇g = 0) and compare to the measured Lagrange positions.

### Step 6: Shadow cone geometry

The user's key insight: gravity = depth of shadow cone × transit speed
along separation distance.

For two bodies separated by distance D:
```
F₁₂ = c² ϟ₁ ϟ₂ / D²
```

This is Newton's law but expressed in koppa:
```
F = GMm/D² = (c²ϟ₁)(c²ϟ₂)/(c²D²)... 
```

The force between two bodies IS the product of their shadow depths
divided by the square of their separation, scaled by c².

---

## 4. The Calculation (Numerical Procedure)

1. **Set up the Sun–Earth system**:
   - Compute ϟ_Sun, ϟ_Earth from measured v_surf and R
   - D = 1 AU = 1.496 × 10¹¹ m
   - Compute μ_ϟ = ϟ_Earth / (ϟ_Sun + ϟ_Earth)

2. **Find L1–L5** by solving ∇Φ_eff = 0 in the rotating frame:
   - Φ_eff(r) = -c²ϟ_Sun/r_Sun - c²ϟ_Earth/r_Earth - ½Ω²r²
   - Ω = v_Earth_orbital / D (= 2π/year)

3. **Compare to measured positions**:
   - L1 (SOHO): ~1.5 × 10⁶ km from Earth
   - L2 (JWST): ~1.5 × 10⁶ km from Earth
   - L4/L5 (Trojans): 60° ahead/behind Earth

4. **Repeat for Earth–Moon**:
   - D = 3.844 × 10⁸ m
   - Compute all five Lagrange points

5. **Full three-body** (Sun–Earth–Moon):
   - Superpose all three shadow cones
   - Find equilibrium and stability regions
   - Compare to measured lunar orbit perturbations

---

## 5. Required Outputs

1. **L1–L5 positions** for Sun–Earth from koppa ratio, vs classical values
2. **L1–L5 positions** for Earth–Moon from koppa ratio, vs classical values
3. **Stability criterion** for L4/L5 in koppa units
4. **Shadow cone depth map** for the Sun–Earth–Moon plane
5. **Comparison**: SDT vs Newton for orbital perturbation amplitudes
6. **Transit-time map**: contour plot showing τ_Sun, τ_Earth, τ_Moon

---

## 6. Success Criteria

- [ ] L1 distance matches classical Hill sphere to < 1%
- [ ] L4/L5 at exactly 60° (geometric necessity)
- [ ] Stability criterion μ < 0.0385 reproduced from koppa ratio
- [ ] No G, No M anywhere in the derivation — only v, R, c
- [ ] Three-body equilibrium points correctly superpose two-body shadow cones
- [ ] Barycentric positions from koppa ratios match mass-ratio predictions

---

## 7. Falsification Conditions

- If the koppa ratio does NOT equal the mass ratio to < 0.1%: the bridge
  law v²R = GM has a systematic error
- If L4/L5 stability depends on quantities beyond ϟ₁/ϟ₂: the shadow
  cone model is incomplete
- If the three-body superposition produces equilibrium points that don't
  match observation: SDT's pressure-field linearisation is wrong

---

## 8. Connection to E97

This investigation is a direct extension of E97, which established:
- ϟ = v²R/c² encodes the full gravitational field
- g = v²/R at the surface, g(r) = v²R frac(r)/r² in the interior
- Phase delay through excluded cells is the mechanism

E98 extends this to MULTIPLE bodies: the gravitational interaction between
two bodies is the interference of their phase-delay fields. The Lagrange
points are nodes in this interference pattern.
