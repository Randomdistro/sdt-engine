# MUST-FETCH — campaign & recovery shopping list (2026-07-23)

Repo-level fetch list for the SM campaign spearheads and the kill-docket recovery pass (the
per-investigation `DATA_REQUIREMENTS.md` pattern, lifted to one table). When a fetch lands:
cache it under `Datasets/` (or `C:\sdt-data\` if >100 MB), add its `MANIFEST.md` row with
sha256(12), and flip its status here to `CACHED`.

**Statuses:** `WANTED` (not yet attempted) · `ATTEMPTED-<date>` · `BLOCKED-<route>` (note the
obstacle and any contact/route) · `CACHED` (manifest row exists).

Note: **E109's primary archival test (DUNES far-IR) is already data-ready in-repo** —
`Experiments/E109_Solar_Spectral_Prism/data/dunes_vizier.tsv` et al. Nothing to fetch for it.

| id | for | what | candidate source | destination | status |
|---|---|---|---|---|---|
| F1 | E105 sungrazer kick (spearhead) | SOHO/LASCO C2/C3 astrometry of Kreutz-group sungrazers — per-pass positions/times sufficient to reconstruct v(r) inside 3 R☉ | Sungrazer Project (Battams, NRL); CDS/VizieR comet astrometry; published Kreutz kinematics compilations | `Datasets/solar_system/` | WANTED |
| F2 | E105 control | Parker Solar Probe trajectory metrology (comet-free G(x) control) | JPL Horizons (spacecraft ephemeris) | `Datasets/solar_system/` | WANTED |
| F3 | E106 lumiopause re-test (docket D05) | **ORIGINAL** (pre-entry) reciprocal semi-major axes 1/a for long-period comets — original, NOT osculating; disambiguate a vs Q before use | MPC; Marsden–Williams catalogue; Królikowska CODE catalogue (original 1/a is its speciality) | `Datasets/solar_system/` | WANTED |
| F4 | E108 galactic floor | Gaia RVS subsample / APOGEE DR17 RVs / globular-cluster RV samples across Galactocentric R, with per-star stellar params | Gaia archive; SDSS APOGEE; Harris GC catalogue | `C:\sdt-data\` (likely large) | WANTED |
| F5 | E109 follow-on | IAG solar FTS atlas (per-line convective blueshifts) | IAG (Göttingen) solar flux atlas | `Datasets/stellar/` | WANTED |
| F6 | E109 follow-on | White-dwarf per-line gravitational redshifts (Sirius B Hα/Hβ; Falcon et al. DA/DB samples) | published tables (VizieR) | `Datasets/stellar/` | WANTED |
| F7 | E97/GOM09 recovery (docket D18) — CONDITIONAL on re-open | PREM tabulation (ρ, v_p, v_s, P vs depth) | Dziewonski & Anderson 1981 table (IRIS/REM electronic form) | `Datasets/geophysics/` (new group) | WANTED |
| F8 | E99 recovery (wave 2) — CONDITIONAL on re-open | Tidal harmonic constants (M2/S2/K1/O1 amplitudes+phases, global) | TPXO / FES model exports; NOAA tide-gauge harmonic constants | `Datasets/geophysics/` (new group) | WANTED |
| F9 | NP30 §11 radial-load test + GOM19 P5(iii) — SHARED row (added 2026-07-23) | Elastic e-scattering **movement-distribution** profiles ρ_mv(r), doubly-magic ladder — decides "borne down from above" (inner compression under closures) which rms radii cannot resolve | De Vries, De Jager & De Vries 1987 (ADNDT 36, 495) via **UVa NCD archive** `discovery.phys.virginia.edu/research/groups/ncd/dldata/` | `Datasets/nuclear/UVaNCD_*.dat` | **CACHED 2026-07-23** (4 files, manifest rows added). Ladder landed: ¹⁶O, ⁴⁰Ca, ⁴⁸Ca, ¹²⁴Sn, ²⁰⁸Pb in SOG; ⁹⁰Zr in FB. ¹³²Sn absent (unstable — no e-scattering); ¹²⁴Sn used. **TEST RUN → strong "borne down" REFUTED** (NP30 §12) |
| F10 | GOM19 P2 (BH column) | GWTC event table — source masses, final mass/spin, radiated energy per event (extracted through GR waveforms — label RIVAL-COMPUTED/OBSERVED-through-model in use) | GWTC-3 catalog release (LIGO/Virgo/KAGRA, Zenodo machine-readable table) | `Datasets/gw/` (new group) | WANTED |

## Rules

1. **Pre-commit before opening data** — for any fetch feeding a live test (F3 especially): the
   pass/fail criterion is written and dated BEFORE the file is opened (fishbowl gate).
2. A fetch that dead-ends gets `BLOCKED-<route>` with the obstacle named — a silent dead-end
   reads as "not tried."
3. Fetched files are cited by `Datasets/` path in investigations — never re-pulled ad hoc.
