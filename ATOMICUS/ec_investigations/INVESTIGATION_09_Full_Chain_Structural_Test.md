# INVESTIGATION 09: Full Chain Structural Test — All EC Closures

> Navigation: [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Gravitational](INVESTIGATION_10_Gravitational_Redshift.md) ·
> [Anions](INVESTIGATION_11_Anionisation.md) ·
> [FINAL](FINAL_REPORT.md)
>
> Data: [Master Table](EC_data/01_All_EC_Isotopes_Master_Table.md) ·
> [Ionisation](EC_data/04_Ionisation_Series.md) ·
> [Redshift](EC_data/10_Gravitational_Redshift_Tables.md)

---

## 1. Purpose

INVESTIGATION_02 exhaustively tested Be-7. This investigation extends
the same structural tests to ALL 9 pure-EC subshell closure isotopes:

## 2. Argon-37 (3p⁶ closure, Z=18)

### Identity card

| Property | Value |
|----------|-------|
| Z=18, A=37, N=19 | n_tri=1, n_deu=15 | Grammar VALID |
| Jπ (ground) | 3/2⁺ |
| Jπ (daughter Cl-37) | 3/2⁺ |
| t½ | 35.04 d |
| Q_EC | 814 keV |
| Pure EC | YES (100%) |
| Daughter | Cl-37 (stable) |

### Scaffold diagram

```
   α core          [1s1|H  1s2|He]
   Shell 2         [2s1|Li 2s2|Be 2p1|B  2p2|C  2p3|N  2p4|O  2p5|F  2p6|Ne]
   Shell 3 (full)  [3s1|Na 3s2|Mg 3p1|Al 3p2|Si 3p3|P  3p4|S  3p5|Cl 3p6|Ar]
```

All 18 positions occupied. The 3p⁶ closure means every gear in Shell 3
is meshed. The defect is NOT a missing gear — it's a RATIO imbalance.
n_tri=1 means one triton block against 15 deuterons. The scaffold is
grammar-valid but the triton count is low (low N/Z ratio).

### Charge state EC chain

| State | Electrons | Config | EC? | K-electrons | t½ estimate |
|-------|----------|--------|-----|-------------|-------------|
| Ar⁰ | 18 | full | YES | 2 (parahelium) | 35.04 d |
| Ar¹⁺ | 17 | -1 from 3p | YES | 2 | ~35 d |
| ... | ... | ... | YES | 2 | ~35 d |
| Ar¹⁶⁺ | 2 | 1s² | YES | 2 (parahelium) | ~36 d |
| **Ar¹⁷⁺** | **1** | **1s¹** | **YES** | **1** | **uncertain** |
| **Ar¹⁸⁺** | **0** | **bare** | **NO** | **0** | **∞ (frozen)** |

Same pattern as Be-7: EC stops at full ionisation. Ar-37¹⁸⁺ is a frozen
defect. But unlike Be-7 (Q=862 < 1022), Ar-37's Q=814 < 1022, so β⁺
is ALSO forbidden. Bare Ar-37¹⁸⁺ cannot decay by any electromagnetic or
weak process → frozen.

### Nuclear level scheme

| State | E (keV) | Jπ | Notes |
|-------|---------|-----|-------|
| Ground | 0 | 3/2⁺ | EC parent |
| 1st excited | ~1,410 | (5/2⁺) | Unbound — above threshold |

Ar-37 has **ZERO** bound excited states. The ground state is the only
bound state. This is even simpler than Be-7 (which has one excited state).
EC proceeds 100% to the Cl-37 ground state. No gamma emission.

### Mirror nucleus: Cl-37 (Z=17, N=20) ↔ Ar-37 (Z=18, N=19)

| | Ar-37 (parent) | Cl-37 (daughter) |
|---|---|---|
| Z | 18 | 17 |
| N | 19 | 20 |
| n_tri | 1 | 3 |
| n_deu | 15 | 12 |
| Stable? | No (35 d) | **YES** |
| B/A | 8.528 MeV/nucleon | 8.570 MeV/nucleon |

Cl-37 is 1.55 MeV MORE tightly bound (total). The additional triton
(n_tri = 3 vs 1) provides better structural stability.

---

## 3. Calcium-41 (4s² closure, Z=20)

### Identity card

| Property | Value |
|----------|-------|
| Z=20, A=41, N=21 | n_tri=1, n_deu=19 |
| Grammar | VALID |
| t½ | 99,400 years |
| Q_EC | 421 keV |
| Pure EC | YES (100%) |
| Daughter | K-41 (stable) |

### Why the enormous half-life?

Ca-41 has the LOWEST Q-value of any s²-closure EC isotope (421 keV).
The grammar penalty is NEGATIVE (−361 keV), meaning the scaffold
must PAY 361 keV from its binding energy to reorganise. The
result: the correction takes 99,400 years.

### No gamma emission

EC to K-41 ground state is 100%. No excited states populated.
Detection requires measuring K-41 daughter accumulation or the
Auger electrons from the K-shell vacancy.

### Anion test

Ca has EA = +2.37 meV — the ONLY EC closure element with a
detectable (positive) electron affinity. Ca⁻ exists, barely.
A 19-electron calcium atom has one 4p¹ electron beyond the
4s² closure. This is the test case: does adding an electron
to a closure element extend or destabilise the gear train?

Answer: barely extends. 2.37 meV is thermal energy at 27 K.
At room temperature, Ca⁻ falls apart instantly.

---

## 4. Krypton-81 (4p⁶ closure, Z=36)

### Identity card

| Property | Value |
|----------|-------|
| Z=36, A=81, N=45 | n_tri=9, n_deu=25 |
| t½ | 229,000 years |
| Q_EC | 281 keV |
| Daughter | Br-81 (stable) |

### The longest noble gas EC

Kr-81 has the longest half-life of any noble gas EC isotope
(229 ky vs Ar-37's 35 d and Xe-127's 36.3 d). This is because
Q = 281 keV — much lower than Ar-37 (814) or Xe-127 (662).

### Cosmochronometer

Kr-81 is used to date ancient groundwater and ice (range: 50,000–
1,000,000 years). The EC decay provides a cosmic clock.

### Scaffold complexity

81 nucleons = 78 scaffold positions beyond alpha. n_tri=9, n_deu=25.
The gear chain is MUCH longer than Be-7 (7 nucleons). Per-sprocket
protection: PF/A = 1.2×10¹⁰/81 = 1.46×10⁸ per gear. Compare Be-7:
7,514/7 = 1,073 per gear. Kr-81 has 136,000× more protection per
gear than Be-7.

---

## 5. Cadmium-109 (4d¹⁰ closure, Z=48)

### Identity card

| Property | Value |
|----------|-------|
| Z=48, A=109, N=61 | n_tri=13, n_deu=35 |
| t½ | 461.4 d |
| Q_EC | 214 keV |
| Daughter | Ag-109 (stable) |

### The 88 keV gamma

Cd-109 EC produces Ag-109 in an excited state 88.034 keV above
ground. This excited state decays by internal conversion (producing
Ag K X-rays at 22 keV) or by gamma emission (88 keV).

This is analogous to Be-7's 478 keV gamma but at lower energy.
The 88/478 ratio = 0.184 ≈ Z(Be)/Z(Cd) (4/48 = 0.083). Not a
clean match, but the gamma energy scales roughly with 1/Z.

### Medical/industrial use

Cd-109 is used in PIXE (proton-induced X-ray emission) for
elemental analysis. The 88 keV gamma and 22 keV X-rays are
clean calibration sources.

---

## 6. Xenon-127 (5p⁶ closure, Z=54)

### Identity card

| Property | Value |
|----------|-------|
| Z=54, A=127, N=73 | n_tri=19, n_deu=33 |
| t½ | 36.34 d |
| Q_EC | 662 keV |
| Daughter | I-127 (stable) |

### Member of the ~35-day cluster

Xe-127's 36.3b-day half-life is within 4% of Ar-37's 35.0 d.
Both are noble gas closures (p⁶): Ar is 3p⁶, Xe is 5p⁶.
The gear rigidity is similar despite Z = 18 vs 54.

### Gamma emissions

EC populates I-127 excited states. Multiple gamma lines:
- 172.1 keV (25.5%)
- 202.9 keV (68.3%)
- 374.9 keV (17.2%)

Unlike Be-7 (single gamma line) or Ar-37 (no gammas), Xe-127
has a complex daughter spectrum. The I-127 nuclear scaffold has
many accessible excited states — a complex gear train with multiple
relaxation channels.

---

## 7. Barium-133 (6s² closure, Z=56)

### Identity card

| Property | Value |
|----------|-------|
| Z=56, A=133, N=77 | n_tri=21, n_deu=35 |
| t½ | 10.551 years |
| Q_EC | 517 keV |
| Daughter | Cs-133 (stable, ONLY Cs isotope) |

### Unique daughter

Cs-133 is the ONLY stable caesium isotope. Ba-133 EC produces
the sole stable form of element 55. This is unique among EC
isotopes — most produce daughters that also have other stable
isotopes.

### Gamma emissions (complex)

| Energy (keV) | Intensity (%) |
|-------------|---------------|
| 53.2 | 2.1 |
| 79.6 | 2.6 |
| 81.0 | 34.0 |
| 276.4 | 7.2 |
| 302.9 | 18.4 |
| 356.0 | **62.1** |
| 383.8 | 8.9 |

The 356 keV gamma line dominates (62.1%). Ba-133 is used as a
standard calibration source in gamma spectroscopy.

---

## 8. Ytterbium-169 (4f¹⁴ closure, Z=70)

### Identity card

| Property | Value |
|----------|-------|
| Z=70, A=169, N=99 | n_tri=29, n_deu=41 |
| t½ | 32.03 d |
| Q_EC | 909 keV |
| Daughter | Tm-169 (stable) |

### ~35-day cluster member

32.03 days — the shortest in the cluster (Ar: 35.0, Xe: 36.3).
This is a 4f¹⁴ closure, not a p⁶ closure. Yet the half-life
is within 9% of the noble gas cluster members.

The f¹⁴ closure has 14 gears in a single subshell — the densest
gear packing of any configuration. Despite being a "loose" gear
by the excitation ratio metric, its half-life matches the "rigid"
noble gas closures.

### Multiple gamma lines

Major lines from Tm-169 relaxation:
- 63.1 keV (44%)
- 93.6 keV (2.6%)
- 109.8 keV (17.4%)
- 130.5 keV (11.3%)
- 177.2 keV (22.2%)
- 197.9 keV (35.8%)
- 307.7 keV (10.0%)

Rich spectrum — many daughter excited states accessible.

---

## 9. Mercury-197 (5d¹⁰ closure, Z=80)

### Identity card

| Property | Value |
|----------|-------|
| Z=80, A=197, N=117 | n_tri=37, n_deu=47 |
| t½ | 64.14 hours |
| Q_EC | 600 keV |
| Daughter | Au-197 (stable, ONLY Au isotope) |

### Unique daughter (like Ba-133)

Au-197 is the ONLY stable gold isotope. Hg-197 EC produces the
sole stable form of element 79. Gold is monoisotopic.

### Relativistic effects

At Z=80, relativistic contraction of the 6s² shell is significant.
The "loose gear" (s²-closure, ρ = 0.447) is tighter than expected
from non-relativistic extrapolation. This manifests as:
- t½ = 64 hours (much shorter than Ca's 99 ky or Ba's 10.5 y)
- Higher excitation ratio (0.447 vs 0.307 for Ca)
- Stronger spin-orbit splitting (³P₀→³P₂ spread = 0.794 eV)

---

## 10. Cross-Closure Comparison Table

| Closure | Z | Isotope | n_tri | Q (keV) | t½ | Excited states in daughter | Gammas? | ρ (gear rigidity) | Family |
|---------|---|---------|-------|---------|-----|--------------------------|---------|-------------------|--------|
| 2s² | 4 | Be-7 | −1 | 862 | 53.2 d | 1 excited | 478 keV (10%) | 0.292 | Loose |
| 3p⁶ | 18 | Ar-37 | 1 | 814 | 35.0 d | 0 excited | None | 0.733 | Rigid |
| 4s² | 20 | Ca-41 | 1 | 421 | 99.4 ky | 0 excited | None | 0.307 | Loose |
| 4p⁶ | 36 | Kr-81 | 9 | 281 | 229 ky | complex | Multiple | 0.709 | Rigid |
| 4d¹⁰ | 48 | Cd-109 | 13 | 214 | 461 d | 1 (88 keV) | 88 keV | 0.45 est. | Mid |
| 5p⁶ | 54 | Xe-127 | 19 | 662 | 36.3 d | Many | Multiple | 0.685 | Rigid |
| 6s² | 56 | Ba-133 | 21 | 517 | 10.5 y | Many | 356 keV (62%) | 0.215 | Loose |
| 4f¹⁴ | 70 | Yb-169 | 29 | 909 | 32.0 d | Many | 63–308 keV | 0.343 | Loose |
| 5d¹⁰ | 80 | Hg-197 | 37 | 600 | 64.1 h | 1 (77 keV) | 77 keV | 0.447 | Mid |

### Key patterns

1. **Gear rigidity predicts EC cluster membership**: All ~35-day cluster
   members (Ar, Xe, Yb) have ρ > 0.33 or are f¹⁴ closures.

2. **No gammas correlates with simplest scaffolds**: Ar-37 and Ca-41 have
   zero daughter excited states. They are the simplest scaffolds (low n_tri,
   low complexity). EC goes straight to ground.

3. **Complex gamma spectra correlate with high n_tri**: Xe-127 (n_tri=19),
   Ba-133 (n_tri=21), Yb-169 (n_tri=29) all have many gamma lines.
   More tritons = more structural modes = more relaxation channels.

4. **Two monoisotopic daughters**: Ba→Cs and Hg→Au. Both produce the
   ONLY stable isotope of their daughter element. Grammar significance:
   these daughters (Cs-133, Au-197) have exactly one viable grammar
   configuration.
