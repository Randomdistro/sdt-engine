# APS12 Pre-registration — Nuclear gravitation and emission (Δz)

**Date:** 2026-08-13  
**Author:** J. C. Harvey, Melbourne.  
**Direct execution.** **Canon edits:** none.  
**Status:** PRE-REGISTERED. This file is frozen before any instrument exists.  
**Prompt:** `PROMPT.md`. **Data:** `DATA_REQUIREMENTS.md`. **Run record:** `RUN_LOG.md`.

Upstream: GOM01/GOM22 depth–closure (`z = ϟ/r`, `c_far = c(1−z)²`); APS01 velocity-seat chain (H / H-like); EMC04 electropause `P_eff`; NP01 `alpha_grammar`; NP12 `nuclear_boundary_radius(A)`; APS07 King landmarks (sort-strike stands; landmarks live).  
Out of scope: Lamb nS–nP amplitude (APS11/PPT08); APS04 1051.8; B04 `k_Lamb`; QED series as an SDT derivation; G, M as fundamentals; retuning packer `dnn`.

---

## ⓪

1. **What don't we know?** Whether laboratory emission, isotope shift, and ionisation energy are the same gravitational depth difference `Δz` evaluated at the electron seats of the nuclear koppa well, excitation by excitation, isotope by isotope, and ionisation by ionisation — including when the well is not a point and not one-electron.
2. **Why it matters?** If a line is `Δz`, then nuclear construction (Z, A, grammar, remaining electrons) is a predictor of spectra, not a perturbation bolted on afterwards. APS01 paid the H-like closed form. This investigation asks for the nuclear-gravitation content that form does not already share with Rydberg algebra.
3. **How?** Freeze hold-outs. Validate the instrument on hydrogen (known answers). One-pass tables on three axes. Occupancy and size rules named here, not inverted from the hold-outs.
4. **Wrong if?** H-like `Δz` misses the APS01 bar; last-electron IE misses the 1% / 2% bars; a scored MATCH is obtained by reading `Z_eff` from IE; King residuals are “explained” by re-sorting on `n_t` at fixed Z; a coefficient is inserted to land Fe XXV or Na D.
5. **Done when?** Dual verdict: prompt completion (every required table shipped) + physics class per axis. H-like alignment alone is CONVERGENCE, not NATIVE-distinct.

---

## Ontology (frozen)

The nucleus sits inside the atom’s c-boundary `ϟ = Z r_e` (`atomic` / `nuclear::c_boundary_nuclear`). Through-going light is not born at `r < ϟ`. Electronic emission is born at electron seats outside that surface. The photon is the depth difference between two seats:

```
z(r) = ϟ_felt / r          ϟ_felt = koppa the electron actually feels
E_bind = ½ m_e c² z        (leading; Law V remainder logged, not fitted)
hν = ½ m_e c² (z_lower − z_upper)
```

This is GOM01 C1 (`z_spec = z_emit − z_obs`) with the observer at the lower seat. Domain pressure `P_eff` is electromagnetic (electropause), not the solar `P_conv` kernel. The *shape* is Law III. Calling it nuclear gravitation means: the nuclear displacement sets the koppa well the electron occupies; gravity and Coulomb are one occlusion law.

Hydrogen is a proton **center**. He⁺ is an α **center**. Packed D/T seats are not hydrogen rings (APS11 center-vs-seat). Neutral multi-electron atoms are occupancy of those centers plus companion electropauses.

---

## What is scored, and what is not

| Object | Role |
|---|---|
| `zk² = 1` | Algebraic identity. Print it. Do not score it as a mechanism win. |
| H-like `hν = ½ m_e c² Δz` vs NIST | Instrument spine + CONVERGENCE with Rydberg closed form. Origin is Δz. Alignment cannot discriminate. |
| Last-electron IE vs `Ry Z² (μ/m_e)` | Same closed form as H-like ionisation. CONVERGENCE. Gate is still numeric (the spine must hold). |
| Intermediate IE from a named occupancy rule that does **not** invert NIST IE | NATIVE-distinct candidate. |
| Isotope shift from reduced mass only | Two-body kinematics. Tag IDENTITY / CONVERGENCE. |
| Isotope shift from NP12 `R(A)` (not measured `⟨r²⟩`) | Size channel from packing. Sign and order are gated; magnitude has CALIBRATED budget **0**. |
| Grammar landmarks (`n_t = 0` entry; `n_t = n_d`) coinciding with King structure | Live APS07 content. Sort-as-evidence is struck. |
| He-like / Li-like / neutrals from remaining-electron occupancy | NATIVE-distinct if the rule was named here and hits; else OPEN. |

---

## Frozen occupancy rules (Phase 2 / 4 — one pass, both reported)

Let `q` be the ion charge after the ionisation under test (the electron is leaving a system with `N_e` electrons; `N_e = Z − q + 1` before the event; after, `N_e' = Z − q`). Valence shell index `n` is the spectroscopic principal index of that electron (H-like: `n = 1` for the last electron; for outers, the ground `n` of that configuration as in NIST ground term — frozen in the corpus, not fitted).

| ID | `ϟ_felt` | Meaning |
|---|---|---|
| **S_bare** | `Z r_e` | No screening. Every electron feels the full nuclear koppa. |
| **S_ion** | Perfect inner screening. NIST ionisation `IE_k` (k = 1…Z) uses `Z_eff = k`. |

S_ion (frozen):

```
IE_k  (k = 1, 2, …, Z)  removes the k-th electron, leaving charge +k.
S_ion: Z_eff(k) = k ,   n = n_valence of that electron as frozen in corpus
E_pred(k) = Ry (μ/m_e) [Z_eff(k)]² / n(k)²
```

For the last electron, `k = Z`, `n = 1`, `Z_eff = Z` — identical to H-like ionisation.  
For He I (`k = 1`, `n = 1`), S_ion predicts `Ry` ≈ 13.6 eV vs NIST 24.59 eV.

No third screening fraction. No Slater σ. No inversion `Z_eff = n √(IE/Ry)`. If both S_bare and S_ion miss intermediate IEs, occupancy is **OPEN**. Do not invent S_frac after seeing the table.

---

## Frozen size / isotope rules (Phase 3 — one pass)

| ID | Rule |
|---|---|
| **I_mass** | `R_∞ (μ/m_e) Z² (1/n_f² − 1/n_i²)` with `μ = m_e m_nuc / (m_e + m_nuc)`, `m_nuc` from AME / `A m_p` as declared per row. |
| **I_size** | I_mass plus a field-shift proxy from **NP12** `R_A = nuclear_boundary_radius(A)`, not from a measured `⟨r²⟩` table. Proxy (declared): `δz / z = −2 δr_eff / r_n` is **not** used with a free `δr_eff`. The named proxy is sky-fraction of the nuclear boundary at the valence radius: `Θ = (1/4)(R_A / r_n)²`, `δΘ` between isotopes, `δν/ν = δΘ` (leading covering-fraction). |
| **I_grammar** | No extra free scale. Report whether APS07 landmarks sit on measured residual structure. Magnitude prediction of kHz King residuals is **not** a Phase-3 MATCH target (APS07 unpaid). |

`dnn` frozen. Measured `⟨r²⟩` may appear as an OBSERVED comparison column only. It is not an input to I_size.

---

## Hold-out corpora (frozen; not inputs to formulae)

### C-EXC — excitation (H-like)

Wavelengths are NIST ASD (vacuum), reduced-mass prediction as in `atomic::emission_wavelength_m`.

| Set | Transitions | Z |
|---|---|---|
| C-EXC-H | H I Lyman n=2..6→1; Balmer n=3..7→2; Paschen n=4..7→3 | 1 |
| C-EXC-He | He II n=2,3,4→1 | 2 |
| C-EXC-Z | H-like Lyα analogue n=2→1 | Z = 1..26 inclusive |
| C-EXC-deep | C VI, O VIII, Si XIV, Fe XXVI: n=2→1, n=3→1, n=3→2 | 6, 8, 14, 26 |

NIST numbers used at run time are copied into `aps12_holdouts.csv` with provenance **before** the first predicted column is computed. If a NIST line is missing, the row is `NO_DATA`, not a skip-to-improve.

### C-ION — ionisation

Source: `Datasets/nuclear/ionisation_energies.json` (NIST/CRC compilation; manifest in `Datasets/MANIFEST.md`).

| Set | Content |
|---|---|
| C-ION-last | Last IE (k = Z) for every Z in 2..30 that has a value in the json |
| C-ION-full | Full series k = 1..Z for Z ∈ {2, 4, 6, 8, 10, 12, 18, 20, 26} |
| C-ION-breach | Named core-breach steps: Be IE₃; Ne IE₉; Ar IE₈; Ca IE₃; Fe IE₉ (3p→3s / shell change as labelled in ATOMICUS `04_Ionisation_Series.md`) |

### C-ISO — isotopes

| Set | Species | Transitions / quantity |
|---|---|---|
| C-ISO-H | ¹H, ²H, ³H | Lyα; I_mass vs measured isotope shift |
| C-ISO-He | ³He⁺, ⁴He⁺ | n=2→1 |
| C-ISO-Ca | ⁴⁰Ca, ⁴²Ca, ⁴⁴Ca, ⁴⁶Ca, ⁴⁸Ca | APS07 King residuals and δ⟨r²⟩ as OBSERVED columns; grammar from `alpha_grammar` |
| C-ISO-Yb | ¹⁶⁸,¹⁷⁰,¹⁷²,¹⁷⁴,¹⁷⁶Yb | APS07 Counts/Hur tables; `n_t = n_d` at A=174 |

### C-MULTI — not H-like (Phase 4; scored only against S_bare / S_ion as applied to the *line energy*, not a new rule)

| ID | Line | OBSERVED |
|---|---|---|
| He I res | 1s² ¹S → 1s2p ¹P | 58.433 nm / 21.218 eV |
| Na D | 3s→3p | 588.995 nm / 2.105 eV |
| Fe XXV w | He-like 1s²–1s2p ¹P | 6.700 keV (laboratory / astrophysical standard; copy exact NIST/Chandra number into holdouts before predict) |
| Be I res | 2s² → 2s2p ¹P | 234.861 nm / 5.279 eV |

Phase 4 MATCH is **not** expected under S_ion for He I / Na D / Be I. The phase exists to *record* the miss and to forbid a rescue coefficient.

---

## Numeric gates (frozen)

| Gate | MATCH | Inconsistent |
|---|---|---|
| V0 instrument | H I 2→1: `emission_wavelength_m(1,1,2,m_p)` within **15 ppm** of NIST 121.5670 nm | >15 ppm (tool fault, not physics) |
| V0 identity | Printed `zk²` on H n=1..7 equals 1 within 1e-12 | tool fault |
| G_EXC | C-EXC-Z: max \|Δλ/λ\| ≤ **1000 ppm**; C-EXC-H max ≤ **15 ppm** | any row outside |
| G_EXC_Fe | Fe XXVI 2→1 ≤ **0.5%**; Law V remainder `mc²[(1−√(1−z₁))−(1−√(1−z₂))] − ½mc²Δz` logged, not used to retune | >0.5% |
| G_ION_last | C-ION-last Z=2..20: max rel ≤ **1.0%**; Z=21..30 ≤ **2.0%** | outside |
| G_ION_S | S_bare and S_ion both reported on C-ION-full. MATCH on intermediate k (k < Z) is rel < 0.10 on **≥ 80%** of those rows **for one named rule**. If neither rule hits 80%, occupancy **OPEN** (not a fail of the Δz ontology) | inventing a third rule after the table is EXCLUDED conduct |
| G_ISO_mass | C-ISO-H Lyα ¹H–²H isotope shift: I_mass rel vs measured shift ≤ **5%** of the shift | >5% |
| G_ISO_size | I_size sign of δΘ on Ca 40→42→44→46→48 vs sign of measured δ⟨r²⟩ step: count of sign agreements. MATCH = 4/4 or 5/5 steps (as many as have δ⟨r²⟩). Magnitude not gated | sign agreements ≤ 2 |
| G_GRAM | Landmark report only. No MATCH on kHz | claiming MATCH from a re-sort |
| G_MULTI | C-MULTI: report rel under S_bare and S_ion. No MATCH required. A MATCH claimed by a new coefficient is prohibited | — |

**NATIVE-distinct** requires at least one of: G_ION_S MATCH on a named rule; G_ISO_size MATCH; a Phase-4 line hit by a rule that was named in this file before the number was seen. G_EXC MATCH without those is CONVERGENCE of the spine.

---

## Prohibited inputs and moves

- G, M, GM as fundamentals; ψ; quarks; QED logs as SDT terms; Slater σ; `Z_eff = n√(IE/Ry)` as a predictor of IE or of λ.
- Restoring `lamb_shift_native_MHz = 1051.8`.
- Retuning `dnn`, `R_p`, or α.
- Scoring `zk² = 1`.
- APS07 bare re-sort of one element’s residuals by `n_t` as evidence.
- Reading prior `APS12_ASSESSMENT.md` or stdout to choose a screening rule.
- CALIBRATED budget: **0**.

---

## Instrument validation (before C-EXC / C-ION / C-ISO)

The tool must first reproduce, from `laws.hpp` only:

1. `koppa_hydrogen = α² a_0` equals `r_e` (relative 1e-12).
2. `z_1 = α²`, `E_1 = ½ m_e c² z_1` equals `Ry_eV` (relative 1e-9).
3. V0 wavelength gate.

Failure here is an instrument fault. Physics tables are not opened.