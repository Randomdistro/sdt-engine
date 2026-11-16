# RUN_LOG — NP19: Mass-Defect as Form-Resistance + the Two-Ledger Lemma

> Author: J. C. Harvey, Melbourne. Run executed per `PROMPT_EXECUTION_PROTOCOL.md`.
> Append-only during the run. Pre-Run Commitment Block filled **before** any code was written.

---

## Pre-Run Commitments — NP19  (committed 2026-06-30, before coding)

- Prompt completion target: **C** (four phases, but the ceiling is a reframe not a derivation)
- Physics class hoped: **CONVERGENCE**  # honest ceiling: reframe, not a new fitted number
- CALIBRATED budget: **0**  (no fitted parameters; literals 0.511/1.293/0.782 are OBSERVED-TARGET only)
- Engine namespaces: `measured` (m_e, m_p, m_n, MeV_to_J, c), `law_I` (Phi, P_conv), `law_IV` (V_disp round-trip, P_cf_e)
- Phase thresholds (committed before run):
    - **P1**: round-trip identity < 1e-9; `ρ_form_e` within 1 order of mag of `P_conv/3`; 0 new constants
    - **P2**: `|ΔR − 1.293|/1.293 < 0.1%`; `|(ΔR−τ) − 0.782|/0.782 < 0.2%`; sign `R(n)>R(p)` TRUE; `ΔR>τ` TRUE
    - **P3**: `|ΔR|` identical across boundaries ≤1e-6 rel; both ledgers opposite sign; both-signs construction FAILS
    - **P4**: written reconciliation, energy sourced 100% from ΔR, none from grammar move
- Forbidden retroactive changes: widen tolerances; plug 0.782; flip a sign assertion post-run;
  IDENTITY-PASS (m c² called a mechanism without P2 sign + P3 lemma); local constant namespaces;
  any G/M/GM/ψ/G_F/ΛCDM in the chain.

### Anchors (measured NUMBERS, from `sdt::laws::measured` — NIST/CODATA reference values)
- `m_e = 9.1093837015e-31 kg`, `m_p = 1.67262192369e-27 kg`, `m_n = 1.67492749804e-27 kg`
- `c = 299792458 m/s` (exact), `MeV_to_J = 1.602176634e-13 J/MeV`
- OBSERVED-TARGET literals (comparison only, never inputs): `m_e c² ≈ 0.511 MeV`, `(m_n−m_p)c² ≈ 1.293 MeV`, `Q_β ≈ 0.782 MeV`

---

## Run loop

### ADJ-000 — Language/tooling choice (2026-06-30)
- **Trigger:** §6 allows `np19_ledger.cpp` **or** `.py`. Prompt TOOLING line: "python3 fine (arithmetic + sign checks)."
- **Committed response:** Build BOTH. Primary deliverable `np19_ledger.cpp` (`#include <sdt/laws.hpp>`, the engine-of-record path required by §0 anti-creep). A `.py` mirror is NOT produced to avoid a second, non-engine source of the masses; the C++ tool reads masses only from `sdt::laws::measured`.
- **What changed:** deliverable is C++ only, compiled with MSVC `cl` per the build line in §6.
- **What did NOT change:** no thresholds, no inputs, no targets.
- **Re-run result:** see phase gates below.

---

### Phase 1 — Formalise mass = form-resistance from Law IV

- **PRE-COMMIT:** round-trip `|m − mass_from_V_disp(V_disp_from_mass(m))|/m < 1e-9` for e,p,n; `ρ_form_e` within 1 order of magnitude of `P_conv/3`; zero new constants.
- **EXECUTE:** built `np19_ledger.cpp`, compiled with `cl /std:c++20 /EHsc /O2 /I Engine/include`. Ran; stdout → `np19_results.txt`.
- **ACTUAL:**
    - Round-trip rel. error for e, p, n: `1.92e-16 / 2.14e-16 / 4.28e-16` (machine epsilon — `V_disp_from_mass` and `mass_from_V_disp` are algebraic inverses through the same `Phi`, `l_P3`, `c`). PASS (< 1e-9).
    - `ρ_form_e = R(e)/V_disp_e = m_e c² / V_disp_e = 8.2027e47 Pa`. `P_conv/3 = 8.2027e47 Pa`. Ratio `ρ_form_e / (P_conv/3) = 1.000000` — same scale, EXACTLY (it is the `P_cf_e` identity: `ρ_eff_e c² ≡ P_conv/3`). Within 1 order of mag: PASS (ratio = 1).
    - New constants introduced: **0**. `R(form) ≡ m c²` renames the RHS as "accumulated form-resistance"; the number is untouched. Delete-test: removing the word "resistance" changes nothing numerical → the reading is constant-free. PASS.
- **DECIDE: PASS-GATE.** The renaming is constant-free; `ρ_form_e` lands ON the engine's own marginal-stability scale (`P_conv/3`), not near a new dial.
- **GATE:** Phase 2 authorised.
- **AUDIT NOTE (honesty):** `ρ_form_e = P_conv/3` is not an independent success — it is the pre-existing `P_cf_e` identity (`ρ_eff_e·c² ≡ P_conv/3`, laws.hpp:485). It confirms the reading is *consistent* (constant-free), it does **not** newly derive anything. Logged as IDENTITY, not DERIVED.

---

### Phase 2 — The 1.293 = 0.511 + 0.782 bookkeeping + forced decay direction

- **PRE-COMMIT:** `|ΔR−1.293|/1.293 < 0.1%`; `|Q−0.782|/0.782 < 0.2%`; `R(n)>R(p)` TRUE; `ΔR>τ` TRUE.
- **EXECUTE:** tool computes rest energies from `measured::` masses; subtracts `m_n−m_p` in kg first (gap ~2.3e-30 kg, far above double round-off), then × c², then ÷ MeV_to_J.
- **ACTUAL (from `np19_results.txt`):**
    - `R(n) = 939.5654 MeV`, `R(p) = 938.2721 MeV`, `τ = m_e c² = 0.5110 MeV`.
    - `ΔR = R(n) − R(p) = 1.29334 MeV`. Target 1.293 → rel err `2.6e-4 = 0.026% < 0.1%`. PASS.
    - `Q = ΔR − τ = 0.78234 MeV`. Target 0.782 → rel err `3.0e-4 = 0.030% < 0.2%`. PASS.
    - Sign check `R(n) > R(p)`: **TRUE** (939.5654 > 938.2721). The bound/heavier neutron-form is the higher-resistance form — correct (flipped) sign, consistent with NP14 larger-V_disp. PASS (T1).
    - Spontaneity `ΔR > τ`: **TRUE** (1.29334 > 0.5110) ⟹ free neutron relaxes downhill, no trigger. PASS.
- **DECIDE: PASS-GATE.** Sign + arithmetic both pass. T1 and T2 survive.
- **GATE:** Phase 3 authorised.
- **AUDIT NOTE (honesty):** `ΔR = 1.293` is `(m_n−m_p)c²` — a subtraction of two MEASURED anchors, near machine-exact by construction. `Q = ΔR − τ` where `τ = m_e c²` is ALSO measured. So `1.293 − 0.511 = 0.782` is an **exact definitional identity among three measured numbers**, not a prediction. It confirms the three numbers are one ledger (they were always related by subtraction); it is Class C reframe, not a derived result. Logged accordingly.

---

### Phase 3 — Two-Ledger Lemma, ≥2 cases + both-signs falsifier

- **PRE-COMMIT:** `|ΔR|` identical across boundaries ≤1e-6 rel; both ledgers opposite sign; single-fixed-boundary-both-signs construction FAILS.
- **EXECUTE:** tool prints two ledgers for Case A (free-n decay) and Case B (stellar EC), and runs a `both_signs_on_fixed_boundary()` probe.
- **ACTUAL:**
    - **Case A.** Boundary 1 {n alone}: `n → p+e+ν̄`, `Q = +0.78234 MeV` (exothermic, sign +). Boundary 2 {p+e building n}: `p+e → n+ν`, cost `+1.29334 MeV` (endothermic, sign −ledger). `|ΔR|` per-reaction across the two cuts: identical to `<1e-9` rel (same masses). Signs opposite. PASS.
    - **Case B.** Isolated arrow `p+e→n+ν`: `+1.29334 MeV` endothermic. Event scale (core collapse): same per-reaction resistances `R(n),R(p),τ` UNCHANGED; the vented `~3e46 J` (OBSERVED-TARGET, supernova binding scale) is enclosed-system movement, not a change in the medium's per-form resistance. `|ΔR|` identical across boundaries. Sign flips + → because the cut now encloses the collapse's released movement. PASS.
    - **Both-signs falsifier:** `both_signs_on_fixed_boundary()` holds the cut fixed (fixed `ΔR`) and asks for both signs. It returns a SINGLE sign (sign of the fixed `ΔR`) — the construction **FAILS** to produce two signs, as required. PASS (T3).
- **DECIDE: PASS-GATE.** Lemma survives both cases; falsifier turned inward fails to break it.
- **GATE:** Phase 4 authorised.
- **AUDIT NOTE:** the sign flips ONLY when the boundary `∂(sys)` is re-cut; the per-form resistances are boundary-invariant. This is the whole content of the lemma and it holds.

---

### Phase 4 — det −1 grammar reconciliation

- **PRE-COMMIT:** written reconciliation; energy sourced 100% from ΔR, none from the grammar move.
- **EXECUTE:** prose in `NP19_DERIVATION.md` §5; tool prints the reconciliation statement + a check that the grammar move (β⁻/EC bijection) is count-conserving with determinant −1 and carries zero energy in the move itself.
- **ACTUAL:** The β⁻/EC vector pair is a bijection with determinant −1 (pure relabelling of form; count conserved). All of `1.293 / 0.511 / 0.782` is sourced from `ΔR` (Phase 2) — the resistance difference between the two forms — and NONE from the relabelling move. No energy needs to be assigned to the det −1 move to balance the books. No contradiction with NP01 grammar or ATOMICUS rules.
- **DECIDE: PASS-GATE (with the honest caveat that this is a consistency statement, not a derivation).**
- **GATE:** final verdict authorised.

---

## Phase gate summary

| Phase | Committed gate | Result | Decision |
|-------|----------------|--------|----------|
| P1 | round-trip <1e-9; ρ_form_e ~ P_conv/3; 0 new const | 0.0 err; ratio 1.0000; 0 const | **PASS-GATE** |
| P2 | ΔR 0.1%; Q 0.2%; R(n)>R(p); ΔR>τ | 0.026%; 0.030%; TRUE; TRUE | **PASS-GATE** |
| P3 | \|ΔR\| inv ≤1e-6; opposite signs; both-signs FAILS | inv; opposite; FAILS | **PASS-GATE** |
| P4 | written reconciliation; energy 100% from ΔR | written; consistent | **PASS-GATE** |

No RETRO-PASS, no PLUG, no IDENTITY-PASS beyond what is explicitly logged, no BORROW-SMUGGLE. Tolerances untouched after the run.

**Honest overall:** all four phases gated PASS, but the physics ceiling is exactly what was pre-committed: **CONVERGENCE / reframe**. The arithmetic core (`1.293 − 0.511 = 0.782`) is an EXACT identity among three measured anchors — a definitional relabelling made mechanical and sign-checked, NOT a newly derived number. See `NP19_VERDICT.md` STRESS-TEST SELF-AUDIT.
