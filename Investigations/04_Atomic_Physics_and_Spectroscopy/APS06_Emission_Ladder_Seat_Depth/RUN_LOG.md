# APS06 — RUN LOG

> Author: J. C. Harvey, Melbourne. Execution per `PROMPT_EXECUTION_PROTOCOL.md`.
> Append-only during the run. Pre-Run Commitment Block filled BEFORE any code.

## Pre-Run Commitments — APS06

- **Prompt completion target:** A (all four phases executed as §④ asks)
- **Physics class hoped:** NATIVE for the ordering + ceiling recovery; the survey is an
  OBSERVED empirical check (exceptionless neutron-requirement), not a derivation.
- **CALIBRATED budget:** 0 — none permitted; any fit flagged explicitly.
- **Engine namespaces used (single source of truth):**
  - `atomic::` — `R_inf_derived = m_e·c·α²/(2h)` (laws.hpp:929), `rydberg_energy_eV` (laws.hpp:871),
    `bohr_velocity` (laws.hpp:896), `bohr_radius` (laws.hpp:901).
  - `measured::` — `Ry_eV` (laws.hpp:155, comparison anchor only), `R_inf` (laws.hpp:154),
    `alpha` (laws.hpp:130), `h` (laws.hpp:133), `c` (laws.hpp:110), `m_e` (laws.hpp:151),
    `hbar` (laws.hpp:111), `eV_to_J` (laws.hpp:183), `MeV_to_J` (laws.hpp:184).
  - `nuclear::` — `alpha_grammar(Z,A)` (nuclear.hpp:131): n_d=3Z−A−2, n_t=A−2Z, valid iff both ≥0;
    valid wedge 2Z ≤ A ≤ 3Z−2 (nuclear.hpp:130); H3 grammar (nuclear.hpp:139).

- **Phase thresholds (committed before run):**
    - **P1 monotone ordering:** ZERO inversions across the four seat classes
      (molecular < outer-shell < inner-shell(Z) < nuclear); H n=1 reproduces `Ry_eV` to < 50 ppm.
    - **P2 ceiling:** `|E_ceiling − Ry_eV|/Ry_eV < 50 ppm` recovered from `R_inf_derived`
      (i.e. from m_e,c,α,h — NOT by printing `Ry_eV`); wedge scan admits ZERO (Z≥2, N=0) valid nuclides.
    - **P3 neutron requirement:** ZERO counterexamples (a bound N=0, Z≥2 gamma emitter) = PASS; ONE = KILL.
    - **P4 overlap:** ≥1 electronic + ≥1 nuclear line within a factor 2 in energy, both cited.

- **Forbidden retroactive changes:** widen any tolerance; relabel an OBSERVED-ANCHOR band as
  DERIVED; hand-edit the alpha-grammar wedge; rescue a T4 counterexample with a fit; local constant
  namespaces; import "X-rays are lower-energy than gammas" as a definitional result; G/M/GM, ψ,
  quarks/gluons, ΛCDM in the SDT chain.

## Environment note (ADJ-000)

- **Trigger:** No C++ compiler present in this environment (checked `cl` — needs vcvars, not found;
  `g++`/MinGW — not found; no VS `vcvars64.bat` on standard paths). The PROMPT §6/TOOLING explicitly
  permits Python ("`python3` fine (seat→band table; nuclide survey…)").
- **Committed response (allowed adjustment, PROMPT §⑩ "python3 fine"):** implement the tool as
  `aps06_seat_ladder.py`. To avoid IDENTITY-PASS, the 13.6 eV ceiling is rebuilt as
  `R_inf_derived = m_e·c·α²/(2h)` from the whitelist primitives read from `laws.hpp`
  (values transcribed with laws.hpp line citations), NOT by reading `Ry_eV`. `Ry_eV` and `R_inf`
  appear only as the OBSERVED comparison anchors. The alpha_grammar is reimplemented byte-for-byte
  from `nuclear.hpp:131` (n_d=3Z−A−2, n_t=A−2Z) and cross-checked against the 3-exception count
  (H-1, H-2, He-3 alpha-invalid) that `nuclear.hpp`'s own static_asserts enforce.
- **What did NOT change:** thresholds, whitelist, no fits, output filenames (`.py` vs `.cpp` is the
  only rename — logged here per §6 "rename ⇒ ADJ entry").

---

## Phase gates (filled during run)

Tool: `aps06_seat_ladder.py` (Python; no C++ compiler available — see ADJ-000).
Constants transcribed from `laws.hpp` with line citations; ceiling rebuilt from
`R_inf_derived = m_e·c·α²/(2h)` (laws.hpp:929), NOT from `Ry_eV`. Ran exit 0.
stdout captured to `APS06_results.txt`; machine table to `APS06_results.csv`.

### P0 — sanity (R_inf_derived vs measured R_inf)
- ACTUAL: `R_inf_derived = 1.0973731568e7 m⁻¹`; |Δ|/R_inf = **0.0000 ppm**. **PASS.**
  (Confirms no units bug; the derived closed form reproduces CODATA R_inf.)

### P1 — seat-depth ladder monotone ordering  →  PASS-GATE
- Four seat classes sort by `s` (release energy) with **0 inversions**:
  molecular 0.1 eV  <  H n=1 13.61 eV  <  Pb K-shell 9.15e4 eV  <  nuclear 1.33e6 eV.
- Molecular + nuclear magnitudes are **OBSERVED-ANCHOR** bands (tagged); the two
  electronic depths are **DERIVED** from `R_inf_derived`.
- H n=1 ceiling (DERIVED) = 13.605693123 eV vs `Ry_eV` → **0.000 ppm** (< 50 ppm gate). PASS.

### P2 — 13.6 eV ceiling + wedge scan + Z² X-ray climb  →  PASS-GATE
- Ceiling `Z²·R_inf_derived·hc` (Z=1) = 13.605693123 eV → **0.000 ppm** vs `Ry_eV`. PASS.
  HONEST CAVEAT: exact because `R_inf_derived` is the same closed form CODATA uses; this is a
  geometric *recovery* from {m_e,c,α,h}, not an independent measurement of 13.6 eV.
- Alpha-grammar wedge scan on the N=0 line (A=Z, Z=1..10): **zero** (Z≥2,N=0) alpha-valid
  nuclides. H-1 alpha-invalid (n_t=−1); He-2 alpha-invalid (n_t=−2) + measured-unbound. PASS.
- Z² X-ray climb (H,He,C,Fe,Pb) monotone: 13.6 eV → 91.5 keV, all electronic seats. PASS.

### P3 — neutron-requirement survey (DECISIVE)  →  PASS-GATE
- 18 gamma emitters surveyed (emitting/de-exciting nucleus, fully cited NNDC A-chain);
  **every one has N ≥ 1**. Counterexamples (N=0, Z≥2, gamma): **0** (gate ZERO = PASS; ONE = KILL).
- Sr-90 included as a control: N=52 but pure β⁻ (no gamma) — confirms N≥1 is necessary, not sufficient.
- Diproton (He-2) measured unbound; only bound N=0 nuclide is H-1, which emits no nuclear gamma
  (its deepest emission is the 13.6 eV electronic Lyman limit).

### P4 — X-ray/gamma overlap = provenance, not energy  →  PASS-GATE
- W Kα1 (Z=74) electronic X-ray 59.32 keV vs Am-241→Np-237* nuclear gamma 59.54 keV;
  ratio **1.0037** (within factor 2). Same photon, different seat. No "X-rays<gammas" definition used.

### ADJ-001 — P3 emitter-identity correction (post first run, pre-verdict)
- **Trigger:** first-run survey listed some SOURCE nuclides where the gamma is actually emitted by
  the DAUGHTER (e.g. 1332.5 keV is Ni-60*, not Co-60; 1274.5 keV is Ne-22*, not Na-22; Am-241's
  59.54 keV is Np-237*). Not a counterexample (all still N≥1) but a labelling defect — the stress
  discipline forbids fished/mislabelled rows.
- **Response (allowed — data-quality fix, no threshold change):** relist (Z,A) as the EMITTING
  (de-exciting) nucleus with accurate NNDC citation. Re-ran; result unchanged (0 counterexamples,
  all N≥1). One dedup collapsed Fe-57's two lines onto the same emitter → 18 rows.
- **What did NOT change:** thresholds, whitelist, the PASS verdicts.

---

## Final decision (all phases): PASS-GATE ×4.  Prompt completion **A**; physics class
mixed — **NATIVE** (ordering) + **CONVERGENCE/IDENTITY** (ceiling, honestly flagged) +
**OBSERVED** (the decisive neutron-requirement survey). See `APS06_VERDICT.md`.
