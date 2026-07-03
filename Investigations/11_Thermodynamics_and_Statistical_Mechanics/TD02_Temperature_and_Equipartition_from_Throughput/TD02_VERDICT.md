# TD02 — Verdict: Temperature and Equipartition from Throughput

**Dual verdict: Prompt completion A · Physics class CONVERGENCE.**
**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td02_throughput_temperature.cpp` → `results.txt` (exit 0).

## What was run

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1 concordance | \|β_budget − β_count\|/β < 1e-3 | 1.32e-4 at N=8000; gap shown ∝ 1/N exactly (discretisation of ∂S/∂E) | PASS |
| P1 T_kin=T_ent | < 1e-3 classical regime | 5e-4 at ⟨j⟩=1000 | PASS |
| P2 equipartition | RMS per-DoF dev < 1%, init-independent, MB marginal | 0.69% RMS both inits; kurtosis 2.988/2.989 | PASS |
| P3 Boltzmann native | ln p_j linear R²>0.999, slope = −β_budget ±1%, no reservoir | exact marginal R²=0.999994, slope gap 0.52%; dynamics R²=0.9999 | PASS |
| P4 delete test | everything = k_B × pure number | holds; k_B enters only as kelvin bridge | PASS |
| T4 firewall | no S_res(E−ε) expansion anywhere | **NOT FIRED** — all three P3 routes are counting/dynamics | PASS |

**Run-1 incident (documented per protocol):** first run gated FAIL at P1 with a constant
2.00e-3 gap. Traced to premise: the central-difference ∂S/∂E carries a finite-size error of
exactly 1/N; my committed 1e-3 gate at N=500 could never pass. Pivot applied per the committed
table (larger lattice — allowed numerics; **threshold unchanged**), and the 1/N scaling was
demonstrated explicitly (gap×N = 1.000 for N=250…8000) so the concordance is proven in the
thermodynamic limit, not asserted at one size.

## The firewall outcome (the load-bearing claim)

The exponential occupation was obtained three ways, none of which instantiates a canonical
reservoir or a predefined `T`:

1. **Lagrange:** maximise ln[N!/Πn_j!] at fixed cell count and fixed total throughput → n_j ∝ e^(−βj), β = ln(1+N/E).
2. **Exact complement count:** p_j = W(E−j, N−1)/W(E, N) under TD01's uniform microstate measure — computed exactly, no Taylor expansion; β read off *after* the fact and it equals the P1 budget multiplier to 0.52%.
3. **Dynamics:** a symmetric one-quantum relay exchange (doubly stochastic → uniform stationary measure) reproduces the same occupancy histogram (R² = 0.9999).

Judgement call, flagged openly: route 2 counts the rest of the lattice, which a hostile reader
could call "a reservoir". It is not the forbidden move — the forbidden move is expanding
S_res(E−ε) around a *presupposed* temperature; here the count is exact, T is an output, and
route 1/route 3 stand without it. The firewall is honestly cleared. **Downstream effect: TD03's
"no ensemble" inheritance and TD06's occupation factor may cite TD02 as NATIVE-counting, and
SAR02's "LINGUISTIC-BORROW" flag on the Boltzmann occupation is now discharged by this route.**

## Physics class: CONVERGENCE — where SDT did and did not do work

The decisive question: which step would break if the substrate were not an SDT relay lattice?
**None.** The derivation is Boltzmann's 1877 most-probable-distribution combinatorics executed
honestly on a generic quanta-on-cells model. No ℓ_P, no occlusion cross-section, no FLM08
coordination number enters any formula; `k_B` is a unit bridge, exactly as the prompt says.
SDT supplies the *ontology* (quanta = disordered relay throughput; T = mean disordered
throughput per DoF) — a re-narration, not a computation. Hence CONVERGENCE, not NATIVE,
even though every numerical gate passed and the anti-tautology firewall did not fire.

What TD02 **earned**: the suite may now use exp(−ε/k_BT) without importing an ensemble — the
factor is an output of counting + symmetric relay dynamics (this is real: SAR02 could not say
this and flagged it). What is **owed** (OPEN, logged as generative):

1. An SDT-specific *departure*: the freeze-out curve T_kin/T_ent = ⟨j⟩ln(1+1/⟨j⟩) is the
   Einstein-oscillator form from throughput discreteness alone — at what physical scale does ε
   sit, and is c_v suppression at low T *the lattice gap* rather than QM? (Prompt Q3 — untested.)
2. Whether FLM08 tetrahedral frustration perturbs equipartition (Q2 — untested here; TD03
   addresses the rank-2 part).
3. β as a shadow price connecting to TD04's ∇T (Q1 — see TD04).

**Certification:** P1–P3 COMPUTED; c_v = 3/2 k_B flagged near-definitional; zero CALIBRATED.
**Earned vs owed: earned the ensemble-free occupation factor for the suite; owed any lattice-specific fingerprint that would upgrade CONVERGENCE to NATIVE.**

## HUNTER §D — seven questions on the CONVERGENCE (non-NATIVE) landing

1. **Why:** every formula in the chain (β = ln(1+N/E), geometric marginal, ½k_BT) depends only
   on counting + k_B; no ℓ_P, occlusion R², or FLM08 geometry enters anywhere.
2. **Recoverable?** PARTIAL — routes named, not executed.
3. **Failed to account for:** where ε physically sits. The freeze-out curve turns on at ⟨j⟩ ~ 1,
   i.e. at the ε scale — locating that scale is exactly what would make the result falsifiably SDT.
4. **Errored premise:** that "quanta-on-cells" is SDT-specific. It is Boltzmann's generic 1877
   model; SDT enters only as ontology (a relabel, per the contamination audit's translation test).
5. **Freedom that fixes it:** pin ε to Law I (ε = u₀ℓ_P³) and derive one observable where
   discreteness or FLM08 frustration shifts a thermodynamic number.
6. **Accounting for the freedom:** ε is a native laws.hpp quantity, not a knob — but no
   observable consequence was derived here. Owed, not plugged.
7. **Cascade:** yes — shared with TD03/TD04/TD07 mechanisms and TD06's occupation: one root,
   the ε-scale invisibility of lattice structure in equilibrium counting (TD-ROOT-1).

**Prompt completion A · Physics class CONVERGENCE · Recovery PARTIAL (freedom named: physical ε scale + FLM08 fingerprint, not yet derived) · Cascade root TD-ROOT-1 (ε-scale invisibility of lattice structure in equilibrium counting)**
