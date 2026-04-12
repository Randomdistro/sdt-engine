# INVESTIGATION 17: Spallation Damage and EC Repair Chains

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [He-3 Core](INVESTIGATION_16_He3_Core_Hypothesis.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Master Table](EC_data/01_All_EC_Isotopes_Master_Table.md) ·
> [He-3 Grammar](EC_data/12_He3_Core_Grammar.md) ·
> [Spallation Data](EC_data/13_Spallation_EC_Chains.md)

---

## 1. Scope and Objective

This investigation examines EC isotopes produced by violent assembly —
spallation, heavy-ion collisions, or supernova explosive nucleosynthesis
— that require TWO or more successive EC events to reach stability.

Objectives:
1. Catalogue all multi-step EC chains and their production reactions
2. Compute the complete grammar (He-4 core) at each step
3. Determine whether the neutron vacancies are at identifiable positions
4. Map the ionisation data for each element in the chain
5. Identify the charge state threshold to halt EC repair
6. Compare L/K capture ratios between single-EC and multi-EC isotopes

All data sourced from: NIST ASD, LNHB Table de Radionucléides,
NNDC/NUBASE2020, X-Ray Data Booklet (LBNL).

---

## 2. Two Classes of EC

### 2.1 Class I — He-3 Core Defect (single EC)

The He-3 core occupies the 1s nuclear shell:
- 1s1 = deuteron (1p+1n)
- 1s2 = bare proton (1p+0n) — neutron VACANCY at 1s2

The core captures a 1s electron (K-shell, measured 88–93%) and reels in
a valence proton, transmuting it to a neutron. One EC event completes
the He-3 → He-4 core transition.

Production: slow neutron capture, cosmic ray spallation, natural decay.
Representatives: Be-7, Ar-37, Kr-81, all 9 closure EC isotopes.

### 2.2 Class II — Spallation Damage (multi-step EC)

Violent production ejects neutrons from OUTER nuclear positions. Each
ejected neutron leaves a vacancy at the corresponding nuclear shell.
Each vacancy requires one EC event to repair.

The damage sites are NOT at the 1s core. They are at higher nuclear
shells — positions that correspond to outer electron shells in the
SDT shell-mapping scheme.

Production: (p,xn) reactions, (α,xn) reactions, supernova α-capture,
heavy-ion collisions.

---

## 3. Catalogue of Multi-Step EC Chains

### 3.1 Double EC (ΔZ = 2)

| Chain | t½ step 1 | t½ step 2 | Production | n ejected |
|-------|----------|----------|-----------|-----------|
| Ti-44 → Sc-44 → **Ca-44** | 59.1 y | 3.97 h | Supernova | 0 (N=Z built-in) |
| Ni-56 → Co-56 → **Fe-56** | 6.075 d | 77.24 d | Supernova | 0 (N=Z built-in) |
| Ge-68 → Ga-68 → **Zn-68** | 270.9 d | 67.7 min | Ga-69(p,2n) | 2 |
| Zr-88 → Y-88 → **Sr-88** | 83.4 d | 106.6 d | Y-89(p,2n) | 2 |
| Ru-97 → Tc-97 → **Mo-97** | 2.84 d | 4.21 My | Mo-96(α,3n) | 3 |
| Sm-145 → Pm-145 → **Nd-145** | 340 d | 17.7 y | Nd-144(α,3n) | 3 |

### 3.2 Triple EC (ΔZ = 3)

| Chain | Production |
|-------|-----------|
| Cu-56 → Ni-56 → Co-56 → **Fe-56** | Heavy-ion |
| As-68 → Ge-68 → Ga-68 → **Zn-68** | Heavy-ion |
| Nb-88 → Zr-88 → Y-88 → **Sr-88** | Spallation |

### 3.3 Quadruple EC (ΔZ = 4)

| Chain | Production |
|-------|-----------|
| Se-68 → As-68 → Ge-68 → Ga-68 → **Zn-68** | Heavy-ion |

---

## 4. Grammar at Each Step

The universal EC grammar rule (He-4 core):
- Per EC event: Δn_tri = +2, Δn_deu = −3
- Z decreases by 1, A unchanged, N increases by 1

### 4.1 The A=68 Chain (quadruple)

| Step | Isotope | Z | N | n_tri | n_deu | t½ |
|------|---------|---|---|-------|-------|----|
| 0 | Se-68 | 34 | 34 | 0 | 32 | 35.5 s |
| 1 | As-68 | 33 | 35 | 2 | 29 | 151 s |
| 2 | Ge-68 | 32 | 36 | 4 | 26 | 270.9 d |
| 3 | Ga-68 | 31 | 37 | 6 | 23 | 67.7 min |
| 4 | **Zn-68** | 30 | 38 | **8** | **20** | stable |

Se-68 starts at n_tri = 0 (N = Z). Every step adds 2 tritons and
removes 3 deuterons. The grammar remains valid at every step
(both counts ≥ 0 throughout).

Notable: Se-68 has the maximum possible deuteron count for A=68.
The chain progressively converts deuterons to tritons.

### 4.2 The A=56 Chain (Ni-56, supernova)

| Step | Isotope | Z | N | n_tri | n_deu | t½ |
|------|---------|---|---|-------|-------|----|
| 0 | Ni-56 | 28 | 28 | 0 | 26 | 6.075 d |
| 1 | Co-56 | 27 | 29 | 2 | 23 | 77.24 d |
| 2 | **Fe-56** | 26 | 30 | **4** | **20** | stable |

Ni-56 powers Type Ia supernova light curves. Its double EC chain
(Ni-56 → Co-56 → Fe-56) produces the gamma rays that illuminate
the expanding supernova remnant.

### 4.3 The A=44 Chain (Ti-44, supernova)

| Step | Isotope | Z | N | n_tri | n_deu | t½ |
|------|---------|---|---|-------|-------|----|
| 0 | Ti-44 | 22 | 22 | 0 | 20 | 59.1 y |
| 1 | Sc-44 | 21 | 23 | 2 | 17 | 3.97 h |
| 2 | **Ca-44** | 20 | 24 | **4** | **14** | stable |

Ti-44 is observed directly in supernova remnant Cassiopeia A.

### 4.4 Supernova pattern: N=Z starting point

Both Ti-44 and Ni-56 start at n_tri = 0 and N = Z. This is a
direct consequence of their production via α-capture chains, where
each α particle (2p+2n) preserves N = Z at every step.

Stable nuclei at A ≈ 44–56 require N > Z. The α-capture process
cannot produce stable nuclei directly — it overshoots on protons.
The double EC corrects this by converting 2 protons to 2 neutrons.

---

## 5. Ionisation Data for Multi-EC Elements

### 5.1 Ionisation Energies (eV) — NIST ASD

| Element | Z | IE₁ | IE₂ | IE₃ | IE₄ | IE₅ | Config |
|---------|---|-----|-----|-----|-----|-----|--------|
| Ca | 20 | 6.1132 | 11.872 | 50.913 | 67.273 | 84.50 | [Ar]4s² |
| Ti | 22 | 6.8281 | 13.576 | 27.477 | 43.267 | 99.25 | [Ar]3d²4s² |
| Ni | 28 | 7.6398 | 18.169 | 35.196 | 54.9 | 76.06 | [Ar]3d⁸4s² |
| Zn | 30 | 9.3942 | 17.964 | 39.723 | 59.58 | 82.60 | [Ar]3d¹⁰4s² |
| Ge | 32 | 7.8994 | 15.935 | 34.058 | 45.716 | 90.50 | [Ar]3d¹⁰4s²4p² |
| Zr | 40 | 6.6341 | 13.13 | 23.170 | 34.418 | 80.35 | [Kr]4d²5s² |
| Ru | 44 | 7.3605 | 16.76 | 28.47 | ~45 | ~59 | [Kr]4d⁷5s¹ |
| Sm | 62 | 5.6437 | 11.07 | 23.4 | ~35 | ~47 | [Xe]4f⁶6s² |

### 5.2 k-Values (k = c/v₀)

Computed from IE₁ using v₀ = c × √(2 × IE₁ / 511000):

| Element | IE₁ (eV) | v₀/c | k = c/v₀ | k/α⁻¹ |
|---------|---------|------|---------|--------|
| Ca | 6.113 | 0.004892 | 204.4 | 1.491 |
| Ti | 6.828 | 0.005171 | 193.4 | 1.411 |
| Ni | 7.640 | 0.005470 | 182.9 | 1.334 |
| Zn | 9.394 | 0.006064 | 164.9 | 1.203 |
| Ge | 7.899 | 0.005563 | 179.8 | 1.312 |
| Zr | 6.634 | 0.005097 | 196.2 | 1.431 |
| Ru | 7.361 | 0.005370 | 186.2 | 1.359 |
| Sm | 5.644 | 0.004700 | 212.8 | 1.553 |

All multi-EC parents and endpoints have k >> α⁻¹ (137.036),
indicating loose coupling — consistent with being outside the
rigid noble-gas closure regime.

### 5.3 Electron Binding Energies (eV) — X-Ray Data Booklet

| Element | Z | K (1s) | L₁ (2s) | L₂ (2p₁/₂) | L₃ (2p₃/₂) | M₁ (3s) |
|---------|---|--------|---------|-------------|-------------|---------|
| Ti | 22 | 4,966 | 560.9 | 460.2 | 453.8 | 58.7 |
| Ni | 28 | 8,333 | 1,009 | 870.0 | 852.7 | 110.8 |
| Ge | 32 | 11,103 | 1,415 | 1,248 | 1,217 | 180.1 |
| Zr | 40 | 17,998 | 2,532 | 2,307 | 2,222 | 430.3 |
| Ru | 44 | 22,117 | 3,224 | 2,967 | 2,838 | 586.2 |
| Sm | 62 | 46,834 | 7,745 | 7,316 | 6,716 | 1,723 |

---

## 6. L/K Capture Ratios — Core vs Outer Damage

### 6.1 Measured Shell Capture Probabilities

Source: LNHB Table de Radionucléides and evaluated ENSDF data.

**Class I — Single EC (He-3 core defects):**

| Isotope | Z | Type | P_K | P_L | P_M | L/K |
|---------|---|------|-----|-----|-----|-----|
| Be-7 | 4 | Core | 0.9078 | 0.0922 | — | 0.1016 |
| Ar-37 | 18 | Core | 0.9020 | 0.0907 | 0.0073 | 0.1006 |
| Fe-55 | 26 | Single | 0.8804 | 0.1024 | 0.0172 | 0.1163 |
| Cd-109 | 48 | Closure | 0.833 | 0.134 | 0.033 | 0.1609 |

**Class II — Double EC (spallation/supernova products):**

| Isotope | Z | Type | P_K | P_L | P_M | L/K |
|---------|---|------|-----|-----|-----|-----|
| Ti-44 | 22 | Supernova | 0.891 | 0.099 | 0.010 | 0.111 |
| Ni-56 | 28 | Supernova | 0.878 | 0.104 | 0.018 | 0.118 |
| Ge-68 | 32 | (p,2n) | 0.864 | 0.115 | 0.021 | 0.133 |
| Zr-88 | 40 | (p,2n) | 0.851 | 0.126 | 0.023 | 0.148 |

### 6.2 Analysis of L/K Ratios

The L/K ratio increases monotonically with Z across BOTH classes.
This is expected: higher-Z atoms have L-shell electrons whose
wavefunctions extend closer to the nucleus, increasing L-capture
probability relative to K.

Plotting L/K vs Z:

```text
Z:    4     18     22     26     28     32     40     48
L/K:  0.102  0.101  0.111  0.116  0.118  0.133  0.148  0.161
Type: I      I      II     I      II     II     II     I
```

The Class II isotopes (Ti-44, Ni-56, Ge-68, Zr-88) do NOT show a
statistically significant deviation from the Z-dependent trend
established by Class I isotopes.

This indicates one of two things:
1. The L/K ratio is dominated by Z-dependent atomic physics (electron
   wavefunction overlap at the nucleus), with the nuclear vacancy
   position contributing only a secondary effect
2. The nuclear vacancy position is NOT directly coupled to which
   ELECTRON shell participates in the capture — the electron capture
   occurs at the nucleus surface regardless of which nuclear shell
   has the vacancy

**Interpretation**: The L/K ratio alone does not resolve the vacancy
position. The atomic electron structure governs WHICH electron is
most likely to be at the nuclear surface, independent of which
nucleon position has the defect. A different diagnostic is required.

---

## 7. Identifying Vacancy Positions from Ionisation Records

### 7.1 The Ionisation Discontinuity Method

Each element's ionisation energy series shows sharp jumps at shell
boundaries. These jumps map the electron shell structure, which in
the SDT framework corresponds to the nuclear shell structure.

For Ge (Z=32), the IE series reveals:

| IE# | Energy (eV) | Ratio to prev | Shell transition |
|-----|------------|--------------|-----------------|
| IE₁ | 7.899 | — | 4p (outermost) |
| IE₂ | 15.935 | 2.02× | 4p → 4p |
| IE₃ | 34.058 | 2.14× | 4p → 4s |
| IE₄ | 45.716 | 1.34× | 4s → 4s |
| IE₅ | 90.50 | 1.98× | 4s → 3d |

The 4p→4s gap (IE₂ to IE₃ = 2.14×) and the 4s→3d gap
(IE₄ to IE₅ = 1.98×) indicate the shell boundaries.

### 7.2 Ga-69 → Ge-68: Where Did the Neutrons Leave?

The (p,2n) reaction on Ga-69 ejects 2 neutrons. In compound
nucleus formation, the proton enters and the compound system
(Ge-70*) evaporates 2 neutrons from the highest-energy positions.
These are the LEAST BOUND neutron positions.

Ga-69 electron configuration: [Ar]3d¹⁰4s²4p¹ (Z=31)
The 31st electron (4p¹) is the least bound (IE₁ = 5.999 eV).

In the SDT nuclear-shell mapping, the outermost nuclear positions
correspond to the outermost electron positions. The 2 evaporated
neutrons come from the outermost neutron positions — which map to
the 4p/4s region of the electron structure.

Ge-68 nuclear structure:
- Z = 32 protons fill: 1s(2) 2s(2) 2p(6) 3s(2) 3p(6) 3d(10) 4s(2) 4p(2)
- N = 36 neutrons SHOULD fill the same levels up to 36
- But N=36 with 2 vacancies means 2 neutron positions are empty

The 2 empty neutron positions correspond to what WOULD be the
37th and 38th neutrons in Ga-69 (N=38). These are the outermost
neutron levels — somewhere in the 4p/3d boundary region.

### 7.3 Ionisation Energy Mapping for Damage Sites

For each double-EC parent, the neutron vacancies are at the
outermost neutron positions of the TARGET nucleus (before spallation).
The electron binding energies at those positions indicate the
energy scale of the damage:

| Parent | Target | Target N | Vacancies at | Approx electron equiv | Energy scale |
|--------|--------|---------|-------------|----------------------|-------------|
| Ge-68 | Ga-69 | 38 | N=37,38 | 4p region | ~8–16 eV |
| Zr-88 | Y-89 | 50 | N=49,50 | 4d/5s boundary | ~7–13 eV |
| Ti-44 | (supernova) | 22 | N=23,24 | 3d/4s boundary | ~7–14 eV |
| Ni-56 | (supernova) | 28 | N=29,30 | 3d region | ~8–18 eV |

The damage sites map to the VALENCE region in all cases —
ionisation energies of order 7–18 eV, NOT the deep-core
K-shell (thousands of eV).

### 7.4 Test: IE₅ Discontinuity as Damage Boundary

For elements where the 5th ionisation energy shows a large jump,
this indicates crossing a shell boundary. If the damage is at the
outermost positions, ionising past the IE₅ discontinuity should
strip BEYOND the damaged region.

| Element | IE₄ (eV) | IE₅ (eV) | Ratio IE₅/IE₄ | Shell crossed |
|---------|---------|---------|---------------|--------------|
| Ti | 43.27 | 99.25 | **2.29** | 4s → 3p (past 3d) |
| Ge | 45.72 | 90.50 | **1.98** | 4s → 3d |
| Zr | 34.42 | 80.35 | **2.33** | 5s → 4p (past 4d) |
| Ni | 54.9 | 76.06 | 1.39 | 3d → 3d (within) |

The large jumps at IE₅ for Ti (×2.29) and Zr (×2.33) indicate
a shell boundary between the 4th and 5th ionisation. This boundary
separates the outermost shell (where damage is located) from the
next inner shell.

For Ni, the ratio is only 1.39, indicating the 5th electron is
still within the same shell (3d manifold). The damage boundary
for Ni-56 is deeper — past IE₈ or IE₁₀ (end of 3d¹⁰).

---

## 8. Ionisation-to-Halt Thresholds

### 8.1 The Principle

EC requires an electron at the nucleus surface. Stripping electrons
reduces the capture probability in proportion to the removed electron
density at r = 0. To halt EC entirely, ALL electrons with significant
nuclear overlap must be removed.

However, if the damage is at an outer nuclear position, the
corresponding electron at that position may have enhanced coupling
to the repair mechanism. Research at GSI (Darmstadt) on stored
highly-charged ions provides the empirical basis:

| Experiment | Ion | Charge state | Observation |
|-----------|-----|-------------|-------------|
| GSI 1992 | Dy-163⁶⁶⁺ | Fully stripped | Bound-state β⁻ appears (normally stable) |
| GSI | Ho-163⁶⁷⁺ | Fully stripped | EC halted (normally t½ = 4,570 y) |
| GSI | Pr-140⁵⁸⁺ | H-like (1e⁻) | EC rate ≈ P_K of neutral atom |
| GSI | Pm-142⁶⁰⁺ | H-like (1e⁻) | EC rate ≈ P_K of neutral atom |

The H-like ions (single 1s electron) show EC rates consistent with
P_K of the neutral atom. This confirms that K-shell electrons
dominate EC regardless of the nuclear vacancy position.

### 8.2 Charge States to Halt EC

To halt EC entirely, ALL bound electrons must be removed (full
ionisation). The energy required scales as Z²:

| Element | Z | Full ionisation needed | Approx total IE (keV) | K-shell BE (keV) |
|---------|---|----------------------|---------------------|-----------------|
| Ti | 22 | Ti²²⁺ | ~14 | 4.97 |
| Ni | 28 | Ni²⁸⁺ | ~30 | 8.33 |
| Ge | 32 | Ge³²⁺ | ~44 | 11.10 |
| Zr | 40 | Zr⁴⁰⁺ | ~96 | 18.00 |
| Ru | 44 | Ru⁴⁴⁺ | ~130 | 22.12 |
| Sm | 62 | Sm⁶²⁺ | ~400 | 46.83 |

### 8.3 Partial Stripping: Reducing EC Rate

Full ionisation halts EC entirely, but partial stripping can
substantially reduce the rate:

| Charge state | Electrons remaining | Approx EC rate |
|-------------|--------------------|--------------:|
| Neutral | All Z electrons | 100% |
| Li-like (Z−3)⁺ | 3 (1s² 2s¹) | ~92% |
| He-like (Z−2)⁺ | 2 (1s²) | ~91% |
| H-like (Z−1)⁺ | 1 (1s¹) | ~45% |
| Bare (Z)⁺ | 0 | **0%** |

K-shell electrons contribute ~88–91% of the EC rate. Removing
ONLY the L-shell and above reduces EC by approximately 9–12%.
Removing one K-shell electron (going from He-like to H-like)
halves the EC rate. Removing both K-shell electrons eliminates
~90% of the rate.

### 8.4 Implication for Multi-EC Chains

For the (p,2n) spallation products, the damage is at outer nuclear
positions. However, the GSI data indicate that the ELECTRON shell
responsible for the capture is always the K-shell (1s), regardless
of WHERE the nuclear damage is.

This indicates that EC is not a local nuclear-electron coupling
(damaged position ↔ corresponding electron). Rather, the K-shell
electron is captured at the nuclear surface, and the NUCLEAR
rearrangement mechanism redistributes the resulting neutron to the
vacancy site.

The He-3 core mechanism (for single EC) is a special case where
the vacancy, the capture electron, and the repair all occur at the
same position (1s).

For multi-EC (outer damage), the mechanism is:
1. K-shell electron captured at nuclear surface (as always)
2. Proton at damaged position transmuted to neutron
3. Nuclear rearrangement fills the outer vacancy
4. The K-shell is replenished by electron cascade from outer shells

---

## 9. The Neutron Budget Identity

### 9.1 For (p,2n) Reactions

The neutron count of the target equals the neutron count of the
stable endpoint:

| Reaction | Target N | Product N | Endpoint N | Target = Endpoint? |
|----------|---------|----------|-----------|-------------------|
| Ga-69(p,2n)Ge-68 | 38 | 36 | 38 (Zn-68) | **YES** |
| Y-89(p,2n)Zr-88 | 50 | 48 | 50 (Sr-88) | **YES** |

The spallation knocked out exactly 2 neutrons. Two EC events
convert 2 protons to neutrons, restoring the original neutron
count. The atom returns to the same N.

### 9.2 For Supernova Products

The α-capture chain produces N = Z (all α blocks have N = Z = 2).
The stable endpoint has N > Z. The deficit equals the EC count:

| Isotope | N_start | Z_start | N_end | Z_end | ΔN = EC count |
|---------|---------|---------|-------|-------|---------------|
| Ti-44 | 22 | 22 | 24 | 20 | 2 |
| Ni-56 | 28 | 28 | 30 | 26 | 2 |
| Se-68 | 34 | 34 | 38 | 30 | 4 |

### 9.3 Total Chain Accounting

For any multi-step EC chain of length n:
- n protons converted to neutrons
- Z decreases by n
- N increases by n
- A unchanged
- n_tri increases by 2n (He-4 core basis)
- n_deu decreases by 3n

---

## 10. Locating the Hole: Diagnostic Test Design

### 10.1 The Problem

The L/K ratio does not distinguish vacancy positions (Section 6.2).
The GSI data indicate K-capture dominates regardless of vacancy
location. How then can the vacancy position be identified?

### 10.2 Proposed Diagnostic: Partial Ionisation EC Rate Measurement

If the NUCLEAR rearrangement step (not the electron capture step)
is the rate-limiting process, then the rate may show structure
at specific partial ionisation states.

Proposed experiment:
1. Produce Ge-68 ions at various charge states:
   Ge⁰, Ge⁴⁺(4p stripped), Ge¹⁰⁺(4p+4s+3d stripped),
   Ge³⁰⁺(He-like), Ge³¹⁺(H-like), Ge³²⁺(bare)
2. Measure EC decay rate at each charge state
3. Look for rate discontinuities at specific ionisation levels

If the vacancy is at the 4p position, there may be a rate change
when the 4p electron is stripped (Ge⁴⁺), because the 4p electron
may participate in the nuclear rearrangement coupling — even though
the K-shell electron does the actual capture.

Predicted rate profile:

```text
Charge state:    0    4+    10+   30+   31+   32+
Electrons:      32    28     22     2     1     0
Expected EC:   100%  ~100%  ~100%  ~91%  ~45%   0%
If 4p coupled:  100%  <100%  <100%  ~91%  ~45%   0%
                        ↑ possible step here
```

The difference between the two profiles is measurable if the
4p electron contributes to the nuclear coupling.

### 10.3 Existing Data: EC Rate vs Charge State

The only systematic measurements are from GSI/ESR for a limited
set of ions. No data exists for Ge-68 at intermediate charge states.
This experiment has not been performed.

### 10.4 Alternative Diagnostic: Gamma-Ray Fine Structure

After EC, the daughter nucleus typically de-excites by emitting
gamma rays. The gamma-ray energies correspond to nuclear level
transitions. If the vacancy is at a specific nuclear shell, the
de-excitation spectrum may show transitions that reveal which
nuclear level was involved.

Ge-68 → Ga-68: Ge-68 decays to the ground state of Ga-68 (no
gamma emission — allowed transition, 100% to ground state). This
isotope is unfortunately uninformative for this test.

Co-56 (from Ni-56 → Co-56): Co-56 has a rich gamma spectrum with
transitions at 846.8, 1238.3, 2598.5 keV among others. The complex
decay scheme involves multiple nuclear levels, and the specific
levels populated indicate which nuclear shells are rearranging.

---

## 11. Summary of Findings

| # | Finding | Status | Evidence |
|---|---------|--------|---------|
| 1 | Six double-EC chains identified | Confirmed | NNDC data |
| 2 | Triple and quadruple EC chains exist | Confirmed | Se-68 (4-step) |
| 3 | Spallation (p,2n) ejects exact neutrons EC replaces | Confirmed | N(target)=N(endpoint) |
| 4 | Supernova products: N=Z → N>Z via double EC | Confirmed | Ti-44, Ni-56 |
| 5 | All multi-EC intermediates are grammar-valid | Confirmed | He-4 core: all n_tri≥0, n_deu≥0 |
| 6 | L/K ratio does not resolve vacancy position | Indicated | Z-dependence dominates |
| 7 | K-capture dominates regardless of vacancy site | Indicated | GSI H-like ion data |
| 8 | Damage is at outermost neutron positions | Indicated | Spallation energetics |
| 9 | Full ionisation halts EC entirely | Confirmed | GSI Ho-163 experiment |
| 10 | Partial ionisation EC rate test: not yet performed | Proposed | No data exists |

---

## 12. Open Questions

1. **Can partial ionisation reveal vacancy positions?**
   The proposed Ge-68 charge-state scan (Section 10.2) has not been
   performed. If the EC rate shows a step at the 4p ionisation level,
   this would confirm outer-shell coupling.

2. **Does the nuclear rearrangement step have a measurable timescale?**
   The EC event itself is effectively instantaneous. The subsequent
   nuclear rearrangement (redistributing the new neutron to the
   vacancy site) may have a finite timescale detectable through
   delayed gamma emission.

3. **Why do (α,3n) products do only 2 EC instead of 3?**
   The Ru-97 and Sm-145 chains eject 3 neutrons in production but
   require only 2 EC events. The third neutron deficit is compensated
   by the incoming α particle contributing 2 extra neutrons (4 nucleons
   in, 3 out = net +1 nucleon). This accounting requires further
   verification.

4. **Can the Se-68 quadruple chain be used as a cascade timer?**
   Each step has a well-defined half-life (35s → 151s → 271d → 68min).
   The cascade could serve as a multi-timescale nuclear clock if the
   individual steps can be selectively halted by ionisation.

---

## 13. Data Sources

| Source | Access | Items used |
|--------|--------|-----------|
| NIST ASD | physics.nist.gov/asd | Ionisation energies, all elements |
| LNHB Table de Radionucléides | lnhb.fr | P_K, P_L shell capture fractions |
| X-Ray Data Booklet (LBNL) | xdb.lbl.gov | K, L, M binding energies |
| NNDC/NUBASE2020 | nndc.bnl.gov | Half-lives, decay modes |
| GSI Publications | gsi.de | Charge-state EC measurements |
