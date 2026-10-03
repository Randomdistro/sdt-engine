# E14: Ionisation-Controlled EC Halt for Nuclear Medicine

> Source: [INV 17 §8](../ATOMICUS/EC%20Investigations/INVESTIGATION_17_Spallation_Damage_EC_Repair.md)
> SDT Finding: #31

---

## 1. Background

EC isotopes used in nuclear medicine (Ga-67, In-111, I-125, Tl-201)
decay by capturing orbital electrons. The GSI experiments demonstrate
that full ionisation halts EC entirely (Ho-163⁶⁷⁺ shows zero EC).
Partial ionisation (H-like) reduces the rate to approximately 45%
of the neutral value.

Current nuclear medicine delivers these isotopes as neutral atoms
embedded in chemical compounds. The EC rate is fixed by the atomic
structure and cannot be externally controlled.

SDT analysis indicates that selective ionisation could serve as a
remote "switch" for EC decay — suppressing decay during transit and
enabling it at the target site through electron recombination.

## 2. SDT Prediction

### Part I: EC rate suppression by charge state

For any EC isotope at charge state q:
- q < (Z−2): rate ≈ 100% (K-shell intact)
- q = (Z−2): rate ≈ 91% (He-like, 2 K electrons)
- q = (Z−1): rate ≈ 45% (H-like, 1 K electron)
- q = Z: rate = 0% (bare, no electrons)

This predicts that delivering a medical EC isotope in a He-like
charge state would have minimal rate reduction (~9%), while H-like
delivery would halve the dose rate.

### Part II: Electron recombination triggers EC

When a highly ionised EC isotope enters an electron-rich environment
(biological tissue), recombination with ambient electrons should
restore the EC rate. The recombination timescale determines the
spatial precision of dose delivery.

### Part III: Selective step-halting in multi-EC chains

For Ge-68/Ga-68 generator systems (used in PET), the double-EC
chain could be arrested at the Ga-68 intermediate by ionising
past the Ga-68 K-shell. This would allow:
- Ge-68 → Ga-68 (first EC: permitted)
- Ga-68 → Zn-68 (second EC: suppressed by ionisation)
- Ga-68 β⁺ emission: also suppressed (same weak interaction)

This would freeze the generator at Ga-68 for extended periods.

## 3. Observable

### Part I measurement
Measure EC half-life of Ga-67 (t½ = 3.26 d, Z=31) at:
- Ga⁰ (neutral)
- Ga²⁹⁺ (He-like)
- Ga³⁰⁺ (H-like)
- Ga³¹⁺ (bare)

The half-life should scale inversely with the total K-shell
electron density at the nucleus: t½(H-like) ≈ 2 × t½(neutral).

### Part II measurement
Inject H-like Ga-67³⁰⁺ ions into a recombination target (cold
electron gas or solid foil). Measure the EC rate as a function
of time after recombination onset. The rate should step from
~45% to ~100% of neutral within the recombination timescale.

## 4. Apparatus

- ECR ion source or accelerator stripping foil for H-like ions
- Ion trap or storage ring (CRYRING at GSI, or ELENA at CERN)
- Single-ion detection for EC event identification
- Electron cooler or recombination target for Part II
- Ga-67 source (commercially available, used in SPECT imaging)

## 5. Feasibility

**Difficulty: MODERATE-HIGH**

- Part I: Similar to existing GSI measurements of Pr-140, Pm-142.
  The 3.26-day half-life of Ga-67 is within ESR storage capability.
  This measurement is achievable with current GSI/FAIR infrastructure.
- Part II: Controlled recombination with single-ion sensitivity has
  been demonstrated at CRYRING. The time resolution needed is
  microseconds to milliseconds.
- Part III: Requires maintaining Ga-68 in a specific charge state
  for ~68 minutes. This is feasible in a storage ring but not in
  a clinical setting with current technology.

## 6. Clinical Implications

- **Dose timing control**: Deliver isotope in ionised state → no decay
  during transit → recombination at target → decay delivers dose locally
- **Reduced collateral exposure**: Transit dose = 0% instead of
  proportional to transit time
- **Extended generator lifetime**: Freeze Ge-68/Ga-68 at intermediate
  state → extend generator shelf life
- **Practical barrier**: Maintaining charge state in biological tissue
  is not currently feasible. This is a physics-first experiment that
  establishes the principle; clinical translation requires further
  engineering of ion delivery systems.
