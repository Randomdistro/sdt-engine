# CQ-32 · GATE G1 — RUN LOG (append-only)

Protocol: **CQ-32 (Gate G1: The Price of Displacement)**, prepared 2026-06-11, J. Tyndall / Fable.
Executor: Claude (Opus 4.8). SDT v6.0+ ruleset in force. Deliverable **D9**.

---

## RUN 1 — STAGE 0 (preparation · constants ledger · environment)

### 0.1 Environment
- `packing.hpp` located at `Engine/include/sdt/packing.hpp` — **not yet compiled**: no C++ compiler on PATH
  (`cl`, `g++` both NOT FOUND). → **BLOCKER-1**: Candidate C (packed-lattice volume) blocked pending MSVC
  `vcvars` location or a Python reimplementation of the lattice count.
- Python 3.13 available (`...\Python313\python.exe`). Candidates A (analytic) and B (Monte-Carlo) feasible.

### 0.3 Constants ledger (MEASURED-INPUT / corpus) — judged BEFORE any result page (R2)
- From `laws.hpp`: `Φ = N·ε` (Law I); `P_conv = Φ/ℓ_P³ = 2.459×10⁴⁸ Pa`; `V_disp_from_mass(m)=3mℓ_P³c²/Φ`;
  rest energy `E₀ = Φ·V_disp/(3ℓ_P³) = mc²`. **The functional `E=(Φ/3ℓ_P³)·V_disp` is Law IV already in the
  engine; with V_disp taken FROM mass it is the identity `E=mc²`** — verified: `P*·V_disp_p = 938.272 MeV =
  m_p c²`. So a non-trivial test REQUIRES V_disp from independent geometry, never from mass. [confirms protocol §0]

### 0.4 Reaction set (frozen)
R1 d+d→α · R2 t+p→α · R3 h+n→α · R4 d+t→α+n · R5 d+d→t+p · R6 d+d→h+n · R7 α+d→⁶Li · R8 2α+n→⁹Be.
Acceptance: ONE volume definition prices all eight within ±15% (max/min ≤ 1.35).

### 0.X — LEDGER FINDING: the Machian price equivalence carries a 10¹⁵ unit slip
Audit script: `stage0_units.py` (this folder). Verified numerically:
```
P_conv = 2.459×10⁴⁸ Pa  =  1.5348×10¹⁶ MeV/fm³     (protocol §0 says "15.35 MeV/fm³")
15.35 MeV/fm³           =  2.459×10³³ Pa             (protocol §0 says "2.459×10⁴⁸ Pa")
ratio                   =  9.999×10¹⁴  ≈ 10¹⁵
```
- **Mantissa tell:** `1.5348e16` vs `15.35 = 1.535e1` — identical mantissa, exponent dropped by 15.
- **Provenance:** repo-wide grep finds `15.35 MeV/fm³` **nowhere**. It is NOT an independent corpus quantity —
  it is `P_conv` re-expressed in MeV/fm³ with 15 orders dropped. The "two-instrument agreement on 2.459" is
  therefore one number compared to itself at the wrong scale.
- **Scale check:** pricing a geometric ~1 fm³ volume at the Planck price `P*=Φ/3ℓ_P³` overshoots nuclear
  binding by ~3×10¹⁴ (1 fm³ → 5.1×10¹⁵ MeV). The failed charge-radius prices (0.381, 3.544 MeV/fm³) and the
  target 15.35 MeV/fm³ all sit at the **nuclear scale ~10³¹–10³³ Pa**, i.e. ~10¹⁵ BELOW `P_conv`.

### 0.X — IMPLICATION for the gates
- **Gate G1 (one nuclear price across 8 reactions?)** — scale-correct, UNAFFECTED. Expect ~few–15 MeV/fm³.
  Proceed (Stages 1–3).
- **Gate G1-M (the Machian "Eddington" gate)** — as written compares a nuclear price (~10³³ Pa) to the Planck
  `P_conv` (2.459×10⁴⁸ Pa), 10¹⁵ apart, via the slip above. **Cannot pass G1-M(a) at face value.** By the
  protocol's own Stage 3.3 this is outcome (c) — "constant but local, not cosmological" — UNLESS a *derived*
  ℓ_P³→fm³ scale factor of ~10¹⁵ exists (outcome (b)), which R5 requires deriving first, not inferring from a
  mantissa coincidence.

### DECISION POINT for J.T. (before committing the deep Stages 1–3)
The Machian reading is the protocol's "defining page," so logging and pausing here rather than spending it down:
- **(A)** Proceed with Gate G1 at the nuclear scale; reframe G1-M as local-vs-cosmological, honest default =
  local until a bridge is derived.
- **(B)** First attempt to DERIVE an ℓ_P³↔fm³ bridge (~10¹⁵) from SDT geometry; if it exists, G1-M is
  rehabilitated; if not, the Machian reading is the (valuable) negative result.
- **(C)** J.T. supplies a provenance for 15.35 MeV/fm³ not found in the repo.

**RESOLUTION:** J.T. "continue" → proceed on **(A)**: run Gate G1 at the nuclear scale; G1-M reframed as
local (honest default) pending a derived ℓ_P³↔fm³ bridge. Side note (script): the would-be bridge is doubly
unlikely — the price ratio is 10¹⁵ but the proton's throughput volume / geometric-tube ratio
(1.83×10⁻¹³ fm³ / ~14 fm³ ≈ 1.3×10⁻¹⁴) is ~10¹⁴, so even the scales of the two ratios don't agree.

---

## RUN 1 — STAGE 1 (block topology declarations, frozen) — see `declarations.md`
- D1 = merger neutron; D2 = linked tubes (alternates → Stage 6). Radii from W+1 rule.
- proton tube: a=0.8412 fm, R=1.0303 fm, V_free=14.392 fm³; neutron: 0.8401 / 1.0289 / 14.333 fm³.
- conscription radius r_c = 2.818 fm (nucleon c-boundary). Electron a_e=772 fm logged UNDER TENSION, unused.
- **Pivotal frozen open:** inter-block separation `s` for the conscription overlap — parameter-free only if
  from tube-contact/gear-mesh, never measured charge radii.

## RUN 1 — STAGE 2 (Candidate A) — `stage2_volumes.py`
- Free-tube volumes computed (linked model). **Result: ΔV_free = 0 EXACTLY for all 8 reactions** (every
  reaction conserves nucleon content). → **Candidate A (tube volume) is a NULL channel: predicts zero binding
  for all eight.** Logged negative (R4).
- **Structural consequence:** binding lives ENTIRELY in the overlap/deficit. And *linked solid tubes interlock
  without sharing solid volume*, so the deficit is NOT in the tube solid either → it must be in the
  **wake/conscription overlap (Candidate B)**, governed by the inter-block separation `s`.
- **Therefore Gate G1 reduces to: derive `s` (the mesh separations) from tube-contact/gear geometry.** This is
  the same unbuilt mesh-geometry as the stack's ROOT-SIM / the Energy-Functional V_disp. Candidate B is the
  next computation; Candidate C (packing.hpp) remains BLOCKER-1 (no compiler).

### STATUS after Run 1
Stage 0 ✔ (env + ledger + the 10¹⁵ G1-M finding) · Stage 1 ✔ (declarations frozen) · Stage 2 Candidate A ✔
(null channel — clean negative). NEXT: Candidate B conscription-overlap, pivoting on the derived separation
`s` — the crux, and the bridge to ROOT-SIM.

## RUN 2 — STAGE 2 Candidate B (conscription overlap) — `stage2b_candidateB.py`
Parameter-free: r_c = 2.818 fm (nucleon c-boundary); s = 2·R_ring = 2.0606 fm (ring-edge contact);
V_disp = union of A conscription spheres at declared positions (d=dimer, t/h=triangle, α=tetra, edge s).
MC 1e6 pts, seeded. **Two-stream verified:** deuteron MC union vs analytic 2-sphere lens = **+0.08%**.

Price `P = Q/(−ΔV)` (MeV/fm³) via sealed `compare.py`:
```
R1 dd→a 0.293 · R2 tp→a 0.297 · R3 hn→a 0.309 · R5 dd→tp 0.272 · R6 dd→hn 0.220   ← 5 cluster (spread 1.40)
R4 dt→a+n 0.798   ← clean outlier 2.7× (small union-change, large Q; only d+t→α+n channel)
R7 ad→Li6 0.0156 · R8 2an→Be9 0.0111   ← ~20× LOW, FLAGGED: Li6=octahedron, Be9=crude 2-tetra+n,
                                          NOT grammar-faithful α+d / 2α+n → arrangement artifact, not the model
```
**GATE G1: FAIL** (spread max/min = 71.9; bar ≤1.35) — dominated by the flagged R7/R8.
**Sub-threshold signal:** 5 of 6 *clean* reactions converge on ONE price ≈ 0.28 MeV/fm³ within ±20%
(spread 1.40) with parameter-free s. R4 the lone clean outlier; R7/R8 fail on MY arrangement guess.
**G1-M:** mean clean price ≈ 0.28 MeV/fm³ ≈ 5.5×10³¹ Pa — *local*, ~55× below corpus 15.35 MeV/fm³, ~10¹⁷
below Planck P_conv → Machian reading stays dead (outcome c). (0.28 sits near the failed charge-radius 0.381.)
**Diagnosis (3.4):** residuals sort by (i) flagged arrangement (R7,R8), (ii) free-nucleon-in-products+α (R4).
The 5/6 convergence says a single price plausibly EXISTS but the geometry is not yet FORCED (arrangement
freedom = the D1/D2 "more than one way to be"). Pinning it = forcing the geometry (ROOT-SIM) — same step the
north-star needs for choosable scission.
NEXT: grammar-faithful α+d / 2α+n (R7/R8); dissect R4; s & r_c sensitivity (Stage 6).

## RUN 2b — Candidate B v2 (grammar-faithful R7/R8) — `stage2b_candidateB_v2.py`
Li6 = α + EXTERNAL deuteron off one face; Be9 = 2α (vertex-in) + bridging n. Same parameter-free r_c, s.
- R7 0.0156→**0.0219**, R8 0.0111→**0.0176** (moved the right way), cluster R1/2/3/5/6 unchanged ≈0.28, R4=0.798.
- **GATE G1: still FAIL** — spread 72×→**45×** (bar ≤1.35). Tightened, not rescued.
**Why R7/R8 stay ~13–16× LOW (a REAL finding, not arrangement):** the model OVER-predicts binding for
*loosely-bound cluster nuclei*. ⁶Li's α–d bond is only 1.47 MeV, but conscription-overlap-at-contact-`s`
creates a 67 fm³ union reduction → predicts large binding. ⁶Li/⁹Be physically have α–d / α–α separations
≫ s (~3.5–4 fm), so the single contact-`s` is WRONG for them.
**Why R4 stays high (0.80):** d+t→α+**n** ejects a free nucleon → its conscription sphere re-enters the
product union → small |ΔV| (22) vs large Q (17.6). The deficit over-counts the already-compact d,t.
**Root:** single-nucleus BE/deficit rises 0.050(d)→0.082(t)→0.166(α)→0.135(Be9) — the union-deficit does NOT
scale with binding, so **no single price exists under contact-`s` geometry.** The separation is not universal;
it is binding-dependent — i.e. the geometry is **not yet forced** (the same D1/D2 "more than one way to be").
**VERDICT (R4 honesty): Candidate B with a single parameter-free contact `s` FAILS Gate G1.** Clean negative.
The 5/6 tight-core cluster ≈0.28 MeV/fm³ is a partial signal, not a pass. Do NOT tune `s` per reaction (R5).
**Principled next (no tuning):** (a) Stage 4 declared fallback E = P·ΔV + σ·ΔA (calibrate on R1–R4, predict
R5–R8); (b) derive *binding-dependent* separations from the gear-mesh (ROOT-SIM) — the forced geometry that
closes G1 and serves the north-star; (c) Candidate C (packing.hpp) once a compiler is located.

## RUN 3 — STAGE 4 declared fallback (G4) — `stage4_geom.py` + `stage4_fit.py`
E = −(P·ΔV + σ·ΔA), union volume + union surface area (MC, surface via exposed-fraction estimator).
Calibrate (P,σ) least-squares on R1–R4 [CALIBRATED(2)]; predict R5–R8 blind.
- Calibrated P=1.996 MeV/fm³, **σ=−1.367 MeV/fm² (negative — unphysical surface sign)**.
- Even the CALIBRATION set won't fit: R1 +17.0%, R2 −11.6%, R3 −8.6%, R4 −15.0% (2 params can't reconcile the
  α-formers with R4).
- Blind predictions: R5 **+158%**, R6 **+178%**, R7 **+1099%**, R8 **+161%**.
- **GATE G4: FAIL.**
**Candidate C note:** not run (no compiler) but **reduces to the Candidate-A null channel** — C counts displaced
*tube* sites (= V_disp tube), which is nucleon-conserved → ΔV_C = 0. The only binding-bearing channel is the
conscription overlap (B). So all three declared candidates are covered: A null, C≡A null, B fails G1+G4.

### HALT (protocol Stage 4) — two failures of the deficit form → KILL REPORT (D5), see `KILL_REPORT.md`.
The linear energy functional **E = price × geometric-deficit is FALSIFIED at the nuclear scale** in both
pure-volume (G1) and volume+surface (G4) forms. Successor named: **E = ℏ·Δω** (gear-frequency of meshed
circulation); acceptance test = the H₂ frequency-pull. Five locks re-route.

