# CH05 — Reaction Energetics & Activation from Wake Reconfiguration

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether reaction enthalpy ΔH can be derived as the difference in total wake-cost between reactant and product electropause configurations, and the activation barrier Eₐ as the highest wake-cost point (a wake *saddle*) along the reconfiguration path, with catalysis simply a lower-wake route — NO transition-state wavefunctions, NO orbital correlation diagrams.
2. **Why does it matter?** — The transition state becomes a geometric saddle of the wake field, not a quantum resonance. It consumes CH01 bond well-depths and CH04 geometries, feeds the downstream chemical-kinetics investigations, and ties to TD05 free-energy accounting. If it holds, reaction barriers stop being quantum resonances and become locatable points in a classical wake field.
3. **How will we find out?** — Gated phases in §④: ΔH bond-energy bookkeeping, then Eₐ as a 1-D wake-cost saddle, then catalysis as improved cancellation along the path, then a novel Eₐ/BEP-slope call — the native mechanism is built before any orbital correlation diagram or `atomic::`/rival is invoked.
4. **What would prove us wrong?** — §⑧ numeric triggers: ΔH signs or magnitudes wrong across the reaction set, or barriers that cannot be located without an orbital correlation diagram (a quantum TS).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

ΔH bookkeeping from summed CH01 well-depths is a near-IDENTITY — it IS the standard bond-energy
sum re-narrated as electropause-merge accounting. So **ΔH alone earns at most CONVERGENCE.** The
LOAD-BEARING, gradeable content is (a) locating Eₐ as a genuine wake *saddle* that emerges from the
path geometry — not read off a measured Eₐ — and (b) the catalysis "same ΔH, lower Eₐ" signature
falling out natively.

> **Reproducing ΔH by summing tabulated bond energies is the textbook identity — it does not by
> itself earn NATIVE; the barrier-as-saddle and catalysis predictions are where the model is
> tested. Reading the barrier height off the measured Eₐ caps the grade at C.**

One wake-cost scale may be **CALIBRATED(1)** — declare it explicitly. The Eₐ ORDERING / BEP slope
must be **predicted**, not fit per reaction.

## Question

A chemical reaction breaks some shared electropauses and forms others, rerouting the wake field
along the way. **Can reaction enthalpy ΔH be derived as the difference in total wake-cost between
reactant and product electropause configurations, and the activation barrier Eₐ as the highest
wake-cost point along the reconfiguration path (a wake *saddle*), with catalysis being simply a
lower-wake route — no transition-state wavefunctions, no orbital correlation diagrams?** The
transition state is the geometric saddle of the wake field, not a quantum resonance.

## SDT mechanism & hypotheses

Each shared electropause (CH01) carries a well depth (bond energy) and each active wake carries a
cost. A reaction is a continuous deformation from the reactant wake configuration to the product
one. ΔH is the net change in summed well depths (the familiar "bonds broken − bonds formed"), now
read as electropause-merge bookkeeping. Along the deformation path the wakes must transiently
*overlap and mis-cancel* before re-pairing; the peak of that mis-cancellation cost is the barrier,
and its location is the transition state. A catalyst supplies an alternative electropause partner
that keeps wakes better cancelled throughout, lowering the saddle.

- **H1 (ΔH = Σ well-depth change):** ΔH = (Σ reactant electropause depths) − (Σ product depths);
  recover signs and magnitudes for a set of gas-phase reactions from CH01 bond energies.
- **H2 (Eₐ = wake saddle):** the barrier height tracks the maximum transient un-cancelled wake
  along the minimum-cost path; predicts Eₐ ordering across a homologous series.
- **H3 (catalysis = lower-wake path):** an added partner that keeps wakes cancelled lowers the
  saddle without changing ΔH; reproduces the catalyst's "same ΔH, lower Eₐ" signature.

## Strategy

**Phase 1 — ΔH bookkeeping.** *Goal:* enthalpies from bond-energy sums. *Method:* CH01 well depths
in/out. *Success:* ΔH sign correct for ≥12 reactions, magnitude within ~15% (combustion,
hydrogenation, HX formation).

**Phase 2 — Barrier as saddle.** *Goal:* Eₐ trend. *Method:* 1-D wake-cost profile along a bond
coordinate; locate the maximum. *Success:* correct Eₐ ordering across a homologous series; a
Hammond-postulate-style late/early TS correlation emerges natively.

**Phase 3 — Catalysis.** *Goal:* lower barrier, same ΔH. *Method:* add a partner wake that
improves cancellation along the path. *Success:* Eₐ drops, ΔH unchanged, for one model reaction.

**Phase 4 — Falsifier.** *Goal:* a novel call. *Method:* predict an un-fit Eₐ or a BEP-line slope
(ΔEₐ vs ΔH) and check against measured kinetics.

## Success criteria

- **PASS (A):** ΔH set + Eₐ ordering + catalysis signature + a correct novel Eₐ/BEP slope, no
  TS wavefunction.
- **QUALIFIED (C):** ΔH from bond sums + qualitative barrier-as-saddle; one wake-cost scale
  CALIBRATED(1). *(Expected landing.)*
- **PENDING (D):** ΔH bookkeeping works; barrier only schematic.
- **FAIL (F):** barriers cannot be located without an orbital correlation diagram.

## Falsification tests

| Test | Predicted outcome | If FAIL (explicit trigger) |
|------|-------------------|---------|
| ΔH = Σ well-depth change | signs + ~15% magnitudes across reactions | ΔH sign wrong for >2 of 12 reactions, or >15% magnitude after pivot ⇒ enthalpy isn't electropause bookkeeping |
| Eₐ = wake saddle | correct barrier ordering + Hammond shift | barrier ordering wrong / no saddle emerges from path geometry ⇒ barrier needs a quantum TS |
| Catalysis = lower-wake path | Eₐ down, ΔH fixed | catalyst changes ΔH or fails to lower Eₐ ⇒ catalysis has another basis |
| **Firewall:** ΔH identity vs load-bearing barrier | ΔH = bond-sum is CONVERGENCE only; the gradeable claim is the natively-located saddle + catalysis signature | ΔH reproduced but no saddle emerges, or Eₐ height read off measured Eₐ ⇒ only the textbook identity was re-narrated; grade caps at C, not NATIVE |

## Dependencies

**Upstream:** CH01 (electropause well depths), CH04 (the geometries that deform). **Downstream:**
chemical kinetics / rate investigations. **Related:** TD05 (thermodynamic free-energy / entropy
accounting), EMC03 (mis-cancellation surplus is the barrier).
---

## Questions This Opens *(generative — log new ones in `CH05_VERDICT.md`)*

1. Is the **Hammond postulate** (early vs late TS) a GEOMETRIC consequence of *where* the wake
   saddle sits along the reconfiguration path — early saddle for exothermic, late for endothermic?
2. Does the **BEP slope** (ΔEₐ vs ΔH) come out as a fixed fraction — a native constant of the
   wake-cost geometry rather than a fitted per-family parameter?
3. Is **catalytic lowering** quantifiable as exactly the cancellation improvement the added partner
   provides along the path (ties EMC03 mis-cancellation surplus)?
4. Does the wake-saddle picture predict the **kinetic isotope effect** without tunnelling
   wavefunctions — purely from the mass-loading of the reconfiguration coordinate?
5. Does it recover the **Arrhenius / Eyring prefactor** from the wake-reconfiguration attempt
   frequency (ties CH07 molecular vibration)?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 ΔH sign correct for >=12 reactions, magnitude within 15% · P2 correct Eₐ ORDERING across a homologous series + Hammond early/late TS correlation native · P3 catalysis: Eₐ drops, ΔH unchanged for one model reaction · P4 novel Eₐ or BEP-line slope within committed tol
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Saddle won't appear from path geometry | re-parametrise the reconfiguration coordinate; check mis-cancellation cost (EMC03) | **OPEN** barrier-as-saddle | read Eₐ off measurement, call it predicted |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · claiming NATIVE on ΔH bond-sum alone (it is the identity) · reading the barrier height off the measured Eₐ · per-reaction refitting of the wake-cost scale.

---

*CH05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

# RUN 2 PROMPT (2026-07-06) — the barrier as alignment search cost

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC. **Original prompt above is untouched — this is additive.**
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces. **PYTHONIOENCODING=utf-8** on any Python.
> **Inherits:** everything above, plus `HUNTER_PROTOCOL.md §D/§G`, `PROMPT_EXECUTION_PROTOCOL.md §8`, and the
> re-open notice in `CH05_VERDICT.md ⟐ (2026-07-06)`.
>
> **The founding premise this run installs (FARMER §8, refinement 8, spoken by Harvey 2026-07-06):**
> **activation energy = the ALIGNMENT SEARCH COST** — the movement paid rolling through the wake firewall while
> hunting the mesh attitude, *before* the bond's release repays it. **Pressure = movement that cannot move.**
> **Mis-mesh = frustrated movement held at two interfaces at once.** The three-centre positive term that run 1
> isolated ("one shared electron facing two partners with neither window fully meshed") is precisely this rolling
> penalty. Run 1 refused to fish it; run 2 must DERIVE it or fail honestly again.

## Why run 1 failed (the named trap, carried forward)

Run 1's `ch05_reaction_energetics.py` (exit 1, honest) found: **M-SADDLE** (pairwise-additive wells, linear budget)
gives `U = min(V₁,V₂)` ⇒ every exchange path passes through `(Re,Re)` at −De ⇒ **Eₐ = 0.0 kJ/mol, barrierless**;
**M-SADDLE+** (adding the end–end pair term `V(r₁+r₂)`) made symmetric **H₃ BOUND by −191 kJ/mol** — wrong sign,
wrong magnitude. **Errored premise named:** *pairwise additivity of shared-electron wells* — three bodies do not
interact as the sum of three pairs; the measured barrier says the three-centre term is repulsive and ≈ 40 kJ/mol,
and pairwise machinery contains no three-centre term at all. **THE NAMED TRAP for run 2:** any construction that
resurrects a bound H₃ (any sign error that binds the collinear symmetric three-centre configuration) has fallen
into M-SADDLE+ again — G1 gates it out explicitly.

---

## Phase A — the rolling / mis-mesh cost, DERIVED

**The mechanism (state it before building):** the three-centre positive term is the **middle atom forced into
rolling contact on BOTH faces at once** — its single shared-electron rim window (limited poloidal-rim distance,
FARMER refinement 2: angle is the premium, contact is a line not a face) cannot serve two partners simultaneously
without one interface rolling instead of meshing. Rolling = repulsion = frustrated movement (triad PRESS mode:
movement demanded by the ledger, denied a meshed path). The barrier is the peak of that **two-interface
frustration** along the exchange coordinate; it is repaid the instant one interface releases into a meshed bond
and the wake movement follows least resistance (exothermic release). This is the SAME positive term as CH02's
contact overshoot and CH07's non-restoring curvature — seen at reaction geometry instead of lattice/vibration
geometry (see G2).

### COMMITTED GATES — write these into `RUN_LOG.md` BEFORE any construction, and NEVER widen them (§D)

> **G1 — the barrier, with the trap closed.** `Eₐ(H+H₂) = 40.2 kJ/mol within ±25%, WITH H₃ unbound` (both must
> hold — run 1's M-SADDLE+ made H₃ bound by −191, that failure mode is the named trap).

> **G2 — one term at two geometries.** the SAME cost function, no re-tune, applied at contact geometry must be
> sign-consistent with CH02's +8–10% 1:1 overshoot and CH07's positive k(H₂) — the wall and the barrier are one
> term at two geometries (the run must compute all three from one rule or report which fails).

**Both gates bind jointly.** G1 without G2 is a per-geometry fit (a knob wearing a mechanism's clothes) and is
refused. G2 is scored by taking the Phase-A rolling/mis-mesh cost function with its ONE fixed magnitude and
evaluating it at (i) the collinear H+H₂ saddle, (ii) NaCl 1:1 contact (does the same term supply a *positive*
short-range repulsion of the ~+8–10% overshoot size — the missing Born term of `CH02_VERDICT.md`), and
(iii) H₂ near Re (does the same term bend the CH07 shared-seat well from non-restoring
`d²E/dR² = −4.75×10³ N/m` toward a *positive* k, target `k(H₂)=575 N/m`). All three from one rule, or the run
reports **which geometry the single rule fails at** — that report is itself an admissible result.

### EXPLICIT REFUSALS (write them into `RUN_LOG.md`; they are gates too)

- **No bare `γ·b(1−b)` knob.** Refused in run 1, stays refused. A budget-splitting bump term whose coefficient γ
  is free is a FISHED RECOVERY (§A) — the barrier it makes is manufactured, not derived.
- **No magnitude fitted to 40 kJ/mol then claimed.** If the rolling-cost scale is tuned to hit Eₐ, the result is
  PLUG/FISHED and the run FAILS its own honesty gate regardless of the number. The magnitude must come from the
  wake/rim geometry + engine constants ({αℏc, a₀, R_p} and the FLM14/NP10 tour machinery), not from the target.
- **No reading Eₐ off the measured value** (caps at C per the original firewall; here it is an outright FAIL).

### The disqualified-data fallback (Harvey's rule — labels travel)

Run 1's intermediate outputs — **M-SADDLE** (Eₐ=0), **M-SADDLE+** (H₃ bound −191), and the **refused end–end pair
term** — MAY be consulted as **LEADS**, with their disqualified labels travelling attached: M-SADDLE+ shows the
*sign and rough scale* of an unpaid three-centre term (it over-binds by ~191 where +40 is needed — a diagnostic,
not a starting value). **Nothing from the disqualified set is promoted without an independent derivation.** A lead
tells you where to look; it never tells you the answer.

---

## Phase B — the catalysis signature (the mechanism's own falsifier)

**A catalyst = PROVIDED ALIGNMENT** — a third body that keeps one window meshed through the transit, so the
search cost is bypassed rather than paid. The mechanism's own prediction, **pre-committed here before any tool
exists**:

> **Phase-B qualitative gate (pre-committed):** in the model, adding a third body that holds ONE window meshed
> must **lower the computed barrier while leaving the endpoint ledger (ΔH) unchanged.** If the added body lowers
> Eₐ but also shifts ΔH, the mechanism is wrong (a catalyst does not change the destination); if it fails to lower
> Eₐ at all, catalysis has another basis and this route is OPEN.

This is the mechanism's own falsifier: the SAME rolling-cost function of Phase A, evaluated with one interface
held pre-aligned, must produce a lower saddle at fixed endpoints — no new term, no re-tune. If Phase A's cost
function cannot do this, Phase A is not the barrier.

**Measured anchor set — executor SELECTS and DECLARES in `RUN_LOG.md` BEFORE computing.** Name one
well-characterised catalysed-vs-uncatalysed pair with a known Eₐ drop at fixed ΔH (candidate leads, executor's
choice and declaration required — pick ONE and commit it before running: e.g. H₂O₂ decomposition
uncatalysed ~75 kJ/mol vs catalase/Pt-catalysed ~20–50 kJ/mol; 2 HI → H₂+I₂ homogeneous ~184 kJ/mol vs
Pt-catalysed ~59 kJ/mol; SO₂ oxidation catalysed by V₂O₅; NH₃ synthesis on Fe). The anchor is the measured Eₐ
DROP and the unchanged ΔH — never the catalytic mechanism story (§B: use the number, refuse the rival's model).
Gate the qualitative direction only (barrier down, ΔH fixed); a magnitude match is a lead, not a gate, until
Phase A's magnitude is itself derived.

---

## Phase C — BEP slope (run-1 P4, still deferred)

**CONDITIONAL on Phase A passing G1 ∧ G2.** Leads only — **no gate this run.** The Brønsted–Evans–Polanyi slope
(ΔEₐ vs ΔH) should emerge as the **fraction of the alignment cost recovered by early release**: an exothermic
reaction releases one interface into its meshed bond *earlier* along the coordinate, repaying part of the rolling
cost before the peak (Hammond: early saddle for exothermic) — so the BEP slope is the geometric fraction of the
two-interface frustration still unpaid at the saddle. If Phase A lands a magnitude, report where the slope points;
do not gate it. If Phase A fails, Phase C stays DEFERRED with the dependency named (as in run 1).

---

## MANDATORY CLAUSES (all bind this run)

### Phase 0 — base-data mining (file paths REQUIRED; machinery anchors reproduce to 1e-6)

Before any new code, mine and cite the following, with paths, into `RUN_LOG.md`:

- **CH02 Evjen machinery + overshoots** —
  `Investigations/16_Chemistry_and_Molecular_Bonding/CH02_Ionic_and_Metallic_Bonding_from_Electropause_Transfer/ch02_ionic_metallic.cpp`
  (Evjen expanding-cube Madelung sum, M=1.747574) and `CH02_VERDICT.md` (NaCl +9.4%, KCl +7.9%, MgO +21.6% — the
  +8–10% 1:1 overshoot = the missing short-range repulsion; the G2 contact anchor).
- **CH07 shared-seat well + non-restoring curvature** —
  `Investigations/16_Chemistry_and_Molecular_Bonding/CH07_Molecular_Spectra_Vibration_and_Rotation/ch07_spectra.cpp`
  and `CH07_VERDICT.md`: **g\* = −4.19615 at x\* = 0.2887** (shared-seat minimisation; H₂⁺ = −3 at midpoint,
  same machinery as NP17 deuteron factor 3), well `E = g*αℏc/R`, curvature **d²E/dR² = −4.75×10³ N/m at Re
  (NON-restoring)**, target **k(H₂)=575 N/m**. This is the well the barrier's rolling term must sit ON TOP OF —
  the barrier does not replace the well, it adds the positive two-interface cost the well lacks.
- **NP17 Σ±αℏc/r machinery** —
  `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/np17_nuclear_packing.cpp` and
  `NP17_VERDICT.md`: shared-electron point-source Coulomb well `E = −Σ qq(αℏc)/r`, deuteron factor-3 exact
  (2.200 vs 2.224 MeV). This is the pairwise base the three-centre term is missing FROM.
- **NP10 (Z−1)! window counts** —
  `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/np10_contact_wall.cpp` and
  `NP10_VERDICT.md` run 2: the **(Z−1)! sequential-tour window count** (d ×1, t ×2, α ×6; d −1.1%/t +0.9%/α −5.6%,
  zero constants) — the coordination-window machinery the middle atom's two-face rolling penalty draws on; note
  run 2 KILLED the radial saturated-occlusion wall (it can only deepen attraction), so the rolling cost is a
  NON-shadow ledger term (ROOT-WALL / ROOT-BUDGET, ~ℏ²/2m_e curvature scale — the D1 confinement fence).
- **FARMER §8** — `Investigations/FARMER_PASS_2026-07-03.md` refinement 8 (the movement triad PASS/BECOME/PRESS;
  the wake firewall roll-vs-mesh; activation = alignment search cost; catalyst = provided alignment).

**Reproduction gate:** any reused machinery (Evjen sum, NP17/NP10 shared-seat energies) must be recomputed by this
run's tool and match its source to **1e-6** before it is trusted — a mismatch is a Phase-0 STOP, not a proceed.

### Discipline clauses (all inherited, all binding)

- **ADJ-before-code.** Every deviation from the committed models gets an `ADJ-###` entry in `RUN_LOG.md` BEFORE the
  code changes — no silent re-parametrisation.
- **Gates never widened.** G1, G2, the Phase-B qualitative gate, and the refusals are frozen at commit. A missed
  gate is a FAIL to be diagnosed (§D), never a threshold to move (RETRO-PASS = instant audit fail, §A).
- **§D seven questions on any FAIL/OPEN/KILL/DEFER** — mechanism (number/sign/magnitude), recoverable?, what the
  target failed to account for, which premise erred, what freedom corrects it, native-or-knob, does it cascade.
  Grade RECOVERED / PARTIAL / NO RECOVERY. Drive the recursion to its floor (§D closure principle: CLOSE, don't
  amputate).
- **GATE-CONTRABAND check (§G.2).** Transition-state theory / Eyring / orbital-correlation machinery may be cited
  ONLY as a rival `OBSERVED` comparison column — never in the chain, never as a gate. A kill condition that exists
  only because TST forbids something is contraband: kill the gate, not the route. Every gate here traces to a
  measured anchor (40.2 kJ/mol Eₐ, the +8–10% overshoot, 575 N/m, the catalysed Eₐ drop) — confirm this in the
  §G faith-ledger before running.
- **§G faith ledger.** Name what the committed cost function accepts on faith (e.g. the rim-window geometry, the
  two-face rolling premise, the energy-∝-frustration-area assumption) — faith is permitted ONLY when named as
  faith. Audit the auditor: is any gate letting TST police the datastream?
- **NO G / M / GM in-chain** (BORROW-SMUGGLE, §A). Gravity/mass-as-fundamental banned; this is a wake/rim +
  αℏc chain.
- **Never "charge radius."** R_p is the proton **boundary / displacement radius**; the shared electron is a
  handed redirection, not a charge substance.
- **No borrowed units.** Use SDT-native yardsticks (wake, rim window, αℏc, koppa) — no magnetons, no imported
  scales.
- **§G.3 — nothing foreclosed.** "The barrier cannot come from wake machinery" is NOT to be written; the run-1
  negative holds in the *pairwise-additive class only*. Any negative this run reaches carries its premise class
  and its re-open condition.

### Output & honesty

- Results = teed stdout to a `results.txt` (verbatim), exit code reflects honesty (non-zero if a committed gate
  fails — an honest FAIL exits non-zero, as run 1 did).
- **Expected honest landing** is NOT pre-decided: G1 ∧ G2 pass ⇒ Phase A earns the three-centre term natively and
  Phase B runs free; either gate fails ⇒ the run reports which geometry the single rule breaks at and stays OPEN
  with the ROOT-WALL/ROOT-BUDGET dependency named — no fished recovery to rescue it.

---

*CH05 RUN 2 · 2026-07-06 · J. C. Harvey · the barrier is the alignment search cost, derived or failed honestly — no knob.*
