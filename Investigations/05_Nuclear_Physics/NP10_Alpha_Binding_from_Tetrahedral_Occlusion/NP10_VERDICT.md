# NP10 — VERDICT: Alpha Binding from Tetrahedral Geometry (NP17 premise)

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` only.
> Tool: `np10_alpha_binding.cpp` (MSVC exit 0) → `np10_results.txt` (redirected stdout).
> Premise: NP09 occlusion route dead (−97.3%); mechanism = NP17 shared-electron Coulomb well.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | All committed gates scored, no geometry fished, expected failure confirmed and *quantified* rather than papered over. |
| **Physics class** | **OPEN** (one new structural constraint EARNED; G2 re-verification; G4 DEGENERATE) | Pure shared-electron electrostatics under-binds the alpha 6.35×; the ratio test shows the missing lock term is coordination-dependent, not a common factor. |

## Numbers (all gates committed in RUN_LOG before coding)

| Gate | Result | Label |
|---|---|---|
| G1: B(α) from NP17-exact config (a = 2R_p) | 4.454 MeV vs 28.296 → **−84.3% FAIL → OPEN** | lock remainder R_lock = 23.842 MeV (84.3% of total) |
| G1b: D-spaced variant | 3.817 MeV (−86.5%) | same conclusion |
| G2: R_He = 2R_p = 1.6828 fm vs 1.6755 | **+0.44% PASS (1% blind)** | pre-existing engine result (`nuclear::R_He_predicted`, class C-flagged) — re-verified, NOT sold as new |
| G3: B_α/B_t = 3.336 | predictions 1.041 / 0.892 / 0.980 → **ALL FAIL (−69 to −73%)** | **the informative result** — see below |
| G4: μ_α = 0 | consistent via paired cancellation | DEGENERATE (declared pre-run) |
| G5: edge for 28.296 MeV electrostatically | 0.265 fm < 2R_p | UNPHYSICAL → remainder is real, not a spacing choice (reproduces NP17 inverse) |

## What is earned vs owed

**Earned — a new constraint on the lock term (the actual product of this run):**
The implied boost factors on pure shared-electron electrostatics are
**deuteron ×1.01 → triton ×1.98 → alpha ×6.35** (d: NP17's 2.200 vs 2.224; t: chain
p–e–p–e–p at D; α: NP17-exact tetrahedron). Because ALL committed ratio pairings fail at
~−70%, the missing "tetrahedral lock" is **NOT a common multiplicative factor** on the
electrostatic well — it **grows super-linearly with interleave/coordination number**
(≈1, 2, 6.35 for 1, 2, 3+ interlocked units). Any future lock derivation that produces a
flat per-bond boost is pre-falsified by this run. This sharpens NP17's "PENDING" from
"a remainder exists" to "a remainder with this scaling exists."

**Also earned:** the honest kill of the PROMPT's own Step-2 arithmetic (occlusion bond sums)
— executed under the corrected premise instead, per the 2026-07-03 note; and the G5
unphysical-inversion result showing no spacing choice rescues electrostatics.

**Owed (cascade root):**
- The tetrahedral-lock mechanism and magnitude (NP17-PENDING) — now with a quantitative
  target curve: it must supply 0.02, 4.2, 23.8 MeV for d, t, α respectively (and, via NP08,
  close the 0.379 MeV Hoyle barrier at A=12).
- The prompt's B(He-3) hierarchy row was not scored: it needs the electron-count asymmetry
  (He-3 = 3p + 1e, alternate grammar) whose geometry is part of the same pending import.

## Success criteria scoring (PROMPT §3)

- [ ] Total binding within 20% of 28.296 — **FAIL → OPEN** (−84.3%; remainder quantified)
- [x] R_He within 1% — PASS (+0.44%; pre-existing engine result re-verified)
- [~] μ_α = 0 explained — consistent but DEGENERATE
- [ ] B_α/B_triton ratio reproduced — **FAIL** (and the failure is the finding: lock is
  coordination-dependent)
- [x] Bond-energy consistency with the deuteron — yes at the deuteron (×1.01) and it is
  precisely the *breakdown* of that consistency at t and α that was measured here

## Stress-test self-audit

1. **Identity/circularity:** all energies computed from engine lengths + αℏc; measured
   28.296/8.482 (engine `measured::B_alpha`, `B_triton`) used as OBSERVED targets only.
2. **Fished factors:** zero. Geometries (4 configs) were committed in RUN_LOG before any
   energy was computed; no additional configurations were tried after seeing numbers.
3. **Dimensions:** MeV·fm/fm throughout; charges integer; no borrowed units.
4. **Cascade root:** NP17-PENDING lock magnitude. NP10 does not close it; it fences it in
   (scaling ≈ superlinear in interlock count, unreachable by spacing or common factor).

## §D Seven questions (HUNTER_PROTOCOL, on the G1/G3 FAILs)

1. **Why exactly?** Magnitude: pure shared-electron electrostatics gives 4.454 MeV vs 28.296 (−84.3%); and the α/t ratio fails at ~−70% in all committed pairings — the deficit is not uniform.
2. **Recoverable?** Not by spacing (G5: required edge 0.265 fm < 2R_p, unphysical) and not by a common factor (G3). Recovery requires a qualitatively new term, already named by NP17.
3. **What did the target fail to account for?** Whatever binds interlocked trefoils beyond point-charge electrostatics — the interlock/occlusion ("lock") contribution that grows with coordination.
4. **Which premise erred?** "Alpha binding = sum of pairwise shared-electron Coulomb wells at physical spacing." True for the deuteron (×1.01), increasingly false with interleave count (t ×1.98, α ×6.35).
5. **What freedom corrects it?** The tetrahedral-lock term. This run adds its constraint curve: it must supply ≈0.02 / 4.2 / 23.8 MeV for d / t / α — superlinear in interlock number.
6. **Native or knob?** Must be native (geometry of interleaved trefoils + occlusion); any flat per-bond boost is now pre-falsified by G3. No knob was taken here.
7. **Cascades?** Yes — the same NP17-PENDING root as NP08 (and the heavy-isotope curve). G2 (R_He) and G4 (μ_α) do not cascade; they stand.

**Recovery grade: PARTIAL** (failure fenced with a quantitative target curve; the lock mechanism itself unpaid).

---

> **Prompt completion B · Physics class OPEN (G1 FAIL quantified; G3 constraint EARNED; G2 re-verified; G4 DEGENERATE) · Recovery PARTIAL · Cascade root: NP17-PENDING tetrahedral-lock magnitude (shared with NP08)**

*NP10 · executed 2026-07-03 · honest OPEN · the lock term is now a quantified, falsifiable target.*

---
---

# NP10 — RUN 2 VERDICT: ROOT-CONTACT, the shared-seat contact wall

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-05. **Engine:** `sdt/laws.hpp` only.
> Tool: `np10_contact_wall.cpp` (MSVC exit 1 — honest) → `np10_contact_wall_results.txt`.
> Mission: the REGISTERED THREE-FIELD CROSS-CHECK (STACK §3b / CH07 §D7) — one wall
> mechanism, one constant set {αℏc, a₀, R_p}, three fields, no per-target tuning.
> Mechanism, gates (25% each) and expectations committed in RUN_LOG.md BEFORE coding.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | All three registered targets scored against pre-committed gates; expected failures confirmed and structurally diagnosed; no tolerance widened, nothing re-chosen after numbers. |
| **Physics class** | **KILLED** (Face R as the chemistry wall) / **OPEN-candidate** (Face T lock, −5.6% α) / **conjunction FAIL** | The saturated-occlusion radial ledger cannot be the contact wall — it *enhances* attraction identically everywhere above deep interpenetration. The lock ladder is quantitatively the FLM14 sequential-tour count (Z−1)!. |

## The registered cross-check score (all gates committed pre-run)

| Target | Predicted | Anchor (OBSERVED) | Gate 25% |
|---|---|---|---|
| (a) k(H₂), Face-R wall | 17 801 N/m at R_min = 0.315 Å (−57.6%) | 575 N/m at 0.7414 Å | **FAIL (+2996%)** |
| (b) NaCl correction, Face-R | **+40.6 kJ/mol (adds binding)** | −74.0 kJ/mol (861.0 → 787) | **FAIL (sign wrong)** |
| (c) alpha lock, Face T (Z−1)! | ×6 | ×6.354 required | **PASS (−5.57%)** |
| **CONJUNCTION (the cross-check)** | | | **FAIL** |

Face T support rows: deuteron (Z=2) ×1 → 2.200 MeV (−1.06%); triton (Z=3) ×2 → 8.557 MeV
(+0.88%); alpha (Z=4) ×6 → 26.721 MeV (−5.57%) — three nuclei, zero constants.
Diagnostics: **D2** cage rule holds (nuclear ledger shifts the deuteron only +0.23%; the
ledger does not break NP17). **D1** budget-wall rival (ℏ²/2m_e confinement, flagged
formally degenerate with the QM zero-point form): R_min 0.579 Å (−22%), k 2697 N/m
(+369%) — an order of magnitude closer than Face R; fences the chemistry wall's true
scale for ROOT-BUDGET; earns nothing here (CONVERGENCE cap declared pre-run).

## The kill — Face R (saturated-occlusion ledger as the contact wall)

The failure is **structural, not numerical**: the exact solid-angle energy obeys
E_exact/E_point = ρ(π−2ρ) ≥ 1 for all ρ = r/R̂ > 0.444. Exact occlusion **deepens**
attraction — it cannot generate Born-type repulsion, cannot soften a well, and its only
"wall" is the untouched surplus 1/R divergence (hence H₂ collapses to 0.31 Å at 31× the
measured stiffness). At NaCl the enhancement is long-ranged (per-pair difference ~
αℏc R̂²/12r³, lattice sum log-divergent: +34.4/+40.6/+46.8 kJ/mol at cutoff 20/40/80 —
magnitude cutoff-dependent, **sign unconditionally wrong**: every term adds binding).
**Kill scope (declared):** this committed form — exact-solid-angle deficit ledger +
ceiling extension + cage rule — as the *chemistry-scale contact wall*. NOT killed: the
two-regime G(x) law in its own regime (gravitational grazing, E105/GOM13 — no
interpenetration there), and NOT the coordination-dependence itself (which survives as
Face T). GATE-CONTRABAND check: all three gates are measured anchors (575 N/m, 787 vs
861 kJ/mol, 28.296 MeV) — no rival axiom sits in any kill condition.

### §D Seven questions (on the Face-R kill)

1. **Why exactly?** GA +2996% (minimum at 0.315 Å, k 17 801 N/m); GB sign inverted (+40.6 predicted vs −74.0 required). Both were pre-declared from the identity ρ(π−2ρ) ≥ 1 and confirmed by the run.
2. **Recoverable?** Not by any sub-boundary shape choice: the enhancement identity holds for r > 0.444 R̂ regardless of the extension; no R̂ assignment flips it (checked: ionic-contact R̂ makes it worse). Recovery requires a *different resource*, not a different profile.
3. **What did the target fail to account for?** A short-range cost that REMOVES binding at contact. Occlusion geometry supplies only shadow (deficit → attraction); the wall must be paid from a non-shadow ledger.
4. **Which premise erred?** FARMER's "saturation at contact IS the lock/wall" — at the *pair* level. The saturated pair correction is +0.23% at the deuteron and attractive at Å scale: too small for the lock, wrong sign for the wall.
5. **What freedom corrects it?** The seat's movement/residence budget (Law V / FLM14 tour cost): D1 shows the ℏ²/2m_e confinement scale lands within ×4.7 of k(H₂) where occlusion misses by ×31.
6. **Native or knob?** Native in kind (FLM12's confinement cost, Law-IV/V); underived in magnitude and formally degenerate with the QM zero-point form — flagged, capped CONVERGENCE, not gated, not tuned.
7. **Cascades?** Yes — ROOT-CONTACT **splits** (see below). CH02's overshoot, CH07's k, and CH05's barrier are NOT cleared by this run; the alpha lock leaves the contact cluster entirely.

**Recovery grade: PARTIAL** (mechanism killed with the disqualifying identity named; the
replacement resource fenced by D1 but not derived).

## What is earned

**Face T — the (Z−1)! sequential-tour lock (the run's positive product):** the number of
distinct closed tours of Z destinations (FLM14 rotating-spation sequential occupancy;
Harvey's scarce-rim-angle premium read as *sequential* engagement) reproduces the entire
run-1 ladder with **zero constants**: d −1.06%, t +0.88%, α −5.57%. It is superlinear in
coordination exactly as run-1's G3 demanded, vanishes for two-centre systems ((2−1)! = 1
— natively explaining why pairwise chemistry needs no lock), and the tetrahedron was not
hard-coded (only the destination count Z enters). **Honesty labels:** POST-DICTION of a
published ladder (declared pre-run); look-elsewhere logged (Catalan −21%, 2^C(n,2) +26%,
(Z−2)!! dead — (Z−1)! is the only committed survivor of ~5 simple forms); the energy-law
"B = tour-count × electrostatics" is UNDERIVED (§G item 3). **Falsifiers registered:**
Z=5 seat-tour lock must be ×24; He-3 (alternate grammar, 3p+1e) untested; the FLM14
residence law must produce energy ∝ tour multiplicity or this dies.

## §G faith ledger (what the committed wall accepted on faith)

1. **Surplus-no-ceiling asymmetry** (EMC03): accepted; it alone produced any wall at all. Still underived.
2. **Ceiling-force linear extension below R̂:** accepted; shown irrelevant to the kill (the enhancement identity lives above R̂).
3. **Energy ∝ tour count** for Face T: pure faith — now the named debt owed to FLM14.
4. **Cage rule R̂ = min(a₀, half-gap):** held at the deuteron (+0.23%); untested elsewhere.
5. **The CH07 point well retained to contact:** its −81.5 eV depth at Re is 2.5× the measured total electronic binding (31.95 eV) — the *well*, not only the wall, fails at contact. MIRROR: the gates were measured anchors, the rival (D1) was flagged and not gated; nothing oppositional policed the datastream.

## Cascade roots (reported; STACK edit left to owner)

**ROOT-CONTACT SPLITS:**
- **ROOT-LOCK (nuclear, many-body):** candidate paid at first order by FLM14 tour
  multiplicity (Z−1)! — owner FLM14; owed: the residence-energy derivation + Z=5 and
  He-3 falsifiers. Supersedes "saturated solid-angle ledger" as the lock route.
- **ROOT-WALL (chemistry contact repulsion):** NOT occlusion-saturation (killed here);
  converges with **ROOT-BUDGET** (Law V confinement/residence cost — D1 fences its scale
  at ℏ²/2m_e). CH02 overshoot / CH07 k / MgO remain OPEN under this root.

## Canonical line

**Prompt completion B (registered three-field cross-check executed; GA/GB honest FAIL as pre-declared, GC PASS) · Physics class KILLED (radial saturated-occlusion wall — enhancement identity ρ(π−2ρ)≥1 disqualifies it at chemistry scale) / OPEN-candidate (Face T (Z−1)! tour lock: d −1.1%, t +0.9%, α −5.6%, zero constants, post-diction declared) · Conjunction FAIL — ROOT-CONTACT splits into ROOT-LOCK (→FLM14) + ROOT-WALL (→ROOT-BUDGET) · Recovery PARTIAL**

*NP10 run 2 · executed 2026-07-05 · the wall and the lock are not one mechanism; the lock now has a zero-constant candidate and two registered falsifiers.*
