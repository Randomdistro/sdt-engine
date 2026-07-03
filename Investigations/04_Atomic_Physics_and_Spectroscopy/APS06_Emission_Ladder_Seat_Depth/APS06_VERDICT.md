# APS06 — VERDICT

> Author: J. C. Harvey, Melbourne.
> **Prompt completion: A** (all four gated phases executed as §④ asks).
> **Physics class: mixed — NATIVE (ordering) + CONVERGENCE/IDENTITY (13.6 eV
> ceiling, honestly flagged) + OBSERVED (the decisive neutron-requirement
> survey, exceptionless on the tested set).**

Tool: `aps06_seat_ladder.py` (consumes constants transcribed from `sdt/laws.hpp`
and `sdt/nuclear.hpp` with line citations). No C++ compiler in this environment
(ADJ-000); PROMPT §6/TOOLING permits `python3`. Ran exit 0; stdout →
`APS06_results.txt`, machine table → `APS06_results.csv`.

---

## Phase-by-phase result

| Phase | Gate (committed) | Actual | Decision |
|---|---|---|---|
| **P0** sanity | `R_inf_derived ≈ R_inf`, ~0 ppm | 0.0000 ppm | PASS |
| **P1** monotone ladder | 0 inversions; H n=1 → Ry_eV < 50 ppm | 0 inversions; 0.000 ppm | **PASS-GATE** |
| **P2** 13.6 eV ceiling | < 50 ppm from `R_inf_derived`; wedge admits 0 `(Z≥2,N=0)` | 0.000 ppm; 0 nuclides; Z² climb monotone | **PASS-GATE** |
| **P3** neutron requirement | 0 counterexamples = PASS; 1 = KILL | 18 emitters, all N≥1; **0** counterexamples | **PASS-GATE** |
| **P4** overlap provenance | ≥1 electronic + ≥1 nuclear within factor 2, cited | W Kα1 59.32 vs Am-241 59.54 keV, ratio 1.0037 | **PASS-GATE** |

**Dual verdict:** Prompt completion **A**; Physics class **NATIVE ordering +
CONVERGENCE ceiling + OBSERVED survey** (no KILL, no OPEN blocking the parent
claim). The seat-depth thesis stands on the tested corpus.

---

## Falsification table (with actual numbers)

| Test | Hypothesis | Result | Verdict |
|---|---|---|---|
| **T1** | seat depth monotone with energy | 4 classes, 0 inversions (0.1 eV → 13.6 eV → 91.5 keV → 1.33 MeV) | **PASS** |
| **T2** | 13.6 eV recoverable from geometry | `Z²·R_inf_derived·hc` (Z=1) = 13.605693123 eV, 0.000 ppm | **PASS** (see caveat) |
| **T3** | no bound all-proton nucleus past H-1 | wedge scan Z=1..10, N=0: 0 alpha-valid nuclides | **PASS** |
| **T4** | every nuclear gamma from a neutron-bearing nucleus | 18 emitters surveyed, all N≥1, **0** counterexamples | **PASS** |
| **T5** | X-ray/gamma overlap is provenance not energy | W Kα1 vs Am-241 at 59.3/59.5 keV, ratio 1.0037 | **PASS** |

No falsifier tripped. One bound proton-only gamma emitter would have been a
KILL; none exists on the chart, and none can (the `N=0` line is outside the
alpha wedge for all `Z ≥ 1`, and He-2 is measured unbound).

---

## Circularity / delete-test note

- **The ceiling (T2)** passes the delete-test *against `Ry_eV`*: delete
  `measured::Ry_eV` from the derivation and the 13.6 eV still emerges from
  `m_e·c·α²/(2h)` — `Ry_eV` is used only as the comparison column. **BUT** the
  match is exact by construction (that closed form *is* how the Rydberg energy
  is defined from `{m_e,c,α,h}`), so the number is **CONVERGENCE/IDENTITY**, not
  an independent measurement. Reported as such, not dressed up as a prediction.
  This is the WATCH-POINT the PROMPT flagged, and it is handled honestly.
- **The ordering (T1)** and **the wedge scan (T3)** pass the delete-test
  cleanly: they use only the whitelist Bohr kinematics and the pure-integer
  alpha grammar; no measured spectrum is fed in to force the order.
- **The survey (T4)** is genuinely empirical and independent: `N = A − Z` is a
  trivial integer transform, but *which* nuclides emit gamma and *that* the
  diproton is unbound are OBSERVED facts the theory did not choose. The claim
  could have been killed by a single counterexample and was not.

---

## Honest residue

- The 13.6 eV "0.000 ppm" is an **identity-grade** recovery, not a fresh
  measurement (stated in P2 and the DERIVATION caveat). The *structural* content
  — deepest neutron-free electronic seat — is what earns NATIVE, not the ppm.
- The survey is **Class C corpus**: 18 hand-curated, fully-cited emitters, not a
  full machine-read AME2020/NNDC sweep. Upgrading to the complete nuclide table
  (every gamma emitter in ENSDF) would move the survey from "exceptionless on
  the tested set" to "exceptionless on the chart" (Class A corpus). The physical
  claim is unchanged; the corpus is partial. **DEFER** the full sweep.
- Molecular and nuclear band magnitudes are **OBSERVED-ANCHOR** (tagged), never
  relabelled as DERIVED. Only the two electronic depths and the wedge result are
  DERIVED.
- Diproton instability is taken as measured datum; its SDT derivation is
  **DEFER → NP19/NP20**. The neutrino-below-gamma rung is **DEFER → PPT10**.

---

## STRESS-TEST SELF-AUDIT

1. **Independent, or identity/circular?**
   - *Ordering (P1)* and *wedge/diproton (P2/P3)*: **INDEPENDENT** — Bohr
     kinematics + pure-integer alpha grammar; pass the delete-test; no spectrum
     fed in to force the result.
   - *13.6 eV ceiling (P2)*: **IDENTITY/CONVERGENCE** — exact because
     `R_inf_derived = m_e c α²/(2h)` is the defining closed form; a *recovery*
     from whitelist primitives, honestly **not** an independent measurement. It
     is **not** an identity-pass on `Ry_eV` (that value is never read into the
     derivation, only compared against) — the QM06-style failure mode
     (wrapping `atomic::` and calling it a prediction) is explicitly avoided.
   - *Neutron-requirement survey (P3/T4)*: **INDEPENDENT / OBSERVED** — the real
     result; falsifiable, could have died on one counterexample, did not.

2. **Fished numbers?** **No.** Zero fitted/CALIBRATED parameters. No tolerance
   was widened after seeing a value. The survey emitters are NNDC-cited; the
   first-run labelling defect (sources listed where daughters emit) was
   **corrected** to the true emitting nucleus (ADJ-001), not massaged to help —
   the result was already 0 counterexamples before and after.

3. **Dimensions.** `R_inf_derived` `[m⁻¹]` × `hc` `[J·m]` = `[J]` → eV via
   `eV_to_J`. `s` and `E_γ` in `[eV]` throughout the ladder; nuclear via
   `MeV_to_J`. Alpha grammar is dimensionless integers `(Z,A)→(n_d,n_t)`.
   `N = A − Z` dimensionless. Overlap ratio dimensionless. All consistent; the
   ladder spans ~7 orders of magnitude (0.1 eV → 1.3 MeV) in one unit.

4. **Honest class + what is owed.**
   - **Class A (prompt completion)** — four phases executed, all gates met.
   - **Physics class: NATIVE** for the seat-depth *ordering* and the wedge
     (no-proton-only-nucleus) result; **CONVERGENCE/IDENTITY** for the 13.6 eV
     ceiling magnitude; **OBSERVED (Class C corpus)** for the exceptionless
     neutron-requirement survey.
   - **Owed:** (i) the full ENSDF/AME2020 machine sweep to lift the survey to
     Class A corpus (DEFER); (ii) SDT derivation of the diproton's instability
     (DEFER → NP19/NP20); (iii) the neutrino-below-gamma rung (DEFER → PPT10);
     (iv) a *first-principles* value of 13.6 eV that does not route through the
     CODATA closed form would upgrade the ceiling from IDENTITY to a true
     derivation — currently OPEN, shared with the α/`m_p/m_e` seed-wall status.
