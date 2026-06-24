# PPT04: Neutrino Magnetic Moment — Formal SDT Investigation

> **Classification**: Pure theoretical derivation  
> **Status**: COMPLETE  
> **Author**: SDT Canonical Engine — James Tyndall, Melbourne, Australia  
> **Date**: May 2026  
> **Source reference**: `neutrino.hpp:9`, `Theory/01_Closure_Derivations.md:32`, `Theory/03_Open_Problems.md:41`

---

## Abstract

This investigation formally derives the SDT prediction that all neutrino flavours possess **exactly zero** magnetic moment (μ_ν ≡ 0). The proof proceeds from the wake tensor ℓ-expansion applied to the neutrino's W = 0 open-winding topology. We show that the vanishing of the ℓ = 1 (charge) and ℓ = 2 (magnetic dipole) wake components is not incidental but is a **topological necessity** — a direct consequence of the neutrino's failure to close into a persistent toroidal circulation. We compare the SDT prediction against the minimally-extended Standard Model prediction (μ_ν ≈ 3.2 × 10⁻²⁰ μ_B for m_ν = 0.1 eV), survey the full experimental landscape from GEMMA to XENONnT, and identify the precise sensitivity threshold required to discriminate between the two frameworks. The prediction is **falsifiable**: any confirmed non-zero neutrino magnetic moment at any scale would refute the W = 0 topological assignment.

---

## Part I: Theoretical Foundations

### I.1 The Wake Tensor and ℓ-Expansion

Every vortex topology in the spation lattice produces a convergence perturbation — a **wake** — in the surrounding medium. The wake field Φ(r, n̂) admits a spherical harmonic decomposition:

$$\Phi(\mathbf{r}, \hat{n}) = \sum_{\ell=0}^{\infty} \sum_{m=-\ell}^{\ell} \Phi_{\ell m}(r) \, Y_{\ell}^{m}(\hat{n})$$

Each multipole order ℓ corresponds to a distinct physical interaction (from `Theory/01_Closure_Derivations.md`):

| ℓ | Components | Symmetry | Physical Role | Radial Dependence |
|---|-----------|----------|---------------|-------------------|
| 0 | 1 (scalar) | Isotropic | Background convergence Nε — no net force | Constant |
| 1 | 3 (vector) | Dipolar | Pressure gradient → **Coulomb force** | ∝ 1/r² |
| 2 | 5 (traceless symmetric) | Quadrupolar | Organised circulation → **Magnetic dipole** | ∝ 1/r³ |
| ≥3 | 2ℓ+1 | Higher multipole | Nuclear form factors | ∝ 1/r^(ℓ+1) |

**Critical relationship**: The ℓ = 2 component (magnetic dipole) requires **organised toroidal flow** — a net circulation current around a closed loop. This is the mechanical origin of magnetism in SDT: a circulating charge traces a current loop, whose area and current determine the dipole moment.

### I.2 Vortex Topology Classification

SDT classifies all persistent lattice defects by their winding number W and genus g:

| Particle | g | W | Topology | Circulation | Wake Structure |
|----------|---|---|----------|-------------|----------------|
| **Electron** | 1 | 1 | Simple torus | Closed, single-loop | ℓ = 0,1,2,... all present |
| **Proton** | 1 | 3 | Trefoil knot | Closed, triple-loop | ℓ = 0,1,2,... all present |
| **Neutrino** | 0 | 0 | Open winding | **Open, non-closing** | **ℓ = 0 only** |
| **Photon** | — | — | Propagating mode | No circulation (v_circ = 0) | No wake |

The electron (W = 1) and proton (W = 3) are **closed topological defects** — their internal circulation traces a persistent loop that cannot be smoothly unwound. The neutrino (W → 0⁺) is an **open winding** — a helical perturbation that propagates through the lattice without ever closing on itself.

### I.3 The Three Circulation Modes

For a genus-1 torus (electron, proton), the movement budget partitions into three orthogonal circulation modes (from `CQ02_Vortex_Equilibrium_Quantisation/PROMPT.md`):

$$v_T^2 + v_P^2 + v_C^2 = c^2$$

Where:
- **v_T** = toroidal velocity (circulation around the major axis)
- **v_P** = poloidal velocity (circulation around the minor axis)  
- **v_C** = centre-of-mass translational velocity

For the **electron** (W = 1, at rest where v_C = 0):
- v_T ≈ c (dominant mode)
- v_P = α × v_T ≈ αc (subdominant, where α ≈ 1/137)
- The ratio v_P/v_T = α is the **fine structure constant** — a geometric property of the W = 1 torus

For the **neutrino** (W = 0, open winding):
- The winding never closes → **no toroidal circuit exists**
- v_T = 0 (no closed toroidal path to circulate around)
- v_P = 0 (no closed poloidal path exists without a torus)
- v_C ≈ c (nearly all budget allocated to translation)

This is why neutrinos travel at near-light speed: with no closed circulation modes to absorb the movement budget, almost all of c² goes to translation.

---

## Part II: The Core Proof — μ_ν ≡ 0

### II.1 Theorem Statement

> **Theorem (Neutrino Magnetic Moment Vanishing)**:
> Let ν be a lattice perturbation with winding number W = 0 (open winding topology). Then the ℓ = 2 component of its wake tensor vanishes identically:
>
> Φ₂ₘ(r) = 0 for all m ∈ {-2, -1, 0, 1, 2} and all r
>
> Consequently, the neutrino magnetic moment μ_ν = 0 exactly.

### II.2 Proof

The proof proceeds by showing that the ℓ = 2 wake component requires a **closed toroidal current**, which the W = 0 topology cannot support.

**Step 1: Magnetic moment from circulation current**

For any vortex with a closed circulation loop, the magnetic dipole moment is:

$$\mu = I \cdot A$$

where I is the effective current (charge × circulation frequency) and A is the area enclosed by the current loop. In SDT, for a torus of major radius R and minor radius a:

$$\mu = \frac{e \cdot v_T}{2\pi R} \cdot \pi R^2 = \frac{e \cdot v_T \cdot R}{2}$$

The ℓ = 2 wake amplitude is proportional to this moment:

$$\Phi_{2m} \propto \mu \propto v_T \cdot R$$

**Step 2: Open winding has no closed circuit**

For the neutrino (W = 0), the perturbation is an **open helix** — it propagates forward without closing. The defining property of W = 0:

$$\oint_{\gamma_T} d\phi = 0$$

where γ_T is any attempted toroidal circuit. There is no closed path around a major axis because **no major axis exists** — the topology is not toroidal. The perturbation has no genus-1 (or higher) structure.

Since v_T requires a closed toroidal path:

$$W = 0 \implies \text{no closed toroidal path} \implies v_T = 0$$

**Step 3: Vanishing of ℓ = 1 (charge)**

The ℓ = 1 wake component (Coulomb field / charge) arises from the **net displacement asymmetry** of the toroidal flow. For a W ≥ 1 torus, the circulation sweeps charge around a closed loop, creating a net ℓ = 1 pressure gradient.

For W = 0:

$$v_T = 0 \implies \text{no circulation} \implies \text{no displacement asymmetry} \implies \Phi_{1m} = 0$$

The neutrino is electrically neutral. This is not a coincidence — it is the **same topological fact** that makes the magnetic moment vanish.

**Step 4: Vanishing of ℓ = 2 (magnetic dipole)**

The ℓ = 2 component requires **organised flow** — a current loop enclosing an area. With v_T = 0:

$$\mu = \frac{e \cdot v_T \cdot R}{2} = \frac{e \cdot 0 \cdot R}{2} = 0$$

and equivalently:

$$\Phi_{2m} \propto v_T = 0 \implies \Phi_{2m} = 0 \quad \forall m, r$$

**Step 5: Completeness — no alternative sources of ℓ = 2**

Could the neutrino acquire a magnetic moment through some mechanism other than toroidal circulation?

**(a) Poloidal circulation?** — v_P requires a minor axis, which requires a torus (genus ≥ 1). W = 0 has genus 0. Therefore v_P = 0.

**(b) Translational motion through the lattice?** — A neutral perturbation translating through the lattice generates no ℓ = 1 or ℓ = 2 wake. Translation produces only ℓ = 0 perturbation (symmetric compression ahead, rarefaction behind — but this is a monopole/longitudinal effect, not a dipole).

**(c) Spin angular momentum?** — In SDT, "spin" IS the circulation. Electron spin = v_T circulation direction (±). Neutrino helicity = propagation-direction projection of whatever residual internal motion exists. But for W = 0, the residual internal motion is the **pitch precession** between mass eigenstates (flavour oscillation), which is axially symmetric about the propagation direction and produces no ℓ = 2 transverse component.

**(d) Virtual loop contributions?** — In the Standard Model, μ_ν arises from one-loop W-boson diagrams. In SDT, there are no virtual particles, no W bosons, no loop diagrams. Force is mediated by wake overlap, not particle exchange. The entire mechanism that generates the SM prediction **does not exist** in SDT.

**Therefore**: μ_ν = 0 exactly, for all neutrino flavours and mass eigenstates. ∎

### II.3 The Logical Chain

The proof can be compressed to a single causal chain:

```
W = 0 (open winding)
  → genus = 0 (no torus)
    → no closed toroidal path
      → v_T = 0 (no toroidal circulation)
        → no current loop
          → ℓ = 1 wake = 0 (no charge)
          → ℓ = 2 wake = 0 (no magnetic moment)
```

Each step is a **topological necessity**, not a dynamical approximation. The conclusion holds at all energies, all temperatures, and all distances. It is exact.

### II.4 Extension to All Three Mass Eigenstates

The three neutrino mass eigenstates (ν₁, ν₂, ν₃) differ in their **pitch angle** — the helical tilt of the open winding (from `neutrino.hpp:13-15`). The pitch angle determines the mass eigenstate via the displacement volume:

| Eigenstate | m [eV/c²] | V_disp [m³] | R_excl [m] | Pitch Angle |
|-----------|-----------|-------------|------------|-------------|
| ν₁ | 0.02 | 3.91×10⁻⁶⁹ | 9.77×10⁻²⁴ | θ₁ (shallowest) |
| ν₂ | 0.029 | 5.66×10⁻⁶⁹ | 1.11×10⁻²³ | θ₂ |
| ν₃ | 0.06 | 1.17×10⁻⁶⁸ | 1.41×10⁻²³ | θ₃ (steepest) |

All three share the same W = 0 topology. None has a closed circulation path. Therefore:

$$\mu_{\nu_1} = \mu_{\nu_2} = \mu_{\nu_3} = 0$$

Flavour oscillation (the precession between pitch angles) does not create or destroy a toroidal circuit. It cannot generate a magnetic moment at any point in the oscillation cycle.

---

## Part III: Comparison with the Standard Model

### III.1 The SM Prediction

In the minimally-extended Standard Model (adding right-handed Dirac neutrinos), the neutrino magnetic moment arises from a one-loop W-boson diagram (Fujikawa & Shrock, 1980):

$$\mu_\nu^{SM} = \frac{3 e G_F m_\nu}{8\pi^2 \sqrt{2}} \approx 3.2 \times 10^{-19} \left(\frac{m_\nu}{1 \text{ eV}}\right) \mu_B$$

For the three mass eigenstates:

| Eigenstate | m_ν [eV] | μ_ν^SM [μ_B] | μ_ν^SDT [μ_B] |
|-----------|----------|--------------|---------------|
| ν₁ | 0.02 | 6.4 × 10⁻²¹ | **0** |
| ν₂ | 0.029 | 9.3 × 10⁻²¹ | **0** |
| ν₃ | 0.06 | 1.9 × 10⁻²⁰ | **0** |

### III.2 Why the Predictions Differ

The disagreement is **ontological**, not parametric:

| Aspect | Standard Model | SDT |
|--------|---------------|-----|
| **Mechanism** | W-boson loop diagram couples ν to photon | No virtual particles; force = wake overlap |
| **Source** | Quantum loop correction to ν-γ vertex | Toroidal circulation of displaced volume |
| **Scales with** | m_ν (linear) | v_T (which is identically zero) |
| **Prediction** | μ_ν ∝ m_ν → small but non-zero | μ_ν = 0 exactly |
| **Falsification** | Non-zero measurement consistent (expected) | ANY non-zero measurement at ANY scale refutes W=0 |

The Standard Model predicts a non-zero moment because it has access to virtual loop processes. SDT has no such mechanism — its magnetic moments are **purely mechanical** (circulation current × loop area). No circulation → no moment. The gap between the two predictions (~10⁻²⁰ μ_B) is the discriminating interval.

### III.3 Majorana vs Dirac Distinction

If neutrinos are Majorana particles (ν = ν̄), CPT invariance forces the **diagonal** magnetic moment to vanish even in the Standard Model. Only transition moments (μ_ij, i ≠ j) survive.

In SDT, the Majorana/Dirac distinction does not exist in the standard sense. The neutrino is an open winding; the antineutrino is the same open winding with opposite helicity (counter-propagating pitch). Both have W = 0, both have μ = 0. SDT predicts:

$$\mu_{ij} = 0 \quad \forall \, i, j \quad \text{(diagonal AND transition moments)}$$

This is a stronger prediction than both the Dirac SM (where diagonal μ ≠ 0) and the Majorana SM (where transition μ ≠ 0).

---

## Part IV: Experimental Landscape

### IV.1 Current Bounds

| Experiment | Year | Method | Upper Bound [μ_B] | Neutrino Source |
|-----------|------|--------|-------------------|-----------------|
| GEMMA | 2012 | Reactor ν̄_e-e⁻ scattering | 2.9 × 10⁻¹¹ | Reactor |
| Borexino | 2017 | Solar ν-e⁻ scattering | 2.8 × 10⁻¹¹ | Solar |
| XENONnT | 2022 | Low-energy solar ν recoil | 6.3 × 10⁻¹² | Solar |
| PandaX-4T | 2023 | Low-energy ν recoil | ~10⁻¹¹ | Solar |
| LUX-ZEPLIN | 2024 | Xenon TPC recoil | ~10⁻¹¹ | Solar |

**Best current bound**: |μ_ν| < 6.3 × 10⁻¹² μ_B (XENONnT, 90% CL)

### IV.2 The Sensitivity Gap

```
Current best:       |μ_ν| < 6.3 × 10⁻¹² μ_B     (XENONnT)
                          ↕ ~8 orders of magnitude
SM prediction:       μ_ν ≈ 10⁻²⁰ μ_B               (Fujikawa-Shrock)
                          ↕ exactly zero
SDT prediction:      μ_ν = 0                          (topological)
```

The current experimental sensitivity is **eight orders of magnitude** above the Standard Model prediction. Both SDT and the SM are consistent with all existing data. Neither framework is falsified.

### IV.3 Discrimination Roadmap

To distinguish SDT (μ_ν ≡ 0) from the SM (μ_ν ~ 10⁻²⁰ μ_B), experiments must reach 10⁻²⁰ μ_B sensitivity. This requires:

**Near-term (achievable by ~2035)**:
- Next-generation xenon TPCs (DARWIN/XLZD): projected sensitivity ~10⁻¹² μ_B
- Improves bound but cannot discriminate SDT vs SM

**Medium-term (2035–2050)**:
- PTOLEMY (cosmic neutrino background detection, E01): if CνB neutrinos are detected, their scattering cross-sections can constrain μ_ν at lower energies
- Coherent elastic neutrino-nucleus scattering (CEνNS) at high-power reactors: potential ~10⁻¹³ μ_B

**Long-term (post-2050)**:
- Purpose-built μ_ν experiment at 10⁻²⁰ μ_B sensitivity
- Would require a dedicated low-background facility with orders-of-magnitude improvement in detection threshold
- If null result at 10⁻²⁰ μ_B: SM falsified (for Dirac case), SDT consistent
- If positive signal at any level: SDT falsified

### IV.4 Indirect Constraints

Astrophysical observations provide complementary bounds:

| Source | Constraint | Bound [μ_B] |
|--------|-----------|-------------|
| Red giant cooling | Extra energy loss from ν magnetic scattering | < 4.5 × 10⁻¹² |
| White dwarf luminosity function | Anomalous cooling rates | < 10⁻¹¹ |
| SN 1987A neutrino signal | Duration of neutrino burst | < 10⁻¹² |
| Big Bang nucleosynthesis | Extra degrees of freedom (N_eff) | < 10⁻¹⁰ |

All astrophysical constraints are consistent with μ_ν = 0.

---

## Part V: Falsification Protocol

### V.1 SDT Falsification Conditions

SDT's prediction μ_ν ≡ 0 is falsified if:

1. **Any** experiment detects a non-zero neutrino magnetic moment at **any** confidence level above 5σ
2. The detection is confirmed by at least one independent experiment using a different detection method
3. Systematic effects (particularly neutrino charge radius contributions to the scattering cross-section) are excluded

**Critical note**: A measurement of μ_ν ≠ 0 would specifically falsify the **W = 0 topological assignment** for the neutrino. It would not necessarily falsify all of SDT — it would indicate that the neutrino's topology is not an open winding, and the theory would need to assign a different (perhaps W = ½ or fractional) winding number that permits a small ℓ = 2 component.

### V.2 Standard Model Falsification Conditions

The minimally-extended SM prediction μ_ν = 3.2 × 10⁻¹⁹ (m_ν/eV) μ_B is falsified if:

1. A null measurement at 10⁻²⁰ μ_B sensitivity excludes the predicted value (for Dirac neutrinos)
2. Alternatively, a positive detection at μ_ν >> 10⁻¹⁹ μ_B would indicate **beyond-SM** contributions but not falsify the SM itself (the BSM contribution adds to the SM contribution)

### V.3 Decisive Experiment

The ideal decisive experiment would:
- Measure or bound μ_ν to 10⁻²⁰ μ_B precision
- Use low-energy (keV-scale) neutrinos to maximise the magnetic scattering contribution relative to weak scattering
- Employ multiple target materials to distinguish electromagnetic from weak contributions

**SDT's discriminating prediction table**:

| Outcome at 10⁻²⁰ μ_B sensitivity | SDT verdict | SM verdict |
|-----------------------------------|-------------|------------|
| μ_ν = 0 (null) | ✓ Consistent | ✗ Falsifies Dirac SM |
| μ_ν ≈ 10⁻²⁰ μ_B | ✗ Falsifies W=0 | ✓ Consistent with Dirac SM |
| μ_ν >> 10⁻²⁰ μ_B | ✗ Falsifies W=0 | Indicates BSM physics |

---

## Part VI: Relationship to Other SDT Predictions

### VI.1 Charge-Magnetic Moment Correlation

SDT predicts a strict correlation between charge and magnetic moment:

$$Q = 0 \iff \mu = 0 \quad \text{(for fundamental particles)}$$

This holds for:
- **Electron**: Q = -e, μ ≠ 0 ✓ (W = 1, closed torus, both ℓ = 1 and ℓ = 2 present)
- **Proton**: Q = +e, μ ≠ 0 ✓ (W = 3, closed trefoil, both present)
- **Neutrino**: Q = 0, μ = 0 ✓ predicted (W = 0, open winding, neither present)
- **Photon**: Q = 0, μ = 0 ✓ (propagating mode, no wake)

The **neutron** is an apparent exception: Q = 0 but μ_n = -1.913 μ_N ≠ 0. SDT resolves this because the neutron is **not a fundamental topology** — it is a W = 3 composite (same trefoil as the proton) with internal charge separation. The neutron's W = 3 topology provides the closed circulation paths that generate ℓ = 2 contributions, despite the net ℓ = 1 cancelling to zero (neutral overall). See Investigation NP15 for the full treatment.

The neutrino, by contrast, has W = 0. It has no internal charge separation because it has no torus structure at all. The charge-moment correlation holds at the fundamental topological level.

### VI.2 Connection to the Weak Interaction

The neutrino's negligible interaction cross-section is explained by the same topology (from `neutrino.hpp:17-19`):

| Particle | W | R_wake/R_excl | Interaction Strength |
|----------|---|---------------|---------------------|
| Proton | 3 | 2.39 × 10⁴ | Strong |
| Electron | 1 | 9.79 × 10⁵ | Electromagnetic |
| Neutrino ν₁ | 0 | 1.01 × 10¹⁸ | Weak |

The neutrino's wake-to-body ratio is **10¹² times** the electron's. Its influence is maximally diluted — this IS the weak interaction, explained geometrically, not via coupling constants. The same W = 0 topology that eliminates the magnetic moment also explains the feeble interaction strength.

### VI.3 Connection to Neutrino Mass

The neutrino mass (m_ν₁ ≈ 0.02 eV) represents the **minimum persistent displacement volume** — the smallest V_disp that can propagate indefinitely through the lattice without thermalising (from `neutrino.hpp:99-101`):

$$V_{\text{gap}} = V_{\text{disp},\nu_1} = \frac{3 m_{\nu_1} \ell_P^3 c^2}{\Phi} \approx 3.91 \times 10^{-69} \text{ m}^3$$

$$N_{\min} = \frac{V_{\text{gap}}}{\ell_P^3} \approx 9.25 \times 10^{35} \text{ spations}$$

The mass gap is a **lattice property** — the minimum number of spations that must be coherently displaced for the perturbation to persist. Below this threshold, disturbances thermalise. Above it, they propagate as neutrinos.

Crucially: having a non-zero mass does **not** give the neutrino a magnetic moment. Mass comes from V_disp (ℓ = 0 wake component). Magnetic moment comes from v_T (ℓ = 2 wake component). These are **independent** wake orders. The neutrino has ℓ = 0 (mass) but not ℓ = 2 (magnetic moment).

---

## Part VII: Summary of Results

### VII.1 Success Criteria Evaluation

From the original PROMPT.md:

- [x] **SDT prediction (μ_ν ≡ 0) formally stated with topological argument**
  - Proven via the ℓ-expansion: W = 0 → no closed toroidal circuit → v_T = 0 → ℓ = 2 wake = 0 → μ = 0
  
- [x] **Comparison to Standard Model prediction**
  - SM: μ_ν = 3.2 × 10⁻¹⁹ (m_ν/eV) μ_B ≈ 6 × 10⁻²¹ to 2 × 10⁻²⁰ μ_B
  - SDT: μ_ν = 0 exactly
  - Gap: ~10⁻²⁰ μ_B — requires purpose-built experiment to discriminate
  
- [x] **Experimental pathway to distinguish the two**
  - Current bounds (~10⁻¹² μ_B) are 8 orders above discrimination threshold
  - Near-term: DARWIN/XLZD will push to ~10⁻¹² μ_B
  - Long-term: dedicated experiment at 10⁻²⁰ μ_B needed for decisive test
  - PTOLEMY CνB detection provides complementary indirect constraints

### VII.2 The Prediction in One Line

> **SDT predicts μ_ν ≡ 0 for all neutrino species because the W = 0 open-winding topology cannot support the closed toroidal circulation required for an ℓ = 2 magnetic dipole wake.**

This is the third entry in SDT's falsifiable prediction register (`Theory/03_Open_Problems.md:41`), and it represents one of the sharpest discriminating tests between SDT and the Standard Model — a qualitative difference (exactly zero vs non-zero) rather than a quantitative one.

---

## Appendix A: Notation and Constants

| Symbol | Value | Description |
|--------|-------|-------------|
| W | 0, 1, 3 | Winding number (neutrino, electron, proton) |
| ℓ | 0, 1, 2, ... | Spherical harmonic order |
| μ_B | 9.274 × 10⁻²⁴ J/T | Bohr magneton |
| μ_N | 5.051 × 10⁻²⁷ J/T | Nuclear magneton |
| G_F | 1.166 × 10⁻⁵ GeV⁻² | Fermi coupling constant |
| v_T | Toroidal circulation velocity | Around major axis of torus |
| v_P | Poloidal circulation velocity | Around minor axis of torus |
| Φ_ℓm | Wake tensor component | ℓ-th multipole, m-th order |
| R_wake | ℏ/(mc) for W=0 | Wake radius (Compton wavelength) |
| R_excl | (3V_disp/4π)^(1/3) | Exclusion radius |

## Appendix B: Verification Code

See `cq07_neutrino_magnetic_moment.cpp` in this directory for the complete computational verification, which:
1. Computes the ℓ-expansion coefficients for W = 0, 1, and 3 topologies
2. Evaluates the SM prediction μ_ν^SM for all three mass eigenstates
3. Computes the sensitivity gap between current experiments and the discrimination threshold
4. Generates the full comparison table across all experimental bounds
