# E24: Mercury Precession from k-Hierarchy — Investigation Prompt

> **Classification**: Pure calculation
> **Experiment file**: Experiments/E24_Mercury_Precession.md
> **Engine function**: bridge::v_orbital, bridge::k_Sun
> **Target**: Reproduce 42.98"/century from SDT pressure gradient

---

## 1. The Question

GR explains Mercury's anomalous perihelion precession as spacetime curvature near the Sun. SDT must reproduce the same 42.98"/century from the k²-gradient (convergence pressure profile) without invoking curved spacetime.

## 2. Methodology

### Step 1: The SDT velocity profile

From bridge namespace: v(r) = (c/k)√(R_Sun/r)

This is Keplerian at large r but incorporates the k-factor. The precession arises when the effective potential deviates from pure Keplerian at small r.

The key: near the Sun, the convergence gradient introduces a correction to the effective potential. This correction has the same functional form as GR's Schwarzschild correction because BOTH arise from the same velocity-field profile.

### Step 2: Derive the correction

The SDT effective potential for radial motion:

$$V_{\text{eff}}(r) = -\frac{c^2 R}{k^2 r} + \frac{L^2}{2r^2} - \frac{c^2 R L^2}{k^2 r^3 c^2}$$

The last term is the SDT correction (from the k-gradient modifying the angular momentum coupling). This is identical in form to the GR Schwarzschild correction:

$$V_{\text{GR}}(r) = -\frac{GM}{r} + \frac{L^2}{2r^2} - \frac{GM L^2}{r^3 c^2}$$

Since GM = c²R/k² (bridge law), these are ALGEBRAICALLY IDENTICAL.

### Step 3: Compute the precession

$$\delta\phi = \frac{6\pi c^2 R_{\text{Sun}}}{k^2 c^2 a(1-e^2)} = \frac{6\pi R_{\text{Sun}}}{k^2 a(1-e^2)}$$

Substitute:
- R_Sun = 6.957 × 10⁸ m
- k² = 686.3² = 471,008
- a = 5.7909 × 10¹⁰ m  
- e = 0.2056
- (1−e²) = 0.9577

$$\delta\phi = \frac{6\pi \times 6.957 \times 10^8}{471008 \times 5.7909 \times 10^{10} \times 0.9577}$$

Convert to arcseconds per century (multiply by 415 orbits/century and 206265 arcsec/radian).

### Step 4: Verify the algebraic identity

Show explicitly that the SDT precession formula and the GR formula give the same number because GM_equiv = c²R/k² maps one to the other exactly.

## 3. Critical Discussion

The result will NECESSARILY match GR, because the bridge law ensures GM = c²R/k². The SDT contribution is not a new prediction — it's a demonstration that the k-gradient formalism reproduces the same effective potential.

The DISTINGUISHING test would be: does SDT predict a different precession rate for objects with different internal structure at the same orbit? (GR says no — equivalence principle. SDT might say yes if the k-coupling depends on the orbiting body's own displacement field.)

## 4. Success Criteria

- [ ] Precession computed from SDT parameters (k, R_Sun, orbital elements)
- [ ] Result matches 42.98"/century to within 0.1"
- [ ] Algebraic equivalence to GR formula demonstrated
- [ ] Discussion of WHERE SDT and GR could diverge (if anywhere)
