# E98b: N-Body Equilibrium Points — Generalised Lagrange Finder

> **Classification**: Numerical search + validation
> **Parent**: E98 (Three-Body Lagrange from Koppa)
> **Engine dependencies**: `laws.hpp` (`bridge::koppa`)
> **Language**: C++20, header-only, no external dependencies

---

## 1. Objective

Find all static equilibrium points in a co-rotating frame containing N ≥ 3
gravitating bodies — i.e. positions where the net acceleration (gravitational
+ centrifugal + Coriolis at zero test-particle velocity) vanishes.

The classical restricted three-body problem has exactly five such points.
For N ≥ 3 co-orbiting bodies the equilibrium landscape becomes richer: the
number and character of equilibrium points depends on the geometry and mass
ratios. This investigation numerically locates them.

### Scope

Start with three well-characterised systems of increasing complexity:

| System | Bodies | Rotating frame |
|---|---|---|
| Sun–Earth (validation) | 2 | Kepler, period = 1 yr |
| Sun–Earth–Moon | 3 | Sun–Earth frame; Moon averaged or instantaneous |
| Sun–Jupiter–Saturn | 3 | Sun–Jupiter frame; Saturn treated as perturber |

Then generalise to an arbitrary list of N bodies with positions, koppa values,
and a chosen rotation axis/rate.

---

## 2. Physics

### 2.1 Effective potential in the co-rotating frame

For N bodies at positions **rᵢ** with koppa values ϟᵢ = vᵢ²Rᵢ / c², the
effective potential at a test point **r** in a frame rotating at angular
velocity **Ω** about the system barycentre is:

```
Φ_eff(r) = − Σᵢ c² ϟᵢ / |r − rᵢ|  −  ½ |Ω × r|²
```

The gravitational acceleration from body i at distance dᵢ is:

```
gᵢ = c² ϟᵢ / dᵢ²     directed toward body i
```

The equilibrium condition is:

```
∇Φ_eff = 0     ⟹     Σᵢ c² ϟᵢ (r − rᵢ) / |r − rᵢ|³  =  Ω × (Ω × r)
```

This is the standard condition — the koppa ratio ϟ₂/(ϟ₁ + ϟ₂) is
numerically identical to the mass ratio M₂/(M₁ + M₂) by the bridge
relation ϟ = GM/c².

### 2.2 What "equalised force from three or more directions" means

At a classical L1 point, the test particle sits where the pull from two
bodies (plus centrifugal) balances along a line. The generalisation:

- **Collinear equilibria**: net acceleration vanishes along the axis joining
  two dominant bodies. For N bodies there can be N−1 such points between
  adjacent pairs, plus exterior points.

- **Triangular / polyhedral equilibria**: points where the vector sum of
  gravitational pulls from three or more bodies, each from a distinct
  angular direction, cancels against the centrifugal term. These are the
  analogues of L4/L5 but for three or more source directions.

- **Saddle points vs minima**: classify each equilibrium by the eigenvalues
  of the Hessian of Φ_eff. Stable (all eigenvalues positive in the
  effective-potential sense) vs unstable (saddle).

### 2.3 Honest caveats

- The koppa substitution ϟ = v²R/c² reproduces the Newtonian potential
  identically (since GM = v²R at the surface). The equilibrium positions
  will therefore match Newtonian predictions by construction. The value of
  this exercise is (a) validating the koppa machinery on a non-trivial
  multi-body problem, and (b) building the numerical infrastructure to
  explore configurations that haven't been exhaustively tabulated.

- For 3+ comparable-mass bodies, the "co-rotating frame" is not unique.
  The choice of Ω matters and must be stated explicitly.

- The Moon's orbit is not coplanar with the ecliptic (inclination ~5°).
  For the 2D planar scan this is ignored. Flag the approximation.

---

## 3. Algorithm

### 3.1 Grid scan + Newton refinement (2D planar)

1. **Define the plane**: the orbital plane of the dominant pair.
2. **Grid**: lay down a regular grid covering [−2a, +2a] × [−2a, +2a]
   where a is the separation of the dominant pair.
3. **Evaluate** ∇Φ_eff at each grid point.
4. **Detect sign changes**: any cell where ∂Φ/∂x or ∂Φ/∂y changes sign
   across an edge is a candidate.
5. **Refine**: use Newton–Raphson on the 2×2 system (∂Φ/∂x, ∂Φ/∂y) = 0
   with the Hessian as the Jacobian.
6. **Classify**: compute eigenvalues of the 2×2 Hessian at each found
   equilibrium. Report stability type (stable node, saddle, unstable node).
7. **Dedup**: merge any equilibria closer than ε_merge = 1e-6 × a.

### 3.2 Extension to 3D

For non-coplanar configurations, extend to a 3D grid and solve the
3×3 system. Use coarser initial grid + adaptive refinement near candidates.

### 3.3 Convergence guard

Newton–Raphson on ∇Φ_eff can diverge near the bodies (where the potential
is singular). Exclude a guard radius r_guard = 0.01 × R_body around each
body from the search.

---

## 4. Data Structures

```cpp
struct Body {
    const char* name;
    double koppa;       // ϟ = v²R/c²  [metres]
    double pos[3];      // position in the rotating frame [metres]
    double R;           // physical radius [metres] (for guard zone)
};

struct Equilibrium {
    double pos[3];      // location [metres]
    double grad_norm;   // |∇Φ_eff| at convergence (should be ~0)
    double hessian_eigenvalues[3]; // stability classification
    int    type;        // 0 = stable, 1 = saddle-1, 2 = saddle-2, 3 = unstable
    int    dominant_bodies[3];     // indices of the 3 strongest contributors
};
```

---

## 5. Required Outputs

### 5.1 Validation (Sun–Earth, N=2)

- L1–L5 positions from the grid+Newton finder
- Compare to the existing `e98_lagrange.cpp` analytical solver
- Agreement to < 0.01% required

### 5.2 Sun–Earth–Moon (N=3)

- Place Moon at several orbital phases (0°, 90°, 180°, 270°)
- For each phase, find all equilibrium points in the ecliptic plane
- Report how the classical L1/L2 positions shift due to lunar perturbation
- Identify any new equilibrium points that appear only in the 3-body case
- Tabulate: position, stability type, dominant body contributions

### 5.3 Sun–Jupiter–Saturn (N=3)

- Fix Jupiter and Saturn at their current orbital positions
- Find equilibria in the Sun–Jupiter rotating frame
- Report how Saturn perturbs the Jupiter Trojan points (L4/L5)
- Quantify the displacement from the ideal equilateral position

### 5.4 General N-body scan

- Accept an arbitrary vector of Body structs
- Report all found equilibria with classification
- Print a directional breakdown: for each equilibrium, list the fractional
  contribution of each body's pull to the total gravitational acceleration
  at that point (before centrifugal cancellation)

---

## 6. Success Criteria

- [ ] Sun–Earth L1–L5 reproduced to < 0.01% vs analytical
- [ ] Sun–Earth–Moon equilibria found at all four lunar phases
- [ ] Lunar perturbation of L1/L2 quantified (expected: ~km-scale shift)
- [ ] Jupiter Trojan displacement from Saturn quantified
- [ ] Stability classification (Hessian eigenvalues) reported for all points
- [ ] No G, no M in the calculation — only ϟ, v, R, c
- [ ] Runs in < 5 seconds for N ≤ 5 on a desktop CPU

---

## 7. Falsification Conditions

- If the grid+Newton method misses known equilibria: the grid resolution
  or guard radius needs adjustment (implementation issue, not physics).
- If the koppa-derived positions differ from Newtonian predictions by
  more than numerical precision: there is a bug, since ϟ = GM/c² is an
  identity, not an approximation.
- If new "SDT-only" equilibria appear that have no Newtonian counterpart:
  that would be a genuine prediction to investigate further, but treat
  with scepticism until independently confirmed.

---

## 8. Notes

- The existing `e98_lagrange.cpp` solves the collinear points analytically
  via Newton's method on the quintic. This new code is a brute-force
  numerical scanner that should reproduce those results and extend to N > 2.
- Keep the code self-contained in a single `.cpp` file.
- Use `sdt::laws` constants where available.
- Print results in a clean tabular format with units.
