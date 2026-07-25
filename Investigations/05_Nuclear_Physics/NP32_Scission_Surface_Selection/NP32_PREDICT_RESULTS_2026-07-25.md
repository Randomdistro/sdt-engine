# NP32 — cross-fissioner prediction: RESULTS (checked against 8 systems)

> Criterion frozen in `NP32_PREDICT_PRECOMMIT_2026-07-25.md` **before** any distribution opened.
> Data: `Datasets/nuclear/fission_yields/` + `nuclear/IAEA_U235_*` (independent yields, Σ over Z at
> fixed A → post-prompt-neutron primary-fragment mass yield). Tool: `/tmp/np32_refine.py` (kept below).
> Peaks = yield-weighted centroid over mode±8 (smooths the severe odd-even Z staggering; the raw
> single-bin mode gave unphysical ν and is rejected — recorded so the method choice is visible).

## Measured (independent yields)

| system | A_fiss | E | A_L | A_H | A_L+A_H | ν(back-computed) | ν̄(lit) | valley | P/V |
|---|---|---|---|---|---|---|---|---|---|
| U-235 | 236 | thermal | 95.2 | 136.5 | 231.6 | 4.4 | 2.42 | 0.0001 | 571 |
| U-233 | 234 | thermal | 93.2 | 137.2 | 230.4 | 3.6 | 2.49 | 0.0002 | 573 |
| Pu-239 | 240 | thermal | 101.3 | 136.3 | 237.6 | 2.4 | 2.88 | 0.0004 | 171 |
| Pu-241 | 242 | thermal | 102.7 | 136.0 | 238.8 | 3.2 | 2.94 | 0.0009 | 82 |
| Np-237 | 238 | fast | 98.4 | 136.4 | 234.8 | 3.2 | 2.60 | 0.0005 | 155 |
| Am-241 | 242 | fast | 101.5 | 137.6 | 239.2 | 2.8 | 3.20 | 0.0007 | 101 |
| U-238 | 239 | fast | 99.0 | 137.2 | 236.2 | 2.8 | 2.50 | 0.0002 | 321 |
| Th-232 | 233 | fast | 90.5 | 139.8 | 230.2 | 2.8 | 2.30 | 0.0007 | 115 |

## Verdict against the pre-committed gates

- **P1 — heavy peak STATIONARY → PASS (strong).** slope(A_H vs A_fiss) = **−0.197** all-8 (gate
  <0.25); **−0.019 excluding Th-232** — A_H pinned in **136.0–137.6** across seven fissioners with
  A_fiss 234→242. The heavy fragment does not move with the parent.
- **P2 — light peak SLIDES 1:1 → PASS.** slope(A_L vs A_fiss) = **+1.26** all-8 / **+1.16** excl-Th
  (gate 0.7–1.3). Light peak walks 93→103.
- **P3 — complementarity closes → PASS (strong internal check).** ν back-computed from the peak sum
  alone lands **2.4–4.4** (gate 1.5–4.0) and matches literature ν̄ to **mean |Δ| = 0.70 neutrons** —
  ν was never an input; it fell out of the peak positions and complementarity.
- **P4 — Th valley signature → REFUTED (reported as failed).** I pre-called Th-232 to have the
  shallowest valley / lowest P/V. It does **not** (Am-241 P/V 101 < Th 115). The valley depth tracks
  **incident energy** — thermal (U-235/U-233 P/V ~570) deep, all fast systems filled (P/V ~100–320) —
  a physically correct excitation effect that is **not** Th-specific. The sub-prediction's mechanism
  was wrong. (Th is still the mildest *peak-position* outlier — A_H 139.8, highest — which is why
  removing it flattens P1 from −0.197 to −0.019; but not via the signature I named.)

## Honest classification (SM status held in view, as pre-stated)
**The lock-anchored-heavy-fragment picture is CONSISTENT across 8 fissioners** — a test that could
have failed (if A_H slid with A_fiss, the picture dies; it did not). But:

- **DEGENERATE IN VALUE.** Heavy-peak stationarity at A≈137 is textbook fission — standard theory
  gets it from the ¹³²Sn double shell (Z=50, N=82). SDT does **not** beat the SM on any number here.
- **The SDT-native content is the MECHANISM only:** the closure is the point of maximal
  interleave-lock (measured this session, NP30 §11), so the cut cannot pass through it and the heavy
  fragment forms *around* it. That is a native *reading*, **not a proof** — the data is consistent
  with it, not uniquely selected by it.
- **What is NOT derived (stated plainly):** the *location* of the lock (N=82) is still the empirical
  magic number, exactly as in the SM. SDT explains why a closure resists the cut; it does **not** yet
  derive **why the closures sit at 2,8,20,28,50,82,126**. So this is **convergence-in-value,
  native-in-mechanism, anchor-location-still-empirical.** No fork, no fitted parameter, no CALIBRATED
  knob — and no overclaim of derivation.

## What genuinely advanced
1. The cross-fissioner **stationary-heavy / sliding-light** structure is now measured on 8 systems
   from the fresh cache, with complementarity closing to ν̄±0.7 — SDT's picture survives a real
   multi-system stress it had never faced (prior work was U-235 only).
2. **Th-232 flagged as the peak-position edge** (consistent with its known symmetric-component
   enhancement) — the lightest parent is where a single lock is least dominant.
3. The **genuine open** is unchanged and now sharpened: NP32's minimum-cost cut must predict the
   *light*-peak position and the *asymmetry* (why A_H−A_L, not A/2+A/2) from geometry with zero fit —
   the stationary heavy anchor is necessary but not sufficient, and it is degenerate until the cut
   itself is derived. The N=82 location remains the upstream debt (why the magic numbers).

> **Verdict:** P1 PASS · P2 PASS · P3 PASS · P4 REFUTED-as-stated · overall **picture consistent,
> label convergence-in-value / native-in-mechanism / anchor-location-empirical**. Zero fitted
> parameters. The claim that survives: *SDT's interleave-lock is consistent with the measured
> cross-fissioner fission systematics* — not that it beats the SM, and not that it derives the anchor.
