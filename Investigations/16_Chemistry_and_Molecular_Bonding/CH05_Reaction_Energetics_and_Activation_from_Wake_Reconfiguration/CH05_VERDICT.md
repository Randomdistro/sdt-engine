# CH05 — VERDICT: Reaction Energetics & Activation from Wake Reconfiguration

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch05_reaction_energetics.py` (exit 1 — honest) · Output: `results.txt`

## Results (models and gates committed in RUN_LOG.md before the run)

| Phase | Result | Call |
|---|---|---|
| P1 ΔH bookkeeping | 12/12 signs, 11/11 tested magnitudes ≤15% (best 0.0%, worst 10.2%; H₂+I₂ %-exempt by the pre-committed \|ΔH\|<20 rule) | matches — **labelled CONVERGENCE/IDENTITY per the prompt's own firewall**; earns no NATIVE credit |
| P2 barrier = wake saddle | M-SADDLE (budget split): **Eₐ = 0.0 kJ/mol** — the deeper well always holds the seat, path is barrierless. M-SADDLE+ (end-end pair term): symmetric H₃ comes out **BOUND by 191 kJ/mol** — wrong sign (H₃ is not a bound molecule). Measured Eₐ(H+H₂) ≈ 40 kJ/mol | **FAIL → OPEN** (no saddle emerges) |
| P3 catalysis | DEFER — depends on a saddle existing | DEFER |
| P4 novel BEP slope | DEFER — same dependency | DEFER |

The refusal is the result: a mis-cancellation cost term with a tuned magnitude would have manufactured the barrier — that is a FISHED RECOVERY and was refused. The barrier is real physics the current machinery does not contain.

## FAILURE RECOVERY (§D seven questions — P2)

1. Why: with pairwise-additive wells and a linear engagement budget, U = min(V₁,V₂); every exchange path can pass through (Re,Re) at −De, so Eₐ = 0 exactly. Adding the end-end pair term makes it worse: −191 kJ/mol (spurious bound H₃) instead of +40 kJ/mol — magnitude AND sign of the middle-configuration cost are both missing.
2. Recoverable: yes in principle — what is missing is a positive cost for the three-centre mis-meshed configuration, which SDT owns conceptually (EMC03 mis-cancellation surplus; FARMER: meshing is the defect, so MIS-meshing is a real energetic penalty) but has never derived as a magnitude.
3. Unaccounted: the transient state where one shared electron faces two partners with neither window fully meshed — pairwise sums see only distances, not window allocation.
4. Errored premise (named): **pairwise additivity of shared-electron wells** — that three bodies interact as the sum of three pairs. The measured barrier says the three-centre term is repulsive and ~40 kJ/mol; pairwise machinery cannot produce any three-centre term.
5. Freedom: the angular-window mis-mesh cost (the same limited-poloidal-rim scarcity: the middle atom's rim window cannot serve two partners at once without a penalty).
6. Accounting: native in kind — NP10/FLM07 angular-window allocation (FARMER refinement 2) and EMC03 surplus; a bare γ·b(1−b) knob was explicitly refused. Magnitude underived.
7. Cascade: **yes** — same root as CH04-P4/XeF₄ (window allocation) and, at contact scale, CH02's missing repulsion: the short-range/three-centre closure family. Not an independent CH05 defect.

**Recovery grade: PARTIAL** — premise (pairwise additivity) and native freedom (window mis-mesh cost) named; not built. Re-open condition: NP10 angular-window law lands a quantitative window cost → re-run P2 (then P3 catalysis becomes the clean test: a partner that keeps windows meshed must lower Eₐ at fixed ΔH). Per §G.3: "barriers cannot come from wake machinery" is NOT claimed — the negative holds in the pairwise-additive class only.

## Cascade root (reported)

**ROOT-RIM (angular-window allocation, NP10/FLM07):** CH05-P2 no-saddle = the three-centre expression of the same root as CH04's misses. **ROOT-CONTACT** (CH02/NP17-alpha) is its contact-scale sibling.

## Canonical line

**Prompt completion D (P1 done and correctly down-labelled; P2 failed its committed gate; P3/P4 deferred with the dependency named) · Physics class CONVERGENCE/IDENTITY (P1) / OPEN (P2 barrier) · Recovery PARTIAL · Cascade root ROOT-RIM**
