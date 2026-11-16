# RUN_LOG — NP07 Primordial Lithium Resolution

> **Author of run:** executor (agent), on behalf of J. C. Harvey investigation spec.
> **Run date:** 2026-07-03. **Engine:** `sdt/laws.hpp` (measured::alpha, m_e, c, eV), `sdt/nuclear.hpp`.
> **Tool:** `np07_lithium.cpp` (MSVC, C++20). Append-only during the run.

---

## Pre-Run Commitments — NP07

- **Prompt completion target:** realistic **C** — the grammar/mechanism phases are executable;
  the prompt's phases 2–4 (destruction integral during the ionised window, final Li-7/H) require
  (a) a native SDT primordial thermal history (does not exist; SDT rejects the expansion
  framework and its own cyclic cosmology is uncommitted) and (b) measured σ(p + Be-7 → B-8)
  data (NACRE/EXFOR — not in repo). If they cannot be closed natively, the committed verdict is
  an honest **OPEN with a mechanism map** — no plugging, no borrowed BBN network as load-bearing.
- **Physics class hoped:** NATIVE for the grammar selection rule (imported from NP18, re-run
  here); OPEN for the quantitative resolution.
- **CALIBRATED budget:** 0.
- **Anchor discipline (per §B):** the observed Spite-plateau Li-7/H = (1.58 ± 0.31)e-10
  (Sbordone 2010) is the OBSERVED anchor. The BBN prediction (4.68 ± 0.67)e-10 (Cyburt 2016)
  is a RIVAL's number — comparison column ONLY; it may parameterise what a mechanism *would*
  need to deliver, never enter an SDT chain as truth.

### Phase thresholds (committed BEFORE run)

- **P0 grammar (NATIVE, exact integers):** Be-7 α-grammar = (3,−1) INVALID (n_t < 0 underflow);
  Be-7 H3-grammar = (2,0) VALID (He-3 core — the EC-isotope alternate grammar); Li-7 = (0,1)
  valid; Li-6 = (1,0) valid; single EC vector (Δn_d,Δn_t) = (−3,+2) maps Be-7 → Li-7 exactly.
  Any mismatch → STOP. (Cross-checks NP18 Phase 0.)
- **P1 seat scale (ENGINE MACHINERY ONLY):** innermost-seat velocity from the engine's own
  `atomic::bohr_velocity(Z, n)` (the k-ladder kinematics already in `laws.hpp`), stripping
  cost = ½ m_e v² (pure kinematic reorganisation cost). Gate: E(Z=4, n=1) within 0.5% of
  217.7 eV. **ADJ-001 (before first run):** an earlier draft of the tool phrased this route
  through the "hydrogenic closed form" — struck on Harvey's direct instruction (no imported
  formalism; pure calculative machinery). Same gate value; the chain now touches only
  `laws.hpp` functions + kinematics. The draft never ran; no output existed before this change.
- **P2 required-destruction fraction (RIVAL-COMPARISON arithmetic):** f = 1 − 1.58/4.68 with
  uncertainty propagated from both quoted errors. This quantifies what ANY pre-EC destruction
  mechanism must deliver *if* the rival's production number were taken at face value. It is
  bookkeeping about the discrepancy, not an SDT prediction.
- **P3 closure decision (committed):** an SDT-quantitative resolution may be claimed ONLY if
  both (i) a native thermal/density history and (ii) measured destruction cross-sections are
  available in-chain. Neither is. Therefore the committed reachable outcome is OPEN with the
  mechanism map + named data needs. Anything better found mid-run must still pass §C.

### Forbidden

- BBN network codes as load-bearing; plugging the 3× factor; treating 4.68e-10 as an SDT truth;
  inventing a destruction rate; treating delayed-EC alone as a resolution (EC conserves mass-7 —
  the SIGN analysis must be shown, not assumed).

---

## Phase execution record

*(to be appended AFTER the run, from the real stdout in `np07_results.txt` — never before)*
### Phase record (appended from real stdout, np07_results.txt — run 2026-07-12, Fable direct, NO agent)

- Build: MSVC BuildTools 2022 x64, `cl /std:c++20 /EHsc /O2 /I Engine\include`. BUILD_EXIT=0, RUN_EXIT=0.
- **P0 grammar gate: PASS** — Be-7 α-grammar (3,−1) INVALID (underflow); H3-grammar (2,0) valid;
  Li-7 (0,1), Li-6 (1,0) on-lattice; EC vector (−3,+2) maps Be-7 → Li-7 EXACT. [NATIVE]
- **P1 seat scale: PASS** — engine `atomic::bohr_velocity`: v_seat(Z=4)=8.7508e6 m/s →
  strip cost 217.69 eV vs 217.7 eV ref (err 0.004%). EC-blocking rule: stripped Be-7 cannot EC;
  the EC clock starts at the ~218 eV seat (~16× H). [COMPUTED, scale-setting]
- **P2 rival-comparison bookkeeping**: f = 66.2% ± 8.2% pre-EC destruction required IF the rival
  production number is taken at face value. SIGN analysis shown: delayed EC conserves mass-7;
  reduction requires destruction during the ionised window (p+Be-7→B-8→2α); the SDT EC-block
  LENGTHENS the window — right sign. [RIVAL-COMPARISON only]
- **P3: OPEN** per pre-commit — no native thermal history (i), no σ(p+Be-7) data in repo (ii).
  No final Li-7/H claimed. Deliverable = mechanism map + named data needs.

**Honest outcome: mechanism map earned (P0/P1), quantitative resolution OPEN. No ADJ needed —
run followed pre-commitments exactly.**
