# GOM03: 3D Volumetric Eclipse Saturation — The Pure Geometric Galaxy

> **Classification**: SCore Engine Formalization — The LSB/HSB Unification
> **Prerequisites**: `laws.hpp` (bridge invariants), GD05 failure analysis
> **Target**: Replace the empirical 2D saturation anchor with pure 3D radial occlusion integration.

## 1. The Core Problem: The 2D "MOND" Cheat

In early iterations of the SDT engine (`galactic.hpp` up to GD05), galaxy rotation curves were modeled using a flat 2D exponential disk surface density ($\Sigma_0 e^{-r/h_R}$). Because a 2D sheet lacks physical depth, the model could not natively calculate the true occlusion of convergence lines. 

To bypass this, previous developers "cheated": they empirically calibrated a saturation threshold ($\Sigma_{sat} = 175 M_\odot/\text{pc}^2$) based on the Milky Way. This forced the engine to act as a MOND-like interpolation function. 

**The Failure:** When this 2D engine was tested against Low Surface Brightness (LSB) galaxies (e.g., UGC 128, IC 2574), it catastrophically failed. Because LSBs are highly diffuse, their vertical surface density ($\approx 50 M_\odot/\text{pc}^2$) never crosses the hardcoded $175$ threshold, yielding a predicted flat velocity of 0 km/s. 

Your job is to purge this empirical fudging and implement the true SDT solution: **3D Volumetric Integration.**

## 2. The Theoretical Framework: Steel vs. Cheese

Galaxies are not 2D sheets; they are 3D volumes. The convergence pressure that dictates orbital velocity at radius $R$ travels **radially (horizontally)** through the galactic mid-plane, not vertically through the face.

### The Scale Inversion Principle (The Muon/Electron Analogy)
In SDT, higher mass deepens the convergence well, drawing topology tighter together (like a muon). Lower mass results in a shallower well, allowing topology to puff outward (like an electron). 
- **High Surface Brightness (HSB)**: High mass, tightly bound, compact radius ($h_R$), thin disk. (The "Steel Wheel")
- **Low Surface Brightness (LSB)**: Low mass, loosely bound, highly diffuse, massive radius. (The "Cheese Wheel")

### Horizontal Column Density ($\Lambda$)
A convergence line traveling radially from the edge of an LSB galaxy to its center passes through a much longer path length than in an HSB galaxy. While the LSB's local volume density ($\rho$) is low, the integration of that density over its massive radial scale length accumulates tremendous occlusion.

**The breakthrough:** An LSB's horizontal column density $\Lambda(R)$ will hit the exact same geometric occlusion saturation limit ($f_{occ} \to 0.5$) as an HSB. The "cheese" is less dense, but the axle is vastly thicker. 

## 3. Strict Development Rules (Zero-Parameter Doctrine)

1. **NO EMPIRICAL ANCHORS.** You are strictly forbidden from calibrating against the Milky Way, SPARC data, or MOND constants. If you hardcode a number like $175$ or $1.2 \times 10^{-10}$, you have failed.
2. **USE FUNDAMENTAL INVARIANTS ONLY.** The only declared dependencies are Planck length ($l_p$), speed of light ($c$), proton mass ($m_p$), and the reduced Planck constant ($\hbar$). From these, SDT natively derives $\kappa_{per\_baryon}$.
3. **NO DARK MATTER.** Do not fit or reference NFW halos.

## 4. Required Implementation Steps

### Phase 1: 3D Density Formulation
Define a 3D cylindrical volume density profile for a galaxy:
$$ \rho(r, z) = \rho_0 e^{-r/h_R} e^{-|z|/h_z} $$
Mathematically derive $\rho_0$ purely from the total baryonic mass $M_{bar}$ and the geometric scale parameters $h_R$ (radial scale length) and $h_z$ (vertical scale height). 

### Phase 2: Radial Occlusion Integral
Write the integration that calculates the total horizontal column density $\Lambda(R)$ experienced by a body orbiting at radius $R$ in the mid-plane ($z=0$):
$$ \Lambda(R) = \int_{0}^{R} \rho(r, 0) dr $$
You must incorporate the structural multiplier $(h_R / h_z)$ that natively accounts for the "puffiness" of LSB galaxies.

### Phase 3: Pure Geometric Saturation
Calculate the eclipse fraction $f_{occ}$ along this horizontal path using only the SDT invariant $\kappa_{per\_baryon}$ as the effective cross-section. 

### Phase 4: C++ Engine Integration
Rewrite the `sdt::galactic` namespace in `galactic.hpp`. 
- Delete `Sigma_sat_Msun_pc2 = 175.0`.
- Replace `eclipse_fraction(Sigma)` with `radial_eclipse_fraction(Lambda, koppa_per_baryon)`.
- Re-run the GD05 investigation on the SPARC dataset to definitively prove that both HSBs and LSBs reach saturation and flat rotation curves purely via 3D geometry.

## 5. Deliverables
- A mathematically rigorous markdown proof of the horizontal column density integration.
- The updated, mathematically pure `galactic.hpp` header.
- A successful compilation and run against the SPARC dataset proving LSB survival.
