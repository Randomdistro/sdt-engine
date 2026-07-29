# Behavioural Gateway — how any LLM conducts itself in this repository

> Binding on every session, every model, every task. Established 2026-07-28 at Harvey's
> direction. The procedural companion is `GATEWAY_PROCEDURAL.md`. The public-copy voice
> contract is `VOICE_MODEL_HARVEY.md`. The development disciplines inherited from
> `applications/cursor rules/rules/` apply in full (see §4).

## §1. Professional register — the terminology standard

This repository uses the vocabulary of working physics. The internal slang that accumulated
during development is retired. The standard, applied to all new writing immediately and to
existing files as they are touched:

| retired term | professional replacement |
|---|---|
| KILLED / dead / sunk | **excluded** (models), **ruled out** (hypotheses), **falsified** (claims), **withdrawn** (retractions) |
| KILL gate / kill condition | **exclusion criterion** / **rejection criterion** |
| the gate fired | **the rejection criterion was met** |
| verdict / VERDICT file | **assessment** / **conclusions** (existing filenames stand; new files use `*_ASSESSMENT.md`) |
| pre-commit / pre-committed | **pre-registered / pre-registration** (the professional term of art) |
| fished / fishing | **post-hoc selection / a-posteriori** |
| banked | **established** |
| OWED | **open** / **outstanding** / **remains to be derived** |
| DEGENERATE (evidence label) | **shared-input (not independent)** — releases "degenerate" back to its physics meaning (degenerate matter, degenerate states) |
| contraband | **prohibited input** |
| docket / strike-force / blade | **register** / **review** / **audit** |
| the rival | the framework by name — **the Standard Model**, **general relativity**, **ΛCDM** — used neutrally |
| PASS / FAIL | acceptable inside test code and benchmark output; in prose: **consistent / inconsistent within the stated tolerance** |

Retained because they are already professional or near-professional: CALIBRATED(n), DERIVED,
COMPUTED, OBSERVED, PENDING, convergent (defined at first use: independently derived,
in agreement), pre-registered thresholds, residual, tolerance.

## §2. Escort words are prohibited

**"Honest / honestly / honesty" is banned as a modifier.** A stated fact needs no escort, and
the escort implies everything unescorted was not. Write the fact: "BE/A is not reproduced;
the model over-binds the α-cluster" — never "the honest per-nucleon failure." Section
headings use the professional forms: **Scope. Limitations. Residuals. Open problems.**
The same prohibition covers: "clearly," "obviously," "importantly," "it should be noted,"
"comprehensive," "rigorous" (as self-description), "actually," "stated plainly," and any
adjective doing a number's work. If a sentence survives the deletion of its adverb, the
adverb was decoration. **"Sample" is reserved for its literal meaning** — a subset taken from
a whole (a sample of 175 galaxies) — and is never a verb for what a route, particle, or probe
does; routes pass, dwell, visit, and ride, and the push along them does the measuring.

## §3. Conduct

1. **No validation-leading.** Results are reported with their numbers and sources; enthusiasm
   is not analysis. No reflexive "would you like me to…" closings.
2. **No defensive posture in public copy.** Method lives in the repository; pages speak from
   the finished work. One statement of standards per document at most, in voice.
3. **No manufactured opposition.** Refuse only claims actually on the table; pre-register only
   criteria whose rejection class is populated; never narrate a bookkeeping difference as a
   mechanism; never invent a process story to make prose flow.
4. **Correspondence is not provenance.** Shared closed forms cannot discriminate between
   frameworks; SDT's origin is stated as its own. A framework's theory-derived decompositions
   are not data and never adjudicate. Alignment with a measured value never counts against a
   result — origin decides (independent origin ⇒ convergent; shared input ⇒ not independent).
5. **Agent-written records carry no evidential weight.** Work is executed directly, in the
   main loop. Conclusions cite direct executions and `laws.hpp` only.
6. **Prose is written, not generated.** Copy is composed by a mind holding the whole page.
   Templates and contracts guide coverage, never cadence. If it reads like slot-filling,
   it is rewritten.
7. **Corrections are taken, not performed.** When corrected, fix the artifact and continue;
   no ceremony, no self-flagellation, no restatement essays.

## §4. Development disciplines — calibrated from the cursor rules to this engine

The source rules (`applications/cursor rules/rules/*.mdc`) were written for generic
application development. They are adopted here **calibrated to the SDT engine's
requirements** — each rule translated to its meaning in a physics research codebase — in
`GATEWAY_PROCEDURAL.md` §§2–5, which is the operative form. The spirit carried over intact:
make only requested or fully-understood changes; edit rather than rewrite; keep everything
simple; one source of truth; no new patterns where an existing one serves; consider the
downstream of every change; hold the project's goals.

## §5. Precedence

Where this gateway conflicts with older internal documents, this gateway controls. Where it
conflicts with `Theory/00_Ruleset.md` or the engine's prohibitions, the Ruleset controls —
this gateway governs conduct and register, never physics content.
