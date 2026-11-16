# TD01 (entropy and the arrow of time from lattice microstates) — blank-slate assessment (2026-10-08)

> **Correction 2026-10-10 (Harvey):** the "arrow" framing of this record (D5, D4, §4 thesis row, §5 items 1 and 4) imports time as a primitive; SDT has movement (travel, circulate, rebound, scatter), not time, and no direction of movement to reverse. I should have listed that as a premise defect (D-class) here and did not. Numbers (V1, V2, Phase 1, R1–R3) stand as counts of arrangements and of passes of a rule; the arrow reading is withdrawn. See the correction block in `TD01_EXPANSION_2026-10-09.md`.

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`, with the method of 2026-10-07. Instrument `td01_reset_1.cpp` (registration in its header, fixed before the run); output `td01_reset_1_results.txt`. Single pass, no re-run, no amendment.

## 0. Inputs read and exposure
Read: `TD01/PROMPT.md` (the first 95 lines, through the verdict table and outputs; the closing list of generated questions was not read); `laws.hpp` (`measured::k_B`). Not read: `TD01_VERDICT_DIRECT_2026-07-26.md`, `td01_microstates.cpp`, `td01_rerun_2026-07-26.txt`. Exposure: the prompt states that Phase 1 "cannot fail" and caps at grade C, and that Phase 2 is the falsifiable core; it names the Stosszahlansatz as the assumption to avoid. No earlier outcome is given in the part read.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | Phase 1 (S = k_B ln W with W from stars and bars, Stirling, extensivity) is a definition and a counting identity; the prompt says so. |
| D2 | gating | Phase 2 asks for the arrow from "the bare relay update (FLM02 GPI)", without molecular chaos and without hand coarse-graining. The relay rule is not written in the prompt, and the outcome depends on it (§3). |
| D3 | gating | The observable S of a single trajectory is not defined: for one microstate the count of compatible microstates needs a macrostate, i.e. a coarse-graining; for a distribution over microstates the Shannon entropy needs the distribution (an ensemble). The prompt's "W proxy or exact count" does not say which. |
| D4 | gating | The success criterion "⟨S⟩ non-decreasing, net ΔS ≥ 0" is satisfied by an entropy that is constant; a stronger reading (approach to the maximum) is registered here. |
| D5 | premise | The stated aim is the arrow without an imported chaos assumption; any symmetric stochastic rule supplies the sign of dS/dt by the symmetry of its transition matrix (a theorem), so no chaos assumption is needed there, but randomness is. |
No downgrade is made on agreement grounds.

## 2. The five questions
**1. What do we not know?** What relay rule the lattice follows at each tick and whether the entropy of a lattice state, defined by a stated observable, rises under it. The arrow is a statement about a rule and an observable together.
**2. Why does it matter?** TD02 (temperature as the derivative of S with respect to E) and everything above it take S = k_B ln W as native; the thermodynamic arrow is said to be the same asymmetry as the cosmological one.
**3. By what methods?** (M1) Exact enumeration of a small lattice (7 cells, 10 quanta: 8008 microstates). (M2) Evolve the exact distribution under a symmetric stochastic rule (R1). (M3) Evolve a single trajectory under two deterministic rules (R2 reversible swap; R3 one-way transfer) and track the macro-entropy of a stated coarse-graining. (M4) Register what counts as an arrow before running.
**4. What would prove us wrong?** (a) Indicators: an observable that cannot decrease by construction presented as a test; an arrow that appears only after coarse-graining chosen to produce it. (b) Mathematics: no net decrease and approach to the maximum (S/S_max ≥ 0.9). (c) What it breaks: if the bare deterministic relay shows no arrow, the arrow needs a native source other than the update (randomness, irreversibility, coarse-graining by the observer, or the initial condition).
**5. Done when** the arrow is tested under stated rules with a stated observable and the dependence on both is recorded, and the native relay rule is named or flagged open.

## 3. Results (COMPUTED)
- **Validations met.** V1: stars-and-bars equals the brute-force count for (N, E) = (4, 3): 20; (5, 6): 210; (7, 10): 8008. V2: the R1 transition matrix for N = 5, E = 4 (70 states) is symmetric (max |P − Pᵀ| = 0) with unit row sums (max error 1.1×10⁻¹⁶).
- **Phase 1 (gates met).** ln W(E = 1000, N = 50) = 195.1195; leading Stirling form 201.0163 (error 3.02%, gate 5%); ln W(2000, 100) = 395.7901, ratio to 2 ln W(1000, 50) = 1.0142 (gate ±5%); ln W is monotone in E (24.864, 91.704, 195.120 for E = 10, 100, 1000 at N = 50); S(1000, 50) = 2.6939×10⁻²¹ J/K. CONSTRUCTION (definition plus Stirling).
- **R1, symmetric stochastic exchange (ring, exact distribution of 8008 states, hot start: all 10 quanta in one cell).** S(1) = 0.5091, S(10) = 2.6313, S(100) = 8.0172, S(1000) = 8.9882, S(10⁴) = 8.9882 = ln 8008 = S_eq; S/S_eq = 1.000000; no tick with a decrease (smallest one-tick change −1.2×10⁻¹³, rounding). The criterion is met, and the sign of dS/dt is guaranteed by the symmetry of the transition matrix (V2): the class "S decreases" is empty for this rule.
- **R2, deterministic reversible swap (open chain, single trajectory, macrostate = block sums over (0,1), (2,3), (4,5), (6)).** ln W_macro: start 2.3979, minimum 0.0000, maximum 2.3979, mean over 10⁴ ticks 2.0555, final 2.3979; maximum over all states 4.3820; 714 one-tick decreases; net change 0.0000; mean/max = 0.4691. No arrow: the contents move ballistically and bounce.
- **R3, deterministic richer-to-poorer transfer (open chain).** ln W_macro: start 2.3979, rises to 3.4657 and stays there (minimum 2.3979, maximum 3.4657, mean 3.4651, final 3.4657); maximum over all states 4.3820; final/max = 0.7909; no decrease; net change +1.0678; mean/max = 0.7907, below the registered 0.9: the entropy rises to a frozen state (differences between neighbours ≤ 1), not to the maximum of the observable.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Phase 1 | **G3, CONSTRUCTION** | a definition and a counting identity; gates met |
| Phase 2, R1 | **G3, shared-input** | arrow shown; contaminating input: the randomness of the rule and the symmetry of its transition matrix, entering at the rule definition (`td01_reset_1.cpp`, the R1 block); the class "decrease" is empty |
| Phase 2, R2 | **G1, excluded for this rule** | no arrow for a deterministic reversible exchange: the macro-entropy returns to its start |
| Phase 2, R3 | **G2, open** | a one-way rule builds the sign into the update and freezes below the maximum |
| The thesis "the arrow emerges from the native relay update" | **G2, open** | the native rule is not specified; it holds for a symmetric stochastic rule (given randomness), fails for a reversible deterministic rule, and is built in by an irreversible one |
| Phase 3 (ideal gas) | deferred to TD03 | as the prompt allows |

## 5. Direction
1. State the native relay rule in SDT terms: the repository's principle is that a relay passes impulses deterministically in parallel and that movement has no sink; a deterministic reversible rule leaves the fine-grained entropy constant (R2 shows the macro-entropy has no trend either), so the arrow needs a native source: a stated randomness, a stated irreversible element, the coarse-graining forced by observers made of the same medium, or the initial condition.
2. Define the observable (ensemble or macrostate) before running; register the macrostate partition and show the result does not depend on the partition within a stated family.
3. Extend R2 to a reversible rule that mixes (a reversible cellular automaton), to test whether a reversible deterministic update with a stated coarse-graining yields an arrow with recurrences on the expected time scale.
4. The cosmological link (the arrow as one asymmetry) rests on the initial low-entropy state; state it as an input of the cyclic picture, with its origin.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
