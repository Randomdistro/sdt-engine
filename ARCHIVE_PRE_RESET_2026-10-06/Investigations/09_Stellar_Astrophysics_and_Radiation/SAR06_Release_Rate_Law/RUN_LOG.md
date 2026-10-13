# RUN_LOG — SAR06 Release-Rate Law

> Executor: **Fable, direct.** Opened 2026-07-13. Append-only; pre-commitments before coding.

## Pre-Run Commitments (before coding)

- **CALIBRATED budget: 0.** All C1–C5 inherited zero-fit from SAR03 (results.txt, RUN_LOG H1–H6).
- **M1 bands:** weighting exponents m ∈ {2,4,6,8} run on the √(R/r) and hybrid profiles;
  report every amplification factor; a divergence is handled by reporting the kernel
  radius at which the integral reaches ×23 (a STRUCTURE finding, not a fit — the ×23 is
  the known gap, the kernel is the shape the mechanism would need; no m is "chosen").
- **M2 pre-registered candidates:** (R_p/λ_peak)², (R_p/λ_mean)², linear variants. The
  planning pass saw the squared forms land in C4's decade — logged as PRE-REGISTERED, not
  discovered. Lead threshold ×10; mechanism statement required in the verdict either way.
- **M3 is an IDENTITY check** — labelled before running; its output is the release
  quantum, not a validation.
- **M4 committed band:** homology exponent within 2.5–4.5 vs empirical M–L slope 3.5
  (rival column). Outside band = candidate killed as stated (dissection follows).
  Homology relations used (SDT-native, no G): N_b ∝ M-census, n ∝ census/R³,
  v_th ∝ v_koppa = c/k_star ∝ √(census/R) via ϟ = v²R/c² (mass-free k from v_surf),
  R(census) from the empirical MS radius relation R ∝ M^0.8 (OBSERVED, comparison-grade).
- **Forbidden:** fitting m or any exponent to close ×23 and calling it derived; promoting
  M3 to a result; rescuing an M4 failure by post-hoc state-dependence without naming the
  mechanism and its own testable exponent.

## Phase record (from real stdout, results.txt — run 2026-07-13, Fable direct)

Build: MSVC `cl /std:c++20 /EHsc /O2` (+ <initializer_list> include fix, no physics change).
BUILD_EXIT=0, RUN_EXIT=0.

- **M1:** m=2 → ×1.5, m=4 → ×3.0 (insufficient); m≥6 diverges at centre — truncated m=6
  reaches the needed ×23.1 at a **317 km central kernel** (m=8: 90,000 km, too soft).
  Reading: hot-cores weighting closes the gap ONLY as a km-class central engagement kernel
  — a structure PREDICTION of the weighting family, not a fit (m not chosen; family mapped).
- **M2 (pre-registered): (R_p/λ_mean)² = 1.853×10⁻²⁵ vs C4 = 1.286×10⁻²⁵ — ×1.44.**
  (λ_peak variant ×4.9; linear variants fail by 10¹².) Mechanism named: grip = transverse
  footprint² (PPT10's derived n=2), with the span being the LATTICE's Clearing-set λ_CMB —
  the medium remembers its span; local plasma light does not reset it. LEAD.
- **M3 [IDENTITY]:** E_event = 13.36 MeV vs grammar per-deuteron release 13.37 MeV —
  internal consistency exact; fixes the release quantum (nuclear class), derives nothing.
- **M4 KILL (as committed):** constant-grip law scales L ∝ M^−0.30 vs empirical 3.5 —
  outside band, KILLED, dissected: the alignment factor A(T) must carry T-exponent
  **q ∈ [14, 24]** (T_core ∝ M^0.2 homology). Rival column: SM pp q≈4, CNO q≈17 — the
  demanded q overlaps the CNO class that actually dominates the empirical M–L slope.

**LAW SHAPE EARNED (candidate, 3/5 constraints touched):**
  rate/baryon = attempt(n, v_th, πR_p²) × (R_p/λ_CMB)² × A(T),  A(T) owing q ~ 14–24.
Next decidable: derive A(T) from alignment-search geometry (mesh windows NP23, Arrhenius
root QM03) with its own exponent — no Gamow import permitted in-chain.

## External confrontation (web sweep 2026-07-13, Fable direct; sources in verdict)

- **C6 (NEW constraint, from solar-neutrino literature):** measured emission shells —
  B8 confined to 0.02–0.07 R⊙ (peak 0.05 R⊙), Be7 to 0.22 R⊙, pp to 0.30 R⊙; 94% of L
  produced inside 0.20 R⊙ (helioseismic accuracy ~2% at the production maxima).
  **M1's 317 km central kernel is KILLED by observation** (§K sort: CLAIM-FALSE for the
  m=6 kernel candidate). The concentration job passes to A(T): with q ≈ 15–25,
  engagement ∝ T^q naturally confines release to r ≲ 0.1–0.2 R⊙ — the A(T) factor must
  now reproduce the SHELL RADII, not just the M–L slope. Two observables, one exponent.
- **H4/Oort — CONVERGENCE-class hit:** r_domain = 20,857 AU vs the Hills-cloud outer
  border at 20,000–30,000 AU — and the literature places the MORPHOLOGY change there:
  flattened, ecliptic-organised inner cloud → isotropic outer sphere at ~20,000 AU.
  That is precisely the SDT mechanism's shape: solar convergence organises (disc) inside
  r_domain; CMB isotropy rules (sphere) outside. Flag: Oort structure is inferred from
  comet dynamics, not imaged — comparison-grade, not decisive.
- **C5 corona — CLASS hit, ×5 tension:** measured quiet-corona DEM peaks near 1 MK with
  little plasma above 2–3 MK; the koppa floor says 7.7×10⁶ K. Right class (10³ above the
  photosphere, as observed), wrong factor (×4–8 vs quiet Sun; the floor sits in the
  ACTIVE-corona band). k(r) refinement owed before C5 can score.
- **M4 refinement from real M–L slopes** (empirical bins: 4.84 for 0.38–1.05 M⊙, 4.33
  for 1.05–2.4, 3.96 for 2.4–7, 2.73 for >7): demanded q per bin under our homology =
  25.7 / 23.2 / 21.3 / 15.1 — q DECREASES with mass, while the rival's mechanism mix
  (pp→CNO) INCREASES its T-sensitivity with mass. Under a single A(T) this demands
  mass-dependent T_core homology (convection changes it — known) — logged as open
  structure, not resolved.
- **Band-table verification:** ALMA B3 quiet Sun 7220–7324 K (used 7300 ✓); B6
  6280–6343 K (used 6200 — low by ~2%, corrected in dossier use); 1.4 GHz quiet Sun
  55 sfu at minimum (used 50–60 ✓; implies T_b ≈ 1.2–1.3×10⁵ K, not 9×10⁴).
- **Unlooked-at status CONFIRMED:** CMB experiments treat the Sun exclusively as
  sidelobe contamination (avoidance + ground screens; QUIET's Sun-centred maps exist
  only as sidelobe finders). No search for a sky-fixed transmitted component in solar
  mm data has ever been performed. The fishbowl's requirement — predict, THEN look at
  an unlooked place — is available here.
