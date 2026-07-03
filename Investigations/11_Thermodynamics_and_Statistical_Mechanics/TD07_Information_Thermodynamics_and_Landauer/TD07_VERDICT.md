# TD07 — Verdict: Information Thermodynamics and Landauer

**Dual verdict: Prompt completion B · Physics class NULL-SDT-CONTENT/CONVERGENCE (with one scoped lattice-flavoured overhead result).**
**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td07_landauer_relay.cpp` → `results.txt` (exit 0).

## What was run

Joint microcanonical register + TD01 bath (N=2000 cells, E=20000 quanta, kT = ε/ln(1+N/E) =
10.492 ε), symmetric proposals only — **no Boltzmann factor input anywhere**; p_R comes from
counting (W_b ratios) and independently from dynamics.

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1 exact ledger | W_qs/(kT ln2) ±1% | 0.9995 | PASS |
| P1 sim occupation | p_R at 4 levels within 3σ of counting | worst 0.05σ | PASS |
| P1 finite-time | W monotone with speed; slowest ≥ bound | 7.74 / 7.43 / 7.51 ε, all ≥ 7.27 | PASS |
| P2 demon exact | net = extract − erase ≤ 0 | −0.4995 ε = −[p(0)−p(80)]·ε exactly | PASS |
| P2 demon sim | net ≤ 0 at 3 speeds (3 SE) | −0.78 / −0.71 / −0.46 ε | PASS |
| P3 partial erasure | Q vs kT[ln2 − H(p)] ± 1.5% | worst 0.027% over 5 targets | PASS |
| P4 delete test | k_BT × pure number | holds | PASS |

**Incidents (documented in RUN_LOG):**
1. **ADJ-0 (pre-compile):** drafted P3 compared the *work* W = ΔF to kT[ln2 − H]; the
   Landauer-form quantity for partial erasure is the *heat* Q = W − ΔU_register. Category error
   caught before any run.
2. **RUN 1 fired the finite-time gate with W_fast = 6.81 < kT ln2.** Traced to premise, not
   physics: trajectories started from an UNMIXED bath (every cell exactly 10 quanta). A
   fluctuation-free bath has no rich cells, so L→R re-entry is kinetically blocked while R→L
   exit is always allowed — the register erases "for cheap" against a non-equilibrium bath,
   which is a work resource and voids the bound's premise. Fix: 5e5-tick bath pre-mix (ADJ-1,
   gates unchanged). Post-fix all speeds sit above the bound. This fired-and-traced event is
   itself the cleanest demonstration in the suite that Landauer's bound is a statement about
   *equilibrium* baths — the "violation" vanished exactly when the premise was restored.
3. Slow-limit note: a stepped protocol's quasi-static work is the left Riemann sum
   Σp(E) = 7.52 ε, not the trapezoid 7.27 ε; measured slow runs center there. Same origin as
   the demon deficit (below).

## The demon closure (the prompt's load-bearing content)

Extraction (lower a known state) and erasure (raise to reset) are the *same* counted ledger;
the stepped cycle nets **−ε·[p_R(0) − p_R(E_max)] ≈ −0.5 ε exactly** (≤ 0), and finite speed
only makes it worse. No Second-Law loophole exists in the relay model: H4 of TD01 is discharged.

**Scoped lattice-flavoured result (not oversold):** because the register level can only move in
integer multiples of the relay quantum ε, *this protocol class* strictly loses ~0.5 ε per cycle
even quasi-statically (~6.9% of kT ln2 at kT = 10.5 ε). The deficit vanishes as ε/kT → 0 and a
continuous-protocol demon closes at exactly 0 — so the claim is: **on a lattice with quantised
throughput, stepped-potential demons cannot even break even.** This is the one statement in TD07
that depends on the lattice's discreteness; it is a modest overhead bound, not a new law.

## Physics class: NULL-SDT-CONTENT / CONVERGENCE

The prompt itself conceded kT ln2 is near-definitional given TD01+TD02, and the run confirms it:
Landauer, the demon ledger, and the Bennett reversible limit are theorems of counting + energy
bookkeeping. They were executed here without importing an ensemble (worth having: the whole
chain is counting-native), but nothing except the ε-discreteness note would change on a non-SDT
substrate. Q = kT[ln2 − H(p)] to 0.03% is generic stochastic thermodynamics.

**Earned:** demon closed on the relay lattice with exact ledgers; the ε-step overhead bound;
the equilibrium-bath premise demonstrated by a real fired falsifier. **Owed:** prompt Q2
(minimum erase time/power from the tick — untouched); any claim that the overhead bound applies
beyond stepped protocols (it does not, and none is made).

**Certification:** P1–P3 COMPUTED (exact counting + dynamics); zero CALIBRATED; k_B unit-bridge only.

## HUNTER §D — seven questions on the NULL-SDT landing

1. **Why:** Landauer, the demon ledger, and the Bennett limit follow from counting + energy
   conservation on ANY substrate; every gate here would pass identically on a non-SDT bath.
2. **Recoverable?** NO RECOVERY for the core — and that is the correct closure, not a defeat:
   substrate-independent mathematics cannot be made NATIVE, only executed honestly (done) or
   falsely decorated (refused).
3. **Failed to account for:** nothing within scope; the prompt itself pre-declared the
   near-definitional character. What remains unaccounted is prompt Q2 (a minimum erase
   time/power from the relay tick) — untouched, OPEN.
4. **Errored premise:** the suite hope that information thermodynamics would carry SDT-specific
   content; it carries SDT-*consistency* content (throughput conservation forbids the free lunch).
5. **Freedom:** the one lattice-dependent element found is the ε-step overhead
   (net = −ε·Δp per stepped cycle) — earned, scoped, and already banked.
6. **Accounting:** ε is native (Law I); the overhead bound is derived from it exactly.
7. **Cascade:** from TD-ROOT-1 (equilibrium counting is substrate-blind); the ε-overhead also
   touches TD-ROOT-3 (what ε physically is).

**Prompt completion B · Physics class NULL-SDT-CONTENT/CONVERGENCE (demon closed; ε-step overhead earned, scoped) · Recovery NO RECOVERY (core is substrate-independent — closure by acceptance); Q2 OPEN · Cascade root TD-ROOT-1 (+ TD-ROOT-3 for the ε overhead)**
