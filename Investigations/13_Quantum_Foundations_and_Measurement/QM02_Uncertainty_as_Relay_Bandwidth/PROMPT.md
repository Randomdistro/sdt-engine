# QM02 — Uncertainty as Relay Bandwidth

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Quantum Foundations & Measurement (deterministic relay mechanics, no ψ).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is `Δx·Δp ≥ ℏ/2` a **classical band-limit theorem** on the convergence
   wake (the Fourier-duality floor `Δx·Δk ≥ ½` of any real lattice pulse, with ℏ attached via
   `κ=h/m`), or does the `ℏ/2` *only* appear once the canonical commutator `[x,p]=iℏ` is assumed? The
   vortex has a definite (x, p) every tick; the open question is whether "uncertainty" is provably a
   property of the **wake's spectrum**, not of the vortex — and whether the coefficient comes out
   exactly `½` (Gaussian-saturated) or only `≥ ½` with a non-Gaussian floor.
2. **Why does it matter?** — If the bound is a band-limit, then "indeterminacy" is a shadow of a wrong
   premise (the §8.2 census owes *no* ontic randomness). It also supplies the natural linewidth
   `Γ = ℏ/τ` to QM06 (line widths) and the variance↔residence link to QM04 — both inherit whatever
   QM02 imports.
3. **How will we find out?** — Four gated phases (§④). Phase 1 derives `Δx·Δk ≥ ½` from discrete
   Fourier analysis of an N-spation pulse **before** ℏ is attached; the commutator is never written
   (the §⑤ anti-tautology gate: assuming `[x,p]=iℏ` caps the grade at C).
4. **What would prove us wrong?** — §⑧, three falsifiers each with the numeric outcome that kills it
   (a pulse that beats `½`; an ℏ that must be smuggled rather than traced to `κ=h/m`; a vortex whose
   per-tick x or p is *itself* spread rather than sharp).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

Is the Heisenberg relation **Δx · Δp ≥ ℏ/2** a *bandwidth* property of the convergence wake — the
unavoidable Fourier-type trade between how tightly the wake is localised in the lattice and how
sharply its relay period is defined — rather than an operator-commutator postulate? In SDT a
particle is a hard solid vortex with a definite position and momentum at every tick; "uncertainty"
must then be a property of the **wake's spectral content**, not an ontic indeterminacy of the
vortex. Reproduce ℏ/2, the minimum-uncertainty packet, and the Δt·ΔE form from relay mechanics.

## SDT mechanism & hypotheses

The vortex drags a convergence wake (PPT06/APS04) whose spatial profile is a real lattice pulse. A
pulse confined to N spations has a relay-period spread set by discrete Fourier duality on the
lattice — narrow in `x` ⇒ broad in spatial frequency ⇒ broad in `p` via the relay dispersion
λ = h/p (QM01-H2). The "measurement disturbance" story is replaced by a **structural bandwidth
floor**: you cannot build a wake packet that is both spatially compact and spectrally pure.

- **H1 (Fourier-duality floor):** the wake's `Δx · Δk ≥ ½` is the standard band-limit theorem on the
  relay lattice; multiplying by ℏ (from `κ = h/m`, FD02) gives Δx·Δp ≥ ℏ/2 with **no commutator**.
- **H2 (minimum packet = relay Gaussian):** the equality case is the smoothest lattice pulse (a
  discrete Gaussian), the wake shape of a free vortex — saturating the bound natively.
- **H3 (energy–time):** Δt·ΔE ≥ ℏ/2 is the same theorem on the time axis — finite relay-tick
  duration vs frequency sharpness; linewidth Γ = ℏ/τ follows for QM06 emissions.

## Strategy

**Phase 1 — Relay band-limit theorem.** *Goal:* derive Δx·Δk ≥ ½ for a lattice pulse.
*Method:* discrete Fourier analysis of an N-spation wake packet; variance product. *Success:* the ½
floor recovered analytically and numerically for Gaussian/box/triangle pulses; saturation only by
the Gaussian to <1%.

**Phase 2 — Attach ℏ.** *Goal:* turn Δk into Δp. *Method:* apply λ=h/p with h from `κ=h/m` (FD02,
0.02%). *Success:* Δx·Δp ≥ ℏ/2 with the coefficient ℏ/2 **derived, not inserted**; trace ℏ provenance.

**Phase 3 — Minimum-uncertainty packet.** *Goal:* show the free-vortex wake saturates the bound.
*Method:* evolve a discrete Gaussian wake one tick at a time (FLM05); track variance product.
*Success:* product stays within 1% of ℏ/2 while the packet spreads — spreading is real, indeterminacy is not.

**Phase 4 — Energy–time & linewidth.** *Goal:* Δt·ΔE form. *Method:* finite-duration wake on the
time axis; map to natural linewidth Γτ ≈ ℏ. *Success:* Γ = ℏ/τ reproduced; hooks QM06.

## Success criteria (canonical A–F) + anti-tautology gate

- **PASS (A — NATIVE):** all four phases native; `Δx·Δk ≥ ½` derived from discrete Fourier band-limit,
  ℏ attached via `κ=h/m` (FD02), `Δx·Δp ≥ ℏ/2` to ±1% with zero fitted scale; Gaussian saturates,
  Δt·ΔE follows on the time axis.
- **QUALIFIED (C — CONVERGENCE):** bound reproduced but ℏ attaches via one flagged borrow from FD02.
  **Anti-tautology gate: if the `ℏ/2` only appears because `[x,p]=iℏ` (or an operator-variance
  inequality) was written into the code, the answer was imported — cap at C.** Expected landing.
- **PENDING (D):** Fourier floor shown but the Gaussian-saturation or Δt·ΔE step only heuristic.
- **FAIL (F):** cannot get `ℏ/2` without importing the canonical commutator `[x,p]=iℏ`. Report honestly.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction | What kills it (numeric) |
|---|------|----------------|-------------------------|
| T1 | band-limit is the source | `Δx·Δk ≥ ½` for **every** lattice pulse; `= ½` only for the discrete Gaussian (to <1%) | if any lattice pulse gives `Δx·Δk < ½ − 0.01`, uncertainty is not a band-limit fact → thesis dead; if the box/triangle also saturate ½, the saturation argument is wrong |
| T2 | coefficient is `ℏ/2` | derived `ℏ/2` within ±1%, h traced to `κ=h/m` (±0.02%) | if `ℏ/2` is off by >1%, or matches only after `[x,p]=iℏ` is assumed, ℏ was smuggled → C, not A |
| T3 | vortex stays definite | per-tick x and p of the vortex are **sharp**; only the *wake* spreads | if the model requires the vortex's own x or p to be spread (a packet, not a point) to hit the bound, ontic indeterminacy crept back in → F on the determinism claim |

## Dependencies

**Upstream:** QM01 (relay-wake kinematics, λ=h/p), FD02 (`κ=h/m` fixes ℏ), FLM05 (tick evolution).
**Downstream:** QM06 (linewidth/Δt·ΔE), QM04 (variance ↔ residence density).
**Related:** [[project_paradox_census]] (§8.2 — no ontic randomness owed), [[project_foundational_ontology_influx_monopole]] (no ψ).

## Questions This Opens *(generative — log new ones in `QM02_VERDICT.md`)*

1. **Does the discrete lattice give a *correction* to `ℏ/2`?** A continuum Fourier transform gives
   exactly `½`; a finite N-spation pulse on a granular lattice may give `½ + O(1/N²)`. Is that residual
   a *measurable* floor — an SDT fingerprint on the uncertainty bound near the spation cutoff?
2. **Is the minimum-uncertainty packet the *free vortex's actual* wake shape?** If the equality case
   (discrete Gaussian) is literally the wake a free vortex drags (QM01), then "minimum uncertainty" is
   not special preparation — it is the default. Can that be shown, not just asserted?
3. **Does Δt·ΔE = the linewidth Γτ ≈ ℏ feed QM06's line widths quantitatively?** If the same band-limit
   sets both, QM06's emission widths are *predictions*, not fits — is the Lyman/Balmer natural width
   reproduced?
4. **Is there an entropic (information) form?** The band-limit is also an entropic-uncertainty
   statement. Does the relay lattice give the entropic bound natively, and does it match or undercut
   the QM one?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — QM02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (flag the ℏ-attach borrow from FD02 if used)
- Engine namespaces used: measured (h via κ=h/m from FD02), FLM05 tick — NO ψ, NO commutator, NO atomic:: in the band-limit chain
- Phase thresholds (committed before run): P1 Δx·Δk ≥ ½ exact (Gaussian saturates <1%) · P2 ℏ/2 ±1% · P3 product within 1% of ℏ/2 while spreading · P4 Γ=ℏ/τ reproduced
- Forbidden retroactive changes: write `[x,p]=iℏ` / an operator-variance inequality into the code then claim A; widen tolerances; plug ℏ; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols (h, κ) | STOP — report blocker | Fit to target |
| P1 some pulse gives `Δx·Δk < ½` | re-check the discrete variance definition (lattice, not continuum) | **KILL** the band-limit thesis | redefine variance to force ≥ ½ |
| P1 box/triangle also saturate ½ | refine the saturation criterion (smoothness functional) | **OPEN** the Gaussian-uniqueness claim | claim Gaussian-only without showing it |
| P2 ℏ/2 off >1% or needs the commutator | alternative native ℏ route (κ=h/m vs FD02 circulation) | **OPEN**; cap at C — ℏ was imported | assume `[x,p]=iℏ` then report A |
| P3 product needs the vortex itself to spread | re-derive spreading as wake-only (vortex point stays sharp) | **OPEN** the determinism claim; report honestly | let the vortex become a packet and call it native |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · the canonical commutator / operator-variance inequality inserted into
  the native chain · `atomic::`/GM/G in the band-limit chain · burying the T3 determinism outcome.

---

*QM02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

**REASSESSMENT (2026-07-04, Harvey directive — §G GATE-CONTRABAND check) — two-channel scope note,
appended before the run completes.** The RUN_LOG commitments (frozen 2026-07-03) are untouched — no
gate moves. This note scopes the premise only:

- The band-limit thesis is a statement about the **energy/pulse channel**: the wake is a relayed
  displacement field, and relay at c (measured light speed — unchanged) is what makes Δx·Δk ≥ ½ a
  physical bandwidth statement. That stays.
- Under the two-channel architecture (FLM14 RUN_LOG ADJ-7; Synchrony Theorem, FARMER_PASS
  2026-07-03 refinements 5–6), **constraint through gear-locked clusters propagates uncapped** and
  is not subject to the wake's Fourier band-limit. Grading consequences: (a) any FAIL/cap earned
  here is a verdict on the *wake spectrum*, not a global "SDT cannot beat ℏ/2" — do not extrapolate
  the bound to constraint-channel phenomena (EPR steering, QM05 joint readout, FLM14 gear phase);
  (b) T3's determinism claim (vortex x, p sharp every tick) is if anything strengthened — the sharp
  per-tick values are constraint-side facts, the spread is a pulse-side (readout/wake) fact. A
  ruling conflating the two channels would be §G GATE-CONTRABAND (enforcing the rival's "all
  information is c-capped wave content").
