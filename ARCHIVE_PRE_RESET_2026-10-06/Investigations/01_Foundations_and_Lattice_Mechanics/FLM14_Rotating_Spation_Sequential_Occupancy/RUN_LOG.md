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
- **ADJ-12 (run-5 claim-decision spec — committed 2026-07-05 BEFORE flm14_form5.py
  exists; ordered by Harvey).** Machinery = flm14_form4b verbatim (two-channel tour);
  T_W = 27 remains the committed instrument constant everywhere except the declared
  scan of (2). Nothing re-tuned.
  1. **Seed-2 replication, UNCONDITIONAL:** geometry seed 2, beta = {0.10, 0.20}, full
     64 draws x 40,000 hops each, phase seeds 20001-20064. Replication PASS per beta :=
     pooled p_occ defined (committed fit criteria, incl. |r| >= 0.6) AND
     |p_seed2 - p_seed1(run-4)| <= 0.3 (the committed band) AND split-half (32/32)
     both defined and within +-0.4 of the seed-2 pooled value.
  2. **T_W diagnosis (WAKE-MEMORY debt):** scan T_W in {13.5, 27, 54, 108} at
     beta = 0.20, geometry seed 1, 64 draws each. MACHINERY ANCHOR: the 13.5/27/54
     points must reproduce run-4's +2.596/+2.040/+1.620 exactly (same seeds,
     deterministic; tolerance 1e-6 on the fitted slope) — mismatch = instrument fault,
     halt. Convergence rule, declared NOW with Delta1 = p(54)-p(27), Delta2 =
     p(108)-p(54): PLATEAU if |Delta2| <= 0.15 -> the instrument's p := p(108).
     CONVERGING if 0.15 < |Delta2| <= 0.5*|Delta1| -> report geometric extrapolation
     p_inf = p(108) + Delta2*r/(1-r), r = Delta2/Delta1, labelled DIAGNOSTIC (not a
     claim); WAKE-MEMORY stays open. NO PLATEAU if |Delta2| > 0.5*|Delta1| -> monotone
     slide; p is NOT a law on this instrument — reported as such. NO native-T_W
     derivation is attempted this run (none is declared; deriving one from the plateau
     after seeing it would be fishing).
  3. **beta=0.40 upturn check (report, don't gate):** ONE declared test of the
     amplitude-mask-erosion hypothesis: fit log(occ at beta=0.40) vs log(A at
     beta=0.40) over the FIXED usable-seat set of beta=0.20 (T_W=27, seed 1).
     Hypothesis SUPPORTED if the fixed-mask slope lies within 0.3 of beta=0.20's
     pooled p (the upturn is seat-selection, not dynamics); CONTRADICTED if it stays
     >= 2.5 (the dynamics genuinely steepen). Reported either way; no gate moves.
  4. **CLAIM CONJUNCTION (unchanged from ADJ-11):** (i) stable regime on the committed
     instrument (T_W=27, seed-1 beta grid = run-4 table; deterministic identity, cited
     not re-run); (ii) split-half at every regime beta; (iii) seed-2 replication. If
     met: p claimed at its measured value (median pooled p_occ over the regime) and
     Part C runs per ADJ-6 verbatim. If not met: refusal stands; the blocking leg(s)
     are NAMED. **Pre-declared honesty note:** run-4's table already shows leg (i)
     FAILED (beta=0.05 drift-FAIL and beta=0.40 band-break pincer the grid), so the
     expected outcome is refusal-with-named-blockers; legs (ii)/(iii) and the T_W
     diagnosis are still executed UNCONDITIONALLY because their evidence stands on its
     own (Harvey's order) — declaring this now prevents any later reading of the
     unconditional legs as a fish for a pass.
- **Run-6 CLOSED (computed 2026-07-07 00:35, verdict recorded same day — executor wake-up
  lost, verdict written by the session from the teed results).** `flm14_form6.py` exit 0;
  anchors 0.00e+00 (measure switch licensed, dynamics bit-identical). **CLAIM REFUSED**
  (leg i: 0.05 drift-FAIL; {0.10,0.20,0.40} band broken by +4.191). WAKE-MEMORY **PAID by
  construction** — memory-free centre exponent +2.585 = the T_W→0 limit of run-5's family;
  the 2.040 was window-dependent. NEW DEBTS: **BETA-DEPENDENCE** (p_MF monotone in β, both
  seeds — β is now the single blocking unknown; owner FLM03 coefficient) · **DWELL-LEG NULL**
  (p_dwell undefined at all 8 arms — occupancy carries the signal, dwell-duration does not).
  Mask-erosion re-opens geometry-split under MF. Part C NOT RUN. Export delivered
  (`flm14_run6_dwell_table.txt`, leads-grade, CH07 stake). Successor requires new ADJ:
  native β from FLM03, or 3-D CRN seats at scale.
- **Run-5 CLOSED (executed 2026-07-05, verdict recorded 2026-07-06).** `flm14_form5.py`
  exit 0; anchors exact; CLAIM REFUSED (legs i/ii/iii blockers named in VERDICT); Part C
  NOT RUN. Standing-alone evidence: MASK-EROSION SUPPORTED (+2.270 fixed-mask vs +2.040
  centre), seed-2 centre replication PASS at β=0.20 (drift-caveat logged), T_W=108
  undefined ⇒ WAKE-MEMORY hardened to dissolution. New debt: DRIFT-GEOMETRY. Named
  successor: run 6 = memory-free dwell-count measure (requires a new pre-committed ADJ
  before any code exists).
- **ADJ-13 (run-6 memory-free-measure spec — committed 2026-07-07 BEFORE flm14_form6.py
  exists; the successor named by run 5's verdict).** Machinery = flm14_form4b two-channel
  tour VERBATIM — the DYNAMICS (tour rule, star locks, σ-signed same-tick cluster kicks,
  gap rule, release-on-departure, T_W = 27 wake decay in the dynamics, W, OMEGA0, hop
  counts, phase-seed conventions) are UNCHANGED. ONE change only: the MEASUREMENT.
  * **THE ONE CHANGE (A_mf — exact formula, declared before any code).** form4b's A is a
    T_W-INTEGRATED wake ledger: A[k] = mean over measured hops of
    |dφ_k(t)·exp(−(t−tlast_k)/T_W)|, and dφ itself integrates kick history with memory
    T_W — run 5 showed p inherits that window (+2.596 → +2.040 → +1.620 → undefined).
    Memory-free replacement, read from the instrument's own kick structure:
      **A_mf[k] = (1/N_meas) · Σ_{measured hops h} |Δdφ_k(h)|**,
    where Δdφ_k(h) = the NET wake deposited at seat k by hop h's contacts under the
    UNCHANGED rule — for a singleton receiver j: −β·wrap(c_sj); for a member k of the
    engaged cluster: Σ_j [−β·wrap(c_sj)]·σ_k·σ_j over that hop's contacts. Single-tick,
    CURRENT configuration only: no decay factor, no history integration, **no T_W, no
    instrument constant in the measure**. β enters only as a common positive scale at
    fixed β, so the fitted log-log slope is invariant to it (declared). ONE formula; no
    alternate measure will be tried after looking (no second scan). Occupancy (y-axis)
    stays the dwell fraction occ[s] = Σ_draws dwell_s / Σ_draws,seats dwell (ADJ-8
    pooled aggregation, unchanged); p_dwell (dpv vs A_mf) reported secondary as before;
    committed fit criteria unchanged (≥12 seats above 0.05·A_max, spread ≥×3, |r| ≥ 0.6).
  * **T_W-independence is now STRUCTURAL:** no T_W exists in A_mf, so run-5's
    measurement-window dependence cannot exist by construction — the WAKE-MEMORY debt is
    paid BY CONSTRUCTION if and only if the exponent is defined and stable. Honest
    scope: T_W = 27 remains the committed constant of the DYNAMICS (untouched this run);
    what is eliminated is the measure's window. A native derivation of the dynamical
    T_W (FLM03 co-rotation / FLM09 reconnection) stays a separate, already-named open.
  * **MACHINERY ANCHOR (halt on fail).** Dynamics unchanged + same seeds ⇒ the tours
    must be IDENTICAL to run-4/5's. Operationalised two ways, both required, in the same
    tool run BEFORE the measure switch is trusted: (a) the IMPORTED flm14_form4b
    ensemble (verbatim module import) at β=0.20, geometry seed 1, T_W=27, phase seeds
    10001–10064 must reproduce run-4's p_occ = +2.040 to |Δp| ≤ 5e-4 (print rounding —
    ADJ-12's operationalisation of a 3-dp record); (b) the NEW tool's tour (form4b code
    verbatim + passive Δdφ bookkeeping only) must reproduce the imported machinery's
    OLD-measure slope to **|Δp| ≤ 1e-6** (bit-identical tours), with max|Δocc| reported
    (expected 0 exactly). Any mismatch = INSTRUMENT FAULT: halt (exit 1), nothing
    bankable. Only after both anchors pass is the measure switched.
  * **GRID (production, committed):** β ∈ {0.05, 0.10, 0.20, 0.40} × geometry seeds
    {1, 2} — seed-2 UNCONDITIONAL — 64 phase draws × 40,000 hops per arm; phase seeds
    10001–10064 (seed 1) and 20001–20064 (seed 2), ADJ-12 conventions; T_W = 27
    everywhere. No truncation to save time. Drift < 1% per ADJ-8 (pooled per-hop dwell
    quarters), reported PER SEED; **DRIFT-GEOMETRY debt carried visibly** (run-5: seed-2
    fails drift where seed-1 passes — reported, never hidden; leg (iii)'s committed
    definition, per ADJ-12, does not include drift).
  * **Fixed-mask discipline (run-5 mask-erosion lesson):** β=0.40 scored on its own mask
    AND on the FIXED β=0.20 usable-seat mask (fit_exponent's mask on β=0.20's A_mf/occ),
    per seed — the band check must see both. Report-only; no gate moves.
  * **CLAIM CONJUNCTION — ADJ-11 verbatim, unchanged, evaluated on THIS run's
    memory-free table (seed 1 = the committed instrument):** (i) stable regime = ≥3
    consecutive grid betas with defined pooled p_occ AND drift < 1%, all within
    |p_i − median| ≤ 0.3 of the window median; (ii) split-half (draws 1–32 vs 33–64)
    DEFINED in both halves at every regime beta, each within ±0.4 of the pooled value;
    (iii) geometry-seed-2 replication at the regime-median beta: pooled p defined,
    |p_seed2 − p_seed1| ≤ 0.3, and seed-2 split-half both defined within ±0.4 of the
    seed-2 pooled value (ADJ-12's committed operationalisation; 64 draws here, stronger
    than ADJ-11's 32). If met: p is CLAIMED at its measured value (median pooled p_occ
    over the seed-1 regime, signed, not rounded) AND **Part C runs per ADJ-6 VERBATIM in
    the same session** (P(B=A|a,b) = C^p/(C^p+S^p), N = 2,000,000, marginal flatness
    ≤ 0.002 graded per ADJ-7 as a data anchor; per FARMER refinement 5 ANY marginal
    deviation is FIRST investigated as an implementation fault — Synchrony-Theorem
    check). If not met: REFUSAL with the blocking leg(s) NAMED. If p_mf is undefined or
    unstable, rule-form-4's Born story dies honestly (run-5's pre-commitment stands).
  * **EXPORT (cross-program stake, delivered REGARDLESS of claim outcome):** CH07-R2
    opened root **WELL-DEPTH-AT-CONTACT** — the chemistry well at contact is ×17.2 too
    deep because all p–e engagements count at FULL, simultaneous weight; the
    dwell-WEIGHTED well is THIS run's export. Deliverable: per-seat dwell-fraction table
    at the centre β = 0.20 (fixed now, before any run-6 result), BOTH geometry seeds,
    written to `flm14_run6_dwell_table.txt` (seat, shell, radius, coords, degree, z,
    ω, dwell fraction, visit fraction, dwell-per-visit, A_mf) — the input CH07's
    dwell-weighted well rerun needs.
  * **Smoke allowance (ADJ-10 class, declared):** one mechanical smoke (≤4 draws,
    ≤4,000 hops) to verify plumbing and the anchor-identity path ONLY; no production
    statistics viewed; no smoke-scale exponent recorded as evidence.

---

# ADJ-14 (2026-07-07, committed BEFORE any tool exists): Part C re-drafted against the corrected bridge

**Trigger:** QM05 RUN 2 (ALL GATES PASS) retired ADJ-6's transcription — the Bell readout is
LINEAR in one conserved director-space kick (cos²Δ ≡ (1+cos2Δ)/2); NO residence exponent
enters Bell. ADJ-6 stays in the record, marked SUPERSEDED-for-Part-C by this entry. The old
license (a stable p_occ regime) was a condition on a quantity Bell never consumes — void.
Part C's job re-poses: show the FLM14 instrument REALIZES the conserved-kick channel, rather
than show it produces p = 2.

## Part C′ — the emergent-channel test (tool: flm14_form7_partC.py)

**The pair construction (native, from existing machinery):** two wings = two seat annuli
(run-4 3-D shell geometry, one per wing), joined by ONE gear-locked rigid cluster (the ADJ-11
locks-in-tour machinery). The cluster's shared director phase per trial = the kick k̂;
conservation = the rigidity theorem (locked-dwell must be 0.00e+00, as at every production
run). Analyzer setting per wing = a declared local reference orientation for that wing's
readout; the electron tours BOTH wings (one tour, two wings — refinement 5).

**Stage 1 — LICENSE (all three or Part C′ does not run):**
- L1 conservation: the locked cluster's shared phase is constant within-trial to machine
  precision (rigidity extended to the pair; report max drift).
- L2 memory-free native readout: wing outcome = SIGN of a declared local counting statistic
  (occupancy-difference between the wing's two seat sectors relative to its analyzer
  orientation — a counting measure; NO cosine, NO cos², NO import anywhere in the readout).
  Declared here, before code; one rule, both wings, all settings (F6).
- L3 marginals: |P(±) − 0.5| ≤ 0.002 at every setting of BOTH wings, at every β scanned
  (Synchrony Theorem check — a marginal shift = implementation fault, halt and hunt).

**Stage 2 — the run (only if licensed):**
- C1 (shape): measure E(Δ) on the declared grid Δ ∈ {0°,15°,…,90°} (relative analyzer
  angle). Fit E = k·cos(2Δ−ψ): report k, ψ, RMS residual (fit-quality threshold 0.05,
  declared). The SHAPE is the result: cos-form emerging from tour dynamics = the projection
  geometry earned; any other shape is reported and the channel model takes the hit.
  **k < 1 (sub-quantum) is expected at first attempt and fully publishable.**
- C2 (ceiling): CHSH from measured E at the standard angles: S ≤ 2.8334 (2√2 + 5σ). S above
  it = instrument-fault hunt (conservation should forbid), NOT a discovery claim.
- C3 (the physical control — the lock IS the non-locality): sever the constraint channel
  (unlock the cluster, same seeds, same readout): the wings become independent local
  machines ⇒ committed gate S_unlocked ≤ 2.004. Locked S > unlocked S at ≥ 5σ = the
  channel's transmission DEMONSTRATED. (The abstract S→4 overdraw is not physically
  reachable in this instrument and is NOT a target.)
- β: scanned {0.10, 0.20, 0.40}, exploratory as always; S(β) and k(β) reported wherever they
  land; no β fitted to maximise S (F6 — fishing check: the report must show the full scan).

**Pre-declared honest expectations:** first-attempt likely outcomes are (a) LICENSE-FAIL at
L2/L3 (readout too crude), or (b) licensed but k ≪ 1 (weak emergent correlation) — both are
honest landings that bound the channel's realizability. The kill: locked S ≤ unlocked S
(the constraint channel transmits nothing) ⇒ rule-form-4's non-locality claim dies.
**What would pay what:** C1 cos-form ⇒ projection geometry earned from dynamics; C2+C3 ⇒
QM05-R2's NATIVE-conditional loses its biggest conditional; total = the two-channel
architecture's first end-to-end Bell exhibit, sub-quantum or not.

Machinery anchors: reused tour core must reproduce run-6 anchor (+2.040 old-measure,
1e-6) before the pair build; locked-dwell 0.00e+00 at every arm. Results = teed stdout,
exit 0, PYTHONIOENCODING=utf-8. Seeds declared in-tool. Nothing above may be widened.

## ADJ-14 build note (2026-07-07, logged BEFORE flm14_form7_partC.py exists)

Instrument REALIZATION choices only; every ADJ-14 gate stands as committed, none touched.

* **Two-wing construction (ADJ-8 geometry; ADJ-13's committed instrument):** wing L =
  `build_seats3d(1)` verbatim (42 seats, own heavy central defect); wing R = the SAME
  seed-1 geometry mirrored in z (identical apparatus — the Bell-pair configuration; the
  mirror preserves every x–y azimuth, so the readout frames correspond seat-for-seat)
  and translated so the ports face pole-to-pole. No cross-wing adjacency except the bridge.
* **Bridge cluster (ADJ-11 lock machinery):** ONE permanent rigid pair {b_L, b_R}; b =
  the outer-shell seat of maximum z (deterministic from geometry); bridge bond length =
  the wing's median bond length (native yardstick); the bridge bond is a real bond
  (port z += 1, ADJ-8 coordination rule verbatim). sigma_bL = +1, sigma_bR = −1 (g = −1
  across the bridge); Omega_P = mean(sigma·omega) = 0 exactly for identical wings — the
  run-3 frozen backbone at n = 2. Ports evolve and close windows at their RIGID rate
  (sigma·Omega_P; ADJ-11's cluster-rate rule applied to the receiver side). A
  frozen–frozen contact with c ≥ W is a STATIC window (counted, reported; the form4b
  r ≤ 0 guard is reserved for the no-departure path).
* **Per-trial shared director phase (the kick; ADJ-14/QM05-R2):** k̂ = the bridge bond's
  contact phase c_bridge = (theta_bL + dphi_bL + theta_bR + dphi_bR) mod 1, set by the
  trial's base draw; conserved by the ADJ-11 rigidity theorem (sigma-signed kicks land
  on the pair as exact ±, decay acts on exact-negative dphi at common ticks, the rigid
  rate sums to zero). L1 = its worst within-trial drift, sampled every hop.
* **Tour (ADJ-11 verbatim, one rule):** one electron tours BOTH wings (refinement 5),
  start = wing-L seat 0 (ADJ-8); dwell stars, sigma-signed same-tick cluster kicks, gap
  rule, release-on-departure, T_W = 27 in the dynamics — flm14_form4b lines unchanged.
  The ONE extension (forced by the pair, no new constant): a kick or lock addressed to
  a port engages the port's PERMANENT cluster (receiver = j's cluster, ADJ-11's own
  wording), so constraint transmission crosses the bridge the SAME tick. Locked-dwell
  (dwell during any transient lock) must print 0.00e+00 at every arm (the theorem).
* **Analyzer (ADJ-14):** a declared rotation a of the wing's seat-sector partition in
  the wing's x–y director plane: sector+(a) = seats with (az_i − a) mod π < π/2,
  az_i = atan2(y_i, x_i) — the two-fold (director) partition; one rule, both wings, all
  settings. Settings enter the READOUT ONLY (the analyzer never touches the dynamics).
* **L2 counting statistic (declared):** wing outcome = sign( Σ_{sector+} dwell_i −
  Σ_{sector−} dwell_i ) over the trial's measured half — occupancy is the program's
  Born-mapped dwell ledger (ADJ-5/ADJ-8); no cosine, no trig, no T_W anywhere in the
  readout. Detection = both wings record nonzero dwell (settings-INDEPENDENT, so no
  setting-dependent post-selection); exact sector ties excluded-and-counted (measure 0).
* **Trial structure (declared before any run):** per arm N = 2560 trials × 10,000 hops
  (first half burn-in, ADJ-8 convention) = 25.6M hops/arm (10× a run-6 arm — per-trial
  sign readout requires trial multiplicity; 10k hops keeps several expected bridge
  crossings per measured half). Phase seeds: seed = 700000 + 100·round(1000·beta) +
  trial index; the SAME seeds drive locked and unlocked arms (C3's committed pairing).
* **Settings (declared):** C1 grid measured at (a, b) = (Δ, 0°), Δ ∈ {0,15,…,90}°; C2
  at the standard CHSH angles a ∈ {0°,45°}, b ∈ {22.5°,67.5°}, S = E00 − E01 + E10 +
  E11; L3 marginals evaluated at every setting used, per beta, on the locked arms.
* **Unlocked control (C3):** the ONE severed thing is the lock — no permanent cluster,
  no cross-bridge kick transmission, ports at natural omega; graph, seeds, tour rule,
  and readout identical (ADJ-7: constraint channel severed, pulse channel untouched).
* **Noted pre-run (structural, so it cannot become a post-hoc excuse):** with analyzers
  entering readout only, E(a,b) factorises over the shared trial ensemble, so the
  locked instrument is bounded by S ≤ 2 mathematically. Part C′ therefore probes k (the
  cos-form and its amplitude = orientation actually transmitted through the bridge) and
  the locked-vs-unlocked gap; C2's ceiling can only fail via implementation fault. A
  sub-2 S at nonzero k is exactly ADJ-14's pre-declared honest landing.
* **FARMER-ref-5 diagnostic protocol (hunt tools, not gates):** if L3 fails, the fault
  hunt = (anchors, L1, guards) integrity + per-setting dev vs the sampling sigma + the
  static-pattern mechanism check (sign of the pooled-dwell sector difference vs sign of
  the marginal dev); if the worst dev ≤ 0.05 (plausibly sampling-floor), ONE 4×-trials
  scaling diagnostic at beta = 0.20 locked (form4b's scaling test, verbatim protocol).
  A frame-averaging symmetrisation (pooling a with a+90°) was considered and REFUSED —
  it forces marginals to zero by construction and would launder the Synchrony check.
* **Smoke allowance (ADJ-10 class):** one mechanical smoke (≤ 2 trials × 2000 hops) for
  plumbing and guard printing only; no production statistics viewed.

**ADJ-14 build amendment (ADJ-10 class — logged BEFORE production, from the mechanical
smoke only; no gate, criterion, or constant changed).** The smoke printed crossings = 0
(both trials, locked and unlocked): the first build did NOT realize ADJ-14's committed
construction "the electron tours BOTH wings". Two realization faults, both named and fixed:

1. **Locked bond ⇒ gap 0 (rule-consistency fix, not a tune).** The first build evaluated
   the permanent bridge bond's departure gap by its raw window c (giving a static ∞ gap at
   the frozen ports whenever the conserved c_bridge ≥ W — half the trial population could
   NEVER cross, selected by the conserved phase itself). ADJ-11's own rule is that a
   LOCKED bond holds gap 0; the pair is locked BY CONSTRUCTION ("gears engage at the
   relation as found"). Treating the constructed lock as unlocked in the departure rule
   was the implementation inconsistency. Fixed: a bond from s to any member of s's
   current rigid cluster (permanent pair or transient star) has gap 0. In single-wing
   anchor mode this is a no-op (transient locks already hold c < W exactly — the run-4/6
   theorem), so the machinery anchors still bind bit-identically.
2. **Bridge position in the port's adjacency list = SECOND, both ports (machinery).**
   The committed tie rule (first zero gap in fixed adjacency order, ADJ-11) starves a
   last-listed choke bond (P ≈ 0.5^deg per visit — the smoke's zero crossings), and
   position-first is excluded by a ping-pong theorem (both ports' bridge-first ⇒ the
   locked zero-gap bond wins every tie in both directions ⇒ a permanent two-seat bounce).
   The minimal non-degenerate symmetric position is second; crossing then occurs iff the
   port's first-listed bond does not lock (P ≈ 0.5 per port visit), identically from both
   sides. Declared as machinery, same class as the adjacency ordering itself.

Consequences (stated before production): ports become zero-dwell relay seats in the
locked arms (their bridge gap is always 0), so they contribute visits but no occupancy to
the readout; the r ≤ 0 counter in pair mode now counts only receding windows (the run-4
guard, harmless). Unlocked control is untouched by fix 1 (no permanent cluster — the
bridge is an ordinary bond there) and shares fix 2's geometry verbatim.

3. **Port placement (second mechanical probe, still pre-production, no measured
   observable viewed).** Even after fixes 1–2, crossings stayed 0: a 10k-hop mechanical
   probe of the plain form4b single-wing tour shows the KNOWN self-trapping structure
   (runs 2–4) concentrates ~85% of visits on two inner-shell seats and gives the outer
   shell 0.07% of visits — the outer-pole port is unreachable, so the outer-pole port
   CHOICE was an instrument fault of the same class as ADJ-2's uniform ring. Port
   re-declared: b = the INNER-shell seat of maximum z (the wing's core pole, bonded to
   the heavy defect) — the Bell-natural attachment: the shared source cluster joins the
   two wings' CORES, where the tour actually resides. Wing R remains the z-mirrored
   copy with port-to-port distance = d_b (median bond); the embedding overlap this
   produces is inert — only BONDED distances ever enter the dynamics (declared). No
   gate, criterion, observable, or constant changed by any of 1–3.
