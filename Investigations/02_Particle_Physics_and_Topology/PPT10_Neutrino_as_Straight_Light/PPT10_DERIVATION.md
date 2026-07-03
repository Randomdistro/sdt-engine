# PPT10 — Derivation: The Neutrino as Straight Light (pitch = grip)

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-01.
> **Tool:** `ppt10_pitch_coupling.cpp` (→ `ppt10.exe`, stdout in `ppt10_results.txt`).
> **Engine only:** `sdt::laws::{measured, law_V, law_VI::winding}` + `sdt::neutrino`. No local constants.
> **Prohibited in the SDT chain:** `G_F`, virtual W, flavour numbers, wavefunctions, `G/M/GM`,
> "charge radius". Charge = handed redirection (EMC03); `e` = unit-bridge.

Every step is tagged **DERIVED** (from Law V / Law VI / whitelist geometry), **COMPUTED**
(arithmetic on derived + measured), **ASSUMED** (a body radius taken as MEASURED-INPUT from the
`neutrino.hpp` comment block), or **OBSERVED-TARGET** (a rival/measured cross-section, comparison only).

---

## P1 — Transverse pitch from the Law-V movement budget

**Law V** (`sdt::laws::law_V::v_circ`, `laws.hpp:540`): a moving impulse partitions its speed budget
between a forward and a transverse (circulation) component,

  `v_∥² + v_⊥² = c²`.   **[axiom, Operator 6]**

Define the **transverse pitch** as the ratio of the two:

  `p_T ≡ v_⊥ / v_∥ = tan θ_w`,  dimensionless, `p_T ∈ [0, p_T^max]`.   **[DERIVED — definition on Law V]**

- Straight light = the emission that spends its whole budget forward: `v_⊥ → 0 ⇒ p_T → 0`. This is the
  **W=0** limit (`neutrino.hpp`, `W_neutrino=0`): no transverse channel ⇒ no ℓ=1 charge wake, no ℓ=2
  moment (**PPT04**, μ_ν ≡ 0). Pitch and polarisation are the **same transverse channel** (**OP04**):
  polarisation is its *orientation*, pitch is its *magnitude*; the straight limit is that magnitude
  vanishing.

**Native geometric proxy (no free angle).** The wake presents its body of radius `R_excl` at its wake
reach `R_wake`; the cone half-angle is

  `tan θ_w ≈ R_excl / R_wake`  ⇒  `p_T ≈ R_excl / R_wake`.   **[DERIVED — geometry]**

This is **exactly the inverse** of `neutrino.hpp`'s headline `R_wake/R_excl` ratio, so `p_T` is a
re-reading of an already-canonical SDT number, **not** a new fitted tilt (F1 anti-fit gate).

| rung | R_excl [m] | R_wake [m] | `p_T = R_excl/R_wake` | W | tag |
|---|---|---|---|---|---|
| electron | 2.88e-21 | 2.818e-15 (`r_e`) | **1.022e-06** | 1 | DERIVED (R_excl ASSUMED) |
| proton | 3.52e-20 | 8.41e-16 | **4.186e-05** | 3 | DERIVED (radii ASSUMED) |
| neutrino ν₁ | 9.770e-24 | 9.866e-06 | **9.902e-19** | 0 | DERIVED |

**Law-V cross-check (tool):** reconstructing `p_T(ν)` from a wake angle gives `v_⊥ = 2.97e-10 m/s`,
`p_T = 9.902e-19`, and the budget `v_∥² + v_⊥² = c²` closes to `1.000000000000000`. **[DERIVED]**

**Wake-ratio tie:** `R_wake/R_excl (ν) = 1.010e18`, matching `neutrino.hpp`'s 1.01e18 to 0 orders
(committed ±1). **[COMPUTED]**

**F1 result — PASS-GATE with logged caveat (ADJ-001).** On the **straight-light line** — the W=1
electron emission descending to the W=0 neutrino — `p_T` is monotone-decreasing to 0. The **proton is
off this line**: it is a *closed* W=3 trefoil, a different topological class; the naive proxy is
non-monotone electron→proton (`1.02e-6` vs `4.19e-5`). The committed metric ("monotone **to the
neutrino**") holds; the electron/proton inversion is an honest caveat, not a fit.

---

## P2 — Coupling = f(pitch): the transverse-area law

**Mechanism (native, pre-committed BEFORE reading σ_ν).** The grip is the wake's ability to
occlude/redirect an incoming relay. That ability is set by the **transverse footprint** the wake
presents — an **area**. So cross-section scales as the square of the transverse extent measured
against the forward reach:

  `σ ∝ (transverse extent)² ∝ p_T²`  ⇒  **n = 2, DERIVED from a transverse-area argument.**   **[DERIVED]**

**F2 — sign test (existential).** `dσ/dp_T = 2 A₀ p_T > 0`, so σ **decreases monotonically** as
`p_T → 0`. Straightening genuinely removes grip. **F2 PASSES** — straight-light is *not* killed at the
sign level. **[DERIVED]**

**Scale-free prediction (no absolute A₀ fitted).** The pitch drop electron→neutrino is

  `log₁₀(p_T,e / p_T,ν) = 12.014` decades.   **[DERIVED]**

With the **derived** n=2:

  predicted suppression `= 2 × 12.014 = 24.03 orders`.   **[DERIVED]**

**OBSERVED comparison column (read only after n was fixed):**

| quantity | value | tag |
|---|---|---|
| photon (Thomson) σ_T | 6.652e-29 m² | OBSERVED-TARGET |
| neutrino σ (~10 MeV) | 1e-47 m² | OBSERVED-TARGET |
| neutrino σ (~1 MeV) | 1e-48 m² | OBSERVED-TARGET |
| **observed suppression** | **18.8 – 19.8 orders** | OBSERVED-TARGET |

**Comparison against the committed ±2-order band:** predicted **24.0** vs observed **18.8** ⇒
**Δ ≈ 5.2 orders, OUTSIDE the band.** The geometry **overshoots** the suppression by ~5 orders.

The exponent that *would* land on 18.8 is `n = 18.8/12.01 ≈ 1.57`. **Fitting n to the neutrino point is
an IDENTITY-PASS (F3) and is FORBIDDEN** — not taken.

**P2 result — QUALIFIED, Class C (CONVERGENCE with residual).** The un-fitted n=2 law gets the **sign**
(F2) and the **order-of-magnitude class** right (tens of orders, not 3, not 100), but it does **not**
reproduce the gap to ±2 orders without fitting. **F3 fires as a near-miss.** Honest label: convergence
with a real ~5-order residual — *not* a NATIVE PASS.

> Why the residual is not cosmetic: the two cross-sections are also **different kinds of measurement**
> — photon Thomson is a real transverse-area scatter off a *closed* W=1 wake; the neutrino number is a
> *nuclear* interaction rate. The p_T² law compares transverse footprints as if the coupling
> per-unit-footprint were identical across a W=1→W=0 change of topological class. That assumption is
> exactly what the ~5-order residual measures. Flagged, not fitted away.

---

## P3 — The ~20-order gap: CONTINUOUS vs SNAP

**The CONTINUOUS reading.** `σ(p_T)=A₀p_T²` is smooth, so it **predicts a populated middle** — a ramp
of half-gripping, partly-stoppable emissions at intermediate pitch:

| p_T | decades below electron-pitch | predicted suppression vs photon | tag |
|---|---|---|---|
| 1e-9 | 3.01 | 6.02 orders | COMPUTED (predicted middle) |
| 1e-12 | 6.01 | 12.02 orders | COMPUTED (predicted middle) |
| 1e-15 | 9.01 | 18.02 orders | COMPUTED (predicted middle) |

**Search for occupants (before declaring empty).** Collinear/forward soft radiation and coherent
forward scattering *are* low-σ, strongly-forward channels — **candidate** occupants of the middle —
but none is cleanly a measured "half-neutrino" sitting at one of these intermediate σ values. The
middle is **not observed populated**, but it is **also not provably empty**: mislabelled or
hard-to-detect forward channels are not excluded by any measurement in hand.

**Is a native SNAP admissible?** Topology gives a discrete jump: `W` is an Alexander-polynomial
invariant (`law_VI::winding`, PPT09 reconnection), and open (W=0) vs closed (W≥1) winding is **not
continuously deformable**. *But* — the decisive point — **`p_T` (a continuous Law-V partition) is not
the same variable as `W` (a discrete topological label).** A snap in `W` does **not** force a snap in
`p_T`. Asserting a threshold on `p_T` "because W is discrete" would be a threshold on the **wrong
variable to save the fit** — a forbidden **PLUG**.

**Decision against the pre-written rule.** The middle is **neither** populated (so CONTINUOUS is not
earned) **nor** provably empty with an admissible **p_T**-snap (so SNAP is not earned). Per the
pre-committed rule ⇒ **OPEN.**

**The sharpened fork shipped:**

> **Fork:** is the weak coupling **coupling-as-continuous-pitch** — σ = A₀ p_T², which requires a
> populated (currently unobserved) middle of half-stoppable forward emissions — **or**
> **coupling-as-discrete-winding** — grip switches with the topological W jump, which snaps but on
> **W**, not on the continuous **p_T** the straight-light picture is built on?
>
> **Decision rule for whoever resolves it:** (a) find a measured emission at an intermediate σ in the
> predicted (p_T, σ) band ⇒ CONTINUOUS wins, gap is a detection/labelling artefact; (b) prove the
> middle empty **and** re-express grip as a function of **W** (not p_T) with a topology-derived jump ⇒
> SNAP wins, but the straight-light-as-continuous-pitch narrative is then wrong and must be replaced by
> winding-quantised grip. Until one fires, PPT10 does **not** claim closure.

---

## P4 — The νₑ → e⁻ direct-grounding prediction (hands NP18 its test)

**SDT (single sentence):** a neutrino is straight-running electron-stuff; on hitting a **gapless wall**
(a lattice with no through-channel at the incoming pitch) the thread **cannot stay straight** and
**grounds into a wiggling electron (νₑ → e⁻) with no mediator**, emitting an electron that carries the
neutrino's forward energy, continuum-distributed. **[DERIVED — geometry: gaplessness = no channel at p_T]**

**Gaplessness condition (SDT variables):** grounding when the lattice through-channel aperture at the
incoming pitch `p_T` is smaller than the thread's forward reach — no straight path exists, so the
budget must re-partition into transverse circulation (`v_⊥ > 0`, the electron wiggle).

**SM (OBSERVED column only):** flavour is conserved at the vertex; an electron arises **only** via the
weak charged current through a **virtual W** (rate ∝ `G_F²`); **direct free νₑ → e⁻ conversion is
forbidden**. `G_F`/W tagged **OBSERVED-TARGET**, never in the SDT chain. **[OBSERVED-TARGET]**

**Discriminating observable:** the **presence (SDT) vs absence (SM)** of a direct, mediator-free
conversion channel, plus its **continuum electron energy spectrum**. Not degenerate — **P4 PASS-GATE.**
Numeric apparatus design handed to **NP18**.

---

## Ledger summary

| step | result | label | class contribution |
|---|---|---|---|
| P1 pitch `p_T=tan θ_w`, proxy `R_excl/R_wake` | built from Law V, no fitted angle | DERIVED | PASS-GATE (e/p caveat) |
| P1 Law-V budget closure | 1.000000000000000 | DERIVED | — |
| P2 exponent n=2 | transverse-area geometry, un-fitted | DERIVED | — |
| P2 F2 sign | dσ/dp_T > 0, σ falls as p_T→0 | DERIVED | straight-light NOT killed |
| P2 predicted vs observed | 24.0 vs 18.8 orders (Δ 5.2) | COMPUTED vs OBSERVED-TARGET | **C — CONVERGENCE w/ residual** |
| P2 fitted-n rescue | n≈1.57 | rejected as IDENTITY-PASS | not taken |
| P3 continuous middle | populated in the model, unobserved in data | COMPUTED | — |
| P3 W-snap on p_T | rejected as PLUG (wrong variable) | — | **OPEN** |
| P4 SDT vs SM | direct grounding vs forbidden | DERIVED vs OBSERVED-TARGET | PASS-GATE, hands NP18 |

**No fits used. No G/M/GM, no G_F/virtual-W/flavour/ψ in the SDT chain, no "charge radius".**
