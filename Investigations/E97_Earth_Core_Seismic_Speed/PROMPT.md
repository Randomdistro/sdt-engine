# E97: Earth Core Seismic Speed from Lattice Compression — Investigation Prompt

> **Classification**: Archival data analysis + SDT derivation
> **Experiment file**: Experiments/E97_Earth_Core_Seismic_Speed_from_Lattice_Compression.md
> **Engine dependencies**: laws.hpp (Law I: P_conv, Law III: f, Law IV: V_disp), magnetosphere.hpp (k_Earth, Earth constants)
> **Archival sources**: PREM (Dziewonski & Anderson 1981), ak135 (Kennett 1995), ISC travel-time catalogue
> **Constitutional constraints**: Theory/00_Ruleset.md — No G, No M, No GM, No QM

---

## 1. Objective

Derive the seismic P-wave velocity profile v_p(r) inside Earth from the SDT
convergence-field compression gradient. The derivation must use ONLY SDT
quantities (P_conv, f, k, ℓ_P, V_disp) and the measured PREM density profile
ρ(r). No bulk modulus or shear modulus from material science may be invoked as
inputs — they must EMERGE from the convergence gradient if SDT is correct.

The measured PREM profile (v_p from 5.8 km/s at the surface to 13.7 km/s at
the CMB mantle-side, dropping to 8.1 km/s in the liquid outer core, rising
again to 11.3 km/s at the centre) must be reproduced or else the discrepancy
must be precisely quantified.

---

## 2. Background

### 2.1 Standard Physics

Standard seismology derives wave speeds entirely from material properties:

$$v_p = \sqrt{\frac{K + \frac{4}{3}G}{\rho}} \qquad v_s = \sqrt{\frac{G}{\rho}}$$

Where K is the bulk modulus (incompressibility), G is the shear modulus
(rigidity), and ρ is the density. These are measured in high-pressure
laboratory experiments (diamond anvil cells, shock compression) on candidate
mantle and core minerals.

The approach works remarkably well — PREM matches observed travel times to
within ~0.5 seconds over paths of 1000+ seconds. The question is whether SDT
can DERIVE K(r) and G(r) from first principles rather than measuring them.

### 2.2 SDT Interpretation

In SDT, the spation lattice is the medium through which ALL waves propagate.
Seismic waves are NOT vibrations of "atoms connected by bonds" — they are
low-frequency lattice disturbances propagating through the same medium that
carries light, but modulated by the local matter distribution.

The convergence gradient compresses the lattice toward Earth's centre:
- At the surface: lattice is at background pressure P_surf
- At depth r: the convergence from all overlying matter compresses the lattice
- At the centre: maximum lattice compression → maximum local relay speed

The seismic wave speed should therefore depend on TWO quantities:
1. The local lattice compression (from convergence gradient) → sets the "stiffness"
2. The local matter density ρ(r) → sets the inertia

The wave speed is then:

$$v_p(r) = \sqrt{\frac{P_{\text{lattice}}(r)}{\rho(r)}}$$

where P_lattice(r) is the effective lattice stiffness at radius r, set by
the convergence gradient.

---

## 3. Derivation

### Step 1: Convergence pressure profile inside Earth

Earth's convergence gradient creates a radially varying convergence pressure.
At the surface, the convergence from the entire planet produces the
gravitational acceleration g ≈ 9.81 m/s². At depth, the convergence from
the overlying shell is balanced by the convergence from the core below.

The SDT convergence pressure at radius r (distance from centre):

$$P_{\text{conv}}(r) = \frac{4\pi f P_{\text{conv,cosmo}}}{3} \int_0^r \rho(r') \, r'^2 \, dr' \times \frac{1}{r^2}$$

This is the SDT analog of the gravitational potential integral. The
difference from Newton: the prefactor uses f × P_conv (SDT coupling)
instead of G (gravitational constant).

Actually, since GM_equiv = c²R/k² (bridge law):

$$g(r) = \frac{c^2 R_E}{k^2 r^2} \times \frac{M(\le r)}{M_E}$$

The enclosed-mass correction ensures g(r) is correct at all depths.
This gives us the local gravitational acceleration profile g(r), which
we can integrate to get the pressure:

$$P(r) = \int_r^{R_E} \rho(r') \, g(r') \, dr'$$

### Step 2: Lattice compression from convergence pressure

The spation lattice spacing at depth is altered by the local convergence
pressure. Define the lattice compression ratio:

$$\eta(r) = \frac{\ell_s(r)}{\ell_P} = 1 - \frac{P_{\text{local}}(r)}{P_{\text{conv,cosmo}}}$$

Since P_local << P_conv,cosmo (363 GPa << 2.459×10⁴⁸ Pa), η ≈ 1 to
extraordinary precision. The fractional compression is:

$$\delta\eta = \frac{P_{\text{local}}}{P_{\text{conv}}} \approx \frac{364 \times 10^9}{2.459 \times 10^{48}} \approx 1.48 \times 10^{-37}$$

This is INFINITESIMAL. Direct lattice compression cannot explain the
seismic velocity profile — the spation lattice is effectively rigid on
these pressure scales.

### Step 3: Alternative SDT mechanism — effective bulk modulus from occlusion geometry

If lattice compression is negligible, the seismic velocity must come from
the MATTER's response to pressure, mediated through the convergence field.

The SDT-derived bulk modulus K(r) is:

$$K_{\text{SDT}}(r) = \frac{\pi}{4} P_{\text{eff}} \times n(r)^{2/3} \times R_p^2 \times R_n^2 / d(r)^2$$

where:
- n(r) = number density of nucleons at depth r (from ρ(r) and mean atomic mass)
- d(r) = mean internuclear spacing ≈ n^(-1/3)
- R_p, R_n = wake radii of constituent nucleons
- P_eff = effective pressure at nuclear scale (law_III)

This gives K as the cumulative occlusion stiffness of the material — how
much convergence pressure is needed to compress the internuclear spacing
by a fractional amount.

### Step 4: Compute v_p(r) from SDT

$$v_p(r) = \sqrt{\frac{K_{\text{SDT}}(r)}{\rho(r)}}$$

Tabulate this at every depth point in the PREM model and compare to
the measured v_p(r).

### Step 5: Phase transitions

The 410 km and 670 km discontinuities show abrupt v_p jumps. In SDT,
these arise when the convergence pressure crosses a threshold that causes
a structural rearrangement of the scaffold (crystal structure change =
grammar transition at the mineral scale).

Compute: at what pressures do the discontinuities occur? Are these related
to simple ratios of P_eff or the occlusion force thresholds for common
minerals?

- 410 km (P ≈ 13.4 GPa): olivine → wadsleyite (coordination change)
- 670 km (P ≈ 23.8 GPa): ringwoodite → bridgmanite (major restructuring)
- 2891 km (P ≈ 136 GPa): CMB — solid → liquid iron interface

### Step 6: The outer core S=0 constraint

S-waves (shear) have v_s = 0 in the outer core because it is liquid (G=0).
SDT must explain: why does G → 0 in the outer core? In SDT, shear rigidity
requires a FIXED scaffold structure. A liquid has no scaffold — the
constituent topologies (iron nuclei) are free to translate and rotate.
v_s = 0 because the ℓ≥3 wake bonds are broken (internuclear distance
exceeds the occlusion lock distance).

### Step 7: Inner core anisotropy

The inner core has v_p ~3% faster along the polar axis than in the
equatorial plane. Standard explanation: preferred crystal alignment of
hcp-iron from solidification conditions.

SDT offers an additional mechanism: Earth's ℓ=2 quadrupole wake (magnetic
field) provides a preferred axis. If the convergence gradient has an
axial component from the core's toroidal circulation, the lattice
compression would be slightly anisotropic → v_p(polar) > v_p(equatorial).

Compute: does the magnetic dipole field's energy density (B²/2μ₀ ~ 
10⁻² Pa at the ICB) produce a detectable anisotropy? It's ~10⁻¹³ of
the local pressure → probably too small. The anisotropy is more likely
structural (crystal alignment), which SDT can address through grammar-
based crystal packing preferences.

---

## 4. The Calculation (Numerical Procedure)

1. **Input**: PREM ρ(r) at 50 radial points, logarithmically spaced from
   r = 0 to r = R_E

2. **For each radius r**:
   a. Compute enclosed mass M(≤r) from density integral
   b. Compute g(r) = c²R_E/(k² r²) × M(≤r)/M_E
   c. Compute hydrostatic pressure P(r) from surface integral of ρg
   d. Compute number density n(r) = ρ(r) / ⟨A⟩ m_u (where ⟨A⟩ is mean
      atomic mass: 22 for mantle silicates, 56 for core iron)
   e. Compute mean interatomic spacing d(r) = n(r)^(-1/3)
   f. Compute K_SDT(r) = occlusion stiffness from the nuclear-scale
      occlusion force integrated over the local crystal structure
   g. For solids: compute G_SDT(r) = shear resistance from directed
      occlusion bonds (subset of K_SDT based on scaffold geometry)
   h. Compute v_p(r) = √((K_SDT + 4G_SDT/3) / ρ)
   i. Compute v_s(r) = √(G_SDT / ρ) (= 0 in liquid regions)

3. **Output**: v_p(r) and v_s(r) profiles from SDT, plotted alongside
   PREM reference profiles

4. **Residual**: Δv(r) = v_p,SDT(r) − v_p,PREM(r) at each depth

---

## 5. Required Outputs

1. **SDT seismic velocity profile**: v_p(r) and v_s(r) from surface to centre,
   plotted as a function of depth alongside PREM data

2. **Bulk modulus profile**: K_SDT(r) vs K_PREM(r) — does SDT derive the
   correct stiffness at each depth?

3. **Phase transition pressures**: Do the 410 km and 670 km discontinuities
   fall at SDT-predicted convergence thresholds?

4. **Outer core G=0**: Explicit demonstration that the outer core's liquid
   state corresponds to broken scaffold bonds in SDT

5. **Inner core anisotropy**: Quantification of the convergence anisotropy
   contribution vs crystal alignment contribution

6. **Residual map**: Depth-by-depth comparison with RMS deviation

7. **Travel time verification**: Compute P-wave travel times for standard
   ray paths (PKP, PKIKP, PcP) using the SDT velocity profile and compare
   to ISC catalogue travel times

---

## 6. Success Criteria

- [ ] SDT v_p profile matches PREM to within 5% RMS across all depths
- [ ] Surface v_p (5.8 km/s), CMB v_p (13.7/8.1 km/s), and centre v_p
      (11.3 km/s) all reproduced within 10%
- [ ] Phase transitions at 410/670 km correspond to SDT convergence thresholds
- [ ] v_s = 0 in outer core derived from scaffold-breaking criterion
- [ ] PKP travel times match ISC observations within 2 seconds over 1000+ km paths
- [ ] NO material-science bulk modulus used as input — all stiffness derived
      from occlusion force at nuclear scale
- [ ] If residuals exceed 10% anywhere: the discrepancy is localised and
      attributed to a specific SDT limitation

---

## 7. Falsification Conditions

- If SDT cannot match the PREM profile to within 30% at any depth after
  honest calculation: the lattice compression model needs fundamental
  revision for macroscopic wave propagation
- If the phase transition pressures show no correlation with SDT thresholds:
  seismic discontinuities are purely material phenomena with no lattice
  coupling
- If SDT predicts G > 0 in the outer core: the scaffold-breaking criterion
  is wrong
