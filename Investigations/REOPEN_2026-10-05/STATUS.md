# Reopen programme — status (updated as work proceeds)

Request (Harvey, 2026-10-05): reopen every investigation; for each analyse the prompt, upgrade it, show dependents and dependencies, give alternative outs, gradated outputs and triggers, and re-run in sequence from primary outputs down the chains; use dependency outcomes to direct the next layer of theory; step by step, meticulously. Protocol: `PROTOCOL.md`. Ledger: `LEDGER.csv`. Edges: `EDGES_LOG.csv`. Id collisions: `ID_COLLISIONS.md`.

## Scope found while building the graph
- 287 investigation folders under the category directories (not 208): 207 with `PROMPT.md`, about 74 more record in other formats (PRE_REGISTRATION / ASSESSMENT / INVESTIGATION / VERDICT only), including roots FLM04/06/07/08/12/15, PPT05/17, EMC03/04, APS01/02/05/07/12/14, NP01/17/21/25–34, NSEQ06a–14, GOM15–18/22, MM01–04, OM01–04, PSP01, CR01/02/07/10–13/17, GD02/07, NU01/02, CK01/02, AS01/02. The 2026-10-05 error audit covered the 207 PROMPT folders only; the other ~74 were not audited.
- Id collisions (propose-only renames): FLM15 ×2, NP21 ×2, GD06 ×2, Outstanding_Closure ×3.
- Declared dependency edges are noisy (stack-declared and "by supplier" edges are unreliable; one 28-node strongly connected group built from mixed upstream/downstream/neighbour declarations). Order inside it is set by hand from each prompt's `Upstream (required)` lines. The graph is rebuilt after every layer.

## Done (R2 record + run + ledger row)
| Id | Grade | One line |
|---|---|---|
| PPT01 | G2 | closure rule (n_T, n_P) not fixed by budget + helix; proton geometry depends on it (x = 1.2247 / 1 / 1.5); electron does not |
| FLM01 | G3 | hierarchy F_C/F_G = α(ƛ_p/ℓ_P)² reproduced G-free to +0.0195%, algebraic through ℓ_P (CODATA, measured via G); state28d scales dormant (≤ 5.2e-6) |
| FLM08 | G3 geometry / G2 identification | all invariants reproduced by independent construction (600-cell 3600/3600 at 72°; BC twist 131.810315°); identification premises untested |
| FLM07 | G3 (A–D, R=4ƛ_p within 0.76σ CODATA 2022) / G2 (E selection) | R = 6ƛ_p excluded (221–1079σ); selection is the sign of the price premise; T = 12, 1.831c, R_p/ƛ_p are one datum |
| FLM06 | G3 (ledger) | d ln X/d ln G: per-baryon routes ±1, body-level kinematics 0; seed = per-baryon gravitational coupling (`G_TAGS.csv`) |
| FLM15-inf | G3 | sealed ratio reproduced by independent grid quadrature to 0.11%; kernel 8πb³/7, 4πb³/21, 6/7 = engine to 1e-12; ratio = (1.05–1.22) × length ratio; normalisation convention (RMS vs major radius) moves it +8% to +55% |
| FLM02 | G1 (exact theorem) / G3 (restatement) | zero-force theorem fails node-level on the CRN substrate; knot-level net force = Σ(w_i−w_j)d̂_ij, suppressed below the uncorrelated bound; 12/12 rows are identities |
| FLM05 | G1 (torus derives mass) / G2 (z form) | torus-derived mass is 1.3e11–4.3e13 × m_p for the three trefoil sizes in use; stray z = 1/k² is canonical z = ϟ_H/r with ϟ_H = r_e; r_e/ϟ_b = F_C/F_G(e–p); 15 of 16 proofs are identities |
| PPT05 | G1 (geometry) / G2 (coefficient) | σ = m_pc²/(2πR) depends on R alone, spans 0.167–1.230 GeV/fm across lengths in use; PPT05 geometry = (1,2) partition on a (2,3) torus, not PPT01's; census at chance |
| PPT06 | G3 (reproduction; 1.831c = sqrt(r_e/R_p)) / G2 (T = 12) / G1 (record arithmetic) | T = 3R_p/lam_p holds for PPT05's trefoil only (PPT01 rules: 1.85-4.80); W=1 control 0.667 vs 6; gear decomposition printed 3mu/alpha (should be /alpha^2); N_contact, F_total in record text x10 low; l>=3 role conflicts with Theory/01 |

## Findings that change premises downstream
1. PPT01: the proton geometry used by NP15 (bracket −9.4% / +11.0%) and NP04A (√(3/2)) is rule-A conditional; PPT06 does not use PPT01's partition and cannot decide the rule.
2. FLM01: F_C/F_G(p–p) = α(ƛ_p/ℓ_P)²; the F_G expressions in FLM01's record are dimensionally wrong; the hierarchy rests on one number, ƛ_p/ℓ_P = 1.30121e19, and agreement with measurement carries G through the CODATA ℓ_P.
3. FLM07: "12 = 3×4" and 1.831c and R_p = 4ƛ_p are one measured datum (R_p); PPT06/NP15/NP20/NP27 neighbour confirmations are not independent of it. The stored R_p label ("muonic H 2019") holds the CODATA 2018 value; CODATA 2022 is 8.4075(64)e-16 m (fetched).
4. FLM06: the per-baryon koppa carries G in every route (exponent ±1); body-level koppa quantities carry none. Layer synthesis: `LAYER_0_FOUNDATIONS_SYNTHESIS.md`.
5. PPT06: 1.831c is the hydrogen koppa law at R_p (v_phase²/c² = r_e/R_p); T = 12 is PPT05's trefoil geometry times the datum R_p = 4ƛ_p (T = 1.85–4.80 with PPT01's closure rules); the gear ratio 1.03e8 = 3μ/α² (printed as 3μ/α); the ℓ=1/2/≥3 map is assigned in both Theory/01 and PPT06, and the two differ on ℓ≥3.

## Next, in order (layer 0 → down)
FLM03 → FLM04 → PPT09 → PPT02 → PPT17/PPT07 → EMC01 → EMC03/04 → FLM12/13 → FLM10 → FLM09 → FLM14 → … then the nuclear, gravitational, cosmological and suite chains (FD, TD, CM, QM, PM, OP, CH) in dependency order.

(PPT06 was taken ahead of FLM03/FLM04 on 2026-10-06; FLM03 and FLM04 remain next in layer 0.)

## Depth policy
Roots and high-reach nodes: full treatment (new or validated instrument, pre-registered, run). Where a folder already holds a pre-registered, validated, blind record (e.g. FLM15-inf, NSEQ, NP34), the record is read in full, its tool is reproduced, and only defects found are extended.

## Errata
- 2026-10-06: PPT01 R2 §7 T2 absolute lengths for rules B and C (see the erratum at the end of PPT01's R2): R = n_T ℏ/(m v_T), a = n_P ℏ/(m v_P). Velocities and x unaffected.
- Disk: the system drive was at 100% (≈ 0.6 GB free of 423 GB) on 2026-10-06; one write failed with ENOSPC and was repeated successfully. Not caused by this work (scratch ≈ 59 MB).
- 2026-10-06 (finding 1 above, and FLM07 R2 D7, PPT01 R2 §8, PPT05 R2 §8): PPT06 R2 (T3) shows that the statement 'PPT06's 1.831c and T = 12 do not use PPT01's mode partition; they are functions of the measured R_p alone' holds for 1.831c (v_phase²/c² = r_e/R_p, partition-free) and does not hold for T. T = ω_demand/ω_max with ω_demand = 2πq/T_circ, T_circ = 2πR_t/v_T; the engine's ω_demand = 3m_pc²/ℏ rests on PPT05's R_t = ƛ_p/√3 and v_T = c/√3. With PPT01's closure rules A, B, C the same formula gives T = 4.80, 1.85, 2.00 (instead of 12.00). T therefore carries a trefoil partition, and the dependence of the confirmation of T on the closure rule is restored; 1.831c remains partition-free. Errata appended in the three R2 records.
- 2026-10-06: the old Investigations tree (4,623 files, 293 MB) was copied in full to `ARCHIVE_PRE_RESET_2026-10-06/Investigations/` before the blank-slate runs; counts match. The ten R2 records above were produced by a procedure that read each old record first; they are drafts pending the blank-slate re-run. Their computed numbers come from validated tools on engine constants; the selection of tests and the pre-registrations were not blind.
