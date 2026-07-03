# TD08 — Verdict: Fluctuation–Dissipation and Brownian Motion

**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td08_fdt_brownian.cpp` → `results.txt` (exit 0, single run — no adjustments after first execution).

## What was run

1D Rayleigh gas: heavy vortex M = 100 m in a TD02-MB bath; collisions by exact flux-weighted
thinning. **The tool contains no noise-amplitude parameter** — kicks and drag both emerge from
the one simulated collision stream, so the Einstein and FDT ratios are outputs, not
normalisations (the prompt's forbidden move is structurally impossible in this code).

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P0 equilibrium | ⟨MV²⟩/k_BT = 1 ± 2% | 0.9982 (T=1), 0.9994 (T=4) | PASS |
| P1 Brownian walk | MSD linear; D extracted; τ_v reported | D = 0.3175 (τ=35.4); D = 0.6330 (τ=21.4) | PASS |
| P2 Einstein relation | D/(µk_BT) = 1 ± 2% at two T; linearity | **1.0061 and 1.0039**; Vd(F/2)/Vd(F) = 0.496/0.502 | PASS |
| P3 FDT S_F(0) | vs 2γk_BT ± 3% (O(m/M)=1% declared) | 0.9866 — matches the declared M/(M+1)=0.990 correction | PASS |
| P4 Stokes–Einstein vs FD02 | — | **DEFERRED as declared pre-run** (no 1D Stokes law; FD02 η carries ×1.44) | OPEN |

## The honest content

H2 — noise and drag as two faces of one statistic — is *demonstrated*, not imposed: a single
collision stream, with zero separate inputs, yields D/(µk_BT) = 1 within 0.6% at two
temperatures and S_F(0) = 2γk_BT within the declared finite-mass correction. The committed
decision rule ("if a noise knob is ever needed to pass, that IS the failure") was never invoked.

## Physics class: CONVERGENCE / NULL-SDT for the mechanism

Which step would break on a non-SDT substrate? None — the Rayleigh gas is textbook kinetic
theory; "relay shot-noise" is the SDT narration of bath collisions. The prompt's `~t_P`
correlation-time claim (T1) is untestable in a toy whose tick is the collision time; classed
OPEN, not asserted. The FDT itself is, as pre-registered, a theorem of one underlying
statistic + equilibrium — precisely why it reproduces here without SDT structure doing work.

## HUNTER §D — seven questions on the NULL-SDT/OPEN items

1. **Why:** the Einstein/FDT ratios follow from any equilibrium collision bath; no ℓ_P, R²,
   or lattice geometry enters. P4 unclosed because the toy has no hydrodynamic sector.
2. **Recoverable?** PARTIAL — routes named below, not executed.
3. **Failed to account for:** (a) a 3D hydrodynamic medium (needed for Stokes–Einstein);
   (b) any observable at the genuine relay tick (sub-t_P VACF, prompt Q1).
4. **Errored premise:** that a 1D shot-noise toy could cash the cross-suite closure; and
   upstream, FD02's η itself carries the ×1.44 single-speed defect.
5. **Freedom that fixes it:** the same speed-resolved transport solve owed at FD-ROOT-2 —
   closing it fixes FD02's η and enables an honest P4 in 3D.
6. **Accounting for the freedom:** native (the TD02 bath supplies the full speed
   distribution); a real computation, not a knob.
7. **Cascade:** P4 cascades from FD-ROOT-2 (single-speed coarse-graining, = TD04 P4's root).
   The mechanism-class finding cascades from TD-ROOT-1 (ε-scale invisibility in equilibrium
   statistics).

**Earned:** the suite's cleanest demonstration that fluctuation and dissipation are one
statistic in-model, with the forbidden normalisation structurally excluded; transport triad
closed in-model (TD04's α, FD02's ν, TD08's D all = ⅓vλ-class random walks — prompt Q2
confirmed at toy level). **Owed:** P4 closure via FD-ROOT-2; any t_P-scale observable.

**Certification:** P0–P3 COMPUTED; P4 DEFERRED-OPEN (declared pre-run); zero CALIBRATED; k_B unit-bridge only.

**Prompt completion B · Physics class CONVERGENCE/NULL-SDT (mechanism; Einstein+FDT demonstrated from one statistic) · Recovery PARTIAL (P4 via FD-ROOT-2 speed-resolved solve) · Cascade root FD-ROOT-2 (P4) + TD-ROOT-1 (mechanism class)**
