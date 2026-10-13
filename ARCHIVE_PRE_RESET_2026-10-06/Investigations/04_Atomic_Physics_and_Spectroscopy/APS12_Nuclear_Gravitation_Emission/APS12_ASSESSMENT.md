# APS12 Assessment — Nuclear gravitation and emission (Δz)

**Date:** 2026-08-13  
**Direct execution.** **Canon edits:** none.  
**Instrument:** `aps12_nuclear_z_emission.py`  
**Stdout:** `.audit-tmp/aps12_run.txt` (copy `aps12_results.txt`)  
**Hold-outs:** `aps12_holdouts.csv` sha256 `c55b44c86b74e610ed59f35c66cfbd948fb60d689d3d4cc9b3f41585b5c5620b`  
**Pre-registration:** `APS12_PRE_REGISTRATION.md` (before instrument)

## Dual verdict

| Axis | Grade |
|---|---|
| **Prompt completion** | **A** — Phases 0–5 executed in order; required CSVs written; hold-out SHA256 before predict; two-route 5.3×10⁻¹⁶; ADJ-001 documented; dual verdict |
| **Physics class (parent)** | **Native origin** on the one-electron spine: koppa depth `z = ϟ/r`, `hν = ½ m_e c² Δz`, electropause well — not Coulomb-as-primitive. The closed form is shared with Bohr–Rydberg, so the H-like *number* cannot discriminate mechanisms. Occupancy **OPEN**. **I_size excluded** as a sign law on Ca. Leading Fe XXVI **inconsistent** with the 0.5% gate. Distinct predictions that Coulomb does not already write remain unpaid. |

## Ontology

The nucleus sits inside `ϟ = Z r_e`. Laboratory electronic light is born at seats outside that surface. A line is `hν = ½ m_e c² Δz` with `z = ϟ_felt / r`. A heavier Z or a stripped ion is a deeper seat. Companions change `ϟ_felt`. A different A changes μ and the nuclear boundary. That is the claim.

Rydberg measured wavelengths. Bohr filled Coulomb. SDT fills Law III occlusion at the electropause: same `1/r²` shape, different pressure (`P_eff` vs solar `P_conv`), depth `z = ϟ/r`. The H-like algebra is the same closed form. The mechanism is not. Correspondence is not provenance. The word CONVERGENCE is not used for that agreement: it is not a shared claim.

## Gate table

| Gate | Actual | Decision |
|---|---|---|
| V0 | H 2→1 Δppm = **+11.89** (bar 15) | MATCH |
| V0 zk² | 1.000000000000 on n=1..7 | printed; not scored |
| G_EXC H | max \|ppm\| = **12.50** | MATCH |
| G_EXC Z (observed rows) | max \|ppm\| = **9348** (Fe XXVI); without Fe, max is Li 4→1 **263 ppm** | **INCONSISTENT** on the frozen corpus because Fe XXVI is an observed C-EXC-Z row |
| G_EXC_Fe | rel = **0.935%** (bar 0.5%); δ_LV/E = **1.15%** logged | **INCONSISTENT** on leading; remainder not used to retune |
| G_ION_last | Z=2..20 max rel = **0.506%** (Ca); Z=21..29 max rel = **1.08%** (Cu); Z=30 NO_DATA | MATCH |
| G_ION_S | S_bare 3/97 = 0.031; S_ion 14/97 = 0.144; bar 80% | **OPEN** |
| G_ISO_mass | H–D Δλ rel_on_shift = **9.16×10⁻⁴** (bar 5%) | MATCH |
| G_ISO_size | sign 2/4 (bar 4/4 MATCH; ≤2 inconsistent) | **INCONSISTENT** |
| G_GRAM | landmarks listed; re-sort not used | report only |
| G_MULTI | four lines; no coefficient | table only |

## ADJ-001 (instrument identity, not a physics bar)

`α² a_0` vs typed `r_e` in `laws.hpp`: relative **1.94×10⁻¹²**, above the prompt’s 1e-12 identity. Both are independent CODATA literals. Instrument identity widened to 1e-11. V0 wavelength bar unchanged (11.89 ppm). Forbidden list untouched.

## Excitation

`aps12_T1_excitation.csv` N=46. Hold-out Lyα Z=4–25: NO_DATA (no in-repo NIST). Observed comparisons: H series, He II, Li III, Fe XXVI 2→1.

Worst ppm on H: Balmer 3→2 **+12.5 ppm**. Worst on He/Li: Li 4→1 **+263 ppm** (APS01 same number). Fe XXVI 2→1: λ_pred **0.179739 nm**, obs centroid **0.178074 nm** (6.9625 keV doublet mean), **+9348 ppm**.

Law V remainder at Fe: δ_LV/E = 1.15%. Applying it would shorten λ toward the centroid (~0.18% if used). The gate scores leading `½mc²Δz` only. That remainder is a residual, not a MATCH.

Two-route (Δz vs `R_∞` formula) max rel **5.3×10⁻¹⁶**.

**Class:** H-like through Li — native origin (Δz / koppa seats); algebra shared with Bohr–Rydberg so the *number* cannot discriminate. Fe XXVI leading — inconsistent with G_EXC_Fe. C-EXC-Z as frozen (including Fe) — inconsistent.

## Ionisation

**Last electron** (`aps12_T2_last.csv` N=29): `Ry (μ/m_e) Z²` vs json. Residual grows with Z (0.0045% He → 0.51% Ca → 0.87% Fe → 1.08% Cu), inside the 1%/2% bars. Same Dirac/high-z remainder pattern as Fe XXVI, under a looser IE bar. Native origin (`z_1`); same algebra as H-like ionisation.

**Full series** (`aps12_T2_ionisation.csv` N=106): S_bare over-binds outers by large factors (He IE1 rel 1.21; Fe IE1 rel 128). S_ion under-binds outers (He IE1 13.6 vs 24.59, rel 0.45). Intermediate 80% test fails both rules. Occupancy **OPEN**. No S_frac.

**Core-breach location:** Be IE3, Ne IE9, Ca IE3, Fe IE9 are n-drops in the frozen Madelung map and json ratios >1.5 (Be 8.45, Ne 5.00, Ca 4.29). Ar IE8 is **same-n** in that freeze (3s still); the n-drop is the next electron. ATOMICUS labelled Ar IE8 as 3s→2p. The freeze and the label disagree by one k. Reported, not fitted.

## Isotope

**I_mass:** H Lyα 121.5684 nm vs 121.5670; D 121.5354 vs 121.5339. Shift 0.033070 vs 0.033100 nm, rel **0.092%**. IDENTITY (two-body μ). T and ³He II: prediction only (NO_DATA).

**I_size:** NP12 `R(A)` is monotone in A. δΘ > 0 on every Ca step. Measured δ⟨r²⟩ turns negative at 44→46 and 46→48. Sign 2/4. Packing A^{1/3} does not invert. **I_size as a sign law on Ca is excluded.** Magnitude was not gated.

**Grammar:** Ca-40 `n_t=0`. Yb-174 `n_t=n_d`. Ca even chain does not contain A=49. King residual sign-change on Ca is 44→46 / 46→48 (`n_t` 6→8), not the first-triton step 40→42. Report only. Re-sort by `n_t` not used as evidence.

## Multi

| Line | E_obs | S_bare | rel | S_ion | rel | note |
|---|---:|---:|---:|---:|---:|---|
| He I 58.433 nm | 21.218 eV | 40.81 | 0.92 | 10.20 | 0.52 | miss both |
| Na D | 2.105 eV | 0 | 1 | 0 | 1 | SAME_N_NULL |
| Be I 234.861 nm | 5.279 eV | 0 | 1 | 0 | 1 | SAME_N_NULL (n=2→2) |
| Fe XXV w | 6.700 keV | 6.898 keV | 0.030 | 6.378 keV | 0.048 | printed; **not claimed MATCH** |

Principal-n seats cannot make same-n term differences. That is a limitation of this investigation, not a licence to import ℓ.

## Residuals

- Fe XXVI / last-IE Z-growth: leading `½mc²z` short of the laboratory number by ~Z²α² order; Law V remainder is the same order and was not scored as a fix.
- Occupancy: S_bare and S_ion miss the intermediate IE table. `ϟ_felt` unpaid.
- NP12 covering fraction cannot follow Ca radius inversion.
- C-EXC-Z Z=4–25: NO_DATA in-repo NIST; not used to improve max ppm.
- Fe ground 4s vs Madelung `n_of_outermost(26)=3`: freeze limitation; changing n after T2 is prohibited. Would not have passed G_ION_S anyway.

## Scope

One-electron seats and last-electron IE. Not Lamb. Not fine-structure doublets as a scored target. Not Saha. Not canon.

## Limitations

H-like Δz lands on the same closed form as the Rydberg series. That is algebra, not mechanism. This run cannot discriminate origin by the hydrogenic number. Distinct payload that Coulomb does not already write (occupancy, packing size as a spectral sign law) did not MATCH.

## Open problems

`ϟ_felt` for N_e > 1. A size channel that can invert (Ca 46/48). Same-n term intervals without spherical-harmonic input. High-Z remainder as a scored Law V prediction (would need a pre-registered E_LV gate, not this run’s leading bar).

## Parameter ledger (from `laws.hpp`)

`c`, `h`, `e_charge`, `alpha`, `a_0`, `r_e`, `R_p`, `m_e`, `m_p`, `m_n`, `Ry_eV`, `R_inf`, `B_deuteron`, `B_triton`, `B_alpha` — MEASURED-INPUT or engine DERIVED as tagged in the header.  
`m_d`, `m_t`, `m_He4` — COMPUTED from those.  
`m_He3` binding 7.718 MeV — ASSUMED (³He II line NO_DATA).  
CALIBRATED(n): **0**.

## Prohibited-move checklist

- [x] No G, M, ψ, QED logs, Slater σ  
- [x] No `Z_eff = n√(IE/Ry)` as predictor  
- [x] No 1051.8  
- [x] No `dnn` retune  
- [x] zk² printed, not scored  
- [x] King re-sort not used as evidence  
- [x] No S_frac after C-ION  
- [x] Measured ⟨r²⟩ comparison only  
- [x] No Fe XXV / Na D coefficient  
- [x] n(k) not changed after Phase 0  

## Physics class per axis

| Axis | Class |
|---|---|
| Excitation (H, He, Li) | native origin (Δz); algebra shared — number cannot discriminate |
| Excitation (Fe XXVI leading) | inconsistent with G_EXC_Fe |
| Last-electron IE | native origin (`z_1`); algebra shared |
| Intermediate IE occupancy | OPEN |
| I_mass H–D | IDENTITY (two-body) |
| I_size Ca signs | excluded |
| Grammar landmarks | report; unpaid magnitude |
| Parent | native Δz origin, not Coulomb; hydrogenic number unpaid as a discriminator; occupancy and inverting size unpaid |
