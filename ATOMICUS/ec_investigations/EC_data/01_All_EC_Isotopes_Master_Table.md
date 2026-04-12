# Master Table: All EC-Capable Isotopes

> Navigation: [Subshell Map](02_Subshell_Closure_Map.md) · [L/K Ratios](03_LK_Capture_Ratios.md) ·
> [Ionisation](04_Ionisation_Series.md) · [Protection](05_Protection_Factors.md) ·
> [Energy Ratios](06_Energy_Ratios_And_Constants.md)
>
> Investigations: [Grammar](../INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](../INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](../INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Protection](../INVESTIGATION_04_Protection_Factor.md) ·
> [Orthohelium](../INVESTIGATION_05_Orthohelium_Connection.md) ·
> [Missing](../INVESTIGATION_06_Missing_Elements.md) ·
> [Ratios](../INVESTIGATION_07_Energy_Ratios.md) ·
> [Dual Defect](../INVESTIGATION_08_Dual_Defect_Branching.md) ·
> [FINAL](../FINAL_REPORT.md)

---

## Data Sources

All values from: NNDC NuDat 3.0, NUBASE2020, LNHB/CEA Table de Radionucléides,
AME2020 (Atomic Mass Evaluation 2020). Where sources disagree, NUBASE2020 preferred.

## Grammar Decomposition Formula (SDT Rule 2)

For any isotope with Z protons, A nucleons, beyond the alpha core (Z=2, A=4):

```
n_tri = A - 2Z        (triton count: number of 1p+2n blocks)
n_deu = 3Z - A - 2    (deuteron count: number of 1p+1n blocks)
Grammar VALID if: n_tri ≥ 0 AND n_deu ≥ 0
```

## Constants

| Constant | Value | Symbol |
|----------|-------|--------|
| Free neutron t½ | 612 s (PDG avg) | t½_n |
| Free neutron Q | 782 keV | Q_n |
| β⁺ threshold | 1022 keV (2 × m_e c²) | Q_β⁺_min |
| Proton/electron mass ratio | 1836.15 | m_p/m_e |
| Fine structure constant⁻¹ | 137.036 | α⁻¹ |
| Rydberg energy | 13.606 eV | E_R |

---

## Band 1: Shell 2 (Z = 3–10)

**Subshells**: 2s (Z=3–4), 2p (Z=5–10)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | β⁺% | Daughter | D.stable? | D.n_tri | D.n_deu | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|------|----------|-----------|---------|---------|----------|---------|
| 4 | Be | 7 | 3 | **−1** | **5** | **NO** | 53.22 d | 4,598,208 | 862 | No | 100 | 0 | Li-7 | YES | 1 | 4 | 2s² | 80 |
| 6 | C | 11 | 5 | **−1** | **11** | **NO** | 20.36 min | 1,221.6 | 1,982 | Yes | 0.2 | 99.8 | B-11 | YES | 1 | 10 | 2p² | 1,200 |
| 7 | N | 13 | 6 | **−1** | **14** | **NO** | 9.965 min | 597.9 | 2,221 | Yes | 0.2 | 99.8 | C-13 | YES | 1 | 13 | 2p³ | 1,439 |
| 8 | O | 15 | 7 | **−1** | **17** | **NO** | 122.24 s | 122.24 | 2,754 | Yes | 0.1 | 99.9 | N-15 | YES | 1 | 16 | 2p⁴ | 1,972 |
| 9 | F | 18 | 9 | 0 | 7 | yes | 109.77 min | 6,586.2 | 1,656 | Yes | 3.3 | 96.7 | O-18 | YES | 2 | 6 | 2p⁵ | 874 |
| 10 | Ne | 19 | 9 | **−1** | **23** | **NO** | 17.22 s | 17.22 | 3,239 | Yes | 0.05 | 99.95 | F-19 | YES | 1 | 22 | 2p⁶ | 2,457 |

### Shell 2 Summary

- **Every n_tri = −1 isotope**: Be-7, C-11, N-13, O-15, Ne-19. ALL grammar-INVALID.
- **F-18** is the sole grammar-valid EC parent in this band (n_tri = 0).
- **All daughters** are grammar-valid (n_tri = +1 for the invalids, n_tri = +2 for F-18→O-18).
- **Grammar penalty** (Q_EC − 782 keV) ranges from 80 keV (Be-7) to 2,457 keV (Ne-19).
- **Be-7 is the only pure EC** in this band. All others have Q > 1022, enabling β⁺.

---

## Band 2: Shell 3 (Z = 11–18)

**Subshells**: 3s (Z=11–12), 3p (Z=13–18)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | β⁺% | Daughter | D.stable? | D.n_tri | D.n_deu | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|------|----------|-----------|---------|---------|----------|---------|
| 11 | Na | 22 | 11 | 0 | 9 | yes | 2.603 y | 82,108,000 | 2,842 | Yes | 9.6 | 90.4 | Ne-22 | YES | 2 | 8 | 3s¹ | 2,060 |
| 12 | Mg | 23 | 11 | **−1** | **14** | **NO** | 11.305 s | 11.305 | 4,056 | Yes | 0.03 | 99.97 | Na-23 | YES | 1 | 13 | 3s² | 3,274 |
| 13 | Al | 26 | 13 | 0 | 13 | yes | 717,000 y | 2.262×10¹³ | 4,004 | Yes | 18 | 82 | Mg-26 | YES | 2 | 12 | 3p¹ | 3,222 |
| 14 | Si | 27 | 13 | **−1** | **17** | **NO** | 4.16 s | 4.16 | 4,812 | Yes | — | ~100 | Al-27 | YES | 1 | 16 | 3p² | 4,030 |
| 15 | P | 30 | 15 | 0 | 15 | yes | 2.498 min | 149.9 | 4,232 | Yes | 0.07 | 99.93 | Si-30 | YES | 2 | 14 | 3p³ | 3,450 |
| 16 | S | 31 | 15 | **−1** | **20** | **NO** | 2.572 s | 2.572 | 5,396 | Yes | — | ~100 | P-31 | YES | 1 | 19 | 3p⁴ | 4,614 |
| 17 | Cl | 36 | 19 | 2 | 13 | yes | 301,000 y | 9.496×10¹² | 1,142 | Yes | — | — | Ar-36 (EC) / S-36 (β⁻) | YES | — | — | 3p⁵ | 360 |
| 18 | Ar | 37 | 19 | 1 | 15 | yes | 35.04 d | 3,027,456 | 814 | No | 100 | 0 | Cl-37 | YES | 3 | 12 | **3p⁶** | 32 |

### Shell 3 Summary

- **n_tri = −1 invalids**: Mg-23, Si-27, S-31. Same pattern as Shell 2.
- **Ar-37 is the pure EC** at the 3p⁶ closure. Q = 814 keV < 1022. t½ = 35 days.
- **Cl-36** is a *dual-defect* nucleus: EC to Ar-36 AND β⁻ to S-36.
- **Al-26** has extraordinarily long t½ (717,000 y) despite Q = 4,004 keV.
  This is a **forbidden transition** (ΔJ = 5, 5⁺ → 0⁺). The scaffold
  geometry blocks the direct transition.
- **Grammar penalty**: Ar-37 has only 32 keV penalty (almost bare n-p difference!).

---

## Band 3: Shell 4s / 3d (Z = 19–30)

**Subshells**: 4s (Z=19–20), 3d (Z=21–30)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | β⁺% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|------|----------|-----------|----------|---------|
| 19 | K | 40 | 21 | 2 | 15 | yes | 1.248×10⁹ y | 3.94×10¹⁶ | 1,505 | Yes | 10.7 | 0.001 | Ar-40 (EC) / Ca-40 (β⁻) | YES | **4s¹** | 723 |
| 20 | Ca | 41 | 21 | 1 | 19 | yes | 99,400 y | 3.136×10¹² | 421 | No | 100 | 0 | K-41 | YES | **4s²** | −361 |
| 21 | Sc | 44 | 23 | 2 | 19 | yes | 3.97 h | 14,292 | 3,653 | Yes | 5.7 | 94.3 | Ca-44 | YES | 3d¹ | 2,871 |
| 22 | Ti | 44 | 22 | 0 | 22 | yes | 59.1 y | 1.865×10⁹ | 268 | No | 100 | 0 | Sc-44 | No (3.97h) | 3d² | −514 |
| 23 | V | 49 | 26 | 3 | 20 | yes | 330 d | 2.851×10⁷ | 602 | No | 100 | 0 | Ti-49 | YES | 3d³ | −180 |
| 24 | Cr | 51 | 27 | 3 | 21 | yes | 27.7 d | 2,393,280 | 753 | No | 100 | 0 | V-51 | YES | 3d⁴ | −29 |
| 25 | Mn | 54 | 29 | 4 | 21 | yes | 312.2 d | 2.698×10⁷ | 1,377 | Yes | 100 | <0.01 | Cr-54 | YES | 3d⁵ | 595 |
| 26 | Fe | 55 | 29 | 3 | 26 | yes | 2.744 y | 8.658×10⁷ | 231 | No | 100 | 0 | Mn-55 | YES | 3d⁶ | −551 |
| 27 | Co | 57 | 30 | 3 | 28 | yes | 271.8 d | 2.348×10⁷ | 836 | No | 100 | 0 | Fe-57 | YES | 3d⁷ | 54 |
| 28 | Ni | 56 | 28 | 0 | 30 | yes | 6.075 d | 524,880 | 2,136 | Yes | 100 | <0.01 | Co-56 | No (77d) | 3d⁸ | 1,354 |
| 29 | Cu | 64 | 35 | 6 | 23 | yes | 12.70 h | 45,720 | 1,675 | Yes | 43.1 | 17.5 | Ni-64 (EC) / Zn-64 (β⁻) | YES | 3d⁹ | 893 |
| 30 | Zn | 65 | 35 | 5 | 28 | yes | 243.93 d | 2.108×10⁷ | 1,352 | Yes | 98.5 | 1.5 | Cu-65 | YES | **3d¹⁰** | 570 |

### Shell 4s/3d Summary

- **K-40** is the dual-defect Rosetta Stone: EC (10.7%) + β⁻ (89.3%).
- **Ca-41** is pure EC at the 4s² closure. Q = 421, t½ = 99,400 years.
- **NEGATIVE grammar penalties** appear: Ca-41 (−361), Ti-44 (−514), Fe-55 (−551).
  These have Q < Q_n (782 keV). The grammar penalty is negative because the
  daughter is LESS tightly bound per nucleon than the free n→p difference predicts.
  The scaffold reorganisation COSTS energy rather than releasing it.
- **Fe-55**: Pure EC, Q = 231 keV, t½ = 2.74 years. One of the lowest Q-values.
- **Cu-64**: Triple-branch (EC + β⁺ + β⁻). The only light isotope with all three.

---

## Band 4: Shell 4p–5s (Z = 31–38)

**Subshells**: 4p (Z=31–36), 5s (Z=37–38)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | β⁺% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|------|----------|-----------|----------|---------|
| 31 | Ga | 67 | 36 | 5 | 28 | yes | 3.261 d | 281,750 | 1,001 | No | 100 | 0 | Zn-67 | YES | 4p¹ | 219 |
| 32 | Ge | 68 | 36 | 4 | 32 | yes | 270.9 d | 2.341×10⁷ | 107 | No | 100 | 0 | Ga-68 | No (67m) | 4p² | −675 |
| 33 | As | 73 | 40 | 7 | 26 | yes | 80.3 d | 6,937,920 | 341 | No | 100 | 0 | Ge-73 | YES | 4p³ | −441 |
| 34 | Se | 75 | 41 | 7 | 27 | yes | 119.78 d | 1.035×10⁷ | 864 | No | 100 | 0 | As-75 | YES | 4p⁴ | 82 |
| 35 | Br | 77 | 42 | 7 | 28 | yes | 57.04 h | 205,344 | 1,365 | Yes | 99.3 | 0.7 | Se-77 | YES | 4p⁵ | 583 |
| 36 | Kr | 81 | 45 | 9 | 25 | yes | 229,000 y | 7.226×10¹² | 281 | No | 100 | 0 | Br-81 | YES | **4p⁶** | −501 |
| 37 | Rb | 83 | 46 | 9 | 26 | yes | 86.2 d | 7,447,680 | 920 | No | 100 | 0 | Kr-83 | YES | **5s¹** | 138 |
| 38 | Sr | 85 | 47 | 9 | 27 | yes | 64.85 d | 5,603,040 | 1,065 | Yes | ~100 | <0.01 | Rb-85 | YES | **5s²** | 283 |

### Shell 4p/5s Summary

- **Kr-81** is the pure EC at the 4p⁶ closure. Q = 281 keV. t½ = 229,000 years.
  Longest-lived pure EC in this range (lowest Q).
- **Ge-68** has Q = 107 keV — one of the lowest Q-values in the entire table.
  Penalty = −675. The scaffold pays 675 keV to reorganise.
- **Se-75**: Q = 864 keV. Penalty = +82 keV. Almost identical to Be-7 (862/80).
  Same Q, same penalty band, but Z=34 vs Z=4. Different shell, same grammar cost.

---

## Band 5: Shell 4d (Z = 39–48)

**Subshells**: 4d (Z=39–48)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|----------|-----------|----------|---------|
| 39 | Y | 88 | 49 | 10 | 27 | yes | 106.6 d | 9,210,240 | 3,623 | Yes | 99.8 | Rb-88? No: Sr-88 | YES | 4d¹ | 2,841 |
| 40 | Zr | 88 | 48 | 8 | 34 | yes | 83.4 d | 7,205,760 | 674 | No | 100 | Y-88 | No (107d) | 4d² | −108 |
| 41 | Nb | 91 | 50 | 9 | 32 | yes | 680 y | 2.146×10¹⁰ | 1,253 | Yes | 100 | Zr-91 | YES | 4d³ | 471 |
| 42 | Mo | 93 | 51 | 9 | 33 | yes | 4,000 y | 1.262×10¹¹ | 406 | No | 100 | Nb-93 | YES | 4d⁴ | −376 |
| 43 | Tc | 97 | 54 | 11 | 30 | yes | 4.21×10⁶ y | 1.328×10¹⁴ | 320 | No | 100 | Mo-97 | YES | 4d⁵ | −462 |
| 44 | Ru | 97 | 53 | 9 | 35 | yes | 2.84 d | 245,376 | 1,104 | Yes | ~100 | Tc-97 | 4.21My EC | 4d⁶ | 322 |
| 45 | Rh | 101 | 56 | 11 | 32 | yes | 3.3 y | 1.041×10⁸ | 543 | No | 100 | Ru-101 | YES | 4d⁷ | −239 |
| 46 | Pd | 103 | 57 | 11 | 33 | yes | 16.99 d | 1,468,336 | 575 | No | 100 | Rh-103 | YES | 4d⁸ | −207 |
| 47 | Ag | 108 | 61 | 14 | 29 | yes | 2.38 min | 142.8 | 1,918 | Yes | ~97 | Pd-108 (EC) / Cd-108 (β⁻) | YES | 4d⁹ | 1,136 |
| 48 | Cd | 109 | 61 | 13 | 35 | yes | 461.4 d | 3.987×10⁷ | 214 | No | 100 | Ag-109 | YES | **4d¹⁰** | −568 |

### Shell 4d Summary

- **Tc-97**: EC with t½ = 4.21 million years. Q = 320 keV. The longest-lived
  Tc isotope. Grammar-valid but has unpaired odd-block scaffold.
- **Cd-109** is the pure EC at the 4d¹⁰ closure. Q = 214 keV. t½ = 461 days.
- **Ag-108**: Dual-defect (EC + β⁻), like K-40 and Cl-36.
- **Negative penalties dominate** this band: Mo-93 (−376), Tc-97 (−462),
  Cd-109 (−568). These scaffolds pay more to reorganise than the bare
  n-p mass difference provides.

---

## Band 6: Shell 5p (Z = 49–54)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|----------|-----------|----------|---------|
| 49 | In | 111 | 62 | 13 | 36 | yes | 2.805 d | 242,352 | 862 | No | 100 | Cd-111 | YES | 5p¹ | 80 |
| 50 | Sn | 113 | 63 | 13 | 37 | yes | 115.1 d | 9,944,640 | 1,036 | Yes | ~100 | In-113 | YES | 5p² | 254 |
| 51 | Sb | 119 | 68 | 17 | 33 | yes | 38.19 h | 137,484 | 583 | No | 100 | Sn-119 | YES | 5p³ | −199 |
| 52 | Te | 121 | 69 | 17 | 34 | yes | 19.17 d | 1,656,288 | 1,054 | Yes | ~100 | Sb-121 | YES | 5p⁴ | 272 |
| 53 | I | 125 | 72 | 19 | 32 | yes | 59.40 d | 5,132,160 | 186 | No | 100 | Te-125 | YES | 5p⁵ | −596 |
| 54 | Xe | 127 | 73 | 19 | 33 | yes | 36.34 d | 3,139,776 | 662 | No | 100 | I-127 | YES | **5p⁶** | −120 |

### Shell 5p Summary

- **Xe-127** is the pure EC at the 5p⁶ closure. Q = 662 keV. t½ = 36.3 days.
  Part of the **~35 day cluster** (with Ar-37 at 35.0 d and Yb-169 at 32.0 d).
- **In-111**: Q = 862 keV — EXACTLY the same as Be-7! Penalty = 80 keV —
  EXACTLY the same as Be-7! Z=49 vs Z=4. Same grammar cost, 12 shells apart.
- **I-125**: Q = 186 keV, pure EC, t½ = 59.4 days. Used in medical imaging.
  Penalty = −596 keV (high reorganisation cost).

---

## Band 7: Shell 6s / 4f / 5d (Z = 55–80)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|----------|-----------|----------|---------|
| 55 | Cs | 131 | 76 | 21 | 34 | yes | 9.689 d | 837,130 | 358 | No | 100 | Xe-131 | YES | 6s¹ | −424 |
| 56 | Ba | 133 | 77 | 21 | 35 | yes | 10.551 y | 3.329×10⁸ | 517 | No | 100 | Cs-133 | YES | **6s²** | −265 |
| 57 | La | 137 | 80 | 23 | 34 | yes | 60,000 y | 1.893×10¹² | 600 | No | 100 | Ba-137 | YES | 5d¹/4f | −182 |
| 58 | Ce | 139 | 81 | 23 | 35 | yes | 137.6 d | 1.189×10⁷ | 270 | No | 100 | La-139 | YES | 4f² | −512 |
| 61 | Pm | 145 | 84 | 23 | 40 | yes | 17.7 y | 5.583×10⁸ | 163 | No | 100 | Nd-145 | YES | 4f⁵ | −619 |
| 62 | Sm | 145 | 83 | 21 | 44 | yes | 340 d | 2.938×10⁷ | 620 | No | 100 | Pm-145 | 17.7y EC | 4f⁶ | −162 |
| 63 | Eu | 150 | 87 | 24 | 39 | yes | 36.9 y | 1.164×10⁹ | 2,261 | Yes | ~100 | Sm-150 | YES | 4f⁷ | 1,479 |
| 64 | Gd | 153 | 89 | 25 | 39 | yes | 240.4 d | 2.078×10⁷ | 484 | No | 100 | Eu-153 | YES | 4f⁸ | −298 |
| 67 | Ho | 163 | 96 | 29 | 38 | yes | 4,570 y | 1.442×10¹¹ | 2.8 | No | 100 | Dy-163 | YES | 4f¹¹ | −779 |
| 69 | Tm | 167 | 98 | 29 | 40 | yes | 9.25 d | 799,200 | 748 | No | 100 | Er-167 | YES | 4f¹³ | −34 |
| 70 | Yb | 169 | 99 | 29 | 41 | yes | 32.03 d | 2,767,392 | 909 | No | 100 | Tm-169 | YES | **4f¹⁴** | 127 |
| 71 | Lu | 174 | 103 | 32 | 39 | yes | 3.31 y | 1.044×10⁸ | 1,374 | Yes | ~100 | Yb-174 | YES | 5d¹/4f | 592 |
| 72 | Hf | 175 | 103 | 31 | 43 | yes | 70.0 d | 6,048,000 | 684 | No | 100 | Lu-175 | YES | 5d² | −98 |
| 73 | Ta | 179 | 106 | 33 | 42 | yes | 1.82 y | 5.742×10⁷ | 110 | No | 100 | Hf-179 | YES | 5d³ | −672 |
| 74 | W | 181 | 107 | 33 | 43 | yes | 121.2 d | 1.047×10⁷ | 188 | No | 100 | Ta-181 | YES | 5d⁴ | −594 |
| 76 | Os | 185 | 109 | 33 | 47 | yes | 93.6 d | 8,087,040 | 1,013 | No | 100 | Re-185 | YES | 5d⁶ | 231 |
| 77 | Ir | 192 | 115 | 38 | 41 | yes | 73.83 d | 6,378,912 | 1,460 | Yes | ~100 | Os-192 (EC) / Pt-192 (β⁻) | YES | 5d⁷ | 678 |
| 78 | Pt | 193 | 115 | 37 | 45 | yes | 50 y | 1.577×10⁹ | 56 | No | 100 | Ir-193 | YES | 5d⁸ | −726 |
| 79 | Au | 195 | 116 | 37 | 46 | yes | 186.1 d | 1.608×10⁷ | 227 | No | 100 | Pt-195 | YES | 5d⁹ | −555 |
| 80 | Hg | 197 | 117 | 37 | 47 | yes | 64.14 h | 230,904 | 600 | No | 100 | Au-197 | YES | **5d¹⁰** | −182 |

---

## Band 8: Shell 6p (Z = 81–86)

| Z | Elem | A | N | n_tri | n_deu | Valid? | t½ | t½ (s) | Q_EC (keV) | β⁺? | EC% | Daughter | D.stable? | Subshell | Penalty |
|---|------|---|---|-------|-------|--------|--------|---------|------------|------|-----|----------|-----------|----------|---------|
| 81 | Tl | 201 | 120 | 39 | 44 | yes | 3.042 d | 262,829 | 483 | No | 100 | Hg-201 | YES | 6p¹ | −299 |
| 82 | Pb | 205 | 123 | 41 | 43 | yes | 15.3×10⁶ y | 4.828×10¹⁴ | 51 | No | 100 | Tl-205 | YES | 6p² | −731 |
| 83 | Bi | 207 | 124 | 41 | 44 | yes | 31.55 y | 9.955×10⁸ | 2,398 | Yes | ~100 | Pb-207 | YES | 6p³ | 1,616 |

### Shell 6p Summary

- **Pb-205**: Q = 51 keV, t½ = 15.3 million years. One of the LOWEST Q-values
  in the entire table. Almost no energy available. Penalty = −731.
- **Ho-163** (Q = 2.8 keV!) has the absolute lowest Q-value of ANY EC isotope.
  Just 2.8 keV available. t½ = 4,570 years.

---

## Extreme Records

| Record | Isotope | Value |
|--------|---------|-------|
| Lowest Q_EC | **Ho-163** | **2.8 keV** |
| Second lowest Q | Pb-205 | 51 keV |
| Third lowest Q | Pt-193 | 56 keV |
| Highest Q (pure EC) | **Yb-169** | **909 keV** |
| Shortest t½ (band 1 β⁺) | S-31 | 2.57 s |
| Longest t½ (EC) | **K-40** | **1.248×10⁹ y** |
| Longest t½ (pure EC) | **Pb-205** | **15.3×10⁶ y** |
| Most negative penalty | **Ho-163** | **−779 keV** |
| Be-7 Q twin | **In-111** | **862 keV (exact match)** |
| Be-7/Ar-37 t½ cluster | Ar-37, Xe-127, Yb-169 | 35.0d, 36.3d, 32.0d |

---

## Computed Statistics

**Total isotopes in table**: 56 representative EC isotopes

**Grammar-invalid parents (n_tri < 0)**: 9 (all in Z ≤ 18)

**Grammar-valid parents (n_tri ≥ 0)**: 47 (all in Z ≥ 9)

**Pure EC (Q < 1022 keV)**: 42 isotopes (75%)

**Pure EC at subshell closures**: Be(2s²), Ar(3p⁶), Ca(4s²), Kr(4p⁶),
Cd(4d¹⁰), Xe(5p⁶), Ba(6s²), Yb(4f¹⁴), Hg(5d¹⁰) — **9 of 15 closures**

**Dual-defect (EC + β⁻)**: K-40, Cl-36, Cu-64, Ag-108, Ir-192 — **5 isotopes**
