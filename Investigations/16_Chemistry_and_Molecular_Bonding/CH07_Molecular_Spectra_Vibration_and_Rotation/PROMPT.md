# CH07 — Molecular Spectra (Vibration & Rotation)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether IR/Raman vibrational lines can be derived as oscillations of the bond-wake (the shared electropause flexing along its axis) and microwave rotational lines as whole-molecule rotation of the wake field — recovering the CO stretch ~2143 cm⁻¹, the CO rotational constant B, and the ν∝√(k/μ) mass dependence — with NO normal-mode wavefunctions and NO rigid-rotor eigenfunctions, only wake mechanics.
2. **Why does it matter?** — The spectrum is the bond-wake's mechanical resonance, not a quantum eigenstate ladder; it EXTENDS atomic emission ([[project_cq03_scroller]] APS01) to two new channels, CONSUMES the CH01 electropause stiffness, and TIES the CM04 phonon picture — all unified under one wake-winding quantiser (PPT06/APS04).
3. **How will we find out?** — Gated phases in §④: vib frequencies from the CH01 well curvature → k, then ω=√(k/μ); rot B from wake-winding-quantised whole-molecule rotation; demonstrate one winding integer indexes all three channels; then a novel un-fit line. Native wake mechanics BEFORE any per-channel quantum postulate or `atomic::`/rival import.
4. **What would prove us wrong?** — §⑧ numeric kill triggers: spectra require normal-mode / rigid-rotor wavefunctions, or each channel needs its own postulate.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is getting the stiffness **k** from the CH01 electropause **WELL CURVATURE** (d²U/dR² at R_e) — an INDEPENDENT quantity — and predicting ν=√(k/μ) OUT. The harmonic-oscillator formula ν∝√(k/μ) is itself classical mechanics and a near-IDENTITY, so it carries no gradeable content on its own. The gradeable content is (a) that the SDT well supplies the *right* k, and (b) that ONE wake-winding quantiser does all three channels.

> **Using ν=√(k/μ) with k read back off the measured frequency is circular — k MUST come from the CH01 well curvature independently, or the grade caps at C.**

One stiffness scale MAY be CALIBRATED(1); declare it explicitly. The √(k/μ) ORDERING across CO/HCl/H₂ and the HCl→DCl isotope shift must be PREDICTED (not back-fit), and the single-quantiser claim (Phase 3) must be DEMONSTRATED, not asserted.

## Question

Atomic emission is k-ladder rung structure (APS01); molecules add two new spectral channels.
**Can IR / Raman vibrational lines be derived as oscillations of the bond-wake (the shared
electropause flexing along its axis), and microwave rotational lines as whole-molecule rotation of
the wake field — recovering the CO stretch ~2143 cm⁻¹, the CO rotational constant B, and the
ν ∝ √(k/μ) mass dependence — with no normal-mode wavefunctions and no rigid-rotor eigenfunctions,
only wake mechanics?** The spectrum is the bond-wake's mechanical resonance, not a quantum
eigenstate ladder.

## SDT mechanism & hypotheses

A shared electropause (CH01) is a pressure-balance surface with a restoring stiffness: displace
the two nuclei along the bond and the occlusion balance pushes back — a harmonic oscillation whose
frequency is set by the electropause stiffness k and the reduced nuclear mass μ. That oscillation
*is* the vibrational line. Rotating the whole wake field about the centre of mass costs movement
budget ([[law_V]]) quantised by the wake winding (PPT06/APS04), giving evenly spaced rotational
lines with spacing 2B. The quantisation that makes lines discrete is the same wake-winding
quantisation that quantises atomic rungs — one mechanism, three channels (electronic/vib/rot).

- **H1 (vibration = bond-wake stiffness):** ω = √(k_electropause/μ); recover the CO/HCl/H₂ stretch
  frequencies from electropause stiffness (from CH01 well curvature) and reduced mass.
- **H2 (rotation = wake-field rotation):** rotational constant B = ħ/(4πcI) emerges from
  wake-winding-quantised whole-molecule rotation; recover CO/HCl B and the 2B line spacing.
- **H3 (one quantisation):** the discreteness of vib + rot lines is the PPT06/APS04 wake-winding
  quantisation, the same that sets atomic rungs (APS01) — no separate quantum postulate per channel.

## Strategy

**Phase 1 — Vibration.** *Goal:* stretch frequencies. *Method:* electropause well curvature (CH01)
→ k; ω=√(k/μ). *Success:* CO 2143 cm⁻¹, HCl 2886 cm⁻¹, H₂ 4401 cm⁻¹ within ~10%; correct √(k/μ)
ordering and isotope shift (HCl→DCl).

**Phase 2 — Rotation.** *Goal:* B and line spacing. *Method:* wake-winding-quantised rotation of
moment of inertia I=μR². *Success:* CO B≈1.93 cm⁻¹, HCl B≈10.6 cm⁻¹ within ~10%; even 2B spacing.

**Phase 3 — Unification.** *Goal:* one quantiser. *Method:* show vib + rot discreteness = PPT06/APS04
winding. *Success:* the same winding integer indexes all three channels; no per-channel postulate.

**Phase 4 — Falsifier.** *Goal:* a novel line. *Method:* predict an un-fit frequency or B (e.g. N₂,
CO₂ bend, or an isotopologue shift) from stiffness + mass alone.

## Success criteria

- **PASS (A):** vib frequencies + rot B + isotope shifts from electropause stiffness & mass under
  one winding quantiser, plus a correct novel line.
- **QUALIFIED (C):** CO/HCl vib & rot within ~10% with the stiffness scale CALIBRATED(1).
  *(Expected landing.)*
- **PENDING (D):** vibrations recovered; rotation only schematic.
- **FAIL (F):** spectra require normal-mode / rigid-rotor wavefunctions.

## Falsification tests

| Test | Predicted outcome | If FAIL (numeric kill trigger) |
|------|-------------------|---------|
| Vib = bond-wake oscillation | CO 2143 cm⁻¹, ν∝√(k/μ), HCl→DCl isotope shift | CO/HCl/H₂ stretch off >10% with k from the CH01 well, or √(k/μ) ordering wrong ⇒ vibration needs normal-mode ψ |
| Rot = wake-field rotation | CO B≈1.93 cm⁻¹, even 2B spacing | B off >10% or spacing not even 2B ⇒ rotation needs rigid-rotor ψ |
| One quantiser | one winding integer indexes all 3 channels | channels need separate quantisers ⇒ each channel needs its own postulate |
| Firewall: k from CH01 well, not back-solved | k = d²U/dR² at R_e (independent), ν predicted OUT | k can only be recovered by back-solving from the measured ν ⇒ tautology, grade caps at C |

## Dependencies

**Upstream:** CH01 (electropause stiffness/well), APS01 (k-ladder atomic spectra it extends),
PPT06/APS04 (wake winding = the quantiser). **Downstream:** spectroscopic identification, astro
molecular lines. **Related:** CM04 (phonons — lattice wake oscillation is the solid-state analogue).
---

## Questions This Opens *(generative — log new ones in `CH07_VERDICT.md`)*

1. Does the anharmonicity (the Morse-like bend, overtone spacing) come from the SHAPE of the CH01 electropause well natively, or must it be added by hand?
2. Does the SAME well curvature predict bond length, bond energy AND vibration — one curve, three observables — tying CH01 to CH07?
3. Is the winding quantiser that sets B the SAME integer ladder as the APS01 atomic rungs — one quantiser spanning atoms and molecules?
4. Does vibration-rotation coupling (centrifugal distortion) fall out of the flexing wake, or does it require a separate correction term?
5. Are the selection rules (IR-active vs Raman-active) a wake-symmetry consequence rather than a transition-dipole rule?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 CO 2143 / HCl 2886 / H2 4401 cm⁻¹ within 10%, correct √(k/μ) ordering + HCl→DCl isotope shift · P2 CO B≈1.93 / HCl B≈10.6 cm⁻¹ within 10%, even 2B spacing · P3 one winding integer indexes all three channels (no per-channel postulate) · P4 novel line (N2 / CO2 bend / isotopologue) within committed tol
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| k from well curvature gives wrong ν | re-examine CH01 well shape (anharmonicity / electropause stiffness) | **OPEN** the vib link | back-solve k from measured ν, call it predicted |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · reading k back off the measured frequency (circular) instead of from CH01 well curvature · claiming NATIVE on ν=√(k/μ) alone (it is classical) · a separate quantum postulate per channel.

---

*CH07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---
---

# RUN 2 PROMPT (2026-07-06) — k from the rolling wall

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — run 2. Everything above this section is
> the run-1 record and is UNTOUCHED, including its dead CH01 branch and its honest P1 OPEN.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` ·
> `HUNTER_PROTOCOL.md` §D + §G (including §G.2 GATE-CONTRABAND and §G.3 no-foreclosure) · the
> run-1 faith ledger (`RUN_LOG.md` §G.1 — the two ASSERTED quantisation rules, the rotational
> ladder step and the E = ℏω line-position bridge, still travel with every number that touches
> them; their caps travel too).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Owner transfer (why this run exists):** run 1 left P1 OPEN under ROOT-CONTACT with the
> recorded re-open condition "NP10 saturation law lands → recompute k here directly." NP10 run 2
> (2026-07-05) fired that condition NEGATIVE: the radial saturated-occlusion wall is structurally
> KILLED (the enhancement identity can only deepen attraction — R2·⓪ below). P1's owner is now
> **ROOT-WALL**: the rolling wake firewall of FARMER refinement 8, with the ~ℏ²/(2m_e·d²)
> curvature budget (ROOT-BUDGET) as its scale fence and the nuclear-transmission amendment
> (force nuclear, compliance electronic) as its sourcing rule. See the ⟐ RE-OPENED notice in
> `CH07_VERDICT.md` (2026-07-06).

## R2·⓪ The standing of the board (settled vs owed — read before Phase 0)

**Settled by run 1 (2026-07-05) — do not re-litigate:**

1. The structural theorem: the shared-seat well **E = g\*·αℏc/R with g\* = −4.19615 at
   x\* = 0.2887 CANNOT vibrate** — d²E/dR² = 2g\*αℏc/R³ < 0 for ALL R (at Re: −4.75×10³ N/m,
   non-restoring). The well that binds cannot vibrate. **The IR stretch is direct evidence of
   the wall.** This run does not question the theorem; it collects on it.
2. The mass-only isotope block: DCl −0.002%, D₂ −0.070%, ¹³CO +0.001% (gates <0.5%) — the
   premise "the well is charge geometry, mass-blind" survived. Run 2 must not break it.
3. Rotation is IDENTITY (earns nothing); the one-quantiser question is OPEN with owner
   PPT06/APS04 (FLM14 door). Neither is re-opened here.

**Settled by NP10 run 2 (2026-07-05) — do not resurrect:**

4. **The wall is NOT saturation.** The exact solid-angle ledger obeys the enhancement identity
   E_exact/E_point = ρ(π−2ρ) ≥ 1 for all ρ = r/R̂ > 0.444: exact occlusion DEEPENS attraction
   at every radius above deep interpenetration; it cannot supply a restoring wall anywhere.
   Face R died on H₂ (+2996% on k, collapse to 0.315 Å) and on NaCl (sign wrong: +40.6 kJ/mol
   of ADDED binding where −74.0 was required). Any W(R) that is radial occlusion in disguise
   is pre-killed — see TRAP-2.
5. **The lock is not the wall.** The (Z−1)! Face-T sequential-tour lock reproduces the nuclear
   ladder with zero constants (d ×1 −1.06%, t ×2 +0.88%, α ×6 −5.57% vs ×6.354 required).
   The ×6.35 belongs to the lock. Run 2's wall must not double-count it — Phase B(iii).
6. **The scale fence:** the D1 budget-wall diagnostic (ℏ²/2m_e confinement class) landed within
   ×4.7 of k(H₂) where occlusion missed by ×31 (R_min 0.579 Å −22%, k 2697 N/m +369%). That
   fence is the reason the curvature budget below is named IN ADVANCE, not after the numbers.

**Given by FARMER refinement 8 (`Investigations/FARMER_PASS_2026-07-03.md`, Rules refinements
§8 — the movement triad + firewall chain; the refinement text is the authority, this is a
pointer):**

7. Movement is one conserved quantity in three modes — **PASS** (relay), **BECOME** (closed
   path), **PRESS** ("pressure itself is movement that cannot move"). Occlusion never creates
   movement; it transfers movement already there.
8. **The rolling wake firewall:** desynchronised/oversynchronised rotations ROLL across each
   other (roll = repulsion = frustration SURPLUS at the interface); cadence-locked rotations
   MESH (mesh = bond = movement saved). **"Vibration = the bond breathing against rolling
   contact."** The bond sits where mesh is paid for; compression past it drives the wakes into
   rolling contact, and the roll cost is the wall.
9. **The nuclear-transmission amendment:** electron repulsion is nuclear repulsion TRANSMITTED
   — the shell is a gearbox; every rotor defends with its own wake, and the nuclear rotor
   dominates when present. **Force nuclear, compliance electronic:** the wall's DEPTH tracks
   the core; the LENGTH that bends is electronic (hence m_e, not m_p, in the curvature budget).

**Owed by run 2:** derive W(R) — the rolling cost — from this mechanics, add it to the run-1
well, and put the ONE resulting wall through the registered three-field cross-check.

## R2·Phase 0 — MANDATORY base mining (fill this table into RUN_LOG.md before one line of code)

Run 2 is executed against an earned base, not from a blank page. The executor MUST open each
source below, extract the named quantities, and record them in RUN_LOG.md with the file path
beside each number. A run that re-derives (or worse, re-invents) machinery the base already
carries is a defective run.

| # | Source | Path | Extract (minimum) | Checkpoint |
|---|--------|------|-------------------|------------|
| 0.1 | CH07 run-1 machinery | `Investigations/16_Chemistry_and_Molecular_Bonding/CH07_Molecular_Spectra_Vibration_and_Rotation/ch07_spectra.cpp` + `results.txt` + `RUN_LOG.md` | the shared-seat minimiser g(x); the OBSERVED anchor block (ω_e, B, R, masses, amu bridge); the §G.1 faith ledger | **CP-1: reproduce g\* = −4.19615 at x\* = 0.2887 to \|Δg\*\| ≤ 1e-6 with the reused machinery BEFORE any wall work.** Not reproduced ⇒ STOP, report blocker |
| 0.2 | NP17 shared-electron law | `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/` (`INVESTIGATION.md`, `NP17_VERDICT.md`, `np17_nuclear_packing.cpp`) | the E = Σ±αℏc/r point-source machinery; deuteron 2.200 vs 2.224 MeV anchor | the wall ADDS to this well; it never replaces or re-scales it |
| 0.3 | NP10 run-2 kill + fence | `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/NP10_VERDICT.md` + `np10_contact_wall.cpp` + `np10_contact_wall_results.txt` | the enhancement identity ρ(π−2ρ) ≥ 1 (ρ > 0.444); the D1 fence numbers; the Face-T (Z−1)! ladder; the deuteron cage shift +0.23% | **CP-2: write into RUN_LOG one explicit sentence demonstrating the proposed W is not radial occlusion in disguise** (TRAP-2) |
| 0.4 | CH02 Evjen sums | `Investigations/16_Chemistry_and_Molecular_Bonding/CH02_Ionic_and_Metallic_Bonding_from_Electropause_Transfer/ch02_ionic_metallic.cpp` + `results.txt` + `CH02_VERDICT.md` | the Evjen machinery (M = 1.747574, geometric); NaCl 861.0 vs 787 kJ/mol (+9.4%); KCl 771.8 vs 715 (+7.9%); MgO 4611.6 vs 3791 (+21.6%); the ⟐ isoelectronic re-open notice | reuse the Evjen sum AS-IS; the wall enters as a pairwise lattice sum on top, no new lattice machinery |
| 0.5 | CM01/CM05 stiffness families | `Investigations/12_Condensed_Matter_Physics/CM01_Superconductivity_as_Phase_Locked_Vortex_Pairs/` · `Investigations/12_Condensed_Matter_Physics/CM05_Superfluidity_and_BEC_from_Phase_Lock/` — and SEARCH `Investigations/` for any other earned stiffness / phase-lock / cadence-lock result | any earned compliance or lock-stiffness number that bears on the roll cost (consult-if-relevant) | if used, the earned label travels; if judged irrelevant, say so in RUN_LOG (one line) rather than silently skipping |
| 0.6 | FARMER refinement 8 | `Investigations/FARMER_PASS_2026-07-03.md` (Rules refinements §8) | the movement triad; roll vs mesh; force nuclear / compliance electronic; the Ne/Na⁺/Mg²⁺ isoelectronic decidable | the mechanism text in R2·⓪ is a pointer — the refinement is the authority |

**Harvey's disqualified-data fallback (standing clause):** previously disqualified or
quarantined intermediates (dead branches, killed faces, C-capped back-solves — e.g. run 1's
declared-circular k table, NP10's Face-R profiles, CH01's dead well) MAY be consulted as
LEADS. Labels travel with the numbers. Nothing is promoted without a derivation.

## R2·Phase A — the wall's curvature at the H₂ seat (primary gate)

**The claim under test.** The run-1 well binds and cannot vibrate; refinement 8 names what it
breathes against. Run 2's committed target: a **DERIVED rolling-firewall wall term W(R)**,
added to the run-1 well —

E_tot(R) = g\*·αℏc/R + W(R), g\* = −4.19615 (reused, CP-1 anchored)

— must produce an **interior minimum at Re(H₂) = 0.7414 Å with curvature
k = d²E_tot/dR²|_min = 575 N/m, both within ±25%, with NO parameter fitted to k or Re.**

**The scale budget, named in advance (ROOT-BUDGET):** W's curvature must live in the
**~ℏ²/(2m_e·d²) confinement class** — the electron-side compliance scale the NP10 D1
diagnostic fenced (within ×4.7 of k(H₂) where occlusion missed ×31) — with the
**nuclear-transmission amendment**: the wall's depth tracks the core (nuclear rotor's defence,
transmitted through the shell gearbox); the compliance is electronic (m_e, electronic lengths).
The compliance length d must be DERIVED or arrive with an earned base label (candidates the
base already owns: a₀, the seat radius x\*·R, the seat gap). If more than one candidate is
evaluated, ALL evaluations must be printed (look-elsewhere logged) and the selection rule must
be stated independently of the gates — selecting d because it lands is fishing.

**Derivation obligations (all four in RUN_LOG before the tool runs):**

- **D-A1:** W(R)'s functional form, written down with its mechanism sentence (what is rolling,
  what is meshed, what movement is frustrated), BEFORE any evaluation against Re or k.
- **D-A2:** every constant in W traced to the whitelist / an earned base result, each with its
  label. Fitted-parameter count against this domain: **zero**.
- **D-A3:** the CP-2 not-occlusion sentence (Phase 0.3).
- **D-A4:** the roll/mesh domain rule — where W fires (rolling interfaces between distinct
  rotor+wake systems) and where it does not (cadence-locked meshed interiors). This rule is
  load-bearing for Phase B(iii); it must be stated here, before any nuclear number is seen.

**Gates (committed, never widened):**

- **G-A1:** E_tot has an interior minimum with R_min within ±25% of 0.7414 Å.
- **G-A2:** k = d²E_tot/dR² at R_min within ±25% of 575 N/m.

**Report-only columns (mandatory to print, not gated):** E_tot(R_min) against the OBSERVED
well depth D_e(H₂) = 4.75 eV, AND against NP10's §G-5 finding that the bare run-1 well is
−81.5 eV at Re — 2.5× the measured total electronic binding (31.95 eV). The depth ledger is
known-sick at contact; a curvature PASS with an absurd depth must be printed and flagged, not
hidden (TRAP-4).

**GATE-CONTRABAND clause (§G.2):** importing the rival's exchange-repulsion / Pauli-exclusion
machinery is **forbidden in-chain**; it may appear as a **labelled rival column only**. The
converse guard also applies: no kill condition in this run may exist only to protect a rival
axiom — every gate above is a measured anchor (0.7414 Å, 575 N/m, 787 kJ/mol, 28.296 MeV).
And per NP10's D1 flag: the ℏ²/2m_e curvature CLASS is formally degenerate with the rival's
zero-point form — if the final W is form-identical to the rival expression with no native
derivational content beyond the form, the physics class caps at CONVERGENCE (delete-test),
never NATIVE. Say so in the verdict if it happens.

**Named traps (error-resistance — the executor initials each in RUN_LOG):**

- **TRAP-1 (the two-knob fit):** any well −A/R plus wall B/Rⁿ with B, n free can ALWAYS hit
  (Re, k) — two conditions, two knobs. That is a fit wearing a derivation's coat. W's form and
  constants are committed at D-A1/D-A2; nothing is chosen to land a gate.
- **TRAP-2 (occlusion in disguise):** if W's derivation, translated, is a solid-angle/shadow
  ledger, it is pre-killed by ρ(π−2ρ) ≥ 1. CP-2 sentence required.
- **TRAP-3 (rival laundering):** Pauli/exchange machinery renamed "rolling" is contraband
  in-chain. The rival column is labelled or absent.
- **TRAP-4 (depth blindness):** curvature gates can pass while the energy ledger is absurd —
  the depth columns are mandatory print.
- **TRAP-5 (stale binaries):** OneDrive + MSVC — rebuild before every cited result; the exe
  mtime must postdate the cpp mtime (the GD05 lesson).

## R2·Phase B — the registered three-field cross-check (the life-or-death gate)

The wall was re-opened under a REGISTERED cross-check (CH07 §D-7 → NP10 run-2 → CH07 ⟐
notice: 575 N/m ∧ NaCl +9.4% ∧ α ×6.35). Run 2 executes it. **The SAME W(R) — frozen at the
Phase-A commit, no re-tune, no per-target constants, no per-field re-derivation — must
simultaneously:**

- **(i)** give k(H₂) ≈ 575 N/m (G-A2 restated; it is one leg of the conjunction);
- **(ii)** correct CH02's NaCl overshoot: adding the pairwise lattice sum of W (nearest
  shells until converged; Evjen machinery reused from Phase 0.4) must move 861.0 kJ/mol
  (+9.4%) to **inside ±5% of 787 kJ/mol**, and must move KCl (771.8 vs 715, +7.9%) **in the
  same direction** (binding reduced, toward 715). MgO (4611.6 vs 3791, +21.6%) is a mandatory
  REPORT-ONLY column — under the nuclear-transmission amendment the wall stiffens with Z at
  fixed shell (Mg²⁺/O²⁻ are neon-shell), and this run's MgO residual is that prediction's
  first controlled data point; the CH02 ⟐ notice's Ne/Na⁺/Mg²⁺ isoelectronic decidable may be
  sketched as REPORT-ONLY if reachable, gated nowhere;
- **(iii)** cohere with the NP10 α-lock story: evaluate W at the NP17 nuclear geometries
  (deuteron, triton, alpha; Σ±αℏc/r machinery from Phase 0.2) under the D-A4 roll/mesh domain
  rule, and show the Face-T ladder survives — **each of d/t/α binding shifts by <5%**, so
  that **×6.35 remains the lock's, not the wall's**: the run must show the wall does NOT
  double-count the lock. (Anchor for scale: NP10's cage-rule diagnostic shifted the deuteron
  +0.23%.) If the derived W fires hard inside meshed nuclear interiors, the domain rule D-A4
  has failed and the conjunction fails with it.

**One wall pays all, or the wall dies.**

**Gate G-B (conjunction):** (i) ∧ (ii) ∧ (iii). A wall that passes Phase A but fails either
ionic leg or the nuclear-coherence leg is KILLED for this W-class — not tuned, not re-homed,
not "targeted for run 3" (dead matches are killed cleanly). Partial credit exists only as
honest §D recovery material, never as a PASS.

## R2·Phase C — anharmonicity as the free prediction (report-only)

A rolling wall is asymmetric by construction — stiffer inbound (compression into rolling
contact) than outbound (the 1/R well). **Pre-committed sign: ωₑχₑ > 0 (Morse-like).** From
the cubic coefficient of E_tot at R_min, derive the anharmonicity ratio ωₑχₑ/ωₑ for H₂ and
compare with the measured 121.3/4401.2 = 0.0276 as a **REPORT-ONLY column — no gate,
look-elsewhere protected**: a match earns nothing until pre-registered as a gate in a future
run; a miss kills nothing here. The sign pre-commitment IS scored (a derived ωₑχₑ < 0
contradicts the rolling mechanism and must be reported as a mechanism strike in the verdict).
The E = ℏω line-position bridge cap (run-1 faith ledger) travels with any cm⁻¹ conversion.
Also print, report-only: ω_e(H₂) from the DERIVED k via √(k/μ) vs 4401.2 cm⁻¹ — the number
run 1 was structurally unable to print.

## R2·Phase D — isotope re-verification (regression gate)

The run-1 mass-only isotope block is earned machinery and must SURVIVE the wall: W is charge
geometry, mass-blind, so k stays isotope-invariant and the mass-only transfers must reproduce
**DCl −0.002%, D₂ −0.070%, ¹³CO +0.001%** — run-1 numbers cited as machinery anchors —
**regression gate <0.5% each, unchanged from run 1.** Rerun the transfer block with the wall
in place. Any drift beyond the gate means the wall has smuggled in a mass dependence: G-D
FAIL, §D seven questions, and the "charge geometry, mass-blind" premise goes back on the
table. This phase is cheap and non-optional.

## R2·Mandatory execution clauses (non-negotiable; copy into RUN_LOG.md)

1. **ADJ-before-code.** Every deviation from this spec — filename, mesh, phase split,
   candidate list — gets an ADJ-### entry in RUN_LOG.md BEFORE the code changes.
2. **Gates never widened.** The tolerances above are committed at spec time. Widening after
   numbers is forbidden regardless of how close the miss is.
3. **§D seven questions on any FAIL** (`HUNTER_PROTOCOL.md` §D), recovery graded RECOVERED /
   PARTIAL / NO RECOVERY; Q7 cascade traced to root.
4. **NO G/M/GM in-chain.** Anywhere. Conversions via the legacy helper are not "in-chain".
5. **Never "charge radius."** R_p is the proton **boundary radius** (boundary/surface/
   displacement radius). No charge substance anywhere in prose or comments — handed
   redirection; e is a unit-bridge.
6. **No borrowed units.** No magnetons, no rival-native yardsticks; SDT-native quantities plus
   declared SI bridges (the amu bridge is already declared in the run-1 log).
7. **Results = teed stdout of exit-0 tool.** Every number cited in the verdict comes from the
   teed stdout (`results_run2.txt`) of a tool that ran to completion with **exit code 0**;
   PASS/FAIL verdicts are printed lines in that stdout, not crash codes (this supersedes the
   run-1 exit-1 convention for this run). No hand-transcribed values.
8. **PYTHONIOENCODING=utf-8** set for any Python step (Windows console mangling of unicode in
   teed output is a known corruption source); C++ remains the default tool class.
9. **Harvey's disqualified-data fallback** (Phase 0, restated): disqualified/quarantined
   intermediates may be consulted as LEADS; labels travel; nothing promoted without derivation.
10. **GATE-CONTRABAND** (§G.2, Phase A, restated): rival exchange/Pauli machinery in-chain is
    forbidden — labelled rival column only; and no gate may exist merely to enforce a rival
    axiom.

## R2·Pre-Run Commitment Block (copy to RUN_LOG.md before coding, below the run-1 log)

```markdown
## Pre-Run Commitments — CH07 RUN 2 (k from the rolling wall)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: NATIVE (wall) — honest fallbacks CONVERGENCE (form-degenerate with
  rival zero-point), OPEN (no interior minimum derivable), KILLED (conjunction fails)
- CALIBRATED budget: 0 fitted to k, Re, or any Phase-B target. Every constant in W enters
  with a derivation or an earned base label (D-A2).
- W(R) form + constants + mechanism sentence + domain rule (D-A1..D-A4): WRITTEN HERE before
  evaluation against any gate. Look-elsewhere: all evaluated compliance-length candidates listed.
- Committed gates: G-A1 R_min ±25% of 0.7414 Å · G-A2 k ±25% of 575 N/m · G-B conjunction =
  (i) G-A2 ∧ (ii) NaCl inside ±5% of 787 kJ/mol AND KCl moved toward 715 ∧ (iii) d/t/α shifts
  each <5% (Face-T ladder intact; ×6.35 stays the lock's) · G-C sign only: ωₑχₑ > 0 (ratio
  0.0276 REPORT-ONLY) · G-D isotope regression <0.5% each (anchors −0.002% / −0.070% / +0.001%)
- Checkpoints: CP-1 g* = −4.19615 to 1e-6 · CP-2 not-occlusion sentence · TRAP-1..5 initialled
- Forbidden: widening any gate; per-target constants; re-tuning W between fields; radial
  occlusion in disguise; rival machinery in-chain; back-solving anything from a gated target;
  "charge radius"; G/M/GM; borrowed units.
```

## R2·Pivot table (extends the run-1 table; PIVOT / KILL / OPEN — never RETRO-PASS or PLUG)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| CP-1 g\* not reproduced to 1e-6 | fix units/machinery against run-1 files | STOP — report blocker | proceeding on an unverified base |
| No interior minimum from derived W | re-derive the roll cost within refinement-8 mechanics (ADJ-logged) | Phase A FAIL → §D; class OPEN or KILLED | adding/adjusting a constant to force a minimum |
| G-A passes, G-B(ii) fails | check lattice-sum convergence and ionic geometry ONLY (ADJ) | **the wall dies** — KILLED for this W-class | re-tuning W at the ionic field |
| G-B(iii) double-counts the lock | re-examine the D-A4 domain rule as derived (ADJ) | conjunction FAIL → §D | exempting the nuclear field by fiat after seeing numbers |
| Depth columns absurd while gates pass | print, flag, carry as named ledger debt | — | hiding or omitting the depth columns |
| W lands form-identical to rival zero-point | label CONVERGENCE (delete-test), say so in verdict | — | claiming NATIVE |
| ωₑχₑ derived < 0 | report as mechanism strike in verdict | — | silently dropping Phase C |

## R2·Verdict requirements

Dual verdict line (prompt completion A–F · physics class NATIVE / CONVERGENCE / DEGENERATE /
KILLED / OPEN · recovery grade · cascade root), a §G faith ledger for run 2 (what W accepted
on faith — the surplus asymmetry, the domain rule, the compliance-length selection), §G.1/§G.2
mirror answers at start and at any kill, and explicit disposition of ROOT-WALL and ROOT-BUDGET
(paid, fenced, or split — with re-open conditions named per §G.3). Append to `CH07_VERDICT.md`
below the ⟐ notice; run-1 verdict untouched.

---

*CH07 RUN 2 · spec 2026-07-06 · J. C. Harvey · one wall pays all, or the wall dies.*
