# PPT04 (neutrino magnetic moment) — blank-slate assessment (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `ppt04_reset_1.cpp` exists.

## 0. Inputs read and exposure
Read: `PPT04/PROMPT.md` in full (including the 2026-10-05 audit correction); `laws.hpp` (`law_VI::winding::W_electron`, `W_proton`; the comment at the neutrino line "W = 0 (open winding) → neutrino"). External, verified by search on 2026-10-10: Borexino Phase-II 2.8×10⁻¹¹ μ_B (90% CL); GEMMA about 2.9–3.2×10⁻¹¹ μ_B (analysis-dependent; 5.0×10⁻¹² with an atomic-ionisation mechanism); XENONnT, flavour-universal, about 7.2×10⁻¹² μ_B (a 2025 reanalysis; the collaboration's own 2022 figure of about 6.3×10⁻¹² was not confirmed); the minimal-extension Dirac value 3.2×10⁻¹⁹ (m_ν/eV) μ_B. Not read: `INVESTIGATION.md`, `PPT04_VERDICT.md`, `results.txt`, the old `.cpp` and the scroller.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | "Magnetic moment" is not defined natively. It is a coefficient of response to a magnetic field, and a field is not a primitive in SDT. A native observable would be the response of a body to a circulating relay environment; none is written, so the table's "≠ 0" for the electron and proton and "0" for the neutrino is a classification by winding, not a computed moment. |
| D2 | premise | The comparison unit μ_B (and μ_N for the neutron caveat) is a borrowed unit (no magnetons). It is used only in the OBSERVED column, where the experimental limits are stated in it. |
| D3 | gating | The falsifier "any non-zero μ_ν at 10⁻²⁰" lies nine orders below every limit (audit correction, 2026-10-05); the discriminant against the current upper limit is the quantity to state. Registered: gap = limit / SM value for m_ν = 0.06 eV, for each limit. |
| D4 | gating | Phase 0 (refactor of the old tool to `laws.hpp`) concerns a file this run does not open; the new instrument has no local redefinition of c, ℏ, α, m_e, m_p; its only literals are the labelled external limits. |
| D5 | premise | The step from W = 0 to μ_ν ≡ 0 ("no toroidal circuit, ℓ = 2 = 0") is an assignment of the topology class to the neutrino (from the pip ruling) followed by the statement that no circulation gives no circulation-induced response. The table cannot fail; it is a classification. Neutron: the prompt's caveat (W = 3 composite) is a premise about the nuclear grammar, not tested here. |
| D6 | record | The neutrino mass 0.06 eV enters only the SM comparison column (a census input); the SDT column carries no mass. |
No downgrade is made on agreement grounds.

## 2. Registered quantities and outputs (fixed before the run)
**Topology table** from `law_VI::winding` (W_electron = 1, W_proton = 3) and the neutrino W = 0 (comment-level in `laws.hpp`; no constant exists). Labels: CLASSIFICATION (no moment is computed).
**SM column (OBSERVED-TARGET).** μ_ν(SM) = 3.2×10⁻¹⁹ (m_ν/eV) μ_B at m_ν = 0.06 eV.
**Limits (OBSERVED).** Borexino 2.8×10⁻¹¹; GEMMA 2.9×10⁻¹¹ (and 3.2×10⁻¹¹); XENONnT 7.2×10⁻¹² (reanalysis) and 6.3×10⁻¹² (collaboration, unconfirmed); all μ_B, 90% CL.
**Discriminants.** (i) gap = limit / μ_ν(SM), in orders of magnitude; (ii) the improvement in sensitivity needed to reach the SM value; (iii) the one-sided statement: an observed moment at or above the limit would exclude both μ_ν ≡ 0 and the minimal-extension value (it would be a shared exclusion class), so a detection cannot separate SDT from the SM minimal extension, and a null result cannot either.
**Outcome form.** Classification stated; discriminant stated; "untestable now" recorded if the gap exceeds six orders (a registered threshold). Grades: CLASSIFICATION G2 (definition missing, D1); discriminant COMPUTED.
**Expected landing (hand estimate).** SM value 1.9×10⁻²⁰ μ_B; gaps 1.5×10⁹ (Borexino), 3.8×10⁸ (XENONnT reanalysis): 8.6–9.2 orders; untestable now.

## 3. Results (COMPUTED; instrument `ppt04_reset_1.cpp`, output `ppt04_reset_1_results.txt`; single pass, no amendment)
**Topology table (CLASSIFICATION).** e⁻ W = 1 and p W = 3 from `law_VI::winding`; ν W = 0 (comment-level in `laws.hpp`, no constant). No moment is computed.
**SM column.** μ_ν = 3.2×10⁻¹⁹ × 0.06 = 1.92×10⁻²⁰ μ_B.
**Discriminant.** limit / SM: Borexino 2.8×10⁻¹¹ → 1.46×10⁹ (9.16 orders); GEMMA 3.2×10⁻¹¹ → 1.67×10⁹ (9.22) and 2.9×10⁻¹¹ → 1.51×10⁹ (9.18); XENONnT 7.2×10⁻¹² (reanalysis) → 3.75×10⁸ (8.57); XENONnT 6.3×10⁻¹² (collaboration 2022, unconfirmed) → 3.28×10⁸ (8.52). Range 8.52–9.22 orders, above the registered 6-order threshold: **UNTESTABLE NOW**. The sensitivity must improve by a factor 3.3×10⁸ from the best limit to reach the SM value.
**One-sided statement.** An observed moment at or above ~10⁻¹¹ μ_B would exclude both μ_ν ≡ 0 (the W = 0 reading) and the minimal-extension value; a null result is consistent with both. A detection or a null result at present sensitivity cannot separate SDT from the SM minimal extension.
Sources for the external numbers (search 2026-10-10): arXiv 2510.12449 (XENONnT and GEMMA citations), arXiv 2204.03011 and 1510.01684 (Borexino, GEMMA), arXiv 1801.08887 and 1603.00337 (the Dirac coefficient 3.2×10⁻¹⁹).

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| Topology table, μ_ν ≡ 0 from W = 0 | **G2, CLASSIFICATION** | the moment is not defined natively (D1); the step is an assignment of the winding class (D5); the table cannot fail |
| Phase 0 refactor | **not applicable to this run** | old tool not opened; the new tool has no local constants (D4) |
| Discriminant against current limits | **COMPUTED: untestable now (8.5–9.2 orders)** | external limits OBSERVED; μ_B is a borrowed unit used only there (D2) |
| Falsifier "any non-zero μ_ν at 10⁻²⁰" | **not reachable**; replaced by "non-zero at or above ~10⁻¹¹ μ_B excludes W = 0 reading and the minimal-extension value alike" | shared exclusion class |

## 5. Direction
1. Define the observable natively (the response of a body to a circulating relay environment) before any further moment claim; until then the table is a classification and PPT10/PPT11 should treat it so.
2. The ν mass in the SM column is a census input only; the pip ruling gives no mass for the SDT column.
3. No experiment now running reaches the SM value; the only decidable content is a detection above ~10⁻¹¹ μ_B.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
