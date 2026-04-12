# Subshell Closure EC Map

> Navigation: [Master Table](01_All_EC_Isotopes_Master_Table.md) · [L/K Ratios](03_LK_Capture_Ratios.md) ·
> [Ionisation](04_Ionisation_Series.md) · [Protection](05_Protection_Factors.md) ·
> [Energy Ratios](06_Energy_Ratios_And_Constants.md)
>
> Investigation: [Closures](../INVESTIGATION_03_Subshell_Closure_Pattern.md)

---

## All 15 Subshell Closures

| # | Subshell | Z | Element | Lowest-Q EC isotope | Q (keV) | t½ | Pure EC? | n_tri | Valid? | Stable isotopes at Z | Stable at Z−1 | Stable at Z+1 |
|---|----------|---|---------|---------------------|---------|-----|---------|-------|--------|---------------------|---------------|---------------|
| 1 | 1s² | 2 | He | — | — | — | — | — | — | 2 (He-3, He-4) | 2 | 2 |
| 2 | **2s²** | 4 | **Be** | **Be-7** | **862** | **53.2 d** | **YES** | −1 | NO | 1 (Be-9) | 2 | 2 |
| 3 | 2p⁶ | 10 | Ne | Ne-19 | 3,239 | 17.2 s | No | −1 | NO | 3 | 1 | 3 |
| 4 | 3s² | 12 | Mg | Mg-23 | 4,056 | 11.3 s | No | −1 | NO | 3 | 3 | 1 |
| 5 | **3p⁶** | 18 | **Ar** | **Ar-37** | **814** | **35.0 d** | **YES** | 1 | yes | 3 | 2 | 5 |
| 6 | **4s²** | 20 | **Ca** | **Ca-41** | **421** | **99.4 ky** | **YES** | 1 | yes | 5 | 2 | 1 |
| 7 | **3d¹⁰** | 30 | Zn | Zn-65 | 1,352 | 244 d | ~No (1.5%β⁺) | 5 | yes | 5 | 2 | 2 |
| 8 | **4p⁶** | 36 | **Kr** | **Kr-81** | **281** | **229 ky** | **YES** | 9 | yes | 6 | 2 | 1 |
| 9 | **5s²** | 38 | Sr | Sr-85 | 1,065 | 64.8 d | Borderline | 9 | yes | 4 | 1 | 1 |
| 10 | **4d¹⁰** | 48 | **Cd** | **Cd-109** | **214** | **461 d** | **YES** | 13 | yes | 8 | 2 | 2 |
| 11 | **5p⁶** | 54 | **Xe** | **Xe-127** | **662** | **36.3 d** | **YES** | 19 | yes | 9 | 1 | 2 |
| 12 | **6s²** | 56 | **Ba** | **Ba-133** | **517** | **10.5 y** | **YES** | 21 | yes | 7 | 1 | 1 |
| 13 | **4f¹⁴** | 70 | **Yb** | **Yb-169** | **909** | **32.0 d** | **YES** | 29 | yes | 7 | 1 | 1 |
| 14 | **5d¹⁰** | 80 | **Hg** | **Hg-197** | **600** | **64.1 h** | **YES** | 37 | yes | 7 | 1 | 4 |
| 15 | 6p⁶ | 86 | Rn | — | — | — | — | — | — | 0 | 1 | 0 |

---

## Pure EC Closure Sequence — Ordered by Q

| Rank | Closure | Isotope | Q (keV) | t½ | Electrons |
|------|---------|---------|---------|-----|-----------|
| 1 | 4d¹⁰ | **Cd-109** | 214 | 461 d | 48 |
| 2 | 4p⁶ | **Kr-81** | 281 | 229 ky | 36 |
| 3 | 4s² | **Ca-41** | 421 | 99.4 ky | 20 |
| 4 | 6s² | **Ba-133** | 517 | 10.5 y | 56 |
| 5 | 5d¹⁰ | **Hg-197** | 600 | 64.1 h | 80 |
| 6 | 5p⁶ | **Xe-127** | 662 | 36.3 d | 54 |
| 7 | 3p⁶ | **Ar-37** | 814 | 35.0 d | 18 |
| 8 | 2s² | **Be-7** | 862 | 53.2 d | 4 |
| 9 | 4f¹⁴ | **Yb-169** | 909 | 32.0 d | 70 |

---

## The ~35 Day Cluster

| Isotope | Closure | t½ (days) | Q (keV) | Z |
|---------|---------|-----------|---------|---|
| Yb-169 | 4f¹⁴ | **32.0** | 909 | 70 |
| Ar-37 | 3p⁶ | **35.0** | 814 | 18 |
| Xe-127 | 5p⁶ | **36.3** | 662 | 54 |
| Be-7 | 2s² | **53.2** | 862 | 4 |

Mean of first three: **34.4 days**. Spread: ±2.2 days (6.3%).

Three subshell closures spanning Z=18 to Z=70 (52 elements apart) produce
EC half-lives within 6% of each other. Be-7 is the outlier at 53 days.

### Why Be-7 is the outlier

Be-7 is the ONLY grammar-INVALID member of the cluster (n_tri = −1).
Ar-37, Xe-127, and Yb-169 are all grammar-VALID. The invalid grammar
adds the extra 80 keV penalty that modifies the coupling and extends
the half-life.

---

## Closures WITHOUT Pure EC

| Closure | Z | Element | Why no pure EC |
|---------|---|---------|----------------|
| 1s² | 2 | He | Alpha core — no EC isotope exists |
| 2p⁶ | 10 | Ne | Q = 3,239 keV ≫ 1022 → β⁺ dominates |
| 3s² | 12 | Mg | Q = 4,056 keV ≫ 1022 → β⁺ dominates |
| 6p⁶ | 86 | Rn | No stable/long-lived Rn isotopes; all α-decay |

### Pattern

Light closures (2p⁶, 3s²): Q too high for pure EC. The small Z means
fewer scaffold blocks, less binding per nucleon, larger grammar penalty,
and Q blows past the β⁺ threshold.

Noble gas closures: 1s² (He), 2p⁶ (Ne) — too light.
3p⁶ (Ar), 4p⁶ (Kr), 5p⁶ (Xe) — pure EC. 6p⁶ (Rn) — α-unstable.

---

## Stable Isotope Count at Closures

| Closure | Z | Stable isotopes | Observation |
|---------|---|----------------|-------------|
| 2s² | 4 (Be) | **1** (Be-9 only) | FEWEST of any element (except H/He/Tc/Pm) |
| 3p⁶ | 18 (Ar) | 3 | Normal for noble gas |
| 4s² | 20 (Ca) | **5** | MOST of that row |
| 3d¹⁰ | 30 (Zn) | 5 | MOST of the 3d block |
| 4p⁶ | 36 (Kr) | **6** | MOST of that row |
| 4d¹⁰ | 48 (Cd) | **8** | MOST of the 4d block |
| 5p⁶ | 54 (Xe) | **9** | MOST of any element (tied with Sn-50) |
| 6s² | 56 (Ba) | 7 | MOST of the lanthanide row |
| 4f¹⁴ | 70 (Yb) | 7 | MOST of the lanthanides |
| 5d¹⁰ | 80 (Hg) | 7 | MOST of the 5d block |

Subshell closures consistently have the MOST stable isotopes in their
respective rows. The closed scaffold is the most structurally versatile —
it can accommodate the widest range of neutron counts while maintaining
grammar validity.
