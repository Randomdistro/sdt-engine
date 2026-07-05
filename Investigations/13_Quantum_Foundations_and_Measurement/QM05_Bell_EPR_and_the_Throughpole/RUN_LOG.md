# RUN_LOG — QM05 Bell / EPR & the Throughpole

**J. C. Harvey, Melbourne — 2026-07-03.** Executor: HUNTER-disciplined agent run.
Written BEFORE any tool code, per `PROMPT_EXECUTION_PROTOCOL.md`.

## Pre-Run Commitments — QM05

- Prompt completion target: **D/OPEN — pre-declared** (per prompt §⓪ Q5: the expected landing).
- Physics class hoped: OPEN (local baseline KILLED-honestly at 2; throughpole channel = structure under test).
- CALIBRATED budget: 0. The throughpole coupling is a structure under test, not a fit.
- Engine namespaces used: none numerically required (CHSH is dimensionless); EMC03 contra-handedness
  is the shared hidden variable λ conceptually. NO ψ, NO collapse, NO atomic::.
- Prior art acknowledged BEFORE this run: `QM01_.../QM01_BELL_MEMO.md` + `qm01_bell_local_vs_throughpole.py`
  (2026-06-25) already established S_local = 2.0000, S_throughpole = 2.8284 (analytic cos-rule). Verified
  reproducible 2026-07-03 before this log was written. This run BUILDS ON it: the throughpole is here
  implemented as **sampled outcomes** so marginals can actually be measured (the memo's E_tp was analytic,
  so its no-signalling was asserted, not tested).

## Phase thresholds (committed before run)

N = 10⁶ pairs per setting cell ⇒ σ_E ≈ 0.001, σ_marginal ≈ 0.0005. CHSH angles a=0°, a′=45°, b=22.5°, b′=67.5°.

- **P1 (local baseline):** three local readouts (deterministic sign, deterministic best-strategy,
  Malus-stochastic). Expect ALL S ≤ 2.000 + 4σ = 2.004. Any local S > 2.004 ⇒ the model leaked a
  shared-setting channel — hunt the leak, do NOT celebrate.
- **P2 (throughpole, sampled):** joint-projection rule P(B=A|a,b) = cos²(a−b), Alice local-sign.
  Expect S = 2.828 ± 0.005. **Label committed in advance: CONSTRUCTION, not derivation** — the cos²
  weighting is imported from the observed correlation law; the run measures its consequences only.
- **P2-NS (no-signalling gate):** for every setting pair, |P(A=+|a,b) − 0.5| and |P(B=+|a,b) − 0.5|
  < 4σ = 0.002. If the S-lift breaks this ⇒ reject the route, debt stands.
- **P3 (coupling sweep):** partial coupling s ∈ {0, 0.25, 0.5, 0.75, 1}: S(s) must be monotone from
  ~2.0 to ~2.83 AND no-signalling must hold at EVERY s (marginal dev < 4σ). If NS holds only at s=1,
  the route is fine-tuned (prompt Q4) ⇒ fragile, report.
- **P4 (Tsirelson probe — pre-registered):** a *different* marginal-preserving joint rule
  (deterministic sign-copy: B = A·sign(cos 2(a−b))) is run to ask whether "joint readout" per se is
  Tsirelson-bounded. Pre-commitment: **whatever S it returns is reported as-is.** If S > 2.828 with
  marginals intact, then the throughpole-as-bare-joint-channel does NOT stop at Tsirelson, and the
  entire QM-match content of P2 lives in the cos² weighting — that sharpens the debt, it does not pay it.

## Forbidden (restated)

Report S>2 without the NS check; fabricate a local Bell violation; repaint the pre-declared D/OPEN as A;
claim P2's 2.828 as "SDT reproduces entanglement".

## Run record

- 2026-07-03: commitments above frozen. Tool `qm05_bell_throughpole.py` written after this block. → see
  `qm05_results.txt` (real stdout) and `QM05_VERDICT.md`.
- **ADJ-1 (2026-07-03, post-run, framing only — NO threshold or number changed):** (a) protocol
  supplement received: verdicts must conform to `Investigations/HUNTER_PROTOCOL.md` (§D seven
  questions + Recovery grade + canonical verdict line) — `QM05_VERDICT.md` re-issued accordingly;
  (b) Harvey directive (machinery only): the Phase-2 cos² joint weighting is re-labelled from
  "CONSTRUCTION (imported from QM)" to "**OBSERVED-data diagnostic probe**" — the curve is the
  measured Bell-experiment correlation (data, not the rival's formalism), used per HUNTER §B as a
  comparison/probe only, never as SDT machinery. All S values, marginals, and gates stand exactly
  as first produced.
- **ADJ-2 (2026-07-04, per Harvey's PROMPT.md banner amendment + FLM14 ADJ-7 + HUNTER §G — class
  change only, NO number moved):** this log's P2-NS gate is reclassified from a route-rejection
  condition to an **OBSERVED comparison against measured Bell marginals** (the marginal-flatness /
  Synchrony-Theorem check). The 0.002 threshold and the measured results (worst dev 0.0011; ≤0.0009
  across the s-sweep) stand unchanged; what changed is what a violation would have MEANT (data-FAIL,
  not an FTL-axiom kill — Einstein locality is GATE-CONTRABAND). The two stale FTL rows in
  `PROMPT.md` (§⑧ T2 kill cell, §⑩ pivot P2 forbidden cell) struck with annotations this date.
  Consequence for the verdict: unchanged (OPEN · PARTIAL · RESIDENCE-LAW); the throughpole/geared
  constraint channel is uncapped by canon precedent, and the owed machinery is still the joint
  residence weighting (FLM14 rule-form-4 in flight owns it).
