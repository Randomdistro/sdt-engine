# NP08: Triple-Alpha Rate from Geometric Packing — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP08] NP08: Triple-Alpha Rate from Geometric Packing — Data/Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| C-12 ground state mass | 12.000000 u (definition) | AME2020 |
| He-4 mass | 4.002603 u | AME2020 |
| 3 × He-4 mass | 12.007809 u | Computed |
| Mass excess = 3×m_α − m_C12 | 7.275 MeV | Q-value |
| Hoyle state energy | 7.654 MeV above C-12 g.s. | Measured |
| Hoyle state width | 8.5 eV | Measured |
| C-12 grammar | 1 alpha + 4 deuterons | ATOMICUS/006_C12.md |
| Alpha geometry | Tetrahedral (2p+2n) | SDT |

## INVESTIGATION PROMPT

**Target**: Derive the Hoyle state energy (7.654 MeV) from the geometric packing energy of 4 deuterons closing around an alpha core.

### SDT Interpretation

C-12 is NOT three alphas. It is 1 alpha core + 4 deuterons (α + 4d). The "triple-alpha" process is actually:
1. α + α → Be-8* (unstable — immediately decays unless...)
2. α + Be-8* → C-12* (Hoyle state) → C-12 + γ

SDT re-reads this as:
1. Two alpha cores approach → their ℓ≥3 wakes overlap → forms Be-8 (2α, no deuterons)
2. Be-8 grammar: 2α + 0d is UNSTABLE in SDT (no scaffold bonds — two standalone alphas)
3. A third alpha approaches → the combined 12 nucleons rearrange into α + 4d (C-12 grammar)
4. The 7.654 MeV Hoyle state = the geometric threshold for tetrahedral closure of the 4 deuterons around the central alpha

### Calculation

1. Compute the tetrahedral closure energy: 4 deuterons at the vertices of a tetrahedron surrounding a central alpha → the packing energy when the deuterons lock into their scaffold positions
2. Energy = sum of all d-α occlusion bonds + d-d occlusion bonds − Coulomb repulsion between the 4 deuterons' protons
   — NOTE (2026-07-03): NP09's scalar-occlusion route FAILED (−97.3%) and FLM12-D1 ruled the linear volume-price out at 34×; revise the premise before execution.
3. Compare to 7.654 MeV

### Success Criteria
- [ ] Hoyle state energy derived within 20% of 7.654 MeV
- [ ] The instability of Be-8 explained by grammar (2α + 0d = unbonded)
- [ ] The C-12 grammar (α + 4d) confirmed as the stable endpoint
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 20%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---
---

# RUN 2 PROMPT (2026-07-06) — the Hoyle barrier as alignment cost

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (run 2 — written 2026-07-06, nothing run).
> **Trigger:** the ⟐ RE-OPENED notice in `NP08_VERDICT.md` (2026-07-06) — the named dependency
> moved from "absent" to "candidate awaiting derivation": NP10 run 2 put the **(Z−1)! closed-tour
> lock** on record (d −1.1% / t +0.9% / α −5.6%, zero constants, post-diction declared; falsifier
> Z=5 → ×24; owner FLM14).
> **Mechanism class under test (FARMER refinement 8, 2026-07-06):** activation energy = the
> **alignment search cost** paid before release. Desynchronised rotations ROLL on mutual wake
> firewalls (roll = repulsion); cadence-locked rotations MESH (mesh = bond = movement saved);
> aligned → bond → wake movement RELEASED → least resistance. The 0.379 MeV Hoyle closure
> barrier is read as the frustrated-movement cost of three alphas rolling on mutual firewalls
> while hunting the α+4d mesh attitude; the 0.092 MeV Be-8 margin is the same quantity at A=8
> (packing competition = two attitudes with nearly equal frustration).
> **Inherits:** the run-1 header block above in full (template §⓪–§⑩, `PROMPT_EXECUTION_PROTOCOL.md`,
> anti-creep R0–R5) **plus** `Investigations/HUNTER_PROTOCOL.md` §§A–G (the §G mirror and the
> GATE-CONTRABAND check are mandatory, not optional).
> **Run 1 is untouched.** Its verdict, its DEFERRED, its premise correction, and its RUN_LOG all
> stand. This section only adds the run-2 program.

## ⓪ Golden Rule — run-2 answers (the run-1 blank, now filled)

1. **What don't we know?** Whether ONE derived lock rule, added to run-1's knob-free repulsion
   ledger, lands BOTH the 0.379 MeV Hoyle closure barrier AND the 0.092 MeV Be-8
   packing-competition margin with no per-nucleus freedom.
2. **Why does it matter?** It is the first two-target test of the ROOT-LOCK candidate outside
   the ladder it was read off (d/t/α), and the first quantitative test of refinement 8's
   "activation = alignment search cost" anywhere in the repo.
3. **How will we find out?** Phase A (runs now): assemble every constraint the base already
   holds and publish the REQUIRED lock values as a target row before any lock derivation
   exists. Phase B (blocked): score the derived lock against both targets. Phase C: sign-only
   falsifier at A=12→16.
4. **What would prove us wrong?** Phase-B dual-gate failure (either target missed at committed
   tolerance); or Phase-C producing a spurious sub-threshold barrier where capture is downhill.
5. **How will we know we're done?** Dual verdict per protocol; the 20% Hoyle gate from run 1
   remains unscored until Phase B actually runs.

## Phase 0 — base-data mining (MANDATORY, do this before anything else)

Read, with file paths logged in `RUN_LOG.md` (run-2 block, appended — run-1 block untouched):

| Source | Path | What to extract |
|---|---|---|
| Run-1 verdict + re-open | `Investigations/05_Nuclear_Physics/NP08_Triple_Alpha_Geometric_Packing/NP08_VERDICT.md` | 6.327 MeV repulsion ledger; 0.379 MeV barrier isolation; 0.092 MeV Be-8 margin; committed geometry |
| Run-1 tool (machinery anchor) | `.../np08_triple_alpha.cpp` + `np08_results.txt` | the point-Coulomb ledger code — **reusable verbatim**; re-run must reproduce 6.327 MeV to 1e-6 before anything new is trusted |
| Run-1 commitments | `.../RUN_LOG.md` | committed geometry r_cv = R_He + D/2 = 2.657 fm; D = 2R_p + R_p/3; forbidden moves |
| NP10 run 2 (lock candidate) | `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/NP10_VERDICT.md`, `np10_contact_wall.cpp`, `np10_contact_wall_results.txt` | (Z−1)! ladder: d ×1 → 2.200 MeV (−1.06%); t ×2 → 8.557 MeV (+0.88%); α ×6 → 26.721 MeV (−5.57%); registered falsifiers (Z=5 → ×24, He-3); "B = tour-count × electrostatics" is UNDERIVED — carry that label |
| NP17 (shared-electron machinery) | `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/NP17_VERDICT.md`, `np17_nuclear_packing.cpp`, `np17_results.txt` | E = −Σ q·q · αℏc / r; αℏc = 1.4400 MeV·fm the ONLY energy scale; deuteron 3αℏc/D = 2.200 MeV; lock target curve ≈ 0.02 / 4.2 / 23.8 MeV (d/t/α) |
| Nuclear Packing Sequencer | `Release/HTML_SDT_Website/nuclear-packing-sequencer.html` | shadow-overlap (union-not-sum) results: κ ≈ 10.7 MeV/fm², R² = 0.988, N = 217; honest residual — over-binds α-cluster nuclei (directly relevant leads) |
| PPT08 seat table | `Investigations/02_Particle_Physics_and_Topology/PPT08_Angular_DOF_from_Trefoil/PPT08_VERDICT.md`, `PPT08_KOPPA_TARGET.md` | the three-seat table (0.272 / 0.410 / 0.452 fm) as angular-window geometry leads |
| Alignment-cost mechanism | `Investigations/FARMER_PASS_2026-07-03.md` refinement 8 (and refinement 2: contact ANGLE is the scarce resource) | the mechanism class Phase B must instantiate |
| Grammar constitution | `ATOMICUS/rules/On the Nature of Atomicus Rules.md` | n_d = 3Z−A−2, n_t = A−2Z — inviolable |
| Audit sheet | `Investigations/HUNTER_PROTOCOL.md` | §D seven questions, §G mirror, GATE-CONTRABAND definition |

**Harvey's disqualified-data fallback (standing order, applies to this run):** disqualified and
quarantined material MAY be consulted as **LEADS** — specifically NP09's failed scalar-bond
intermediates (`Investigations/05_Nuclear_Physics/NP09_Deuteron_Binding_from_Occlusion/` —
RESOLVED-NEGATIVE, −97.3%; its geometry intermediates, not its conclusion) and PPT08A
(`.../PPT08A_Per_Spation_Rolling_Mechanics/` — **fabrication-flagged in the 2026-07-02 HUNTER
scour**; its rolling-mechanics framings may be read as leads ONLY). **Disqualification labels
travel with every number quoted from these sources.** Nothing from a disqualified source is
promoted into a gate, a target, or a derivation input without an independent derivation of its
own. Quote → label → derive-or-drop.

## Phase A — leads mining + the REQUIRED-lock target row (runs NOW, no dependency)

Phase A is executable today. It derives nothing new; it assembles every constraint the base
already holds on the α+4d closure and publishes the target row. All AME-derived numbers carry
the IDENTITY label exactly as in run 1.

**A1 — Machinery anchor.** Recompile/re-run the run-1 point-Coulomb ledger at the committed
geometry (r_cv = R_He + D/2 = 2.657 fm). Gate: reproduce **6.327 MeV to 1e-6** (machine
agreement with `np08_results.txt`). If this fails, STOP — the base is corrupted; report the
blocker (pivot table row 1).

**A2 — The Be-8 repulsion ledger.** Same machinery, verbatim, applied to the α+2d
configuration (grammar: n_d(Be-8) = 3·4−8−2 = 2 — the constitutional decomposition, NOT 2α;
run 1's premise correction stands). Geometry rule identical in form to run 1's (contact
spacing from R_He, D; no new geometric freedom — if a placement choice is unavoidable for two
deuterons, enumerate the symmetric candidates, commit the rule in RUN_LOG **before** computing,
and report all enumerated values). Output: **E_rep(α+2d), DERIVED, knob-free.**

**A3 — The constraint table.** Tabulate, with source paths and labels, every number the base
holds against the closure: run-1 ledger rows (scaffold binding required: Be-8 23.755 MeV =
11.88/d; C-12 54.968 MeV = 13.74/d — IDENTITY); NP10 run-2 lock ladder and per-structure
energies; NP17 well depths and its 0.02/4.2/23.8 MeV lock-target curve; Sequencer κ ≈ 10.7
MeV/fm² shadow-overlap results (with its declared α-cluster over-binding residual); PPT08 seat
table (leads label per Phase 0).

**A4 — The REQUIRED-lock target row (the error-resistance step).** Publish, in stdout and
RUN_LOG, BEFORE any lock derivation is attempted anywhere:

- **ROW-H (A=12):** the attractive lock magnitude the 0.379 MeV Hoyle closure barrier REQUIRES
  given the 6.327 MeV repulsion, under the committed first-order ledger identity
  **L_req(Hoyle) = E_rep(α+4d) − ΔE_barrier = 6.327 − 0.379 = 5.948 MeV** at the transit
  attitude. Label: REQUIRED (IDENTITY-derived target, not a result).
- **ROW-B (A=8):** the lock magnitude the 0.092 MeV Be-8 packing-competition margin REQUIRES:
  **L_req(Be-8) = E_rep(α+2d) − 0.092 MeV**, with E_rep(α+2d) from A2. Same label. Declare
  explicitly: 0.092 MeV is the difference of two ~28 MeV ledgers — **subtractive cancellation**,
  quoted to the digits the AME anchors support and no further.

If the executor judges the first-order identity structurally wrong (e.g. the barrier is not
"repulsion minus lock at one attitude" but an attitude-path integral), the correction is an
**ADJ entry logged before any code**, and BOTH rows are republished under the corrected
identity. The rows may be restated by ADJ; they may never be silently moved. **Purpose,
stated plainly:** these two numbers go on the record while no lock derivation exists, so that
a future fitted lock cannot be steered toward them and then sold as a prediction — any Phase-B
pass must be produced blind by a rule derived elsewhere (FLM14/NP17), against targets whose
timestamp precedes it.

**A5 — Consistency cross-check (leads only, no gate).** Compare ROW-H/ROW-B against the NP10
(Z−1)! ladder and the NP17 target curve: does ×6 tour-lock arithmetic, extended to the α+4d
mesh by any non-fitted counting rule, land near 5.948 MeV? Report the comparison as OPEN
commentary — it gates nothing in Phase A.

## Phase B — the dual zero-freedom gate (CONDITIONAL — BLOCKED until the lock is DERIVED; owner: FLM14/NP17)

**Blocking condition (hard):** Phase B does not run until the lock rule is DERIVED — i.e.
FLM14's residence/tour-energy law (or NP17's geometry) produces "energy ∝ tour multiplicity"
(or its corrected form) from mechanism, not from the d/t/α ladder it was read off. The (Z−1)!
candidate is a post-diction until then. Pattern-matching the ladder does NOT unblock this
phase. DEFERRED stands, exactly as run 1 left it.

**The gate (verbatim, committed now):** One derived lock rule + the run-1 repulsion ledger
must land BOTH the 0.379 MeV Hoyle closure barrier AND the 0.092 MeV Be-8 packing-competition
margin — same rule, same constants, no per-nucleus freedom. Gates: 0.379 MeV within ±30%;
0.092 MeV within ±50% (looser — smaller number, subtractive cancellation declared in Phase A).
BOTH must pass or the mechanism fails as stated.

**Alignment-cost framing to test (refinement 8):** the barrier = the frustrated-movement cost
of three alphas rolling on mutual firewalls hunting the α+4d mesh attitude. Operationally: if
the lock derivation produces an **angular window** (refinement 2 — contact angle is the scarce
resource; rim-windows mesh at a line, not a face), then the barrier must be computable as the
**mis-mesh energy at the transit attitude** — the worst-frustration attitude on the path from
3α (rolling) to α+4d (meshed). The Be-8 margin is then the same computation at A=8, where two
attitudes (α+2d vs 2α reassembly) have nearly equal frustration and the competition is decided
by 0.092 MeV.

**Rules of engagement:** gates never widened (ADJ may only tighten or restructure with the
identity correction of A4, never relax); no per-nucleus constants; no electron placements
invented (run 1's forbidden list carries over); on FAIL, the §D seven questions run in full
and the failure is traced to root before any successor is proposed; on PASS, the §G mirror
runs before any celebration — name what the pass still accepts on faith (at minimum: the
derived lock rule's own upstream premises).

## Phase C — the falsifier extension (sign check only, look-elsewhere protected)

The same machinery must NOT manufacture barriers where nature has none. Pre-committed check:
**A=12→16** — O-16 via α capture on C-12 proceeds downhill/resonant differently (no Hoyle-type
closure bottleneck of the same character). Applying the Phase-B rule + ledger machinery to the
O-16 closure (grammar: Z=8, A=16 → α + 6d) must NOT produce a barrier below the Hoyle-scale
threshold that would predict a second triple-alpha-style bottleneck where none is observed.

**Protection (committed):** this is a **sign/existence check only** — one pre-registered
comparison, no scanning across A until something interesting appears, no quantitative gate on
the O-16 number (the resonance structure of O-16 formation involves capture dynamics this
prompt does not model). PASS = no spurious sub-threshold barrier; FAIL = machinery
over-produces barriers → §D on the mechanism, not a widened reading of "differently."

## Mandatory clauses (non-negotiable, run-2)

1. **ADJ-before-code.** Every adjustment (geometry rule for A2, identity correction for A4,
   anything) is logged in RUN_LOG with an ADJ-### entry BEFORE the code that uses it is written.
2. **Gates never widened.** ±30% / ±50% / 1e-6 anchor / sign-only are frozen at this commit.
3. **The constitutional grammar is inviolable.** Be-8 = α + 2d per n_d = 3Z−A−2, NOT 2α — run 1's
   premise correction stands. C-12 = α + 4d. O-16 = α + 6d. No other decompositions.
4. **§D seven questions on any FAIL**; recovery graded; cascade root named.
5. **GATE-CONTRABAND check (§G.2):** every kill/pass condition above must trace to a measured
   anchor (AME margins, run-1's derived ledger) or a pre-committed native criterion — never to
   a rival's axiom. Audit the three gates for contraband at run start and record the finding.
6. **NO G / M / GM anywhere in-chain.** Lengths from R_p, R_He, D; energy scale αℏc only.
7. **Never "charge radius."** R_p is the proton **boundary radius** (boundary/surface/
   displacement radius). No charge substance; EM language = handed redirection.
8. **No borrowed units.** MeV·fm / fm / MeV throughout; no magnetons, no imported yardsticks.
9. **AME masses enter only as labelled IDENTITY / measured (OBSERVED) anchors** — flagged at
   the point of use, in stdout and in the verdict, exactly as run 1 did.
10. **Results = teed stdout; exit honesty.** Tool prints everything to stdout, redirected/teed
    to `np08_run2_results.txt`; exit code 0 only if every executed gate passed (Phase-A anchor
    included), non-zero otherwise — an honest exit 1 is a valid result (cf. NP10 run 2).
11. **Build recipe (MSVC):** `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:np08_run2.exe <tool>.cpp`
    — `#include <sdt/laws.hpp>` only; no local constant namespaces. If any helper script is
    Python: set `PYTHONIOENCODING=utf-8` before running (Windows console).
12. **Verdict:** dual header (prompt completion A–F + physics class), appended to
    `NP08_VERDICT.md` as a run-2 section; run-1 text untouched.

---

*NP08 RUN 2 · SPEC 2026-07-06 · J. C. Harvey · Phase A runs now; Phase B blocked on the derived
lock (owner FLM14/NP17); the target row goes on the record before the lock exists — that is the
point.*
