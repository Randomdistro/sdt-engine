# Algebraic structures in the pasted text: explanation and two demonstrations each (2026-10-08)

Written for Harvey. Instrument: `paste_algebra_demos/paste_algebra_demos_1.cpp`; output: `paste_algebra_demos/paste_algebra_demos_1_results.txt` (MSVC 19.44, constants from `sdt::laws`; external constants are marked [ext] for illustration only, and [B] where the value is from memory and needs checking). Validated first on a known second derivative and a known integral. Three faults of my own were found in the first run and fixed before these numbers: a missing β in the momentum vector (A2 B), a floating-point drift in the accumulated orbital angle that biased the precession by about 10⁻⁹ rad per orbit (D1, G3), and a wrong growth factor in my text for the photon-orbit perturbation (cosh 5, not e⁵; D1 B).

**Scope.** "Every algebraic structure" means every formula or defining relation written in the pasted text, plus relations that the text describes in words with a definite algebraic form (listed as implicit). The paste was truncated ("Message truncated – exceeded 50,000 character limit") in the middle of the discussion of v = (cϰ)√(R/r); anything after that point is not here. If the rest contains further formulas, send it and I will add them.

**What the two demonstrations are.** Demonstration A is a numerical instance with real numbers. Demonstration B is an independent check of the same structure: a limiting case, a derivation by a second route, a conservation test, or a case where the structure reaches its edge. Each entry ends with a status line: *sound* (the formula as written is correct), *convention* (correct once a sign or symbol convention is stated), *issue* (a gap or error in the paste), or *supplement* (a structure the paste calls for and does not write down, added to answer a question the paste raises).

## Index

| ID | Structure | Attributed in the paste to | Status |
|---|---|---|---|
| A1 | Lorentz factor γ | Lorentz | sound |
| A2 | m∥ = γ³m₀, m⊥ = γm₀ | Lorentz | sound |
| A3 | P^μ = mU^μ, E = γmc² | Einstein | sound |
| A4 | U^μU_μ = −c² | Minkowski | sound |
| A5 | null cone s² = 0, lookback radius | Minkowski | sound |
| B1 | c = 1/√(ε₀μ₀); wave speed = √(stiffness/density) | the "spation" tension and density | sound |
| B2 | Maxwell stress tensor T_ij | Abraham | convention |
| B3 | time-averaged ⟨T_rr⟩ = ½(ε₀⟨E²⟩ + ⟨B²⟩/μ₀) | Abraham | sound |
| B4 | Helmholtz ∇²ψ + k²ψ = 0; Fresnel number | Poincaré | sound; supplement |
| B5 | dispersion ω(k), v_g = ∂ω/∂k | Abraham | sound; supplement |
| C1 | Doppler factor D(θ) | Poincaré | sound |
| C2 | momentum-flux integral F = ∫S n̂ dΩ | Poincaré | sound; supplement |
| C3 | Fresnel drag v′ = c/n + v(1 − 1/n²) | Poincaré | sound |
| D1 | orbit equation u″ + u = GM/h² + 3GMu²/c² | Einstein | sound; note |
| D2 | light deflection 2GM/(c²r) and 4GM/(c²r) | Einstein | sound |
| D3 | Δt = Δt₀(1 − Φ/c²), g₀₀ = −(1 + 2Φ/c²) | Einstein | convention |
| D4 | c(r) = c₀(1 + Φ/c²) (1911) | Einstein | sound; supplement |
| E1 | phase lag Δφ = ωΔt = ω(d/v − d/c) | Lorentz | sound |
| E2 | throughput conservation ∮_in S·dA = ∮_out S·dA | Lorentz | sound |
| E3 | shell area, T ∝ (1 + z), octave 1 + z = 2ⁿ | Minkowski; you | issue (area) |
| F1 | ℓ_P = √(ℏG/c³); Planck force c⁴/G | the displacement construction; "gravitational impedance" | sound |
| F2 | N_disp = Ω₀/v₀ = 8(R₀/ℓ_P)³ | the displacement construction | sound |
| F3 | N_cap(r) = 24(r/ℓ_P)² | the displacement construction | sound |
| F4 | u(r) = Ω₀/(4πr²) = R₀³/(3r²) | the displacement construction | sound |
| F5 | R_term = √(R₀³/(3ℓ_P)) | the displacement construction | sound |
| F6 | strain energy ∝ r⁻⁶ | Abraham | sound (shear); issue (bulk term) |
| F7 | ρ_s = ρ₀(1 − Ω₀/(4πr³)) | Lorentz | issue |
| F8 | n(r) = 1 + αΩ₀/r | Lorentz | issue |
| F9 | ∇·g = −4πGρ ⟺ ∇·u = Ω₀δ(r) | Einstein | sound; supplement |
| G1 | v = c√(ϟ/r) = c/k(r), k = k₀√(r/R) | you | sound |
| G2 | z k² = 1 (spectroscopic z) | you | sound (a test) |
| G3 | modified Kepler a = −(c²ϟ/r²)(1 + βϟ/r) | you | sound; supplement |
| H1 | attenuation exp(−τ), force linear in mass only for τ ≪ 1 | Lorentz (self-shadowing) | implicit |

---

## A. Kinematics and dynamics

### A1 — Lorentz factor, γ = (1 − v²/c²)^(−1/2)
**Explanation.** The factor by which the dynamical quantities of a body (momentum, energy, the resistance to acceleration) grow with speed. It is 1 at rest, diverges as v → c, and is the single function from which A2 to A4 follow. In the paste it is described as either a physical deformation of matter moving through a medium or a kinematic law; the algebra is the same in both readings.
**Demonstration A.** γ at β = 0.1, 0.5, 0.9, 0.99, 0.999: 1.005038, 1.154701, 2.294157, 7.088812, 22.366272.
**Demonstration B (low-speed limit).** At v = 30 km/s, γ − 1 = 5.006925×10⁻⁹ against β²/2 = 5.006925×10⁻⁹ (ratio 1.000000008): the first-order series β²/2 is exact at orbital speeds.
**Status.** Sound.

### A2 — longitudinal and transverse masses, m∥ = γ³m₀ and m⊥ = γm₀
**Explanation.** The resistance to a change of speed depends on the direction of the change relative to the motion. Defining each mass as force over acceleration, with p = γm₀v: along the motion, m∥ = dp/dv = γ³m₀; across it, the momentum changes direction but not magnitude, |dp/dt| = γm₀vω for uniform circular motion, so m⊥ = γm₀. Lorentz (1904) obtained these from the electron's field in the medium (see the companion notes); Einstein's 1905 transverse mass, m₀/(1 − v²/c²) = γ²m₀, differs because force was defined in the moving frame, which is the caution he printed (not in the paste).
**Demonstration A.** β = 0.5: m∥ = 1.5396 m₀, m⊥ = 1.1547 m₀ (1905 transverse 1.3333); β = 0.9: 12.0745, 2.2942 (5.2632); β = 0.99: 356.2217, 7.0888 (50.2513).
**Demonstration B (two derivations).** dp/dv by central difference at β = 0.9: 12.07451238 against γ³ = 12.07451231 (relative 5.9×10⁻⁹). Circular motion at β = 0.9: |dp/dt|/(vω) = 2.29415734 = γ = 2.29415734.
**Status.** Sound. The direction dependence is the content to reproduce from a relay model (the notes, §6 Q1).

### A3 — four-momentum and energy, P^μ = mU^μ, E = γmc², p = γmv
**Explanation.** Energy and momentum of a body are the components of one four-vector whose length is fixed by the invariant mass: E² − p²c² = m²c⁴. The divergence of E as v → c is the "infinite mass" of the paste; in this form the invariant m is constant and E diverges.
**Demonstration A.** For the electron (engine mass), (E² − p²c²)/(m²c⁴) − 1 = 0 at β = 0.1, −1.9×10⁻¹⁵ at 0.9, −1.4×10⁻¹³ at 0.999.
**Demonstration B (low-speed limit).** (E − mc²)/(½mv²) = 1.00007501 at β = 0.01 against the series 1 + 3β²/4 = 1.00007500; 1.00756305 against 1.00750000 at β = 0.1.
**Status.** Sound. That the divergence shows mass to be imparted is not a consequence of this algebra (the notes, §4).

### A4 — the hyperbolic constraint, U^μU_μ = −c²
**Explanation.** With signature (−,+,+,+) the four-velocity U = γ(c, v) has fixed length: U·U = −c², whatever the motion. Boosts are hyperbolic rotations, U = c(cosh η, sinh η) along a line, and rapidities add.
**Demonstration A.** For v = (0.3, 0.4, 0.1)c: U²/c² = −1.000000000000 before and after a boost of 0.6c along x.
**Demonstration B.** Rapidities add: tanh(η₁ + η₂) = 0.8888888889 = (β₁ + β₂)/(1 + β₁β₂) for β₁ = 0.5, β₂ = 0.7; cosh²η − sinh²η = 1.000000000000.
**Status.** Sound.

### A5 — the null cone, s² = −c²(t − t₀)² + |x − x₀|² = 0, and the lookback radius r = c(t₀ − t)
**Explanation.** Events joined by a light ray have zero interval; the past light cone of an event is the set of events that can send it a signal. The paste's "boundary at which light converges on every point" is the cone's intersection with the epoch of emission.
**Demonstration A.** One year of lookback: r = 9.460730×10¹⁵ m = 1.000000 light-year; s²/(c²Δt²) = 0.
**Demonstration B.** s² is invariant under a boost of 0.8c: −6.9653526352×10¹⁷ before and after (relative difference 4.4×10⁻¹⁶).
**Status.** Sound. The statement that matter occludes a bundle of null geodesics with negative expansion is a claim about congruences that the paste does not write as a formula.

## B. Electromagnetism and wave structure

### B1 — c = 1/√(ε₀μ₀), and speed = √(stiffness/density)
**Explanation.** The speed of an electromagnetic wave follows from the two constants of the medium. The paste uses the acoustic analogy: a wave in a medium cannot exceed the speed fixed by the medium's stiffness over its density, c = √(K/ρ)-like. The analogy is a statement about form; the demonstration shows the form working in three media.
**Demonstration A [ext].** 1/√(ε₀μ₀) = 299,792,458.000006 m/s against c (relative 2.2×10⁻¹⁴).
**Demonstration B [ext].** Air (√(γP/ρ), 1.4, 101,325 Pa, 1.204 kg/m³): 343.2 m/s; water (√(K/ρ), 2.2×10⁹ Pa, 998 kg/m³): 1485 m/s; a steel rod (√(E/ρ), 200 GPa, 7850 kg/m³): 5048 m/s.
**Status.** Sound. What stiffness and density of the spation would be is the open derivation.

### B2 — the Maxwell stress tensor, T_ij = ε₀(E_iE_j − ½δ_ijE²) + (1/μ₀)(B_iB_j − ½δ_ijB²)
**Explanation.** The momentum carried by a field and the force on a body inside a closed surface follow from the integral of T over the surface. As written, T is the negative of the momentum flux density: tension along field lines (T_zz > 0 for a field along z), pressure across them. Abraham's use is the force on a body from the field momentum crossing a bounding surface.
**Demonstration A [ext].** Static E = 10⁶ V/m along z: T_zz = 4.4271 Pa (tension along the lines) = ε₀E²/2; T_xx = −4.4271 Pa (pressure across).
**Demonstration B (isotropic average).** For isotropic radiation the momentum flux Π_ii = u⟨nᵢ²⟩ = 1.391599×10⁻¹⁴, 1.391599×10⁻¹⁴, 1.391585×10⁻¹⁴ Pa against u/3 = 1.391594×10⁻¹⁴ Pa, and `law_I::P_rad` = 1.391594×10⁻¹⁴ Pa (u = aT⁴ = 4.17478×10⁻¹⁴ J/m³, direction average by quadrature).
**Status.** Convention (sign of T against the momentum flux).

### B3 — time-averaged flux, ⟨T_rr⟩ = ½(ε₀⟨E²⟩ + ⟨B²⟩/μ₀)
**Explanation.** For a plane wave the momentum flux equals the energy density, so the pressure on a perfect absorber is I/c and on a perfect reflector 2I/c; the factor ½ puts the time-averaged energy density u in the formula as written.
**Demonstration A [ext].** Solar constant 1361 W/m²: E₀ = 1012.65 V/m, B₀ = 3.378×10⁻⁶ T; ⟨T_rr⟩ = 4.539807×10⁻⁶ Pa = I/c; a reflector 9.079615×10⁻⁶ Pa.
**Demonstration B.** A one-directional CMB beam presses with u = 4.17478×10⁻¹⁴ Pa; an isotropic bath with u/3 = 1.39159×10⁻¹⁴ Pa (ratio 3).
**Status.** Sound.

### B4 — Helmholtz equation, ∇²ψ + k²ψ = 0, and the Fresnel number F = a²/(λL)
**Explanation.** A monochromatic wave in a uniform medium satisfies Helmholtz. Behind an obstacle of size a, the geometric shadow survives only while the Fresnel number F = a²/(λL) exceeds 1; beyond L = a²/λ diffraction fills it. This is the quantitative form of the paste's requirement that the carrier wavelength be far smaller than the occluding body.
**Demonstration A.** A plane wave cos(kx) and a spherical wave e^{ikr}/r satisfy the equation to finite-difference accuracy (residuals −8.9×10⁻⁵ and 1.2×10⁻⁴ against k²ψ = 27.0, step 10⁻³; relative 3×10⁻⁶).
**Demonstration B.** F for the Earth at 1 AU: 1.679×10³⁷ for λ = ℓ_P and 2.560×10⁵ for λ = 1.06 mm (the CMB peak): shadow persists. For one baryon (0.84 fm) at 1 m: F = 6.657×10⁻²⁸ for λ = 1.06 mm (diffraction fills it) and 4.366×10⁴ for λ = ℓ_P, i.e. the shadow of a single baryon at a Planck-length carrier persists only to L = a²/λ = 4.4×10⁴ m.
**Status.** Sound; the last number is a supplement the paste's argument needs: the coherence distance of a single baryon's shadow is 44 km, so a 1/r² force over astronomical distances must be built from the shadow of a body's whole cross-section or treated with the diffraction included.

### B5 — dispersion, ω(k), and group velocity v_g = ∂ω/∂k
**Explanation.** The phase velocity ω/k and the group velocity ∂ω/∂k differ whenever the medium disperses; the group velocity carries the signal. The paste raises it as Abraham's question: how can the speed of light vanish at high energy?
**Demonstration A.** A plasma, ω² = c²k² + ω_p²: at ω = 2ω_p, v_g/c = 0.86603, v_p/c = 1.15470; at 1.1ω_p, 0.41660 and 2.40040; at 1.001ω_p, 0.04469 and 22.37745; v_pv_g/c² = 1.0000000000 in each case. The group velocity vanishes at the cutoff ω → ω_p.
**Demonstration B (supplement).** A discrete chain of spacing ℓ, ω = (2c/ℓ)sin(kℓ/2), gives v_g = c cos(kℓ/2): 0.7071c at kℓ = π/2, 1.5708×10⁻³c at kℓ = π(1 − 10⁻³), 1.5708×10⁻⁶c at π(1 − 10⁻⁶): the group velocity goes to zero at the zone edge k = π/ℓ, with no accumulation of stress-energy.
**Status.** Sound. B is the simplest answer to the question in the paste: a discrete medium has v_g → 0 at short wavelength by its own dispersion relation; whether the spation chain has this form is a statement to register.

## C. A moving body in radiation

### C1 — Doppler factor, D(θ) = √(1 − β²)/(1 − β cos θ)
**Explanation.** The frequency (and, for a blackbody, the temperature) of radiation seen from a moving body depends on the direction: higher ahead, lower behind, and by 1/γ across the motion (the transverse Doppler shift).
**Demonstration A.** v = 370 km/s (β = 1.2342×10⁻³): forward D = 1.00123495, T = 2.728866 K; the dipole T₀(D − 1) = 3.3659 mK (first order T₀β = 3.3638 mK).
**Demonstration B.** Backward D = 0.99876657; D(0)/D(π) = 1.00247142 = (1 + β)/(1 − β); transverse D(90°) = 0.9999992384 = 1/γ.
**Status.** Sound.

### C2 — the momentum-flux integral, F_net = ∫S(θ,φ)·n̂ dΩ, and the drag it gives
**Explanation.** The force on a body in a radiation field is the integral of the incoming momentum flux over solid angle. For an isotropic bath it is zero at rest; for a body moving with β the intensity in its frame is I₀[γ(1 − β cos θ)]⁻⁴ and the integral gives a drag, F = −(4/3)uσβ at small β. This is Poincaré's drag objection written as algebra.
**Demonstration A.** F/(uσ) by quadrature: β = 0.001: −1.33333467×10⁻³ against −(4/3)β (ratio 1.000001); β = 0.01: ratio 1.000100; 0.1: 1.010101; 0.5: 1.333333.
**Demonstration B [ext].** The Earth (σ = πR² = 1.275×10¹⁴ m², v = 29.78 km/s): CMB drag F = 7.051×10⁻⁴ N against the centripetal force Mv²/AU = 3.540×10²² N, ratio 2.0×10⁻²⁶.
**Status.** Sound; the drag result is a supplement. It applies to a body absorbing or scattering a radiation bath; whether a lossless relay medium has any such term is the question the paste's d'Alembert remark raises.

### C3 — Fresnel drag, v′ = c/n + v(1 − 1/n²)
**Explanation.** Light in a moving transparent medium is carried along by only part of the medium's speed. The coefficient 1 − 1/n² is the first-order form of relativistic velocity addition.
**Demonstration A [ext].** Water (n = 1.333) at 7 m/s: drag 3.060531 m/s (coefficient 0.4372); exact velocity addition gives 3.060530 m/s (relative −9.1×10⁻⁹).
**Demonstration B.** Limits: n = 1 gives 0, n → ∞ gives v; at v = 0.5c and n = 1.5 the first-order formula gives 0.2778c and the exact addition 0.2083c (the first-order form fails at second order).
**Status.** Sound.

## D. Gravitation

### D1 — orbit equation, d²u/dφ² + u = GM/h² + 3GMu²/c² (u = 1/r)
**Explanation.** With GM = c²ϟ the equation reads w″ + w = Ũ + 3w², with w = ϟ/r and Ũ = ϟ/(a(1 − e²)) = ϟGM/h². The 3w² term makes an orbit precess by 6πϟ/(a(1 − e²)) per revolution to first order. In the effective potential this is a 1/r³ term (force 1/r⁴); the paste's "1/r³ term" refers to it. G3 gives a 1/r³ force with the same first-order precession.
**Demonstration A.** Mercury (a, e and ϟ = 1476.5989 m from the engine), 40 orbits integrated in φ: advance 5.018579×10⁻⁷ rad/orbit = 42.9800 arcsec/century; 6πϟ/(a(1 − e²)) = 5.018578×10⁻⁷ (relative 1.8×10⁻⁷).
**Demonstration B.** For light, w″ + w = 3w² has the circular solution w = 1/3 (r = 3ϟ), residual 0; a perturbation of 10⁻⁸ grows by 74.21 over 5 radians = cosh(5) = 74.21: unstable.
**Status.** Sound.

### D2 — light deflection, 2GM/(c²b) (scalar) and 4GM/(c²b) (tensor)
**Explanation.** Light passing a mass at impact parameter b is bent by 4ϟ/b when both the time and space parts of the metric act, and by half that when only the speed of light varies with the potential (the 1911 form).
**Demonstration A.** Integrating w″ + w = 3ϟw² for the Sun (b = R_Sun): 8.489915×10⁻⁶ rad = 1.7512 arcsec against 4ϟ/b = 8.489860×10⁻⁶ rad (relative 6.5×10⁻⁶, consistent with the second-order term (15π/16)ϟ/b = 6×10⁻⁶ [B]).
**Demonstration B.** The scalar value 2ϟ/b = 4.244930×10⁻⁶ rad = 0.8756 arcsec; tensor/scalar = 2.0000.
**Status.** Sound.

### D3 — time dilation, Δt = Δt₀(1 − Φ/c²), and g₀₀ = −(1 + 2Φ/c²)
**Explanation.** A clock in a potential runs slow by the potential over c². The paste uses two sign conventions: (1 − Φ/c²) with Φ the positive magnitude GM/r, and (1 + Φ/c²), (1 + 2Φ/c²) with Φ negative (Φ = −c²ϟ/r). Both give dτ = dt(1 − ϟ/r) to first order.
**Demonstration A.** Sun surface: ϟ/R = 2.122465×10⁻⁶; √(1 − 2ϟ/R) = 0.999997877532794 against 1 − ϟ/R = 0.999997877535046 (difference −2.25×10⁻¹², second order).
**Demonstration B [ext, B].** GPS: GM from gR² = 3.9805×10¹⁴ m³/s²; gravitational offset +45.66 µs/day, velocity offset −7.21 µs/day, net +38.45 µs/day.
**Status.** Convention (state the sign of Φ in each formula).

### D4 — Einstein's 1911 scalar form, c(r) = c₀(1 + Φ/c²)
**Explanation.** The local coordinate speed of light varies linearly with the potential. It gives the half-deflection of D2 and half of the weak-field delay; the full delay needs the speed to vary as c(1 − 2ϟ/r) to first order (the form c(1 − z)²).
**Demonstration A.** At the Sun's surface c(R) = c(1 − z), so c·z = 636.299 m/s lower (z = 2.122465×10⁻⁶).
**Demonstration B (supplement).** A radar path from 1 AU to 1.52 AU with impact parameter 1.5 R_Sun, n − 1 = aϟ/r: a = 1 (the 1911 form): one-way 57.803 µs, round trip 115.605 µs; a = 2 (the full form): 115.605 µs one way, 231.211 µs round trip (path factor L = 11.7356).
**Status.** Sound.

## E. Phase and throughput

### E1 — phase lag, Δφ = ωΔt = ω(d/v − d/c)
**Explanation.** A wave crossing a region where it travels slower is delayed; the delay in time is independent of frequency for a non-dispersive medium, and the phase lag is ω times it. This is the paste's "phased transmission".
**Demonstration A [ext].** A glass plate 1 mm thick, n = 1.5, at 500 nm: Δφ = 6283.19 rad = 1000.0 cycles.
**Demonstration B.** The delay d(n − 1)/c = 1.6678×10⁻¹² s is the same at 400, 500 and 700 nm.
**Status.** Sound.

### E2 — conservation of throughput, ∮_in S·dA = ∮_out S·dA
**Explanation.** In a lossless region the energy entering a closed surface equals the energy leaving it; a body that delays the wave without absorbing it leaves the total flux unchanged. This is what removes the heating objection in the paste.
**Demonstration A.** A point source of 1 W: the flux through spheres of radius 1, 10 and 10³ m is 1.000000000000 W each.
**Demonstration B.** A lossless slab (n = 1.5, Airy form): the transmitted fraction runs from 0.8521 to 1.0000 with the phase; the worst |T + R − 1| is 2.2×10⁻¹⁶.
**Status.** Sound.

### E3 — the cosmic shell, T = T₀(1 + z), area ∝ (1 + z)⁻², and the octave 1 + z = 2ⁿ
**Explanation.** In the paste the CMB is the boundary event of recombination seen redshifted: temperatures scale as 1 + z, the physical area of a shell at fixed comoving radius as (1 + z)⁻², and your octave statement as 1 + z = 2ⁿ.
**Demonstration A.** T(z = 1100) = T₀(1 + z) = 3000.78 K; 3000 K corresponds to 1 + z = 1100.72.
**Demonstration B.** (1 + z)⁻² = 8.2495×10⁻⁷; n = log₂(1 + z) = 10.1046 octaves; T₀2¹⁰ = 2790.9 K; 2ⁿ = 1101.0000.
**Status.** Issue: the paste writes A(t) = 4πR_H(t)² with R_H ≈ c(t − t_rec) and then states A ∝ (1 + z)⁻². The first is a light-travel distance, growing linearly in time; the second holds for the physical area of a shell at fixed comoving radius. They are different statements.

## F. The displacement construction

### F1 — Planck length, ℓ_P = √(ℏG/c³), and the Planck force c⁴/G
**Explanation.** The length that the construction takes as the spation diameter, and the force scale the paste calls "gravitational impedance". In the repository G is an output of the koppa structure; here G enters only to check the formula.
**Demonstration A [ext G].** √(ℏG/c³) = 1.616255×10⁻³⁵ m against the engine ℓ_P (relative 1.5×10⁻⁸, within the 2×10⁻⁵ uncertainty of G); c⁴/G = 1.21026×10⁴⁴ N.
**Demonstration B [ext G].** (c⁴/G)ℓ_P = 1.95608×10⁹ J = √(ℏc⁵/G) = 1.2209×10¹⁹ GeV.
**Status.** Sound.

### F2 — the displaced count, N_disp = Ω₀/v₀ = 8(R₀/ℓ_P)³ with v₀ = (π/6)ℓ_P³
**Explanation.** The number of spation volumes in the excluded volume Ω₀ = (4/3)πR₀³. The cell volume (π/6)ℓ_P³ is the volume of one sphere of diameter ℓ_P (full filling).
**Demonstration A.** R₀ = 8.4×10⁻¹⁶ m: Ω₀ = 2.4827×10⁻⁴⁵ m³, N_disp = 1.1230×10⁶⁰; with R_lock = 8.41236×10⁻¹⁶ m: 2.4937×10⁻⁴⁵ m³, 1.1280×10⁶⁰.
**Demonstration B (the cell choice).** At R₀ = 8.4×10⁻¹⁶ m: sphere volume 1.1230×10⁶⁰; face-centred cell ℓ_P³/√2: 8.3159×10⁵⁹; cubic cell ℓ_P³: 5.8803×10⁵⁹.
**Status.** Sound; the count depends on the cell choice by a factor 1.35 to 1.91.

### F3 — shell capacity, N_cap(r) = 4πr²ℓ_P/v₀ = 24(r/ℓ_P)²
**Explanation.** The number of spation volumes a shell of thickness ℓ_P at radius r can hold, which grows as the area.
**Demonstration A.** r = R₀ (8.4×10⁻¹⁶ m): 6.4826×10⁴⁰; r = 1 nm: 9.1874×10⁵².
**Demonstration B (discrete against continuous).** For n shells of thickness ℓ_P the exact sum Σ24j² = 4n(n + 1)(2n + 1) is 8.012004×10⁹ for n = 10³ against 8n³ = 8.000000×10⁹ (ratio 1.001500 = 1 + 1.5/n + …); 8.000012×10¹⁸ against 8.000000×10¹⁸ for n = 10⁶ (ratio 1.000002). The cumulative capacity equals the displaced count 8(R/ℓ_P)³ in the continuum limit.
**Status.** Sound.

### F4 — the conserved-volume displacement, u(r) = Ω₀/(4πr²) = R₀³/(3r²)
**Explanation.** If the excluded volume must be carried outward through every shell, the radial displacement is the volume divided by the shell area. This is the origin of 1/r² in the construction: conserved volume spread over a sphere.
**Demonstration A.** The surface integral of u over spheres of radius 10⁻¹⁵, 10⁻¹², 10⁻⁹ and 10⁻⁶ m divided by Ω₀ is 1.000000000000 each time.
**Demonstration B.** u(R₀) = 2.8000×10⁻¹⁶ m = R₀/3; u(1 nm) = 1.9757×10⁻²⁸ m; u(1 µm) = 1.9757×10⁻³⁴ m.
**Status.** Sound.

### F5 — the terminal radius, R_term = √(R₀³/(3ℓ_P)), where u(R_term) = ℓ_P
**Explanation.** The radius at which the displacement per shell falls to one spation thickness. For N_b baryons the volumes add, so R_term(N_b) = R_term(1)√N_b.
**Demonstration A.** R_term = 3.4963×10⁻⁶ m; u(R_term) = 1.6163×10⁻³⁵ m = ℓ_P.
**Demonstration B [ext masses].** Earth (N_b = 3.570×10⁵¹): 2.089×10²⁰ m; the Sun (N_b = 1.189×10⁵⁷): 1.206×10²³ m (3.9 Mpc); R_term equals R_CMB at N_b = 7.425×10⁶⁴.
**Status.** Sound. What R_term means physically is not stated in the paste.

### F6 — strain energy of the displacement field
**Explanation.** For u_r = Ω₀/(4πr²) the strains are ε_rr = −2Ω₀/(4πr³) and ε_θθ = ε_φφ = Ω₀/(4πr³), trace zero. With a shear modulus μ the energy density is 6μ(Ω₀/4π)²/r⁶ and the total outside R₀ is 8πμ(Ω₀/4π)²/R₀³, finite. A bulk term K(∇·u)² is zero.
**Demonstration A.** Total shear energy outside R₀ (μ = 1): quadrature 1.655142×10⁻⁴⁵ against the closed form 1.655142×10⁻⁴⁵ (relative −1.6×10⁻¹²).
**Demonstration B.** The bulk term: worst |∇·u|/(u/r) = 9.8×10⁻¹³, zero to rounding.
**Status.** Sound for the shear energy (finite self-energy, as in the paste); issue for the paste's K(∇·u)² form, which vanishes here.

### F7 — the stated density, ρ_s(r) = ρ₀(1 − Ω₀/(4πr³))
**Explanation.** The paste writes the spation density as reduced by Ω₀/(4πr³) = R₀³/(3r³). For an incompressible medium the density is constant outside the source (F6 B), so the statement does not follow from the displacement. It also fails a conservation test: the volume it removes diverges.
**Demonstration A.** ρ/ρ₀ = 0.666667 at r = R₀, 0.958333 at 2R₀, 0.999667 at 10R₀.
**Demonstration B.** The volume removed between R₀ and r_max is Ω₀ ln(r_max/R₀): 2.303Ω₀ at 10R₀, 6.908Ω₀ at 10³R₀, 13.816Ω₀ at 10⁶R₀. The displaced volume is Ω₀; the integral grows without bound.
**Status.** Issue.

### F8 — the stated index, n(r) = 1 + αΩ₀/r
**Explanation.** The paste writes an index of refraction proportional to Ω₀/r, to be matched to the weak-field g₀₀ by choosing α. As a dimension check, Ω₀/r has the units of an area, so α must have units m⁻². Matching n − 1 = 2ϟ/r for a body of N_b baryons requires αN_bΩ₀ = 2N_bϟ_b, i.e. α = 2ϟ_b/Ω₀ with ϟ_b the koppa per baryon.
**Demonstration A.** α = 2ϟ_b/Ω₀ = 1.0004×10⁻⁹ m⁻² (ϟ_b = 1.2419×10⁻⁵⁴ m, engine): not dimensionless, not derived.
**Demonstration B.** The baryon census of the Sun from ϟ_Sun/ϟ_b = 1.1890×10⁵⁷ against M_Sun/m_p = 1.1892×10⁵⁷ [ext 1.989×10³⁰ kg] (relative −1.2×10⁻⁴): the census route to N_b reproduces the mass route.
**Status.** Issue (α undefined in the paste; derivation absent).

### F9 — the Gauss form, ∇·g = −4πGρ ⟺ ∇·u = Ω₀δ(r)
**Explanation.** Both fields are inverse-square, sourced by a quantity that crosses every closed surface unchanged: the flux of g is 4πc²ϟ = 4πGM; the flux of u is Ω₀. The correspondence is of form; the ratio u/g is a constant of dimension s² (displacement over acceleration).
**Demonstration A.** The flux of g = c²ϟ/r² (the Sun's ϟ) through spheres of radius 10⁶, 10⁹ and 10¹² m: 1.667684×10²¹ m³/s² each = 4πc²ϟ.
**Demonstration B.** For one baryon u/g = Ω₀/(4πc²ϟ_b) = 1.770101×10⁻⁹ s² at 10⁻¹², 10⁻⁹ and 10⁻⁶ m (the same at each radius).
**Status.** Sound as a statement of form; it does not by itself give the force law.

## G. Koppa structures

### G1 — v = c√(ϟ/r) = c/k(r), with k(r) = k₀√(r/R) and ϟ = R/k₀²
**Explanation.** One relation written three ways: the speed at radius r, the speed ratio k = c/v, and the reference pair (R, k₀) from which ϟ follows. The paste's v = (cϰ)√(R/r) corresponds to the second with k = k₀ the speed ratio at R, written c/k₀ (the product ck reads as c divided by k with this definition).
**Demonstration A.** Hydrogen (R = a₀, k₀ = 1/α): v(a₀) = 1.0000αc = 2.18769×10⁶ m/s; v(4a₀) = 0.5000αc; ϟ = α²a₀ = 2.81794×10⁻¹⁵ m = r_e.
**Demonstration B.** The Sun (ϟ = 1476.5989 m): surface speed 436,758.1 m/s (engine value 436,762 m/s); at 1 AU, 29.784 km/s, the Earth's orbital speed.
**Status.** Sound.

### G2 — z k² = 1 with z the spectroscopic shift Δλ/λ
**Explanation.** With z measured by spectroscopy and k = c/v from an independent determination of the speed, the relation is a test: it says ϟ = zR, the surface circular speed is c√z, and the baryon census follows as N_b = ϟ/ϟ_b, with no G and no orbit.
**Demonstration A.** Sirius B: z = 80.42 km/s/c = 2.6825×10⁻⁴ [search result, Barstow et al. 2005]; with R = 5.84×10⁶ m [B]: v = c√z = 4910.1 km/s, ϟ = zR = 1566.6 m, N_b = 1.261×10⁵⁷ = 2.110×10³⁰ kg = 1.061 solar masses (dynamical 1.018 ± 0.011).
**Demonstration B.** The Sun: the predicted shift c·z = 636.30 m/s; the error propagation δϟ/ϟ = δz/z + δR/R: a 50 m/s uncertainty on 636 m/s [B] gives 7.9% on ϟ, against about 10⁻¹⁰ for GM from the orbits [B].
**Status.** Sound; the precision limit is observational.

### G3 — modified Kepler force, a = −(c²ϟ/r²)(1 + βϟ/r)
**Explanation.** In the orbit variable w = ϟ/r the force gives w″ + w(1 − βϟU) = U with U = 1/(a(1 − e²)): a linear oscillator whose frequency is reduced, so the apsides advance by 2π(1/√(1 − βϟU) − 1) ≈ πβϟU per orbit. For β = 6 that is the Mercury value.
**Demonstration A.** Mercury, β = 6: advance 5.018579×10⁻⁷ rad/orbit by integration; exact 2π(1/√(1 − βϟU) − 1) = 5.018579×10⁻⁷; first order πβϟ/(a(1 − e²)) = 5.018578×10⁻⁷.
**Demonstration B.** Circular-orbit speed v² = c²x(1 + 6x), x = ϟ/r: v = c at x = 0.333333 (r = 3ϟ); the stability margin 1/(1 + 6x) is 0.9940 at x = 10⁻³, 0.3333 at x = 1/3, 0.0164 at x = 10: positive everywhere.
**Status.** Sound; supplement (the force law is stated in the paste only as "1/r² and 1/r³"; the coefficient 6 is the value Mercury requires).

## H. Implicit

### H1 — attenuation through a body, exp(−τ), and the linearity of the force in mass
**Explanation.** The paste describes self-shadowing in words: a front particle eclipses a rear one, so the force is proportional to mass only if the body is nearly transparent. As algebra: a flux crossing a column Σ with cross-section per unit mass σ/m is reduced by exp(−τ), τ = (σ/m)Σ; the force per unit mass is linear only for τ ≪ 1, with the surviving fraction (1 − e^{−τ})/τ.
**Demonstration A.** τ = 10⁻¹⁴: 1.0000000000; τ = 0.1: 0.9516258196; τ = 1: 0.6321205588; τ = 10: 0.0999954600.
**Demonstration B [ext mean density 5515 kg/m³].** The column through the Earth Σ = 7.027×10¹⁰ kg/m²; τ < 10⁻¹³ requires σ/m < 1.42×10⁻²⁴ m²/kg; τ = 1 would need σ/m = 1.42×10⁻¹¹ m²/kg.
**Status.** Implicit; this is the structure behind the composition-independence requirement in the evaluation of the model.

---

## Notes on the whole set
- **Sound as written:** A1–A5, B1, B3, C1, C3, D1, D2, D4, E1, E2, F1–F5, F9, G1–G3 (G3 as a supplement).
- **Needs a stated convention:** B2 (T is minus the momentum flux), D3 (the sign of Φ), G1 (k as the speed ratio at R).
- **Issues in the paste:** E3 (the area statement conflates two things), F6 (the bulk term vanishes), F7 (the density statement is inconsistent with the premise), F8 (α undefined and dimensioned).
- **Supplements** (structures the argument needs and the paste does not write): B4's coherence distance, B5's discrete dispersion, C2's drag result, D4's delay form, F9's ratio, G3's stability margin.
- **Relation to the other files.** The evaluation of the displacement construction and the 1/r² + 1/r³ law is in `PASTE_MATH_EVALUATION_2026-10-07.md`; the history is in `HISTORICAL_STRUCTURES_AND_THE_SPATION_2026-10-07.md`.
