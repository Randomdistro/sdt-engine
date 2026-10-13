# APS12a Pre-registration — Independent nuclear-koppa emission test

**Date:** 2026-08-13  
**Author:** direct independent execution  
**Status:** PRE-REGISTERED BEFORE APS12a INSTRUMENT  
**Isolation:** No file under `APS12_Nuclear_Gravitation_Emission/` may be read,
imported, copied, or written by APS12a.

## Question

Test whether the leading seat-depth relation

`E = (1/2) m_e c^2 (z_lower - z_upper)`, with
`z_n = (Z alpha / n)^2`,

survives three progressively distinct comparisons:

1. hydrogenic excitation and last-electron ionisation;
2. multi-electron occupancy under two frozen rules;
3. isotope mass and NP12 nuclear-size signs.

Hydrogenic alignment is CONVERGENCE because it is algebraically the Rydberg
closed form. A NATIVE-distinct result requires a frozen occupancy or NP12-size
rule to pass.

## Legal inputs

- `Engine/include/sdt/laws.hpp`
- `Engine/include/sdt/nuclear.hpp`
- `Datasets/nuclear/ionisation_energies.json`
- APS01 measured comparison values
- APS07 measured Ca/Yb isotope columns

No APS12/Grok-generated script, CSV, stdout, run log, assessment, hold-out, or
derived value is a legal input.

## Frozen rules

- `S_bare`: `Z_eff = Z`
- `S_ion`: for ionisation step `k`, `Z_eff = k`
- Principal `n`: ground-configuration outermost principal shell before the
  removal; frozen in the hold-out ledger.
- `I_mass`: reduced mass only.
- `I_size`: `Theta = (1/4)(R_A/r_n)^2`, with
  `R_A = R_p (A/(pi/sqrt(18)))^(1/3)`.
- `I_grammar`: report `n_d = 3Z-A-2`, `n_t = A-2Z`; no fitted magnitude and no
  count re-sort as evidence.

No third screening rule. CALIBRATED budget: 0.

## Corpora

- Excitation: H I Lyman/Balmer/Paschen rows in APS01; He II and Li III rows in
  APS01; Fe XXVI Ly-alpha centroid as a separately sourced high-Z check.
- Ionisation: last available `IE_Z`, Z=2..30; complete series for
  Z={2,4,6,8,10,12,18,20,26}.
- Isotope: H-D Ly-alpha mass shift; Ca-40,42,44,46,48 size-step signs; Ca/Yb
  grammar landmarks.
- Multi-electron: He I 58.433 nm, Be I 234.861 nm, Na I 588.995 nm, Fe XXV
  6.700 keV.

Unavailable observed values remain `NO_DATA`.

## Frozen gates

| Gate | Criterion |
|---|---|
| V0 constants | copied canonical decimal identities agree within `1e-10` |
| V0 wavelength | H I 2->1 within 15 ppm |
| two-route | explicit Delta-z and Rydberg routes agree within `1e-9` |
| G_EXC_H | maximum absolute residual <=15 ppm |
| G_EXC_light | observed He II/Li III rows <=1000 ppm |
| G_EXC_Fe | leading Fe XXVI Ly-alpha energy within 0.5%; Law-V remainder only logged |
| G_ION_last | max relative error <=1% for Z<=20 and <=2% for 21<=Z<=30 |
| G_ION_S | one frozen rule has relative error <10% on >=80% of intermediate rows |
| G_ISO_mass | H-D predicted isotope shift within 5% of observed shift |
| G_ISO_size | Ca sequential sign agreement 4/4 |
| G_MULTI | table completion only; no fitted coefficient |

If V0 fails, stop. A failed physics gate remains failed. No threshold amendment
is permitted in this run.

## Classification

- **NATIVE-distinct:** excitation spine passes and either G_ION_S or
  G_ISO_size passes.
- **CONVERGENCE:** one-electron spine passes while occupancy and size do not.
- **EXCLUDED:** the applicable excitation spine fails.
- **OPEN:** data are insufficient or a distinct rule misses without excluding
  the one-electron spine.

## Required outputs

- `APS12a_RUN_LOG.md`
- `aps12a_holdouts.csv`
- `aps12a_independent.py`
- `aps12a_results.txt`
- `aps12a_excitation.csv`
- `aps12a_ionisation_last.csv`
- `aps12a_ionisation_full.csv`
- `aps12a_isotope.csv`
- `aps12a_multi.csv`
- `APS12a_ASSESSMENT.md`
