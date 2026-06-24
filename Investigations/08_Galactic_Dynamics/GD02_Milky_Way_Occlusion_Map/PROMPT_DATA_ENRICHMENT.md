# CQ19c DATA ENRICHMENT PROMPT
## Comprehensive Galactic Centre Stellar Catalogue Retrieval

### Objective

Retrieve **every individually catalogued star, compact object, and resolved infrared source** within 150 pc (projected) of Sagittarius A* and format the output as C++ `add()` calls compatible with the `build_catalog()` function in `cq19c_binding_proof.cpp`.

---

### Output Format (MANDATORY)

Every star MUST be output as a single C++ function call in this exact format:

```cpp
add("NAME", "SPECTRAL_TYPE", R_ARCSEC, PA_DEG);
```

Where:
- `NAME` = catalogue designation (e.g. `"S2"`, `"IRS 7"`, `"GCIRS 16NE"`, `"Arches-F1"`)
- `SPECTRAL_TYPE` = spectral classification or object type (e.g. `"B0-2V"`, `"WN7"`, `"K2 III"`, `"LBV"`, `"HII"`)
- `R_ARCSEC` = angular distance from Sgr A* in arcseconds (double precision)
- `PA_DEG` = position angle in degrees, measured North through East (0° = due North, 90° = due East, 180° = due South, 270° = due West)

**If position angle is unknown**, estimate from published (ΔRA, ΔDec) offsets using:
```
r = sqrt(ΔRA² + ΔDec²)
PA = atan2(ΔRA, ΔDec) × 180/π   [mod 360]
```
where ΔRA is positive East and ΔDec is positive North.

**If only galactic coordinates (l, b) are available**, convert to offset from Sgr A* (l=359.944°, b=−0.046°):
```
Δl = l − 359.944°
Δb = b − (−0.046°)
r_arcsec = sqrt(Δl² + Δb²) × 3600
PA ≈ atan2(Δl, Δb) × 180/π   [mod 360]
```

---

### Region of Interest

**Centre**: Sgr A* at RA = 17h 45m 40.04s, Dec = −29° 00′ 28.1″ (J2000)
Galactic: l = 359.944°, b = −0.046°

**Radius**: 150 parsecs projected (≈ 3800 arcseconds ≈ 63 arcminutes at d = 8.178 kpc)

**Distance assumed**: 8.178 kpc (GRAVITY Collaboration 2019)

**Conversion**: 1 arcsec = 0.03965 pc at 8.178 kpc

---

### Source Catalogues to Query (in priority order)

#### Tier 1 — Individual stellar orbits and spectroscopy (COMPLETE these)

1. **Gillessen et al. (2017)** — "An Update on Monitoring Stellar Orbits in the Galactic Center"
   - Contains: ~40 S-stars with full orbital solutions
   - Need: ALL stars with (a, e, i, Ω, ω, T₀), not just S2
   - Stars: S1, S2, S4, S6, S8, S9, S12, S13, S14, S17, S18, S19, S21, S24, S27, S29, S31, S33, S38, S39, S42, S54, S55, S60, S62, S66, S67, S71, S83, S87, S91, S96, S97, S145, S175, R34, R44
   - For each: compute current-epoch (r, PA) from orbital elements

2. **Peißker et al. (2020, 2022)** — Discovery papers for S62, S4711, S4714
   - Contains: ultra-short-period S-stars
   - Stars: S4711 (P=7.6 yr), S4714 (P=12 yr), S62 (P=9.9 yr), S4716, S4718

3. **GRAVITY Collaboration (2020-2024)** — Updated S-star orbits
   - Contains: refined orbits for S2, S29, S38, S55 with GR precession
   - Need: current epoch positions for all monitored targets

4. **Paumard et al. (2006)** — "The Two Young Star Disks in the Central Parsec"
   - Contains: ~100 OB/WR stars in the clockwise and counter-clockwise disks
   - Stars: IRS 16C, 16NE, 16SW, 16NW, 33E, 33N, 29N, AF, AFN, all "E" sources
   - Need: COMPLETE list with (r, PA) for every resolved source

5. **Fritz et al. (2016)** — "The Nuclear Cluster of the Milky Way: Total Mass and Luminosity"
   - Contains: ~6000 late-type giants with proper motions in central 4 pc
   - Need: All individually named/catalogued sources with spectral types

6. **Genzel et al. (2010)** — "The Galactic Center massive black hole and nuclear star cluster"
   - Contains: comprehensive review, reference positions for all IRS sources
   - Need: IRS 1W through IRS 35, all sub-components (E, W, N, S suffixes)

#### Tier 2 — Named clusters and complexes (ENUMERATE members)

7. **Arches Cluster** (l = 0.121°, b = 0.018°, d ≈ 26 pc from Sag A*)
   - Source: Figer et al. (2002), Clark et al. (2019), Lohr et al. (2018)
   - Contains: ~160 OB/WR members, 13 WN stars
   - Need: ALL individually designated stars with spectral types
   - Stars: F1-F18 (WN/WC), A1-A15, plus OB members
   - Format: `add("Arches-F1", "WN8-9h", 660.0, PA);`

8. **Quintuplet Cluster** (l = 0.163°, b = −0.060°, d ≈ 30 pc from Sag A*)
   - Source: Liermann et al. (2009), Clark et al. (2018)
   - Contains: ~100 members, Pistol Star, qF sources
   - Need: ALL qF-designated and individually named stars
   - Stars: Pistol Star (LBV), qF 211, 231, 241, 243, 256, 270, 278, 309, 320, 362, plus LHO sources
   - Format: `add("qF-211", "WC9d", 760.0, PA);`

9. **Central Molecular Zone sources** (|l| < 1.5°, |b| < 0.5°)
   - Sgr B2, Sgr C, Sgr D, Sgr E — positions relative to Sag A*
   - Any resolved stellar sources within GMC complexes
   - Massive YSOs, ultra-compact HII regions, maser sources

#### Tier 3 — Wide-field surveys covering 150 pc radius

10. **GALACTICNUCLEUS survey** (Nogueras-Lara et al. 2019, 2020)
    - Contains: near-IR photometric catalogue, >3 million sources in central 6000 sq arcmin
    - Need: only individually NAMED or spectroscopically classified stars
    - Any star with a published spectral type within 3800" of Sag A*

11. **APOGEE/SDSS GC fields** — spectroscopic survey
    - Any stars with APOGEE IDs within the search region
    - Need: 2MASS ID, spectral type, (RA, Dec) → convert to (r, PA)

12. **Dong et al. (2011)** — "HST/NICMOS Paschen-α Survey of the Galactic Centre"
    - Contains: emission-line sources, WR candidates, LBVs
    - Need: ALL Paschen-α sources with positions

13. **Mauerhan et al. (2010)** — "Discovery of WR Stars in the Galactic Centre"
    - Contains: ~100 new WR and emission-line stars in central degree
    - Stars designated: MHD 1-100+
    - Need: ALL with (RA, Dec) → convert to (r, PA)

14. **SIMBAD query** — `region(circle, GALACTIC, 359.944 -0.046, 63m)`
    - Need: ALL objects returned with:
      - object name
      - object type
      - angular separation from Sag A*
      - position angle from Sag A*
      - spectral type (if available)
    - Filter: stars, WR, emission-line, YSO, compact objects only
    - Exclude: extragalactic, unresolved blends, artefacts

#### Tier 4 — Compact objects and exotic sources

15. **X-ray binaries** — Chandra GC survey (Muno et al. 2009)
    - Need: individually named X-ray point sources within 150 pc
    - Format: `add("CXOGC J174540.0-290031", "XRB", r_arcsec, PA);`

16. **Pulsars** — known radio pulsars within search region
    - PSR J1745-2900 (magnetar, 2.4" from Sag A*), others

17. **Stellar-mass black hole candidates** — any identified from microlensing or X-ray surveys

---

### Completeness Requirements

For **each source**, provide ALL of the following (or state "unknown"):

| Field | Description | Required? |
|-------|-------------|-----------|
| Name | Catalogue designation | YES |
| Type | Spectral type or object class | YES |
| r [arcsec] | Angular distance from Sag A* | YES |
| PA [deg] | Position angle (N through E) | YES |
| RA, Dec (J2000) | If (r, PA) not directly available | for conversion |
| l, b (galactic) | If neither (r, PA) nor (RA, Dec) available | for conversion |
| Epoch | Observation epoch of the position | preferred |
| Source paper | ADS bibcode or short reference | preferred |

### Sorting

Output the `add()` calls sorted by **ascending r_arcsec** (closest to Sag A* first).

### Grouping

Group the output into sections using C++ comments:

```cpp
// ═══ S-STAR CLUSTER (r < 1") — Gillessen+2017, Peißker+2020 ═══
add("S62", "B-type", 0.090, 215);
...

// ═══ IRS COMPLEX (1" < r < 12") — Paumard+2006, Genzel+2010 ═══
add("IRS 16C", "WN5/6", 1.20, 190);
...

// ═══ CLOCKWISE DISK (1" < r < 12") — Paumard+2006 ═══
...

// ═══ CENTRAL PARSEC EDGE (12" < r < 25") ═══
...

// ═══ NUCLEAR STAR CLUSTER (25" < r < 126") ═══
...

// ═══ ARCHES CLUSTER (r ≈ 660") ═══
...

// ═══ QUINTUPLET CLUSTER (r ≈ 760") ═══
...

// ═══ CENTRAL MOLECULAR ZONE (r < 3800") ═══
...

// ═══ X-RAY SOURCES / PULSARS / COMPACT OBJECTS ═══
...
```

### Deduplication Rules

- If a star appears in multiple catalogues (e.g., `S2` = `S0-2` = `GCIRS 7A`), use the **most common designation** and note aliases in a comment
- IRS sub-components (e.g., IRS 13E1, 13E2, 13E3) should be listed INDIVIDUALLY
- Cluster members should be listed individually, not as a single "cluster" entry

### Scale Reference

```
1 arcsec  = 0.03965 pc  = 8178 AU   at 8.178 kpc
10 arcsec = 0.3965 pc
100 arcsec = 3.965 pc
1000 arcsec = 39.65 pc = 16.7 arcmin
3800 arcsec = 150.6 pc = 63.3 arcmin
```

### Expected Yield

Based on the catalogues listed above, the completed `build_catalog()` should contain approximately:

| Region | Expected count |
|--------|---------------|
| S-stars (r < 1") | 40-50 |
| IRS / CW+CCW disk (1-12") | 80-120 |
| Central parsec edge (12-25") | 20-40 |
| Nuclear star cluster (25-126") | 50-100 |
| Arches cluster | 100-160 |
| Quintuplet cluster | 80-100 |
| CMZ field stars | 50-100 |
| Compact objects | 10-20 |
| **TOTAL** | **~500-700** |

### Final Instruction

Produce the COMPLETE output as a single block of C++ `add()` calls ready to paste into the `build_catalog()` function body in `cq19c_binding_proof.cpp`, replacing the existing placeholder entries. Every call must compile. No placeholder data — only entries backed by published observations.
