# RUN_LOG — CH07 Molecular Spectra (Vibration & Rotation)

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding

CH01's electropause well is dead (NP17 is the death knell); the only native molecular well
available is the NP17 shared-seat electrostatic geometry: E(R) = g·αℏc/R with g from pure seat
minimisation. The firewall demand (k from an independent well, not back-solved) is therefore put
to that well directly, and its answer — whatever it is — is the P1 result.

## Faith ledger (§G.1)

1. ℏ is derivation basis; but TWO quantisation RULES enter this domain as assertions, and are flagged as
   such up front: (a) the rotational ladder step (wake-winding quantiser, PPT06/APS04 — asserted,
   not derived here); (b) the line-position bridge E = ℏω (emission bridge — same status). Any
   number depending on them is capped IDENTITY/CONVERGENCE, never NATIVE.
2. Shared-seat configuration for H₂ (2 protons ±R/2 on the axis, 2 electron seats on the
   perpendicular bisector at radius xR): a rendering; the seat TOUR (FLM14) is not modelled.
3. Isotope-transfer premise (native, falsifiable): the well is charge-geometry only, so k is
   UNCHANGED under isotope substitution — all isotopologue predictions below have zero new inputs.
4. OBSERVED anchors: ω_e (cm⁻¹) H₂ 4401.21, D₂ 3115.50, HCl 2990.946, DCl 2145.163, CO 2169.813,
   ¹³CO 2121.42; B (cm⁻¹) CO 1.93128, HCl 10.5934, DCl 5.4488; R (Å) CO 1.1283, HCl 1.2746;
   atomic masses (u) standard NIST values; amu = 1.66053906660e-27 kg (unit bridge).

## Committed gates (before run)

- **P1 (native k):** minimise g(x) for the shared-seat well; compute d²E/dR² of E = g*·αℏc/R.
  REGISTERED PREDICTION: the well is scale-free (pure 1/R), so d²E/dR² < 0 everywhere — **no
  restoring stiffness exists in this class**; P1 then resolves OPEN with the missing closure named
  (the contact-saturation wall that would create the interior minimum). If instead a positive k
  emerges, gate: CO/HCl/H₂ stretch within 10%.
- **P2 (back-solved k, declared circular for ν, caps at C):** k_X = μ(2πcω_e)²; then MASS-ONLY
  isotopologue predictions with zero new inputs: DCl from HCl, D₂ from H₂, ¹³CO from CO —
  gate: |error| < 0.5% each.
- **P3 (rotation):** B = ℏ/(4πcI) with measured R — DECLARED IDENTITY (the measured R of these
  molecules is itself spectroscopic in origin; the loop is closed by construction). Reported for
  the record, earns nothing.
- **P4 (novel, mass-only):** B(DCl) predicted from B(HCl)×μ-ratio — gate |error| < 1%.
- **P3-unification:** one winding quantiser for all channels — NOT demonstrable in this run;
  resolves OPEN with owner PPT06/APS04 (+ FLM14 rotation DOF as the live door). Declared now.

## Pre-Run Commitments — CH07

- Prompt completion target: D (native vib chain expected OPEN; mass-scaling predictions earned)
- Physics class hoped: honest mix — OPEN (P1), CONVERGENCE (P2 shifts), IDENTITY (P3)
- CALIBRATED budget: 0 (the allowed stiffness scale is NOT used — a scale plugged to make ν land
  would be the exact circularity the firewall forbids)
- Forbidden: back-solving k and calling ν predicted; retro-widening; per-channel postulates.

## Run record

- Tool: `ch07_spectra.cpp` (`#include <sdt/laws.hpp>`) · build.bat (MSVC recipe)
- Output: `results.txt` = verbatim stdout.

---
---

# RUN 2 LOG (2026-07-06) — k from the rolling wall

**Executor under HUNTER protocol for J. C. Harvey, Melbourne. Everything in this section was
written BEFORE one line of run-2 tool code existed (ADJ-before-code, clause 1).**

## R2·Phase 0 — base mining (extracts recorded with paths, per spec table)

| # | Source (path) | Extract |
|---|---|---|
| 0.1 | `Investigations/16_Chemistry_and_Molecular_Bonding/CH07_Molecular_Spectra_Vibration_and_Rotation/ch07_spectra.cpp` + `results.txt` + `RUN_LOG.md` | Shared-seat minimiser g(x) = 1 + 1/(2x) − 4/√(¼+x²), grid x ∈ [0.02, 2.0] step 1e-5 → **g\* = −4.19615 at x\* = 0.2887** (note: the grid value is the 5-dp print of the machinery double; the analytic identity of the same minimum is g\* = 1 − 3√3 = −4.196152423 at x\* = 1/(2√3) = 0.288675 — recorded as a cross-check, the GRID machinery is the anchor). d²E/dR² at Re = −4.751×10³ N/m. OBSERVED anchor block: ω_e (cm⁻¹) H₂ 4401.21, D₂ 3115.50, HCl 2990.946, DCl 2145.163, CO 2169.813, ¹³CO 2121.42; B (cm⁻¹) CO 1.93128, HCl 10.5934, DCl 5.4488; amu = 1.66053906660e-27 kg. §G.1 faith ledger travels: rotational ladder step + E = ℏω bridge are ASSERTED — caps travel with every cm⁻¹ conversion below. **CP-1 committed: reproduce g\* with the reused machinery to \|Δg\*\| ≤ 1e-6 before any wall work; also reproduce the −4.75×10³ N/m row.** |
| 0.2 | `Investigations/05_Nuclear_Physics/NP17_Nuclear_Packing_Order_Discovery/` | E = Σ±αℏc/r point-source machinery; NP17 bond D = 2R_p + R_p/3 = 1.9633 fm; deuteron 2.200 vs 2.224 MeV (−1.06%). Rule honoured: **the wall ADDS to this well; it never replaces or re-scales it** (g\* frozen). |
| 0.3 | `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/NP10_VERDICT.md` + `np10_contact_wall.cpp` + `np10_contact_wall_results.txt` | Enhancement identity E_exact/E_point = ρ(π−2ρ) ≥ 1 for ρ > 0.444 (radial occlusion wall KILLED). **D1 fence (regression anchors for this run): ℏ²/2m_e = 3.80998 eV·Å²; H₂ R_min = 0.5790 Å (−21.9%), depth −45.49 eV, k = 2697 N/m (+369%).** Face-T ladder: d ×1 → 2.200 (−1.06%), t ×2 → 8.557 (+0.88%), α ×6 → 26.721 (−5.57%); required α boost ×6.354. Cage-rule deuteron shift +0.23%. CP-2 sentence: see D-A3 below. |
| 0.4 | `Investigations/16_Chemistry_and_Molecular_Bonding/CH02_Ionic_and_Metallic_Bonding_from_Electropause_Transfer/ch02_ionic_metallic.cpp` + `results.txt` + `CH02_VERDICT.md` + `ch02_r2_isoelectronic_results.txt` | Evjen expanding-cubes sum, **M = 1.747574** (pure geometry, reused AS-IS); NaCl r₀ = 2.820 Å → 861.0 vs 787 kJ/mol (+9.4%); KCl r₀ = 3.146 Å → 771.8 vs 715 (+7.9%); MgO r₀ = 2.106 Å → 4611.6 vs 3791 (+21.6%). **CH02-R2 SHAPE CONSTRAINT (required reproduction target, REPORT row here): B₀ rises ×3.44 / ×3.70 / ×3.22 (NaF→MgO, KF→CaO, KCl→CaS) AND the z²-deconvolved wall exponent FALLS 6.98→4.51, 7.96→5.22, 8.61→5.09.** |
| 0.5 | `Investigations/12_Condensed_Matter_Physics/CM01.../CM05...` | Consulted: their earned stiffness is lattice RELAY stiffness (c_s, ionic mass M dependence — phonon channel); no earned molecular roll-cost or seat-compliance number exists there — judged irrelevant to W(R) (this is the one required line). |
| 0.6 | `Investigations/FARMER_PASS_2026-07-03.md` §8 | Movement triad PASS/BECOME/PRESS; "pressure itself is movement that cannot move"; roll (desynchronised wakes, frustration surplus) vs mesh (cadence-locked, movement saved); **nuclear-transmission amendment: force nuclear, compliance electronic** (shell = gearbox; every rotor defends with its own wake, nuclear rotor dominates when present); Ne/Na⁺/Mg²⁺ isoelectronic decidable (executed as CH02-R2 Phase A → the shape constraint in 0.4). The refinement text is the authority. |

## ADJ-R2-1 (committed before tool code; supersedes nothing in run 1)

**(a) Tool class:** Python (`ch07_r2_rolling_wall.py`), run with PYTHONIOENCODING=utf-8;
`results_run2.txt` = teed stdout; **exit 0 = ran to completion** (verdicts are printed lines,
per R2 clause 7, superseding run-1's exit-1 convention). Engine constants are transcribed BY
VALUE from `Engine/include/sdt/laws.hpp` `measured::` / `coulomb_identity::` (cited in the tool
header, values printed at start); no local re-derivation, no new constants. ASCII-only output
(Windows tee corruption guard).

**(b) Candidate wall constructions (the look-elsewhere budget — ALL declared here, ALL will be
evaluated and printed; NONE selected because it lands; NOTHING fitted to k = 575 N/m or
Re = 0.7414 Å):** every candidate is E_tot(R) = g(x)·αℏc/R + W, jointly minimised over (R, x)
with the run-1 g(x) frozen. Seat geometry: 2 seats at radius xR on the perpendicular bisector;
p–e seat distance s = u(x)·R, u = √(¼+x²); e–e gap = 2xR.

- **W-1 (PRIMARY):** W = Σ_seats ℏ²/(2m_e s²) = 2·ℏ²/(2m_e u²R²). Coefficient = seat count 2
  (structural). This IS the NP10 D1 fence form — the only candidate carrying an earned base
  label. **Primary-status selection rule (stated independent of the gates): it is the one
  candidate with an earned base label; the rest are structural enumerations.** Regression
  anchors: R_min 0.5790 Å, k 2697 N/m, depth −45.49 eV (NP10 D1).
- **W-2a / W-2b:** W-1 × (1/4) and W-1 × 4 — the W+1 = 4 shell-gearbox ratio (FLM07 1:4 void
  gearing). The gearing DIRECTION is not derivable from the base → both enumerated, both
  printed (they count double in the look-elsewhere budget).
- **W-3:** W = ℏ²/(2m_e (2xR)²) — ONE rolling interface between the two seat wings (interface
  count 1; compliance length = e–e gap).
- **W-4:** W = Σ_seats ℏ²/(2m_e (2πs)²) — compliance length = the seat-tour circumference
  (FLM14 tour reading; 2π geometry), seat count 2.
- **W-5:** W = (ℏ²/2m_e a₀²)·exp(−R/a₀) — the exponential class with its range DERIVED from a
  native length (a₀, derivation basis); coefficient 1 (one rolling interface). No other exponential
  range is admissible (r_e and seat spacing variants would need R-dependent ranges — not
  exponentials — or circular Re input).

Look-elsewhere budget: 6 evaluated constructions. Committed expectation (registered before
numbers): W-1 is expected to reproduce the D1 fence — G-A1 near-PASS/PASS, **G-A2 FAIL
(+369%)**; the others are expected worse. An honest all-FAIL on G-A2 is the likely landing.

**(c) Diagnostic locus sweep (NOT a candidate, NO parameter is promoted):** for the W-1 form,
scale the wall coefficient by λ over a log range and trace (R_min(λ), k(λ)). Scaling theorem
(from E = a(x)/R + λβ·f(x)/R²: x̂ is λ-invariant, R_min ∝ λ, k ∝ λ⁻³): **k·R_min³ is a class
invariant.** The sweep reports whether the committed gate box (R_min ∈ [0.556, 0.927] Å,
k ∈ [431, 719] N/m) intersects the class locus at ANY coefficient — a fence for future
derivations, exactly as D1 fenced the scale. If a required-multiplier band exists, any named
structural constants inside it are LISTED with a numerology/look-elsewhere caveat and NOT
promoted (single-number coincidence discipline).

**(d) The known trap — WELL DEPTH (declared before any curvature number is trusted):** the
bare run-1 well at Re is g\*·αℏc/Re = **−81.5 eV = ×17.2 the measured D_e(H₂) = 4.75 eV and
×2.55 the measured total electronic binding 31.95 eV** (NP10 §G item 5). Mandatory prints
(TRAP-4): bare depth at Re; E_tot(R_min) per candidate vs 4.75 eV; and the depth-pins-curvature
analysis — for any power-law wall B/Rⁿ at fixed x on this well, k(min) = (n−1)·|g(x)|αℏc/R\*³,
so the ×17 depth surplus converts directly into a curvature surplus. **If the depth mismatch
structurally blocks G-A1∧G-A2 for the whole declared class, that finding IS the run's product
and is scored as an honest FAIL — no re-scaling of the well (rule 0.2), no coefficient
invented to dodge it.**

**(e) Scoring (committed):** per candidate, **G-A1** interior minimum with R_min within ±25%
of 0.7414 Å; **G-A2** k = d²E_tot/dR² at R_min within ±25% of 575 N/m. G-B conjunction = (i)
G-A2 ∧ (ii) NaCl inside ±5% of 787 kJ/mol AND KCl moved toward 715 ∧ (iii) d/t/α shifts each
<5%. **G-B legs are run for W-1 (primary) regardless of the G-A outcome** — labelled REPORT if
(i) already failed (the conjunction is then dead by definition; the legs inform ROOT-WALL):
- **(ii) ionic leg**, Evjen machinery reused as-is (M recomputed as regression). Two declared
  transcriptions, both printed, neither selected post hoc: **V-ion-A** — W fires per unlike
  nearest-neighbour rolling contact, compliance length = contact separation r₀, coefficient 1
  per contact, 6 contacts per formula unit (rocksalt); **V-ion-B** — per-ion seat compliance,
  W = ℏ²/2m_e·(1/r₊² + 1/r₋²) per NN contact with Shannon 6-coord radii (measured anchors,
  data-boundary units; Na⁺ 1.02, Cl⁻ 1.81, K⁺ 1.38, Mg²⁺ 0.72, O²⁻ 1.40 Å). MgO = mandatory
  REPORT column.
- **(iii) nuclear leg** under the D-A4 domain rule (below), evaluated at the NP10/NP17
  geometries (Face-T machinery replicated as regression) — PLUS the mandatory counterfactual
  print: W-1 wrongly applied to the nuclear seat distances, to show the domain rule is
  load-bearing and not decorative.
- **CH02-R2 shape constraint** as a REPORT row: the model's own B₀ (from d²U/dr² at the
  model's own equilibrium) for NaF→MgO vs the measured ×3.44 rise, and the wall exponent of
  the class (n = 2, fixed, Z-blind) vs the measured fall 6.98→4.51.
- **Phase C** (report-only, sign scored): E''' at R_min → Morse mapping → ωₑχₑ sign
  (pre-committed: > 0) and ratio ωₑχₑ/ωₑ vs 0.0276 (REPORT); ω_e from derived k via √(k/μ) vs
  4401.2 cm⁻¹ (REPORT; E = ℏω bridge cap travels).
- **Phase D** (regression gate, non-optional): mass-only isotope transfers rerun with the wall
  in place; W carries m_e only (no nuclear mass) → k isotope-invariant; gates <0.5% each
  against anchors DCl −0.002%, D₂ −0.070%, ¹³CO +0.001%.

**(f) Numerics:** joint minimiser replicates NP10 D1's grids for the regression anchor
(x ∈ [0.02, 5] step 2e-4; R ∈ [0.06, 4] step 1e-3, local refine 5e-5; k by central second
difference, h = 1.5e-3 Å); derivative rows (E''') use a locally refined x-scan (declared
finer-numerics adjustment) and a 5-point stencil. Regression tolerances: CP-1 |Δg\*| ≤ 1e-6;
D1 row |ΔR_min| ≤ 0.002 Å, |Δk|/k ≤ 1%; Evjen M = 1.747574 to 6 dp; Face-T ladder to ±0.01 MeV.

## Derivation obligations (D-A1…D-A4, written before any evaluation)

**D-A1 (form + mechanism sentence, W-1 primary):** W = Σ_seats ℏ²/(2m_e s²), s = u(x)R.
*What rolls:* the two proton rotor+wake systems — at ångström separation they share NO cadence
lock (the nuclear lock engages at fm), so pressed together their wakes roll across each other
(refinement 8: roll = repulsion = frustration surplus at the interface). *What is meshed:* each
electron seat with its own core's cadence — the shared tour that binds (the run-1 well g\*).
*What movement is frustrated:* the seat's residence movement — held at compliance length s from
the core while the interface closes, its tour demands movement that compression denies a path;
PRESS mode, "movement that cannot move," and the budget price of movement confined to length s
is ℏ²/(2m_e s²) (FLM12 confinement reading of Law IV/V). Depth tracks the cores (both press —
force nuclear); the length that bends is electronic (m_e, s = uR — compliance electronic).

**D-A2 (constants traced):** ℏ, m_e, a₀, α, c — derivation basis (`laws.hpp measured::`); αℏc =
`coulomb_identity::k_e_e2` (engine class-F identity, declared as in run 1); seat count 2, u(x),
2xR — run-1 geometry (earned); W+1 = 4 (FLM07 gearing, earned label); 2π (geometry); Shannon
radii (OBSERVED anchors, ionic leg only). **Fitted-parameter count: ZERO.** The λ-sweep is a
diagnostic, not a parameter.

**D-A3 = CP-2 (not-occlusion sentence):** W is not radial occlusion in disguise: it contains no
solid angle, no R̂, no shadow/deficit-surplus split — it is a Law-V/FLM12 movement-budget cost
paid in ℏ²/(2m_e·length²), a resource the occlusion ledger does not possess; the Face-R kill
identity ρ(π−2ρ) ≥ 1 is a statement about solid-angle energies and does not touch this term.

**D-A4 (roll/mesh domain rule — stated before any nuclear number is seen):** W fires at rolling
interfaces **between core rotor+wake systems that do not share a cadence lock**: two H atoms at
Å separation (no nuclear tour spans them), two closed-shell ions in lattice contact. W does
**not** fire inside a single cadence-locked tour: a bound nucleus (d/t/α) is ONE (Z−1)!-tour
lock — its interior is meshed, and mesh = movement saved, not frustrated (refinement 8). Declared
consequence for Phase B(iii): W contributes 0 inside d/t/α, so the Face-T ladder must survive
unshifted; the counterfactual (W applied to fm-scale seat distances) is printed to show the rule
carries real load. This rule was fixed HERE, before the nuclear leg ran.

## R2·Pre-Run Commitments — CH07 RUN 2 (k from the rolling wall)

- Prompt completion target: B (all gates scored honestly; FAIL-heavy landing expected)
- Physics class hoped: NATIVE (wall) — honest fallbacks CONVERGENCE (W-1 is form-degenerate
  with the rival zero-point term — **pre-declared: even a full G-A/G-B PASS caps this W-class
  at CONVERGENCE by delete-test**), OPEN (no interior minimum derivable), KILLED (conjunction
  fails for the class)
- CALIBRATED budget: 0 fitted to k, Re, or any Phase-B target (D-A2)
- W(R) forms + constants + mechanism + domain rule: D-A1…D-A4 above, written before evaluation.
  Look-elsewhere: 6 constructions declared in ADJ-R2-1(b); locus sweep declared in (c)
- Committed gates: G-A1 R_min ±25% of 0.7414 Å · G-A2 k ±25% of 575 N/m · G-B = (i) ∧ (ii)
  NaCl inside ±5% of 787 AND KCl toward 715 ∧ (iii) d/t/α each <5% · G-C sign only ωₑχₑ > 0
  (ratio 0.0276 REPORT-ONLY) · G-D isotope regression <0.5% each (−0.002% / −0.070% / +0.001%)
- Checkpoints: CP-1 g\* to 1e-6 (+ the −4.75e3 N/m row) · CP-2 = D-A3 · D1 regression row ·
  Evjen M regression · Face-T ladder regression
- TRAP-1 (two-knob fit): no coefficient chosen to land; all candidates pre-declared; λ-sweep is
  explicitly not a candidate — **initialled JCH**
- TRAP-2 (occlusion in disguise): CP-2/D-A3 sentence on record — **initialled JCH**
- TRAP-3 (rival laundering): no exchange/Pauli machinery in-chain; W-1's FORM degeneracy with
  the rival zero-point term is pre-declared with the CONVERGENCE cap — **initialled JCH**
- TRAP-4 (depth blindness): depth columns mandatory per ADJ-R2-1(d) — **initialled JCH**
- TRAP-5 (stale binaries): tool is Python (no exe); results_run2.txt regenerated by the cited
  run; run-1 artifacts untouched — **initialled JCH**
- Forbidden: widening any gate; per-target constants; re-tuning W between fields; radial
  occlusion in disguise; rival machinery in-chain; back-solving anything from a gated target;
  "charge radius"; G/M/GM; borrowed units.

**§G.2 mirror (at start):** What am I accepting on faith? — the ℏ²/2m_e confinement PRICE of
frustrated residence (FLM12 reading, underived here); the D-A4 lock/no-lock dichotomy; the
structural coefficients of W-2/3/4/5. All flagged; the first two are the run's §G ledger items.
Am I letting an oppositional standpoint police the datastream? — the gates are measured anchors
(0.7414 Å, 575 N/m, 787 kJ/mol, ladder MeV); no rival axiom sits in any kill condition.
