# QM05 — VERDICT: Bell / EPR & the Throughpole

**J. C. Harvey, Melbourne — 2026-07-03.**
Tool: `qm05_bell_throughpole.py` (seed 11, N=10⁶/cell). Real stdout: `qm05_results.txt`.
Pre-commitments: `RUN_LOG.md` (frozen before coding; ADJ-1 records the mid-run protocol supplement —
no threshold was moved). Prior art built on, not duplicated:
`../QM01_Deterministic_Double_Slit_from_Lattice_Relay/QM01_BELL_MEMO.md` (verified reproducible 2026-07-03).

## Framing rule applied (machinery only)

Everything below is a **calculative mechanism** or is labelled as *not one*. The correlation curve
`E(θ) = cos 2θ` appears in Phase 2 **only as the OBSERVED data curve from Bell-test experiments**
(the numbers the experimenters took) — used as a diagnostic probe target, per HUNTER §B. It is
**never** presented as SDT machinery. No wavefunction, no collapse, no Hilbert space anywhere.

## Results (all thresholds as pre-committed — none moved)

1. **Local machinery caps at 2.0000, saturated.** Three honest local mechanisms (shared-handedness
   sign readout; exhaustive best deterministic strategy; stochastic Malus readout) give
   S = 2.0000, 2.0000, 1.4148. These runs ARE derivations — real machinery, really computed. A
   strictly-local SDT readout therefore predicts sub-quantum correlation, and the observed data
   (loophole-free S ≈ 2.4 > 2) already falsifies that branch. **KILLED cleanly.**
2. **The observed curve, run as a joint-readout probe, gives S = 2.8286 with no-signalling
   MEASURED intact** (worst marginal deviation 0.0011 < 0.0020 gate, all four setting pairs).
   This is a **probe, not a result**: the cos² joint weighting is the observed data curve fed in;
   the run only establishes that a marginal-preserving joint readout *carrying that curve* signals
   nothing. It upgrades the QM01 memo (whose no-signalling was asserted, not measured).
3. **No-signalling is structural, not tuned** (prompt Q4): coupling sweep s = 0→1 gives
   S = 2.00→2.83 monotone, worst marginal deviation ≤ 0.0009 at every s.
4. **A bare joint channel is NOT bounded at 2√2** (prompt Q1, answered negatively — the run's one
   genuinely new number): a different marginal-preserving joint rule (deterministic sign-copy)
   returns **S = 4.0000** with marginals intact (dev 0.0007). So "the throughpole is non-local"
   explains too much by itself: an unconstrained joint readout permits super-observed correlations.
   **The entire burden is the specific weighting** — the machinery that would make a split pair's
   joint landing counts follow the observed cos² law.

## The one-debt reduction (what this run earned)

The Bell debt and the Born/residence debt are **one debt**. A derived residence law (how landing
counts of a steered vortex pair distribute — QM04's open core; the same law as QM07's sequential
re-projection cos²(θ/2)) would, plugged into the throughpole channel, decide Bell outright:
land at the observed 2√2, undershoot (falsifiable SDT departure), or overshoot (channel killed).
Until that machinery exists, QM05 is **OPEN** and census §8.2 debt #1 **stands, bounded and named**.

## HUNTER §D — seven questions (verdict is OPEN → mandatory)

1. **Why (exact mechanism)?** Any per-wing readout of a shared λ factorises
   E(a,b) = ∫A(a,λ)B(b,λ)ρ(λ)dλ ⇒ CHSH ≤ 2 (measured: saturates at 2.0000). Observed data ≈ 2.4;
   the shortfall is 0.4–0.83 in S. The failure is arithmetic, not numerical noise.
2. **Recoverable?** Only by a non-factorising readout. ~~SDT owns exactly one candidate structure~~
   **[FARMER correction 2026-07-03: SDT owns TWO named structures, which are one object — the
   throughpole (the channel: in/out flow never terminates) AND the FLM07 geared rotation (the
   machinery: the split pair remains one 1:4 void-geared rotational system, so one wing's readout
   mechanically constrains the geared partner's conjugate state at readout). The original prompt
   transcription dropped the gearing, which is why this verdict found only the channel and no
   weighting mechanism. The local kill stands — Bell's inequality is a theorem about the factorised
   form itself — but the joint weighting now has a named mechanical owner.]**
3. **What did the target fail to account for?** The readout stage. The split-pattern model treats
   measurement as two independent local wake samplings; the shared through-flow at readout is
   unmodelled machinery.
4. **Errored premise?** "Measurement = independent local sampling at each wing." The pair's
   construction was shared; its *readout* was assumed separable.
5. **What freedom corrects it?** A joint residence law across the pair — one landing account, two
   ends, weighting fixed by mechanics.
6. **Native quantity or bare knob?** The *channel* is native (throughpole, already in the
   ontology). The *weighting* is currently neither derived nor tuned — we imported the observed
   curve as a probe and proved (S=4 probe) that the channel alone cannot fix it. It is a **named
   closure debt**, not a knob: nothing was fished, nothing fitted.
7. **Cascade?** **YES.** Shares its root with QM04 Phase-2 (residence ∝ energy density) and QM07
   Phase-4 (sequential-SG cos²(θ/2)): all three owe the same law — *how a steered vortex's landing
   count follows the wake's squared amplitude*. Root id: **RESIDENCE-LAW**.

**Recovery grade: PARTIAL** — route and errored premise named; the correcting freedom (joint
residence law) identified as native-candidate but not yet justified by machinery. Per the Closure
Principle: the fix is to CLOSE the residence-law loop, not to amputate the throughpole.

## What would change the verdict

- Residence law derived from relay machinery (QM04) → re-run Phase 2 with the derived weighting;
  wherever S lands (2√2, under, over) is then a real SDT prediction → NATIVE or KILLED, either way paid.
- Proof the throughpole cannot couple readouts → F, debt permanent.

## New questions logged

1. Does the joint-readout structure extend to GHZ (three wings, one λ)? Not run — OPEN.
2. What machinery *excludes* the S=4 sign-copy rule in nature? SDT owes its own exclusion
   principle (its "why not 4"). OPEN — likely the same RESIDENCE-LAW root.

---
**Prompt completion B · Physics class OPEN (local branch KILLED; probe branch = OBSERVED-data
diagnostic, not SDT machinery) · Recovery PARTIAL · Cascade root RESIDENCE-LAW**

---

# QM05 — RUN 2 VERDICT (2026-07-07): the action/reaction quadrature split

> **Provenance:** Harvey, verbatim: "no one in there thought to split that into action and
> reaction? 2 out the back gives 2 forward." Spec: RUN_LOG ADJ-R2-1, committed before code.
> Tool: `qm05_r2_quadrature.py` (exit 0; `qm05_r2_results.txt` = teed stdout; seed 13,
> N = 10^6/cell). One instrument fault, caught by its own gate and logged: the anchor arm's
> first build squared cos(2Δ) instead of doubling cos²(Δ) → S ≈ 0; one-line fix, no other
> arm touched (the ψ=0 physics arm is algebraically the anchor and had already landed 2.8282).

## Gates (committed in ADJ-R2-1; none widened)

| Gate | Result | Call |
|---|---|---|
| G-A anchor (run-1 P2 weighting reproduced) | S = +2.8269, marg dev 0.0010 | **PASS** |
| G-1 ceiling: conserved unit kick, full ψ scan | max S = **+2.8282** at ψ=0; no ψ above 2.8334; S(ψ) tracks 2√2·cos ψ at every point | **PASS** |
| G-1 per-pair prediction (|E| = 1/√2 each) | +0.7076 / −0.7076 / +0.7058 / +0.7077 | **PASS** |
| G-2 control: conservation OFF (per-pair kick renewal) | S = **+4.0000**, marginals flat (0.0003) | **PASS** |
| G-3 no-signalling, every arm every pair | worst dev 0.0013 (< 0.002) | **PASS** |
| G-4 the ×2 identity (joint vs independent Malus) | ratio = 2.0003 | **PASS** |

## What is now on the record

1. **The vector theorem (pure algebra, printed):** the four CHSH direction combinations in
   doubled-angle director space sum to a vector of length **exactly 2√2**, pointing along the
   symmetric axis. Hence for ONE conserved unit kick k̂: S(ψ) = k̂·Σ = 2√2·cos ψ. **Tsirelson
   = |one conserved kick| × |the CHSH geometry's own vector sum|.** Nothing else enters.
2. **The conservation⇔ceiling link (the new falsifiable content):** |k̂| = 1 enforced →
   ceiling 2√2, measured. Kick renewed per setting pair (reaction-free limit) → 4.0000,
   measured, marginals still flat. **S = 4 is an overdraw — per-pair |E| = 1 at four pairs of
   one conserved vector is unrealisable at unit norm.** Run-1's owed exclusion ("what
   machinery stops nature at 2.828 instead of 4") is **PAID, conditionally**: conditional on
   the conserved-kick channel model. The PR box is not exotic; it is a gearbox with no
   reaction torque.
3. **The observed correlation law re-derives with its square dissolved:** P(same) = cos²(Δ)
   ≡ (1 + cos 2Δ)/2 = mean + LINEAR projection of the conserved kick (disclosure committed in
   ADJ before running). The Bell readout is linear in the kick. **Consequently the ADJ-6
   bridge C^p/(C^p+S^p) is a MIS-TRANSCRIPTION: no residence exponent p enters the Bell
   readout at all.** FLM14 run-6's super-quantum tension (p_occ ≈ 2.6 ⇒ S ≈ 3.26) DISSOLVES —
   Bell never consumed p_occ. The Born question re-poses as channel geometry: why the readout
   is the projection of ONE conserved kick (quadrature/Law-V form), not why a power law has
   exponent 2.
4. **Structural bonus rows (report):** the classical bound S = 2 appears at ψ = 45° — the
   local ceiling is the half-way projection of the same conserved kick; and the per-pair
   optimum |E| = 1/√2 = 0.7071 is the model's own prediction and the measured per-pair value
   in real Bell experiments. The ×2 identity (2√2 = 2×√2) is mechanical: independent wings
   pay the projection twice; one object pays it once.

## Honest class and what is NOT claimed

**Class: NATIVE-conditional** — conditional on (a) the throughpole/one-object channel (run-1
ontology) and (b) doubled-angle director geometry (gear-tooth alignment; native). If the
projection-cosine is judged an import, the result caps at CONSTRUCTION — but the
conservation⇔ceiling link and its control survive either judgement, and they are new. NOT
claimed: why the kick locks to the pair's director (ψ = 0; any misalignment only LOWERS S —
sub-quantum, never super); a derivation of the channel model itself (that remains FLM14's
residence program, now decoupled from the Bell ceiling); "SDT reproduces entanglement" (the
run-1 prohibition stands).

---
**Prompt completion A (all committed gates PASS; instrument fault self-caught and logged) ·
Physics class NATIVE-conditional (Tsirelson = conservation × CHSH geometry; S=4 = reaction-free
overdraw — run-1's owed exclusion PAID conditionally) / the ADJ-6 bridge retired as
mis-transcription (Bell is linear in the kick; run-6's super-quantum tension dissolved) ·
Recovery n/a · Cascade: RESIDENCE-LAW re-scoped (Born question → channel quadrature geometry,
Law-V form); FLM14 Part C license criteria to be re-drafted against the corrected bridge.**
