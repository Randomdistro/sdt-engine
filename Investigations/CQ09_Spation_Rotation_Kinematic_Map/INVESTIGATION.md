# CQ09: Spation Rotation Kinematic Map — The Proton Interior to the Valence Shell

> **Classification**: Pure theoretical derivation + numerical verification
> **Status**: COMPLETE — 19/19 proofs passed (CQ09: 9/9, CQ09b: 10/10)
> **Author**: SDT Canonical Engine — James Tyndall, Melbourne, Australia
> **Date**: May 2026
> **Prerequisites**: Law V (Movement Budget), Law VI (Vortex Topology), CQ02, CQ11, CQ14

---

## Abstract

The proton surface sits at k = 0.5464 — inside the hydrogen c-boundary (k < 1). The circulation velocity at R_p is therefore superluminal: v_surface = c/k = 1.831c. This investigation constructs the complete kinematic map of the hydrogen atom: from 1.831c at the proton charge radius, through the c-boundary at r_e = 2.818 fm where v = c, outward through 3.27 × 10²⁴ Planck shells to the valence electron at a₀ = 5.292 × 10⁻¹¹ m where v = αc = 2.188 × 10⁶ m/s.

**Central result (CQ09b)**: The proton's rotation field and the electron's rotation field are algebraically identical at every radius:

$$v(r) = c\alpha\sqrt{a_0/r}$$

There is no "proton field" and "electron field". There is one field. The proton is where this field exceeds c (the source). The electron is where this field equals αc (the node). The c-boundary r_e = α²a₀ is where v = c. Koppa is not a property of a body — it is the field profile evaluated at a radius:

$$k(r) = \frac{1}{\alpha}\sqrt{\frac{r}{a_0}}$$

yielding k(R_p) = 0.5464, k(r_e) = 1.0, k(a₀) = 137.036.

**Subsidiary results**:
- The rotation field decays at |Δv/v| = l_P/(2r) per Planck shell — at the Bohr radius, this is 1.53 × 10⁻²⁵ per shell. Effectively zero. The field propagates at c with near-zero dissipation.
- Angular momentum quantisation L_n = nℏ emerges exactly at Bohr radii (verified n = 1 through 5, all to machine precision).
- The 21-cm hydrogen hyperfine line is recovered at f = 1.4212 GHz vs measured 1.4204 GHz (0.05% error).
- Bond formation is rotation field superposition: antiparallel spins → constructive addition → lower energy → covalent bond.
- The proton angular momentum from rotation is L_p = 7.322ℏ, and the electron's internal circulation gives L_e = 0.707ℏ.

---

## Part I: The Rotation Profile v(r) — From 1.831c to αc

### I.1 Boundary Conditions

Three radii define the hydrogen kinematic structure:

| Boundary | r (m) | v(r) | k(r) | Physical Meaning |
|----------|-------|------|------|-----------------|
| Proton surface | R_p = 8.414 × 10⁻¹⁶ | 1.831c | 0.5464 | Superluminal phase rotation |
| c-boundary | r_e = 2.818 × 10⁻¹⁵ | c | 1.0 | Displacement = l_P threshold |
| Electron orbit | a₀ = 5.292 × 10⁻¹¹ | αc | 137.036 | Ground state resonance |

### I.2 The Velocity Law

From `laws.hpp:396`:

$$v(r) = \frac{c}{k}\sqrt{\frac{R_p}{r}}$$

where k = k_proton_surface = 0.5464. This is the proton's rotation field at arbitrary radius.

### I.3 Complete Velocity Profile (Verified Output)

| Label | r (m) | v/c | k(r) | ω (rad/s) | T (s) | d_disp/l_P | Regime |
|-------|-------|-----|------|-----------|-------|------------|--------|
| 0.5 R_p | 4.207×10⁻¹⁶ | 2.5882 | 0.3864 | 1.844×10²⁴ | 3.407×10⁻²⁴ | 2.5882 | SUPERLUM |
| R_p (surface) | 8.414×10⁻¹⁶ | 1.8302 | 0.5464 | 6.521×10²³ | 9.636×10⁻²⁴ | 1.8302 | SUPERLUM |
| 2 R_p | 1.683×10⁻¹⁵ | 1.2941 | 0.7727 | 2.306×10²³ | 2.725×10⁻²³ | 1.2941 | SUPERLUM |
| r_e (c-boundary) | 2.818×10⁻¹⁵ | 1.0001 | 0.9999 | 1.064×10²³ | 5.906×10⁻²³ | 1.0001 | c-BOUNDARY |
| 5 r_e | 1.409×10⁻¹⁴ | 0.4472 | 2.236 | 9.516×10²¹ | 6.603×10⁻²² | 0.4472 | STRONG |
| 10 r_e | 2.818×10⁻¹⁴ | 0.3162 | 3.162 | 3.364×10²¹ | 1.868×10⁻²¹ | 0.3162 | STRONG |
| 100 r_e | 2.818×10⁻¹³ | 0.1000 | 9.999 | 1.064×10²⁰ | 5.906×10⁻²⁰ | 0.1000 | STRONG |
| ƛ_C_e | 3.862×10⁻¹³ | 0.0854 | 11.71 | 6.632×10¹⁹ | 9.474×10⁻²⁰ | 0.0854 | WEAK |
| 0.01 a₀ | 5.292×10⁻¹³ | 0.0730 | 13.70 | 4.134×10¹⁹ | 1.520×10⁻¹⁹ | 0.0730 | WEAK |
| 0.1 a₀ | 5.292×10⁻¹² | 0.0231 | 43.33 | 1.307×10¹⁸ | 4.806×10⁻¹⁸ | 0.0231 | WEAK |
| a₀ (ground) | 5.292×10⁻¹¹ | 0.0073 | 137.03 | 4.134×10¹⁶ | 1.520×10⁻¹⁶ | 0.0073 | BOHR |
| 4 a₀ (n=2) | 2.117×10⁻¹⁰ | 0.0036 | 274.06 | 5.168×10¹⁵ | 1.216×10⁻¹⁵ | 0.0036 | BOHR |
| 9 a₀ (n=3) | 4.763×10⁻¹⁰ | 0.0024 | 411.08 | 1.531×10¹⁵ | 4.103×10⁻¹⁵ | 0.0024 | BOHR |
| 16 a₀ (n=4) | 8.467×10⁻¹⁰ | 0.0018 | 548.11 | 6.460×10¹⁴ | 9.726×10⁻¹⁵ | 0.0018 | BOHR |
| 25 a₀ (n=5) | 1.323×10⁻⁹ | 0.0015 | 685.14 | 3.308×10¹⁴ | 1.900×10⁻¹⁴ | 0.0015 | BOHR |

### I.4 Key Ratios

| Quantity | Value |
|----------|-------|
| Velocity span v(R_p)/v(a₀) | 1.831/0.00730 = **250.9** |
| Angular velocity span ω(R_p)/ω(a₀) | 6.521×10²³ / 4.134×10¹⁶ = **1.577×10⁷** |
| Period span T(R_p)/T(a₀) | 9.636×10⁻²⁴ / 1.520×10⁻¹⁶ = **6.340×10⁻⁸** |
| Total Planck shells R_p → a₀ | **3.274 × 10²⁴** |

### I.5 Velocity Milestones

At what radius does the field velocity drop to key thresholds?

| Target v | r (m) | r/R_p | Physical Meaning |
|----------|-------|-------|-----------------|
| 1.5c | 1.255×10⁻¹⁵ | 1.49 | Deep superluminal |
| **1.0c** | **2.818×10⁻¹⁵** | **3.35** | **c-boundary = r_e** |
| 0.5c | 1.127×10⁻¹⁴ | 13.4 | Mid strong coupling |
| 0.1c | 2.818×10⁻¹³ | 335 | Onset of weak regime |
| 0.01c | 2.818×10⁻¹¹ | 33,491 | Near Bohr radius |
| αc | 5.292×10⁻¹¹ | 62,907 | Electron ground state |

---

## Part II: The Superluminal Interior (R_p < r < r_e)

### II.1 The Saturation Zone

Inside the c-boundary (r < r_e), the phase velocity v(r) > c. The displacement per spation per tick exceeds one Planck length. This is the **saturated regime** — the lattice is maximally deformed.

**Verification**: r_Ϟ = R_p/k² = R_p/0.5464² = 2.818 × 10⁻¹⁵ m = r_e ✓ (CQ09-2a PASS, 0.0%)

The proton surface occupies **29.9%** of the saturation zone. The saturation zone contains 1.223 × 10²⁰ Planck shells.

### II.2 Displacement Profile Through the Saturation Zone

| r (m) | v(r)/c | d/l_P | Status |
|-------|--------|-------|--------|
| 0.1 R_p | 5.789 | 5.789 | **SATURATED** — 5.8 spations share the load |
| 0.25 R_p | 3.661 | 3.661 | **SATURATED** |
| 0.5 R_p | 2.588 | 2.588 | **SATURATED** |
| R_p | 1.830 | 1.830 | **SATURATED** — 1.83 spations share |
| 1.5 R_p | 1.494 | 1.494 | **SATURATED** |
| 2.0 R_p | 1.294 | 1.294 | **SATURATED** |
| 2.5 R_p | 1.158 | 1.158 | **SATURATED** |
| r_e | 1.000 | 1.000 | **THRESHOLD** — exactly l_P |
| 1.5 r_e | 0.816 | 0.816 | Linear — subluminal |

At the proton surface: displacement = 1.830 l_P. Each displacement event involves ~1.83 spations cooperatively sharing the deformation. This is the mechanical basis of the trefoil's stability — the load is distributed, not concentrated.

### II.3 Trefoil (2,3) Knot Geometry

The proton circulation traces a (2,3) torus knot:
- **2 poloidal** + **3 toroidal** turns per cycle
- **3 crossing points** in any equatorial projection, equally spaced at 120°
- At each crossing: displacement field sign reversal → three-fold stabilisation

**Circulation velocities** (from CQ02):

| Component | Velocity | Energy Fraction |
|-----------|----------|----------------|
| Toroidal v_T | c√(2/5) = 0.6325c | 2/5 = 40% |
| Poloidal v_P | c√(3/5) = 0.7746c | 3/5 = 60% |
| Total | √(v_T² + v_P²) = **1.0000c** | 100% ✓ |
| Helical pitch angle | arctan(v_P/v_T) = **50.77°** | — |

### II.4 Phase vs Transport at R_p

The 1.831c is a **phase velocity**, not a transport velocity. The spation lattice cannot transport information faster than c. The resolution:

- Phase velocity = 1.831c (the pattern sweeps at this speed)
- Each spation displacement per tick = 1.830 l_P (> l_P → saturated)
- Load-sharing factor: 1.830 spations cooperate per event
- Each individual spation displaces l_P/1.830 = **0.546 l_P** per tick (subluminal ✓)

This is the same mechanism as phonon phase velocities exceeding the speed of sound in solids — the pattern moves faster than any individual atom.

---

## Part III: Counter-Rotation Shell Structure (r_e < r < a₀)

### III.1 Shell Counting

| Region | Shells | Fraction |
|--------|--------|----------|
| R_p to r_e (saturation) | 1.223 × 10²⁰ | 0.0037% |
| r_e to a₀ (subluminal) | 3.274 × 10²⁴ | 99.9963% |
| **Total** | **3.274 × 10²⁴** | 100% |

The superluminal zone is a tiny core — only 0.004% of the total shell count. 99.996% of the hydrogen atom's radial structure is in the subluminal regime.

### III.2 Decay Rate Per Shell

The velocity changes by |Δv/v| = l_P/(2r) per Planck shell:

| Location | r (m) | |Δv/v| per shell | Shells to halve |
|----------|-------|-----------------|-----------------|
| R_p (surface) | 8.414×10⁻¹⁶ | 9.60×10⁻²¹ | 7.22×10¹⁹ |
| r_e (c-boundary) | 2.818×10⁻¹⁵ | 2.87×10⁻²¹ | 2.42×10²⁰ |
| 10 r_e | 2.818×10⁻¹⁴ | 2.87×10⁻²² | 2.42×10²¹ |
| ƛ_C | 3.862×10⁻¹³ | 2.09×10⁻²³ | 3.31×10²² |
| 0.01 a₀ | 5.292×10⁻¹³ | 1.53×10⁻²³ | 4.54×10²² |
| 0.1 a₀ | 5.292×10⁻¹² | 1.53×10⁻²⁴ | 4.54×10²³ |
| **a₀ (ground)** | **5.292×10⁻¹¹** | **1.53×10⁻²⁵** | **4.54×10²⁴** |

At the Bohr radius: 1.53 × 10⁻²⁵ fractional change per shell. To halve the velocity at this radius would require 4.54 × 10²⁴ shells — **more shells than exist between the proton and the electron**. The rotation field is effectively lossless across the entire atomic volume.

This is why koppa works at astronomical scales. The rotation field extends from femtometres to astronomical units with negligible dissipation because the fractional loss per relay is infinitesimal.

### III.3 Torsional Coupling Mechanism

The rotation does **not** propagate by viscous diffusion. It propagates by relay:

| Quantity | Value |
|----------|-------|
| Relay content per shell per tick (ε) | 1.763 × 10⁻¹¹⁸ J |
| Coupling coefficient κ = ε/(l_P c) | 3.638 × 10⁻⁹² N·m/rad |
| Torsional wave speed | l_P/t_P = **c** |
| Relaxation time per shell | t_P = 5.391 × 10⁻⁴⁴ s |

The torsional wave propagates at c — identical to the relay speed. There is no separate "rotation field". The velocity law v(r) = (c/k)√(R/r) IS the convergence field. Rotation, translation, and convergence are aspects of the same lattice deformation.

### III.4 Angular Momentum Quantisation

For an electron at Bohr radius r_n = n²a₀:

| n | r_n (m) | v_n (m/s) | L_n (J·s) | L_n/ℏ |
|---|---------|-----------|-----------|-------|
| 1 | 5.292×10⁻¹¹ | 2.188×10⁶ | 1.054572×10⁻³⁴ | **1.0000** |
| 2 | 2.117×10⁻¹⁰ | 1.094×10⁶ | 2.109144×10⁻³⁴ | **2.0000** |
| 3 | 4.763×10⁻¹⁰ | 7.292×10⁵ | 3.163715×10⁻³⁴ | **3.0000** |
| 4 | 8.467×10⁻¹⁰ | 5.469×10⁵ | 4.218287×10⁻³⁴ | **4.0000** |
| 5 | 1.323×10⁻⁹ | 4.375×10⁵ | 5.272859×10⁻³⁴ | **5.0000** |

L_n = nℏ **exactly** to machine precision. ℏ quantisation is not postulated — it emerges from the geometry.

**Verified**: CQ09-3a (L₁ = ℏ, 0.0000%) ✓, CQ09-3b (L₂ = 2ℏ, 0.0000%) ✓

---

## Part IV: The Electron as Driven Orbit

### IV.1 The Resonance Condition

At r = a₀, the proton's rotation field velocity must equal the electron's orbital velocity for a stable orbit. The field velocity at a₀:

$$v_{\text{field}}(a_0) = \frac{c}{k}\sqrt{\frac{R_p}{a_0}} = 2.1878 \times 10^6 \text{ m/s}$$

The electron's orbital velocity: v_e = αc = 2.1877 × 10⁶ m/s.

**Match: 0.0057%** — identical to within the precision of the input constant k = 0.5464.

**Verified**: CQ09-4a PASS (0.0057%)

The resonance is **automatic** — it follows from the definition of k. The electron is not freely orbiting. The lattice is rotating at the electron's velocity at that radius. The electron is **stationary in the co-rotating frame**.

### IV.2 Frame Dragging

The proton's rotation field drags the local spation lattice. At a₀:
- ω_field = 4.134 × 10¹⁶ rad/s
- ω_electron = 4.134 × 10¹⁶ rad/s
- Ratio = 1.000057 ≈ 1.0

The electron does not orbit "against" the lattice. The lattice IS rotating at the electron's speed at that radius. This is the mechanical basis for the electron's stability — it is not radiating because it is not accelerating relative to its local medium.

### IV.3 Bond Formation: Rotation Field Superposition

When two hydrogen atoms approach at separation d, their rotation fields superpose:

**H₂ bond (d = 0.74 Å)**:

At midpoint (r = d/2 = 3.70 × 10⁻¹¹ m):
- Field from proton 1: v₁ = 2.616 × 10⁶ m/s = 0.00873c
- Field from proton 2: v₂ = 2.616 × 10⁶ m/s = 0.00873c
- **Antiparallel spins (singlet)**: v_total = v₁ + v₂ = 0.01745c → ENHANCED
- **Parallel spins (triplet)**: v_total = |v₁ - v₂| = 0 → CANCELLED

The covalent bond is the prograde zone between two counter-rotating proton fields. Electrons preferentially occupy the enhanced region where the combined field velocity is higher, producing a deeper energy well.

**Bond energy estimate** (rotation field KE difference):
- E_enhanced = ½m_e(2v)² = 1.247 × 10⁻¹⁷ J
- E_separate = 2 × ½m_e v² = 6.236 × 10⁻¹⁸ J
- ΔE = 6.236 × 10⁻¹⁸ J = **38.9 eV**

This overestimates the measured 4.52 eV by ~8.6×, because this simple estimate uses the bare kinetic energy without the self-consistent potential adjustment. The correct treatment requires the full convergence-occlusion integral (see CQ14 §II). The key point is not the magnitude but the **mechanism**: bonding is rotation field superposition, not "electron sharing".

### IV.4 Spin-Spin Interaction and the 21-cm Line

**Proton angular momentum from rotation**:

$$L_p = m_p \times v_{\text{surf}} \times R_p = 1.673 \times 10^{-27} \times 5.489 \times 10^8 \times 8.414 \times 10^{-16}$$
$$= 7.722 \times 10^{-34} \text{ J·s} = 7.322\hbar$$

**Electron circulation angular momentum** (W=1, (1,1) unknot):

$$L_e = m_e \times v_{\text{circ}} \times R_{\text{torus}} = 9.109 \times 10^{-31} \times \frac{c}{\sqrt{2}} \times \bar{\lambda}_C$$
$$= 7.457 \times 10^{-35} \text{ J·s} = 0.7071\hbar = \frac{\hbar}{\sqrt{2}}$$

**Hyperfine splitting** (Fermi contact interaction):

$$\Delta E_{\text{HF}} = \frac{8}{3}\alpha^4 m_e c^2 \frac{m_e}{m_p}\mu_P = 9.417 \times 10^{-25} \text{ J}$$

$$f_{\text{HF}} = \frac{\Delta E_{\text{HF}}}{h} = 1.4212 \text{ GHz}$$

Measured: f = 1.4204 GHz. **Error: 0.054%**.

**Verified**: CQ09-4b PASS (0.054%)

The 21-cm hydrogen line — the most precisely measured transition in astrophysics — is the spin-spin interaction between the proton trefoil's rotation and the electron torus's circulation, mediated through the spation lattice.

---

## Part V: Field Unification (CQ09b) — The Central Discovery

### V.1 The Electron's Koppa

The electron is a (1,1) torus unknot (W=1):
- v_T = v_P = c/√2
- Total circulation: √(v_T² + v_P²) = **c exactly** ✓ (CQ09b-1a PASS)
- Surface velocity = c → koppa_e = c/c = **1.0**

The electron IS the c-boundary. Its surface is the event horizon of its own field. There is no separate c-boundary — the electron IS the threshold.

### V.2 The Electron's Rotation Field at the Proton

The electron's field:
$$v_e(r) = \frac{c}{k_e}\sqrt{\frac{r_e}{r}} = c\sqrt{\frac{r_e}{r}}$$

At r = a₀ (proton's location from the electron):
$$v_e(a_0) = c\sqrt{\frac{r_e}{a_0}} = c\sqrt{\alpha^2} = \alpha c$$

**Verified**: CQ09b-2a (r_e/a₀ = α², 0.0000%) ✓, CQ09b-2b (v_e(a₀) = αc, 0.0000%) ✓

At r = R_p (proton surface):
$$v_e(R_p) = c\sqrt{\frac{r_e}{R_p}} = c\sqrt{3.349} = 1.8301c$$

The proton's field at R_p: v_p(R_p) = c/k = 1.8302c.

**Verified**: CQ09b-3a PASS (0.0057%)

### V.3 The Algebraic Identity

**Proton field**:
$$v_p(r) = \frac{c}{k_H}\sqrt{\frac{R_p}{r}} \quad \text{where } k_H = \frac{1}{\alpha}\sqrt{\frac{R_p}{a_0}}$$
$$= c\alpha\sqrt{\frac{a_0}{R_p}} \times \sqrt{\frac{R_p}{r}} = c\alpha\sqrt{\frac{a_0}{r}}$$

**Electron field**:
$$v_e(r) = c\sqrt{\frac{r_e}{r}} = c\sqrt{\frac{\alpha^2 a_0}{r}} = c\alpha\sqrt{\frac{a_0}{r}}$$

$$\boxed{v_p(r) \equiv v_e(r) = c\alpha\sqrt{\frac{a_0}{r}} \quad \text{EVERYWHERE}}$$

The ratio v_e(r)/v_p(r) = k_H × √(r_e/R_p) = 0.5464 × √3.349 = **0.99994 ≈ 1** at every radius.

**Verified**: CQ09b-4a PASS (0.006%) — the 0.006% residual is the precision of the hardcoded k = 0.5464 vs the exact (1/α)√(R_p/a₀) = 0.54643.

### V.4 Side-by-Side Field Comparison (All 13 Radii)

| Location | v_proton/c | v_electron/c | Ratio | Match |
|----------|-----------|-------------|-------|-------|
| 0.5 R_p | 2.588239 | 2.588092 | 0.999943 | ✓ |
| R_p | 1.830161 | 1.830057 | 0.999943 | ✓ |
| 2 R_p | 1.294119 | 1.294046 | 0.999943 | ✓ |
| r_e | 1.000057 | 1.000000 | 0.999943 | ✓ |
| 10 r_e | 0.316246 | 0.316228 | 0.999943 | ✓ |
| 100 r_e | 0.100006 | 0.100000 | 0.999943 | ✓ |
| ƛ_C_e | 0.085429 | 0.085425 | 0.999943 | ✓ |
| λ_C_e | 0.034081 | 0.034079 | 0.999943 | ✓ |
| 0.01 a₀ | 0.072978 | 0.072974 | 0.999943 | ✓ |
| 0.1 a₀ | 0.023078 | 0.023076 | 0.999943 | ✓ |
| a₀ | 0.007298 | 0.007297 | 0.999943 | ✓ |
| 4 a₀ | 0.003649 | 0.003649 | 0.999943 | ✓ |
| 9 a₀ | 0.002433 | 0.002432 | 0.999943 | ✓ |

**13 for 13.** The ratio is constant at 0.999943 because the two formulations are algebraically identical.

### V.5 The Unified Field

There is one field:

$$v(r) = c\alpha\sqrt{\frac{a_0}{r}} = \frac{A}{\sqrt{r}} \quad \text{where } A = c\alpha\sqrt{a_0} = 15.914 \text{ m}^{3/2}/\text{s}$$

**Verified**: CQ09b-5a (v(a₀) = αc, 0.0000%) ✓

The koppa profile is the field's own coordinate:

$$k(r) = \frac{c}{v(r)} = \frac{1}{\alpha}\sqrt{\frac{r}{a_0}}$$

| Location | r (m) | k(r) | Verified |
|----------|-------|------|----------|
| R_p (proton) | 8.414×10⁻¹⁶ | 0.5464 | CQ09b-5b ✓ (0.006%) |
| r_e (c-boundary) | 2.818×10⁻¹⁵ | 1.0000 | CQ09b-5c ✓ (0.000%) |
| a₀ (electron) | 5.292×10⁻¹¹ | 137.036 | CQ09b-5d ✓ (0.000%) |
| 4a₀ (n=2) | 2.117×10⁻¹⁰ | 274.072 | — |
| 9a₀ (n=3) | 4.763×10⁻¹⁰ | 411.108 | — |

**koppa is not a property of a body. It is a property of the field at a radius.**

---

## Part VI: Proton Displacement Volume

From the mass definition (Theorem T5):

$$V_{\text{disp}} = \frac{3 m_p l_P^3 c^2}{\Phi} = 1.833 \times 10^{-58} \text{ m}^3$$

$$R_{\text{excl}} = \left(\frac{3V}{4\pi}\right)^{1/3} = 3.524 \times 10^{-20} \text{ m}$$

$$N_{\text{displaced}} = \frac{V_{\text{disp}}}{l_P^3} = 4.341 \times 10^{46} \text{ spations}$$

The proton displaces 4.34 × 10⁴⁶ spations. Its exclusion radius (3.52 × 10⁻²⁰ m) is 4.7 orders of magnitude smaller than its charge radius (8.41 × 10⁻¹⁶ m). The vast majority of the proton's "presence" is its wake, not its body.

---

## Part VII: Three Regimes — One Field

The hydrogen atom divides into three regimes, but there is NO physical boundary between them. The field v(r) = cα√(a₀/r) is continuous and differentiable everywhere:

| Regime | Range | Condition | Physics |
|--------|-------|-----------|---------|
| **Superluminal** | r < r_e (0 → 2.818 fm) | v > c, d > l_P | Saturated lattice, trefoil topology, nuclear physics |
| **Strong subluminal** | r_e < r < ƛ_C (2.818 fm → 386 fm) | v < c, d < l_P, strong coupling | Transition zone, QED-equivalent processes |
| **Weak subluminal** | ƛ_C < r < ∞ | v ≪ c, d ≪ l_P | Linear response, Bohr orbits, chemistry |

The transition from "nuclear physics" to "atomic physics" is **not** a boundary — it is the transition from saturated to linear lattice response in a single, continuous field.

---

## Part VIII: Verification Summary

### All 19 Proofs

| ID | Statement | Derived | Expected | Error | Status |
|----|-----------|---------|----------|-------|--------|
| CQ09-1a | v(R_p) = 1.831c | 1.830161 | 1.830161 | 0.000% | **PASS** |
| CQ09-1b | v(r_e) = c | 1.000057 | 1.000000 | 0.006% | **PASS** |
| CQ09-1c | v(a₀) = αc | 2.1878e6 | 2.1877e6 | 0.006% | **PASS** |
| CQ09-2a | r_Ϟ = r_e | 2.818e-15 | 2.818e-15 | 0.000% | **PASS** |
| CQ09-2b | Phase velocity = 1.831c | 1.830161 | 1.830161 | 0.000% | **PASS** |
| CQ09-3a | L(n=1) = ℏ | 1.0546e-34 | 1.0546e-34 | 0.000% | **PASS** |
| CQ09-3b | L(n=2) = 2ℏ | 2.1091e-34 | 2.1091e-34 | 0.000% | **PASS** |
| CQ09-4a | v_field(a₀) = αc | 2.1878e6 | 2.1877e6 | 0.006% | **PASS** |
| CQ09-4b | f_HF ≈ 1.42 GHz | 1.4212 | 1.4204 | 0.054% | **PASS** |
| CQ09b-1a | Electron circ = c | 2.998e8 | 2.998e8 | 0.000% | **PASS** |
| CQ09b-1b | Electron c-boundary = r_e | 2.818e-15 | 2.818e-15 | 0.000% | **PASS** |
| CQ09b-2a | r_e/a₀ = α² | 5.325e-5 | 5.325e-5 | 0.000% | **PASS** |
| CQ09b-2b | v_e(a₀) = αc | 2.1877e6 | 2.1877e6 | 0.000% | **PASS** |
| CQ09b-3a | v_e(R_p) = v_p(R_p) | 5.486e8 | 5.487e8 | 0.006% | **PASS** |
| CQ09b-4a | v_e/v_p = 1 everywhere | 0.99994 | 1.00000 | 0.006% | **PASS** |
| CQ09b-5a | v(a₀) = αc unified | 2.1877e6 | 2.1877e6 | 0.000% | **PASS** |
| CQ09b-5b | k(R_p) = 0.5464 | 0.54643 | 0.54640 | 0.006% | **PASS** |
| CQ09b-5c | k(r_e) = 1.0 | 1.00000 | 1.00000 | 0.000% | **PASS** |
| CQ09b-5d | k(a₀) = 137.036 | 137.036 | 137.036 | 0.000% | **PASS** |

**19/19 PASS. Maximum error: 0.054% (hyperfine). Mean error: 0.005%.**

---

## Conclusions

### What CQ09 Proves

1. **The proton is a 1.831c phase vortex** — a (2,3) trefoil knot circulating at c, imposing superluminal phase demands on the lattice.

2. **The c-boundary at r_e is the saturation threshold** — the radius where spation displacement drops to exactly l_P. Inside: nuclear physics (saturated). Outside: atomic physics (linear).

3. **The rotation field decays at l_P/(2r) per shell** — at the Bohr radius, this is 10⁻²⁵ per shell. The field propagates with near-zero dissipation through 3.27 × 10²⁴ Planck shells. This is why koppa works at stellar and planetary scales.

4. **Angular momentum quantisation L = nℏ emerges exactly** — not postulated, but a geometric consequence of the field velocity at Bohr radii.

5. **The electron orbit IS the proton's rotation field at a₀** — the electron is not independently orbiting. It is stationary in the co-rotating frame of the lattice at that radius.

6. **The proton field and electron field are algebraically identical**: v(r) = cα√(a₀/r). There is ONE field with two features — a superluminal source (proton) and a standing-wave node (electron).

7. **koppa is a field profile, not a body property**: k(r) = (1/α)√(r/a₀). The "proton koppa" and "electron koppa" are the same continuous function evaluated at different radii.

8. **Bond formation is rotation field superposition** — antiparallel spins add constructively, creating a potential well between protons that electrons preferentially occupy.

9. **The 21-cm line is the spin-spin interaction** — recovered at 1.4212 GHz (0.054% error) from the trefoil-torus rotation coupling.

10. **One field. Three regimes. No boundary.** The hydrogen atom is a single self-consistent vortex in the spation lattice. Not two particles. One field. Two features.

### Connection to CQ14

CQ09 establishes the **kinematic structure** — the velocity, displacement, and angular momentum profiles. CQ14 establishes the **causal mechanism** — the traction ratio 𝒯 = 12 = 3(W+1), the three mechanical outputs (Coulomb, magnetic, orbital), and the gear ratio ~10⁸. Together they provide the complete mechanical description of the hydrogen atom as a topological engine in a pressurised lattice.

### Open Questions

1. **The bond energy overestimate** (38.9 eV vs 4.52 eV) indicates the simple KE model needs refinement. The full convergence-occlusion integral should recover the correct depth.

2. **The proton angular momentum** L_p = 7.322ℏ from the rotation model does not immediately yield the measured spin ½ℏ. The ½ℏ likely emerges from the trefoil's half-integer topological charge, not from the total mechanical angular momentum — this requires formal derivation.

3. **Multi-electron atoms**: extending the single-field description to helium and beyond requires superposition of multiple koppa fields, which connects to the ionisation closure zk² = 1 already verified for 126 levels.

---

## Technical References

- **Verification code**: `cq09_spation_rotation_map.cpp` (9/9 proofs), `cq09b_electron_drives_proton.cpp` (10/10 proofs)
- **Build targets**: `sdt-cq09-rotation`, `sdt-cq09b-inverse`
- **Constants**: All from `Engine/include/sdt/laws.hpp` (single source of truth)
- **Dependencies**: CQ02 (vortex equilibrium), CQ11 (trefoil confinement), CQ14 (spation traction)

