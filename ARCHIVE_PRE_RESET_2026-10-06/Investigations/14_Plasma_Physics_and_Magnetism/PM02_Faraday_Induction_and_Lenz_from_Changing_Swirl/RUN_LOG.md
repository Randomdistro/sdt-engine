# RUN_LOG — PM02 (Faraday Induction and Lenz from Changing Swirl)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Written BEFORE any code.

## Pre-Run Commitments — PM02

- Prompt completion target: **C** (the prompt itself expects C; the minus-sign-from-handedness-alone
  is expected to hit the HG-1 wall found in PM01 — committed before running).
- Physics class hoped: NATIVE for (Φ = streamline count; motional ≡ transformer kinematics);
  CONVERGENCE (energy-fixed) for the Lenz minus, per the prompt's own pivot row 3.
- CALIBRATED budget: 0. Native units (κ=1, m=1); SI only on final tagged lines (none needed).
- Engine namespaces: `measured` (via laws.hpp include); PM01 swirl `w` (aligned-bundle geometry,
  earned in PM01 P2a).
- Firewall: no Faraday rule, no primitive E/B, no µ_B/µ_N; Φ is a count.

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | Φ two routes | Φ as enclosed-circulation count (∮w·dl) vs area-integral of ∇×w agree < 1% |
| P2 | EMF residual | \|∮(−∂w/∂t)·dl − (−dΦ/dt)\|/\|EMF\| < 1% across ≥5 ramp rates. **PRE-FLAGGED:** this is Stokes' theorem — a kinematic identity, not physics; the physics is the drive rule (which coupling the carriers obey), tested in P3. Turns ratio N₂/N₁ exact (count linearity). |
| P3 | Lenz sign | Dichotomy test, committed in advance: couple loop carriers to the changing swirl with the only two available linear rules — K1 (co-drag, F = +g∂w/∂t) and K2 (reactive, F = −g∂w/∂t) — each with the carriers' own induced wake fed back (PM01 P2a). Prediction committed: K1 → runaway (throughput created, ledger violation ⇒ KILLED by conservation); K2 → opposition, ledger closes < 2%. **The minus is then energy/ledger-fixed = CONVERGENCE, not NATIVE**, unless the handedness alone selects K2 — which PM01's HG-1 result says it cannot, today. No hand-flip; the dichotomy is the result. |
| P4 | motional ≡ transformer + eddy ledger | same dΦ/dt via loop motion vs source ramp on shared geometry: EMFs agree < 1%; drag opposes motion, drag ∝ v (fit slope 1.0 ± 0.1 over ≥4 speeds), dissipated power = work input < 2% |

### Forbidden retroactive changes

Import Faraday/E/B into the sign chain then claim A; choose the minus silently (the K1/K2 dichotomy
must be run and shown); widen tolerances; magnetons anywhere; IDENTITY-PASS (P2 is pre-flagged as an
identity and will NOT be counted as a discovery).

## Run record (filled after execution)
- Build/run: see `pm02_results.txt`; verdict: `PM02_VERDICT.md`.

## ADJ-1 (2026-07-04, after run 1, disclosed)

Run 1 eddy-brake bracket (ν=0.3 ⇒ τ=5; v=0.05–0.4) probed the saturation crossover (v·τ ≳ fringe
width): slope 0.372. That is real eddy-brake saturation physics, but not the committed small-v
linear-response regime. Bracket moved INTO the committed regime (ν=3.0 ⇒ τ=0.5; v=0.02–0.16;
v·τ ≤ 0.08 ≪ 1). **Gate unchanged (1.0 ± 0.1).** Run 2 slope: 0.992 → PASS. Both runs kept in
`pm02_results.txt`.

## Run record
- Build: MSVC clean, 0 errors. Run: exit 0. All committed gates: P1 3.1e-5/1.7e-4 PASS ·
  P2 1.6e-9 PASS (pre-flagged identity) · P3 dichotomy as committed (K1 runaway at L_g=2, K2
  opposes+decays) · P4 motional≡transformer 0.0 PASS (by-construction at kinematic level,
  flagged) · P4 drag slope 0.992 PASS (ADJ-1).
