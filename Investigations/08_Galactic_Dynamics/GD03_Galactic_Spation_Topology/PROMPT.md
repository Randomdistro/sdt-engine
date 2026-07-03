# GD03: GALACTIC SPATION TOPOLOGY — Mapping the Lattice Through the Milky Way

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 0. GROUND ZERO STATEMENT

The spation lattice is the medium. It is a hyperspherical superfluid of Planck-length spheres (radius = ℓ_P/2). It comprises all fields, generates all movement, moderates all interactions, and contains all particles as persistent displacements. This investigation maps the **topological state of the spation lattice** at every radial scale from the proton interior (10⁻¹⁶ m) to the MW disk edge (10²¹ m) — 37 orders of magnitude — and proves that the same nine axioms (R1-R6, M1-M3) govern the lattice at every scale without exception.

PPT07 proved the particle scale. CR01 proved the redshift scale. GD02 proved the galactic structure scale. GD03 unifies them: one lattice, one topology, one closure condition (zk² = 1), traced continuously through the Milky Way.

---

## 1. THE SPATION — DEFINITION AND PROPERTIES

### 1.1 What Is a Spation?
From Axiom R1: a single element of the gap-free, contact-only relay medium.
- **Geometry**: sphere of radius r_s = ℓ_P / 2 = 8.081 × 10⁻³⁶ m
- **Packing**: hyperspherical close-packing (kissing number 24 in 4D projection → 12 nearest neighbours in 3D)
- **Content**: each spation carries deformation content ε = u_CMB × ℓ_P³ = 1.761 × 10⁻¹¹⁸ J (Axiom R3)
- **Relay rate**: nearest-neighbour transmission at exactly c = ℓ_P / t_P (Axiom R2)
- **State**: at any instant, each spation is in one of:
  - **Quiescent**: carrying background convergence Φ = Nε
  - **Displaced**: part of a persistent vortex (matter)
  - **Transiting**: relaying a perturbation (photon/wave)

### 1.2 The Convergence Pressure
From Law I (Theorems T1-T2):
- N = R_CMB / ℓ_P = 5.894 × 10⁶¹ shells from here to the Clearing
- Φ = Nε = 1.038 × 10⁻⁵⁶ J (total convergence burden per point)
- P_conv = Φ / ℓ_P³ = Nε / ℓ_P³ = 2.459 × 10⁴⁸ Pa (convergence pressure at every point)
- This is the **isotropic background**. It exists everywhere. It is not a force — it is the medium's resting state.

### 1.3 Matter as Displacement
From Axioms M1-M3 and Law IV:
- A particle is a **persistent displacement** of spations from their equilibrium positions
- The displaced volume V_disp determines the mass: m = Φ V_disp / (3 ℓ_P³ c²)
- The displaced spations circulate at v_circ, consuming movement budget: v_circ² + v_trans² = c²
- Topology determines stability: W=1 (electron, simple torus), W=3 (proton, trefoil knot)

---

## 2. INVESTIGATION CHAIN — 12 RADIAL ZONES

Map the spation lattice state at each zone. For every zone, compute and report:

| Quantity | Symbol | Formula |
|----------|--------|---------|
| Characteristic velocity | v | measured (orbital, rotation, dispersion) |
| k-value | k | c / v |
| Spation depth | z | 1/k² = (v/c)² |
| c-boundary | Ϟ | v²R/c² = R/k² |
| Closure check | zk² | must equal 1.000000 |
| Convergence pressure | P_local | P_conv × (1 ± δ) where δ = local displacement density |
| Displacement density | n_disp | V_disp_total / V_zone |
| Relay coherence length | λ_coh | characteristic wavelength of lattice perturbations |
| Traction fraction | τ | 1/3 (must hold at every scale — Theorem T7) |

### Zone 1: PROTON INTERIOR (r < R_p = 0.84 fm)
**Source**: PPT07, FLM03

- k = 0.5464 (INSIDE c-boundary: superluminal phase rotation)
- v_phase = c/k = 1.831c (phase velocity, not signal velocity)
- z = 1/k² = 3.350 (z > 1 → superluminal interior)
- Ϟ = R_p / k² = r_e = 2.818 fm (the proton's c-boundary IS the classical electron radius)
- Topology: (2,3) trefoil knot, W=3
- V_disp = 1.834 × 10⁻⁵⁸ m³
- Mass from topology: m_p/m_e = 6π⁵ = 1836.118 (PPT07 result, 0.002% from measured)

**Task**: Compute the spation displacement density inside R_p. How many spations are displaced? What is the local convergence pressure perturbation? Show that the traction fraction τ = 1/3 holds at the proton boundary (Theorem T7).

### Zone 2: PROTON c-BOUNDARY TO BOHR RADIUS (r_e < r < a₀)
**Source**: FLM03, laws.hpp bridge namespace

- At r = r_e (c-boundary): k = 1, v = c, z = 1 (transition surface)
- At r = a₀: k = 1/α = 137.036, v = αc, z = α² = 5.325 × 10⁻⁵
- This is the **strong-to-electromagnetic transition zone**
- The lattice transitions from superluminal vortex interior to Keplerian orbital regime
- Electron "orbit" is the driven resonance of the proton's wake field at r = a₀

**Task**: Map z(r) continuously from R_p through r_e to a₀. Identify the k=1 crossing (c-boundary). Compute the convergence pressure gradient dP/dr through this transition. Show that the Coulomb force law F = (π/4) P_eff R_charge⁴ / r² (Law III, T3) emerges naturally from the lattice pressure gradient.

### Zone 3: ATOMIC / MOLECULAR (a₀ < r < 10 nm)
**Source**: laws.hpp atomic namespace

- Multi-electron atoms: z = Z²α² for charge Z
- Molecular bonds: shared Ϟ fields between nuclei (micro-scale bonding)
- The lattice here is in the "quiescent + perturbation" regime: background P_conv with small displacement wakes from nuclear vortices

**Task**: Compute the lattice displacement density for H, He, Fe. Show how molecular bond formation (shared occlusion) at this scale is topologically identical to bar-arm junction bonding at galactic scale (CQ19b). Establish the formal analogy.

### Zone 4: STELLAR INTERIOR — SUN (r < R_Sun = 6.957 × 10⁸ m)
**Source**: laws.hpp bridge namespace, SAR03

- k_Sun = 686.3, v_surface = c/k = 4.369 × 10⁵ m/s
- Ϟ_Sun = R_Sun / k² = 1477 m
- z_surface = 1/k² = 2.124 × 10⁻⁶
- Pressure domain radius: r_domain = 3.12 × 10¹⁵ m ≈ 20,800 AU (Law II)
- The Sun is a **convergence recycler**: it captures convergence pressure from all 4π, fuses baryons, re-emits photons that feed the lattice

**Task**: Map z(r) from solar core (where nuclear reactions occur) to solar surface. Compute the displacement density at the core (n_disp_core) vs surface (n_disp_surface). The Sun's baryonic mass = 1.989 × 10³⁰ kg. How many spation displacement volumes does this represent? Verify: N_disp = M_Sun / m_p × V_disp_p gives the correct total displaced volume.

### Zone 5: STELLAR NEIGHBOURHOOD — SOLAR PRESSURE DOMAIN (R_Sun < r < r_domain)
**Source**: Law II

- Between the Sun's surface and r_domain (20,800 AU), the Sun's convergence field dominates over the CMB background
- Beyond r_domain, the lattice returns to the isotropic CMB convergence state
- Planetary orbits sit INSIDE the pressure domain
- Each planet has its own Ϟ: Earth = 4.43 mm, Jupiter = 14.2 m

**Task**: Compute the lattice state at each planet's orbital radius. Show that Ϟ_Sun derived from every planet's orbit (via SDT Kepler: Ϟ = 4π²a³/T²c²) converges to the same value (CQ18a verification). Map the transition at r_domain where solar convergence equals CMB convergence.

### Zone 6: INTERSTELLAR MEDIUM — LOCAL BUBBLE (r_domain < r < 100 pc)
**Source**: CQ19c ring structure

- Between pressure domains, the lattice is in near-quiescent state
- Local ISM density ~ 0.1–1 atom/cm³ → displacement density n_disp ~ 10⁻⁵⁷ m⁻³
- The lattice "relaxes" between stellar pressure domains
- Stars are point displacements; the ISM between them is almost pure lattice

**Task**: Compute the background lattice state (convergence pressure, displacement density) in the local ISM. Compare to the proton interior. The ratio should be enormous — the ISM is "empty lattice" with occasional displacement points. Quantify: what fraction of the local volume is displaced vs quiescent?

### Zone 7: GALACTIC NUCLEUS — S-STAR CLUSTER (r < 0.04 pc from Sag A*)
**Source**: CQ19b Shell 1, CQ19c Rings 1-2

- Ϟ_SagA = 6.26 × 10⁹ m (from S2 orbit, no G, no M)
- S2: a = 1031 AU, P = 16.046 yr, e = 0.8843, v_peri = 7650 km/s
- S62: P = 9.9 yr (closest known orbit)
- Displacement density: extremely high — nuclear star cluster packs ~10⁷ M_Sun in 5 pc

**Task**: Trace the lattice from Sag A*'s c-boundary outward through the S-star orbits. At what radius does k cross from <1 (superluminal, inside the BH c-boundary) to >1 (subluminal, matter can exist)? This is the event horizon in SDT terms — the surface where v_orbital = c. Compute Ϟ_SagA from at least 5 independent S-star orbits and show convergence. Map the displacement density profile ρ_disp(r) through the nuclear cluster.

### Zone 8: BULGE AND BAR (0.04 pc < r < 3.5 kpc)
**Source**: CQ19b Shells 2-5, GD02 main

- Nuclear star cluster σ ~ 100 km/s → k ~ 3000
- Central molecular zone: r < 200 pc, dense gas, high displacement density
- Inner bulge: v_circ ~ 210 km/s at r = 2 kpc → Ϟ_bulge = 3.03 × 10¹³ m
- Bar: semi-axes 3.5 × 1.5 × 1.0 kpc, oriented 27° from Sun-GC line
- Bar pattern speed: Ω_bar ~ 40 km/s/kpc

**Task**: Map the lattice topology through the bulge. The bar is a NON-AXISYMMETRIC displacement structure — a triaxial overdensity rotating as a rigid body within the lattice. Compute the convergence pressure anisotropy created by the bar: P(θ) = P_conv × (1 + δ_bar(θ)). Show that the bar's rotation speed is consistent with the lattice relay rate (bar cannot rotate faster than information propagates through the lattice). Compute the bar's total Ϟ and its displacement fraction relative to the bulge.

### Zone 9: BAR-ARM JUNCTIONS — MACRO BONDING (r ~ 3-5 kpc)
**Source**: CQ19b ArmJunction struct, CQ19c binding proof

- This is the SDT bonding zone: where the bar's Ϟ field overlaps with the spiral arm Ϟ field
- Analogous to atomic covalent bonding: shared occlusion between two displacement structures
- Near-end junction: Scutum-Centaurus arm attaches to bar (l ~ 30°)
- Far-end junction: Sagittarius-Carina arm attaches to bar (l ~ 330°)

**Task**: This is CRITICAL. Compute:
1. Ϟ_bar at the junction radius
2. Ϟ_arm at the junction radius
3. The overlap fraction: f_overlap = Ϟ_shared / (Ϟ_bar + Ϟ_arm)
4. Compare f_overlap to atomic bond overlap fractions (e.g., H₂ molecule)
5. Compute the "bond energy" = convergence pressure × overlap volume
6. Show that the junction is dynamically stable (not just coincidental alignment)

This is the macro-bonding proof. If f_overlap is non-trivial and the bond energy is mechanically consistent with the arm streaming velocity, then galactic spiral structure is BONDED in the same topological sense as molecular structure. The lattice mediates both identically.

### Zone 10: SPIRAL ARMS AND DISK (3 kpc < r < 15 kpc)
**Source**: CQ19d (baryon census), CQ19e (spiral arm tracer)

- Rotation curve: v(R₀) = 229 km/s, approximately flat
- Disk: exponential, h_R = 3.5 kpc, h_z = 0.3 kpc
- Ϟ at R₀ = v²R₀/c² = 1.52 × 10¹⁴ m
- z at R₀ = (229/299792)² = 5.83 × 10⁻⁷
- Four major arms + Local arm (Reid+2019 log-spiral model)
- Self-lensing: we sit inside the lens (CQ19e, δθ up to 0.46 arcsec)

**Task**: Map the lattice through all 100 rings of the CQ19c structure. At each ring:
1. Compute v_circ(r) from the rotation curve
2. Derive z(r), k(r), Ϟ(r)
3. Compute the displacement density from the baryon census (CQ19d)
4. Compute the convergence pressure perturbation from the disk density model
5. Identify spiral arm density enhancements as lattice compression waves
6. Quantify the self-lensing correction (CQ19e) as a direct consequence of the z-gradient

The flat rotation curve means z(r) ≈ constant across the disk. In the spation lattice, this means the displacement density adjusts to maintain constant convergence throughput. Map this explicitly.

### Zone 11: DISK EDGE AND HALO (15 kpc < r < 200 kpc)
**Source**: CQ19d extended, CR01 cosmological

- Rotation curve declines slowly: v ~ 180 km/s at 30 kpc
- Stellar halo: sparse, σ ~ 100 km/s, nearly isotropic
- Globular clusters: ancient displacement structures orbiting in the lattice
- The "missing mass" that standard model attributes to a dark matter halo

**Task**: Map the lattice state at the disk edge. The displacement density drops dramatically. What does the lattice look like here? Nearly pure quiescent lattice with occasional stellar displacement points. Compute:
1. The lattice relaxation profile: how quickly does z(r) → 0 beyond the disk?
2. The total Ϟ of the MW from the rotation curve at r = 15 kpc, 30 kpc, 50 kpc
3. The transition from galactic convergence field to intergalactic lattice
4. Show that the "flat rotation curve" is a natural consequence of the lattice's aggregate displacement structure — not evidence of a separate dark matter component

### Zone 12: INTERGALACTIC → LANIAKEA (r > 200 kpc)
**Source**: CR01 unified, CQ18f GA test

- Beyond the MW: the lattice returns to near-CMB quiescent state
- Laniakea supercluster: aggregate convergence field of ~10⁵ galaxies
- Ϟ_Laniakea = (627/c)² × 160 Mpc
- CMB dipole: lattice convergence gradient, not kinematic bulk velocity
- z between galaxies = strain rate in the lattice (what standard model calls "expansion")

**Task**: Map the lattice from the MW disk edge through the Local Group, through the Virgo Supercluster, to the Laniakea boundary. Show that the CMB dipole is a convergence pressure gradient in the lattice (CQ18f finding). Show that intergalactic redshift is lattice strain accumulation along the photon path. Connect back to Law I: every shell from here to the Clearing contributes ε.

---

## 3. CLOSURE HIERARCHY — THE FOUR LEVELS

GD03 does not just check one identity. There are **four nested closure levels**, each harder than the last. All four must hold at every zone. Failure at any level invalidates the lattice claim at that scale.

### Level 1: LOCAL IDENTITY — zk² = 1

The dimensionless invariant. At every radial position:

$$z \times k^2 = \left(\frac{v}{c}\right)^2 \times \left(\frac{c}{v}\right)^2 = 1$$

This is trivially true by construction when both z and k are derived from the same v. **It is necessary but not sufficient.** It proves only that the notation is self-consistent — not that the physics is.

**Test**: Compute zk² at every zone boundary. Report to 12 significant figures. It must be 1.000000000000 everywhere.

### Level 2: BOUNDARY SCALAR — Ϟ = R/k²

The c-boundary radius. At every structural boundary (proton surface, stellar surface, galactic shell boundary):

$$\Upsilon = \frac{R}{k^2} = \frac{v^2 R}{c^2}$$

This is the single scalar that characterises the convergence field of a displacement structure. It is distance-independent — the same Ϟ is measured whether you probe it from 1 AU or 10 kpc away.

**Test**: At each zone, compute Ϟ from the local velocity and radius. Verify that Ϟ is invariant under change of probe distance (e.g., Ϟ_Sun must be the same from Mercury and from Neptune).

### Level 3: PARENT INVARIANCE — Independent probes return the same Ϟ_parent

This is the first non-trivial closure. Multiple independent probes of the same parent structure must converge to the same Ϟ:

- **Solar system**: 8 planets, each with different (T, a), all must give the same Ϟ_Sun via 4π²a³/T²c² (CQ18a verified this)
- **Sag A***: S2, S62, S55, S38, S14 — each orbit gives an independent Ϟ_SagA. They must agree.
- **MW disk**: rotation curve at R = 3, 5, 8, 10, 15 kpc — the enclosed Ϟ(R) must form a self-consistent monotonic profile
- **Laniakea**: independent probes (CMB dipole, galaxy count dipole, peculiar velocity field) must give the same Ϟ_Laniakea

**Test**: For each parent structure, compute Ϟ from at least 3 independent probes. Report the standard deviation. If σ/μ > 1%, the closure fails at that scale.

**This is where CQ18a-b live.** They already proved Level 3 for the solar system and for exoplanetary systems. GD03 extends it to the galactic nucleus, the bulge, the disk, and Laniakea.

### Level 4: PREDICTIVE CLOSURE — The Drag Wake Maps the Galaxy

**This is the critical level.** Levels 1-3 all start from a measured velocity v and derive Ϟ. This is descriptive, not predictive. Level 4 starts from the ENGINE and maps what the lattice must look like.

#### THE ENGINE

Matter is real. The realest of real. Each baryon is an eternity drive — an indestructible engine crushed under P_conv = 2.459 × 10⁴⁸ Pa, omnidirectional convergence pressure. It survives by **deflecting** that pressure: channelling convergence through the poloidal axis of its (2,3) trefoil topology. This channelling IS what creates the rotation. The proton doesn't rotate because something spins it — it rotates because deflecting convergence through the poloidal channel is the only geometric solution to surviving under P_conv.

At the proton surface: v = 1.83c (k = 0.5464). This is superluminal phase rotation — the displacement structure whips the adjacent spations around at faster than light.

#### THE DRAG WAKE

The rotation doesn't stop at the proton surface. It propagates outward through contact:
- Shell 1 (nearest neighbours): dragged by the proton surface at ~1.83c
- Shell 2: dragged by Shell 1, slightly slower
- Shell 3: dragged by Shell 2, slower still
- ...continuing outward, each shell dragging the next through contact friction

This is not a "field" propagating through empty space. This is a **mechanical rotation wake** — nearest-neighbour contact drag in an inviscid superfluid of Planck-length spheres. The wake decays with distance because each shell has more spations than the last (surface area grows as r²) and the drag must be shared among more contact points.

The wake profile v(r) from a single proton:
- r < R_p: superluminal interior, v > c, z > 1 (Zone 1)
- r = Ϟ (c-boundary): v = c, z = 1, k = 1 (the transition surface)
- r = a₀: v = αc, z = α² (the electron resonance — driven by the wake)
- r → ∞: v → 0, z → 0 (wake decays, lattice returns to quiescent)

**The electron is not a separate engine at a₀. It is a resonance node in the proton's drag wake.** The proton drives it. The "electron mass" (0.511 MeV) is the relay-state energy at the c-boundary, carried by the proton at all times.

#### WHAT GD03 MUST MAP

At every radial scale, the drag wake from displacement engines creates observable effects. The SAME mechanism — contact drag of spation rotation — manifests as different "forces" depending on distance and topology:

| Scale | Distance | What the drag wake looks like | Classical name |
|-------|----------|-------------------------------|----------------|
| Proton interior | r < R_p | Superluminal vortex, confined by trefoil topology | Strong force |
| c-boundary → a₀ | R_p → a₀ | Wake drives electron resonance, 1/r² coupling | Electromagnetism |
| Molecular | a₀ → nm | Overlapping wakes from adjacent engines share drag | Chemical bonding |
| Stellar | AU → pc | Aggregate drag from ~10⁵⁷ engines creates Ϟ_Sun | Gravity |
| Galactic | kpc | Aggregate drag from ~10⁶⁸ engines creates rotation curve | Galactic dynamics |

GD03 must compute the drag wake profile from a SINGLE displacement engine (one proton), then show how AGGREGATION of ~10⁶⁸ engines (the MW's baryon count) produces the observed rotation curve.

#### THE LEVEL 4 TEST

1. **Single-engine wake**: Derive v(r) from the proton surface outward, using only:
   - Proton surface velocity: v₀ = 1.83c
   - Contact drag coefficient: determined by the 12-around-1 packing geometry and the octahedral gap mobility
   - Shell-by-shell propagation: each shell drags the next, area grows as 4πr²

2. **Aggregation**: Sum the wakes from N baryons distributed according to the MW's baryonic density profile:
   - Ϟ(r) = Σᵢ Ϟᵢ(r - rᵢ) for each baryon i at position rᵢ
   - The rotation curve v(R) = c√(Ϟ_enclosed(R)/R) must emerge from this sum

3. **Compare**: predicted v(R) to the observed MW rotation curve.

**The key unknown**: the drag coefficient. How much velocity does each shell lose to the next? This is determined by:
- The packing geometry (12-around-1, FCC/HCP)
- The octahedral gap mobility (how freely spations can rearrange)
- The inviscid character of the superfluid (zero viscosity → perfect relay? or does the gap mobility introduce effective dissipation?)

GD03 must derive this coefficient from the lattice geometry, then show it produces the correct v(r) at every scale.

#### CONNECTION TO ELECTRICITY, MAGNETISM, CHEMICAL BONDS

At each scale, the drag wake has structure beyond the simple radial 1/r² envelope:

- **Electricity**: The ℓ=1 (dipole) component of the wake. The poloidal channel creates an axial pressure gradient — convergence is preferentially occluded along the channel axis vs the equatorial plane. This anisotropy IS charge. The wake's ℓ=1 moment IS the Coulomb field (from Closure Derivation §2, Wake Tensor).

- **Magnetism**: The ℓ=2 (quadrupole) component. When the displacement has toroidal circulation (v_T ≠ 0), the wake acquires an organised flow pattern that falls off as 1/r³. This IS the magnetic dipole field. No v_T → no ℓ=2 → no magnetic moment (neutrino prediction, PPT04).

- **Chemical bonding**: When two engines are close enough that their drag wakes OVERLAP, the shared drag region has lower convergence pressure than the non-shared region. This creates a net inward force — the engines are pushed together by the excess external convergence. This IS the covalent bond. The overlap geometry determines bond angle, length, and energy.

- **Gravity**: The ℓ=0 (monopole) component. The aggregate isotropic occlusion from all shells of the wake. At stellar/galactic distances, only ℓ=0 survives — the higher multipoles have decayed. This IS Newton's 1/r² (via F = (π/4) P_eff R₁² R₂² / r²).

GD03 must trace all four of these through the 12 zones and show that they are the SAME wake, the SAME drag, the SAME contact mechanics — differentiated only by distance, topology, and which ℓ-moment dominates.

---

### ADDITIONAL STRUCTURAL REQUIREMENTS

### 3.5 Traction: τ = 1/3
The normal projection of the convergence stress tensor must equal P_conv/3 at every boundary. This is a geometric identity in 3D (τ = 1/d for dimension d). Verify at the proton surface, stellar surface, Sag A* c-boundary, and disk edge.

### 3.6 Scale Invariance of the Force Law
F = (π/4) P_eff R₁² R₂² / r² must produce the correct force at every scale:
- Proton-electron: Coulomb force (using R_charge)
- Sun-Earth: g = 9.807 m/s² (using Ϟ_Sun)
- Sag A*-S2: orbital dynamics (using Ϟ_SagA)
- Bar-arm junction: macro bonding force (using overlap Ϟ)

### 3.7 Continuity of z(r)
z(r) must be continuous from the proton interior to the Clearing. No regime changes, no different formulae. One law: z = (v/c)² = 1/k². Plot z(r) on log-log across all 37 orders of magnitude.

---

## 4. DELIVERABLES

### 4.1 C++ Engine: `cq20_spation_topology.cpp`
Single standalone tool that:
- Defines all 12 zones with their measured inputs
- Computes the full lattice state (v, k, z, Ϟ, P, n_disp, τ, zk²) at each zone
- Traces z(r) continuously across all zones
- Prints the 37-order-of-magnitude closure table
- Verifies all five proof conditions (3.1–3.5)
- Reports PASS/FAIL for each zone and each condition

### 4.2 Bonding Proof: `cq20_macro_bonding.cpp`
Dedicated solver for Zone 9 (bar-arm junctions):
- Computes Ϟ_bar and Ϟ_arm at both junction points
- Calculates overlap fraction and bond energy
- Compares to atomic bond overlap (H₂, He₂)
- Produces the formal proof that galactic bonding IS atomic bonding at macro scale

### 4.3 Lattice Profile: `cq20_lattice_profile.cpp`
Numerical integration tool:
- Traces a radial ray from Sag A* to disk edge (0 → 15 kpc)
- At each step: compute displacement density, convergence perturbation, z(r)
- Produce a high-resolution radial profile of the lattice state
- Identify the zone boundaries (superluminal interior → c-boundary → Keplerian → flat curve)

---

## 5. PROHIBITED INPUTS (from Theory/00_Ruleset.md)

- No G, no M as fundamentals (Ϟ = v²R/c² replaces GM/c²)
- No dark matter, no dark energy
- No quantum wavefunctions, no fields as ontological primitives
- No quarks, gluons, virtual particles
- No probabilistic wavefunction collapse
- Only permitted inputs: {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} + measured observables

---

## 6. ADVERSARIAL TESTS

### 6.1 Falsification Condition A — Closure Failure
If zk² ≠ 1 at any zone to within measurement uncertainty, GD03 fails. The lattice would not be scale-invariant.

### 6.2 Falsification Condition B — Traction Deviation
If τ ≠ 1/3 at any boundary, the convergence stress tensor is not isotropic. The lattice would require a modified geometry.

### 6.3 Falsification Condition C — Bonding Asymmetry
If the bar-arm junction overlap fraction is zero or negative, galactic bonding does not exist. Spiral structure would be coincidental, not structural.

### 6.4 Falsification Condition D — z(r) Discontinuity
If z(r) requires different formulae in different zones (as standard physics requires: QCD inside nucleon, QED at atomic scale, Newtonian at stellar, GR at galactic), the SDT lattice fails. It would not be a single medium.

---

## 7. CONNECTION TO PRIOR INVESTIGATIONS

| CQ | Contribution to GD03 |
|----|----------------------|
| PPT07 | Zone 1-2: particle topology, m_p/m_e = 6π⁵ from (2,3) trefoil |
| CQ18a | Zone 5: solar Ϟ from orbital timing, no G |
| CQ18b | Zone 5: multi-planet Ϟ consistency |
| CQ18c | Zone 7: AGN z_grav from BLR line widths |
| CQ18d | Zone 12: six-layer z decomposition, H₀ correction |
| CQ18e | Zone 10-12: redshift gradient ladder |
| CQ18f | Zone 12: Great Attractor dissolution |
| CQ18g | Zone 12: perpendicular ring null-test |
| CQ18h | Zone 12: cone-shell velocity map |
| GD02 | Zone 8-10: MW directional z_grav occlusion map |
| CQ19b | Zone 7-9: nuclear shells, bar-arm junctions |
| CQ19c | Zone 7-10: 100-ring enrichable star catalogue |
| CQ19d | Zone 10: baryon census, Ϟ_kinematic vs Ϟ_luminous |
| CQ19e | Zone 10: spiral arm self-lensing correction |

---

## 8. EXECUTION SEQUENCE

1. Build Zone 1-3 (subatomic) from laws.hpp constants and PPT07 results
2. Build Zone 4-5 (stellar) from CQ18a/b and laws.hpp bridge
3. Build Zone 6 (ISM) from density models
4. Build Zone 7-8 (nucleus/bulge) from CQ19b S-star data
5. Build Zone 9 (bonding) from CQ19b junction data — this is the critical new computation
6. Build Zone 10-11 (disk/halo) from CQ19d rotation curve and CQ19e arm model
7. Build Zone 12 (intergalactic) from CR01 unified data
8. Trace z(r) continuously across all zones
9. Verify all five proof conditions
10. Produce the verdict: does one lattice, one topology, one closure govern all 37 orders of magnitude?

**The spation lattice is the driver. zk² = 1. Map it.**
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GD03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: galactic.hpp, GD01 eclipse saturation
- Phase thresholds (committed before run): 0.002%, 1%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GD03 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
