# NP20 — Derivation Record: The Neutron from One Seat

> **Author:** J. C. Harvey, Melbourne. **Status:** EXECUTED (honest OPEN — closure not paid).
> **Engine:** every constant from `sdt::laws` (`measured`, `law_VI::traction`, `depth_closure`, `bridge`).
> **Unit flag:** μ_N (the nuclear magneton) is a **BORROWED yardstick** — the anchor's reporting unit,
> not an SDT-native quantity. It appears here only to compare against `measured::mu_P`, `measured::mu_N`.

---

## 0. The claim under test

From **one** seat geometry — an electron driven onto the proton boundary `R_p` at the framework's
already-fixed hyper-relativistic seat speed ~1.83c — **generate both** the **0.782 MeV** free-decay
surplus (form-resistance step) **and** the **−1.913 μ_N** moment (sign and magnitude), with **zero
per-number knobs**. If a *different* knob is needed for each number, it is **not one geometry** →
downgrade to two separate results (or OPEN).

**Result:** the seat-speed premise is real and clean, but the two physical numbers are **bracketed,
not predicted**. The closure is **NOT paid**.

---

## 1. The frozen seat geometry  (Phase 1 — declared before any number)  — **DERIVED / PASS**

| Symbol | Value | Dimension | Tag | Source |
|---|---|---|---|---|
| `R_p` | 8.414×10⁻¹⁶ | m | MEASURED-INPUT | `measured::R_p` — proton **boundary/displacement** radius (**never** "charge radius") |
| `v_seat` | 1.83016 c | m/s | DERIVED | `law_VI::traction::v_phase_proton_surface = c / k_proton_surface`, k=0.5464 (PPT06) |
| `v_bound` | 1.83006 c | m/s | DERIVED | `depth_closure::v_bound(r_e, R_p) = c·√(r_e/R_p)`  (bound-motion law v=c√z) |
| `z_seat` | 3.3495 | — | DERIVED | `depth_closure::depth_from_v(v_seat) = (v_seat/c)²` |
| `sense` | −1 (counter) | — | **ASSUMED** | sign convention for the seated electron's rotation |

**Reconciliation (the one genuine, non-circular win).**
Two independent engine routes agree:
- PPT06 traction demands `v_phase = c/k_proton_surface = 1.83016 c` at `R_p`.
- Depth-closure `v = c√z` with the hydrogen c-boundary koppa `α²a₀ = r_e` gives
  `v_bound = c√(r_e/R_p) = 1.83006 c`.

**Agreement = 0.0057%** (gate < 1%). The "same 1.83c" is **not** a free parameter — it is forced
twice over. This passes the delete-test: neither route imports the other's number. **PASS-GATE.**

**v > c regime (honest note).** `z_seat = 3.35 > 1`, i.e. `v_seat > c`. This is the traction / W+1
**superluminal phase velocity** (a relay-mismatch, not a moving rest-mass). We use the depth
formulation `z=(v/c)²` throughout; a naive SR factor `√(1−v²/c²)` would go imaginary and is **not**
applied. (§9 of the spec.)

---

## 2. Number 1 — the MASS (form-resistance step)  (Phase 2)  — **COMPUTED / MISS → OPEN**

**Target (OBSERVED-TARGET).** decay surplus = (m_n − m_p)c² − m_e c² = **1.2933 − 0.5110 = 0.7823 MeV**.
This subtraction is the *sanity rail*, not the mechanism — NP20 must **generate** 0.782, not subtract to it.

**Native factors the frozen geometry offers** (dimensionless, DERIVED):

| factor | value |
|---|---|
| `z_seat − 1` | 2.3495 |
| `√z_seat` | 1.8302 |
| `ln z_seat` | 1.2090 |

**A-priori native prediction** (chosen before reading the target — the excess-depth resistance
analogue, halved for a two-body split):
```
pred = ½·(z_seat − 1)·m_e c² = ½ · 2.3495 · 0.5110 MeV = 0.6003 MeV      [COMPUTED]
```
**Error vs 0.782 MeV = −23.3%** → outside the committed ±15% gate.

**Why it does not pay.** The dimensionless factor the geometry would need to *predict* is
`0.782 / 0.511 = 1.531` [OBSERVED-TARGET]. None of {2.349, 1.830, 1.209} equals 1.531; the ½·(z−1)
route gives 1.175. Landing 0.782 requires an extra **×1.303 coefficient** [CALIBRATED(1)] with no
derivation basis justification. The geometry **brackets** 0.782 (0.42–0.60 MeV across the candidate factors)
but does not **generate** it.

**DECIDE: OPEN.** Do not insert the ×1.303 knob; do not widen the tolerance. The resistance-magnitude
mechanism is the open dependency (NP19/NP21). *(This is exactly the FLM12-D1 deuteron precedent:
bracketing the number is not predicting it.)*

---

## 3. Number 2 — the MOMENT (composite flux)  (Phase 3)  — **IDENTITY (magnitude) / sign ASSUMED → OPEN**

**Target (OBSERVED-TARGET).** μ_n = **−1.91304 μ_N** (μ_N = **BORROWED unit**). Proton μ_P = +2.79285 μ_N.

**Composition attempt.**
- Bare electron moment in borrowed μ_N units = `m_p/m_e = 1836.15 μ_N` (this is μ_B expressed in μ_N). [DERIVED]
- To turn +2.793 into −1.913 the seated electron must contribute an increment
  `μ_N − μ_P = −4.7059 μ_N` [OBSERVED-TARGET].
- The gearing on the bare electron moment required is `−4.7059 / 1836.15 = −0.002563` [OBSERVED-TARGET].

**Why it does not pay.**
- **Sign.** The composite comes out **negative** — but *only* because `sense = −1` was **ASSUMED** and
  fed in as the sign of the increment. There is no dynamical over-rotation calculation here that
  *forces* the negative; the sign is carried in, not derived. So T1 is **not violated** (no positive
  sign → no KILL), but the negative sign is **not a native prediction** either.
- **Magnitude.** The required gearing **−0.002563** matches **neither** α (0.00730), **nor** k²
  (0.2986), **nor** any clean derivation basis combination. Reproducing −1.913 μ_N is an **IDENTITY** (the
  measured increment fed back in), not a prediction.

**DECIDE: OPEN.** Correct-sign *would* be a partial win only if the sign were derived; here it is
assumed and the magnitude needs a per-number knob. Do **not** re-tune `v_seat` to fix the magnitude.

**Tempting near-coincidence (KILLED as a route).** `μ_P + μ_N = 0.880 ≈ μ_D = 0.857` (deuteron), and
`(μ_N − μ_P)/(0.782/m_e c²) = 4.706/1.531 = 3.074 ≈ 3` (winding q). Both are **dead ends**: the first
is a *different* relation (degenerate); the second would let one *assert* `moment_incr = 3 × mass_factor`
and back out μ = −1.800 (−5.9%) — but that is **IDENTITY-PASS** (it consumes the measured mass anchor
to get the moment, and "3.074≈3" absorbs a 2.5% fudge). Rejected under stress discipline.

---

## 4. Phase 4 — zero-knob ledger (the actual closure test)  — **CLOSURE FALSE**

| Consumed by | Quantity | Tag |
|---|---|---|
| BOTH (shared geometry) | `R_p`, `v_seat`, `z_seat`, `sense` | derivation basis / DERIVED / ASSUMED-sign |
| MASS only | ×1.303 coefficient | **CALIBRATED(1)** |
| MOMENT only | gearing −0.002563 | **CALIBRATED(1)** |

**Per-number knob count beyond the shared geometry = 2** (committed pass = 0).

→ The two numbers do **not** fall out of the identical declared parameters. Per §5, this **falsifies
the one-geometry closure**. Downgraded honestly: the mass and moment are **two separate results**, and
each is itself only **bracketed** (mass −23%; moment magnitude via identity, sign assumed). Net:
**OPEN**, not a retro-PASS.

---

## 5. Ledger of every constant used

| Constant | Value | derivation basis? | Tag |
|---|---|---|---|
| `measured::R_p` | 8.414e-16 m | measured observable | MEASURED-INPUT |
| `measured::r_e` | 2.8179e-15 m | measured observable (=α²a₀) | MEASURED-INPUT |
| `bridge::k_proton_surface` | 0.5464 | derived (1/α·√(R_p/a₀)) | DERIVED |
| `law_VI::traction::v_phase_proton_surface` | 1.83016 c | derived | DERIVED |
| `measured::m_e, m_p, m_n` | — | derivation basis / measured | MEASURED-INPUT |
| `measured::MeV_to_J` | 1.6022e-13 | unit conversion | MEASURED-INPUT |
| `measured::mu_P, mu_N` | +2.793, −1.913 μ_N | **anchors (borrowed μ_N unit)** | OBSERVED-TARGET |
| ×1.303 (mass) | — | **not derivation basis** | CALIBRATED(1) |
| gearing −0.002563 (moment) | — | **not derivation basis** | CALIBRATED(1) |

**No G / M / GM, no quarks / gluons / W-boson, no wavefunctions/fields, no "charge radius", no G_F.**
μ_N flagged borrowed throughout. Two CALIBRATED(1) knobs → closure fails; both documented, neither hidden.
