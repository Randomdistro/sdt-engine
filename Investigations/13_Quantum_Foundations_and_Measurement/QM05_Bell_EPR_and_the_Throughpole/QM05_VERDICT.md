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
