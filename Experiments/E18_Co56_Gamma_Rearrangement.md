# E18: Co-56 Gamma-Ray Spectroscopy for Nuclear Rearrangement

> Source: [INV 17 §10.4](../ATOMICUS/EC%20Investigations/INVESTIGATION_17_Spallation_Damage_EC_Repair.md)
> SDT Finding: #27, #30

---

## 1. Background

Ni-56 is produced in supernova explosive silicon burning with N=Z=28.
It undergoes two EC events: Ni-56 → Co-56 → Fe-56. The excess
protons (ΔZ=2) are converted to neutrons via EC.

Co-56 has a rich gamma-ray de-excitation spectrum following EC from
Ni-56. The specific nuclear levels populated during the EC transition
reveal which nuclear shells are involved in the rearrangement.

If the EC mechanism involves rearrangement at specific nuclear
positions (as SDT predicts), the gamma spectrum should show
population patterns consistent with those positions. The gamma
energies correspond to transitions between nuclear levels, and the
relative intensities reveal which levels are most strongly coupled
to the EC process.

## 2. SDT Prediction

In the SDT model, the Ni-56 EC mechanism operates differently from
the He-3 core single-EC:
- Ni-56 has an intact He-4 core (N=Z=28 means 1s is complete)
- The damage is the N=Z structure itself — 2 neutron positions are
  "missing" relative to the stable Fe-56 configuration
- The EC converts 2 protons at the outermost positions (3d region,
  corresponding to IE₃–IE₅ ≈ 35–76 eV)

If the rearrangement involves the 3d nuclear positions, the gamma
spectrum should preferentially populate nuclear levels associated
with the f₇/₂ neutron orbital (the dominant orbital above the N=28
shell closure). Transitions FROM f₇/₂ states should be enhanced
relative to transitions from other orbitals.

**Specific prediction**: The 846.8 keV gamma line (2⁺ → 0⁺ ground
state transition in Fe-56) should dominate the spectrum, as it
corresponds to the fundamental quadrupole vibration of the newly
completed f₇/₂ shell.

## 3. Observable

### Part I: Gamma spectrum analysis
1. Obtain Co-56 from Ni-56 decay (or directly from EC of Ni-56)
2. Record high-resolution gamma spectrum using HPGe detector
3. Measure relative intensities of all gamma lines
4. Identify which nuclear levels are populated and their orbital
   character (from nuclear structure databases)
5. Compare population pattern with:
   (a) Statistical model prediction (compound nucleus, all levels
       equally weighted by density of states)
   (b) SDT prediction (f₇/₂ states preferentially populated)

### Part II: Timing analysis
1. Measure the time distribution of gamma emissions following EC
2. If nuclear rearrangement has a finite timescale, there should be
   a measurable delay between the EC event (prompt X-ray emission
   from K-shell vacancy) and the nuclear de-excitation gammas
3. Expected delay: femtoseconds to picoseconds (nuclear timescale)
4. Measurement requires fast-timing coincidence with BaF₂ or LaBr₃
   scintillators

## 4. Apparatus

### Part I (spectrum)
- Co-56 source (produced by Ni-58(p,3n) or from Ni-56 decay)
- HPGe detector with resolution < 2 keV FWHM at 1 MeV
- Lead shielding and Compton suppression
- Standard nuclear spectroscopy setup

### Part II (timing)
- Co-56 source
- LaBr₃(Ce) or CeBr₃ fast-timing scintillator pair
- Time-to-amplitude converter (TAC) or digital timing system
- Time resolution requirement: < 100 ps
- K X-ray detection in coincidence with nuclear gammas

## 5. Feasibility

**Difficulty: LOW (Part I), MODERATE (Part II)**

- Part I: Co-56 gamma spectroscopy is extensively documented in
  nuclear data tables. The gamma lines and intensities are already
  precisely measured. This is primarily a DATA ANALYSIS experiment
  — reinterpret existing measurements through the SDT lens.
  New measurement is optional.
- Part II: Fast-timing nuclear spectroscopy with sub-nanosecond
  resolution is routinely performed. Co-56 has sufficiently high
  gamma energies for good timing resolution. The challenge is
  distinguishing nuclear rearrangement delays from electronic
  timing artefacts.

## 6. Existing Data

Co-56 decay scheme is well-characterised (ENSDF, NDS). Key gamma
lines from Co-56 (EC/β⁺ decay to Fe-56):

| Energy (keV) | Intensity (%) | Transition | Level character |
|-------------|-------------|-----------|----------------|
| 846.77 | 99.94 | 2⁺₁→0⁺ | Quadrupole, ground band |
| 1238.28 | 66.46 | 4⁺₁→2⁺₁ | Quadrupole, ground band |
| 2598.46 | 16.97 | 2⁺₂→0⁺ | Second 2⁺ state |
| 1771.36 | 15.41 | 2⁺₂→2⁺₁ | Mixed |
| 1037.84 | 14.05 | 4⁺₁→ | Yrast band |

The dominance of the 846.8 keV (2⁺→0⁺) transition at 99.94% is
consistent with the SDT prediction that the EC rearrangement
populates the fundamental f₇/₂ quadrupole excitation.

## 7. Impact

- **If f₇/₂ dominance confirmed by orbital analysis**: Supports SDT
  prediction that spallation damage is at specific outer nuclear
  positions and the rearrangement proceeds through those positions.
- **If timing delay detected**: Direct evidence of a finite nuclear
  rearrangement timescale following EC. This would be the first
  measurement of the "repair step" duration — a quantity that has
  no standard-model analogue (SM treats the entire process as
  instantaneous weak interaction).
- **If statistical population pattern**: Indicates the rearrangement
  is not position-specific, and the nuclear structure redistributes
  energy democratically across all available levels.
