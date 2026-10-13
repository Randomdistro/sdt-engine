# PPT16 — Muon lifetime and the movement budget: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Claimed by session sdt-engine-e0.

**Read:**
- `PROMPT.md`, including its 2026-10-03 pre-registration, which is carried here unchanged
- `laws.hpp` law_V
- `graph_v2.json` (layer 0; no suppliers or dependents)

**Not opened:** `PPT16_ASSESSMENT.md`, `RUN_LOG.md`, `ppt16_results.txt`, `ppt16_muon_budget.cpp`. The instrument was written afresh. The prompt's own audit line (convergent, not discriminating) was seen.

## Run
- Instrument: `ppt16_reset_1.cpp`; output in `ppt16_reset_1_results.txt`. MSVC, single pass.
- **Validations V1–V5 met.** V5: law_V against the closed form, to 1.2e-14.

**Prediction from the budget.** β = 0.999417421, so c/v_circ = 29.300229. With τ₀ = 2.1969811 µs:

**τ_pred = 64.3720 ± 0.0104 µs.** The σ comes from pc = 3094 ± 0.5 MeV.

| anchor (Bailey et al. 1977; secondary transcription per the prompt) | measured (µs) | measured − predicted | deviation |
|---|---|---|---|
| µ⁺ | 64.419 ± 0.058 | +0.0470 µs | +0.80σ |
| µ⁻ | 64.368 ± 0.029 | −0.0040 µs | −0.13σ |
| weighted | 64.378 ± 0.026 | +0.0060 µs | +0.21σ |

**Rejection criterion not met.** The budget ratio is consistent with all three anchors. The fractional agreement with the weighted anchor is +9.3e-5, against an experimental 1σ of 4.0e-4. The budget admits no correction term larger than about 1e-3 at γ = 29.3.

## Labels
- **Result:** COMPUTED from a measured-input set (rest energy, rest lifetime, magic momentum). No free parameter.
- **Provenance:** CONVERGENT. Law V yields the factor; no measured τ(γ) enters.
- **Discrimination:** not discriminating. The closed form is shared with special relativity.
- Following the 2026-10-05 correction, this is recorded as a **consistency check of Law V**, not a discriminating test.

**Grade: G4** (consistent, independent origin, not discriminating).

## Limitations
- The anchors are a secondary transcription; the primary paper was not retrieved.
- The muon constants are declared locally (propose-and-wait for `measured`).
- Altitude-survival pairs: PENDING_DATA.
- A discriminating quantity would need a native prediction that special relativity does not make. None is specified.

## Comparison with the archived record
Deferred to the end-of-programme pass.
