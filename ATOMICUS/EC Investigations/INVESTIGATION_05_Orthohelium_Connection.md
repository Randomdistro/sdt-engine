# INVESTIGATION 05: Orthohelium/Parahelium Connection to EC

> Navigation: [Grammar Test](INVESTIGATION_01_Grammar_Test.md) ·
> [Be-7](INVESTIGATION_02_Be7_Deep_Dive.md) ·
> [Closures](INVESTIGATION_03_Subshell_Closure_Pattern.md) ·
> [Protection](INVESTIGATION_04_Protection_Factor.md) ·
> [Missing](INVESTIGATION_06_Missing_Elements.md) ·
> [Ratios](INVESTIGATION_07_Energy_Ratios.md) ·
> [Dual Defect](INVESTIGATION_08_Dual_Defect_Branching.md) ·
> [FINAL](FINAL_REPORT.md)

---

## 1. Definitions (SDT Gear Model)

### Parahelium
The 1s² ground state of helium. Two electrons in counter-rotating
convergence orbits (the parahelium dyad). Energy: 0 eV (reference).
This is the default, serene, lowest-energy configuration of the
helium atomic gear train.

### Orthohelium
The 2³S₁ metastable excited state. One electron has been kicked from
1s to the 2s excitation position. The pair is now in a same-direction
circulation (parallel gears). This is METASTABLE — it cannot radiate
a single photon to return to parahelium because the transition violates
ΔS = 0.

### The transition
Ortho → para produces a single photon at **62.56 nm** (**19.82 eV**),
in the extreme ultraviolet (XUV). This is the most energetic allowed
electronic transition in any two-electron system.

Metastable lifetime: **~7,870 s** (2.19 hours). This is the lifetime
of the 2³S₁ state against all de-excitation mechanisms.

---

## 2. The Helium Template in Nuclear EC

### The hypothesis (as developed)

The 1s² parahelium dyad is the electronic template that the alpha core
(2p+2n) projects outward. In Be-7, the 2s shell is occupied, creating
a Li-like / Be-like electronic structure on top of the alpha core's
projection.

The QUESTION: does the parahelium template of the 1s² electrons govern
the EC mechanism?

### What the data shows

**YES — partially:**
- 93% of Be-7 EC is K-capture (1s electrons) — the parahelium position
- L-capture (2s, 7%) is secondary and environment-dependent
- The K-capture rate is constant regardless of chemical bonding

**NO — to the full dyad requirement:**
- Be³⁺ (single 1s electron, NO dyad) **still undergoes EC**
- The parahelium pairing is NOT required for the mechanism
- A single electron coupled to the nuclear convergence field suffices

### Revised interpretation

The parahelium dyad is the PREFERRED entry point for EC — the most
efficient channel — but not the REQUIRED entry point. Any electron
meshed into the nuclear gear train can be captured. The 1s electrons
are most efficiently meshed (closest to the nucleus, highest density
at the convergence point).

---

## 3. The Orthohelium → EC Timescale Chain

| Process | What flips | Energy (eV) | Time | Scale |
|---------|-----------|-------------|------|-------|
| Orthohelium decay | 1 electron gear direction | 19.82 eV | 7,870 s | Electronic |
| Be-7 EC | 1 proton identity (p→n) | 862,000 eV | 4,598,208 s | Nuclear |
| Free neutron β⁻ | 1 neutron identity (n→p) | 782,000 eV | 612 s | Nucleonic |

### The 584× ratio

t½(Be-7) / t½(orthohelium) = 4,598,208 / 7,870 = **584.3**

Possible decomposition: **584.3 ≈ mp/me / π = 1836.15 / 3.14159 = 584.4**

This is correct to 0.02%.

If this is genuine (not coincidental), it means:
- The nuclear gear flip (EC) takes mp/me / π times longer than the
  electronic gear flip (ortho→para)
- mp/me is the mass ratio (nuclear gears are heavier)
- π is the geometric phase factor (one full cycle of rotation)
- Combined: the nuclear gear system runs mp/me/π times slower than
  the electronic gear system

---

## 4. The 62.6 nm XUV Photon — What Else Emits This?

The 62.56 nm photon is characteristic of helium's ortho→para transition.

Other known sources of ~62.6 nm:
| Source | Wavelength (nm) | Process |
|--------|----------------|---------|
| He 2³S₁ → 1¹S₀ | 62.56 | Orthohelium forbidden decay |
| Solar He II | ~60.4 (30.4 × 2) | He⁺ Lyman-α resonance |
| O V | 62.97 | O⁴⁺ emission line |

The He orthohelium line at 62.56 nm is UNIQUE to the two-electron
gear-flip. No other process emits at exactly this wavelength.

---

## 5. The 24,117 Ratio Decomposition

478,000 eV / 19.82 eV = **24,117** (using 478 keV for Li-7 gamma)

24,117 ≈ 137.036 × 176.0 = **24,118** (0.004% match)

### What is 137 × 176?

- 137 = α⁻¹ (fine structure constant inverse): the fundamental coupling
  between circulation and radiation
- 176 = undetermined. 176 is NOT a standard physical constant.

Possible interpretations of 176:
- 176 = 4 × 44 = Z(Be) × 44. But 44 = A(Ti-44), a coincidence.
- 176 = 16 × 11 = Z²(Be) × 11
- 176 = 175 + 1 = A(Hf-175) + 1. Coincidence.
- 176 = 2⁴ × 11 = 16 × 11

None reduce to fundamental constants cleanly. 176 may be a DERIVED
quantity specific to the A=7 system.

### √24,117 = 155.3 ≈ Be IE₃ (153.9 eV)

The geometric mean of the nuclear and electronic gear-flip energies
equals the alpha core breach energy of beryllium. This places the
core breach at the MIDPOINT (in log scale) between the two gear-flip
scales:

```
19.82 eV ←── 155.3 eV ──→ 478,000 eV
(electronic)  (core breach)   (nuclear)

log₁₀(19.82) = 1.297
log₁₀(155.3) = 2.191  ← midpoint
log₁₀(478,000) = 5.679

Midpoint of 1.297 and 5.679 = 3.488 → 10^3.488 = 3,074
Not exactly 155.3. So it's not the LOG midpoint.

Geometric mean: √(19.82 × 478,000) = √(9,473,960) = 3,078
Not 155.3 either. So the √ratio ≠ geometric mean directly.

√(478,000/19.82) = √24,117 = 155.3 ← this IS √(ratio), not √(product)
```

The quantity 155.3 is the SQUARE ROOT of the energy RATIO, not the
geometric mean. It measures how many times more energetic the nuclear
flip is compared to the electronic flip, expressed as a multiplicative
depth: the nuclear scale is 155² = 24,100 times deeper than the electronic.

And this depth ≈ the energy to breach the alpha core (153.9 eV), measured
from the valence shell.

---

## 6. The Magnetic Quenching Question

### Open question (from session notes)

Can an extremely high magnetic field (nuclear Zeeman mixing) alter
the Be-7 EC rate?

If the defect is COMPOSITIONAL (wrong nucleon type), no magnetic
field can change it — you cannot rotate a proton into a neutron
with a magnet.

If the defect is CIRCULATIONAL (wrong rotation direction), a
magnetic field that reverses the offending circulation COULD
stabilise the nucleus.

### What the data says

Be-7⁴⁺ is STABLE (no decay, no output). This proves the defect
is compositional — the nucleus needs an electron to convert p→n.
No electromagnetic field can substitute.

**Prediction**: magnetic fields should NOT alter Be-7 EC rate.
This is testable and would distinguish SDT's compositional defect
model from any circulational model.

**Note**: Standard physics predicts minimal EC rate changes from
magnetic fields (the nuclear Zeeman splitting is ~μ_N × B ≈ nanovolts
at achievable fields, negligible compared to Q = 862 keV).

---

## 7. The Orthohelium → Nuclear Parallel — What Holds and What Doesn't

| Aspect | Electronic (orthohelium) | Nuclear (Be-7 EC) | Match? |
|--------|--------------------------|-------------------|--------|
| What flips | Electron gear direction | Proton identity | **NO** (different) |
| Energy budget | 19.82 eV | 862,000 eV | Scale by 43,500× |
| Timescale | 7,870 s | 4,598,208 s | Scale by 584× ≈ mp/me/π |
| Output photon | 62.56 nm XUV | 478 keV gamma | Same: radiation |
| Requires external input | Yes (collision) | Yes (electron capture) | **YES** |
| Product lower energy | Yes (parahelium) | Yes (Li-7) | **YES** |
| Metastable against spontaneous radiation | Yes (ΔS forbids) | Yes (Q < 1022 forbids β⁺) | **YES** |
| Dyad required | N/A (only 2 electrons) | NO (Be³⁺ works) | **NO** |
| Mediated by weak force | No (EM only) | YES | **NO** |

### Conclusion

The orthohelium/parahelium template is an ANALOGY, not a mechanism.
The electronic gear flip (ortho→para) and the nuclear gear flip (EC)
share structural parallels (metastability, external input, radiation
output) but differ fundamentally in mechanism (EM vs weak) and scale
(eV vs keV).

The energy ratios (24,117 = 137 × 176, √ ≈ 155) and timescale ratio
(584 ≈ mp/me/π) suggest a deeper connection between electronic and
nuclear gear-flip dynamics, but the CONNECTION is not identity — it's
scaling.
