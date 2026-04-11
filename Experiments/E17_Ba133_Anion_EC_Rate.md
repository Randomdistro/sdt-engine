# E17: Ba-133 Anion EC Rate Test

> Source: [FINAL_REPORT §20 Q9, §21 Pred8](../ATOMICUS/EC%20Investigations/FINAL_REPORT.md)
> SDT Finding: #17 (7/9 EC closures reject anions)

---

## 1. Background

Seven of the nine EC closure elements have negative or near-zero
electron affinities, meaning they reject anion formation. This
correlates with their role as EC hosts — if the nuclear structure
actively captures electrons, the atom should resist holding an
EXTRA electron.

Barium (Ba, Z=56) is an exception: it has a positive electron
affinity (EA = 0.145 eV) and forms stable Ba⁻ anions. Ba-133
(t½ = 10.5 y) decays by EC to Cs-133.

The question: does the extra electron in Ba-133⁻ alter the EC rate?

## 2. SDT Prediction

In SDT, the EC mechanism captures a 1s (K-shell) electron. An extra
electron in Ba⁻ occupies the 6p orbital — far from the nucleus.
The 6p electron has negligible wavefunction density at r = 0.

**SDT prediction**: The extra electron does NOT alter the EC rate.
The K-shell electron density is unchanged by the addition of a
loosely-bound 6p electron. The EC rate of Ba-133⁻ should be
identical to that of Ba-133⁰ within measurement precision.

**Alternative hypothesis**: If EC involves any coupling to the
outer electron structure (e.g., through nuclear rearrangement),
the extra electron could produce a detectable rate change. This
would indicate that the outer electron environment participates
in the EC mechanism beyond simple K-shell overlap.

## 3. Observable

Measure the EC half-life of Ba-133 in two states:
- Ba-133⁰ (neutral, reference: t½ = 10.551 ± 0.011 y)
- Ba-133⁻ (anion)

Required precision: better than 0.1% to be meaningful.
The known chemical-environment effect on EC rates is ~0.01–0.1%,
so the measurement must exceed this sensitivity or use identical
chemical environments for both states.

## 4. Apparatus

- Ba-133 source (commercially available)
- Anion source: Ba⁻ can be produced by Cs-sputter negative ion
  sources (standard in AMS facilities)
- Ion trap for Ba-133⁻ storage (Paul trap or Penning trap)
- Gamma-ray detector (HPGe) for 356 keV and 81 keV lines
  from Ba-133 EC decay
- Alternative: embed Ba-133 in a matrix with high and low
  electron density (metallic Ba vs BaF₂) and compare rates

## 5. Feasibility

**Difficulty: MODERATE**

- Ba-133 sources are inexpensive and widely available
- Ba⁻ anion production is routine in accelerator mass spectrometry
- The primary challenge is measuring half-life differences at the
  0.1% level or better, which requires:
  - Large source activity (~MBq)
  - Long counting periods (years)
  - Rigorous control of systematic effects (geometry, dead time,
    detector efficiency drift)
- The 10.5-year half-life means the measurement requires patient
  data collection over 1–3 years minimum
- A differential approach (Ba⁰ and Ba⁻ measured simultaneously
  in identical detector geometries) reduces systematic errors

## 6. Existing Constraints

- The chemical-environment effect on Be-7 EC rate is ~0.1%
  (metallic Be vs BeO). This establishes that outer-electron
  changes CAN affect EC rates at the 0.1% level.
- Ba has a much higher Z than Be (56 vs 4). The K-shell is more
  deeply buried. The relative effect of a 6p electron on K-shell
  density should be smaller than the effect of chemical bonding
  changes on Be 1s density.
- No measurement of anion EC rate exists for any isotope.

## 7. Impact

- **If rate unchanged**: Confirms that EC is a pure K-shell process
  insensitive to outer electron configuration. Consistent with
  the SDT prediction and the observation that 7/9 EC closures
  reject anions (the rejection is a structural property, not
  related to the EC mechanism itself).
- **If rate changed**: Indicates outer electron coupling to the
  EC mechanism. Would require revisiting the He-3 core model to
  include valence electron effects. Would also explain WHY Ba
  and Cd are the two EC closures that accept anions — their EC
  mechanism may differ from the other seven closures.
