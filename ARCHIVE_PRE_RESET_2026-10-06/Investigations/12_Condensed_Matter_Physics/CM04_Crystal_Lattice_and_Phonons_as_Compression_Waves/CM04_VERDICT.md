# CM04 — Verdict: Crystal Lattice and Phonons as Compression Waves

**Author:** J. C. Harvey, Melbourne · **Run:** 2026-07-04 · Tool `cm04_phonons.cpp` → `cm04_results.txt`
(MSVC `/std:c++20 /O2 /utf-8`, real stdout; thresholds pre-committed in `RUN_LOG.md` before coding).

## Headline

**The T³ law is a readout of lattice granularity.** Run with granularity OFF (continuous exchange),
the lattice holds C_v = 3R at every temperature — no freeze-out exists, at any T, period. Run with
the discrete-relay branch ON — (i) granular lattice, (ii) one reconnection event per wave cycle
(FLM09), (iii) action h per winding event (Law VI; FD02-earned at 0.02% with no free integer) —
the low-T exponent comes out **p = 2.9950** against a committed gate of 3.0 ± 0.1, with zero
calibrated parameters. No phonon field operator, no oscillator postulate, no ψ appears anywhere in
the chain; the occupation statistics are classical Boltzmann counting over integer relay-event
numbers (a geometric series, not a quantum partition import).

## Phase results (all numbers from `cm04_results.txt`)

| Phase | Committed gate | Result | Decision |
|---|---|---|---|
| P1 mode count → 3R | 3N exact; model limit 0.1%; band [0.95,1.10] ≥4 solids | 3N EXACT (L=2..6); 0.9995; 4/4 in band | **PASS-GATE** |
| P2 g(ω)∝ω² → T³ | slope 2.0±0.1; p=3.0±0.1; firewall first | slope 1.924; p=2.9950; continuum branch: NO T³ | **PASS-GATE**, grade capped C |
| P3 θ_D one-rule | 10% for Cu/Al/diamond/NaCl | −0.4% / −6.7% / +3.3% / **−10.1% FAIL** | 3/4 — OPEN on NaCl |
| P4 Cu crossover | 20% at 50/100/200/300 K, no refit | **−20.2% FAIL** / −7.8% / −4.4% / −4.4% | 3/4 — OPEN at 50 K |

Earned numbers (not re-exposed inputs): **θ_D(Cu) = 341.8 K vs 343 K observed (−0.4%)** and
**θ_D(diamond) = 2304 K vs 2230 K (+3.3%)** from measured sound speeds + one geometric rule
(ℏv_D/k_B)(6π²n)^{1/3} — the same rule, no per-solid multiplier; and the **p = 2.995** exponent.

## §G mirror (faith ledger)

- On faith: **action-per-reconnection = h for compression waves** — named, load-bearing, and the
  reason P2 is graded C not A. Re-open condition: an independent earn of the Law VI extension to
  relay waves (the FD02 shape of proof, applied to a compression mode). Ledger, not legislation.
- No rival axiom sits in any kill gate: every gate above traces to a measured anchor
  (calorimetric θ_D, tabulated C_p, 3R).

## FAILURE RECOVERY (§D seven questions — P3 NaCl / Pb exhibit, and P4 50 K)

**P3 (NaCl −10.1%; exhibit Pb −28.7%):**
1. **Why:** predicted θ_D low — room-temperature polycrystalline v_L/v_T understate the T→0
   directional stiffness that calorimetric θ_D measures; Pb adds extreme elastic anisotropy
   (a two-speed 1/v³ average is a poor stand-in there).
2. **Recoverable?** Yes — in the input class, not the mechanism.
3. **Unaccounted:** temperature dependence of elastic constants; single-crystal anisotropy.
4. **Errored premise:** "room-T polycrystalline speeds are an adequate stand-in for the T→0
   directional stiffness." Input-fidelity premise, not an SDT-mechanism premise.
5. **Freedom:** low-T single-crystal C_ij tensors with a full directional average.
6. **Accounted natively?** Yes — better measured input, independently tabulated; it is data, not a knob.
7. **Cascade:** local (input fidelity). Does NOT share the ROOT-A premise below.

**P4 (50 K −20.2%):**
1–4. Single constant θ_D compresses the real mode spectrum; Cu's effective θ_D(T) droops ~10%
   near 30–80 K, so the one-θ curve under-sits the data exactly there. Premise: "one θ fits all T."
5–6. Freedom: the real g(ω) (inelastic-neutron dispersion) in place of the sphere-with-cutoff —
   measured input, not a knob. 7. Cascade: same approximation family as P3 (spectrum compression),
   independent of ROOT-A.

**Recovery grade: PARTIAL** (routes named and natively justified; not executed — no refit was
performed in this run and none will be claimed).

## Generative questions logged (prompt §10)

1. The −10% (NaCl) and −29% (Pb) misses are *signed* — always low. Is the low-T stiffening of the
   relay channel itself an SDT-computable correction (GOM05 hinge-closing under thermal contraction)?
2. The g(ω) slope 1.924 (not 2.000) on a finite periodic grid: the deficit is the BZ-corner bend —
   the same short-k bend CM05's roton question points at. One curve, two phenomena?

---

> **Prompt completion C · Physics class CONVERGENCE · Recovery PARTIAL · Cascade root ROOT-A
> (action-per-event = h beyond vortex winding — Law VI extension; grade-cap only, no gate fails
> trace to it)**
