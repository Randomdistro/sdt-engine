# NP11: Neutron Lifetime from Lattice Topology — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on canon flags.
> **Run:** Pre-commit in `RUN_LOG.md`; four-root sort (§⑨.E) on every FAIL.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **What sets the ~880 s neutron lifetime** — i.e. the *rate* of the topological rearrangement (proton + internal electron → free proton + shed W=1 torus + open winding). The timescale is a **barrier depth B** (SCT regime II, τ ~ e^B), and *what sets B is SDT's analogue of G_F* — the deep open.
2. **Why does it matter?** — β-decay as **topology rearrangement**, not quark transformation. Ties the neutron (metastable, regime II) to proton stability (regime I, τ ~ 2^d_min). The 1.83c counter-seat already gives Q_β = 0.782 MeV and μ_n sign+order (NP20/NP15) — the *rate* is the missing third number from the same seat.
3. **How will we find out?** — Three routes (§④): A the barrier tunnelling rate (SCT B); B does the 1.83c seat that fixes Q_β also fix the rate?; C the beam/bottle 8.6 s split as a *lattice-coupling* prediction.
4. **What would prove us wrong?** — §⑧: if B only lands 880 s when tuned (bare knob, not a native span), OPEN honestly; if beam/bottle is flat under boundary change, the SDT prediction fails.
5. **How will we know we're done?** — Dual verdict. Order-of-magnitude of τ from a *native* barrier, the decay products as topology, and a committed beam/bottle sign.

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| Neutron beam lifetime | 888.0 ± 2.0 s | Yue 2013 |
| Neutron bottle lifetime | 878.4 ± 0.5 s | Serebrov 2018 |
| Beam–bottle discrepancy | ~8.6 s (4.6σ) | the "puzzle" |
| Q_β (n→p+e+ν̄) | 0.782 MeV | m_n−m_p−m_e (NP20: from 1.83c seat) |
| Neutron = proton + internal electron | NP17 | **not a bare W=3 trefoil** |

## SDT Interpretation (updated to NP17 — neutron = p + internal e⁻)

β-decay is **not** a quark transformation. The neutron is a proton with an **internal (shared) electron** (NP17), metastable:
1. it lacks the free ℓ=1 wake stabilisation of the bare proton;
2. the internal electron is expelled — the configuration relaxes to free proton + W=1 torus (electron) + open winding (antineutrino) + KE;
3. **lifetime = 1/(rearrangement rate).** The rate is a barrier crossing: τ ~ e^B (SCT regime II), where B is the depth of the topological hold.

> **Movement-only framing:** the neutron is a *held* configuration (BECOME — closed-path matter banking movement). Decay is the hold releasing downhill (p + e + ν̄). "89" (SCT) is the barrier **depth**, not a count. The tug-of-war: hold (repair/re-form) vs pull (downhill to p+e). Restate any "energy barrier" as a span the internal electron must cross before it enters a phase.

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| neutron = p + internal e | NP17 | **the model** (supersedes bare W=3) | ✔ |
| Q_β = 0.782 MeV from 1.83c seat | NP20 | UPSTREAM (same seat as rate?) | ✔ |
| μ_n sign+order from 1.83c | NP15 | sibling (same seat) | ✔ |
| SCT regime II, τ~e^B, "89"=B | Theory_SCT | **barrier framework** (Route A) | ✔ |
| what sets B = SDT's G_F | Theory_SCT (deep OPEN) | the irreducible gap | ⚠ open |
| beam/bottle boundary conditions | measured | Route C (falsifiable) | ✔ |

## ④ Strategy — three routes

**Route A — Barrier rate (SCT regime II).** Compute τ ~ e^B from the topological hold depth B of the internal-electron configuration. *Native seed:* B must come from the trefoil+internal-e geometry, not a fitted number. *Metric:* τ order-of-magnitude (10²–10³ s) from B with no tuned prefactor. *Expected:* PARTIAL — B is the deep open (SDT's G_F); honest floor is "τ ~ e^B with B named but not yet derived."
**Route B — The shared seat.** The 1.83c counter-seat fixes Q_β = 0.782 and μ_n. Test whether the *same* seat's release dynamics set the rate (pricing map E(z) vs γ, NP20's "required 1.531" ≡ γ₀−1). *Metric:* rate consistent with the seat that already pays Q_β. Cross-gate: must not break NP15 μ_n or NP20 Q_β.
**Route C — Beam/bottle as lattice coupling (the falsifiable prediction).** SDT: coupling to container walls (bottle) modifies the transition rate vs free space (beam). *Pre-commit the SIGN:* does wall-coupling raise or lower the rate (bottle τ shorter → higher rate)? Bottle 878 < beam 888 → bottle decays faster → wall-coupling *raises* the rate. Commit this before modelling. *Rival:* dark-decay n→p+χ. SDT predicts a boundary-dependent rate; dark-decay predicts a fixed missing branch.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | τ ~ e^B, B from topology gives 10²–10³ s | root-1 (B needs tuning) → OPEN as G_F-analogue |
| T2 | rate consistent with the 1.83c Q_β seat | root-2 (seat) if the seat can't also price rate |
| T3 | beam/bottle sign = wall-coupling raises rate | root-1 if SDT predicts wrong sign |
| T4 | products = p + W=1 torus + open winding (topology) | root-1 |
| T5 | "internal circulation temperature" is a native span, not imported thermal QM | root-4 (contraband) |

## ⑨.E Four-root sort
root-1 claim false (B/rate not native → OPEN as SDT's G_F) · root-2 dependency (1.83c seat, NP17) · root-3 prompt under-specified · root-4 contraband (thermal-QM barrier). The "what sets B" gap is a **named OPEN closure** (§D), not a kill.

## Brainstorm — overlooked factors
- **The rate is the third number from one seat.** Q_β (0.782), μ_n (−1.913), and τ (880 s) may all issue from the 1.83c counter-seat. Two are on file; the rate is the test of whether the seat is the whole story.
- **B = SDT's G_F.** Weak-decay rates in the SM ride G_F; SDT's B (barrier depth) is the same role. Deriving B is the make-or-break — say so; do not fake it with a fitted prefactor.
- **Beam/bottle is a live decidable** — SDT's boundary-dependence vs dark-decay's fixed branch. This is a real experiment SDT can call; commit the sign now (bottle faster).
- **Free neutron = exposed triton remnant** (ATOMICUS): the "free neutron" isn't fundamental — it's an unshielded configuration. Its instability is the grammar's statement that free neutrons are forbidden in stable nuclei.

## ⑤ Success / ⑥ Outputs
Class A: τ order-of-magnitude from native B, products as topology, beam/bottle sign committed and matched. **Honest floor (likely):** τ ~ e^B with B named as SDT's G_F-analogue (deep OPEN), products + beam/bottle prediction on record. Outputs: `RUN_LOG.md`, `np11_neutron_lifetime.cpp`, `NP11_DERIVATION.md`, `NP11_VERDICT.md`.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — NP11 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 (no tuned prefactor on the rate)
- Routes: A barrier B(SCT) · B shared 1.83c seat · C beam/bottle sign
- Beam/bottle SIGN committed before modelling: bottle faster (wall-coupling raises rate) [y/n]
- Neighbours to protect: NP20 Q_β=0.782, NP15 μ_n
- Forbidden: fitted rate prefactor; thermal-QM barrier import; change beam/bottle sign post-run
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| B needs a tuned prefactor | name B as SDT's G_F (OPEN closure) | ship OPEN honest | fit the prefactor, call it derived |
| seat can't price the rate | Route A barrier only | OPEN | force the seat |
| beam/bottle sign wrong | trace mechanism (root-1) | KILL the wall-coupling claim | flip sign post-hoc |
| uses thermal QM T | recast as native span | OPEN | import kT-as-thermal-bath |

**Disallowed:** post-hoc tolerance widening · fitted rate prefactor · thermal-QM barrier · changing the committed beam/bottle sign.

---

*NP11 · §K-deepened 2026-07-13 · neutron = p + internal e (NP17); τ ~ e^B with B = SDT's G_F-analogue (deep OPEN); rate is the third number from the 1.83c seat; beam/bottle sign committed as a falsifiable SDT prediction.*

---

## Pre-registration (2026-10-03, before the instrument exists)

**Method note.** Rounds are registered as they are designed and every round, including those
that fail, stays in the attempt ledger of `NP11_ASSESSMENT.md`. The five-line commitments
block above (⑩) is answered here: calibrated budget 0; no fitted rate prefactor; no thermal
barrier import; the beam/bottle sign statement is treated as below.

**Premise update.** The seed's data table (beam 888.0 ± 2.0 s, bottle 878.4 ± 0.5 s) predates
a beam measurement from J-PARC (2024 result): 877.2 ± 1.7 (stat) +4.0/−3.6 (sys) s, consistent
with the bottle value and in tension with the earlier beams. Inputs used (MEASURED-INPUT,
transcribed from secondary summaries; primary papers not retrieved):
bottle 877.8 ± 0.3 s; earlier beams 888.1 ± 2.0 s; J-PARC beam 877.2 s with σ = (1.7² + 3.8²)^½
(asymmetric systematic symmetrised). The earlier table is retained for reference.

**Instrument validation (before any round).** (V1) Weighted-mean and difference arithmetic
reproduces hand-computed values for a two-measurement test case. (V2) `ln` and clock
constants: ħ/(m_ec²) from engine constants equals 1.2880e-21 s to 1e-4 and R_p/c equals
2.807e-24 s to 1e-3. (V3) The null model of the census (below) returns the analytic expected
hit count for a uniform-density test grid to 2%.

**Part C — beam/bottle (data audit, arithmetic on the inputs above).** Differences and their
significance for: earlier beam − bottle; J-PARC − bottle; J-PARC − earlier beam; all beams
combined − bottle.
- Route C of the seed says free-flight beams measure the free-space rate and bottles a
  wall-modified rate, so beam-type results should agree with each other.
- *Predicted before running:* earlier beam − bottle about 5σ; J-PARC − bottle consistent with
  zero; J-PARC − earlier beam about 2.4σ.
- *Rejection criterion (populated):* the wall-coupling explanation alone is disfavoured if the
  two beam-type results disagree by more than 2σ. Predicted met; "excluded" is reserved for
  more than 3σ, so the expected outcome is disfavoured, not excluded.
- *Status of the seed's sign commitment:* "bottle faster" was written with 888 against 878 in
  view, so it is a retrodiction, not a prediction. Recorded as such.
- The size of the effect to be explained is ln(888.1/877.8) = 0.0117, a 1.2% change in rate.

**Part A1 — attempt frequency (computation, no fit).** B_req(t) = ln(τ/t) for τ = 877.8 s over a
registered clock list from engine constants: R_p/c; the seat rotation period 2πR_p/v_phase
(`law_VI::traction::v_phase_proton_surface`); ħ/(m_pc²); ħ/(m_ec²); r_e/c (r_e = α²a₀);
ℓ_P/c; the Bohr period 2πa₀/(αc). Reported with the spread across the five nuclear-scale
clocks and the ratio of that spread to the beam–bottle difference in B (0.0117).
No criterion: the result is arithmetic and its purpose is to size the ambiguity.

**Part A2 — look-elsewhere census.** Construction grammar registered now: B_c = k·ln X, with
k = 1…16 and X in {1/α, m_p/m_e, 4π, 2π, π, γ₀, v_phase/c}, where γ₀ = (m_n − m_p)/m_e
(the electron's Lorentz factor at the Q_β seat) and v_phase/c = 1.831. 112 constructions,
7 clocks. A hit is |B_c − B_req| ≤ 1.5% of B_req. The null: the seven ln X values redrawn
uniformly from [0.5, 8] (seeded, 10⁵ trials), counting hits per clock.
- *Predicted before running:* at least one hit for some nuclear-scale clock (for example
  8 ln(m_p/m_e) = 60.1 against B_req(R_p/c) = 61.0), and the observed total hit count is
  consistent with the null (permutation probability above 0.05).
- *Rejection criterion (populated):* a construction would be regarded as distinguishable from
  chance only if the observed hit count for a clock exceeds the null's 95th percentile **and**
  the same construction hits two or more physically independent clocks. Predicted not met.

**Part A3 — per-tick survival candidate (Law V).** q = 1/γ₀ (the budget ratio v_circ/c at the
seat release speed); τ(N) = t·q^(−N) for integer N = 50…80 and each clock. A hit is τ within
±1.5% of 877.8 s. Expected hits by chance over 7 clocks: about 0.2 (the step in ln τ per N is
ln γ₀ = 0.93).
- *Rejection criterion:* no clock with an integer N inside the band, or hits on clocks that are
  not supported by a stated reason for choosing them. Predicted not met on both counts.

**Not tested here.** The products-as-topology statement (T4) and the exclusion of an imported
thermal barrier (T5) are qualitative and have no numerical test in this run. The shared-seat
route (Part B of the seed) enters through the census (γ₀, v_phase/c as X) and is not
derived.

**Labels.** Part C: arithmetic on MEASURED-INPUT. Part A1: COMPUTED. Parts A2 and A3:
COMPUTED censuses; a hit is recorded as a coincidence with its chance rate stated, never as
a derivation of B.

