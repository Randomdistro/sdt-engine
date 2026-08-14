# PPT02: Ground-State Velocity, Bohr Radius, and the Fine-Structure Constant from Topology

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces. **Propose-only** on any `Engine/`/`Laws/` flag.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩). Sort every failure into the four roots (§⑨.E) before the next phase runs.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Why the hydrogen ground-state tour gears down to exactly α = 1/137.036 of the relay speed c.** The closure `v = αc` is exact *given* α; the open gap is the *value* of α — i.e. the size of the W=1 electron's lattice wake `r_e` relative to its coherence scale `ƛ_Ce`, currently an input, not a derivation (`laws.hpp:1403` poses this verbatim).
2. **Why does it matter?** — α is one of only 8 derivation basis inputs `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}`. Deriving it drops the minimal input set from 4 (`{ℓ_P, T_CMB, α, d=3}`) to 3 and removes the last dimensionless free number in the atomic sector. Downstream: PPT03 (m_p/m_e), EMC01 (transfer function), every `atomic::` coupling scales through α.
3. **How will we find out?** — Three declared, competing native routes (§④ A/B/C), gated, native mechanism before any `atomic::`/rival comparison. α is treated throughout as a **velocity gear ratio** `v_ground/c`, not a "coupling strength" (§③.movement).
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers; any route that only *back-solves* α from a length already scaled by α is CIRCULAR and dies (§④.circularity gate).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). A route "derives α" only if it predicts 1/137.036 to its committed s.f. from a quantity that is *not* itself α-scaled (delete-test).

---

## 1. Mathematical Framework & Definitions

In SDT, space is a reconfigurable lightspeed superfluid (spation lattice) under convergent pressure. Subatomic defects (vortices) occlude throughput, generating forces and stable orbits.

| Symbol | Name | SDT Definition / Value | Physical Meaning |
|--------|------|------------------------|------------------|
| $\alpha$ | Fine-structure constant | $7.2973525693\times10^{-3}$ | **The ground-state gear ratio** $v_\text{ground}/c$ (§2.3). Equivalently the boundary ratio $r_e/\bar\lambda_{C,e}$. |
| $\hbar$ | Reduced Planck constant | $1.054571817\times10^{-34}$ J·s | Quantum of circulation action in the lattice. |
| $c$ | Relay speed | $299\,792\,458$ m/s | Nearest-neighbour handoff speed $\ell_P/t_P$. |
| $m_e$ | Electron mass | $9.1093837015\times10^{-31}$ kg | Displacement/exclusion cost of the $W=1$ torus. |
| $r_e$ | *(historically "classical electron radius")* | $2.8179403262\times10^{-15}$ m | **See ⚠ ERROR-FLAG below.** In SDT this length is the **hydrogen koppa** $\ϟ_H=\alpha^2 a_0$ (`laws.hpp:675`), an *atomic-orbit* c-boundary — **not the electron's own size.** |
| $\bar\lambda_{C,e}$ | Reduced Compton wavelength | $\hbar/(m_e c)\approx3.86159\times10^{-13}$ m | The electron's coherence scale. |
| $a_0$ | Bohr radius | $\hbar/(m_e c\alpha)\approx5.29177\times10^{-11}$ m | Stable H ground-state orbital radius. |
| $\ϟ_H$ | Hydrogen Koppa | $\alpha^2 a_0\approx2.81794\times10^{-15}$ m | c-boundary of hydrogen: where local orbital speed $=c$. Identically equals $r_e$ (§2.4). |
| $R_{\text{excl},e}$ | **Electron exclusion radius (SDT)** | $2.878\times10^{-21}$ m (`laws.hpp:478`) | **The electron's actual SDT displacement radius** — ~6.7 orders below $r_e$. |

> ### ⚠ ERROR-FLAG (mislabel; propose-only against canon) — carry into the verdict
> The prior draft's §1 called $r_e=2.818$ fm *"the electron's wake radius: the boundary of its lattice
> pressure perturbation."* **That label is the misnomer Harvey flagged (2026-07-12).** The number
> $2.818$ fm is the **hydrogen koppa** $\ϟ_H=\alpha^2 a_0$ (`laws.hpp:675`) — a *proton-orbit-scale
> c-boundary*, the length historically mis-named "classical electron radius." The **electron's own**
> SDT size is $R_{\text{excl},e}\approx2.878\times10^{-21}$ m (`laws.hpp:478`), ~6.7 orders smaller.
> The **identity** $\ϟ_H=r_e$ (§2.4) is *real and canonical* — but it must be read as *"hydrogen's
> koppa equals the length historically misnamed the electron radius,"* **never** as *"the electron is
> 2.818 fm across."* `laws.hpp:144` still carries the legacy comment `Classical electron radius`; this
> is a **propose-only relabel flag for Harvey** (do not edit the engine). Any route below that treats
> $r_e$ as *the electron's own wake* is running on the mislabel and must be re-sorted (§⑨.E root-2).

---

## 2. The Subatomic Force-Quantization Closure  *(EARNED — preserve verbatim; conditional on α)*

First-principles H ground state from two geometric constraints, no field ontology, no charge primitive:

### 2.1 Occlusion Force Balance (Law III = centripetal)
$$\frac{k_e e^2}{r^2}=\frac{m_e v^2}{r}\ \implies\ \frac{k_e e^2}{r}=m_e v^2,\qquad k_e e^2=\alpha\hbar c.$$
Here $\alpha\hbar c$ is the coupling *product* — a movement magnitude, not a charge substance (§3).

### 2.2 Law VI Circulation Quantization ($n=1$, $W=1$ torus)
$$m_e v r=\hbar\ \implies\ \frac{1}{r}=\frac{m_e v}{\hbar}.$$

### 2.3 Ground-State Velocity and Radius
$$k_e e^2\left(\frac{m_e v}{\hbar}\right)=m_e v^2\ \implies\ \boxed{v=\frac{k_e e^2}{\hbar}=\alpha c}\ ,\qquad \boxed{a_0=\frac{\hbar}{m_e v}=\frac{\hbar}{m_e c\alpha}}.$$
**Movement reading (§③):** $\alpha=v/c$ *is the definition of the gear* — the ground-state tour runs at the fraction α of relay speed. "Deriving α" ≡ "deriving the ground-state gear."

### 2.4 The Koppa Identity
$$\ϟ_H=\frac{v^2 a_0}{c^2}=\alpha^2 a_0=\frac{\alpha\hbar}{m_e c}=r_e\ \implies\ \boxed{\ϟ_H=r_e}.$$
The H c-boundary is identically the length historically called $r_e$ — a clean atomic↔gravitational link GR/SM cannot make. **(Read per ERROR-FLAG: this is the hydrogen koppa, not the electron's size.)**

---

## 3. Ontological Status of "Charge" and α

* **No charge substance.** There is no quantum $e$ in the lattice; "charge" is a *count of handednesses* (Z), $e$ a unit-bridge. Never "charge radius" → boundary/displacement radius.
* **α as gear / boundary ratio.** $\alpha=v_\text{ground}/c=r_e/\bar\lambda_{C,e}$ — the fraction of the coherence scale occupied by the wake, equivalently the fraction of $c$ the ground tour runs at.
* **Movement-only rule for this run:** every "energy," "potential," "coupling strength" must be restated as a span/velocity before it enters a phase. If a term won't translate, it is carrying an inherited abstraction (HUNTER §0.1.3) — flag it, don't use it.

---

## 4. The Value of α — re-opened per HUNTER §G.3

> **PRIOR VERDICT (now RE-OPENED):** the earlier draft closed "α is a Tier-1 input; every back-solve is
> circular (11/11 proofs)." **HUNTER §G.3 (Harvey, 2026-07-04) forbids that foreclosure:** the
> circularity proofs are sound **only inside the premise-class they were run in — the *static* spation
> lattice.** *"Nothing ruled out of hand."* A "cannot be derived" must carry (a) its premise-class and
> (b) its re-open condition. Both are now named:
> - **Premise-class of the old kill:** static spation, W=1 wake radius fixed only by its own α-coupling.
> - **Re-open condition (LIVE):** the **FLM14 rotating-spation DOF** is a *new carrier* the circularity
>   proofs never examined (electron positions sequential; orbital = tour; Born = dwell-time). A rotation
>   rate is a movement quantity that could fix the wake gear **without** consuming α. Status: **OPEN.**

**The circularity gate (kept as a filter, not a foreclosure).** A route is CIRCULAR and dies if its
predicted α is computed from any length already scaled by α ($a_0$, $\ϟ_H$, $r_e$ via the closure).
The gate does not forbid deriving α — it forbids *laundering* it. Delete-test each route.

---

## Dependency Map (mandatory, §K.3) — every item the chain consumes

| Item | Where | Class it enters as | Live? |
|------|-------|--------------------|-------|
| `alpha` | `laws.hpp` `measured::` derivation basis | **INPUT** (the thing we are trying to remove) | ✔ |
| `r_e` = α·ƛ_Ce | `laws.hpp:144` | IDENTITY (α-scaled) — legacy label flagged | ⚠ relabel |
| `koppa_hydrogen` = α²a₀ = r_e | `laws.hpp:675` | DERIVED identity | ✔ |
| `R_excl_e` = 2.878e-21 | `laws.hpp:478` | the electron's *actual* radius (Route A target) | ✔ |
| `g_electron` = r_e·m_e·c/ħ ≡ α | `laws.hpp:1122-1126` | DEFINITIONAL IDENTITY (α = g(W=1)) | ✔ |
| open Q: "can α be derived from W=1 torus?" | `laws.hpp:1403` | the engine's own posed gap | ✔ |
| PPT01 velocity/equilibrium budget | Investigations/02 | UPSTREAM (v_T, R/a per winding) | verify on file |
| **FLM14 rotating-spation dwell** | Investigations/01 | **UPSTREAM (Route B carrier)** — un-verdicted, ACTIVE | ⚠ dependency |
| **FLM05 lattice reconnection → wake radius** | Investigations/01 | **UPSTREAM (Route C)** — un-enacted SPEC | ⚠ dependency |
| PPT17 m_p/m_e (6π⁵, resolved shared-input construction) | Investigations/02 | SIBLING (mass gear; cross-check, not input) | informative |
| law_VI winding, `bridge::k_*` | `laws.hpp` | mechanism namespaces | ✔ |

**Dependency risk:** Routes B and C both stand on **un-verdicted** upstream investigations (FLM14 ACTIVE, FLM05 SPEC). If they underdeliver, the honest verdict is **DEFER**, citing the blocker by ID — **never a fake PASS** (§⑩).

---

## ④ Investigation Strategy — THREE declared mechanism routes (§K.3: ≥3 before re-run)

Each route must (i) name its non-α-scaled seed, (ii) pass the circularity gate (§4), (iii) state a pre-committed numeric metric, (iv) formulate its seed in movement terms.

### Route A — Topological wake radius (the g_electron = α identity, `laws.hpp:1122`)
- **Seed (non-α):** the W=1 torus geometry itself — can the wake radius $r_e$ (equivalently $R_{\text{excl},e}$) fall out of the *unknotted-loop displacement* without importing α?
- **Phase A1:** compute the W=1 solid-torus displacement volume from $\ell_P$ and the winding geometry (Law VI); **metric:** yields a length ratio $r_e/\bar\lambda_{C,e}$ within committed % of α **with zero α input**.
- **Known obstacle (pre-registered):** the electron is an *unknotted* loop — no crossing constraints to fix its wake (prior §4 conclusion). Route A is expected to **PARTIAL/OPEN** unless the rotation DOF (Route B) supplies the missing constraint. Declaring this up front is the point.
- **Kill:** if the only way to land α is to insert a length already $=α·ƛ_{Ce}$ → CIRCULAR, **KILL Route A**, cascade to B.

### Route B — Rotation carrier (FLM14, the §G.3 re-open) ★ primary
- **Seed (non-α):** the spation **rotation rate** / sequential-dwell fraction (FLM14). α as a **gear** `v/c` invites a gear *mechanism*: what sets the ground tour's speed fraction?
- **Phase B1:** import FLM14's dwell-fraction result (verify on file first — it is un-verdicted); test whether the ground-state gear $v/c$ equals the dwell/tour ratio. **Metric:** predicted gear within committed s.f. of 1/137.036.
- **Phase B2 (movement-only):** restate the whole closure as spans — tour circumference, dwell time, relay speed — and check that α emerges as a *ratio of movements*, not a coupling.
- **Cross-gate:** the same rotation DOF must not break PPT03's mass gear or FLM14's own results (§⑧ neighbour test).

### Route C — Lattice reconnection (FLM05, un-enacted SPEC)
- **Seed (non-α):** FLM05's tick-by-tick Planck-shell reconnection deriving the defect wake boundary from reconnection dynamics (FLM05 §"reactive gap").
- **Phase C1:** if FLM05 delivers a wake radius from $\ell_P$ + reconnection lag alone, feed it here; **metric:** $r_e$ from FLM05 within committed % **with no α**.
- **Status:** **DEFER-likely** — FLM05 is itself un-enacted. Route C is the long lever; log the dependency, do not fake it.

**Route selection rule:** run A (cheap, likely-negative — establishes the obstacle), then B (primary, §G.3-live), C only if B stalls. Do not merge routes to manufacture a pass.

---

## ⑧ Falsification Tests (numeric triggers)

| Test | Hypothesis | Predicted | If FAIL → root (§⑨.E) |
|------|-----------|-----------|----------------------|
| T1 | Closure is exact given α | $v=αc$, $a_0$, $\ϟ_H=r_e$ reproduce CODATA to <1e-6 | root-1 (algebra error) — none expected |
| T2 | Any route derives α without α-scaled input | predicted α = 1/137.036 to committed s.f., delete-test passes | root sorted per route |
| T3 (Route B) | Ground gear = FLM14 dwell ratio | $v/c$ = dwell/tour within committed % | root-2 (FLM14 dependency) or root-1 |
| T4 | $R_{\text{excl},e}$ (not $r_e$) is the electron's size | any route treating $r_e$ as electron-size mis-scales by ~6.7 orders | root-2 (mislabel dependency) |
| T5 (neighbour) | α-mechanism preserves PPT03 & FLM14 | no standing result breaks | root-4 (gate contraband) if a rival axiom leaks |

---

## ⑨.E Error-refinement loop (§K.2 four-root sort — run on EVERY failure before the next phase)

Every FAIL / KILL / OPEN is sorted into exactly one root before any subsequent phase may run:
- **root-1 — the CLAIM is false:** the mechanism itself doesn't produce α. → KILL that route, name what died.
- **root-2 — a DEPENDENCY upstream is false/missing:** FLM14 dwell, FLM05 wake, or the $r_e$ mislabel. → ROOT-RELOCATED; fix or flag upstream, return this claim to OPEN.
- **root-3 — the PROMPT under-specified the mechanism:** phase mis-scoped, metric wrong. → deepen this prompt again (recurse §K.3), re-run.
- **root-4 — the GATE is contraband (§G):** a kill condition enforcing a rival's axiom (QM quantisation-as-primitive, charge-as-substance) rather than a measured anchor. → kill the gate, not the route.

Record the sort in `RUN_LOG.md` per failure; link shared roots once in `INVESTIGATION_STACK.md` (§E cascade).

---

## Brainstorm — overlooked / newly-discovered factors (§K.3, non-binding leads)

- **α is a velocity, not a strength.** `v=αc` means α is literally the ground gear. Harvey's current King-plot movement law ("every emission = path × velocity gear at c, 7 floors") suggests the H ground state is *floor 1* of that same gear ladder — α may be the first rung of a countable sequence, not a lone magic number. Cross-check against the 7-floor structure.
- **The rotation DOF is un-mined.** FLM14 says positions are sequential (tour). A tour has a *rate*. No route has yet asked whether the 1/137 gear is the tour's dwell fraction. This is the §G.3 opening and the primary lead.
- **Two radii, not one.** The whole field has been conflating $r_e$ (hydrogen koppa) with the electron's size ($R_{\text{excl},e}$). Any α-derivation that targets "the electron radius" must state *which* — Route A targets $R_{\text{excl},e}$; the closure's $r_e$ is the koppa.
- **6π⁵ sibling.** PPT17 resolves m_p/m_e ≈ 6π⁵ (19 ppm) as a
  shared-input tube-volume construction. It remains a cross-check, not an
  input swap or independent prediction.
- **Look-elsewhere discipline.** Before any "α = f(π, geometry)" candidate is called a result, run the look-elsewhere correction (memory: 6π⁵ is unique *because* it survived it; bare α-fits do not).
- **Contraband watch:** do not let "α must be an input because QM treats it as fundamental" sit in the kill table — that is GATE-CONTRABAND (§G.2). QM's status of α is not an SDT anchor.

---

## ⑤ Success Criteria (dual verdict)

- **Class A (NATIVE / DERIVED):** a route predicts α = 1/137.036 to committed s.f. from a non-α-scaled seed; delete-test passes; movement-only formulation holds. Minimal input set drops to `{ℓ_P, T_CMB, d=3}`.
- **Class C (CONVERGENCE):** α reproduced with ≤1 documented approximation from a native quantity; label the approximation CALIBRATED.
- **Class D / OPEN:** closure re-verified (Class A on the *identities* v=αc, ϟ_H=r_e), α still input — but with the §G.3 routes mapped and one advanced to PARTIAL. **This is the honest floor and a legitimate ship.**
- **KILLED:** a route proven CIRCULAR at the gate — logged, cascaded, not rescued.

Preserving the earned closure (§2) is Class A on the *identities* regardless of the α outcome — report the two axes separately (`PROMPT_EXECUTION_PROTOCOL.md §4`).

---

## ⑥ Outputs

`RUN_LOG.md` (pre-commit + ADJ + four-root sorts) · `ppt02_alpha_routes.cpp` (A/B/C, `#include <sdt/laws.hpp>` only) · `PPT02_DERIVATION.md` (movement-only steps, DERIVED vs ASSUMED tagged) · `PPT02_VERDICT.md` (dual verdict + falsification table + the relabel flag for Harvey).

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN / DEFER** — never RETRO-PASS or PLUG.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT02 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 — α is the thing being removed, not a fittable knob]
- Routes to run this session: [A | B | C], in order
- Non-α seed for each route (name it): [A: W=1 displacement · B: FLM14 dwell · C: FLM05 wake]
- Engine namespaces: law_VI winding, bridge::k_*, measured::alpha (INPUT flag), PPT01 equilibrium
- Upstream verify-on-file before use: FLM14 dwell result, FLM05 wake result, PPT01 v_T
- Phase thresholds (committed before run): [per phase, s.f. for α match]
- Forbidden: widen tolerances post-run; α-scaled length as a "derivation" of α; treat r_e as electron size; import QM quantisation as a primitive
```

### Pivot table (real triggers)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Route A lands α only via an α-scaled length | declare CIRCULAR, cascade to Route B | **KILL Route A** (root-1) | call it a derivation |
| FLM14 dwell result not on file / un-verdicted | verify on file; if absent, **DEFER Route B**, cite FLM14 ID | ship OPEN with routes mapped | fabricate the dwell number |
| FLM05 wake radius unavailable | **DEFER Route C**, cite FLM05 SPEC status | — | fake PASS on borrowed value |
| Predicted α off > committed s.f. | four-root sort (§⑨.E) before next phase | OPEN, name the root | RETRO-PASS the tolerance |
| A route needs QM quantisation as primitive | check §G contraband | **kill the gate** if rival-axiom (root-4) | import ψ / field-primitive |
| Neighbour test (T5) breaks PPT03/FLM14 | re-scope the mechanism | **OPEN**, flag the cross-break | claim α while breaking a sibling |

### Allowed adjustments
Finer numerics; phase splits (Na/Nb); alternative **native** route already listed in §④; filename fix via ADJ.

### Disallowed adjustments
Post-hoc tolerance widening · coefficient plugs · α-scaled length passed off as an α derivation · `atomic::`/GM/G in a Phase-1 native chain · rival axiom as a kill gate.

---

*PPT02 · §K-deepened 2026-07-13 · execute with `PROMPT_EXECUTION_PROTOCOL.md` + `HUNTER_PROTOCOL.md` §K. Earned closure (§2) preserved; α-value re-opened per §G.3; three routes declared before re-run.*
