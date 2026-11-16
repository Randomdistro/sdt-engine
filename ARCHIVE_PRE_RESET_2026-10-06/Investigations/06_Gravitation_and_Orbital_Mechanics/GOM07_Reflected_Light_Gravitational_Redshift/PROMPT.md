# GOM07: Reflected-Light Redshift — re-earning the Lanza regression, and resolving the stamp-vs-observer tension the file itself names

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **first standalone prompt 2026-07-24.**
> The Harvey-authored `INVESTIGATION.md` (predictions corrected 2026-06-20) REMAINS as the
> spec-source; its verdict-layer (agent-era GOM07_VERDICT + RUN_LOG) deleted 2026-07-24 —
> the Lanza-regression numbers are re-earned here. **Campaign context is controlling:**
> **E107 is DEAD on the strict front** (any SDT-vs-GR *shared-redshift* fork is degenerate,
> ϟ≡GM/c² — firing log 2026-07-23), and this folder holds docket-question D06:
> *can ϟ_J be derived ≠ GM_J/c²?* **Inherits:** template + protocol + HUNTER §0/§G.
> **Execution: DIRECT ONLY.** Tools: `gom07_reflection_redshift.py`, `gom07_partB_lanza2016.py`,
> `gom07_sun_well.py`.

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Three things, in rising order of importance:
   (a) whether the Part-B regression on the Lanza et al. 2016 common-scale dataset re-earns
   direct: prior record slope **−1.11 ± 1.28** (0.9σ from SDT-flat, 1.6σ from GR-naive-climb,
   floor-limited ~1.5 m/s) — consistent-with-flat, not decisive, and only ever a kill of the
   NAIVE one-way-climb picture (rigorous cancellation-GR also predicts flat — the file's own
   honest caveat);
   (b) whether the within-Jupiter Galilean gradient (Io−Callisto 0.78 m/s under naive-climb)
   is worth an ESPRESSO-class follow-up given (a)'s scope — i.e. what exactly dies if it lands
   flat at ±0.2 m/s (answer: only naive-climb pedagogy; GR proper survives — state this cost-
   benefit honestly before recommending telescope time);
   (c) **the internal tension — the real work:** the engine's own `depth_closure::z_spectral =
   z_emit − z_obs` carries an OBSERVER term; the pure emission-stamp reading ("set at emission,
   stable, no re-fighting") has none. These are different theories: at Parker Solar Probe depths
   (0.046 AU) they differ by tens of m/s, and the observer-term form is EXACTLY GR's — which is
   why E102's near-Sun leg was ruled degenerate. **SDT must pick one reading and pay its price:**
   observer-term → degenerate with GR everywhere a shared redshift is measured (E107's death
   generalises, honestly); pure-stamp → divergent at Parker BUT then the engine's z_spectral
   and the Depth-Closure paper's 0.03% solar validation need re-derivation under the stamp
   reading. This is a canon-level fork and the deliverable is the decision matrix, not a verdict.
2. **Why does it matter?** — (c) decides whether ANY shared-redshift observable can ever be a
   fork for SDT — it is the generalisation of the E107 lesson to the whole depth sector, and it
   feeds docket D06 directly.
3. **How will we find out?** — P1 re-run predictions + Part-B regression direct (labels per
   contract); P2 the Galilean cost-benefit note; P3 the tension memo: both readings formalised,
   each one's consequences computed at three benchmarks (solar 633.35 baseline · Parker 0.046 AU
   · Jupiter H₃⁺ emission), each one's conflicts listed (engine lines, Depth-Closure paper,
   E102 spec) — ending in a decision matrix for Harvey, NOT a unilateral canon choice.
4. **What would prove us wrong?** — P1 slope re-earning outside ±0.2 of the recorded value
   (data-handling defect); P3 finding both readings force the same numbers everywhere
   (the tension is illusory — document why and close D06 as DEGENERATE-permanently).
5. **Done =** dual verdict + the decision matrix filed for Harvey's ruling.

## §0 Reader's contract
1. **E107's death is controlling.** No shared-redshift fork may be proposed; the only
   permissible fork-hunting ground is the observer-position dependence (P3), and only IF the
   stamp reading survives Harvey's ruling.
2. **The Lanza result's honest scope** (from the file itself): it adjudicates naive-climb, not
   GR proper. Every P1 output line says so.
3. No G/M in-chain (the file's provenance note stands: v_surf = √(g·R) from tracking; GM never
   written). Lanza data = OBSERVED (published table).
4. **P3 is propose-only at canon level:** the memo may not edit `laws.hpp` or the Depth-Closure
   paper; it names the lines that would change under each reading (CANON_FLAGS style).
5. Direct only; teed stdout; fresh dated files.

## §④ Phases
**P0** — tool audit (three scripts: what each consumes/produces; the Lanza table's provenance
printed). **P1** — re-earn: the §3 prediction table (SDT-flat 633.35 vs naive-climb column,
labeled) and the Part-B regression. Gates: slope within ±0.2 of −1.11; σ within ±0.1 of ±1.28;
scope label on every line. **P2** — Galilean follow-up cost-benefit (one page in the verdict:
what ±0.2 m/s buys — the naive-climb kill only — and what it cannot buy). **P3** — the tension
memo `GOM07_STAMP_VS_OBSERVER_<date>.md`: formalise both readings; compute the three benchmarks
under each; list every repo line that takes a side (engine z_spectral, Depth-Closure C1, E102
spec, this file's §0); decision matrix with each option's costs. **Files to D06.**

## §⑧ Falsifiers
F1 P1 re-earn misses → data handling defect, fix before anything. F2 P3 readings converge
everywhere → tension illusory; D06 closed DEGENERATE (that IS an answer — record it).
F3 canon edited → run VOID (propose-only).

## §⑤ Outputs
Fresh `RUN_LOG.md` · `gom07_rerun_<date>.txt` · `GOM07_STAMP_VS_OBSERVER_<date>.md` ·
`GOM07_VERDICT_DIRECT_<date>.md` (dual verdict + the matrix; D06 cross-reference).

## ⑩ Pre-Run Commitments
```markdown
- Target [A|B|C] · P1 ceiling: consistent-with-flat, naive-climb-scope only
- CALIBRATED budget: 0 · Gates: P1 ±0.2/±0.1 re-earn · P3 three benchmarks × two readings, all
  conflicts listed, matrix filed
- Forbidden: shared-redshift fork proposals; canon edits; unilateral reading choice; agents.
```

*GOM07 · first spec 2026-07-24 · the reflection question is settled to its honest scope; the
live question is which redshift theory SDT actually is — and that ruling is Harvey's.*
