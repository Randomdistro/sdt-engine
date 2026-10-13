# RUN_LOG — GD03 Galactic Spation Topology (audit re-run)

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.
> **Purpose:** NOT a rescue. The 2026-07-02 scour graded GD03 CIRCULAR
> (v_obs → koppa → v_obs). This run compiles all nine May-2026 tools AS-IS, captures the
> real output of each, and writes the missing honest VERDICT.md.

## Pre-Run Commitments — GD03

- Prompt completion target: n/a (audit run)
- Physics class expected: CIRCULAR/IDENTITY for the closure levels; any Level-4
  "prediction" claims to be checked against what the code actually computes
- Pre-declared audit points (from source inspection of `gd03_spation_topology.cpp`
  BEFORE running):
  1. Level 1 (zk² = 1): computed as z·k² where both come from the same v — algebraic
     identity; the tool itself prints "trivially true by construction".
  2. Level 2 (ϟ = R/k²): every zone's koppa is DERIVED from the measured v_char of that
     zone. Nothing is predicted. v_obs → ϟ → (nothing else) = the circularity.
  3. Level 3 (parent invariance): ϟ_Sun from 8 planetary (a,T) and ϟ_SagA from 5 S-star
     orbits — this is Kepler's third law consistency (4π²a³/T² = GM = const), a real but
     Newtonian-equivalent check. CONVERGENCE at best.
  4. Level 4: single-engine wake v(r) = 1.831c·R_p/r. Predicted check: v(r_e) should be c
     — but 1.831·R_p/r_e = 0.547, so the tool's own printed ratio should show ~0.55, NOT
     1; and v(a₀) vs αc should miss by ~250×. Yet the final banner hand-stamps
     "Level 4 ... PASS — cq20g proves flat rotation" (a claim about ANOTHER tool, not
     computed here). If the printed ratios miss as computed above, Level 4 is a FAIL
     stamped PASS = fabricated verdict line.
- Committed reporting: per-tool real stdout, verbatim key numbers; class CIRCULAR;
  superseded-by GD05 for anything rotation-curve shaped.

## Build log

- 2026-07-03: all NINE tools compiled AS-IS, zero source edits, MSVC 19.44.35223 x64,
  `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include`. 9/9 exit 0.

## Run log (all exit 0; full stdout in `results_<tool>.txt`)

| Tool | Key real output |
|---|---|
| gd03_spation_topology | Level 3 solar: σ/μ = 0.0611% PASS (Kepler consistency). **Level 3 Sag A*: σ/μ = 51.03% — prints "Level 3 FAIL"**. Level 4 wake: v(r_e)/c ratio **0.5467** (target ~1), v(a₀)/αc ratio **0.00399** (target ~1). **Final banner nevertheless stamps Levels 1–4 ALL PASS** — contradicting its own computed FAIL two screens above, and citing "cq20g proves flat rotation" (a different tool, not computed here). |
| gd03_convergence_occlusion | Source line ~361–368: `K_obs = Koppa(v_obs·1e3, R_m); v_occ = √(c²K_obs/R)` with comment "just use observed Ϟ as the proxy" → **v_occlusion ≡ v_observed by construction**; table prints them identical. "Linear Ϟ ramp verification" evaluates Ϟ = v²R/c² from OBSERVED v — v≈const ⟹ Ϟ∝R is an identity restatement of flatness, not a prediction. |
| gd03_galactic_occlusion | Actual forward model over-predicts everywhere: v_SDT 955 vs v_obs 220 km/s (3.8 kpc), 681 vs 229 (8.1 kpc), 406 vs 185 (24.7 kpc) — 2–4× high, declining not flat; prose still claims "flat rotation is the natural output". No PASS/FAIL gate at all. |
| gd03_bulge_from_sagA | Prints its own miss honestly: "At 26 pc: v_kep = 166, v_obs = 232 km/s (core under-predicts by 40%)". |
| gd03_galactic_skymap | GA section: "Observed bulk flow toward GA: ~600 km/s ... Ratio: 0.000" — predicted ~0 vs observed 600. Anisotropy map itself is descriptive (column Ϟ from assumed density model). |
| gd03_proton_spation_cmb | "Ϟ(r_e) = r_e exactly" — definitional (r_e IS the H-atom koppa in laws.hpp). Prints an unexplained 5.4e58 "dimensional bridge factor" — numerology-adjacent, no gate. |
| gd03_torus_differential / torus_spation_count / trefoil_convection | Exploratory torus/trefoil geometry scans; no verdicts claimed, none earned; not rotation-curve relevant. |

- Audit points 1–4 (pre-committed above): ALL CONFIRMED by the real output.
