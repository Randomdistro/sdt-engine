# QM01 Phase-5 — Bell scope memo (CONCRETE): local vs throughpole, a CHSH number

**J. C. Harvey, Melbourne — 2026-06-25.** Tool: `qm01_bell_local_vs_throughpole.py` (seed 7, N=3×10⁶,
reproducible). This is the Phase-5 memo the QM01 prompt asked for — and it is no longer a memo of
words: the split-pattern entanglement mechanism is **simulated** and its CHSH is **measured**.

## The mechanism under test

Harvey's picture: split ONE pattern (a vortex / emission) into two; both carry a shared orientation
λ — *"turn one, turn all."* Two analyzers at angles a, b each return ±1. Two readout rules, same λ:

- **(1) LOCAL** — each end reads its *own* analyzer locally from λ ("adjacently divergent pathways
  through the dynamic flux"). A local hidden-variable model.
- **(2) THROUGHPOLE** — the shared phase is projected onto *both* analyzers jointly (one object, two
  ends; the in/out that never terminates). A non-local shared account.

## Result (CHSH, photon-polarisation angles 0°/45°/22.5°/67.5°)

| readout | CHSH S | E(22.5°) | sits on |
|---|---|---|---|
| **(1) LOCAL split-pattern** (sim) | **2.0000** | +0.500 | the classical ceiling, EXACTLY |
| **(2) THROUGHPOLE** (shared account) | **2.8284** | +0.707 | = QM (Tsirelson 2√2) exactly |
| local-hidden-variable Bell ceiling | 2.000 | — | — |
| quantum mechanics | 2.8284 | +0.707 | — |
| experiment (loophole-free, 2015) | ≈ 2.40 | — | > 2 ⇒ world not locally causal |

`E(θ)` is the triangle `1−4θ/π` for the local rule (0.5 at 22.5°) vs `cos 2θ` for the throughpole
(0.707) — the two curves agree at 0°, 45°, 90° and split where Bell lives.

## What this proves — and what it does NOT

**Proves:**
1. The **local** mechanism does not merely respect the bound, it **saturates it (2.0000)**: even the
   best local "adjacently-divergent-pathways" readout cannot reach QM. So **a strictly local SDT
   entanglement predicts SUB-quantum correlations** — and that is already falsified (experiment 2.40).
2. The entanglement debt is now a **single number: 0.828** (2.828 − 2.000), and it lives **entirely in
   the throughpole** (the non-local readout). The problem is sharp, not vague.

**Does NOT prove (the honesty line):** Model (2) does **not derive** 2.828 — it **assumes** the shared
phase is read jointly (non-locally) and that assumption yields QM *by construction*. The sim
**localises** the non-locality; it does not earn it. Claiming this "reproduces QM entanglement" would
be the dishonest read.

## The well-posed problem this leaves

> Does the throughpole's "in/out that never terminates" **force** a joint (non-local) projection of the
> shared phase, **from SDT primitives** — rather than by assumption?

- **If yes:** QM-level entanglement is native, and the **c-relay independently bounds any signal at c**
  (non-local in structure, local in dynamics ⇒ no-signalling for free — cleaner than abstract QM,
  cleaner than ER=EPR's isolated bridges). [[project_foundational_ontology_influx_monopole]] (throughpole).
- **If no** (the lattice can only ever read locally): SDT predicts entanglement **below Tsirelson** — a
  real, falsifiable departure from QM, testable at a Bell apparatus.

Either outcome is a result. Bell guarantees the full FLM10 lattice-dynamics version (two vortices in
live flux) lands on the **2.000** side **unless** the throughpole's non-local channel is in the readout
explicitly — so the toy is not a shortcut around the heavy sim; it shows the heavy sim's verdict is
fixed by one design choice: throughpole in the readout, or not.

## Status

**QM01 Phase-5 — the Bell debt is now quantified, not waved.** Open work: derive (or refute) the
throughpole's joint readout from the foundational ontology, then — once FLM10 has dynamics — run the
full two-vortex lattice CHSH as the heavy confirmation. Pairs with QM01 Phases 1–4 (double-slit/Born).

---

**REASSESSMENT (2026-07-04, Harvey directive — §G GATE-CONTRABAND check)**
*Appended below the original; nothing above this line is altered.*

- **The arithmetic stands.** Local readout S = 2.0000 (saturated), throughpole readout S = 2.8284,
  debt = 0.828 — unchanged. The local branch's kill (sub-quantum vs measured ≈ 2.4) is
  measured-anchor-class and stands.
- **Two clauses were c-interferative and are reclassified, not deleted:**
  1. *"non-local in structure, local in dynamics ⇒ no-signalling for free"* — this grounded marginal
     flatness in a c-capped dynamics, i.e. the rival's axiom doing the guaranteeing. Under the
     two-channel architecture (FLM14 RUN_LOG ADJ-7) energy/pulses relay at c (unchanged), but
     CONSTRAINT through a gear-locked pair propagates uncapped (canon precedents: the 1.83c seat,
     k<1 inside R_p, the instantaneous throughpole, GOM05 rigid hinge units). Marginal flatness is
     instead guaranteed by the **Synchrony Theorem** (FARMER_PASS 2026-07-03 refinements 5–6):
     matter IS lattice structure, so matter/space cannot desynchronise — a theorem-check, not a
     c-relay consequence; and a synchronous constraint channel can carry structure with marginals
     flat forever (communication ≠ desynchronisation).
  2. The framing that the joint (throughpole) readout is an assumption to be *earned from local
     primitives*. The channel is native canon; what is unearned is the **weighting** (QM05's S = 4
     sign-copy probe proved the channel alone fixes nothing). The well-posed problem restates as:
     not "derive non-locality" but "derive the cos² residence weighting of the constraint channel."
     Owner: RESIDENCE-LAW root (QM04/05/07); instrument: FLM14 rule-form-4 / ADJ-6.
- **Classification change:** "the entanglement debt lives entirely in the (assumed) non-local
  readout" → **OPEN — re-opened under the two-channel/constraint framework.** The honesty line
  (2.8284 was fed, not derived) stands verbatim.
