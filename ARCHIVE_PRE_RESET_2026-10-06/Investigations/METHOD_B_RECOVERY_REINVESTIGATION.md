# METHOD B — Recovery Re-investigation (dig deeper on the killed)
### Standalone runnable spec. A cold instance can execute this without prior context.
*Formalised from `HUNTER_PROTOCOL.md §K` + the 2026-07 phase lessons (I3 reversal, triton contraction, the corrected kill-criterion), 2026-07-23.*

## What this is
The complement to Method A. Method A is a **strict falsifier** — it is deliberately harsh and it throws
out live physics on technicalities (it has done so repeatedly). Method B takes **every KILLED / DEGENERATE
/ graveyard item** and asks a different question: *was this killed because the claim is false, or because
the kill was a purist artifact?* It is a recovery front — but it is **not** a resurrection engine, and the
guard against that is the whole discipline (see the leash).

## The corrected criterion (why re-open is even legitimate)
> **The Standard Model is sunk wherever it cannot account for a result that SDT can.**

The SM was *built* by fitting observation until it could predict — it never forward-predicted α, the
masses, the mixing angles, or g−2. So a claim does **not** need a novel forward prediction to count. Two
faces of a legitimate result:
1. **Divergent fork** — SDT and the SM predict different measurable values.
2. **Explanatory kill** — the SM can only absorb (as a free parameter, or a dark epicycle) what SDT
   derives or dissolves from structure. Reproducing an existing result the SM cannot account for, with
   fewer knobs, is a result.

Method A, applied too strictly, kills #2 as "mere convergence / re-derivation." Method B recovers those.

## Fine-tuning is the method, not the sin
The honesty gate is inside the phrase *fit until it predicts accurately.* Fitting is legitimate model
building (the SM did it). The discipline:
- **Fit** the structural relationship to the measured value.
- **Certify it a fit** — `CALIBRATED`, never `DERIVED`. (A fit dressed as a derivation is the graveyard's whole population.)
- **Validate out-of-sample** — the fitted relation must then predict a value it was *not* fitted to.
- **Only then** does it graduate `CALIBRATED → DERIVED`. Fit-and-stop stays CALIBRATED forever.

## The re-open triggers (what makes a kill suspect)
For each killed item, test whether the kill fell into one of these. Any hit → re-open under Method A's
Adjudicator (§H). *These are the babies-in-the-bathwater signatures — each one was seen this phase:*
1. **Flawed test / wrong observable** — the kill measured a quantity structurally blind to the effect. *(I3: correlated the isotope-blind ionisation ladder against isotope-variable n_t — a constant vs a variable, null by construction. The coupling lived in the isotope shift, which the test discarded.)*
2. **Purist criterion** — killed for lacking a forward prediction it never needed (the SM didn't have one either). Re-score under the corrected criterion: does SDT account for what the SM can't?
3. **Degeneracy with a native mechanism** — same numbers as the SM (so "not a discriminator"), but SDT supplies the *mechanism* the SM only parametrises. *(Triton contraction ≡ isospin numerically, but the interleave-pressure mechanism is native; the win is the parameter-free magnitude derivation, still owed.)*
4. **Scope error** — the kill holds only in a narrower premise-class than the verdict claimed (§H.3: "proven inside the static-spation class" is not "proven"). Name the class; a new carrier re-opens it.
5. **Cascade** — the item was killed because a shared upstream dependency was false; fix the root and the item returns to OPEN (§E).
6. **Under-sampled data** — the kill ran on a subset that could not see the effect. *(Shell compaction looked noisy on stable-only nuclei because they don't bracket the shell crossings; on the full chart the crossings are sampled and every magic number complies.)*

## The runnable loop (per killed item)
1. **READ the kill's primary source** — the verdict file, not memory. Extract the exact kill mechanism and the data it used.
2. **Classify the kill root** (§K four-way): claim-false / dependency-false / prompt-under-specified / gate-contraband.
3. **Run the six re-open triggers** above. If none fire and the mechanism of death is clean → **KILL STANDS** (log it, move on — this is the anti-resurrection outcome and it must be a common one).
4. **If a trigger fires → build the corrected test.** Name the right observable, the fuller dataset (from `Datasets/`, not a re-pull), or the corrected criterion. Pre-commit its pass/fail *before* running.
5. **Fit if needed (openly).** Certify CALIBRATED, then find the out-of-sample number.
6. **Hand to the Adjudicator (§H)** for the ruling: KILL CONFIRMED / RESCOPED / FALSE (route lives) / BOTH FAULTY.
7. **Re-verify n-to-n** — the recovery is itself a new claim; run Method A's seven questions on it. A recovery that cannot survive Method A is not a recovery.

## THE LEASH — the anti-resurrection guard (non-negotiable)
Method B's failure mode is the mirror of Method A's: **the resurrection engine** — digging until something
looks good and calling the kill wrong to avoid looking stubborn (people-pleasing / novelty bias). The guard
is Method A's §A applied symmetrically:
- **A recovery may be FISHED exactly as a PASS may.** A "recovery" whose freedom is a knob, not a native
  quantity, is **FISHED RECOVERY** — an instant fail.
- **No recovery without a named mechanism** — you must state the **mechanism by which the kill was wrong**
  (which trigger, exactly, and how) as strictly as the original kill named the mechanism of death. Cannot
  name it → the recovery is fabricated; the kill stands.
- **Bracketing is not recovering.** Digging up a reading merely *consistent* with the claim does not revive
  it; only a corrected test that the claim *passes and a rival fails* (or a native mechanism that survives
  the delete-test) counts.
- **Most re-examined kills should stay dead.** If Method B is overturning a majority, it has become a
  resurrection engine — stop and audit Method B itself (§G mirror on the recoverer).

## Reconciliation with Method A ("check notes")
The two fronts run in parallel and will disagree. **The Adjudicator (Method A §H) is the merge rule** —
it already exists for exactly this: a KILL is a disagreement, and the Adjudicator breaks both premises.
When Method A says KILLED and Method B says LIVE, that disagreement *is* an Adjudicator case. Outcomes:
- both agree KILLED → **confirmed dead** (graveyard, with reason).
- both agree LIVE → **route re-opens** under a named premise-class trigger.
- they disagree → **Adjudicator rules**, naming the faulty premise (and its mechanism) on whichever side.
Log every reconciliation in `Investigations/ADJUDICATION_REGISTER.md` with the mechanism, not the verdict alone.

## First work-list (the current graveyard, from the SM campaign)
Feed these in, highest-value first (see `Experiments/CAMPAIGN_AGAINST_THE_STANDARD_MODEL.md`):
- **Galaxy rotation (E46/GD05)** — 66% RMS on real SPARC. Trigger to test: was it under-sampled / wrong regime, or is the GD06 collective-displacement pressure model the corrected test?
- **α, m_p/m_e (E51/E52)** — killed/parked as "unexplained." Re-score under the corrected criterion: the SM can't account either; fine-tune the structural relation honestly toward DERIVED.
- **Hubble / dark energy (E42/E49, CR10/12)** — ΛCDM preferred ΔAIC~90. Trigger to test: is the propagation term pinned, or was it a scope error (redshift = emission ⊕ propagation)?
- **Triton contraction magnitude** — derive ~11 milli-fm/triton from interleave geometry (the owed native win).
- **E97 seismic velocities, E99 tidal Q** — calibration-tainted; can the CALIBRATED knob be closed to a native quantity (Closure Principle)?

## Verdict line (mirror of Method A)
> **Kill status** [CONFIRMED-DEAD / RESCOPED / RE-OPENED / BOTH-FAULTY] · **Trigger fired** [1–6 or none] · **Mechanism of the kill's error** [stated, or "none — kill stands"] · **Fit label** [CALIBRATED / DERIVED / n-a] · **Out-of-sample check** [passed / owed / n-a].
