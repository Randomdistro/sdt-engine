# PPT16 — Muon Lifetime Dilation as a Movement-Budget Test

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B62). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

Cosmic-ray muons made at ~15 km altitude reach the ground in numbers only possible if their
2.197 μs rest lifetime stretches with speed — the classic time-stretch measurement, with
modern storage-ring data at γ ≈ 29.3 as the precision anchor.

## SDT footing

Law V makes this a bookkeeping theorem: the muon's decay clock is its internal circulation,
and circulation is paid from the one budget — v_circ² + v² = c². At v = 0.9994c the internal
turning slows by exactly the budget ratio, and the unwinding that constitutes decay slows
with it. Nothing dilates but the spending. The suite recovers SR as theorems (L7); this
investigation is the cleanest laboratory instance, worth its own tally because the measured
number (survival fraction vs altitude; storage-ring lifetime) tests the budget directly.

## Pre-registration skeleton (complete before any tool)

- Question: does the budget ratio reproduce the storage-ring lifetime at γ = 29.3 and the
  measured altitude survival, with the rest lifetime as the one measured input?
- Rejection criterion (populated): any measured lifetime departing the budget ratio beyond
  experimental error — the budget admits no correction terms; a deviation would wound Law V
  itself.
- Anchors: τ_μ(rest) = 2.197 μs; CERN storage-ring τ(γ=29.3); altitude flux pairs.
- Tolerance: experimental error bars, no widening.

## Benchmark linkage

Catalogue row B62 · suite coverage roster · a straightforward tally candidate once written
from the engine's law_V.

## Pre-registration (2026-10-03, before the instrument exists)

**Route.** `sdt::laws::law_V` only (`time_dilation`, `v_circ`, `gamma`). The engine exposes no
muon constants; the tool declares them locally as MEASURED-INPUT with provenance and the
addition to `sdt::laws::measured` is a propose-and-wait item.

**Measured inputs.** m_μc² = 105.658 MeV; τ₀ = 2.1969811 µs (PDG; 2.197 µs cross-checked
against the Bailey et al. summary); storage-ring magic momentum pc = 3094 MeV, rounded to the
last quoted digit (σ_p = 0.5 MeV, propagated into the prediction).

**Anchor.** Bailey et al., *Nature* **268**, 301 (1977), CERN muon storage ring, γ ≈ 29.3:
τ⁺ = 64.419 ± 0.058 µs, τ⁻ = 64.368 ± 0.029 µs, weighted τ = 64.378 ± 0.026 µs. The
secondary-source transcription of these values (search summaries of the paper) is recorded
as such; the primary paper was not retrieved.

**Procedure.** β from (pc, mc²) as pc/√((pc)²+(mc²)²) ; v = βc ; τ_pred = τ₀ · c / v_circ(v).
Single pass. No free parameter.

**Instrument validation (before touching the anchor).** (i) v=0 gives ratio 1 exactly;
(ii) β=0.6 gives v_circ/c = 0.8 and τ ratio 1.25; (iii) β=0.8 gives 0.6 and 1.6667;
(iv) v_circ² + v² = c² to 1e-12 relative at ten velocities spanning 0–0.9999c;
(v) two-route agreement: `law_V::time_dilation` against the closed form √(1+(pc/mc²)²) at the
registered inputs to 1e-12.

**Rejection criterion (populated).** The criterion is met if τ_pred departs any of the three
anchors (τ⁺, τ⁻, weighted) by more than 2σ, with σ² = σ_exp² + σ_pred². A budget carrying
any correction term of order 10⁻³ would meet it.

**Out of scope for this run.** Altitude-survival flux pairs: no verified pairs are cached in
the repository. Recorded PENDING_DATA; not scored.

**Labels.** Numerical result: COMPUTED from a MEASURED-INPUT set. Provenance relative to
special relativity: CONVERGENT (Law V yields the Lorentz factor; no measured τ(γ) enters).
Discrimination against special relativity: not discriminating (shared closed form).

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The premise is that the muon decay clock equals its movement budget, which is the special-relativistic time-dilation relation, so a pass cannot distinguish the framework from the standard account (the run confirmed it is convergent and non-discriminating).

**Correction:** Record it as a consistency check and gate on a quantity SR does not predict, or retire it as a test.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
