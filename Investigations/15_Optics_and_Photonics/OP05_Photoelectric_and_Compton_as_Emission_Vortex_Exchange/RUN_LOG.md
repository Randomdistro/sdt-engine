# OP05 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04.

## Pre-Run Commitments — OP05 (written BEFORE first compile/run)

- Prompt completion target: **C**
- Physics class hoped: **CONVERGENCE** — pre-declared: if the derivation is energy–momentum
  bookkeeping with E = hf as an OBSERVED anchor plus Law-V kinematics, it is SR kinematics with
  renamed nouns and will be classed exactly that. No pretence otherwise.
- CALIBRATED budget: **0** (W and m_e MEASURED-INPUT; h = measured tick→energy conversion, whitelist)
- Engine namespaces used: `measured::` (h, m_e, c, lambda_C_e as the OBSERVED comparison column)
- **Implementation honesty rules (committed):**
  - The Compton solver solves the conservation ledger NUMERICALLY (bisection on the scattered
    tick rate after eliminating the vortex recoil direction) — the closed form λ_C(1−cosθ) appears
    ONLY as the OBSERVED comparison column.
  - `λ_C = h/(m_e c)` is an IDENTITY given measured h and m_e. The prompt's hope that λ_C falls out
    of Law-VI vortex geometry independently is NOT attempted by arithmetic re-expression; if no
    independent geometric route exists in the engine, that row is **OPEN**, stated plainly.
  - No point-quantum of light anywhere: the emission enters the ledger as (E = hf, p = E/c), an
    extended relay train's energy/momentum rates. That E = hf is itself underived (why the lattice
    exchanges energy in f-proportional units) is the **named ℏ entry point** — logged, not papered.
- Phase thresholds (committed before run):
  - P1: emission ledger E(589 nm) and p = E/c self-consistent; E/p = c to 1e-12 (labelled identity)
  - P2: Millikan slope from least-squares over 6 tick rates = h to 1e-9 relative (IDENTITY under the
    anchor — labelled as such, NOT claimed as a derivation); thresholds for Na (2.28 eV), Cs (2.14 eV),
    W (4.55 eV) printed as wavelengths, order-consistent with observation
  - P3: numeric conservation solve at θ = 30/60/90/120/180°, incident 0.0711 nm (Mo Kα, Compton's
    anchor) and 511 keV: |Δλ_solved − λ_C(1−cosθ)|/λ_C(1−cosθ) < 1e-6; λ_C printed vs
    measured::lambda_C_e (definitional agreement — labelled IDENTITY)
  - P4: Thomson limit — relative shift → 0 as hf ≪ m_ec² (600 nm case printed); moving-vortex
    (inverse) case: energy GAIN with the correct sign, scale within ×2 of the γ²(1+β)² head-on factor
- F3 (prompt absorption) committed handling: OBSERVED anchor = attosecond-streaking data (tens of
  attoseconds relative delays; no intensity-dependent build-up at any measured flux). This supports
  threshold-not-accumulation but does NOT support the prompt's literal "sub-attosecond" phrasing —
  the tension is reported as-is; F3 row = OPEN. (§G: the gate is the measured number, not the story.)
- §G mirror check: no gate legislates "no superluminal/sub-cycle"; the same-tick vortex swallowing
  (one coherent gulp) is constraint-channel adjacent (FLM14 ADJ-7) and is NOT ruled out by any gate here.
- Forbidden retroactive changes: relabelled photon–electron kinematics claimed as NATIVE; plugging
  λ_C; tolerance widening; point-photon smuggling.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Phase | Result | Notes (from `results.txt`, run 2026-07-04, exit 0) |
|-------|--------|-------|
| P1 | **PASS-GATE (labelled IDENTITY)** | 589 nm: E = 2.104995 eV, E/(pc) = 1.000000000000000; ℏ entry point named in output |
| P2 | **PASS-GATE (slope = IDENTITY) / F3 OPEN** | Millikan slope = 6.626070e-34 = h, intercept 2.280 eV; thresholds Na 543.8 / Cs 579.4 / W 272.5 nm; timing tension reported |
| P3 | **PASS-GATE** | numeric ledger solve, worst rel dev 1.2e-12 vs λ_C(1−cosθ) over 10 cases; λ_C row = IDENTITY, vortex-geometry route OPEN |
| P4 | **PASS-GATE** | Thomson shift 8.1e-06 at 600 nm; moving-vortex gain 3.9999 vs 4.0000 (sign + scale correct) |
