# TD05 — Verdict: Phase Transitions and Latent Heat from Reconfiguration

**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td05_packing_reconfiguration.cpp` → `results.txt` (exit 1 — the P2 gate fired and the exit records it).

## What was run

3D MD (velocity Verlet, NVE production) of N=108 wake-bound hard vortices (pair-potential
proxy: LJ, the one declared measured form), ρ* = 1.0 fixed, heating 0.40→2.16 then cooling.
**No Landau/order-parameter field entered the dynamics at any point** — S(k₁₁₁) was diagnostic
only. Deterministic seed; the re-run after the gate-implementation fix reproduces the identical
trajectory.

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1 sharp transition | ΔU > 0.4 ε and > 4× median; S collapse >0.3→<0.1 in ≤2 steps; hysteresis > 5× noise | ΔU = 0.511 at T* = 1.96; S 0.545→0.024 in 2 steps; hysteresis 1.013 | PASS |
| P2 latent-heat ledger | L within factor 1.5 of Δbonds × \|ū_bond\| | **factor 6.03 — FAIL (fired; trace below)** | FAIL |
| P3 argon magnitude | L_melt, cohesion within 3× (OBSERVED LJ params) | L_melt ×2.32; cohesion 6.77 vs 6.53 ε (×1.04); L_vap ≫ L_melt | PASS |
| P4 Clausius–Clapeyron | — | DEFERRED as pre-declared (needs pressure-controlled coexistence) | OPEN |

Disclosures held: "L = T_mΔS" with calorimetric ΔS is an identity — NOT TESTED (declared
pre-run, not laundered); flat-T absorption is protocol-set. Incident: the S-collapse check was
first implemented as a single-step test, stricter than the committed ≤2-step window; the
committed gate was implemented as written (ADJ-1, RUN_LOG) — same trajectory, no re-rolling.
Cooling branch glass-arrests rather than recrystallising (S/N = 0.011 at T* = 0.40) — the
prompt's Q2 (glass = failed reconfiguration, FLM09) is observed in-model and logged.

## P2 run to ground (HUNTER §D — the fired falsifier is the headline result)

1. **Why:** the committed ledger L = Δ(bond count) × |ū_bond| under-predicts by ×6 (single
   step) and ×3 (transition window): only 0.52 of 12 first-shell bonds per particle are lost
   on melting at fixed density.
2. **Recoverable?** PARTIAL — see 5–6.
3. **Failed to account for:** the transition-window decomposition (in results.txt) shows the
   energy goes 13% to bond loss and **87% to re-pricing surviving bonds** (ū_bond softens
   −0.571 → −0.389 ε as the packing disorders at the same density).
4. **Errored premise:** H2's "L = N_bonds × Δε_reorg" assumes reconfiguration = bond
   *breaking*. At fixed density, reconfiguration is overwhelmingly bond *deformation* — the
   packing pays for worse geometry, not fewer contacts.
5. **Freedom that fixes it:** run at coexistence conditions (NPT or two-density), where melting
   expands and the count channel is not artificially suppressed — a native, physical freedom,
   not a knob. Alternatively restate H2 as L = Δ(Σ pair energies), but that is an identity and
   is refused as a repair (it would empty the hypothesis).
6. **Accounting for the freedom:** real melting (argon, ΔV > 0) genuinely loses more contacts;
   whether count-x-cost then dominates is decidable by the same tool + a barostat. OWED.
7. **Cascade:** independent of TD-ROOT-1 (this is a mechanics failure, not a counting-class
   issue); shares no root with FD-ROOT-2. New named debt: **TD05-LEDGER (count vs re-pricing
   at coexistence)**. P4's deferral folds into the same follow-up (a barostat run would pay both).

## Physics class: CONVERGENCE (with a fired sub-hypothesis, honestly kept)

Which step would break on a non-SDT substrate? None — LJ melting, superheating hysteresis, and
glass arrest are generic condensed matter; "wake binding" and "Law IV reorganisation cost" did
narrative work only, and the one place the SDT narrative was cashed as a formula (count × cost)
is exactly where the run said no. A clean kill of H2's naive form outranks a forced pass (R4).

**Earned:** first-order transition + hysteresis with no Landau field in the dynamics (T1
discharged); argon orders of magnitude with one declared proxy; glass-arrest observation (Q2).
**Owed:** TD05-LEDGER at coexistence; Clausius–Clapeyron (P4); any FLM08-motif-specific
prediction (Q1, untouched).

**Certification:** P1/P3 COMPUTED; P2 FAIL-honest with trace; P4 DEFERRED; CALIBRATED(1) = the declared LJ proxy (argon mapping OBSERVED).

**Prompt completion C · Physics class CONVERGENCE (T1 pass; H2 count-ledger KILLED at fixed density) · Recovery PARTIAL (coexistence-density route named, not run) · Cascade root TD05-LEDGER (new, local; none shared)**
