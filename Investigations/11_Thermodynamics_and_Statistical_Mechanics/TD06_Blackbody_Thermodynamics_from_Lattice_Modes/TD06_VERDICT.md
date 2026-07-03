# TD06 — Verdict: Blackbody Thermodynamics from Lattice Modes

**Dual verdict: Prompt completion B · Physics class CONVERGENCE (capped by TD02 inheritance; the ε=hν bridge is the disclosed load-bearing assertion).**
**Author:** J. C. Harvey, Melbourne · 2026-07-03 · Tool: `td06_lattice_blackbody.cpp` → `results.txt` (exit 0).

## What was run

| Phase | Gate (pre-committed) | Result | Status |
|---|---|---|---|
| P1a mode density | counted vs 8πν²/c³ mean < 0.1% | 0.0030% (periodic bulk) | PASS |
| P1b Bose from counting | stationarity fit R²>0.9999, RMS vs Bose < 1%, geometric marginal < 1% | R²=1.000000, intercept 1.7e-5, RMS 0.006%; marginal 0.014% | PASS |
| P2 Planck curve | < 0.1%; RJ + Wien limits | 0.0014%; limits recovered (see note) | PASS |
| P3 Stefan–Boltzmann | mode-sum < 0.1%; exponent 4.00±0.02 | 0.0086%; 4.0000; I3 = 6.493383 vs π⁴/15 = 6.493939 | PASS |
| P4 Wien | root derived ±1e-5; b < 0.1% | 4.965114 by bisection; b dev 0.008% | PASS |
| P5 UV honesty | committed disclosure | delivered (see below) | DONE |
| SAR02 cross-check | consistency only | a = 7.565733e-16 vs measured a_rad, 4.4 ppm — same as SAR02; **not the pass** | OK |

**Incidents (documented in RUN_LOG):**
1. Run 1 P1a/P2/P3 fired together — one root: the octant standing-wave count carries the Weyl
   *surface* term (dev·R = −1.44…−1.49, constant — a deterministic 1/R boundary deficit my error
   budget omitted). Pivot to the boundary-free periodic bulk count (allowed alternative native
   route; gates unchanged); the octant contrast is kept in the output as evidence, and it is
   itself physics: a real walled cavity has the surface term; bulk space does not.
2. Run 1 P1b fired with R² = 1.000000 but intercept 0.682: the paired-shift move set accidentally
   conserved total quantum *number*, equilibrating to Bose-with-μ. Radiation quanta carry no
   number conservation; energy-conserving merge/split moves added (premise fix, gates unchanged).
   The fixed climb lands on μ = 0 Bose (intercept 1.7e-5) — an instructive fired-and-traced
   falsifier: the counting *itself* discovers that removing number conservation is what
   distinguishes the photon gas.
3. RJ sub-check: value 0.97521 at x = 0.05 differs from 1 by exactly the analytic x/2 term
   (second-order RJ expansion 1 − x/2 + x²/12 = 0.975208; agreement 3e-6). My RUN_LOG "1%"
   wording was mis-specified against this estimator; disclosed, not re-gated.

## What is native, what is inherited, what is asserted

- **Counted, native to this tool:** the mode density (P1a), the Bose denominator emerging from
  ln W maximisation with no reservoir, no partition function, and no QM lift (P1b — including
  the geometric per-mode marginal, i.e. the "multiple quanta per mode" series is counted), the
  π⁴/15 (P3, from the sum), the 4.9651 root (P4, from bisection).
- **Inherited:** the occupation-factor legitimacy from TD02 (native counting; class CONVERGENCE)
  — TD06 is therefore capped at CONVERGENCE per its own T4. SAR02's "LINGUISTIC-BORROW" debt on
  the occupation is now discharged by the TD02+P1b route.
- **Asserted (the honest crux):** `ε = hν` — the identification of the throughput-per-tick
  granularity with Planck's quantum. P5 shows the ℓ_P mode cutoff does ZERO numerical work at
  physical temperatures (x_cutoff ~ 1.5e30 at 300 K); the spectrum's finiteness is carried
  entirely by ε = hν, which is Planck's postulate renamed as the Law-I bridge. The "quantisation
  is structural, not an extra axiom" claim therefore remains **narrative**: the structure that
  does the work is the energy quantum, not the spatial lattice.

## Physics class: CONVERGENCE

Which step would break on a non-SDT substrate? None — this is Planck/Bose counting executed
cleanly. The SDT-specific *prediction* (a Wien-tail deviation at the spation scale) requires
T ~ 1e32 K: stated, untestable. Prompt Q4 (why 2 polarisations) remains OPEN — the factor 2 was
*input* as the two transverse branches, not derived here.

**Earned:** all three laws recomputed from one mode count at ≤0.01% with the Bose sum shown
native; the walled-vs-bulk Weyl term identified and demonstrated. **Owed:** a derivation of
ε = hν from relay mechanics (the whole quantum content); the 2-polarisation count (CONDENSA c_T
link); any observable ℓ_P fingerprint.

**Certification:** P1–P4 COMPUTED; ε=hν ASSERTED-BRIDGE (disclosed); zero CALIBRATED; SAR02 cross-check consistent at 4.4 ppm.

## HUNTER §D — seven questions on the CONVERGENCE landing (OPEN items)

1. **Why:** the numerics are Planck/Bose counting; the quantum content sits entirely in ε = hν,
   which is asserted (Law I bridge), and the ℓ_P cutoff does zero work at physical T (P5).
2. **Recoverable?** PARTIAL for the bridge; OPEN for the polarisation count.
3. **Failed to account for:** why one relay mode carries energy only in hν lumps — the tool
   demonstrated everything downstream of that, nothing upstream of it.
4. **Errored premise:** "the lattice is already discrete, so quantisation is free." Spatial
   discreteness at ℓ_P is NOT energy discreteness at hν; conflating the two was the smuggle the
   prompt's own F-clause guards against, and P5 documents it instead of hiding it.
5. **Freedom that fixes it:** derive ε = hν from relay mechanics (FLM09 bond-switch waves /
   Law-VI winding — a quantised circulation per transit would do it); derive the 2 transverse
   branches from CONDENSA c_T (prompt Q4).
6. **Accounting for the freedom:** both candidates are native structures already in the canon;
   neither derivation exists yet. Owed, not plugged.
7. **Cascade:** the ε=hν debt is its own root (TD-ROOT-3) — it also underwrites TD02's quanta
   and every "quantisation is structural" claim in the suite; the occupation-class cap cascades
   from TD-ROOT-1 via TD02.

**Prompt completion B · Physics class CONVERGENCE (capped by TD02; ε=hν asserted) · Recovery PARTIAL (native routes named: Law-VI winding / FLM09 for the bridge, CONDENSA c_T for the factor 2) · Cascade root TD-ROOT-3 (ε=hν bridge underived) + TD-ROOT-1 (occupation inheritance)**
