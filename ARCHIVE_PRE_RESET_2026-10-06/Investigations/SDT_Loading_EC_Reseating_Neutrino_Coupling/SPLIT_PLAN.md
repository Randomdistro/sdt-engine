# SPLIT_PLAN — SDT_Loading_EC_Reseating_Neutrino_Coupling

**Date:** 2026-10-03<br>
**Status:** PROPOSED. No child folder has been created. Ids and placement are propose-only.<br>
**Basis:** `DEPENDENCY_LEDGER_v2.csv` (97 rows: the 55 Phase 0 rows with D22, D29, D43, D49, D51, D52 revised, plus 42 upstream-source rows U01–U42). Upstream statuses are read from each folder's own record and were not re-run; nine rows are marked PARTIAL where the class was not extracted.

## Why this order

Phase 0 and the audit show the chain has one executed result (the atomic reference depth, which is the supplied α) and four mechanisms whose governing law is absent from the corpus. A child can only be pre-registered when its upstream inputs are classified. The children below are ordered by what each needs from the one before.

## Children

| Child | Proposed id | Scope (spec phase) | Starting state | Blocking gaps (ledger rows) |
|---|---|---|---|---|
| A | APS15 | Reference depth, seat response, emission (1) | Rydberg identity given a₀, α; per-ion R = L²/(μC_Z) = a₀/Z; fixed-action compression ΔE = E_B(R/r−1)² | Reference length carries the seat (D31). E_B undefined in the spec (D32, defined C/(2R) in continuation ADJ-003). z_R = Δλ/λ conflicts with the engine's z_spec (D30). C = Zαħc by construction (D22). |
| B | PM08 | Plasma connectivity and contact loading (2) | PM01–PM07 give circulation, induction, oscillation, reconnection; PM04 P2c PASS is toolchain-dependent | No native definition of collective electron connectivity or plasma pressure (D48). Occlusion channel weights are a frozen construction (D49). Solver qualification stale (D52). |
| C1 | NP40 | EC conversion event, accessibility, capture clock (3) | NP18 DEFER; NP20 OPEN; NP11 B back-solved (7.5 nats clock spread); PPT10/11 OPEN | No capture clock (D45), no derived Q_β (D44), no carrier law (D46, D47). Table holds only stable and long-lived nuclides, so 0 of 213 "inventory pairs" have Q_EC>0 (audit F3): a physical selection has to be defined first. |
| C2 | NP41 | Many-contact energy, emission, reverse response (4) | NSEQ18 builds 221/221; 37–41% of stored binding energy; value law PENDING; 212 of 217 nuclides exceed 3 contacts | Contact degree breaks a three-port reading almost everywhere (audit F5). NSEQ17 values are CALIBRATED(8–9) (D41). Heavy magnitude PENDING (NP17). |
| D | SAR10 | Bulk feedback, stability, escape (5) | PPT09 dynamical stability OPEN; SAR03 OPEN; PM07 named orphans | No instability equation; l_P is Axiom R1 (FLM06). |
| E | validation protocol (parent file) | Hold-out and blindness (6) | Historical exposure declared in RUN_LOG | Hold-out set chosen from outside the declared exposure and sealed before access. |

Dependency direction: A → B → C1 → C2 → D; E constrains all. B and C1 share no inputs and could be pre-registered in parallel; C2 needs C1's accessibility definition.

## Conditions for a child to be registered

1. Every load-bearing input has a ledger row with a class; none left PARTIAL or untraced.
2. A template-conformant `PROMPT.md` (§⓪–§⑩) with numeric gates and a pivot table, written before any instrument is built.
3. Instruments validated on known answers (A: hydrogen and He⁺ with R = a₀/Z; C2: He-4 and U-238 binding as the known-failure baseline).
4. A downgrade-trace line before any CONSTRUCTION or shared-input label (§3.8).
5. No fitted parameter added; existing CALIBRATED(1) items carried as declared in RUN_LOG.

## Decisions needed from the Operator

1. Ids and placement as proposed (APS15, PM08, NP40, NP41, SAR10 in their category folders), with the parent kept as a dependency map.
2. Whether to open A first. It needs no new law and its gate is the reduced-mass, R = a₀/Z, compression check; it will mostly confirm identities, which is itself a recorded result.
3. The FLM15 id collision and the stale solver manifest remain propose-only; neither is touched.

## Status update 2026-10-05
Child folders now exist (ids and placement still proposed, not approved): `04_Atomic_Physics_and_Spectroscopy/APS15_Reference_Depth_and_Emission` (run: COMPUTED, identity given α; D−H shift 0.17858 nm), `14_Plasma_Physics_and_Magnetism/PM08_Plasma_Connectivity_and_Contact_Loading` (spec only; blocked on a connectivity definition, ledger D48), `05_Nuclear_Physics/NP40_EC_Conversion_Accessibility_and_Capture_Clock` (P0–P1 run: 927 EC/B+ parents accessible; alternate grammar 94.0% valid, gate not met, 56 proton-rich light cases outside the grammar's domain), `05_Nuclear_Physics/NP41_Many_Contact_Energy_Emission_and_Reverse_Response` (P0 run: B_calc ≈ 0.366 B_meas with Spearman 0.9997, plateau factor ≈ 2.76 at A ≥ 60 unidentified; contact count equals A, so counts carry no information beyond A), `09_Stellar_Astrophysics_and_Radiation/SAR10_Bulk_Feedback_Stability_and_Escape` (spec only; blocked on earlier children). Unrelated: `05_Nuclear_Physics/NP42_Nu_A_Closure_Reset` (ν̄(A) onset test, renamed from NP37 to avoid the queued NP37 flay-depth id). Ledger row references in the child prompts follow `DEPENDENCY_LEDGER_v2.csv`.
