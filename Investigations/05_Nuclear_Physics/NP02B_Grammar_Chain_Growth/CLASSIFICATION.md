# NP02B — Provenance Classification

Labels per the project scheme (`Audits/FORMULATIONS_PROVENANCE_AUDIT.md`): `provenance` · `correspondence` · `input_dependency` · `class` (A/B/C/D/E/X/F).

| # | Formula / claim | provenance | correspondence | input_dependency | class |
|---|---|---|---|---|---|
| 1 | `n_t = A−2Z`, `n_d = 3Z−A−2` (grammar) | SDT-derived | known-match | isotope integers | **C** |
| 2 | construction lattice: `+d` steps `n_d`, `+t` steps `n_t` | SDT-derived | internal-only | isotope integers | **B** |
| 3 | pathway multiplicity `= C(Z−2, n_t)` | SDT-derived | internal-only | isotope integers | **B** |
| 4 | `+2` deuterons (n_d-axis) ≡ stellar alpha-capture | SDT-derived | known-match | grammar facts | **C** |
| 5 | `B = k_occ·bonds`, bond counts (α 6, d 1+2, t 3+2) | SDT-derived | internal-only | isotope integers | **B** |
| 6 | `k_occ = 2.224 MeV/contact` (deuteron-pinned) | calibrated | known-match | calibrated-target | **E** |
| 7 | `B_occ` MeV binding estimate | calibrated | partial-match | calibrated-target | **E** |
| 8 | `f_t = n_t/(n_d+n_t)`; overload past ~17% → He-5 ejection | SDT-derived | novel-prediction | grammar facts | **D** |
| 9 | trefoil traction `T = 3(W+1) = 12` (free-strand `E=σL→∞`) | SDT-derived | internal-only | primitive-whitelist | **B** |
| 10 | He-3 core grammar `n_t=A−2Z+1`, `n_d=3Z−A−3`; EC gate `n_d≥2` | SDT-derived | known-match | isotope integers | **C** |
| 11 | EC core-change `−2`d`+1`t | SDT-derived | known-match | grammar facts | **C** |
| 12 | EC `rate ∝ Q²` (PF spread) | external-input | known-match | measured Q | **X** |
| 13 | `Z³(In-111)/Z³(Be-7) = 1838 ≈ m_p/m_e` | SDT-derived | known-match | isotope integers | **C-flagged** *(numerical coincidence; risk_flag: post-hoc ratio)* |
| 14 | inversion `n_t == unpaired electrons` (48% match) | SDT-derived | novel-prediction | grammar facts vs measured-e | **D** *(partially supported; reported honestly as not-a-law)* |
| 15 | Rule 18 "proton is the code" (geometry mirror) | SDT-posited | novel-prediction | — | **D** *(conceptual; the geometry-mirror form is untested)* |

**Notes.** The only fitted scale is `k_occ` (#6) → everything downstream of it (#7) is **E**. The lattice/multiplicity results (#2,#3) consume *only isotope integers* — parameter-free (**B**). The inversion (#14) is the speculative prize: a genuine **D** that the run shows is **only 48% quantitatively true** — disclosed, not laundered. #13 is flagged as a numerical coincidence, not a derivation.
