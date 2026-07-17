# FLM10 — The Per-Spation Lattice Solver (ROOT-SIM)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — the five questions, answered up front

1. **What don't we know?** The per-spation contact mechanics on the (FLM08) corner-sharing tetrahedral lattice
   has **never been computed**. Everything above L1 rests on continuum summaries of it.
2. **Why does it matter?** **Five** open investigations all reduce to this one solver — FLM09-A2 (isotropy /
   `ω(k)`), PPT07 (the `6π⁵` wake integral), FLM03/04 (the `v(r)` rotation decay), OP-2 (winding stability), and
   OP-1/OP-3 (`R/a` & `α` quantisation). Build once, pay five.
3. **How will we find out?** A standalone, per-spation rigid-contact simulation under convergence pressure with
   the `c`-relay, configurable to four validation problems of increasing difficulty.
4. **What would prove us wrong?** A network that stays *anisotropic* as it grows (kills Lorentz emergence); a
   `v(r)` that won't decay; a wake ratio that needs a target plugged in; a `W=2` knot that refuses to decay.
5. **How will we know we're done?** At least the **isotropy residual** is REPRODUCED (not plugged), with no
   coefficient fitted to a measured target, and the delete-test is clean.

---

## §K ADDENDUM (2026-07-13) — this prompt is the gold-standard reference; three current-§K additions

> **FLM10 is the exemplar** the `PERFECT_PROMPT_TEMPLATE` was validated against (excessive detail + gates,
> reproduce-not-plug, prohibitions, 5-debt dependency map). No rewrite. Three additions only:

**(1) FLM10 is the cascade ROOT (HUNTER §E) — build once, pay many.** Beyond the 5 debts named in §⓪.2, the
2026-07-02 cascade ledger ran **D1 (deuteron), NP20-mass, NP21, NP18 all to ground at the FLM10 influx/engagement
profile.** So FLM10 is the single upstream that unblocks a large fraction of the un-verdicted stack (PPT03 V_disp,
EMC01 R_p geometry, FLM05 packing, the nuclear synchrony debts). **Priority-order Phase 1 (isotropy) — it is the
most-earned and the widest-paying.** A negative result is still a PASS (measure, don't confirm).

**(2) Harvey's framing (2026-07-13) — isotropy IS the perfect pressure regime, and that is why Bell is
inevitable.** *"All energy is movement under a perfect pressure regime so precise that Bell's-theorem violations
are an inevitability."* Phase 1's **isotropy residual → 0** is the *quantitative statement of that precision*: the
network relaxes to a single synchronised medium (one longitudinal + two transverse, Lorentz-linear). **The Zener
ratio → 1 is the mechanism behind QM05/QM01's Bell inevitability** — a medium this isotropic is not a collection of
separate locals, so its correlations are non-local by construction (the throughpole/synchronous channel). Log the
FLM10 isotropy ↔ Bell-inevitability link once in `INVESTIGATION_STACK.md`; it converts "why is Bell violated?" from
a debt into a *measured* consequence of the substrate.

**(3) The substrate is a reconfigurable superfluid, not a frozen glass** (2026-06-25 upgrade). FLM10's "rigid
tetrahedra + RUM hinges" is the rigid-contact *limit*; the bulk actually flows (bond-switch = flow; CRN =
transient structure). Phase 0's WWW bond-switching already models this — keep the superfluid reading of the CRN, do
not quench it into a static glass (this is also FLM05's flag C: reconcile rigid-limit ↔ superfluid).

**Four-root loop (§K.2):** on each failed validation problem, sort — root-1 claim false (network won't isotropise /
v(r) won't decay / wake ratio needs a plug) · root-2 dependency (FLM08 geometry, the whitelist radii) · root-3
prompt (Hessian/discretisation mis-scoped) · root-4 contraband (a wavefunction/probability smuggled as a
"mechanical" phrase, per the §③ prohibition). **KILL-DEEPEN (§K):** because five debts hang on FLM10, a premature
KILL here cascades — no KILLED verdict on a first-pass gate; re-run unanchored, old agent results deleted first.

---

## ① Executive Summary

The bottom of the SDT stack — the **dynamics of the spation lattice itself** — has never been simulated; every
result above L1 is a continuum approximation of it. **FLM10 builds the lattice solver:** a per-spation
rigid-contact mechanics engine on the FLM08 corner-sharing tetrahedral random network, under isotropic
convergence pressure, relaying disturbances at one spation per tick (`c`). It is **configurable**, not
single-purpose: the same engine attacks five debts. **We expect**, in order of how *earned* each is: (1) the
**isotropy residual** — anisotropy should decay toward zero as the network grows, *forcing* one longitudinal +
two transverse modes (gravity's `c_L`, light's two `c_T`); (2) the **wake phase-space integral** — the
proton/electron displacement-zone ratio, run **blind** against `6π⁵`; (3) the **rotation field** `v(r)`,
reproducing `αc` at `a₀` without plugging it; (4) **winding stability**, `W=2` decaying while `W∈{1,3}` persist.
A negative result is still a PASS — the point is to *measure*, not to confirm.

---

## ② Physical Context

**The medium.** Per FLM08, the vacuum is a **corner-sharing tetrahedral random network** (Zachariasen CRN
topology): rigid spation tetrahedra joined at shared vertices (hinges), coordination **4**, void fraction
`≈ 1 − π√3/16 ≈ 0.66`, statistically **isotropic** and space-filling. *(This supersedes the older "close-packed
shells" picture in `FLM04/DEEPTHINK_PROMPT.md` — the bulk is the CRN; radial shell order is something that must
*emerge* near a massive defect, not be assumed.)* Spations are perfect rigid spheres of radius `a = ℓ_P/2`.

**The forces.** An isotropic **convergence pressure** `P_conv` packs the network. The only low-energy give is
**rigid-unit-mode (RUM)** hinge rotation — the tetrahedra stay rigid, the inter-tetrahedral angles flex. Matter
is **substantive, not a void**: a particle *raises* local pressure and **pins strain** (held strain = mass).

**The carriers.** A particle is a **hard, localised solid vortex** — never a cloud. Two windings matter: the
**electron**, `W=1` (an unknot loop); the **proton**, `W=3`, the `(2,3)` torus knot (trefoil), surface radius
`R_p = 8.414×10⁻¹⁶ m`, equatorial phase speed `v₀ = 1.831c`, internal circulation `v_T = c√(2/5) = 0.632c`,
`v_P = c√(3/5) = 0.775c` (`v_T² + v_P² = c²`).

**The key variables** (define all): node position `xᵢ`; the local **displacement/phase field** `φ(x)` (the
vortex winds `2πW` around the defect); per-node **spin axis & rate** `ωᵢ = vᵢ/a`; the **hinge angles** `θⱼ`;
the **contact set** (who touches whom, and at what latitude); the local closure `ℓ_P(r)`; the relay front.

**Why it matters.** This is the L0/L1 root. `v(r)`, the mass ratio, the dispersion relation, the particle
spectrum — all are *outputs* of this dynamics that are currently *assumed*. Closing it converts five
"continuum-summary" results into earned ones.

---

## ③ Theoretical Framework

**Permitted inputs (whitelist, the ONLY external scales):** `{ℓ_P, c, ℏ, α, m_e, m_p}` plus the two measured
radii `R_p, a₀`. **No `G`, no `M` (kg), no `GM`.** FLM08 geometry constants come from
`sdt::laws::lattice_structure` (`dihedral = arccos(1/3)`, `deficit = 2π−5·arccos(1/3) = 7.356°`,
`bc_twist = arccos(−2/3)`, `coordination = 4`, `void = 1 − π√3/16`).

**Governing physics (the equations the solver discretises):**
- **RUM elasticity.** Tetrahedra rigid; energy is in hinge rotation: `E = ½ Σⱼ κ (Δθⱼ)²` (the hinge stiffness
  `κ` sets the modulus; only *ratios* of speeds depend on it, so it cancels in dimensionless outputs).
- **Convergence pressure** `P_conv` (Law I) sets the packed reference state; a defect raises local pressure.
- **Contact / traction law.** Spations **roll without slipping** (perfect traction); axially-aligned neighbours
  **contra-rotate at contact with no slip ⇒ no drag** (they mesh like gears); surface speed falls off-equator
  as `ω·a·cosθ`.
- **Movement budget (Law V):** at every contact, `v_circ² + v² = c²` — the hard `c` ceiling.
- **The `c`-relay.** A disturbance is handed outward node-to-node, **one spation per tick** (`Δt = a/c`).
- **Topological defect.** Embed a closed loop carrying phase winding `W`; the field obeys `∇²φ = 0` away from
  the core, multivalued by `2πW` around it. The **wake** is the phase-locked displacement zone:
  `E_wake = ½∫|∇φ|² dV`, with the **angular integrations carried out explicitly** (this is where `π` factors
  live — the thing the cheap PPT07 test omitted).

**Hard prohibitions (do not use, even as scaffolding):** wavefunction / probability density / operator /
Hilbert space; "orbital" as a cloud; intrinsic quantum spin; magnetic moment / magneton; virtual particles /
loops / exchange bosons; Schrödinger / Dirac / QED machinery; "test particle", "observer", "measurement";
curved spacetime; **and any fitting of a coefficient to a known target value.** A mechanical-sounding phrase
that secretly stands in for one of these (e.g. "the electron *samples/penetrates* the core" = a probability
density in disguise) is equally forbidden. **Do not present a definitional restatement (a volume re-expressed
as a count of cells) as a derivation.**

**Constraints to REPRODUCE, never plug:** `v₀ = 1.831c` at `R_p` → `αc` at `a₀`; `ω → ck` linear at small `k`;
the wake ratio; the winding spectrum.

---

## ④ Investigation Strategy

Build the engine once (Phase 0), then run four validation problems ordered by how *earned* the target is — the
cheapest and most-forced first, so a failure is caught before the expensive work.

**Phase 0 — the core engine (the substrate). (~1–2 days)**
- *Goal:* a per-spation data structure on a real corner-sharing CRN, with pressure, contacts, and the `c`-relay.
- *Method:* generate the CRN by **Wooten–Winer–Weaire bond-switching** (or Keating-potential relaxation) from a
  periodic seed → randomise → relax to coordination-4 corner-sharing. Store nodes, tetrahedra, hinges,
  contacts, latitudes. Implement the relay tick (`Δt = a/c`).
- *Success:* the generated network reproduces the FLM08 invariants — coordination `4.00`, void `0.66±0.02`,
  ring statistics consistent with a CRN, and (the seed of Phase 1) **statistical isotropy**.

**Phase 1 — the isotropy residual / dispersion `ω(k)`. (THE earned root; do first.) (~2–3 days)**
- *Goal:* show the amorphous network is **Lorentz-linear** — `ω = ck`, isotropic, with one longitudinal + two
  transverse branches — and that anisotropy *decays* as the network grows.
- *Method:* assemble the **dynamical (RUM Hessian) matrix** of the hinge energy; diagonalise (sparse Lanczos).
  Extract `ω(k)` along many directions; compute the **Zener anisotropy ratio** vs system size `N`.
- *Success:* Zener ratio → `1` (isotropic) as `N→∞` (report the decay exponent); `ω → ck` linear at small `k`
  with no dispersive residual to the precision the run allows; exactly **1 longitudinal + 2 transverse** acoustic
  modes (= gravity's `c_L`, light's two `c_T` polarisations). *This is the one non-inherited win; spend here.*

**Phase 2 — the wake phase-space integral (`6π⁵`). (~3–5 days)**
- *Goal:* compute the proton/electron **wake ratio** blind and compare to `6π⁵ = 1836.118` (and to the
  decomposition `3·A(S³)·A(S⁵)`).
- *Method:* embed a `W=1` unknot and a `W=3` `(2,3)`-trefoil as winding defects; relax `φ` to equilibrium with
  the multivalued boundary condition; compute `E_wake = ½∫|∇φ|² dV` **with the angular integration explicit**.
  Take the ratio. **The measured `1836.15` must never enter the computation** — reveal it only at comparison.
- *Success:* the ratio **emerges** (whatever it is). If it lands on `6π⁵` (or `3·A(S³)·A(S⁵)`) → `6π⁵` earned;
  if it lands O(10) (like the bare invariants) → the `6π⁵` mechanism is elsewhere; if a *different* clean number
  → *that* becomes the prediction. All three are valid scientific outcomes.

**Phase 3 — the rotation field `v(r)`. (~2–4 days)**
- *Goal:* reproduce `v(r) = v₀√(R_p/r)` → `αc` at `a₀` **without plugging it**, and find where the `a/r` decay
  comes from mechanically.
- *Method:* drive the proton surface at `v₀ = 1.831c`; propagate rotation outward via the traction /
  contra-rotation / latitude-`cosθ` / interstitial-disallowance rules; record `v(r)`. Determine which
  ingredient (finite sphere size, off-equator `cosθ`, packing geometry, pressure, `c`-anisotropy) supplies the
  decay and with what coefficient.
- *Success:* `αc` emerges at `a₀` to ≤10%; the per-shell decay coefficient is **derived**, not assumed.

**Phase 4 — winding stability + `R/a` quantisation (OP-1/2/3). (hardest; ~1–2 weeks)**
- *Goal:* the stable-particle catalogue from topology alone.
- *Method:* reconnection dynamics — perturb `W=1, 2, 3` defects, evolve, observe decay/persistence; scan `(R/a)`
  for stable sets; test `α = v_P/v_T` at `W=1`.
- *Success:* `W=2` (a torus *link*) spontaneously decays to `W=1 + energy`; `W∈{1,3}` persist; the stable `(R/a,
  α)` sets predict the lepton ladder. *(If this phase stalls, Phases 1–3 already justify the build.)*

*Checkpoints:* gate after each phase; if Phase 1's isotropy fails, **stop and report** (it falsifies the FLM08
substrate, a bigger result than any later phase).

---

## ⑤ Success Criteria (canonical labels)

✅ **PASS (Class A — Derived).** The engine reproduces — with **no coefficient fitted to a measured target** and
a clean delete-test — at minimum the **Phase 1 isotropy residual** (Zener → 1, `ω → ck`, 1+2 modes), *and at
least one* of {Phase 2 wake ratio computed blind, Phase 3 `αc` at `a₀`}. Publishable as "the SDT substrate
dynamics, computed."

✅ **QUALIFIED (Class C — Convergence).** Reproduces the above with 1–2 **documented** approximations (e.g. a
linearised hinge potential, a finite-`N` extrapolation) — match within ~50%, every approximation flagged.

⚠️ **PENDING (Class D — Computed).** The engine runs and emits `ω(k)` / wake / `v(r)`, but matches only to an
order of magnitude, or a physical interpretation is incomplete. Still useful; states exactly what's missing.

❌ **FAIL (Class F).** The engine cannot reproduce even the isotropy residual, **or** any headline number
required plugging its target. *Note:* a **negative scientific result** (e.g. wake ratio ≠ `6π⁵`) is **not** a
FAIL — it is a PASS for the solver (it answered the question honestly), even though it kills a conjecture.

---

## ⑥ Outputs (exact files)

1. **`flm10_lattice_solver.cpp`** — the core C++20 engine (`#include <sdt/laws.hpp>`,
   `<sdt/lattice_structure.hpp>`); CRN generation, RUM matrix, defect embedding, the relay update.
2. **`flm10_solver.py`** — analysis/plots driver (dispersion, Zener-vs-N, wake field, `v(r)` log-log).
3. **`FLM10_DERIVATION.md`** — the per-contact equations and discretisation, *derived* vs *assumed* flagged
   line-by-line.
4. **Per-phase results:** `dispersion_omega_k.csv` + `zener_vs_N.png`; `wake_ratio.txt` (blind);
   `v_of_r.csv` + `v_of_r.png`; `winding_stability.txt`.
5. **`FLM10_VERDICT.md`** — per-phase classification (PASS / QUALIFIED / PENDING / FAIL) with the honest reading
   (including any conjecture the run killed).

---

## ⑦ Dependencies & References

**Upstream (required):** **FLM08** (the corner-sharing CRN substrate + exact geometry, `lattice_structure.hpp`);
**PPT01** (trefoil/unknot velocities, `R/a`); **Laws I/III/IV/V** (pressure, occlusion, mass-as-displacement,
movement budget); the whitelist (`sdt::laws::measured`).

**Downstream (blocked until this exists):** **FLM09-A2** (isotropy/`ω(k)` = the CONDENSA Lorentz-emergence
debt); **PPT07** (the `6π⁵` wake mechanism); **FLM03/FLM04** (the `v(r)` decay coefficient); **OP-1/OP-2/OP-3**
(the particle spectrum, `α` from topology); **GD05** (the galactic crossover inherits the same contact law).

**Related (read in parallel):** `FLM04/DEEPTHINK_PROMPT.md` (the narrow `v(r)` scoping — Phase 3 here);
`CONDENSA_Spation_Lattice_Unification.md` (the synthesis the solver pays down); `PPT07/ROOTSIM_VERDICT.md` (why
the bare-invariant test was the wrong quantity — Phase 2 is the right one).

---

## ⑧ Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| **T1** | the amorphous CRN is statistically isotropic | Zener ratio → 1 as `N→∞` (a measurable decay) | stays anisotropic ⇒ **FLM08/CONDENSA substrate is wrong** (the biggest result) |
| **T2** | the lattice is Lorentz-linear | `ω → ck`, no dispersive/anisotropic residual to run precision | a residual above limits ⇒ predicts Lorentz violation |
| **T3** | mass = wake; `m_p/m_e` = wake ratio | ratio emerges blind; is it `6π⁵` / `3·A(S³)·A(S⁵)` / O(10) / other? | requiring the target plugged ⇒ the wake picture is empty |
| **T4** | `v(r)` decays from contact geometry | `αc` emerges at `a₀` without plugging | `|v|=const` (no decay) ⇒ the `a/r` mechanism is missing |
| **T5** | topology selects the spectrum | `W=2` decays; `W∈{1,3}` persist | `W=2` stable ⇒ topology does not fix the particle catalogue |

Recovery: if a phase fails, **report the failure with the numbers** and isolate which assumption broke — do not
tune a coefficient to rescue it. A failed phase that is *honestly reported* still advances the stack.

---

## ⑨ Implementation Notes

- **Precision & scaling.** Double precision throughout; work in **dimensionless ratios** (`v/c`, `r/a`,
  `E/E_ref`) — absolute scales span ~60 orders of magnitude and will overflow. The hinge stiffness `κ` cancels
  in every dimensionless output; never let an absolute `κ` enter a reported number.
- **CRN generation** is the make-or-break step. Use **WWW bond-switching** (accept/reject on the Keating /
  hinge energy) to anneal a periodic seed into a coordination-4 corner-sharing network; verify the FLM08
  invariants *before* any physics. Keep one fixed seed for reproducibility (pass it in; do not call a wall-clock
  RNG that breaks re-runs).
- **The RUM dynamical matrix** is sparse and symmetric — assemble as the Hessian of `½Σκ(Δθ)²`; diagonalise
  with Lanczos/ARPACK; the three lowest acoustic branches are the physics. Watch for spurious zero modes
  (rigid-body translations/rotations — project them out).
- **The wake field** (Phase 2): relax `φ` with a multivalued winding boundary condition (carry the branch cut
  explicitly; **unwrap** gradients). Embed the `(2,3)` trefoil as a closed `(2,3)`-torus-knot path. **Do the
  angular integration in full** — that is the whole point; a radial-only integral repeats the PPT07 mistake.
- **Visualisation:** (1) `ω(k)` along ≥10 directions overlaid (isotropy by eye); (2) Zener-vs-`N` log-log (the
  decay exponent); (3) the wake `|∇φ|²` field for `W=1` vs `W=3`; (4) `v(r)` log-log with the `√(R_p/r)`
  reference.
- **Tooling:** C++ for the engine (link the engine headers), Python+NumPy/SciPy for eigensolves and plots; build
  via the MSVC `vcvars64.bat` recipe used across the repo. **Run blind** on Phase 2 — keep `1836.15` out of the
  source until the comparison line.
- **Cardinal sins to self-audit against, every commit:** (a) a coefficient fitted to a target; (b) a
  definitional restatement sold as a derivation; (c) an imported QM/GR concept wearing a mechanical costume; (d)
  a wall-clock RNG that makes a run unreproducible.

---

*Spatial Displacement Theory · FLM10 · the root the whole stack stands on. Build the engine once; pay five
debts. J. C. Harvey, Melbourne.*
### Dual verdict (required in `*_VERDICT.md`)

| Axis | Grades | Notes |
|------|--------|-------|
| **Prompt completion** | A / B / C / D / F | Phase gates in §④ executed? |
| **Physics class** | NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN | Mechanism earned vs identity check |


---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FLM10
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: FLM08 `lattice_structure.hpp`, FLM02/FLM05 relay mechanics
- Phase thresholds (committed before run): 10%, 50%
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

*FLM10 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
