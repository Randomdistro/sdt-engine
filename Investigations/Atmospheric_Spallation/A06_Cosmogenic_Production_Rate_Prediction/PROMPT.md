# A06: Cosmogenic Production Rate Prediction — Investigation Prompt

> **Classification**: Archival data computation + SDT prediction test
> **Prerequisites**: A01 (grammar audit), A03 (atmospheric inventory),
> A04 (cross-section scaling), cosmic ray spectrum data
> **Output format**: Production rate predictions vs measured benchmarks

---

## 1. Objective

Predict the global production rate (atoms/cm²/s) of the 6 principal
cosmogenic isotopes (C-14, Be-7, Be-10, H-3, Cl-36, Na-22) using ONLY:

1. The measured cosmic ray proton spectrum (AMS-02)
2. The atmospheric composition and density profile (US Standard Atmosphere)
3. Measured channel-specific spallation cross-sections from EXFOR/ENDF

Then compare these predictions to measured production rates. This is NOT
an SDT-specific derivation — it is a conventional calculation done
carefully to establish the BASELINE against which SDT predictions can
be tested.

The SDT-specific extension (Phase C) is to attempt the same calculation
using SDT-predicted cross-sections from A04, rather than measured ones.
If the SDT-predicted cross-sections are accurate, the production rates
should match.

---

## 2. The Calculation

### The production rate formula

For isotope X produced by cosmic ray protons on target T via reaction
channel R:

$$Q_X = \\int_0^{X_{\\text{atm}}} \\frac{N_T(x)}{M_T} \\int_{E_{\\text{thr}}}^{E_{\\text{max}}} \\sigma_R(E) \\cdot \\phi_p(E, x) \\, dE \\, dx$$

Where:
- x = atmospheric depth (g/cm², from 0 at TOA to 1030 at ground)
- N_T(x)/M_T = target atom number density at depth x (atoms/g × density)
- σ_R(E) = reaction cross-section (cm²)
- φ_p(E,x) = proton flux at energy E and depth x (protons/cm²/s/MeV)
- E_thr = threshold energy for reaction R
- E_max = maximum cosmic ray energy (practical: ~1 TeV)

The proton flux attenuates with depth:
$$\\phi_p(E, x) = \\phi_p(E, 0) \\cdot e^{-x/\\lambda_p(E)}$$

For neutron-induced reactions (like N-14(n,p)C-14):
$$Q_X = \\int_0^{X_{\\text{atm}}} \\frac{N_T(x)}{M_T} \\int_0^{E_{\\text{max}}} \\sigma_R(E_n) \\cdot \\phi_n(E_n, x) \\, dE_n \\, dx$$

The neutron flux φ_n(E,x) is itself a product of primary spallation.

---

## 3. Methodology

### Phase A: Conventional production rate calculation

#### Step 1: Cosmic ray input spectrum

- Use AMS-02 proton spectrum at solar-minimum conditions (φ ≈ 400 MV)
- Parametrise as:  φ(E) = C × E^(-γ) × (E + φ_SM)^(-1)
  where γ ≈ 2.7, φ_SM = solar modulation parameter
- Tabulate dΦ/dE at 50 energy points logarithmically spaced from
  0.1 GeV to 1 TeV

#### Step 2: Atmospheric model

- Use US Standard Atmosphere 1976
- Compute N₂, O₂, Ar column densities as function of depth x
- Compute temperature profile (affects thermal neutron energy)
- Compute geomagnetic-averaged exposure (weight by cos⁴λ for
  geomagnetic latitude λ, average over globe)

#### Step 3: Cross-section compilation

For each cosmogenic isotope, compile σ(E) from EXFOR for ALL
contributing reactions:

**C-14:**
- Primary: N-14(n,p)C-14 (thermal + epithermal)
- Secondary: O-16(p,x)C-14, N-14(p,x)C-14
- The primary reaction requires computing the atmospheric neutron
  flux from all spallation channels

**Be-7:**
- Direct: N-14(p,x)Be-7, O-16(p,x)Be-7
- No significant neutron-induced pathway

**Be-10:**
- Direct: N-14(p,x)Be-10, O-16(p,x)Be-10
- Minor: secondary neutron channels

**H-3:**
- Direct: N-14(p,x)H-3, O-16(p,x)H-3
- Neutron: N-14(n,³H)C-12 (threshold: ~4 MeV)

For each reaction, interpolate σ(E) from EXFOR data points using
log-log interpolation. Where data gaps exist, use TENDL-2023
evaluated values.

#### Step 4: Numerical integration

Perform the double integral (energy × depth) numerically:
- Energy grid: 50 points, logarithmic, 0.1 GeV – 1 TeV
- Depth grid: 20 points, linear, 0 – 1030 g/cm²
- For C-14: must ALSO compute the neutron flux at each depth from
  the primary spallation, then fold with the N-14(n,p)C-14 cross-section

Report the production rate for each isotope in atoms/cm²/s.

### Phase B: Comparison with measured rates

| Isotope | Computed Q | Measured Q | Ratio | Within factor 2? |
|---------|----------|----------|-------|-----------------|
| C-14 | ? | 2.02 | ? | ? |
| Be-7 | ? | 0.062 | ? | ? |
| Be-10 | ? | 0.019 | ? | ? |
| H-3 | ? | 0.25 | ? | ? |
| Cl-36 | ? | 0.0012 | ? | ? |
| Na-22 | ? | 3.6e-5 | ? | ? |

If all ratios are within 0.5–2.0, the calculation is validated.
If any ratio is outside 0.1–10.0, identify the source of error.

### Phase C: SDT cross-section prediction test

Replace the EXFOR/ENDF cross-sections with SDT-predicted values:

1. Use the scaling law from A04 to predict σ_reaction for each
   target at each energy
2. Use the branching ratios from A01 (grammar audit) to partition
   σ_reaction into individual channels
3. Recompute the production rates using ONLY SDT-derived cross-sections

Compare:
| Isotope | EXFOR-based Q | SDT-based Q | Measured Q | SDT/measured |
|---------|-------------|-----------|----------|------------|
| C-14 | ? | ? | 2.02 | ? |
| ... | ... | ... | ... | ... |

If SDT-based production rates match measured values within a factor
of 3, this constitutes a STRONG validation of the SDT cross-section
framework for nuclear processes.

### Phase D: Grammar analysis of the production cycle

For each cosmogenic isotope, trace the complete grammar cycle:

```
Parent (stable atmosphere) →[spallation]→ Product (cosmogenic)
→[decay]→ Daughter →[decay]→ ... →[final]→ Stable endpoint
```

At each step, compute grammar (d, t, n_tri, n_deu).

Key questions:
1. Does every cosmogenic isotope eventually return to a stable grammar
   state that matches one of the original atmospheric isotopes?
2. Is the atmospheric nuclear grammar a CLOSED SYSTEM under cosmic
   ray bombardment? (Everything produced eventually decays back to
   original species?)
3. Are there any products that create PERMANENTLY NEW isotopes in the
   atmosphere? (Yes: Be-10, Al-26, Cl-36 are long-lived enough to
   accumulate, but they all eventually decay to existing stable nuclei.)

---

## 4. Required Outputs

1. **Production rate table**: Computed Q for all 6+ cosmogenic isotopes,
   with comparison to measured values

2. **Cross-section compilation**: σ(E) tables for each contributing
   reaction, with EXFOR references

3. **Depth profile**: Production rate as function of atmospheric depth
   for each isotope (shows altitude of maximum production)

4. **SDT prediction comparison**: Production rates using SDT-predicted
   vs EXFOR cross-sections

5. **Grammar cycle table**: Complete grammar trace for each cosmogenic
   isotope from production through all decay steps to stable endpoint

6. **Atmospheric grammar balance sheet**: Net grammar effect of cosmic
   ray bombardment — how many d and t blocks are created and destroyed
   per unit time?

---

## 5. Success Criteria

- [ ] All 6 isotopes have computed production rates
- [ ] EXFOR-based rates match measurements within factor of 3
      (factor of 2 for C-14)
- [ ] SDT-based rates (Phase C) match measurements within factor of 5
      (if better than factor of 3, this is a strong result)
- [ ] Grammar is computed at every step of every production cycle
- [ ] Grammar validity is maintained throughout (100%, no exceptions)
- [ ] The atmospheric grammar balance sheet closes (no net creation
      or destruction of nuclear grammar — everything cycles back)
- [ ] Depth profiles show peak production at correct altitude
      (~12–15 km for most species)
