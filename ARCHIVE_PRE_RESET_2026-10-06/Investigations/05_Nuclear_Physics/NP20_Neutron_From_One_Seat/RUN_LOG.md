# RUN_LOG — NP20 · The Neutron from One Seat

> Executed per `PROMPT_EXECUTION_PROTOCOL.md`. Append-only. Author: J. C. Harvey, Melbourne.
> Run date: 2026-07-01.

## Pre-Run Commitments — NP20  (filled BEFORE coding)

- **Prompt completion target:** B (realistic fallback C/D)
- **Physics class hoped:** NATIVE (one-geometry-two-numbers); realistic fallback CONVERGENCE/OPEN
- **CALIBRATED budget:** 0 — any fitted param must be declared CALIBRATED(n) and documented
- **Engine namespaces:** `measured` (R_p, mu_P, mu_N, m_n, m_p, m_e, r_e, MeV_to_J),
  `law_VI::traction::v_phase_proton_surface`, `depth_closure` (depth_from_v, v_bound),
  `bridge::k_proton_surface`
- **Frozen geometry (P1, declared before numbers):** `{ R_p, v_seat≈1.831c, sense = counter (−1) }`
- **Phase thresholds (committed before run):**
  - P1: v_seat agreement with `v_bound` at R_p **< 1%**
  - P2: mass surplus **±15%** of 0.782 MeV (stretch ±10%)
  - P3: moment sign **NEGATIVE** (hard gate) + magnitude **±15%** of −1.913 μ_N (stretch ±10%)
  - P4: per-number knobs beyond shared geometry **= 0**
- **Forbidden retroactive changes:** widen tolerances; plug targets; IDENTITY-PASS; local constant
  namespaces; different seat speed per number; "charge radius"; treat μ_N as native; G/M/GM/quarks/ψ.

---

## Engine reconnaissance (before coding)

- `law_VI::traction::v_phase_proton_surface = c / bridge::k_proton_surface`, k=0.5464 → **1.83016 c**.
- `depth_closure::depth_from_v(v) = (v/c)²`; `depth_closure::v_bound(koppa,r) = c·√(koppa/r)`.
- Hydrogen c-boundary koppa = `α²a₀ = r_e` (laws.hpp line 669). At the proton surface,
  `v_bound(r_e, R_p) = c·√(r_e/R_p) = c·√(3.3491) = 1.83006 c`.
- Masses in kg; convert with `measured::MeV_to_J`. μ_N/μ_P are literals in **μ_N (borrowed unit)**.
- **Namespace gotcha:** `traction` is nested inside `law_VI`; fully-qualified `law_VI::traction::…`.
  (First compile failed C2653 on bare `traction::`; fixed via ADJ-001.)

---

## Run loop

### Phase 1 — Fix the single seat geometry  → **PASS-GATE**
- **PRE-COMMIT:** v_seat vs v_bound(R_p) must agree < 1%.
- **EXECUTE:** v_seat = 1.83016 c (traction); v_bound = 1.83006 c (depth-closure, koppa=r_e).
- **COMPARE:** agreement = **0.0057%** ≪ 1%.
- **DECIDE:** **PASS-GATE.** The "same 1.83c" premise is supported — two independent engine routes
  (PPT06 traction, depth-closure v=c√z) land on the same number. Geometry frozen:
  `{ R_p = 8.414e-16 m, v_seat = 1.83016 c, sense = −1 (counter, ASSUMED), z_seat = 3.3495 }`.
- **Note (honest):** z_seat = 3.35 > 1 (v > c). Handled with the depth formulation `z=(v/c)²`,
  **not** SR γ (which would be imaginary). This is the traction/W+1 superluminal phase-velocity
  regime, not a moving rest-mass. Documented per §9.

### Phase 2 — Read the MASS off that geometry  → **MISS → OPEN**
- **PRE-COMMIT:** predicted surplus within ±15% of 0.782 MeV.
- **METHOD:** NP19 resistance reframe. The frozen geometry offers exactly three native
  dimensionless depth factors: `(z−1)=2.349`, `√z=1.830`, `ln z=1.209`. Chosen a-priori (before
  reading the target): the excess-depth factor `(z−1)`, halved for a two-body split →
  `pred = ½·(z−1)·m_e c² = 0.6003 MeV`.
- **COMPARE:** vs 0.782 MeV → **−23.3%** (outside ±15%).
- **The required factor** to reach 0.782 is `0.782/0.511 = 1.531`. None of {2.349, 1.830, 1.209}
  equals 1.531; the ½·(z−1) route = 1.175, still off. To land 0.782 needs an extra **×1.303
  coefficient** with no derivation basis justification.
- **DECIDE:** **OPEN** (per pivot table row P2). The geometry **brackets** 0.782 but does **not
  predict** it. Do NOT PASS by widening tolerance or inserting the ×1.303 knob. Resistance-magnitude
  mechanism is the OPEN dependency (NP19/NP21). This is the FLM12-D1 precedent: bracketing ≠ paying.

### Phase 3 — Read the MOMENT off the SAME geometry  → **SIGN survives (assumed) / magnitude IDENTITY → OPEN**
- **PRE-COMMIT:** sign NEGATIVE (hard) + magnitude ±15% of −1.913 μ_N.
- **METHOD:** proton flux μ_P = +2.793 μ_N; bare electron moment = `m_p/m_e = 1836.15 μ_N`
  (μ_B in borrowed μ_N units). Seat a **counter** (sense=−1) electron; composite μ_n = μ_P + Φ_seat.
- **What the target demands:** the seat must contribute `μ_N − μ_P = −4.706 μ_N`. The gearing on the
  bare electron moment required is `−4.706/1836.15 = −0.002563`.
- **COMPARE:**
  - **Sign:** the composite is NEGATIVE — but only because `sense=−1` was **ASSUMED**; the negative
    sign is *carried in*, not derived from any dynamical over-rotation calculation. T1 "survives" in
    the weak sense (not violated), but the sign is not a native prediction.
  - **Magnitude:** the required gearing −0.002563 matches **neither** α (0.00730) **nor** k²
    (0.2986) **nor** any clean derivation basis combination. Reproducing −1.913 μ_N is therefore an
    **IDENTITY** (feed the measured increment back in), not a prediction.
- **DECIDE:** **OPEN** (per pivot table row P3). Correct-sign partial only if the sign were derived;
  here it is assumed, and the magnitude needs a per-number knob. Do NOT change v_seat to fix it.

### Phase 4 — One-geometry / zero-knob ledger  → **CLOSURE FALSE**
- **PRE-COMMIT:** per-number knobs beyond the shared geometry = 0.
- **EXECUTE:** MASS reader needs a ×1.303 knob (MASS-only). MOMENT reader needs a −0.002563 gearing
  knob (MOMENT-only). **Knob count = 2**, committed pass = 0.
- **DECIDE:** **CLOSURE FALSE** (pivot table row P4). The two numbers do NOT fall out of the
  identical declared parameters. Per §5 Class D: downgrade to **two separate results** — and both of
  those are themselves only bracketed, not predicted. Honest outcome: **OPEN**, not a retro-PASS.

---

## Adjustment register

### ADJ-001 — Phase 1 build fix (2026-07-01)
- **Trigger:** first `cl` compile → C2653 `'traction': is not a class or namespace name`.
- **Cause (not a physics pivot):** `traction` is nested inside `law_VI` in laws.hpp (lines 1050–1343).
- **Committed response:** fully-qualify as `law_VI::traction::v_phase_proton_surface`.
- **What changed:** one identifier path. **What did NOT change:** no constants, no thresholds, no target.
- **Re-run result:** compiles clean; geometry values unchanged.

*(No physics pivots taken. P2/P3 misses were reported as OPEN per the pivot table — NOT rescued by
tolerance widening or coefficient plugs. That would be a forbidden RETRO-PASS/PLUG.)*

---

## Gate summary

| Phase | Gate metric | Committed | Actual | Decision |
|-------|-------------|-----------|--------|----------|
| P1 | v_seat vs v_bound | < 1% | 0.0057% | **PASS-GATE** |
| P2 | mass vs 0.782 MeV | ±15% | −23.3% | **OPEN** (brackets, no predict) |
| P3 sign | composite sign | NEGATIVE | negative but ASSUMED | not KILLED, not native |
| P3 mag | mu vs −1.913 | ±15% | IDENTITY (knob req.) | **OPEN** |
| P4 | per-number knobs | 0 | **2** | **CLOSURE FALSE** |

**Bottom line:** one genuine non-circular result (P1 seat-speed reconciliation, 0.006%). Neither
0.782 MeV nor −1.913 μ_N is generated knob-free. **The one-geometry closure is NOT paid.**
