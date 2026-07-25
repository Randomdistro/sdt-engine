# Datasets — cache manifest

*Standing reference cache so investigations do not re-pull online. Pulled/collected during the 2026-07 nuclear+radius phase.*

**Rule:** every investigation that consumes a dataset cites it by the path below. Re-pull only to refresh; log the date here when you do.

| file | what it is | source | used by | sha256 (12) | bytes |
|---|---|---|---|---|---|
| `nuclear/AME2020_mass_excess.txt` | AME2020 atomic mass evaluation (mass excesses) | IAEA / AMDC — mass_1.mas20 | nuclear binding energies, mass defects | `e8599c6d7f72` | 472,648 |
| `nuclear/NUBASE2020.txt` | NUBASE2020 ground-state properties (spin, half-life, abundance, decay) | IAEA / AMDC — nubase_4.mas20 | stability, spin, magnetism, monoisotopy | `1585a5eea86c` | 761,906 |
| `nuclear/IAEA_ground_states_radii.csv` | IAEA live-chart ground states incl. measured boundary radii (Angeli-Marinova) | nds.iaea.org/relnsd/v1/data?fields=ground_states&nuclides=all | triton-contraction rule, shell compaction | `8aee5dc431af` | 900,613 |
| `nuclear/IAEA_U235_independent_FY.csv` | U-235(n_th,f) independent fission yields | nds.iaea.org relnsd independent_fy parents=235U | fission spectrum, anchor walk, nu=100-A(Zr) | `87fcd49503a5` | 121,193 |
| `nuclear/IAEA_U235_cumulative_FY.csv` | U-235(n_th,f) cumulative fission yields | nds.iaea.org relnsd cumulative_fy parents=235U | cumulative products, Tc-99 | `dd2c4ff493e4` | 120,337 |
| `nuclear/ionisation_energies.txt` | Elemental ionisation-energy ladders | Wikipedia/CRC compilation | I1 Moseley check, valence coupling | `5833cda96148` | 64,583 |
| `stellar/SPARC_meta.txt` | SPARC rotation-curve galaxy metadata | SPARC (Lelli+2016) | GD05/E46 galaxy rotation | `19b6f9ad1116` | 6,673 |
| `stellar/stellar_partial.csv` | partial stellar census (T_eff, L, R, type) | E109 DUNES koppa work | E109 solar prism, koppa table | `47f34beae8a7` | 8,623 |
| `solar_system/SDT_ephemeris.csv` | solar-system ephemeris | local 'SDT solar system' folder | orbital mechanics, koppa, resonance | `d0b0f69477df` | 286,583 |
| `solar_system/SDT_resonance_lattice.csv` | SDT resonance-lattice map | local 'SDT solar system' folder | resonance structure | `a86d29430647` | 2,223 |
| `solar_system/solar_system_mass_inventory.md` | solar-system mass inventory | local 'SDT solar system' folder | mass-free orbital checks | `b9fc37ff3c42` | 4,063 |
| `pressure/sibling_run_20250812_pressure.csv` | pressure-field run output | Spatial_displacement_theoriser/runs/run_20250812T074635Z | pressure-domain reference (provenance: sibling repo) | `fa8158aa0c9c` | 6,416 |
| `solar_system/JPL_SBDB_comets.json` | JPL SBDB comet orbital elements, 4069 comets (full_name, e, a, q, i) | NASA/JPL SBDB Query API (signature embedded in file) | E106 lumiopause tests (docket D05) | `67bd0c3dfd40` | 242,303 |
| `cosmology/PantheonPlusSH0ES.dat` | Pantheon+SH0ES SN Ia compilation (zHD, m_b_corr, MU_SH0ES, Cepheid calibrator flags) | Pantheon+ release (Scolnic 2022) + SH0ES (Riess 2022) | CR10-12 / E42 / E49 re-audit (docket D02), Hubble-tension work | `1cb0fc379ef0` | 579,283 |
| `stellar/SPARC_full_175.mrt` | full SPARC mass models MRT — 175 disk galaxies, Spitzer photometry + rotation curves | SPARC (Lelli, McGaugh & Schombert 2016) | GD05 / E46 re-audit (docket D01) | `9108994b12cc` | 269,518 |
| `nuclear/radii_compact.csv` | compact measured rms boundary-radius subset (z, n, symbol, radius, unc) | IAEA live chart (Angeli–Marinova) subset pull | quick radius checks | `7bb8c087189d` | 955 |
| `nuclear/U235_FY_ranked.txt` | ranked U-235 thermal fission products with grammar columns (n_d, n_t, yield%, cum%) | derived in-repo from the IAEA U-235 FY tables above | NP25 / NP26 fission work | `13f2556672e7` | 39,119 |
| `nuclear/nucdata_snapshot.js` | compact JS nuclear table (SYM/NUC arrays: Z, A, energy, spin, abundance) for HTML tools | derived snapshot of AME/NUBASE-class values | HTML viewers and tools | `529356382545` | 80,024 |
| `nuclear/NIST_ionisation_snapshot.txt` | raw HTML snapshot of a NIST ASD ionisation-energy page (UNPARSED — not clean data) | NIST ASD (web snapshot) | provenance backup for ionisation ladders | `a18139668194` | 3,262 |
| `nuclear/ionisation_energies.json` | parsed ionisation-energy ladders keyed by Z (eV) | parsed from NIST/CRC compilation | valence / ionisation tooling | `ff53c50eeeb3` | 6,784 |
| `nuclear/magnetic_moments_compact.txt` | raw HTML snapshot of a nuclear magnetic-moments reference page (UNPARSED — measured anchors only) | web reference snapshot | NP15 moment audits (OBSERVED anchors) | `217ded58b36c` | 1,954 |
| `nuclear/UVaNCD_SOG_data.dat` | Sum-of-Gaussians **movement-distribution** parameters (Z, A, rms, width, 12 R/Q pairs per nuclide) | UVa Nuclear Charge Density archive, `discovery.phys.virginia.edu/research/groups/ncd/dldata/` — De Vries, de Jager & de Vries 1987 (ADNDT 36, 495) | NP30 §12 radial-load test (F9) | `ac270d4f603b` | 3,585 |
| `nuclear/UVaNCD_SOG_normalized_columns.dat` | **pre-computed ρ_mv(r) profiles**, SOG, 17 nuclides incl. ¹⁶O/⁴⁰Ca/⁴⁸Ca/¹²⁴Sn/²⁰⁸Pb; r=0–10 fm at 0.01 fm. **Integrates to A** (0.997–0.999), i.e. movement density per nucleon count, NOT per Z | as above | NP30 §12 (the file the verdict was computed from) | `02186bfbc73e` | 272,054 |
| `nuclear/UVaNCD_FB_data.dat` | Fourier-Bessel movement-distribution coefficients | as above | NP30 §12 cross-check; ⁹⁰Zr available here (absent from SOG set) | `e977046004c9` | 18,306 |
| `nuclear/UVaNCD_FB_normalized_columns.dat` | pre-computed ρ_mv(r) profiles, Fourier-Bessel, ~90 nuclides incl. ⁹⁰Zr | as above | NP30 §12 cross-check / ladder completion | `781c672721f3` | 1,219,845 |
| `nuclear/fission_yields/IAEA_232Th_independent_FY.csv` | Th-232(n,f) **independent** yields (fast+14 MeV; no thermal — fast-only fissioner) | IAEA NDS relnsd `independent_fy parents=232TH` | NP32 scission cut, cross-fissioner test | `6641d35d4f2c` | 85,712 |
| `nuclear/fission_yields/IAEA_232Th_cumulative_FY.csv` | Th-232(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=232TH` | NP32 post-decay | `2d86d478f326` | 84,947 |
| `nuclear/fission_yields/IAEA_233U_independent_FY.csv` | U-233(n,f) independent yields (thorium-cycle fissile; thermal+fast+14 MeV) | IAEA relnsd `independent_fy parents=233U` | NP32 cross-fissioner test | `878e4e6c1f39` | 128,347 |
| `nuclear/fission_yields/IAEA_233U_cumulative_FY.csv` | U-233(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=233U` | NP32 post-decay | `08b4e458db1c` | 126,426 |
| `nuclear/fission_yields/IAEA_238U_independent_FY.csv` | U-238(n,f) independent yields (fast+14 MeV; no thermal) | IAEA relnsd `independent_fy parents=238U` | NP32 cross-fissioner test | `e602f666aeb3` | 90,478 |
| `nuclear/fission_yields/IAEA_238U_cumulative_FY.csv` | U-238(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=238U` | NP32 post-decay | `ad78c4e488b4` | 90,142 |
| `nuclear/fission_yields/IAEA_237Np_independent_FY.csv` | Np-237(n,f) independent yields (thermal+fast) | IAEA relnsd `independent_fy parents=237NP` | NP32 minor-actinide test | `a14c5e3540fe` | 88,035 |
| `nuclear/fission_yields/IAEA_237Np_cumulative_FY.csv` | Np-237(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=237NP` | NP32 post-decay | `7015089edca3` | 86,940 |
| `nuclear/fission_yields/IAEA_239Pu_independent_FY.csv` | Pu-239(n,f) independent yields (MOX/breeder/weapon; thermal+fast) | IAEA relnsd `independent_fy parents=239PU` | NP32 cross-fissioner test (key out-of-sample) | `8e9272960f54` | 98,073 |
| `nuclear/fission_yields/IAEA_239Pu_cumulative_FY.csv` | Pu-239(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=239PU` | NP32 post-decay | `c81261918347` | 97,507 |
| `nuclear/fission_yields/IAEA_241Pu_independent_FY.csv` | Pu-241(n,f) independent yields (thermal+fast) | IAEA relnsd `independent_fy parents=241PU` | NP32 cross-fissioner test | `52bbb5be8087` | 93,869 |
| `nuclear/fission_yields/IAEA_241Pu_cumulative_FY.csv` | Pu-241(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=241PU` | NP32 post-decay | `6824eda417a5` | 92,783 |
| `nuclear/fission_yields/IAEA_241Am_independent_FY.csv` | Am-241(n,f) independent yields (minor actinide; thermal+fast) | IAEA relnsd `independent_fy parents=241AM` | NP32 minor-actinide test | `a75a4ecd5109` | 100,715 |
| `nuclear/fission_yields/IAEA_241Am_cumulative_FY.csv` | Am-241(n,f) cumulative yields | IAEA relnsd `cumulative_fy parents=241AM` | NP32 post-decay | `f4c7c23400d5` | 99,413 |

## External cache (large files, outside OneDrive)

Files **>100 MB** live in `C:\sdt-data\` — outside OneDrive sync (stale-file hazard, APS03 precedent) and **never committed**. Investigations cite the absolute path; sha256 discipline identical to above.

| path | what it is | source | used by | sha256 (12) | bytes |
|---|---|---|---|---|---|
| `C:\sdt-data\eb_wide_binaries.fits.gz` | Gaia wide-binary catalog (El-Badry et al.) | Zenodo (see `C:\tmp\zenodo_eb.json` metadata) | E108 / wide-binary gravity floor tests | `d49025e25fa0` | 882,786,816 |

## Provenance notes
- **IAEA live-chart** pulls used `nds.iaea.org/relnsd/v1/data` (single-nuclide queries; `nuclides=all` for the full ground-state chart). Boundary radii are the measured rms values (Angeli & Marinova 2013 via the live chart).
- **AME2020 / NUBASE2020** are the canonical mass/ground-state evaluations (AMDC).
- **Boundary radius** = proton displacement boundary, NOT 'charge radius' (no charge substance).
- The **sibling repo** `Spatial_displacement_theoriser` is a code framework, not a data trove — its only run-output data (`pressure.csv`) is cached here; the stellar/solar data lived in the separate local 'SDT solar system' folder and in this repo's own `Hubble/data/` and `Experiments/E109_.../data/`.
- Not re-copied (already in-repo): `Hubble/data/`, `Experiments/E109_Solar_Spectral_Prism/data/` (dunes_koppa_table), `ATOMICUS/tools/_iaea_ground_states.csv` (same IAEA pull, kept beside the enrichment tool).
- **2026-07-23 migration** (dual-front campaign prep): `cosmology/`, `stellar/SPARC_full_175.mrt`, six `nuclear/` extras, and the external-cache Gaia wide-binary file were migrated from the `C:\tmp` working cache. `C:\tmp` originals retained until Harvey OKs deletion. The 842 MB external file was verified by full-64-char sha256 source-vs-destination match. Regenerable caches (`.pkl`/`.npy`) deliberately not migrated.
- Outstanding wanted data lives in `Datasets/MUST_FETCH_2026-07-23.md` — check it before assuming a dataset is unavailable.
