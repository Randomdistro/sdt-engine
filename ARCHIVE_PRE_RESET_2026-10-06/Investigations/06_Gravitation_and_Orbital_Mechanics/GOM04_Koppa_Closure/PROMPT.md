# GOM04: Koppa Closure — recovering c from orbital observables (a consistency inversion, named as one)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **first prompt for this folder,
> 2026-07-24** (the folder previously held only tools + an output file; the agent-era output was
> deleted 2026-07-24, git-recoverable). **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` ·
> `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G. **Execution: DIRECT ONLY — no agents.**
> Tools: `gom04_koppa_closure.cpp`, `Deriving_c_From_Mercurial_Precession.cpp`.

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Whether the koppa ledger CLOSES on c: from purely orbital
   observables — Mercury's measured precession (42.98″/cy, Le Verrier-class), measured orbital
   velocities scaled to surface values (v_orbiter·√(d/R)), and geometry — invert
   δφ = 6πR/(k²a(1−e²)) for k, then form c = k·v_surface. If the ledger is coherent, the output
   lands on 299,792,458 m/s. **What this is:** a CLOSURE/consistency test — three independent
   measurement channels forced through one identity. **What this is NOT:** a derivation of c
   from nothing (the precession formula's 1/r³ provenance is GOM08's open transplant question,
   inherited here; and the measured precession itself encodes the same physics the bridge maps).
   The honest question: does the loop close, and at what precision do the inputs allow it to?
2. **Why does it matter?** — A failed closure would be a real defect in the bridge (the
   k-hierarchy's central identity caught contradicting orbital data). A passed closure is a
   clean pedagogical demonstration that the ledger needs no c *input* on this loop — GOM02's
   reach thesis in executable form.
3. **How will we find out?** — P1 run both tools direct with the iterative-convergence
   demonstration (start k = 600, show closure failing, converge); P2 the precision budget
   (propagate input uncertainties → the allowed window on recovered c); P3 the provenance
   ledger (which steps are IDENTITY/bridge algebra, which are measured, what GOM08-P2 would
   change).
4. **What would prove us wrong?** — Recovered c outside the P2-budgeted window (bridge defect —
   escalate); the inversion found to consume c anywhere upstream (closure claim VOID — audit in
   P0).
5. **How will we know we're done?** — Dual verdict; the recovered c with its budgeted window;
   the provenance ledger printed.

## §0 Reader's contract
1. **Name the loop.** Every output carries `[CLOSURE — consistency inversion; 1/r³ provenance
   per GOM08]`. No "c derived from first principles" language.
2. **P0 source audit is a gate:** grep both tools for any c or GM upstream of the output line
   (the banner claims "c IS NOT AN INPUT" — verify it at code level; the killed GOM04 output
   file is not evidence).
3. No G, no M in-chain; 42.98″/cy and orbital elements are OBSERVED anchors.
4. Direct only; teed stdout; fresh dated verdict.

## §④ Phases
**P0** — audit both tools (c/GM sweep; what each actually computes). **P1** — run direct:
convergence demonstration + recovered c. Gate: within the P2 window of 299,792,458 (compute the
window FIRST from input precisions: δφ ±0.04″, v_surf from orbiter data ~0.1%-class, geometry
~1e-4 — expect a ~0.2%-class window; commit the number before comparing). **P2** — the precision
budget, printed as a table. **P3** — provenance ledger; cross-cite GOM08-P2 (a native 1/r³
derivation would upgrade this closure's class from IDENTITY-loop to CONVERGENCE-with-mechanism).

## §⑧ Falsifiers
F1: recovered c outside budgeted window → bridge defect, escalate root-2 then root-1.
F2: c found upstream in-code → closure VOID until patched.
F3: window computed after the comparison → run VOID (fishbowl).

## §⑤ Outputs
Fresh `RUN_LOG.md` · `gom04_rerun_<date>.txt` · `GOM04_VERDICT_DIRECT_<date>.md` (recovered c ±
window, provenance ledger, dual verdict).

## ⑩ Pre-Run Commitments (copy to RUN_LOG before code)
```markdown
- Target [A|B|C] · class ceiling: CLOSURE/IDENTITY-loop (upgradeable only via GOM08-P2)
- CALIBRATED budget: 0 · Gates: P0 audit clean · P2 window committed before P1 comparison
- Forbidden: "derives c" language; window-after-comparison; agents.
```

*GOM04 · first spec 2026-07-24 · the loop either closes or it doesn't — and closing is
consistency, not creation. Say which.*
