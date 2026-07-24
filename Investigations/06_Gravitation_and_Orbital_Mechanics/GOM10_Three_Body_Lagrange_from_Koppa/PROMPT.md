# GOM10: Lagrange Points from Koppa — the identity run, the shadow-cone divergence hunt, and the tractability claim on trial

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). **Register/stack status:** PARTIAL on input precision (Kepler 0.351%, μ_ϟ −0.122%
> — "near-certain to clear with ephemeris-grade inputs"); this run must clear it or find out why
> not. **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER
> §0/§G. **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> Prior agent-era VERDICT/RUN_LOG/results deleted 2026-07-24 (git-recoverable).
> Companion spec `PROMPT_nbody_equilibria.md` remains as the extended n-body appendix.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Three cleanly separated things:
   (a) *the identity leg:* nothing — μ_ϟ = ϟ₂/(ϟ₁+ϟ₂) equals the mass ratio **algebraically**
   through the bridge, so L1–L5 landing on the classical positions is IDENTITY-class and its
   only open item is clearing the input-precision PARTIAL with ephemeris-grade v, R;
   (b) *the divergence leg (the actual question):* Newton's field is a POINT-DEFICIT with no
   internal geometry; SDT's is a **shadow cone with finite width and saturation behaviour**
   (two-regime: g → 2× near contact). L2 sits INSIDE Earth's umbra along the Sun line — does
   cone geometry (finite angular width, saturation onset, penumbra profile) shift L2 relative
   to the point-field prediction by ANY computable amount? That is a place the rival predicts
   exactly zero (the firing-log targeting rule's shape);
   (c) *the tractability claim on trial:* the old §2.3 asserted three-body chaos is "resolution
   limit, not fundamental" because smooth fields superpose smoothly. As stated this is
   UNSUPPORTED — Newtonian fields are equally smooth away from their sources, and chaos is a
   property of the dynamics, not of field singularities. The claim is demoted to a hypothesis
   with a falsifier or it is struck.
2. **Why does it matter?** — The identity leg guards the bridge at 5+ digits with ephemeris
   inputs (feeds GOM02's invariance case). The shadow-cone leg is one of the few candidate
   zero-vs-nonzero forks in weak-field orbital mechanics — and spacecraft (SOHO, JWST) sit AT
   the exact point in question with cm-class tracking. The tractability claim, if kept
   unearned, is exactly the over-claim class HUNTER exists to purge.
3. **How will we find out?** — §④: P1 identity leg with ephemeris-grade inputs (clears the
   PARTIAL); P2 the shadow-cone L2 computation (the divergence hunt, with a pre-committed
   magnitude-vs-tracking-precision decision rule); P3 the tractability trial (state the
   mechanism-level claim precisely, derive one falsifiable consequence, or strike);
   P4 Sun–Earth–Moon superposition map (bookkeeping, labeled).
4. **What would prove us wrong?** — §⑧: identity leg missing at ephemeris precision (bridge
   error — serious); P2 predicting a measurable L2 shift already excluded by JWST/SOHO
   station-keeping (that cone-geometry variant KILLED — with the bound recorded); P3 producing
   no falsifiable consequence (claim struck as prose).
5. **How will we know we're done?** — Dual verdict; the three legs reported under their own
   labels (IDENTITY / DIVERGENCE-HUNT / TRIAL), never blended.

## §0 Reader's contract

1. **The identity rule.** μ_ϟ ≡ μ and Φ_eff(koppa) ≡ Φ_eff(Newton) under the bridge. Every P1
   output line carries `[IDENTITY — bridge algebra]`. The honest content of P1 is precision
   (does the kinematic route reproduce ephemeris L-points at their known precision), not truth.
2. **The mechanism story (transit-time equalisation / phase-delay interference) is a READING
   until it computes something the point-field does not.** P2 is where it gets its chance. A
   reading that only re-derives the classical equilibria stays LINGUISTIC.
3. **Saturation input:** the two-regime saturation function G(x) = 2(1−√(1−x)) is the
   pre-registered E105 form (campaign-locked); if P2 uses it, cite it — do not refit it.
4. **No G, no M in-chain**; ephemeris L-point positions and station-keeping envelopes are
   OBSERVED anchors (rival-fit; comparison only).
5. **Direct only; teed stdout; fresh dated verdict.**

## §1 Definitions and anchors

| Quantity | Value | Label |
|---|---|---|
| ϟ_Sun · ϟ_Earth · ϟ_Moon | 1477 m · 4.434 mm · 0.0546 mm | COMPUTED (kinematics; ephemeris-grade v, R this run) |
| μ_ϟ (Sun–Earth) | ϟ_E/(ϟ_S+ϟ_E) ≈ 3.00×10⁻⁶ | IDENTITY with mass ratio |
| L1/L2 (Sun–Earth) | ≈ 1.50×10⁶ km from Earth (Hill: a(μ/3)^{1/3}) | OBSERVED-anchor |
| L4/L5 | 60° (geometric) · stability μ < 0.0385 | OBSERVED-anchor / classical |
| Earth umbra length | ~1.4×10⁶ km (R_E·D/(R_☉−R_E)) | geometry — NOTE: comparable to the L2 distance; this coincidence is why P2 exists |
| JWST/SOHO station-keeping envelopes | ~10³–10⁴ km halo, tracking to ~km | OBSERVED-anchor (the P2 decision scale) |

## §④ Phases

**P0 — Sanity + input upgrade.** Ephemeris-grade v_orb and R per body (DE-class values, cited);
recompute all ϟ; z·k² = 1 printed [IDENTITY].

**P1 — The identity leg at full precision (clears the register PARTIAL).** Solve ∇Φ_eff = 0 in
the rotating frame with Φ_eff = −c²ϟ_S/r_S − c²ϟ_E/r_E − ½Ω²r² for Sun–Earth and Earth–Moon.
Gates: L1/L2 within 0.1% of classical (was 1% — tightened because the PARTIAL was
input-precision-limited); L4/L5 at 60.000°; stability threshold 0.0385 reproduced; μ_ϟ = μ to
<0.01% (was 0.1%). Labels per contract §1. Failing at ephemeris precision = bridge defect —
escalate immediately (this cannot honestly fail).

**P2 — The shadow-cone divergence hunt (the native question).** The point-field treats Earth's
occlusion as a 1/r² deficit from a point. The SDT picture is a CONE: angular radius R_E/d,
penumbra structure, and saturation (G(x), x = occlusion fraction) as the line Sun–Earth–L2 is
approached. Compute, with the cone geometry and the E105 saturation form, the effective axial
force at the L2 region vs the point-field value, and locate the equilibrium shift Δr_L2.
Pre-committed decision rule (write in RUN_LOG before the number):
- |Δr_L2| ≥ 10³ km (inside halo scales): almost certainly already excluded — check against
  JWST/SOHO orbit determination; if excluded, THIS CONE VARIANT IS KILLED, bound recorded;
- 1 km ≤ |Δr_L2| < 10³ km: potentially testable — escalate to campaign as a candidate fork
  with the number (rare, valuable);
- |Δr_L2| < 1 km: unmeasurable — parked with the number; the mechanism reading stays
  LINGUISTIC but now with a computed magnitude attached.
Also compute the same for L1 (SOHO side — outside the umbra: the cone asymmetry between L1
and L2 is itself a signature Newton lacks; report the L1/L2 shift asymmetry).

**P3 — The tractability claim on trial.** Restate §2.3's old claim as a mechanism: "phase-delay
interference gives closed contours where point-gravity gives chaos." Derive ONE concrete,
checkable consequence (e.g. a bound on Lyapunov time in the Sun–Earth–Moon restricted problem
differing from the Newtonian value; or a stability-island boundary at a computable μ beyond
0.0385). If no such consequence can be derived in this run: **the claim is STRUCK from the
spec's assertions and recorded as prose-only** — the verdict says so in one line. No third
option (keeping it as unearned assertion is the forbidden state).

**P4 — Superposition map (bookkeeping).** The Sun–Earth–Moon g(x,y) field from summed koppa
terms; equilibrium points located; compared to classical. Labeled CONVERGENCE (linear
superposition is shared with Newton at this order; GR's nonlinearity is below relevance here —
note it, magnitude included, as part of GOM01-P3's residue ledger).

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | P1 misses at ephemeris precision | bridge defect — STOP, escalate (root-2 first: inputs) |
| F2 | P2 shift ≥ 10³ km | cone variant EXCLUDED by existing tracking — killed with bound |
| F3 | P2 machinery cannot close (saturation form inapplicable at 10⁻⁶ occlusion fractions) | say so — the hunt returns "no computable divergence"; mechanism stays LINGUISTIC |
| F4 | P3 yields no falsifiable consequence | tractability claim STRUCK |
| F5 | any per-system refit | identity leg VOID (nothing may be fit — it is algebra) |

## §⑨.E Four-root sort
root-1 (cone geometry genuinely adds nothing measurable — respectable negative) · root-2
(ephemeris inputs; E105 G(x) dependency) · root-3 (spec: penumbra profile under-specified —
state the assumption, compute both bracketing cases) · root-4 (gate contraband — none expected).

## §⑤ Outputs
Fresh `RUN_LOG.md` · re-audited `gom10_lagrange.cpp` (+ P2 extension) · `gom10_rerun_<date>.txt`
· `GOM10_VERDICT_DIRECT_<date>.md` (three legs, three labels, the P2 number and its decision).

## §6 Dependencies
Upstream: bridge · E105 pre-registration (the saturation form — cite, never refit) ·
two-regime/occlusion-saturation thread. Anchors: DE ephemerides, JWST/SOHO orbit determination
(rival-fit, comparison only). Downstream: GOM02 (precision case), GOM01-P3 (residue ledger),
campaign (if P2's middle band ever fires).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM10 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Legs and labels: P1 IDENTITY (precision only) · P2 DIVERGENCE-HUNT (decision rule below) ·
  P3 TRIAL (derive-or-strike) · P4 CONVERGENCE bookkeeping
- CALIBRATED budget: 0 (saturation form cited from E105, not fit)
- Gates: P1 0.1%/60.000°/0.0385/0.01% · P2 decision bands 1e3 km / 1 km pre-committed ·
  P3 one consequence or STRUCK
- Forbidden: blending legs; refitting G(x); keeping §2.3 as assertion if P3 fails; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 0.1% miss | upgrade inputs to DE-grade, re-run | F1 escalation | loosening to 1% |
| P2 penumbra ambiguity | compute umbra-only and full-penumbra brackets | report the bracket | picking one silently |
| P3 derivation stalls | narrow to the restricted 3-body Lyapunov bound only | STRUCK | asserting anyway |

---

*GOM10 · upgraded 2026-07-24 · the equilibria are free through the bridge; the cone is not the
point — and L2 lives in the shadow. Compute the difference or admit there is none.*
