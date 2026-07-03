# FLM10 Phase 0 — Build the Network: results

**J. C. Harvey, Melbourne — 2026-06-25.** Tool: `flm10_network.py` (seed 20260625, reproducible).
Outputs: `flm10_network.npz` (216 nodes, 432 bonds), `flm10_network_diagnostics.png`.

## What was built

A corner-sharing tetrahedral **continuous random network** (the FLM08 substrate): a diamond seed (the ordered
4-coordinated tetrahedral crystal) amorphised by **Wooten–Winer–Weaire bond-switching** with **Keating-potential
relaxation** (simulated annealing, 3- and 4-rings forbidden).

## Verified vs the FLM08 invariants

| invariant | crystal seed (diamond) | amorphous CRN | FLM08 target | verdict |
|---|---|---|---|---|
| coordination | 4 (every node) | **4 (every node)** | 4 | ✅ preserved by every WWW switch |
| bond angle (mean) | 109.47° (δ-function) | **108.7°** | arccos(−1/3)=109.47° | ✅ |
| ring statistics | all 6-rings | **{5:253, 6:158, 7:20}** (no 3/4-rings) | 5/6/7 mix | ✅ mixed, no forbidden rings |
| void fraction | 0.660 | 0.660 | ≈0.66 (π√3/16) | ✅ |
| **isotropy** (Steinhardt Q₄) | **0.509** | **0.052** | →0 (isotropic) | ✅ collapsed ~10× |
| **isotropy** (Steinhardt Q₆) | **0.629** | **0.058** | →0 (isotropic) | ✅ collapsed ~10× |

**The headline — isotropy emerges.** The crystal's bond-orientational order (Q₄=0.51, Q₆=0.63) **collapses to
~0.05** in the amorphous network: the medium becomes **statistically isotropic**. This is the seed of Phase 1 —
an isotropic elastic medium has exactly one longitudinal + two transverse acoustic modes (gravity's `c_L` +
light's two `c_T` polarisations), and *no preferred axis* — i.e. the structural precondition for Lorentz
linearity that CONDENSA/FLM08 assert. **This result is robust** (it is a topological/orientational fact, not a
fine quantity).

## Honest caveat — glass quality is sub-gold-standard

The network reproduces every FLM08 *topological* invariant, **but it is a strained glass**, not yet a
gold-standard CRN:
- **bond-angle σ = 25.3°** — a well-relaxed tetrahedral CRN (amorphous Si benchmark) is **σ ≈ 10–11°**.
- **ring distribution is 5-peaked** (253 fives vs 158 sixes); a good CRN is **6-peaked**.

Diagnosis (checked, not guessed): a final tight relaxation did **not** reduce σ, so this is **topological strain,
not under-relaxation** — the 5-ring-heavy topology is geometrically frustrated (5-rings can't sit at tetrahedral
angles), forcing both bond and angle strain. A longer continuous-cooling anneal (1600 switches) did **not**
escape it either → it is a **finite-size / modest-WWW limitation** at N=216.

## Status & next step

**PHASE 0: substrate built — FLM08 topological invariants + isotropy reproduced; glass quality flagged
sub-gold.** The isotropy result (the Phase-1 seed) stands. But a **quantitative** Phase-1 dispersion `ω(k)` wants
a faithful glass, so before Phase 1 the network should be **rebuilt at N ≥ 512 with a longer anneal** (and likely
moved into the C++ engine `flm10_lattice_solver.cpp` for the speed to reach a 6-peaked, σ≈10° network). The
Python prototype is the correct, verified scaffold; it is honest about where its glass quality stops.
