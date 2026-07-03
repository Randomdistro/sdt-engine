# VERDICT — GOM13: Occlusion-Altitude Cavendish (pre-flight set, owed to E104)

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER discipline).
> **Tool:** `gom13_preflight.cpp` (new; commitments in RUN_LOG.md written first).
> **Run:** exit 0. **Evidence:** `results.txt` (real stdout).

## Dual verdict

- **Prompt completion: B** — the full gate-zero / pre-flight prediction set the PROMPT
  and E104 §8 demand is delivered (κ, δ(h), saturation curve, make-or-break number).
  No hardware, no flight claims.
- **Physics class: KILLED (the flagship sin-dip altitude law, pre-flight, by an
  OBSERVED anchor) · NATIVE-but-conditional (κ = 1) · OPEN (the E104 correlation
  test at the surviving signal level, which is unreachable)**
- **Earned vs owed: the honest pre-flight answer is earned — and it is "do not fly
  as designed." E104's engine-target block is now filled; the experiment spec itself
  needs rework before any hardware step.**

## The pre-flight prediction set (real numbers, `results.txt`)

**(a) κ — the shared-P_eff coupling.** Both channels are Law III,
F = (π/4)·P_eff·R₁²R₂²/r², linear in P_eff ⟹ κ ≡ ∂lnF_Cas/∂lnP_eff ÷
∂lnF_Cav/∂lnP_eff = **1 exactly** (SDT) vs **0** (SM). P_eff = 5.2252e31 Pa, printed
with its verbatim laws.hpp provenance ("risk_flag: coefficient calibrated", class E)
— disclosed; κ is a ratio, so the class-E magnitude cancels out of it. What κ = 1
DOES depend on is EMC03's premise that the Casimir channel is occlusion-sourced;
if false, κ = 0 and the correlation reads null. This is the cleanest piece of the
investigation and survives.

**(b) δ(h), 0–40 km — the fork between two committed models (they differ by 10⁵):**

| h (km) | G1: sin(arccos(R/(R+h))) | G2: mass-proportional (barometric column) |
|---|---|---|
| 0.5 | 1.25e-2 | 8.27e-7 |
| 8.85 (Everest) | 5.26e-2 | 2.77e-7 |
| 40 | **1.115e-1** | 4.70e-9 |

G2 (occlusion ∝ occluding mass, koppa-per-baryon × barometric column) lands at the
same order as the measured Bouguer effect of the air column (~4.4e-7 of g) —
consistent with existing gravimetry. G1 (occlusion = pure solid-angle opacity,
mass-independent) is the PROMPT's flagship +11%-at-40-km claim.

**(c) Near-contact saturation** g(x) = 2(1−√(1−x))/x, x = (R/r)²: table emitted;
limits verified (g→1 far-field, g→2 at contact; 7.2% deviation from 1/r² at two
radii separation). This term is altitude-independent and rides along on any flight
— it is the only near-term testable piece of the set.

**(d) Make-or-break: δ(h)·κ vs the committed noise floors.**
- G1: 1.12e-1 = 37× ABOVE the PROMPT's own 0.3%/bin floor — trivially measurable
  *if real*. But see (e): it is already excluded.
- G2: Δδ(0→40 km) = **8.78e-7** = 3,417× BELOW the 0.3%/bin floor and **11× below
  even a heroic 1e-5 lock-in floor**. Required fractional force sensitivity ~3e-7.
  **Committed wording applies: orders below reachable sensitivity.**

## The pre-flight kill (the PROMPT's own suggested check, executed)

The PROMPT §10 says: "re-examine the G record now for a correlation with lab
elevation; the first data point may already be sitting in the literature." Done:
G1 predicts elevated labs read the lab-mass force high by √(2h/R): **+1.97% at JILA
(Boulder, 1655 m), +2.34% at LANL (Los Alamos, 2231 m)** relative to sea-level labs.
The published record (HUST, UWash, BIPM, JILA, LANL) scatters by ~5e-4 total — and
JILA, the highest-precision high-altitude entry, reads **LOW** (−2.8e-4), not 2%
high. Predicted shift = 47× the entire inter-lab scatter, against a pre-committed
10× exclusion criterion. **The sin-dip geometric-opacity law is excluded by data
that already exist. KILLED pre-flight.**

The only escape is the PROMPT's own H1-FALSE branch (the torsion fibre's EM constant
rides the same ambient flux) — but on that branch the ratio θ = F/κ_fibre cancels
identically and **no altitude experiment can see anything either**. Both branches
printed; neither leaves a flyable altitude signal.

## Disposition

- E104 §8 engine targets: **delivered** (this folder, `results.txt`).
- Flagship altitude law (G1): **KILLED** by the existing G record (47× over criterion,
  wrong sign at JILA) — do not build hardware for it.
- Defensible mass-proportional law (G2): real physics scale (~9e-7, Bouguer-order)
  but **orders below any plausible lock-in floor** — the honest make-or-break answer.
- Surviving flyable content: the near-contact saturation curve (7.2% at 2 radii — a
  benchtop-scale test, no balloon needed) and κ = 1 as the conditional signature if
  a Casimir/Cavendish correlation platform is ever built for OTHER reasons.
- The three HTML decks in this folder (`OCCLUSION_EXPERIMENT_DECK.html`,
  `BALLOON_EXPANSION.html`, `SOFT_SATELLITE_CEILING.html`) predate this verdict and
  present the G1 curve as the expectation — they are now superseded by this
  pre-flight kill and should not be circulated without it.

## §D — Seven questions (on the flagship G1 kill)

1. **Why (exact mechanism)?** G1 (ΔF/F = sin(arccos(R/(R+h)))) predicts +1.97e-2 at
   JILA (1655 m) and +2.34e-2 at LANL (2231 m) relative to sea-level labs. The
   published G record scatters by ~5e-4 total and the highest-precision high lab
   (JILA) reads LOW (−2.8e-4): magnitude excluded at 47× the entire scatter (committed
   criterion was 10×), and the sign is wrong in the best pair. Number, sign, and
   magnitude all fail.
2. **Recoverable?** Not as a geometric-opacity law. The corrected form exists: G2,
   occlusion ∝ occluding mass (koppa_per_baryon × barometric column), which lands at
   8.8e-7 — consistent with the Bouguer anchor (~4.4e-7 of g) but 3,417× below the
   PROMPT's own 0.3%/bin floor and 11× below a heroic 1e-5 lock-in. The LAW recovers;
   the EXPERIMENT does not.
3. **What did the target fail to account for?** That Law III itself makes occlusion
   scale with the occluder's cross-section budget (the R² terms — i.e. with mass),
   not with blocked solid angle alone; and that ground Cavendish labs already span
   0–2.2 km of the predicted curve, so the "unflown" experiment had, in effect,
   already been flown.
4. **Errored premise?** "The Earth occludes its full solid angle as an opaque disk
   regardless of column mass" — i.e. occlusion saturation at planetary scale was
   assumed, not derived. The un-derived piece is the occlusion transfer function
   (how much flux a given mass column blocks).
5. **Correcting freedom?** The per-mass occlusion coefficient. Under Law III scaling
   it is koppa_per_baryon-proportional (G2) — that choice is forced by the theory's
   own force law, not tuned to the G record (it was anchored to Bouguer BEFORE the
   record comparison, see RUN_LOG order).
6. **Native or knob?** Native: G2 uses bridge::koppa_per_baryon (whitelist expression,
   provenance disclosed) and the measured barometric column. No fitted parameter; the
   number that comes out is unmeasurably small, and is reported as such rather than
   inflated.
7. **Cascade?** **Yes.** The assumed-saturation premise is the same unbuilt occlusion
   transfer function behind GD03's Level-4 wake failure and GD04's calibrated
   κ_per_baryon: root **OCCLUSION-MECHANISM**. Paying that root (deriving the
   transfer/drag coefficient from lattice geometry, FLM10/GOM05-class) settles the
   G1-vs-G2 fork from first principles instead of by anchor.

**Recovery grade: PARTIAL** — the corrected law (G2) falls out natively and survives
the observed anchors, so the premise error is paid; but the folder's deliverable (a
flyable altitude signal) has **NO RECOVERY**: both H1 branches close it.

---

**Prompt completion B · Physics class KILLED (G1 flagship altitude law, by OBSERVED
G-record anchor) / NATIVE-conditional (κ = 1) / OPEN (E104 correlation at the
unreachable G2 level) · Recovery PARTIAL · Cascade root OCCLUSION-MECHANISM.**
