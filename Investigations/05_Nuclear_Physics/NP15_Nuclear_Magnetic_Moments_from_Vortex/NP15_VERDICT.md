# NP15 — VERDICT: Nuclear Magnetic Moments from Vortex Geometry

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` only.
> Tool: `np15_magnetic_moments.cpp` (MSVC exit 0) → `np15_results.txt` (redirected stdout).
> μ_N used throughout as a **borrowed** comparison unit, flagged.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | All five required outputs addressed with pre-committed candidates and blind 5% gates; μ_n honestly inherited from NP20 instead of re-fished. |
| **Physics class** | **OPEN** (composites **DEGENERATE**; one flagged numerology candidate) | No committed trefoil formula lands μ_p; block-addition reproduces only what the rival's impulse approximation also gives, and breaks beyond A=4. |

## Numbers (gate 5%, committed blind in RUN_LOG before coding)

| Target | Committed prediction | Result | Label |
|---|---|---|---|
| μ_p = +2.7928 | C1 rim g_p = 4.0008 | +43.25% | FAIL |
| | C2 toroidal @R_p = 2.5303 | −9.40% | FAIL |
| | C3 poloidal @R_p = 3.0990 | +10.96% | FAIL |
| | C4 toroidal @R_major = 1.3930 | −50.12% | FAIL |
| | C5 g_p√(v_Tv_P)/c = 2.8003 | **+0.27%** | **[OPEN] numerology ledger — no derivation, PASS forbidden by RUN_LOG** |
| μ_n = −1.9130 | not re-derived | — | OPEN (inherited NP20: magnitude IDENTITY, sign assumed) |
| μ_n/μ_p = −0.68498 | −2/3 proximity (+2.67%) | — | OPEN (no SDT derivation; SU(6) inadmissible) |
| μ_d = +0.8574 | μ_p+μ_n = +0.8798 | +2.61% | PASS(5%) but **DEGENERATE** |
| μ_t = +2.979 | μ_p | −6.25% | FAIL |
| μ_h = −2.128 | μ_n | +10.10% | FAIL |
| μ_α = 0 | 0 (paired cancellation) | exact | PASS but **DEGENERATE** (spin-0, every model) |
| μ(Li-7) = +3.2564 | μ_p (α+t, α silent) | −14.24% | FAIL |
| μ(Be-9) = −1.1778 | μ_n (2α+n, α silent) | −62.43% | FAIL |

## What is earned vs owed

**Earned:**
1. **A clean bracket, honestly reported.** The two (2,3)-trefoil mode projections straddle μ_p
   (−9.4% / +11.0%). The trefoil is the right *neighbourhood*; no committed single-mode
   current loop is the right *mechanism*. Bracketing ≠ predicting (NP20 precedent held).
2. **A falsifying result for naive block-addition.** The grammar-pairing rule degrades
   monotonically with A (d +2.6% → t −6.3% → h +10% → Li-7 −14% → Be-9 −62%). Whatever
   carries nuclear moments beyond the deuteron, it is NOT free-nucleon addition over
   ATOMICUS blocks. This kills a tempting easy story before it could calcify.
3. **Discipline held on two traps**: (a) C5's +0.27% geometric-mean match was flagged
   post-hoc at design time, logged with its look-elsewhere cost (~5 combinations tried),
   and barred from PASS; (b) μ_n was not re-fished past NP20's OPEN.

**Owed:**
- A derivation (or kill) of the C5 form `μ_p = g_p√(v_T v_P)/c` — i.e. WHY would the moment
  ride the geometric mean of the mode speeds? Until derived from the helical current
  geometry it is numerology-class, same bar as 6π⁵: unique, cheap, untested mechanism.
- The NP20 debts: native flux composition + dynamical sign for μ_n.
- A real composition rule for A ≥ 3 moments (the Be-9 −62% miss says the α blocks are not
  magnetically silent, or the odd nucleon is not a free nucleon — structure the model owes).

## Success criteria scoring (PROMPT §4)

- [ ] μ_p within 5% from geometric argument — **NO** (OPEN; bracket only; C5 barred)
- [ ] μ_n sign and magnitude — **NO** (OPEN, inherited NP20)
- [ ] μ_n/μ_p geometric — **NO** (OPEN)
- [~] μ_d within 5% — arithmetic yes (+2.61%) but DEGENERATE (rival-identical)
- [x] μ_α = 0 by paired cancellation — consistent, DEGENERATE

## Stress-test self-audit

1. **Identity/circularity:** all candidate formulas use engine lengths/speeds only; the
   measured moments enter solely as OBSERVED targets. No candidate consumes its own target.
2. **Fished factors:** the one near-perfect number (C5, +0.27%) is *named as the fish it is*
   and quarantined; the blind gates were committed before compilation and never widened.
3. **Dimensions:** everything reported in μ_N (borrowed, flagged); the native content is the
   dimensionless g-factor `R m c v /(ℏ c)` — sound.
4. **Cascade root:** NP20's un-derived flux composition; secondarily PPT01's mode speeds are
   solid (class A) but the *current-to-moment* map is the missing physics.

## §D Seven questions (HUNTER_PROTOCOL, on the μ_p OPEN and composite FAILs)

1. **Why exactly?** μ_p: every committed single-mode loop misses on magnitude (−9.4% to +43%), signs fine. Composites: additive block rule degrades monotonically with A (+2.6% → −62.4%).
2. **Recoverable?** μ_p: plausibly — the two mode projections bracket the target, so a derived *helical* (both-mode) current map could land inside the bracket (C5 shows a two-mode combination can; it is quarantined until derived). Composites: not by addition — needs interaction structure.
3. **What did the target fail to account for?** μ_p: the trefoil charge rides both circulations at once (a helix, not a flat loop at one radius). Composites: packed blocks share electrons and deform (NP17), so free-nucleon moments do not survive packing.
4. **Which premise erred?** μ_p: "the moment is a single-mode current loop at a single radius." Composites: "grammar blocks are magnetically rigid and independent."
5. **What freedom corrects it?** A derived effective loop (radius × speed) for the helical trefoil path; for composites, the shared-electron circulation of the packed geometry.
6. **Native or knob?** The helical current-to-moment map would be native (pure geometry) but does not exist; adopting C5 now would be a knob (refused). Composite corrections wait on NP17's imported per-isotope geometry — native in principle, unbuilt.
7. **Cascades?** μ_n inherits NP20's flux-composition debt. Composites cascade from NP17-PENDING. The μ_p current-to-moment map is NP15's own new named debt (roots in PPT01/PPT08, whose mode speeds are solid).

**Recovery grade: PARTIAL** (bracket real, premise errors named; no freedom yet justified natively).

---

> **Prompt completion B · Physics class OPEN (composites DEGENERATE; C5 quarantined numerology-risk) · Recovery PARTIAL · Cascade roots: trefoil current-to-moment map (NEW, owned by NP15); NP20 flux-composition (μ_n); NP17-PENDING (composites)**

*NP15 · executed 2026-07-03 · honest OPEN/DEGENERATE · the bracket is real, the landing is owed.*
