# Relationship corrections ledger — 2026-08-09

Cross-links among nuclear / geometry / aggregation audits. Canon arithmetic
untouched; comments already carry pure-shell / link / T14 seating (NSEQ05).

| Relationship | Wrong / incomplete reading | Corrected reading | Status |
|---|---|---|---|
| Grouped `+12d+10t` | One mixed shell | Closure *sum* of pure D then T | NSEQ05-C1 SURVIVES |
| First “12” after T₈ | Triangular faces ⇒ 12,16,20 | Cube-edge / link ⇒ 12,20,30 = R(n) | NSEQ05-C2 SURVIVES |
| Stella “12 faces” language | Face centres = next seats | Edge midpoints = cuboct (3+6+3); faces of *that* cuboct give 14 normals | NSEQ05-C3/C4 |
| Square-pole latitudes on 14-set | Primary seating | Diagnostic only (0° belt); **triangle pole** gives 2×90°+6×35.264°+6×19.471° | NSEQ05-C4 |
| 14 after D₁₂ | Immediate next triton shell | Capacity schedule: next T is T₁₀; 14 orients **T₁₄** | NSEQ05 + schedule |
| 14→42 | Arbitrary seats | Face-incidence graph, deg 6, two polar Q–Q branches; E>3V−6 OPEN | NSEQ05-C5/C6 |
| 14→42 “broken sphere” | E=42>3V−6 means seating fails | Surface S=TQ∪TT is maximal spherical (E=36, χ=2); +6 Q–Q chords ⇒ genus-1 triangulation (χ=0); 6 doublets = QQ⊕S midpoint pairs | NSEQ07 C1–C4 SURVIVES |
| 42 midpoints → rays | (unstated) | 42 distinct midpoints → **36** directions, **6** radial doublets / branch | NSEQ06-C1 SURVIVES |
| Branch doublet complementarity | Disjoint / empty ∩ | **EXCLUDED**: ∩=4, ∪=8 (share 4, 2 private each) | NSEQ06-C2 EXCLUDED |
| Shared doublet meaning | (unstated after NSEQ06) | Shared 4 rays = the 4 edges in `QQ∩` with fixed surface partners; each branch owns 2 private QQ | NSEQ08 SURVIVES |
| Magic N for δ₂ₙ | Must insert `{2,8,20,…}` | SEAL from F/B/R show ~4 MeV median gaps; OPEN_D `{40,70,112}` stay ~1 MeV — geometry supplies both classes | NSEQ09 SURVIVES |
| One branch rule | Polar ∩ and C3×inversion are the same cut | C3 WITHDRAWN. NSEQ11: Shared∪K₂,₂ matching. NSEQ12: TT-vs-TQ surface split **EXCLUDED** (all QQ doublets → TT) | NSEQ11 SURVIVES; NSEQ12 EXCLUDED |
| Shared vs matching by TT/TQ doublet partner | Matching → TQ | **EXCLUDED** (NSEQ12): matching also → TT; label class does not discriminate | NSEQ12 EXCLUDED |
| Shared vs matching by TT flip-axis | Shared→y, matching→{x,z} | **EXCLUDED** (NSEQ13): observed **inverse** (Shared→{x,z}, matching→y); not rescued | NSEQ13 EXCLUDED |
| Triton “belt” | Planar rolling equator | Dual-tetra / polar / cuboct face-normals | laws.hpp comments |
| Parity “precisely five” | Only H quasi-stables | Primordial misfits = L∪H | NP34b; comment corrected |
| Micro→macro Ω / Om | Body = N·Om_H | **MM02:** wrong unit — use `koppa_per_baryon`; ε≈4.4×10⁻⁴⁰ = `koppa_b/Om_H` IDENTITY. Law-III without `l_P↔G` **PARKED_PERMANENT (MM03, Iter 42)** | MM01–MM03 / Iter 42 |
| Spectroscopic Om in R_∞λ_C | Same as EM `r_e` | **EXCLUDED** length plug; Om_spec=`1/α` is α-IDENTITY (AS01) | AS01 |
| Shared solar om | Retune per observable | One `om_☉` → limb 1.751″ + z (CONDITIONAL, OM01) | OM01 |

## Approve phrases

Parity / shell comment block in `laws.hpp` is already aligned with NSEQ05–NP34b.
No further approve phrase pending for those comments.

## Iteration 42 outstanding closure

All post-07–22 unlabeled OPEN mechanism rows adjudicated
(`MASTER_PROTOCOL_ITERATION_42_2026-08-11.md`). Terminal parks / exclusions /
underdetermined classes only — see `OUTSTANDING_FAILED_AFTER_07-22_CORRECTIONS_2026-08-09.md`.

Note: geometric **NSEQ13** (TT flip-axis Shared/matching) remains **EXCLUDED** above;
Iter-42 suite ID **NSEQ13** = occupation/MeV map (**UNDERDETERMINED**).

## External import still missing

`SDT_Audit_Iterations_07-22_Corrected_Mathematical_Proofs.md` was not found under
this workspace. MM01 captures the ε_agg debt independently; advertised numerical-pass
exclusions from that document remain file-import work if the source appears later.
