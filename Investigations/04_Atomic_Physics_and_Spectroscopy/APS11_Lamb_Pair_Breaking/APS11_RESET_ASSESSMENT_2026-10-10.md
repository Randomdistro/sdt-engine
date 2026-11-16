# APS11 — Lamb as pair-breaking occupancy: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:**
- PROMPT.md
- APS11_PRE_REGISTRATION.md (2026-08-13; carried unchanged where run)

**Not opened:** APS11_ASSESSMENT.md, ps11_lamb_pair_break.py, RUN_LOG.md.

## Scope under the 2026-10-07 method rule
- **Phase B is not run.** It is a declared matrix of 12 candidate cells (L1, L2, E1, E2, E3 at two node lengths) scored against measured intervals: a census. Harvey's 2026-10-07 rule excludes such censuses; NP06's census was withdrawn on the same grounds. G_table, G_HD and G_µ are therefore not evaluated.
- **Run:** Phase A (the koppa re-expression, with instrument gate V1 against PPT08's 0.2722 fm and 0.7034 m/s within 1%) and G_sign.
- **G_sign note.** The S2 ontology (an incomplete dyad puts 2S higher) was written with the measured sign known. G_sign can only show consistency, not confirm the ontology.

## Run and results
(below)
- Instrument: `aps11_reset_1.py`; output in `aps11_reset_1_results.txt`. Single pass.
- Constants are copied from `measured::`, with CODATA citation, as the 2026-08-13 pre-registration permits.
- He+ nucleus mass = atomic ⁴He mass − 2 mₑ, with electron binding neglected (well below the precision used).

**V1 met.** H n = 2: Δr = **0.2725 fm** (PPT08: 0.2722) and Δv = **0.7038 m/s** (PPT08: 0.7034), both within 1%.

**Phase A table** (koppa re-expression of the measured intervals; not a derivation):

| interval | f (MHz) | r_n (m) | v_n (m/s) | Δv (m/s) | Δr (fm) | Δr/r_n |
|---|---|---|---|---|---|---|
| H n=2 | 1057.8450 | 2.11786e-10 | 1.0938e6 | 0.7038 | 0.2725 | 1.287e-6 |
| D n=2 | 1059.2341 | 2.11729e-10 | 1.0938e6 | 0.7046 | 0.2728 | 1.288e-6 |
| H n=3 | 314.819 | 4.76519e-10 | 7.2923e5 | 0.3142 | 0.4106 | 8.617e-7 |
| He⁺ n=2 | 14041.13 | 1.05850e-10 | 2.1877e6 | 4.6692 | 0.4518 | 4.269e-6 |

**What the table shows** (descriptive, not a gate):
- The seat offset Δr is **not constant**: 0.27 / 0.41 / 0.45 fm across H n=2, H n=3 and He⁺ n=2.
- Every Δr sits within a factor of 2 of R_p/3 (0.280 fm) to R_p/2 (0.42 fm). No native rule is selected; choosing one now would reopen the census.

**G_sign: consistent.** In H, D and He⁺ the measured 2S₁/₂ lies above 2P₁/₂, as S2 requires. The ontology was written with the sign known, so this does not confirm it.

**Grades:**
- Phase A: G4 (computed; it reproduces PPT08's numbers).
- Sign: consistent, not a confirmation.
- Magnitude (Phase B): **not run**, excluded as a census under the 2026-10-07 rule.
- The native Lamb amplitude remains **G2, open**. It needs a single native offset rule, stated before any interval is loaded.

## Comparison with the archived record
Deferred.
