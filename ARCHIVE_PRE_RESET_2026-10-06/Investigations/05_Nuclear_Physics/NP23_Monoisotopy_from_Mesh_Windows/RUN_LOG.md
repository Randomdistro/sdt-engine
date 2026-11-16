# RUN_LOG — NP23: Monoisotopy from Mesh Windows

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-06. **Written BEFORE any tool code.**
> Tool: Python, pure counts; no engine include; NP08 MeV rows cited from the repo record.

## Pre-Run Commitments

- Prompt completion target: **A** (both phases executed per spec, no knob taken)
- Physics class ceiling (declared): **CONVERGENCE / CALIBRATED (data-interpolated)** even at
  full PASS — see Design-time exposure disclosure below. NATIVE not reachable in this run.
- CALIBRATED budget: **0 fitted constants** (the gated rule V1 uses held-out data
  interpolation + committed global tie-break only; V0/V2 scans each carry one global
  held-out median constant, declared, scan-only).

## Anchor conventions (committed)

- **C1 — stable:** no experimentally observed decay (NUBASE2020-class). Measured-2β/2EC,
  measured-α, and primordial-β/EC nuclides are excluded from windows and listed as leads
  (full list in PROMPT §6). Ta-180m kept with isomer flag.
- **C2 — grammar:** n_t = A−2Z, n_d = 3Z−A−2 (standard). H (Z=1) pre-grammar; He-3
  non-decomposable — both flagged, excluded from grammar statistics and calibration.
- **C3 — target set:** the 26 monoisotopic elements (19 mononuclidic + 7 with radioactive
  sibling): Be F Na Al P Sc V Mn Co As Rb Y Nb Rh In I Cs La Pr Eu Tb Ho Tm Lu Re Au.
  Bi-209 = unscored near-stable row; Tc, Pm = unscored lead-only rows; Th/Pa out of scope.
- **C4 — held-out calibration set:** all non-target elements Z=2..82 with ≥1 stable nuclide.
  Every target has held-out immediate neighbours at Z±1 (verified in-run); Bi uses linear
  extrapolation from Tl(81), Pb(82).
- **C5 — parity constraint (data-structural, declared):** no odd-Z element above Z=7 has an
  even-A stable ground state (Ta-180m is an isomer — footnote). Hence odd-Z candidate sets
  are restricted to odd n_t. This is an OBSERVED regularity of the anchor table, not an
  imported pairing axiom (it is re-verified by the tool over the whole table; if it fails,
  the constraint is dropped and logged).

## Identities declared up front (can earn NOTHING)

- n_t = N−Z (the grammar triton count IS the neutron excess — a relabeling).
- Any restatement of Mattauch/pairing structure in grammar coordinates = CONVERGENCE at most
  (PROMPT §3 rival declaration).
- The NP08 ledger rows (B(α) = 28.296, B(Be-8) = 56.500, Δ = −0.092 MeV) are IDENTITY
  (measured BEs consumed); only their USE as a window-pinch mechanism is SDT content.

## Rule variants (ALL examined; look-elsewhere ledger — committed now)

Let m(Z') = median n_t over the stable nuclides of held-out element Z'; t̂(Z) = linear
interpolation of m between the nearest held-out neighbours (Z±1 for all 26 targets).
Candidates at Z: grammar-legal n_t (0 ≤ n_t ≤ Z−2), odd-Z restricted to odd n_t (C5).

- **GX — general packing-competition exclusion (even-Z only):** a candidate whose grammar
  configuration is beaten by whole-alpha reassembly in the measured ledger is excluded
  BEFORE nearest-candidate selection. The repo record carries this ledger only at Z=4
  (NP08: Be-8 = α+2d loses to 2α by 0.092 MeV → n_t=0 excluded at Z=4). No other exclusion
  is applied anywhere. At odd Z the pure-α competitor is grammatically impossible (reported
  as a Phase A structural point).
- **V1 (GATED — the Phase B rule):** predicted n_t\* = legal candidate nearest t̂(Z) after GX;
  **tie-break = LOWER n_t\** (deuteron-rich side; native motivation: ATOMICUS rules §6 —
  tritons are the strain units, triton overload is the decay side). Predicted A = 2Z + n_t\*.
  Zero per-element freedom: everything comes from held-out neighbours + three global,
  pre-committed choices (C1 convention, C5 parity, LOW tie-break) + GX.
- **V0 (scan, cannot PASS):** valley power-law n_t\* = legal candidate minimizing
  |n_t − c·(2Z+n_t)^(5/3)|, c = median of n_t/A^(5/3) over held-out stable nuclides with
  n_t ≥ 1. RIVAL-SHAPED (the 5/3 is the rival's Coulomb/asymmetry balance) — logged for
  look-elsewhere, scan-only.
- **V2 (scan, cannot PASS):** quadratic-in-blocks n_t\* nearest (Z−2)²/κ, κ = held-out median
  of (Z−2)²/n_t (n_t ≥ 1). Scan-only.
- **Sensitivity (reported, unscored):** V1 with HIGH tie-break; V1 with the 2β-measured
  nuclides restored to windows (convention flip). Both reported for honesty; neither can
  alter the gate.

**Look-elsewhere count:** {V0, V1, V2} × tie-break {LOW, HIGH} × convention {C1, C1+2β} = 12
cells examined at design time; ONE cell gated (V1, LOW, C1), chosen before the tool ran, with
the LOW and C1 choices motivated independently of score (rules §6; "no observed decay" is the
only clean measured criterion).

## Design-time exposure disclosure (the honest part)

The rule family and tie-break were designed WITH hand-estimates of the target rows in view
(the stable table is centuries-old public data; ~20 rows were approximated by hand during
design, projecting V1 ≈ 23/26 with misses {Mn, La, Ho} and the tie-break resolving ~7 tie
rows). **Therefore Phase B is graded as POST-DICTION-EXPOSED and capped at CONVERGENCE /
CALIBRATED (data-interpolated) regardless of score** — same discipline as NP10 run 2's
declared post-diction. The tool's exact numbers override the hand-estimates; no variant,
tie-break, convention, or candidate set may change after the tool prints.

## Gates (committed now, before any number exists)

- **G0 (data integrity):** the width-1 element set computed from the typed anchor table must
  equal the declared 26-element target set exactly. Mismatch = typing error → fix table
  against the declared source (logged), re-run; grading with a broken table forbidden.
- **G1 (Phase B, the only scoreable gate):** V1 correct stable-A picks ≥ 20/26 **AND** the
  Be row = A 9 (via GX complement). PASS → CONVERGENCE-capped per disclosure. FAIL → §D.
- **Phase A produces NO gates** — leads and reported correlations only.
- **Unscored rows (committed):** Bi-209 (near-stable; extrapolated), Tc and Pm
  (longest-lived proxy, lead-only), V1 residual table (actual − t̂ per single).

## Forbidden retroactive changes

Widening G1; editing V1/tie-break/parity/GX after results; flipping C1 after results;
promoting V0/V2 or a sensitivity cell to PASS; per-element patches; special-casing any Z
beyond the declared GX; deleting the design-time exposure disclosure.

## Planned outputs

`np23_mesh_windows.py` → `PYTHONIOENCODING=utf-8 python ... | tee np23_results.txt`
(exit 0) → `NP23_VERDICT.md` (dual verdict; §D on any FAIL; canonical line).

---

## Post-run addendum (2026-07-06, after single execution — nothing above edited)

- **ADJ count: 0.** One pre-run hygiene edit before first execution (tool return value set to
  exit-0 per the committed hygiene clause); no commitment touched.
- **G0 PASS** (width-1 set from the typed table == the declared 26 exactly; 252 stable
  nuclides under C1; 31 excluded-natural rows printed for audit).
- **G1 PASS: V1 = 24/26, Be row = A 9 via GX** (NP08 −0.092 MeV exclusion; no special case).
  Misses: La-139 (pred 137), Ho-165 (pred 163) — both t-rich of t̂ (+1.75 / +1.25).
  Tie rows In/Pr/Re: 3/3 correct under the committed LOW tie-break.
- **Design-time hand-estimate reconciliation (disclosure follow-through):** the hand
  projection said ≈23/26 with misses {Mn, La, Ho}; the tool shows 24/26 — the Mn hand-estimate
  was an arithmetic error (t̂=4.50 lies 0.5 from candidate 5, 1.5 from 3: no tie, correct
  pick). Tool numbers govern; disclosure retained.
- **Scans/sensitivity (unscored, as committed):** V0 16/26; V2 14/26; V1-HIGH 21/26;
  V1+2β-restored 22/26. The gated cell was best; exposure cap (CONVERGENCE) stands.
- **Unscored rows:** Bi-209 extrapolated HIT (A=209); Tc → A=97 (matches longest-lived proxy);
  Pm → A=147 (longest-lived is Pm-145 — proxy miss, lead only, no stable A exists).
- Verdict: `NP23_VERDICT.md`. No §D owed (no gate failed); miss autopsy and §G MIRROR are in
  the verdict.
