# PPT16 Assessment — muon lifetime as a movement-budget test

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `ppt16_muon_budget.cpp` (reads `sdt::laws::law_V` only)<br>
**Stdout:** `ppt16_results.txt`<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)"

## Status

`PPT16_BUDGET_CONSISTENT_WITHIN_TOLERANCE` — COMPUTED, convergent with special relativity,
not discriminating. The storage-ring gate is met; the altitude-survival gate is `PENDING_DATA`.

## Instrument validation

Five known-answer checks passed before any anchor was opened: v = 0 gives ratio 1; β = 0.6
gives v_circ/c = 0.8 and ratio 1.25; β = 0.8 gives 0.6 and 5/3; the budget
v_circ² + v² = c² holds to 1e-12 at ten velocities from 10⁻⁶c to 0.9999c; and
`law_V::time_dilation` agrees with the closed form √(1+(pc/mc²)²) to 1e-12 at the registered
inputs (γ = 29.300228557 by both routes).

## Result

| Input (MEASURED-INPUT) | Value |
|---|---|
| m_μc² | 105.658 MeV |
| τ₀ | 2.1969811 µs |
| pc (magic momentum) | 3094 ± 0.5 MeV |

COMPUTED: τ_pred = 64.3720 µs, σ_pred = 0.0104 µs (momentum rounding 0.0104; τ₀ 0.0001).

| Anchor (Bailey et al. 1977) | τ_meas (µs) | σ_tot (µs) | τ_pred − τ_meas | in σ_tot | 2σ gate |
|---|---:|---:|---:|---:|---|
| τ⁺ | 64.419 ± 0.058 | 0.059 | −0.047 | −0.80 | inside |
| τ⁻ | 64.368 ± 0.029 | 0.031 | +0.004 | +0.13 | inside |
| weighted | 64.378 ± 0.026 | 0.028 | −0.006 | −0.21 | inside |

The rejection criterion (any anchor beyond 2σ) was not met. No parameter was fitted.

## Provenance and discrimination (behavioural §3.8)

- **Provenance:** CONVERGENT with special relativity. Law V yields the Lorentz factor; the
  measured storage-ring lifetime τ(γ) does not enter the chain. Only m_μ, τ₀ (PDG) and the
  ring momentum enter, none of which contains the dilated lifetime.
- **Discrimination:** not discriminating. Law V and special relativity share the closed form
  τ = τ₀γ, so no measurement of τ(γ) separates them.
- No downgrade is applied; none is admissible without a traced contaminating input.

## Limitations

1. **Resolution.** σ_pred is set by the rounding of the quoted momentum (±0.5 MeV). The
   combined test resolves a correction of about 2×10⁻³ in τ, the same level as the paper's
   own 95% bound on the time-dilation factor. A budget correction below that is not excluded.
2. **Input convention.** The registered route takes γ from (pc, mc²), giving γ = 29.3002.
   Bailey's quoted γ = 29.33 would give τ = 64.4375 µs, +0.060 µs from the weighted mean
   (about 2.1σ_tot). The 0.1% difference between the two γ values is the size of the
   experimental error bar. Its origin is not resolved here because the primary paper was not
   retrieved; the anchors above are transcribed from secondary summaries of it.
3. **Coverage.** The altitude-survival measurement named in the seed is not scored: no verified
   flux pairs are cached in the repository.

## Open

- Retrieve the primary Bailey et al. paper and replace the secondary transcription of the
  three lifetimes, p, and the quoted γ.
- Altitude-survival data (primary flux pairs with their uncertainties) into `Datasets/`
  with a manifest row.
- Muon constants (m_μc², τ₀) are absent from `sdt::laws::measured`. Addition is a canon
  edit and waits for approval.
- Benchmark row B62 can carry this as a COMPUTED tally on approval; `Benchmarks/` is not
  edited by this run.
