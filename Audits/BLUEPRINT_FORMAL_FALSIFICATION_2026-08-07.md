# Blueprint Formal Falsification — 2026-08-07

## Object tested

This audit tests the supplied *Comprehensive Chronological Distillation and Mathematical Formalization of Spatial Displacement Theory (SDT) — Master Architecture Blueprint* (the blueprint) against its own equations and the current engine. It extends the first adversarial audit and does not modify canon.

The admissibility rule is internal: a statement fails when it is dimensionally undefined, numerically contradicts its own formula, omits a condition required to evaluate it, or is presented as a derivation despite being an input or definition. No competitor theory is used as a rejection criterion.

## Initial conditions required

Before the blueprint can produce a calculation, these have to be supplied with units, values, domains, and evolution or boundary laws.

| Symbol or object | Required for | Status |
|---|---|---|
| E(V_excl) and state variables | P_conv = -∂E/∂V_excl | absent |
| A_excl, ΔP_eff, C, and ds measure | torus work integral | absent |
| P(x,t), PDE, initial and boundary data | beta shear and neutrino flux | absent |
| eta_slip and each A_topo,k | heat rate | unspecified; eta_slip << 1 is a free magnitude |
| N in z = N a0 alpha²/R | optical compactness | ambiguous: shell, knot, and baryon count differ |
| K_parallel, K_perp, admissible paths A | transport and mass-gap minimisation | absent |

Absent these conditions, the equations define neither an initial-value problem nor a prediction. An explanatory noun is not a substitute for a state variable and an evolution law.

## Reproducible arithmetic ledger

Using current values in Engine/include/sdt/laws.hpp:

| Quantity | Result | Consequence |
|---|---:|---|
| l_P / t_P | 299,792,812.04 m/s | differs from stored c by +1.181×10⁻⁶ relative |
| (a0/Rp)² | 3.955×10⁹ | not 10³⁹ |
| engine Sun baryon ledger | 1.189×10⁵⁷ | used below only when N means the stated knot count |
| blueprint z with that N | 4.815×10³³ | conflicts with engine solar depth 2.123×10⁻⁶ |
| N required to reproduce solar depth | 5.240×10¹⁷ | not an identified source count |

The area-ratio calculation is:

~~~powershell
$a0=5.29177210903e-11; $alpha=7.2973525693e-3; $rp=8.414e-16
[math]::Pow($a0/$rp,2)
~~~

## BF-01 — c = l_P/t_P is not a strict engine identity

### Claim falsified

The blueprint says the relay rate is defined strictly by c = l_P/t_P.

### Evidence and origin

The engine stores all three quantities as separate decimal literals. At their stored precision, l_P/t_P is 299,792,812.04 m/s while c is 299,792,458 m/s. The relative mismatch is 1.181×10⁻⁶. Rounding of t_P can explain the size of the mismatch, but a strict identity is not implemented.

### Recovery

Choose one independent dimensional seed: define t_P = l_P/c in source, or state the precision and uncertainty of an independently measured t_P. Three independently stored rounded values are not an exact derivation.

**Grade:** PARTIAL — a rounding repair is available; strictness is presently false.

## BF-02 — Phi is energy in the engine, not a rate

### Claim falsified

The blueprint calls Phi = N epsilon a throughput and then uses it as both a pressure source and a rate-carrying energy supply.

### Evidence and origin

The engine defines epsilon = u_CMB l_P³ in joules and Phi = N epsilon in joules. Consequently P_conv = Phi/l_P³ has pressure units, and Law IV's mass relation is dimensionally valid. Phi is not watts, joules per second, or a flux.

The phrase “total throughput packet density” has no compatible unit. If N is a count then Phi is energy; if N is a density, the documented pressure formula requires an additional volume factor.

### Recovery

Name Phi an energy burden, retain N as a dimensionless shell count, and add a separate rate or flux variable with an explicit time scale wherever power is claimed. The time scale is an open closure, not a notation change.

**Grade:** NO RECOVERY in the blueprint as written.

## BF-03 — the blueprint omits Law IV's factor of three

### Claim falsified

The blueprint gives m = Phi V_disp/(l_P³ c²).

### Evidence and mechanism

The current engine's Law IV defines:

~~~text
m = Phi V_disp / (3 l_P³ c²)
~~~

It identifies the factor 3 as angular averaging and P_cf = P_conv/3. The blueprint formula returns exactly three times the engine mass for every nonzero volume. This is algebraic, not a tolerance issue.

### Recovery

Restore the denominator 3 and derive the angular average from a specified isotropic stress tensor. Without that derivation the factor is a premise, not an earned mechanism.

**Grade:** PARTIAL — the formula can be corrected, but its underlying average is not supplied by the blueprint.

## BF-04 — the claimed 10^39 surface-area hierarchy is arithmetically false

### Claim falsified

The blueprint asserts:

~~~text
F_nuclear/F_gravity ~ (a0/Rp)² ~ 10^39.
~~~

### Counterexample

With the blueprint's own radii:

~~~text
(5.29177210903×10⁻¹¹ / 8.414×10⁻¹⁶)² = 3.955462309×10⁹.
~~~

The displayed area ratio is about thirty orders of magnitude below the claimed result. Cancelling 4pi is valid; it does not create the missing thirty orders.

### Origin of error

An atomic-to-proton geometric ratio was conflated with a claimed force ratio. No stated mapping supplies the missing dimensions or factors.

### Recovery

Withdraw the 10^39 conclusion from this equation. A replacement must define the two forces, participating areas, pressure at each interface, and every count or transfer factor before a ratio is computed.

**Grade:** NO RECOVERY for the stated equation.

## BF-05 — F_CMB/A_topo has the wrong dimensions

### Claim falsified

The blueprint defines P_effective = F_CMB/A_topo.

### Evidence and origin

Engine law_II::F_CMB = c u_CMB/4 has units W/m², despite the symbol F. Dividing it by an area yields W/m⁴, not pascals. If F_CMB is instead intended to be a force, the blueprint must define that force and its collecting surface; neither is supplied.

### Recovery

Use pressure directly, or derive a force from pressure times a declared area. The transfer from cosmic flux to occlusion pressure then needs time, momentum, and angular-coupling laws.

**Grade:** NO RECOVERY in the current formula.

## BF-06 — the inertial anisotropy does not model acceleration

### Claim falsified

The blueprint says the expression below is anisotropy “under an acceleration vector v” and establishes phase resistance under acceleration while preserving zero drag during coasting:

~~~text
dPhi/dOmega = Phi/(4pi) [1 + v·n_hat/c].
~~~

### Evidence and mechanism gap

v has velocity units, not acceleration units. The expression changes at constant nonzero velocity and contains no acceleration, derivative, memory, or phase-lag variable. Its angular integral remains Phi because the dipole term integrates to zero; that neither derives force nor cancels directional stress. No equation maps the angular distribution to a net force proportional to acceleration.

### Recovery

Define local state, an update rule, and a response kernel with a time scale. Demonstrate that uniform velocity is a stationary zero-force solution and that changing velocity yields the stated force. The current distribution cannot establish both claims.

**Grade:** NO RECOVERY in the blueprint.

## BF-07 — torus, beta-decay, and Möbius equations are underdetermined

### Claim falsified

The blueprint presents the torus work, beta-shear threshold, decay partition, winding integral, mass-gap minimum, and anisotropic flux as mathematical formalisation of mechanisms.

### Evidence and origin

- V_tube = 2pi a0 A_excl has valid dimensions but no definition or calculation of A_excl.
- E_torus = ∮ Delta P_eff dA ds becomes an energy only after a surface measure and contour-to-surface map are supplied; both are absent.
- grad P >= P_conv/l_P has matching units but no field equation for P(x,t), so it cannot locate a shear event or predict decay rate.
- W_Q = W_retained + W_e + W_nu is accounting notation. Defining retained work as residual makes it true for any partition, so it predicts no spectrum or branching fraction.
- min over Gamma in A has no admissible set, boundary conditions, or pressure field. K_perp << K_parallel has neither numerical values nor units.

### Recovery

For each route, provide state variables, governing equations, domain, initial and boundary conditions, dimensional coefficients, and an output observable not used as an input. Register rejection thresholds before fitting coefficients.

**Grade:** NO RECOVERY in the blueprint; these are research programmes, not predictive equations.

## BF-08 — eta_slip is free and the heat-rate equation fails units

### Claim falsified

The blueprint calls this a derived thermal output:

~~~text
Qdot_slip = eta_slip Phi Sum[A_topo,k] (1 - c_local/c_infinity).
~~~

### Counterexample

Under the engine definition [Phi] = J and [A_topo] = m², the right side is J m², not watts. There is no division by time or area normalisation. Further, eta_slip << 1 has neither a value nor a derivation. Any desired power can be selected through it, so it is a free calibration until independently fixed.

### Recovery

Introduce a dimensionally valid incident flux and interaction area, then derive eta_slip from microdynamics or label it CALIBRATED(1) and exclude it from prediction counts. Test the one fixed value against independent thermal observables in at least two systems.

**Grade:** NO RECOVERY in the blueprint.

## BF-09 — the optical compactness formula contradicts the engine if N is a knot count

### Claim falsified

The blueprint defines z = N a0 alpha²/R_surface, describes N as a body’s topological knot count, and uses this for stellar optics.

### Counterexample and initial-condition ambiguity

Since a0 alpha² = r_e, the formula is z = N r_e/R. The engine Sun baryon ledger is 1.189×10^57. Taking the stated knot count to be that count gives z = 4.815×10^33. The engine solar depth is koppa_Sun/R_Sun = 2.123×10^-6. The discrepancy is about 2.27×10^39.

Reproducing solar depth requires N = 5.240×10^17, which has no blueprint mechanism. If N is not the stated baryon or knot count, its definition and body relation are missing.

The refractive index is frequency-independent as written: neither z nor n(r) = (1-z)^-2 contains frequency. It cannot alone produce a claimed chromatic effect.

### Recovery

Define N unambiguously, derive it from independent body data, and reproduce compactness without reusing the target. Add a dispersion relation n(r,omega) before claiming chromatic predictions. Reconcile the profile with the already documented domain and inverse failure before applying it below z = 1.

**Grade:** NO RECOVERY for the stated stellar application.

## BF-10 — alpha/Koppa terminology and derivation status drift

### Claim falsified

The blueprint calls the fine-structure constant “Koppa, alpha” and presents r_e = a0 alpha² as a derivation of the electronic boundary.

### Evidence and origin

The repository’s current notation distinguishes alpha (empirical atomic anchor), k = c/v (dimensionless gear), and koppa/Om (length). It stores a0, alpha, and r_e as validation anchors. The relation is therefore a correspondence among inputs, not a derivation of r_e. The engine explicitly classifies the analogous g_electron = r_e m_e c/hbar = alpha relation as a definitional identity that fails the delete test.

### Recovery

Use current terms and label this relation IDENTITY/known-match until alpha or a0 is derived independently from topology. Do not use the same measured quantities as both premise and predicted result.

**Grade:** PARTIAL — numerical relation valid; claimed provenance false.

## Corrected standing and next instrument

The blueprint contains four direct formal exclusions (BF-03, BF-04, BF-05, BF-08), two incompatible or incomplete mechanism claims (BF-06, BF-09), and four definitions, correspondences, or underspecified research programmes (BF-01, BF-02, BF-07, BF-10). It is not a closed mathematical model.

The next productive instrument is one narrowly specified mechanism with:

1. state variables and SI dimensions;
2. initial and boundary conditions;
3. no hidden coefficient or an explicit calibration ledger;
4. a deterministic solver validated on a known analytic case; and
5. a pre-registered observable not used in the derivation.

The thermal-slip or optical route is unsuitable until BF-08 or BF-09 is repaired. Until then, numerical agreement from these routes is not admissible evidence.

## Audit limitations

- This is a formal audit of the supplied blueprint and current engine source, not a global judgement of all SDT investigations.
- The Sun counterexample takes “topological knot count” at its stated face value; a different meaning of N must be supplied before a different calculation is assessed.
- No external data or theory-dependent fitting machinery was used.

