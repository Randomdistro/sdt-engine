# RUN_LOG — NP03B Independent Nuclear Equilibrium (electron-blind positions)

> **Author of run:** executor (agent), on behalf of J. C. Harvey investigation spec.
> **Run date:** 2026-07-03. **Engine:** `sdt/nuclear.hpp` (block counts), `sdt/packing.hpp`
> (kissing-radius formula, preset reference angles). **Tool:** `np03b_equilibrium.cpp` (MSVC, C++20).
> Append-only during the run.

---

## Pre-Run Commitments — NP03B

- **Prompt completion target:** A.
- **Physics class hoped:** class **B** (SDT-derived, internal-only, electron-blind by
  construction) — positions are a *substrate* for NP03C/D/E, not themselves a prediction.
- **CALIBRATED budget:** 0. (Solver hyper-parameters — iteration counts, exponent schedule,
  seeds — are numerics, logged below, and provably do not enter the equilibrium definition:
  the maximin objective is parameter-free.)
- **Engine namespaces:** `sdt::nuclear::alpha_grammar` (inputs), `sdt::packing`
  (`r_from_tammes_theta`, reference preset angles). **HARD BAN honoured:** no `SUBSHELLS`,
  no Aufbau order, no electron-shell radius, no `2n²`, no electron quantity of any kind
  appears in the tool. Block count N = n_d + n_t (= Z − 2, an exact grammar identity).
- **Method (fixed before run):** maximin angular separation (Tammes) approached by
  inverse-power chord repulsion with exponent continuation p = 2 → 4 → 8 → 12, fixed-seed
  LCG multi-start, best-of-starts by θ_min; kissing radius r = sin(θ_min/2)/(1 − sin(θ_min/2)).
  Deterministic double-precision arithmetic; no time(), no std::random_device.

### Phase thresholds (committed BEFORE run)

- **P0 solver sanity:** N=2 → 180.0°, N=3 → 120.0°, both within 0.5% (known exact optima).
- **P1 emergent presets (the prompt's <2% gate):** solved θ_min within 2.0% of
  N=4: 109.4712° (tetrahedron), N=6: 90.0° (octahedron), N=8: 74.8585° (square antiprism,
  the `packing.hpp` value), N=12: 63.4349° (icosahedron, acos(1/√5)). These must EMERGE from
  relaxation — the preset coordinates are never fed to the solver, only compared after.
- **P2 determinism:** two complete independent re-solves (same seeds) must produce **identical**
  FNV-1a-64 hashes over the final coordinates (exact bit equality after 1e-9 rounding).
- **P3 electron-blindness:** zero electron quantities in the dependency chain (auditable by
  grepping the tool: no a_0, no shell, no Aufbau, no 2n² anywhere).
- **P4 null model (carried to NP03E):** fixed-seed random placement WITHOUT relaxation recorded
  per demo isotope; solved θ_min must be ≥ random θ_min in every demo case (N ≥ 2).
- **P5 triton sites:** tritons assigned by deterministic greedy max-min subset selection;
  the chosen subset's min pairwise angle reported; assignment must be reproducible (same hash).

### Demo isotope set (fixed before run; consumed by NP03C/D)

He-4 (N=0), Li-7 (N=1, 1t), C-12 (N=4), O-16 (N=6), Ne-20 (N=8), Si-28 (N=12), Fe-56 (N=24, 4t).
Plus a full θ_min/kissing-radius sweep N = 1..90 (every element Z = 3..92) as reference table.

### Forbidden retroactive changes

- widen the 2% preset tolerance; seed-shopping until presets pass (seeds fixed at 11,23,37,53,71,97
  BEFORE the first run); feeding preset coordinates as initial conditions; any electron input.

---

## Phase execution record (appended 2026-07-03 from real stdout, `np03b_results.txt`)

Build: MSVC 19.44.35223 x64, exit 0. Run: exit 0, 35 s.

- **P0 PASS** — N=2: 180.0000° (0.000%), N=3: 120.0000° (0.000%).
- **P1 PASS** — emergent presets, preset coordinates never fed to the solver:
  N=4 → 109.4712° (0.000% vs tetrahedron), N=6 → 90.0000° (0.000% vs octahedron),
  N=8 → 73.5337° (**1.770%** vs 74.8585° square antiprism — inside the committed 2% gate,
  but honestly noted: the relaxation sits in a near-antiprism basin slightly short of the
  Tammes optimum; NOT claimed as exact), N=12 → 63.4349° (0.000% vs icosahedron).
- **P2 PASS** — full re-solve hash equality, all four gated N: IDENTICAL
  (e.g. N=4 `be3519c61e94a831`, N=12 `6f216b7edfa6f9c5`).
- **P3** — electron-blind by construction; tool contains no a_0/shell/Aufbau/2n² symbol.
- **P4 PASS** — solved θ_min ≥ random-null θ_min for every demo N ≥ 2
  (e.g. O-16: 90.00° vs 2.14° null; Fe-56: 43.01° vs 10.22° null). Null baselines recorded
  for NP03E.
- **P5** — Fe-56 (n_d,n_t)=(20,4): greedy max-min triton subset min pairwise angle 86.42°
  (vs 43.01° block θ_min) — tritons maximally separated, deterministic.
- Demo positions written to `np03b_positions.txt` (consumed by NP03C, frozen).
- Bonus observation (no gate): N=5 relaxes to 90° (degenerate with N=6 octahedron minus
  one vertex) — matches the known Tammes result; recorded for NP03E context only.
- **No pivots fired. No tolerances changed. CALIBRATED count: 0.**
