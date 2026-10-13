# Q01: Spallation Event Geometry — Investigation Prompt

> **Classification**: Theoretical derivation (no laboratory work required)
> **Prerequisite knowledge**: SDT Ruleset, Nuclear Construction Grammar,
> Triton Overload mechanism, Wake multipole hierarchy
> **Output format**: Step-by-step geometric narrative with quantitative
> predictions at each stage

---

## 1. Background

Cosmic ray spallation is the dominant production mechanism for several
light isotopes (Be-7, Be-9, Be-10, B-10, B-11) and a significant
contributor to EC isotope production (INV 12, INV 17). The existing
SDT-engine codebase describes spallation outcomes (what is produced,
what grammar states result, how EC repairs the damage) but does NOT
describe the spallation event itself — the moment-by-moment geometric
process of a high-energy proton entering a nuclear scaffold and causing
neutron ejection.

This is an unacceptable gap. SDT claims to derive all nuclear behaviour
from geometric first principles. The most violent nuclear process in
the natural environment — cosmic ray spallation — must have a complete
SDT geometric description.

---

## 2. Scope

This investigation must produce a complete, step-by-step geometric
description of the spallation event, analogous to the Triton Overload
micro-mechanism (ATOMICUS/isotopes/INVESTIGATION_Triton_Overload.md)
which described alpha decay as a 5-step geometric process.

The description must cover:

1. **Approach phase**: The incident proton (W=3 torus) approaching the
   target nucleus. What does the proton "see" as it approaches? How does
   the convergence gradient of the target interact with the proton's own
   displacement field? At what distance does interaction begin?

2. **Contact phase**: The proton's displacement volume enters the target's
   displacement volume. What happens to the spation lattice between them?
   Is there an occlusion shadow? Does the proton's wake (ℓ=1 dipole)
   interact with the target's wake structure?

3. **Penetration phase**: The proton enters the nuclear scaffold. Does it
   tunnel through the Coulomb barrier (SDT: the ℓ=1 wake repulsion), or
   does its kinetic energy (movement budget allocation: v → large, v_circ
   → small) allow it to overcome the repulsion? At what k-number does the
   proton's translational velocity dominate its circulation, and what
   does this mean for its ability to breach the ℓ=1 barrier?

4. **Compound formation or direct knockout**: Two competing pathways exist
   in conventional nuclear physics:
   - **Compound nucleus**: The proton is fully absorbed, its energy
     thermalises across all nucleons, and neutrons "evaporate" from the
     equilibrated compound
   - **Direct knockout**: The proton collides with individual nucleons
     near the nuclear surface, ejecting them immediately without
     equilibration

   SDT MUST describe both pathways in geometric terms:
   - Compound formation = the proton's displacement volume merges with
     the scaffold, redistributing convergence pressure across all blocks
   - Direct knockout = the proton's displacement volume collides with a
     specific deuteron or triton block, transferring momentum locally
     before the scaffold equilibrates

   What determines which pathway dominates? Is it the k-number of the
   projectile relative to the target's internal circulation speeds?

5. **Neutron ejection**: The actual moment of neutron release. The neutron
   is NOT a fundamental particle in SDT — it is a neutron (W=3 torus,
   uncharged, metastable). When a neutron is "ejected", what happens
   geometrically?
   - Does a triton block lose its connecting neutron?
   - Does a deuteron block lose its only neutron, leaving a bare proton?
   - Does the ejection break a scaffold bond?
   - What determines the kinetic energy of the ejected neutron?

6. **Scaffold rearrangement**: After neutron ejection, the remaining
   scaffold must rearrange. How does this proceed?
   - Does the scaffold collapse inward (reducing radius)?
   - Do adjacent blocks redistribute their connections?
   - Is the rearrangement itself a source of gamma emission?
   - How does this connect to the "damage at outermost positions"
     finding from INV 17 §7?

---

## 3. Methodology

### Phase A: Establish the geometric parameters

For the canonical test case Ga-69(p,2n)Ge-68:

1. Compute the Ga-69 nuclear scaffold structure:
   - Z=31, N=38, A=69
   - Grammar: α core + d blocks + t blocks (get exact counts from
     ATOMICUS/isotopes/031_Ga69.md)
   - Nuclear charge radius: ~4.0 fm (Angeli & Marinova)
   - Displacement volume: V_disp from SDT formula

2. Compute the incoming proton's state at the threshold energy:
   - (p,2n) threshold for Ga-69: ~15 MeV (from EXFOR)
   - At 15 MeV: v/c = √(2×15/938.3) ≈ 0.179
   - k = c/v ≈ 5.6
   - Movement budget: v_circ² = c² − v² → v_circ/c = √(1 − 0.032) ≈ 0.984
   - The proton still has nearly all its circulation at this energy

3. Compute the interaction geometry:
   - At what distance does the proton's ℓ=1 wake overlap the Ga-69 wake?
   - What is the Coulomb barrier height in SDT terms (ℓ=1 wake repulsion)?
   - Does the proton's kinetic energy exceed the barrier?

### Phase B: Describe the event step by step

Using the parameters from Phase A, write the complete geometric narrative.
Number each step. For each step, state:
- What moves
- What changes shape/topology
- What convergence pressure redistribution occurs
- What is emitted (if anything)
- What the grammar state is after the step

### Phase C: Generalise

After completing the Ga-69 canonical case, generalise:
- Which features of the description depend on the specific target?
- Which features are universal to all (p,xn) spallation?
- What changes for (α,xn) reactions (α = composite projectile)?
- What changes for (d,xn) reactions?
- What changes at ultra-high energies (GeV+) where the proton's
  circulation is nearly zero?

### Phase D: Make predictions

The description must generate at least 3 QUANTITATIVE predictions that
differ from conventional nuclear physics or that conventional nuclear
physics cannot make without fitted parameters:

1. A geometric relationship between target grammar and spallation threshold
2. A geometric relationship between target grammar and neutron multiplicity
3. A prediction for the angular distribution of ejected neutrons based
   on scaffold geometry (not phase space statistics)

---

## 4. Required Outputs

1. **Narrative**: A numbered, step-by-step geometric description of the
   spallation event (minimum 10 steps, analogous to the 5-step alpha
   decay narrative in Triton Overload)

2. **Diagram description**: A text-based diagram showing the proton
   approach, scaffold contact, and neutron ejection geometry

3. **Grammar table**: A table showing the grammar state (d, t, n_tri,
   n_deu) at each step in the event, from initial approach through
   final product

4. **Predictions table**: A table of quantitative predictions with
   estimated values and the archival data needed to test each one

5. **Open questions**: A numbered list of aspects of the event that the
   geometric description cannot yet resolve, with specific suggestions
   for what additional data or derivation would resolve each one

---

## 5. Success Criteria

The investigation succeeds if:

- [ ] Every step in the narrative uses only SDT-permitted concepts
      (no quarks, no nuclear potential wells, no wavefunctions)
- [ ] The grammar state is tracked at every step and remains consistent
- [ ] The narrative explains WHY neutrons are ejected (not just that
      they are) — this connects to Q02
- [ ] The narrative explains WHY the damage is at outer positions
      (connecting to INV 17 §7 finding #8)
- [ ] At least one quantitative prediction is testable against EXFOR data
- [ ] The narrative is fully self-contained (readable without needing
      to reference other documents, though it may cite them)

---

## 6. Prohibitions

Per the SDT Constitutional Ruleset:
- Do NOT invoke nuclear potential wells, Wood-Saxon potentials, or
  shell model quantum numbers
- Do NOT invoke quarks, gluons, or the strong force as a separate entity
- Do NOT use G or M as fundamental — use convergence pressure P_conv
- Do NOT invoke probabilistic wavefunction overlap for barrier penetration
- The Coulomb barrier must be described as ℓ=1 wake repulsion geometry
- The nuclear force must be described as ℓ≥3 wake structure at short range
