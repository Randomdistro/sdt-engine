# TD03 — Verdict: Ideal Gas and Pressure from Occlusion

**Dual verdict: Prompt completion B · Physics class CONVERGENCE (with one NATIVE geometric sub-result, P1b).**
**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td03_pressure_occlusion.cpp` → `results.txt` (exit 0).

## What was run

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1a 1/3 from dynamics | bath ⟨cos²θ⟩ = 1/3 (3σ); impulse counting = Σmv_x²/V (0.5%) | 0.7σ; 0.000% dev; PV/Σmv² = 0.3362 | PASS |
| P1b FLM08 bond set | rank-2 residual < 1e-14; rank-4 spans [1/9, 7/27] | 3.3e-16; [0.111115, 0.259259] | PASS |
| P2 per-axis isotropy | \|r_axis−1\| < 4√(2/Np) | all 12 axes within gate | PASS |
| P3 Dalton + co-volume | ΣP_i additivity 1%; b>0 within 0.5% of 4v_p | exact (0e+0); split 1.0001/0.9997; b dev 0.01% | PASS |
| P4 delete test | k_B unit-bridge only | holds | PASS |
| T4 inherited firewall | grade ≤ TD02's class | honoured: PV=NkT labelled CONVERGENCE | PASS |

**Incidents (documented):** (i) pre-first-compile, the drafted P2 gate (axis-mean PV/NkT ± 1e-3)
was caught as an **identity** — with entropic T, axis-mean = Σmv²/2E = 1 cannot fail — and was
replaced by the falsifiable per-axis isotropy gate (ADJ-0, before any run). (ii) Run 1 gated FAIL
on the two-species split: the committed 1% gate sat below the √(2/1800) ≈ 3.3% noise floor of a
600-particle species — bath enlarged (gate unchanged), passes at the 0.03σ level. Both are in RUN_LOG.

## The honest split (as demanded by the prompt)

- **What TD03 owns and earned:** pressure = one-sided momentum flux counted at the wall with the
  1/3 emerging from isotropy (P1a — no inserted factor), and **P1b, the one genuinely SDT-specific
  result of this suite so far:** the FLM08/CONDENSA W+1 = 4 tetrahedral bond set satisfies
  Σbb^T = (4/3)I — a spherical 2-design — so ⟨cos²θ⟩ = 1/3 **exactly, for every wall orientation**,
  to machine precision. The discrete lattice does not perturb the pressure at all: the frustration
  fingerprint is *forbidden* at rank 2 and first appears in rank-4 moments, which span [1/9, 7/27]
  against the continuum 1/5. Answer to prompt Q1: δ = 0 identically; precision gas thermometry can
  never see the lattice — fourth-moment observables (e.g. non-Newtonian corrections, viscometric
  normal stresses) are where to look. This is geometry the SDT lattice supplies and generic kinetic
  theory does not.
- **What TD03 inherits:** equipartition and the MB bath from TD02 (CONVERGENCE — firewall clear
  but no SDT-specific content). The *number* PV = Nk_BT is therefore CONVERGENCE here; the claim
  "ensemble-free ideal-gas law" is **not** asserted. Disclosed identity: with entropic T the
  axis-averaged PV/NkT is 1 by bookkeeping; the physics lives in isotropy and the flux mechanism.
- **Flagged borrow:** the co-volume b → P(V−Nb) = NkT link is the virial/Mayer expansion.
  TD03 claims only sign (b > 0, hard-vortex exclusion) and magnitude (b = 4 × particle volume,
  MC-integrated to 0.01%, no fit).

## Physics class: CONVERGENCE overall

Which step would break if the substrate were not the SDT lattice? Only P1b — and P1b *protects*
the textbook answer rather than departing from it (a null fingerprint at rank 2 is still a real,
falsifiable statement about where lattice anisotropy must show up). Everything else is honest
kinetic theory with SDT vocabulary. Law III occlusion language did narrative work only.

**Owed (OPEN):** Q2 — feed a measured molecular radius into b for one real gas (needs a species
where "vortex wake radius" has an SDT-native definition; none exists yet). Q4 — radiation P = u/3
from the same ⟨cos²θ⟩ (see TD06). Rank-4 fingerprint: name a real observable bounded by [1/9,7/27].

**Certification:** P1a/P2/P3 COMPUTED; P1b DERIVED (exact geometry); virial link BORROWED-FLAGGED; zero CALIBRATED.
**Earned vs owed: earned the exact rank-2 protection theorem for the 1/3 (native); owed any observable that sees the rank-4 lattice fingerprint.**

## HUNTER §D — seven questions on the CONVERGENCE landing (OPEN items)

1. **Why:** the pressure chain (flux counting, isotropy, PV=NkT) is generic kinetic theory;
   the only lattice-specific step (P1b) *protects* the textbook 1/3 rather than departing from it.
2. **Recoverable?** PARTIAL — the upgrade path is concrete.
3. **Failed to account for:** an observable that couples to fourth-moment anisotropy — the
   rank-4 band [1/9, 7/27] is derived but not yet attached to a measurable.
4. **Errored premise:** that lattice structure should show in the *pressure*; P1b proves it
   cannot (spherical 2-design) — the fingerprint was sought at the wrong tensor rank.
5. **Freedom that fixes it:** fourth-rank observables (viscometric normal-stress differences,
   nonlinear response) evaluated on the FLM08 bond set — native geometry, no knob.
6. **Accounting for the freedom:** fully native (lattice_structure.hpp supplies the bond set);
   derivation owed, not fitted.
7. **Cascade:** the CONVERGENCE class of the PV=NkT *number* cascades from TD-ROOT-1 via the
   TD02 inheritance; the P1b sub-result does not cascade (it is closed and exact).

**Prompt completion B · Physics class CONVERGENCE (P1b sub-result NATIVE, exact) · Recovery PARTIAL (rank-4 observable owed) · Cascade root TD-ROOT-1 (via TD02 inheritance); P1b: none**
