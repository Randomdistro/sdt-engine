# RUN_LOG — FLM14 (Rotating Spation & Sequential Occupancy)

> Executor: the session (FARMER/HUNTER), 2026-07-04. **Committed BEFORE any tool was written.**

## Pre-Run Commitments

- Prompt completion target: **B** (P1+P2 executed this run; P3–P5 gated on P2, DEFER honestly if unpaid)
- Physics class hoped: NATIVE (P1 rule + frustration-born rotation); P2 honest-emergent whatever the exponent
- CALIBRATED budget: **0 fitted to targets.** P2 carries ONE declared exploratory parameter (the
  entrainment kick strength β, not natively derived yet — FLM03's open coefficient). It will be
  SCANNED and reported as a scan; any claim of the form "dwell ∝ amplitude²" must hold across a
  regime, not at a tuned point. Fitting β to produce 2.000 and claiming derivation = FISHED.
- Forbidden: inserting cos²/psi-squared anywhere (R-Born); widening gates; per-phase re-tuning (F6).

## Committed gates

- **P1-G1 (rule economy):** stepping rule stated in ≤5 native quantities.
- **P1-G2 (frustration):** on a lattice with odd rings, perfect antisymmetric gearing must be
  IMPOSSIBLE (measured frustration > 0) — rotation is then defect-carried, matching OP-2. If the
  lattice 2-colours cleanly, the "rotation must be carried" claim loses its native origin → flag.
- **P1-G3 (local isotropy):** front-arrival speed anisotropy (std/mean over ≥12 directions) of the
  GEARED lattice ≤ 1.2× the ungeared same lattice. Amorphous jitter ON (FLM10 lesson: periodic FCC
  is anisotropic by construction; the comparison is geared-vs-ungeared, same geometry).
- **P2-G1 (emergence):** dwell-time distribution emerges from the stepping rule + self-entrainment
  ONLY. Measured deliverable: the exponent p in dwell ∝ (wake amplitude)^p, fitted from the
  emergent histogram, reported with its β-scan curve. NO committed value of p — the theory's hope
  is p→2, but the commitment is to REPORT p(β) honestly, including "no stable exponent".
- **P2-G2 (no-signalling sanity):** the tour must close (steady state, drift < 1% per revolution);
  a non-closing tour = model unstable → report FAIL.
- **P3–P5:** NOT RUN this session unless P2-G1 yields a stable exponent regime; otherwise DEFER
  with dependency named. Pre-committed: no partial P3 "peek" at the Lamb table with a tuned β.

## ADJ ledger
- **ADJ-1** first execution crashed on Windows cp1252 console (the ≤ glyph) after P1-G2 had
  printed; re-run with PYTHONIOENCODING=utf-8. No code or gate changed; both runs' P1-G2
  value identical (0.347).
- **ADJ-3 (rule-form ladder, gates unmoved):** form-1 global-clock ×7.47 FAIL → form-2
  bond-local relative phase ×2.88 FAIL (improved; residual = quenched phase texture freezing
  bonds; pulse percolates anisotropically around them). Named next ingredient: ENTRAINMENT
  (β kicks annealing the texture) = rule-form-3, requiring the FLM10-grade solver — dispatched
  2026-07-04 with this ladder as its committed baseline (must beat 1.2, not merely 2.88).
- **ADJ-2 (lesson, owned):** P2's minimal ring tour was a foreseeable instrument fault — a
  uniform ring visited uniformly converges to a uniform wake, so the amplitude spread needed
  to measure an exponent cannot exist in that geometry. Caught at run time, reported as
  instrument-not-physics; a sharper design review would have caught it pre-run. The dwell-law
  question is hereby bound to a structured seat geometry (ROOT-SIM class), not re-asked of
  toy rings.
- **ADJ-4 (rule-form-3 instrument spec — committed 2026-07-04 BEFORE flm14_solver.py exists).**
  Gates P1-G3 (≤1.2) and the ladder baseline (must beat 1.2, not merely 2.88) are UNMOVED.
  New instrument commitments:
  * Lattice: FLM10-style CRN — diamond(5) seed, N=1000, WWW bond switches with Keating
    relaxation (Metropolis kT=0.14, cooling 0.85/80), **500 attempted switches** per glass
    (instrument bound, declared: shallower amorphisation than FLM10's ~1/site; the gate is
    geared-vs-ungeared on the SAME geometry, so depth is controlled for). 3 independent
    glass seeds {21,22,23}, each with an independent quenched-phase draw.
  * Per-site rate (native, "rates from local coordination"): omega_i = omega0 * z_i/<z>,
    z_i = geometric coordination (sites within 1.25 * median bond length). omega0=0.37/tick,
    W=0.5 (run-1 instrument constants, unchanged).
  * THE FORM-3 RULE (one rule, F6): bond window opens when contact phase
    c_ij(t) = (phi_i0+dphi_i + phi_j0+dphi_j + (omega_i+omega_j) t) mod 1 < W (g=-1 sum).
    ENTRAINMENT: at contact formation the pulse kicks the RECEIVER once,
    dphi_j += -beta * wrap(c_ij(t_contact)), wrap into [-1/2,1/2) — a pull toward the g=-1
    gearing lock point c=0. No other kick. Wake dphi decays exp(-dt/T_w), T_w = 27 ticks
    (10 rotor periods; instrument constant, NOT scanned; one robustness line at T_w/2, 2*T_w).
  * Front measurement: event-driven first-arrival from the centre site; hop travel time =
    bond length (c0=1); direction-resolved speed v(u)=mean(|r|/t_arr) over a shell
    2.5*dbar < r < 0.42*L, cone cos>=0.75, >=5 sites/cone, **24 golden-spiral directions**
    (>=16 must be valid or the run is reported instrument-fault); anisotropy = std/mean over
    directions; ratio = geared/ungeared, same glass, same phases (paired).
  * beta grid (SCANNED, never fitted): {0 (= form-2 control on this instrument), 0.05, 0.1,
    0.2, 0.4, 0.8, 1.0}. PASS statement must be per-beta; a pass confined to part of the grid
    is reported as a regime, and F6 requires the P2 regime to overlap it.
- **ADJ-5 (P2 structured-tour spec — committed BEFORE code, per ADJ-2's binding).**
  P2-G1/P2-G2 wording unmoved; definitions fixed now:
  * Geometry: 2-D annulus around a heavy central defect. Three rings r={1.0,1.55,2.3},
    counts {8,13,21} (incommensurate), angular jitter seeded; adjacency = ring neighbours
    +-1 and 2 nearest inter-ring links; the defect is NOT occupiable and couples only by
    being a bond-partner of the inner ring (raises inner z, hence omega gradient via the
    SAME omega_i = omega0*z_i/<z> rule). No other defect coupling.
  * Electron = defect stepping when local windows open: on landing at seat s at time t it
    forms contacts with ALL graph neighbours j and applies the SAME single kick per contact,
    dphi_j += -beta*wrap(c_sj(t)); it departs through the first window to open; dwell(s) =
    departure - landing; hop travel time = seat separation.
  * Observables (both reported): p_dwell from log(dwell-per-visit) vs log(A_k) and p_occ
    from log(occupancy fraction) vs log(A_k), A_k = event-sampled mean |dphi_k| over the
    measurement half. **Born-mapped primary = p_occ** (occupancy IS the landing statistic).
  * Exponent defined only if: >=12 seats above 0.05*A_max, amp spread >=x3, AND log-log
    Pearson |r| >= 0.6 (else "no exponent defined — reported"). Run: 40,000 hops, first half
    discarded; 3 tour seeds. beta grid {0.02,0.05,0.1,0.2,0.4,0.8}.
  * STABLE REGIME (the P3-P5 gate) := >=3 consecutive grid betas with defined p_occ,
    |p_i - median| <= 0.3, and P2-G2 closure drift < 1% (mean dwell, half-2 vs half-1).
- **ADJ-6 (conditional CHSH transcription — committed BEFORE code).** Runs ONLY if ADJ-5's
  stable regime exists. QM05 Phase-2 machinery reused verbatim except the imported cos^2
  joint weighting is REPLACED by the emergent residence law: with C=|cos(a-b)|, S=|sin(a-b)|
  (projection geometry of the throughpole channel, not a weighting),
  P(B=A|a,b) = C^p / (C^p + S^p) with p = the MEASURED median p_occ of the stable regime,
  signed, NOT rounded to 2. Marginals measured, no-signalling gate <= 0.002 (unchanged).
  S is reported wherever it lands; 2*sqrt(2), under, over all publishable. No re-tuning of
  beta, T_w, W, omega0 between P1, P2 and this step (F6).
- **ADJ-7 (Harvey directive, 2026-07-04, logged BEFORE acting on it — reclassifies one
  gate, adds a channel; no committed gate MOVED).** The spec smuggled Einstein locality
  (the rival's axiom) as a kill condition. Corrections, verbatim-in-spirit:
  1. **Two-channel dynamics.** Energy/pulse relay stays at c (measured light speed,
     unchanged). ADDED: the geared CONSTRAINT channel — within a geared/contact-locked
     cluster, phase constraint propagates UNCAPPED (rigid-gear-train rigidity; canon
     precedent: the 1.83c seat, k<1 superluminal inside R_p, throughpole = instantaneous
     through-flow, GOM05 rigid hinge units). Concretely: when the pair/cluster is
     gear-locked, a readout constraint on one member updates the geared partner's phase in
     the SAME tick, regardless of separation — no c-delay on constraint, only on pulses.
  2. **Reclassify the no-signalling number.** Marginal flatness <= 0.002 is now an
     OBSERVABLE COMPARISON to measured Bell data (anchor), NOT a route-rejection axiom.
     If marginals deviate: report "disagrees with measured marginals" = data-FAIL. If they
     stay flat WITH the v>c constraint channel: report that as the emergent result
     (constraint carries no free energy — controllability to be ASSESSED, not presumed).
     F3's threshold number is retained; only its CLASS changes (axiom -> data anchor).
  3. **ADJ-6 CHSH implementation** is via this constraint channel (same-tick partner
     update), not via any imported weighting; the C^p/(C^p+S^p) transcription stands as
     committed, with MEASURED p.
  4. F6 (one rule throughout) still binds. Parts A and B are untouched by this ADJ — their
     kicks are local contact events on the pulse channel; no P1/P2 gate involves locality.
- **ADJ-8 (rule-form-4 instrument spec — committed 2026-07-04 BEFORE flm14_form4.py exists;
  run 3).** Gates UNMOVED: P1-G3 <= 1.2; P2-G1 exponent criteria (>=12 seats above
  0.05*A_max, spread >=x3, |r| >= 0.6); P2-G2 drift < 1%; stable-regime rule (>=3
  consecutive betas, |p_i - median| <= 0.3); F6. Ladder to beat: 7.47 -> 2.88/2.29 -> 1.35.
  * **THE FORM-4 RULE (two channels, per ADJ-7).** PULSE channel: every hop travels at c
    (travel time = bond length), NO waits, NO kicks — transparent BY ARCHITECTURE (run-2
    lesson made structural, not parameter-saturated). CONSTRAINT channel: at each first
    contact per bond (i,j), if the contact window coincides — c_ij = (phi_i + phi_j) mod 1
    < W — the bond GEAR-LOCKS: both sites' clusters merge into one RIGID cluster (union-
    find). Rigid = one collective coordinate: member phase phi_i(t) = A_i + sigma_i *
    Omega_c * (t - t_c); g=-1 fixes sigma alternation across each locked bond; phase
    continuity enforced at every merge (A_i re-based at merge time, cluster-wide, SAME
    tick, uncapped — the ADJ-7 constraint channel). Collective rate Omega_c =
    (1/n) * sum_members(sigma_i * omega_i) — the rigid train's net signed drive under
    equal coupling; no new constant. NO snap-to-lock kick: the gears engage at their
    coincident relation as found (window coincidence IS tooth tolerance W). Locks persist
    while engaged (lattice bonds = permanent contact in Part A); release-on-separation is
    live only where contacts are transient (the tour). Same-cluster contact with
    sigma_i*sigma_j = +1 = FRUSTRATED lock refusal (odd rings; the P1-G2 carrier
    population) — counted, not silently dropped. Native quantities: {base phi, omega_i =
    OMEGA0*z_i/<z>, g=-1, W, lock-rigidity} — 5, P1-G1 intact. beta does NOT exist on the
    lattice channel in form-4 (removed, not re-tuned); it survives ONLY as the electron's
    declared contact-kick coefficient in P2 (ADJ-5 verbatim; F6's P2-P5 scope unbroken).
  * Part A instrument: identical CRN machinery (diamond(5), N=1000, 500 WWW switches,
    Keating, glass seeds {21,22,23}), 24 golden directions, same anisotropy measure,
    paired geared/ungeared. Pre-stated: arrival identity is BY CONSTRUCTION (ratio 1.00
    trivially); the run must (a) verify max|t_g - t_u| = 0 exactly, (b) state the
    triviality honestly, and (c) measure the RESIDUAL gearing signature on the constraint
    channel — declared observables: locked-bond fraction, window-refusal fraction,
    frustrated-refusal fraction, cluster-size distribution (largest/N = percolation),
    Omega_c distribution (freeze test: |Omega|/omega0 for the largest cluster), and
    lock-network direction anisotropy (std/mean of locked fraction over the same 24
    cones, bond orientation, +-u pooled). All descriptive; no gate other than P1-G3.
  * Part B (P2 per ADJ-5 with run-2's two corrections, NOTHING else changed): rule, kick,
    W, OMEGA0, T_W, observables, exponent criteria, beta grid {0.02,0.05,0.10,0.20,0.40,
    0.80} all verbatim ADJ-5. Correction 1 — ENSEMBLE-OVER-PHASE: 64 independent initial-
    phase draws (base ~ U[0,1)^N) per beta, geometry FIXED (seed 1), start seat fixed
    (inner shell, seat 0); probability = ignorance of starting tick (R-seq, verbatim).
    8,000 hops per draw, first half discarded (ensemble replaces run-2's long single
    histories; total measured hops per beta = 256k vs run-2's 60k). Correction 2 — 3-D
    seat geometry: three spherical shells r = {1.0, 1.55, 2.3}, counts {8, 13, 21}
    (incommensurate), Fibonacci-sphere placement + seeded angular jitter; adjacency =
    4 nearest within-shell + 2 nearest in each adjacent shell (symmetrised); min degree
    must be >= 6 (reported; < 6 = instrument fault). Heavy central defect: NOT occupiable,
    bond-partner of the inner shell only (z += 1), as ADJ-5.
    ENSEMBLE AGGREGATION (fixed now): pooled occ[s] = sum_draws dwell_s / sum_draws,seats
    dwell; pooled A[s] = mean over draws of the per-draw event-sampled mean |dphi_s|
    (measurement half); pooled dpv[s] = sum_d dwell_s / sum_d visits_s. P2-G2 drift =
    |m_q4 - m_q3| / mean over the POOLED per-hop dwell quarters (<1% unchanged). Coverage
    reported both pooled (union over draws) and mean per-draw. Exponent fits on POOLED
    (occ vs A) and (dpv vs A); p_occ Born-mapped primary (ADJ-5 verbatim). Robustness
    lines (declared, not gates): split-half p_occ (draws 1-32 vs 33-64) at each defined
    beta; geometry seed 2 x 16 draws at the beta nearest the regime median; T_W/2 and
    2*T_W at beta=0.20 as before.
  * Part C: ADJ-6 verbatim (runs ONLY on a stable regime; C^p/(C^p+S^p), p = measured
    median pooled p_occ, signed, not rounded; N = 2,000,000 per setting). Marginal
    flatness <= 0.002 graded per ADJ-7 as data anchor; per FARMER refinement 5 any
    deviation is FIRST investigated as an implementation bug (Synchrony-Theorem check)
    before being reported as physics. No re-tuning of anything between parts (F6).
- **ADJ-9 (bonus probe pre-commit — one scan, declared BEFORE code; runs on Part A's
  locked-cluster data only).** Question: does form-4 gearing force the NP14 candidate
  speed 0.91859c (internal-electron seat) or the 0.918 ratio ((m_p/m_e)/2000 = 0.91808)
  anywhere in locked-cluster kinematics? EXACTLY FOUR observables, fixed now, no derived
  combinations after looking, no inversions:
    R1 = <|Omega_c|> / <omega_i>_members  over locked clusters with >= 2 members
         (rate retention under locking);
    R2 = |Omega_largest| / OMEGA0          (largest cluster's residual rate);
    R3 = <pi * l_bond * |Omega_c|>         over locked bonds, in units of c = 1
         (gear rim speed: circumference-rate of a wheel of diameter l_bond);
    R4 = <omega_i>_locked / <omega_i>_all  (coordination selection of the lock).
  HIT criterion: any R_i within 1% relative of 0.9186 (covers 0.91859 and 0.91808 at
  this window). Report all four values found/not-found regardless. A miss is a miss;
  no fishing, no second scan.
- **ADJ-10 (instrument amendment, logged BEFORE the production run; ADJ-1 class).**
  Smoke test (4 draws, crystal + tiny ensemble; no production statistics viewed) showed
  the ADJ-8 hop budget under-samples the drift estimator on the 3-D geometry: at degree
  ~7.5 the min-gap window is open with p ~ 0.99, so nonzero-dwell events are ~8x rarer
  than on run-2's degree-4 annulus and the pooled quarter-mean drift is sampling noise
  at 8,000 hops (0.25 observed at 4 draws). AMENDED: HOPS 8,000 -> 40,000 per draw
  (run-2 parity; first half discarded), all 64 draws retained. NO gate, criterion,
  observable, beta value, or rule constant changed. The exponent was not looked at
  before this amendment beyond the smoke's "undefined at 4 draws".
- **ADJ-11 (run-4 two-channel TOUR spec — committed 2026-07-05 BEFORE flm14_form4b.py
  exists; ordered by Harvey's §G audit: run-3 P2 ran single-channel, so its exponents
  and probe negative are scoped to the uncorrected instrument).** Everything held from
  ADJ-8/ADJ-10 except the constraint channel enters the tour: same geometry (seed 1,
  shells {8,13,21}), 64 draws x 40,000 hops, phase seeds 10001-10064, beta grid, p_occ
  criteria, drift gate, T_W robustness lines at beta=0.20.
  * **Seat phase state:** theta_k (rotor coordinate; free evolution at omega_k) + wake
    ledger dphi_k (decay exp(-dt/T_W) unchanged). Contact phase c_kj = (theta_k + dphi_k
    + theta_j + dphi_j) mod 1 — same quantity as ADJ-5; the state is now lockable.
  * **On landing at seat s (tick t):** dwell cluster C := {s}, sigma_s = +1. Neighbours
    processed sequentially in fixed adjacency order (machinery order): compute c_sj with
    CURRENT (post-any-same-tick-kick) phases. LOCK if c_sj < W: j joins C, sigma_j = -1
    (g=-1 across the engaged bond); Omega_C = (1/|C|) sum sigma_k*omega_k recomputed at
    each join (Part A's rigid-train rule, reused). KICK (ADJ-5's single kick, now
    constraint-carried): the receiver is j's CLUSTER — every member k gets
    dphi_k += -beta*wrap(c_sj)*sigma_k*sigma_j the SAME tick (rigid displacement;
    uncapped; for an unlocked singleton j this reduces VERBATIM to ADJ-5's kick; inside
    a locked cluster s itself receives the sigma-signed back-action — new, native, no
    new constant). Locks form ONLY on electron-engaged bonds (the electron is the
    contact-maker, ADJ-5); the dwell cluster is therefore a star — 2-colourable, so
    tour-side frustration is absent BY CONSTRUCTION (stated, not hidden).
  * **Departure:** gaps evaluated after all contacts, with final cluster state. Noted
    pre-run as a structural theorem of the rule: the sigma-signed cluster kick leaves
    every INTRA-cluster contact phase invariant (rigidity), so a locked bond holds its
    engaged c < W exactly -> gap 0. Hence dwell > 0 ONLY when no bond locks, in which
    case C = {s} and all rates are natural and positive (no halt path). Unlocked gap =
    (1-c)/(rate_s + omega_j), rate_s = sigma_s*Omega_C if |C|>=2 else omega_s;
    non-finite/negative-rate gaps counted as an instrument event (expected zero).
    Departure through min gap, ties -> first in adjacency order (machinery). During a
    dwell g locked members advance theta at sigma_k*Omega_C (memory trace; measure-zero
    by the theorem above — reported if the run contradicts this). RELEASE on
    separation: all locks dissolve at departure; theta re-based continuously.
  * **CLAIM RULE (hardened per the §G order, declared now):** claimable regime = ALL of
    (i) ADJ-5 stable regime (>=3 consecutive defined pooled p_occ, |p_i - median| <=
    0.3, drift < 1%); (ii) split-half (draws 1-32 vs 33-64) DEFINED in both halves at
    every regime beta, each half within +-0.4 of the pooled value; (iii) geometry-seed-2
    replication, 32 draws (raised from ADJ-8's 16: replication is now decisional and
    needs power — declared before code) at the regime-median beta, defined and within
    +-0.4 of the seed-1 pooled value. Part C (ADJ-6 CHSH, verbatim, p = median pooled
    p_occ over the seed-1 regime, signed, not rounded) is licensed ONLY on the full
    conjunction. Anything less is reported as regime-without-claim.
  * **Probe re-scope (ADJ-9 class; one scan, declared, on TWO-CHANNEL tour kinematics;
    run-3's negative stands for the single-channel instrument):** evaluated at beta =
    0.20 FIXED (mid-grid anchor, chosen before any run-4 result), pooled over the 64
    draws, measurement half only. EXACTLY FOUR observables, no inversions, no post-hoc
    combinations, no second scan:
      Q1 = <|Omega_C|> / <omega>_members   over dwell clusters with |C| >= 2;
      Q2 = <pi * D_sj * |Omega_C|>         over locked engaged bonds, units c = 1
           (star rim speed at seat separation D_sj);
      Q3 = sum(D) / sum(g + D)             per measured hop (effective tour speed / c);
      Q4 = <omega>_locked-members / <omega>_all seats.
    HIT = within 1% relative of 0.9186. A miss is a miss.
