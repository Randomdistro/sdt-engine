# PM07 — Magnetohydrodynamics Coupling to the Fluid Suite

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can the **ideal-MHD equation set be *assembled* from FD01 (relay momentum)
   ⊕ PM01 (wake circulation)** — with frozen-in flux as wake advection, the induction equation
   `∂B/∂t = ∇×(v×B)` emerging with **no Ohm's-law postulate**, Alfvén waves as a transverse
   lattice+swirl mode, and magnetic pressure/tension as PPT06 traction — **rather than the MHD set being
   imported wholesale**? The open question is whether every MHD term is *named* in an FD/PM primitive
   (a true bijection), or whether one closure has to be put in by hand.
2. **Why does it matter?** — MHD is the workhorse of plasma astrophysics; if it assembles natively, then
   dynamos, the solar wind, accretion, and PM05 reconnection all inherit SDT's no-G/no-field ontology.
   PM07 also closes the loop: FD05's sound becomes magnetosonic, FD08's energy budget gains the magnetic
   stress, and PM05's reconnection is the *breaking* of the frozen-in flux derived here.
3. **How will we find out?** — Four gated phases (§④) with a **bijection gate** (every assembled term
   must map to a named FD/PM primitive); the native coupling (P1→P3) precedes any textbook-MHD
   comparison; standard MHD is the CONVERGENCE target, never an imported closure.
4. **What would prove us wrong?** — §⑧, each falsifier with its killing number (flux not conserved as
   η→0, `v_A` off the form or dispersive, magnetic stress not reducible to traction).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase.

## Question

The FD suite already derives fluid mechanics as continuum spation relay. A conducting fluid threaded
by a swirl field (PM01) is **that same lattice carrying circulation while it flows**. **Can ideal
magnetohydrodynamics be assembled as the FD fluid equations coupled to the wake-circulation field —
with Alfvén waves as transverse lattice+swirl modes, frozen-in flux as wake advection, and magnetic
pressure/tension as native traction — rather than the MHD equation set imported wholesale?** MHD is a
TARGET; no magneton, no primitive B, no resistive-Ohm postulate (resistivity = FD02 relay diffusion).

## SDT mechanism & hypotheses

A swirl field embedded in a flowing relay lattice is advected by it (the wakes ride the flow = frozen-in);
the swirl exerts a back-traction on the fluid (magnetic pressure ⊥ + tension ∥ the swirl streamlines).
Couple FD01's Navier–Stokes (relay momentum) to PM01's swirl and the ideal-MHD set assembles natively.

- **H1 (frozen-in = wake advection):** in the low-relay-diffusion limit (FD02 → 0) the swirl flux
  through any co-moving lattice loop is conserved — the wakes advect with the flow; recover the
  ideal induction equation `∂B/∂t = ∇×(v×B)` as PM01⊕FD01 with no Ohm's-law postulate.
- **H2 (Alfvén = transverse lattice+swirl mode):** the GOM06 transverse rigidity *plus* swirl tension
  gives a restoring force → a wave at `v_A = B/√(µ₀ρ)` (native: swirl tension over lattice inertia).
- **H3 (magnetic pressure/tension = traction):** the `B²/2µ₀` pressure and tension are PPT06 wake
  traction resolved ⊥ and ∥; recover the Maxwell stress tensor as relay traction, plug into FD08 budget.

**Anti-tautology firewall.** The *trivial* path is to write down the ideal-MHD set and "annotate" each
term with an SDT word — that is relabelling, not assembly. The *load-bearing* path is the **bijection
gate**: every term in the assembled momentum + induction equations must be *produced* by FD01 relay
momentum or PM01 wake circulation, with **no term left over and no closure inserted by hand**. The
induction equation must emerge *without* an Ohm's-law postulate (resistivity ≡ FD02 relay diffusion);
`v_A = B/√(µ₀ρ)` must come from swirl tension over lattice inertia, not be quoted. **Importing the MHD
set, or a primitive `B` as a closure, caps the grade at C.** **Native-before-borrowed / forbidden:** no
primitive `B`, no resistive-Ohm postulate, no µ_B/µ_N/magneton (energies/pressures in native traction
units, SI map once at the end), no G/M-fundamental, no QM wavefunction. `∇·B=0` (E58) holds throughout.

## Strategy

**Phase 1 — Couple the sets.** Add PM01 swirl back-traction to FD01 Navier–Stokes. *Goal:* ideal-MHD set.
*Method:* assemble momentum + induction. *Success:* the ideal-MHD equations reproduced term-for-term;
each term named in FD/PM primitives (bijection gate).

**Phase 2 — Frozen-in flux.** Drive FD02 relay diffusion → 0. *Goal:* flux conservation. *Method:*
co-moving loop integral. *Success:* swirl flux conserved to <0.5%; finite diffusivity gives slip ∝ η.

**Phase 3 — Alfvén waves.** Perturb a uniform-field fluid. *Goal:* `v_A`. *Method:* GOM06 + tension
dispersion. *Success:* `v_A = B/√(µ₀ρ)` form to <1%; non-dispersive; transverse; magnetosonic modes recovered.

**Phase 4 — Magnetic pressure/tension.** Resolve PM01 traction ⊥/∥. *Goal:* Maxwell stress. *Method:*
PPT06 traction projection. *Success:* `B²/2µ₀` pressure + tension recovered; pinch/sausage stability order-correct.

## Success criteria

- ✅ **PASS (A):** ideal-MHD set + frozen-in + `v_A` + magnetic stress all native, zero fitted params.
- ✅ **QUALIFIED (C):** set assembled; one flagged coupling coefficient in the stress projection. *(Expected.)*
- ⚠️ **PENDING (D):** induction + frozen-in shown but Alfvén speed only scaling-correct.
- ❌ **FAIL (F):** cannot couple without importing the MHD set or a primitive B as a closure.

## Falsification tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | Bijection of the MHD set | every assembled momentum+induction term maps 1:1 to an FD01/PM01 primitive; **zero leftover terms, zero hand-inserted closures** | any term unmapped or any closure imported → MHD is relabelled, not assembled → C, not A |
| T2 | Frozen-in flux | co-moving swirl flux conserved to <0.5% as FD02 η→0; finite η gives slip `∝ η` | flux drifts >0.5% at η→0, or slip not `∝ η` → swirl is not wake-advected → induction not native |
| T3 | Alfvén wave | `v_A = B/√(µ₀ρ)` to <1%, transverse, **non-dispersive** (ω/k flat in k); magnetosonic modes recovered | `v_A` off >1%, or the mode is dispersive/longitudinal → swirl tension + GOM06 do not make the wave |
| T4 | Magnetic stress | `B²/2µ₀` pressure ⊥ and tension ∥ recovered from PPT06 traction projection; pinch stability order-correct | stress not reducible to traction (a residual term remains) → Maxwell stress is not relay traction |

## Questions This Opens *(generative — log in `PM07_VERDICT.md`)*

1. **Is the dynamo a wake-topology instability rather than a kinematic effect?** If frozen-in flux is
   wake advection, field amplification should be a traction instability of the flow — does SDT predict a
   dynamo threshold from PPT06 traction without the usual magnetic Reynolds-number postulate?
2. **Does the magnetosonic spectrum unify FD05 sound with Alfvén?** If the fast/slow/Alfvén modes are
   all transverse/compressive lattice+swirl branches, the FD05 `c/√3` ceiling and `v_A` should be two
   limits of one dispersion surface — is there a single relay dispersion `ω(k,θ)` that contains both?
3. **What is the SDT meaning of the plasma `β` (gas vs magnetic pressure)?** Both are traction in this
   picture — is `β` the ratio of isotropic relay pressure to directed swirl traction, and does it set
   where matter occlusion vs circulation dominates?
4. **Is there a native upper limit to frozen-in (the breakdown PM05 needs)?** PM07 derives frozen-in in
   the η→0 limit; PM05 breaks it via topology snap. Is the breakdown threshold a single FD02-diffusion
   criterion shared between the two prompts?

## Dependencies

**Upstream:** FD01 (Navier–Stokes / relay momentum), [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl
back-traction), [[PM03_EM_Waves_as_Coupled_Relay_Pulses]] (wave coupling), GOM06 (transverse rigidity), FD02 (relay diffusion ≡ resistivity).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]] (breaks frozen-in flux), dynamo / magnetosphere modelling.
**Related:** FD05 (sound → magnetosonic), FD08 (energy budget + magnetic pressure), PPT06 (traction), [[feedback_no_borrowed_units]].
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces actually used: law_III, law_V, bridge; FD01 momentum, PM01 swirl, FD02 diffusion, GOM06 rigidity, PPT06 traction
- Phase thresholds (committed before run): P1 bijection (0 leftover terms) · P2 flux <0.5% at η→0, slip∝η · P3 v_A <1%, non-dispersive · P4 B²/2µ₀ stress from traction
- Forbidden retroactive changes: import the MHD set / a primitive B as closure then claim A; postulate Ohm's law; quote stresses in µ_B/µ_N; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM07)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 a term won't map to FD01/PM01 | seek the missing primitive (PPT06 traction, FD02 η) | **OPEN** the bijection; report the orphan term | annotate the term and claim assembled |
| P1 a closure must be inserted by hand | derive it from relay momentum/circulation | down-grade to **C** (set imported) | postulate Ohm's law / primitive B |
| P2 flux drifts > 0.5% at η→0 | refine the co-moving loop integral | **KILL** H1; swirl not wake-advected | average the drift away |
| P3 `v_A` dispersive or off > 1% | check swirl-tension / lattice-inertia ratio | **OPEN** the Alfvén mode | quote `v_A = B/√(µ₀ρ)` without deriving |
| P4 stress leaves a residual term | re-project PPT06 traction ⊥/∥ | **OPEN** the Maxwell-stress link | drop the residual silently |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
