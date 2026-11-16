# Spatial Displacement Theory (SDT) Framework Investigation Proposal

**Context**: This report proposes new physical experiments and computational investigations to test, validate, falsify, or extend the Six-Law Spatial Displacement Theory (SDT) framework. All proposals strictly adhere to the framework's axioms, rely solely on observable parameters (such as `sdt::laws::measured` constraints and derived coupling constants), avoid prohibited constructs ($G$, $M$, dark matter, dark energy), and explicitly cite SDT laws and theorems.

---

## 1. Computational Investigation: Deriving $c$ from Mercury's Precession Using Koppa Formulas
**Objective**: Calculate the exact speed of light $c$ directly from solar system orbital parameters using the SDT koppa formalism, independently of standard electromagnetic or Maxwellian assumptions.

**SDT Grounding**: 
* Law V (Movement Budget, Theorems T16 & T17)
* SDT Bridge Law ($z = (v/c)^2 = 1/k^2$)
* $c$-boundary radius (Koppa): $\kappa = v_{surface}^2 R / c^2$

**Methodology**: 
In standard General Relativity, the anomalous perihelion precession of Mercury is modeled using the mass of the Sun and the gravitational constant ($6\pi GM / c^2 a(1-e^2)$). Under the SDT framework, $GM/c^2$ is an artifact. We replace it with the Sun's koppa ($\kappa_{Sun}$), which represents the c-boundary radius derived solely from the Sun's surface velocity and radius (Theorem T17). 
The SDT precession formula becomes:
$$ \Delta \phi = \frac{6\pi \kappa_{Sun}}{a(1-e^2)} = \frac{6\pi v_{Sun}^2 R_{Sun}}{c^2 a(1-e^2)} $$
We will computationally invert this relation to solve for $c$:
$$ c = v_{Sun} \sqrt{ \frac{6\pi R_{Sun}}{\Delta \phi \cdot a(1-e^2)} } $$
Using high-precision kinematic measurements of Mercury ($a$, $e$, $\Delta \phi$) and the Sun ($v_{Sun}$, $R_{Sun}$), we will compute $c$.

**Falsification Criteria**: 
If the derived $c$ significantly deviates from the fundamental invariant $299,792,458 \text{ m/s}$ (outside the combined observational uncertainty of Mercury's orbital elements and the Sun's surface kinematics), then the Bridge Law ($z = 1/k^2$) and Theorem T17 ($R_c = R/k^2$) are conclusively falsified.

---

## 2. Physical Experiment: Oort Cloud Kinematics at the Solar Pressure Domain Boundary
**Objective**: Detect the macroscopic boundary of the Release Cascade convergence pressure to confirm the spatial extent of the Sun's influence against the cosmological background.

**SDT Grounding**: 
* Law I (Cosmological Relay Throughput, Axioms R1-R6) - Background convergence pressure $P_{conv}$.
* Law II (Release Cascade, Corollaries) - Solar pressure domain.
* Law III (Convergent Boundary Pressure, Theorem T4) - Occlusion force.

**Methodology**: 
Law II defines the solar pressure domain radius, $r_{domain} = \sqrt{L_{Sun} / (4\pi F_{CMB})}$, mathematically pre-computed to be approximately $3.12 \times 10^{15} \text{ m}$ ($\approx 20,800 \text{ AU}$). Beyond this boundary, the isotropic CMB convergence pressure overwhelms the Sun's local recycled convergence. 
We propose an observational survey targeting extreme Trans-Neptunian Objects (eTNOs) and Oort cloud bodies whose aphelia cross the 20,800 AU threshold. We will measure their orbital accelerations to detect the theoretical pressure wall where the $1/r^2$ occlusion force (Theorem T4) undergoes an inflection point or disruption due to background convergence dominance.

**Falsification Criteria**: 
If objects natively orbit beyond 20,800 AU following undisturbed Keplerian trajectories extrapolated from standard $1/r^2$ scaling—without exhibiting any boundary pressure inflection or scattering effects predicted by Law II—the Release Cascade model and the CMB energy density equivalence to local convergence are falsified.

---

## 3. Computational Investigation: Spation Lattice Simulation of Vortex Topologies ($W=1$ vs $W=3$)
**Objective**: Computationally resolve Open Problem 2 and 4 by demonstrating why only specific vortex winding numbers ($W$) are stable, and deriving the exact proton-to-electron mass ratio.

**SDT Grounding**: 
* Law I (Cosmological Relay Throughput) - Shell cancellation $P_{conv}$.
* Law IV (Inertial Mass, Theorems T5-T7) - Mass as throughput reorganization cost: $m = \Phi V_{disp} / (l_P^3 c^2)$.
* W+1 Radius Conjecture: $R_{wake} = (W+1)\hbar / (mc)$.

**Methodology**: 
Construct a finite-element lattice simulation of spations phase-loaded with the convergence pressure $P_{conv} = 2.459 \times 10^{48} \text{ Pa}$. We will seed the lattice with various topological winding numbers (e.g., $W=1$ torus, $W=2$, $W=3$ trefoil knot, $W=4$) and evaluate their marginal stability under Theorem T10's condition ($P_{cf} = P_{conv}/3$).
For the stable configurations, we will integrate the volumetric displacement $V_{disp}$ of the lattice. We will then compute the predicted mass ratio $m_p/m_e$ as the strict ratio of their exclusion volumes $V_{disp}(W=3) / V_{disp}(W=1)$.

**Falsification Criteria**: 
If the simulation demonstrates that non-observed topologies (like $W=2$ or $W=4$) are stable, or if the resulting exclusion volume ratio $V_{disp,p} / V_{disp,e}$ fails to recover the measured physical mass ratio of $1836.15$, the W+1 Radius Conjecture and the geometric basis of Law IV (Theorems T5-T7) are falsified.

---

## 4. Physical Experiment: Precision Time Dilation Map via Earth's Koppa
**Objective**: Validate the Movement Budget's gravitational time dilation exclusively through derived kinematic values, eschewing mass-based gravity models.

**SDT Grounding**: 
* Law V (Movement Budget, Theorem T16) - Time dilation $d\tau/dt = \sqrt{1 - z R/r}$.
* Bridge Law ($z = 1/k^2$, $\kappa = R/k^2$).

**Methodology**: 
In SDT, Earth's koppa is derived strictly from its surface rotation/orbital properties: $\kappa_{Earth} = v_{Earth}^2 R_{Earth} / c^2 \approx 4.43 \text{ mm}$. We propose launching a constellation of optical lattice clocks into highly elliptical orbits to map the time dilation gradient $\Delta \tau$. 
The SDT prediction relies solely on Theorem T16, substituting $z R$ with Earth's koppa: 
$$ \frac{d\tau}{dt} = \sqrt{1 - \frac{\kappa_{Earth}}{r}} $$
This will be mapped continuously from $r = R_{Earth}$ to $r = 10 R_{Earth}$. 

**Falsification Criteria**: 
If the time dilation gradient cannot be perfectly matched by the parameter-free formula $\sqrt{1 - \kappa_{Earth}/r}$, or if it requires the re-introduction of a parameterized mass tensor or gravitational constant $G$ to resolve anomalies, Theorem T16 and the underlying Bridge Law are falsified.

---

## 5. Computational Investigation: Baryon Census of Galaxy Clusters without Missing Mass
**Objective**: Reconcile galactic orbital dynamics strictly using the SDT baryon census equation without invoking dark matter.

**SDT Grounding**: 
* Law IV (Inertial Mass) - Exclusion volumes.
* Bridge Law - Baryon $\kappa$ quantum: $\kappa_{per\_baryon} = l_P^2 c m_p / \hbar$.

**Methodology**: 
Dark matter is an artifact of applying a mass-based parameter $G$ to galactic rotation curves. In SDT, the baryon count of any orbital system is directly measured by its koppa:
$$ N_{baryons} = \frac{\kappa_{galaxy}}{\kappa_{per\_baryon}} = \frac{v^2 R / c^2}{l_P^2 c m_p / \hbar} $$
We will computationally apply this relation to a comprehensive dataset of galaxy clusters (e.g., SPARC database). Using only the outermost stable orbital velocities $v$ and galactic radii $R$, we will compute the required $N_{baryons}$ and compare it exclusively to observable baryonic matter (stars, plasma, interstellar gas).

**Falsification Criteria**: 
If the koppa-derived baryon count $N_{baryons}$ systematically exceeds the total observable baryonic matter (requiring an invisible missing mass to satisfy the SDT kinematic equation), the application of the Bridge Law at galactic scales is falsified.
