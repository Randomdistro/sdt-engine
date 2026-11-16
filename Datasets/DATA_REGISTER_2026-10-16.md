# Data register — retrieval and verification, 2026-10-16

Scope: the data required to settle, or to specify, every item left open by `Investigations/EXTERNAL_AUDIT_2026-10-16_ASSESSMENT.md`. Retrieval ran in the main session by direct HTTP GET and local text extraction; no agent output is cited. Files, hashes and queries: `Datasets/external_audit_2026-10-16/MANIFEST.md`. Arithmetic and instrument checks: `Datasets/external_audit_2026-10-16/VERIFICATION_LOG.txt` (V1–V16). Nothing here changes `laws.hpp`, a benchmark, or an SDT claim; every value below is OBSERVED (published measurement or reconstruction) or COMPUTED (stated diagnostic), never DERIVED.

Status vocabulary: **PRIMARY** = read from the originating paper or data centre · **SECONDARY** = read from a compilation or review · **COMPUTED** = recomputed here from retrieved inputs · **IN-REPO** = already cached under `Datasets/` · **NOT RETRIEVED** = obstacle stated.

---

## 1. Requirements matrix

| id | open item | data required | status | where |
|---|---|---|---|---|
| R1 | Flyby anomaly (audit item 5; E21; GOM43) | per-flyby V∞, declinations, inclination, altitude; measured ΔV∞ and error; DSN/ESTRACK coverage and gap times; as-flown Doppler and range residuals; constants entering K | geometry **PRIMARY** (6 flybys) + **COMPUTED** from JPL Horizons (9 flybys); ΔV∞ **PRIMARY** (6) + **SECONDARY** (null cases) + **PRIMARY 2026** (Rosetta I re-analysis); gap times **PRIMARY** for NEAR, Galileo I, Rosetta I, qualitative for Juno; residual time series **NOT RETRIEVED** (restricted, §12) | §2, `flyby_*.csv` |
| R2 | Mercury c-route (GOM04/B27) | observed excess perihelion advance with uncertainty; statement of how the ephemeris models GR; Mercury elements | **PRIMARY** (Pitjeva & Pitjev 2013 Table 4; Genova et al. 2018; Iorio 2018) + **IN-REPO** elements | §3 |
| R3 | Hydrogen B01 | CODATA R∞, m_p/m_e; H I Balmer vacuum wavelengths; air→vacuum relation | **PRIMARY** (CODATA 2022 listing; NIST ASD Ritz) | §4 |
| R4 | α-cluster bond screening | binding energies of ⁴He…⁴⁰Ca; cluster bond topology | energies **IN-REPO** (AME2020), tabulated here; bond topology **NOT RETRIEVED** (not a measurement; assumed in the audit test) | §5 |
| R5 | Galactic crossover | SPARC mass models; acceleration scale g† | **IN-REPO** (175-galaxy MRT); g† **PRIMARY** (McGaugh & Lelli 2016) | §6 |
| R6 | Polytope / kissing claims | kissing-number bounds D = 1…8; 600-cell and 120-cell element counts | **SECONDARY** (Wikipedia wikitext citing Musin, Conway–Sloane, Cohn tables) | §7 |
| R7 | Jupiter/Io check | GM_J, radii, Io a, e, P | **IN-REPO** (JPL SSD, NASA fact sheet; re-fetched, identical sizes) | §8 |
| R8 | Engine `measured` provenance | CODATA 2022 values for every constant in `measured::` | **PRIMARY**, compared in `engine_measured_vs_CODATA2022.csv` | §9 |
| R9 | APS02 slot weight 8/3 | λ_meas, IE₁ tables | **IN-REPO** (`nuclear/ionisation_energies.*`); the 8/3 premise is not a data item | — |
| R10 | E105 sungrazer kick (F1–F3) | SOHO/LASCO Kreutz astrometry; original 1/a for long-period comets | **NOT RETRIEVED** this session (not attempted) | §12 |

---

## 2. Flyby data (R1)

### 2.1 Constants entering Anderson's K
| quantity | value | source |
|---|---|---|
| Earth rotation rate ω | 7.292115×10⁻⁵ rad/s | Anderson et al. 2008, Eq. (3) (their ref. [9]) |
| Earth radius used in K | **6371 km (mean)** | Anderson et al. 2008, Eq. (3) |
| speed of light | 299 792 458 m/s | SI exact |
| K = 2ωR/c | **3.0993×10⁻⁶** (printed 3.099×10⁻⁶) | COMPUTED, V1 |
| Earth GM used by the PRL | 398 600.4 km³/s² | Anderson et al. 2008 text under Eq. (1) |
| Earth equatorial radius | 6378.1366 ± 0.0001 km; mean 6371.0084 km | JPL SSD (IN-REPO `solar_system/jpl_ssd_planet_phys_par.html`) |

An equatorial-radius K (v_rot = ωR_eq = 465.10 m/s ⇒ 3.1028×10⁻⁶) differs from the PRL value by +0.12 %.

### 2.2 Primary table — Anderson et al., PRL 100, 091102 (2008), Table I
Transcribed from the PDF text layer (minus signs render as the glyph `/.0255`); validated by V2 (Eq. (1) row reproduced to ≤ 0.005 mm/s for all six). Machine-readable: `flyby_primary_Anderson2008_TableI.csv`.

| | Galileo I | Galileo II | NEAR | Cassini | Rosetta I | MESSENGER |
|---|---|---|---|---|---|---|
| date | 1990-12-08 | 1992-12-08 | 1998-01-23 | 1999-08-18 | 2005-03-04 | 2005-08-02 |
| H (km, geoid) | 960 | 303 | 539 | 1175 | 1956 | 2347 |
| V_f (km/s) | 13.740 | 14.080 | 12.739 | 19.026 | 10.517 | 10.389 |
| **V∞ (km/s)** | 8.949 | 8.877 | 6.851 | 16.010 | 3.863 | 4.056 |
| deflection (°) | 47.7 | 51.1 | 66.9 | 19.7 | 99.3 | 94.7 |
| inclination I (°) | 142.9 | 138.7 | 108.0 | 25.4 | 144.9 | 133.1 |
| α_i, α_o (°) | 266.76, 219.97 | 219.35, 174.35 | 261.17, 183.49 | 334.31, 352.54 | 346.12, 246.51 | 292.61, 227.17 |
| **δ_i, δ_o (°)** | −12.52, −34.15 | −34.26, −4.87 | −20.76, −71.96 | −12.92, −4.99 | −2.81, −34.29 | +31.44, −31.92 |
| mass (kg) | 2497 | 2497 | 730 | 4612 | 2895 | 1086 |
| **measured ΔV∞ (mm/s)** | 3.92 | −4.6 (raw −8; drag 3.4 removed) | 13.46 | −2 | 1.80 | 0.02 |
| realistic error (mm/s) | 0.08 | 1.0 | 0.13 | 1 | 0.03 | 0.01 |
| Eq. (1) prediction (mm/s) | 4.12 | −4.67 | 13.28 | −1.07 | 2.07 | 0.06 |

Error-row digits for Galileo I and NEAR are corrupted in the PDF text layer (`0.3`, `0.01`); 0.08 and 0.13 are restored from three secondary transcriptions (Turyshev & Toth 2009 Table 1; ASTG II Table II, arXiv:0803.1370; the repo's `earth-flyby-observed-comparison.json`). Image-level confirmation of the PDF page is outstanding. The Galileo II raw value is −8 mm/s; the PRL subtracts an estimated atmospheric-drag term of −3.4 mm/s to give −4.6.

### 2.3 Geometry computed from JPL Horizons (nine flybys) — instrument validated on the six above
Horizons geocentric ICRF state vectors (10-min cadence, ±~30 h of closest approach) were converted to osculating hyperbolic asymptotes at ±12 h (`flyby_horizons_asymptotes.csv`; raw responses in `raw/horizons/`). Validation against PRL Table I: V∞ within 0.003 km/s; inclination within 0.05° except Galileo II (0.45° at ±12 h, 0.08° at ±6 h; the 303 km pass is strongly perturbed, osculating r_p − 6378.137 = 379.0 km at ±12 h and 303.0 km at ±6 h); declinations within 0.22° for Galileo I/II, NEAR, Cassini and within 0.9° for Rosetta I and MESSENGER (later trajectory reconstructions). Eq. (1) evaluated on the Horizons geometry reproduces the PRL column to ≤ 0.04 mm/s for the first four.

| flyby | V∞ in/out (km/s) | I (°) | δ_in (°) | δ_out (°) | osculating r_p − 6378.137 (km) | Eq. (1) (mm/s) |
|---|---|---|---|---|---|---|
| Galileo I | 8.9481 / 8.9477 | 142.94 | −12.48 | −34.17 | 946.0 | 4.13 |
| Galileo II | 8.8793 / 8.8769 | 139.15 | −34.27 | −4.82 | 379.0 | −4.68 |
| NEAR | 6.8510 / 6.8493 | 107.99 | −20.57 | −71.98 | 533.6 | 13.31 |
| Cassini | 16.0125 / 16.0132 | 25.41 | −12.92 | −4.99 | 1189.1 | −1.07 |
| Rosetta I | 3.8612 / 3.8622 | 144.93 | −1.94 | −34.07 | 1945.6 | 2.05 |
| MESSENGER | 4.0579 / 4.0581 | 133.12 | +32.24 | −32.74 | 2327.7 | 0.06 |
| **Rosetta II** | 9.3640 / 9.3627 | 115.10 | **−10.80** | **+18.59** | 5316.5 | **+1.00** |
| **Rosetta III** | 9.3787 / 9.3771 | 155.56 | **+18.47** | **+24.36** | 2482.9 | **+1.09** |
| **Juno** | 10.3887 / 10.3897 | 47.28 | **+14.17** | **+39.48** | 513.5 | **+6.37** |

Published predictions that these reproduce independently: Rosetta II "less than 1 mm/s" (Anderson 2008 abstract); Rosetta III "up to about 1 mm/s" (ASTG II text); Juno "about +6.0 mm/s" (Busack 2013, using pre-encounter V∞ = 9.91 km/s, giving 6.04). Osculating altitudes differ from published closest-approach altitudes by 5–46 km (perturbations, geoid); use PRL/ESOC altitudes for H.

### 2.4 Late and null flybys; contemporary census
Source for the census: Hoffmann & Budnik (ESA/ESOC), 30th ISSFD, Toulouse, 1–5 June 2026, arXiv:2609.23482, Table 1 (`flyby_census_Hoffmann2026_Table1.csv`).

| flyby | ΔV∞ (mm/s) | note |
|---|---|---|
| Galileo I / II, NEAR | 3.92 / −4.60 / 13.46 | Anderson 2008 |
| Cassini | −0.50 (this table) vs −2 ± 1 (PRL) | statistical re-analysis value; two values in the literature |
| Rosetta I | 1.82 | perigee increment 0.67 ± 0.02 |
| MESSENGER | 0.02 | |
| Rosetta II (alt. 5295 km), Rosetta III (alt. 2480 km) | 0 | ESOC internal investigation |
| EPOXI I–III | 0 | distant (> 15 000 km) |
| Juno | ~0 (0 ± 0.8 per compilation) | AAS 14-435 |
| BepiColombo, Solar Orbiter | 0 | |
| **JUICE I (LEGA, 2024-08-20)** | **0.6 (perigee 0.10)** | first small measured prograde increase since 2005 |
| Stardust, OSIRIS-REx, Lucy I/II | ? | no published value in the census |

ESOC 2026 result for Rosetta I: anomaly reproduced with ESOC's new deep-space orbit-determination system and the original tracking data (perigee ΔV = 0.655 ± 0.015 mm/s, 1σ formal; 0.692 ± 0.059 mm/s with perigee time freed); ephemeris, gravity-field, relativistic and propagator explanations ruled out; candidate cause is Earth-albedo-triggered outgassing, tested against attitude data. Status of the candidate: proposed by the authors, not independently confirmed.

### 2.5 Tracking coverage (`flyby_tracking_coverage.csv`)
| flyby | statement | times relative to closest approach | source |
|---|---|---|---|
| NEAR | DSN two-way lost (Goldstone BWG last), resumed with Canberra BWG | −1 h 08 m → +2 h 31 m (gap 3 h 39 m) | Antreasian & Guinn 1998; Anderson 2008 |
| NEAR | SSN Millstone 06:12:22–06:44:27 UTC, Altair 06:14:28–06:51:05 UTC | Altair ends 32 min before CA | Antreasian & Guinn 1998 |
| Galileo I | Madrid two-way ends; antenna switch at −19 min; one-way (USO) Doppler through CA; Goldstone two-way resumes at low elevation (5.8°–12.7°) | −55 min → +14 min | Antreasian & Guinn 1998 |
| Galileo II | TDRSS special tracking; ionospheric signature on TDRSS signal; drag at 303 km | — | Antreasian & Guinn 1998 |
| Rosetta I | gap between two ground passes, 19:20–22:44 UTC (perigee 22:09:14) | −2 h 49 m → +0 h 35 m | Hoffmann & Budnik 2026 |
| Juno | predicted gap −60 to +120 min without extra stations; as flown, DSN + two ESA stations, near-continuous | — | Busack 2013; NTRS 20160008163 |
| Cassini, MESSENGER, Rosetta II/III, JUICE | coverage **NOT RETRIEVED** | — | §12 |

Gap radii implied by these times (hyperbolic Kepler; diagnostic only, V5/V16): NEAR r_in = 5.35 r_p, r_out = 10.88 r_p; Galileo I 4.87 r_p, 1.64 r_p; Rosetta I 7.43 r_p, 2.11 r_p; Juno predicted 6.18 r_p, 11.82 r_p. Gaps are asymmetric about closest approach in every sourced case. Prior art for an anomaly tied to tracking interruption: Guruprasad, EPL 110, 54001 (2015), arXiv:1507.08222 (positive anomaly only when DSN tracking is interrupted around perigee).

### 2.6 External-audit table inputs against retrieved data
| row | audit input | retrieved | result |
|---|---|---|---|
| NEAR gate | "4.2 r_p gap across perigee" | r_in 5.35 r_p, r_out 10.88 r_p | audit value unsourced; actual gate asymmetric |
| Galileo I δ_in | +12.52° | −12.52° (PRL) | sign differs; cos δ unchanged |
| Galileo I gate | "3.6 r_p" | 4.87 r_p / 1.64 r_p | unsourced |
| Rosetta I gate | "2.9 r_p" | 7.43 r_p / 2.11 r_p | unsourced |
| Rosetta II V∞, δ | 9.360 km/s; −19.2°/+20.1° | 9.364 km/s; **−10.80°/+18.59°** | declinations wrong; Eq. (1) = **+1.00**, not −0.56 |
| Juno V∞ | 10.389 km/s | 10.3887–10.3897 km/s | correct |
| Juno δ | −14.2°/+39.6° | +14.17°/+39.48° | |δ| correct, sign of δ_in differs (cos unchanged); Eq. (1) = +6.37, not +6.89 |
| repo `Hubble/tools/zk2_flyby_anomaly.cpp:168-177` | Rosetta II −6.0/−6.7, Rosetta III −34.2/−24.7, Juno −17.1/−22.1 | table §2.3 | repo rows are labelled estimates and match no retrieved source |

---

## 3. Mercury and PPN data (R2)
| quantity | value | source |
|---|---|---|
| GR perihelion advance | 42.98″/cy | quoted model value (Genova 2018; Iorio 2018) |
| EPM2011 additional perihelion precession, Mercury | **−0.020 ± 0.030 mas/yr** (= −2.0 ± 3.0 mas/cy) | Pitjeva & Pitjev 2013, Table 4 |
| relative bound on departure from GR-modelled advance | 3.0/42 980 = **7×10⁻⁵** | COMPUTED |
| formal σ of Mercury perihelion, EPM2017 | 8 µas/cy (realistic: up to ×10) | Iorio 2018 Table 1 |
| β − 1 | (−1.6 ± 1.8)×10⁻⁵ | Genova et al. 2018 (MESSENGER ranging) |
| Sun J₂ | (2.246 ± 0.022)×10⁻⁷ | Genova 2018 |
| η (Nordtvedt) | (−6.6 ± 7.2)×10⁻⁵ | Genova 2018 |
| Ġ M☉/GM☉ | (−6.13 ± 1.47)×10⁻¹⁴ yr⁻¹ | Genova 2018 |
| Mercury a, e, sidereal period | 57.909×10⁶ km; 0.2056; 87.969 d | NASA NSSDCA fact sheet; Standish table in-repo |

Genova et al. 2018 integrate the PPN-parametrised relativistic acceleration with c in the force model ("relativistic corrections … formulated based on the PPN parameters β and γ … c is the speed of light"). Pitjeva & Pitjev 2013 fit the additional precession "taking into account all other known effects". The quoted observable is a residual to a c-dependent model, the contaminating-input statement of `derivelist/README.md:51-57`. Sensitivity (V11): Δω = 42.98″/cy gives c = 299 795 202 m/s (+9.2 ppm); the quoted Δω = 5.0188×10⁻⁷ rad/orbit gives 299 788 582 m/s (−12.9 ppm); the 7×10⁻⁵ bound corresponds to ± 10.5 km/s.

## 4. Hydrogen (R3)
| quantity | value | source |
|---|---|---|
| R∞ | 10 973 731.568157(12) m⁻¹ | CODATA 2022 |
| m_p/m_e | 1836.152 673 426(32) | CODATA 2022 |
| m_e/m_p | 5.446 170 214 889(94)×10⁻⁴ | CODATA 2022 |
| Ry (eV) | 13.605 693 122 990(15) | CODATA 2022 |
| 6π⁵ | 1836.118 109 | COMPUTED; −18.8 ppm from m_p/m_e |
| Hα, Hβ, Hγ, Hδ, n=7,8,9 vacuum Ritz wavelengths (nm) | 656.4632(7), 486.2691(3), 434.1691(3), 410.28991(24), 397.12020(22), 389.01577(21), 383.64789(21) | NIST ASD H I |
| Rydberg-formula wavelengths with R_H | 656.46961, 486.27378, 434.17302, 410.29350 … | COMPUTED; +9.8, +9.6, +9.0, +8.8 ppm above Ritz (V9) |
| Edlén (1966) air→vacuum of B01 air targets | 656.4623, 486.2708, 434.1690, 410.2898 | COMPUTED; −1.4, +3.5, −0.2, −0.4 ppm from Ritz (V10) |

The Edlén conversion in `benchmarks_suite.cpp` is validated against NIST on four known answers. NIST Ritz vacuum values are available as direct B01 targets and would remove the conversion; the "NIST 656.4696 nm" in the external text is the Rydberg-formula value, 9.8 ppm above NIST's Ritz value.

## 5. α-chain binding energies (R4) — AME2020, IN-REPO (`nuclear/AME2020_mass_excess.txt`)
`alpha_chain_AME2020.csv`. B(total) = (BE/A)·A.

| nucleus | BE/A (keV) | B (MeV) | B − n·B(⁴He) (MeV) | bonds assumed in audit test | per bond (MeV) |
|---|---|---|---|---|---|
| ⁴He | 7073.9156 | 28.2957 | — | — | — |
| ⁸Be | 7062.4356 | 56.4995 | −0.0918 (unbound) | 1 | −0.092 |
| ¹²C | 7680.1446 | 92.1617 | 7.2747 | 3 (triangle) | 2.4249 |
| ¹⁶O | 7976.2072 | 127.6193 | 14.4367 | 6 (tetrahedron) | 2.4061 |
| ²⁰Ne | 8032.2412 | 160.6448 | 19.1665 | 9 (trigonal bipyramid) | 2.1296 |
| ²⁴Mg | 8260.7103 | 198.2570 | 28.4831 | 12 (octahedron) | 2.3736 |
| ²⁸Si … ⁴⁰Ca | 8447.7445 … 8551.3046 | 236.5369 … 342.0522 | in file | topology not retrieved | — |

V8: B(⁴He) from mass excesses = 28 295.662 keV = BE/A × 4; Q(⁸Be → 2α) = −91.84 keV. The bond counts are an assumption of the audit test, not data; cluster-geometry literature was not retrieved.

## 6. Galactic (R5)
SPARC: `stellar/SPARC_full_175.mrt` (175 disk galaxies, Lelli, McGaugh & Schombert 2016, CDS J/AJ/152/157; 3416 lines) and `stellar/SPARC_meta.txt`, IN-REPO. g† = (1.20 ± 0.02 random ± 0.24 systematic)×10⁻¹⁰ m/s² (McGaugh & Lelli 2016, radial acceleration relation, adopted Υ⋆). The engine's `a_floor = 1.10061×10⁻¹⁰` is an SDT-derived value (B34), not a datum.

## 7. Geometry (R6) — Wikipedia wikitext, SECONDARY
Kissing number: D = 3 → 12; D = 4 → 24 (exact); D = 5 → 40–44; D = 6 → 72–77; **D = 7 → 126–134**; D = 8 → 240 (exact); D = 24 → 196 560. 600-cell: 120 vertices, 720 edges, 1200 faces, 600 tetrahedral cells (20 per vertex). 120-cell: 600 vertices, 120 dodecahedral cells (4 per vertex). Icosahedral 12-around-1 with equal spheres: neighbour spacing 2.1029 against contact distance 2, gap 0.1029 (V12). Primary sources (Musin 2008; Conway & Sloane; Coxeter) not retrieved.

## 8. Jupiter / Io (R7)
GM(Jupiter system) = 126 686 531.9 ± 0.42 km³/s² (JUP365); Jupiter equatorial radius 71 492 ± 4 km, mean 69 911 ± 6 km; Io a = 421 800 km, e = 0.004, P = 1.762732 d (JPL SSD mean elements, epoch 2000-01-01.5). V13: √(GM/a) = 17.3305 km/s; 2πa/P = 17.4015 km/s (ratio 1.00409). The mean-element triple (GM, a, P) is not mutually Keplerian at 4×10⁻³, so any Io check must name which pair it uses. The external audit used the mean radius 69 911 km; the equatorial radius differs by 2.3 %.

## 9. Engine `measured::` against CODATA 2022 (R8) — `engine_measured_vs_CODATA2022.csv`
| symbol | engine edition | (engine − 2022)/2022 |
|---|---|---|
| α | 2018 | +6.85×10⁻¹⁰ |
| m_e | 2018 | −1.36×10⁻⁹ |
| a₀ | 2018 | +6.78×10⁻¹⁰ |
| R∞ | 2018 | +2.7×10⁻¹³ |
| Ry (eV) | 2018 | +2.9×10⁻¹³ |
| m_p, m_n, m_d, m_t, m_He3, μ_P…μ_He3 | 2022 | 0 |
| R_p | muonic-H 2019 (8.414×10⁻¹⁶ m) | +7.7×10⁻⁴ against CODATA 2022 8.4075(64)×10⁻¹⁶ m (1.0 σ) |

The block header at `laws.hpp:123` reads "CODATA 2018 measured values" while the mass block is 2022. Effect on any product mixing the two editions (for example m_p/m_e): ≈ 1.4×10⁻⁹. Held as a record; canon unchanged.

---

## 10. Discrepancy log
1. Galileo I δ_i, δ_o: PRL both negative (−12.52, −34.15); ASTG II prints both positive; external audit used +12.52. cos δ is even, so Eq. (1) is unaffected; any signed-declination use is.
2. Rosetta I ΔV∞: PRL 1.80 ± 0.03; Turyshev & Toth 2009, Wikipedia, repo dataset 1.82 ± 0.05; ESOC 2026 quotes 1.82.
3. NEAR inclination: PRL, ACN 2007, Wikipedia 108.0°; Turyshev & Toth Table 1 prints 108.8° (likely typo).
4. Altitude conventions: PRL H (geoid) 960/303/539/1175/1956/2347 km; ACN/Turyshev minimal altitude 956.053/—/532.485/1171.505/1954.303/2336.059 km; repo dataset uses the latter. Choose one per computation.
5. ACN 2007 Table: MESSENGER eccentricity printed 1.13597; recomputed 1.3597 (V3) — transposition.
6. ASTG II Table II: Cassini V∞ printed 1.601 (16.01 km/s).
7. Cassini ΔV∞: −2 ± 1 (PRL) against −0.50 (ESOC 2026 census, citing statistical re-analysis).
8. Rosetta II altitude 5322 (Lämmerzahl/Wikipedia), 5301 (ESA pre-encounter), 5295 (ESOC 2026), 5316.5 osculating (Horizons); Rosetta III 2483/2481/2480/2482.9.
9. Antreasian & Guinn 1998 give ΔV ≈ 4.3 mm/s (Galileo I) and ≈ 13.0 mm/s (NEAR) with the 1998 gravity field; Anderson 2008 reports 3.92 and 13.46 after re-analysis. Vintage differences are ~10 % and ~3 %.
10. Repo `zk2_flyby_anomaly.cpp:168-177`: Rosetta II/III and Juno declinations and Rosetta II V∞ 9.32, Juno V∞ 9.87 match no retrieved source (§2.6).
11. ISSI flyby team page: its Table 1 is an image; no numbers extractable.
12. NASA JPL TRS landing page for AIAA 98-4287 serves HTML, not the PDF; the PDF was read from the Internet Archive snapshot of the same handle (2014/20322).
13. First attempt at the Pitjeva & Pitjev paper used a guessed arXiv identifier that resolved to an unrelated paper; discarded; correct identifier 1306.3043 found by search.
14. Wikipedia flyby table is internally inconsistent in places (Galileo II −5.9 ± 0.2 in one reference); used only as SECONDARY.
15. `Investigations/EXTERNAL_AUDIT_2026-10-16_ASSESSMENT.md` quotes per-bond energies 2.129 and 2.373 MeV (rounded inputs); full-precision AME2020 gives 2.1296 and 2.3736 (§5). Conclusion unchanged.
16. Horizons osculating altitude for Galileo II depends on the state offset (379.0 km at ±12 h, 303.0 km at ±6 h); the PRL altitude (303 km) is the closest-approach value.

## 11. Master Specification pass (applied to this register)
| gate | result |
|---|---|
| 1.1 adversarial vantage points | peer reviewer: PDF text-layer transcription → validated by V2; design-around: Edlén coefficients → validated against NIST (V10); examiner: provenance of every number in `MANIFEST.md` with sha256 |
| 1.4 pronoun ban | applied to chat output; repository text follows the gateway register |
| 2.1 step-by-step arithmetic | V1–V16 executed and logged; no figure typed from memory except where marked transcribed |
| 2.2 dimensional homogeneity | K dimensionless; V∞ km/s, ΔV mm/s (×10³ conversion explicit in the script); r in km; gap times in s |
| 3.2 excluded symbols | none introduced; G, M do not appear as inputs (GM_J, GM_Earth are the measured combined parameters) |
| 3.4 tombstones | no excluded construction used; the exponential saturation form and the m³/kg displacement constants appear only in the audit-intake record as rejected items |
| 3.5 certification | every row OBSERVED or COMPUTED; no row claims DERIVED, no IDENTITY restatement counted |
| 4.x spherical purity | not applicable: no spatial scalar crosses a frame algebra here; declinations/right ascensions are spherical angles from the ICRF equator |
| 5.1 back-check | flyby and CODATA findings cross-checked against `benchmarks_suite.cpp` B01 (done), `laws.hpp` `measured::` (§9), `Hubble/tools/zk2_flyby_anomaly.cpp` (§2.6) |
| 6.x deliverables | no manuscript or deployment package: retrieved data refute the audit table and supply no new derived result |

## 12. Not retrieved / outstanding
| item | obstacle |
|---|---|
| as-flown Doppler and range residual series, DSN station schedules, TNF/ODF | access-restricted (as already noted in `parker_solar_probe_2026-08/MANIFEST.md`); Cassini SCE1 TDF is the only DSN tracking file in the cache and concerns Saturn-cruise conjunction, not Earth flyby |
| tracking coverage for Cassini, MESSENGER, Rosetta II/III, JUICE, Hayabusa2, OSIRIS-REx, BepiColombo | not in retrieved sources; ESA/ESOC navigation reports and Thompson et al. AAS 14-435 (NTRS `downloadsAvailable: false`) needed |
| Juno reconstructed ΔV∞ ± 0.8 mm/s primary text | AAS 14-435 full text not openly downloadable |
| Iess et al. 2021 (BepiColombo) | not retrieved |
| Pitjeva & Pitjev 2013 Tables 1 and 3 (data intervals) and Park et al. 2017 | not retrieved |
| primary kissing-number and polytope references | not retrieved |
| cluster-bond topology literature for ²⁰Ne, ²⁴Mg | not retrieved |
| E105 F1 (SOHO/LASCO Kreutz astrometry), F3 (original 1/a), F4–F6, F8, F9 follow-ons | not attempted this session; `Datasets/MUST_FETCH_2026-07-23.md` rows F2 (PSP Horizons: `parker_solar_probe_2026-08/`), F7 (PREM), F10 (GWTC) and F12 (ENDF/B-VIII SFY) carried stale WANTED/BLOCKED statuses against cached files; corrected 2026-10-16 |
| IAG solar FTS atlas, white-dwarf per-line redshifts | WANTED, unchanged |

## 13. Files written
`Datasets/external_audit_2026-10-16/` (MANIFEST.md, VERIFICATION_LOG.txt, 10 CSV tables, `raw/` with 18 cached source files plus `raw/horizons/` with 9 responses); `C:\sdt-data\flyby_2026-10-16\` (4 files: publisher-copyright reading copies of PRL 100, 091102 and AIAA 98-4287 with text layers; never committed); this register; rows appended to `Datasets/MANIFEST.md`.

---

## 14. Control data — flybys by entry/exit pressure depth (added 2026-10-16, GOM44)

Added data: heliocentric Horizons tables for the nine flybys of §2.3 and geocentric + heliocentric tables for eleven further Earth encounters (Stardust 2001, EPOXI I–III 2007–2009, Hayabusa2 2015, OSIRIS-REx 2017, BepiColombo 2020, Solar Orbiter 2021, Lucy I–II 2022/2024, JUICE LEGA 2024): 40 tables in `external_audit_2026-10-16/raw/horizons_gom44/` with `SHA256SUMS.txt` (JPL Horizons API, VECTORS, ICRF, 10-min step; query as §2.3 with CENTER = 500@399 geocentric, 500@10 heliocentric). Endpoint vectors at equal geocentric radius, the quantity `GOM43` named as missing, are now computable for all 20.

Result (`Investigations/06_Gravitation_and_Orbital_Mechanics/GOM44_Flyby_Endpoint_Depth_Controls/`, registered before the run): the registered endpoint formula is inconsistent within tolerance on G2–G5 (anomalous class 4/4 fail, null class 9/9 fail, Spearman ρ = 0.375, p = 0.092).

Equal-depth control population (|B| ≤ 0.1, B = (D/R_☉,in)² cosψ_in − (D/R_☉,out)² cosψ_out, post-hoc threshold): Hayabusa2 at all three reference radii (B = 0.031, 0.021, 0.019 at 20 000, 50 000, 100 000 km); EPOXI II at 50 000 km only, as a geometric artefact (closest approach 49 829 km). No published Δv∞ exists for Hayabusa2 (census "?"; JAXA reports a 43 cm/s planned-versus-actual offset, not an isolated anomaly): **NOT RETRIEVED** (the genuine control cannot be scored). Prediction on record for Hayabusa2: +0.29 mm/s.

Further not retrieved: published Δv∞ and tracking coverage for Stardust, OSIRIS-REx, Lucy I/II, Hayabusa2 (mission navigation papers/JAXA ISAS reports).
