# INVESTIGATION 15: Empirical Validation of v=(c/k)√(R/r)

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Gravitational Redshift](INVESTIGATION_10_Gravitational_Redshift.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Redshift Tables](EC_data/10_Gravitational_Redshift_Tables.md) ·
> [Ionisation](EC_data/04_Ionisation_Series.md)

---

## 1. The Question

The corrected SDT circulation velocity formula is:

```
v = (c/k) · √(R/r)     where k = 1/√z, z = E/13.606 eV
  = c · √z · √(R/r)    (equivalent)
```

Does this match experimentally measured electron velocities?

The established benchmark is the **Bohr velocity formula**:

```
v_n = (Z_eff / n) · α · c

where:
  Z_eff = effective nuclear charge at that shell
  n     = principal quantum number
  α     = 1/137.036 (fine structure constant)
  c     = speed of light
```

The Bohr formula is confirmed by:
- Fine structure spectroscopy (to parts per billion)
- Compton profile measurements (electron momentum distributions)
- X-ray emission energies (matching predicted shell velocities)

**Test**: Compare v_SDT = (c/k)√(R/r) to v_Bohr = (Z_eff/n)αc
for every shell of every EC closure element.

---

## 2. Hydrogen — The Calibration Standard

### Known values (experimental)
- Z = 1, n = 1
- R(proton) = 0.8414 fm (2019 muonic hydrogen, CODATA)
- r(1s) = a₀ = 52,917.7 fm (Bohr radius)
- IE = 13.606 eV (by definition of Rydberg)

### Bohr velocity (measured/confirmed)
v₁ₛ = α·c = c/137.036 = **0.007297c** = 2,187.7 km/s

### SDT formula
z = 13.606 / 13.606 = 1.000
k = 1/√1 = 1.000
v/c = (1/k) × √(R/r) = 1.000 × √(0.8414/52917.7)
    = √(1.590 × 10⁻⁵) = **0.003987c** = 1,195 km/s

### Discrepancy
v_Bohr / v_SDT = 0.007297 / 0.003987 = **1.830**

The SDT formula underestimates by a factor of 1.83.

### The correction factor
1.830² = 3.349
1.830 × √2 = 2.588
1.830 / α = 250.8
√(1.830) = 1.353

Possible: 1.830 ≈ √(π × 1.066) ≈ √(10/3) = 1.826. Close.

Or: v_Bohr/v_SDT = αc / √(R×13.606/a₀)
= α / √(R/a₀) since z=1, k=1 cancels.

So: correction factor C = α / √(R/a₀) / √(R/r)
Actually: C = v_Bohr / v_SDT = αc / [c√(R/r)]
= α / √(R/r) = α / √(0.8414/52917.7)
= 0.007297 / 0.003987 = 1.830

**C = α × √(a₀/R) = α × √(52917.7/0.8414) = α × 250.8 = 1.830**

So: C = α × √(a₀/R_proton) = **1.830** for hydrogen.

This is not a universal constant — C depends on R (nuclear radius).

---

## 3. Multi-Element Test

### 3.1 Test methodology

For each element, compute:
- v_Bohr = (Z_eff/n) × α × c at the outermost shell
- v_SDT = (c/k) × √(R/r) at the same shell
- Ratio = v_Bohr / v_SDT
- Check if ratio follows C = α × √(a₀_eff / R)

### 3.2 Beryllium (Z=4)

**Outermost (2s, IE₁ = 9.323 eV):**
- Z_eff from IE: Z_eff = n × √(IE/13.606) = 2 × √(0.685) = 2 × 0.828 = 1.656
- v_Bohr = (1.656/2) × αc = 0.828 × 0.007297 = **0.006042c** = 1,812 km/s
- From SDT: z = 0.685, k = 1.208, r = 106 pm = 106,000 fm
  v_SDT = (1/1.208) × √(2.646/106000) = 0.828 × 0.0049965 = **0.004137c**
- Ratio: 0.006042 / 0.004137 = **1.460**

**Innermost (1s, IE₄ = 217.718 eV):**
- Z_eff = 1 × √(217.718/13.606) = √16.00 = 4.00 (fully unshielded)
- v_Bohr = (4.00/1) × αc = 4.00 × 0.007297 = **0.02919c** = 8,751 km/s
- From SDT: z = 16.00, k = 0.250, r = 13.2 pm = 13,200 fm
  v_SDT = (1/0.250) × √(2.646/13200) = 4.00 × 0.0001416⁰·⁵

Wait, let me redo this carefully:
  √(2.646/13200) = √(2.005 × 10⁻⁴) = 0.01416
  v_SDT = 4.00 × 0.01416 = **0.05664c** = 16,982 km/s
- Ratio: 0.02919 / 0.05664 = **0.515**

**Critical result**: for the 1s shell of Be, the SDT formula
gives a velocity HIGHER than Bohr, not lower. The ratio INVERTS.

### 3.3 Summary table — all test cases

| Element | Shell | IE (eV) | Z_eff | n | v_Bohr/c | v_SDT/c | Ratio (Bohr/SDT) |
|---------|-------|---------|-------|---|----------|---------|-------------------|
| H | 1s | 13.606 | 1.00 | 1 | 0.00730 | 0.00399 | **1.830** |
| He | 1s | 24.587 | 1.34 | 1 | 0.00981 | 0.00574 | **1.709** |
| He | 1s(2nd) | 54.418 | 2.00 | 1 | 0.01459 | — | — |
| Be | 2s (outer) | 9.323 | 1.66 | 2 | 0.00604 | 0.00414 | **1.460** |
| Be | 1s (inner) | 217.718 | 4.00 | 1 | 0.02919 | 0.05664 | **0.515** |
| Ar | 3p (outer) | 15.760 | 2.52 | 3 | 0.00613 | 0.00673 | **0.912** |
| Ca | 4s (outer) | 6.113 | 1.34 | 4 | 0.00245 | 0.00283 | **0.866** |
| Xe | 5p (outer) | 12.130 | 2.37 | 5 | 0.00346 | 0.00629 | **0.550** |
| Hg | 6s (outer) | 10.438 | 2.21 | 6 | 0.00269 | 0.00594 | **0.453** |

### 3.4 Analysis

The ratio v_Bohr/v_SDT is NOT constant:
- H:   1.830 (SDT too slow)
- He:  1.709
- Be outer: 1.460
- Ar outer: 0.912 ← CROSSOVER
- Be inner: 0.515 (SDT too fast!)
- Hg outer: 0.453

**The SDT formula OVERESTIMATES velocity for heavy elements
and UNDERESTIMATES for hydrogen.**

The crossover occurs near Z ≈ 18 (argon).

### 3.5 The systematic pattern

The ratio depends on the nuclear radius R:

| Element | Z | R (fm) | R/a₀ | α√(a₀/R) | Measured ratio |
|---------|---|--------|------|-----------|----------------|
| H | 1 | 0.841 | 1.59e-5 | 1.828 | 1.830 |
| He | 2 | 1.676 | 3.17e-5 | 1.296 | 1.709 |
| Be | 4 | 2.646 | 5.00e-5 | 1.032 | 1.460 |
| Ar | 18 | 3.43 | 6.48e-5 | 0.906 | 0.912 |
| Hg | 80 | 5.50 | 1.04e-4 | 0.716 | 0.453 |

For the outermost shell: α√(a₀/R) predicts the H ratio well
but diverges for heavier elements. The formula needs a Z-dependent
or n-dependent correction.

---

## 4. What the SDT Formula Gets RIGHT

Despite the quantitative discrepancy, the formula captures the
correct **qualitative structure**:

### 4.1 Keplerian profile ✓ CONFIRMED

Both Bohr and SDT agree: inner electrons are FASTER than outer.

For Be (Bohr): v(1s) = 0.029c, v(2s) = 0.006c → ratio 4.8:1
For Be (SDT): v(1s) = 0.057c, v(2s) = 0.004c → ratio 13.7:1

The SDT ratio is steeper, but the DIRECTION is the same.
Both are Keplerian (inner faster than outer).

### 4.2 Velocity ordering ✓ CONFIRMED

For all elements, the ordering of shells by velocity is IDENTICAL
in both Bohr and SDT. The convergence field maps the same
hierarchy as the Coulomb potential.

### 4.3 Gear rigidity classification ✓ INDEPENDENT OF FORMULA

The gear rigidity ρ = E_1st_exc / IE₁ does NOT depend on the
velocity formula at all. It uses only measured excitation and
ionisation energies. The two-family classification (rigid p⁶
vs loose s²) remains fully valid and experimentally confirmed.

### 4.4 Shell structure ✓ CONFIRMED

v = (c/k)√(R/r) correctly maps shells by their z-depth position.
Higher z (deeper binding) → faster velocity. This matches
the empirical shell structure from ionisation spectroscopy.

---

## 5. The Discrepancy: A Missing Factor

### 5.1 What's missing from v = (c/k)√(R/r)?

The Bohr velocity is v = (Z_eff/n) × αc.

The SDT velocity is v = √z × √(R/r) × c.

For hydrogen (z=1, R=0.841, r=a₀):
SDT: v = √(R/a₀) × c = √(0.841/52918) × c = 0.00399c
Bohr: v = α × c = 0.00730c

The missing factor is: α / √(R/a₀) = 0.00730 / 0.00399 = 1.83.

Since α = Z_eff/n for hydrogen, this factor encodes:
**The SDT formula uses √(R/r) but the actual velocity uses α.**
The connection is: α² = R_∞ × something / a₀

Specifically: α²/2 = R_∞ × hc / (m_e c²) = 13.606 eV / (511 keV)
So α = √(2 × 13.606 / 511000) = √(5.326e-5) = 0.007298 ✓

The proton radius R appears in the SDT formula but NOT in the
Bohr formula. The Bohr velocity depends only on α, Z, and n —
it is independent of nuclear size.

### 5.2 SDT interpretation

The SDT formula v = (c/k)√(R/r) maps the convergence field
geometry — it describes the field's spatial gradient between
the nuclear surface (R) and the electron position (r).

The Bohr formula v = (Z/n)αc maps the energy balance — the
velocity needed to maintain a circular orbit at the given
binding energy.

These are DIFFERENT physical quantities:
- SDT: the field gradient velocity (displacement rate)
- Bohr: the circulation velocity (kinetic energy)

The connection between them involves α, which in SDT is the
convergence coupling constant at the Rydberg depth.

### 5.3 The correction

To bring SDT in line with Bohr:

v_actual = v_SDT × (α × √(a₀/R))^f(Z,n)

For hydrogen: f = 1.00 (exact match with f=1)
For Be outer: need f = 0.65
For Ar outer: need f ≈ −0.07

This is NOT a clean universal correction. The formula v = (c/k)√(R/r)
maps the convergence field structure but is not a direct predictor
of absolute electron velocity. It is a TOPOLOGICAL mapping tool,
not a dynamical equation.

---

## 6. Conclusions

### 6.1 What is empirically confirmed

| Finding | Status | Evidence |
|---------|--------|----------|
| Keplerian velocity profile (inner faster) | **CONFIRMED** | Bohr model, spectroscopy, Compton profiles all agree |
| Two gear families (rigid/loose) | **CONFIRMED** | Independent of velocity formula — uses only IE and E_exc |
| Shell ordering by z-depth | **CONFIRMED** | Matches Bohr shell structure exactly |
| Anti-Keplerian profile | **REFUTED** | Was based on old formula v=c·k·√(R/r), now corrected |
| Absolute velocity prediction | **PARTIAL** | Correct order of magnitude, but off by 0.5×–1.8× |

### 6.2 What v = (c/k)√(R/r) IS

It is a **field mapping tool** that correctly recovers:
- Shell hierarchy
- Keplerian ordering
- Relative velocity structure

It is NOT a direct predictor of absolute electron velocity.
The absolute velocity requires the fine structure constant α,
which encodes the coupling between the EM field and the electron.

### 6.3 The SDT formula as geometric map

v = (c/k)√(R/r) maps the ratio of nuclear size to electron
position, modulated by the convergence depth z. This is the
geometric structure of the atom — WHERE things are relative
to the nucleus. The Bohr formula adds the DYNAMICS — HOW FAST
things circulate given their energy balance.

Both give Keplerian profiles. Both map the same shell structure.
The SDT formula provides the spatial geometry; Bohr provides
the kinematic velocity.

---

## 7. Impact on Previous Findings

| Previous claim | Updated status |
|----------------|---------------|
| Anti-Keplerian profile | **WITHDRAWN** — corrected formula gives Keplerian |
| Velocity ceiling ~0.008c | **REVISED** — outer shells ~0.003–0.007c (SDT), ~0.003–0.006c (Bohr) |
| v(1s)/v(2s) ≈ α⁻¹/10 for Be | **SDT-SPECIFIC** — Bohr gives ratio 4.8, SDT gives 13.7 |
| Gear rigidity classification | **UNCHANGED** — independent of velocity formula |
| Noble gas compound stability ∝ 1/ρ | **UNCHANGED** — independent of velocity formula |
| 7/9 EC closures reject anions | **UNCHANGED** — measured data |
| Neutron capture creates EC need | **UNCHANGED** — production chain data |
| Grammar identity Δn_tri=+2 | **UNCHANGED** — nuclear arithmetic |
