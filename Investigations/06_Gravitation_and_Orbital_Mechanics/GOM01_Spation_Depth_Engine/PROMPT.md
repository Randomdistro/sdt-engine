# GOM01: zk² = 1 Spation Depth Engine — one scalar field, four observables, and the honest ledger of what that proves

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes the
> 2026-06-27 bulk-template version; the prior spec embedded pre-checked PASS boxes, which violated the
> fishbowl — all outcome text stripped; every gate below is unchecked and pre-registered).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G.
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Execution: DIRECT ONLY — no agents** (agent-run verdicts are the voided class; the prior
> agent-era VERDICT/RUN_LOG/results layer was deleted 2026-07-24, git-recoverable).
> **Run:** copy §⑩ commitments to `RUN_LOG.md` before any code; ADJ-log every deviation.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Three separable things, and the prior spec conflated them:
   (a) whether the four weak-field observables (Pound–Rebka, Shapiro, bending, plus the coherence
   checks) all fall out of the ONE kernel z(r) = ϟ/r with **no per-observable freedom**;
   (b) whether the two hand-waved prefactors — the Shapiro "2" and the bending "2" — can be
   **derived from a single stated relay mechanism** rather than adopted because the measured
   answers need them; (c) whether the depth engine forces ANY observable that GR does not
   (the divergence residue) — because under ϟ ≡ GM/c², (a) alone is CONVERGENCE, never a kill.
2. **Why does it matter?** — z(r) = ϟ/r is the spine of the whole gravitational sector (GOM05
   variable closure, GOM06 waves, GOM08 precession, the Depth-Closure paper, GOM19's rung table
   all consume it). If the prefactors are owed, every downstream "PASS" carries that debt.
   If the divergence residue is empty, this sector can only ever tie GR, and the campaign must
   look elsewhere for kills (the firing-log targeting rule: clean kills live where the rival
   predicts exactly zero).
3. **How will we find out?** — §④: P1 re-earn the four observables against measured anchors
   (CONVERGENCE gates, labeled as such); P2 the prefactor derivation attempt (the actual native
   content); P3 the divergence hunt (rung structure below 3ϟ, path-dependence, anything GR lacks);
   P4 the cosmology quarantine (the strain-redshift claim is CONTESTED canon — see contract §5).
4. **What would prove us wrong?** — §⑧: any of the four observables needing a per-observable
   coefficient (kernel fails); the prefactors requiring different mechanisms for Shapiro vs
   bending (relay story fails); z·k²≠1 anywhere (algebra bug); P3 finding a forced divergence
   that measurement already excludes (engine KILLED in that regime, recorded).
5. **How will we know we're done?** — Dual verdict in a fresh `GOM01_VERDICT_DIRECT_*.md`:
   prompt completion A–F × physics class, **with the prefactor ledger and the divergence residue
   stated explicitly even if empty.**

---

## §0 Reader's contract (non-negotiable)

1. **The degeneracy rule (E107, firing log 2026-07-23).** Under the identification ϟ ≡ GM/c²,
   every weak-field agreement below is **shared algebra with GR** — consistency, not
   discrimination. No P1 result may be reported as a kill, a "beats GR," or a prediction. The
   honest ceiling for P1 is **CONVERGENCE (class C)**. Divergence lives only in P3, or nowhere.
2. **The two 2's are OWED until derived.** The prior spec said the Shapiro factor 2 "accounts for
   the round trip (or equivalently the relay overhead)" and the bending prefactor "arises
   naturally." Neither is a derivation. Until P2 lands, every P1 result is labeled
   **CONVERGENCE-with-owed-prefactor**, and the two 2's appear in the parameter ledger as
   `ASSUMED`. An "equivalently" joining two different physical stories is a tell, not a proof.
3. **No outcome text in this spec.** Gates are unchecked. If you know the measured answer, you
   pre-register the tolerance and then look — never the reverse.
4. **No G, no M.** ϟ = v²R/c² from kinematics (surface/orbital v and R); `bridge::GM_equivalent()`
   only in rival comparison columns, labeled.
5. **Cosmology is quarantined (P4).** The linear-strain reading z_cosmo = (H₀/c)·d that the old
   spec asserted as PASS is **CONTESTED**: CR07's earned octave law (1+z = 2^Δn, non-compounding)
   and the CR08/CR09 kills sit against it, and CR06 (emission/propagation split) is
   VOID-pending-readjudication in the register. P4 may CHARACTERISE the strain model against the
   octave law; it may not PASS it. Any cosmological claim from this investigation is `PENDING`
   until the CR06 re-adjudication lands.
6. **Direct execution only.** No delegated runs; stdout is teed to a dated results file; the
   verdict quotes only machine output produced today.

---

## §1 Definitions (honest labels attached)

| Symbol | Name | Value/form | Label |
|---|---|---|---|
| z(r) | spation depth | ϟ/r, dimensionless | DERIVED form (Law I/III reading); numerically ≡ GM/c²r (rival algebra — degeneracy rule) |
| ϟ | koppa / c-boundary | v²R/c² [m] | DERIVED from kinematics (no G/M) |
| k | velocity ratio | c/v | DERIVED |
| z·k² = 1 | closure | exact | **IDENTITY** (algebra: (v²/c²)(c²/v²) = 1) — a consistency check, never evidence |
| σ₀ | background strain | H₀/c [m⁻¹] | CONTESTED (P4 only) |
| ϟ_Earth | Earth koppa | 4.435×10⁻³ m | COMPUTED from v_orb(R⊕), R⊕ |
| ϟ_Sun | solar koppa | 1477 m | COMPUTED (laws.hpp:539) |

Measured anchors (comparison columns only): Pound–Rebka Δλ/λ = 2.46×10⁻¹⁵ over h = 22.6 m;
Shapiro (Cassini-class) delay form Δt = (2ϟ/c)·ln(4r₁r₂/r₀²); solar-limb bending 1.75″.

## §2 The kernel and the four samplings (derivation content, carried from the prior spec, relabeled)

One field: **z(r) = ϟ/r**. Four geometric samplings:

1. **Difference** (emit vs receive): Δλ/λ = z(r₁) − z(r₂) = ϟ(1/r₁ − 1/r₂) → for h ≪ R:
   ϟh/R² = gh/c². *(Sampling: subtraction.)*
2. **Line integral** (path loading): Δt = (**2**/c)∫z dl → (2ϟ/c)ln(4r₁r₂/r₀²).
   *(Sampling: accumulation. The bold 2 is OWED — contract §2.)*
3. **Transverse gradient** (wavefront tilt): δ = **2**∫∇⊥z dl = 2ϟ·(2/r₀) = 4ϟ/r₀ → 1.75″ at the
   solar limb. *(Sampling: differentiation. The bold 2 is OWED; the OTHER 2 — ∫r₀ dl/(r₀²+l²)^{3/2}
   = 2/r₀ — is exact geometry, earned.)*
4. **Uniform strain** (cosmological) — QUARANTINED to P4 (contract §5).

The prior spec's phrasing "there is no GR doubling to explain — the factor of 4 is geometric" is
retired: HALF of the 4 is geometric (the integral); the other half is the owed relay prefactor.
Say it that way or not at all.

## §④ Phases

**P0 — Sanity (½ h).** Engine symbols resolve; ϟ_Earth, ϟ_Sun recomputed from kinematic inputs
match laws.hpp to <0.01%; z·k² = 1 prints 1.000000000000 (IDENTITY check, labeled as such).

**P1 — The four samplings vs measured anchors (CONVERGENCE gates, pre-registered).**
- G1 Pound–Rebka: |Δλ/λ − 2.46×10⁻¹⁵|/(2.46×10⁻¹⁵) < 1% (input-precision limited).
- G2 Shapiro: functional form reproduces the ln(4r₁r₂/r₀²) shape; Earth–Venus superior-conjunction
  magnitude within 1% of the standard value computed from the same geometry.
- G3 Bending: δ(R☉) = 1.75″ ± 0.01″.
- G4 Coherence: no angular smearing; wavefront uniformity preserved (qualitative gate, printed).
**Every G1–G4 result line must carry the suffix `[CONVERGENCE — shared algebra under ϟ≡GM/c²;
prefactors owed]`.** No kill language.

**P2 — The prefactor derivation (the native content; this is the phase that matters).**
Attempt ONE mechanism that yields BOTH bold 2's: candidate route — the relay handoff at each
lattice crossing contributes once on load and once on release (in-boundary/out-boundary of the
throughpole; cf. EMC03's two-ended through-flow), giving a factor 2 per traversal in BOTH the
time-accumulation and tilt-accumulation integrals. Pre-commit: the SAME mechanism must produce
both; deriving them from two different stories is a FAIL of this phase (that's how rival algebra
gets smuggled in one factor at a time).
- Gate: both 2's from one stated mechanism, written before checking that the observables still
  land → prefactors move `ASSUMED → DERIVED`, and P1's labels upgrade to clean CONVERGENCE.
- Fail → prefactors stay OWED; the debt is recorded in the verdict header and the stack.

**P3 — The divergence hunt (does the engine force anything GR does not?).**
Enumerate, compute, and classify every place z(r) = ϟ/r departs from the Schwarzschild weak-field
expansion or its strong-field continuation:
- the rung structure (v_orb = c at r = ϟ vs GR horizon at 2ϟ — observable only via strong-field
  phenomena → hand to GOM06 echoes / GOM19; cite, don't re-derive);
- second-order terms in Δλ/λ (the depth engine's z² coefficient vs GR's — compute both; if they
  differ, THAT is a pre-registrable number: state it, magnitude, and where it could be measured);
- path-dependence / superposition (two-body depth fields: does z add linearly? GR is nonlinear at
  second order — the difference is in principle measurable in the Shapiro delay past the Sun at
  superior conjunction with Jupiter also near the line of sight — compute the SDT-vs-GR
  difference magnitude and state whether any instrument reaches it).
**Gate:** the residue list is produced with numbers, even if every entry is "below measurement" —
an empty divergence residue is a finding (the sector ties GR by construction and the campaign
must not spend further kill-effort here).

**P4 — Cosmology quarantine.** Compute the linear-strain z(d) and the octave law 1+z = 2^Δn over
the same distance ladder; print both; characterise where they differ measurably. **No PASS/FAIL
permitted** — output labeled `CONTESTED — pending CR06 re-adjudication`.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | any of G1–G3 needs a per-observable coefficient | the one-kernel claim FAILS — record which sampling broke |
| F2 | P2's mechanism yields one 2 but not the other | prefactor story FAILS; both stay ASSUMED; no partial credit |
| F3 | z·k² ≠ 1 anywhere | algebra bug — STOP, fix, re-run all |
| F4 | P3 finds a forced divergence already excluded by measurement | engine KILLED in that regime; record magnitude and source |
| F5 | P4 written as PASS/FAIL | run VOID (contract §5 violated) |

## §⑨.E Four-root sort (on any failure)
root-1 claim false (kernel/prefactor genuinely wrong) · root-2 dependency (ϟ inputs, CR06 status)
· root-3 spec under-specified (sampling definition ambiguous) · root-4 gate contraband (a gate
that exists only to protect GR's answer — flag per §G, kill the gate not the route).

## §⑤ Outputs
`RUN_LOG.md` (fresh, commitments first) · `gom01_spation_depth_engine.cpp` (existing tool —
re-audit its gates against THIS spec before running; if it embeds the old checked-box logic,
patch and ADJ-log) · `gom01_rerun_<date>.txt` (teed stdout) · `GOM01_VERDICT_DIRECT_<date>.md`
(dual verdict + prefactor ledger + divergence residue).

## §6 Dependencies
Upstream: laws.hpp bridge/koppa · Depth-Closure paper (ϟ≡GM/c² caveat holds the degeneracy rule).
Downstream: GOM05 (variable ℓ_P), GOM06 (waves/echoes), GOM08 (precession — same kernel at next
order), GOM19 (rung table). Register: CR06 VOID-pending (P4 quarantine tracks it).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM01 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Physics class ceiling acknowledged: CONVERGENCE for P1 (degeneracy rule); NATIVE only via P2/P3
- CALIBRATED budget: 0 · ASSUMED ledger: the two prefactor 2's (until P2)
- Gates: G1 <1% · G2 form+<1% · G3 ±0.01″ · P2 one-mechanism-both-2s · P3 residue list with numbers
- Forbidden: kill language in P1; PASS/FAIL in P4; widening tolerances; treating z·k²=1 as evidence;
  deriving the two 2's from two different stories; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 symbol/units failure | fix refs, verify laws.hpp lines | STOP — blocker | fit to target |
| G1–G3 miss gate | check input precision (root-2) before touching the kernel | OPEN that sampling | RETRO-PASS |
| P2 mechanism halves | try the load/release route once more with the OTHER integral first | prefactors stay ASSUMED | two-story derivation |
| P3 residue empty | say so plainly — it is a finding | — | inventing a divergence |

---

*GOM01 · upgraded 2026-07-24 · one kernel, four samplings, two owed 2's, and the divergence residue
stated even if empty. The number is never the prey.*
