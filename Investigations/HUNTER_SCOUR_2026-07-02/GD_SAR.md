# HUNTER SCOUR 2026-07-02 — Region: 08_Galactic_Dynamics + 09_Stellar_Astrophysics_and_Radiation

> Auditor: HUNTER at maximum pressure, assume-fabrication.
> Method: read every committed result/verdict; for each high-value claim COMPILE+RUN (MSVC
> `cl /std:c++20 /O2`, Python direct) in scratchpad and diff against the committed numbers;
> trace every headline to its premise. Laws canon NOT touched (verified — no edits under
> `Engine/include/sdt/` or `Laws/`; all builds ran from a scratchpad copy of the .exe, includes read-only).
> Every number below is reproduced program output unless marked otherwise.

---

## Fault table

| ID | Item | Claim as committed | What I found (evidence) | Grade |
|----|------|--------------------|--------------------------|-------|
| F1 | **GD04** `gd04_3d_volumetric_integration.cpp` | Prints `[SUCCESS] LSB galaxies like UGC 128 and IC 2574 survived! 3D Volumetric Integration naturally yields saturation.` | **Built + ran (BUILD_EXIT=0).** Actual output: **RMS 71.39 %**, max residual **97.7 %**. UGC 128: V_SDT **3.7** vs V_obs 64 (+94.2 %); IC 2574: 6.7 vs 67 (+90.1 %); DDO 154: 1.1 vs 47 (+97.7 %). The `[SUCCESS] … survived` gate (line 100) only tests `predicted_velocity > 10 m/s` — i.e. "not exactly zero" — **not** that it matches. A ~10-40× under-prediction is stamped SUCCESS. (The separate `RMS<30%` success line correctly does NOT fire.) No verdict/INVESTIGATION.md to contextualise it. This is the exact tool GD05 later ran to ground at RMS 66 %. | **INFLATED** (false SUCCESS on a 90 %+ order-of-magnitude miss) |
| F2 | **GD01** `INVESTIGATION.md` (May 2026, byline Tyndall) | "Answer: YES — Eclipse Saturation Mechanism Demonstrated… BTFR slope = 4… No dark matter required." Table of `v_flat` for 10 galaxies. | **Not reproducible.** (a) The cited tool `cq06_eclipse_saturation.cpp` **is not present** in the folder. (b) The folder's `gd01_eclipse_saturation.cpp` **does not compile** against the current engine: `error C2039: 'Sigma_sat_Msun_pc2' is not a member of 'sdt::galactic'` / `'Sigma_sat_SI'` (both renamed to `_DEPRECATED` and moved to function scope in `galactic.hpp:1402`). (c) The `v_flat` "results" (NGC 6503→116, NGC 3198→150 …) are the **observed inputs echoed back**. This "YES / RESOLVED" directly contradicts the honest GD05 finding that the *same* eclipse model gives RMS 66 %, BTFR 1.33 on real SPARC. Stale, non-running, superseded "success." | **INFLATED / stale** (superseded circular-era success, no running tool) |
| F3 | **GD05-twin** `INVESTIGATION_twin_regime.md` M4 law | Header + §7: "M4 convergence-floor law: RMS 23.8 %, unbiased (−1.6 %), BTFR 3.58 (**PASS**)… **zero free parameters**… SDT now reproduces galaxy rotation curves." | **Numbers are REAL** (rebuilt + ran twin tool, BUILD_EXIT=0: RMS 23.8, bias −1.6, BTFR 3.58 — bit-match to `gd05_twin_output.txt`). **But M4 is MOND with SDT labels.** Law `g_obs = g_bar/(1−exp(−√(g_bar/a₀)))` is MOND's "simple/exponential" interpolation function; `a₀ = c·H₀/2π = 1.042e-10` is the MOND acceleration scale (= 86.8 % of Milgrom's 1.2e-10; the `c·H₀/2π ≈ a₀` coincidence is a known MOND-literature identity, and `galactic.hpp:74` comment literally says "SDT Milgrom scale"). The deep limit `√(g_bar·a₀) → v⁴=GM a₀` **is** the MOND/BTFR relation. The tool's own VERDICT prints `[FAIL] M4 RMS<20% (got 23.8%)` — so "PASS" in the doc header refers only to the BTFR band, and RMS did **not** pass. BORROW-SMUGGLE (MOND interpolation + a₀) load-bearing behind the one winning model. | **BORROW** (partly self-flagged §6/§8 as "borrowed, not derived"; but headline "zero free parameters / SDT reproduces rotation curves" over-claims) |
| F4 | **GD03** `gd03_convergence_occlusion.cpp` (May 2026) | `=== PROOF: LINEAR KOPPA RAMP → FLAT ROTATION ===` … "The flat zone… is the convergence occlusion balance point, **NOT a dark matter coincidence**." | **Circular.** The "verification from observed rotation curve" reads `v_obs`, forms `K = Koppa(v_obs, R)` (koppa **from** the observed velocity), then shows `K/R = v²/c²` and reads it back as `v_occ = √(c²·K_obs/R) ≡ v_obs` (line 361-368). It proves `v_obs = v_obs`. The "linear koppa ramp" is just the restatement that a flat curve has `v²R = const`. No independent prediction. Mitigant: GD03 has **no committed verdict/results/INVESTIGATION.md** — these are exploratory tools, nothing is asserted as a validated PASS. | **CIRCULAR / IDENTITY** (in-tool prose only; no committed verdict) |
| F5 | **SAR02** `sar02_blackbody_lattice.cpp` — Wien check | `λ_peak·T = 2.897772e-3 m·K (target 2.897772e-3) │error│ 5.49e-10 [PASS]` | **Identity dressed as a test.** `lam_wien = 2.897771955e-3` (CODATA Wien constant) is hard-coded as a literal, then `lam_peak` is recomputed as `h c/(x_wien k_B T)`, so `lam_peak·T = h c/(x_wien k_B)` — which **equals the Wien constant by construction**. The 5.49e-10 "error" is just `x_wien`'s rounding. Comparing a quantity to a literal of itself. `x_wien = 4.9651142…` is also the standard transcendental root, hard-coded, not derived. | **MINOR / IDENTITY-PASS** (one of three checks; verdict is honestly Class C otherwise) |
| F6 | **SAR02** Stefan-Boltzmann + n_γ | "a (Stefan-Boltzmann) COMPUTED 4.4 ppm; Planck spectrum COMPUTED from mode counting." | `a = (8π⁵/15)·k_B⁴/(h³c³)` is the **textbook radiation constant**; the `8π⁵/15`, the `ζ(3)` photon-density prefactor, and `x_wien` are all **results of integrating the Planck/Bose-Einstein distribution** — the distribution is *assumed*, not derived. The tool re-exposes textbook radiation thermodynamics. **Honest**: verdict explicitly says "Boltzmann exp: LINGUISTIC-BORROW (counting axiom, not derived here)" and Class C. Does **not** claim to derive Planck. Noting for completeness, not a fault. | **OK (honest Class C)** — re-expose flagged, not a fault |

---

## Per-investigation status (1-line)

- **GD01** Eclipse Saturation — *INFLATED/STALE.* "YES/RESOLVED, BTFR=4, no dark matter" (May 2026) is not reproducible: cited tool absent, present tool won't compile (engine symbols renamed), results = inputs echoed; contradicts honest GD05. **[F2]**
- **GD03** Galactic Spation Topology — *CIRCULAR (uncommitted).* Multiple May-2026 tools "prove flat rotation, NOT dark matter" by reading v_obs → koppa → v_obs (identity). No committed verdict, so no fabricated PASS on record; flag the in-tool claims. **[F4]**
- **GD04** 3D Volumetric Integration — *INFLATED.* Runs, prints RMS **71.4 %** yet stamps `[SUCCESS] LSB survived` on 90 %+ misses via a "velocity ≠ 0" gate. The circular-era tool GD05 retired. **[F1]**
- **GD05** Galaxy Rotation Curves — **HONEST NEGATIVE (single-regime) + BORROW (twin M4).** `INVESTIGATION.md` correctly reports RMS 66 %, BTFR 1.33, retracts the prior circular-mock success, labels κ CALIBRATED — **this is exactly right, GOOD.** `INVESTIGATION_twin_regime.md` M4 numbers are real but the win is MOND (interp fn + a₀); over-claims "zero-param / reproduces curves" while self-admitting the borrow in §6/§8. **[F3]**
- **GD06** Gravitational Lensing — **HONEST Class C.** Rebuilt+ran: 1.7517″ vs 1.7500″ (0.10 %). δ=4ϟ/b with ϟ=koppa_Sun≡GM_⊙/c² is the standard Einstein deflection (CONVERGENCE), verdict says so and labels it Class C, PENDING on SLACS. No fabrication.
- **GD02 / GD07** — out of scope for claimed-result audit (GD02 = PROMPT only; GD07 = legacy calculator; no committed verdicts).
- **SAR01** Le Sage Thermal Budget — **PROMPT ONLY.** No tool, no results, no verdict. Nothing to audit / nothing claimed.
- **SAR02** Blackbody from Lattice — **HONEST Class C, one MINOR identity-check.** SB constant & n_γ are textbook radiation thermodynamics re-exposed (verdict admits Boltzmann occupation is borrowed); Wien "PASS" is an identity (F5). Does not over-claim a Planck derivation.
- **SAR03** Solar Luminosity — **PROMPT ONLY.** No tool/results/verdict. Nothing claimed (famous number not actually targeted in a committed run).
- **SAR04** Stellar Main Sequence — **PROMPT ONLY.** No tool/results/verdict. Nothing claimed.
- **SAR05** Provenance After Iron — **HONEST Class C / DEGENERATE (well-labeled).** Rebuilt (Python) + ran, exit 0, bit-match: z↔T declared an identity by construction; 2/5 an integer grammar identity; after-iron fork declared DEGENERATE single-event, LIVE-only-at-population (unmeasured, owed); no G/M smuggle. Model of an honest verdict — no fault.

---

## Verdict lines

- **GD01** — Prompt completion **D** · Physics class **KILLED-as-committed** (non-running/superseded; the *hypothesis* survives as OPEN, already re-tested honestly in GD05) · Recovery: none needed, GD05 is the live successor · Cascade root: shared eclipse-saturation velocity law, which GD05 ran to ground.
- **GD03** — Prompt completion **C** · Physics class **CIRCULAR** (v_obs→koppa→v_obs) · Recovery: PARTIAL (real test = the GD05 twin per-radius run) · no committed verdict so no fake-PASS on record.
- **GD04** — Prompt completion **C** · Physics class **INFLATED** (false SUCCESS label on RMS 71 %) · Recovery: the honest number is GD05's; GD04's SUCCESS line is retracted.
- **GD05** — Prompt completion **A** · Physics class **NEGATIVE (single-regime, HONEST) / BORROW (twin M4 = MOND)** · Recovery: single-regime correctly UNPAID; twin M4 needs the crossover derived natively before "zero-param" stands · Cascade root: the MOND interpolation shape + a₀, self-flagged as owed.
- **GD06** — Prompt completion **A** · Physics class **CONVERGENCE (Class C, honest)** · no fault.
- **SAR02** — Prompt completion **A** · Physics class **CONVERGENCE (Class C, honest)**; one MINOR identity-check (Wien) · no material fault.
- **SAR05** — Prompt completion **A** · Physics class **CONVERGENCE / DEGENERATE (honest, well-labeled)** · no fault.

## Note on the region's honesty gradient

The recent-session work (GD05 single-regime negative, GD06, SAR02, SAR05 — all late-June/July 2026) is **honestly graded**: negatives declared, borrows flagged, identities labeled. The faults concentrate in the **older May-2026 Tyndall-era GD tools** (GD01, GD03, GD04) that predate the circular-mock retraction and were never re-verdicted — exactly the higher-risk cohort. GD05's `INVESTIGATION.md` §1 already names the disease ("circular test data", "deprecated calibrated path") that F1/F2/F4 are instances of; those three older tools/docs just weren't cleaned up after the cure.
