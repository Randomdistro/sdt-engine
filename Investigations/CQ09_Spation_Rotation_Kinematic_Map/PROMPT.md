# CQ09: Spation Rotation Kinematic Map — The Proton Interior to Valence Shell

## THE QUESTION

The proton surface sits at k = 0.5464 — inside the c-boundary (k < 1). This means the circulation velocity at R_p is superluminal: **v_surface = c/k = 1.831c**. The proton is a superluminal phase-rotation vortex embedded in the spation lattice.

This investigation demands a complete kinematic map: from the 1.83c equatorial rotation at R_p, through every shell of spations outward, tracking how the rotation velocity decays from superluminal to subluminal, how it organises the lattice into counter-rotating shells, and how it finally reaches the lone valence electron at r = a₀ = 5.292 × 10⁻¹¹ m where the velocity is αc = 2.188 × 10⁶ m/s.

---

## KNOWN BOUNDARY CONDITIONS

### Inner boundary: The proton surface (r = R_p = 8.414 × 10⁻¹⁶ m)

| Quantity | Value | Source |
|----------|-------|--------|
| Radius R_p | 8.414 × 10⁻¹⁶ m | muonic H (CODATA 2018) |
| koppa ϟ_H | 0.5464 | (1/α)√(R_p/a₀) |
| k at surface | 0.5464 | c/v_surf |
| v_surface | 1.831c = 5.49 × 10⁸ m/s | c / k_surf (superluminal phase) |
| z at surface | 1/k² = 3.350 | (v/c)² |
| Spation count (R_p / l_P) | 5.21 × 10¹⁹ | R_p / l_P = 8.414e-16 / 1.616e-35 |
| Winding number | W = 3 (trefoil knot) | SDT W+1 conjecture (0.02%) |
| g_proton | 4.0008 ≈ W+1 | R_p m_p c / ℏ |
| Toroidal velocity v_T | c√(2/5) = 0.632c | CQ02 (2,3) torus knot |
| Poloidal velocity v_P | c√(3/5) = 0.775c | CQ02 (2,3) torus knot |
| Trefoil crossing velocity | √(v_T² + v_P²) = c | Budget closure |

### The c-boundary (r = r_Ϟ = R_p / ϟ² = 2.818 × 10⁻¹⁵ m = r_e)

| Quantity | Value |
|----------|-------|
| r_Ϟ | 2.818 × 10⁻¹⁵ m = r_e (classical electron radius) |
| v_orbital | c (exact — this IS the c-boundary) |
| k | 1.0 |
| z | 1.0 |
| Distance from proton centre | 3.35 × R_p |
| Spation shells from R_p to r_Ϟ | ~ 1.22 × 10²⁰ |

### Outer boundary: The electron ground state (r = a₀ = 5.292 × 10⁻¹¹ m)

| Quantity | Value |
|----------|-------|
| a₀ | 5.292 × 10⁻¹¹ m |
| v_electron | αc = 2.188 × 10⁶ m/s |
| k | 1/α = 137.036 |
| z | α² = 5.325 × 10⁻⁵ |
| Spation count (a₀ / l_P) | 3.27 × 10²⁴ |

---

## INVESTIGATION STRUCTURE

### Part I: The Rotation Profile v(r) — From 1.83c to αc

Map the full velocity field from the proton interior outward.

**Tasks:**
1. Compute v(r) = (c/ϟ)√(R_p/r) at logarithmically spaced radii from r = R_p to r = a₀.
2. Mark the THREE critical radii:
   - **r₁ = R_p** (proton surface): v = 1.831c (superluminal phase)
   - **r₂ = r_e = R_p/ϟ²** (c-boundary): v = c (transition point)
   - **r₃ = a₀** (Bohr radius): v = αc (electron orbit)
3. Compute the **number of Planck cells (spations) in each shell** at every radius: N_shell(r) = 4πr²/l_P².
4. Compute the **rotation period** T(r) = 2πr/v(r) at each radius.
5. Map the **angular velocity** ω(r) = v(r)/r and its radial gradient dω/dr.

**Key questions:**
- At what radius does v drop to 0.5c? 0.1c? 0.01c?
- How many spation shells lie between the proton and the c-boundary?
- What is the angular velocity ratio ω(R_p)/ω(a₀)?

### Part II: The Superluminal Interior (R_p < r < r_e)

The proton's k < 1 means the lattice inside the c-boundary supports phase velocities > c. This is NOT a transport violation — the spations circulate as a phase pattern, not a material flow.

**Tasks:**
1. Map the **circulation-translation budget** at every radius inside the c-boundary:
   - v_circ(r)² + v_trans(r)² = c² — BUT the orbital velocity v(r) > c.
   - Resolve: inside the c-boundary, the "orbital velocity" is a **phase velocity** of the convergence field pattern, not a particle velocity. The actual spation displacement is always ≤ l_P per tick.
2. Compute the **displacement amplitude** of each spation as a function of r:
   - d(r) = (v_phase(r) / c) × l_P — the fractional displacement per tick.
   - At R_p: d = 1.831 l_P (the displacement exceeds one Planck length).
   - This means neighbouring spations are displaced by MORE than their own size → the lattice is in a **saturated displacement regime**.
3. Quantify the **saturation zone**: from r = 0 to r = r_sat where d(r) = l_P (v_phase = c).
   - r_sat = r_Ϟ = r_e = 2.818 × 10⁻¹⁵ m.
   - Inside r_sat: displacement > l_P → multiple spations share the load → trefoil knot topology.
4. Compute the **trefoil crossing pattern**:
   - The (2,3) torus knot has 3 crossing points viewed from any direction.
   - At each crossing, the displacement field has a SIGN REVERSAL.
   - Map the angular positions (θ, φ) of the three crossing planes.
   - Show how the three-fold symmetry organises the superluminal displacement into a stable pattern.

### Part III: The Counter-Rotation Shell Structure (r_e < r < a₀)

Outside the c-boundary, v(r) < c and the displacement per spation is fractional. The rotation must decay through the lattice. Classical fluid dynamics would give Couette flow; the spation lattice gives QUANTISED SHELL STRUCTURE.

**Tasks:**
1. **Viscous analogy**: in a continuous medium, a rotating sphere at angular velocity ω₀ in a viscous fluid induces rotation decaying as ω(r) ~ ω₀(R/r)³ (Stokes flow). Does the spation lattice reproduce this, or does it give a different power law?
   - SDT predicts v(r) ~ √(1/r) for gravitational orbital velocity.
   - Compute: does the ROTATIONAL field also go as 1/√r, or does it follow the 1/r³ Stokes pattern?
   
2. **Counter-rotation**: In a discrete lattice, a rotating shell drags the next shell. Angular momentum conservation requires alternating counter-rotation, damped by viscous coupling.
   - Compute the **torsional coupling coefficient** between adjacent Planck shells: κ = ε/(l_P c) where ε = u_CMB × l_P³ (elementary relay content).
   - Compute the **torsional relaxation time** per shell: τ_shell = l_P / c = t_P.
   - Does the rotation alternate sign shell-by-shell (acoustic-like), or does it propagate as a smooth decay?
   - KEY: the relay content ε arrives from ALL directions every tick (GPI axiom). This means the torsional coupling is NOT viscous — it is RELAY-MEDIATED. Each shell receives the rotation pattern of the previous shell via the relay field.

3. **Shell counting from R_p to a₀**:
   - N_shells = (a₀ - R_p) / l_P ≈ a₀/l_P = 3.27 × 10²⁴ Planck shells.
   - The rotation must persist through 3.27 × 10²⁴ shells with a velocity ratio of v(R_p)/v(a₀) = 1.831c / (αc) = 1.831/α = 250.9.
   - The decay factor per shell: δv/v per shell = ln(250.9) / (3.27 × 10²⁴) = 1.69 × 10⁻²³ per shell.
   - This is an INCREDIBLY GENTLE decay — effectively zero per shell. The rotation propagates almost without loss.

4. **Angular momentum quantisation**: 
   - At the electron orbit (r = a₀), the angular momentum is L = m_e v a₀ = m_e αc a₀ = ℏ (exactly one reduced Planck quantum).
   - At the proton surface: L_proton = m_p × 1.831c × R_p.
   - Compute L_proton in units of ℏ.
   - Compute the angular momentum GRADIENT dL/dr through the intermediate zone.

### Part IV: The Electron as a Driven Orbit

The electron at a₀ is NOT freely orbiting. It is DRIVEN by the proton's rotation field. The "orbit" is the resonance condition where the electron's circulation matches the proton's rotation field at that radius.

**Tasks:**
1. Compute the **resonance condition**: at r = a₀, the proton's rotation field velocity must equal the electron's orbital velocity:
   - v_field(a₀) = (c/ϟ)√(R_p/a₀) = αc → this IS the koppa formula. The resonance is automatic.
   
2. **Frame dragging**: the proton's rotation drags the local spation lattice. At each radius, the frame-dragging velocity is v_drag(r) = v(r) - v_Keplerian(r). Compute this residual.

3. **Exchange and interaction**: when two hydrogen atoms approach, their rotation fields overlap. Map the geometry:
   - At separation d, the rotation fields of two protons form a SUPERPOSITION.
   - Where the rotations ADD (prograde): enhanced velocity → lower local energy.
   - Where the rotations CANCEL (retrograde): reduced velocity → higher local energy.
   - This creates the covalent BOND: the electrons preferentially occupy the prograde zone between the protons.
   - Compute the bond length d where the prograde enhancement = 2αc.

4. **Spin coupling**: 
   - Proton spin = ½ℏ → the trefoil knot has a half-integer angular momentum.
   - Electron spin = ½ℏ → the (1,1) unknot also has half-integer angular momentum.
   - Parallel spins: rotation fields add → repulsion (Pauli exclusion).
   - Antiparallel spins: rotation fields partially cancel → attraction (singlet state).
   - Compute the spin-spin interaction energy from the rotation field overlap integral.

### Part V: The Full Kinematic Map (Quantitative Output)

Produce a table at the following radii with ALL kinematic quantities:

| r | r/l_P | v(r)/c | k(r) | z(r) | ω(r) [rad/s] | T(r) [s] | N_shell | d_disp/l_P | L(r)/ℏ | Regime |
|---|-------|--------|------|------|---------------|---------|---------|------------|--------|--------|
| 0.5 R_p | | | | | | | | | | Interior |
| R_p | | | | | | | | | | Surface |
| 2 R_p | | | | | | | | | | Near wake |
| r_e | | | | | | | | | | c-boundary |
| 10 r_e | | | | | | | | | | Far wake |
| 100 r_e | | | | | | | | | | Transition |
| λ̄_C_e | | | | | | | | | | Compton |
| 0.1 a₀ | | | | | | | | | | Inner Bohr |
| a₀ | | | | | | | | | | Ground state |
| 4 a₀ | | | | | | | | | | n=2 |
| 9 a₀ | | | | | | | | | | n=3 |

---

## NUMERICAL INFRASTRUCTURE

### Constants (from laws.hpp measured namespace — single source of truth)

```
c        = 299,792,458 m/s
ℏ        = 1.054571817 × 10⁻³⁴ J·s
l_P      = 1.616255 × 10⁻³⁵ m
t_P      = 5.39124 × 10⁻⁴⁴ s
α        = 7.2973525693 × 10⁻³
α⁻¹      = 137.035999084
m_e      = 9.1093837015 × 10⁻³¹ kg
m_p      = 1.67262192369 × 10⁻²⁷ kg
R_p      = 8.414 × 10⁻¹⁶ m
r_e      = 2.8179403262 × 10⁻¹⁵ m
a₀       = 5.29177210903 × 10⁻¹¹ m
λ̄_C_e    = 3.8615926796 × 10⁻¹³ m
ε        = u_CMB × l_P³ = 1.761 × 10⁻¹¹⁸ J
P_conv   = 2.459 × 10⁴⁸ Pa
ϟ_H      = 0.5464
k_H      = 137.036
```

### Derived proton rotation quantities

```
v_surface   = c / 0.5464 = 5.489 × 10⁸ m/s = 1.831c
ω_surface   = v_surface / R_p = 6.524 × 10²³ rad/s
T_surface   = 2π R_p / v_surface = 9.631 × 10⁻²⁴ s
r_Ϟ         = R_p / ϟ² = r_e = 2.818 × 10⁻¹⁵ m
```

### Derived electron quantities

```
v_electron  = αc = 2.188 × 10⁶ m/s
ω_electron  = v_electron / a₀ = 4.134 × 10¹⁶ rad/s
T_electron  = 2π a₀ / v_electron = 1.520 × 10⁻¹⁶ s
L_electron  = m_e × v_electron × a₀ = ℏ (exactly)
```

---

## SUCCESS CRITERIA

- [ ] Full velocity profile v(r) from R_p to 9a₀ at ≥ 20 logarithmically spaced radii
- [ ] Identification of the three regimes: superluminal (r < r_e), subluminal-strong (r_e < r < λ̄_C), subluminal-weak (λ̄_C < r < a₀)
- [ ] Displacement amplitude d(r)/l_P computed at all radii
- [ ] Angular momentum profile L(r) showing ℏ-quantisation at Bohr radii
- [ ] Counter-rotation shell analysis: period, coupling, decay rate
- [ ] Bond formation geometry from rotation field superposition
- [ ] Spin-spin interaction energy from rotation overlap
- [ ] ALL quantities computed from (ϟ, R_p, c, ℏ, m_e, m_p, α) — NO G, NO M, NO GM

## WHAT THIS INVESTIGATION CLOSES

If the rotation field map is complete and self-consistent:
1. The proton is a fully kinematic object: a superluminal phase vortex at 1.83c.
2. The electron orbit is a driven resonance, not an independent particle.
3. Chemical bonding is rotation-field superposition.
4. Spin is the angular momentum of the (p,q) torus knot.
5. The c-boundary r_Ϟ = r_e acquires physical meaning: it is the saturation radius where spation displacement drops below one Planck length.
6. The transition from "nuclear physics" (r < r_e) to "atomic physics" (r > r_e) is the transition from saturated to linear lattice response — a single, continuous field with no boundary.
