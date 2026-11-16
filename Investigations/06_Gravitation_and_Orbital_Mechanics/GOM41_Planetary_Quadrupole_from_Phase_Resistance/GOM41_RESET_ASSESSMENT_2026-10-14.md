# GOM41 (planetary quadrupole from phase resistance), Round 2 — registration and assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–4 are the registration, written **before** `gom41_reset_2.py` exists. Sections 5 onward are filled in after the run.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (state after the reset; Q0/Q1/Q2 outcomes as printed in it; Round-2 order; prohibitions) and the kept specification (corpus fields, ladder, gates 1–7). Not read: `GOM41_ASSESSMENT.md`, `gom41_planetary_quadrupole.cpp`, `gom41_results_2026-10-05.txt`, `GOM41_RESET_ASSESSMENT_2026-10-10.md`.

Exposure, stated plainly:
- The prompt prints the old outcomes: Q0 RMS 254.75 % and 0/6 within 10 %; Q1 Earth +0.91 %, Jupiter −2.11 %, 3/6 within 10 %, RMS 28.89 %; Q2 per-body values. Q0 and Q1 are therefore **post-seen** (the prompt says so: "consistency only").
- Data already read in the cache stage (2026-10-14): the radius and rotation-period rows of the JPL physical-parameters page and of the six NASA per-planet fact sheets; the rows of the JPL satellite page for Moon, Phobos, Io, Titan, Titania, Triton. **Not read:** the `J2` row of each NASA per-planet fact sheet (sealed by discipline: the extraction printed only the radius and rotation rows, and the instrument below reads the `J2` row only in its second stage); the mass, GM, gravity rows (never used).
- A hand estimate of the Q1 Earth value made while drafting this registration (+0.9 %) coincides with the value printed in the prompt. The reconstruction of Q1 below was derived from the prompt's one-line description ("exact equator/pole convergence-boundary balance using the measured polar and equatorial boundary"), not from the old code; the coincidence is stated so that the Q1 label is read as "reconstructed and consistent", not "independently found".

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | internal inconsistency | Section 3 step 3 asks for a blind comparison on "a held-out body not in the six (e.g. Uranus or Neptune)", but Uranus and Neptune are two of the six. No body outside the six has all of: a satellite orbit, a measured polar/equatorial boundary and a measured J2 in the cached sources (Mercury, Venus have no satellite; the Moon has none; Pluto has no measured J2). Resolution registered below (Section 4). |
| D2 | definition | "Constant engaged resistance inside the measured mean radius" (Q0) leaves open which radius enters the rotation parameter q. J2 is defined against the equatorial reference radius; q is formed on the same radius (the first-order Maclaurin result J2 = q/2 holds with that pairing). Registered: equatorial radius throughout; mean radius carried for the record only. |
| D3 | what Q1 consumes | Q1 uses the measured polar radius. For the gas and ice giants the flattening is itself a response of the interior, so Q1 is a two-point consistency relation (it predicts J2 from the figure and the spin), not a profile prediction. It is kept because the prompt registers it and because it gives a profile-free reference scale. |
| D4 | the profile statement | Round 2 step 3 asks for "the native phase-resistance profile, stated before J2 is unsealed". The canon proposal in the sibling prompts (Harvey 2026-10-11/12, SAR03 and NSEQ15) is that engagement is modulated by the displacement depth z = ϟ(<r)/r at the place of engagement. Section 4 states that as the profile and derives what it implies at planetary depth. |

No downgrade is made on agreement grounds.

## 2. Corpus (rows, sources, rules fixed before the run)
Sources (all cached unmodified in `Datasets/solar_system/`, hashes in `GOM41_CORPUS_SOURCES_2026-10-14.md`, written at the cache stage):
- `jpl_ssd_planet_phys_par.html` — JPL SSD, equatorial and mean radius, sidereal rotation period (days).
- `nasa_earthfact.html`, `nasa_marsfact.html`, `nasa_jupiterfact.html`, `nasa_saturnfact.html`, `nasa_uranusfact.html`, `nasa_neptunefact.html` — NASA NSSDCA per-planet fact sheets: equatorial radius, polar radius, rotation period (hours), and (sealed until stage 2) the measured J2.
- `jpl_ssd_sats_elem.html` — JPL satellite mean elements: a (km) and P (days), epoch 2000-01-01.5.
- `FAILED_FETCH_404_jpl_ssd_planets_grav.html` — a failed attempt to fetch a gravity-field page (HTTP 404, error page). Kept, renamed; not a source.

Fixed rules:
1. Primary satellite per body (chosen here, before any koppa is computed): Earth → Moon, Mars → Phobos, Jupiter → Io, Saturn → Titan, Uranus → Titania, Neptune → Triton. Reason: one satellite per body, the same rule for all (a regular, near-circular, near-equatorial satellite where one exists; the Moon is the only Earth satellite). Validation satellites (V1 below): Mars → Deimos, Jupiter → Europa, Ganymede, Callisto, Saturn → Rhea, Uranus → Oberon, Neptune → Proteus.
2. Koppa from the satellite: ϟ = (2π/P)² a³ / c² (Kepler's third law as a statement of the satellite's movement budget; no G, no M).
3. Equatorial and polar radii from the NASA per-planet fact sheet (one source for the ratio a_e/a_p); the JPL page is a cross-check (gate C1).
4. Spin: the JPL sidereal rotation period in days (more digits); the sign (retrograde) is dropped because J2 depends on ω². The NASA hour values are the cross-check.
5. J2 (comparison-only): the `J2` row of each NASA per-planet fact sheet; read only in stage 2, after the predictions file is written and hashed.

## 3. Instruments, models, gates (fixed before the run)
Let n_s = 2π/P_s, ω = 2π/P_spin. The rotation parameter is q = ω²a_e³/(c²ϟ) = (ω/n_s)²(a_e/a_s)³ (c and ϟ cancel; ϟ is reported for the record).

**Q0_UNIFORM.** Constant engaged resistance inside the figure; the first-order response of a homogeneous rotating body gives flattening f = (5/4) q and J2 = q/2.

**Q1_CONVERGENCE (reconstructed).** The measured boundary is an equipotential of the koppa field plus rotation. With the exterior potential per unit mass in units of c²: Φ(r,θ) = −(ϟ/r)[1 − J2 (a_e/r)² P2(cos θ)] − ½ (ω/c)² r² sin²θ, equating Φ at the equator (r = a_e, P2 = −1/2) and at the pole (r = a_p, P2 = 1):

J2 = (a_e/a_p − 1 − q/2) / ((a_e/a_p)³ + 1/2).

At first order in f and q this is J2 = (2f − q)/3. J4 and higher are truncated (registered; this is the main expected residual for Jupiter and Saturn).

**Q2_BOUNDARIES.** Not run. It imports Clairaut/Radau theory and PREM/polytrope source models, which the rewritten prompt's prohibitions exclude as native tests, and its inputs (Earth strata, Mars core boundary, gas/ice profiles) are not cached.

**Validations on known answers (before any gate on the corpus):**
- **V1 (koppa instrument).** Koppa from two independent satellites of one planet agrees: Mars (Phobos, Deimos), Jupiter (Io, Europa, Ganymede, Callisto), Saturn (Titan, Rhea), Uranus (Titania, Oberon), Neptune (Triton, Proteus): relative spread ≤ 1.5 %. (Satellite orbits carry planetary-oblateness and third-body terms of order J2(R/a)², a few 10⁻⁴ to 10⁻³; the Moon, with the Sun's perturbation of a few 10⁻³, has no companion satellite and is excluded from V1.)
- **V2 (volume integration vs harmonic projection, gate 3).** Uniform oblate spheroid with a_p/a_e = 0.9: J2 by direct volume integration (Gauss–Legendre in r and μ) versus the exact (1 − a_p²/a_e²)/5 and versus Legendre projection of the same distribution: agreement ≤ 0.5 %.
- **V3 (zero spin and spherical leakage, gates 1 and 2).** ω = 0 and a_p = a_e: Q0 = 0 and Q1 = 0 with |J2| < 1×10⁻¹²; a spherical grid rotated through 37° and projected on P2: |J2| < 1×10⁻⁸.
- **V4 (resolution, gate 4).** Doubling radial and angular resolution of V2 changes J2 by < 1 %.
- **V5 (Q1 solver round-trip).** Choose ϟ, ω, a_e and a J2_true, build a_p from the equipotential relation by bisection, recover J2 by the closed form: error < 1×10⁻12 relative. Small-limit consistency: Q1 against (2f − q)/3 for f, q < 10⁻³: relative difference < 2×10⁻³.

**Corpus gates.**
- **C1 (cache consistency).** JPL equatorial radius vs NASA equatorial radius ≤ 0.01 % (Earth, Mars), ≤ 0.01 % for the four giants (1-bar level); JPL rotation period (days × 24) vs NASA hours ≤ 0.2 %; mean radius vs (a_e² a_p)^(1/3) ≤ 0.1 % (Earth, Mars), ≤ 0.1 % giants. Failures are recorded as input defects, not claim results.
- **G6 (prompt gate 6, applied to Q0 and Q1 in the registered order).** Advances only if Earth and Jupiter are each within 3 %, at least 4 of 6 within 10 %, and whole-corpus RMS fractional residual ≤ 10 %. Residuals are reported for all six bodies, signed.
- Predictions (Q0, Q1, and S1 of Section 4) are written to `gom41_reset_2_predictions.txt`, SHA-256 recorded in the results file, **before** stage 2 reads any J2.

**Hand estimates made before the run** (from the printed radii and periods; the only numbers I looked up are the ones listed in Section 0):
| body | q (hand) | Q0 J2 | Q1 J2 |
|---|---|---|---|
| Earth | 3.43×10⁻³ | 1.71×10⁻³ | 1.09×10⁻³ |
| Jupiter | 8.85×10⁻² | 4.42×10⁻² | 1.46×10⁻² |
| Neptune | 2.61×10⁻² | 1.30×10⁻² | 2.8×10⁻³ |
Expectation: Q0 fails badly (about +60 % Earth, +200 % Jupiter, a factor of several for Neptune); Q1 passes Earth and Jupiter and drifts for the ice giants.

## 4. The profile statement S1, held-out body, and its gate (written before J2 is read)
**S1 (native profile).** The engagement density at radius r is a function of the local displacement depth only, ε(r) = ε₀ h(z(r)), z(r) = ϟ(<r)/r, with h analytic at 0 and h(0) finite and nonzero. No other variable (no composition stratum, no equation of state, no body-specific coefficient). The form of h is not selected here and is not scanned (no census over candidate forms).

**Consequence derived before the run.** For any planet z(r) ≤ z(a_e) = ϟ/a_e, of order 10⁻¹⁰ (Earth) to 10⁻⁸ (Jupiter) (to be printed by the instrument). Then ε(r)/ε₀ = 1 + (h′(0)/h(0)) z(r) + O(z²): the profile departs from uniform by at most |h′(0)/h(0)| × z(a_e). For |h′(0)/h(0)| of order one the resistance is uniform to better than 10⁻⁷, and S1 predicts the Q0 value of J2 for every body, with a correction below 10⁻⁷ relative. S1 can differ from Q0 only if the coefficient |h′(0)/h(0)| exceeds ~10⁷, which would be a new parameter, not a native result.

**Blind comparison.** Because S1 has no parameter and consumes no J2, every body is blind in the sense of selection; the prompt's request for a body "not in the six" cannot be met (D1). Registered designation: **Neptune** (one of the two bodies the prompt names; chosen before any J2 is read). Scope: the prompt's printed Q2 values reveal Neptune's old residual, so "blind" means "no value of Neptune's J2 enters S1 or the choice of Neptune".

**Gate (committed).** The S1 prediction for Neptune is within 10 % of the measured J2. The S1 prediction for every body is also reported; gate 6 is applied to the S1 set as to Q0 (identical in value). Hand estimate: S1 = Q0 = 1.30×10⁻² for Neptune, a factor of several above any plausible J2 for a body of that flattening (f = 0.017 and q = 0.026 give (2f − q)/3 = 2.8×10⁻³). Expected: S1 fails.

**If S1 fails (gate 7).** The whole-corpus residual is preserved and the missing dependency is stated: a native variable that produces central condensation at z ≈ 10⁻⁹. Depth z is far too small to be that variable (the lever is of order z); the dependency is a different engagement variable, for example the load/pressure the Law-I/IV balance builds up inward (which scales as ϟ/r³ times a density-like scale, and is not small), and its normalisation is owed. No interior profile is tuned to J2.

## 5. Results (`gom41_reset_2.py`; outputs `gom41_reset_2_stage1_results.txt`, `gom41_reset_2_stage2_results.txt`, `gom41_reset_2_diag_results.txt`; predictions file sha256 `fbcf59167a5e8feb25f2e11694e422f3bba916442d24136fb76e1321d32ef4f8`, written and hashed before stage 2 read any J2)
Three attempts before the clean run, all kept: (1) satellite-page parser used the wrong cell for the name (`..._attempt1_parser_KeyError.txt`); (2) the Earth fact sheet is a `<pre>` text page, not a table (`..._attempt2_NASA_pre_layout_KeyError.txt`); (3) my patch script wrote a literal newline into a string (`..._attempt3_patch_SyntaxError.txt`). All three are instrument-reading defects with no bearing on any result.

**Validations and cache gates.**
- V2 met: GL projection matches the exact uniform-spheroid value (0.0380000) to 3.7×10⁻¹⁴; midpoint volume integration agrees to 6.3×10⁻⁴ (N = 400) and 3.0×10⁻⁴ (N = 800) (gate 0.5 %). V4 met: doubling changes J2 by 3.3×10⁻⁴ (midpoint) and 2×10⁻¹⁴ (GL) (gate 1 %).
- V3 met: zero spin and a_p = a_e give |J2| ≤ 2×10⁻¹⁵ (gate 10⁻¹²); tilted-axis spherical leakage 8.8×10⁻¹⁶ (gate 10⁻⁸).
- V5 met: Q1 round-trip relative error 1.8×10⁻¹⁵; small-limit difference from (2f − q)/3 is 2×10⁻⁴ (gate 2×10⁻³).
- C1 met for all six bodies (largest difference: spin Saturn 2.3×10⁻⁵; radii ≤ 6×10⁻⁶).
- **V1 NOT MET by the registered letter, for Jupiter only: koppa spread over Io, Europa, Ganymede, Callisto 1.518 % against the gate 1.5 %** (Mars 0.18 %, Saturn 0.068 %, Uranus 0.028 %, Neptune 0.15 % met). The gate is not amended. The spread is systematic in distance (Io 1.4211, Europa 1.4309, Ganymede 1.4094, Callisto 1.4096 m), a property of the JPL mean elements for the Laplace-resonant Galilean satellites, not of the instrument. It is carried as an uncertainty on the Jupiter row (post-seen diagnostic below).

**Koppa from one satellite (m):** Moon → Earth 4.47730×10⁻³ (Mars Phobos 4.77354×10⁻⁴; Jupiter Io 1.42114; Saturn Titan 0.422206; Uranus Titania 6.44787×10⁻²; Neptune Triton 7.60906×10⁻²). Surface depth z = ϟ/a_e: Earth 7.0×10⁻¹⁰, Mars 1.4×10⁻¹⁰, Jupiter 2.0×10⁻⁸, Saturn 7.0×10⁻⁹, Uranus 2.5×10⁻⁹, Neptune 3.1×10⁻⁹.

**Gate 6, signed fractional residual of J2 (predicted against the unsealed value):**
| body | Q0_UNIFORM | Q1_CONVERGENCE | S1 depth profile |
|---|---|---|---|
| Earth | +58.35 % | +0.91 % | +58.35 % |
| Mars | +17.00 % | +21.99 % | +17.00 % |
| Jupiter | +200.18 % | −0.98 % | +200.18 % |
| Saturn | +374.76 % | +2.87 % | +374.76 % |
| Uranus | +341.61 % | +65.53 % | +341.61 % |
| Neptune | +282.07 % | −17.97 % | +282.07 % |
| within 10 % | 0/6 | 3/6 | 0/6 |
| RMS | 251.82 % | 29.19 % | 251.82 % |
| gate 6 | NOT MET | NOT MET (Earth and Jupiter within 3 %: met; 3/6 against 4/6; RMS 29.2 % against 10 %) | NOT MET |

**S1 blind comparison, Neptune:** predicted 1.303×10⁻² against 3.411×10⁻³ measured, +282.07 %, gate (10 %) NOT MET. As registered, S1 equals Q0 to z (≤ 2×10⁻⁸ relative); the table columns are identical in value.

**Post-seen diagnostic (not gated): Q1 residual by choice of satellite.** Mars Phobos +21.99 % / Deimos +21.85 %; Jupiter Io −0.98 % / Europa +0.22 % / Ganymede −2.43 % / Callisto −2.40 %; Saturn Titan +2.87 % / Rhea +3.04 %; Uranus Titania +65.53 % / Oberon +65.61 %; Neptune Triton −17.97 % / Proteus −18.33 %. The satellite choice moves Jupiter's Q1 residual by 2.6 percentage points, inside the 3 % gate for every satellite; it moves no other row by more than 0.4 points.

## 6. What the result says, and does not say
- Q0 and Q1 reproduce the printed old outcomes closely (Q0 RMS 251.8 % against 254.75 %; Q1 Earth +0.91 % identical, Jupiter −0.98 % against −2.11 %, 3/6 and RMS 29.2 % against 28.9 %). The cached corpus is therefore consistent with the one the old instrument used, at the level these gates resolve. Q1 is the reconstruction named in Section 3 and is post-seen (Section 0).
- Q1's pattern is the finding: it holds to 1–3 % where the 1-bar boundary is a good equipotential of the field J2 describes (Earth, Jupiter, Saturn) and misses where it is not or where the J2-only truncation is coarse (Mars +22 %, Uranus +66 %, Neptune −18 %). Uranus and Neptune carry opposite signs, so a single truncation (J4 and higher) does not explain both; candidate causes (a non-equipotential boundary at the quoted level, the spin value used, Mars's non-hydrostatic crust) are named, not tested, and none is adopted.
- **S1 is excluded as a source of the missing quadrupole condensation.** The depth variable z = ϟ/r is 10⁻¹⁰ to 10⁻⁸ at every planetary surface, so an analytic modulation h(z) with |h′/h| of order one changes the resistance by less than 10⁻⁷ and S1 returns the uniform (Q0) quadrupole, which fails by +17 % to +375 %. S1 could differ from Q0 only with a coefficient |h′(0)/h(0)| ≳ 10⁷, which would be a new parameter and not a native result. This bounds Harvey's displacement-depth proposal at planetary depth; it does not bear on its use where z ~ 1 (nuclear contacts, NSEQ15) or ~ 10⁻⁶ (solar interior, SAR03).
- The dependency the prompt names stays open and is now sharpened: a native engagement variable that scales as a load or pressure (ϟ/r³ times a density-like scale, not small) rather than as the depth z. Its normalisation is owed. No interior profile was tuned to J2 and none is proposed here.
- Prompt defect D1 (held-out body "not in the six" while naming Uranus/Neptune) stands; the blind designation is Neptune with the stated scope.

## 7. Grades
| Item | Grade |
|---|---|
| Corpus cache (six bodies, hashes, provenance) | **done**; J2 column sealed until the predictions hash |
| Instrument validations V2–V5, cache gates C1 | **met** |
| V1 koppa spread (Jupiter) | **NOT MET by 0.018 percentage points; unamended**; effect on the corpus bounded (2.6 points on Jupiter Q1, within gate) |
| Q0_UNIFORM, gate 6 | **NOT MET** (RMS 251.8 %, 0/6) |
| Q1_CONVERGENCE, gate 6 | **NOT MET** (Earth +0.91 %, Jupiter −0.98 %, 3/6, RMS 29.2 %); COMPUTED, post-seen, profile-free two-point balance (not a profile prediction) |
| S1 depth-modulated profile, Neptune blind gate | **NOT MET** (+282 %); excluded at planetary depth by z ≲ 2×10⁻⁸ |
| B11 | **PENDING** (unchanged) |
| Label | **COMPUTED** (no DERIVED claim); Q1 convergent with the standard Clairaut first-order relation (2f − q)/3 by construction, not a discriminator |

## 8. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
