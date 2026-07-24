# Direct re-run — category 06 (Gravitation & Orbital Mechanics), 2026-07-24

> **Executor: Fable, direct, no agents.** Sequence: 39 agent-era outcome files purged → all 14
> prompts read in full and upgraded (commit 73b4157) → P0 source audits → 17 C++ + 10 Python
> tools compiled/executed → this record. Every number below is from today's teed output
> (`*_rerun_2026-07-24.txt` beside each tool). GOM15–18 (Harvey-direct arcs) were re-verified,
> not re-verdicted. One build repair (GOM12 missing `<cstring>`, ADJ-noted in-file).
> Tools predate the upgraded specs; where a tool's print-layer violates its new spec, the
> override is stated here and the patch is listed as owed. **This file is the verdict record
> for the P0/P1-wave; per-folder `*_VERDICT_DIRECT` files follow when each spec's full phase
> set (the new P2/P3-class work) runs.**

## P0 audit results

- G/M sweep: GOM06's IAU GM-as-measured-length = its R2 rule (legal); GOM01/GOM05
  `GM_equivalent(k,R)` = kinematic, rival-column (legal); GOM02's G usage = its thesis (legal).
- **GOM09 trefoil tool: register suspicion CONFIRMED in specific form** — its G-candidate
  formulas are native, but Earth-side conversions consume M_Earth in kg (G-decomposed);
  outputs labeled G-sweep-contaminated exploratory.
- **GOM04: clean** — `c_known` appears only as the comparison column; the derived chain runs
  precession → k → c with no c upstream (adjudicated from the run output).
- **GOM11: the E99 taint is still in the tool** — hardcoded Q = 2.31 (ran before the strip;
  handled by labeling below; strip owed).

## Run matrix and verdicts (27 executions, 0 crashes)

| inv | today's numbers | verdict of the wave |
|---|---|---|
| **GOM01** | 27/27 incl. Pound–Rebka 0.4%, Shapiro 123.66 µs, bending 1.7517″ | P1 CONVERGENCE gates re-earned. **Overrides:** the tool's "Cosmological z PASS" line is void per spec (quarantined, CONTESTED pending CR06); the two prefactor 2s remain OWED. P2/P3 (prefactor mechanism; divergence residue) not yet run |
| **GOM02** | 15/15; GM_Sun recovery 0.0000% | Re-earned, but the print-layer still sells identities as predictions, still says "charge radius", still lists the STRUCK v_rot claim — label patch owed per P1. The P2 invariance case is now fed by GOM12+GOM14 (below) |
| **GOM03** | pipeline round-trip passes | **[SELF-TEST — no physics weight]** per spec; P2 sensitivity budget and P3 real-data phase not yet run |
| **GOM04** | **c recovered = 299,795,136 m/s (+0.0009%)**; uniqueness shown (±1 in k_Sun breaks the precession match); cross-body closure Sun/Earth/Saturn | CLOSURE PASS inside the committed window. Labeled `[CLOSURE — consistency inversion]`; symbol note: tool prints "ϟ" for k |
| **GOM05** | 4/4 identities; z_surf 2.123×10⁻⁶; Shapiro re-read | IDENTITY/CONVERGENCE legs re-earned; lumiopause/galactic-floor lines carry campaign statuses (E106 INCONCLUSIVE / E108 DOWNGRADED); lumiostasis falsifier armed on F3 |
| **GOM06** | chirp: 67.65 vs 68 Hz (−0.52%) with the tool's own identity-honest ledger; echoes: **Δt = 57.6 ms** (wall-placement POSIT, log-sensitive, observationally contested — stated in-run); memory: Δϟ_rad = 4.43 km, 7–35% of peak, **G3≡G4 one-quantity identity printed** | G1/G2/G4/G5 re-earned at Class C with OWED ledger (96/5, κ, η). G3 conservation-chain derivation note = owed fresh (June doc deleted, not restored) |
| **GOM07** | slope **−1.11 ± 1.28** re-earned to the digit; floor 1.46 m/s ≫ signal; Io albedo-artifact handled; Europa−Ganymede +2.25±1.04 (10× the predicted 0.23 → systematic) | P1 done at honest naive-climb-only scope. **P3 (stamp-vs-observer decision matrix, feeds D06) = the owed centrepiece** |
| **GOM08** | 42.9930″ vs 42.98; SDT≡Standard to 0.03% (identity); embeds the GOM04 closure | P1 `[IDENTITY]` re-earned; its own §Step-6 lists the divergence candidates. P2 (native 1/r³ routes), P3 (structure-dependence fork), P4 (Venus/Earth) not yet run |
| **GOM09** | **RE-ADJUDICATION: the agent-era FAIL does NOT reproduce.** Today: v_p RMS **6.24%** (80 pts), v_s RMS **6.69%** (51 pts) vs recorded 11.5%/28.0%. Gates: centre/CMB/ICB pressures ✓, v_s=0 outer core ✓, centre v_p +6.7% ✓; v_p<5% ✗ (6.24), surface ✗ (+13%) | **Register ruling proposed: KILL-OVERTURNED → OPEN** — the recorded FAIL magnitudes were wrong (source of the discrepancy unknown; tool unmodified — the agent record simply does not match its own tool's output), BUT the claim-as-originally-posed (stiffness with NO material moduli) remains unmet: the tool's own ledger lists lab K₀/G₀ per phase as measured inputs; native content = K′₀=4 from traction, G-saturation, g/P profiles (g-leg 1.82%-class intact). NP30-§10 shear route (P3) not yet run. Harvey ratifies |
| **GOM10** | L1–L5 re-earned; Routh 0.0385 ✓ (3 systems); barycentres inside primaries ✓; 3-body field map | Identity leg done `[IDENTITY]`. P2 (the L2-in-the-umbra cone hunt — the divergence candidate) and P3 (tractability derive-or-strike) not yet run |
| **GOM11** | h_eq 0.2717 m; **M2/S2 = 2.177 vs 2.170 (0.3%) — the zero-knob gate PASSES**; but Step-2 "M2 0.4% PASS" rode the in-tool Q=2.31 | Clean gate banked; **Step-2 output OVERRIDDEN to CALIBRATED (Q-rule)**; tool strip owed |
| **GOM12** | exit 1 = honest gated FAILs. **Banked: koppa_Jupiter invariant across 4 Galilean moons at σ/μ = 0.010%**; planetary occlusion budget 4.19×10⁻⁹ of the solar sky; Jupiter's depth 4460× below the 1e-8 residual (stated plainly); lumiopause vs Oort left OPEN (criterion under-specified vs a 10×-wide literature band); **E21 integer conjecture: 0/7 — NOT supported, stated plainly** | Old-gate rerun honest. The upgraded spec's P2 (L☉ budget-closure question + tautology check) not yet implemented in-tool — owed |
| **GOM13** | sin-dip exclusion re-earned (**47×**, committed criterion 10×); G2 mass-column ramp ~9×10⁻⁷ = orders below sensitivity; **H1 fork run BOTH branches: either way the balloon has no live signal path**; E104 "NOT WORTH FLYING"; G-record scan shows JILA (high lab) reads LOW | **Disposition: PARKED** — per the upgraded P4, with triggers (balance-floor factor ~10³; H1 resolution via ambient-P_eff derivation; saturation curve = only near-term piece). Register GOM13 entry completable |
| **GOM14** | **693 hosts, median 5.91% (anchor 5.9% ✓), shuffled 50.74%, within-10%: 54.6 vs 18.2; Sun anchor 1476.6 m = CODATA exact; density 1409.8 vs 1408** | Fully re-earned at its fixed class (CONVERGENCE-demonstration). Host-spreads export for GOM02 owed (P2 file) |
| GOM15–18 | drive-chain octave scans print honest negatives (no ≤2% hits); Vulcan iron-refractory prediction stands; exchange-ledger additivity row-local; Sgr A* seat ON the M-σ point (rival column labeled) | Standing Harvey-direct verdicts CONFIRMED by re-execution |

## The wave's headline findings

1. **GOM09's recorded failure was false.** The direct rerun contradicts the agent-era record by
   ~2× on v_p and ~4× on v_s. This is the strongest single vindication yet of the voiding
   ruling: an UNCONFIRMED-FAIL that, on direct execution, was simply not what the tool produces.
2. **The Galilean invariance number (σ/μ = 1.0×10⁻⁴)** puts real measurement behind GOM02's
   advantage thesis for the first time — with GOM14's 693-host demonstration beside it.
3. **E21's integer-ratio conjecture is dead on its own gate** (0/7) — killed by the tool built
   to find it, stated plainly.
4. **GOM13 is honestly parked** — the branch where a Harvey correction, a rescope, and now a
   computed reachability audit close a flagship over-claim without residue.
5. The category's honest class-map after relabeling: the weak-field sector is IDENTITY/
   CONVERGENCE throughout (as the degeneracy rule predicts); the surviving divergence
   candidates are exactly three — **GOM06's echo train + breathing≡memory identity, GOM10's
   L2-in-the-umbra shift, GOM08's structure-dependence fork** — and none has yet been computed
   to a decision.

## Owed next (the upgraded specs' un-run phases, in value order)

GOM07-P3 stamp-vs-observer matrix (canon fork, feeds D06) · GOM09-P3 NP30-shear route +
register ratification · GOM10-P2 umbra hunt · GOM08-P2 native-coefficient routes · GOM12-P2
budget-closure question · GOM01-P2 prefactor mechanism · tool label/strip patches (GOM01
cosmology line, GOM02 print-layer, GOM11 Q) · GOM02-P2 formal gate on GOM12/GOM14 exports.
