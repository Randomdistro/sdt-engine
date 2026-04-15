# Energy Ratios and Cross-Correlations

> Navigation: [Master Table](01_All_EC_Isotopes_Master_Table.md) · [Subshell Map](02_Subshell_Closure_Map.md) ·
> [Protection](05_Protection_Factors.md)
>
> Investigation: [Ratios](../INVESTIGATION_07_Energy_Ratios.md)

---

## Validated Ratios

| Ratio | Expression | Value | Match | Accuracy |
|-------|------------|-------|-------|----------|
| E_Li7 / E_ortho | 478,000 / 19.82 | 24,117 | α⁻¹ × 176 = 24,118 | **0.004%** |
| √(E_Li7 / E_ortho × 1000) | √24,117 | 155.3 | Be IE₃ = 153.9 | **0.9%** |
| Q(Be-7) / E*(Be-7) | 862 / 429 | 2.009 | ~2 | **0.5%** |
| t½(Be-7) / t½(ortho) | 4,598,208 / 7,870 | 584.3 | mp/me / π = 584.4 | **0.02%** |
| Z³(In-111) / Z³(Be-7) | 117,649 / 64 | 1,838 | mp/me = 1,836.15 | **0.1%** |
| PF(Be-7) / (mp/me × Z) | 7,514 / 7,345 | 1.023 | 1.0 (exact match) | **2.3%** |

## Rejected Ratios (Numerological Noise)

| Ratio | Value | Best match attempt | Accuracy | Status |
|-------|-------|-------------------|----------|--------|
| 176 itself | 176 | No fundamental decomposition | — | UNRESOLVED |
| Q_Be7 / Q_n = 1.102 | 1.102 | No clean constant | >5% | REJECTED |
| Grammar penalty = 80 keV | 80 | No clean constant | — | SYSTEM-SPECIFIC |
| ~35 day = 3.02 × 10⁶ s | 3.02M | π × 10⁶ = 3.14M | 3.9% | TOO ROUGH |
| PF ∝ mp/me × Z (general) | — | Only works for Be-7 | — | REJECTED |

## Key Energy Relationships

| Parent→Daughter | Q_EC (keV) | Q_n (keV) | Penalty | Ratio Q/Q_n |
|----------------|-----------|-----------|---------|-------------|
| Be-7 → Li-7 | 862 | 782 | +80 | 1.102 |
| Ar-37 → Cl-37 | 814 | 782 | +32 | 1.041 |
| Ca-41 → K-41 | 421 | 782 | −361 | 0.539 |
| Fe-55 → Mn-55 | 231 | 782 | −551 | 0.295 |
| I-125 → Te-125 | 186 | 782 | −596 | 0.238 |
| Ho-163 → Dy-163 | 2.8 | 782 | −779 | 0.004 |
| Pb-205 → Tl-205 | 51 | 782 | −731 | 0.065 |

## The Q Per Sprocket Analysis

| Isotope | A | Q (keV) | Q/A (keV/sprocket) |
|---------|---|---------|-------------------|
| Free n | 1 | 782 | **782** |
| Be-7 | 7 | 862 | **123** |
| Ar-37 | 37 | 814 | 22 |
| Xe-127 | 127 | 662 | 5.2 |
| Yb-169 | 169 | 909 | 5.4 |
| Pb-205 | 205 | 51 | 0.25 |

**Q per sprocket decreases with A.** The energy available per gear
position drops as the chain gets longer. Longer chains distribute
the stress more effectively.
