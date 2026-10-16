# External audit intake — assessment, 2026-10-16

Scope: claims from an external LLM audit of the repository (pasted by the Operator), checked by direct
execution against `laws.hpp`, the benchmark suite and the derivelist before any inclusion. Agent-written
text carries no evidential weight; only the recomputations below are cited. Nothing here changes a
`laws.hpp` constant or law.

## Included (applied 2026-10-16)

| Item | Disposition | Change |
|---|---|---|
| B01 finite-nucleus offset | Confirmed. Factor μ/m_e = m_p/(m_e+m_p) = 0.9994556794 (6π⁵ ratio gives 0.9994556692; E₁ differs by 0.01 ppm, so B01 does not depend on the open 6π⁵ status). | `B01_atomic_structure()` uses `atomic::reduced_mass_factor(measured::m_p)`. |
| B01 air/vacuum mismatch | Confirmed. Targets 656.281 / 486.135 / 434.047 / 410.174 nm are air values; prior SDT output was the infinite-nucleus vacuum wavelength. | Targets converted to vacuum by Edlén (1966) in `air_to_vacuum_nm()` (medium conversion of a measured target; no SDT quantity). Balmer rows use `atomic::emission_wavelength_m`. |
| `measured::` CODATA edition | Aligned to CODATA 2022 (α, m_e, a₀, R∞, Ry, k_e; shifts 0.3 – 1.4×10⁻⁹) | `laws.hpp` `measured`; `CLAUDE.md`; `ATOMICUS/reference/SDT_LAWS_REFERENCE.md`; B17 g-factor target |
| B01 targets | NIST ASD Ritz vacuum Balmer wavelengths replace the Edlén-converted air values; `air_to_vacuum_nm` retired; levels via `atomic::level_energy_eV` | `benchmarks_suite.cpp`, `laws.hpp` `atomic` |
| Occlusion theorem label and derivation | T4 → T3 (matches Ruleset); pair-coefficient derivation from the projected solid angle recorded; `solid_angle_cap`, `cap_over_projected` added (additive; `solid_angle_occluded` unchanged; E105 cap model retained) | `laws.hpp` `law_III` |
| GOM04/B27 Mercury closure | `bridge` STATUS paragraph; class B-conditioned; closed form `c_from_perihelion_advance`; B27 rows CONSTRUCTION; earned tally 66/66 → 64/64 | `laws.hpp`, `benchmarks_suite.cpp`, `derivelist/README.md` |
| n = 3 onset | second route recorded as a candidate with its unestablished premise | `laws.hpp` `nuclear` provenance |
| Flyby tool rows | Rosetta II/III and Juno V∞ and declinations replaced by Horizons values | `Hubble/tools/zk2_flyby_anomaly.cpp` |
| MUST_FETCH F2, F7, F10, F12 | stale WANTED/BLOCKED statuses corrected | `Datasets/MUST_FETCH_2026-07-23.md` |
| Ledger entries | four dated rows | `Theory/03_Open_Problems.md` |
| Header comment, shell-schedule provenance | Earlier note that the comment was stale is withdrawn: the onset remains READ at the pricing-rule level. Pointer to `triton_descent_onset` added. | Comment-only, `laws.hpp` (authorised by the Operator). |

B01 after the change: energy residuals 0.0008–0.0014 % (were 0.0536 %); Balmer vacuum residuals 0.0006–0.0011 %
(were 0.0253–0.0259 %). Suite tally after the B01 correction alone: 66/66 earned, 19 construction, 3 pending note-only; zero
diff outside the B01 rows. After the B27 relabelling of 2026-10-16 (above): 64/64 earned, 22 construction. The remaining +9.8 ppm on Hα (against NIST Ritz 656.4632 nm) is the next movement-budget term already logged at
`laws.hpp` (`emission_wavelength_m`). The reference value 656.4696 nm quoted in the external text is the
Rydberg-formula value, not a measurement; the measured vacuum centroid is 656.462 nm.

## Not included

| Claim | Finding |
|---|---|
| Mercury precession gives c without v_surf or R_⊙ (GOM04/B27) | Algebra valid (R_⊙ cancels), equivalent to the GR advance formula solved for c. The stated inputs return 299,788,582 m/s (−12.9 ppm), not 299,795,136. Withdrawal basis unchanged: contaminating input: Δω_orb, e — measured via ephemeris fits that propagate light with c — enters upstream of the closure (`derivelist/README.md:51-57`). Input uncertainty (0.1 % on Δω ⇒ 0.05 % on c) exceeds the 9 ppm agreement. Remains a consistency check. |
| n = 3 descent from F(n) > K₃ = 12 | Arithmetic correct. Premise (tier members kiss one core) not established; F(n) is a bipartite tier capacity. Not an independent second route to `triton_descent_onset`. Open candidate. |
| α-cluster screening factor (1 − z̄/16) | Tested against ¹²C, ¹⁶O, ²⁰Ne, ²⁴Mg binding energies (bond counts: triangle, tetrahedron, trigonal bipyramid, octahedron): per-bond 2.425 / 2.406 / 2.130 / 2.374 MeV; after the factor 2.771 / 2.961 / 2.748 / 3.165 MeV (full-precision AME2020 inputs, `Datasets/DATA_REGISTER_2026-10-16.md` §5). Spread 12 % → 14 %, rising slope introduced. Not supported; E_bridge undefined in the source text. |
| Galactic crossover "with zero borrowed function" | Limits correct (v⁴ = c²ϟ·a_floor outer; r·a_floor inner). Interpolation shape asserted, not derived; τ = r/R_flat and √(a_floor/a_bar) coincide only for a point mass; the form 1 − exp(−r/λ) is on the exclusion list. Requires derivation from Law III, a pre-registered single pass over SPARC, and passing GD05's 66 % RMS record. No result exists. |
| Flyby depth-gradient formula and six-mission table | Second term bounded ≤ 3.4×10⁻⁵ of the first; formula reduces to Anderson × (R/r_p) × W_gap. Recomputed NEAR 9.34, Galileo-I 2.59, Rosetta-I 1.04, Cassini −0.22 mm/s against table 13.44 / 3.94 / 1.81 / −1.98: table not reproducible from the formula. Gate radii unsourced. Deployment package and named contacts withdrawn. |
| APS02 slot weight 8/3 from ∫(1+cos²θ)sinθ dθ | Integral correct (8/3). Premise (occlusion ∝ 1+cos²θ) asserted; sphere average of 1+cos²θ is 4/3, the factor 2 is unexplained. The three "independent" routes share no anchored premise. APS02 remains CALIBRATED. |
| Occlusion cap versus projection (earlier intake) | Projection Ω = πR²/r² exact; cap form is the deliberate E105 near-contact saturation model. Physics fork, not a defect; no change made. |
| 13-sphere "42 contacts" | Icosahedral neighbour spacing 2.1029 against touching distance 2 (gap 0.103): 12 radial contacts, 30 near-contacts. |

Record: the T3/T4 label mismatch (`laws.hpp:489` says T4; `Theory/00_Ruleset.md:53` says T3) is open and held for the Operator.
