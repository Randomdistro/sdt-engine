# RUN_LOG — GOM18: Sagittarius A* — the equilibrium seat

**J. C. Harvey, Melbourne — 2026-07-07. Committed BEFORE any tool code.**
Directive (Harvey, verbatim): "let's determine Sagittarius A's equilibrium position."
Frame: the ENERGY_AS_MOVEMENT table's cosmic-terminus row — the SMBH as the bottom of the
support regress (maximum queue). This run places Sgr A* in the ledger: its seat (koppa,
kinematic), its consistency across dependents, its pressure-domain equilibrium against the
bath, and its position in the Galaxy's column. **No G, no M, no GM in-chain** — koppa from
(a,T) only; GM/M_sun appear ONLY in labelled informational rival columns.

## Declared measured inputs (literature, 3–5 s.f., sources named in-tool)

- S-star orbital elements (Gillessen et al. 2017 catalogue class + GRAVITY):
  S2 (a = 0.1255", T = 16.05 yr), S38 (0.1416", 19.2 yr), S55/S0-102 (0.1078", 12.80 yr).
- R0 = 8.277 kpc (GRAVITY collaboration distance to the galactic centre).
- EHT Sgr A* ring angular diameter: 51.8 ± 2.3 μas (2022).
- Sgr A* bolometric luminosity: ~10^35.5 erg/s (declared band 10^35–10^36; famously dim).
- Milky Way: v_circ = 233 km/s at R0 (kinematic); total luminosity band 1.5–3.0e10 L_Sun.
- sigma_bulge ≈ 105 km/s (rival-column M–σ check only).
- u_CMB (engine, Law I): F_CMB = c·u_CMB/4. Proton column m_p/σ_T from CODATA/Thomson
  (whitelisted particle constants; σ_T is a measured atomic cross-section — data boundary).

## Committed gates (never widened)

- **G1 (seat consistency — the GOM14 test at the terminus):** koppa computed independently
  from THREE dependents (S2, S38, S55) via ϟ = 4π²a³/(T²c²): spread (max−min)/mean ≤ 2%.
  FAIL ⇒ the two-body seat reading is broken at the galactic centre — report, do not tune R0.
- **G2 (cross-ledger consistency, 4700× apart in radius):** the photon-ring prediction
  θ_ring = 2·√27·ϟ/R0 from the S-STAR koppa must match EHT's 51.8 μas within the
  measurement error band (±2.3 μas) plus 2% input slack. This is the depth-closure move at
  Sgr A*: one ϟ read at ~1000 AU (stellar orbits) and at ~0.2 AU (light's capture rim).
  [√27 = the capture-rim factor of the native c-boundary geometry; carried from the same
  closure that gives r_photon = 3ϟ — declared as geometry, its native derivation is the
  GOM05-class debt, not re-litigated here.]
- **G3 (report rows, no gates — the equilibrium placements):**
  (a) r_eq(L_SgrA*) = √(L/4πF_CMB) — Sgr A*'s own radiative pressure-domain, in pc;
  (b) r_eq(L_MW) — the Galaxy's domain vs its stellar radius (the scale-invariance row:
      Sun 20,857 AU → galaxy → BAO, one equation);
  (c) column share: ϟ_SgrA* / ϟ_enc(solar circle, v²R/c²) — the terminus's fraction of the
      enclosed ledger;
  (d) native Eddington column-lift: L_lift = 4π c³ ϟ (m_p/σ_T) — the discharge luminosity
      that would hold the whole column off — and the measured L/L_lift ratio (the queue's
      current duty);
  (e) rival column [informational]: M–σ placement of the MW point.
- Look-elsewhere: ONE construction per row, no scanning. Precision honesty: inputs carry
  3–5 s.f.; nothing sharper than 1% is claimed anywhere.

Tool: `gom18_equilibrium_seat.py` → teed `gom18_results.txt`. PYTHONIOENCODING=utf-8.
