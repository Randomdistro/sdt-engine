# E29: Deuteron Binding from Occlusion Geometry — Investigation Prompt

> **Classification**: Pure calculation
> **Experiment file**: Experiments/E29_Deuteron_Binding.md
> **Engine function**: law_III::F_occlusion
> **Target**: Reproduce B_d = 2.224 MeV from geometry alone

---

## 1. The Question

The deuteron (p+n) is the simplest nuclear system. SDT's occlusion force is:

$$F = \frac{\pi}{4} P_{\text{eff}} \frac{R_1^2 R_2^2}{r^2}$$

Can this reproduce the measured binding energy of 2.22457 MeV when applied to a proton and neutron at their measured separation of ~2.14 fm?

## 2. Methodology

### Step 1: Identify the correct radii

The proton has R_wake = R_p = 0.8414 fm (the charge radius, confirmed by W+1 conjecture). The neutron has no charge radius — it is overall neutral. What radius does the neutron present for occlusion purposes?

Three candidates:
- **R_n = R_p** (same W=3 topology → same wake radius): 0.8414 fm
- **R_n = 4ℏ/(m_n c)** (W+1 applied to neutron mass): 0.8401 fm (0.15% less than proton)
- **R_n = 0** (no ℓ=1 wake → no occlusion): This would give zero binding → WRONG

The neutron MUST have a non-zero wake radius for occlusion. SDT's position: the neutron has the same W=3 trefoil topology as the proton. Its ℓ≥3 wake IS the nuclear interaction. The ℓ=1 wake (charge) is absent, but the ℓ≥3 wake (structure) provides the occlusion cross-section.

Hypothesis: use R_n_eff ≈ R_p for the nuclear occlusion radius (same topology → same effective size for ℓ≥3 wake).

### Step 2: Compute the binding energy

$$E_B = \int_{r_0}^{\infty} F(r) \, dr = \frac{\pi}{4} P_{\text{eff}} R_p^2 R_n^2 \int_{r_0}^{\infty} \frac{dr}{r^2}$$

$$E_B = \frac{\pi}{4} P_{\text{eff}} \frac{R_p^2 R_n^2}{r_0}$$

With R_p = R_n = 0.8414×10⁻¹⁵ m and r_0 = 2.14×10⁻¹⁵ m:

Compute this numerically and compare to 2.224 MeV.

### Step 3: If the simple occlusion gives the wrong answer

Possible corrections:
1. The neutron's effective radius for ℓ≥3 occlusion differs from R_p
2. The occlusion force includes higher-order terms (not just 1/r²)
3. The deuteron's loosely-bound state means quantum zero-point motion affects the average separation
4. P_eff as calibrated from hydrogen (atomic scale) may need a nuclear-scale correction

### Step 4: Reverse engineering

If the formula doesn't give 2.224 MeV, invert:

$$R_{n,\text{eff}} = \sqrt{\frac{4 r_0 E_B}{\pi P_{\text{eff}} R_p^2}}$$

What R_n_eff is required? Is it physically reasonable?

## 3. Success Criteria

- [ ] Binding energy computed from SDT occlusion formula
- [ ] If match (within 10%): report as confirmed
- [ ] If no match: identify and quantify the discrepancy
- [ ] Determine whether the discrepancy reveals the ℓ≥3 nuclear wake contribution
- [ ] Compare the SDT approach to standard Yukawa potential (conceptual mapping)
