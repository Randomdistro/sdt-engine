# CM05 — Verdict: Superfluidity and BEC from Phase Lock

**Author:** J. C. Harvey, Melbourne · **Run:** 2026-07-04 · Tool `cm05_superfluid.cpp` →
`cm05_results.txt` (MSVC `/std:c++20 /O2 /utf-8`, real stdout; gates pre-committed).

## Headline

**The body-count rule is the earned result: the circulation-quantum divisor counts the locked
bodies, and it lands three for three with zero adjustments.** He-4 single wake → κ = h/m
(9.9693e-8 vs 9.97e-8 measured, **0.007%**, divisor exactly 1, no free integer — Law VI);
He-3 → pair lock → h/2m₃, which is precisely what is measured (Avenel–Varoquaux, OBSERVED
comparison); CM01 electron pair → h/2m. One rule across superfluid, fermionic superfluid, and
superconductor. He-3's *need* to pair is narrated (odd constituent count leaves an unpaired
half-wake) and honestly labelled ARGUED, not derived.

## The honest FAIL (P1 magnitude)

Both pre-committed native routes missed the 2× gate, from opposite sides:

- Route 1 (wake-crossover, λ_w = spacing): T₁ = 12.52 K → **5.77× high — FAIL**
- Route 2 (lock-energy, CM01 form): T₂ = 0.476 K → **0.22× low — FAIL**

They bracket T_λ = 2.17 K, and **bracketing is not predicting** (HUNTER §C3) — no average was
taken, no third route fished. What is earned: a lock transition *exists* on both routes at kelvin
scale (not mK, not 100 K) with zero fitted parameters. What is owed: the magnitude.

## Zero viscosity (P2) and v_c (P4)

- η → 0 is the same FLM14 machinery as CM01's R = 0: the locked cluster is gear-rigid; only the
  unlocked fraction 1−f dissipates. Mean-field lock fraction collapses sharply (f = 0.96 at
  T/T_lock = 0.5; exactly 0 above) — both committed gates PASS. Rotation enters only as quantised
  vortices because a locked phase cannot wind fractionally (Law VI) — same door as P3.
- v_c: native content is only the bound v_c ≤ c_s = 238 m/s. The 59.0 m/s number is
  **OBSERVED-reprocessing of measured roton parameters — no SDT credit**, printed as a
  consistency check. The roton is CM04's short-k relay bend, OPEN there.

## §G mirror

- The Bose-counting rescue for P1 (ζ(3/2), which would give 3.13 K) was refused in advance —
  the rival's occupation statistics are not admissible machinery until SDT earns
  indistinguishable-wake seating natively. The refusal is logged as the named OPEN, per §G(3):
  status-OPEN with re-open condition, never "underivable."
- No rival axiom in any gate; anchors: measured T_λ, κ, He-3 circulation, roton data.

## FAILURE RECOVERY (§D — P1 magnitude double-FAIL)

1. **Why:** Route 1 high by 5.8× (equipartition v_rms overstates the effective wake speed in a
   dense locked liquid); Route 2 low by 4.6× (single-neighbour lock energy understates a
   12-neighbour collective lock). Signs are mechanically sensible and opposite.
2. **Recoverable?** Yes in principle: the two routes are limits of one unbuilt calculation —
   collective seating of N mutually-locking wakes.
3. **Unaccounted:** how many neighbours participate in the lock, and what fraction of thermal
   motion is already collective at onset.
4. **Errored premise:** "a two-body criterion (one wake vs one spacing / one neighbour) captures
   a many-body lock." Both routes share it.
5. **Freedom:** the seating multiplicity (effective z_lock between 1 and ~12).
6. **Accounted natively?** Not yet — z_lock chosen to land 2.17 K would be a FISHED knob. The
   native quantity that would fix it is the same FLM14 engagement number CM01's η needs.
7. **Cascade:** YES — **ROOT-B** (lock-depth/engagement magnitude), shared with CM01's η and
   SCT's barrier B. The bracket's geometric centre (~2.4 K) sitting near T_λ is noted and
   deliberately NOT claimed (look-elsewhere).

**Recovery grade: PARTIAL.**

## Generative questions logged

1. Does one FLM14 engagement number simultaneously close CM01's η spread AND pick the T_λ point
   inside this bracket? (ROOT-B payoff test — two debts, one payment.)
2. Is the He-3/He-4 divisor flip observable in a mixed film (3-4 solutions) as a discrete
   κ-spectrum with BOTH quanta present?
3. Two-fluid ρ_s/ρ = f(T): does the measured curve match the mean-field lock fraction shape
   (it should undershoot near T_λ where fluctuations beat mean field) — a falsifiable shape test.

---

> **Prompt completion C · Physics class CONVERGENCE (κ + body-count rule earned; T_λ magnitude
> OPEN, honestly failed) · Recovery PARTIAL · Cascade root ROOT-B (lock-depth magnitude — shared
> with CM01 η, SCT B)**
