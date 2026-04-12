# INVESTIGATION 06: Missing Elements — Technetium and Promethium

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Protection](INVESTIGATION_04_Protection_Factor.md) ·
> [Orthohelium](INVESTIGATION_05_Orthohelium_Connection.md) ·
> [Ratios](INVESTIGATION_07_Energy_Ratios.md) ·
> [Dual Defect](INVESTIGATION_08_Dual_Defect_Branching.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Master Table](EC_data/01_All_EC_Isotopes_Master_Table.md)

---

## 1. The Observation

Below bismuth (Z=83), there are exactly TWO elements with zero stable isotopes:
- **Technetium** (Z=43)
- **Promethium** (Z=61)

Every other element from Z=1 to Z=83 has at least one stable isotope.
What makes these two unique?

---

## 2. The Building Block Count

Beyond the alpha core (Z=2), each element requires (Z − 2) scaffold
building blocks (deuterons and tritons).

| Z | Element | Blocks (Z−2) | Pairs | Remainder |
|---|---------|-------------|-------|-----------|
| 42 | Mo | 40 | **20** | 0 (fully paired) |
| **43** | **Tc** | **41** | **20** | **1 (unpaired)** |
| 44 | Ru | 42 | **21** | 0 (fully paired) |
| ... | ... | ... | ... | ... |
| 60 | Nd | 58 | **29** | 0 (fully paired) |
| **61** | **Pm** | **59** | **29** | **1 (unpaired)** |
| 62 | Sm | 60 | **30** | 0 (fully paired) |

**Both missing elements have ODD block counts — an always-unpaired position.**

---

## 3. The Even-Z Neighbour Dominance

### Technetium's neighbourhood

Mo (Z=42) stable isotopes: **7** (A = 92, 94, 95, 96, 97, 98, 100)
Ru (Z=44) stable isotopes: **7** (A = 96, 98, 99, 100, 101, 102, 104)

Mass number coverage in Tc's range (A = 95–100):

| A | Mo stable? | Ru stable? | Coverage |
|---|-----------|-----------|----------|
| 95 | **YES** | — | Mo blocks |
| 96 | **YES** | **YES** | Both block |
| 97 | **YES** | — | Mo blocks |
| 98 | **YES** | **YES** | Both block |
| 99 | — | **YES** | Ru blocks |
| 100 | **YES** | **YES** | Both block |

**Every mass number in Tc's range is already occupied by a stable
even-Z neighbour.** Tc's perpetually unpaired scaffold cannot compete
at ANY A value.

### Promethium's neighbourhood

Nd (Z=60) stable isotopes: **7** (A = 142, 143, 144, 145, 146, 148, 150)
Sm (Z=62) stable isotopes: **7** (A = 144, 147, 148, 149, 150, 152, 154)

Coverage of Pm's range (A = 143–150):

| A | Nd stable? | Sm stable? | Coverage |
|---|-----------|-----------|----------|
| 143 | **YES** | — | Nd blocks |
| 144 | **YES** | **YES** | Both block |
| 145 | **YES** | — | Nd blocks |
| 146 | **YES** | — | Nd blocks |
| 147 | — | **YES** | Sm blocks |
| 148 | **YES** | **YES** | Both block |
| 149 | — | **YES** | Sm blocks |
| 150 | **YES** | **YES** | Both block |

**Same result.** Every mass number is covered.

---

## 4. Why Other Odd-Z Elements Survive

The question: if odd blocks are always disadvantaged, why are OTHER
odd-Z elements (V, Mn, Co, As, etc.) stable?

Answer: their even-Z neighbours leave GAPS in mass number coverage.

Example: **Cobalt (Z=27, blocks=25, odd)**
- Fe (Z=26): stable at A = 54, 56, 57, 58
- Ni (Z=28): stable at A = 58, 60, 61, 62, 64

Gap: A = **59** is not covered by Fe or Ni. Co-59 (Z=27, A=59)
fills this gap. Its unpaired scaffold disadvantage is irrelevant
because no even-Z competitor exists at A=59.

Example: **Vanadium (Z=23, blocks=21, odd)**
- Ti (Z=22): stable at A = 46, 47, 48, 49, 50
- Cr (Z=24): stable at A = 50, 52, 53, 54

Gap: A = **51** is not covered. V-51 fills it.

### The Tc/Pm uniqueness

Tc and Pm are unique because Mo/Ru and Nd/Sm are PROLIFIC —
7 stable isotopes each, covering essentially every mass number
in their range. No gaps for the odd-Z element to fill.

---

## 5. Grammar Decomposition of Tc Isotopes

| Isotope | Z | A | n_tri | n_deu | Valid? | Decay | t½ | Q (keV) |
|---------|---|---|-------|-------|--------|-------|-----|---------|
| Tc-95 | 43 | 95 | 9 | 32 | yes | EC/β⁺ | 20.0 h | 1,691 |
| Tc-96 | 43 | 96 | 10 | 31 | yes | EC/β⁺ | 4.28 d | 2,973 |
| Tc-97 | 43 | 97 | 11 | 30 | yes | **EC** | **4.21 My** | **320** |
| Tc-98 | 43 | 98 | 12 | 29 | yes | β⁻ | 4.2 My | 1,793 |
| Tc-99 | 43 | 99 | 13 | 28 | yes | **β⁻** | **211 ky** | **294** |

**Tc-97** (EC, 4.21 My) and **Tc-99** (β⁻, 211 ky) are the longest-lived.
Both have low Q-values (320 and 294 keV). Both are grammar-valid but
their unpaired scaffolds cannot compete with their even-Z neighbours'
fully-paired scaffolds at the same A.

### The competing stable isotopes at each A

| Tc isotope | A | Competing stable isotope | Winner |
|------------|---|--------------------------|--------|
| Tc-97 | 97 | **Mo-97** (Z=42, fully paired) | Mo wins |
| Tc-98 | 98 | **Mo-98** and **Ru-98** | Mo+Ru win |
| Tc-99 | 99 | **Ru-99** (Z=44, fully paired) | Ru wins |

---

## 6. Grammar Decomposition of Pm Isotopes

| Isotope | Z | A | n_tri | n_deu | Valid? | Decay | t½ | Q (keV) |
|---------|---|---|-------|-------|--------|-------|-----|---------|
| Pm-143 | 61 | 143 | 21 | 40 | yes | EC | 265 d | 1,041 |
| Pm-144 | 61 | 144 | 22 | 39 | yes | EC | 363 d | 2,332 |
| Pm-145 | 61 | 145 | 23 | 38 | yes | **EC** | **17.7 y** | **163** |
| Pm-146 | 61 | 146 | 24 | 37 | yes | EC/β⁻ | 5.53 y | — |
| Pm-147 | 61 | 147 | 25 | 36 | yes | **β⁻** | **2.624 y** | **225** |

**Pm-145** (EC, 17.7 y) and **Pm-147** (β⁻, 2.624 y) are the longest.
Both grammar-valid but cannot compete with Nd/Sm.

---

## 7. Why Both Missing Elements Are in the d/f Block

Tc is in the 4d block (first transition series gap).
Pm is in the 4f block (first lanthanide gap).

Both are in regions where even-Z elements have MANY stable isotopes
(Mo=7, Ru=7, Nd=7, Sm=7). The d and f blocks, with their high
orbital degeneracy, allow even-Z elements to accommodate many
neutron counts stably. This saturates the mass number space,
leaving no gaps for odd-Z elements.

In the s and p blocks, even-Z elements have fewer stable isotopes
(typically 2–5), leaving gaps for odd-Z elements.

---

## 8. The SDT Grammar Explanation

The construction grammar predicts:
1. **Even-Z elements** (even blocks beyond alpha) naturally pair all
   scaffold positions. Fully paired = structurally serene.
2. **Odd-Z elements** (odd blocks) always have one unpaired position.
   This is a permanent structural disadvantage.
3. **The disadvantage matters** only when even-Z neighbours cover
   every available mass number. If a gap exists, the odd-Z element
   fills it despite its unpaired scaffold.
4. **Tc and Pm** are the only odd-Z elements whose even-Z neighbours
   are prolific enough (7 stable isotopes each on both sides) to
   completely block every mass number.

### Falsifiable prediction

If a new superheavy element (Z > 118) were synthesised with odd Z
and its even-Z neighbours had enough stable (or very long-lived)
isotopes to cover every mass number, it would also have zero stable
isotopes. This is testable in principle once island-of-stability
elements are characterised.
