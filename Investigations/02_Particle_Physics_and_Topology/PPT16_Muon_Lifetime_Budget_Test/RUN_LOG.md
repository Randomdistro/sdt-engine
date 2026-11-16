# PPT16 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Gates, inputs, validation checks and rejection criterion are in `PROMPT.md`, section
"Pre-registration (2026-10-03)". Route: `sdt::laws::law_V`. Registered γ convention: from
(pc, mc²). Altitude survival out of scope (PENDING_DATA).

## 2026-10-03 — run

Built with MSVC (`cl /std:c++20 /EHsc /O2 /I Engine\include`). Validation passed (five
known-answer checks). Single pass: τ_pred = 64.3720 µs against τ⁺, τ⁻ and the weighted
mean, all inside 2σ. Rejection criterion not met. Output: `ppt16_results.txt`.
Conclusions: `PPT16_ASSESSMENT.md`.
