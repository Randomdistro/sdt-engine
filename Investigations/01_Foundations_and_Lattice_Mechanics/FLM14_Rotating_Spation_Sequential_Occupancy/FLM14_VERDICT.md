# FLM14 — VERDICT (first run, 2026-07-04)

> Tool: `flm14_rotor_tour.py` (exit 0; `flm14_results.txt` = real stdout). Gates pre-committed
> in `RUN_LOG.md` before code; none moved. beta scanned as declared, nothing fitted.

## Results against the committed gates

- **P1-G1 PASS** — the stepping rule closes in five native quantities: {φ, ω₀, g=−1, W, β}.
- **P1-G2 PASS (the run's earned result)** — gearing frustration on FCC neighbourhoods =
  **0.347 of bonds unsatisfiable**: antisymmetric contact gearing CANNOT be globally smooth on
  a lattice with odd rings, so **rotation must be carried by defects** — the native origin of
  OP-2 (particles = quantised vortices) falling out of the gearing premise itself. Harvey's
  "the spation MUST rotate" acquires its structural companion: *and the lattice cannot let that
  rotation be uniform — it precipitates carriers.*
- **P1-G3 FAIL (rule-form-1 KILLED as implemented)** — front-speed anisotropy geared/ungeared
  = 0.0934/0.0125 = **×7.47** (gate ≤1.2). The naive form ties every window to a global clock
  (`2ωt` in each bond test): windows open in lattice-wide synchronous waves, and the frozen
  random phases gate directions unequally. Killed honestly; not retro-passed.
- **P2 NOT ANSWERABLE by this instrument** — the minimal ring tour visits every seat equally,
  so its self-wake converges to near-uniform amplitude: no amplitude spread → no measurable
  exponent (reported at every β). This is an instrument limitation, not a physics null: the
  dwell-law question REQUIRES a structured seat geometry where wake amplitude varies.
- **P2-G2 / P3–P5: DEFER** per pre-commitment (no tuned peek at the Lamb table).

## §D — seven questions (on the P1-G3 kill and P2 deferral)

1. **Why exactly?** Global-clock windows synchronise lattice-wide → propagation advances in
   breathing waves whose interaction with frozen phase texture is direction-unequal (×7.47).
2. **Recoverable?** Plausibly — the correcting form is **bond-local gating**: windows set by the
   RELATIVE phase of the two rotors evolving at local rates, no global t in any bond test.
3. **What did the target fail to account for?** That "geared rotation" has two inequivalent
   formalisations (global-clock vs bond-local), and only one was tested.
4. **Errored premise?** "One global tick phase serves all bonds."
5. **What freedom corrects it?** Per-bond relative phase — already native (each rotor has φ).
6. **Native or knob?** Native — it removes a global structure rather than adding a parameter.
7. **Cascade?** **YES — everything lands on ROOT-SIM.** Bond-local gating at FLM10 grade, and a
   structured 2-D/3-D seat geometry for the tour, are both the lattice solver's job — the same
   build the STACK ranks priority 1 (pays FLM09-A2, PPT07 wake, GD05 crossover, 6π⁵ mechanism).

**Recovery: PARTIAL** — route and premise named, correcting freedom native, not yet built.

## What stands after run 1

The all-in premise took its first honest fire: the **frustration result is real support**
(rotation cannot be uniform; carriers are forced), the **first rule-form died cleanly**, and
the **decisive questions (dwell exponent, Lamb routes, lock ladder) now name their instrument**:
bond-local gearing on the FLM10-class solver. The program is alive, unfished, and one build
away from its make-or-break.

---
**Prompt completion B · Physics class: P1-G2 NATIVE (frustration-forced carriers) / rule-form-1
KILLED / P2 OPEN-instrument · Recovery PARTIAL · Cascade root: ROOT-SIM (lattice solver).**

---

# FLM14 — VERDICT, Run 2 (2026-07-04): rule-form-3 on the FLM10-grade solver

> Tool: `flm14_solver.py` (exit 0; `flm14_solver_results.txt` = real stdout, teed).
> Instrument pre-committed in RUN_LOG ADJ-4/ADJ-5/ADJ-6 before code; ADJ-7 (Harvey
> two-channel directive) logged mid-run BEFORE acting on it — it touched only the
> unlicensed Part C wording; no executed gate moved. Machinery anchor: at beta=1 geared
> must equal ungeared identically — measured max |t_g − t_u| = 0.00e+00.

## The rule-form ladder (the committed deliverable)

| form | window rule | anisotropy ratio (gate ≤1.2) | verdict |
|---|---|---|---|
| 1 | global clock | ×7.47 | KILLED (run 1) |
| 2 | bond-local relative phase | ×2.88 (old jittered-FCC) / **×2.29 ± 0.12** (β=0 control, this CRN) | FAIL |
| 3 | bond-local + entrainment | β=0.05 ×2.24 · β=0.1 ×2.15 · β=0.2 ×2.07 · β=0.4 ×1.96±0.43 · β=0.8 ×1.35±0.27 · **β=1 ×1.00 exactly** | **FAIL at every non-degenerate β** |

N=1000 WWW/Keating CRN, 3 glass seeds, 24 directions, all 24 valid in every arm. Entrainment
anneals monotonically — mean wait falls 0.102 → 0.030 → 0 and the ratio tracks it — but the
gate is passed ONLY at the saturation endpoint β=1, where the kick fully locks every contact,
all waits vanish, and geared dynamics becomes IDENTICAL to ungeared. That is a degenerate
pass: rotation gating does no work on the pulse channel at all. Not retro-claimed as a pass.

## P2 — emergent exponent p(β): NONE DEFINED (reported as such)

| β | p_dwell | p_occ | drift (<1%) | coverage |
|---|---|---|---|---|
| 0.02 | undefined (3–5 usable seats <12) | undefined | PASS 0.0044 | 33% |
| 0.05 | undefined (1–6 seats) | undefined | PASS 0.0014 | 29% |
| 0.10 | undefined (1–11 seats) | undefined | PASS 0.0008 | 49% |
| 0.20 | undefined (1–4 seats) | undefined | PASS 0.0006 | 17% |
| 0.40 | undefined (2–8 seats) | undefined | FAIL 0.0062 | 34% |
| 0.80 | undefined (\|r\|=0.37–0.51 <0.6) | undefined | FAIL 0.0483 | 71% |

The structured geometry fixed ADJ-2's fault (amplitude spread now exists, ×16–24), but the
wake CONCENTRATES: the deterministic tour self-traps on a short cycle (coverage 17–49% at
β≤0.4), pinning ~30 of 42 seats below 5% of max amplitude — under the committed criteria no
exponent is definable at any β. T_W robustness (13.5/54): undefined both ways, consistent.
**Part C NOT RUN** (committed ADJ-6 condition); the ADJ-7 reclassification is therefore
logged but untested this run.

## §D — seven questions on the form-3 kill (P1-G3)

1. **Why exactly?** Residual anisotropy tracks residual wait ~linearly (0.102→×2.29;
   0.030→×1.35; 0→×1.00): the waits ARE the texture. Entrainment scales waits by (1−β) but
   does not decorrelate their direction-unequal spatial pattern at this system size.
2. **Recoverable?** Two named routes: (a) saturation β→1 — trace-free gearing on the pulse
   channel, which is exactly ADJ-7's two-channel picture (windows live on the constraint
   channel; pulses see none of it); (b) system-size self-averaging (FLM10's A^U fell with N;
   the geared/ungeared ratio might too) — untested.
3. **What did the target fail to account for?** That ANY finite wait inherits the quenched
   phase texture; annealing shrinks the texture, it does not erase its correlation.
4. **Errored premise?** "Entrainment anneals the texture" — it only rescales it.
5. **What freedom corrects it?** Full contact-locking (the β=1 limit / constraint-channel
   rigidity) — native, already in the rule; but claiming the β=1 identity as a pass would be
   claiming a tautology. Refused.
6. **Native or knob?** β was declared exploratory and scanned; nothing fitted.
7. **Cascade?** ROOT-SIM: the surviving candidate is NOT "partially entrained gearing" but
   "gear-locked cluster = rigid (constraint channel), pulse channel transparent" — form-3
   with partial β is dead; the two-channel form is the named successor (rule-form-4).

## §D — seven questions on the P2 no-exponent result

1. **Why exactly?** Self-entrainment is self-ATTRACTING: the wake the electron leaves makes
   its return easier, so the tour collapses onto a short cycle and freezes most seats out of
   the amplitude mask (<12 usable seats at every β; at β=0.8 coverage recovers to 71% but
   closure drift fails at 0.048).
2. **Recoverable?** Named: (a) ensemble over initial phase — R-seq says probability IS
   ignorance of the starting tick; single-history statistics was the instrument's choice,
   not the spec's; (b) 3-D seat geometry with richer adjacency (2-D annulus degree ~4
   favours short cycles); (c) the rule-form-4 constraint channel changes trapping dynamics.
3. **What did the target fail to account for?** Born-class statistics need ergodic visiting
   with structure-dependent weights; the lock-pull kick produces attractor selection instead.
4. **Errored premise?** "The tour visits all seats with weights" — it selects a subset.
5. **What freedom corrects it?** Ensemble-over-phase is native (§0 R-seq, verbatim). A
   per-observable kick-sign change would be a knob — refused.
6. **Native or knob?** Nothing was tuned; all six β reported with reasons.
7. **Cascade?** NEW ROOT NAMED — **SELF-TRAPPING / F6 TENSION**: P1 wants β→1 (isotropy),
   P2's only ergodic-looking regime (β=0.8) fails closure — the two phenomena pull the ONE
   permitted parameter to incompatible ends. Under F6 that is the sharpest honest strike
   yet against rule-form-3 as a single mechanism, and the strongest argument that the
   pulse-channel kick and the cluster-locking constraint are TWO channels (ADJ-7), not one.

## What stands after run 2

Rule-form-3 is dead at every non-degenerate β; its death converges, from the isotropy side
alone, on the same two-channel structure Harvey directed independently mid-run (ADJ-7).
The residence law remains UNPAID; its instrument successor is named (ensemble-over-phase on
a 3-D seat geometry under rule-form-4). P3 (Lamb routes) and P4 (lock ladder) stay DEFERRED:
dependencies = a stable emergent exponent (still absent) + PPT08_KOPPA_TARGET seat ladder +
NP10 contact windows. Part C stays unlicensed; ADJ-7's marginal-anchor reclassification and
constraint-channel implementation are in the instrument, awaiting a licensed run.

---
**Prompt completion B · Physics class: rule-form-3 KILLED (non-degenerate regime; ladder
7.47 → 2.88/2.29 → 1.35 → 1.00-degenerate) / P2 OPEN — no exponent defined at any β
(self-trapping named) / Part C NOT LICENSED · Recovery PARTIAL (rule-form-4 = ADJ-7
two-channel; ensemble-over-phase named) · Cascade roots: ROOT-SIM · SELF-TRAPPING/F6-tension.**

---

# FLM14 — VERDICT, Run 3 (2026-07-04): RULE-FORM-4, two-channel dynamics

> Tool: `flm14_form4.py` (exit 0; `flm14_form4_results.txt` = real stdout). Instrument
> pre-committed in RUN_LOG ADJ-8 (form-4 rule + ensemble + 3-D seats), ADJ-9 (probe),
> ADJ-10 (hop budget, logged before production after a declared smoke test). No gate,
> criterion, or rule constant moved. Machinery reused from `flm14_solver.py` verbatim.

## P1 — the ladder terminates, and the gate DISSOLVES (not "passes")

| form | rule | ratio (gate ≤1.2) | verdict |
|---|---|---|---|
| 1 | global clock | ×7.47 | KILLED (run 1) |
| 2 | bond-local relative phase | ×2.88 / ×2.29 | FAIL (ADJ-3 / run 2) |
| 3 | + entrainment kick β | ×1.35 best non-degenerate | KILLED (run 2) |
| 4 | two channels: pulse at c, constraint rigid | **×1.0000 ± 0.0000, max\|t_g−t_u\| = 0.00e+00** | trivially satisfied BY ARCHITECTURE |

Stated plainly (pre-stated in ADJ-8 before the run): form-4 does not EARN P1-G3 — it
removes the gate's discriminating power. Gearing lives on the constraint channel; the
pulse channel cannot see it, so light-speed isotropy is exact by construction. P1-G1
holds at 5 native quantities {base φ, ω_i = ω₀z_i/⟨z⟩, g=−1, W, lock-rigidity}; β no
longer exists on the lattice channel — run-2's F6 tension (P1 pulling β→1 against P2's
closure) is DISSOLVED structurally, not re-tuned away.

**The residual gearing signature — where the falsifiable content now lives** (measured,
3 glasses): locked-bond fraction **47.9%** (window duty W=0.5 forecast, honest match);
frustrated same-cluster refusals **41.8/52.9/48.7%** (the P1-G2 carrier population at
work; denominator differs from the 0.347 bond census — not a contradiction, reported);
constraint network **percolates (85.5% of sites in one rigid cluster)**; the percolated
cluster's collective rate collapses to **\|Ω\|/ω₀ = 0.0046** — *gear-locking freezes
rotation*: a near-static rigid backbone threaded by frustration-forced carriers, which
is OP-2's picture arrived at from the gearing side. Lock-network anisotropy 0.058.

## P2 — first defined exponents ever; still NO stable regime (committed rule)

64 phase draws × 40,000 hops, 3-D shells {8,13,21}, degree 6/7.48/10, pooled per ADJ-8:

| β | p_occ (pooled) | drift <1% | coverage pool/draw | split-half |
|---|---|---|---|---|
| 0.02 | undefined (6 seats <12) | PASS 0.0006 | 71% / 26% | — |
| 0.05 | undefined (\|r\|=0.55) | PASS 0.0027 | 83% / 32% | — |
| 0.10 | undefined (10 seats <12) | PASS 0.0063 | 86% / 36% | — |
| 0.20 | **+2.375** (\|r\|=0.63, n=17) | PASS 0.0003 | 95% / 46% | undef / +2.457 |
| 0.40 | **+2.325** (\|r\|=0.69, n=23) | PASS 0.0011 | 100% / 54% | undef / +1.736 |
| 0.80 | undefined (spread ×2.9) | FAIL 0.1118 | 93% / 28% | — |

Two consecutive defined betas; the committed rule requires **three** → **NO stable
regime; Part C NOT RUN** (ADJ-6 condition held). The ensemble + 3-D corrections did
real work — pooled coverage 71→100% vs run-2's 17–49%, closure drift now passes across
β≤0.4, and p_occ is *defined* for the first time in the program — and the defined values
sit at +2.3–2.4 with T_W=54 robustness giving +2.291. That is Born-adjacent and is NOT
claimed: split-half first-halves are undefined at both betas, geometry seed 2 fails to
replicate (\|r\|=0.47), and the regime is one β short. Direction of travel reported;
nothing graded.

## Part D — ADJ-9 probe: NOT FOUND

Four declared observables, one scan: R1 = 0.109, R2 = 0.0046, R3 = 0.0057 (rim speeds —
the frozen backbone kills them), R4 = 0.997. **No 0.9186 anywhere in locked-cluster
kinematics.** A miss is a miss; NP14's seat gets no support from this channel.

## §D — seven questions (on the P1-G3 dissolution and the P2 shortfall)

1. **Why exactly?** P1: with waits removed by architecture there is no pulse-channel
   observable left for gearing to fail — the gate measures nothing about form-4. P2:
   per-draw tours still self-trap (26–54%); pooling flattens the log-log correlation to
   \|r\| ≈ 0.5–0.7, right at the committed 0.6 threshold, so definedness survives only
   in the mid-β window — which is one β narrower than the stable-regime rule demands.
2. **Recoverable?** Named: (a) statistics — more draws/denser seats push \|r\| through
   its threshold where p is already defined; (b) the constraint channel is NOT yet in
   the tour: the electron rule is ADJ-5 pulse-channel verbatim (ADJ-7 pt 4 kept it so).
   Form-4 locking of seat rotors during dwell is the named next instrument — new ADJ
   required; not run here.
3. **Unaccounted for?** That the exponent-DEFINABILITY window (instrument) could be
   narrower than the physics window; the committed ≥3-consecutive rule gates on both.
4. **Errored premise?** None found in the rule; the shortfall is threshold-adjacent
   statistics, not a sign error or attractor pathology (drift now passes).
5. **Correcting freedom?** Ensemble size and seat density (native, no rule change);
   tour-side constraint channel (native — it is form-4's own architecture).
6. **Native or knob?** Nothing fitted. ADJ-10 (hops 8k→40k) was logged before
   production from a declared smoke test; gates unmoved. β remains a scanned scan.
7. **Cascade?** SELF-TRAPPING root: softened (coverage cured in the pool, not per
   draw). F6-tension root: CLOSED by architecture. ROOT-SIM: form-4's rigid-backbone
   + carriers picture is now the concrete candidate core. Bell/CHSH debt: still
   unlicensed, now waiting on one β of definedness, not on a whole mechanism.

**Recovery: PARTIAL — the residence law is one instrument step from decidable, and the
step is named twice over (statistics; tour-side constraint channel).**

## What stands after run 3

The isotropy ladder is closed: its lesson was never "anneal harder" but "gearing and
relay are different channels" — and with that separation made structural, the gearing
premise stops paying isotropy penalties and starts making its own falsifiable claims
(frozen percolated backbone, carrier census, window-duty lock fraction). The residence
law remains UNPAID but moved from "no exponent definable anywhere" (run 2) to "defined,
Born-adjacent, one β short of licensed" (this run). Part C stays sealed. The NP14
0.9186 seat is honestly absent from this scale's kinematics. P3/P4 remain DEFERRED on
P2's licence.

---
**Prompt completion B · Physics class: P1-G3 DISSOLVED-BY-ARCHITECTURE (ladder
7.47 → 2.88/2.29 → 1.35 → 1.0000-structural; residual signature = frozen percolated
constraint backbone, 47.9% lock, \|Ω\|/ω₀ = 0.0046) / P2 OPEN — p_occ defined at
β={0.20, 0.40} (+2.375/+2.325), NO stable regime (2 of 3 consecutive), Part C NOT
LICENSED / ADJ-9 probe: 0.9186 NOT FOUND · Recovery PARTIAL (statistics; tour-side
constraint channel — new ADJ required) · Cascade: F6-tension CLOSED · ROOT-SIM inherits
the rigid-backbone-plus-carriers core.**

> **SCOPING ANNOTATION (2026-07-05, Harvey §G audit — verified on disk by grep):** run 3's
> constraint channel was implemented in Part A (lattice) and Part C wording ONLY; `run_tour`
> contains no rigid-cluster coupling — **P2 ran single-channel.** Therefore the p_occ
> +2.375/+2.325 exponents AND the ADJ-9 0.918-probe negative are both scoped to the
> UNCORRECTED tour instrument. Neither is evidence about the two-channel tour. Run 4
> (tour-side constraint channel, new pre-committed ADJ) is the licensed instrument for both
> questions. The §G lesson: a correction applied to one part of an instrument is not a
> corrected instrument.

---

# FLM14 — VERDICT, Run 4 (2026-07-05): the TWO-CHANNEL TOUR

> Tool: `flm14_form4b.py` (`flm14_form4b_results.txt` = real stdout, complete — F6 footer
> present; session crashed post-run, verdict written from the file). Instrument
> pre-committed in RUN_LOG ADJ-11 BEFORE code (confirmed on disk, line 203). Held from
> ADJ-8/10: geometry, 64 draws × 40k hops, β grid, all criteria. New (ADJ-11): locks +
> same-tick rigid cluster kicks INSIDE the tour; claim rule hardened (regime AND
> split-half AND seed-2 replication). Nothing fitted; nothing moved.

## P2 on the licensed instrument — p(β), pooled (64 phase draws × 40k hops)

| β | p_occ (pooled) | drift <1% | coverage pool/draw | split-half (32/32) |
|---|---|---|---|---|
| 0.02 | undefined (10 seats <12) | FAIL 0.0113 | 86% / 31% | — |
| 0.05 | +2.278 (\|r\|=0.80, n=17) | FAIL 0.0766 | 95% / 53% | +1.858 / undef |
| 0.10 | +2.109 (\|r\|=0.76, n=18) | PASS 0.0028 | 100% / 61% | +2.161 / undef |
| 0.20 | **+2.040** (\|r\|=0.71, n=15) | PASS 0.0035 | 98% / 58% | **+2.015 / +2.128** |
| 0.40 | +2.855 (\|r\|=0.68, n=12) | PASS 0.0049 | 88% / 46% | +3.005 / +2.760 |
| 0.80 | +3.769 (\|r\|=0.82, n=16) | FAIL 0.0256 | 95% / 49% | +3.735 / +3.690 |

**NO stable regime by the committed rule — the honest refusal stands.** Three
consecutive drift-PASS defined betas exist (0.10/0.20/0.40) but β=0.40's +2.855 breaks
the ≤0.3 band around the median (+2.109) by 0.75. T_W robustness at β=0.20:
**+2.596 (T_W=13.5) / +2.040 (27) / +1.620 (54)** — the exponent slides monotonically
with wake memory. **Part C NOT RUN** (ADJ-11 conjunction unmet); seed-2 replication
never reached (gated behind a regime that did not form). Instrument guards: locked-dwell
time = 0.00e+00 at every β (the ADJ-11 rigidity theorem holds at production scale);
the receding-window guard fired (689–13,071 counts/β) against ADJ-11's "expected zero"
— wrong expectation, harmless dynamics: every occurrence coincides with an available
zero-gap locked bond, none was ever selected, no halts. Reported as declared.

## Run-3 → run-4 comparison (stated without claiming)

Single-channel (run 3, unlicensed): +2.375/+2.325 at β=0.20/0.40, \|r\|=0.63–0.69,
split-half first-halves undefined, seed-2 failed. Two-channel (this run): at the stable
centre **+2.109/+2.040**, \|r\|=0.71–0.80, and at β=0.20 BOTH split-halves defined and
tight (+2.015/+2.128). Bringing the constraint channel into the tour moved the measured
exponent TOWARD the Born value and made it half-replicable at the centre. That is
direction of travel, not a result: no regime, T_W sensitivity unresolved, seed-2 untested.

## Probe (ADJ-11 re-scope, one scan @ β=0.20 fixed): NOT FOUND

Q1 = 0.52655 (star rate retention) · Q2 = 0.85505 (star rim speed, units c) ·
Q3 = 0.99953 (effective tour speed) · Q4 = 1.12895 (lock selection). Four misses at the
1% window; **no 0.9186 in two-channel tour kinematics either.** Both instruments have
now answered honestly; NP14's seat remains unsupported from FLM14 at this scale. Q2's
0.855 is 7% off — noted as a miss, not massaged. No second scan.

## §D — seven questions on the no-regime result

1. **Why exactly, the β=0.40 upturn?** Strong kicks + σ-signed back-action concentrate
   the wake: usable seats fall (18→15→12), coverage drops (100→98→88%), and the
   surviving high-amplitude seats steepen the log-log slope (+2.855, then +3.769 at
   β=0.80). The upturn is amplitude-mask erosion, and it is exactly what the ≤0.3 band
   exists to catch — the rule worked.
2. **Why is p T_W-sensitive?** The wake ledger dφ is BOTH dynamics and the measured
   amplitude A; T_W sets how much history A integrates, so p is currently a JOINT
   property of the residence dynamics and an instrument memory constant. A residence
   LAW must be T_W-independent: either T_W has a native value to be derived (FLM03
   co-rotation / FLM09 reconnection lifetimes are the candidates) or A must be
   re-defined memory-free. Until then p ≈ 2.0 at (β=0.20, T_W=27) is a point reading.
3. **Seed-2 unreached — statistics or structure?** UNKNOWN by construction: the
   hardened claim rule gated replication behind a regime that never formed. Named for
   the next ADJ: run seed-2 UNCONDITIONALLY at the two centre betas.
4. **Errored premise?** One, owned: ADJ-11's "(expected zero)" on the receding-window
   guard. The dynamics were right, the expectation wrong; no gate involved.
5. **What freedom corrects it?** Unconditional seed-2 (statistics); native-T_W
   derivation or memory-free amplitude (structure). Both declared, neither tuned.
6. **Native or knob?** Nothing fitted; grid, criteria, phase seeds, probe β all
   pre-committed; the upturn and the T_W slide are reported against the run's hopes.
7. **Cascade?** RESIDENCE-LAW: unpaid, but the two-channel tour is now its best
   instrument (centre p ≈ 2.04, split-half replicated). NEW DEBT NAMED —
   **WAKE-MEMORY (T_W-DEPENDENCE)**: the exponent is not a law until T_W is derived or
   eliminated. F6 intact. ROOT-SIM inherits the two-channel tour core unchanged.

**Named next step (requires a new pre-committed ADJ):** seed-2 unconditional at
β={0.10, 0.20} + T_W-drift diagnosis — declared p(T_W) scan with a pre-committed
functional test, or a native T_W derivation from FLM03/FLM09. No other freedom.

---
**Prompt completion B · Physics class: P2 OPEN — regime-without-claim REFUSED (three
consecutive defined betas broken by the β=0.40 upturn, +2.855 vs median +2.109; centre
reading +2.040 with split-half +2.015/+2.128 at β=0.20; T_W slide 2.596→2.040→1.620
named as WAKE-MEMORY debt) / Part C NOT LICENSED (ADJ-11 conjunction unmet) / ADJ-11
probe on the licensed two-channel instrument: 0.9186 NOT FOUND (Q1–Q4 all miss) ·
Recovery PARTIAL (unconditional seed-2; T_W diagnosis — new ADJ) · Cascade: WAKE-MEMORY
root opened; RESIDENCE-LAW instrument upgraded; ROOT-SIM unchanged.**

---

# FLM14 — VERDICT, Run 5 (2026-07-05, recorded 2026-07-06): the claim decision

> Tool: `flm14_form5.py` (exit 0; `flm14_form5_results.txt` = real stdout). Spec = RUN_LOG
> ADJ-12, committed before code, ordered by Harvey. Machinery = flm14_form4b verbatim;
> machinery anchors reproduced run-4's +2.596/+2.040/+1.620 exactly at the declared
> tolerance. Nothing re-tuned; the pre-declared honesty note (refusal expected from run-4's
> table; unconditional legs run anyway) held.

## CLAIM DECISION: REFUSED — blockers named per ADJ-12

- **Leg (i) stable regime: FAIL** (run-4 table cited, not re-run — β=0.05 drift-FAIL and
  β=0.40 band-break pincer the grid).
- **Leg (ii) split-half: FAIL at β=0.10** (one half undefined; β=0.20 passes).
- **Leg (iii) seed-2 replication: FAIL at β=0.10** (+2.871 vs +2.109, band and split-half
  both broken); **PASS at β=0.20** (+2.186 vs +2.040, band OK; split-half +1.983/+2.176 OK).
- **Part C: NOT RUN** (committed condition). No Born claim; no CHSH licence.

## What run 5 nevertheless settled (evidence standing alone, as ordered)

1. **The β=0.40 upturn is instrument, not dynamics — MASK-EROSION SUPPORTED.** On the FIXED
   β=0.20 seat mask the β=0.40 slope is +2.270, within the declared 0.3 of the centre
   +2.040 (own-mask +2.855). One of leg (i)'s two pincers is now diagnosed as seat-selection
   artifact. Run-4 §D-1's hypothesis is paid.
2. **The centre reading replicates across geometry.** β=0.20: seed-2 pooled +2.186 against
   seed-1 +2.040, both split-halves defined and tight. The ~2 exponent is not a property of
   one glass realisation. Honest caveat, not hidden: seed-2 fails the <1% closure drift at
   BOTH betas (0.0298/0.0639) — the drift criterion is geometry-sensitive; the replication
   PASS is per ADJ-12's committed definition, which did not include drift.
3. **WAKE-MEMORY hardened from slide to dissolution.** T_W scan {13.5, 27, 54, 108}:
   +2.596 / +2.040 / +1.620 / **undefined** (|r| = 0.43 < 0.6 at T_W=108). The declared
   convergence rule cannot evaluate (Δ2 undefined) → diagnosis INCONCLUSIVE as committed —
   but the honest reading is worse than a monotone slide: at long memory the log-log
   relation itself dissolves. p is a window property of the wake-amplitude instrument.

## §D — seven questions

1. **Why exactly?** The measured amplitude A integrates T_W of wake history; the exponent
   inherits the integration window and vanishes when the window blurs the seat contrast.
2. **Recoverable?** Named, one route ranked first: **a memory-free residence measure** —
   occupancy against dwell-count fraction (a counting measure, no instrument constant),
   which is verbatim the spec's own ontology ("Born = dwell time"). Second: derive a native
   T_W from FLM03 co-rotation / FLM09 reconnection lifetimes. Neither attempted this run
   (neither was declared — attempting one post-hoc would be fishing).
3. **What did the target fail to account for?** That A imports an instrument constant; a
   residence LAW must survive with none.
4. **Errored premise?** None new; ADJ-12 executed clean; run-4's "(expected zero)" fault
   was already owned.
5. **What freedom corrects it?** The dwell-count measure is native (§0 R-seq, verbatim); a
   per-run T_W choice would be a knob — refused.
6. **Native or knob?** Nothing moved; anchors exact; scan, bands, and the fixed-mask test
   all pre-declared in ADJ-12.
7. **Cascade?** WAKE-MEMORY deepened (dissolution, not slide). MASK-EROSION closed (paid).
   RESIDENCE-LAW unpaid, instrument now geometry-replicated at the centre. NEW DEBT NAMED —
   **DRIFT-GEOMETRY**: the closure-drift criterion fails on seed-2 at betas where seed-1
   passes; either the criterion or the glass generation carries a geometry sensitivity that
   must be understood before any future leg (i) can be trusted.

**Named next step (requires a new pre-committed ADJ — run 6):** re-run the β grid with the
memory-free dwell-count measure, seed-1 AND seed-2, claim conjunction unchanged. If p ≈ 2
survives with no instrument constant, the claim is live again; if it does not, rule-form-4's
Born story dies honestly.

---
**Prompt completion A (ADJ-12 executed in full; unconditional legs honoured) · Physics
class: P2 claim REFUSED (three blockers named) / MASK-EROSION SUPPORTED (β=0.40 pincer =
artifact) / seed-2 centre replication PASS-with-caveat / T_W diagnosis INCONCLUSIVE-hardened
(p undefined at T_W=108) / Part C NOT RUN · Recovery NAMED (run-6 memory-free dwell measure)
· Cascade: WAKE-MEMORY deepened · MASK-EROSION closed · DRIFT-GEOMETRY opened.**

---

# FLM14 — VERDICT, Run 6 (computed 2026-07-07 00:35; verdict recorded same day): the memory-free measure

> Tool: `flm14_form6.py` (exit 0; `flm14_form6_results.txt` = teed stdout). Spec: ADJ-13,
> committed before code. Machinery = flm14_form4b VERBATIM, dynamics untouched (T_W=27 stays
> in the dynamics); THE ONE CHANGE: A → A_mf = per-hop |net wake deposit| — no decay, no
> history, no T_W in the measure. **Anchors exemplary:** imported form4b reproduces run-4's
> +2.040 exactly; this tool on the old measure differs by 0.00e+00 — the tours are
> bit-identical, the measure switch is licensed.

## CLAIM DECISION: REFUSED (ADJ-11 verbatim; blocker named)

- **Leg (i) stable regime: FAIL.** β=0.05 drift-fails (0.0766); the only possible 3-window
  {0.10, 0.20, 0.40} breaks the ±0.3 band — p_MF = +2.382 / +2.585 / **+4.191**.
- **Part C: NOT RUN** (committed condition). Seed-2: all four betas drift-FAIL
  (0.019–0.064) — the DRIFT-GEOMETRY debt reproduced bit-exactly from run 5, as it must be
  (dynamics unchanged).

## What run 6 settled (and it is load-bearing)

1. **WAKE-MEMORY is PAID — and the payment convicts the old centre value.** The memory-free
   exponent at the committed centre is **+2.585**, which is the T_W→0 limit of run-5's own
   family (2.596 @ T_W=13.5 → 2.040 @ 27 → 1.620 @ 54): instrument-coherent. The celebrated
   p ≈ 2.040 was the T_W=27 window's value, not the dynamics'. **With no instrument constant
   anywhere in the measure, the residence exponent reads ≈ 2.4–2.6 at the drift-passing
   centre and is NOT 2.**
2. **NEW DEBT — BETA-DEPENDENCE:** p_MF rises monotonically with kick strength on both seeds
   (seed 1: 2.109→2.382→2.585→4.191; seed 2: 2.227→2.966→3.376→3.487). Under the memory-free
   measure the exploratory β is exposed as load-bearing: no residence LAW exists until β is
   derived natively (FLM03's open co-rotation coefficient) or a β-independent regime is
   exhibited (system-size route, 3-D CRN seats — named since run 2, still unbuilt).
3. **DWELL-LEG NULL:** p_dwell(MF) is undefined at every arm on both seeds (|r| = 0.01–0.54).
   Against the instantaneous wake, dwell-TIME carries no power law — only occupancy (visit
   counts) does. Honest tension with the program's own "Born = dwell time" phrasing: as
   instrumented, Born-weight-as-occupancy survives partially; Born-weight-as-dwell-duration
   does not. Reported, not resolved.
4. **MASK-EROSION splits by geometry:** seed 1 CONTRADICTED (fixed-mask +4.542 — the MF
   dynamics genuinely steepen at β=0.40), seed 2 SUPPORTED (+3.487, within 0.3 of centre).
   The run-5 closure of this question was measure-specific; under MF it re-opens,
   geometry-dependent. Filed under DRIFT-GEOMETRY.
5. **THE EXPORT SHIPPED (the CH07 stake):** `flm14_run6_dwell_table.txt` — per-seat dwell
   fractions at β=0.20, both geometry seeds. **Labelled honestly: leads-grade input** — the
   dwell table is real measured output of an instrument whose residence law is UNCLAIMED, so
   any CH07 dwell-weighted well rerun it feeds is exploratory class until a residence law
   lands, per the re-open condition's own wording.

## §D — seven questions

1. **Why exactly?** Removing the T_W integration removes the smoothing that made p look
   β-stable; the raw per-hop deposit tracks kick strength directly.
2. **Recoverable?** Two named routes, both requiring new ADJs: (a) derive β from FLM03
   co-rotation (the coefficient has been open since the program began — it is now the SINGLE
   blocking unknown); (b) 3-D CRN seat geometry at larger N (the 42-seat annulus caps usable
   seats at 12–18 every run).
3. **What did the target fail to account for?** That "stability across β" under the old
   measure was window-borrowed, not dynamical.
4. **Errored premise?** None new; ADJ-13 executed clean; anchors 0.00e+00.
5. **What freedom corrects it?** A native β only. A fitted β would be the knob this program
   has refused five runs running — still refused.
6. **Native or knob?** Nothing tuned; one change, declared; diagnostics carried both measures
   side by side at every arm.
7. **Cascade?** WAKE-MEMORY closed (paid by construction). BETA-DEPENDENCE opened (owner:
   FLM03 coefficient). DWELL-LEG NULL logged against the program's own ontology wording.
   DRIFT-GEOMETRY unchanged, still open. RESIDENCE-LAW remains UNPAID — five debts stand.

---
**Prompt completion A (ADJ-13 executed in full; anchors 0.00e+00; claim rule verbatim) ·
Physics class: CLAIM REFUSED (leg-i blocker named) / WAKE-MEMORY PAID (memory-free exponent
≈ 2.4–2.6 at centre — the 2.040 was window-dependent) / BETA-DEPENDENCE opened / DWELL-LEG
NULL reported / Part C NOT RUN · Export delivered (leads-grade) · Recovery NAMED (native β
from FLM03, or 3-D CRN at scale — new ADJ required) · Cascade: RESIDENCE-LAW unpaid.**
