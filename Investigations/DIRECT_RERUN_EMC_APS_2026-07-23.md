# Direct re-run — categories 03 (EMC) and 04 (APS), 2026-07-23

> **Executor: Fable, direct (no agents), on Harvey's directive:** *"delete the sub-agent outcomes
> and verdicts and run all the prompts again, after checking that they are free of GR, QM and
> standard model assumptions."* Every number in the per-investigation
> `*_VERDICT_DIRECT_2026-07-23.md` files comes from a program executed today in this session.
> Compiler: g++ 15.2 (MSYS2 ucrt64), `-std=c++20 -O2 -I Engine/include`; Python 3.13 for APS06.

## 1. Deletions (27 files, all git-tracked → recoverable)

Agent-era outcome/verdict layer removed from all 11 investigations: INVESTIGATION.md results
write-ups (EMC01, EMC02, APS01, APS03), all `*_VERDICT.md`, all stale results/output txt/csv,
APS04's entire fabrication-era document layer (README, TREFOIL_WAKE, ANGULAR_QUANTISATION,
HUNTER_AUDIT, lamb_shift.txt), APS06's RUN_LOG. **Kept as specs (not outcomes):** EMC03 and
EMC04 `INVESTIGATION.md` (Harvey-authored theory docs), APS05 `INVESTIGATION.md` (Harvey spec),
all PROMPT.md files, APS07 `DATA_COLLECTION.md` (measured data), all tools and data files.

## 2. Prompt contraband findings

| prompt | ruling |
|---|---|
| EMC01, APS03, APS06 | **CLEAN — exemplary** (self-policing; APS03/APS06 pre-register every gate) |
| EMC02, APS05, EMC03/EMC04 docs | CLEAN (hygiene note EMC02: embedded stale phase-outcomes from the 2026-06-27 bulk template upgrade) |
| PROMPT_all_emissions (APS01/02) | CLEAN of rival axioms; **two flags:** says "charge radius" (canon: boundary radius); H/H-like chain is Rydberg algebra → must be labeled CONVERGENCE/IDENTITY, never sold as prediction |
| **APS04** | **CONTAMINATED (Phase 4):** imports the QM wavefunction (ψ single-valuedness = the quantisation postulate). Phases 1–3 native. Phase 4 not run; needs native re-pose |

## 3. Run matrix (18 executions)

| inv | result | headline (today's output) |
|---|---|---|
| EMC01 | 6/7 PASS, exit 1 | force law class C; G-test honest FAIL (~5×); P_eff question routed to EMC04 |
| EMC02 | PASS (negative) | e stays Tier-1: dimensional closure impossible ([A·s] unreachable); Lk route deferred (PPT09) |
| EMC03 | PASS class C | occlusion=Coulomb magnitude 1.4e-16; sign symmetry structural; zk²=1 |
| EMC04 | **4/4 PASS** | **P_eff derived from kinematics** (4.1e-12; whitelist form 3.9e-4); E→C on framework terms; residuals: α input, W+1 conjectural |
| APS01 ×8 | 7 ran, 1 CRASH | H 12.5 ppm / H-like 263 ppm (**CONVERGENCE**, Rydberg algebra); blind terrain recovery 7/9; capacities emerge (pair=2, cube); magnetism 102/118 with named fails; triton–d/f pattern (suggestive only — counts-degeneracy rule); `aps01_forward_derivation` unrunnable (0xC0000005 at -O2 and -O0) |
| APS02 | PASS pattern | drag D monotone with outer-shell count: 1.766 (lone) → 1.021 (full) |
| APS03 | **PILOT PASS + collapse re-earned** | with real full SPARC wired: pilot 23.7%/BTFR 3.58 exact; **C+A+B collapse 8.8%** over 20 bins; neg-control 53.3% (6× worse → power); nuclear 447% excluded; atomic floor slope +0.25 wrong-sign (ξ_A open); shape still BORROWED (MOND-simple) |
| APS04 | **FAIL, exit 2** | first-ever real execution: Lamb −2.05e16 MHz, exponents −2.99/broken/−3.07 vs −1/−3/−4. **Fabrication confirmed by execution**; hypothesis unadjudicated; solver needs rebuild |
| APS05 | 3 PASS + OPEN | 1/α = 136.912 (pure ratio) and 137.0726 (Law V seat); α² = second-order movement-budget term (+0.0013%); geometric derivation open |
| APS06 | ALL GATES PASS — **but P3 powerless** | 13.6 eV ceiling 0 ppm (convergent algebra); X-ray/γ overlap = provenance (convergent with modern convention). **P3 neutron-requirement corrected per Harvey: zero counterexamples was guaranteed (no bound N=0,Z≥2 nucleus exists at all — upstream fact, all frameworks) → consistency check, NOT falsifiable content.** Native residue: monotone ordering; teeth require deriving diproton unboundness (NP19/20, wedge-free) |
| APS07 | not run | data-collection stage only (King-plot dossier); intact |

## 4. Build repairs (logged, no tool sources edited)

- APS01 ×8: pre-rename `#include "cq12_element_data.hpp"` satisfied via scratch alias header.
- APS03 full-SPARC run: scratch harness supplying the tool's expected `../E46_Galaxy_Rotation_Curves/`
  data path with copies of GD05's SPARC files (tool's own §10 provenance protocol logged them).
- APS04 compiled under g++ (MSVC's C2131 constexpr-sqrt rejection does not apply) — first successful build.

## 5. What changed in the honest ledger

1. **P_eff (EMC04): now direct-class DERIVED-on-framework-terms** — was agent-class. Named
   residuals: α (input), W+1 (conjectural, 2e-4).
2. **APS03's 8.8% collapse: recovered** — the RETRACTED-STALE ruling is superseded; pilot passes
   on provenance-verified data. Wide-binary deep-floor extension now possible from the local
   cache (`C:\sdt-data\eb_wide_binaries.fits.gz`).
3. **APS04: fabrication confirmed by execution** — the solver's real output is 16 orders off.
   PPT08/Lamb amplitude remains OPEN and unbuilt; Phase-4 prompt contraband flagged.
4. **e irreducibility (EMC02): direct-class** — dimensional impossibility re-run, honest negative.
5. Two prompts need edits (propose-only): PROMPT_all_emissions ("charge radius" → boundary
   radius + identity-labeling rule), APS04 PROMPT (native re-pose of Phase 4).
6. One tooling blocker: `aps01_forward_derivation.cpp` crashes (needs debugging before its claims
   can exist at all).
