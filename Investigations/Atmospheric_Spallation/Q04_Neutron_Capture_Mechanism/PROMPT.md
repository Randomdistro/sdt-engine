# Q04: Neutron Capture Mechanism — Investigation Prompt

> **Classification**: Theoretical derivation with archival verification
> **Prerequisites**: Q01, Q02, nuclear construction grammar, INV 12
> **Output format**: Geometric step-by-step mechanism with cross-section
> prediction rule

---

## 1. Background

Neutron capture is the inverse of neutron ejection. A free neutron
approaches a nucleus, merges with it, and the resulting compound emits
a gamma ray to shed the excess energy. The reaction notation is (n,γ).

This is the dominant mechanism for producing EC isotopes (INV 12 §11):
7 out of 9 closure EC isotopes are created by neutron capture on stable
parents. The SDT codebase has established the CONSEQUENCE of neutron
capture (grammar change, EC requirement) but has NOT described the
MECHANISM — the geometric process by which a free neutron merges with
a nuclear scaffold.

Neutron capture is geometrically unique because the neutron has NO ℓ=1
wake (no charge). It approaches the nucleus without any long-range
repulsion. The only long-range coupling is the ℓ=2 (magnetic) wake,
which is attractive for certain orientations and repulsive for others.
At short range, the ℓ≥3 (structure) coupling takes over and pulls the
neutron into the scaffold.

The mystery: **why do some nuclei capture neutrons 10⁶ times more
readily than others?** Gd-157 has σ_cap = 254,000 barns. Pb-208 has
σ_cap ≈ 0.0005 barns. Both are stable. SDT must explain this 10⁹
dynamic range from geometry alone.

---

## 2. The Core Question

**What is the geometric process by which a free neutron merges with a
nuclear scaffold, and what geometric property of the scaffold determines
the capture cross-section?**

Sub-questions:

1. How does the neutron's displacement volume interact with the target's
   convergence gradient as it approaches?
2. Without an ℓ=1 wake (no Coulomb barrier), what determines whether
   the neutron is captured vs scattered?
3. Where in the scaffold does the captured neutron attach? Does it
   fill a specific vacancy, or does it add to the outermost shell?
4. What determines the prompt gamma energy — is it the scaffold
   rearrangement energy from the grammar transition?
5. Why does the cross-section follow a 1/v law at low energies?
   What is the SDT geometric explanation for this scaling?
6. What geometric property creates the resonances (sharp peaks in
   σ_cap at specific neutron energies)?
7. Why are magic-number nuclei (shell closures) nearly transparent
   to neutrons? What is "full" in grammar terms?

---

## 3. Methodology

### Phase A: Describe the approach geometry

The free neutron at thermal energy has k ≈ 1.36 × 10⁵. This means its
movement budget is almost entirely circulation (v_circ ≈ c) with very
little translational velocity (v ≈ 2200 m/s ≈ 7.3 × 10⁻⁶ c).

1. At this k-number, the neutron is a slowly drifting, rapidly
   circulating W=3 torus. Its displacement volume is V_disp ≈ 1.84 × 10⁻⁵⁸ m³
   (same as proton by mass similarity).

2. As it approaches the target nucleus (radius R ≈ 4–7 fm), it enters
   the target's convergence gradient. Since the neutron has no ℓ=1 wake,
   there is no Coulomb repulsion — but also no Coulomb ATTRACTION.

3. The convergence gradient of the target acts isotropically (ℓ=0 term).
   Does this pull the neutron inward (gravitational analogue at nuclear
   scale)? Compute the convergence pressure differential across the
   neutron's displacement volume at r = 10 fm, 5 fm, 3 fm.

4. The ℓ=2 (magnetic) coupling between the neutron (μ = −1.913 μ_N)
   and the target (various μ) provides orientation-dependent force.
   For thermal neutrons, is this coupling strong enough to steer the
   approach? Compute the magnetic interaction energy at r = 5 fm for
   representative targets.

### Phase B: Describe the scaffold insertion

Once the neutron reaches the nuclear surface:

1. The ℓ≥3 (structure) coupling activates. This is the short-range
   force that holds the scaffold together. At the nuclear surface,
   a neutron approaching an "open" position (a scaffold vacancy or
   an available bonding site) experiences a strong inward pull.

2. SDT must describe WHAT an "open position" is in grammar terms:
   - A deuteron with only one scaffold bond (can accept a neutron
     to become a triton)?
   - A triton's n_o position (already occupied — NOT available)?
   - A vacant position in the next unfilled shell?
   - The surface of the nucleus where an additional block can attach?

3. The neutron attaches to the scaffold. This changes the grammar:
   - If neutron → added to a deuteron: d → t (Δn_tri = +1, Δn_deu = −1)
   - If neutron → creates a new block: depends on what forms
   - Compute the grammar change for specific examples:
     Ca-40(n,γ)Ca-41, Cd-108(n,γ)Cd-109, Xe-126(n,γ)Xe-127

4. The attachment releases energy (the binding energy of the new neutron,
   which equals S_n of the product). This energy is emitted as prompt
   gamma radiation. Compute: does the gamma energy equal the grammar
   transition energy?

### Phase C: Cross-section from geometry

The central challenge: predict σ_cap from scaffold geometry.

Hypothesis 1: **σ_cap ∝ (number of available attachment sites)**
- Nuclei with many open positions have large σ_cap
- Nuclei with closed shells (all positions filled) have small σ_cap
- Test: correlate σ_cap with the number of unfilled positions in the
  current shell

Hypothesis 2: **σ_cap ∝ 1/(scaffold rigidity)**
- Rigid scaffolds (high deformation resistance) cannot accommodate
  an additional neutron easily
- Flexible scaffolds (high triton fraction, many n_o) can rearrange
  to accept a neutron
- Test: correlate σ_cap with triton fraction or nuclear softness β₂

Hypothesis 3: **σ_cap ∝ n_o (number of open neutrons that can mediate)**
- The triton's open neutron n_o acts as a "docking antenna" — its
  dangling, paramagnetic end couples magnetically (ℓ=2) to the
  approaching free neutron
- More n_o → larger effective capture radius
- Test: correlate σ_cap with n_o count

Hypothesis 4: **σ_cap governed by grammar-matching**
- The neutron is captured only if the resulting product has a valid
  grammar state
- If the product would have n_tri < 0 or n_deu < 0, capture is
  geometrically forbidden
- This is always satisfied for neutron addition (it always increases
  n_tri), so this doesn't explain the dynamic range

For EACH hypothesis:
1. Compute the predicted σ_cap ordering for 20 representative nuclides
2. Compare against measured σ_cap from ENDF/B-VIII.0
3. Compute rank correlation (Spearman ρ)
4. Identify which hypothesis best explains the 10⁹ dynamic range

### Phase D: The 1/v Law

At low energies, σ_cap ∝ 1/v for most nuclides. In SDT:

1. The neutron's k-number at low energy is very large (k → ∞ as v → 0)
2. High k = nearly all movement budget is circulation
3. A slowly drifting, rapidly circulating torus spends more TIME
   near each potential capture site
4. The capture probability per unit time is constant (set by the ℓ≥3
   coupling rate), so more time near the target → higher probability
5. Time near target ∝ 1/v, hence σ ∝ 1/v

Formalise this argument:
- Define the "interaction time" τ_int = d/v, where d is the effective
  interaction diameter
- Define the "capture rate" Γ_cap = ℓ≥3 coupling rate at surface
- Then σ = Γ_cap × τ_int × (geometric area) = Γ_cap × (d/v) × πR²
- This gives σ ∝ 1/v with a proportionality constant that depends
  on Γ_cap and R

Compute Γ_cap for Gd-157 and Pb-208. Is the 10⁹ ratio in σ_cap
explainable by a 10⁹ ratio in Γ_cap? Or is d (effective interaction
diameter) also target-dependent?

### Phase E: Resonance structure

At specific neutron energies, σ_cap shows sharp peaks (Breit-Wigner
resonances). In conventional physics, these correspond to compound
nucleus states whose energy matches the neutron kinetic energy plus
binding energy.

SDT must describe resonances as:
- **Mode-matching**: The neutron's circulation frequency matches a
  scaffold vibration mode at specific kinetic energies
- When mode-matched, the neutron's torus locks into phase with the
  scaffold oscillation → capture probability spikes
- Between resonances, the neutron is phase-mismatched → bounces off

Test:
1. For a nucleus with well-measured low-lying resonances (e.g., U-238
   with resonances at 6.67, 20.87, 36.68 eV), compute whether the
   resonance energies correspond to scaffold vibration frequencies
2. The scaffold vibration frequency can be estimated from the grammar:
   f_vib ≈ c / (circumference of torus chain at nuclear surface)
3. Does the resonance spacing match integer multiples of f_vib?

---

## 4. Required Outputs

1. **Step-by-step capture narrative**: Analogous to Q01's spallation
   narrative — minimum 8 steps from free neutron approach to prompt
   gamma emission

2. **Hypothesis test table**: For each of the 4 cross-section hypotheses,
   show the rank correlation against measured σ_cap for 20+ nuclides

3. **1/v derivation**: Formal SDT derivation of the 1/v law from
   k-number and interaction time geometry

4. **Magic number explanation**: Specific geometric explanation for
   why shell-closed nuclei have anomalously small σ_cap

5. **Giant cross-section explanation**: Specific geometric explanation
   for why Gd-157, Xe-135, Sm-149 have anomalously large σ_cap —
   what grammar property do they share?

6. **Resonance interpretation**: Whether resonance energies can be
   mapped to scaffold vibration modes for at least one test nucleus

---

## 5. Success Criteria

- [ ] The capture mechanism uses only SDT geometric concepts
- [ ] At least one hypothesis correctly orders σ_cap for ≥15/20 nuclides
- [ ] The 1/v law is derived from SDT first principles
- [ ] The 10⁹ dynamic range between Gd-157 and Pb-208 is explained
      by a specific, identifiable geometric property
- [ ] Magic number transparency is explained without invoking shell
      model quantum numbers
- [ ] The narrative connects to INV 12's finding: "neutron capture
      creates the need for EC; EC fulfills that need"
