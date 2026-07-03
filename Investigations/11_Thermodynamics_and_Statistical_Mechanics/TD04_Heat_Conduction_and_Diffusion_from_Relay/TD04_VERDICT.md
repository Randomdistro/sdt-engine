# TD04 — Verdict: Heat Conduction and Diffusion from Relay

**Dual verdict: Prompt completion C · Physics class CONVERGENCE (mechanism); P4 magnitude FAIL-reported; P5 OPEN.**
**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td04_relay_conduction.cpp` → `results.txt` (exit 0, core gates).

## What was run

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1 D = vλ/3 | ±2% from MSD | 0.33683, dev 1.05% | PASS |
| P2 diffusion eq. | α = vλ/3 ±2%; kurtosis 3 ± 0.1 | worst 1.99%; worst kurt dev 0.027 | PASS |
| P3 Fourier slab | J vs ⅓nvλk_B·ΔT/L_eff ±5%; linearity; √T | dev 0.34%; 0.5043; ratio 1.9971 | PASS |
| P4 argon/air | within factor 2 | **factor 3.30 / 2.96 — FAIL, reported** | FAIL |
| P4 copper | — | DEFERRED (native metal channel absent) | OPEN |
| P5 Wiedemann–Franz | 10% (declared unreachable pre-run) | classical L low by 2.19× — **fired** | OPEN |

Note on P2: the committed 2% gate survived by 0.01% (worst point 1.99% at t=50, the shortest
time, where ballistic-to-diffusive crossover bias is largest). Recorded as-is; a longer-time-only
fit would look better but was not the committed estimator.

## P4 failure run to ground (seven questions, HUNTER §D)

1. **Why:** elementary k = ⅓nv̄λc_v under-predicts argon by 3.3× and air by 3.0× (air also
   carries the Eucken internal-DoF correction).
2. **Recoverable?** PARTIAL — route named, not executed.
3. **What did the model fail to account for:** the single-speed relay walk ignores the
   speed–flux correlation: faster carriers both carry more energy and fly farther between
   scatterings, so the energy flux is weighted toward the fast tail (Chapman–Enskog resums
   this into ≈2.5× for hard spheres).
4. **Errored premise:** "one relay speed v̄ represents the bath" — the bath TD02 built has a
   full MB spread; collapsing it to v̄ is the error.
5. **Freedom that fixes it:** speed-resolved carriers with λ(v) and energy-weighted flux — a
   native quantity (the TD02 bath supplies the distribution), not a knob.
6. **Accounting for the freedom:** requires the velocity-resolved transport solve
   (Chapman–Enskog-equivalent) executed inside the relay model. Owed, not fudged here.
7. **Cascade:** same premise underlies FD02's viscosity factor 1.44 (air) — one shared root:
   single-speed coarse-graining. Fixing it once should close both suites' absolute magnitudes.

## P5 (Wiedemann–Franz) — honest kill of the naive claim

One-channel classical relay carriers give L = (3/2)(k_B/e)² = 1.114e-8 WΩK⁻²; measured is
2.44e-8. The π²/3 prefactor is a degenerate-statistics result; SDT has no native derivation of
degenerate carrier statistics, and importing the Fermi surface would be BORROW-SMUGGLE.
T3 is recorded as fired; the H3 claim ("one channel carries heat and charge → universal L")
remains OPEN at the level of the prefactor and untestable at the level of constancy.

## Physics class: CONVERGENCE

Which step would break on a non-SDT substrate? None — D = vλ/3, the Fourier law, and the
diffusion equation are generic kinetic theory; the 1/3 is the same rank-2 isotropy TD03
established (there, at least, the FLM08 bond set gave an exact discrete statement; here nothing
lattice-specific enters). "Heat is disordered relay throughput" did narrative work only.
The √T slope is the fixed-λ lattice limit, same as FD02, with the same Sutherland caveat.

**Earned:** the transport spine q = −k∇T, ∂T/∂t = α∇²T with α = D = vλ/3 verified end-to-end
at sub-percent level, one machinery across FD02 (momentum), TD04 (energy), TD08 (mass) — the
prompt's Q3 unification holds in-model. **Owed:** the ~2.5× speed–flux correlation factor
(shared root with FD02); a native degenerate-statistics route for metals; second-sound/ballistic
regime (Q2, untouched).

**Certification:** P1–P3 COMPUTED; P4 OBSERVED inputs, FAIL honest; P5 OPEN; zero CALIBRATED (Milne z0 declared, not load-bearing at the 5% gate).

## Recovery grades (HUNTER §D — the seven-questions block above is the P4 analysis)

- **P4 (materials ×3.3/×3.0 FAIL):** Recovery **PARTIAL** — premise error named (single-speed
  coarse-graining drops the speed–flux correlation), freedom named and native (speed-resolved
  carriers from the TD02 bath, a Chapman–Enskog-class solve), not yet executed.
- **P5 (Wiedemann–Franz OPEN):** Recovery **NO RECOVERY on the current whitelist** — the π²/3
  prefactor requires degenerate carrier statistics, which SDT has not derived natively and may
  not import; until a native degenerate-statistics theorem exists this stays a named closure
  debt, not a tuning target.
- Mechanism class (CONVERGENCE): Recovery PARTIAL via TD-ROOT-1 (same as TD02).

**Prompt completion C · Physics class CONVERGENCE (mechanism); P4 FAIL-honest, P5 OPEN · Recovery PARTIAL (P4: FD-ROOT-2 named) / NO RECOVERY yet (P5 degenerate statistics) · Cascade root FD-ROOT-2 (single-speed coarse-graining, shared with FD02 ×1.44) + TD-ROOT-1 (mechanism class)**
