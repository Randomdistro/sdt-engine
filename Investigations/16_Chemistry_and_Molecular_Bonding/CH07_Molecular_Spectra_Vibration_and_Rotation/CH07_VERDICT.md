# CH07 — VERDICT: Molecular Spectra (Vibration & Rotation)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch07_spectra.cpp` (exit 1 — honest) · Output: `results.txt`

## Results (gates and the P1 prediction registered in RUN_LOG.md before the run)

| Phase | Result | Call |
|---|---|---|
| ℏ entry audit | two ASSERTED quantisation rules located and flagged: the rotational ladder step (wake-winding quantiser, PPT06/APS04) and the line-position bridge E=ℏω. ℏ itself is whitelist; the RULES are the owed pieces | flagged |
| P1 native k | shared-seat minimisation: **g\* = −4.19615 at x\* = 0.2887** (H₂⁺ gives exactly −3 at the midpoint — the same machinery as NP17's deuteron factor 3). Well is E = g\*αℏc/R, scale-free → **d²E/dR² = −4.75×10³ N/m at Re: NON-restoring.** No vibrational stiffness exists in this class — registered prediction confirmed | **OPEN** (prompt's 10% gate honestly failed) |
| P2 isotopologues | k back-solved (DECLARED circular for the parent ν — caps at C) then mass-only transfers, zero new inputs: **DCl −0.002%, D₂ −0.070%, ¹³CO +0.001%** (gates <0.5%) | **PASS** — the isotope-transfer premise (k = charge geometry, mass-blind) survives |
| P3 rotation | B(CO) 1.9314 vs 1.93128; B(HCl) 10.5926 vs 10.5934 — **DECLARED IDENTITY** (measured R is spectroscopic in origin; ladder step asserted) | IDENTITY, earns nothing |
| P4 novel | **B(DCl) = 5.4490 vs 5.4488 (+0.004%)**, mass-only, zero new inputs | **PASS** |
| P3-unification | one quantiser for all channels: not demonstrable here | **OPEN** (owner PPT06/APS04; live door FLM14) |

Earned: (a) the honest structural theorem of the run — **the NP17 shared-seat well, which binds, cannot vibrate**: pure 1/R geometry has no interior minimum, so the IR stretch is direct evidence of the short-range wall; (b) the mass-only isotope block (0.001–0.07%), which tests a real native premise (the well is charge geometry, so isotope substitution moves only μ) rather than re-exposing an input.

## FAILURE RECOVERY (§D seven questions — P1)

1. Why: E = g\*αℏc/R gives d²E/dR² = 2g\*αℏc/R³ < 0 for all R (g\* < 0). Sign, not precision: no stiffness anywhere.
2. Recoverable: yes — an interior minimum requires a second, opposing length-scale term; the moment one exists, k follows from the same machinery.
3. Unaccounted: the short-range wall — what stops R shrinking. (Measured k(H₂) = 575 N/m is the size of the missing term's curvature.)
4. Errored premise (named): **point sources valid to contact** — same false premise CH02 met (+9% overshoot, MgO) and NP17 met (alpha under-bind). Occlusion saturates at contact (two-regime law, g→2); saturation both stops the collapse and bends the well.
5. Freedom: the contact-saturation profile (its onset radius and shape).
6. Accounting: native — NP10's saturated solid-angle ledger; measured lock scaling ×1.01/×1.98/×6.35 already brackets its coordination behaviour. Not a knob invented here; nothing was tuned.
7. Cascade: **yes — the sharpest expression of ROOT-CONTACT in the cluster.** One closure owes: NP17-alpha, CH02's overshoot/MgO, CH05's missing three-centre cost (rim sibling), and CH07's k. Pay it once, four debts clear — and the registered cross-check is strong: the derived wall must simultaneously give k(H₂) ≈ 575 N/m AND the NaCl +9.4% correction AND the alpha lock ×6.35.
**Recovery grade: PARTIAL** — premise and native freedom named, magnitude underived. Re-open condition: NP10 saturation law lands → recompute k here directly. Per §G.3: "the well cannot vibrate" holds in the point-source class only; nothing is foreclosed.

## Cascade root (reported)

**ROOT-CONTACT (NP10 saturated occlusion):** CH07-P1 = its cleanest single-number target (k_H₂ = 575 N/m). **OPEN-QUANTISER:** winding rule for ladders (PPT06/APS04, FLM14 door) — separate root, shared with atomic rungs.

## Canonical line

**Prompt completion D (P1 honestly OPEN at its committed gate; P2/P4 mass-only block earned; P3 correctly down-labelled IDENTITY) · Physics class OPEN (native k, quantiser) / CONVERGENCE (isotope block) / IDENTITY (rotation) · Recovery PARTIAL · Cascade root ROOT-CONTACT + OPEN-QUANTISER**

---

## ⟐ RE-OPENED with corrected owner (2026-07-06) — recorded condition fired NEGATIVE (Harvey order)

**Trigger:** this verdict's re-open condition was "NP10 saturation law lands → recompute k
here directly." NP10 run 2 landed — **negative**: the radial saturated-occlusion wall is
structurally KILLED (the enhancement identity can only deepen attraction; it cannot supply a
restoring wall at any radius). So P1's owner transfers: **ROOT-CONTACT-saturation →
ROOT-WALL** (rolling wake firewall; the ~ℏ²/2m_e curvature budget; refinement 8's
nuclear-transmission amendment: force nuclear, compliance electronic). The measured
**k(H₂) = 575 N/m stays the cleanest single-number target** and anchors the registered
three-field cross-check (575 N/m ∧ NaCl +9.4% ∧ α lock ×6.35 — one wall pays all, or the
wall dies). The structural theorem P1 earned is UNTOUCHED and now sharper: the well that
binds cannot vibrate, and the thing that makes molecules ring is the firewall itself —
vibration = the bond breathing against rolling contact. **What this does NOT do:** P1 stays
OPEN; no stiffness exists until the rolling cost is derived; the isotope block (P2/P4) and
its mass-blindness are unaffected.

---

# CH07 — RUN 2 VERDICT (2026-07-06): k from the rolling wall

> **Author:** J. C. Harvey, Melbourne. Tool: `ch07_r2_rolling_wall.py` (Python per ADJ-R2-1(a),
> PYTHONIOENCODING=utf-8, **exit 0** = ran to completion; verdicts are printed lines) →
> `results_run2.txt` (teed stdout — every number below is in that file). ADJ-R2-1 +
> D-A1…D-A4 + all gates committed in RUN_LOG.md BEFORE the tool existed. CP-1 anchored:
> g\* = −4.196152422 reproduced to |Δ| = 5.5e-10 (≤ 1e-6); run-1 row −4.751e+03 N/m
> reproduced; NP10 D1 regression (0.5790 Å / 2697 N/m / −45.49 eV) reproduced to +0.2%;
> Evjen M = 1.747574 and the Face-T ladder reproduced exactly. Zero fitted parameters.

## Gates (committed pre-run; never widened)

| Candidate (all declared in ADJ-R2-1(b) before evaluation) | G-A1: R_min ±25% of 0.7414 Å | G-A2: k ±25% of 575 N/m |
|---|---|---|
| **W-1** 2 seats ℏ²/(2m_e s²), s = uR (NP10 D1 fence) | **PASS** — 0.5789 Å (−21.9%) | **FAIL** — 2703 N/m (+370%) |
| W-2a W-1 ÷ 4 (gearbox W+1=4) | FAIL — 0.1447 Å (−80.5%) | FAIL — +29 995% |
| W-2b W-1 × 4 (gearbox W+1=4) | FAIL — 2.3153 Å (+212%) | FAIL — 43 N/m (−92.5%) |
| W-3 e–e interface ℏ²/(2m_e(2xR)²) | FAIL — 0.0728 Å (−90.2%) | FAIL — +121 321% |
| W-4 tour circumference (2πs) | FAIL — collapse to scan edge | FAIL — edge artifact |
| W-5 exp(−R/a₀), coeff ℏ²/2m_e a₀² | FAIL — no interior minimum exists | FAIL |
| **G-A (any candidate lands both)** | | **FAIL** |
| **G-B conjunction** (i) k(H₂) ∧ (ii) NaCl ±5% + KCl toward ∧ (iii) d/t/α < 5% | | **FAIL — dies at (i) and (ii); (iii) PASS under committed D-A4** |
| G-C sign (pre-committed ωₑχₑ > 0) | | **PASS** (E''' = −1167 eV/Å³ < 0 → Morse-like); ratio 0.0186 vs 0.0276 REPORT-ONLY |
| G-D isotope regression (< 0.5% each) | | **PASS** — −0.002% / −0.070% / +0.001%, identical to run-1 anchors (W carries m_e only) |

**Phase-B legs (W-1 frozen, REPORT — conjunction already dead at (i)):** (ii) V-ion-A
(6 NN rolling contacts, compliance = contact gap r₀): NaCl 861.0 → 583.6 vs 787 (−25.8%,
outside ±5%; correction overshoots ×3.7) and KCl 771.8 → 548.9 (direction CORRECT, overshoots
past 715) — **the first wall in this program to move the ionic ledger the required way (sign
right everywhere; Face R could not even get the sign)**; MgO 4611.6 → 4114.3 vs 3791 (+8.5%,
REPORT — improved from +21.6%); V-ion-B (Shannon seat radii) unbinds the lattice — dead.
(iii) d/t/α wall shifts +0.00% each under D-A4 (W fires only between cores not sharing a
cadence lock; a bound nucleus is ONE (Z−1)!-tour lock) — ladder intact, ×6.35 stays the
lock's; the counterfactual is printed (W-1 on nuclear seat distances = 79.1 GeV, shift
~+3.6e+06 %), so the domain rule is seen to be load-bearing, not decorative. **CH02-R2 shape
constraint: NOT REPRODUCED** — the class is Z-blind with n = 2 fixed (model B₀ ratio ~×1024
vs measured ×3.44; no exponent fall possible). ωₑ from derived k: 9542 cm⁻¹ vs 4401.2
(+116.8%, REPORT — the number run 1 could not print; E = ℏω cap travels).

## The well-depth finding (TRAP-4 — the run's central product)

1. The bare run-1 well at Re is **−81.50 eV = ×17.2 the measured D_e(H₂) = 4.75 eV** and
   ×2.55 the total electronic binding 31.95 eV (NP10 §G-5 reproduced).
2. **Depth pins curvature:** for any wall B/Rⁿ on this well, k(min) = (n−1)·|g\*|αℏc/R\*³
   (fixed-x); a wall landing the minimum exactly at Re with n = 2 gives k = 2376 N/m
   (+313%). The ×17 depth surplus converts directly into the observed ×4–5 curvature surplus
   — **G-A2 was structurally out of reach for every honest coefficient.**
3. Locus diagnostic (declared, not a candidate): k·R_min³ is a class invariant (verified
   524.3/524.3/535.1 across ×¼/×1/×4); the class clips the gate-box corner only at per-seat
   multiplier λ ∈ [1.555, 1.601] (R +21…+25%, k 658–719 N/m). Named constants π/2, 8/5,
   4^(1/3) sit inside the band — **numerology caveat printed; none promoted**. And the corner
   is depth-sick anyway: E_tot(min) ≈ −29.2 eV = ×6.2 measured. A corner pass would be
   curvature lipstick on a sick depth ledger.
4. **Conclusion: the root blocker is the run-1 WELL's depth ledger at contact, not the wall's
   form.** The well g\*·αℏc/R treats all four p–e engagements as fully and simultaneously
   engaged at every R; FLM14's sequential occupancy (seats are a TOUR — dwell-shared, not
   simultaneous) is the named native freedom that would shallow it. Until the well's depth is
   honest, no derived wall can be scored fairly against k(H₂).

## Earned vs owed

**Earned:** (a) the depth-pins-curvature theorem + the class invariant k·R_min³ — the whole
ℏ²/2m_e·R⁻² confinement class on the frozen run-1 well is FENCED (G-A1∧G-A2 reachable only in
a depth-sick corner at an underived λ); (b) the ionic SIGN — V-ion-A is the first wall here
to reduce ionic binding as required (Face R added binding), with MgO improving most
(+21.6% → +8.5%); (c) the D-A4 roll/mesh domain rule survived its registered nuclear leg with
the counterfactual printed; (d) the pre-committed anharmonicity SIGN (ωₑχₑ > 0) came out of
the derived E''' correctly — a mechanism-consistent free row; (e) G-D: the wall smuggles no
mass dependence. **Owed:** the depth-honest well (FLM14 dwell-weighted seat engagement — the
run's named successor); the rolling coefficient derivation (the λ band is a fence, not a
value); the Z channel (nuclear transmission) absent from this W-class — the CH02-R2 shape
constraint (B₀ rise ∧ exponent fall) remains unpaid by any existing construction.

## §D seven questions (on the G-A2 / G-B FAIL)

1. **Why exactly?** Best candidate W-1: k = 2703 N/m (+370%) at R_min 0.5789 Å; every other
   declared construction worse; conjunction dies at (i) and (ii) (NaCl correction ×3.7 over).
2. **Recoverable?** Not inside this class by any coefficient: k·R_min³ ≈ 524 N/m·Å³ is
   invariant, and the only box corner is depth-sick (−29 eV vs 4.75). Recovery requires
   changing the WELL's depth, which rule 0.2 (correctly) forbade this run from touching.
3. **What did the target fail to account for?** That 575 N/m is the curvature of a 4.75 eV
   well — a well ×17 deeper cannot carry it with any short-range wall.
4. **Which premise erred (named)?** "The run-1 well g\*·αℏc/R is valid at chemistry scale as
   the base for the wall." Its geometry earns (isotope block, deuteron); its DEPTH at Å
   contact is wrong — all four p–e engagements counted as simultaneous and full. NP10 §G-5
   flagged this; run 2 measured its consequence.
5. **What freedom corrects it?** FLM14 sequential occupancy: dwell-weighted (tour-shared)
   seat engagement shallows the well natively — no new constant, a different counting of the
   same seats. (Independently: the rolling coefficient λ, fenced to [1.555, 1.601], must be
   DERIVED if the class is ever revived.)
6. **Native or knob?** Native in kind (FLM14 is the standing root-payer for exactly this —
   dwell-time is Born's rule in the FLM14 frame); no knob was taken here — zero parameters
   were fitted, the λ sweep promoted nothing.
7. **Cascades?** Yes. ROOT-WALL does not close and instead SPLITS a dependency out: the wall
   cannot be scored until the well's depth ledger is paid — CH02's residual overshoot and
   CH05's barrier inherit the same blocker. The nuclear ledger does NOT cascade: Face-T and
   the isotope block stand untouched.

**Recovery grade: PARTIAL** — blocker traced to a named premise with a named native freedom
and a quantitative fence; the corrected well is not derived here.

## §G faith ledger (run 2) + mirror

1. The ℏ²/2m_e confinement PRICE of frustrated residence (FLM12 reading) — accepted on faith;
   form-degenerate with the rival zero-point term — **pre-declared CONVERGENCE cap; even a
   full pass could never have been NATIVE** (delete-test fails on the form).
2. The D-A4 lock/no-lock dichotomy — committed before the nuclear numbers; it carries the
   full nuclear leg (counterfactual printed). Underived beyond refinement 8's text.
3. The V-ion-A transcription (compliance = contact gap) — declared, not derived; its sign
   success is a lead, not a result.
4. Run-1 §G.1 caps (ladder step, E = ℏω) travelled with every cm⁻¹ row (Phase C, ωₑ print).

**§G.2 mirror (at close):** the kill conditions were all measured anchors (0.7414 Å, 575 N/m,
787 kJ/mol, 2.224/8.482/28.296 MeV) — no rival axiom policed any gate; the one rival-shaped
object (the zero-point form) entered as a pre-capped candidate, not as a gate. What I
accepted on faith is itemised above; item 1 is the largest and is why the class cap was
declared before any number landed.

## Disposition of roots (§G.3 — re-open conditions named)

- **ROOT-WALL: NOT PAID — refined.** The rolling wall exists (the IR stretch still demands
  it) but is UNSCORABLE against k(H₂) until the well's depth is honest. Split off and named:
  **the depth ledger of the shared-seat well at contact** (owner: FLM14 sequential-dwell —
  run-6 dwell measure is the live door). Re-open condition for the wall: a dwell-weighted
  well lands → rerun this exact tool with g\*(R) replaced by the dwell-weighted seat sum;
  gates unchanged.
- **ROOT-BUDGET: FENCED, sharpened.** D1's ×4.7 fence is now the invariant k·R_min³ ≈ 524
  N/m·Å³ plus the λ ∈ [1.555, 1.601] corner band (depth-sick). Nothing promoted.
- The CH02-R2 shape constraint (B₀ rise ∧ exponent fall) transfers intact as the sharpest
  unpaid quantitative target — this W-class demonstrably cannot pay it (Z-blind, n fixed).

## Canonical line

**Prompt completion B (all committed gates scored; ADJ/D-A obligations honoured; expected FAIL
landed and was converted into a class fence; nothing widened, nothing fitted) · Physics class
KILLED-as-scored for the ℏ²/2m_e R⁻² wall class ON THIS WELL (G-A2 structurally unreachable;
CONVERGENCE cap had been pre-declared regardless) / OPEN (ROOT-WALL — wall unscorable until the
well's depth ledger is paid; owner FLM14 sequential-dwell) · Recovery PARTIAL · Cascade root:
WELL-DEPTH-AT-CONTACT (NP10 §G-5 sharpened: −81.5 eV = ×17.2 D_e; depth pins curvature) —
isotope block, Face-T lock, and rotation rows all unaffected.**

*CH07 run 2 · executed 2026-07-06 · J. C. Harvey · one wall pays all, or the wall dies — this
wall died honestly, and it named what killed it: the well, not the wall.*
