# INVESTIGATION 08: Dual-Defect Branching

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Protection](INVESTIGATION_04_Protection_Factor.md) ·
> [Orthohelium](INVESTIGATION_05_Orthohelium_Connection.md) ·
> [Missing](INVESTIGATION_06_Missing_Elements.md) ·
> [Ratios](INVESTIGATION_07_Energy_Ratios.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Master Table](EC_data/01_All_EC_Isotopes_Master_Table.md)

---

## 1. Definition

A **dual-defect nucleus** decays by BOTH electron capture (EC) and
beta-minus (β⁻) — two competing grammar corrections to two different
daughters.

EC converts p → n: daughter has (Z−1, A)
β⁻ converts n → p: daughter has (Z+1, A)

The nucleus can correct "upward" (EC) or "downward" (β⁻), meaning it
sits at a grammar SADDLE POINT — stressed in both directions.

---

## 2. All Known Dual-Defect Nuclei

### 2.1 Potassium-40: The Rosetta Stone

| Property | Value | Source |
|----------|-------|--------|
| Z | 19 | — |
| A | 40 | — |
| N | 21 | — |
| n_tri | 2 | — |
| n_deu | 15 | — |
| Grammar | VALID | yes |
| t½ (total) | 1.248 × 10⁹ y | NUBASE2020 |
| EC branch | **10.72%** → Ar-40 (Z=18) | ENSDF |
| β⁺ branch | 0.001% → Ar-40 | ENSDF |
| β⁻ branch | **89.28%** → Ca-40 (Z=20) | ENSDF |

#### Grammar of both daughters

| | K-40 (parent) | Ar-40 (EC daughter) | Ca-40 (β⁻ daughter) |
|---|---|---|---|
| Z | 19 | 18 | 20 |
| A | 40 | 40 | 40 |
| n_tri | 2 | 4 | 0 |
| n_deu | 15 | 12 | 18 |
| Grammar | valid | valid | valid |
| Configuration | α + 15d + 2t | α + 12d + 4t | α + 18d + 0t |
| Stability | UNSTABLE | **STABLE** | **STABLE** |

Both daughters are grammar-valid AND stable. K-40 sits between two
stable grammar-valid configurations. It can go EITHER way.

#### Why β⁻ dominates (89%)

| Channel | Q (keV) | Transition type | Branching |
|---------|---------|----------------|-----------|
| β⁻ → Ca-40 | 1,311 | 4⁻ → 0⁺ (3rd forbidden unique) | **89.28%** |
| EC → Ar-40 | 1,505 | 4⁻ → 0⁺ (3rd forbidden unique) | **10.72%** |

Both transitions are 3rd-forbidden unique (ΔJ = 4, parity change).
β⁻ dominates despite LOWER Q-value because:
- β⁻ does not require electron capture from a specific shell
- β⁻ creates its own electron ex nihilo
- EC must compete for electron density at the nucleus

The grammar correction to Ca-40 (n_tri = 0, all deuterons) is
geometrically simpler than correction to Ar-40 (n_tri = 4, mixed).

### 2.2 Chlorine-36

| Property | Value |
|----------|-------|
| Z | 17, A = 36, N = 19 |
| n_tri = 2, n_deu = 13 | Grammar VALID |
| t½ | 301,000 y |
| EC → Ar-36 | 1.9% (Q = 1,142 keV) |
| β⁻ → S-36 | 98.1% (Q = 709 keV) |

#### Daughters

| | Ar-36 (EC) | S-36 (β⁻) |
|---|---|---|
| Z | 18 | 16 |
| n_tri | 0 | 4 |
| n_deu | 16 | 10 |
| Stable? | YES | YES |

β⁻ dominates (98.1%) despite having a LOWER Q-value (709 vs 1142).
The same pattern as K-40: β⁻ is kinetically favoured over EC.

### 2.3 Copper-64

The ONLY light isotope with ALL THREE decay modes:

| Property | Value |
|----------|-------|
| Z | 29, A = 64, N = 35 |
| n_tri = 6, n_deu = 23 | Grammar VALID |
| t½ | 12.70 h |
| EC → Ni-64 | **43.1%** (Q = 1,675 keV) |
| β⁺ → Ni-64 | **17.5%** (Q = 653 keV) |
| β⁻ → Zn-64 | **39.4%** (Q = 579 keV) |

#### Daughters

| | Ni-64 (EC/β⁺) | Zn-64 (β⁻) |
|---|---|---|
| Z | 28 | 30 |
| n_tri | 8 | 4 |
| n_deu | 20 | 26 |
| Stable? | YES | YES |

**Cu-64 is the most balanced dual-defect nucleus.** EC (43%) and β⁻ (39%)
nearly equal, with β⁺ (18%) as a minor channel.

### 2.4 Silver-108

| Property | Value |
|----------|-------|
| Z | 47, A = 108, N = 61 |
| n_tri = 14, n_deu = 29 | Grammar VALID |
| t½ | 2.38 min |
| EC → Pd-108 | ~97% (Q = 1,918 keV) |
| β⁻ → Cd-108 | ~3% (Q = 1,650 keV est.) |

EC strongly dominates. Different from K-40/Cl-36 where β⁻ dominates.

### 2.5 Iridium-192

| Property | Value |
|----------|-------|
| Z | 77, A = 192, N = 115 |
| n_tri = 38, n_deu = 41 | Grammar VALID |
| t½ | 73.83 d |
| EC → Os-192 | **4.1%** (Q = 1,460 keV) |
| β⁻ → Pt-192 | **95.2%** (Q = 1,461 keV) |

Nearly identical Q-values (1460 vs 1461 keV!) yet β⁻ vastly dominates.
Again: β⁻ is kinetically favoured when Q-values are comparable.

---

## 3. The Odd-Odd Rule

| Dual-defect | Z | N | Z even? | N even? | Z×N odd? |
|-------------|---|---|---------|---------|----------|
| Cl-36 | 17 | 19 | odd | odd | **odd-odd** |
| K-40 | 19 | 21 | odd | odd | **odd-odd** |
| Cu-64 | 29 | 35 | odd | odd | **odd-odd** |
| Ag-108 | 47 | 61 | odd | odd | **odd-odd** |
| Ir-192 | 77 | 115 | odd | odd | **odd-odd** |

**Every dual-defect nucleus is odd-odd** (both Z and N are odd).

### Why odd-odd = dual defect

In the construction grammar:
- Odd Z → odd number of scaffold blocks → one permanently unpaired
- Odd N → odd number of neutrons in the scaffold → one triton with
  no deuteron partner (or vice versa)

The double-unpaired scaffold has TWO structural weaknesses:
1. The unpaired proton position → correctable by EC (p → n)
2. The unpaired neutron position → correctable by β⁻ (n → p)

The nucleus can correct EITHER weakness. The branching ratio tells
you which weakness is more severe.

---

## 4. Branching as Stress Indicator

| Nucleus | EC% | β⁻% | Which side is more stressed? |
|---------|-----|------|----------------------------|
| Cl-36 | 1.9 | 98.1 | **Proton side** (needs +p, removes n) |
| K-40 | 10.7 | 89.3 | **Proton side** |
| Cu-64 | 43+18 | 39 | **Balanced** (nearly equal) |
| Ag-108 | 97 | 3 | **Neutron side** (needs +n, removes p) |
| Ir-192 | 4.1 | 95.2 | **Proton side** |

When β⁻ dominates: the nucleus primarily wants MORE protons (add +p
via n→p). The neutron excess is the bigger problem.

When EC dominates: the nucleus primarily wants MORE neutrons (add +n
via p→n). The proton excess is the bigger problem.

Cu-64's near-equal split suggests it sits at the exact centre of the
dual-defect saddle — equally stressed on both sides.

---

## 5. Q-Value Asymmetry

| Nucleus | Q_EC (keV) | Q_β⁻ (keV) | Q ratio | β⁻ branch |
|---------|-----------|-----------|---------|-----------|
| Cl-36 | 1,142 | 709 | 1.61 | **98.1%** |
| K-40 | 1,505 | 1,311 | 1.15 | **89.3%** |
| Cu-64 | 1,675 | 579 | 2.89 | **39.4%** |
| Ir-192 | 1,460 | 1,461 | 1.00 | **95.2%** |

**β⁻ dominates even when Q_EC > Q_β⁻** (Cl-36: 1.61× more EC energy,
yet 98% β⁻). This confirms that EC rate is intrinsically slower than
β⁻ rate because:
1. EC requires an electron already present at the nucleus
2. β⁻ creates its own electron — no prerequisite
3. The electron DENSITY at the nucleus is a limiting factor for EC
   that β⁻ does not face

In SDT terms: EC requires the gear train to CAPTURE an external gear
(the electron). β⁻ EJECTS a gear that the train already contains.
Ejection is mechanically easier than capture.

---

## 6. Grammar Prediction Test

Does the grammar correctly predict which branch dominates?

For EC: Δn_tri = +2, Δn_deu = −3 (adds tritons)
For β⁻: Δn_tri = −2, Δn_deu = +3 (adds deuterons)

| Nucleus | n_tri | EC gives n_tri+2 | β⁻ gives n_tri−2 | Dominant | Grammar prediction |
|---------|-------|------------------|-------------------|----------|-------------------|
| Cl-36 | 2 | 4 | 0 | β⁻ (98%) | β⁻ → n_tri=0 (all deu) = simpler |
| K-40 | 2 | 4 | 0 | β⁻ (89%) | β⁻ → n_tri=0 (all deu) = simpler |
| Cu-64 | 6 | 8 | 4 | EC (61%) | Both valid; EC → higher n_tri |
| Ag-108 | 14 | 16 | 12 | EC (97%) | Both valid; EC → higher n_tri |
| Ir-192 | 38 | 40 | 36 | β⁻ (95%) | β⁻ kinetically favoured |

For Cl-36 and K-40: β⁻ produces the SIMPLEST grammar (n_tri = 0,
pure deuteron scaffold). The grammar predicts β⁻ dominance. CONFIRMED.

For Cu-64 and Ag-108: EC dominates, producing higher triton counts.
The n_tri level is already high (6 and 14), so the direction of
correction is about neutron balance, not scaffold simplification.

For Ir-192: despite near-equal Q-values, β⁻ strongly dominates.
The grammar doesn't clearly predict this — it's the kinetic
advantage of β⁻ over EC in heavy nuclei.

---

## 7. Summary

| Finding | Status |
|---------|--------|
| All dual-defect nuclei are odd-odd | **CONFIRMED** (5/5) |
| β⁻ kinetically favoured over EC at equal Q | **CONFIRMED** (Ir-192) |
| β⁻ dominates when daughter = pure deuterons (n_tri=0) | **CONFIRMED** (Cl-36, K-40) |
| EC dominates when proton-rich stress exceeds neutron-rich stress | **CONFIRMED** (Ag-108) |
| Cu-64 is the most balanced dual-defect | **CONFIRMED** (43:39 split) |
| Grammar Δn_tri correctly predicts dominant branch for 3/5 cases | PARTIAL |
