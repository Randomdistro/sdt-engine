# NP10 — The alpha's mass defect and its cooperative lock (specification rewritten 2026-10-10)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction (2026-10-10): dependencies first, prompts carry new data, and the packing sequencer is understood before grammar work. The 2026-06-27 specification is kept unchanged below the line and is superseded.

## 1. Question (as it now stands)
⁴He binds **B(α; {4p, 2e}) = 26.731023 MeV** on its native list (AME2020; NP17 reset T1). It binds 28.296 MeV on {2p, 2n}, but that list carries the owed neutron term twice. What cooperative mechanism makes the α's binding per contact several times the deuteron's? What arrangement does the construction actually use?

## 2. What is established (with source)

| # | Fact | Source |
|---|---|---|
| E1 | Binding is mass defect. Energy is movement. The bond-sum route below the line ("4E_pn + E_nn + E_pp − E_Coulomb") is withdrawn bookkeeping. | Harvey 2026-10-07 |
| E2 | Native lists: d 1.442246, ³H 6.917143, ³He 6.935735, ⁴He 26.731023 MeV on {A p, N e}. | NP17 reset (AME2020) |
| E3 | Per-electron seat ledgers are **excluded for A ≥ 3**. ⁴He exceeds even the most generous ceiling (all electrons on all boundaries) by 3.90×. | NP17 reset T1 |
| E4 | A shared-resource angular lock (H-W) is **excluded**: binding per contact rises 1.16–3.18× the deuteron's with coordination, under every admissible graph. The lock is **cooperative**. | NP10 reset 2026-10-09 |
| E5 | The W+1 channel set cannot face a regular tetrahedron's three neighbours at once (it misses by 35.26°, outside the 30° cone). The **square ring** and the triangle engage fully. | NP10 reset (instance) |
| E6 | The live sequencer (NSEQ18-WEB-1) builds the α as a **4-ring** (4 "alpha" contacts, cycle rank 1), not a tetrahedron. This is independent of, and agrees with, E5. Every A ≥ 4 nucleus is that ring plus a tree of dock and internal contacts, with E = A. | engine run 2026-10-10 |
| E7 | 2R_p_lock = 1.68247 fm against R_He 1.67550 fm (+0.42%), G4 and not discriminating. | NP10 reset R3 |
| E8 | NP33 rule in canon: missing lock contacts cost one engaged-resistance unit, and completing the graph saves one (`laws.hpp:2132–2150`). | canon |

## 3. Errors already made, and what each teaches

| # | Error | Lesson |
|---|---|---|
| X1 | The electrostatic α (old NP17) gave 4.45 MeV, and the "lock remainder 23.842 MeV" was defined against {p, n} with a withdrawn pair ledger. | The remainder must be restated on the native list against a native contact ledger. It is not a residual of a withdrawn sum. |
| X2 | The far-field occlusion bond (NP09 route) is about 30× short. | The scale is the seat movement αħc/R_p = m_e v(R_p)² (1.711391 MeV), not occlusion. |
| X3 | The live engine's zero-fit ledger gives ⁴He 11.69 MeV against 28.30 ({p, n}). It also gives **μ(⁴He) = 1.65 μN against a measured 0**. | The sequencer's 4-ring as built does not cancel its moments. Either the ring's phase assignment or the moment ledger is wrong, and this is a construction defect to report to the sequencer. A native α must give μ = 0 by its arrangement. |
| X4 | The tetrahedron was taken as a premise (old Step 1). | Let the construction and the angle budget pick. Both now pick the ring (E5, E6). |

## 4. Dependency
**Required supplier: NP17 round 2 (O1 contact-mesh cooperative ledger).** O1 must state natively, before any value is loaded:
- what one open mesh contact frees;
- what closing a loop frees (the cooperative term; NP33 gives the counting form "completing the graph saves one unit", but its energy unit is not yet derived).

**Blindness limit.** d, t, h and α are already seen. The α is therefore a **consistency check**. The blind test is O1 applied, with no new parameter, to A ≥ 6 nuclei on the sequencer's graphs (one ring plus tree), registered in NP17 round 2.

**Status:** DEFERRED until O1 exists. Run now, independently:
- C3 (μ_α from the sequencer), a construction check;
- C4 (R_He), already G4.

## 5. Pre-registered checks
- **C1 (when O1 exists).** O1 on the 4-ring against 26.731023 MeV, ±5%. Post-seen, so G3 at most.
- **C2 (when O1 exists).** The same rule on the open chains (E = 2) for ³H and ³He; equal to each other within 2%. Structural; the values are seen.
- **C3 (now; construction).** The magnetic moment of the sequencer's α. Measured 0 (spin-zero anchor). **Not met** as built (1.65 μN). Recorded as a sequencer defect, propose-only (Release is not edited).
- **C4.** R_He = 2R_p_lock: carried, G4.

## 6. Prohibitions
- No pair potentials.
- No neutron as an independent particle without the owed term.
- No tetrahedron or ring imposed by hand: the construction and the angle budget decide.
- No census or post-hoc coefficient.
- No QM narration.
- The word "charge" is not used.
- No edits to Engine, Laws or Release.

---

## Superseded specification (2026-06-27, kept as written)

# NP10: Alpha Binding from Tetrahedral Occlusion — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP10] NP10: Alpha Binding from Tetrahedral Occlusion — Investigation Prompt: **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** Can the total occlusion energy of the tetrahedral geometry of 2 protons and 2 neutrons (6 bonds) reproduce the He-4 binding energy 28.296 MeV, and what sets the lock remainder (23.842 MeV) beyond the shared-electron electrostatics?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

---

## 1. The Question

He-4 (the alpha particle) has binding energy 28.296 MeV — anomalously large compared to its neighbours. SDT describes it as a tetrahedral arrangement of 2 protons + 2 neutrons, forming 6 occlusion bonds (every nucleon bonded to every other). Can the total occlusion energy of this tetrahedral geometry reproduce 28.296 MeV?

## 2. Methodology

> **FARMER correction (2026-07-03, J.C.Harvey directive):** the transcription below carried only the
> FAR-FIELD occlusion route (the NP09 scalar bond, since failed −97.3%) and dropped the branch's
> founding mechanism — **occlusion SATURATION at contact**. The occlusion principle of the CMB
> throughput: every location receives the full convergent influx of the boundary sphere (growing
> 2 ly/yr in diameter) *unless blocked — and blocking is the work*. At nucleon contact (d ≈ 2R_p)
> each nucleon shadows ~half its partner's sky: this is the SATURATED regime (two-regime law,
> g → 2 near contact), where the bond energy is the full unoccluded-hemisphere pressure asymmetry,
> not the 1/r² far-field residual. Saturation is natively **coordination-dependent** — three
> contacts occlude more solid angle of a nucleon's sky than one — which is precisely the lock
> scaling measured by the 2026-07-03 run (×1.01 deuteron → ×1.98 triton → ×6.35 alpha, flat
> per-bond factors falsified). **The next run must test the saturated-occlusion solid-angle ledger
> as the lock term.**
>
> **Refinement (Harvey, same day):** the ledger is likely NOT a broad solid-angle area — the
> limited rim distance of the poloidal flow means contact area is very small and **contact ANGLE
> is the premium resource**. Treat the lock as an *angular-window allocation* problem: engagement
> in narrow rim-windows (FLM07 glancing-transfer locus), where simultaneous alignment for many
> partners is geometrically scarce — a native route to nonlinear coordination-dependence. The
> tetrahedral placement itself is a rendering, not settled structure — do not hard-code it as a
> premise; let the angle budget pick the arrangement.

### Step 1: Tetrahedral geometry

Place 4 nucleons at the vertices of a regular tetrahedron. The edge length d is determined by equilibrium between:
- Attractive occlusion — **saturated-regime solid-angle shadowing at contact (primary, per the correction above)**; far-field ℓ≥3 only beyond contact
- Repulsive centrifugal pressure from circulation (outward)
- For the two protons: repulsive ℓ=1 Coulomb

The measured He-4 boundary radius (1.6755 fm; lit. "charge radius") constrains d:
- R_boundary = d × √(3/8) → d ≈ 2.73 fm for the tetrahedron edge
- OR: R_boundary = 2R_p → d is the proton-proton distance ≈ 2R_p × √(8/3)

### Step 2: Count bonds and compute total energy

6 bonds in a tetrahedron:
- 4 × p-n bonds (each at distance d)
- 1 × p-p bond (distance d, with Coulomb repulsion reducing the net)
- 1 × n-n bond (distance d, pure occlusion)

Total binding = 4×E_pn + 1×(E_pp − E_Coulomb) + 1×E_nn

Where:
- E_pn = occlusion bond energy from NP09
  — NOTE (2026-07-03): NP09's scalar-occlusion route FAILED (−97.3%) and FLM12-D1 ruled the linear volume-price out at 34×; revise the premise before execution.
- E_pp = same occlusion, minus Coulomb repulsion
- E_nn = occlusion between two neutrons (no Coulomb)
- E_Coulomb = k_e e²/d = 1.44 MeV·fm / d

### Step 3: Consistency checks

1. Does 4×E_pn + E_nn + (E_pp − E_C) = 28.296 MeV?
2. Is B_alpha / 6 ≈ 4.72 MeV per bond reasonable compared to B_d = 2.224 MeV per bond? (Yes if closer packing → stronger occlusion)
3. Does the predicted R_He = 2R_p (1.683 fm) match measured 1.6755 fm? (0.43% — already in laws.hpp)
4. Does the tetrahedral symmetry explain μ_alpha = 0 (all magnetic moments cancel)?

### Step 4: Hierarchy test

Compute from the same geometry:
- B(He-3) = 3 p-n bonds + 0 p-p + ... (only 3 nucleons — triangle)
- B(H-3) = 3 p-n bonds (triangle geometry)
- Compare predicted ratio B_alpha / B_triton to measured 28.296 / 8.482 = 3.34

## 3. Success Criteria

- [ ] Total binding energy predicted within 20% of 28.296 MeV
- [ ] R_He predicted within 1% of measured
- [ ] μ_alpha = 0 explained by tetrahedral symmetry
- [ ] B_alpha / B_triton ratio reproduced
- [ ] Bond energy per edge is self-consistent with NP09 deuteron result
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP10
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 0.43%, 20%, 1%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| A rival lands on the same number | adjudicate by **origin** (gateway procedural §3.8): SDT-origin route ⇒ **CONVERGENCE**; a *named* contaminating input ⇒ **SHARED-INPUT**; state discrimination separately | — | downgrade a convergent result because a rival formula agrees; claim discrimination the numbers do not show *(row corrected 2026-10-03 — the stamped alignment row was excluded 2026-07-26)* |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP10 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The question is unfilled by the bulk template, the total-binding gate is "within 20% of 28.296 MeV", and the committed electrostatic model under-binds the alpha by 6.35× (−84.3%).

**Correction:** State the gap (the origin of the 23.842 MeV lock remainder) and gate the lock remainder directly.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
