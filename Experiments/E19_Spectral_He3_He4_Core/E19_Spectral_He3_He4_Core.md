# E19: Spectral Diagnostics of the He-3/He-4 Core Transition

> Source: Conversation request (spectral line analysis of core differences)
> SDT Finding: #23–26 (He-3 core mechanism)

---

## 1. Background

SDT identifies two core configurations for light EC isotopes:
- **He-3 core** (2p+1n): present in all 56 EC parents. 1s2 has a
  bare proton (neutron vacancy).
- **He-4 core** (2p+2n): present in all EC daughters and stable
  nuclei. 1s shell complete.

The core directly bounds the lowest electron orbital (1s). A change
in the nuclear 1s structure (He-3 vs He-4) alters the nuclear charge
distribution and therefore the electron energy levels, particularly
the 1s orbital binding energy and the isotope shift.

## 2. SDT Prediction

The He-3 core has a bare proton at 1s2 (no neutron partner). The
He-4 core has a matched deuteron at 1s2 (proton + neutron). This
structural difference changes:

1. **Nuclear charge radius**: He-3 has a different charge radius
   from He-4 (measured: r(He-3) = 1.966 fm, r(He-4) = 1.681 fm).
   He-3 core is ~17% larger.

2. **Isotope shift**: The 1s electron binding energy shifts between
   parent (He-3 core) and daughter (He-4 core). This shift is
   detectable as a spectral line displacement.

3. **Hyperfine structure**: The nuclear magnetic moment changes
   when the core transitions from He-3 to He-4 configuration.
   He-3 has μ = −2.128 μ_N; He-4 has μ = 0. The change in
   nuclear magnetic moment alters the hyperfine splitting.

**Specific prediction**: For Be-7 (He-3 core) vs Li-7 (He-4 core),
the 1s electron binding energy difference (isotope shift) should
reflect the charge radius difference between the He-3 and He-4
core components. This is decomposable into:
- Mass shift (trivial, from A and Z changes)
- Field shift (from nuclear charge radius change)
- SDT structural shift (from the specific He-3 → He-4 core change)

The SDT structural shift is a SUBSET of the field shift, but it
predicts a specific magnitude based on the He-3/He-4 radius
difference (17% larger core → specific ΔE).

## 3. Observable

### Part I: Isotope shift measurement
Measure the optical transition frequencies of:
- Be-7 (He-3 core parent, t½ = 53.22 d)
- Be-9 (He-4 core, stable)
- Li-7 (He-4 core, EC daughter of Be-7)

The Be-7 ↔ Be-9 isotope shift isolates the nuclear structure effect
(same Z, different A and core structure). The difference should
contain the He-3/He-4 core signature.

Be-7 nuclear charge radius is already measured: r(Be-7) = 2.647 fm
(ISOLDE 2009). Be-9: r(Be-9) = 2.519 fm. The difference
(Δr = 0.128 fm, Be-7 is 5.1% larger) is attributed in SDT to the
He-3 core's distended 1s2 bare proton.

### Part II: King plot analysis
1. Measure isotope shifts for Be-7 vs Be-9 in multiple optical
   transitions (at least 3 transitions)
2. Plot King plot (modified isotope shift vs modified isotope shift)
3. Look for nonlinearity: a deviation from the straight line
   expected from pure nuclear charge radius effects

Nonlinearity in the King plot would indicate a contribution beyond
the simple charge radius — potentially from the He-3 core structure.

### Part III: Hyperfine structure
Measure the hyperfine splitting of Be-7 (I = 3/2, μ = −1.399 μ_N)
in comparison with Be-9 (I = 3/2, μ = −1.178 μ_N). The different
nuclear moments produce different hyperfine splittings. The ratio
of splittings should match the ratio of nuclear moments IF the
electron density at the nucleus is the same. Any deviation indicates
a core structure effect on the electron density.

## 4. Apparatus

### Parts I & II
- Be-7 source from Li-7(p,n)Be-7 (proton cyclotron)
- Laser spectroscopy setup (collinear or fluorescence)
- Facility: ISOLDE (CERN) — Be-7 spectroscopy has been performed
  here (Nörtershäuser et al., 2009)
- Reference: Be-9 measured in same apparatus

### Part III
- High-resolution laser spectroscopy with sub-MHz resolution
- Atom trap (MOT) for Be-7 atoms, if achievable
- RF spectroscopy for ground-state hyperfine interval

## 5. Feasibility

**Difficulty: MODERATE**

- Be-7 spectroscopy has already been performed at ISOLDE (2009).
  The charge radius was measured. This means the basic infrastructure
  exists and the measurement is repeatable.
- King plot analysis requires measuring multiple transitions, which
  may require UV/VUV laser systems for Be (first transition at
  234.9 nm). This is within current capabilities.
- Hyperfine structure measurement requires higher resolution than
  the charge radius measurement but uses the same facility.
- Be-7 half-life (53 d) is long enough for extended measurement
  campaigns.

## 6. Existing Data

| Quantity | Be-7 | Be-9 | Source |
|----------|------|------|--------|
| Charge radius (fm) | 2.647(17) | 2.519(12) | ISOLDE 2009 |
| Nuclear spin I | 3/2 | 3/2 | Known |
| Nuclear moment μ/μ_N | −1.3995 | −1.1776 | Known |
| IE₁ (eV) | 9.323 | 9.323 | NIST (same Z) |

The charge radius data ALREADY shows Be-7 is 5.1% larger than Be-9.
SDT attributes this to the distended He-3 core. The existing data
is consistent with the SDT prediction. New measurements would test
the MECHANISM (King plot nonlinearity, hyperfine ratio) rather than
the bare radius.

## 7. Impact

- **If King plot nonlinearity detected**: Indicates a contribution
  beyond simple nuclear charge radius — consistent with a structural
  difference (He-3 vs He-4 core) that affects electron-nucleus
  coupling differently from a generic radius change.
- **If hyperfine ratio anomalous**: Indicates that the electron
  density at the core is affected by the He-3 structure beyond
  what the charge radius alone predicts. Direct probe of the 1s2
  bare proton.
- **If all measurements consistent with standard nuclear physics**:
  The He-3 core model is consistent with existing data but does
  not produce additional observables beyond established nuclear
  structure theory. Constrains the SDT model's scope.
