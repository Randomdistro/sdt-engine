# PM05 — Verdict: Magnetic Reconnection and Solar Flares from Wake Topology

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05
**Tool:** `pm05_reconnection.cpp` (MSVC, real run, exit 0) → `pm05_results.txt`
**Pre-commitments:** `RUN_LOG.md` (target D committed up front; no reconnection dynamics simulated
or claimed — the required 3-D lattice wake-topology solver does not exist).

---

## 1. Deciding metrics

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | stored throughput | U = ½ρ_a∫\|w\|² computed (d = 8/4/2: 0.246/0.151/0.062 native); U_int < 0 deepening on approach — the anti-parallel sheet configuration is the low-U state whose surplus a topology change can dump | CONVERGENCE (native reading of B²/2µ₀; conversion = ORPHAN-1) |
| P2 | ledger + snap | ledger exact by construction (**pre-flagged as the trivial bookkeeping the prompt's anti-tautology names — not claimed as a result**); **the SNAP is OPEN — missing tool named: 3-D lattice wake-topology solver (ROOT-SIM class)** | OPEN |
| P3 slow | 1/√S | assembled from PM07's *measured* slip law (leak ∝ η, 0.943) + sheet continuity; **pre-classed LINGUISTIC/CONVERGENCE (textbook chain, renamed nouns — said so)**; table shows the 4–6 order fast-gap at coronal S honestly | LINGUISTIC/CONVERGENCE |
| P3 fast | ~0.1 v_A | **OPEN.** Named native candidate (FLM14 ADJ-7): topology snap = **constraint-channel release event** in a gear-locked flux structure — rate geometry-fixed, weakly S-dependent. Yields the falsifiable divergence from resistive MHD the prompt's Q1 asks for (plateau ~flat in S). CANDIDATE ONLY | OPEN + named candidate |
| P4 flare | 10³¹–10³² erg | band 4.3e31–4.5e32 erg with pre-fixed OBSERVED inputs — **overlaps, order-correct** | CONVERGENCE (OBSERVED inputs) |
| P4 CME | 10²–10³ km/s | **FAIL, recorded**: v_A band 4.4e3–2.1e4 km/s, entirely above gate (ADJ-1: only the printed classification was corrected; numbers untouched) | honest FAIL |
| T4 | ∇·B through snap | structural: quanta removal keeps w a superposition of curls (PM01 P2c identity; pre-flagged) | IDENTITY |

## 2. §D seven questions

**(a) On the P4 CME FAIL:**
1. **Why?** v_A(B=0.02–0.03 T, n=1e15–1e16) = 4.4e3–2.1e4 km/s; gate 1e2–1e3; miss by 0.6–1.3 orders.
2. **Recoverable?** Plausibly: the errored quantity is the *identification*, not the energy.
3. **Failed to account for:** mass loading — the released throughput accelerates a CME mass far
   exceeding the sheet plasma; v_launch = √(2f·ΔU/M_CME) ≠ v_A.
4. **Errored premise:** "CME launch speed = source-region v_A" (the prompt's H3 shorthand).
5. **Freedom:** the release partition fraction f and loaded mass M_CME.
6. **Accounting:** f is exactly what the snap dynamics would fix — blocked behind the same missing
   solver; M_CME is OBSERVED. Not a bare knob, but not payable today.
7. **Cascade?** YES — same root as P2/P3-fast: the missing topology solver.
**Recovery: PARTIAL.**

**(b) On the P2/P3-fast OPEN:** premise class (§G-3): diffusion-only (pulse-channel-only) transport
of wake topology. Re-open condition: the ADJ-7 constraint channel implemented in a 3-D lattice
wake-topology solver (ROOT-SIM class — the same tool NP17/PPT09 name as their linchpin). Until it
exists, "fast reconnection" is SDT's open problem exactly as it is resistive MHD's — stated without
foreclosure, with SDT's candidate carrying one falsifiable signature (S-independence of the plateau)
that MHD's anomalous-resistivity patch does not share.

**§G-1 faith ledger:** the Gaussian-core bundle profile (P1 geometry) is a modelling choice, named;
the observed fast rate ~0.1 v_A is used as a measured anchor, not as a Petschek endorsement (§B).

## 3. Verdict

> **Prompt completion D** · **Physics class** OPEN (snap, fast rate — with the ADJ-7 constraint-
> channel candidate and its falsifiable S-independence signature) / LINGUISTIC-CONVERGENCE (slow
> branch, said so) / CONVERGENCE (stored energy, flare order) / honest FAIL (CME = v_A
> identification) · **Recovery** PARTIAL (all routes named; none payable without the solver) ·
> **Cascade root** ROOTSIM-lattice (3-D wake-topology solver; shared with APS04 Phase-2, PM03
> rebuild, NP17/PPT09 linchpin) + ORPHAN-1/HG-1 for the energy conversion.
