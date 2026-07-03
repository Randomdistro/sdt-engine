# RUN_LOG — CM04 Crystal Lattice and Phonons as Compression Waves

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-03.
> Append-only. Pre-commitments written BEFORE any tool code exists (per `PROMPT_EXECUTION_PROTOCOL.md` §0).

## Pre-Run Commitments — CM04

- Prompt completion target: **C** (prompt's own expected landing: 3R + T³ derived; c_s as MEASURED-INPUT)
- Physics class hoped: **CONVERGENCE**
- CALIBRATED budget: **0** in the mode-counting chain (c_s and lattice spacing are MEASURED-INPUT, not fits)
- Engine namespaces actually used: `sdt::laws::measured` (hbar, h, k_B). FD05 supplies the *narration*
  (compression wave = relay wave; c_s = relay stiffness); crystal c_s values are measured material inputs.
- Phase thresholds (committed before run):
  - **P1** — mode count of a finite periodic lattice = exactly 3N (combinatorial k-point enumeration
    x 3 polarisations, zero tolerance); model high-T limit C_v(T=10 θ_D) within 0.1% of 3R = 24.943 J/mol/K;
    empirical Dulong–Petit band: measured C_p(298 K) / 3R in [0.95, 1.10] for >=4 solids (Cu, Al, Pb, NaCl).
    *Declared before run:* the empirical band is wider than the prompt's 2% because tabulated values are C_p
    (not C_v) and 298 K < θ_D for Cu/Al/NaCl; the C_p−C_v anharmonic gap (~1–7%) is a named, not fitted, effect.
  - **P2** — density-of-modes exponent: fit of ln g(ω) vs ln ω over the low-ω half of the enumerated spectrum
    gives slope = 2.0 ± 0.1. Low-T heat-capacity exponent p = 3.0 ± 0.1 for T in [θ_D/100, θ_D/10].
    **Firewall (committed):** the classical (equipartition) branch is run FIRST and is expected to show
    NO T³ (C_v = 3R at all T). If T³ appears only on the lump branch, P2 grades **C**, per prompt — the
    energy lump ℏω is GRANTED (whitelist ℏ; the relay action quantum h), not derived here. That finding
    is the honest answer to the prompt's own Golden-Rule question 1.
  - **P3** — θ_D = (ℏ v_D/k_B)(6π²n)^{1/3} with v_D the standard 1/v³ Debye average of measured
    polycrystalline v_L, v_T (one rule, all solids, no per-solid multiplier): within 10% for
    Cu (343 K), Al (428 K), diamond (2230 K), NaCl (321 K). Known risk, declared now: room-T elastic
    constants vs low-T calorimetric θ_D and polycrystal anisotropy averaging inject O(5–10%); NaCl is
    expected to be the closest to the gate edge. No input will be changed after the first run.
  - **P4** — full Debye crossover for Cu (θ_D = 343 K, no refit) vs measured C_p at
    50, 100, 200, 300 K within **20%** at every point. T = 20 K excluded, declared now: below ~25 K the
    measured value contains the conduction-carrier term γT and θ_D(T) droop; both are outside this
    prompt's lattice-only scope.
- Forbidden retroactive changes: import a phonon field operator / oscillator partition then claim A;
  per-solid refit of the θ_D cutoff or of v_D; widening any band above; plugging θ_D; IDENTITY-PASS;
  local constant namespaces.

## MEASURED-INPUT ledger (fixed before run; sources: standard elastic/calorimetric tables)

| Solid | ρ [kg/m³] | atomic mass [g/mol] | v_L [m/s] | v_T [m/s] | θ_D obs [K] | C_p(298) [J/mol_atom/K] |
|---|---|---|---|---|---|---|
| Cu | 8960 | 63.546 | 4760 | 2325 | 343 | 24.44 |
| Al | 2700 | 26.982 | 6420 | 3040 | 428 | 24.20 |
| Pb | 11340 | 207.2 | 1960 | 690 | 105 | 26.65 |
| NaCl | 2165 | 29.22 (mean/atom) | 4780 | 2440 | 321 | 25.25 |
| C (diamond) | 3515 | 12.011 | 17500 | 12800 | 2230 | 6.11 (not in DP set) |

Cu C_p anchors for P4 [J/mol/K]: 50 K: 6.25 · 100 K: 16.01 · 200 K: 22.63 · 300 K: 24.47.

## Phase gate record (to be filled ONLY from real tool stdout after execution)

- P1: [pending run]
- P2: [pending run]
- P3: [pending run]
- P4: [pending run]

### ADJ register

- **ADJ-000 (self-caught, pre-run):** first draft of this file pre-filled the gate record with
  hand estimates as if they were results. Deleted before any code was written; the record above is
  now blank until the tool runs. Logged as evidence of the firewall working, per HUNTER §F.
- **ADJ-001 (Harvey intervention, pre-run, 2026-07-03):** first draft of the tool framed the
  discrete energy exchange as "lump ℏω GRANTED (QM oscillator concession)". **Rejected by Harvey:
  no QM machinery in the chain — machinery only.** Re-boned BEFORE first run onto native machinery:
  the lattice is discrete (spation granularity); Law VI winding quantisation — *earned* by FD02
  (κ = h/m, 0.02%, no free integer) — forces action exchange in units of h, one reconnection event
  per wave cycle (FLM09 bond-switch) ⇒ energy per event = h/T_cycle = ℏω, DERIVED from named native
  premises, then classical Boltzmann counting over discrete relay events. **No threshold, gate, or
  input changed** — narration bones only. The firewall branch is reframed mechanically:
  continuous-exchange lattice (granularity OFF) vs discrete-relay lattice (granularity ON).
  Load-bearing named premise: "action per reconnection event = h (Law VI extension to compression
  waves)" — killable independently.
