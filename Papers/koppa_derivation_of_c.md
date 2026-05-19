# The Speed of Light as a Geometric Closure Property of Orbital Mechanics

**James Tyndall**
Melbourne, Australia

---

## Abstract

We demonstrate that the speed of light *c* can be derived from purely gravitational orbital observables without direct electromagnetic measurement. By introducing the dimensionless kinematic ratio ϟ ≡ *c*/*v* (koppa), where *v* is the surface orbital velocity of a gravitating body, we show that the requirement of cross-body consistency — that ϟᵢ × vᵢ yields the same universal constant for every body — uniquely determines *c* from orbital geometry alone. The standard gravitational parameter μ = *GM* is recovered from orbital motion as v²d (velocity squared times distance), and the surface orbital velocity v* = √(μ/R) follows from measurable radius R. We prove that ϟ is overdetermined: perturbation of ϟ for any single body produces disagreement with every other body, simultaneous failure of the Schwarzschild boundary relation 2R/ϟ² = 2μ/c², violation of the redshift identity z = 1/ϟ², and breach of the closure invariant zϟ² = 1. We validate this framework across three bodies (Sun, Earth, Saturn), recovering c = 299,792,462 m/s to within 0.000001% of the accepted value, using no electromagnetic timing, no gravitational constant G, and no mass M — only orbital velocities, distances, and radii.

**Keywords:** speed of light, gravitational parameter, Schwarzschild radius, koppa, orbital kinematics, geometric derivation

---

## 1. Introduction

The speed of light *c* has been measured with progressively greater precision since Rømer's observation of Jovian satellite eclipses in 1676 [1]. All historical and modern determinations — including stellar aberration [2], toothed-wheel experiments [3], cavity resonance, and interferometry — rely on electromagnetic observation: the direct timing or geometric displacement of light signals.

We present a fundamentally different route. We show that *c* emerges as a geometric closure property of Newtonian orbital mechanics, recoverable without any electromagnetic measurement. The derivation requires only:

1. **Orbital velocities and distances** from any system of orbiting bodies (v²d = μ = *GM*);
2. **Body radii** from angular diameter measurements or circumference;
3. **One gravitational anchor**: the Schwarzschild radius of any body, determinable from orbital precession or gravitational lensing — both purely gravitational observations.

The key object is the **kinematic ratio** ϟ ≡ *c*/*v*, which we term *koppa* (from the archaic Greek letter, U+03DF). For a body of radius R and standard gravitational parameter μ = *GM*, the surface orbital velocity is v* = √(μ/R), and ϟ = *c*/v*. We show that ϟ is not a free parameter but is uniquely determined by the simultaneous satisfaction of six independent closure conditions.

The framework replaces the historical constants G and M — which are never independently measurable to high precision — with the kinematic pair (ϟ, R), yielding an equivalent description of gravity that is fully specified by orbital geometry.

---

## 2. Framework

### 2.1 Recovery of the gravitational parameter from orbital motion

For any body of mass M orbited by a test particle at distance d with velocity v:

$$\mu = GM = v^2 d \tag{1}$$

This product is directly measurable from:
- **Distance** d: parallax, angular measurement, or radar ranging;
- **Velocity** v: from d and orbital period P via v = 2πd/P;
- **Period** P: from any precision clock (pendulum, atomic, etc.).

Equation (1) does not require separate knowledge of G or M. The product μ is historically one of the most precisely known quantities in gravitational physics [4], determined to ~10⁻¹¹ relative uncertainty for the Sun, versus ~10⁻⁵ for G alone [5].

### 2.2 Surface orbital velocity

Given μ and the body's radius R:

$$v_* = \sqrt{\mu / R} \tag{2}$$

This is the circular orbital velocity at the surface. For the Sun, v* ≈ 436,800 m/s; for Earth, v* ≈ 7,910 m/s; for Saturn, v* ≈ 25,090 m/s. All are computable from orbital observables without *c*.

### 2.3 The kinematic ratio ϟ (koppa)

Define the dimensionless ratio:

$$\textrm{ϟ} \equiv c / v_* \tag{3}$$

If *c* is universal, then for any two bodies *i*, *j*:

$$\textrm{ϟ}_i \times v_{*,i} = \textrm{ϟ}_j \times v_{*,j} = c \tag{4}$$

The ratio ϟᵢ/ϟⱼ = v*,ⱼ/v*,ᵢ is immediately known from orbital observables. Only the absolute scale requires one anchor.

### 2.4 The c-boundary and the Schwarzschild relation

Define the **c-boundary radius**:

$$R_c = R / \textrm{ϟ}^2 \tag{5}$$

This is the hypothetical orbital radius at which circular velocity equals *c*. From equations (1)–(3):

$$R_c = R v_*^2 / c^2 = \mu / c^2 \tag{6}$$

Therefore:

$$2 R_c = 2\mu / c^2 = r_s \tag{7}$$

where rₛ is the Schwarzschild radius. This is an identity: the c-boundary radius is exactly **half the Schwarzschild radius** for every gravitating body.

### 2.5 The closure invariant

Define the gravitational redshift parameter:

$$z = 1 / \textrm{ϟ}^2 = v_*^2 / c^2 \tag{8}$$

Then:

$$z \textrm{ϟ}^2 = 1 \tag{9}$$

This is the **closure invariant**: the product of the redshift fraction and the square of the kinematic ratio is identically unity at every depth, for every body.

---

## 3. Derivation of *c* Without Electromagnetic Measurement

### 3.1 Inputs

For each body, we require (from purely orbital/gravitational observation):

| Quantity | Method | Example (Sun) |
|----------|--------|---------------|
| μ = *GM* | v²d from orbiting bodies | 1.327 × 10²⁰ m³/s² |
| R | Angular diameter × distance | 6.957 × 10⁸ m |
| v* | √(μ/R) | 436,762 m/s |

For the **Schwarzschild anchor**, we use the Sun's Schwarzschild radius rₛ ≈ 2,953 m, determinable from:
- Mercury's perihelion precession: δφ = 6πμ/(c²a(1−e²)) → c² = 6πμ/(δφ·a(1−e²)) [6]
- Shapiro time delay in radar ranging to inner planets [7]
- Gravitational lensing of background stars during solar eclipses [8]

All three methods are **gravitational** observations — none requires timing a light signal over a known baseline.

### 3.2 Extraction of *c*

From equation (7):

$$c = \sqrt{2\mu / r_s} \tag{10}$$

Using the Sun:

$$c = \sqrt{2 \times 1.32712 \times 10^{20} / 2953.25} = 299{,}792{,}462 \text{ m/s} \tag{11}$$

This agrees with the accepted value of *c* = 299,792,458 m/s to within **0.000001%**.

### 3.3 Cross-body validation

Once *c* is determined from the Sun, ϟ follows for every body:

| Body | v* (m/s) | ϟ = c/v* | R_c = R/ϟ² (m) | 2R_c (m) | rₛ (m) | Match |
|------|----------|----------|-----------------|----------|--------|-------|
| Sun | 436,762 | 686.40 | 1,476.6 | 2,953.2 | 2,953.3 | ✓ |
| Earth | 7,910 | 37,901 | 4.435×10⁻³ | 8.870×10⁻³ | 8.870×10⁻³ | ✓ |
| Saturn | 25,087 | 11,950 | 0.4220 | 0.8441 | 0.8441 | ✓ |

The Schwarzschild relation 2R_c = rₛ holds exactly for all three bodies, confirming that the derived *c* is universally consistent.

### 3.4 Closure verification

For all bodies: zϟ² = 1.000000 (to machine precision).

---

## 4. Adversarial Overdetermination Proof

We now prove that ϟ is **overdetermined**: no value other than the true ϟ simultaneously satisfies all constraints.

### 4.1 Perturbation analysis

Let ϟ☉ = 686.40 (true value). Perturb by ε = ±1:

| ϟ☉ | c = ϟ × v* (m/s) | Δc (km/s) | 2R_c (m) | ΔR_c (m) | Earth consensus |
|------|-------------------|-----------|----------|----------|-----------------|
| 685.40 | 299,355,700 | −437 | 2,961.9 | +8.6 | ✗ broken |
| **686.40** | **299,792,462** | **0** | **2,953.3** | **0** | **✓** |
| 687.40 | 300,229,224 | +437 | 2,944.7 | −8.6 | ✗ broken |

A perturbation of ±1 in ϟ shifts *c* by ±437 km/s and displaces R_c by ±8.6 m. The perturbed *c*, when applied to Earth or Saturn, produces a Schwarzschild radius that disagrees with the value obtained from their own orbital dynamics.

### 4.2 The six closure traps

For a given body, ϟ must simultaneously satisfy:

1. **Surface velocity**: v* = c/ϟ matches √(μ/R)
2. **Escape velocity**: v_esc = √2 · c/ϟ
3. **C-boundary**: R_c = R/ϟ² is a consistent orbital radius
4. **Schwarzschild lock**: 2R_c = 2μ/c²
5. **Redshift**: z = 1/ϟ² = μ/(c²R)
6. **Closure**: zϟ² = 1

All six are algebraically coupled through ϟ. Perturbation of ϟ breaks the cross-body consensus while remaining internally consistent only at the true value.

### 4.3 Multi-body consensus

The critical test: if ϟ is perturbed for one body, the derived *c* disagrees with the *c* derived from every other body. Three bodies provide three independent determinations of *c*; agreement to within measurement uncertainty constitutes overdetermination.

---

## 5. Discussion

### 5.1 What this result means

The speed of light is conventionally understood as an electromagnetic constant — the propagation speed of photons in vacuum. This derivation shows that *c* is equally a **gravitational** constant: it is the unique velocity at which the orbital mechanics of all gravitating bodies achieve mutual consistency. The electromagnetic and gravitational routes to *c* arrive at the same number because they must — *c* is a property of spacetime geometry, not of electromagnetism specifically.

### 5.2 The koppa formulation as a replacement for G and M

The standard gravitational constant G = 6.674 × 10⁻¹¹ m³/(kg·s²) is the least precisely known fundamental constant, with relative uncertainty ~2.2 × 10⁻⁵ [5]. Mass M is similarly imprecise for most bodies. The product μ = GM is known to ~10⁻¹¹ relative uncertainty for the Sun.

The koppa formulation replaces the pair (G, M) with the pair (ϟ, R):

$$\mu = c^2 R / \textrm{ϟ}^2 \tag{12}$$

Both ϟ and R are determined from **geometric** observables (velocities, distances, radii). No poorly-measured coupling constant is required.

### 5.3 Historical accessibility

The inputs to this derivation — orbital velocities from parallax and timing, body radii from angular measurements, and surface gravity from pendulums — were in principle available to any civilisation with sextants, pendulums, and basic arithmetic. The sole modern input is the Schwarzschild radius, which requires measurement of orbital precession or gravitational lensing. Mercury's anomalous precession was first quantified by Le Verrier in 1859 [9], preceding Einstein's explanation by 56 years. Had Le Verrier possessed the koppa framework, *c* could have been derived from Mercury's orbit in the 19th century — before Michelson's interferometric measurement.

### 5.4 Relation to general relativity

The Schwarzschild metric yields the same c-boundary naturally: the coordinate singularity at r = rₛ = 2GM/c² corresponds to 2R_c in our notation. The koppa framework does not contradict general relativity; it provides an alternative parameterisation that foregrounds the kinematic ratio ϟ = c/v rather than the Newtonian constants G and M. The closure invariant zϟ² = 1 is a restatement of the Schwarzschild redshift formula z = rₛ/(2r) evaluated at the surface (r = R).

---

## 6. Conclusion

We have shown that the speed of light can be derived from the geometry of orbital mechanics without direct electromagnetic measurement. The derivation proceeds in three steps:

1. **Recover** the gravitational parameter μ = v²d from any orbiting body;
2. **Compute** the surface orbital velocity v* = √(μ/R);
3. **Extract** *c* = √(2μ/rₛ) from the Schwarzschild radius of any body with a measurable orbital precession.

The kinematic ratio ϟ = c/v* is uniquely determined for each body and is overdetermined by six simultaneous closure conditions. Perturbation of ϟ produces cross-body disagreement that is immediately detectable.

The result demonstrates that *c* is not exclusively an electromagnetic quantity but a geometric property of gravitational orbital structure — the unique universal velocity at which all orbiting systems close.

---

## References

[1] O. Rømer, "Démonstration touchant le mouvement de la lumière trouvé par M. Roemer de l'Académie Royale des Sciences," *Journal des Sçavans*, 1676.

[2] J. Bradley, "A Letter from the Reverend Mr. James Bradley to Dr. Edmond Halley giving an Account of a new discovered Motion of the Fix'd Stars," *Phil. Trans. R. Soc.* **35**, 637–661, 1728.

[3] H. Fizeau, "Sur une expérience relative à la vitesse de propagation de la lumière," *Comptes Rendus* **29**, 90–92, 1849.

[4] E. V. Pitjeva and N. P. Pitjev, "Masses of the Main Asteroid Belt and the Kuiper Belt from the Motions of Planets and Spacecraft," *Solar Syst. Res.* **52**, 21–29, 2018.

[5] CODATA 2018 recommended values. P. J. Mohr, D. B. Newell, B. N. Taylor, "CODATA recommended values of the fundamental physical constants: 2018," *Rev. Mod. Phys.* **93**, 025010, 2021.

[6] A. Einstein, "Erklärung der Perihelbewegung des Merkur aus der allgemeinen Relativitätstheorie," *Sitzungsberichte der Preussischen Akademie der Wissenschaften*, 831–839, 1915.

[7] I. I. Shapiro, "Fourth Test of General Relativity," *Phys. Rev. Lett.* **13**, 789–791, 1964.

[8] F. W. Dyson, A. S. Eddington, C. Davidson, "A Determination of the Deflection of Light by the Sun's Gravitational Field," *Phil. Trans. R. Soc. A* **220**, 291–333, 1920.

[9] U. J. J. Le Verrier, "Théorie du mouvement de Mercure," *Annales de l'Observatoire Impérial de Paris* **5**, 1–196, 1859.

---

## Appendix A: Nomenclature

| Symbol | Name | Definition | Units |
|--------|------|------------|-------|
| ϟ | koppa (lowercase, U+03DF) | c / v* | dimensionless |
| Ϟ | Koppa (uppercase, U+03DE) | R / ϟ² = μ/c² | metres |
| μ | gravitational parameter | v²d = GM | m³/s² |
| v* | surface orbital velocity | √(μ/R) | m/s |
| R_c | c-boundary radius | R/ϟ² = Ϟ | metres |
| rₛ | Schwarzschild radius | 2μ/c² = 2Ϟ | metres |
| z | gravitational redshift | 1/ϟ² = v*²/c² | dimensionless |

## Appendix B: Computational Validation

The C++ source code implementing the full derivation and adversarial perturbation test is available at:

`sdt-engine/Investigations/CQ24_Koppa_Closure/cq24_koppa_closure.cpp`

Compiled with MSVC C++20 (/std:c++20). Reproduces c = 299,792,462 m/s from orbital inputs alone.
