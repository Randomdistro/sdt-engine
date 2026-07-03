# HUNTER SCOUR 2026-07-02 — Benchmarks + Engine Headers

> Region: `Benchmarks/B01_B25/benchmarks_b01_b25.cpp` + `Engine/include/sdt/*.hpp`.
> Read-only audit under `HUNTER_PROTOCOL.md`. Assume fabrication until disproven.
> Build: MSVC 2022 BuildTools, `cl /std:c++20 /EHsc /O2 /I Engine\include`. **Both benchmarks compile clean and run.**

---

## (i) THE REAL BENCHMARK RUN — verified, not asserted

`benchmarks_b01_b25.cpp` is mis-named: it actually contains **B01–B29** (grew past B25).
Build `BUILD_EXIT=0`; ran `bench.exe`, `EXIT_CODE=0`.

```
RESULTS: 62/73 passed (84.9%)
0 genuine fail · 11 PENDING (known-open, flagged)
```

**11 PENDING fails** (all honestly labelled `PENDING`, exit-code-exempt by design):
- B06 ×9 — multi-electron ionisation (Slater screening, errors 6.6% … 501%). Comment admits "empirical Slater σ, NOT an SDT derivation."
- B11 ×2 — Earth/Jupiter J2 (uniform-fluid, 59% / 203% off). Comment admits it "imports GM, against the no-G rule."

**Cross-check vs the memory tally "54/65, 0 fail, 11 PENDING":** the *shape* holds (0 genuine fail, 11 PENDING) but the **totals are STALE** — the suite is now **62/73**, not 54/65 (8 extra sub-checks from B26–B29 added since that note). Not a fault, just an out-of-date record. **No tolerance was moved past a failure that I can find** — the two tolerance edits (B03, B14) are documented and did not convert a fail→pass at the wire (see fault table).

**What the "62 PASS" actually contains** (this is where the real faults are — many PASSes are not predictions):

| Class | Count | Benchmarks |
|---|---|---|
| Genuine independent derivation (fair PASS) | ~15 | B01/B02 (Rydberg from R∞), B07 (Stefan-Boltzmann from k_B,h,c), B10 (Mercury/deflection from koppa), B17 (g-2 leading term), B18 (R_p W+1), B19 (β-Q from masses), B26 6π⁵, B27 c-from-precession, B28 depth |
| **IDENTITY-PASS** (engine value = the CODATA it was built from) | ~10 | **B03** Bohr v=αc, **B12/B20** zk²=1, **B23** k_e e²=αℏc, **B24** V_p/V_e=m_p/m_e & P_cf/(P_conv/3), **B25** exact-NR |
| **HAND-WRITTEN literal** (typed to sit on target; no formula) | 5 | **B04** Lamb 1051.8, **B09** dP/dt −2.4029e-12, **B15** BAO 147.0, **B16** exponent 0.5, **B25** E_exact −79.0052 |
| **BORROW-SMUGGLE** (imports G / GM) | 3 | **B21** G=6.674e-11 hardcoded, **B08** GM_equivalent, **B11** GM (labelled PENDING) |
| CALIBRATED presented as COMPUTED/DERIVED | 3 | **B22** P_eff & f_transfer (laws.hpp itself says class E, FAILS delete-test) |

Second executable in the tree that consumes an engine header: `Benchmarks/spherical_packing.cpp` (→ `packing.hpp`). Built clean, ran: **28/28 PASS**. These are integer scaffold-count identities (vertices == grammar decomposition) — self-consistent geometry, no fitted match. Fair.

---

## (ii) PER-HEADER UN-DERIVED NUMERIC-LITERAL TABLE

**Scope note (decisive):** the CMake target `sdt-benchmarks` builds **only** `benchmarks_b01_b25.cpp`, which `#include`s **only `laws.hpp`**. Therefore **`state28d.hpp`, `magnetosphere.hpp`, `neutrino.hpp`, `cosmology.hpp`, `nuclear.hpp`, `galactic.hpp`, `lattice_structure.hpp` are consumed by NO benchmark in the suite.** Any orphaned constant in them is inert *to the benchmark verdict* (load-bearing only inside their own Investigation tools).

| Header | Literal | Line | Use | Verdict |
|---|---|---|---|---|
| **state28d.hpp** | `1e10` | 134 | `tanh(|T_5|/1e10)` screening scale in `calculate_occlusion` | **ORPHANED / latent** — the FLM01 finding. `T_5=0` from both factories ⇒ fires nothing; un-derived [Pa/m] scale. Not consumed by B-suite. |
| state28d.hpp | `1e-20` | 159 | `1 + |Phi_5|/1e-20` in `accessible_phase_space_volume` | **ORPHANED / dead** — function uncalled; un-derived [J] scale. |
| state28d.hpp | `1e-30` | 123 | `if (separation < 1e-30)` div-guard | benign guard, not a physics scale |
| **laws.hpp** | `1051.8` | 1340 | `lamb_shift_native_MHz` (B04 reads it) | **HAND-WRITTEN** — bare literal, no formula; = APS04's fished value (see faults) |
| laws.hpp | `147.0` (bench), `1.23`, `0.23e-15`, `3.5e-7`, `3.0e-20`, `686.3`, `0.5464` | var | string tension, string-break, z_gal floor, r_e body, k_Sun seed, k_proton_surface | mix: some pre-computed-from-formula (0.5464, k_Sun), some DERIVED-order (1.23 GeV/fm class C, flagged +37% off), some OPEN (3e-20, 3.5e-7 flagged). None fabricate a benchmark PASS except via B04. |
| laws.hpp | `P_eff`, `f_transfer` | 365/376 | B22 | **CALIBRATED** — laws.hpp self-labels **class E, "FAILS delete-test"**; benchmark relabels COMPUTED |
| **magnetosphere.hpp** | `3.986e14`, `5.972e24`, `8.0e22` … | 44–52 | GM_earth, M_earth, dipole | **BORROW** (G/M) + measured Earth obs. Not in B-suite. |
| **neutrino.hpp** | `0.02/0.029/0.06`, `0.307/0.546/0.0222`, `26.7`, `0.251` | 38–178 | ν masses, mixing angles, chain energy | measured/assumed inputs, hardcoded. Not in B-suite. |
| **cosmology.hpp** | `67.4e3`, `73.04e3`, `2.898e-3` | 88–191 | H0 Planck/SH0ES, Wien | measured H0 values + Wien const. Not in B-suite. |
| **galactic.hpp** | `175 M☉/pc²` (Σ_sat), `8.178 kpc` | 1115/859 | eclipse-saturation | **CALIBRATED** (self-labelled "MW-calibrated") + observer radius. Not in B-suite. |
| **nuclear.hpp** | — | — | — | **CLEAN.** Only Z·R_p, 2·R_p geometry. Explicitly "no empirical fitting." |
| **packing.hpp** | golden φ (√5), `acos(-1/3)`, `√(3/2)` | 47–436 | polyhedra | **CLEAN.** All analytic geometric constants (tetrahedral angle etc.). Consumed by spherical_packing.cpp; 28/28 structural PASS. |
| **lattice_structure.hpp** | `0.5196…`, `0.3162…`, `0.9487…` | 52–59 | BC-helix ratios | **DERIVED** — irrational (3√3/10, 1/√10, 3/√10). Not fitted, not in B-suite. |

**Un-derived numeric-literal count per header (physics scales that are neither whitelist nor measured-observable nor analytic-geometry):**
`state28d.hpp` = **2** (`1e10`, `1e-20` — both orphaned) · `laws.hpp` = **1 load-bearing fabrication** (`1051.8` → B04) + several flagged-OPEN placeholders (self-disclosed) · `galactic.hpp` = **1 CALIBRATED** (Σ_sat, not in suite) · all others = **0 un-disclosed** (their literals are measured observables or analytic).

---

## (iii) FAULT TABLE (worst → minor)

| # | Bench/Header | Fault | Signature | Evidence |
|---|---|---|---|---|
| F1 | **B04 Lamb shift** | `lamb_shift_native_MHz = 1051.8` is a **bare hardcoded literal**; no formula computes it. Benchmark PASSes (0.57% < 1%) by comparing a typed number to the target. laws.hpp comment *claims* "ΔE≈(9/4)Φ₂(a₀) … zero fitted params" but the (9/4)Φ₂ evaluation is **not in the code** — only the answer is. This is the exact value the **APS04 HUNTER audit already ruled FABRICATED** (fished amplitude, non-compiling solver, hand-typed). | HAND-WRITTEN / PLUG | `laws.hpp:1340` sole assignment `= 1051.8;` (grep: one hit, no arithmetic). `APS04_HUNTER_AUDIT.md` §3. |
| F2 | **B09 Hulse-Taylor** | `sdt_dPdt = -2.4029e-12` typed directly — literally the **GR quadrupole value**, then "compared" to observed −2.4025e-12. Comment: *"SDT gives the same as GR quadrupole."* Nothing SDT is computed. | HAND-WRITTEN + BORROW (GR) | `benchmarks…cpp:297` |
| F3 | **B21 force ratio** | `G_derived = 6.674e-11` — the **NIST G, hardcoded**, inside a suite whose banner says "No G." Comment: "SDT derives same from k-hierarchy" but the k-hierarchy derivation is not invoked; the NIST number is. | BORROW-SMUGGLE (G) | `benchmarks…cpp:560` |
| F4 | **B23 / B24 / B03 / B12 / B20** | **IDENTITY-PASS cluster.** B23: SDT `k_e e² = αℏc` vs "codata" `k_e e²` — but α≡k_e e²/(ℏc), so this is a definitional tautology (laws.hpp itself: class F, "FAILS delete-test", "relabel from Derived — it is an identity"). B24: V_p/V_e ≡ m_p/m_e by construction (same 3ℓ_P³c²/Φ factor cancels). B03: `bohr_velocity`=αc vs αc. B12/B20: zk²=1 is the closure *definition* z≡1/k². All stamped DERIVED and PASS at ~0 error. | IDENTITY-PASS | recompute: B23 rel-diff 6e-10; `laws.hpp:1016-1022` self-flags F; `coulomb_identity` + `bridge::zk2_product`. |
| F5 | **B22 P_eff, f_transfer** | Stamped **COMPUTED**, but laws.hpp provenance block says **class E, CALIBRATED, "FAILS delete-test — hydrogen calibration fixes the scale", "load-bearing fitted pressure."** The benchmark's certification is softer than the engine's own honest label. | mislabel CALIBRATED→COMPUTED | `laws.hpp:359-364, 371-374` vs `benchmarks…cpp:577,580` |
| F6 | **state28d.hpp `1e10` / `1e-20`** | Two un-derived scale constants (`tanh(T_5/1e10)`, `Phi_5/1e-20`). `1e10` is a **dormant fitted parameter** in the Coulomb↔Gravity occlusion selector (live if T_5≠0); `1e-20` is in a dead function. Neither is consumed by the B-suite. Per FLM01 self-correction this is a **closure debt**, not to be amputated. | hidden-constant / orphaned | `state28d.hpp:134,159`; grep confirms only caller is FLM03 (T_5=0). |
| F7 | **B15 / B16 / B25-exact** | B15 `r_s_sdt = 147.0` typed ("from detailed SDT computation" — not shown). B16 `exponent_sdt = 0.5000` typed. B25 `E_exact = -79.0052` is the **Pekeris 1959 QM value** compared to −79.005 (borrowed answer, 0.0003% "PASS"). | HAND-WRITTEN | `benchmarks…cpp:446,461,643` |
| F8 | tally record | Memory/docs say **54/65**; real is **62/73**. Stale, not a fault in the code. | MINOR / bookkeeping | run output above |

**Tolerance-edit check (was any widened past a near-miss?):** No fail was flipped. B03 tol 1.0% (comment: factor-½ is j-structure, actual err 0.006% — huge margin, edit irrelevant to pass). B14 widened 1%→12% (comment-documented) but every galaxy already lands ≤4.2%, so it would pass at a tighter bar too — the widening is honest-but-unnecessary, **not a RETRO-PASS rescue**. B04 tol 1.0% with err 0.57% — the margin is real; the fault there is F1 (the value is typed), not the tolerance.

---

## Verdict line

> **Prompt completion A** (both benchmarks built + ran; real tally captured; every header grepped and its consumers traced) ·
> **Physics class of the suite: MIXED** — ~15 fair derivations, but **F1 (B04) is a live FABRICATED value** carried into a PASS, **F2/F3/F7 are hand-written/borrowed numbers**, **F4 is a 5-benchmark IDENTITY-PASS cluster**, **F5 downgrades two CALIBRATED constants to COMPUTED at the wire.** ·
> **Recovery:** F1 → retract B04 as the APS04 audit already demands (PPT08 OPEN); F2/F3/F7 → relabel BORROW/OBSERVED not DERIVED; F4 → relabel IDENTITY not DERIVED (laws.hpp already does for B23); F5 → restore the engine's own class-E label; F6 → CLOSE (derive screening scale) per FLM01, do not delete. ·
> **Cascade root:** the honest-labelling gap between `laws.hpp` provenance blocks (which are rigorous) and the benchmark `Certification` enum (which is looser) — the engine tells the truth; the benchmark rounds it up.

— HUNTER · BENCH_ENGINE · 2026-07-02
