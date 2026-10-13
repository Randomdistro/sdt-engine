# NP09 — The deuteron's mass defect, native (specification rewritten 2026-10-10)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction (2026-10-10): dependencies first, prompts carry new data, packing sequencer understood before grammar work. The 2026-06-27 specification is kept unchanged below the line; it is superseded.

## 1. Question (as it now stands)
What movement does one proton–proton mesh contact free when a stabled electron is shared? Can the defect of the deuteron against its native list, **B(d; {2p, 1e}) = 1.442246 MeV** (AME2020; NP17 reset V4), be derived from that contact without a fitted coefficient?

## 2. What is established (with source)
| # | Fact | Source |
|---|---|---|
| E1 | Binding is mass defect. Energy is movement. Law III is a push. Integrated-force (potential) bookkeeping is withdrawn. | Harvey ruling 2026-10-07 |
| E2 | Ledgers are list-dependent. {p, n} gives 2.224571 MeV; {2p, 1e} gives 1.442246 MeV. The {p, n} list carries the owed neutron term (+0.782 MeV, no derivation stands). | NP14 native; NP17 reset |
| E3 | The neutron is p + one stabled electron; it has the same boundary R_p. The old "which neutron radius" question (Step 1 below) dissolves. | NP30 §3; NP14 |
| E4 | αħc/r ≡ m_e v(r)²: the seat movement on the Ѻ_H = r_e ladder. The native scale at the 1.83c boundary seat is αħc/R_p = 1.711391 MeV. | NP17 PROMPT E2 |
| E5 | The live sequencer (NSEQ18-WEB-1) builds the deuteron as one open "internal" contact (graph V = 2, E = 1). Its deuteron is **CALIBRATED(8)**: 8 parameters fitted to B, μ and Q. **There is no derived deuteron in the construction.** | engine run 2026-10-10 |

## 3. Errors already made on this question, and what each teaches
| # | Error | Lesson |
|---|---|---|
| X1 | The far-field occlusion integral (this prompt's 2026-06-27 route) gives 0.06–0.08 MeV per contact, about 30× short. The route is also withdrawn bookkeeping (E1). | The MeV scale is the seat movement (E4), not the occlusion residual. |
| X2 | Old NP17 claimed "3αħc/D = 2.200 MeV, −1.06%". It compared a {p, p, e} configuration with the {p, n} binding. On its own list it is +52.6%. Withdrawn. | Name the list before any comparison. |
| X3 | The shared-electron seat ledger (half-movement per electron–proton seat) gives the deuteron at +1.71%, post-seen. It is **excluded for A ≥ 3** by a geometry-free ceiling (³H 1.35×, ³He 2.70×, ⁴He 3.90× over). It fails H₂⁺ across scale (+67%). | The deuteron agreement is isolated (G3), not a mechanism. Binding does not track electron count (³H ≈ ³He to 0.019 MeV). The carrier is the proton–proton contact. |
| X4 | NP06: no α-free rim-rate Δω. "Why D/3" was one of eight lengths. | No length is selected by agreement. |
| X5 | The live engine's zero-fit universal ledger (wake contact coupling × αħc/R_p) under-binds ⁴He–¹⁶O at about 0.42×. | The scale is right in order; the contact weight is not derived. |

## 4. Dependency
**Required supplier: NP17 round 2, the O1 contact-mesh ledger** (`NP17_.../PROMPT.md` §7). O1 must state natively what one mesh contact frees: the counter-rotating meeting of two boundaries at 1.83c (NP30 §5), in movement units. It must also state how loop closure adds to it (NP10, NP33). That statement must be written before any measured binding is loaded.

**Blindness limit.** The deuteron, triton, helion and alpha values are already seen. O1 must therefore be tested blind on heavier nuclei, using the sequencer's own contact graphs. For A ≥ 4 these are trees plus one 4-ring (the α core), with E = A. NP09's deuteron is then a **consistency check, not a test**.

**Status:** DEFERRED until NP17 round 2 registers O1. What opens it: a native statement of the per-contact freed movement. That is derived from the FLM07 glancing transfer or FLM10 lattice solver, or given by Harvey as construction.

## 5. Pre-registered checks (for when O1 exists)
- C1: O1's deuteron (one open contact) against 1.442246 MeV, ±3%. Post-seen class, so G3 at most.
- C2: the same O1 rule, with no new parameter, on the ³H and ³He open chains (E = 2). B(t) and B(h) must agree with each other to the measured 0.019 MeV pattern (equal within 2%). This is structural; the values are seen.
- C3: the blind test belongs to NP17 round 2 (A ≥ 6 from the sequencer graphs). NP09 inherits its grade.

## 6. Prohibitions
- No pair potentials; no {p, n} list without the owed neutron term named.
- No length or coefficient chosen by agreement; no census.
- No QM narration; the word "charge" is not used.
- No edits to Engine or Laws.

---

## Superseded specification (2026-06-27, kept as written)

# NP09: Deuteron Binding from Occlusion Geometry — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP09] NP09: Deuteron Binding from Occlusion Geometry — Investigation Prompt: **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** Can the occlusion force F = (pi/4) P_eff R1^2 R2^2 / r^2 reproduce the measured deuteron binding energy 2.22457 MeV at the measured separation of about 2.14 fm without a fitted coefficient?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

---

## 1. The Question

The deuteron (p+n) is the simplest nuclear system. SDT's occlusion force is:

$$F = \frac{\pi}{4} P_{\text{eff}} \frac{R_1^2 R_2^2}{r^2}$$

Can this reproduce the measured binding energy of 2.22457 MeV when applied to a proton and neutron at their measured separation of ~2.14 fm?

## 2. Methodology

### Step 1: Identify the correct radii

The proton has R_wake = R_p = 0.8414 fm (the charge radius, confirmed by W+1 conjecture). The neutron has no charge radius — it is overall neutral. What radius does the neutron present for occlusion purposes?

Three candidates:
- **R_n = R_p** (same W=3 topology → same wake radius): 0.8414 fm
- **R_n = 4ℏ/(m_n c)** (W+1 applied to neutron mass): 0.8401 fm (0.15% less than proton)
- **R_n = 0** (no ℓ=1 wake → no occlusion): This would give zero binding → WRONG

The neutron MUST have a non-zero wake radius for occlusion. SDT's position: the neutron has the same W=3 trefoil topology as the proton. Its ℓ≥3 wake IS the nuclear interaction. The ℓ=1 wake (charge) is absent, but the ℓ≥3 wake (structure) provides the occlusion cross-section.

Hypothesis: use R_n_eff ≈ R_p for the nuclear occlusion radius (same topology → same effective size for ℓ≥3 wake).

### Step 2: Compute the binding energy

$$E_B = \int_{r_0}^{\infty} F(r) \, dr = \frac{\pi}{4} P_{\text{eff}} R_p^2 R_n^2 \int_{r_0}^{\infty} \frac{dr}{r^2}$$

$$E_B = \frac{\pi}{4} P_{\text{eff}} \frac{R_p^2 R_n^2}{r_0}$$

With R_p = R_n = 0.8414×10⁻¹⁵ m and r_0 = 2.14×10⁻¹⁵ m:

Compute this numerically and compare to 2.224 MeV.

### Step 3: If the simple occlusion gives the wrong answer

Possible corrections:
1. The neutron's effective radius for ℓ≥3 occlusion differs from R_p
2. The occlusion force includes higher-order terms (not just 1/r²)
3. The deuteron's loosely-bound state means quantum zero-point motion affects the average separation
4. P_eff as calibrated from hydrogen (atomic scale) may need a nuclear-scale correction

### Step 4: Reverse engineering

If the formula doesn't give 2.224 MeV, invert:

$$R_{n,\text{eff}} = \sqrt{\frac{4 r_0 E_B}{\pi P_{\text{eff}} R_p^2}}$$

What R_n_eff is required? Is it physically reasonable?

## 3. Success Criteria

- [ ] Binding energy computed from SDT occlusion formula
- [ ] If match (within 10%): report as confirmed
- [ ] If no match: identify and quantify the discrepancy
- [ ] Determine whether the discrepancy reveals the ℓ≥3 nuclear wake contribution
- [ ] Compare the SDT approach to standard Yukawa potential (conceptual mapping)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP09
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 0.15%, 10%
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

*NP09 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (gating)

**Finding:** The sign-off reads "FAIL on occlusion magnitude; PASS on documentation (quoted, modifier omitted)", so a documentation criterion that cannot fail is scored as a PASS beside a real failure.

**Correction:** Remove documentation items from PASS/FAIL scoring and report only the magnitude gate.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
