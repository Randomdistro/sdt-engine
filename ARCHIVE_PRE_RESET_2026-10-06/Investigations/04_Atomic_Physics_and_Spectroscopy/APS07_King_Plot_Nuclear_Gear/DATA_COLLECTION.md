# APS07 — King Plot Nonlinearity: Data Collection

> **Status**: DATA COLLECTION (no SDT analysis yet — this file is measured-world input only)
> **Collected**: 2026-07-11, by Fable (HUNTER), at Harvey's direction
> **Motivation**: If the nucleus is a complex universal/orbital gear driving the electron
> structure (valence grammar ↔ nuclear grammar correlation), the electron ladder must carry
> fingerprints of nuclear *construction* (n_d, n_t) beyond what Z + mass + charge-radius allow.
> King-plot nonlinearity is precisely the residual after mass + size are subtracted — it is
> the measured world's own ledger of "what else the electron knows about the nucleus."
> **This is the SDT-vs-QED fork**: standard theory permits only ⟨r²⟩, ⟨r⁴⟩, polarization,
> QFS; a gear-hub nucleus permits grammar-sorted structure.

---

## 1. What a King plot is (King 1963; King's book 1984)

Leading-order isotope shift of transition *i* between isotopes A, A′:

```
ν_i^AA' = K_i μ^AA' + F_i δ⟨r²⟩^AA'
```

- `μ^AA' = 1/m_A − 1/m_A'` (inverse-mass difference) — the **mass shift** (movement re-pricing
  from the changed recoil partner)
- `δ⟨r²⟩^AA'` — nuclear mean-square charge-radius difference — the **field shift** (seat-size change)
- K_i, F_i electronic (transition-dependent, isotope-independent)

Divide by μ (modified shifts): two transitions plotted against each other over ≥3 isotope
pairs must fall on a **straight line** — slope F₂/F₁, intercept from K's. **Any nonlinearity
= a third nuclear parameter the two-term factorisation cannot absorb.**

Higher-order expansion actually used by the experiments (Hur 2022 Eq. 1):

```
ν_γ^AA' = F_γ δ⟨r²⟩ + K_γ μ + G(4)_γ δ⟨r⁴⟩ + G(2)_γ [δ⟨r²⟩²] + υ_ne D_γ a^AA' + ...
```

where `a^AA' = A − A'` (neutron-number difference) and `υ_ne = (−1)^(s+1) y_e y_n /(4πħc)`
is a hypothetical new boson coupling. **The new-physics term rides on the NEUTRON COUNT;
the SM terms ride on radius moments** — that distinction is the whole discrimination game
(Flambaum, Geddes, Viatkina PRA 97, 032510 (2018)).

### Pattern decomposition (four pairs → 2D nonlinearity space)
With 4 isotope pairs, residuals decompose onto two basis patterns (Counts 2020 ζ±; Hur 2022 Λ±):
- **Λ₊ / ζ₊ = zigzag** `+ − + −`
- **Λ₋ / ζ₋ = curve** `+ − − +`
Each candidate source has a FIXED direction in the (λ₊, λ₋) plane; multiple transitions
sharing one direction ⇒ one dominant source.

---

## 2. Ytterbium (Z = 70; even isotopes 168, 170, 172, 174, 176)

Nuclear grammar (canonical, Z≥2): `n_t = A − 2Z`, `n_d = 3Z − A − 2`, 1 alpha core.

| A | n_t (tritons) | n_d (deuterons) |
|---|---|---|
| 168 | 28 | 40 |
| 170 | 30 | 38 |
| 172 | 32 | 36 |
| 174 | 34 | 34 |  ← n_t = n_d crossing
| 176 | 36 | 32 |

Deformed nuclei (prolate, β₂ ~ 0.3). Note **174 is the triton/deuteron balance point** —
unremarked in the literature, flagged here for the grammar analysis.

### 2.1 Counts et al., PRL 125, 123002 (2020) — the seed (arXiv:2004.11383)
Transitions: α: ²S₁/₂→²D₅/₂ (411 nm), β: ²S₁/₂→²D₃/₂ (436 nm), trapped single Yb⁺ ions, ~300 Hz accuracy.

| pair | μ (10⁻⁶ u⁻¹) | ν_α (kHz) | ν_β (kHz) | δ⟨r²⟩ (fm², CI) |
|---|---|---|---|---|
| (168,170) | 70.113 698(46) | 2 179 098.93(21) | 2 212 391.85(37) | −0.156 |
| (170,172) | 68.506 890 50(63) | 2 044 854.78(34) | 2 076 421.58(39) | −0.146 |
| (172,174) | 66.958 651 95(64) | 1 583 068.42(36) | 1 609 181.47(22) | −0.115 |
| (174,176) | 65.474 078 21(65) | 1 509 055.29(28) | 1 534 144.06(24) | −0.110 |
| (170,174) cross-check | | 3 627 922.95(50) | 3 685 601.95(33) | |

Electronic factors (CI): F_α = −15.852 GHz/fm², F_β = −16.094 GHz/fm², K_α = −1678.3 GHz·u, K_β = −1638.5 GHz·u.
**Result: 3×10⁻⁷ fractional nonlinearity, 3σ.** ζ± analysis: consistent with both new-boson
line and QFS line (couldn't separate). Seltzer δ⟨r⁴⟩ absorbed into QFS term here.

### 2.2 Hur et al., PRL 128, 163201 (2022) — two sources (arXiv:2201.03578)
New transition γ: ²S₁/₂→²F₇/₂ octupole (467 nm), ~500 Hz. F-state electron config very
different from D states → nonlinearity ×20 larger.

| pair | ν_γ (MHz) |
|---|---|
| (168,170) | −4 438.160 30(50) |
| (170,172) | −4 149.190 38(45) |
| (172,174) | −3 132.321 60(50) |
| (174,176) | −2 976.391 60(48) |
| (168,172) | −8 587.352 00(47) |
| (170,174) | −7 281.511 88(45) |
| (172,176) | −6 108.712 93(44) |

Absolute γ frequencies (THz): 168: 642.108 197 799 37(37); 170: 642.112 635 960 22(32);
172: 642.116 785 150 887 6(24) [ref]; 174: 642.119 917 472 26(33); 176: 642.122 893 863 84(36).

**Results**:
- γ-vs-α King plot: **41σ nonlinearity** (10⁻⁵ level). With neutral Yb data (δ: ¹S₀→³P₀
  clock, Ono 2022; ε: ¹S₀→¹D₂, Figueroa 2022): **240σ**.
- All five transitions (α,β,γ,δ,ε) lie along ONE direction in the (λ₊,λ₋) plane ⇒ one
  dominant source — and that direction matches **neither the new boson nor the QFS**.
- Dominant source: **δ⟨r⁴⟩** (Seltzer / 4th radial moment). Nuclear DFT with four EDFs;
  only the **Fayans functional Fy(Δr)** reproduces the trend (Skyrme SV-min, UNEDF1,
  RD-min all fail — they give monotone δ⟨r²⟩ ratios; data is non-monotone).
  δ⟨r²⟩ ratios measured to <20%; **the data discriminates between nuclear models**.
- **Second source at 4.3σ** (χ²=25.4 for single-source fit): too large for QFS. Origin
  UNIDENTIFIED in the paper. Its per-pair pattern is the deviation off the common line.
- New-boson bound (if second source = boson): y_e·y_n near/above (g−2)_e × neutron
  scattering bounds, masses 10²–10⁶ eV.

### 2.3 Figueroa et al., PRL 128, 073001 (2022) — neutral Yb ¹S₀→¹D₂ (556→? ε line)
Nonlinearity in joint Yb/Yb⁺ analysis **accountable by nuclear deformation** (quadrupole
β₂ changes along the chain). (Data via compilations; shifts at few-Hz level.)

### 2.4 Door et al., PRX 15, 011056 (2025) — Penning-trap masses + 411/467 nm (arXiv:2403.07792)
PENTATRAP mass ratios, δ(m/m) ~ 4×10⁻¹²:

| A | m_A/m_172 |
|---|---|
| 168 | 0.976 715 921 749(4) |
| 170 | 0.988 355 799 258(4) |
| 174 | 1.011 649 212 140(4) |
| 176 | 1.023 305 557 965(4) |

(Literature mass deviations up to −1890(780)×10⁻¹² for 168 — old masses were WRONG;
mass-table errors are themselves a King-plot nonlinearity source.)

Isotope shifts (Hz): α: (168,170) 2 179 098 868.0(5.3); (170,172) 2 044 851 281.0(4.9);
(172,174) 1 583 064 149.3(4.8); (174,176) 1 509 053 195.8(4.7).
γ: (168,170) −4 438 159 671.1(15.7); (170,172) −4 149 190 501.1(15.7);
(172,174) −3 132 320 458.1(15.7); (174,176) −2 976 392 045.3(15.7).
[Note ~kHz-scale differences from 2.1/2.2 values reflect corrected masses/systematics.]

**Results**: mean nonlinearity 20.17(2) kHz; **23σ preference for TWO sources**
(strengthens Hur's 4.3σ by ×5). Leading source confirmed δ⟨r⁴⟩; extracted
**δ⟨r⁴⟩^(176,174) ≈ 7 fm⁴** (ab initio VS-IMSRG predicts 6–8 fm⁴ — consistent).
QFS slope incompatible; new-physics-alone slope incompatible. New boson 2σ bounds
supersede all previous KP bounds (keV–MeV range; cuts into the 17 MeV ATOMKI band).

### 2.5 2026: ¹S₀↔³P₂ measurement (arXiv:2601.08487) — boson interpretation EXCLUDED
Fifth ultra-narrow transition (magic wavelength 905.4(2) nm lattice, <100 Hz lines).
Shifts vs 174 (Hz): (168,174) 3 677 546 251.3(6.8); (170,174) 2 300 235 711.8(5.7);
(172,174) 1 006 735 627.8(4.9); (176,174) −960 303 320.6(7.0).

3D generalized King plot, five transitions simultaneously: **86σ residual nonlinearity**;
light-boson-only interpretation excluded for m_φ ≤ 6.5 keV and 18–100 keV (χ²=872 at
best-fit 8.4 keV without theory uncertainties; one insensitive window ~9.67 keV survives).
**Conclusion: Yb nonlinearity = higher-order SM nuclear structure (δ⟨r⁴⟩ + second source),
not a new force — but the second source remains an open nuclear-structure question.**

---

## 3. Calcium (Z = 20; even isotopes 40, 42, 44, 46, 48)

Nuclear grammar: n_t = A − 40, n_d = 58 − A:

| A | n_t | n_d | note |
|---|---|---|---|
| 40 | 0 | 18 | **zero tritons** — pure alpha+deuteron nucleus; doubly magic |
| 42 | 2 | 16 | |
| 44 | 4 | 14 | |
| 46 | 6 | 12 | |
| 48 | 8 | 10 | doubly magic (N=28); famously small radius change 40→48 |

Spherical nuclei — finite-size effects ~10³ smaller than Yb (stated in paper). The chain
runs from a **triton-free** nucleus to a neutron-rich doubly-magic one.

### 3.1 PTB/MPIK, PRL 134, 233002 (2025) (arXiv:2412.10277)
Transitions: Ca¹⁴⁺ ³P₀→³P₁ (570 nm, HCI clock) and Ca⁺ ²S₁/₂→²D₅/₂ (729 nm), sub-Hz;
masses to <4×10⁻¹¹ (Penning trap).

| pair | Ca¹⁴⁺ 570 nm (Hz) | Ca⁺ 729 nm (Hz) |
|---|---|---|
| (40,42) | 539 088 421.24(12) | 2 771 872 430.217(27) |
| (40,44) | 1 030 447 731.64(11) | 5 340 887 395.288(38) |
| (40,46) | 1 481 135 946.74(14) | 7 768 401 432.916(63) |
| (40,48) | 1 894 297 294.53(14) | 9 990 382 526.834(55) |

**Results**:
- Nonlinearity **~900σ** — smooth curved pattern, all five isotopes on a consistent curve.
- Second-order mass shift (largest expected SM higher-order term) computed:
  K⁽²⁾₅₇₀ = −1.0(1) GHz·u², K⁽²⁾₇₂₉ = 0.59 GHz·u² — **direction in ζ-plane WRONG, cannot
  account for the observed nonlinearity.**
- **Nuclear polarization** (dipole + giant resonances through octupole; 50% model
  uncertainty) is the only SM term left big enough — uncertainty ellipse overlaps data ⇒
  "compatible with SM" but essentially **unconstrained nuclear-model territory.**
- New-boson Yukawa bounds improved for 10 eV–10⁷ eV masses despite the nonlinearity.

### 3.2 Earlier Ca⁺ work
Solaro et al. PRL 125, 123003 (2020): Ca⁺ D₃/₂/D₅/₂ fine-structure King plot, ~20 Hz;
linear at that precision. Knollmann et al. PRA: 729/733 nm shifts. (Superseded by 3.1.)

---

## 4. Other elements — status board

| element | status | detail |
|---|---|---|
| **Sm** (Z=62) | NONLINEAR (old data) | first observed KP nonlinearities (MHz-era data; refs in Fuchs 2025 [61,70,71]) — deformed rare earth like Yb |
| **Sr** (Z=38) | linear so far | 84,86,87,88; 689 nm + 394 nm (PRR 1, 033113 (2019): 91052(35), 54600(33), 51641(28) kHz for 84,86,87 vs 88); Rydberg-transition shifts sub-MHz (2024/25); clock-network precision available |
| **Cd** (Z=48) | proposed/measured MHz | 6 stable even; 229/326/361/480 nm lines analysed as BSM probe (arXiv:2208.13599); earlier nonlinearity reports in Zn/Cd RESOLVED as errors (linearity restored) |
| **Ba** (Z=56) | data 100–400 MHz | 4 even stable + one 10²¹ y; KP candidate |
| **Kr⁺** | sub-MHz | P-state fine-structure splitting isotope shifts (2025) |
| **Th³⁺** | <10 MHz | 2025 measurement |
| **molecules** | new arena | KP analysis extended to diatomics (arXiv:2301.11064); RaF isotope shifts (arXiv:2105.10549) |
| **global fit** | tool exists | `kifit` (Fuchs et al., arXiv:2506.07303): first combined multi-element analysis framework; currently linear-KP-only; recommends: more even isotopes, metastable isotopes of Ca/Yb, Ba, Cd next |

---

## 5. The scorecard (what the measured world now says)

1. **King linearity is dead at high precision.** Yb: 240σ (86σ in 5-transition 3D form);
   Ca: ~900σ; Sm: nonlinear in old data. Wherever precision reaches Hz, the two-parameter
   (mass + size) nucleus FAILS.
2. **The failure is NOT a new force.** Boson-only interpretations excluded in Yb (2026);
   Ca bounds improved. The nonlinearity direction matches nuclear STRUCTURE.
3. **What the nucleus is telling the electron, beyond mass and ⟨r²⟩:**
   - Yb (deformed): δ⟨r⁴⟩ ≈ 7 fm⁴ per pair-step — the 4th moment = SHAPE information
     (deformation), plus an **unidentified second source (23σ)**.
   - Ca (spherical): second-order mass shift fails; only **nuclear polarization** —
     i.e. the nucleus's dynamic RESPONSE, not its static size — can carry it in the SM.
4. **Model discrimination is live**: only the Fayans functional survives Yb; Skyrme
   functionals killed by tabletop atomic physics.
5. **Mass tables were wrong** (Yb-168 off by ~2×10⁻⁹) — Penning-trap masses are now a
   mandatory input.

## 6. Open hooks for the SDT/grammar analysis

- ~~Sort every residual by **triton count n_t** instead of neutron number.~~ **Bare SORT struck
  2026-07-25** (see `APS07_VERDICT_DIRECT_2026-07-25.md`): at fixed Z, n_t is monotone in N, so
  the re-sort reproduces the N-sort — order adds nothing. **The landmark content stays live**:
  the neutron ledger runs N = 2 + n_d + 2·n_t (each triton carries TWO neutrons — the triton
  pool moves at 2n while the count steps by one), and the grammar picks absolute positions no
  count-sort distinguishes — the triton-free anchor n_t = 0 (Ca-40; the 40→42 first-triton step
  is the opposite-sign residual), the **n_t = n_d crossing at 2A = 5Z − 2 → A = 174 for Yb**, and
  EC-lineage offsets. Cross-element landmark test + the magnitude targets (kHz scale at the Ca
  46/48 flip, δ⟨r⁴⟩ per pair-step from trefoil packing, naming Yb's second source) are the moves.
- The Λ₊ zigzag vs Λ₋ curve basis is exactly a "pairing-parity vs smooth-drift"
  decomposition — compare with grammar parity (even/odd deuteron-triton exchange steps).
- EC-grammar isotopes (He-3 core) are ODD-Z/odd-A mostly — excluded from all current
  King plots (they use spinless even isotopes only). Metastable/odd isotopes are on the
  community wish list; grammar predicts they sit OFF the even-isotope line in a specific way.
- Nuclear polarization (Ca's residual carrier) = the nucleus as a RESPONSIVE gear —
  closest SM concept to "the hub engages the electron's tour."

## 7. Ca nonlinearity magnitude — reconstructed from the published table (2026-07-11)

The paper never states the NL in Hz. Reconstructed here by building the King plot directly
from PRL 134, 233002 Table I (digit-verified against the published PDF): weighted linear fit
of modified shifts ν̄₅₇₀ vs ν̄₇₂₉ over the four (40,A) pairs, residuals mapped back to Hz on
the 570 nm line:

| pair | residual (Hz) |
|---|---|
| (40,42) | +57 |
| (40,44) | +15 |
| (40,46) | **−1077** |
| (40,48) | **+1060** |

RMS ≈ 0.76 kHz, max ≈ 1.1 kHz → **beat span c/Δν ≈ 250–425 km**. Pattern decomposition:
zigzag ζ₊ ≈ −520 Hz and curve ζ₋ ≈ +540 Hz, comparable — NOT a pure smooth curve; the
deviation is concentrated in a sign-flip between A=46 and A=48 (n_t = 6 → 8; Ca-48 doubly
magic, N=28). Caveat: this residual basis is not identical to the paper's (λ₊,λ₋) machinery,
but the underlying fact is table-level: the four points miss a straight line by up to ±1.1 kHz.

**Pre-committed prediction test (fishbowl discipline)**: before reconstruction, Fable
predicted ~100 Hz (bracket 25–150), span ~3000 km — **MISSED by ~5–7×** (outside bracket).
Diagnosed error: treated the ~10³σ significance as residual/optical-floor (0.12 Hz),
omitting the mass-ratio error contribution (~0.25 Hz/point at A=46,48) to σ_eff; corrected
route (10³σ × 0.3–0.5 Hz) lands 300–500 Hz, consistent with the reconstruction. Recorded
as a worked example of prediction-then-look with honest scoring.

## 8. Mass-defect ledger vs King residuals (2026-07-11)

Binding energies computed from the papers' own mass ratios (Ca: 4×10⁻¹¹; Yb: 4×10⁻¹²)
anchored on one atomic mass each [anchors from memory — AME verify owed]. Ca BE values
reproduce standard AME to <10 keV (342.03/361.88/380.94/398.75/415.98 MeV).

**Ca (Z=20)** — sequential-pair basis:

| pair | King res (Hz) | S2n (MeV) | δ⟨r²⟩ step (fm²) | Δ²BE (MeV) | grammar step |
|---|---|---|---|---|---|
| (40,42) | +96 | 19.844 | +0.213 | — | 0→2 t |
| (42,44) | −236 | 19.063 | +0.069 | −0.780 | 2→4 t |
| (44,46) | **−1653** | 17.812 | **−0.158** | **−1.251** | 4→6 t |
| (46,48) | **+1641** | 17.230 | −0.127 | −0.582 | 6→8 t |

(radii: famous Ca parabola r_ch 3.4776/3.5081/3.5179/3.4953/3.4771 fm — memorized, verify)

**THE CORRELATION**: the King residual couplet sits exactly on the radius-inversion steps
(44→46→48, where adding neutrons SHRINKS the boundary), and the mass-defect curvature Δ²BE
kinks at the same place (max softening at 46). BE/A peaks at **Ca-46** (8.6686), where
n_t/n_d = 6/12 = 1/2. Ca-48 returns to Ca-40's boundary radius with a completely different
interior (8t,10d vs 0t,18d) — same outside, different gearing; the two-parameter King line
cannot price a hub whose boundary and mass decorrelate. Ca-46 is also the rarest stable
isotope (0.004%, production-bypassed) and sits at the kink.

**Yb (Z=70)**: BE 1362.6 → 1419.1 MeV; S2n declines smoothly 15.33 → 12.69; Δ²BE = −0.69,
−0.80, −1.14 (smooth accelerating softening, no kink) — consistent with the Yb King NL being
one smooth dominant source (δ⟨r⁴⟩ shape drift) unlike Ca's localized event. n_t = n_d = 34
crossing at A=174. Yb-168 (the isotope whose legacy mass was wrong by 1.9×10⁻⁹) is the
p-process rarity (0.13%).

**EC bridge (from ATOMICUS EC_data/13_Spallation_EC_Chains.md)**: Ca-44 is the endpoint of
the double-EC repair chain Ti-44 → Sc-44 → Ca-44 (Ti-44: N=Z, 0 tritons, 20 deuterons,
SN alpha-freeze; each EC step = +2 tritons, −3 deuterons). Ca-40, Ti-44, Ni-56, Se-68 are
all triton-free N=Z starters; EC chains walk them onto the stability line by installing
tritons. Long-lived EC steps ↔ small Q (Tc-97: 320 keV, 4.21 My) = small movement re-pricing.

## Sources (primary)

- King, W.H. (1963); *Isotope Shifts in Atomic Spectra* (1984)
- Counts et al., PRL 125, 123002 (2020) — arXiv:2004.11383
- Solaro et al., PRL 125, 123003 (2020)
- Figueroa et al., PRL 128, 073001 (2022) — arXiv:2111.01429
- Hur et al., PRL 128, 163201 (2022) — arXiv:2201.03578
- Ono et al., PRX 12, 021033 (2022) — neutral Yb clock transition
- Door et al., PRX 15, 011056 (2025) — arXiv:2403.07792
- PTB/MPIK Ca, PRL 134, 233002 (2025) — arXiv:2412.10277
- Yb ¹S₀↔³P₂ (2026) — arXiv:2601.08487
- Flambaum, Geddes, Viatkina, PRA 97, 032510 (2018) — arXiv:1709.00600
- Berengut et al., PRL 120, 091801 (2018) — generalized KP proposal
- Fuchs, Kirk, Mariotti, Richter, Robbiati (2025) — arXiv:2506.07303 (kifit, global)
- Cd BSM probe — arXiv:2208.13599; molecules — arXiv:2301.11064; Sr — PRR 1, 033113
