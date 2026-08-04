# Celestial data catalogue — what we hold, and what it can carry

> Swept 2026-08-03 for scroller work. Every row is a file that exists in the repo
> now, with its row count and what it is good for. Provenance from
> `Datasets/MANIFEST.md` where it applies. Author: J. C. Harvey, Melbourne.

## A. Raw measured data — solar system

| file | size | contents | scroller value |
|---|---|---|---|
| `Datasets/solar_system/SDT_ephemeris.csv` | **2 920 rows** | 8 planets × 365 days: `day, body, theta_deg, r_AU, v_km_s, ϟ_host, R_host_km` | **the strongest asset.** A full year of positions and speeds — enough to *animate* an orbit truthfully rather than draw a cartoon ellipse. ϟ_host is already on every row. |
| `Datasets/solar_system/SDT_resonance_lattice.csv` | 72 rows | 8 drivers × 9 ratios (1:2 … 5:6) with `a_res_AU` | resonance-shell scroller: where each planet's ratios land, and what sits there |
| `Datasets/solar_system/solar_system_mass_inventory.md` | — | Sun, 8 planets, major moons of every system, counts (Jupiter 95, Saturn 146) | mass ledger; note SDT uses it for **mass-free** checks, i.e. as the comparison column |
| `Datasets/solar_system/JPL_SBDB_comets.json` | **4 069 comets** | `full_name, e, a, q, i` — Halley through the whole SBDB pull | lumiopause / Oort work (E106); a 4 000-point scatter of a, q, i is a serious visual |
| `Datasets/stellar/stellar_partial.csv` | 77 rows | `class, name, host, a_AU, P_yr, host_mass, v_obs_kms, source, source_id` — planets **and** moons in one schema | the cleanest single table for a "one law, every scale" ladder |

## B. Raw measured data — beyond the solar system

| file | size | contents | scroller value |
|---|---|---|---|
| `Experiments/E109_Solar_Spectral_Prism/data/exo_hosts.csv` | **5 195 hosts** | `hostname, hd_name, hip_name, sy_pnum` | exoplanet host census; planet-count distribution |
| `Investigations/06_.../GOM14_.../koppa_multiplanet.csv` | **1 846 planets** | `hostname, pl_name, sy_pnum, pl_orbper, pl_ratdor, pl_orbeccen` | **koppa consistency across 1 846 exoplanets** — the multi-planet system test at scale |
| `Datasets/stellar/SPARC_full_175.mrt` + `SPARC_meta.txt` | 175 galaxies | Spitzer photometry + rotation curves | galactic, not planetary — the GD05 open problem, stated as open |
| `Datasets/cosmology/PantheonPlusSH0ES.dat` | 1 701 SNe | `zHD, m_b_corr, MU_SH0ES`, Cepheid flags | CR10–12; the EdS exclusion (ΔAIC ≈ 90) |
| `C:\sdt-data\eb_wide_binaries.fits.gz` | 883 MB | Gaia wide binaries (El-Badry) | outside OneDrive; the gravity-floor test |
| `C:\sdt-data\kic8462852\` | full locker | Kepler photometry, WISE, GTC/LCO chromatic, papers | **SAR09** — Tabby's Star, run and assessed 2026-07-30 |

## C. Computed results ready to narrate (numbers already earned)

| source | the result | why it scrolls |
|---|---|---|
| **GOM12** `gom12_rerun_2026-07-24.txt` | **koppa_Sun from each of 8 planets independently**: 1476.50, 1476.57, 1476.16, 1470.57, 1479.51, 1487.48, 1477.08, 1475.71 m — mean 1477.45, σ/µ = **0.30%**. Kepler v(r) = (c/k_Sun)√(R_Sun/r) reproduces all 8 JPL speeds, worst error **0.35%** (Saturn) | eight independent bodies returning one length. The pre-registered gate was 0.1% and it reads FAIL at 0.30% — **the honest headline is the convergence, with the missed gate stated** |
| **GOM12 §4** | **per-body koppa from satellite kinematics alone**: Moon→Earth +0.73%, Phobos→Mars +0.07%, Io/Europa/Ganymede/Callisto→Jupiter +0.016/−0.003/+0.018/+0.024%, Titan→Saturn −0.06%, Titania→Uranus −0.32%, Triton→Neptune +0.006% | **the four Galileans agreeing to 0.02% on one number** is the single most persuasive planetary figure we own |
| **GOM17** exchange ledger | one two-body ledger across **20 orders of magnitude** — Sun–Jupiter ↔ hydrogen at 0.4%; k_seat(H) = 137.0726 at 1.2 ppm | the "one law, every scale" spine |
| **GOM08 / laws.hpp `mercury_closure`** | k_Sun = 686.4 from Mercury's precession; ϟ_Sun = 1477 m | ⚠ **c-from-Mercury is WITHDRAWN** as a derivation (ephemeris fits use c upstream). Retained as a consistency closure — must be labelled that way |
| **GOM22** (2026-07-30) | Shapiro round-trip **247.24 µs** measured vs canon; the factor-2 repair; solar redshift 636.3 vs 633 m/s | the light-delay scroller, with the canon fault and its repair as the story |
| **B39 / B28 / B29** in the suite | Shapiro, depth, chirp rows — all tallied | live numbers for any figure |
| **GOM24** Cassini ring-moon corpus | PROMPT only — **no data pulled yet** | named gap |

## D. Canon constants available to any figure (`sdt::laws`)

`R_Sun` 6.957e8 m · `AU` 1.495978707e11 m · `L_Sun` 3.828e26 W · `koppa_Sun` 1477.05 m ·
`k_Sun` 686.4 · `r_domain_Sun` 3.12e15 m (**≈ 20 800 AU — the lumiopause**) ·
`a_Mercury`, `e_Mercury`, `delta_phi_Mercury` · plus the whole depth-closure block
(`depth`, `v_bound`, `shapiro_delay`, `c_far`, `clock_rate`).

## E. Already built on the site — do not duplicate

| page | subject |
|---|---|
| `solar-system.html` | **The Orrery** — 3D solar system |
| `st_ring_moons.html` | **The Seat Between Two Streams** — Saturn's ring moons |
| `koppa-ladder.html` | the koppa ladder |
| `clearing-ladder.html` | the wall in the infrared |
| `st_gom_gravity.html` | **Why Everything Is a Ball** — gravitation |
| `depth_closure_scroller.html` | the depth–closure theorem |
| `cq06-eclipse.html` | eclipse geometry |

## F. The gaps — scrollers the data supports and nobody has built

1. **One length, eight witnesses.** GOM12's ϟ_Sun table: each planet hands back the
   same 1477 m from its own speed and distance, no mass anywhere. The 0.30% spread
   and the missed 0.1% gate are part of the story, not hidden from it.
2. **The Galilean quartet.** Io, Europa, Ganymede, Callisto returning ϟ_Jupiter to
   0.02%. Four moons, one number, measured kinematics only.
3. **A year in the ephemeris.** 2 920 rows animating eight real orbits with ϟ_host
   carried on every row — the orrery exists, but not the *data-driven* one.
4. **Four thousand comets.** SBDB a/q/i scatter against the lumiopause at 20 800 AU.
5. **1 846 exoplanets, one koppa test.** The GOM14 table at full scale.
6. **The moon ladder** — `stellar_partial.csv` puts planets and moons in one schema:
   the same law from Phobos to Neptune.

## G. Named absences (do not invent these)

- **GOM24** Cassini ring-moon corpus: prompt written, corpus not pulled.
- No asteroid-belt or Kuiper table beyond the comet pull.
- No planetary-atmosphere or magnetosphere dataset in-repo.
- Solar-oblateness (E27) and sungrazer (E105) are specs, not data.
