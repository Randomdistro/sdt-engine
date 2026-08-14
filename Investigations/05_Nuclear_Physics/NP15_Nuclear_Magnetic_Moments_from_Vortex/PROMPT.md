# NP15: Nuclear Magnetic Moments from Vortex Geometry — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP15] NP15: Nuclear Magnetic Moments from Vortex Geometry — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Question

The proton's magnetic moment is +2.793 μ_N — anomalous (not 1.0) because it is not a point charge. The neutron has μ = −1.913 μ_N despite being neutral. Standard physics explains these via quark substructure. SDT must explain them from the W=3 trefoil torus circulation.

## 2. Methodology

### Step 1: Magnetic moment from circulation

A current loop produces a magnetic moment μ = IA. For a torus:
- The toroidal circulation (v_T, around the major axis) generates a poloidal magnetic moment
- The poloidal circulation (v_P, around the minor axis) generates a toroidal magnetic moment

For the proton (charged, W=3):
- The charge circulates with the torus flow
- μ_proton = contribution from ALL three circulation modes
- The W=3 trefoil means the charge traces the torus 3 times poloidally per toroidal circuit
- This amplifies the magnetic moment by a factor related to W

### Step 2: Derive μ_proton

$$\mu_p = \frac{e}{2m_p c} \times g_p \times (\text{mode structure factor})$$

Where g_p is the Landé g-factor. SDT predicts g_p from the trefoil geometry:
- g_p = (W+1)/2 × (v_P/v_T ratio) × (helicity correction)
- Must give g_p = 5.586 (since μ_p = g_p × μ_N / 2 = 2.793)

### Step 3: Derive μ_neutron

The neutron has the SAME W=3 topology but NO net charge. However, its internal circulation generates charge separation:
- The neutron's trefoil has regions of + and − charge density (measured)
- The circulating charge distribution generates a NET magnetic moment
- The sign is NEGATIVE because the charge distribution's centroid is opposite to the proton's

SDT must explain:
- Why μ_n / μ_p ≈ −2/3 (is this a geometric ratio from the trefoil?)
- Why the neutron has a negative moment (the charge distribution is inverted)

### Step 4: Composite nuclei

For d (p+n), t (p+2n), He-3 (2p+n):
- Add the constituent moments vectorially
- Account for the relative spin orientations in the ground state
- μ_d should ≈ μ_p + μ_n = 0.880 (measured: 0.857 — 2.6% off → exchange current correction in standard model; what is the SDT equivalent?)

### Step 5: Schmidt limits comparison

Standard nuclear physics has the Schmidt limits: μ_free_nucleon applied to single-particle states. SDT should reproduce these from the vortex geometry of the scaffold.

## 3. Required Outputs

1. **μ_proton derivation**: From W=3 trefoil geometry → 2.793 μ_N
2. **μ_neutron derivation**: From charge-separated W=3 → −1.913 μ_N
3. **Composite nuclei table**: Predicted vs measured for d, t, He-3, He-4
4. **μ_n/μ_p ratio**: Is −2/3 a geometric consequence of the trefoil?
5. **Prediction for heavier nuclei**: Using grammar (d+t block structure), predict moments for Li-7, Be-9, etc.

## 4. Success Criteria

- [ ] μ_proton reproduced within 5% from geometric argument
- [ ] μ_neutron sign (negative) and magnitude explained
- [ ] μ_n/μ_p ratio explained geometrically
- [ ] Deuteron moment predicted within 5%
- [ ] α moment = 0 explained by tetrahedral cancellation
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP15
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 2.6%, 5%, 5%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

> NOTE: 2.6% equals the known μ_d discrepancy — re-commit a blind threshold before running.

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

*NP15 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---
---

# RUN 2 PROMPT (2026-07-06) — composite moments from mesh circulation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (run 2 — the run-1 prompt above is
> untouched and remains the historical record).
> **Authorised by:** `NP15_VERDICT.md` "⟐ RE-OPENED, composites route only (2026-07-06)"
> (§G.3 premise-class event, Harvey order).
> **Inherits:** everything the run-1 header inherits, plus `Investigations/HUNTER_PROTOCOL.md`
> §G in full (faith ledger + gatekeeper check at start AND at every kill).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.

## §0 SCOPE FENCE (written first; read before anything else)

1. **This run addresses A ≥ 2 COMPOSITES ONLY.** The question is the COMPOSITION RULE —
   how meshed blocks carry a moment — not the nucleon moments themselves.
2. **μ_p's current-to-moment map is NOT in scope.** It is still NP15's own unpaid debt
   (run-1 verdict, "Owed"). Nothing in this run may claim, imply, or partially credit a μ_p
   derivation.
3. **C5 (`g_p√(v_T v_P)/c`, +0.27%) stays QUARANTINED.** Consulting it as a **LEAD** is
   permitted under Harvey's disqualified-data fallback (§M2 below), but it **cannot be
   claimed**, cannot enter any PASS, and its quarantine label travels with any use. If a
   *derived* two-mode circulation map built in this run lands near the C5 form, the executor
   MUST disclose the coincidence explicitly and charge its look-elsewhere cost (run-1 logged
   ~5 combinations tried) in the verdict — proximity to C5 is a flag to raise, never a
   result to bank.
4. **μ_n is not re-fished.** It stays inherited from NP20 (magnitude IDENTITY, sign assumed,
   OPEN). Here it is a **declared measured input** (see Phase B), which is honest because
   this run tests composition, not nucleons.
5. The run-1 verdict's composite rows (DEGENERATE / FAIL labels) are not edited — run 2
   appends; it never rewrites the record.

## Phase 0 — base-data mining (file paths first; before any construction)

Mine the following, citing file paths in `RUN_LOG.md` for every geometric fact consumed:

- **The premise replacement.** `Investigations/FARMER_PASS_2026-07-03.md`, Rules refinements
  **8** (cadence-locked rotations MESH; mesh = bond = movement saved — a meshed pair's
  circulation is ONE shared tour, not two summed loops), **3** (meshing IS the mass defect;
  union-not-sum bookkeeping — the interleaved region is not attributable to either form
  separately), and **4** (electron positions are SEQUENTIAL; the orbital is a tour).
- **The packing geometry.** `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/`
  (`NP17_VERDICT.md`, `np17_nuclear_packing.cpp`): interleaved 6π trefoils; **neutron =
  proton + one internal electron**; the shared electron between adjacent protons IS the
  binding; deuteron spacing D = 2R_p + R_p/3. The composite's circulation topology lives here.
- **The tour multiplicity.** `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/NP10_VERDICT.md`
  (RUN 2 section) + `np10_contact_wall.cpp` / `np10_contact_wall_results.txt`: the **(Z−1)!
  interleaved closed-tour counts — d = 1, t = 2, α = 6** — reproduce the binding lock ladder
  with zero constants (d −1.06%, t +0.88%, α −5.57%). The tour multiplicity should enter the
  circulation. **Label travels:** the energy-∝-tour-count law is UNDERIVED (NP10 §G item 3,
  owed to FLM14); using the tour COUNT as a circulation multiplicity here is a new,
  independent use and must be declared as such, not inherited as earned.
- **Per-structure geometry (if findable).** In-repo: the Nuclear Packing Sequencer,
  `Release/HTML_SDT_Website/nuclear-packing-sequencer.html` (subunit-centric packing:
  interleaved trefoil clusters, holes facing a shared-electron centre; α = tetrahedral
  4-trefoil, t = 3-trefoil, d = 2-trefoil). NP17's referenced imports
  (`NUCLEAR_PACKING_STRUCTURE_AND_DATA.md`, `trefoil_mappings.json`) are **NOT in this repo**
  (checked 2026-07-06; companion repo `Spatial_displacement_theoriser`) — if unavailable,
  say so in `RUN_LOG.md` and proceed on in-repo geometry only.
- **The sequential-tour frame.** `Investigations/01_Foundations_and_Lattice_Mechanics/FLM14_Rotating_Spation_Sequential_Occupancy/PROMPT.md`
  (rotating spation, gear-stepped tours) — frame only; no FLM14 result is assumed landed.
- **Disqualified leads (see §M2).** Run-1's candidate table C1–C5 (`RUN_LOG.md` above),
  NP20 intermediates (`Investigations/05_Nuclear_Physics/NP20_Neutron_From_One_Seat/`).

## Phase A — the mesh-circulation rule (leads + construction; runs now)

**Replace the falsified premise.** Run 1 falsified block-ADDITION monotonically
(+2.6% → −6.3% → +10% → −14% → −62.4% with A): "grammar blocks are magnetically rigid and
independent" is dead. The successor, per FARMER refinement 8 and NP10 run 2: **packed blocks
MESH, and a meshed pair's circulation is ONE shared tour, not two summed loops.** The shared
electron's path threads BOTH partners' geometry — the composite moment is the **circulation
of the interleaved path**, not the sum of free moments. The NP10 tour counts (d = 1, t = 2,
α = 6 closed tours) are the multiplicity of exactly that interleaved path and should enter
the circulation.

**Construction requirement (error-resistance — this is the run's constitution):**
the rule must be written as a **single formula/algorithm over the grammar decomposition**
(1 alpha core + n_d deuterons + n_t tritons; alternate grammar where applicable) in
`RUN_LOG.md` **BEFORE any moment is computed**. One rule text, every row. declared dependencies:
μ_p and μ_n (declared measured inputs), the block tour counts / interleave geometry from
Phase 0, and engine lengths/speeds. **No per-isotope freedom of any kind** — no per-row
coefficients, orientations chosen after seeing numbers, or "silent" flags assigned per
nucleus. Every formula variant written down counts against the look-elsewhere ledger
(§ Phase B), whether or not it is run.

**Grammar note (constitutional).** Under n_t = A−2Z, n_d = 3Z−A−2: Li-7 = α + t (n_d = 0,
n_t = 1) — matching run 1; **Be-9 = α + d + t (n_d = 1, n_t = 1)** — run-1's table read
Be-9 as "2α + n", which contains a free neutron and is therefore grammar-contraband (a free
neutron is an exposed triton remnant). The constitutional decomposition GOVERNS the rule;
if the 2α+n cluster reading is consulted at all, it is a LEAD under §M2 with an ADJ entry.
The alpha content of Be-9 cannot be magnetically silent under meshing — the rule must say
HOW MUCH it contributes, from the rule text alone.

## Phase B — committed gates (blind; μ_N = borrowed comparison unit, flagged)

**Declared measured inputs:** μ_p = +2.7928 and μ_n = −1.9130 (μ_N, borrowed unit, flagged)
enter as measured inputs, declared here — this run tests COMPOSITION, not the nucleon
moments. All anchors typed as OBSERVED (engine `measured::` where present; Li-7/Be-9/Phase-C
from Stone 2019, typed literature anchors, flagged — as run 1 did).

| Row | Target (OBSERVED anchor, μ_N — borrowed unit, flagged) | Mesh-rule gate (blind, committed — never widened) | Run-1 block-addition NULL (reprinted beside every prediction) |
|---|---|---|---|
| B1 | μ_d = +0.8574 | within 5% AND error no worse than +2.61% — must at least match run-1's addition or the mesh rule LOSES to addition (recorded as such) | μ_p+μ_n = +0.8798 → +2.61% (PASS(5%), DEGENERATE) |
| B2 | μ_t = +2.979 | within 8% | μ_p → −6.25% (FAIL) |
| B3 | μ_h (He-3) = −2.128 | within 8% | μ_n → +10.10% (FAIL) |
| B4 | μ_α = 0 | exact, by closure — the cancellation must fall out of the tour-closure of the rule, not be asserted | 0 exact (PASS, DEGENERATE — every model) |
| B5 | μ(Li-7) = +3.2564 | within 15% | μ_p (α+t, α silent) → −14.24% (FAIL) |
| B6 | μ(Be-9) = −1.1778 | **within 15% — THE KILL-OR-CURE ROW** | μ_n (2α+n, α silent) → −62.43% (FAIL) |

- **Null column mandatory:** run-1's block-addition prediction is reprinted beside every
  mesh prediction, every table, every output. If the mesh rule does not beat the null where
  the null failed, that is the headline, not a footnote.
- **Look-elsewhere:** declare EVERY formula variant tried (including variants written and
  discarded before running). Gates are never widened; no post-hoc mixing, averaging, or new
  exponents after seeing numbers (run-1 decision rule carries over verbatim).
- **He-3 note:** h is the alternate-grammar core (NP10 run-2 registered falsifier: alternate
  grammar, 3p + 1e); the rule must reach it through the EC alternate grammar, not a special case.
- **Degeneracy cap declared now:** B4 (and B1 if the mesh rule reduces to addition at A=2)
  cannot exceed DEGENERATE — declared pre-run so a match cannot be inflated into NATIVE later.

## Phase C — falsifier row (one blind, out-of-construction isotope)

The executor picks **ONE additional odd-A isotope not used anywhere in construction**
(e.g. B-11 or N-15), **declares it in `RUN_LOG.md` BEFORE computing anything for it**, types
its measured moment at declaration time (Stone 2019, OBSERVED, typed literature anchor —
flagged), predicts **blind** from the same single rule text, and reports **inside/outside
15% honestly**. One isotope, one prediction, no second pick. An outside-15% result is
reported as FAIL with §D — it is not excused, contextualised away, or retried.

## Mandatory clauses (constitution for this run)

- **M1 — Phase 0 first.** Base-data mining with file paths (above) precedes construction;
  every geometric fact consumed is cited to its file.
- **M2 — Harvey's disqualified-data fallback.** C5, the NP20 intermediates, and run-1's
  candidate table may be consulted as **LEADS only**. Labels travel: anything derived by
  consulting quarantined material carries the consultation in its provenance line; nothing
  disqualified can be claimed, PASSed, or silently laundered into a "derived" form. Near-C5
  landings disclose the coincidence + look-elsewhere cost (§0.3).
- **M3 — ADJ-before-code.** Any deviation from this spec (phase split, filename, numeric
  refinement, grammar-reading consultation) gets an ADJ-### entry in `RUN_LOG.md` BEFORE
  the code changes. Forbidden adjustments (run-1 list) carry over: no tolerance widening,
  no plugs, no RETRO-PASS, no IDENTITY-PASS.
- **M4 — §D on FAIL.** Every FAIL/OPEN/KILL row gets the seven questions
  (`HUNTER_PROTOCOL.md` §D / `PROMPT_EXECUTION_PROTOCOL.md` §8) with a recovery grade.
- **M5 — GATE-CONTRABAND.** No Schmidt-line, shell-model, impulse-approximation, or SU(6)
  machinery anywhere in the chain — the rival appears in the **OBSERVED comparison column
  only**. Symmetrically (§G.2): no kill condition may enforce a rival's axiom; every gate
  above traces to a measured anchor.
- **M6 — No G, no M, no GM.** Anywhere.
- **M7 — Never "charge radius".** R_p is the proton **boundary/surface/displacement radius**.
  No charge substance; EM language is handed redirection.
- **M8 — μ_N flagged borrowed everywhere it appears.** The native content is the
  **dimensionless g-factor** (engine form `R m c v/(ℏ c)`-class); μ_N is the comparison
  yardstick only.
- **M9 — Results = teed stdout; exit honesty.** Tool `np15_mesh_circulation.cpp` →
  `np15_run2_results.txt` (teed/redirected stdout, committed as-is). Exit code reflects the
  honest verdict (0 only if all committed gates pass; nonzero otherwise — NP10 run-2
  precedent: "exit 1 — honest").
- **M10 — Build recipe (MSVC primary):**
  `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:np15_run2.exe np15_mesh_circulation.cpp`
- **M11 — Constitutional grammar inviolable.** n_t = A−2Z, n_d = 3Z−A−2 (Z ≥ 2, 1 alpha
  core); EC isotopes use the alternate grammar (He-3 core): n_t = A−2Z+1, n_d = 3Z−A−3.
  Free neutrons are forbidden in stable nuclei. No other decompositions.
- **M12 — Deliverables.** `RUN_LOG.md` gains a "Pre-Run Commitments — NP15 RUN 2" block
  (copied below, filled) before coding; `NP15_VERDICT.md` gains an appended RUN 2 verdict
  (dual verdict header, numbers table with null column, earned/owed, §D, §G faith ledger,
  canonical line). Nothing above the append line is edited.

### Pre-Run Commitment Block — RUN 2 (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP15 RUN 2 (mesh circulation)
- Prompt completion target: B
- Physics class hoped: NATIVE (composition rule); honest floor: OPEN / addition-wins
- CALIBRATED budget: 0
- Declared measured inputs: μ_p = +2.7928, μ_n = −1.9130 (μ_N, borrowed, flagged)
- Engine namespaces: measured (μ anchors), law_VI topology (block geometry), grammar
- The ONE rule text (written before any number): [formula/algorithm over
  1 alpha core + n_d deuterons + n_t tritons — REQUIRED HERE]
- Gates (blind, committed): B1 5% (and ≤ +2.61% vs addition) · B2 8% · B3 8% ·
  B4 exact · B5 15% · B6 15% · Phase C 15% (isotope: [DECLARE])
- Look-elsewhere ledger: every variant written, run or not
- Forbidden: widen gates; per-isotope freedom; promote C5; re-fish μ_n; RETRO-PASS;
  IDENTITY-PASS; rival machinery in-chain
```

---

*NP15 RUN 2 · spec'd 2026-07-06 · J. C. Harvey · composites only — the mesh either says how
much the alpha contributes, or it loses to the addition it replaced.*
