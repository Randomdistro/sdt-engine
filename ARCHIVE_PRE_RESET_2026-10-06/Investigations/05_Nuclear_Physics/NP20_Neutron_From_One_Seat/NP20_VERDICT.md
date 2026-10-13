# NP20 — VERDICT: The Neutron from One Seat

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-01. **Engine:** `sdt/laws.hpp` only.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **C** | All four phases executed, gated, and logged (P1 PASS, P2 MISS→OPEN, P3 sign-assumed/mag-IDENTITY→OPEN, P4 CLOSURE-FALSE). Outputs delivered. Not B/A because the physics closure did not pay. |
| **Physics class** | **OPEN** (with one DERIVED sub-result; the tempting q=3 shortcut is KILLED) | The 1.83c seat speed is genuinely forced twice over (P1, 0.006%). Neither 0.782 MeV nor −1.913 μ_N is generated knob-free. |

**Closure verdict: the one-geometry closure is FALSE / NOT PAID.** Two per-number CALIBRATED(1) knobs
were required (one for mass, one for moment). The geometry **brackets** both targets but **predicts**
neither. This is the FLM12-D1 precedent held to its bar: bracketing ≠ paying.

---

## What actually happened, number by number

| Quantity | SDT native (knob-free) | Anchor | Error | Sign | Label |
|---|---|---|---|---|---|
| **Seat speed** `v_seat` | 1.83016 c (traction) | 1.83006 c (`v_bound`) | **0.006%** | + | **DERIVED · PASS** |
| **Mass surplus** | 0.6003 MeV `[½(z−1)m_e c²]` | 0.7823 MeV | **−23.3%** | + | COMPUTED · **MISS→OPEN** (needs ×1.303) |
| **Neutron moment** | sign −, magnitude via identity | −1.913 μ_N | mag = IDENTITY | NEG (assumed) | **IDENTITY / OPEN** (needs gearing −0.002563) |

- The **only** genuine, non-circular, delete-test-passing result is **P1**: two independent engine
  routes (PPT06 traction; depth-closure `v=c√z` with koppa=r_e) land on the same 1.83c to 0.006%.
- The **mass** native factor (z−1)/2 = 1.175 vs required 1.531 → brackets, no predict.
- The **moment** sign is only negative because `sense=−1` was assumed; the magnitude requires a gearing
  that matches neither α nor k² → identity, not prediction.

---

## Falsification table (updated)

| Test | Trigger | Committed | Actual | Result |
|------|---------|-----------|--------|--------|
| **T1 — Sign** | composite moment sign | negative | negative **but ASSUMED via sense=−1** | not KILLED; **not a native win** (sign carried in, not derived) |
| **T2 — Mass magnitude** | \|pred−0.782\|/0.782 ≤ 15% | ±15% | **−23.3%** | **FAIL → OPEN** (NP19/NP21 resistance-magnitude dependency) |
| **T3 — Moment magnitude** | \|pred−1.913\|/1.913 ≤ 15%, sign neg | ±15% | magnitude = IDENTITY (gearing −0.002563, no derivation basis match) | **FAIL → OPEN** |
| **T4 — One geometry** | per-number knob count = 0 | 0 | **2** (×1.303 mass; gearing moment) | **CLOSURE FALSE** |
| **T5 — Same seat speed** | v_seat(mass) == v_seat(moment) | identical | identical (single struct, one `v_seat`) | **PASS** (structurally enforced) |
| **T6 — Borrowed-unit honesty** | μ_N flagged? | flagged | flagged borrowed throughout | **PASS** |

**Terminal for the closure:** T2, T3, T4. **Not terminal (survives):** T1 (sign not positive), T5, T6.
No RETRO-PASS, no PLUG, no IDENTITY-PASS taken to rescue the numbers.

---

## STRESS-TEST SELF-AUDIT  (mandatory)

**(1) Independent, or identity/circular?**
- **P1 (seat speed): INDEPENDENT and DERIVED.** `v_seat = c/k_proton_surface` (traction) and
  `v_bound = c√(r_e/R_p)` (depth-closure) are two different formulas that do not import each other's
  value; they agree to 0.006%. Passes the delete-test. This is the one real result.
- **P2 (mass): NOT circular but does NOT pay.** The native ½(z−1)m_e c² prediction (0.600 MeV) is
  independent of the target but misses by −23%. The 0.782 "rail" is an anchor subtraction, used as an
  OBSERVED-TARGET column only, never fed into the mechanism. To *land* 0.782 needs a ×1.303 knob.
- **P3 (moment): IDENTITY on the magnitude.** Reproducing −1.913 μ_N consumes the measured increment
  (μ_N−μ_P) fed back through a gearing that matches no derivation basis quantity. The sign is ASSUMED via
  `sense=−1`, not derived. The `moment_incr/mass_factor ≈ 3.074 ≈ q=3` shortcut was recognised as a
  disguised **IDENTITY-PASS** (it consumes the measured mass anchor and absorbs a 2.5% fudge in
  "3.074≈3") and **KILLED** as a route.

**(2) Fished exponents/coefficients?**
- **No coefficient was fished to land a target.** The mass factor (z−1) and the ½ two-body split were
  chosen a-priori and reported at their honest −23% miss. The ×1.303 (mass) and −0.002563 (moment)
  are printed **as the knobs that would be required**, tagged CALIBRATED(1), and used to *fail* the
  closure — not to claim a pass. No exponent hunting; no tolerance widening after the fact.

**(3) Dimensions.**
- v_seat, v_bound [m/s]; z, factors [dimensionless]; mass surplus built as (dimensionless)·m_e c²
  [J → MeV via `MeV_to_J`] — dimensionally sound. Moment worked in **μ_N (borrowed unit)**, flagged as
  such throughout; the bare electron moment enters as `m_p/m_e` [dimensionless ratio = μ_B/μ_N], which
  is dimensionally the correct μ_N-normalisation. v > c handled by the depth formulation `z=(v/c)²`,
  **not** SR γ (which would be imaginary) — documented.

**(4) Honest class + what is owed.**
- **Class: OPEN.** Prompt completion **C**; physics **OPEN** (one DERIVED sub-result at P1).
- **Owed:**
  1. A native resistance-magnitude law (NP19/NP21) that *emits* the 1.531 factor from the seat depth
     without a ×1.303 knob — currently the load-bearing gap.
  2. A native flux-composition that *derives* the gearing −0.002563 (and the negative **sign from
     dynamics**, not from an assumed `sense`) — currently μ_N reproduction is an identity.
  3. Until both exist, the neutron's two numbers remain **two separate, individually-unpaid results**,
     **not** "one defect read by two instruments." The headline claim is **not** supported.

---

## Stack status

`INVESTIGATION_STACK.md` tag: **ACTIVE / OPEN** — P1 result solid; P2 blocked on NP19/NP21
resistance-magnitude; P3 blocked on a native flux-composition + sign derivation. Not RESOLVED, not
KILLED (the central picture is not falsified — the moment sign is not positive — but it is not
demonstrated either).

---

*NP20 · executed · honest OPEN · the seat speed is real; the closure is not paid.*
