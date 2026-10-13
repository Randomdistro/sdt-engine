# OP04 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04.

## Pre-Run Commitments — OP04 (written BEFORE first compile/run)

- Prompt completion target: **C**
- Physics class hoped: **CONVERGENCE** (pre-declared: a real transverse 2-vector with per-axis
  arrival-time lags is ALGEBRAICALLY ISOMORPHIC to the Jones calculus; the firewall's own cap)
- CALIBRATED budget: **0** in the projection chain (chiral Δn = MEASURED-INPUT for magnitude)
- Engine namespaces used: `measured::` (context); no local constant namespaces
- **Implementation honesty rules (committed):**
  - The state is a REAL time-domain transverse displacement u(t) = (Ax·cos(ωt+φx), Ay·cos(ωt+φy)) —
    sampled mechanically over a period. No Jones matrices, no Stokes axioms, no spin operator, no
    complex-amplitude ontology anywhere in the machinery.
  - A polariser is anisotropic closure: instant-by-instant projection of u(t) onto the pass axis
    (the orthogonal component is dumped). A retarder lags ONE axis by a fraction of the tick period.
  - Unpolarised light = Monte-Carlo ensemble of random transverse orientations (no Stokes formalism).
- Phase thresholds (committed before run):
  - P1: linear/circular/elliptical states all representable as (Ax, Ay, φy−φx); trajectory traced
  - P2: Malus I(θ)/I(0) within 0.1% of cos²θ over 0–90°; crossed extinction ≤ 1e-12·I₀;
    three-polariser revival = I₀/8 within 1% (MC ensemble, K ≥ 2e5)
  - P3: QWP on linear@45° gives circularity min|u|/max|u| ≥ 0.99; HWP rotates linear@ψ to −ψ
    (rotation 2ψ) within 0.1°
  - P4: chiral split (n_L ≠ n_R, MEASURED-INPUT): rotation angle ∝ L (doubling L doubles rotation
    to 0.1%); the SIGN mapping to EMC03 ± redirection is expected **OPEN** (assertion, not derived)
- §G mirror check: gates trace to measured anchors (Malus cos², I₀/8, 2ψ); no gate legislates
  handedness ontology; "photon spin" appears nowhere as target or mechanism — classical polarisation
  optics never required it either, and the verdict will say so plainly.
- Forbidden retroactive changes: apply a Jones matrix then claim A; assign spin ±ℏ as mechanism;
  widen tolerances; flip the activity sign by fiat.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Phase | Result | Notes (from `results.txt`, run 2026-07-04, exit 0) |
|-------|--------|-------|
| P1 | **PASS-GATE** | linear circ 6.1e-17, circular circ 1.000000, elliptical 0.3950 — all carried by (Ax, Ay, lag) |
| P2 | **PASS-GATE** | Malus dev 4.6e-15; crossed floor 3.7e-33·I₀; three-polariser revival 0.125176 vs 1/8 (0.14%, MC K=2e5) |
| P3 | **PASS-GATE** | QWP circularity 1.000000; HWP 20° → −20.0000° (2ψ rotation) |
| P4 | **PASS-GATE (magnitude) / OPEN (sign, as committed)** | rotation 3.056° @1 cm, 6.112° @2 cm, ratio 2.000000; sign→EMC03 mapping asserted, not derived |
