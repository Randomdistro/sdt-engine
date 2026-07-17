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

---

# RUN 2 — ADJ-R2-1 (2026-07-07, committed BEFORE any tool exists): the action/reaction quadrature split

**Provenance:** Harvey, this date, on run-1's Phase-4: "no one in there thought to split that
into action and reaction? 2 out the back gives 2 forward." Formalised in-session BEFORE code;
ONE construction declared (look-elsewhere: no alternates tried; any future variant gets its own ADJ).

## The declared model (all primitives named)

- Pair = ONE rotor (run-1's throughpole ontology, unchanged): hidden phase λ uniform per trial;
  Alice's outcome = run-1's local sign rule (marginal-flat by construction); Bob = A·g.
- **Doubled-angle director space (native: a gear/rotor orientation is a DIRECTOR — alignment at
  Δ and Δ+180° are the same tooth engagement — so channel geometry lives at 2Δ).**
- **The constraint channel carries ONE CONSERVED KICK per trial: a unit vector k̂ at orientation
  ψ in director space. Conservation = action books its reaction = |k̂| = 1, fixed. The joint
  readout at relative setting Δ receives the LINEAR PROJECTION: E(Δ) = k̂ · û(2Δ).**
  g = ±1 sampled with P(g=+1) = (1 + E)/2. NO cos² anywhere; cosine enters ONLY as dot product
  (projection geometry — the same licensed status as ADJ-6's C,S).
- **DISCLOSURE (committed now, because it is the point):** cos²(Δ) ≡ (1 + cos 2Δ)/2. The model's
  P(same) is ALGEBRAICALLY IDENTICAL to run-1's imported Malus weighting. This run therefore
  changes the PROVENANCE, not the numbers: Born's square at the Bell readout re-derives as
  "mean + linear projection of a conserved kick in director space." The square dissolves.
  Machinery anchor: the model must reproduce run-1's S = 2.8286 ± 0.005.
- **The vector theorem under test (stated before running):** for CHSH angles a=0°,a′=45°,
  b=22.5°,b′=67.5°, the four director-space readout combinations sum to the vector
  û(−45°)−û(−135°)+û(45°)+û(−45°) = (2√2, 0) EXACTLY. Hence S(ψ) = k̂·(2√2,0) = 2√2·cos ψ:
  **Tsirelson = |one conserved unit kick| × |the CHSH direction sum|. S = 4 requires |k̂| = √2 —
  an overdraw: more comes forward than was booked out the back.** Run-1's sign-copy rule = the
  conservation-free limit (kick renewed per setting pair).

## Committed gates (never widened)

- **G-A (anchor):** run-1 Phase-2 machinery reproduced: S = 2.8286 ± 0.005, marginals < 0.002.
- **G-1 (ceiling from conservation):** with |k̂| = 1 enforced, scan ψ over the full circle:
  max S = 2√2 ± 0.005 and NO ψ exceeds 2.8334 (2√2 + 5σ). The per-pair correlations at the
  optimum must land at |E| = 1/√2 ± 0.005 each (the model's own prediction; also the measured
  per-pair value in real Bell experiments).
- **G-2 (control — conservation OFF):** allow the channel to renew its kick per setting pair
  (each pair gets its own optimally-aligned unit kick): S must reach 4.000 ± 0.005 with marginals
  still flat — proving the ceiling in G-1 comes from CONSERVATION, not from a smuggled weighting.
- **G-3 (no-signalling):** every arm, every setting pair: marginal deviation < 0.002 (4σ at
  N = 10⁶/cell; seed 13; σ_E ≈ 0.001).
- **G-4 (the ×2 identity, report row):** independent-Malus arm (run-1 L3 machinery) vs joint arm:
  the correlation ratio must be 2.000 ± 0.01 (one projection paid once vs paid twice).
- **Overdraw row (report):** S(|k|) for |k| ∈ {0.5, 1/√2, 1, √2}: linearity S = 2√2·|k| shown;
  the |k|=√2 row prints as ALGEBRAIC ONLY (per-pair |E| > 1 is unrealisable with ±1 outcomes —
  the PR box is not just conservation-violating, it is outcome-impossible at fixed norm).

## Pre-declared class ceiling and implications

- Best case = **NATIVE-conditional**: conditional on (a) the throughpole channel model (run-1)
  and (b) director-space geometry (gear-tooth doubling) — both pre-existing canon. If the
  projection-cosine is judged an import, the result caps at CONSTRUCTION like run-1; either way
  the CONSERVATION⇔CEILING link (G-1 vs G-2) is the new falsifiable content.
- **If G-1∧G-2 land:** (i) run-1's owed "what excludes S=4" exclusion is PAID (S=4 = reaction-free
  overdraw, outcome-unrealisable at conserved norm); (ii) the ADJ-6 bridge C^p/(C^p+S^p) is
  exposed as a MIS-TRANSCRIPTION — the Bell readout is linear in the conserved kick, so NO
  residence exponent p enters Bell at all, dissolving run-6's super-quantum tension (p_occ ≈ 2.6
  and Bell's p_eff = 2 stop being in conflict: Bell never consumed p_occ); (iii) the residence
  law's Born question re-poses as "why is the readout power the sum of two orthogonal
  projections" — quadrature, Law V form. Each implication is CONDITIONAL and none is claimed
  before the gates print.

Tool: `qm05_r2_quadrature.py` → teed `qm05_r2_results.txt`. PYTHONIOENCODING=utf-8.

**Cross-note (2026-07-07):** run-2's bridge correction is now acted on — FLM14 ADJ-14
re-drafts Part C as the emergent-channel test (license = conservation + native counting
readout + flat marginals; gates = cos-form shape, 2√2 ceiling, locked-vs-unlocked control).
ADJ-6's C^p transcription is SUPERSEDED for Part C; it remains in this record unedited.
