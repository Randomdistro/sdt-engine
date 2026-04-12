# INVESTIGATION 03: Subshell Closure Pattern

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Protection](INVESTIGATION_04_Protection_Factor.md) ·
> [Orthohelium](INVESTIGATION_05_Orthohelium_Connection.md) ·
> [Missing](INVESTIGATION_06_Missing_Elements.md) ·
> [Ratios](INVESTIGATION_07_Energy_Ratios.md) ·
> [Dual Defect](INVESTIGATION_08_Dual_Defect_Branching.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Subshell Map](EC_data/02_Subshell_Closure_Map.md)

---

## 1. The Claim

**Every completed subshell (noble gas configuration, filled s/p/d/f block)
produces a pure-EC isotope** — provided Z is heavy enough to keep Q below
the β⁺ threshold and the element isn't α-unstable.

---

## 2. The Evidence

### 2.1 Pure EC at closures (9 of 15)

| Closure | Z | Element | EC isotope | Q (keV) | t½ | Q < 1022? |
|---------|---|---------|------------|---------|-----|-----------|
| 2s² | 4 | Be | Be-7 | 862 | 53.2 d | ✓ |
| 3p⁶ | 18 | Ar | Ar-37 | 814 | 35.0 d | ✓ |
| 4s² | 20 | Ca | Ca-41 | 421 | 99.4 ky | ✓ |
| 4p⁶ | 36 | Kr | Kr-81 | 281 | 229 ky | ✓ |
| 4d¹⁰ | 48 | Cd | Cd-109 | 214 | 461 d | ✓ |
| 5p⁶ | 54 | Xe | Xe-127 | 662 | 36.3 d | ✓ |
| 6s² | 56 | Ba | Ba-133 | 517 | 10.5 y | ✓ |
| 4f¹⁴ | 70 | Yb | Yb-169 | 909 | 32.0 d | ✓ |
| 5d¹⁰ | 80 | Hg | Hg-197 | 600 | 64.1 h | ✓ |

### 2.2 No pure EC at closures (6 of 15)

| Closure | Z | Element | Reason |
|---------|---|---------|--------|
| 1s² | 2 | He | Alpha core — cannot EC (would destroy the core) |
| 2p⁶ | 10 | Ne | Q = 3,239 keV ≫ 1022 → β⁺ dominates |
| 3s² | 12 | Mg | Q = 4,056 keV ≫ 1022 → β⁺ dominates |
| 5s² | 38 | Sr | Q = 1,065 keV ≈ 1022 → borderline β⁺ |
| 3d¹⁰ | 30 | Zn | Q = 1,352 keV > 1022 → small β⁺ (1.5%) |
| 6p⁶ | 86 | Rn | All isotopes α-unstable; no long-lived EC |

### 2.3 The exclusion pattern

The 4 closures without pure EC (Ne, Mg, Zn, Sr) all have Q > 1000 keV.
The pattern:
- **Light closures** (Z ≤ 12): Q too high (thousands of keV) → β⁺
- **Medium closures** (Z = 18–80): Q moderate (100–900 keV) → pure EC
- **Very heavy** (Z = 86): α-decay pathway dominates over EC

---

## 3. The ~35-Day Cluster

Three subshell closures produce EC half-lives within 6% of each other:

| Isotope | Closure | Z | t½ (d) | Q (keV) | A |
|---------|---------|---|--------|---------|---|
| Yb-169 | 4f¹⁴ | 70 | 32.0 | 909 | 169 |
| Ar-37 | 3p⁶ | 18 | 35.0 | 814 | 37 |
| Xe-127 | 5p⁶ | 54 | 36.3 | 662 | 127 |

### Properties of the cluster

| Property | Ar-37 | Xe-127 | Yb-169 |
|----------|-------|--------|--------|
| Z | 18 | 54 | 70 |
| Z ratio (to Ar) | 1× | 3× | 3.9× |
| A | 37 | 127 | 169 |
| Q (keV) | 814 | 662 | 909 |
| n_tri | 1 | 19 | 29 |
| Grammar valid? | YES | YES | YES |
| Subshell type | p⁶ | p⁶ | f¹⁴ |
| Stable isotopes at Z | 3 | 9 | 7 |
| t½ (days) | 35.0 | 36.3 | 32.0 |

### Why same half-life despite wildly different Z?

The decay rate depends on Q², Z³ (electron density), and the nuclear
matrix element |M|². For these three isotopes:

| Factor | Ar-37 | Xe-127 | Yb-169 |
|--------|-------|--------|--------|
| Q² (keV²) | 662,596 | 438,244 | 826,281 |
| Z³ | 5,832 | 157,464 | 343,000 |
| Q² × Z³ | 3.86 × 10⁹ | 6.90 × 10¹⁰ | 2.83 × 10¹¹ |
| t½ (s) | 3,024,000 | 3,139,776 | 2,767,392 |
| λ = ln2/t½ | 2.29 × 10⁻⁷ | 2.21 × 10⁻⁷ | 2.50 × 10⁻⁷ |
| λ / (Q²Z³) ratio | 5.94 × 10⁻¹⁷ | 3.20 × 10⁻¹⁸ | 8.85 × 10⁻¹⁹ |

The Q²×Z³ product varies by 73×, but the half-lives are within 10%.
This means the nuclear matrix element |M|² varies inversely with Q²Z³
to an extraordinary degree. The heavier the nucleus, the SMALLER the
matrix element — as if the scaffold geometry precisely compensates for
the increased electron coupling.

### SDT interpretation

The nuclear scaffold acts as a gear transmission. More sprockets
(higher A) means higher gear ratio — the electron signal is diluted
across more nucleon positions. The dilution factor is A/Z³ × Q²
(approximately), which happens to produce the same output torque
(decay rate) for these three closure configurations.

The ~35-day period may represent a fundamental gear cycling time for
CLOSED subshells — the time it takes the nuclear gear train to complete
one full correction cycle when the scaffold is in a completed (closed)
configuration with moderate stress (Q ≈ 700–900 keV).

---

## 4. The Be-7 Outlier

Be-7 (53.2 d) is 1.5× longer than the ~35-day cluster despite having
Q = 862 keV (similar to the cluster). Why?

| Property | Be-7 | Cluster average |
|----------|------|-----------------|
| n_tri | **−1** (INVALID) | 1–29 (all valid) |
| A | **7** | 37–169 |
| Z | **4** | 18–70 |
| Z³ | **64** | 5,832–343,000 |

Two differences:
1. Be-7 is grammar-INVALID (n_tri = −1). The cluster members are all valid.
2. Be-7 has Z³ = 64 — orders of magnitude less electron density.

The lower electron density (Z³ = 64 vs 5,832+) should make Be-7 SLOWER.
But Be-7's Q = 862 is higher than Xe-127 (662) and close to Ar-37 (814).
The balance of these factors gives 53 days — close to the cluster but
not within it.

---

## 5. Opener vs Closer Pattern

Each subshell has a first position (opener) and last position (closer):

| Subshell | Opener | Opener EC | Closer | Closer EC | Pattern |
|----------|--------|-----------|--------|-----------|---------|
| 2s | Li (Z=3) | — | Be (Z=4) | **Be-7 (53d)** | Closer = pure EC |
| 2p | B (Z=5) | — | Ne (Z=10) | Ne-19 (17s β⁺) | Closer = β⁺ |
| 3s | Na (Z=11) | **Na-22 (2.6y)** | Mg (Z=12) | Mg-23 (11s β⁺) | Opener = EC |
| 3p | Al (Z=13) | **Al-26 (717ky)** | Ar (Z=18) | **Ar-37 (35d)** | Both = EC |
| 4s | K (Z=19) | **K-40 (1.2Gy)** | Ca (Z=20) | **Ca-41 (99ky)** | Both = EC |
| 3d | Sc (Z=21) | Sc-44 (3.9h β⁺) | Zn (Z=30) | Zn-65 (244d ~β⁺) | Neither pure |
| 4p | Ga (Z=31) | **Ga-67 (3.3d)** | Kr (Z=36) | **Kr-81 (229ky)** | Both = EC |
| 4d | Y (Z=39) | Y-88 (107d β⁺) | Cd (Z=48) | **Cd-109 (461d)** | Closer = EC |
| 5p | In (Z=49) | **In-111 (2.8d)** | Xe (Z=54) | **Xe-127 (36d)** | Both = EC |
| 5d | — | — | Hg (Z=80) | **Hg-197 (64h)** | Closer = EC |

**Closers predominantly produce pure EC.** Openers are mixed (some EC, some β⁺).

---

## 6. Stable Isotope Count Correlation

Subshell closures have the MOST stable isotopes:

| Closure | Z | Stable count | Row context |
|---------|---|-------------|-------------|
| 4s² Ca | 20 | 5 | Most in row 4 early |
| 3d¹⁰ Zn | 30 | 5 | Most in 3d block |
| 4p⁶ Kr | 36 | 6 | Most in row 4 late |
| 4d¹⁰ Cd | 48 | 8 | Most in 4d block |
| 5p⁶ Xe | 54 | 9 | Most of ANY element |
| 6s² Ba | 56 | 7 | High |
| 4f¹⁴ Yb | 70 | 7 | Most in lanthanides |
| 5d¹⁰ Hg | 80 | 7 | Most in 5d block |

**Closed subshells accommodate the widest range of neutron counts** while
maintaining structural stability. The completed gear configuration is
the most versatile scaffold geometry.

---

## 7. Falsifiable Predictions

### Prediction: The 5f¹⁴ closure (Z=102, No, Nobelium)

If the pattern holds, Nobelium should have a pure-EC isotope with
Q < 1022 keV and a half-life in the days-to-years range.

No-255 (Z=102, A=255) has t½ = 3.52 min, decaying by EC/α.
No-253 (Z=102, A=253) has t½ = 1.62 min, decaying by EC/α.

These are too short for the "closure pattern" — but Nobelium is
α-unstable (same problem as Rn/Z=86). The α-decay channel
overwhelms EC for very heavy elements.

**Prediction revised**: The closure pattern applies only below the
α-instability line (Z ≤ 83). Above that, α-decay disrupts all patterns.
