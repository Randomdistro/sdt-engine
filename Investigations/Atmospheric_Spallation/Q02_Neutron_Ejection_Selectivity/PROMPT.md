# Q02: Neutron Ejection Selectivity — Investigation Prompt

> **Classification**: Theoretical derivation with archival verification
> **Prerequisites**: Q01 (spallation event geometry), SDT wake hierarchy,
> nuclear construction grammar
> **Output format**: Geometric proof with quantitative predictions

---

## 1. Background

When a high-energy proton strikes a nucleus, the products are
overwhelmingly neutrons — not protons. The (p,xn) channels dominate
over (p,pxn) or (p,xp) channels at all but the highest energies.
This is the foundational observation behind cosmic ray spallation
producing neutron-rich environments.

Conventional nuclear physics explains this with two mechanisms:
1. **Coulomb barrier**: Protons must overcome the Coulomb barrier to
   escape the nucleus; neutrons do not. At low excitation energies,
   this barrier suppresses proton emission.
2. **Statistical competition**: In compound nucleus evaporation, the
   available phase space for neutron emission exceeds that for proton
   emission because neutrons have no barrier.

SDT must not invoke Coulomb barrier as a separate phenomenon. In SDT,
the Coulomb force IS the ℓ=1 wake interaction. The question becomes:
**why does the ℓ=1 wake tether protons to the scaffold while allowing
neutrons to escape?**

This is not a trivial restatement. It demands a geometric explanation
for WHY charged particles (those with ℓ=1 wakes) are geometrically
bound by their wake coupling, while uncharged particles (those WITHOUT
ℓ=1 wakes) lack this additional tether.

---

## 2. The Core Question

**Why, in the SDT geometric framework, are neutrons easier to eject
from a nuclear scaffold than protons?**

Sub-questions:
1. What is the geometric difference between how a proton sits in the
   scaffold versus how a neutron sits?
2. Is the difference purely the ℓ=1 wake (Coulomb), or does the ℓ=2
   wake (magnetic moment) also contribute to tethering?
3. Does the triton's internal topology (connecting neutron n_c vs open
   neutron n_o, per Triton Overload) create a hierarchy of neutron
   ejection ease?
4. Is there a "weakest link" criterion — the neutron with the fewest
   scaffold connections is ejected first?
5. Does the n_c/n_o distinction predict WHICH neutron is ejected in
   a specific spallation event?

---

## 3. Methodology

### Phase A: Catalogue the tethering forces

For a proton embedded in a nuclear scaffold, enumerate every geometric
coupling that holds it in place:

| Coupling | Type | SDT Multipole | Range | Strength |
|----------|------|---------------|-------|----------|
| Coulomb attraction to all other protons/neutrons | ℓ=1 | 1/r² | Long | Strong |
| Magnetic coupling to adjacent nucleons | ℓ=2 | 1/r³ | Medium | Moderate |
| Nuclear structure coupling (scaffold bond) | ℓ≥3 | 1/r^(ℓ+1) | Very short | Very strong |
| Convergence pressure (isotropic background) | ℓ=0 | uniform | — | Baseline |

For a neutron embedded in the same scaffold:

| Coupling | Type | SDT Multipole | Range | Strength |
|----------|------|---------------|-------|----------|
| ~~Coulomb~~ | ~~ℓ=1~~ | ~~N/A~~ | ~~—~~ | **ABSENT** |
| Magnetic coupling to adjacent nucleons | ℓ=2 | 1/r³ | Medium | Moderate |
| Nuclear structure coupling (scaffold bond) | ℓ≥3 | 1/r^(ℓ+1) | Very short | Very strong |
| Convergence pressure (isotropic background) | ℓ=0 | uniform | — | Baseline |

The neutron is missing the ℓ=1 term entirely. This is the leading-order
difference. Quantify it:
- What is the energy equivalent of the ℓ=1 coupling for a proton at the
  nuclear surface (~4 fm for medium nuclei)?
- Compare this to S_n − S_p (neutron vs proton separation energy) from
  AME2020 data
- Is the ℓ=1 deficit sufficient to explain the FULL selectivity, or
  must ℓ=2 (magnetic) differences also contribute?

### Phase B: Analyse the triton topology

The Triton Overload investigation established that each triton has two
neutrons with distinct roles:
- **n_c (connecting)**: bonded to the scaffold, bridging to adjacent blocks
- **n_o (open)**: dangling, unbonded, exposed to the nuclear surface

Hypothesis: **n_o neutrons are ejected first because they have fewer
scaffold connections.**

Test this hypothesis:
1. Count the scaffold connections of n_c vs n_o for a triton in a
   typical medium-mass nucleus (e.g., Ga-69)
2. Compute the ejection energy for n_c (must break scaffold bridge
   bond) vs n_o (only ℓ≥3 structure coupling)
3. Compare the predicted energy difference to the measured difference
   between the first and second neutron separation energies (S_1n vs S_2n)
4. Does the n_o-first hypothesis predict the correct product nucleus
   in all known (p,2n) reactions?

### Phase C: Energy threshold analysis

If neutron ejection selectivity is governed by the ℓ=1 wake absence,
then:
- At LOW projectile energies (just above threshold): neutrons are
  ejected exclusively — the available energy exceeds S_n but not
  S_p + Coulomb barrier. SDT: the energy exceeds the ℓ≥3 scaffold
  bond for the neutron, but not the ℓ≥3 bond PLUS the ℓ=1 wake
  coupling for the proton.
- At HIGH projectile energies (> 100 MeV): protons begin to be
  ejected too (the ℓ=1 tether is overcome). The onset energy for
  proton ejection should equal the ℓ=1 coupling energy.

Predict:
1. The energy at which (p,p') outscattering becomes comparable to (p,n)
   for Ga-69. Compare to EXFOR data.
2. The systematic Z-dependence of this crossover energy (ℓ=1 scales
   as Z × e² / R_nuc).
3. Whether the crossover energy scales as Z/A^(1/3) (conventional
   Coulomb barrier) or differently in SDT.

### Phase D: The magnetic moment asymmetry

Proton: μ = +2.793 μ_N (positive, large)
Neutron: μ = −1.913 μ_N (negative, smaller magnitude)

In SDT, the magnetic moment is the ℓ=2 wake strength. The signs are
opposite. Does this affect ejection selectivity?

Investigate:
1. For nuclei with large deformation (quadrupole moment ≠ 0), does the
   ℓ=2 coupling create a different tethering geometry for protons vs
   neutrons?
2. Is there a measurable correlation between nuclear quadrupole moment
   and the (p,n)/(p,p') branching ratio?
3. Does the sign difference in μ create a preferential ejection
   direction for neutrons (toward the nuclear equator vs poles)?

---

## 4. Required Outputs

1. **Tethering force table**: A complete table of all geometric couplings
   (ℓ=0,1,2,3+) for protons and neutrons in a nuclear scaffold,
   with quantitative estimates at r = 4 fm (nuclear surface)

2. **Selectivity proof**: A step-by-step derivation showing that the
   ℓ=1 wake absence makes neutron ejection energetically cheaper
   by a specific, calculable amount

3. **n_c vs n_o hierarchy**: Whether the triton's internal topology
   creates a further subdivision of neutron ejection ease

4. **Predictions table**: At least 3 quantitative predictions:
   - Energy threshold for proton emission onset vs Z
   - Neutron multiplicity ordering based on n_o count
   - Branching ratio (p,xn)/(p,pxn) as a function of energy

5. **Verification checklist**: For each prediction, state which EXFOR
   dataset would confirm or refute it

---

## 5. Success Criteria

- [ ] The explanation uses ONLY wake multipole hierarchy (ℓ=0,1,2,3+)
      and scaffold geometry — no Coulomb potential, no nuclear potential
- [ ] The ℓ=1 absence is shown to produce a QUANTITATIVE energy deficit
      matching S_n − S_p within 20%
- [ ] The n_c/n_o hierarchy is either confirmed or refuted against data
- [ ] At least one prediction is novel (not derivable from conventional
      Coulomb barrier argument alone)
- [ ] The analysis explains why neutron selectivity DECREASES at very
      high energies (where both channels become geometrically accessible)
