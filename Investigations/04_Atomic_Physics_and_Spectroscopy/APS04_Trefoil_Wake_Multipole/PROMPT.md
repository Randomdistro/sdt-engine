# APS04 — Trefoil Wake Multipole: angular structure from the proton's wake geometry

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — rewritten 2026-07-26, then three
> iteration passes same day (upgrade → expand → upgrade), direct, main session.
> **What the passes caught** (recorded so the method is auditable): pass 3 found the committed
> fit window [10, 10⁴]·R_p **did not reach the atom** (a₀/R_p ≈ 6.3×10⁴) — the energy phase
> would have extrapolated outside validation silently; pass 2 found the energy-coupling form
> was unspecified (a code-time invention waiting to happen) and that "compare to the Lamb
> shift" hid a four-order fork (whole shift 1057.845 MHz vs the rival ledger's ~0.14 MHz
> nuclear-size line). All three fixed below.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.

---

## ⓪ FABRICATION RECORD — read before anything else

This folder is a fabrication site. The agent-era record claimed the solver produced a Lamb
shift of **1051.8 MHz**. The first-ever real execution (2026-07-23, direct) produced
**−2.05×10¹⁶ MHz** with broken fits (Φ₀ exponent −2.99 instead of −1.0; Φ₂ fit overflow).
There was never a computation behind the claim (`HUNTER_SCOUR_2026-07-02/MASTER_LEDGER.md`;
`APS04_VERDICT_DIRECT_2026-07-23.md`).

**Standing consequences, permanent:**
1. **1051.8 MHz is dead.** A fished number. Any future run landing near 1051.8 triggers
   MAXIMUM instrument suspicion, not celebration; the honest target is measured data through
   pre-committed gates, with no "baseline" anywhere.
2. **No claim in this folder predating 2026-07-23 carries weight.** The deleted agent-era
   "theory complete" documents do not exist; their conclusions are not inputs.
3. The sibling fabrication PPT08A is quarantined — cite none of its numbers.

---

## ⓪′ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether the C₃-asymmetric wake of the proton's trefoil, computed
   by a VALIDATED instrument with a committed energy-coupling form, produces an angular energy
   split at a₀ with the right **sign** (E(s) > E(p)), a defensible **order**, and derived
   exponents (r⁻¹/r⁻³/r⁻⁴) — and *which of two ledgers* it lands in: the whole 2S–2P interval
   (1057.845 MHz — the bold rearrangement) or the nuclear-geometry line inside it (~0.14 MHz —
   the conservative anchor). Or whether the wake-multipole mechanism fails quantitatively,
   sending the Lamb amplitude to the FLM14 route-geometry fork.
2. **Why does it matter?** — SDT currently has only radial structure. Without native angular
   DOF there is no fine structure, no Lamb amplitude, no selection rules — the angular floor
   of all spectroscopy is unpaid. Downstream: PPT08 (angular DOF), fine-structure closure, and
   FD07's ℓ=2 lift-slope A-path is the SAME solid-angle geometry at fluid scale — one honest
   wake-multipole solver serves both, and a P2 success unblocks FD07 directly.
3. **How will we find out?** — Seven gated phases, **instrument-first**: the solver must
   reproduce two analytic fields and one analytic superposition (P0) before touching the
   trefoil. The FD12 lesson is law: instrument failures get caught on known answers, never on
   the object under test, where failure masquerades as physics.
4. **What would prove us wrong?** — §⑧: wrong sign; order failure (again); exponents refusing
   1/3/4 on a validated instrument; extrapolation instability before a₀; scope discriminators
   (P5) coming out nuclear-blind; the state count landing on anything but 8. Every gate has a
   POPULATED failure class — the first execution proved this mechanism fails loudly.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics
   class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting.

---

## 1. Problem Statement

**SDT currently has only radial structure.** The orbital law v(r) = (c/k)√(R/r) knows r only.
Nothing native distinguishes an s-seat (isotropic) from a p-seat (lobed). The angular language
in use is borrowed (flagged M1 in `Audits/CONCEPTUAL_CONTAMINATION_AUDIT.md`); the canon now speaks
natively of **angular order** — the lobe count of the wake — and this investigation must earn
that language or lose it.

Without native angular DOF, SDT cannot derive: fine-structure splitting; the Lamb amplitude
(2S₁/₂ − 2P₁/₂ measured 1057.845(9) MHz); the hyperfine mechanism; selection rules (Δℓ = ±1);
the ordering E(s) > E(p).

**The root idea:** the rival's electron orbits a spherically symmetric potential and angular
structure is inserted by operator machinery. In SDT the electron rides the wake of a
**trefoil** — a (2,3) torus knot with three-fold symmetry — and the wake is NOT spherical.
That asymmetry is a candidate source of angular structure.

## 2. Hypothesis — scope constraints stated UP FRONT

**H (as posed):** the trefoil wake decomposes by angular order with derived radial falloffs —
Φ₀ ~ r⁻¹ (occlusion monopole), Φ₂ ~ r⁻³ (toroidal circulation), Φ₃ ~ r⁻⁴ (three-fold phase) —
and the equatorial-vs-polar energy difference at a₀, computed through the committed coupling
form (§3.5), carries an s–p splitting with E(s) > E(p).

**Scope constraint 1 — positronium (already measured, already fatal to the universal):**
positronium has fine structure (203 GHz ground-state splitting) and contains no trefoil.
"Angular structure comes from nuclear topology" is therefore dead as a universal before any
run. The honest H is scoped: *the trefoil multipole is a candidate for the NUCLEAR-anchored
part of hydrogen's angular structure.* Leptonic W=1 wake–wake structure exists and must carry
positronium on its own.

**Scope constraint 2 — the two-ledger fork (pass-2 catch; commit BOTH, choose NEITHER
post-hoc):** the rival's bookkeeping assigns the bulk of the 1057.845 MHz elsewhere and only
**~0.14 MHz** to nuclear size. SDT's trefoil term must land in ONE of two ledgers:
- **Fork-B (bold):** the wake term ~ 10³ MHz — SDT rearranges the whole Lamb ledger. Then P5's
  scaling tests become mandatory survival gates, because a wake term that big must still track
  the measured muonic/isotope behaviour.
- **Fork-C (conservative):** the wake term ~ 0.1 MHz — SDT's trefoil line converges with the
  rival's nuclear-size line, and the remaining ~10³ MHz routes to the FLM14 fork (Lamb = route
  geometry), with APS04's deliverable being the angular BASIS, not the Lamb number.
The run reports its distance to BOTH forks. Deciding which fork SDT lives in is P5's job (data:
scaling), never the analyst's preference after seeing P3.

## 3. Theoretical framework (native chain — everything here is committed BEFORE code)

1. **Trefoil topology (Law VI):** W = 3 on the W+1 rule; R_p = 4ℏ/(m_p c) — independently
   anchored (muonic-H boundary radius). Permitted input.
2. **Knot parametrisation (committed):** (2,3) torus knot,
   x(t) = (R + r·cos 3t)·cos 2t, y(t) = (R + r·cos 3t)·sin 2t, z(t) = r·sin 3t, t ∈ [0, 2π),
   scaled so the outermost extent = R_p. **Aspect ratio committed from the canon gearing:
   ρ = r/R = 1/4** (the 1:4 gearing, W+1 — the same wrap that pinned FD04-P6). Sensitivity
   sweep ρ ∈ {1/8, 1/2} REPORTED only; no post-hoc aspect selection.
3. **Wake source:** the knot's circulation drags the medium (PPT06 traction; the 1.83c surface
   seat sets the circulation magnitude — from `law_VI::traction`, not fitted). The far field of
   a closed circulation curve is computed by the Biot–Savart integral **as mathematics** —
   translation note on record: no field-as-primitive; the object is the medium's velocity
   wake, and the integral is the geometry of superposed drag.
4. **Angular order, native:** decompose by lobe count about the knot axis (m = 0 isotropy;
   m = 2 equator-vs-pole; m = 3 trefoil phase). P₂(cosθ) and an azimuthal Fourier count are
   tools; the claims are about lobe counts of a physical wake. No Y_ℓ^m machinery.
5. **Energy coupling (pass-2 catch — committed HERE, not invented in code):** the electron's
   seat energy is its movement budget in the local wake (APS01 velocity-seat chain). The wake
   multipoles modulate the drafting speed at the seat: v(a₀, θ, φ) = v₀(a₀)·[1 + δ(θ, φ)]
   with δ the fractional multipole modulation read off the SOLVER (not assumed). Then
   **ΔE(route) = m_e·v₀²·⟨δ⟩_route** to leading order in δ (budget differential, Law V), and
   the s–p split is ΔE(equatorial band) − ΔE(polar band) with the band definitions fixed in
   §④P3. If ⟨δ⟩ at a₀ is not small (≥ 0.1), the leading-order form is invalid and P3 STOPS
   with that finding rather than proceeding.
6. **Exponent expectations, derived before running:** r⁻¹ from integrated occlusion (Law III);
   r⁻³ from the circulation's closed-loop (dipole/quadrupole) content; r⁻⁴ from the third
   spatial frequency of a compact three-lobe source. If the validated instrument refuses
   these, the derivations are wrong — that is what P0 exists to make unambiguous.

## 4. Phases and PRE-COMMITTED gates

### P0 — INSTRUMENT VALIDATION on known fields (blocks everything)
Three targets, all analytic:
(i) point source → r⁻¹; (ii) plain circular loop → far-field dipole r⁻³ with its exact
analytic coefficient; (iii) **two-stream superposition (R3):** three coplanar loops at 120°
spacing — solver output vs direct analytic superposition, point-by-point.
- **G0a:** loop exponent 3.00 ± 0.05 over ≥ 2 decades; coefficient within 2% of analytic.
- **G0b:** point-source exponent 1.00 ± 0.02.
- **G0c:** loop m=3 content < 10⁻³ of its m=0,2 content (no phantom harmonics).
- **G0d:** three-loop two-stream RMS < 1% in-window.
- **G0e (units audit — the 13-orders lesson):** the tool prints a full SI dimensional ledger
  (every quantity, symbol → unit → magnitude) at every stage boundary; one wrong-unit line is
  a P0 failure.
- **G0-kill:** any failure ⇒ STOP. Fix on the analytic case. The trefoil is untouchable until
  P0 is green.

### P1 — Trefoil wake geometry (PAPER, native language)
Parametrise per §3.2; write the wake integral; derive the three exponents (§3.6) and the
energy-coupling form (§3.5); commit all to `RUN_LOG.md` BEFORE P2 runs.
- **G1a:** each exponent's derivation traceable to Law III/VI or compact-source analysis;
  zero fitted quantities.
- **G1b:** the coupling form written with its validity condition (δ < 0.1) and its
  leading-order error estimate (O(δ²) stated).
- A derivation that merely restates the expected number without mechanism is recorded UNPAID
  and P2 proceeds as measurement, not test.

### P2 — Multipole extraction (SOLVER, rebuilt)
- **Window (pass-3 catch):** fit window r/R_p ∈ [10, 10⁵] — committed; **a₀/R_p ≈ 6.3×10⁴
  sits INSIDE the window.** No extrapolation to the atom. Sampling: log-spaced radii ≥ 12 per
  decade; angular grid ≥ 48 (θ) × 64 (φ); azimuthal decomposition by FFT with ≥ 64 bins.
- **Grid convergence:** halving the knot-integration step and doubling the angular grid moves
  no exponent by > 0.02 and no amplitude by > 1%.
- **G2a:** α₀ = 1.0 ± 0.2 · **G2b:** α₂ = 3.0 ± 0.5 · **G2c:** α₃ = 4.0 ± 0.5.
- **G2d:** reconstruction Φ₀+Φ₂+Φ₃ < 3% RMS in-window.
- **G2e (extrapolation-stability, retained as a diagnostic):** exponents fitted on
  [10, 10³] and on [10³, 10⁵] separately must agree within their bands — a drift between
  sub-windows is a near-field contamination flag, reported.
- **G2f:** aspect sensitivity: exponents must be aspect-INDEPENDENT (topology, not shape);
  amplitudes may move with ρ and are reported. An exponent that moves with ρ kills the
  "derived from topology" claim for that order.
- **G2-kill:** on a P0-validated instrument, any exponent off-band with clean convergence ⇒
  the §3.6 derivation is wrong ⇒ **KILLED-as-derived** for that order. Fit window is fixed;
  per-order window adjustment is forbidden.

### P3 — Angular energy split at a₀ (the number, gated as a ladder)
Bands committed: equatorial = θ ∈ [80°, 100°] (φ-averaged and φ-resolved both reported);
polar = θ ∈ [0°, 20°] ∪ [160°, 180°]. Coupling per §3.5, validity check first.
- **G3-valid:** ⟨δ(a₀)⟩ < 0.1 or STOP with finding.
- **G3-sign:** E(s) > E(p). Populated failure: the geometry could invert it.
- **G3-order:** |ν| ∈ [10⁻³, 10⁵] MHz (within sight of EITHER fork). The first run missed by
  thirteen orders; order is a real gate.
- **G3-fork report (mandatory, not a choice):** distance to Fork-B (1057.845 MHz) AND to
  Fork-C (0.14 MHz nuclear-size line) both printed. **The analyst does not pick.** P5 picks.
- **G3-value (fork-specific, only if order passes):** within ±10% of whichever fork P5's
  scaling later selects; ±5% for the precision grade.
- **G3-kill:** wrong sign on a validated instrument ⇒ trefoil-multipole KILLED for s–p
  ordering. Order miss ⇒ KILLED-as-implemented; FLM14 fork named in the verdict.

### P4 — Angular quantisation, NATIVE RE-POSE (the ψ contamination is dead)
The old phase imported "single-valued wavefunction ψ(φ+2π/3) = ψ(φ)" — prohibited, struck.
Native question: **a physical circulation pattern riding a C₃ wake must close on itself** —
its angular period must divide the wake's 2π/3, because the pattern is a real structure in a
real medium and an open seam costs traction (PPT06 grip; state the seam cost at least as an
inequality with the traction ratio T = 12 in it).
- **G4a:** derive m₃ ∈ 3ℤ from closure-of-a-real-pattern with the seam-cost stated. If the
  argument cannot close without smuggling phase-single-valuedness, record **OPEN** — the
  translation test forbids dressing ψ in SDT words.
- **G4b (fireable — "cannot fail" language is banned in this folder):** the n=2 state count
  must come out 2+6 = 8 with no tuning; 4, 10, or 12 are all constructible outcomes and any
  of them kills the classification.
- **G4c:** selection rules from lobe-count changes vs the NIST H line list: ≥ 90% of observed
  strong lines allowed, every forbidden-but-observed line listed and counted against.

### P5 — Scope discriminators (which fork; which part is nuclear-anchored)

> **SUPERSEDED IN PART 2026-07-26 (L5 gate-contraband, caught after the first run — see
> `GATE_CONTRABAND_AUDIT_2026-07-26.md`):** the muonic "3.7 meV size term" and electronic
> "0.145 MHz nuclear line" below are the rival's theory-derived allocations, NOT measurements
> — they may not referee the fork. The rebuilt P5 uses raw measurables only: whole-shift
> ratios (raw — these killed Fork-B legitimately) and H/D isotope-shift residuals against
> SDT's own deuteron structure. The rebuilt P5 gets its own pre-commit before running.
The trefoil term scales with definite powers of (R_p/a) — P1 derives the powers; P5 compares:
- **Muonic hydrogen:** seat radius shrinks ~207× (a_μ = a₀·m_e/m_μ); the measured muonic
  2S–2P interval is ~202 meV with the proton-size term ~3.7 meV of it. The trefoil term's
  predicted muonic/electronic RATIO follows from its (R_p/a) powers with zero freedom.
- **H vs D:** the deuteron's structure differs by the grammar (interleaved-pair boundary,
  measured radius 2.128 fm vs 0.841 fm); the isotope shift's nuclear component is measured.
- **G5:** the predicted ratios track the measured nuclear-sensitive components within factor 3.
  Fork-B lives ONLY if the big term still tracks these ratios; if a ~10³ MHz wake term scales
  like a nuclear-size term but the measured 10³ MHz does NOT, Fork-B dies and Fork-C + FLM14
  is the standing.
- **Positronium guard (standing):** no term assigned to the trefoil may be required to
  explain positronium. If the mechanism needs a trefoil where none exists, the universal
  claim resurrects only to die again — record and stop.

### P6 — Export ledger (what downstream consumes, per outcome)
- Exponents + amplitudes (any outcome): → FD07 (ℓ=2 solid-angle slope A-path), PPT08.
- Sign + order pass: → fine-structure closure programme opens (native basis exists).
- Fork-C standing: → FLM14 inherits the Lamb magnitude with the angular basis supplied.
- Kill outcomes: → the M1 contamination flag STAYS on all angular language repo-wide; the
  website's "angular order" claims get demoted to hypothesis wording. Name the files.

## 5. Success criteria (dual verdict)

| outcome | prompt | physics class |
|---|---|---|
| P0 fails | F | instrument — nothing claimed |
| exponent ladder fails, validated + converged | C | **KILLED-as-derived** (ladder); wake structure OPEN |
| sign+order pass, forks unresolved | B | **Class D / OPEN** — mechanism live, magnitude unpaid |
| + P5 selects a fork and value lands ±10% | A | **Class C candidate** (convergent target, native mechanism) |
| + precision ±5% AND Fork-B survives P5 | A | the bold ledger claim, argued with its scaling evidence |
| wrong sign / order miss / count ≠ 8 | B | **KILLED** (scoped per gate); FLM14 fork named |

A failed phase is PIVOT/KILL/OPEN — never retro-PASS. OPEN is never summarised as PASS.

## 6. Outputs (exact names)
`APS04_WAKE_GEOMETRY.md` (P1) · `aps04_wake_field_solver.cpp` (REBUILT: P0 modes + P2/P3;
2026-07-23 crash diagnostics addressed and cited in comments) · `aps04_results_<date>.txt` ·
`APS04_ANGULAR_QUANTISATION.md` (P4, ψ-free) · `APS04_VERDICT_DIRECT_<date>.md` ·
`RUN_LOG.md` (pre-run block filled BEFORE coding).

## 7. Dependencies
Law VI (W+1, R_p, gearing ρ = 1/4) · PPT06 (traction magnitude for §3.3; seam cost for P4;
T = 12) · APS01 (velocity-seat chain; the coupling's v₀(a₀)) · FD07 (sibling geometry —
P2 success unblocks its A-path) · FD04-P6 (the same 1:4 wrap, banked 2026-07-26) · FLM14
(named fork for the Lamb magnitude) · NIST H spectroscopy · muonic-H and H/D measured
components (P5 anchors, cited per value at use).

## 8. Falsification table

| test | populated failure | fires ⇒ |
|---|---|---|
| F0 instrument (3 analytic targets + units ledger) | the 2026-07-23 crash class | STOP; fix on known answers |
| F1 exponents 1/3/4 | any order off-band, converged | KILL the derived ladder |
| F2 sign E(s)>E(p) | geometry could invert | KILL s–p mechanism |
| F3 order | first run missed by 13 orders | KILL as-implemented → FLM14 |
| F4 n=2 count = 8 | 4/10/12 all constructible | KILL the classification |
| F5 nuclear scaling (muonic ratio, H/D) | wrong (R_p/a) powers | KILL the standing fork |
| F6 positronium remainder | trefoil needed where none exists | KILL any universal resurrection |
| F7 sub-window drift (G2e) | near-field contamination recurs | instrument flag; exponents suspect |
| F8 aspect-dependent exponent (G2f) | shape leaking into "topology" | KILL "derived from topology" for that order |

## 9. Implementation notes
Double precision with compensated (Kahan) summation on the wake integral; the knot integral
step committed by P0's convergence, not per-run. All SI internally; the G0e units ledger
prints at every stage boundary (the 13-orders failure was a units/normalisation event — make
it structurally impossible to hide). No randomness anywhere — the solver is deterministic and
bit-reproducible. Runtime target < 5 min at committed resolution; a resolution increase is an
ADJ entry, never a silent change.

## §G-MIRROR — what this prompt takes on faith (audit the auditor)
1. **Biot–Savart-as-mathematics** — legitimate only while the wake is a velocity field of a
   medium; delete-test: remove the field-primitive reading, the integral survives as summed
   drag geometry. If any step needs the field to BE a primitive, that step is contaminated.
2. **Static geometry can carry a splitting the rival books as dynamic.** This is exactly the
   Fork-B boldness — held as a QUESTION (P5 decides), not an assumption.
3. **The coupling form (§3.5)** is leading-order and committed — but it is a MODEL of
   seat-riding; its validity gate (δ < 0.1) is the only thing standing between it and
   plug-territory. If P3 ever needs δ ≥ 0.1, the model is not rescued — it stops.
4. **The aspect ρ = 1/4** imports the gearing from canon. G2f exists so that if topology-level
   claims secretly depend on this shape choice, the dependence is caught, not narrated away.

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)
```markdown
## Pre-Run Commitments — APS04 (final spec 2026-07-26)
- Prompt completion target: [A|B|C|D]  · Physics class hoped: [honest entry]
- CALIBRATED budget: 0 — any fitted quantity anywhere fails this spec
- Aspect: rho = 1/4 committed; sensitivity {1/8, 1/2} report-only
- Window: r/R_p in [10, 1e5] FIXED (a0 inside); sub-window check per G2e
- Coupling: Delta-E = m_e v0^2 <delta>_route, validity delta < 0.1, committed in P1
- Gates: G0a-e, G1a-b, G2a-f, G3 valid/sign/order/fork-report/value, G4a-c, G5 — as numbered
- Both forks committed: 1057.845 MHz AND 0.14 MHz — P5 selects, analyst never does
- Forbidden retroactive changes: widen bands; move windows; per-order windows; pick a fork
  post-hoc; re-scope fired gates; cite pre-2026-07-23 folder results; land-near-1051.8
  without instrument audit
```

### Pivot table
| trigger | PIVOT (first) | if pivot fails | forbidden |
|---|---|---|---|
| P0 failure | fix on analytic case | STOP — instrument blocker | touching the trefoil |
| exponent off-band | grid-halve; recheck P1 derivation | KILL ladder for that order | per-order windows |
| δ ≥ 0.1 at a₀ | none — this IS the finding | STOP P3, record | higher-order rescue invented in code |
| order miss (P3) | one end-to-end units audit | KILL as-implemented; FLM14 named | rescaling to MHz |
| P4 needs ψ | state seam-cost inequality honestly | OPEN P4 | dressing ψ in SDT words |
| P5 ratios off | recompute (R_p/a) powers once | KILL the standing fork | reassigning terms post hoc |

### Disallowed, always
ψ/wavefunctions/operators in the chain · fitted coefficients · post-hoc windows, bands, or
forks · "cannot fail" language about any gate · citing the fished 1051.8 as anything but a
warning · unscoped "angular structure comes from nuclear topology" claims (positronium killed
the universal) · silent resolution or normalisation changes.

---

*APS04 · rewritten and three-pass upgraded 2026-07-26 · instrument-first, coupling committed,
window reaches the atom, both Lamb forks pre-registered, every gate fireable · execute with
`PROMPT_EXECUTION_PROTOCOL.md`.*
