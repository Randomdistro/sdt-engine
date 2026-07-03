# FLM09 — Reconnection Dynamics: the Light Mode and the Boundary Arrival

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [FLM09] FLM09 — Reconnection Dynamics: the Light Mode and the Boundary Arrival: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**J. C. Harvey, Melbourne — 2026-06-24.** Domain: `01_Foundations_and_Lattice_Mechanics`.
Builds on **FLM08** (the corner-sharing tetrahedral random network) and **CONDENSA** (the three motions, the
claim-class discipline). Status: **freshly opened** — almost every row below is `[IDENTIFICATION]` or `[OPEN]`.
The benchmark numbers are *reference values to aim at*, not results already earned.

---

## Thesis

One mechanism, read at two scales.

The elementary move of a continuous random network is the **bond switch**: a tetrahedral hinge *disconnects*
at one site and *reconnects* at another (the Wooten–Winer–Weaire move — the actual relaxation step of
amorphous silicon/silica). FLM09 claims this single move is the engine of two phenomena:

- **ARM A — the light mode (local).** A propagating chain of bond-switches *is* the transverse `c_T` wave.
  Because each switch is **transient** (it opens and heals), two crossing waves **time-share** a reconnection
  site → they pass through each other → **linear superposition**. They only contend when frequency × amplitude
  drives the event rate to **saturation** → **opacity**. One mechanism gives linear light *and* its nonlinear
  ceiling.

- **ARM B — the boundary arrival (cosmic).** The CMB is the **thermal aftermath of a boundary-scale
  reconnection** — "a 3D zipper closing up" — arriving here omnidirectionally. It is thermal for the same
  reason any explosion's aftermath is: the release **equilibrates** in the dense phase (the cyclic detonation;
  see `SDT cyclic cosmology`).

> **The two arms are claimed *fundamentally linked* — the same bond-switch reconnection at the micro and the
> boundary scale — but their ledgers are kept SEPARATE.** A soft cosmological identification must never prop up
> a hard local result, and a clean local number must never be spent buying the cosmology. The link itself is
> `[IDENTIFICATION]`, named as such.

---

## Claim-class discipline (inherited from CONDENSA)

- **[GEOMETRY]** — pure mathematics, no physics input. Provable, closed.
- **[FORM / MAGNITUDE]** — the *shape* of a law is forced; the coefficient is either a whitelist input or `[OPEN]`.
- **[IDENTIFICATION]** — a mechanism is *claimed to be* a physical thing. Promising, **not closed**.
- **[OPEN]** owed · **[KILLED]** tested and abandoned.

## Inputs (whitelist only)

`ℓ_P, c, ℏ, k_B, T_CMB, m_e, e_charge` from `sdt::laws::measured`; lattice geometry (coordination 4, void
fraction, the frustration angles) from `sdt::laws::lattice_structure` (FLM08). Nothing else is tuned.

---

## ARM A — the light mode as a bond-switch wave

| # | claim | class |
|---|---|---|
| A0 | a propagating chain of hinge bond-switches *is* the transverse `c_T` (light) mode | [IDENTIFICATION] |
| A1 | **linearity from transience** — transient sites time-share, so crossing waves superpose at low density | [IDENTIFICATION] |
| A1′ | **opacity from saturation** — when the event rate contends for sites, the relay fails → opaque | [IDENTIFICATION] |
| A1″ | derive the saturation threshold and compare to the **Schwinger field** `E_S = 1.323×10¹⁸ V/m` (the measured onset of vacuum nonlinearity) | **[OPEN]** |
| A2 | **dispersion `ω(k)`** of the amorphous hinge network with no anisotropic/dispersive residual to limits | **[OPEN]** (the CONDENSA §7 debt) |
| A2′ | crystalline reference (chain, `a=ℓ_P`): `ω = ω_max·|sin(ka/2)|`, `ω_max = 2c/ℓ_P`, linear `ω≈ck` at small k | [GEOMETRY] |
| A3 | **transversality** — rotation transmits only ⊥ to the spin axis ⇒ the wave is transverse | [IDENTIFICATION] |
| A3′ | does that geometry put helicity *along* `k` (as the photon demands)? | **[OPEN]** |

**Why A2 is reassuring before it's done:** `k·ℓ_P` = 2.0×10⁻²⁸ (optical) and 3.4×10⁻⁴¹ (LIGO band), so any
lattice dispersion is invisible until `k` nears the zone edge — the medium is Lorentz-linear to absurd
precision at every accessible wavelength. Consistent; but "consistent" is not "derived."

## ARM B — the boundary arrival (CMB)  *(separate ledger)*

| # | claim | class |
|---|---|---|
| B0 | the CMB is the omnidirectional arrival of a **boundary-scale reconnection release** | [IDENTIFICATION] |
| B1 | **isotropy** — omnidirectional arrival is isotropic by construction | [IDENTIFICATION] |
| B2 | **thermal because explosion-aftermath** — equilibrated release ⇒ blackbody (same mechanism as the standard hot phase) | [IDENTIFICATION] |
| B2′ | reproduce `T = 2.7255 K` **and** the FIRAS blackbody to **< 50 ppm** | **[OPEN] — the gate** |
| B3 | a "particular-size" reconnection ⇒ a characteristic scale (Wien `λ=1.063 mm`, `ν=1.60×10¹¹ Hz`; `log₂(1+z_rec)=10.10` octaves) | [IDENTIFICATION] |
| B4 | the **acoustic-peak** angular structure (standard: baryon–photon oscillations) | **[OPEN]** — owes its own account |
| B5 | "crushing force from beyond the CMB" = `P_conv` sourced at the Clearing (Law I) | [IDENTIFICATION] — consistent |

## The link (why one investigation, two ledgers)

Local zipper (light) and boundary zipper (CMB) are asserted to be the **same** bond-switch reconnection at two
scales. That assertion is `[IDENTIFICATION]` — kept explicit precisely so neither arm's score leaks into the
other. If the link is ever *derived* (a single reconnection law that yields both the `c_T` dispersion and the
boundary thermalization), it graduates to `[FORM]`. Not now.

---

## Falsifiers

1. **A** — a measured vacuum **dispersion or birefringence** residual above current limits kills the
   "Lorentz-clean CRN" reading (A2).
2. **A** — a bond-switch saturation threshold derived honestly that lands **orders off** the Schwinger field
   weakens the linearity↔opacity mechanism (A1″).
3. **B** — FIRAS-level spectral distortions the arrival picture cannot reproduce, or an **acoustic-peak**
   structure it cannot source (B2′, B4).
4. **B** — Pantheon+ requiring `Ω_Λ` after a static `d(z)` fit (shared with CONDENSA — kept on the cosmology
   ledger, not the local one).

## Verified benchmarks (engine-grounded, reference values — NOT results)

| arm | quantity | value | role |
|---|---|---|---|
| A | zone-edge `ω_max = 2c/ℓ_P` | 3.710×10⁴³ rad/s | top of the crystalline dispersion |
| A | `k·ℓ_P` (optical / LIGO) | 2.0×10⁻²⁸ / 3.4×10⁻⁴¹ | why structure is invisible at accessible k |
| A | Schwinger field `E_S = m_e²c³/(eℏ)` | 1.323×10¹⁸ V/m | the opacity onset to aim A1″ at |
| B | `T_CMB` | 2.7255 K | the target |
| B | Wien `λ_peak` / `ν_peak` | 1.063 mm / 1.60×10¹¹ Hz | the "particular size" |
| B | octaves from `z_rec=1100` | 10.10 | links the redshift-octave ladder |
| B | FIRAS blackbody bound | < 5×10⁻⁵ (50 ppm) | **the gate** |

## Next (what to actually build)

1. **A2** — the amorphous `ω(k)`: generate a small corner-sharing CRN, build the dynamical matrix, diagonalise,
   check for an anisotropic/dispersive residual. This is the headline debt.
2. **A1″** — a saturation model for the bond-switch event rate; does the opacity onset land near `E_S`?
3. **B2′** — the thermalization account: does an equilibrated boundary release give a blackbody, and what fixes
   `T = 2.7255 K`?

## Build (future)

`cq/flm09_reconnection.cpp` will `#include <sdt/laws.hpp>` and `<sdt/lattice_structure.hpp>` and print the two
ledgers **separately**, each with its own PASS/OPEN tally — so the local score and the cosmological score are
never summed.

---

*Spatial Displacement Theory · FLM09 · the same reconnection, micro and cosmic — scored apart. J. C. Harvey, Melbourne.*
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FLM09
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: FLM08 `lattice_structure.hpp`, FLM02/FLM05 relay mechanics
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*FLM09 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
