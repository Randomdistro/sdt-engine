# FLM05: Lattice Pulse Propagation — The Non-Contact Mechanism

## THE PROBLEM WITH CQ09b

CQ09b showed that the proton field and the electron field are algebraically identical: v(r) = cα√(a₀/r). But this is physically meaningless because it treats the field as a smooth, pre-existing thing at every point simultaneously. In reality, the "field" is built one tick at a time, through 3.27 × 10²⁴ Planck shells of spations, and at every shell there is a dissipation, a phase lag, a reaction. The combined effect of those 10²⁴ discrete handoffs is what MAKES the inverse square law — not a magical smooth function written on paper.

This investigation does the real work: the tick-by-tick mechanism.

---

## THE LATTICE: PLANCK SPHERES WITH A REACTIVE GAP

### The spheres

These are **Planck spheres**. The Planck length l_P = 1.616 × 10⁻³⁵ m is the smallest scale before breaking. Each spation sphere has:

- **Radius: r_s = l_P / 2**
- **Diameter: l_P**
- **The sphere IS the Planck scale. It cannot be compressed further. It is the floor.**

If you try to go below l_P, you break the lattice. The sphere is incompressible, indeformable, structureless. It is the quantum of space.

### The equilibrium gap

In the free lattice (no matter), 12 spheres surround each central sphere. The centres are NOT at l_P separation — they are at some d > l_P. The gap between any two adjacent spheres is:

$$g_0 = d - 2r_s = d - l_P$$

This gap is:
- **Identical in all directions** — isotropy demands it.
- **Reactive** — it is not empty. It is the channel through which relay content ε passes.
- **The medium** — the gap IS the physics. The spheres are inert. The gaps carry the relay.

The gap provides two things that solid contact cannot:

1. **Deformability without compression.** The gap can narrow or widen. The spheres do not change shape. The lattice is soft because the gaps are soft, not because the spheres are soft.

2. **Compression without deformation.** The gap can be compressed (narrowed) all the way to zero without deforming the spheres. The spheres stay at r_s = l_P/2. Only the gap changes.

### The contact condition: MATTER

**Matter is where the gap has been forced to zero.**

When displacement is large enough, the gap between adjacent spations is fully compressed. The spheres are now in physical contact. This is a qualitatively different state:

| State | Gap width | Regime | Physics |
|-------|----------|--------|---------|
| Free lattice | g = g₀ (equilibrium) | Vacuum | Relay at c, isotropic, no force |
| Compressed | 0 < g < g₀ | Gravitational field | Asymmetric relay, convergence gradient |
| Contact | g = 0 | **Matter** | Spheres touching, displacement saturated |
| Below contact | g < 0 (impossible) | Forbidden | Would require compressing Planck spheres |

**The "surface" of matter is where the gap just barely reopens.** Inside: contact. Outside: the gap gradually reasserts itself. This gradient — from zero gap to equilibrium gap — IS the gravitational field.

### Why inverse square is inevitable

From the contact zone outward, the gap must reassert itself. The displacement flux emanating from the contact zone spreads over the surface area of concentric shells:

- At shell n (radius n × l_P from the contact surface): area ≈ 4πn²l_P²
- The total displacement flux F is conserved (what went in must come out).
- Displacement per spation at shell n: δ_n = F / (4πn²) → **1/r²**

This is not dynamics. This is **geometry**. The 1/r² relationship is the solid angle of a sphere. It follows from three spatial dimensions, not from any force law.

### The infinite recursion

For the gap to be self-consistent:
- The 12 spheres around the central sphere must be at equal angular spacing.
- The lateral spread required for even angular distribution lifts them off the surface.
- But this lift is only consistent if EACH of the 12 also has 12 around it, at the same gap.
- And each of those 12 must have 12.
- **The structure must tessellate infinitely.** There is no outer boundary. The lattice is infinite, recursive, and self-consistent at every scale.

This recursive tessellation is what gives the lattice its:
- **Rigidity** (every spation is locked by its 12 neighbours, each locked by their 12, etc.)
- **Isotropy** (the gap is the same in all 12 directions at every point)
- **Invariance** (the relay content ε is the same in every gap, every tick)

---

## INVESTIGATION STRUCTURE

### Part I: One Tick — The Anatomy of a Pulse

Model a single relay event across one gap.

**Tasks:**
1. Define the gap geometry:
   - Spation radius: r_s = l_P / 2. The sphere diameter IS the Planck length.
   - Centre-to-centre distance: d (the lattice constant; d ≥ l_P)
   - Equilibrium gap width: g₀ = d - l_P
   - The gap is the FREE SPACE between surfaces of adjacent Planck spheres.
   - In the gap: relay content ε traverses at c.
   - Inside the sphere: structureless. At the Planck limit. Cannot be subdivided.

2. Displacement mechanics:
   - A displaced spation has its centre shifted by δ from equilibrium.
   - Gap toward displacement: g₀ - δ (compressed)
   - Gap away from displacement: g₀ + δ (expanded)
   - **When δ = g₀: gap is ZERO. CONTACT. This is MATTER.**
   - **When δ > g₀: IMPOSSIBLE. The sphere cannot compress. Planck scale is the floor.**
   - So δ is hard-bounded: 0 ≤ δ ≤ g₀.

3. Two modes — the only two that exist:

   **Mode A: Gap compression (δ < g₀) — GRAVITY**
   - The gap narrows. Relay arrives earlier from compressed side, later from opposite.
   - Phase velocity asymmetry: Δv/c ≈ δ/g₀
   - Spheres do not deform. Only the gap changes.
   - Deformability without compression of the spheres.
   - Compression of the gap without deformation of the spheres.

   **Mode B: Contact (δ = g₀) — MATTER**
   - Gap = zero. Surface-to-surface contact.
   - A contact event in an otherwise contactless medium.
   - The displacement is saturated. The pressure is at P_conv maximum.
   - This IS what matter is: a region of forced contact in a non-contact lattice.

### Part II: Shell-by-Shell — The Gap Reasserts Itself

From the contact zone (matter) outward, the gap reopens. This gradient IS gravity.

**Tasks:**
1. At the surface of matter: g = 0 (just at contact).
2. Moving outward: the gap reopens. The displacement δ(r) decreases from g₀ toward 0.
3. Flux conservation:
   - Shell n has ≈ 4πn² spations.
   - Total displacement flux: F_n = 4πn² × δ_n = constant.
   - **δ_n = F₀ / (4πn²) → 1/r² law is FORCED by geometry.**

4. Gap profile: g(r) = g₀ − δ(r) = g₀ − F₀/(4πr²/d²)
   - g → g₀ at r → ∞ (free lattice recovered)
   - g → 0 at r = R_matter (the contact surface)

5. Test: compute g(r) for hydrogen at R_p, r_e, a₀.

### Part III: The Rotorpause

The proton and electron are both contact zones. Between them: a hard equilibrium surface.

**Tasks:**
1. Proton displacement: δ_p(r) = F₀_p / (4πr²)
2. Electron displacement: δ_e(r') = F₀_e / (4πr'²) where r' = distance from electron
3. Rotorpause at r_rp where δ_p = δ_e:
   - r_rp / (a₀ − r_rp) = √(m_p/m_e) = 42.85
   - **r_rp = 0.9772 a₀** (proton dominates 97.7% of the interior)

4. Electron's domain: thin shell 0.977 a₀ to a₀ (thickness ≈ 0.023 a₀)
5. **Flail tail:** beyond the electron, its displacement flux dominates in a compressed cone.
   - Opening angle θ ≈ √(m_e/m_p) ≈ 1.34°
   - Like a planet's magnetotail in the solar wind.

### Part IV: The Pulse as Light

A transverse gap perturbation propagates at c. This IS a photon.

**Tasks:**
1. TRANSVERSE: gap narrows perpendicular to propagation → cannot be absorbed by radial relay → propagates without loss. This is LIGHT.
2. LONGITUDINAL: gap narrows along propagation → absorbed into the convergence field → this is GRAVITY.
3. Why transverse survives: centrosymmetric lattice (GPI axiom) cannot convert transverse → longitudinal. Orthogonality is preserved.
4. Wavelength = gap crossings per oscillation cycle.
5. Redshift: in a displacement zone, outgoing gaps are wider. Each photon cycle is stretched. Accumulated stretch = z = 1/ϟ².

### Part V: Determining the Gap Width g₀

**r_s = l_P/2 is fixed.** What remains: the centre-to-centre distance d, hence g₀ = d − l_P.

**Tasks:**
1. c = d/t_P defines d = c × t_P = l_P.
   - This gives g₀ = 0. Contact everywhere. PROBLEM.

2. **Resolution**: l_P is the LATTICE CONSTANT (sphere + gap). The sphere is a fraction of l_P:
   - Sphere diameter = l_P × f_sphere (f_sphere < 1)
   - Gap = l_P × f_gap = l_P × (1 − f_sphere)
   - c = l_P/t_P includes both sphere traversal and gap crossing.

3. The gap fraction f_gap determines displacement sensitivity:
   - δ_max = g₀ = l_P × f_gap (contact threshold)
   - Sensitivity: Δv/c ≈ δ/(l_P × f_gap) = (δ/l_P) / f_gap

4. From the transfer function f = P_eff/P_conv = 2.125 × 10⁻¹⁷:
   - If f relates to f_gap, this constrains the sphere/gap ratio.

---

## THE DEEP STRUCTURE

1. **THE GAP IS THE MEDIUM.** Planck spheres are inert, incompressible. All physics is in the gap.

2. **MATTER IS FORCED CONTACT.** A contact event in an otherwise contactless medium. The contact zone IS the particle. Its surface IS the charge radius.

3. **GRAVITY IS THE GAP REASSERTING ITSELF.** From contact outward, the gap reopens as 1/r². The gradient is the force. No mystery.

4. **LIGHT IS TRANSVERSE GAP OSCILLATION.** Perpendicular to radial displacement, cannot be absorbed, propagates forever.

5. **REDSHIFT IS GAP STRETCHING.** Photon cycles stretch as they climb wider gaps. z = 1/ϟ².

6. **INVERSE SQUARE IS d=3.** Flux over 4πr² = 1/r² per spation. Geometry, not dynamics.

7. **c IS ONE HOP PER TICK.** Lattice constant / Planck time. Cannot be exceeded. Cannot be skipped.

---

## SUCCESS CRITERIA

- [ ] Gap geometry: r_s = l_P/2, g₀ = d − l_P, contact condition defined
- [ ] Single-tick anatomy: gap compression → relay asymmetry → force
- [ ] Contact → matter: proton as a contact zone
- [ ] Shell-by-shell gap reopening: δ_n ∝ 1/n² from flux conservation
- [ ] Rotorpause location: r_rp ≈ 0.9772 a₀
- [ ] Flail tail opening angle: θ ≈ 1.34°
- [ ] Light as transverse gap oscillation
- [ ] Redshift from gap stretching = z = 1/ϟ²
- [ ] Gap fraction constrained by transfer function
- [ ] All from {l_P, t_P, ε, d=3} — NO fitted parameters

## TEMPERATURE THRESHOLDS — THE GAP CONNECTION

The interspation gap may have direct temperature correlates:

| Temperature | What happens | Gap interpretation |
|-------------|-------------|-------------------|
| **T_CMB = 2.7255 K** | Present-day background. Free lattice. | Full equilibrium gap g₀. Relay at c. No displacement. |
| **T_rec = 3000 K** | Recombination. Neutral atoms form. The Clearing. | The gap CLOSES at this energy density. Below 3000K the gap reopens. Above 3000K the gap is consumed — all spations in contact — no atoms can form because the lattice is in the contact regime everywhere. This IS why recombination happens at 3000K: it is the temperature at which the interspation gap first appears. |
| **T_solar_trough = 4400 K** | The solar temperature "trough" — the minimum in the solar atmosphere, crossable only by CME. | A SECOND gap threshold? The gap between the photosphere (5800K) and the corona (1-2 MK) has a hard minimum at 4400K. If the gap has a secondary resonance at this energy, it would explain why the transition region is so thin and why energy must be injected violently (CME/flares) to cross it. |
| **T_photosphere = 5800 K** | Solar surface. | Gap fully compressed locally. Continuous emission. |

### The connection

If T_rec = 3000K is the temperature at which the interspation gap first opens:
- u_gap = a_rad × T_rec⁴ = 6.13 × 10⁻² J/m³
- u_CMB = a_rad × T_CMB⁴ = 4.17 × 10⁻¹⁴ J/m³
- Ratio: u_gap / u_CMB = T_rec⁴ / T_CMB⁴ = (3000/2.7255)⁴ = 1.46 × 10¹²

The gap opened when the energy density dropped by a factor of 10¹² from the contact regime. The present-day gap is the FULLY RELAXED state, 10¹² times wider than at the threshold.

This connects the CMB temperature, the recombination epoch, the solar transition region, and the interspation gap in a single framework. FLM05 must test this quantitatively.
