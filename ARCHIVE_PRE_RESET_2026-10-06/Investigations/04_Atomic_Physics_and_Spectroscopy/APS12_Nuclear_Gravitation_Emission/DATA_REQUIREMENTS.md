# APS12 — Data requirements

**Investigation:** Nuclear gravitation and emission (Δz).  
**Hold-outs are frozen in** `APS12_PRE_REGISTRATION.md`. This file is provenance and paths only.  
**No SDT analysis lives here.**

## Already in the repository (use these; do not silently replace)

| Path | Role | Provenance |
|---|---|---|
| `Datasets/nuclear/ionisation_energies.json` | C-ION series (eV, keyed by Z) | NIST/CRC compilation; `Datasets/MANIFEST.md` sha256 `ff53c50eeeb3` |
| `Datasets/nuclear/ionisation_energies.txt` | Human-readable companion | same compilation |
| `Investigations/04_Atomic_Physics_and_Spectroscopy/APS07_King_Plot_Nuclear_Gear/DATA_COLLECTION.md` | C-ISO-Ca, C-ISO-Yb measured shifts, δ⟨r²⟩, King residuals | Counts 2020, Hur 2022, Door 2025, PTB/MPIK Ca 2025 — as tabulated there |
| `Investigations/04_Atomic_Physics_and_Spectroscopy/APS01_Emissions/aps01_emissions_rerun_2026-07-23.txt` | Instrument-check wavelengths (H, He II, Lyα Z-ladder) | APS01 direct run; NIST numbers quoted there are **comparison**, not a second SoT |
| `Engine/include/sdt/laws.hpp` | α, a_0, r_e, R_p, Ry, m_e, m_p, c, h, `emission_wavelength_m`, `bohr_radius`, `c_boundary_nuclear`, `nuclear_boundary_radius` | SoT |
| `Engine/include/sdt/nuclear.hpp` | `alpha_grammar(Z,A)`, EC grammar | SoT |

## Must be copied into the run hold-out file before any prediction column

Create `aps12_holdouts.csv` at the start of the run (Phase 0). Every OBSERVED energy or wavelength used later must already have a row: `corpus_id, species, Z, A, ion_stage, transition, quantity, value, unit, source, citation`.

NIST ASD queries (if a number is not already in APS01 stdout or the json):

- H I, D I, T I Lyα (vacuum).
- He II, ³He II n=2→1.
- H-like Lyα Z=1–26; C VI / O VIII / Si XIV / Fe XXVI n=2→1, 3→1, 3→2.
- He I 1s²–1s2p ¹P; Be I 2s²–2s2p ¹P; Na I 3s–3p; Fe XXV 1s²–1s2p ¹P (w).

If a query cannot be completed, the row is `NO_DATA`. Do not substitute a calculated “NIST-like” value.

## Masses (I_mass)

AME2020 (already used in NP21). Per nuclide `m_nuc` in kg. Hydrogen isotopes: CODATA `m_p`, deuteron and triton masses from `sdt::laws::measured` if present, else AME. State the source on every C-ISO row.

## Not inputs

- Measured nuclear `⟨r²⟩` (Angeli & Marinova, muonic) — OBSERVED comparison only, not I_size input.
- QED tabulated “field shift factors” F_i, K_i — comparison columns in the King appendix, not SDT inputs.
- Slater screening constants.
- SPARC, ΛCDM, or any gravitational-G conversion of atomic energies.