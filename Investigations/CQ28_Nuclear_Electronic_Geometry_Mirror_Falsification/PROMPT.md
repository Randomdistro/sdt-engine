# CQ28 — Independent Nuclear–Electronic Geometry Mirror **Falsification** Test

> ## Rule 18 is not assumed. **Rule 18 is placed on trial.**

Rule 18 ("the proton is the code" — electron-shell geometry is a projection of nuclear geometry) is the framework's most beautiful claim and its most dangerous one to *visualise*, because a picture can fake it. This investigation exists to give that claim a **hostile, falsifiable trial** — never a render.

---

## 0. The fatal circularity this investigation must never commit

The mock-up's contamination, stated plainly so it is never repeated:

```
electron-shell order  →  nuclear placement  →  electron/nuclear "match"
```

That is **not a discovery. That is a stencil.** If nucleons are placed in electron-Aufbau order (`2S→2P→3S…` square antiprisms), the mirror is *baked in*, and any subsequent "agreement" is the input read back out. The original `atomicus-stick-v3` did exactly this (`SUBSHELLS`/`buildStructure` use the electron fill order) and is therefore **contaminated for mirror testing** — demoted to `ATOMICUS/Deprecated_Visual_Mockups/atomicus-stick-v4-CONTAMINATED.html`, evidence-barred.

The only valid pathway is the inverse:

```
alpha grammar  →  deuteron/triton count lattice  →  INDEPENDENT packing/equilibrium solve
              →  nucleon topology imposed on solved positions
              →  electron topology generated INDEPENDENTLY
              →  score correspondence against null models
```

Generate the nucleus **without electron assumptions**. Generate the electrons **without nuclear assumptions**. *Then* compare. If correspondence survives that, it is real; if it dies, the by-products are still valuable.

## 1. The two tangled claims (must be tested separately, never allowed to backfill each other)

| | claim | type | where tested | does it prove geometry? |
|---|---|---|---|---|
| **Claim 1** | every isotope = `1α + n_d·d + n_t·t` | arithmetic / transition grammar | **CQ28A** | **No** |
| **Claim 2** | nuclear *equilibrium* geometry corresponds to electron shell/subshell geometry | geometric / topological | **CQ28E** | **This is where Rule 18 lives or dies** |

**The cardinal sin:** letting Claim 2 backfill Claim 1's visuals. Claim 1 is true arithmetic and proves nothing geometric; Claim 2 must be earned independently.

## 2. The central falsifiable question

> Can a nuclear geometry produced **only** from the α/deuteron/triton grammar and equilibrium packing — with **zero** electron input — *predict, resemble, constrain, or topologically permit* electron shell/subshell geometry **better than null models** by a pre-registered, fixed metric?

Answer is YES only if the mirror score beats every null/negative control at a pre-declared significance. Otherwise Rule 18 is **falsified at the geometric level** (Claim 1 may still stand).

---

## 3. Architecture — five sub-investigations, strict one-way dependency

```
CQ28A  Alpha-Grammar Validity ─────────────► (validated grammar maps)
CQ28B  Independent Nuclear Equilibrium ────► (nuclear positions, NO electron input)
CQ28C  Trefoil Nucleon Topology ──────────► (6π/toroidal nucleons ON CQ28B positions)
CQ28D  Electron Threading Feasibility ────► (can electrons thread without intersection?)
CQ28E  Mirror-Score Falsification ────────► (independent nuclear vs independent electron, scored vs nulls)
```

Each sub-folder has its own `PROMPT.md` with **inputs · outputs · fixed metrics · null/negative controls · failure criteria · logged parameters**. Summary:

### CQ28A — Alpha-Grammar Validity *(Claim 1, arithmetic only)*
- **In:** full isotope table (Z, A). **Out:** `(n_d, n_t)` map + validity flag per isotope.
- **Metric:** fraction mapping cleanly to `1α + n_d d + n_t t` with `n_d, n_t ≥ 0`; decay-transition closure (`α, β⁻, EC, n` vectors).
- **Null:** random `(n_d,n_t)` assignment must NOT satisfy the inverse `Z=2+n_d+n_t, A=4+2n_d+3n_t`.
- **Fail:** any stable isotope failing the inverse map, or a decay vector breaking conservation. *(Largely DONE: `nuclear.hpp` 7 static_asserts + `CQ25`; this stage re-certifies and is the only "uses electrons = forbidden? no — uses nothing electronic" clean foundation.)*
- **Reuses:** `nuclear.hpp` (`alpha_grammar`, `h3_grammar`, fission identities), `CQ25`.

### CQ28B — Independent Nuclear Equilibrium *(positions, electron-blind)*
- **In:** `(n_d, n_t)` block count from CQ28A **only**. **Out:** 3-D block positions per isotope, solved.
- **Method:** Tammes/Thomson equilibrium (max-min angular separation) + kissing radius `r = sin(θ/2)/(1−sin(θ/2))`, reproducing `packing.hpp` presets (tetra-4, octa-6, antiprism-8, icosa-12) as **emergent** results. Tritons take maximally-separated sites.
- **HARD BAN:** no `SUBSHELLS`, no Aufbau order, no electron-shell radius, no `2n²`. Any such call must be named `contaminated_visual_mockup_only()` and is barred from this stage.
- **Metric:** convergence to the Thomson minimum; reproduction of `packing.hpp` angles (θ_min) to <2%; determinism (fixed seed → identical output).
- **Null:** random sphere placement (no relaxation) as the baseline geometry to beat in CQ28E.
- **Fail:** positions depend on any electron quantity; non-deterministic output; divergence from `packing.hpp` presets.
- **Reuses:** `packing.hpp`, the verified equilibrium solver.

### CQ28C — Trefoil Nucleon Topology *(embodiment, positions FROZEN from CQ28B)*
- **In:** CQ28B positions (frozen). **Out:** each nucleon as a 6π (2,3) trefoil / toroidal structure at its solved site.
- **Rule:** topology is *imposed on* solved positions — it may **not** move them. Rendering ≠ evidence; this stage produces the substrate CQ28D tests.
- **Metric:** knot validity (closed (2,3)), radial orientation, `R_p`-scale tubes; no position drift vs CQ28B.
- **Fail:** any nucleon position differs from CQ28B; knot degenerate.
- **Reuses:** `laws.hpp::winding`, `CQ11`/`CQ14` trefoil.

### CQ28D — Electron Threading Feasibility *(topological permission test)*
- **In:** CQ28C nuclear topology. **Out:** per-electron Hopf-fibre path through a proton poloidal channel, with an **intersection test**.
- **Question:** can `Z` electron paths be threaded through/around the nuclear topology **without intersecting** the nucleon tubes or each other — using real non-overlap constraints (not "rings outside the nucleus")?
- **Metric:** # of electrons placeable with zero tube/tube and tube/loop intersection; minimum clearance; whether a full Hopf-fibration (every fibre linked, none crossing) is realisable for the shell count.
- **Null:** random electron paths; expected high intersection.
- **Fail:** feasibility declared without an explicit intersection metric; Bohr-`2n²` ring simplification used as proof.
- **Honesty:** the v4 "trefoil electrons" used shell rings + `2n²` + linked-loop styling — **that is feasibility *theatre*, not a solve.** This stage replaces it with a real intersection solver.

### CQ28E — Mirror-Score Falsification *(where Rule 18 lives or dies)*
- **In:** CQ28B nuclear geometry (electron-blind) **and** an electron shell/subshell geometry generated **independently** (from spectroscopy / orbital angular maxima, with **no nuclear input**). **Out:** a correspondence score + significance vs nulls.
- **Pre-registered fixed metrics (declared BEFORE running):** e.g. (i) directional alignment of nuclear block lobes vs electron orbital lobes (mean min-angle), (ii) symmetry-group match (point-group of nuclear cluster vs electron shell), (iii) count/closure coincidence (does a nuclear-geometry closure land on a noble Z?), (iv) valence-class prediction accuracy.
- **MANDATORY controls:** (a) **null model** — random sphere geometry (CQ28B null); (b) **negative control** — a *different* element's nuclear geometry vs this element's electrons; (c) **statistical baseline** — distribution of the score under shuffled assignments; (d) report effect size + p-value.
- **PASS:** the real nuclear-vs-electron score beats all nulls/negatives at pre-registered significance across the isotope set. **FALSIFIED:** it does not — and that is a *publishable* result, not a failure of the project.
- **Forbidden:** declaring correspondence before scoring; manual rotation until pleasing; the contaminated mock-up as evidence.

---

## 4. Discipline — FORBIDDEN and REQUIRED (binding on every coding agent)

**FORBIDDEN**
```
electron-Aufbau-derived nuclear placement
electron-shell ordering used as a nuclear layout heuristic
manual visual alignment / post-hoc rotation until pleasing
Bohr-2n² ring simplification used as proof
declaring correspondence before scoring
using the mock-up as evidence
```

**REQUIRED**
```
nuclear geometry generated independently (electron-blind)
electron geometry generated independently (nuclear-blind)
fixed scoring metrics declared BEFORE comparison
negative controls + null models + statistical baselines
explicit failure criteria
logged parameters + fixed seeds + reproducible outputs
```

**Quarantine rule.** Any code path that places nuclear objects using electron-shell order MUST be named `contaminated_visual_mockup_only()` and is barred from every metric-producing test. The demoted mock-up carries a red warning header (see `ATOMICUS/Deprecated_Visual_Mockups/`).

## 5. Why this strengthens the project (even if Rule 18 dies)

The test is now **hostile**: generate nucleus without electrons, electrons without nucleus, then compare. If correspondence survives *that*, it is far more interesting than any picture. If it fails, the retained artefacts are still valuable:

```
valid isotope grammar maps      (CQ28A)
independent nuclear packing engine (CQ28B)
decay transition vectors        (CQ28A)
topological nucleon renderer    (CQ28C)
electron-threading solver       (CQ28D)
mirror-score falsification framework (CQ28E)
```

## 6. Provenance discipline (`FORMULATIONS_PROVENANCE_AUDIT.md`)
- CQ28A grammar maps: **C** (SDT-derived, known-match, isotope integers).
- CQ28B positions: **B** (SDT-derived, internal-only) — *electron-blind by construction*.
- CQ28E mirror score: **D** (novel-prediction) if it beats nulls; **F (falsified)** if it does not — **either outcome is a result**. The delete-test (`§4`) is automatic here: the nuclear geometry is generated with the electron data *deleted*, so a surviving score cannot be circular.

*Author attribution: James Christopher Tyndall, Melbourne.*
