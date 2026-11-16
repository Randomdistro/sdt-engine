# RUN_LOG — CM07 Ferromagnetism as Aligned Vortex Wakes

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-04.
> Append-only. Pre-commitments written BEFORE any tool code exists.

## Pre-Run Commitments — CM07

- Prompt completion target: **C**
- Physics class hoped: **CONVERGENCE**
- CALIBRATED budget: **0** (the exchange formula below is committed with NO free coefficient).
  MAGNETON budget: **0 (absolute)** — every magnetic quantity in wake counts and native units.
- Engine namespaces: `measured` (hbar, m_e, k_B, alpha), law_III (occlusion), law_VI (wake
  circulation), EMC03 (handedness), CM04 (thermal disorder), NP17 precedent (α-geared coupling).

### The committed exchange hypothesis (H, declared with provenance)

**J = α · ℏ²/(2 m_e d²)** — the wake-overlap energy at the confinement scale (the SAME FD02/Law VI
door as CM01 v_pack and CM03 E_g), geared down by the handed-redirection coupling fraction α
(NP17 precedent: EM-mediated binding is the confinement scale geared by 1/137).
**k_B T_C = z · n_w · J** — coordination × aligned-wake count × exchange.

*Provenance honesty:* this H was formed by mechanism analogy (NP17 gear-down + shared confinement
door) with rough hand arithmetic during prompt analysis suggesting viability BEFORE this log; that
is disclosed here, the gates below are still pre-committed before the tool exists, and the
look-elsewhere caveat (α vs any other small factor) is carried into the verdict as a standing
falsification duty: the formula must survive out-of-family tests it was never sighted on.

### Phase thresholds (committed)

- **P1 (exchange sign):** co- vs contra-rotation occlusion. Committed honesty: the run computes
  |J| natively; the SIGN separation (why Fe/Co/Ni co-rotate but Cr/MnO contra-rotate) is NOT
  derivable from the magnitude formula — expected outcome **OPEN on first-principles sign**
  (pivot-table row "report both signs"). Ferro/antiferro classes enter as OBSERVED anchors only.
- **P2 (Curie points):** predicted T_C = z·n_w·α·ℏ²/(2 m_e d² k_B) for the three direct-overlap
  (3d) ferromagnets. Gates: ordering **Co > Fe > Ni exact**; each magnitude within **2×** of
  measured 1388 / 1043 / 627 K (anchors). **Scope declared pre-run:** direct-overlap 3d metals
  only; Gd (4f, indirect/RKKY-mediated — no direct 4f wake overlap) is OUT OF SCOPE and will be
  printed as an out-of-scope exhibit, expected to FAIL — showing the boundary is real, not hidden.
- **P3 (M(T)):** mean-field self-consistent alignment fraction; gates: M(T) → 0 at T_C;
  effective exponent β = 0.5 ± 0.1 fitted on t = 1−T/T_C ∈ [1e-4, 1e-2]. All magnetisation
  quoted as **aligned-wake count per atom** (dimensionless count × the electron's own wake
  circulation κ_e = h/m_e as the native unit). n_w values (2.22, 1.72, 0.606) are MEASURED
  saturation counts — measured moment ÷ one electron wake unit; the borrowed-unit NAME never
  appears; flagged openly: the native single-wake unit is numerically the same object the rival
  calls its unit — the rule's content is the narration and the count, and the count is what we use.
- **P4 (hysteresis):** 1-D domain-wall in a seeded (index-derived, no RNG) pinning landscape;
  gates: finite coercivity (loop opens, h_c > 0) and remanence > 0.5 of saturation at h = 0.
- Forbidden: μ_B/μ_N anywhere (automatic FAIL); spin operators / Heisenberg machinery as
  mechanism; per-element refit of z, n_w, or any coefficient; tolerance widening.

### §G mirror (pre-run)

- Faith ledger: (a) the α gear-down — *the* faith item in this run; named; its test is the
  out-of-family duty above; (b) the confinement door (shared, named cluster-wide); (c) n_w as a
  measured count. No rival axiom polices a gate; anchors are measured T_C, structures, moments.
- Gatekeeper: mean-field self-consistency is generic statistics (not a Heisenberg import); the
  Heisenberg Hamiltonian itself is a target, not machinery — none of its operators appear.

## MEASURED-INPUT ledger (frozen)

| Element | structure | z | d_nn [Å] | n_w [wakes/atom] | T_C obs [K] | role |
|---|---|---|---|---|---|---|
| Fe | BCC | 8 | 2.482 | 2.22 | 1043 | committed |
| Co | HCP | 12 | 2.507 | 1.72 | 1388 | committed |
| Ni | FCC | 12 | 2.492 | 0.606 | 627 | committed |
| Gd | HCP | 12 | 3.573 | 7.63 | 293 | OUT-OF-SCOPE exhibit (4f) |
| Cr | BCC | 8 | 2.498 | — | T_N = 311 | OBSERVED antiferro contrast |

## Phase gate record (from real stdout only)

- Run 1 (2026-07-04, preserved in git history of `cm07_results.txt`):
  P1 |J| = 4.42–4.51 meV, sign OPEN as committed · **P2 ALL PASS** (Fe 0.892, Co 0.763, Ni 0.603;
  ordering Co>Fe>Ni exact; Gd exhibit 7.90× out-of-scope FAIL as declared) ·
  P3 M→0 PASS but **β = 0.2109 FAIL** · P4 h_c = 0.3 PASS but **remanence 0.067 FAIL**.
- Run 2 (after ADJ-1/ADJ-2 below; run-1 stdout preserved as `cm07_results_run1.txt`):
  P2 unchanged (all PASS — the physics chain was untouched by the ADJs) ·
  P3 **β = 0.4993 PASS** (solver fixed, gate unchanged) · P4 **remanence 1.000 PASS,
  h_c = 0.80 PASS** (toy now saturable, gates unchanged). P1 sign remains OPEN as committed.

### ADJ register

- **ADJ-1 — P3 numeric solver (allowed: finer numerics; gate UNCHANGED at 0.5 ± 0.1).**
  Trigger: β = 0.2109. Diagnosis: fixed-point iteration m ← tanh(T_C/T·m) converges as slowly as
  1/(1−slope) near T_C; at t = 1e-4 the 400-iteration value is far from the fixed point, so the
  fit measured solver error, not the exponent (analytic mean-field β is ½ — the run must EARN it
  numerically, not have it asserted). Fix: bisection on f(m) = tanh(T_C/T·m) − m (exact fixed
  point to 1e-15). Physics unchanged; threshold unchanged.
- **ADJ-2 — P4 toy construction (allowed: the toy has NO measured anchor; gates qualitative and
  UNCHANGED: remanence > 0.5, h_c > 0).** Trigger: remanence 0.067 with h_c 0.30. Diagnosis: max
  pinning force (~4.4) exceeded the maximum drive (1.0), so the wall never saturated — the toy
  tested "drive too weak to move a wall", not hysteresis. Fix: pinning amplitude reduced (0.02/k →
  0.004/k) so h_max > max pinning force and the wall can saturate; remanence sampling window
  |h| ≤ 0.011 (FP-safe). This is a demonstration-construction repair, not a calibration — no
  measured quantity is targeted by the toy.
