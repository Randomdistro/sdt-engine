# RUN_LOG — NP18 Be7BEC Flux Resonator

> **Author of run:** executor (agent), on behalf of J. C. Harvey investigation spec.
> **Run date:** 2026-07-01. **Engine:** `sdt/laws.hpp`, `sdt/nuclear.hpp`, `sdt/neutrino.hpp`.
> **Tool:** `np18_rate_fork.py` (python3 3.13; spec permits python for the rate arithmetic).
> Append-only during the run.

---

## Pre-Run Commitments — NP18

- **Prompt completion target:** aim A (complete tool, all phases attempted with honest gates).
- **Physics class hoped:** NATIVE on the selection rule; honest OPEN/DEFER expected on the
  cross-condensate coherence span (T3 is flagged UNESTABLISHED in the spec itself).
- **CALIBRATED budget:** ≤1 — reserved for the B_step flux-per-atom absolute, and ONLY because
  the upstream NP19/NP20 that would derive it are still SPEC (see BLOCKER-01). Everything else
  DERIVED/COMPUTED, or MEASURED-INPUT / OBSERVED-TARGET.
- **Engine namespaces used:** `nuclear::alpha_grammar`, `neutrino` (open-winding wake radius,
  W→0), `laws::measured` (c, hbar, alpha, m_e, m_p, MeV_to_J, eV_to_J). No local constant
  namespaces; no redefinition of measured values.

### Phase thresholds (committed BEFORE run)
- **P0:** grammar assertions exact — Be-7 → (n_d,n_t)=(3,−1) with n_t<0 underflow; Li-7 → (0,1)
  on-lattice; single EC vector (Δn_d,Δn_t)=(−3,+2) maps Be-7→Li-7. 478 keV labelled GAMMA
  (Li-7* de-excitation), NOT a neutrino line. Any mismatch → STOP.
- **P1:** R_inc within factor 2 of an independent σ·Φ·n hand check (fail if >10× off).
  Cross-section σ_inc from the resonant inverse-EC line; R_inc = n_e σ_inc Φ_ν. No N² factor.
- **P2:** R_coh/R_inc = N to <1% for ρ_coh≥1 (full span); model reduces EXACTLY to R_inc at N=1
  and at ρ_coh→0 (both limit checks asserted in code). Crossover shown explicitly, not hidden.
- **P3:** finite N* with B_sig(N*) ≥ 10×B_floor (fT) AND ρ_coh(N*)≥1 SIMULTANEOUSLY, else
  PIVOT density/τ; if still unreachable → DEFER to CEνNS scale or OPEN.
- **P4:** deep-K vs shallow-2s B_step signatures differ ≥3× (from NP19/NP20 flux ratio); else
  the stripped-control sub-claim is OPEN.

### Forbidden retroactive changes (audit-fail if done)
- widen tolerances post-run; plug N* to a target; IDENTITY-PASS (re-expose a measured/laws value
  and call it a prediction); import G / M / GM / ψ / field / **G_F** into the SDT chain (G_F is
  OBSERVED-comparison column ONLY); local constant namespaces; relabel the 478 keV gamma as a
  neutrino line; over-claim "virtual particles are fictions in general."

### BLOCKER-01 — upstream siblings unexecuted (logged before coding)
- NP19_Mass_Defect_as_Form_Resistance: **SPEC only** (PROMPT.md, no results).
- NP20_Neutron_From_One_Seat: **SPEC only** (PROMPT.md, no results).
- PPT10_Neutrino_as_Straight_Light: **SPEC only** (PROMPT.md, no results).
- Consequence (per §⑩ pivot table, last row): the **absolute** B_step flux-per-atom is NOT
  derivable in this run. Handle Phase 3 in **dimensionless ratios** (spec §9 explicitly prefers
  this) and DEFER the absolute B_step→fT crossing to NP19/NP20. Any absolute B_step used to
  illustrate the crossing is tagged CALIBRATED(1) and its provenance flagged as PENDING.

---

## Phase execution record

Tool: `np18_rate_fork.py`; stdout captured in `np18_results.txt`. Run 2026-07-01, python3 3.13.

### Phase 0 — Grammar selection rule — **PASS-GATE**
- Be-7 (Z=4,A=7) → alpha_grammar = (n_d,n_t)=(3,−1), valid=False (n_t<0 UNDERFLOW). EXACT.
- Li-7 (Z=3,A=7) → (0,1), valid=True (on-lattice). EXACT.
- EC grammar vector (Δn_d,Δn_t) = (−3,+2). EXACT — single step maps Be-7→Li-7.
- 478 keV (477.6) printed as **Li-7\* → Li-7 de-excitation GAMMA**, NOT a neutrino line. Correct.
- All three committed integer assertions exact → PASS-GATE. **Physics: NATIVE** (zero-parameter
  selection rule straight from `nuclear.hpp`).

### Phase 1 — Incoherent baseline R_inc — **PASS-GATE (with documented ASSUMED bandwidth)**
- λ̄_ν = ħc/E_ν = 2.289e−13 m; λ_ν = 1.438e−12 m at E_ν=0.862 MeV. DERIVED.
- Resonance CEILING σ_peak = λ̄² · g_spin · 4 = 1.048e−25 m² — width-independent, **G_F-free**
  (the wavelength caps the peak; G_F would only set the width). g_spin=0.5 from measured spins.
- EC width Γ_EC = ħ·ln2/t_½ = 1.590e−41 J from the **measured** half-life (no G_F).
- σ_avg = σ_peak·(π/2)·(Γ_EC/dE) = 1.633e−47 m² with dE = 1 eV (ASSUMED cold-trap linewidth).
- Sanity: σ_avg/σ_weak_ref = 0.163 — inside the loose resonance band (pass, well within 10×).
- **Honesty note (not a retro-change):** σ_avg scales with the ASSUMED dE; the *sanity gate*
  therefore has a soft input. The load-bearing Phase-3 result (span) is **independent of dE**.

### Phase 2 — Coherent N-vs-N² law — **PASS-GATE**
- Explicit amplitude-sum form: incoherent rate ∝ N·|a|²; coherent ∝ |Σa|²·span = N²·|a|²·span.
  Multiplier Kcoh(N,ρ) = N + (N²−N)·span(ρ), span=min(ρ,1).
- Limit checks (load-bearing, asserted in code, all True):
  - N=1 (any ρ): Kcoh=1 — recovers single-atom incoherent. EXACT.
  - ρ→0 (N=1e6): Kcoh=N — recovers incoherent N-atom baseline. EXACT.
  - full span ρ≥1 (N=1e6): Kcoh=N² to <1%. EXACT.
- Crossover shown explicitly in the rate table; N² is NOT asserted unconditionally.

### Phase 3 — Divergence N* vs fT floor — **DEFER (T3 span fails) + PENDING (signal blocked)**
- **T3 SPAN GATE FAILS on the tabletop.** λ_ν = 1.438e−12 m vs smallest BEC L ≈ 2.15e−6 m
  ⇒ best ρ_coh = 6.68e−7 over the whole tabletop grid (N=1e4–1e7, n=1e13–1e15 cm⁻³).
  ρ_coh < 1 everywhere by ~6–7 orders → **λ_ν cannot span the condensate.** Whole-condensate
  N² coherence is UNESTABLISHED at achievable BEC parameters. Decision = **DEFER to CEνNS scale**
  (the intra-nucleus regime where q·R≲1 already holds), exactly the §8 honest boundary.
- **Signal side BLOCKED (BLOCKER-01):** absolute B_step needs the NP19/NP20 2s flux-per-atom,
  both still SPEC. No honest absolute N* is claimable. Illustrative crossing shown with a single
  CALIBRATED(1) placeholder B_step=1e−24 T, labelled illustrative-only; even that does not clear
  10×fT at ρ<1 (as expected). Decision = **PENDING / DEFER absolute N\***.
- Combined gate (span AND signal simultaneously) is NOT met → **no PASS**. Rate table shipped.

### Phase 4 — Stripped-Be-7 fork — **PASS (proxy) / OPEN on absolute**
- Seat-size proxy (dimensionless, no absolute B_step): r_2s ≈ 3.18 a₀ (shallow, flux-active)
  vs r_1s ≈ 0.27 a₀ (deep K). Linear ratio 11.75× ; volume ratio 1621×. Both ≥ 3× threshold
  → the deep-K vs shallow-2s signatures ARE distinguishable by the seat-depth proxy.
- Caveat: the absolute B_step and the flux-vs-size exponent are PENDING NP19/NP20. The FORK is
  callable in shape; the absolute is owed. Physics: CONVERGENCE (uses hydrogenic/Slater seat
  sizes, standard atomic input, not a fitted SDT coefficient).

### ADJ entries
- **ADJ-001 — filename/format:** spec §6 lists `np18_rate_fork.cpp (or .py)`. Chose `.py`
  (python3, spec-permitted for rate arithmetic). Engine constants MIRRORED from `laws.hpp`
  with per-line citations (python cannot #include the header). No value refitted. Not a scope
  change; recorded per protocol §3.
- **No pivots fired.** No tolerance was widened; no N* was plugged; no G_F entered the chain.

### Blocker cross-reference
- BLOCKER-01 (NP19/NP20/PPT10 all SPEC) → forced Phase 3 signal-side into DEFER/PENDING and
  Phase 4 absolute into OWED. This matches the §⑩ pivot-table last row ("Upstream missing → DEFER
  the affected phase; cite blocker ID"). Not a failure of the tool — a documented dependency gap.
