# RUN_LOG — NP03C Trefoil Nucleon Topology (positions FROZEN from NP03B)

> **Author of run:** executor (agent), on behalf of J. C. Harvey investigation spec.
> **Run date:** 2026-07-03. **Engine:** `sdt/laws.hpp` (`measured::R_p`, `law_VI::winding::R_p_predicted`).
> **Input:** `../NP03B_Independent_Nuclear_Equilibrium/np03b_positions.txt` (frozen — read-only).
> **Tool:** `np03c_trefoil_topology.cpp` (MSVC, C++20). Append-only during the run.

---

## Pre-Run Commitments — NP03C

- **Prompt completion target:** A.
- **Physics class hoped:** class **B** (internal embodiment). Rendering is NOT evidence; this
  stage only produces the substrate NP03D tests, with numeric validity metrics.
- **CALIBRATED budget:** 0 fitted parameters. Representation choices (declared here, BEFORE
  run, and never tuned against any output):
  - trefoil torus major radius `R_t = 0.6 R_p`, minor `a_t = 0.2 R_p` (R/a = 3),
    tube radius `r_tube = 0.08 R_p` → knot extent `R_t + a_t = 0.8 R_p ≤ R_p` (the prompt's
    "R_p-scale tube" requirement, satisfied by construction and echoed numerically);
  - physical placement scale: block unit directions from NP03B × common factor chosen so the
    **minimum block–block centre distance = 2 R_p** (boundary-radius contact convention).
    A common scale factor is a unit conversion, not a position change — drift gate below
    checks the *directions* exactly;
  - alpha core represented as **2 proton trefoils at ±0.5 R_p on the +Y axis** (deterministic).
    SIMPLIFICATION, logged: the NP17 interleaved-lock internal geometry of the alpha is NOT
    reproduced here; blocks are represented by their proton's trefoil only (one per block).
    These do not affect the position-drift metric and are inherited honestly by NP03D.
- **Grammar/positions:** consumed from NP03B output only. No electron quantity.

### Phase thresholds (committed BEFORE run)

- **C0 input integrity:** FNV-1a-64 hash recomputed from the file's block coordinates must
  equal the per-isotope hash recorded inside the file (exact).
- **C1 zero position drift (the prompt's hard rule):** unit directions of emitted block-trefoil
  centres == NP03B file directions, max |Δcomponent| < 1e-12. Core trefoils are additions at
  the origin convention above, not moved blocks.
- **C2 knot validity:** each trefoil curve closes: |P(0) − P(2π)| < 1e-9·R_p; crossing count in
  the axis projection == **3 exactly** (the (2,3) analytic value q(p−1) = 3) for every trefoil.
- **C3 tube non-degeneracy:** min non-adjacent self-distance of each knot curve ≥ 2·r_tube
  (analytic expectation for this parametrisation: 2·a_t = 0.4 R_p ≥ 0.16 R_p).
- **C4 radial orientation:** knot axis · site unit direction = 1 within 1e-9 (block trefoils).
- **C5 scale + global clearance:** R_p taken from `laws.hpp::measured::R_p` (8.414e-16 m;
  `winding::R_p_predicted` echoed for reference only); tube–tube clearance ≥ 0 for **every**
  pair of trefoils in every demo isotope (numeric, curve-sampled).

### Forbidden retroactive changes

- moving any NP03B position; retuning R_t/a_t/r_tube after seeing a clearance number;
  claiming the render as evidence of anything.

---

## Phase execution record (appended 2026-07-03 from real stdout, `np03c_results.txt`)

Build: MSVC 19.44.35223 x64, exit 0 (three builds — see ADJ trail). Final run: exit 0.

- **C0 PASS** — 6/6 isotopes with blocks: recomputed hash == file hash (He-4 N=0: n/a, no
  blocks to verify — first build compared a vacuous pair and mislabelled it; fixed).
- **C1 PASS** — zero position drift: max |Δ| ≤ 2.22e-16 (double-precision floor; unit-direction
  recovery from physical centres is exact to machine epsilon).
- **C2 PASS** — 69 trefoils total (2 core + N blocks per isotope): closure fails 0; crossing
  count range **[3,3]** — every knot projects to exactly the analytic q(p−1) = 3 crossings.
- **C3 PASS** — worst min self-distance 0.1840 R_p ≥ committed gate 0.16 R_p (= 2·r_tube).
- **C4 PASS** — min axis·û = 1.000000000000 (radial orientation exact).
- **C5 PASS** — R_p consumed from `laws.hpp::measured::R_p` = 8.414e-16 m (W+1 predicted value
  8.412356e-16 m echoed as reference only, never consumed); worst tube–tube clearance
  +0.0295 R_p (C-12, tightest) — all pairs clear in all isotopes.

### ADJ entries (instrumentation corrections — no tolerance touched, no physics changed)

- **ADJ-001** — first build's crossing counter used an absolute collinearity epsilon (1e-30)
  against metre-scale coordinates (~1e-16 m ⇒ cross-products ~1e-34): every crossing read as
  "collinear", count 0 everywhere. Fix: project in R_p units, epsilon 1e-14.
- **ADJ-002** — second build still counted 0: with M = 720 (divisible by 12), the three
  analytic crossings (t = π/6 + kπ/3) fall EXACTLY on shared segment endpoints, and the
  proper-crossing predicate (all four orientations nonzero) rejects endpoint contact.
  Fix: half-step offset sampling for the projection. Third run: [3,3] everywhere.
- **Premise error owned:** the pre-run note claimed "analytic expectation 2·a_t = 0.4 R_p" for
  the min self-distance. That is only the same-projected-ray pair separation — an upper bound,
  not the minimum; the true 3D minimum is 0.1840 R_p ≈ 0.92·a_t. The committed GATE (≥ 0.16 R_p)
  was stated independently of that note and is passed legitimately; margin is thin (0.184 vs
  0.16) and is reported as-is, not celebrated.

- **No pivots fired. No tolerances changed. CALIBRATED count: 0** (R_t, a_t, r_tube declared
  pre-run as representation choices; none retuned after any output was seen).
